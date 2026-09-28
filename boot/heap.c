// The heap: a reserved range of address space cut into 64 KB pages. A page
// holds cells of one size (2 to MAX_WORDS words), or permanent objects
// (literals, closures of global functions) that are never freed.
//
// Collection is mark-sweep and conservative: the roots are every word of
// the evaluator's stack, its registers (setjmp) and the registered root
// slots. A word that points anywhere inside an allocated cell keeps the
// cell. Marking traces a cell's words the same way, so a cell's layout
// does not matter to the collector. Sweeping is lazy: after a collection
// a page's allocated bits are its mark bits, and the allocator hands out
// the cells whose bit is clear as it passes each page.
#include "bendi.h"
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <sys/mman.h>

#define PAGE_BITS 16
#define PAGE_SIZE ((uintptr_t)1 << PAGE_BITS)
#define RESERVE ((uintptr_t)1 << 36)  // 64 GB of address space
#define COMMIT_STEP ((uintptr_t)1 << 26)
#define MAX_WORDS 80
#define BITMAP_WORDS 64                 // PAGE_SIZE / 16 bytes / 64 bits

enum { PG_FREE, PG_SMALL, PG_PERM };

// A page's header, at its start; its cells follow.
typedef struct {
  uint32_t kind, words, ncells, first;  // cell size in words; offset of cell 0 in words
  uint32_t next;                        // the next page of its class's list (page index + 1)
  uint32_t live;                        // cells marked at the last collection
  uint64_t alloc[BITMAP_WORDS];
  uint64_t mark[BITMAP_WORDS];
} Page;

uintptr_t heap_lo, heap_span;
static uintptr_t heap_top, heap_commit;  // pages in use end at heap_top
static size_t npages;

// Per size class: the pages to allocate from (after the cursor), all of
// its pages, and the cursor (page, cell index).
typedef struct {
  uint32_t all;      // list of all its pages (via Page.next)
  uint32_t *queue;   // the pages the allocator still has to pass
  size_t nq, qcap, qi;
  Page *cur;
  uint32_t ci;
} Class;

static Class classes[MAX_WORDS + 1];
static uint32_t *free_pages;
static size_t nfree, free_cap;

static Page *perm_page;
static uint32_t perm_used;

static size_t since_gc, gc_threshold = (size_t)256 << 20, live_bytes, ngc;
static char *stack_base;
static V **roots;
static size_t nroots, roots_cap;

static Page *page_at(size_t i) { return (Page *)(heap_lo + i * PAGE_SIZE); }

void heap_init(void) {
  size_t size = RESERVE;
  void *hint = (void *)((uintptr_t)1 << 45);
  void *p = mmap(hint, size, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
  if (p == MAP_FAILED) die("cannot reserve the heap");
  uintptr_t lo = ((uintptr_t)p + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
  heap_lo = lo;
  heap_span = (uintptr_t)p + size - lo;
  heap_top = heap_commit = lo;
}

void set_stack_base(void *p) { stack_base = p; }

void gc_root(V *slot) {
  if (nroots == roots_cap) { roots_cap = roots_cap ? roots_cap * 2 : 256; roots = xrealloc(roots, roots_cap * sizeof *roots); }
  roots[nroots++] = slot;
}

static Page *new_page(void) {
  if (nfree) return page_at(free_pages[--nfree]);
  if (heap_top + PAGE_SIZE > heap_lo + heap_span) die("out of heap");
  if (heap_top + PAGE_SIZE > heap_commit) {
    if (mprotect((void *)heap_commit, COMMIT_STEP, PROT_READ | PROT_WRITE) != 0) die("out of memory (heap commit)");
    heap_commit += COMMIT_STEP;
  }
  Page *pg = (Page *)heap_top;
  heap_top += PAGE_SIZE;
  npages++;
  return pg;
}

static size_t page_index(Page *pg) { return ((uintptr_t)pg - heap_lo) >> PAGE_BITS; }

static void set_small(Page *pg, int words) {
  memset(pg, 0, sizeof *pg);
  pg->kind = PG_SMALL;
  pg->words = (uint32_t)words;
  pg->first = (uint32_t)((sizeof(Page) + 7) / 8);
  pg->ncells = (uint32_t)((PAGE_SIZE / 8 - pg->first) / (uint32_t)words);
}

static void queue_push(Class *c, uint32_t pi) {
  if (c->nq == c->qcap) { c->qcap = c->qcap ? c->qcap * 2 : 64; c->queue = xrealloc(c->queue, c->qcap * sizeof(uint32_t)); }
  c->queue[c->nq++] = pi;
}

// Collection
// ----------

static int popcount64(uint64_t x) { int n = 0; while (x) { x &= x - 1; n++; } return n; }
static int ctz64(uint64_t x) { int n = 0; while (!(x & 0xffff)) { x >>= 16; n += 16; } while (!(x & 1)) { x >>= 1; n++; } return n; }

static V *mstack;
static size_t msp, mcap;

static inline void mark_word(V w) {
  if (w - heap_lo >= heap_top - heap_lo) return;
  Page *pg = (Page *)(w & ~(PAGE_SIZE - 1));
  if (pg->kind != PG_SMALL) return;
  uintptr_t off = ((w - (uintptr_t)pg) >> 3);
  if (off < pg->first) return;
  uint32_t ci = (uint32_t)((off - pg->first) / pg->words);
  if (ci >= pg->ncells) return;
  uint64_t bit = (uint64_t)1 << (ci & 63);
  if (!(pg->alloc[ci >> 6] & bit) || (pg->mark[ci >> 6] & bit)) return;
  pg->mark[ci >> 6] |= bit;
  if (msp == mcap) { mcap = mcap ? mcap * 2 : 1 << 16; mstack = xrealloc(mstack, mcap * sizeof(V)); }
  mstack[msp++] = (V)((V *)pg + pg->first + (size_t)ci * pg->words);
}

static void mark_range(V *lo, V *hi) {
  for (; lo < hi; lo++) mark_word(*lo);
}

static void drain(void) {
  while (msp) {
    V *cell = (V *)mstack[--msp];
    Page *pg = (Page *)((uintptr_t)cell & ~(PAGE_SIZE - 1));
    mark_range(cell, cell + pg->words);
  }
}

static __attribute__((noinline)) void collect(void) {
  jmp_buf regs;
  setjmp(regs);
  volatile char here = 0;
  for (size_t i = 0; i < npages; i++) {
    Page *pg = page_at(i);
    if (pg->kind == PG_SMALL) memset(pg->mark, 0, sizeof pg->mark);
  }
  mark_range((V *)&regs, (V *)((char *)&regs + sizeof regs));
  drain();
  char *sp = (char *)&here;
  if (stack_base) {
    V *lo = (V *)((uintptr_t)sp & ~(uintptr_t)7);
    mark_range(lo, (V *)stack_base);
    drain();
  }
  for (size_t i = 0; i < nroots; i++) { mark_word(*roots[i]); drain(); }
  // Sweep: the allocated bits become the mark bits; empty pages are freed.
  size_t live = 0;
  nfree = 0;
  for (int w = 2; w <= MAX_WORDS; w++) { classes[w].nq = classes[w].qi = 0; classes[w].cur = 0; classes[w].all = 0; }
  for (size_t i = 0; i < npages; i++) {
    Page *pg = page_at(i);
    if (pg->kind == PG_PERM) continue;
    uint32_t n = 0;
    if (pg->kind == PG_SMALL)
      for (int j = 0; j < BITMAP_WORDS; j++) { pg->alloc[j] = pg->mark[j]; n += (uint32_t)popcount64(pg->mark[j]); }
    if (n == 0) {
      pg->kind = PG_FREE;
      if (nfree == free_cap) { free_cap = free_cap ? free_cap * 2 : 1024; free_pages = xrealloc(free_pages, free_cap * sizeof(uint32_t)); }
      free_pages[nfree++] = (uint32_t)i;
      continue;
    }
    pg->live = n;
    live += (size_t)n * pg->words * 8;
    Class *c = &classes[pg->words];
    pg->next = c->all;
    c->all = (uint32_t)i + 1;
    if (n < pg->ncells) queue_push(c, (uint32_t)i);
  }
  // Pages are reused from the low addresses first.
  for (size_t a = 0, b = nfree ? nfree - 1 : 0; a < b; a++, b--) { uint32_t t = free_pages[a]; free_pages[a] = free_pages[b]; free_pages[b] = t; }
  live_bytes = live;
  gc_threshold = live > ((size_t)256 << 20) ? live : ((size_t)256 << 20);
  since_gc = 0;
  ngc++;
}

// Allocation
// ----------

// The next free cell of the class's current page, or 0.
static inline V *take(Class *c) {
  Page *pg = c->cur;
  if (!pg) return 0;
  uint32_t ci = c->ci;
  while (ci < pg->ncells) {
    uint64_t free = ~pg->alloc[ci >> 6] >> (ci & 63);
    if (free == 0) { ci = (ci | 63) + 1; continue; }
    ci += (uint32_t)ctz64(free);
    if (ci >= pg->ncells) break;
    pg->alloc[ci >> 6] |= (uint64_t)1 << (ci & 63);
    c->ci = ci + 1;
    return (V *)pg + pg->first + (size_t)ci * pg->words;
  }
  c->cur = 0;
  return 0;
}

static V *alloc_slow(int words) {
  Class *c = &classes[words];
  for (;;) {
    V *r = take(c);
    if (r) return r;
    if (c->qi < c->nq) {
      Page *pg = page_at(c->queue[c->qi++]);
      c->cur = pg;
      c->ci = 0;
      since_gc += (size_t)(pg->ncells - pg->live) * pg->words * 8;
      continue;
    }
    if (since_gc > gc_threshold && stack_base) { collect(); continue; }
    Page *pg = new_page();
    set_small(pg, words);
    pg->next = c->all;
    c->all = (uint32_t)page_index(pg) + 1;
    c->cur = pg;
    c->ci = 0;
    since_gc += PAGE_SIZE;
  }
}

V *gc_alloc(int words) {
  if (words < 2) words = 2;
  if (words > MAX_WORDS) die("object too large (%d words)", words);
  V *r = take(&classes[words]);
  if (!r) r = alloc_slow(words);
  memset(r, 0, (size_t)words * 8);  // stale words would keep garbage alive
  return r;
}

V *perm_alloc(int words) {
  size_t need = (size_t)(words < 2 ? 2 : words);
  size_t first = (sizeof(Page) + 7) / 8;
  if (need > PAGE_SIZE / 8 - first) die("permanent object too large");
  if (!perm_page || perm_used + need > PAGE_SIZE / 8) {
    perm_page = new_page();
    memset(perm_page, 0, sizeof *perm_page);
    perm_page->kind = PG_PERM;
    perm_used = (uint32_t)first;
  }
  V *r = (V *)perm_page + perm_used;
  perm_used += (uint32_t)need;
  return r;
}

void gc_stats(void) {
  fprintf(stderr, "bendi: %zu collections, %zu MB live at the last, %zu MB of pages\n", ngc, live_bytes >> 20,
          (npages * PAGE_SIZE) >> 20);
}

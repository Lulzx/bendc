// Bend source to declarations: the lexer, the layout and the parser, each a
// port of bendc.bend's (sections "Lexer", "Layout", "Parser monad",
// "Expressions", "Patterns", "Statements", "Declarations"), and the module
// loader (Main.load, Mod.qualify). `bendi --tokens f` and `bendi --ast f`
// print what `bendc --tokens f` and `bendc --ast f` print, so the two
// front ends can be compared on any file.
#include "bendi.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// Utilities
// =========

void die(const char *fmt, ...) {
  va_list ap;
  fflush(stdout);
  va_start(ap, fmt);
  fputs("bendi: ", stderr);
  vfprintf(stderr, fmt, ap);
  fputc('\n', stderr);
  va_end(ap);
  exit(1);
}

void *xmalloc(size_t n) { void *p = malloc(n ? n : 1); if (!p) die("out of memory"); return p; }
void *xcalloc(size_t n, size_t k) { void *p = calloc(n ? n : 1, k ? k : 1); if (!p) die("out of memory"); return p; }
void *xrealloc(void *p, size_t n) { p = realloc(p, n ? n : 1); if (!p) die("out of memory"); return p; }

void vpush(Vec *v, void *x) {
  if (v->n == v->cap) { v->cap = v->cap ? v->cap * 2 : 8; v->a = xrealloc(v->a, v->cap * sizeof(void *)); }
  v->a[v->n++] = x;
}

// The intern table: open addressing on the text's hash.
static const char **itab;
static size_t icap, icount;

static uint64_t hash_n(const char *s, size_t n) {
  uint64_t h = 1469598103934665603ull;
  for (size_t i = 0; i < n; i++) h = (h ^ (unsigned char)s[i]) * 1099511628211ull;
  return h;
}

const char *intern_n(const char *s, size_t n) {
  if (icount * 2 >= icap) {
    size_t ncap = icap ? icap * 2 : 4096;
    const char **nt = xcalloc(ncap, sizeof *nt);
    for (size_t i = 0; i < icap; i++) {
      if (!itab[i]) continue;
      size_t j = hash_n(itab[i], strlen(itab[i])) & (ncap - 1);
      while (nt[j]) j = (j + 1) & (ncap - 1);
      nt[j] = itab[i];
    }
    free(itab);
    itab = nt;
    icap = ncap;
  }
  size_t j = hash_n(s, n) & (icap - 1);
  while (itab[j]) {
    if (strncmp(itab[j], s, n) == 0 && itab[j][n] == 0) return itab[j];
    j = (j + 1) & (icap - 1);
  }
  char *c = xmalloc(n + 1);
  memcpy(c, s, n);
  c[n] = 0;
  itab[j] = c;
  icount++;
  return c;
}

const char *intern(const char *s) { return intern_n(s, strlen(s)); }

const char *cat(const char *a, const char *b) {
  size_t na = strlen(a), nb = strlen(b);
  char *t = xmalloc(na + nb + 1);
  memcpy(t, a, na);
  memcpy(t + na, b, nb + 1);
  const char *r = intern_n(t, na + nb);
  free(t);
  return r;
}

// Code points to UTF-8 (as the runtime's str_to_c).
static int utf8(uint32_t cp, char *o) {
  if (cp < 0x80) { o[0] = (char)cp; return 1; }
  if (cp < 0x800) { o[0] = (char)(0xc0 | (cp >> 6)); o[1] = (char)(0x80 | (cp & 0x3f)); return 2; }
  if (cp < 0x10000) {
    o[0] = (char)(0xe0 | (cp >> 12)); o[1] = (char)(0x80 | ((cp >> 6) & 0x3f)); o[2] = (char)(0x80 | (cp & 0x3f));
    return 3;
  }
  o[0] = (char)(0xf0 | (cp >> 18)); o[1] = (char)(0x80 | ((cp >> 12) & 0x3f));
  o[2] = (char)(0x80 | ((cp >> 6) & 0x3f)); o[3] = (char)(0x80 | (cp & 0x3f));
  return 4;
}

static const char *cps_name(const uint32_t *cp, int n) {
  char *b = xmalloc((size_t)n * 4 + 1);
  int k = 0;
  for (int i = 0; i < n; i++) k += utf8(cp[i], b + k);
  const char *r = intern_n(b, (size_t)k);
  free(b);
  return r;
}

// A file's bytes as code points, decoded as the runtime's mk_str decodes.
uint32_t *read_source(const char *path, int *np) {
  FILE *f = fopen(path, "rb");
  if (!f) die("cannot read %s", path);
  size_t cap = 1 << 16, n = 0;
  unsigned char *s = xmalloc(cap);
  size_t k;
  while ((k = fread(s + n, 1, cap - n, f)) > 0) {
    n += k;
    if (n == cap) { cap *= 2; s = xrealloc(s, cap); }
  }
  fclose(f);
  uint32_t *cps = xmalloc((n + 1) * sizeof(uint32_t));
  size_t m = 0;
  for (size_t i = 0; i < n;) {
    unsigned char c = s[i];
    uint32_t cp; int len;
    if (c < 0x80) { cp = c; len = 1; }
    else if ((c >> 5) == 6 && i + 1 < n) { cp = c & 0x1f; len = 2; }
    else if ((c >> 4) == 14 && i + 2 < n) { cp = c & 0x0f; len = 3; }
    else if ((c >> 3) == 30 && i + 3 < n) { cp = c & 0x07; len = 4; }
    else { cp = c; len = 1; }
    for (int j = 1; j < len; j++) cp = (cp << 6) | (s[i + j] & 0x3f);
    cps[m++] = cp;
    i += (size_t)len;
  }
  free(s);
  *np = (int)m;
  return cps;
}

// Lexer
// =====
//
// A line's characters become tokens; the tokens of each line go through
// Lex.split (a def or case line with its body after the ':' becomes two
// lines) and Lex.semis (';' outside brackets separates statements).

static int is_alpha(uint32_t c) { return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'); }
static int is_digit(uint32_t c) { return c >= '0' && c <= '9'; }
static int is_ids(uint32_t c) { return is_alpha(c) || c == '_'; }
static int is_idc(uint32_t c) { return is_alpha(c) || is_digit(c) || c == '_' || c == '.'; }

static uint32_t lex_esc(uint32_t y) {
  return y == 'n' ? 10 : y == 't' ? 9 : y == 'r' ? 13 : y == '0' ? 0 : y;
}

static uint32_t hex_digit(uint32_t c) { return c <= 57 ? c - 48 : c >= 97 ? c - 87 : c - 55; }

typedef struct { Tok *a; int n, cap; } Toks;

static void tpush(Toks *v, Tok t) {
  if (v->n == v->cap) { v->cap = v->cap ? v->cap * 2 : 64; v->a = xrealloc(v->a, (size_t)v->cap * sizeof(Tok)); }
  v->a[v->n++] = t;
}

static Tok mk_tok(int k, int sp, uint32_t ln) {
  Tok t;
  memset(&t, 0, sizeof t);
  t.k = (uint8_t)k;
  t.sp = (uint8_t)sp;
  t.line = ln;
  return t;
}

static const char *ops3[] = {".&.", ".|.", ".^.", "<&>", 0};
static const char *ops2[] = {"=>", "->", "<-", "<>", "<=", ">=", "==", "!=", "++", "&&", "||", ">>", "<<", 0};

static int starts(const uint32_t *s, int n, const char *op) {
  int k = (int)strlen(op);
  if (k > n) return 0;
  for (int i = 0; i < k; i++) if (s[i] != (unsigned char)op[i]) return 0;
  return 1;
}

// Digits as text (Lex.dtext), from s[i]; returns the end.
static int dtext(const uint32_t *s, int i, int e) {
  while (i < e && is_digit(s[i])) i++;
  return i;
}

// The tokens of one line (Lex.line), appended to out.
static void lex_line(const uint32_t *s, int i, int e, uint32_t ln, Toks *out) {
  int sp = 1;
  char buf[256];
  while (i < e) {
    uint32_t x = s[i];
    if (x == 32 || x == 9 || x == 13) { i++; sp = 1; continue; }
    if (x == '#') break;
    Tok t = mk_tok(K_SYM, sp, ln);
    if (is_ids(x)) {
      int j = i;
      while (j < e && is_idc(s[j])) j++;
      t.k = K_ID;
      t.s = cps_name(s + i, j - i);
      i = j;
    } else if (is_digit(x)) {
      int j = dtext(s, i, e);
      // ds: the digits less leading zeros (Lex.unzero)
      int d0 = i;
      while (d0 + 1 < j && s[d0] == '0') d0++;
      uint32_t v = 0;
      for (int q = i; q < j; q++) v = v * 10 + (s[q] - 48);
      if (j < e && s[j] == 'n') {
        if (j + 1 < e && s[j + 1] == '+') { t.k = K_NATPLUS; i = j + 2; }
        else { t.k = K_NAT; i = j + 1; }
        t.n = v;
      } else if (j < e && s[j] == '.') {
        int f0 = j + 1, f1 = dtext(s, f0, e);
        int k = 0, q = f1;  // the exponent (Lex.exp)
        char ex[64];
        int nex = 0;
        if (f1 + 1 < e) {
          uint32_t ec = s[f1], c = s[f1 + 1];
          if ((ec | 32) == 'e') {
            int sign = (c == '+' || c == '-') && f1 + 2 < e && is_digit(s[f1 + 2]);
            k = sign ? 1 : is_digit(c) ? 2 : 0;
          }
          if (k == 1) {
            ex[nex++] = 'e'; ex[nex++] = (char)c;
            q = dtext(s, f1 + 2, e);
            for (int z = f1 + 2; z < q && nex < 60; z++) ex[nex++] = (char)s[z];
          } else if (k == 2) {
            ex[nex++] = 'e';
            q = dtext(s, f1 + 1, e);
            for (int z = f1 + 1; z < q && nex < 60; z++) ex[nex++] = (char)s[z];
          }
        }
        int nb = 0;
        for (int z = d0; z < j && nb < 100; z++) buf[nb++] = (char)s[z];
        buf[nb++] = '.';
        for (int z = f0; z < f1 && nb < 200; z++) buf[nb++] = (char)s[z];
        memcpy(buf + nb, ex, (size_t)nex);
        nb += nex;
        t.k = K_FLT;
        t.s = intern_n(buf, (size_t)nb);
        i = q;
      } else {
        t.k = K_NUM;
        t.n = v;
        i = j;
      }
    } else if (x == '\'') {
      // Lex.lit_char, then the closing quote is dropped
      int j = i + 1;
      uint32_t c = 0;
      if (j >= e) { c = 0; }
      else if (s[j] != '\\') { c = s[j]; j++; }
      else {
        j++;
        if (j >= e) c = 92;
        else {
          uint32_t y = s[j++];
          if (y == 'u' && j < e && s[j] == '{') {
            j++;
            c = 0;
            while (j < e && s[j] != '}') c = c * 16 + hex_digit(s[j++]);
            if (j < e) j++;
          } else c = lex_esc(y);
        }
      }
      if (j < e) j++;
      t.k = K_CHR;
      t.n = c;
      i = j;
    } else if (x == '"') {
      // Lex.str: a state machine over the text, to the closing quote or
      // the end of the line
      uint32_t *acc = xmalloc((size_t)(e - i + 2) * sizeof(uint32_t));
      int na = 0, k = 0, j = i + 1;
      uint32_t hv = 0;
      while (j < e && k != 4) {
        uint32_t c = s[j++];
        if (k == 0) {
          if (c == '"') k = 4;
          else if (c == '\\') k = 1;
          else acc[na++] = c;
        } else if (k == 1) {
          if (c == 'u') k = 2;
          else { acc[na++] = lex_esc(c); k = 0; }
        } else if (k == 2) {
          if (c == '{') { k = 3; hv = 0; }
          else {
            acc[na++] = 'u';
            k = 0;
            if (c == '"') k = 4;
            else if (c == '\\') k = 1;
            else acc[na++] = c;
          }
        } else if (k == 3) {
          if (c == '}') { acc[na++] = hv; k = 0; }
          else hv = hv * 16 + hex_digit(c);
        }
      }
      if (k == 1) acc[na++] = 92;
      else if (k == 2) acc[na++] = 'u';
      else if (k == 3) acc[na++] = hv;
      t.k = K_STR;
      t.cp = acc;
      t.len = na;
      i = j;
    } else {
      const char *op = 0;
      for (int q = 0; ops3[q] && !op; q++) if (starts(s + i, e - i, ops3[q])) op = ops3[q];
      for (int q = 0; ops2[q] && !op; q++) if (starts(s + i, e - i, ops2[q])) op = ops2[q];
      if (op) { t.s = intern(op); i += (int)strlen(op); }
      else { t.s = cps_name(s + i, 1); i++; }
    }
    tpush(out, t);
    sp = 0;
  }
}

typedef struct { int ind; uint32_t ln; Tok *t; int n; } Line;
typedef struct { Line *a; int n, cap; } Lines;

static void put_line(Lines *ls, int ind, uint32_t ln, Tok *t, int n) {
  if (n == 0) return;
  if (ls->n == ls->cap) { ls->cap = ls->cap ? ls->cap * 2 : 1024; ls->a = xrealloc(ls->a, (size_t)ls->cap * sizeof(Line)); }
  Line l = {ind, ln, t, n};
  ls->a[ls->n++] = l;
}

static int tok_sym(const Tok *t, const char *s) { return t->k == K_SYM && strcmp(t->s, s) == 0; }
static int tok_id(const Tok *t, const char *s) { return t->k == K_ID && strcmp(t->s, s) == 0; }

// How many tokens end at the first sym outside brackets (0: none); a
// binder's ':' (@x: A, &x: A) is no split (Lex.colon).
static int lex_colon(Tok *t, int n, const char *sym) {
  uint32_t d = 0, b = 0;
  for (int i = 0; i < n; i++) {
    Tok *h = &t[i];
    if (h->k == K_SYM && strcmp(h->s, sym) == 0 && d == 0 && b != 2) return i + 1;
    uint32_t nb = 0;
    if (h->k == K_SYM) {
      const char *x = h->s;
      uint32_t open = !strcmp(x, "(") || !strcmp(x, "[") || !strcmp(x, "{");
      uint32_t close = (!strcmp(x, ")") || !strcmp(x, "]") || !strcmp(x, "}")) && d > 0;
      d = d + open - close;
      if (!strcmp(x, "@") || !strcmp(x, "&")) nb = 1;
      else if (b == 1 && (!strcmp(x, "-") || !strcmp(x, "+"))) nb = 1;
    } else if (h->k == K_ID) nb = b == 1 ? 2 : 0;
    b = nb;
  }
  return 0;
}

static void lex_semis(Lines *ls, int ind, uint32_t ln, Tok *t, int n) {
  for (;;) {
    int k = lex_colon(t, n, ";");
    if (k == 0) { put_line(ls, ind, ln, t, n); return; }
    put_line(ls, ind, ln, t, k - 1);
    t += k;
    n -= k;
  }
}

static Lines lex_lines(const uint32_t *src, int n) {
  Lines ls = {0, 0, 0};
  uint32_t ln = 1;
  for (int i = 0; i <= n; ln++) {
    int e = i;
    while (e < n && src[e] != 10) e++;
    int ind = 0;
    while (i + ind < e && src[i + ind] == 32) ind++;
    Toks ts = {0, 0, 0};
    lex_line(src, i, e, ln, &ts);
    if (ts.n > 0 && tok_sym(&ts.a[ts.n - 1], ";")) ts.n--;  // Lex.semi
    int k = (ts.n > 0 && (tok_id(&ts.a[0], "def") || tok_id(&ts.a[0], "case"))) ? lex_colon(ts.a, ts.n, ":") : 0;
    if (k > 0 && k < ts.n) {
      put_line(&ls, ind, ln, ts.a, k);
      lex_semis(&ls, ind + 2, ln, ts.a + k, ts.n - k);
    } else lex_semis(&ls, ind, ln, ts.a, ts.n);
    i = e + 1;
  }
  return ls;
}

// Layout
// ======
//
// Lines to a token stream with NL / IN / DE (Lay.*). A block level on the
// stack is twice its indent, plus 1 when its first line is a case arm, plus
// 65536 times the bracket depth it opened at.

typedef struct {
  Toks acc;
  uint32_t depth;
  int colon;
  uint32_t *stack;
  int sn, scap;
  int op;
} LS;

static uint32_t lay_top(LS *st) { return st->sn ? st->stack[st->sn - 1] : 0; }
static uint32_t lay_ind(uint32_t h) { return (h & 65535) >> 1; }
static uint32_t lay_bd(uint32_t h) { return h >> 16; }
static void lay_emit(LS *st, int k, uint32_t ln) { tpush(&st->acc, mk_tok(k, 1, ln)); }
static void lay_spush(LS *st, uint32_t h) {
  if (st->sn == st->scap) { st->scap = st->scap ? st->scap * 2 : 64; st->stack = xrealloc(st->stack, (size_t)st->scap * 4); }
  st->stack[st->sn++] = h;
}

// Pops levels deeper than ind, emitting DE for each.
static void lay_pop(LS *st, uint32_t ind, uint32_t ln) {
  while (st->sn && st->stack[st->sn - 1] > ind) { lay_emit(st, K_DE, ln); st->sn--; }
}

// The innermost block of case arms at bracket depth d, else top.
static uint32_t lay_arms(LS *st, uint32_t d) {
  uint32_t top = lay_top(st);
  for (int i = st->sn - 1; i >= 0; i--) {
    uint32_t h = st->stack[i];
    if (lay_bd(h) != d) return top;
    if ((h & 1) == 1) return h;
  }
  return top;
}

static void lay_open(LS *st, uint32_t ind, uint32_t ln, int arm) {
  lay_emit(st, K_IN, ln);
  lay_spush(st, ind * 2 + (arm ? 1 : 0) + st->depth * 65536);
  st->op = 0;
}

static int lay_is_op(const Tok *t) {
  static const char *ops[] = {"->", "=>", "&", "|", "++", "<>", "&&", "||", "+", "*", ",", "=", "<-", 0};
  if (t->k != K_SYM) return 0;
  for (int i = 0; ops[i]; i++) if (!strcmp(t->s, ops[i])) return 1;
  return 0;
}

static int lay_lead_op(const char *x) {
  return !strcmp(x, "&") || !strcmp(x, "->") || !strcmp(x, "|") || !strcmp(x, "++") || !strcmp(x, "<>");
}

// A line opening with an infix operator continues the one before it;
// &x: T -> B is a dependent pair, not a continuation.
static int lay_lead(Tok *t, int n) {
  if (n >= 3 && t[0].k == K_SYM && t[1].k == K_ID && t[2].k == K_SYM)
    return lay_lead_op(t[0].s) && !(!strcmp(t[0].s, "&") && !strcmp(t[2].s, ":"));
  if (n >= 1 && t[0].k == K_SYM) return lay_lead_op(t[0].s);
  return 0;
}

// 0 for a line that opens with case, 1 with return, else 2.
static int lay_stmt(Tok *t, int n) {
  if (n >= 1 && t[0].k == K_ID) return !strcmp(t[0].s, "case") ? 0 : !strcmp(t[0].s, "return") ? 1 : 2;
  return 2;
}

// The start of a line at bracket depth 0 (Lay.start).
static void lay_start(LS *st, uint32_t ind, uint32_t ln, int lead, int stmt) {
  uint32_t ti = lay_ind(lay_top(st));
  int c = ind < ti ? -1 : ind > ti;
  if (st->op) { st->op = 0; return; }
  if (c > 0) {
    if (st->colon) { lay_open(st, ind, ln, stmt == 0); return; }
    if (stmt == 0) {  // a deeper case arm closes the blocks above the innermost arms
      uint32_t a = lay_arms(st, st->depth);
      lay_emit(st, K_NL, ln);
      lay_pop(st, a, ln);
    } else if (stmt == 1) lay_emit(st, K_NL, ln);
    st->op = 0;
    return;
  }
  if (st->colon && ind > 0 && stmt != 0) { lay_open(st, ind, ln, 0); return; }
  if (c == 0) {
    if (!lead) lay_emit(st, K_NL, ln);
  } else {
    lay_emit(st, K_NL, ln);
    lay_pop(st, ind * 2 + 1 + st->depth * 65536, ln);
  }
  st->op = 0;
}

static void lay_toks(LS *st, Tok *t, int n) {
  for (int i = 0; i < n; i++) {
    Tok *h = &t[i];
    uint32_t delta = 0;
    if (h->k == K_SYM) {
      if (!strcmp(h->s, "(") || !strcmp(h->s, "[") || !strcmp(h->s, "{")) delta = 1;
      else if (!strcmp(h->s, ")") || !strcmp(h->s, "]") || !strcmp(h->s, "}")) delta = 4294967295u;
    }
    uint32_t d = st->depth + delta;
    if (d < lay_bd(lay_top(st))) {
      lay_emit(st, K_NL, h->line);
      lay_pop(st, d * 65536 + 65535, h->line);
    }
    int arrow = tok_sym(h, "=>");
    tpush(&st->acc, *h);
    st->depth = d;
    st->colon = tok_sym(h, ":") || arrow;
    st->op = lay_is_op(h) && !arrow;
  }
}

Tok *lex_all(const uint32_t *src, int n, int *ntoks) {
  Lines ls = lex_lines(src, n);
  LS st;
  memset(&st, 0, sizeof st);
  lay_spush(&st, 0);
  for (int i = 0; i < ls.n; i++) {
    Line *l = &ls.a[i];
    uint32_t bd = lay_bd(lay_top(&st));
    if (st.depth == bd) lay_start(&st, (uint32_t)l->ind, l->ln, lay_lead(l->t, l->n), lay_stmt(l->t, l->n));
    else if (st.colon && (uint32_t)l->ind > lay_ind(lay_top(&st))) lay_open(&st, (uint32_t)l->ind, l->ln, 0);
    lay_toks(&st, l->t, l->n);
  }
  lay_emit(&st, K_NL, 0);
  lay_pop(&st, 0, 0);
  lay_emit(&st, K_EOF, 0);
  *ntoks = st.acc.n;
  return st.acc.a;
}

static void put_cps(FILE *out, const uint32_t *cp, int n) {
  char b[4];
  for (int i = 0; i < n; i++) fwrite(b, 1, (size_t)utf8(cp[i], b), out);
}

// As Toks.show, then a newline (bendc prints it).
void show_toks(FILE *out, Tok *ts, int n) {
  for (int i = 0; i < n; i++) {
    Tok *t = &ts[i];
    if (t->sp) fputc(' ', out);
    switch (t->k) {
    case K_ID: case K_FLT: case K_SYM: fputs(t->s, out); break;
    case K_NAT: fprintf(out, "%un", t->n); break;
    case K_NATPLUS: fprintf(out, "%un+", t->n); break;
    case K_NUM: fprintf(out, "%u", t->n); break;
    case K_CHR: fprintf(out, "'%u'", t->n); break;
    case K_STR: fputc('"', out); put_cps(out, t->cp, t->len); fputc('"', out); break;
    case K_NL: fputs("<NL>\n", out); break;
    case K_IN: fputs("<IN>", out); break;
    case K_DE: fputs("<DE>", out); break;
    case K_EOF: fputs("<EOF>", out); break;
    default: fprintf(out, "<ERR %s>", t->s); break;
    }
  }
  fputc('\n', out);
}

// Parser
// ======
//
// Recursive descent over the token array, as bendc's parser monad does it.
// The position is an index and, when a '>>' or '>=' closed type
// arguments, what is left of that token ('>' or '=').

static Tok *T;
static int P, Psub;
static const char *Pfile;

static Tok peek(void) {
  Tok t = T[P];
  if (Psub == 1) { t.k = K_SYM; t.s = ">"; t.sp = 0; }
  else if (Psub == 2) { t.k = K_SYM; t.s = "="; t.sp = 0; }
  return t;
}

static int stuck(Tok t) { return t.k == K_ERR || t.k == K_EOF; }

static void skip(void) {
  Tok t = peek();
  if (stuck(t)) return;
  P++;
  Psub = 0;
}

static void perr(const char *msg) {
  Tok t = peek();
  die("parse error in %s: line %u: %s (got kind %d '%s')", Pfile, t.line, msg, t.k,
      t.k == K_ID || t.k == K_SYM ? t.s : "");
}

static int is_sym(Tok t, const char *s) { return t.k == K_SYM && !strcmp(t.s, s); }
static int is_idt(Tok t, const char *s) { return t.k == K_ID && !strcmp(t.s, s); }

static void expect(const char *s) {
  if (is_sym(peek(), s)) skip();
  else {
    char m[64];
    snprintf(m, sizeof m, "expected '%s'", s);
    perr(m);
  }
}

static int eat(const char *s) {
  if (is_sym(peek(), s)) { skip(); return 1; }
  return 0;
}

static const char *ident(void) {
  Tok t = peek();
  if (t.k != K_ID) perr("expected an identifier");
  skip();
  return t.s;
}

static void nls(void) { while (peek().k == K_NL) skip(); }

// Index of the token's symbol in xs (or the length when absent; 99 when
// not a symbol).
static int which(Tok t, const char **xs) {
  if (t.k != K_SYM) return 99;
  int i = 0;
  for (; xs[i]; i++) if (!strcmp(t.s, xs[i])) return i;
  return i;
}

static int which_id(Tok t, const char **xs) {
  if (t.k != K_ID) return 99;
  int i = 0;
  for (; xs[i]; i++) if (!strcmp(t.s, xs[i])) return i;
  return i;
}

// Syntax builders
// ---------------

static Expr *ex(int k) { Expr *e = xcalloc(1, sizeof *e); e->k = k; return e; }
static Pat *px(int k) { Pat *p = xcalloc(1, sizeof *p); p->k = k; return p; }

static Expr *e_var(const char *n) { Expr *e = ex(E_VAR); e->name = intern(n); return e; }
static Expr *e_ty(const char *n, int na, Expr **as) { Expr *e = ex(E_TY); e->name = intern(n); e->nargs = na; e->args = as; return e; }

static Expr **arr2(Expr *a, Expr *b) { Expr **r = xmalloc(2 * sizeof *r); r[0] = a; r[1] = b; return r; }

static Expr *e_ctor(const char *n, int na, Expr **as) { Expr *e = ex(E_CTOR); e->name = intern(n); e->nargs = na; e->args = as; return e; }
static Expr *e_call(Expr *f, int na, Expr **as) { Expr *e = ex(E_CALL); e->f = f; e->nargs = na; e->args = as; return e; }

static Pat *p_ctor(const char *n, int na, Pat **as) { Pat *p = px(P_CTOR); p->name = intern(n); p->nargs = na; p->args = as; return p; }
static Pat *p_var(const char *n) { Pat *p = px(P_VAR); p->name = intern(n); return p; }

static Expr **vec_exprs(Vec v) { return (Expr **)v.a; }

// Type head name of a type expression (P.head).
static const char *p_head(Expr *e) {
  if (e->k == E_VAR) return e->name;
  if (e->k == E_CALL && e->f->k == E_VAR) return e->f->name;
  if (e->k == E_TY) return e->name;
  return intern("");
}

const char *ty_head(Expr *e) {
  if (e->k == E_VAR || e->k == E_TY) return e->name;
  if (e->k == E_CALL && e->f->k == E_VAR) return e->f->name;
  return intern("?");
}

static Expr *p_tuple(Expr **xs, int n) {
  if (n == 0) return e_ctor("Unit", 0, 0);
  if (n == 1) return xs[0];
  return e_ctor("Tuple", 2, arr2(xs[0], p_tuple(xs + 1, n - 1)));
}

static Pat *p_ptuple(Pat **xs, int n) {
  if (n == 0) return p_ctor("Unit", 0, 0);
  if (n == 1) return xs[0];
  Pat **r = xmalloc(2 * sizeof *r);
  r[0] = xs[0];
  r[1] = p_ptuple(xs + 1, n - 1);
  return p_ctor("Tuple", 2, r);
}

static Expr *p_elist(Expr **xs, int n) {
  if (n == 0) return e_ctor("Nil", 0, 0);
  return e_ctor("Con", 2, arr2(xs[0], p_elist(xs + 1, n - 1)));
}

static Pat *p_plist(Pat **xs, int n) {
  if (n == 0) return p_ctor("Nil", 0, 0);
  Pat **r = xmalloc(2 * sizeof *r);
  r[0] = xs[0];
  r[1] = p_plist(xs + 1, n - 1);
  return p_ctor("Con", 2, r);
}

// A string literal pattern: a chain of SCon cells.
static Pat *p_pstr(const uint32_t *s, int n) {
  if (n == 0) return p_ctor("SNil", 0, 0);
  Pat *num = px(P_NUM);
  num->n = s[0];
  Pat **c = xmalloc(sizeof *c);
  c[0] = num;
  Pat **r = xmalloc(2 * sizeof *r);
  r[0] = p_ctor("Chr", 1, c);
  r[1] = p_pstr(s + 1, n - 1);
  return p_ctor("SCon", 2, r);
}

// Patterns
// --------

static Pat *pat(void);

static Pat **pats(const char *close, int *np) {
  Vec v = {0, 0, 0};
  for (;;) {
    Tok t = peek();
    if (stuck(t)) break;
    if (is_sym(t, close)) { skip(); break; }
    vpush(&v, pat());
    if (!eat(",")) { expect(close); break; }
  }
  *np = v.n;
  return (Pat **)v.a;
}

static Pat *pat1(void) {
  Tok t = peek();
  Pat *p;
  static const char *syms[] = {"+", "-", "(", "[", 0};
  switch (t.k) {
  case K_ID: {
    skip();
    Tok u = peek();
    if (is_sym(u, "{") && !u.sp) {
      skip();
      int n;
      Pat **as = pats("}", &n);
      return p_ctor(t.s, n, as);
    }
    return p_var(t.s);
  }
  case K_NAT: skip(); p = px(P_NAT); p->n = t.n; return p;
  case K_NATPLUS: {
    skip();
    p = px(P_SUCC);
    p->n = t.n;
    p->nargs = 1;
    p->args = xmalloc(sizeof(Pat *));
    p->args[0] = pat1();
    return p;
  }
  case K_NUM: skip(); p = px(P_NUM); p->n = t.n; return p;
  case K_FLT: skip(); p = px(P_FLT); p->name = t.s; return p;
  case K_CHR: {
    skip();
    Pat *num = px(P_NUM);
    num->n = t.n;
    Pat **c = xmalloc(sizeof *c);
    c[0] = num;
    return p_ctor("Chr", 1, c);
  }
  case K_STR: skip(); return p_pstr(t.cp, t.len);
  case K_SYM: {
    int k = which(t, syms), n;
    if (k == 0 || k == 1) { skip(); return pat1(); }
    if (k == 2) { skip(); Pat **ps = pats(")", &n); return p_ptuple(ps, n); }
    if (k == 3) { skip(); Pat **ps = pats("]", &n); return p_plist(ps, n); }
    break;
  }
  }
  perr("expected a pattern");
  return 0;
}

static Pat *pat(void) {
  Pat *p = pat1();
  if (is_sym(peek(), "<>")) {
    skip();
    Pat **r = xmalloc(2 * sizeof *r);
    r[0] = p;
    r[1] = pat();
    return p_ctor("Con", 2, r);
  }
  return p;
}

// Space-separated patterns up to (not including) one of the stop symbols.
static Pat **pat_seq(const char **stops, int *np) {
  Vec v = {0, 0, 0};
  int ns = 0;
  while (stops[ns]) ns++;
  for (;;) {
    Tok t = peek();
    if (stuck(t) || t.k == K_NL || which(t, stops) < ns) break;
    vpush(&v, pat());
    eat(",");
  }
  *np = v.n;
  return (Pat **)v.a;
}

// Statements
// ----------

enum { S_LET, S_BIND, S_RET, S_EXP, S_SKIP };
typedef struct { int k; Pat *pat; const char *name; Expr *e; } Stmt;

static Stmt *st_new(int k, Pat *p, const char *name, Expr *e) {
  Stmt *s = xmalloc(sizeof *s);
  s->k = k; s->pat = p; s->name = name; s->e = e;
  return s;
}

static Expr *e_let(Pat *p, Expr *v, Expr *b) { Expr *e = ex(E_LET); e->pat = p; e->a = v; e->b = b; return e; }
static Expr *e_lam(Pat *p, Expr *b) { Expr *e = ex(E_LAM); e->pat = p; e->a = b; return e; }

// Folds a statement list into an expression (Fold.plain).
static Expr *fold_plain(Stmt **ss, int n) {
  if (n == 0) { Expr *e = ex(E_ERR); e->name = intern("empty block"); return e; }
  Stmt *s = ss[0];
  if (n == 1) {
    if (s->k == S_SKIP) return e_ty("", 0, 0);
    return s->e;
  }
  switch (s->k) {
  case S_LET: return e_let(s->pat, s->e, fold_plain(ss + 1, n - 1));
  case S_BIND: return e_let(p_var(s->name), s->e, fold_plain(ss + 1, n - 1));
  case S_RET: return s->e;
  case S_EXP: return e_let(p_var("_"), s->e, fold_plain(ss + 1, n - 1));
  default: return fold_plain(ss + 1, n - 1);
  }
}

static Expr *fold_app(const char *m, const char *f, Expr **xs, int nx, Expr **ys, int ny) {
  Expr **as = xmalloc((size_t)(nx + ny + 1) * sizeof *as);
  memcpy(as, xs, (size_t)nx * sizeof *as);
  memcpy(as + nx, ys, (size_t)ny * sizeof *as);
  char buf[512];
  snprintf(buf, sizeof buf, "%s.%s", m, f);
  return e_call(e_var(buf), nx + ny, as);
}

// Folds a do block's statements into binds of its monad (Fold.do).
static Expr *fold_do(const char *m, Expr **xs, int nx, Expr *r, Stmt **ss, int n) {
  if (n == 0) { Expr *e = ex(E_ERR); e->name = intern("empty do block"); return e; }
  Stmt *s = ss[0];
  Expr *ys[4];
  if (n == 1) {
    switch (s->k) {
    case S_RET: ys[0] = r; ys[1] = s->e; return fold_app(m, "pure", xs, nx, ys, 2);
    case S_SKIP: return e_ty("", 0, 0);
    default: return s->e;
    }
  }
  switch (s->k) {
  case S_LET: return e_let(s->pat, s->e, fold_do(m, xs, nx, r, ss + 1, n - 1));
  case S_BIND:
    ys[0] = e_ty("", 0, 0); ys[1] = r; ys[2] = s->e;
    ys[3] = e_lam(p_var(s->name), fold_do(m, xs, nx, r, ss + 1, n - 1));
    return fold_app(m, "bind", xs, nx, ys, 4);
  case S_RET: ys[0] = r; ys[1] = s->e; return fold_app(m, "pure", xs, nx, ys, 2);
  case S_EXP:
    ys[0] = e_ty("", 0, 0); ys[1] = r; ys[2] = s->e;
    ys[3] = e_lam(p_var("_"), fold_do(m, xs, nx, r, ss + 1, n - 1));
    return fold_app(m, "bind", xs, nx, ys, 4);
  default: return fold_do(m, xs, nx, r, ss + 1, n - 1);
  }
}

// Expressions
// -----------

static Expr *expr(void);
static Expr *iexpr(void);
static Expr *term(void);
static Stmt **stmts(int *n);
static Expr *match_expr(void);

typedef struct { const char *op; int prec, right; } OpInfo;
static const OpInfo opinfo[] = {
  {"->", 1, 1}, {"|", 2, 1}, {"&", 3, 1}, {"<&>", 3, 1}, {"||", 4, 0}, {"&&", 5, 0}, {"<>", 6, 1},
  {"++", 6, 1}, {"<", 7, 0}, {"<=", 7, 0}, {">", 7, 0}, {">=", 7, 0}, {".|.", 8, 0}, {".^.", 9, 0},
  {".&.", 10, 0}, {"<<", 11, 0}, {">>", 11, 0}, {"+", 12, 0}, {"-", 12, 0}, {"*", 13, 0}, {"/", 13, 0},
  {"%", 13, 0}, {0, 0, 0}};

static Expr *mk_bin(const char *op, Expr *a, Expr *b) {
  if (!strcmp(op, "->") || !strcmp(op, "|") || !strcmp(op, "&")) return e_ty(op, 2, arr2(a, b));
  if (!strcmp(op, "<&>")) return e_ty("#q", 0, 0);
  if (!strcmp(op, "||")) return e_call(e_var("Bool.or"), 2, arr2(a, b));
  if (!strcmp(op, "&&")) return e_call(e_var("Bool.and"), 2, arr2(a, b));
  if (!strcmp(op, "<>")) return e_ctor("Con", 2, arr2(a, b));
  if (!strcmp(op, "++")) return e_call(e_var("String.append"), 2, arr2(a, b));
  Expr *e = ex(E_OP);
  e->name = intern(op);
  e->a = a;
  e->b = b;
  return e;
}

static Expr *bin(int min) {
  Expr *lhs = term();
  for (;;) {
    Tok t = peek();
    const OpInfo *o = 0;
    if (t.k == K_SYM && t.sp)
      for (int i = 0; opinfo[i].op; i++) if (!strcmp(opinfo[i].op, t.s)) { o = &opinfo[i]; break; }
    if (!o || o->prec < min) return lhs;
    skip();
    Expr *rhs = bin(o->right ? o->prec : o->prec + 1);
    lhs = mk_bin(o->op, lhs, rhs);
  }
}

static Expr *expr(void) { return bin(1); }

// Comma-separated expressions up to (and including) a closing symbol.
static Expr **list(const char *close, int *np) {
  Vec v = {0, 0, 0};
  for (;;) {
    Tok t = peek();
    if (stuck(t)) perr("unterminated list");
    if (is_sym(t, close)) { skip(); break; }
    vpush(&v, expr());
    if (!eat(",")) { expect(close); break; }
  }
  *np = v.n;
  return vec_exprs(v);
}

// Closes type arguments: a '>', or the first half of a '>>' or '>='.
static void p_gt(void) {
  static const char *gts[] = {">", ">>", ">=", 0};
  Tok t = peek();
  int k = which(t, gts);
  if (k == 0) skip();
  else if (k == 1) Psub = 1;
  else if (k == 2) Psub = 2;
  else perr("expected '>'");
}

static int is_gt(Tok t) { return is_sym(t, ">") || is_sym(t, ">>") || is_sym(t, ">="); }

// Type arguments after '<', up to '>'.
static Expr **tyargs(int *np) {
  Vec v = {0, 0, 0};
  for (;;) {
    Tok t = peek();
    if (stuck(t)) break;
    if (is_gt(t)) { p_gt(); break; }
    vpush(&v, expr());
    if (!eat(",")) { p_gt(); break; }
  }
  *np = v.n;
  return vec_exprs(v);
}

// A block body: an indented statement list, folded.
static Expr *body_block(void) {
  if (peek().k != K_IN) perr("expected an indented block");
  skip();
  int n;
  Stmt **ss = stmts(&n);
  return fold_plain(ss, n);
}

static Expr *do_block(void) {
  skip();
  const char *m = ident();
  expect("<");
  int na;
  Expr **args = tyargs(&na);
  expect(":");
  if (peek().k != K_IN) perr("expected an indented block");
  skip();
  int n;
  Stmt **ss = stmts(&n);
  Expr *r = na > 0 ? args[na - 1] : e_ty("", 0, 0);
  return fold_do(m, args, na > 0 ? na - 1 : 0, r, ss, n);
}

// Whether an expression opens with 'pat = value;' (P.lscan).
static int lscan(void) {
  static const char *ks[] = {"=", "(", "[", "{", ")", "]", "}", ";", ",", "=>", 0};
  uint32_t depth = 0;
  for (int i = P;; i++) {
    Tok t = T[i];
    if (i == P && Psub) return 0;
    if (t.k == K_SYM) {
      int k = which(t, ks);
      int end = k == 0 ? 1 : k <= 3 ? 0 : (depth == 0 && k - 4 < 6);
      if (end) return k == 0 && depth == 0;
      if (k >= 1 && k <= 3) depth++;
      else if (k >= 4 && k <= 6) depth--;
    } else if (t.k == K_NL || t.k == K_IN || t.k == K_DE || t.k == K_EOF) return 0;
  }
}

static void skip_ann(void) {
  if (is_sym(peek(), ":")) { skip(); expr(); }
}

static Expr *ilet(void) {
  eat("-");
  eat("+");
  Pat *p = pat();
  skip_ann();
  expect("=");
  Expr *v = expr();
  expect(";");
  Expr *b = iexpr();
  return e_let(p, v, b);
}

// An expression that may open with lets: x = a; y : T = b; e.
static Expr *iexpr(void) { return lscan() ? ilet() : expr(); }

static Expr *neg(Expr *e) {
  if (e->k == E_NUM) { e->n = 0 - e->n; return e; }
  if (e->k == E_FLT) { e->name = cat("-", e->name); return e; }
  return e;
}

// '@x: A -> B' and '&x: A -> B' (dependent types): only their shape is
// kept, as bendc keeps it (P.dep.fin).
static Expr *dep(int amp) {
  int e1 = eat("-");
  eat("+");
  const char *x = ident();
  expect(":");
  Expr *ty = expr();
  if (amp) {
    if (ty->k == E_TY && !strcmp(ty->name, "->") && ty->nargs == 2) {
      Expr **as = xmalloc(4 * sizeof *as);
      as[0] = e_ty("#q", 0, 0);
      as[1] = e_ty("#q", 0, 0);
      as[2] = ty->args[0];
      as[3] = e_lam(p_var(x), ty->args[1]);
      return e_ty("Sigma", 4, as);
    }
    return e_ty("", 0, 0);
  }
  if (e1 && ty->k == E_TY && !strcmp(ty->name, "->") && ty->nargs == 2) {
    Expr *b = ty->args[1];
    const char *mark = "";
    if (b->k == E_TY && !*b->name && b->nargs == 1 && b->args[0]->k == E_TY && b->args[0]->nargs == 0)
      mark = b->args[0]->name;
    Expr **as = xmalloc(sizeof *as);
    as[0] = e_ty(cat("@-", mark), 0, 0);
    return e_ty("", 1, as);
  }
  return e_ty("", 0, 0);
}

static Expr *paren(void) {
  static const char *ks[] = {",", ":", 0};
  skip();
  if (is_sym(peek(), ")")) { skip(); return e_ctor("Unit", 0, 0); }
  Expr *e = iexpr();
  int k = which(peek(), ks);
  if (k == 1) {
    skip();
    Expr *ty = expr();
    expect(")");
    Expr *a = ex(E_ANN);
    a->a = e;
    a->name = p_head(ty);
    return a;
  }
  if (k != 0) { expect(")"); return e; }
  skip();
  Vec v = {0, 0, 0};
  vpush(&v, e);
  for (;;) {  // the elements after the first ',': (a, b, c : T) annotates c alone
    if (is_sym(peek(), ")")) { skip(); break; }
    Expr *x = iexpr();
    int j = which(peek(), ks);
    if (j == 0) { skip(); vpush(&v, x); continue; }
    if (j == 1) {
      skip();
      Expr *ty = expr();
      expect(")");
      Expr *a = ex(E_ANN);
      a->a = x;
      a->name = p_head(ty);
      vpush(&v, a);
      break;
    }
    expect(")");
    vpush(&v, x);
    break;
  }
  return p_tuple((Expr **)v.a, v.n);
}

static Expr *brack(void) {
  skip();
  if (is_sym(peek(), "]")) { skip(); return e_ctor("Nil", 0, 0); }
  Expr *e = expr();
  if (is_sym(peek(), ":")) {  // [v : T*n] / [v : T^d]
    skip();
    Expr *ty = term();
    Tok t = peek();
    skip();
    Tok t2 = peek();
    Expr *d;
    if (is_sym(t, "^")) d = term();
    else {
      if (t2.k != K_NAT) perr("expected an array size");
      skip();
      uint32_t lg = 0, n = t2.n;
      while (n > 1) { lg++; n >>= 1; }
      d = ex(E_NAT);
      d->n = lg;
    }
    expect("]");
    Expr *a = ex(E_ANN);
    a->a = e;
    a->name = p_head(ty);
    Expr **as = xmalloc(3 * sizeof *as);
    as[0] = e_ty("", 0, 0);
    as[1] = d;
    as[2] = a;
    return e_call(e_var("Array.new"), 3, as);
  }
  eat(",");
  int n;
  Expr **rest = list("]", &n);
  Vec v = {0, 0, 0};
  vpush(&v, e);
  for (int i = 0; i < n; i++) vpush(&v, rest[i]);
  return p_elist((Expr **)v.a, v.n);
}

static Expr *brace(void) {
  static const char *ks[] = {"==", "!=", ":", 0};
  skip();
  if (is_sym(peek(), "==")) { skip(); expect("}"); return e_ty("", 0, 0); }
  Expr *e = expr();
  int k = which(peek(), ks);
  if (k == 0 || k == 1) {
    skip();
    expr();
    expect(":");
    expr();
    expect("}");
    return e_ty(k == 0 ? "==" : "", 0, 0);
  }
  if (k == 2) {
    skip();
    Expr *ty = expr();
    expect("}");
    Expr *a = ex(E_ANN);
    a->a = e;
    a->name = p_head(ty);
    return a;
  }
  expect("}");
  return e;
}

// The arms of \{K: h; ...; m} after its '{'.
static Expr *lmat(void) {
  nls();
  Tok t = peek();
  if (is_sym(t, "}")) { skip(); return e_ctor("%efq", 0, 0); }
  if (t.k == K_ID && is_sym(T[P + 1], ":") && !Psub) {
    const char *c = ident();
    expect(":");
    Expr *h = expr();
    eat(";");
    Expr *m = lmat();
    Expr **as = xmalloc(3 * sizeof *as);
    as[0] = e_ctor(c, 0, 0);
    as[1] = h;
    as[2] = m;
    return e_ctor("%mat", 3, as);
  }
  Expr *e = expr();
  eat(";");
  expect("}");
  return e;
}

// A rewrite %e@E : P; f (or %E : P; f) is its tail f.
static Expr *rw(void) {
  skip();
  term();
  if (is_sym(peek(), "@")) { skip(); term(); }
  expect(":");
  expr();
  if (is_sym(peek(), ";")) { skip(); return iexpr(); }
  return e_ctor("Unit", 0, 0);
}

static Expr *primary(void) {
  static const char *syms[] = {"(", "[", "{", "~", "+", "-", "@", "&", "?", "\\", "%", 0};
  static const char *after[] = {"{", "<", 0};
  Tok t = peek();
  Expr *e;
  switch (t.k) {
  case K_ID: {
    if (!strcmp(t.s, "do")) return do_block();
    skip();
    Tok u = peek();
    if (is_sym(u, "=>")) {  // a lambda: an expression, or a block below its '=>'
      skip();
      Expr *body = peek().k == K_IN ? body_block() : iexpr();
      return e_lam(p_var(t.s), body);
    }
    int k = u.sp ? 3 : which(u, after);
    int n;
    if (k == 0) { skip(); Expr **as = list("}", &n); return e_ctor(t.s, n, as); }
    if (k == 1) { skip(); Expr **as = tyargs(&n); return e_ty(t.s, n, as); }
    return e_var(t.s);
  }
  case K_NUM: skip(); e = ex(E_NUM); e->n = t.n; return e;
  case K_NAT: skip(); e = ex(E_NAT); e->n = t.n; return e;
  case K_NATPLUS: skip(); e = ex(E_SUCC); e->n = t.n; e->a = term(); return e;
  case K_FLT: skip(); e = ex(E_FLT); e->name = t.s; return e;
  case K_CHR: {
    skip();
    Expr *num = ex(E_NUM);
    num->n = t.n;
    Expr **as = xmalloc(sizeof *as);
    as[0] = num;
    return e_ctor("Chr", 1, as);
  }
  case K_STR: skip(); e = ex(E_STR); e->str = t.cp; e->slen = t.len; return e;
  case K_SYM:
    switch (which(t, syms)) {
    case 0: return paren();
    case 1: return brack();
    case 2: return brace();
    case 3: case 4: skip(); return term();
    case 5: skip(); return neg(term());
    case 6: skip(); return dep(0);
    case 7: {
      skip();
      if (peek().k == K_NUM) { skip(); return e_ty("#q", 0, 0); }
      return dep(1);
    }
    case 8: skip(); ident(); return e_ty("", 0, 0);
    case 9: skip(); expect("{"); return lmat();
    case 10: return rw();
    }
    perr("unexpected symbol");
  }
  perr("expected an expression");
  return 0;
}

// Postfix: calls f(..), f!(..), and indexing a[i] (or the write a[i] <- v).
static Expr *postfix(Expr *e) {
  static const char *ks[] = {"(", "!", "[", 0};
  for (;;) {
    Tok t = peek();
    int k = t.sp ? 9 : which(t, ks);
    int n;
    if (k == 0) { skip(); Expr **as = list(")", &n); e = e_call(e, n, as); }
    else if (k == 1) {
      skip();
      expect("(");
      Expr **as = list(")", &n);
      Expr **bs = xmalloc((size_t)(n + 1) * sizeof *bs);
      bs[0] = e;
      memcpy(bs + 1, as, (size_t)n * sizeof *bs);
      e = e_call(e_var("%gpu"), n + 1, bs);
    } else if (k == 2) {
      skip();
      Expr *i = expr();
      expect("]");
      if (is_sym(peek(), "<-")) {
        skip();
        Expr *v = expr();
        Expr **as = xmalloc(4 * sizeof *as);
        as[0] = e_ty("U32", 0, 0); as[1] = e; as[2] = i; as[3] = v;
        return e_call(e_var("Array.set"), 4, as);
      }
      Expr **as = xmalloc(3 * sizeof *as);
      as[0] = e_ty("U32", 0, 0); as[1] = e; as[2] = i;
      e = e_call(e_var("Array.get"), 3, as);
    } else return e;
  }
}

static Expr *term(void) { return postfix(primary()); }

static Expr *match_expr(void) {
  skip();
  Vec scrs = {0, 0, 0};
  for (;;) {
    Tok t = peek();
    if (is_sym(t, ":") || stuck(t)) break;
    vpush(&scrs, expr());
    eat(",");
  }
  expect(":");
  Vec cases = {0, 0, 0};
  if (peek().k == K_IN) {
    skip();
    static const char *stops[] = {":", 0};
    for (;;) {
      nls();
      Tok t = peek();
      if (t.k == K_DE) { skip(); break; }
      if (!is_idt(t, "case")) break;
      skip();
      Expr *c = ex(E_CASE);
      c->pats = pat_seq(stops, &c->npats);
      expect(":");
      c->a = body_block();
      vpush(&cases, c);
    }
  }
  Expr *m = ex(E_MATCH);
  m->nargs = scrs.n;
  m->args = vec_exprs(scrs);
  m->ncases = cases.n;
  m->cases = vec_exprs(cases);
  return m;
}

// Finds the first '=' or '<-' at depth 0 on the current line: 0 none, 1
// '=', 2 '<-' (P.scan); a '<-' after a line's leading '(' is an array
// write, not a bind.
static int scan(void) {
  static const char *ks[] = {"=", "<-", "(", "[", "{", ")", "]", "}", 0};
  uint32_t depth = 0;
  int r = 0;
  for (int i = P;; i++) {
    Tok t = T[i];
    if (i == P && Psub) break;
    if (t.k == K_SYM) {
      int k = which(t, ks);
      if (k < 2 && depth == 0) { r = k == 0 ? 1 : 2; break; }
      if (k >= 2 && k <= 4) depth++;
      else if (k >= 5 && k <= 7) depth--;
    } else if (t.k == K_NL) {
      if (depth == 0) break;
    } else if (t.k == K_IN || t.k == K_DE || t.k == K_EOF || t.k == K_ERR) break;
  }
  if (is_sym(peek(), "(") && r == 2) return 0;
  return r;
}

static void skip_block(int depth) {
  for (;;) {
    Tok t = peek();
    if (t.k == K_EOF) return;
    skip();
    if (t.k == K_IN) depth++;
    else if (t.k == K_DE) { if (depth == 1) return; depth--; }
  }
}

// Skips the rest of the line (up to, not including, the newline).
static void skip_line(void) {
  for (;;) {
    Tok t = peek();
    if (t.k == K_NL || t.k == K_DE || t.k == K_EOF || t.k == K_ERR) return;
    skip();
    if (t.k == K_IN) { skip_block(1); return; }
  }
}

static Stmt **one(Stmt *s) { Stmt **r = xmalloc(sizeof *r); r[0] = s; return r; }

static Stmt **stmt(int *n) {
  static const char *ks[] = {"match", "return", "do", 0};
  Tok t = peek();
  *n = 1;
  if (is_sym(t, "%")) { skip_line(); return one(st_new(S_SKIP, 0, 0, 0)); }
  switch (which_id(t, ks)) {
  case 0: return one(st_new(S_EXP, 0, 0, match_expr()));
  case 1: skip(); return one(st_new(S_RET, 0, 0, expr()));
  case 2: return one(st_new(S_EXP, 0, 0, do_block()));
  }
  int k = scan();
  if (k == 0) return one(st_new(S_EXP, 0, 0, expr()));
  if (k == 1) {  // pats = values (a parallel let when two or more)
    static const char *stops[] = {"=", ":", 0};
    int np;
    Pat **ps = pat_seq(stops, &np);
    skip_ann();
    expect("=");
    Expr **vs = xmalloc((size_t)(np + 1) * sizeof *vs);
    for (int i = 0; i < np; i++) vs[i] = expr();
    if (np > 1) return one(st_new(S_LET, p_ctor("%par", np, ps), 0, e_ctor("%par", np, vs)));
    Stmt **r = xmalloc((size_t)(np + 1) * sizeof *r);
    for (int i = 0; i < np; i++) r[i] = st_new(S_LET, ps[i], 0, vs[i]);
    *n = np;
    return r;
  }
  eat("+");
  const char *name = ident();
  Tok u = peek();
  if (is_sym(u, "[") && !u.sp) {  // a[i] <- v
    skip();
    Expr *i = expr();
    expect("]");
    expect("<-");
    Expr *v = expr();
    Expr **as = xmalloc(4 * sizeof *as);
    as[0] = e_ty("U32", 0, 0); as[1] = e_var(name); as[2] = i; as[3] = v;
    return one(st_new(S_LET, p_var(name), 0, e_call(e_var("Array.set"), 4, as)));
  }
  skip_ann();
  expect("<-");
  return one(st_new(S_BIND, 0, name, expr()));
}

// Statements up to (and including) the block's dedent.
static Stmt **stmts(int *np) {
  Vec v = {0, 0, 0};
  for (;;) {
    nls();
    Tok t = peek();
    if (t.k == K_DE) { skip(); break; }
    if (stuck(t)) break;
    int n;
    Stmt **ss = stmt(&n);
    for (int i = 0; i < n; i++) vpush(&v, ss[i]);
  }
  *np = v.n;
  return (Stmt **)v.a;
}

// Declarations
// ------------

static Param param(void) {
  Tok t = peek();
  int mode = is_sym(t, "-") ? 1 : is_sym(t, "+") ? 2 : is_sym(t, "~") ? 3 : 0;
  if (mode) skip();
  Param p;
  p.name = ident();
  if (is_sym(peek(), ":")) {
    skip();
    Expr *ty = expr();
    p.mode = mode;
    // P.phead: the marker of a '@-x: A -> B', else the head
    if (ty->k == E_TY && !*ty->name && ty->nargs == 1 && ty->args[0]->k == E_TY && ty->args[0]->nargs == 0)
      p.ty = ty->args[0]->name;
    else p.ty = p_head(ty);
  } else {
    p.mode = mode == 0 ? 4 : mode;
    p.ty = intern("");
  }
  return p;
}

static Param *params(int *np) {
  int n = 0, cap = 8;
  Param *ps = xmalloc((size_t)cap * sizeof *ps);
  for (;;) {
    Tok t = peek();
    if (is_sym(t, ")") || stuck(t)) { skip(); break; }
    if (n == cap) { cap *= 2; ps = xrealloc(ps, (size_t)cap * sizeof *ps); }
    ps[n++] = param();
    if (!eat(",")) { expect(")"); break; }
  }
  *np = n;
  return ps;
}

static Decl *dnew(int k) { Decl *d = xcalloc(1, sizeof *d); d->k = k; return d; }

static Decl *p_def(void) {
  skip();
  Decl *d = dnew(D_DEF);
  d->name = ident();
  eat("?");
  expect("(");
  d->ps = params(&d->nps);
  if (is_sym(peek(), "->")) { skip(); d->ret = expr(); }
  else d->ret = e_ty("", 0, 0);
  expect(":");
  if (peek().k != K_IN) perr("expected an indented block");
  skip();
  if (is_idt(peek(), "import")) {  // a foreign def: the files it imports
    d->k = D_EFF;
    for (;;) {
      Tok t = peek();
      if (t.k == K_DE) { skip(); break; }
      if (stuck(t)) break;
      skip();
    }
    return d;
  }
  int n;
  Stmt **ss = stmts(&n);
  d->body = fold_plain(ss, n);
  return d;
}

static Decl *p_type(void) {
  skip();
  Decl *d = dnew(D_TYPE);
  d->name = ident();
  Tok t0 = peek();
  if (is_sym(t0, "<") || is_sym(t0, "<-")) {
    skip();
    for (;;) {  // type parameters
      eat("-");
      ident();
      skip_ann();
      if (!eat(",")) { p_gt(); break; }
    }
  }
  for (;;) {  // to just after 'is'
    Tok t = peek();
    if (stuck(t)) break;
    skip();
    if (is_idt(t, "is")) break;
  }
  expr();
  expect(":");
  Vec cs = {0, 0, 0};
  if (peek().k == K_IN) {
    skip();
    for (;;) {
      nls();
      Tok t = peek();
      if (t.k == K_DE) { skip(); break; }
      if (stuck(t)) break;
      CtorD *c = xcalloc(1, sizeof *c);
      c->name = ident();
      expect("{");
      Vec fn = {0, 0, 0}, ft = {0, 0, 0};
      for (;;) {
        Tok u = peek();
        if (is_sym(u, "}") || stuck(u)) { skip(); break; }
        eat("+");
        eat("-");
        vpush(&fn, (void *)ident());
        expect(":");
        vpush(&ft, expr());
        eat(",");
      }
      c->nfields = fn.n;
      c->fnames = (const char **)fn.a;
      c->ftys = (Expr **)ft.a;
      vpush(&cs, c);
    }
  }
  d->nctors = cs.n;
  d->ctors = xmalloc((size_t)(cs.n + 1) * sizeof(CtorD));
  for (int i = 0; i < cs.n; i++) d->ctors[i] = *(CtorD *)cs.a[i];
  return d;
}

// A law's type line as a type, when it reads as one to its end (P.law.ty).
static Expr *law_ty(void) {
  int p0 = P, s0 = Psub;
  Expr *e = expr();
  Tok t = peek();
  P = p0;
  Psub = s0;
  if (t.k == K_NL || t.k == K_DE) return e;
  return e_ty("", 0, 0);
}

// The type of a law: its last line that is not a 'for' (P.law.rets).
static Expr *law_rets(void) {
  static const char *ks[] = {"for", "exs", 0};
  nls();
  Tok t = peek();
  if (t.k == K_DE || stuck(t)) return e_ty("", 0, 0);
  int k = which_id(t, ks);
  if (k == 0) { skip_line(); return law_rets(); }
  if (k == 1) {
    skip();
    const char *x = ident();
    expect(":");
    Expr *ty = expr();
    skip_line();
    Expr *rest = law_rets();
    Expr **as = xmalloc(4 * sizeof *as);
    as[0] = e_ty("#q", 0, 0);
    as[1] = e_ty("#q", 0, 0);
    as[2] = ty;
    as[3] = e_lam(p_var(x), rest);
    return e_ty("Sigma", 4, as);
  }
  Expr *e = law_ty();
  skip_line();
  Expr *rest = law_rets();
  return rest->k == E_TY && !*rest->name ? e : rest;
}

static Decl *p_law(void) {
  skip();
  Decl *d = dnew(D_LAW);
  d->name = ident();
  expect(":");
  if (peek().k != K_IN) perr("expected an indented block");
  skip();
  int p0 = P, s0 = Psub;
  d->ret = law_rets();
  P = p0;
  Psub = s0;
  int n = 0, cap = 8;
  Param *ps = xmalloc((size_t)cap * sizeof *ps);
  for (;;) {  // the 'for' lines
    nls();
    Tok t = peek();
    if (t.k == K_DE) { skip(); break; }
    if (stuck(t)) break;
    if (is_idt(t, "for")) {
      skip();
      if (n == cap) { cap *= 2; ps = xrealloc(ps, (size_t)cap * sizeof *ps); }
      ps[n++] = param();
    }
    skip_line();
  }
  d->nps = n;
  d->ps = ps;
  return d;
}

static Decl *p_import(void) {
  skip();
  Decl *d = dnew(D_IMPORT);
  char buf[1024];
  int n = 0;
  for (;;) {  // the path: the tokens' text up to 'as' or the end of the line
    Tok t = peek();
    const char *s = 0;
    char num[16];
    if (t.k == K_ID) { if (!strcmp(t.s, "as")) break; s = t.s; }
    else if (t.k == K_SYM) s = t.s;
    else if (t.k == K_NUM) { snprintf(num, sizeof num, "%u", t.n); s = num; }
    else break;
    size_t k = strlen(s);
    if (n + k < sizeof buf) { memcpy(buf + n, s, k); n += (int)k; }
    skip();
  }
  d->path = intern_n(buf, (size_t)n);
  d->alias = intern("");
  if (is_idt(peek(), "as")) { skip(); d->alias = ident(); }
  skip_line();
  return d;
}

static Decl *decl(void) {
  static const char *ks[] = {"def", "type", "law", "import", 0};
  Tok t = peek();
  if (is_sym(t, "@")) { skip(); skip(); nls(); return decl(); }
  switch (which_id(t, ks)) {
  case 0: return p_def();
  case 1: return p_type();
  case 2: return p_law();
  case 3: return p_import();
  }
  perr("expected a declaration");
  return 0;
}

Vec parse_file(const char *path, const uint32_t *src, int n) {
  int nt;
  T = lex_all(src, n, &nt);
  P = 0;
  Psub = 0;
  Pfile = path;
  Vec ds = {0, 0, 0};
  for (;;) {
    nls();
    if (stuck(peek())) break;
    vpush(&ds, decl());
  }
  if (peek().k == K_ERR) perr("lexer error");
  return ds;
}

// Printing (Decls.show)
// ---------------------

static void show_pat(FILE *o, Pat *p) {
  switch (p->k) {
  case P_VAR: fputs(p->name, o); break;
  case P_CTOR:
    fprintf(o, "%s{", p->name);
    for (int i = 0; i < p->nargs; i++) { if (i) fputc(' ', o); show_pat(o, p->args[i]); }
    fputc('}', o);
    break;
  case P_NAT: fprintf(o, "%un", p->n); break;
  case P_SUCC: fprintf(o, "%un+", p->n); show_pat(o, p->args[0]); break;
  case P_NUM: fprintf(o, "%u", p->n); break;
  case P_FLT: fputs(p->name, o); break;
  }
}

static void show_expr(FILE *o, Expr *e) {
  switch (e->k) {
  case E_VAR: fputs(e->name, o); break;
  case E_NUM: fprintf(o, "%u", e->n); break;
  case E_NAT: fprintf(o, "%un", e->n); break;
  case E_FLT: fputs(e->name, o); break;
  case E_STR: fputc('"', o); put_cps(o, e->str, e->slen); fputc('"', o); break;
  case E_CALL:
    fputc('(', o);
    show_expr(o, e->f);
    for (int i = 0; i < e->nargs; i++) { fputc(' ', o); show_expr(o, e->args[i]); }
    fputs(e->nargs ? ")" : " )", o);
    break;
  case E_CTOR:
    fprintf(o, "%s{", e->name);
    for (int i = 0; i < e->nargs; i++) { if (i) fputc(' ', o); show_expr(o, e->args[i]); }
    fputc('}', o);
    break;
  case E_LAM: fputs("(\\", o); show_pat(o, e->pat); fputc(' ', o); show_expr(o, e->a); fputc(')', o); break;
  case E_LET:
    fputs("(let ", o); show_pat(o, e->pat); fputc(' ', o); show_expr(o, e->a); fputc(' ', o);
    show_expr(o, e->b); fputc(')', o);
    break;
  case E_MATCH:
    fputs("(match [", o);
    for (int i = 0; i < e->nargs; i++) { if (i) fputc(' ', o); show_expr(o, e->args[i]); }
    fputs("] ", o);
    for (int i = 0; i < e->ncases; i++) { if (i) fputc(' ', o); show_expr(o, e->cases[i]); }
    fputc(')', o);
    break;
  case E_CASE:
    fputs("(case ", o);
    for (int i = 0; i < e->npats; i++) { if (i) fputc(' ', o); show_pat(o, e->pats[i]); }
    fputs(" => ", o); show_expr(o, e->a); fputc(')', o);
    break;
  case E_SUCC: fprintf(o, "(%un+ ", e->n); show_expr(o, e->a); fputc(')', o); break;
  case E_OP: fprintf(o, "(%s ", e->name); show_expr(o, e->a); fputc(' ', o); show_expr(o, e->b); fputc(')', o); break;
  case E_ANN: fputs("(: ", o); show_expr(o, e->a); fprintf(o, " %s)", e->name); break;
  case E_TY:
    fprintf(o, "#%s", e->name);
    if (e->nargs) {
      fputc('<', o);
      for (int i = 0; i < e->nargs; i++) { if (i) fputc(' ', o); show_expr(o, e->args[i]); }
      fputc('>', o);
    }
    break;
  case E_ERR: fprintf(o, "(ERR %s)", e->name); break;
  }
}

static void show_params(FILE *o, Decl *d) {
  for (int i = 0; i < d->nps; i++) fprintf(o, "%d%s:%s ", d->ps[i].mode, d->ps[i].name, d->ps[i].ty);
}

void show_decls(FILE *o, Vec ds) {
  for (int i = 0; i < ds.n; i++) {
    Decl *d = ds.a[i];
    switch (d->k) {
    case D_DEF: fprintf(o, "def %s(", d->name); show_params(o, d); fputs(") = ", o); show_expr(o, d->body); break;
    case D_EFF: fprintf(o, "eff %s(", d->name); show_params(o, d); fputc(')', o); break;
    case D_LAW: fprintf(o, "law %s(", d->name); show_params(o, d); fputc(')', o); break;
    case D_TYPE:
      fprintf(o, "type %s ", d->name);
      for (int j = 0; j < d->nctors; j++) {
        CtorD *c = &d->ctors[j];
        fprintf(o, "%s{", c->name);
        for (int k = 0; k < c->nfields; k++) { fprintf(o, "%s:", c->fnames[k]); show_expr(o, c->ftys[k]); fputc(' ', o); }
        fputs("} ", o);
      }
      break;
    case D_IMPORT: fprintf(o, "import %s as %s", d->path, d->alias); break;
    }
    fputc('\n', o);
  }
}

// Modules
// =======
//
// Main.load: a file, then the modules it imports, each qualified by its
// alias (Mod.qualify: every name the module defines, and every reference to
// one that no local shadows, gets the alias in front).

typedef struct { const char **a; size_t cap, n; } PSet;

static void pset_add(PSet *s, const char *x) {
  if (s->n * 2 >= s->cap) {
    PSet t = {xcalloc(s->cap ? s->cap * 2 : 1024, sizeof(char *)), s->cap ? s->cap * 2 : 1024, 0};
    for (size_t i = 0; i < s->cap; i++) if (s->a[i]) pset_add(&t, s->a[i]);
    free(s->a);
    *s = t;
  }
  size_t j = ((uintptr_t)x >> 3) * 11400714819323198485ull >> 20 & (s->cap - 1);
  while (s->a[j]) { if (s->a[j] == x) return; j = (j + 1) & (s->cap - 1); }
  s->a[j] = x;
  s->n++;
}

static int pset_has(PSet *s, const char *x) {
  if (!s->cap) return 0;
  size_t j = ((uintptr_t)x >> 3) * 11400714819323198485ull >> 20 & (s->cap - 1);
  while (s->a[j]) { if (s->a[j] == x) return 1; j = (j + 1) & (s->cap - 1); }
  return 0;
}

typedef struct { const char *alias; PSet names; Vec bound; } Qual;

static const char *mod_q(Qual *q, const char *x) {
  return pset_has(&q->names, x) ? cat(cat(q->alias, "."), x) : x;
}

static int bound_has(Qual *q, const char *x) {
  for (int i = q->bound.n - 1; i >= 0; i--) if (q->bound.a[i] == x) return 1;
  return 0;
}

static const char *mod_var(Qual *q, const char *x) { return bound_has(q, x) ? x : mod_q(q, x); }

static void mod_pat(Qual *q, Pat *p) {
  if (p->k == P_CTOR) { p->name = mod_q(q, p->name); for (int i = 0; i < p->nargs; i++) mod_pat(q, p->args[i]); }
  else if (p->k == P_SUCC) mod_pat(q, p->args[0]);
}

// The variables a pattern binds (Pat.vars).
static void pat_vars(Pat *p, Vec *v) {
  if (p->k == P_VAR) vpush(v, (void *)p->name);
  else if (p->k == P_CTOR || p->k == P_SUCC) for (int i = 0; i < p->nargs; i++) pat_vars(p->args[i], v);
}

static void mod_expr(Qual *q, Expr *e) {
  int n0 = q->bound.n;
  switch (e->k) {
  case E_VAR: e->name = mod_var(q, e->name); break;
  case E_CALL: mod_expr(q, e->f); for (int i = 0; i < e->nargs; i++) mod_expr(q, e->args[i]); break;
  case E_CTOR: e->name = mod_q(q, e->name); for (int i = 0; i < e->nargs; i++) mod_expr(q, e->args[i]); break;
  case E_LAM: mod_pat(q, e->pat); pat_vars(e->pat, &q->bound); mod_expr(q, e->a); break;
  case E_LET: mod_pat(q, e->pat); mod_expr(q, e->a); pat_vars(e->pat, &q->bound); mod_expr(q, e->b); break;
  case E_MATCH:
    for (int i = 0; i < e->nargs; i++) mod_expr(q, e->args[i]);
    for (int i = 0; i < e->ncases; i++) mod_expr(q, e->cases[i]);
    break;
  case E_CASE:
    for (int i = 0; i < e->npats; i++) mod_pat(q, e->pats[i]);
    for (int i = 0; i < e->npats; i++) pat_vars(e->pats[i], &q->bound);
    mod_expr(q, e->a);
    break;
  case E_SUCC: mod_expr(q, e->a); break;
  case E_OP: mod_expr(q, e->a); mod_expr(q, e->b); break;
  case E_ANN: mod_expr(q, e->a); e->name = mod_var(q, e->name); break;
  case E_TY: e->name = mod_var(q, e->name); for (int i = 0; i < e->nargs; i++) mod_expr(q, e->args[i]); break;
  }
  q->bound.n = n0;
}

static void mod_qualify(const char *alias, Vec ds) {
  Qual q;
  memset(&q, 0, sizeof q);
  q.alias = alias;
  for (int i = 0; i < ds.n; i++) {
    Decl *d = ds.a[i];
    if (d->k == D_IMPORT) continue;
    pset_add(&q.names, d->name);
    if (d->k == D_TYPE) for (int j = 0; j < d->nctors; j++) pset_add(&q.names, d->ctors[j].name);
  }
  for (int i = 0; i < ds.n; i++) {
    Decl *d = ds.a[i];
    if (d->k == D_IMPORT) continue;
    d->name = mod_q(&q, d->name);
    if (d->k == D_DEF) {
      for (int j = 0; j < d->nps; j++) vpush(&q.bound, (void *)d->ps[j].name);
      mod_expr(&q, d->body);
      q.bound.n = 0;
      mod_expr(&q, d->ret);
    } else if (d->k == D_LAW) mod_expr(&q, d->ret);
    else if (d->k == D_TYPE)
      for (int j = 0; j < d->nctors; j++) {
        d->ctors[j].name = mod_q(&q, d->ctors[j].name);
        for (int k = 0; k < d->ctors[j].nfields; k++) mod_expr(&q, d->ctors[j].ftys[k]);
      }
  }
}

static const char *dir_of(const char *path) {
  const char *s = strrchr(path, '/');
  return s ? intern_n(path, (size_t)(s - path + 1)) : intern("");
}

static Vec load(const char *path, int fuel) {
  if (fuel == 0) die("imports nested too deeply at %s", path);
  int n;
  uint32_t *src = read_source(path, &n);
  Vec ds = parse_file(path, src, n);
  const char *dir = dir_of(path);
  Vec out = {0, 0, 0};
  for (int i = 0; i < ds.n; i++) {
    Decl *d = ds.a[i];
    if (d->k != D_IMPORT || !strcmp(d->path, "Base")) continue;
    if (!strncmp(d->path, "0x", 2)) die("hub imports are not supported: %s", d->path);
    const char *p = d->path[0] == '/' ? d->path : cat(dir, d->path);
    Vec sub = load(p, fuel - 1);
    mod_qualify(d->alias, sub);
    for (int j = 0; j < sub.n; j++) vpush(&out, sub.a[j]);
  }
  for (int i = 0; i < ds.n; i++) vpush(&out, ds.a[i]);
  return out;
}

// Base, then the program with its imports.
Vec load_program(const char *base, const char *path) {
  int n;
  uint32_t *src = read_source(base, &n);
  Vec ds = parse_file(base, src, n);
  Vec user = load(path, 64);
  for (int i = 0; i < user.n; i++) vpush(&ds, user.a[i]);
  return ds;
}

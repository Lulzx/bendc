// gpu.h: the device side of f!(x) calls, shared by the Metal kernel and the
// CPU simulator (the same text compiles as MSL and as C).
//
// bendc compiles every function a !-call can reach into one flat state
// machine: a frame per call, a case per block, `pc` the block to run. A
// parallel let pushes its thunks to a lock-free queue and continues through
// a join record, so a lane never blocks: whoever brings a join its last
// value runs the continuation. Values are the CPU's words. The device reads
// the CPU heap in place (unified memory) and builds new objects in an arena
// the host copies the result out of. Anything the device cannot do (an
// effect, a Nat past 2^48 - 1, a full arena or queue, a failed match, a closure
// it has no code for) sets an error, and the host runs the call on the CPU.
//
// bendc generates, after this file, k_frame_size (the frame of each label),
// the flat functions, and k_cases (the blocks). The host gives Metal this
// file's text (rt/gpu_src.h) followed by the generated text. Every name
// starts with k or K: the C version shares a file with bendrt.h.

#ifdef __METAL_VERSION__
#include <metal_stdlib>
using namespace metal;
typedef ulong KW;
typedef uint KU;
typedef int KI;
#define KDEV device
#define KCOH device coherent(device)
#define KTHR thread
#define KCONST constant
#define KCP constant
typedef atomic_uint KAU;
#define K_LOAD(p) atomic_load_explicit((p), memory_order_relaxed)
#define K_STORE(p, v) atomic_store_explicit((p), (v), memory_order_relaxed)
#define K_ADD(p, v) atomic_fetch_add_explicit((p), (v), memory_order_relaxed)
#define K_SUB(p, v) atomic_fetch_sub_explicit((p), (v), memory_order_relaxed)
#define K_CAS(p, e, v) atomic_compare_exchange_weak_explicit((p), &(e), (v), memory_order_relaxed, memory_order_relaxed)
#define K_FENCE() atomic_thread_fence(mem_flags::mem_device, memory_order_seq_cst, thread_scope_device)
#define KF(u) as_type<float>((uint)(u))
#define KUF(f) ((KU)as_type<uint>((float)(f)))
#define KMF(n) n
#define KINLINE inline
#define KNOINLINE __attribute__((noinline))
#define KAUTO auto
#define K_ATW(p) ((device atomic_uint *)(p))
#define K_SIMD_ALL(b) simd_all(b)
#define K_SIMD_FIRST() simd_is_first()
#define K_SIMD_BCAST(x) simd_broadcast_first(x)
#define K_SIMD_PREFIX(x) simd_prefix_exclusive_sum(x)
#define K_SIMD_MIN(x) simd_min(x)
#define K_SIMD_SUM(x) simd_sum(x)
#else
typedef uint64_t KW;
typedef uint32_t KU;
typedef int32_t KI;
#define KDEV
#define KCOH
#define KTHR
#define KCONST static const
#define KCP const
typedef uint32_t KAU;
#define K_LOAD(p) __atomic_load_n((p), __ATOMIC_SEQ_CST)
#define K_STORE(p, v) __atomic_store_n((p), (v), __ATOMIC_SEQ_CST)
#define K_ADD(p, v) __atomic_fetch_add((p), (v), __ATOMIC_SEQ_CST)
#define K_SUB(p, v) __atomic_fetch_sub((p), (v), __ATOMIC_SEQ_CST)
#define K_CAS(p, e, v) __atomic_compare_exchange_n((p), &(e), (v), 1, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define K_FENCE() __atomic_thread_fence(__ATOMIC_SEQ_CST)
static inline float k_f_of(KW u) { union { uint32_t i; float f; } x; x.i = (uint32_t)u; return x.f; }
static inline KU k_u_of(float f) { union { uint32_t i; float f; } x; x.f = f; return x.i; }
#define KF(u) k_f_of(u)
#define KUF(f) k_u_of(f)
#define KMF(n) n##f
#define KINLINE static inline
#define KNOINLINE static
#ifdef __TINYC__
// (tcc has no __auto_type: a word holds a KU as well, the natives truncate)
#define KAUTO KW
#else
#define KAUTO __auto_type
#endif
#define K_ATW(p) ((KAU *)(p))
#define K_SIMD_ALL(b) (b)
#define K_SIMD_FIRST() true
#define K_SIMD_BCAST(x) (x)
#define K_SIMD_PREFIX(x) 0u
#define K_SIMD_MIN(x) (x)
#define K_SIMD_SUM(x) (x)
#endif

// The control words (A).
#define KA_DONE 0
#define KA_ERR 1
#define KA_HEAP 2
#define KA_QHEAD 3
#define KA_QTAIL 4
#define KA_ACTIVE 5
#define KA_GROW 6    // a KQ_ call ran out of arena (see bend_kq)
#define KA_SEQ 16

// Where things are, in words of the arena (H) unless said otherwise.
typedef struct {
  KW ab;          // CPU address of the arena
  KW an;          // arena bytes
  KW gb;          // CPU address of the heap the device reads
  KW qcap;        // queue entries (a power of two)
  KW qd;          // queue data (4 words an entry)
  KW lane0;       // lane states: word k of lane l at lane0 + k * nlanes + l
  KW fn0;         // the CPU functions the device knows: {address, label} pairs
  KW nfn;
  KW heap0;       // the heap, in chunks of K_CHUNK words
  KW heapw;       // words in the heap
  KW budget;      // steps a lane runs in one dispatch
  KW nlanes;
  KW fork_limit;  // tasks fork only this many levels deep
  KW q0;          // the KQ_ stacks (KR_WORDS words a lane)
  KW kqmap;       // optional sorted KQ lane indices: count, then indices
  KW kqep;        // the epoch of this bend_kq dispatch (K_FREE, see k_take)
  KW fresh;       // the call's first dispatch: lanes empty their free lists
} KParams;

#define PC_IDLE 0
#define PC_ROOT 1
#define PC_JOIN 2
#define PC_TASK 3
#define PC_KQ 4      // waiting to run a KQ_ call (see the kernel's loop)
#define KQ_ARGS 12
// Freeing on match (K_FREE): a lane's free lists, one a size in words below
// K_NEXACT, then one a power of two from 64 words (frames, see k_push), are
// words K_FL0.. of its state (see k_take).
#define K_NFC 64
#define K_NEXACT 48
#define K_FL0 (12 + KQ_ARGS)
#define K_PEND 64
#define K_PN0 (K_FL0 + K_NFC)
#ifdef K_FREE
#define K_LANE (12 + KQ_ARGS + K_NFC + K_PEND)  // words of a lane's saved state
#else
#define K_LANE (12 + KQ_ARGS)  // words of a lane's saved state
#endif

#define K_CHUNK 256

// The errors a lane can hit.
#define KE_FX 2      // an effect, or a closure with no device code
#define KE_NAT 3     // a Nat past 2^48 - 1
#define KE_HEAP 4
#define KE_QUEUE 6
#define KE_MATCH 7
#define KE_PC 8
#define KE_FREE 9    // a KQ_ call that freed its arguments gave up (K_FREE)

typedef struct {
  KCOH KW *H;
  KDEV KW *G;
  KDEV KW *Q;
  KDEV KAU *A;
  KW ab, an, gb, lane;
  KW pc, fp, rv, dep, hp, he, ax;
  KW ko[8];            // a flat call's result fields (see KBOX)
  KW blocks, spare;    // span chains: live allocations and lane-local free spans
  KW hs;               // where the lane's current heap chunk starts (or its hp at load)
  KW ca, cb, cc; KU cm, cn, co;  // the narrow arrays the lane last used, and their masks (see k_aget)
  KU err;
  KW kq, kqret, kqfb;  // a KQ_ call: its def, where its value goes, the way through frames
  KW kqa[KQ_ARGS];     // and its arguments
  KW kqlim;            // the blocks it may run (K_KQLIM)
  KW kep;              // a KQ_ call's epoch, shifted to its prefix bits (K_FREE), else 0
  KU kdirty;           // the call freed an object older than it (K_FREE)
  KU kpn;              // and how many it holds back (K_PEND, see k_take)
  KCP KParams *P;
} KCtx;

// A KQ_ call made from the kernel's blocks (not past the fork limit) may
// reach a parallel let deep in its callees: it runs K_KQSTEPS blocks at most,
// then gives up and runs through the frames, which fork. Its kqfb has
// K_KQLIM set.
#define K_KQLIM ((KW)1 << 40)
#ifndef K_KQSTEPS
#define K_KQSTEPS ((KW)1 << 22)
#endif

#define KIMM(t) ((((KW)(t)) << 3) | 1)
#define KBOOL(b) ((b) ? KIMM(1) : KIMM(0))
// A word leaf (LI in bendrt.h).
#define KLI(t, x) ((KW)0xFFFF000000000000ul | ((KW)(KU)(x) << 16) | ((KW)(t) << 3) | 3)
#define KIS_LI(v, t) (((v) & (KW)0xFFFF00000000FFFFul) == ((KW)0xFFFF000000000000ul | ((KW)(t) << 3) | 3))
#define KLI_V(v) ((KW)(KU)((v) >> 16))
#define KIX(c, v) (((v) - (c)->ab) >> 3)
#define KPTR(c, i) ((c)->ab + ((KW)(i) << 3))
// The generated blocks reach frames only through these, so a def's blocks
// also run inside its KR_ function (thread-private frames; see bendc).
#define KS(k) c->H[c->fp + 4 + (k)]
#define KPC c->pc
#define KFP c->fp
#define KRV c->rv
// A parallel let forks below the fork limit while the queue is at most half
// full; past that its values run one after the other (matmul's 8-way lets
// filled the queue: KE_QUEUE, the call ran on the CPU).
#define KFORK (c->dep < c->P->fork_limit && \
  (KU)(K_LOAD(&c->A[KA_QTAIL]) - K_LOAD(&c->A[KA_QHEAD])) < (KU)(c->P->qcap / 2))
#define KPUSH(ret, e) k_push(c, ret, K_FRAME[e])
#define KARG(nf, i) c->H[(nf) + 4 + (i)]
#define KRET(x) k_ret(c, x)
#define KRSEQ true
#define KRCALL(f, ...) f(__VA_ARGS__)
// A closure's code word: a label, where the CPU has a function address.
#define KCLO ((KW)0x7ff << 52)

KINLINE void k_fail(KTHR KCtx *c, KU e) {
  if (c->err == 0) c->err = e;
}

// The words of the object at v: in the arena or in the CPU's heap.
//
// A Nat is a plain word (at most 2^48 - 1, as on the CPU), so a match on one
// needs no check, and a loop that counts down stays a counted loop.
KINLINE bool k_in(KTHR KCtx *c, KW v) { return v - c->ab < c->an; }
// Closed scalar-leaf tree nodes. Normal aligned pointers; only their prefix
// and payload layout differ. High mark/forward bits remain reserved for host.
#define K_PACK ((KW)1 << 59)
#define K_PACK_PTR ((KW)1 << 56)
#define K_PACK_TAG(h) (((h) >> 40) & 255)
#define K_PACK_AR(h) (((h) >> 48) & 255)
#ifdef K_GPU_PACKED
KNOINLINE
#else
KINLINE
#endif
KW k_word(KTHR KCtx *c, KW v, KW i) {
  if (k_in(c, v)) {
    KW ix=(v-c->ab)>>3;
#ifdef K_GPU_PACKED
    KW h=c->H[ix-1];
    if(h&K_PACK) {
      if(i==0)return K_PACK_TAG(h);
      if(h&K_PACK_PTR)return c->H[ix+i-1];
      return ((KDEV KU*)(c->H+ix))[i-1];
    }
#endif
    return c->H[ix+i];
  }
  return c->G[((v - c->gb) >> 3) + i];
}
KINLINE KW k_tag(KTHR KCtx *c, KW v) { return (v & 1) ? (v >> 3) : (k_word(c, v, 0) & (KW)0xffcfffff); }
#define KTAG(v) k_tag(c, v)
#define KFLD(v, i) k_word(c, v, 1 + (i))
// A headerless node's fields start at it (kind 8, see "Bare nodes" in
// bendrt.h); K_BARE in its size word says so (for k_region and the copy out).
#define KFLB(v, i) k_word(c, v, (i))
#define K_BARE ((KW)1 << 61)
// Freeing on match (K_FREE) keeps more in the size word: K_SHR, set on an
// object a variable used twice reaches (it is never freed), and in bits 32
// to 55 the epoch of the KQ_ call that allocated it (see k_take).
#define K_SHR ((KW)1 << 58)
#define K_EPOCH(h) (((h) >> 32) & 0xffffff)
KINLINE KW k_psize(KW h) {
#ifdef K_GPU_PACKED
  if(h&K_PACK)return h&0xffffffff;
#endif
#ifdef K_FREE
  return h&0xffffffff;
#else
  return h&~K_BARE;
#endif
}

// n words from the lane's heap chunk; the word before an object holds its
// size (the host copies results out with it). Chunk 0 is scratch: a lane
// that ran out writes there, and stops.
// The free list of objects of n words, or 0 for none.
KINLINE KW k_flc(KW n) {
  if (n < K_NEXACT) return n;
  if (n < 64 || (n & (n - 1)) != 0) return 0;
  KW b = 0;
  while (((KW)64 << b) < n) b++;
  return K_NEXACT + b < K_NFC ? K_NEXACT + b : 0;
}
#ifdef K_FREE
#define K_FLH(c, n) (c)->H[(c)->P->lane0 + (K_FL0 + (n)) * (c)->P->nlanes + (c)->lane]
#define K_PND(c, i) (c)->H[(c)->P->lane0 + (K_PN0 + (i)) * (c)->P->nlanes + (c)->lane]
#endif
KINLINE KW k_alloc(KTHR KCtx *c, KW n) {
#ifdef K_FREE
  KW fc = k_flc(n);
  if (fc != 0) {
    KW f = K_FLH(c, fc);
    if (f != 0) {
      K_FLH(c, fc) = c->H[f];
      c->H[f - 1] = n | c->kep;
      return KPTR(c, f);
    }
  }
#endif
  if (c->hp + n + 1 > c->he) {
    // Two words link each allocation span, outside its object storage.
    KW k = (n + 3 + K_CHUNK - 1) / K_CHUNK;
    KW start = 0, prev = 0, at = c->spare;
    while (at != 0) {
      if (c->H[at + 1] >= k) {
        if (prev != 0) c->H[prev] = c->H[at];
        else c->spare = c->H[at];
        start = at;
        k = c->H[at + 1];
        break;
      }
      prev = at;
      at = c->H[at];
    }
    if (start == 0) {
      KW idx = (KW)K_ADD(&c->A[KA_HEAP], (KU)k);
      start = c->P->heap0 + idx * K_CHUNK;
      if (start + k * K_CHUNK > c->P->heap0 + c->P->heapw) {
        k_fail(c, KE_HEAP);
        c->hp = c->P->heap0;
        c->he = c->hp + K_CHUNK;
        return KPTR(c, c->P->heap0 + 1);
      }
    }
    c->H[start] = c->blocks;
    c->H[start + 1] = k;
    c->blocks = start;
    c->hp = start + 2;
    c->hs = c->hp;
    c->he = start + k * K_CHUNK;
  }
  KW i = c->hp;
#ifdef K_FREE
  c->H[i] = n | c->kep;
#else
  c->H[i] = n;
#endif
  c->hp += n + 1;
  return KPTR(c, i + 1);
}

// Freeing on match (K_FREE). Values are affine (see "Freeing on match" in
// bendrt.h): a match that opened a node of this call's heap, once it read
// its fields, hands it here, and it goes on the lane's free list of its
// size, which k_alloc takes first. A node marked shared (K_SHR, by KSHARE
// where a variable used twice is bound) stays, and its fields become
// shared. The CPU's heap, and a result an earlier call pinned below heap0,
// are never freed.
//
// A KQ_ call may run again (after the arena grows, or through frames when
// it gives up), and then reads its arguments again: it must not have freed
// them. Objects carry the epoch of the bend_kq dispatch that made them: the
// first K_PEND older ones the call frees wait, untouched, until it returns;
// past them freeing an older one marks the call dirty, and a dirty call that
// stops fails the whole device call instead (see bend_kq).
KINLINE bool k_heap_obj(KTHR KCtx *c, KW v) {
  KW ix = (v - c->ab) >> 3;
  return (v & 7) == 0 && ix - (c->P->heap0 + K_CHUNK) < c->P->heapw - K_CHUNK;
}
KINLINE void k_share(KTHR KCtx *c, KW v) {
#ifdef K_FREE
  if (k_heap_obj(c, v)) c->H[KIX(c, v) - 1] |= K_SHR;
#endif
}
#define KSHARE(v) k_share(c, v)
KINLINE void k_take(KTHR KCtx *c, KW v, KW mask) {
#ifdef K_FREE
  if (!k_heap_obj(c, v)) return;
  KW ix = KIX(c, v), h = c->H[ix - 1], n = h & 0xffffffff;
  if (h & K_SHR) {
    // (mask: the fields that hold objects)
    for (KW i = 0; i < n && i < 64; i++)
      if ((mask >> i) & 1) k_share(c, c->H[ix + i]);
    return;
  }
  KW fc = k_flc(n);
  if (fc == 0) return;
  if (c->kep != 0 && (h & ((KW)0xffffff << 32)) != c->kep) {
    if (c->kpn < K_PEND) {
      K_PND(c, c->kpn) = ix;
      c->kpn++;
      return;
    }
    c->kdirty = 1;
  }
  c->H[ix] = K_FLH(c, fc);
  K_FLH(c, fc) = ix;
#endif
}
#define KTAKE(v, m) k_take(c, v, m)

// A looping flat call (KX_) runs only while no lane's heap ran out: once
// one did, the arena grows and the dispatch reruns, so the call's work would
// be lost; stopping it (as a heap failure) gets the host to the bigger
// arena early (terrain's first KQ pass at 64MB: 0.18s -> a few ms).
KINLINE bool k_short(KTHR KCtx *c) {
  if (c->err != 0) return true;
  if ((KW)K_LOAD(&c->A[KA_HEAP]) * K_CHUNK <= c->P->heapw) return false;
  k_fail(c, KE_HEAP);
  return true;
}

KINLINE void k_anone(KTHR KCtx *c) {
  c->ca = c->cb = c->cc = KPTR(c, c->P->heap0 + 1);
  c->cm = c->cn = c->co = 0;
}

// A flat call (KX_ or KQ_) neither forks nor writes into older objects, and
// compacted parents can point to newer descendants: what the call allocated
// is garbage unless its result reaches it. k_region takes it back: all of it when the
// result is older than the call (or not an object), else all but the result,
// moved down, when the result is the only new object it reaches. h0 and e0
// are the lane's hp and he before the call; when the call took a new chunk,
// only that chunk's words are taken back.
KNOINLINE KW k_region(KTHR KCtx *c, KW h0, KW e0, KW r) {
#ifdef K_FREE
  // (freed objects of the span may be on the free lists: keep it)
  return r;
#endif
  if (c->hp == h0) return r;
  KW lo = c->he == e0 ? h0 : c->hs;
  KW b = c->ab + (lo << 3), n = (c->hp - lo) << 3;
  if (r - b >= n) {
    // A graph rooted in an earlier arena span can still reach the last
    // one. Keep it; a scalar or immediate result cannot reach its objects.
    if (c->he != e0 && k_in(c, r)) return r;
    c->hp = lo;
    return r;
  }
  KW p = (r - c->ab) >> 3, raw=c->H[p-1], m = k_psize(raw);
  KW first=(raw&K_BARE)?0:1;
#ifdef K_GPU_PACKED
  if(raw&K_PACK) first=(raw&K_PACK_PTR)?0:m;
#endif
  for (KW i = first; i < m; i++) {
    // An older child can reach this span through a parent-first compacted
    // graph. Looking only for direct edges into the span would discard its
    // live descendants. Keep arena edges; self-contained scalar nodes can
    // still move down and release their temporary prefix.
    if (k_in(c, c->H[p + i])) return r;
  }
  for (KW i = 0; i <= m; i++) c->H[lo + i] = c->H[p - 1 + i];
  c->hp = lo + m + 1;
  k_anone(c);  // (an array there may be one now: see k_aget)
  return KPTR(c, lo + 1);
}
#define KREG(e) ({ KW kh0_ = c->hp, ke0_ = c->he; KW kr_ = (e); k_region(c, kh0_, ke0_, kr_); })
// The same for a call whose result is a scalar (a U32, F32 or Bool): it reaches
// nothing the call allocated.
// No value escapes a scalar call or an abandoned KQ_ call. Return its
// new spans to this lane; the previous span and its older objects stay live.
KINLINE void k_rewind(KTHR KCtx *c, KW h0, KW e0, KW b0) {
  while (c->blocks != b0) {
    KW at = c->blocks;
    c->blocks = c->H[at];
    c->H[at] = c->spare;
    c->spare = at;
  }
  c->hp = h0;
  c->he = e0;
  c->hs = b0 ? b0 + 2 : h0;
  k_anone(c);
}
#ifdef K_FREE
#undef KREG
#define KREG(e) (e)
#define KSCAL(e) (e)
#else
#define KSCAL(e) ({ KW kh0_ = c->hp, ke0_ = c->he, kb0_ = c->blocks; KU kr_ = (e); if (c->err == 0) k_rewind(c, kh0_, ke0_, kb0_); kr_; })
#endif


// Reclamation for a closed recursive Data. Masks name Self fields by their
// actual payload positions; bit 31 marks the unique headerless constructor.
KINLINE bool k_tree_new(KTHR KCtx *c, KW h0, KW e0, KW b0, KW v) {
  if (!k_in(c,v)) return false;
  KW ix=KIX(c,v);
  if (ix>h0 && ix<e0) return true;
  for (KW at=c->blocks;at!=b0;at=c->H[at])
    if (ix>at+2 && ix<at+c->H[at+1]*K_CHUNK) return true;
  return false;
}
KINLINE KW k_tree_copy_node(KTHR KCtx *src,KTHR KCtx *out,KW v) {
  KW ix=KIX(src,v), raw=src->H[ix-1], n=k_psize(raw);
  KW r=k_alloc(out,n);
  if (out->err) return 0;
  out->H[KIX(out,r)-1]=raw;
  for(KW i=0;i<n;i++) out->H[KIX(out,r)+i]=src->H[ix+i];
  return r;
}
// Bit 31 denotes the type's unique headerless constructor. Immediate word
// leaves remain outside the arena and need no copying or schema lookup.
#define K_TREE_BARE_MASK ((KW)1 << 31)
KINLINE bool k_tree_layout(KTHR KCtx *c,KW v,KCP KW *masks,KW nmasks,
                           KTHR KW *mask,KTHR KW *first) {
  KW ix=KIX(c,v), raw=c->H[ix-1];
#ifdef K_GPU_PACKED
  if(raw&K_PACK) {
    KW tag=K_PACK_TAG(raw);if(tag>=nmasks || masks[tag]&K_TREE_BARE_MASK)return false;
    if(raw&K_PACK_PTR){*mask=masks[tag]>>1;*first=0;return true;}
    if(masks[tag]!=0)return false;
    *mask=0;*first=0;return true;
  }
#endif
  if(raw & K_BARE) {
    for(KW tag=0;tag<nmasks;tag++) if(masks[tag] & K_TREE_BARE_MASK) {
      *mask=masks[tag] & ~K_TREE_BARE_MASK;*first=0;return true;
    }
    return false;
  }
  KW tag=c->H[ix]&0xffcfffff;
  if(tag>=nmasks || (masks[tag] & K_TREE_BARE_MASK)) return false;
  *mask=masks[tag];*first=1;return true;
}
KNOINLINE KW k_tree_compact(KTHR KCtx *c,KW h0,KW e0,KW b0,KW r,
                       KCP KW *masks,KW nmasks) {
  if(c->err || !k_tree_new(c,h0,e0,b0,r)) return r;
  KCtx out=*c;out.hp=out.he=out.hs=0;out.blocks=b0;
  KW root=k_tree_copy_node(c,&out,r);
  KW src[64],dst[64],next[64],depth=1,steps=0;
  src[0]=r;dst[0]=root;next[0]=0;
  bool abort=false;
  while(depth && !out.err) {
    KW d=depth-1,ix=KIX(c,src[d]),n=k_psize(c->H[ix-1]),mask,first;
    if(n>=64 || ++steps>131072 || !k_tree_layout(c,src[d],masks,nmasks,&mask,&first)) {abort=true;break;}
    if(next[d]<first) next[d]=first;
    while(next[d]<n && !(mask&((KW)1<<next[d]))) next[d]++;
    if(next[d]==n) {depth--;continue;}
    KW i=next[d]++,v=c->H[ix+i];
    if(!k_tree_new(c,h0,e0,b0,v)) continue;
    if(depth==64) {abort=true;break;}
    KW copied=k_tree_copy_node(c,&out,v);
    if(out.err) break;
    out.H[KIX(&out,dst[d])+i]=copied;
    src[depth]=v;dst[depth]=copied;next[depth]=0;depth++;
  }
  if(abort || out.err) {
    // Only private output was written. The source and its span links remain
    // valid; return output spans to the lane, and propagate heap failures.
    k_rewind(&out,0,0,b0);
    c->spare=out.spare;
    if(out.err) k_fail(c,out.err);
    return r;
  }
  // A small closed graph fits back in the starting span. The private copy
  // is complete, so the old temporary prefix can now be overwritten. Trace
  // fields by their schema when relocating; scalar address-shaped words stay.
  if(out.blocks!=b0 && out.H[out.blocks]==b0 && out.hp-out.hs<=e0-h0) {
    KW lo=out.hs,words=out.hp-lo,base=KPTR(&out,lo),bytes=words<<3;
    for(KW at=lo;at<out.hp;) {
      KW raw=out.H[at],n=k_psize(raw),mask=0,first=0;
      (void)k_tree_layout(&out,KPTR(&out,at+1),masks,nmasks,&mask,&first);
      c->H[h0+at-lo]=raw;
      for(KW i=0;i<n;i++) {
        KW v=out.H[at+1+i];
        if((mask&((KW)1<<i)) && v-base<bytes) v=KPTR(c,h0)+(v-base);
        c->H[h0+at+1+i-lo]=v;
      }
      at+=n+1;
    }
    KW relocated=KPTR(c,h0)+(root-base);
    k_rewind(&out,0,0,b0);c->spare=out.spare;
    k_rewind(c,h0,e0,b0);c->hp=h0+words;
    return relocated;
  }
  while(c->blocks!=b0) {
    KW at=c->blocks;c->blocks=c->H[at];c->H[at]=out.spare;out.spare=at;
  }
  c->hp=out.hp;c->he=out.he;c->hs=out.hs;
  c->blocks=out.blocks;c->spare=out.spare;k_anone(c);
  return root;
}

#ifdef K_FREE
#define K_TREE_STACK
#define K_TREE_MARK(id) do {} while (0)
#define K_TREE_RET do {} while (0)
#else
#define K_TREE_STACK KW kt_birth[32][5], kt_nb=0
#define K_TREE_MARK(id) do { \
  if(kt_nb>0) { \
    KW kt_prev=kt_nb-1; \
    if(kt_birth[kt_prev][3]==sp && k_tree_schema(id)[0]==0 && k_tree_schema(kt_birth[kt_prev][4])[0]==0) \
      k_rewind(c,kt_birth[kt_prev][0],kt_birth[kt_prev][1],kt_birth[kt_prev][2]); \
  } \
  bool kt_add=kt_nb==0; \
  if(kt_nb>0) kt_add=kt_birth[kt_nb-1][3]!=sp; \
  if(kt_add) { \
    if(kt_nb==32){*ok=false;return 0;} \
    kt_birth[kt_nb][0]=c->hp;kt_birth[kt_nb][1]=c->he; \
    kt_birth[kt_nb][2]=c->blocks;kt_birth[kt_nb][3]=sp; \
    kt_birth[kt_nb][4]=(id);kt_nb++; \
  } \
} while(0)
#define K_TREE_RET do { \
  while(kt_nb>0) { \
    KW kt_ix=kt_nb-1; \
    if(kt_birth[kt_ix][3]!=sp) break; \
    kt_nb=kt_ix;KCP KW *kt_schema=k_tree_schema(kt_birth[kt_ix][4]); \
    if(kt_schema[0]==0) k_rewind(c,kt_birth[kt_ix][0],kt_birth[kt_ix][1],kt_birth[kt_ix][2]); \
    else RV=k_tree_compact(c,kt_birth[kt_ix][0],kt_birth[kt_ix][1],kt_birth[kt_ix][2],RV,kt_schema+1,kt_schema[0]); \
    if(c->err){*ok=false;return 0;} \
  } \
} while(0)
#endif

// A flat def keeps a Nat parameter in a KU: a Nat past 2^32 - 1 fails the call
// over to the CPU (a counted loop never gets there). KSET assigns a parameter
// at a tail call, with that check for a KU (a U32, F32 or Bool passes it).
#define KNAT32(v) ({ KW kv_ = (v); if ((kv_ >> 32) != 0) k_fail(c, KE_NAT); (KU)kv_; })
#define KSET(a, v) ((a) = sizeof(a) == 4 ? KNAT32(v) : (v))

KINLINE KW k_node(KTHR KCtx *c, KW tag, KW n) {
  KW p = k_alloc(c, n + 1);
  c->H[KIX(c, p)] = tag;
  return p;
}
KINLINE KW k_bnode(KTHR KCtx *c, KW n) {
  KW p = k_alloc(c, n);
  c->H[KIX(c, p) - 1] = n | K_BARE | c->kep;
  return p;
}

// A flat def whose result is one constructor of 2 to 8 scalar fields leaves
// the fields in c->ko and no node (raytrace 1.35x faster). KBOX builds the
// node for a caller that keeps the value whole.
KINLINE KW k_box(KTHR KCtx *c, KW n) {
  KW r = k_node(c, 0, n);
  for (KW i = 0; i < n; i++) c->H[KIX(c, r) + 1 + i] = c->ko[i];
  return r;
}
#define KBOX(n, e) ({ (void)(e); k_box(c, n); })

// A frame: [return pc, parent frame, aux, size, slots...], from the heap;
// one still on top of it when it returns gives its words back.
KINLINE KW k_push(KTHR KCtx *c, KW ret, KW fs) {
#ifdef K_FREE
  // (a big frame takes a power of two, from a free list of its size)
  if (fs >= K_NEXACT) {
    KW r = 64;
    while (r < fs) r <<= 1;
    fs = r;
  }
#endif
  KW f = KIX(c, k_alloc(c, fs));
  c->H[f] = ret;
  c->H[f + 1] = c->fp;
  c->H[f + 2] = 0;
  c->H[f + 3] = fs;
  return f;
}

KINLINE void k_ret(KTHR KCtx *c, KW x) {
  KW f = c->fp;
  c->rv = x;
  c->ax = c->H[f + 2];
  c->pc = c->H[f];
  c->fp = c->H[f + 1];
  if (f + c->H[f + 3] == c->hp) c->hp = f - 1;
#ifdef K_FREE
  // (else it goes on its free list: a frame is never shared)
  else {
    KW fc = k_flc(c->H[f + 3]);
    c->H[f] = K_FLH(c, fc);
    K_FLH(c, fc) = f;
  }
#endif
}

// The queue (Vyukov's bounded MPMC queue): an entry is {pc, fp, rv, dep}.
// A slot keeps its sequence number less its index, so a zeroed queue is
// empty (the host clears only the slots a call used).
#define KQ_SEQ(i) (K_LOAD(&c->A[KA_SEQ + (i)]) + (KU)(i))
#define KQ_SET(i, s) K_STORE(&c->A[KA_SEQ + (i)], (s) - (KU)(i))
//
// The lanes of a SIMD group that push (or pop) together take their slots
// together: the group's first lane reads the tail (head), each lane checks
// the slot at its place past it, and one CAS takes the free (published)
// slots in a row. (A CAS a lane, with 4096 lanes forking at one level, made
// the forks of a call take 10 ms.) A pop takes only published slots, so no
// lane waits for another.
KINLINE KU k_simd_run(bool ok, KU i) {
  KU n = K_SIMD_MIN(ok ? ~0u : i);
  return n == ~0u ? K_SIMD_SUM(1u) : n;
}
KINLINE bool k_push_task(KTHR KCtx *c, KW pc, KW fp, KW rv, KW dep) {
  KW mask = c->P->qcap - 1;
  KU pos;
  for (int tries = 0;; tries++) {
    if (tries > 100000) return false;
    KU i = K_SIMD_PREFIX(1u);
    KU t = 0;
    if (K_SIMD_FIRST()) t = K_LOAD(&c->A[KA_QTAIL]);
    t = K_SIMD_BCAST(t);
    pos = t + i;
    KI dif = (KI)(KQ_SEQ(pos & mask) - pos);
    KU n = k_simd_run(dif == 0, i);
    // (full: the group's first slot is a lap behind, no pop freed it)
    if (K_SIMD_BCAST(n == 0 && dif < 0 ? 1u : 0u) != 0) return false;
    KU won = 0;
    if (K_SIMD_FIRST() && n > 0) {
      KU e = t;
      won = K_CAS(&c->A[KA_QTAIL], e, t + n) ? 1u : 0u;
    }
    won = K_SIMD_BCAST(won);
    if (won != 0 && i < n) break;
  }
  KW q = c->P->qd + (KW)(pos & mask) * 4;
  c->H[q] = pc;
  c->H[q + 1] = fp;
  c->H[q + 2] = rv;
  c->H[q + 3] = dep;
  K_FENCE();
  KQ_SET(pos & mask, pos + 1);
  return true;
}

KINLINE bool k_pop_task(KTHR KCtx *c) {
  KW mask = c->P->qcap - 1;
  KU i = K_SIMD_PREFIX(1u);
  KU h = 0;
  if (K_SIMD_FIRST()) h = K_LOAD(&c->A[KA_QHEAD]);
  h = K_SIMD_BCAST(h);
  KU pos = h + i;
  KU n = k_simd_run(KQ_SEQ(pos & mask) == pos + 1, i);
  KU won = 0;
  if (K_SIMD_FIRST() && n > 0) {
    KU e = h;
    won = K_CAS(&c->A[KA_QHEAD], e, h + n) ? 1u : 0u;
  }
  won = K_SIMD_BCAST(won);
  if (won == 0 || i >= n) return false;
  K_FENCE();
  KW q = c->P->qd + (KW)(pos & mask) * 4;
  c->pc = c->H[q];
  c->fp = c->H[q + 1];
  c->rv = c->H[q + 2];
  c->dep = c->H[q + 3];
  K_FENCE();
  KQ_SET(pos & mask, pos + (KU)mask + 1);
  return true;
}

// A join record: [pending, continuation pc, continuation frame, depth, values...].
KINLINE KW k_join_new(KTHR KCtx *c, KW n, KW cont) {
  KW j = KIX(c, k_alloc(c, 4 + n));
  c->H[j] = n;
  c->H[j + 1] = cont;
  c->H[j + 2] = c->fp;
  c->H[j + 3] = c->dep;
  return j;
}

// A value arrives at a join; the last one continues the forking frame.
KINLINE void k_arrive(KTHR KCtx *c, KW j, KW i, KW x) {
  c->H[j + 4 + i] = x;
  K_FENCE();
  KU old = K_SUB(K_ATW(&c->H[j]), 1u);
  if (old == 1) {
    K_FENCE();
    c->pc = c->H[j + 1];
    c->fp = c->H[j + 2];
    c->dep = c->H[j + 3];
  } else {
    c->pc = PC_IDLE;
  }
}

// The label of a CPU function, from the table the host fills.
KINLINE KW k_fn_label(KTHR KCtx *c, KW f) {
  KW t = c->P->fn0;
  for (KW i = 0; i < c->P->nfn; i++) {
    if (c->H[t + 2 * i] == f) return c->H[t + 2 * i + 1];
  }
  return 0;
}

// Natives
// -------

// A Nat result past 2^48 - 1 fails, as 0 (the CPU then stops, as the official runtime).
#define KNAT_BIG(x) ((x) > (((KW)1 << 48) - 1))
KINLINE bool k_nge(KTHR KCtx *c, KW x, KW k) { return x >= k; }
KINLINE bool k_nz(KTHR KCtx *c, KW x) { return x != 0; }
KINLINE KW k_nat_add(KTHR KCtx *c, KW a, KW b) {
  KW s = a + b;
  if (KNAT_BIG(s)) { k_fail(c, KE_NAT); return 0; }
  return s;
}
KINLINE KW k_nat_mul(KTHR KCtx *c, KW a, KW b) {
  if (a != 0 && b > (((KW)1 << 48) - 1) / a) { k_fail(c, KE_NAT); return 0; }
  return a * b;
}
KINLINE KW k_cmp3(KW a, KW b) { return a < b ? KIMM(0) : a == b ? KIMM(1) : KIMM(2); }
#define KN1(name, expr) KINLINE KW KF_Nat_d##name(KTHR KCtx *c, KW a) { return expr; }
#define KN2(name, expr) KINLINE KW KF_Nat_d##name(KTHR KCtx *c, KW a, KW b) { return expr; }
KN1(double, k_nat_add(c, a, a))
KN2(add, k_nat_add(c, a, b))
KN2(sub, a > b ? a - b : 0)
KN2(mul, k_nat_mul(c, a, b))
KN2(div, b == 0 ? 0 : a / b)
KN2(mod, b == 0 ? a : a % b)
KN2(cmp, k_cmp3(a, b))
KN2(is__eq, KBOOL(a == b))
KN2(is__ne, KBOOL(a != b))
KN2(is__lt, KBOOL(a < b))
KN2(is__le, KBOOL(a <= b))
KN2(is__gt, KBOOL(a > b))
KN2(is__ge, KBOOL(a >= b))
KN2(min, a < b ? a : b)
KN2(max, a < b ? b : a)
KINLINE KW KF_Nat_ddivmod(KTHR KCtx *c, KW a, KW b) {
  KW p = k_node(c, 0, 2);
  c->H[KIX(c, p) + 1] = b == 0 ? 0 : a / b;
  c->H[KIX(c, p) + 2] = b == 0 ? a : a % b;
  return p;
}
KINLINE KW KF_Nat_dpow(KTHR KCtx *c, KW a, KW n) {
  KW r = 1;
  for (KW i = 0; i < n && c->err == 0; i++) r = k_nat_mul(c, r, a);
  return r;
}
KINLINE KW KF_Nat_dshow(KTHR KCtx *c, KW a) { k_fail(c, KE_FX); return 0; }
// String.cmp, String.eq, Map.bit, Map.get and Map.has are natives on the
// CPU: a device call that meets one runs on the CPU.
KINLINE KW KF_String_dcmp(KTHR KCtx *c, KW a, KW b) { k_fail(c, KE_FX); return 0; }
KINLINE KW KF_String_deq(KTHR KCtx *c, KW a, KW b) { k_fail(c, KE_FX); return 0; }
KINLINE KW KF_Map_dbit(KTHR KCtx *c, KW a, KW b) { k_fail(c, KE_FX); return 0; }
KINLINE KW KF_Map_dget(KTHR KCtx *c, KW a, KW b, KW d) { k_fail(c, KE_FX); return 0; }
KINLINE KW KF_Map_dhas(KTHR KCtx *c, KW a, KW b) { k_fail(c, KE_FX); return 0; }
// An Array is a node {ARR_HDR(c), 2^c cells}, as on the CPU (see "Arrays"
// in bendrt.h). The device builds them in the arena and reads any; it
// writes only its own (a call that writes one of the CPU's runs on the
// CPU), and runs no match on one (ANode, ALeaf) and no atomic. A flat
// def's let of an Array.get or Array.swap pair makes no pair (KXSLetArr in
// bendc.bend): k_aget and k_aswap answer the cell.
//
// An array of scalars (Array.new%w: U32, F32, Bool or Char cells, see
// Arrw in bendc.bend) the device builds is narrow: header K_ARR_NW | c and
// 2^c 32-bit cells, half the memory traffic of words (terrain's tiles 1.35x
// faster). No such array reaches the CPU: the host widens it as it copies
// the result out (gpu_copy_out), and a call's result that holds one stays
// out of the arena for the CPU (Gen.gpu.pin: no arrays). The CPU's own
// arrays of scalars are narrow too (ARR_NW in bendrt.h), read as such.
#define K_ARR_HDR(n) ((KW)0xFFF00 | (KW)(n))
#define K_ARR_NW ((KW)0x20)
KINLINE bool k_arr(KTHR KCtx *c) { k_fail(c, KE_FX); return false; }
#define KF_ARR(c) (k_fail(c, KE_FX), (KW)0)
KINLINE KW k_amask(KTHR KCtx *c, KW a) { return ((KW)1 << (k_word(c, a, 0) & 31)) - 1; }
#define K_NCELLS(c, w) ((KCOH KU *)((c)->H + (w) + 1))
// The lane keeps the narrow array it last used (ca) and its mask (cm): a
// loop over one reads its header once, not at each access (a dependent load
// that misses the cache the cells stream through: terrain 1.2x faster). An
// array made at an address (k_anew, k_region) updates it. With none, ca is
// the 1-cell array a failed allocation makes (see k_alloc), so a value that
// is no array (after a failure, a call runs on to its return) reads there.
KINLINE KW k_aslow(KTHR KCtx *c, KW a, KW i, KW v, bool sw) {
  if (!k_in(c, a)) {
    if (sw) k_fail(c, KE_FX);
    if (sw) return 0;
    KW o = (a - c->gb) >> 3, h = c->G[o];
    KU m = ((KU)1 << (h & 31)) - 1;
    // (a narrow CPU array: 32-bit cells, see ARR_NW in bendrt.h)
    if (h & K_ARR_NW) return ((KDEV KU *)(c->G + o + 1))[(KU)i & m];
    return c->G[o + 1 + ((KU)i & m)];
  }
  KW w = KIX(c, a), h = c->H[w];
  KU j = (KU)i & (((KU)1 << (h & 31)) - 1);
  if (h & K_ARR_NW) {
    c->cc = c->cb;
    c->co = c->cn;
    c->cb = c->ca;
    c->cn = c->cm;
    c->ca = a;
    c->cm = ((KU)1 << (h & 31)) - 1;
    KCOH KU *q = K_NCELLS(c, w) + j;
    KW o = *q;
    if (sw) *q = (KU)v;
    return o;
  }
  KW o = c->H[w + 1 + j];
  if (sw) c->H[w + 1 + j] = v;
  return o;
}
#define KAI_NARROW ((KW)1 << 32)
#define KAI_CPU ((KW)1 << 33)
KINLINE KW k_ainfo(KTHR KCtx *c, KW a) {
  if (!a) return KAI_NARROW;
  if(a==c->ca) return KAI_NARROW|c->cm;
  if(a==c->cb) return KAI_NARROW|c->cn;
  if(a==c->cc) return KAI_NARROW|c->co;
  bool arena=k_in(c,a);KW h=k_word(c,a,0);KU m=((KU)1<<(h&31))-1;
  return (KW)m | ((h&K_ARR_NW)?KAI_NARROW:0) | (arena?0:KAI_CPU);
}
KINLINE KW k_aget(KTHR KCtx *c, KW a, KW i) {
  if (a == c->ca) return K_NCELLS(c, KIX(c, a))[(KU)i & c->cm];
  if (a == c->cb) return K_NCELLS(c, KIX(c, a))[(KU)i & c->cn];
  if (a == c->cc) return K_NCELLS(c, KIX(c, a))[(KU)i & c->co];
  return k_aslow(c, a, i, 0, false);
}
// (a CPU array: the call fails over, and the write goes to the scratch
// chunk's first word)
KINLINE KW k_aswap(KTHR KCtx *c, KW a, KW i, KW v) {
  if (a == c->ca || a == c->cb || a == c->cc) {
    KCOH KU *q = K_NCELLS(c, KIX(c, a)) + ((KU)i & (a == c->ca ? c->cm : a == c->cb ? c->cn : c->co));
    KW o = *q;
    *q = (KU)v;
    return o;
  }
  return k_aslow(c, a, i, v, true);
}
KINLINE KW k_aiget(KTHR KCtx *c,KW a,KW info,KW i) {
  if(!a) info=KAI_NARROW;
  if(!info) return k_aget(c,a,i);
  KW w=!a?c->P->heap0+1:(info&KAI_CPU)?((a-c->gb)>>3):KIX(c,a);
  KCOH KW *p=(info&KAI_CPU)?(KCOH KW *)(c->G+w):c->H+w;
  KU j=(KU)i&(KU)info;
  return (info&KAI_NARROW)?((KCOH KU *)(p+1))[j]:p[1+j];
}
KINLINE KW k_aiswap(KTHR KCtx *c,KW a,KW info,KW i,KW v) {
  if(!a) info=KAI_NARROW;
  if(!info) return k_aswap(c,a,i,v);
  if(info&KAI_CPU) {k_fail(c,KE_FX);return 0;}
  KW w=!a?c->P->heap0+1:KIX(c,a);KU j=(KU)i&(KU)info;
  if(info&KAI_NARROW) {KCOH KU *p=K_NCELLS(c,w)+j;KW r=*p;*p=(KU)v;return r;}
  KW r=c->H[w+1+j];c->H[w+1+j]=v;return r;
}
KINLINE KW k_aiset(KTHR KCtx *c, KW a, KW info, KW i, KW v) {
  if (!a || !info) { k_aswap(c, a, i, v); return a; }
  k_aiswap(c, a, info, i, v);
  return a;
}
KINLINE KW k_apair(KTHR KCtx *c, KW a, KW x) {
  KW p = k_node(c, 0, 2);
  c->H[KIX(c, p) + 1] = a;
  c->H[KIX(c, p) + 2] = x;
  return p;
}
// (out of arena, p is in the scratch chunk: a 1-cell array there)
KINLINE KW k_anew(KTHR KCtx *c, KW d, KW v, bool nw) {
  if (d > 24) {
    k_fail(c, KE_FX);
    return 0;
  }
  KW n = (KW)1 << d;
  KW p = k_alloc(c, nw ? (n + 1) / 2 + 1 : n + 1);
  KW w = KIX(c, p);
  if (c->err != 0) n = 1, d = 0;
  if (nw) {
    c->cc = c->cb;
    c->co = c->cn;
    c->cb = c->ca;
    c->cn = c->cm;
    c->ca = p;
    c->cm = ((KU)1 << d) - 1;
  } else k_anone(c);
  if (nw) {
    c->H[w] = K_ARR_HDR(d) | K_ARR_NW;
    for (KW i = 0; i < n; i++) K_NCELLS(c, w)[i] = (KU)v;
  } else {
    c->H[w] = K_ARR_HDR(d);
    for (KW i = 0; i < n; i++) c->H[w + 1 + i] = v;
  }
  return p;
}
KINLINE KW KF_Array_dnew(KTHR KCtx *c, KW d, KW v) { return k_anew(c, d, v, false); }
KINLINE KW KF_Array_dnew_x37w(KTHR KCtx *c, KW d, KW v) { return k_anew(c, d, v, true); }
KINLINE KW KF_Array_dclone(KTHR KCtx *c, KW a) {
  KW m = k_amask(c, a);
  KW h = k_word(c, a, 0);
  KW p = k_anew(c, h & 31, 0, k_in(c, a) && (h & K_ARR_NW) != 0);
  for (KW i = 0; i <= m; i++) k_aswap(c, p, i, k_aget(c, a, i));
  return k_apair(c, a, p);
}
KINLINE KW KF_Array_dsize(KTHR KCtx *c, KW a) { return k_apair(c, a, k_amask(c, a) + 1); }
KINLINE KW KF_Array_dget(KTHR KCtx *c, KW a, KW i) { return k_apair(c, a, k_aget(c, a, i)); }
KINLINE KW KF_Array_dswap(KTHR KCtx *c, KW a, KW i, KW v) { return k_apair(c, a, k_aswap(c, a, i, v)); }
KINLINE KW KF_Array_dset(KTHR KCtx *c, KW a, KW i, KW v) {
  k_aswap(c, a, i, v);
  return a;
}
#define KF_Array_dget_x37w KF_Array_dget
#define KF_Array_dswap_x37w KF_Array_dswap
#define KF_Array_dset_x37w KF_Array_dset
#define KF_Array_datomic_dadd(c, ...) KF_ARR(c)
#define KF_Array_datomic_dmin(c, ...) KF_ARR(c)
#define KF_Array_datomic_dmax(c, ...) KF_ARR(c)
#define KF_Array_datomic_dand(c, ...) KF_ARR(c)
#define KF_Array_datomic_dor(c, ...) KF_ARR(c)
#define KF_Array_datomic_dxor(c, ...) KF_ARR(c)
#define KF_Array_datomic_dexch(c, ...) KF_ARR(c)
#define KF_Array_datomic_dcas(c, ...) KF_ARR(c)
#define KF_Array_datomic_dfadd(c, ...) KF_ARR(c)

#define KU32(x) ((KW)(KU)(x))
// U32 and F32 values fit a KU: their natives take and give KUs, and so a
// flat def's locals (KAUTO) and its U32, F32 and Bool parameters are KUs.
#define KU1(name, expr) KINLINE KU KF_U32_d##name(KTHR KCtx *c, KU a) { return expr; }
#define KU2(name, expr) KINLINE KU KF_U32_d##name(KTHR KCtx *c, KU a, KU b) { return expr; }
KU1(inc, KU32(a + 1))
KU2(add, KU32(a + b))
KU2(sub, KU32(a - b))
KU2(mul, KU32((KU)a * (KU)b))
KU2(div, b == 0 ? 0 : KU32(a) / KU32(b))
KU2(mod, b == 0 ? a : KU32(a) % KU32(b))
KU1(not, KU32(~a))
KU2(and, a & b)
KU2(or, a | b)
KU2(xor, a ^ b)
KU1(shl, KU32(a << 1))
KU1(shr, a >> 1)
KINLINE KU KF_U32_dshln(KTHR KCtx *c, KU a, KW b) { return b >= 32 ? 0 : KU32(a << b); }
KINLINE KU KF_U32_dshrn(KTHR KCtx *c, KU a, KW b) { return b >= 32 ? 0 : a >> b; }
KU2(cmp, k_cmp3(a, b))
KU2(is__eq, KBOOL(a == b))
KU2(is__ne, KBOOL(a != b))
KU2(is__lt, KBOOL(a < b))
KU2(is__le, KBOOL(a <= b))
KU2(is__gt, KBOOL(a > b))
KU2(is__ge, KBOOL(a >= b))
KU1(is__zero, KBOOL(a == 0))
KU1(is__even, KBOOL((a & 1) == 0))
KINLINE KW KF_U32_dto__nat(KTHR KCtx *c, KU a) { return a; }
KINLINE KU KF_U32_dfrom__nat(KTHR KCtx *c, KW a) { return KU32(a); }
KU2(min, a < b ? a : b)
KU2(max, a < b ? b : a)
KINLINE KU KF_U32_dpow(KTHR KCtx *c, KU a, KW n) {
  KU r = 1, b = (KU)a;
  for (KW e = n; e; e >>= 1) {
    if (e & 1) r *= b;
    b *= b;
  }
  return r;
}
KINLINE KW KF_U32_dlog2(KTHR KCtx *c, KU n) {
  KW d = 0;
  while (n > 1) { d++; n >>= 1; }
  return d;
}
KU1(to__f32, KUF((float)(KU)a))

#define KF1(name, expr) KINLINE KU KF_F32_d##name(KTHR KCtx *c, KU a) { float x = KF(a); return expr; }
#define KF2(name, expr) KINLINE KU KF_F32_d##name(KTHR KCtx *c, KU a, KU b) { float x = KF(a), y = KF(b); return expr; }
KF2(add, KUF(x + y))
KF2(sub, KUF(x - y))
KF2(mul, KUF(x * y))
KF2(div, KUF(x / y))
KF2(mod, KUF(KMF(fmod)(x, y)))
KF2(pow, KUF(KMF(pow)(x, y)))
KF2(atan2, KUF(KMF(atan2)(x, y)))
KF2(is__eq, KBOOL(x == y))
KF2(is__ne, KBOOL(x != y))
KF2(is__lt, KBOOL(x < y))
KF2(is__le, KBOOL(x <= y))
KF2(is__gt, KBOOL(x > y))
KF2(is__ge, KBOOL(x >= y))
KF1(neg, KUF(-x))
KF1(abs, KUF(KMF(fabs)(x)))
KF1(sqrt, KUF(KMF(sqrt)(x)))
KF1(exp, KUF(KMF(exp)(x)))
KF1(log, KUF(KMF(log)(x)))
KF1(log2, KUF(KMF(log2)(x)))
KF1(log10, KUF(KMF(log10)(x)))
KF1(sin, KUF(KMF(sin)(x)))
KF1(cos, KUF(KMF(cos)(x)))
KF1(tan, KUF(KMF(tan)(x)))
KF1(asin, KUF(KMF(asin)(x)))
KF1(acos, KUF(KMF(acos)(x)))
KF1(atan, KUF(KMF(atan)(x)))
KF1(sinh, KUF(KMF(sinh)(x)))
KF1(cosh, KUF(KMF(cosh)(x)))
KF1(tanh, KUF(KMF(tanh)(x)))
KF1(floor, KUF(KMF(floor)(x)))
KF1(ceil, KUF(KMF(ceil)(x)))
KF1(trunc, KUF(KMF(trunc)(x)))
KF1(bits, KU32(a))
KF1(to__u32, !(x > 0.0f) || x >= 4294967296.0f ? 0 : (KW)(KU)x)
KINLINE KW KF_F32_dshow(KTHR KCtx *c, KW a) { k_fail(c, KE_FX); return 0; }
KINLINE KW KF_F32_dread(KTHR KCtx *c, KW a) { k_fail(c, KE_FX); return 0; }

// A KQ_ function's stack (see bendc): in the lane's private memory, or
// (KQ_SHARED) in the arena, word i of every lane side by side, so lanes at the
// same depth touch neighbouring words.
#ifdef KQ_SHARED
#define KQ_STACK KDEV KW *kq_ = c->Q + c->lane
#define KQ_ST(i) kq_[(KW)(i) * c->P->nlanes]
#else
#define KQ_STACK KW kq_[KR_WORDS]
#define KQ_ST(i) kq_[i]
#endif

// A KR_ function's frames: a thread-private stack, with room past its end
// for the frame that overflows it (the function then gives up, and the call
// runs through the kernel's frames).
#define KR_WORDS 128
#define KR_SLACK 64
KINLINE KW kr_push(KTHR KW *st, KTHR KW *sp, KW fp, KW ret, KW fs) {
  KW f = *sp;
  if (f + fs > KR_WORDS) {
    *sp = KR_WORDS + 1;
    f = KR_WORDS;
  } else {
    *sp = f + fs;
  }
  st[f] = ret;
  st[f + 1] = fp;
  st[f + 2] = 0;
  st[f + 3] = fs;
  return f;
}

// Generated after this file.
KINLINE KW k_frame_size(KW l);
KINLINE void k_cases(KTHR KCtx *c);
KINLINE KW k_kq(KTHR KCtx *c, KTHR bool *ok);

// Applies closure f to x; the value goes to block ret.
KINLINE void k_call_clo(KTHR KCtx *c, KW f, KW x, KW ret) {
  KW fw = k_word(c, f, 0), ar = k_word(c, f, 1), n = k_word(c, f, 2);
  KW l = (fw >> 52) == 0x7ff ? (fw & 0xffffffffu) : k_fn_label(c, fw & (((KW)1 << 48) - 1));
  KW fs = k_frame_size(l);
  if (l == 0 || fs == 0) {
    k_fail(c, KE_FX);
    c->rv = 0;
    c->pc = ret;
    return;
  }
  if (n + 1 < ar) {
    KW p = k_alloc(c, n + 4);
    KW w = KIX(c, p);
    c->H[w] = KCLO | l;
    c->H[w + 1] = ar;
    c->H[w + 2] = n + 1;
    for (KW i = 0; i < n; i++) c->H[w + 3 + i] = k_word(c, f, 3 + i);
    c->H[w + 3 + n] = x;
    // (the closure's captures moved: it goes, or, shared, shares them)
    KTAKE(f, (((KW)1 << n) - 1) << 3);
    c->rv = p;
    c->pc = ret;
    return;
  }
  KW nf = k_push(c, ret, fs);
  for (KW i = 0; i < n; i++) c->H[nf + 4 + i] = k_word(c, f, 3 + i);
  c->H[nf + 4 + n] = x;
  KTAKE(f, (((KW)1 << n) - 1) << 3);
  c->fp = nf;
  c->pc = l;
}

// A lane's state, from and to its slot of the arena.
KINLINE void k_load(KTHR KCtx *c, KCOH KW *H, KDEV KAU *A, KCP KParams *P, KDEV KW *G, KU lane) {
  c->H = H;
  c->G = G;
  c->Q = (KDEV KW *)H + P->q0;
  c->lane = lane;
  c->A = A;
  c->P = P;
  c->ab = P->ab;
  c->an = P->an;
  c->gb = P->gb;
  c->err = 0;
  c->kep = 0;
  c->kdirty = 0;
  c->kpn = 0;
  k_anone(c);
  // Word k of every lane side by side: the host reads the pcs of all lanes
  // after a dispatch, and so touches only their pages.
  KCOH KW *ls = H + P->lane0 + lane;
  KW n = P->nlanes;
  c->pc = ls[0];
  c->fp = ls[n];
  c->rv = ls[2 * n];
  c->dep = ls[3 * n];
  c->hp = ls[4 * n];
  c->he = ls[5 * n];
  c->blocks = ls[(10 + KQ_ARGS) * n];
  c->spare = ls[(11 + KQ_ARGS) * n];
  c->hs = c->blocks ? c->blocks + 2 : c->hp;
  c->ax = ls[6 * n];
  c->kq = ls[7 * n];
  c->kqret = ls[8 * n];
  c->kqfb = ls[9 * n];
  for (int i = 0; i < KQ_ARGS; i++) c->kqa[i] = ls[(10 + i) * n];
}

KINLINE void k_save(KTHR KCtx *c) {
  KCOH KW *ls = c->H + c->P->lane0 + c->lane;
  KW n = c->P->nlanes;
  ls[0] = c->pc;
  ls[n] = c->fp;
  ls[2 * n] = c->rv;
  ls[3 * n] = c->dep;
  ls[4 * n] = c->hp;
  ls[5 * n] = c->he;
  ls[6 * n] = c->ax;
  ls[7 * n] = c->kq;
  ls[8 * n] = c->kqret;
  ls[9 * n] = c->kqfb;
  ls[(10 + KQ_ARGS) * n] = c->blocks;
  ls[(11 + KQ_ARGS) * n] = c->spare;
  for (int i = 0; i < KQ_ARGS; i++) ls[(10 + i) * n] = c->kqa[i];
}

KINLINE bool k_active(KW pc) { return pc != PC_IDLE && pc != PC_KQ; }

// The kernel: each lane runs blocks, taking tasks from the queue when it has
// none. A lane that reaches a gathered call (PC_KQ) leaves the dispatch, and
// so does an idle one once no lane is running (A[KA_ACTIVE] counts them):
// the host then runs the calls with bend_kq, all at once, and dispatches this
// again. (A long call run here, inside this big kernel, runs 3-5x slower.)
#ifdef __METAL_VERSION__
kernel void bend_kernel(device coherent(device) KW *H [[buffer(0)]], device KAU *A [[buffer(1)]],
  constant KParams &PP [[buffer(2)]], device KW *G [[buffer(3)]], uint lane [[thread_position_in_grid]]) {
  constant KParams *P = &PP;
#else
static void bend_kernel(KW *H, KAU *A, const KParams *P, KW *G, uint32_t lane) {
#endif
  if (lane >= P->nlanes) return;
  KCtx cx;
  KTHR KCtx *c = &cx;
  k_load(c, H, A, P, G, lane);
#ifdef K_FREE
  // (here, not on the host: pages only the device touches cost the
  // process no memory)
  if (P->fresh)
    for (KW n = 0; n < K_NFC; n++) K_FLH(c, n) = 0;
#endif
  KW budget = P->budget;
  for (KW step = 0; step < budget; step++) {
    if (c->pc == PC_KQ) break;
    if (c->pc == PC_IDLE) {
      // (the first idle lane of the SIMD group reads the counters for the
      // group: 8192 lanes polling them slowed the forks 3x)
      KU st = 0;
      if (K_SIMD_FIRST()) {
        st = K_LOAD(&A[KA_DONE]) != 0 || K_LOAD(&A[KA_ERR]) != 0 ? 1u : 0u;
        if (K_LOAD(&A[KA_QHEAD]) != K_LOAD(&A[KA_QTAIL])) st |= 2u;
        else if (K_LOAD(&A[KA_ACTIVE]) == 0) st |= 4u;
      }
      st = K_SIMD_BCAST(st);
      if (st & 1u) break;
      if (!(st & 2u) || !k_pop_task(c)) {
        if (st & 4u) break;
        continue;
      }
      K_ADD(&A[KA_ACTIVE], 1u);
    }
    switch (c->pc) {
      case PC_ROOT: {
        H[2] = c->rv;
        K_FENCE();
        K_STORE(&A[KA_DONE], 1u);
        c->pc = PC_IDLE;
        break;
      }
      case PC_JOIN: {
        k_arrive(c, c->fp, c->ax, c->rv);
        break;
      }
      case PC_TASK: {
        // A forked thunk: rv is its closure, fp its join, dep its depth
        // and (dep >> 32) its index.
        KW i = c->dep >> 32;
        c->dep &= 0xffffffffu;
        k_call_clo(c, c->rv, 0, PC_JOIN);
        c->H[c->fp + 2] = i;
        break;
      }
      default: {
        k_cases(c);
#ifdef K_FREE
        // A call that may fork deep in its callees (K_KQLIM) runs through
        // the frames while they still fork, and past that as a KQ_ call
        // with no limit: one that gave up after freeing its arguments
        // could not run again (see k_take).
        if (c->pc == PC_KQ && (c->kqfb & K_KQLIM)) {
          if (KFORK) c->pc = c->kqfb & ~K_KQLIM;
          else c->kqfb &= ~K_KQLIM;
        }
#endif
        break;
      }
    }
    if (!k_active(c->pc)) K_SUB(&A[KA_ACTIVE], 1u);
    if (c->err != 0) {
      KU z = 0;
      K_CAS(&A[KA_ERR], z, c->err);
      break;
    }
  }
  k_save(c);
}

// The waiting calls, a lane each: a small kernel, which runs them fast.
#ifdef __METAL_VERSION__
kernel void bend_kq(device coherent(device) KW *H [[buffer(0)]], device KAU *A [[buffer(1)]],
  constant KParams &PP [[buffer(2)]], device KW *G [[buffer(3)]], uint lane [[thread_position_in_grid]]) {
  constant KParams *P = &PP;
#else
static void bend_kq(KW *H, KAU *A, const KParams *P, KW *G, uint32_t lane) {
#endif
  if (P->kqmap) {
    if (lane >= H[P->kqmap]) return;
    lane = (KU)H[P->kqmap + 1 + lane];
  }
  if (lane >= P->nlanes || H[P->lane0 + lane] != PC_KQ) return;
  KCtx cx;
  KTHR KCtx *c = &cx;
  k_load(c, H, A, P, G, lane);
  bool ok = true;
  KW h0 = c->hp, e0 = c->he, b0 = c->blocks;
  c->kqlim = (c->kqfb & K_KQLIM) ? K_KQSTEPS : ~(KW)0;
#ifdef K_FREE
  c->kep = P->kqep << 32;
#endif
  KW r = k_kq(c, &ok);
#ifdef K_FREE
  if ((c->err == KE_HEAP || !ok) && c->kdirty) {
    // It freed what it would read again: the device call fails (a full
    // arena then runs it again from the start, in a bigger one).
    KU z = 0;
    K_CAS(&A[KA_ERR], z, c->err == KE_HEAP ? (KU)KE_HEAP : (KU)KE_FREE);
    k_save(c);
    return;
  }
  if (c->err == KE_HEAP || !ok) {
    // Only its own objects are on the free lists past their old heads:
    // take them off, the span they are in goes back. The older objects it
    // held back stay as they were, for the next run.
    for (KW n = 1; n < K_NFC; n++) {
      KW f = K_FLH(c, n);
      while (f != 0 && K_EPOCH(c->H[f - 1]) == P->kqep) f = c->H[f];
      K_FLH(c, n) = f;
    }
    c->kep = 0;
  } else {
    c->kep = 0;
    for (KU i = 0; i < c->kpn; i++) {
      KW ix = K_PND(c, i), fc = k_flc(c->H[ix - 1] & 0xffffffff);
      c->H[ix] = K_FLH(c, fc);
      K_FLH(c, fc) = ix;
    }
  }
  c->kpn = 0;
#endif
  // A call that ran out of arena waits for the host to grow it, and runs
  // again (what it allocated is garbage: its result reached none of it).
  if (c->err == KE_HEAP) {
    k_rewind(c, h0, e0, b0);
    K_STORE(&A[KA_GROW], 1u);
    k_save(c);
    return;
  }
  // A call that gave up (ok false) runs again through the frames.
  if (!ok) {
    k_rewind(c, h0, e0, b0);
  } else {
    r = k_region(c, h0, e0, r);
  }
  c->rv = r;
  c->pc = ok ? c->kqret : (c->kqfb & ~K_KQLIM);
  if (c->err != 0) {
    KU z = 0;
    K_CAS(&A[KA_ERR], z, c->err);
  }
  k_save(c);
}

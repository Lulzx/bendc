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
#endif

// The control words (A).
#define KA_DONE 0
#define KA_ERR 1
#define KA_HEAP 2
#define KA_QHEAD 3
#define KA_QTAIL 4
#define KA_ACTIVE 5
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
} KParams;

#define PC_IDLE 0
#define PC_ROOT 1
#define PC_JOIN 2
#define PC_TASK 3
#define PC_KQ 4      // waiting to run a KQ_ call (see the kernel's loop)
#define KQ_ARGS 12
#define K_LANE (10 + KQ_ARGS)  // words of a lane's saved state

#define K_CHUNK 256

// The errors a lane can hit.
#define KE_FX 2      // an effect, or a closure with no device code
#define KE_NAT 3     // a Nat past 2^48 - 1
#define KE_HEAP 4
#define KE_QUEUE 6
#define KE_MATCH 7
#define KE_PC 8

typedef struct {
  KCOH KW *H;
  KDEV KW *G;
  KDEV KW *Q;
  KDEV KAU *A;
  KW ab, an, gb, lane;
  KW pc, fp, rv, dep, hp, he, ax;
  KU ko[8];            // a flat call's result fields (see KBOX)
  KW hs;               // where the lane's current heap chunk starts (or its hp at load)
  KU err;
  KW kq, kqret, kqfb;  // a KQ_ call: its def, where its value goes, the way through frames
  KW kqa[KQ_ARGS];     // and its arguments
  KW kqlim;            // the blocks it may run (K_KQLIM)
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
#define KIX(c, v) (((v) - (c)->ab) >> 3)
#define KPTR(c, i) ((c)->ab + ((KW)(i) << 3))
// The generated blocks reach frames only through these, so a def's blocks
// also run inside its KR_ function (thread-private frames; see bendc).
#define KS(k) c->H[c->fp + 4 + (k)]
#define KPC c->pc
#define KFP c->fp
#define KRV c->rv
#define KFORK (c->dep < c->P->fork_limit)
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
KINLINE KW k_word(KTHR KCtx *c, KW v, KW i) {
  if (k_in(c, v)) return c->H[((v - c->ab) >> 3) + i];
  return c->G[((v - c->gb) >> 3) + i];
}
KINLINE KW k_tag(KTHR KCtx *c, KW v) { return (v & 1) ? (v >> 3) : (k_word(c, v, 0) & (KW)0xffcfffff); }
#define KTAG(v) k_tag(c, v)
#define KFLD(v, i) k_word(c, v, 1 + (i))

// n words from the lane's heap chunk; the word before an object holds its
// size (the host copies results out with it). Chunk 0 is scratch: a lane
// that ran out writes there, and stops.
KINLINE KW k_alloc(KTHR KCtx *c, KW n) {
  if (c->hp + n + 1 > c->he) {
    KW need = n + 1 > K_CHUNK ? n + 1 : K_CHUNK;
    KW k = (need + K_CHUNK - 1) / K_CHUNK;
    KW at = (KW)K_ADD(&c->A[KA_HEAP], (KU)k);
    KW start = c->P->heap0 + at * K_CHUNK;
    if (start + k * K_CHUNK > c->P->heap0 + c->P->heapw) {
      k_fail(c, KE_HEAP);
      c->hp = c->P->heap0;
      c->he = c->hp + K_CHUNK;
      return KPTR(c, c->P->heap0 + 1);
    }
    c->hp = start;
    c->hs = start;
    c->he = start + k * K_CHUNK;
  }
  KW i = c->hp;
  c->H[i] = n;
  c->hp += n + 1;
  return KPTR(c, i + 1);
}

// A flat call (KX_ or KQ_) neither forks nor writes into older objects, and
// an object only points to older ones: what the call allocated is garbage
// unless its result reaches it. k_region takes it back: all of it when the
// result is older than the call (or not an object), else all but the result,
// moved down, when the result is the only new object it reaches. h0 and e0
// are the lane's hp and he before the call; when the call took a new chunk,
// only that chunk's words are taken back.
KINLINE KW k_region(KTHR KCtx *c, KW h0, KW e0, KW r) {
  if (c->hp == h0) return r;
  KW lo = c->he == e0 ? h0 : c->hs;
  KW b = c->ab + (lo << 3), n = (c->hp - lo) << 3;
  if (r - b >= n) {
    c->hp = lo;
    return r;
  }
  KW p = (r - c->ab) >> 3, m = c->H[p - 1];
  for (KW i = 1; i < m; i++) {
    if (c->H[p + i] - b < n) return r;
  }
  for (KW i = 0; i <= m; i++) c->H[lo + i] = c->H[p - 1 + i];
  c->hp = lo + m + 1;
  return KPTR(c, lo + 1);
}
#define KREG(e) ({ KW kh0_ = c->hp, ke0_ = c->he; KW kr_ = (e); k_region(c, kh0_, ke0_, kr_); })
// The same for a call whose result is a scalar (a U32, F32 or Bool): it reaches
// nothing the call allocated.
#define KSCAL(e) ({ KW kh0_ = c->hp, ke0_ = c->he; KU kr_ = (e); if (c->he == ke0_) c->hp = kh0_; kr_; })

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
}

// The queue (Vyukov's bounded MPMC queue): an entry is {pc, fp, rv, dep}.
// A slot keeps its sequence number less its index, so a zeroed queue is
// empty (the host clears only the slots a call used).
#define KQ_SEQ(i) (K_LOAD(&c->A[KA_SEQ + (i)]) + (KU)(i))
#define KQ_SET(i, s) K_STORE(&c->A[KA_SEQ + (i)], (s) - (KU)(i))
KINLINE bool k_push_task(KTHR KCtx *c, KW pc, KW fp, KW rv, KW dep) {
  KW mask = c->P->qcap - 1;
  KU pos = K_LOAD(&c->A[KA_QTAIL]);
  for (int tries = 0;; tries++) {
    if (tries > 100000) return false;
    KU seq = KQ_SEQ(pos & mask);
    KI dif = (KI)(seq - pos);
    if (dif == 0) {
      KU e = pos;
      if (K_CAS(&c->A[KA_QTAIL], e, pos + 1)) break;
      pos = e;
    } else if (dif < 0) {
      return false;
    } else {
      pos = K_LOAD(&c->A[KA_QTAIL]);
    }
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
  KU pos = K_LOAD(&c->A[KA_QHEAD]);
  for (int tries = 0;; tries++) {
    if (tries > 64) return false;
    KU seq = KQ_SEQ(pos & mask);
    KI dif = (KI)(seq - (pos + 1));
    if (dif == 0) {
      KU e = pos;
      if (K_CAS(&c->A[KA_QHEAD], e, pos + 1)) break;
      pos = e;
    } else if (dif < 0) {
      return false;
    } else {
      pos = K_LOAD(&c->A[KA_QHEAD]);
    }
  }
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
// An Array is a host block (see "Arrays" in bendrt.h): the device runs no
// Array operation, and a call that meets one runs on the CPU.
KINLINE bool k_arr(KTHR KCtx *c) { k_fail(c, KE_FX); return false; }
#define KF_ARR(c) (k_fail(c, KE_FX), (KW)0)
#define KF_Array_dsize(c, ...) KF_ARR(c)
#define KF_Array_dget(c, ...) KF_ARR(c)
#define KF_Array_dswap(c, ...) KF_ARR(c)
#define KF_Array_dset(c, ...) KF_ARR(c)
#define KF_Array_dget_x37w(c, ...) KF_ARR(c)
#define KF_Array_dswap_x37w(c, ...) KF_ARR(c)
#define KF_Array_dset_x37w(c, ...) KF_ARR(c)
#define KF_Array_dnew(c, ...) KF_ARR(c)
#define KF_Array_dclone(c, ...) KF_ARR(c)
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
    c->rv = p;
    c->pc = ret;
    return;
  }
  KW nf = k_push(c, ret, fs);
  for (KW i = 0; i < n; i++) c->H[nf + 4 + i] = k_word(c, f, 3 + i);
  c->H[nf + 4 + n] = x;
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
  c->hs = c->hp;
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
  KW budget = P->budget;
  for (KW step = 0; step < budget; step++) {
    if (c->pc == PC_KQ) break;
    if (c->pc == PC_IDLE) {
      if (K_LOAD(&A[KA_DONE]) != 0 || K_LOAD(&A[KA_ERR]) != 0) break;
      if (!k_pop_task(c)) {
        if (K_LOAD(&A[KA_ACTIVE]) == 0) break;
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
  if (lane >= P->nlanes || H[P->lane0 + lane] != PC_KQ) return;
  KCtx cx;
  KTHR KCtx *c = &cx;
  k_load(c, H, A, P, G, lane);
  bool ok = true;
  KW h0 = c->hp, e0 = c->he;
  c->kqlim = (c->kqfb & K_KQLIM) ? K_KQSTEPS : ~(KW)0;
  KW r = k_kq(c, &ok);
  // A call that gave up (ok false) runs again through the frames.
  if (!ok) {
    if (c->he == e0) c->hp = h0;
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

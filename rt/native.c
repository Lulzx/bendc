// The native backend's calls into the runtime
// ============================================
//
// `bendc --native` writes a program's code as AArch64 machine code (see
// asm.bend and "Native code generation" in bendc.bend) that calls the
// runtime through the platform ABI. Most of what it calls is already a
// function of build/bendrt.o (apply, str_cache, arr_node, pr_str, ...); the
// runtime's static inline functions are not, so this file gives each one the
// generated code uses an external name: N_ and the mangled name of the Base
// def it implements (every def of Natives() in bendc.bend), and bn_alloc for
// the allocator, and bn_flt for float literals. It is compiled once, beside
// bendrt.o (as natives.o: see Cc.link in rt/cc.c).

#define BEND_NATIVE_MAP_BIT 1
#define BEND_NATIVE_STR 1
#define BEND_NATIVE_MAP 1
#include "bendrt_split.h"

V *bn_alloc(V words) { return halloc((size_t)words); }

// A float literal's bits, read once as C reads it (the slot holds them
// with bit 32 set: a read 0.0 is then not an empty slot).
V bn_flt(V *slot, const char *s) {
  V c = __atomic_load_n(slot, __ATOMIC_ACQUIRE);
  if (c) return (uint32_t)c;
  V v = VF(strtof(s, 0));
  __atomic_store_n(slot, v | ((V)1 << 32), __ATOMIC_RELEASE);
  return v;
}

#define N1(f) V N_##f(V a) { return F_##f(a); }
#define N2(f) V N_##f(V a, V b) { return F_##f(a, b); }
#define N3(f) V N_##f(V a, V b, V c) { return F_##f(a, b, c); }
#define N4(f) V N_##f(V a, V b, V c, V d) { return F_##f(a, b, c, d); }

N1(U32_dinc) N2(U32_dadd) N2(U32_dsub) N2(U32_dmul) N2(U32_ddiv) N2(U32_dmod) N1(U32_dnot)
N2(U32_dand) N2(U32_dor) N2(U32_dxor) N1(U32_dshl) N1(U32_dshr) N2(U32_dshln) N2(U32_dshrn)
N2(U32_dcmp) N2(U32_dis__eq) N2(U32_dis__ne) N2(U32_dis__lt) N2(U32_dis__le) N2(U32_dis__gt)
N2(U32_dis__ge) N1(U32_dis__zero) N1(U32_dis__even) N1(U32_dto__nat) N1(U32_dfrom__nat)
N2(U32_dmin) N2(U32_dmax) N2(U32_dpow) N1(U32_dlog2) N1(U32_dto__f32)

N1(Nat_ddouble) N2(Nat_dadd) N2(Nat_dsub) N2(Nat_dmul) N2(Nat_ddivmod) N2(Nat_ddiv)
N2(Nat_dmod) N2(Nat_dcmp) N2(Nat_dis__eq) N2(Nat_dis__ne) N2(Nat_dis__lt) N2(Nat_dis__le)
N2(Nat_dis__gt) N2(Nat_dis__ge) N2(Nat_dmin) N2(Nat_dmax) N2(Nat_dpow) N1(Nat_dshow)

N1(Chk_dmemo_dnew) N2(Chk_dmemo_dhas) N1(Chk_dmemo_dget) N3(Chk_dmemo_dset)

N2(F32_dadd) N2(F32_dsub) N2(F32_dmul) N2(F32_ddiv) N2(F32_dmod) N2(F32_dpow) N2(F32_datan2)
N2(F32_dis__eq) N2(F32_dis__ne) N2(F32_dis__lt) N2(F32_dis__le) N2(F32_dis__gt) N2(F32_dis__ge)
N1(F32_dneg) N1(F32_dabs) N1(F32_dsqrt) N1(F32_dexp) N1(F32_dlog) N1(F32_dlog2)
N1(F32_dlog10) N1(F32_dsin) N1(F32_dcos) N1(F32_dtan) N1(F32_dasin) N1(F32_dacos)
N1(F32_datan) N1(F32_dsinh) N1(F32_dcosh) N1(F32_dtanh) N1(F32_dfloor) N1(F32_dceil)
N1(F32_dtrunc) N1(F32_dbits) N1(F32_dto__u32) N1(F32_dshow) N1(F32_dread)

N2(Map_dbit) N3(Map_dget) N2(Map_dhas) N2(String_dcmp) N2(String_deq)

N1(Array_dsize) N2(Array_dget) N3(Array_dswap) N3(Array_dset) N2(Array_dnew) N1(Array_dclone)
N3(Array_datomic_dadd) N3(Array_datomic_dmin) N3(Array_datomic_dmax) N3(Array_datomic_dand)
N3(Array_datomic_dor) N3(Array_datomic_dxor) N3(Array_datomic_dexch) N4(Array_datomic_dcas)
N3(Array_datomic_dfadd)

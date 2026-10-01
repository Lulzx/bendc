#ifndef CID_UNIT
#define CID_UNIT ((1u << 16) | 0u)
#endif
#ifndef CID_FALSE
#define CID_FALSE ((1u << 16) | 0u)
#endif
#ifndef CID_TRUE
#define CID_TRUE ((1u << 16) | 1u)
#endif
#ifndef CID_LT
#define CID_LT ((1u << 16) | 0u)
#endif
#ifndef CID_EQ
#define CID_EQ ((1u << 16) | 1u)
#endif
#ifndef CID_GT
#define CID_GT ((1u << 16) | 2u)
#endif
#ifndef CID_INL
#define CID_INL 0u
#endif
#ifndef CID_INR
#define CID_INR 1u
#endif
#ifndef CID_TUPLE
#define CID_TUPLE 0u
#endif
#ifndef CID_NONE
#define CID_NONE ((1u << 16) | 0u)
#endif
#ifndef CID_SOME
#define CID_SOME 1u
#endif
#ifndef CID_FAIL
#define CID_FAIL 0u
#endif
#ifndef CID_DONE
#define CID_DONE 1u
#endif
#ifndef CID_NIL
#define CID_NIL ((1u << 16) | 0u)
#endif
#ifndef CID_CON
#define CID_CON 1u
#endif
#ifndef CID_WNIL
#define CID_WNIL ((1u << 16) | 0u)
#endif
#ifndef CID_WCON
#define CID_WCON 0u
#endif
#ifndef CID_U32
#define CID_U32 ((2u << 16) | 0u)
#endif
#ifndef CID_F32
#define CID_F32 ((2u << 16) | 0u)
#endif
#ifndef CID_CHR
#define CID_CHR ((2u << 16) | 0u)
#endif
#ifndef CID_SNIL
#define CID_SNIL ((1u << 16) | 0u)
#endif
#ifndef CID_SCON
#define CID_SCON 1u
#endif
#ifndef CID_PIX
#define CID_PIX ((7u << 16) | 0u)
#endif
#ifndef CID_QUA
#define CID_QUA 1u
#endif
#ifndef CID_KEY
#define CID_KEY 0u
#endif
#ifndef CID_MOUSE
#define CID_MOUSE 1u
#endif
#ifndef CID_MOVE
#define CID_MOVE 2u
#endif
#ifndef CID_LOOK
#define CID_LOOK 3u
#endif
#ifndef CID_SCROLL
#define CID_SCROLL 4u
#endif
#ifndef CID_CLOSE
#define CID_CLOSE ((1u << 16) | 5u)
#endif
#ifndef CID_MTIP
#define CID_MTIP ((1u << 16) | 0u)
#endif
#ifndef CID_MLEAF
#define CID_MLEAF 1u
#endif
#ifndef CID_MNODE
#define CID_MNODE 2u
#endif
#ifndef CID_EMIT
#define CID_EMIT 0u
#endif
#ifndef CID_HALT
#define CID_HALT 1u
#endif
#ifndef CID_APP
#define CID_APP 0u
#endif
#ifndef CID_IO_PRINT
#define CID_IO_PRINT ((3u << 16) | 0u)
#endif
#ifndef CID_IO_WRITE
#define CID_IO_WRITE ((3u << 16) | 1u)
#endif
#ifndef CID_IO_PRINT_ERR
#define CID_IO_PRINT_ERR ((3u << 16) | 2u)
#endif
#ifndef CID_IO_GET_ENV
#define CID_IO_GET_ENV ((3u << 16) | 3u)
#endif
#ifndef CID_IO_ARGS
#define CID_IO_ARGS ((3u << 16) | 4u)
#endif
#ifndef CID_PROCESS_RUN
#define CID_PROCESS_RUN ((3u << 16) | 5u)
#endif
#ifndef CID_IO_RANDOM_U32
#define CID_IO_RANDOM_U32 ((3u << 16) | 6u)
#endif
#ifndef CID_IO_SPAWN
#define CID_IO_SPAWN ((3u << 16) | 7u)
#endif
#ifndef CID_IO_SLEEP
#define CID_IO_SLEEP ((3u << 16) | 8u)
#endif
#ifndef CID_IO_NOW
#define CID_IO_NOW ((3u << 16) | 9u)
#endif
#ifndef CID_IO_THREAD_COUNT
#define CID_IO_THREAD_COUNT ((3u << 16) | 10u)
#endif
#ifndef CID_CHAN_NEW
#define CID_CHAN_NEW ((3u << 16) | 11u)
#endif
#ifndef CID_CHAN_SEND
#define CID_CHAN_SEND ((3u << 16) | 12u)
#endif
#ifndef CID_CHAN_RECV
#define CID_CHAN_RECV ((3u << 16) | 13u)
#endif
#ifndef CID_CHAN_CLOSE
#define CID_CHAN_CLOSE ((3u << 16) | 14u)
#endif
#ifndef CID_FILE_OPEN
#define CID_FILE_OPEN ((3u << 16) | 15u)
#endif
#ifndef CID_FILE_READ
#define CID_FILE_READ ((3u << 16) | 16u)
#endif
#ifndef CID_FILE_READ_BYTES
#define CID_FILE_READ_BYTES ((3u << 16) | 17u)
#endif
#ifndef CID_FILE_READ_AT
#define CID_FILE_READ_AT ((3u << 16) | 18u)
#endif
#ifndef CID_FILE_SIZE
#define CID_FILE_SIZE ((3u << 16) | 19u)
#endif
#ifndef CID_FILE_WRITE
#define CID_FILE_WRITE ((3u << 16) | 20u)
#endif
#ifndef CID_FILE_WRITE_BYTES
#define CID_FILE_WRITE_BYTES ((3u << 16) | 21u)
#endif
#ifndef CID_FILE_CLOSE
#define CID_FILE_CLOSE ((3u << 16) | 22u)
#endif
#ifndef CID_TCP_LISTEN
#define CID_TCP_LISTEN ((3u << 16) | 23u)
#endif
#ifndef CID_TCP_ACCEPT
#define CID_TCP_ACCEPT ((3u << 16) | 24u)
#endif
#ifndef CID_TCP_CONNECT
#define CID_TCP_CONNECT ((3u << 16) | 25u)
#endif
#ifndef CID_TCP_SEND
#define CID_TCP_SEND ((3u << 16) | 26u)
#endif
#ifndef CID_TCP_RECV
#define CID_TCP_RECV ((3u << 16) | 27u)
#endif
#ifndef CID_TCP_SEND_BYTES
#define CID_TCP_SEND_BYTES ((3u << 16) | 28u)
#endif
#ifndef CID_TCP_RECV_BYTES
#define CID_TCP_RECV_BYTES ((3u << 16) | 29u)
#endif
#ifndef CID_TCP_POLL
#define CID_TCP_POLL ((3u << 16) | 30u)
#endif
#ifndef CID_UDP_BIND
#define CID_UDP_BIND ((3u << 16) | 31u)
#endif
#ifndef CID_UDP_SEND_TO
#define CID_UDP_SEND_TO ((3u << 16) | 32u)
#endif
#ifndef CID_UDP_RECV_FROM
#define CID_UDP_RECV_FROM ((3u << 16) | 33u)
#endif
#ifndef CID_UDP_POLL
#define CID_UDP_POLL ((3u << 16) | 34u)
#endif
#ifndef CID_SOCKET_CLOSE
#define CID_SOCKET_CLOSE ((3u << 16) | 35u)
#endif
#ifndef CID_LISTENER_CLOSE
#define CID_LISTENER_CLOSE ((3u << 16) | 36u)
#endif
#ifndef CID_WINDOW_OPEN
#define CID_WINDOW_OPEN ((3u << 16) | 37u)
#endif
#ifndef CID_WINDOW_FRAME
#define CID_WINDOW_FRAME ((3u << 16) | 38u)
#endif
#ifndef CID_WINDOW_SET_TITLE
#define CID_WINDOW_SET_TITLE ((3u << 16) | 39u)
#endif
#ifndef CID_WINDOW_GRAB
#define CID_WINDOW_GRAB ((3u << 16) | 40u)
#endif
#ifndef CID_WINDOW_CLOSE
#define CID_WINDOW_CLOSE ((3u << 16) | 41u)
#endif
#ifndef CID_AUDIO_OPEN
#define CID_AUDIO_OPEN ((3u << 16) | 42u)
#endif
#ifndef CID_AUDIO_WRITE
#define CID_AUDIO_WRITE ((3u << 16) | 43u)
#endif
#ifndef CID_AUDIO_CLOSE
#define CID_AUDIO_CLOSE ((3u << 16) | 44u)
#endif
#ifndef CID_LEAF
#define CID_LEAF ((7u << 16) | 0u)
#endif
#define BEND_NATIVE_MAP_BIT 1
#define BEND_NATIVE_STR 1
#define BEND_NATIVE_MAP 1
#ifdef BEND_RT_SPLIT
#include "bendrt_split.h"
#else
#include "bendrt.h"
#endif

// IO
// ==

Term io_print_run(Env e, Term* f, IoWork* w) {
  uint64_t n = 0;
  char* text = io_cstr(e, f[0], &n);
  io_out(stdout, text, n);
  io_out(stdout, "\n", 1);
  free(text);
  return term_pak(CID_UNIT, 0);
}

static void __attribute__((constructor)) io_print_use(void) {
  io_eff(CID_IO_PRINT, io_print_run, 0);
}


#ifdef __TINYC__
// tcc ignores __attribute__((constructor)): main calls these
static void bend_ctors(void) {
  io_print_use();
}
#endif
BEND_NSP_BEGIN
static V F_main(void);
static V G_make(V a0, V a1);
static V L7(V *a);
static V G_sum(V a0);
static V L13(V *a);
static V G_rounds(V a0, V a1);
static V L19(V *a);
static V G_rounds(V a0, V a1);
static V L25(V *a);
static V L32(V *a);
static V G_sum(V a0);
static V W_main(V *a);
static V W_U32_dis__zero(V *a);
static V F_U32_dshow_dif(V a0_, V a1);
static V H_F_U32_dshow_dif(V a0_, V a1);
static V W_U32_dshow_dif(V *a);
static V F_U32_dshow_dgo_x37s1953093269x247193397(V a0, V a1);
static V W_U32_dshow_dgo_x37s1953093269x247193397(V *a);
static V F_U32_dshow_dfin(V a0, V a1, V a2_, V a3);
static V W_U32_dshow_dfin(V *a);
static V W_U32_dmod(V *a);
static V W_U32_dadd(V *a);
static V W_U32_ddiv(V *a);
static V F_U32_dshow_dgo(V a0, V a1, V a2);
static V W_U32_dshow_dgo(V *a);
static V F_sum(V a0);
static V H_F_sum(V a0);
static V L63(V *a);
static V W_sum(V *a);
static V S_sum(V a0);
static V H_S_sum(V a0);
static V F_IO_dprint(V a0);
static V E_IO_dprint(V *a);
static V W_IO_dprint(V *a);
static V F_IO_dbind(V a2, V a3);
static V L75(V *a);
static V L76(V *a);
static V L77(V *a);
static V W_IO_dbind(V *a);
static V F_rounds(V a0, V a1_);
static V W_rounds(V *a);
static V F_make_x37s3795296409x247312561(V a0_);
static V L88(V *a);
static V W_make_x37s3795296409x247312561(V *a);
static V F_make_x37s675041226x247282770(V a0_);
static V L99(V *a);
static V W_make_x37s675041226x247282770(V *a);
static V F_make_x37s2689494263x247252979(V a0_);
static V L110(V *a);
static V W_make_x37s2689494263x247252979(V *a);
static V F_make_x37s4233607528x247223188(V a0_);
static V L121(V *a);
static V W_make_x37s4233607528x247223188(V *a);
static V F_make_x37s1953093269x247193397(V a0_);
static V L132(V *a);
static V W_make_x37s1953093269x247193397(V *a);
static V F_make_x37s3305376709x8269577(V a0_);
static V L143(V *a);
static V W_make_x37s3305376709x8269577(V *a);
static V F_make_x37s2491568216x8239786(V a0_);
static V L154(V *a);
static V W_make_x37s2491568216x8239786(V *a);
static V F_make_x37s1291691603x8209995(V a0_);
static V L165(V *a);
static V W_make_x37s1291691603x8209995(V *a);
static V F_make_x37s32637286x8180204(V a0_);
static V L176(V *a);
static V W_make_x37s32637286x8180204(V *a);
static V F_make_x37s3239606481x8150413(V a0_);
static V L187(V *a);
static V W_make_x37s3239606481x8150413(V *a);
static V F_make_x37s2405009636x8120622(V a0_);
static V L198(V *a);
static V W_make_x37s2405009636x8120622(V *a);
static V F_make_x37s1586577935x8090831(V a0_);
static V L209(V *a);
static V W_make_x37s1586577935x8090831(V *a);
static V F_make_x37s3867092194x8061040(V a0_);
static V L220(V *a);
static V W_make_x37s3867092194x8061040(V *a);
static V F_make_x37s1860454509x8031249(V a0_);
static V L231(V *a);
static V W_make_x37s1860454509x8031249(V *a);
static V S_make_x37s1860454509x8031249(V a0_);
static V F_make_x37s509762208x8001458(V a0_);
static V W_make_x37s509762208x8001458(V *a);
static V W_U32_dinc(V *a);
static V F_make(V a0, V a1_);
static V L248(V *a);
static V W_make(V *a);
static V S_make(V a0, V a1_);

static V L32(V *a) {
return F_IO_dprint(({ V r33;
V v34 = G_sum(a[0]);
bend_share(v34);
r33 = F_U32_dshow_dif(v34, F_U32_dis__zero(v34));
r33; }));
}
static V L25(V *a) {
return F_IO_dbind(F_IO_dprint(({ V r26;
uint32_t (u27) = F_sum(a[0]);
r26 = F_U32_dshow_dif((u27), F_U32_dis__zero((u27)));
r26; })), mk_clo(L32, 2, 1, (V[]){a[0]}));
}
static V L19(V *a) {
return F_IO_dbind(F_IO_dprint(({ V r20;
V v21 = G_rounds(5u, 9u);
bend_share(v21);
r20 = F_U32_dshow_dif(v21, F_U32_dis__zero(v21));
r20; })), mk_clo(L25, 2, 1, (V[]){a[0]}));
}
static V L13(V *a) {
return F_IO_dbind(F_IO_dprint(({ V r14;
V v15 = G_rounds(8u, 0u);
bend_share(v15);
r14 = F_U32_dshow_dif(v15, F_U32_dis__zero(v15));
r14; })), mk_clo(L19, 2, 1, (V[]){a[0]}));
}
static V L7(V *a) {
return F_IO_dbind(F_IO_dprint(({ V r8;
V v9 = G_sum(a[0]);
bend_share(v9);
r8 = F_U32_dshow_dif(v9, F_U32_dis__zero(v9));
r8; })), mk_clo(L13, 2, 1, (V[]){a[0]}));
}
static V F_main(void) {
top:;
V v0 = G_make(13u, 3u);
bend_share(v0);
return F_IO_dbind(F_IO_dprint(({ V r1;
uint32_t (u2) = F_sum(v0);
r1 = F_U32_dshow_dif((u2), F_U32_dis__zero((u2)));
r1; })), mk_clo(L7, 2, 1, (V[]){v0}));
}
static V W_main(V *a) { (void)a; return F_main(); }
static V W_U32_dis__zero(V *a) { (void)a; return F_U32_dis__zero(a[0]); }
static __attribute__((noinline)) V H_F_U32_dshow_dif(V a0_, V a1) {
uint32_t a0 = (uint32_t)a0_;
top:;
V s43 = (a1);
if ((s43) == IMM(1)) {
return C2(1, 48u, IMM(0));
} else if ((s43) == IMM(0)) {
return F_U32_dshow_dgo_x37s1953093269x247193397((a0), IMM(0));
} else { bend_fail("runtime fail-stop"); }
}
BEND_UINL V F_U32_dshow_dif(V a0_, V a1) {
uint32_t a0 = (uint32_t)a0_;
if (((a1)) == IMM(1)) {
return C2(1, 48u, IMM(0));
}
return H_F_U32_dshow_dif(a0, a1);
}
static V W_U32_dshow_dif(V *a) { (void)a; return F_U32_dshow_dif(a[0], a[1]); }
BEND_UINL V F_U32_dshow_dgo_x37s1953093269x247193397(V a0, V a1) {
top:;
bend_share(a0);
return F_U32_dshow_dfin(9u, a1, a0, F_U32_dis__zero(a0));
}
static V W_U32_dshow_dgo_x37s1953093269x247193397(V *a) { (void)a; return F_U32_dshow_dgo_x37s1953093269x247193397(a[0], a[1]); }
static V F_U32_dshow_dfin(V a0, V a1, V a2_, V a3) {
uint32_t a2 = (uint32_t)a2_;
top:;
V s47 = (a3);
if ((s47) == IMM(1)) {
return a1;
} else if ((s47) == IMM(0)) {
return F_U32_dshow_dgo((a0), F_U32_ddiv((a2), 10u), C2(1, F_U32_dadd(48u, F_U32_dmod((a2), 10u)), a1));
} else { bend_fail("runtime fail-stop"); }
}
static V W_U32_dshow_dfin(V *a) { (void)a; return F_U32_dshow_dfin(a[0], a[1], a[2], a[3]); }
static V W_U32_dmod(V *a) { (void)a; return F_U32_dmod(a[0], a[1]); }
static V W_U32_dadd(V *a) { (void)a; return F_U32_dadd(a[0], a[1]); }
static V W_U32_ddiv(V *a) { (void)a; return F_U32_ddiv(a[0], a[1]); }
static V F_U32_dshow_dgo(V a0, V a1, V a2) {
top:;
bend_share(a1);
V s52 = a0;
if ((s52) == 0) {
bend_dead(a1);
return a2;
} else if (nat_ge(s52, 1)) {
return F_U32_dshow_dfin(nat_subk(s52, 1), a2, a1, F_U32_dis__zero(a1));
} else { bend_fail("runtime fail-stop"); }
}
static V W_U32_dshow_dgo(V *a) { (void)a; return F_U32_dshow_dgo(a[0], a[1], a[2]); }
static V L63(V *a) {
return F_sum(a[0]);
}
static __attribute__((noinline)) V H_F_sum(V a0) {
top:;
V s55 = a0;
if (IS_LI(s55, 0)) {
return LI_V(s55);
} else if (IS_B(s55)) {
V m56 = FLB(s55, 1);
V m57 = FLB(s55, 0);
V m58 = s55;
bend_take(m58, 258);
V p59_0; V p59_1; 
static int pcs62;
if (par_depth >= par_front || par_small(&pcs62)) {
#define F_sum S_sum
p59_0 = F_sum(m57);
p59_1 = F_sum(m56);
#undef F_sum
} else {
par_depth += 1;
V p62_0t = par_fork_at(&pcs62, mk_clo(L63, 2, 1, (V[]){m57}));
V p62_1 = F_sum(m56);
V p62_0 = par_join(p62_0t);
p59_0 = p62_0; p59_1 = p62_1; 
par_depth -= 1;
}
return F_U32_dadd(p59_0, p59_1);
} else { bend_fail("runtime fail-stop"); }
}
BEND_UINL V F_sum(V a0) {
if (IS_LI(a0, 0)) {
return LI_V(a0);
}
return H_F_sum(a0);
}
static V W_sum(V *a) { (void)a; return F_sum(a[0]); }
BEND_UINL V S_sum(V a0) {
if (IS_LI(a0, 0)) {
return LI_V(a0);
}
return H_S_sum(a0);
}
#define F_sum S_sum
static __attribute__((noinline)) V H_S_sum(V a0) {
top:;
V s67 = a0;
if (IS_LI(s67, 0)) {
return LI_V(s67);
} else if (IS_B(s67)) {
V m68 = FLB(s67, 1);
V m69 = FLB(s67, 0);
V m70 = s67;
bend_take(m70, 258);
V p71_0 = F_sum(m69);
V p71_1 = F_sum(m68);
return F_U32_dadd(p71_0, p71_1);
} else { bend_fail("runtime fail-stop"); }
}
#undef F_sum
static V E_IO_dprint(V *a) { return io_req(CID_IO_PRINT, 2, (V[]){a[0], a[2]}); }
static V F_IO_dprint(V a0) { return mk_clo(E_IO_dprint, 3, 1, (V[]){a0}); }
static V W_IO_dprint(V *a) { (void)a; return F_IO_dprint(a[0]); }
static V L77(V *a) {
return apply(apply(apply(a[2], a[3]), a[1]), a[0]);
}
static V L76(V *a) {
return apply(apply(a[2], a[1]), mk_clo(L77, 4, 3, (V[]){a[3], a[1], a[0]}));
}
static V L75(V *a) {
bend_share(a[2]);
return mk_clo(L76, 4, 3, (V[]){a[0], a[2], a[1]});
}
static V F_IO_dbind(V a2, V a3) {
top:;
return mk_clo(L75, 3, 2, (V[]){a3, a2});
}
static V W_IO_dbind(V *a) { (void)a; return F_IO_dbind(a[2], a[3]); }
static V F_rounds(V a0, V a1_) {
uint32_t a1 = (uint32_t)a1_;
top:;
V s78 = (a0);
if ((s78) == 0) {
return (a1);
} else if (nat_ge(s78, 1)) {
{ V t0 = nat_subk(s78, 1); V t1 = F_U32_dadd((a1), F_sum(F_make_x37s3795296409x247312561(1u))); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("runtime fail-stop"); }
}
static V W_rounds(V *a) { (void)a; return F_rounds(a[0], a[1]); }
static V L88(V *a) {
return F_make_x37s675041226x247282770(F_U32_dinc(a[0]));
}
static V F_make_x37s3795296409x247312561(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p82_0; V p82_1; 
static int pcs87;
if (par_depth >= par_front || par_small(&pcs87)) {
p82_0 = F_make_x37s675041226x247282770(F_U32_dinc((a0)));
p82_1 = F_make_x37s675041226x247282770(F_U32_dadd((a0), 2u));
} else {
par_depth += 1;
V p87_0t = par_fork_at(&pcs87, mk_clo(L88, 2, 1, (V[]){(a0)}));
V p87_1 = F_make_x37s675041226x247282770(F_U32_dadd((a0), 2u));
V p87_0 = par_join(p87_0t);
p82_0 = p87_0; p82_1 = p87_1; 
par_depth -= 1;
}
return B2(p82_0, p82_1);
}
static V W_make_x37s3795296409x247312561(V *a) { (void)a; return F_make_x37s3795296409x247312561(a[0]); }
static V L99(V *a) {
return F_make_x37s2689494263x247252979(F_U32_dinc(a[0]));
}
static V F_make_x37s675041226x247282770(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p93_0; V p93_1; 
static int pcs98;
if (par_depth >= par_front || par_small(&pcs98)) {
p93_0 = F_make_x37s2689494263x247252979(F_U32_dinc((a0)));
p93_1 = F_make_x37s2689494263x247252979(F_U32_dadd((a0), 2u));
} else {
par_depth += 1;
V p98_0t = par_fork_at(&pcs98, mk_clo(L99, 2, 1, (V[]){(a0)}));
V p98_1 = F_make_x37s2689494263x247252979(F_U32_dadd((a0), 2u));
V p98_0 = par_join(p98_0t);
p93_0 = p98_0; p93_1 = p98_1; 
par_depth -= 1;
}
return B2(p93_0, p93_1);
}
static V W_make_x37s675041226x247282770(V *a) { (void)a; return F_make_x37s675041226x247282770(a[0]); }
static V L110(V *a) {
return F_make_x37s4233607528x247223188(F_U32_dinc(a[0]));
}
static V F_make_x37s2689494263x247252979(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p104_0; V p104_1; 
static int pcs109;
if (par_depth >= par_front || par_small(&pcs109)) {
p104_0 = F_make_x37s4233607528x247223188(F_U32_dinc((a0)));
p104_1 = F_make_x37s4233607528x247223188(F_U32_dadd((a0), 2u));
} else {
par_depth += 1;
V p109_0t = par_fork_at(&pcs109, mk_clo(L110, 2, 1, (V[]){(a0)}));
V p109_1 = F_make_x37s4233607528x247223188(F_U32_dadd((a0), 2u));
V p109_0 = par_join(p109_0t);
p104_0 = p109_0; p104_1 = p109_1; 
par_depth -= 1;
}
return B2(p104_0, p104_1);
}
static V W_make_x37s2689494263x247252979(V *a) { (void)a; return F_make_x37s2689494263x247252979(a[0]); }
static V L121(V *a) {
return F_make_x37s1953093269x247193397(F_U32_dinc(a[0]));
}
static V F_make_x37s4233607528x247223188(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p115_0; V p115_1; 
static int pcs120;
if (par_depth >= par_front || par_small(&pcs120)) {
p115_0 = F_make_x37s1953093269x247193397(F_U32_dinc((a0)));
p115_1 = F_make_x37s1953093269x247193397(F_U32_dadd((a0), 2u));
} else {
par_depth += 1;
V p120_0t = par_fork_at(&pcs120, mk_clo(L121, 2, 1, (V[]){(a0)}));
V p120_1 = F_make_x37s1953093269x247193397(F_U32_dadd((a0), 2u));
V p120_0 = par_join(p120_0t);
p115_0 = p120_0; p115_1 = p120_1; 
par_depth -= 1;
}
return B2(p115_0, p115_1);
}
static V W_make_x37s4233607528x247223188(V *a) { (void)a; return F_make_x37s4233607528x247223188(a[0]); }
static V L132(V *a) {
return F_make_x37s3305376709x8269577(F_U32_dinc(a[0]));
}
static V F_make_x37s1953093269x247193397(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p126_0; V p126_1; 
static int pcs131;
if (par_depth >= par_front || par_small(&pcs131)) {
p126_0 = F_make_x37s3305376709x8269577(F_U32_dinc((a0)));
p126_1 = F_make_x37s3305376709x8269577(F_U32_dadd((a0), 2u));
} else {
par_depth += 1;
V p131_0t = par_fork_at(&pcs131, mk_clo(L132, 2, 1, (V[]){(a0)}));
V p131_1 = F_make_x37s3305376709x8269577(F_U32_dadd((a0), 2u));
V p131_0 = par_join(p131_0t);
p126_0 = p131_0; p126_1 = p131_1; 
par_depth -= 1;
}
return B2(p126_0, p126_1);
}
static V W_make_x37s1953093269x247193397(V *a) { (void)a; return F_make_x37s1953093269x247193397(a[0]); }
static V L143(V *a) {
return F_make_x37s2491568216x8239786(F_U32_dinc(a[0]));
}
static V F_make_x37s3305376709x8269577(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p137_0; V p137_1; 
static int pcs142;
if (par_depth >= par_front || par_small(&pcs142)) {
p137_0 = F_make_x37s2491568216x8239786(F_U32_dinc((a0)));
p137_1 = F_make_x37s2491568216x8239786(F_U32_dadd((a0), 2u));
} else {
par_depth += 1;
V p142_0t = par_fork_at(&pcs142, mk_clo(L143, 2, 1, (V[]){(a0)}));
V p142_1 = F_make_x37s2491568216x8239786(F_U32_dadd((a0), 2u));
V p142_0 = par_join(p142_0t);
p137_0 = p142_0; p137_1 = p142_1; 
par_depth -= 1;
}
return B2(p137_0, p137_1);
}
static V W_make_x37s3305376709x8269577(V *a) { (void)a; return F_make_x37s3305376709x8269577(a[0]); }
static V L154(V *a) {
return F_make_x37s1291691603x8209995(F_U32_dinc(a[0]));
}
static V F_make_x37s2491568216x8239786(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p148_0; V p148_1; 
static int pcs153;
if (par_depth >= par_front || par_small(&pcs153)) {
p148_0 = F_make_x37s1291691603x8209995(F_U32_dinc((a0)));
p148_1 = F_make_x37s1291691603x8209995(F_U32_dadd((a0), 2u));
} else {
par_depth += 1;
V p153_0t = par_fork_at(&pcs153, mk_clo(L154, 2, 1, (V[]){(a0)}));
V p153_1 = F_make_x37s1291691603x8209995(F_U32_dadd((a0), 2u));
V p153_0 = par_join(p153_0t);
p148_0 = p153_0; p148_1 = p153_1; 
par_depth -= 1;
}
return B2(p148_0, p148_1);
}
static V W_make_x37s2491568216x8239786(V *a) { (void)a; return F_make_x37s2491568216x8239786(a[0]); }
static V L165(V *a) {
return F_make_x37s32637286x8180204(F_U32_dinc(a[0]));
}
static V F_make_x37s1291691603x8209995(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p159_0; V p159_1; 
static int pcs164;
if (par_depth >= par_front || par_small(&pcs164)) {
p159_0 = F_make_x37s32637286x8180204(F_U32_dinc((a0)));
p159_1 = F_make_x37s32637286x8180204(F_U32_dadd((a0), 2u));
} else {
par_depth += 1;
V p164_0t = par_fork_at(&pcs164, mk_clo(L165, 2, 1, (V[]){(a0)}));
V p164_1 = F_make_x37s32637286x8180204(F_U32_dadd((a0), 2u));
V p164_0 = par_join(p164_0t);
p159_0 = p164_0; p159_1 = p164_1; 
par_depth -= 1;
}
return B2(p159_0, p159_1);
}
static V W_make_x37s1291691603x8209995(V *a) { (void)a; return F_make_x37s1291691603x8209995(a[0]); }
static V L176(V *a) {
return F_make_x37s3239606481x8150413(F_U32_dinc(a[0]));
}
static V F_make_x37s32637286x8180204(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p170_0; V p170_1; 
static int pcs175;
if (par_depth >= par_front || par_small(&pcs175)) {
p170_0 = F_make_x37s3239606481x8150413(F_U32_dinc((a0)));
p170_1 = F_make_x37s3239606481x8150413(F_U32_dadd((a0), 2u));
} else {
par_depth += 1;
V p175_0t = par_fork_at(&pcs175, mk_clo(L176, 2, 1, (V[]){(a0)}));
V p175_1 = F_make_x37s3239606481x8150413(F_U32_dadd((a0), 2u));
V p175_0 = par_join(p175_0t);
p170_0 = p175_0; p170_1 = p175_1; 
par_depth -= 1;
}
return B2(p170_0, p170_1);
}
static V W_make_x37s32637286x8180204(V *a) { (void)a; return F_make_x37s32637286x8180204(a[0]); }
static V L187(V *a) {
return F_make_x37s2405009636x8120622(F_U32_dinc(a[0]));
}
static V F_make_x37s3239606481x8150413(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p181_0; V p181_1; 
static int pcs186;
if (par_depth >= par_front || par_small(&pcs186)) {
p181_0 = F_make_x37s2405009636x8120622(F_U32_dinc((a0)));
p181_1 = F_make_x37s2405009636x8120622(F_U32_dadd((a0), 2u));
} else {
par_depth += 1;
V p186_0t = par_fork_at(&pcs186, mk_clo(L187, 2, 1, (V[]){(a0)}));
V p186_1 = F_make_x37s2405009636x8120622(F_U32_dadd((a0), 2u));
V p186_0 = par_join(p186_0t);
p181_0 = p186_0; p181_1 = p186_1; 
par_depth -= 1;
}
return B2(p181_0, p181_1);
}
static V W_make_x37s3239606481x8150413(V *a) { (void)a; return F_make_x37s3239606481x8150413(a[0]); }
static V L198(V *a) {
return F_make_x37s1586577935x8090831(F_U32_dinc(a[0]));
}
static V F_make_x37s2405009636x8120622(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p192_0; V p192_1; 
static int pcs197;
if (par_depth >= par_front || par_small(&pcs197)) {
p192_0 = F_make_x37s1586577935x8090831(F_U32_dinc((a0)));
p192_1 = F_make_x37s1586577935x8090831(F_U32_dadd((a0), 2u));
} else {
par_depth += 1;
V p197_0t = par_fork_at(&pcs197, mk_clo(L198, 2, 1, (V[]){(a0)}));
V p197_1 = F_make_x37s1586577935x8090831(F_U32_dadd((a0), 2u));
V p197_0 = par_join(p197_0t);
p192_0 = p197_0; p192_1 = p197_1; 
par_depth -= 1;
}
return B2(p192_0, p192_1);
}
static V W_make_x37s2405009636x8120622(V *a) { (void)a; return F_make_x37s2405009636x8120622(a[0]); }
static V L209(V *a) {
return F_make_x37s3867092194x8061040(F_U32_dinc(a[0]));
}
static V F_make_x37s1586577935x8090831(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p203_0; V p203_1; 
static int pcs208;
if (par_depth >= par_front || par_small(&pcs208)) {
p203_0 = F_make_x37s3867092194x8061040(F_U32_dinc((a0)));
p203_1 = F_make_x37s3867092194x8061040(F_U32_dadd((a0), 2u));
} else {
par_depth += 1;
V p208_0t = par_fork_at(&pcs208, mk_clo(L209, 2, 1, (V[]){(a0)}));
V p208_1 = F_make_x37s3867092194x8061040(F_U32_dadd((a0), 2u));
V p208_0 = par_join(p208_0t);
p203_0 = p208_0; p203_1 = p208_1; 
par_depth -= 1;
}
return B2(p203_0, p203_1);
}
static V W_make_x37s1586577935x8090831(V *a) { (void)a; return F_make_x37s1586577935x8090831(a[0]); }
static V L220(V *a) {
return F_make_x37s1860454509x8031249(F_U32_dinc(a[0]));
}
static V F_make_x37s3867092194x8061040(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p214_0; V p214_1; 
static int pcs219;
if (par_depth >= par_front || par_small(&pcs219)) {
p214_0 = F_make_x37s1860454509x8031249(F_U32_dinc((a0)));
p214_1 = F_make_x37s1860454509x8031249(F_U32_dadd((a0), 2u));
} else {
par_depth += 1;
V p219_0t = par_fork_at(&pcs219, mk_clo(L220, 2, 1, (V[]){(a0)}));
V p219_1 = F_make_x37s1860454509x8031249(F_U32_dadd((a0), 2u));
V p219_0 = par_join(p219_0t);
p214_0 = p219_0; p214_1 = p219_1; 
par_depth -= 1;
}
return B2(p214_0, p214_1);
}
static V W_make_x37s3867092194x8061040(V *a) { (void)a; return F_make_x37s3867092194x8061040(a[0]); }
static V L231(V *a) {
return F_make_x37s509762208x8001458(F_U32_dinc(a[0]));
}
static V F_make_x37s1860454509x8031249(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p225_0; V p225_1; 
static int pcs230;
if (par_depth >= par_front || par_small(&pcs230)) {
#define F_make_x37s1860454509x8031249 S_make_x37s1860454509x8031249
p225_0 = F_make_x37s509762208x8001458(F_U32_dinc((a0)));
p225_1 = F_make_x37s509762208x8001458(F_U32_dadd((a0), 2u));
#undef F_make_x37s1860454509x8031249
} else {
par_depth += 1;
V p230_0t = par_fork_at(&pcs230, mk_clo(L231, 2, 1, (V[]){(a0)}));
V p230_1 = F_make_x37s509762208x8001458(F_U32_dadd((a0), 2u));
V p230_0 = par_join(p230_0t);
p225_0 = p230_0; p225_1 = p230_1; 
par_depth -= 1;
}
return B2(p225_0, p225_1);
}
static V W_make_x37s1860454509x8031249(V *a) { (void)a; return F_make_x37s1860454509x8031249(a[0]); }
#define F_make_x37s1860454509x8031249 S_make_x37s1860454509x8031249
static V S_make_x37s1860454509x8031249(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
V p236_0 = F_make_x37s509762208x8001458(F_U32_dinc((a0)));
V p236_1 = F_make_x37s509762208x8001458(F_U32_dadd((a0), 2u));
return B2(p236_0, p236_1);
}
#undef F_make_x37s1860454509x8031249
BEND_UINL V F_make_x37s509762208x8001458(V a0_) {
uint32_t a0 = (uint32_t)a0_;
top:;
return LI(0, (a0));
}
static V W_make_x37s509762208x8001458(V *a) { (void)a; return F_make_x37s509762208x8001458(a[0]); }
static V W_U32_dinc(V *a) { (void)a; return F_U32_dinc(a[0]); }
static V L248(V *a) {
return F_make(a[1], F_U32_dinc(a[0]));
}
static V F_make(V a0, V a1_) {
uint32_t a1 = (uint32_t)a1_;
top:;
V s241 = (a0);
if ((s241) == 0) {
return LI(0, (a1));
} else if (nat_ge(s241, 1)) {
V p242_0; V p242_1; 
static int pcs247;
if (par_depth >= par_front || par_small(&pcs247)) {
#define F_make S_make
p242_0 = F_make(nat_subk(s241, 1), F_U32_dinc((a1)));
p242_1 = F_make(nat_subk(s241, 1), F_U32_dadd((a1), 2u));
#undef F_make
} else {
par_depth += 1;
V p247_0t = par_fork_at(&pcs247, mk_clo(L248, 3, 2, (V[]){(a1), nat_subk(s241, 1)}));
V p247_1 = F_make(nat_subk(s241, 1), F_U32_dadd((a1), 2u));
V p247_0 = par_join(p247_0t);
p242_0 = p247_0; p242_1 = p247_1; 
par_depth -= 1;
}
return B2(p242_0, p242_1);
} else { bend_fail("runtime fail-stop"); }
}
static V W_make(V *a) { (void)a; return F_make(a[0], a[1]); }
#define F_make S_make
static V S_make(V a0, V a1_) {
uint32_t a1 = (uint32_t)a1_;
top:;
V s253 = (a0);
if ((s253) == 0) {
return LI(0, (a1));
} else if (nat_ge(s253, 1)) {
V p254_0 = F_make(nat_subk(s253, 1), F_U32_dinc((a1)));
V p254_1 = F_make(nat_subk(s253, 1), F_U32_dadd((a1), 2u));
return B2(p254_0, p254_1);
} else { bend_fail("runtime fail-stop"); }
}
#undef F_make
BEND_NSP_END

// The device code of the !-calls: rt/gpu.h, then this program's part
#include "gpu.h"

#define K_NLABELS 1324
#define KL_make_x37s1860454509x8031249 1286
#define KL_make_x37s3867092194x8061040 1247
#define KL_make_x37s1586577935x8090831 1199
#define KL_make_x37s2405009636x8120622 1142
#define KL_make_x37s3239606481x8150413 1076
#define KL_make_x37s32637286x8180204 1001
#define KL_make_x37s1291691603x8209995 917
#define KL_make_x37s2491568216x8239786 824
#define KL_make_x37s3305376709x8269577 722
#define KL_make_x37s1953093269x247193397 611
#define KL_make_x37s4233607528x247223188 491
#define KL_make_x37s2689494263x247252979 362
#define KL_make_x37s675041226x247282770 224
#define KL_make_x37s3795296409x247312561 48
#define KLW_make 13
#define KL_make 12
#define KLW_rounds 11
#define KL_rounds 10
#define KLW_sum 9
#define KL_sum 8
KCONST KW K_FRAME[] = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 18u, 6u, 15u, 7u, 26u, 7u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 11u, 0u, 12u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 8u, 0u, 8u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 8u, 9u, 0u, 0u, 0u, 0u, 0u, 0u, 0};

KINLINE KW k_frame_size(KW l) {
  return l < K_NLABELS ? K_FRAME[l] : 0;
}

KCONST KW K_TREE_EMPTY[] = {0};
KCONST KW K_TREE_53[] = {0};
KCONST KW K_TREE_34[] = {2, 0, 2147483651};
KINLINE KCP KW *k_tree_schema(KW id) {
switch(id) {
case 53: return K_TREE_53;
case 34: return K_TREE_34;
default: return K_TREE_EMPTY;
}
}

KINLINE KW KQ_make(KTHR KCtx *c, KW p0, KW p1, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 32, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = p1;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 40: {
sp -= 1; KW x41_0 = KQ_ST(sp + 0); KW x41 = RV;
RV = ({ KAUTO x42_0 = x41_0; KAUTO x42_1 = x41; KW x42 = k_bnode(c, 2); c->H[KIX(c, x42) + 0] = x42_0; c->H[KIX(c, x42) + 1] = x42_1; x42; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 37: {
sp -= 2; KW x38_0 = KQ_ST(sp + 0); KW x38_1 = KQ_ST(sp + 1); KW x38 = RV;
{ KAUTO x39_0 = x38_0; KAUTO x39_1 = KF_U32_dadd(c, x38_1, 2u); if (sp + 2 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x38; KQ_ST(sp + 1) = 40; sp += 2;
A0 = x39_0; A1 = x39_1; pc = 32; break; }
break;
}
case 32: {
KW x33_0 = A0; KW x33_1 = A1; 
K_TREE_MARK(34);
KAUTO x35 = x33_0;
if ((x35) == 0) {
RV = KLI(0, x33_1);
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
} else if (k_nge(c, x35, 1)) {
{ KAUTO x36_0 = ((x35) - 1); KAUTO x36_1 = KF_U32_dinc(c, x33_1); if (sp + 3 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = ((x35) - 1); KQ_ST(sp + 1) = x33_1; KQ_ST(sp + 2) = 37; sp += 3;
A0 = x36_0; A1 = x36_1; pc = 32; break; }
} else { k_fail(c, KE_MATCH); *ok = false; return 0; }
break;
}
default:
*ok = false;
return 0;
}
}
}
KINLINE KW KX_make_x37s509762208x8001458(KTHR KCtx *c, KU a0) {
for (;;) {
return KLI(0, a0);
}
}

KINLINE KW KQ_rounds(KTHR KCtx *c, KW p0, KW p1, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 51, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = p1;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 81: {
KW x82_0 = A0; 
K_TREE_MARK(34);
KW x83 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x82_0))));
KW x84 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x82_0, 2u))));
RV = ({ KAUTO x85_0 = x83; KAUTO x85_1 = x84; KW x85 = k_bnode(c, 2); c->H[KIX(c, x85) + 0] = x85_0; c->H[KIX(c, x85) + 1] = x85_1; x85; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 90: {
sp -= 3; KW x91_0 = KQ_ST(sp + 0); KW x91 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x92_0 = x91_0; KAUTO x92_1 = x91; KW x92 = k_bnode(c, 2); c->H[KIX(c, x92) + 0] = x92_0; c->H[KIX(c, x92) + 1] = x92_1; x92; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 87: {
sp -= 3; KW x88_0 = KQ_ST(sp + 0); KW x88 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x89_0 = KF_U32_dadd(c, x88_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x88; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 90; sp += 4;
A0 = x89_0; pc = 81; break; }
break;
}
case 79: {
KW x80_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x86_0 = KF_U32_dinc(c, x80_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x80_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 87; sp += 4;
A0 = x86_0; pc = 81; break; }
break;
}
case 97: {
sp -= 3; KW x98_0 = KQ_ST(sp + 0); KW x98 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x99_0 = x98_0; KAUTO x99_1 = x98; KW x99 = k_bnode(c, 2); c->H[KIX(c, x99) + 0] = x99_0; c->H[KIX(c, x99) + 1] = x99_1; x99; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 94: {
sp -= 3; KW x95_0 = KQ_ST(sp + 0); KW x95 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x96_0 = KF_U32_dadd(c, x95_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x95; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 97; sp += 4;
A0 = x96_0; pc = 79; break; }
break;
}
case 77: {
KW x78_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x93_0 = KF_U32_dinc(c, x78_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x78_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 94; sp += 4;
A0 = x93_0; pc = 79; break; }
break;
}
case 104: {
sp -= 3; KW x105_0 = KQ_ST(sp + 0); KW x105 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x106_0 = x105_0; KAUTO x106_1 = x105; KW x106 = k_bnode(c, 2); c->H[KIX(c, x106) + 0] = x106_0; c->H[KIX(c, x106) + 1] = x106_1; x106; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 101: {
sp -= 3; KW x102_0 = KQ_ST(sp + 0); KW x102 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x103_0 = KF_U32_dadd(c, x102_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x102; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 104; sp += 4;
A0 = x103_0; pc = 77; break; }
break;
}
case 75: {
KW x76_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x100_0 = KF_U32_dinc(c, x76_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x76_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 101; sp += 4;
A0 = x100_0; pc = 77; break; }
break;
}
case 111: {
sp -= 3; KW x112_0 = KQ_ST(sp + 0); KW x112 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x113_0 = x112_0; KAUTO x113_1 = x112; KW x113 = k_bnode(c, 2); c->H[KIX(c, x113) + 0] = x113_0; c->H[KIX(c, x113) + 1] = x113_1; x113; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 108: {
sp -= 3; KW x109_0 = KQ_ST(sp + 0); KW x109 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x110_0 = KF_U32_dadd(c, x109_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x109; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 111; sp += 4;
A0 = x110_0; pc = 75; break; }
break;
}
case 73: {
KW x74_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x107_0 = KF_U32_dinc(c, x74_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x74_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 108; sp += 4;
A0 = x107_0; pc = 75; break; }
break;
}
case 118: {
sp -= 3; KW x119_0 = KQ_ST(sp + 0); KW x119 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x120_0 = x119_0; KAUTO x120_1 = x119; KW x120 = k_bnode(c, 2); c->H[KIX(c, x120) + 0] = x120_0; c->H[KIX(c, x120) + 1] = x120_1; x120; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 115: {
sp -= 3; KW x116_0 = KQ_ST(sp + 0); KW x116 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x117_0 = KF_U32_dadd(c, x116_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x116; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 118; sp += 4;
A0 = x117_0; pc = 73; break; }
break;
}
case 71: {
KW x72_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x114_0 = KF_U32_dinc(c, x72_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x72_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 115; sp += 4;
A0 = x114_0; pc = 73; break; }
break;
}
case 125: {
sp -= 3; KW x126_0 = KQ_ST(sp + 0); KW x126 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x127_0 = x126_0; KAUTO x127_1 = x126; KW x127 = k_bnode(c, 2); c->H[KIX(c, x127) + 0] = x127_0; c->H[KIX(c, x127) + 1] = x127_1; x127; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 122: {
sp -= 3; KW x123_0 = KQ_ST(sp + 0); KW x123 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x124_0 = KF_U32_dadd(c, x123_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x123; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 125; sp += 4;
A0 = x124_0; pc = 71; break; }
break;
}
case 69: {
KW x70_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x121_0 = KF_U32_dinc(c, x70_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x70_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 122; sp += 4;
A0 = x121_0; pc = 71; break; }
break;
}
case 132: {
sp -= 3; KW x133_0 = KQ_ST(sp + 0); KW x133 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x134_0 = x133_0; KAUTO x134_1 = x133; KW x134 = k_bnode(c, 2); c->H[KIX(c, x134) + 0] = x134_0; c->H[KIX(c, x134) + 1] = x134_1; x134; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 129: {
sp -= 3; KW x130_0 = KQ_ST(sp + 0); KW x130 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x131_0 = KF_U32_dadd(c, x130_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x130; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 132; sp += 4;
A0 = x131_0; pc = 69; break; }
break;
}
case 67: {
KW x68_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x128_0 = KF_U32_dinc(c, x68_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x68_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 129; sp += 4;
A0 = x128_0; pc = 69; break; }
break;
}
case 139: {
sp -= 3; KW x140_0 = KQ_ST(sp + 0); KW x140 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x141_0 = x140_0; KAUTO x141_1 = x140; KW x141 = k_bnode(c, 2); c->H[KIX(c, x141) + 0] = x141_0; c->H[KIX(c, x141) + 1] = x141_1; x141; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 136: {
sp -= 3; KW x137_0 = KQ_ST(sp + 0); KW x137 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x138_0 = KF_U32_dadd(c, x137_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x137; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 139; sp += 4;
A0 = x138_0; pc = 67; break; }
break;
}
case 65: {
KW x66_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x135_0 = KF_U32_dinc(c, x66_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x66_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 136; sp += 4;
A0 = x135_0; pc = 67; break; }
break;
}
case 146: {
sp -= 3; KW x147_0 = KQ_ST(sp + 0); KW x147 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x148_0 = x147_0; KAUTO x148_1 = x147; KW x148 = k_bnode(c, 2); c->H[KIX(c, x148) + 0] = x148_0; c->H[KIX(c, x148) + 1] = x148_1; x148; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 143: {
sp -= 3; KW x144_0 = KQ_ST(sp + 0); KW x144 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x145_0 = KF_U32_dadd(c, x144_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x144; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 146; sp += 4;
A0 = x145_0; pc = 65; break; }
break;
}
case 63: {
KW x64_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x142_0 = KF_U32_dinc(c, x64_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x64_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 143; sp += 4;
A0 = x142_0; pc = 65; break; }
break;
}
case 153: {
sp -= 3; KW x154_0 = KQ_ST(sp + 0); KW x154 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x155_0 = x154_0; KAUTO x155_1 = x154; KW x155 = k_bnode(c, 2); c->H[KIX(c, x155) + 0] = x155_0; c->H[KIX(c, x155) + 1] = x155_1; x155; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 150: {
sp -= 3; KW x151_0 = KQ_ST(sp + 0); KW x151 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x152_0 = KF_U32_dadd(c, x151_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x151; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 153; sp += 4;
A0 = x152_0; pc = 63; break; }
break;
}
case 61: {
KW x62_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x149_0 = KF_U32_dinc(c, x62_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x62_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 150; sp += 4;
A0 = x149_0; pc = 63; break; }
break;
}
case 160: {
sp -= 3; KW x161_0 = KQ_ST(sp + 0); KW x161 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x162_0 = x161_0; KAUTO x162_1 = x161; KW x162 = k_bnode(c, 2); c->H[KIX(c, x162) + 0] = x162_0; c->H[KIX(c, x162) + 1] = x162_1; x162; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 157: {
sp -= 3; KW x158_0 = KQ_ST(sp + 0); KW x158 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x159_0 = KF_U32_dadd(c, x158_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x158; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 160; sp += 4;
A0 = x159_0; pc = 61; break; }
break;
}
case 59: {
KW x60_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x156_0 = KF_U32_dinc(c, x60_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x60_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 157; sp += 4;
A0 = x156_0; pc = 61; break; }
break;
}
case 167: {
sp -= 3; KW x168_0 = KQ_ST(sp + 0); KW x168 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x169_0 = x168_0; KAUTO x169_1 = x168; KW x169 = k_bnode(c, 2); c->H[KIX(c, x169) + 0] = x169_0; c->H[KIX(c, x169) + 1] = x169_1; x169; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 164: {
sp -= 3; KW x165_0 = KQ_ST(sp + 0); KW x165 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x166_0 = KF_U32_dadd(c, x165_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x165; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 167; sp += 4;
A0 = x166_0; pc = 59; break; }
break;
}
case 57: {
KW x58_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x163_0 = KF_U32_dinc(c, x58_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x58_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 164; sp += 4;
A0 = x163_0; pc = 59; break; }
break;
}
case 174: {
sp -= 3; KW x175_0 = KQ_ST(sp + 0); KW x175 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x176_0 = x175_0; KAUTO x176_1 = x175; KW x176 = k_bnode(c, 2); c->H[KIX(c, x176) + 0] = x176_0; c->H[KIX(c, x176) + 1] = x176_1; x176; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 171: {
sp -= 3; KW x172_0 = KQ_ST(sp + 0); KW x172 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x173_0 = KF_U32_dadd(c, x172_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x172; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 174; sp += 4;
A0 = x173_0; pc = 57; break; }
break;
}
case 55: {
KW x56_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x170_0 = KF_U32_dinc(c, x56_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x56_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 171; sp += 4;
A0 = x170_0; pc = 57; break; }
break;
}
case 187: {
sp -= 1; KW x188_0 = KQ_ST(sp + 0); KW x188 = RV;
RV = KF_U32_dadd(c, x188_0, x188);
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 184: {
sp -= 1; KW x185_0 = KQ_ST(sp + 0); KW x185 = RV;
{ KAUTO x186_0 = x185_0; if (sp + 2 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x185; KQ_ST(sp + 1) = 187; sp += 2;
A0 = x186_0; pc = 180; break; }
break;
}
case 180: {
KW x181_0 = A0; 
KAUTO x182 = x181_0;
if (KIS_LI(x182, 0)) {
RV = KLI_V(x182);
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
} else if (!((x182) & 1)) {
{ KAUTO x183_0 = KFLB(x182, 0); if (sp + 2 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = KFLB(x182, 1); KQ_ST(sp + 1) = 184; sp += 2;
A0 = x183_0; pc = 180; break; }
} else { k_fail(c, KE_MATCH); *ok = false; return 0; }
break;
}
case 190: {
sp -= 2; KW x191_0 = KQ_ST(sp + 0); KW x191_1 = KQ_ST(sp + 1); KW x191 = RV;
{ KAUTO x192_0 = x191_0; KAUTO x192_1 = KF_U32_dadd(c, x191_1, x191); A0 = x192_0; A1 = x192_1; if (c->err) { *ok = false; return 0; }
pc = 51; break; }
break;
}
case 178: {
sp -= 4; KW x179_0 = KQ_ST(sp + 0); KW x179_1 = KQ_ST(sp + 1); KW x179 = k_region(c, KQ_ST(sp + 2), KQ_ST(sp + 3), RV);
{ KAUTO x189_0 = x179; if (sp + 3 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x179_0; KQ_ST(sp + 1) = x179_1; KQ_ST(sp + 2) = 190; sp += 3;
A0 = x189_0; pc = 180; break; }
break;
}
case 51: {
KW x52_0 = A0; KW x52_1 = A1; 
K_TREE_MARK(53);
KAUTO x54 = x52_0;
if ((x54) == 0) {
RV = x52_1;
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
} else if (k_nge(c, x54, 1)) {
{ KAUTO x177_0 = 1u; if (sp + 5 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = ((x54) - 1); KQ_ST(sp + 1) = x52_1; KQ_ST(sp + 2) = c->hp; KQ_ST(sp + 3) = c->he; KQ_ST(sp + 4) = 178; sp += 5;
A0 = x177_0; pc = 55; break; }
} else { k_fail(c, KE_MATCH); *ok = false; return 0; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_sum(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 211, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 218: {
sp -= 1; KW x219_0 = KQ_ST(sp + 0); KW x219 = RV;
RV = KF_U32_dadd(c, x219_0, x219);
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 215: {
sp -= 1; KW x216_0 = KQ_ST(sp + 0); KW x216 = RV;
{ KAUTO x217_0 = x216_0; if (sp + 2 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x216; KQ_ST(sp + 1) = 218; sp += 2;
A0 = x217_0; pc = 211; break; }
break;
}
case 211: {
KW x212_0 = A0; 
KAUTO x213 = x212_0;
if (KIS_LI(x213, 0)) {
RV = KLI_V(x213);
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
} else if (!((x213) & 1)) {
{ KAUTO x214_0 = KFLB(x213, 0); if (sp + 2 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = KFLB(x213, 1); KQ_ST(sp + 1) = 215; sp += 2;
A0 = x214_0; pc = 211; break; }
} else { k_fail(c, KE_MATCH); *ok = false; return 0; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_make_x37s3795296409x247312561(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 236, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 262: {
KW x263_0 = A0; 
K_TREE_MARK(34);
KW x264 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x263_0))));
KW x265 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x263_0, 2u))));
RV = ({ KAUTO x266_0 = x264; KAUTO x266_1 = x265; KW x266 = k_bnode(c, 2); c->H[KIX(c, x266) + 0] = x266_0; c->H[KIX(c, x266) + 1] = x266_1; x266; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 271: {
sp -= 3; KW x272_0 = KQ_ST(sp + 0); KW x272 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x273_0 = x272_0; KAUTO x273_1 = x272; KW x273 = k_bnode(c, 2); c->H[KIX(c, x273) + 0] = x273_0; c->H[KIX(c, x273) + 1] = x273_1; x273; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 268: {
sp -= 3; KW x269_0 = KQ_ST(sp + 0); KW x269 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x270_0 = KF_U32_dadd(c, x269_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x269; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 271; sp += 4;
A0 = x270_0; pc = 262; break; }
break;
}
case 260: {
KW x261_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x267_0 = KF_U32_dinc(c, x261_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x261_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 268; sp += 4;
A0 = x267_0; pc = 262; break; }
break;
}
case 278: {
sp -= 3; KW x279_0 = KQ_ST(sp + 0); KW x279 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x280_0 = x279_0; KAUTO x280_1 = x279; KW x280 = k_bnode(c, 2); c->H[KIX(c, x280) + 0] = x280_0; c->H[KIX(c, x280) + 1] = x280_1; x280; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 275: {
sp -= 3; KW x276_0 = KQ_ST(sp + 0); KW x276 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x277_0 = KF_U32_dadd(c, x276_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x276; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 278; sp += 4;
A0 = x277_0; pc = 260; break; }
break;
}
case 258: {
KW x259_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x274_0 = KF_U32_dinc(c, x259_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x259_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 275; sp += 4;
A0 = x274_0; pc = 260; break; }
break;
}
case 285: {
sp -= 3; KW x286_0 = KQ_ST(sp + 0); KW x286 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x287_0 = x286_0; KAUTO x287_1 = x286; KW x287 = k_bnode(c, 2); c->H[KIX(c, x287) + 0] = x287_0; c->H[KIX(c, x287) + 1] = x287_1; x287; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 282: {
sp -= 3; KW x283_0 = KQ_ST(sp + 0); KW x283 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x284_0 = KF_U32_dadd(c, x283_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x283; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 285; sp += 4;
A0 = x284_0; pc = 258; break; }
break;
}
case 256: {
KW x257_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x281_0 = KF_U32_dinc(c, x257_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x257_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 282; sp += 4;
A0 = x281_0; pc = 258; break; }
break;
}
case 292: {
sp -= 3; KW x293_0 = KQ_ST(sp + 0); KW x293 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x294_0 = x293_0; KAUTO x294_1 = x293; KW x294 = k_bnode(c, 2); c->H[KIX(c, x294) + 0] = x294_0; c->H[KIX(c, x294) + 1] = x294_1; x294; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 289: {
sp -= 3; KW x290_0 = KQ_ST(sp + 0); KW x290 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x291_0 = KF_U32_dadd(c, x290_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x290; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 292; sp += 4;
A0 = x291_0; pc = 256; break; }
break;
}
case 254: {
KW x255_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x288_0 = KF_U32_dinc(c, x255_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x255_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 289; sp += 4;
A0 = x288_0; pc = 256; break; }
break;
}
case 299: {
sp -= 3; KW x300_0 = KQ_ST(sp + 0); KW x300 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x301_0 = x300_0; KAUTO x301_1 = x300; KW x301 = k_bnode(c, 2); c->H[KIX(c, x301) + 0] = x301_0; c->H[KIX(c, x301) + 1] = x301_1; x301; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 296: {
sp -= 3; KW x297_0 = KQ_ST(sp + 0); KW x297 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x298_0 = KF_U32_dadd(c, x297_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x297; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 299; sp += 4;
A0 = x298_0; pc = 254; break; }
break;
}
case 252: {
KW x253_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x295_0 = KF_U32_dinc(c, x253_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x253_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 296; sp += 4;
A0 = x295_0; pc = 254; break; }
break;
}
case 306: {
sp -= 3; KW x307_0 = KQ_ST(sp + 0); KW x307 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x308_0 = x307_0; KAUTO x308_1 = x307; KW x308 = k_bnode(c, 2); c->H[KIX(c, x308) + 0] = x308_0; c->H[KIX(c, x308) + 1] = x308_1; x308; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 303: {
sp -= 3; KW x304_0 = KQ_ST(sp + 0); KW x304 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x305_0 = KF_U32_dadd(c, x304_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x304; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 306; sp += 4;
A0 = x305_0; pc = 252; break; }
break;
}
case 250: {
KW x251_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x302_0 = KF_U32_dinc(c, x251_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x251_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 303; sp += 4;
A0 = x302_0; pc = 252; break; }
break;
}
case 313: {
sp -= 3; KW x314_0 = KQ_ST(sp + 0); KW x314 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x315_0 = x314_0; KAUTO x315_1 = x314; KW x315 = k_bnode(c, 2); c->H[KIX(c, x315) + 0] = x315_0; c->H[KIX(c, x315) + 1] = x315_1; x315; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 310: {
sp -= 3; KW x311_0 = KQ_ST(sp + 0); KW x311 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x312_0 = KF_U32_dadd(c, x311_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x311; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 313; sp += 4;
A0 = x312_0; pc = 250; break; }
break;
}
case 248: {
KW x249_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x309_0 = KF_U32_dinc(c, x249_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x249_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 310; sp += 4;
A0 = x309_0; pc = 250; break; }
break;
}
case 320: {
sp -= 3; KW x321_0 = KQ_ST(sp + 0); KW x321 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x322_0 = x321_0; KAUTO x322_1 = x321; KW x322 = k_bnode(c, 2); c->H[KIX(c, x322) + 0] = x322_0; c->H[KIX(c, x322) + 1] = x322_1; x322; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 317: {
sp -= 3; KW x318_0 = KQ_ST(sp + 0); KW x318 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x319_0 = KF_U32_dadd(c, x318_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x318; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 320; sp += 4;
A0 = x319_0; pc = 248; break; }
break;
}
case 246: {
KW x247_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x316_0 = KF_U32_dinc(c, x247_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x247_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 317; sp += 4;
A0 = x316_0; pc = 248; break; }
break;
}
case 327: {
sp -= 3; KW x328_0 = KQ_ST(sp + 0); KW x328 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x329_0 = x328_0; KAUTO x329_1 = x328; KW x329 = k_bnode(c, 2); c->H[KIX(c, x329) + 0] = x329_0; c->H[KIX(c, x329) + 1] = x329_1; x329; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 324: {
sp -= 3; KW x325_0 = KQ_ST(sp + 0); KW x325 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x326_0 = KF_U32_dadd(c, x325_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x325; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 327; sp += 4;
A0 = x326_0; pc = 246; break; }
break;
}
case 244: {
KW x245_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x323_0 = KF_U32_dinc(c, x245_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x245_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 324; sp += 4;
A0 = x323_0; pc = 246; break; }
break;
}
case 334: {
sp -= 3; KW x335_0 = KQ_ST(sp + 0); KW x335 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x336_0 = x335_0; KAUTO x336_1 = x335; KW x336 = k_bnode(c, 2); c->H[KIX(c, x336) + 0] = x336_0; c->H[KIX(c, x336) + 1] = x336_1; x336; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 331: {
sp -= 3; KW x332_0 = KQ_ST(sp + 0); KW x332 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x333_0 = KF_U32_dadd(c, x332_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x332; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 334; sp += 4;
A0 = x333_0; pc = 244; break; }
break;
}
case 242: {
KW x243_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x330_0 = KF_U32_dinc(c, x243_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x243_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 331; sp += 4;
A0 = x330_0; pc = 244; break; }
break;
}
case 341: {
sp -= 3; KW x342_0 = KQ_ST(sp + 0); KW x342 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x343_0 = x342_0; KAUTO x343_1 = x342; KW x343 = k_bnode(c, 2); c->H[KIX(c, x343) + 0] = x343_0; c->H[KIX(c, x343) + 1] = x343_1; x343; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 338: {
sp -= 3; KW x339_0 = KQ_ST(sp + 0); KW x339 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x340_0 = KF_U32_dadd(c, x339_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x339; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 341; sp += 4;
A0 = x340_0; pc = 242; break; }
break;
}
case 240: {
KW x241_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x337_0 = KF_U32_dinc(c, x241_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x241_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 338; sp += 4;
A0 = x337_0; pc = 242; break; }
break;
}
case 348: {
sp -= 3; KW x349_0 = KQ_ST(sp + 0); KW x349 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x350_0 = x349_0; KAUTO x350_1 = x349; KW x350 = k_bnode(c, 2); c->H[KIX(c, x350) + 0] = x350_0; c->H[KIX(c, x350) + 1] = x350_1; x350; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 345: {
sp -= 3; KW x346_0 = KQ_ST(sp + 0); KW x346 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x347_0 = KF_U32_dadd(c, x346_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x346; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 348; sp += 4;
A0 = x347_0; pc = 240; break; }
break;
}
case 238: {
KW x239_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x344_0 = KF_U32_dinc(c, x239_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x239_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 345; sp += 4;
A0 = x344_0; pc = 240; break; }
break;
}
case 355: {
sp -= 3; KW x356_0 = KQ_ST(sp + 0); KW x356 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x357_0 = x356_0; KAUTO x357_1 = x356; KW x357 = k_bnode(c, 2); c->H[KIX(c, x357) + 0] = x357_0; c->H[KIX(c, x357) + 1] = x357_1; x357; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 352: {
sp -= 3; KW x353_0 = KQ_ST(sp + 0); KW x353 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x354_0 = KF_U32_dadd(c, x353_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x353; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 355; sp += 4;
A0 = x354_0; pc = 238; break; }
break;
}
case 236: {
KW x237_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x351_0 = KF_U32_dinc(c, x237_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x237_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 352; sp += 4;
A0 = x351_0; pc = 238; break; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_make_x37s675041226x247282770(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 374, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 398: {
KW x399_0 = A0; 
K_TREE_MARK(34);
KW x400 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x399_0))));
KW x401 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x399_0, 2u))));
RV = ({ KAUTO x402_0 = x400; KAUTO x402_1 = x401; KW x402 = k_bnode(c, 2); c->H[KIX(c, x402) + 0] = x402_0; c->H[KIX(c, x402) + 1] = x402_1; x402; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 407: {
sp -= 3; KW x408_0 = KQ_ST(sp + 0); KW x408 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x409_0 = x408_0; KAUTO x409_1 = x408; KW x409 = k_bnode(c, 2); c->H[KIX(c, x409) + 0] = x409_0; c->H[KIX(c, x409) + 1] = x409_1; x409; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 404: {
sp -= 3; KW x405_0 = KQ_ST(sp + 0); KW x405 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x406_0 = KF_U32_dadd(c, x405_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x405; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 407; sp += 4;
A0 = x406_0; pc = 398; break; }
break;
}
case 396: {
KW x397_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x403_0 = KF_U32_dinc(c, x397_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x397_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 404; sp += 4;
A0 = x403_0; pc = 398; break; }
break;
}
case 414: {
sp -= 3; KW x415_0 = KQ_ST(sp + 0); KW x415 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x416_0 = x415_0; KAUTO x416_1 = x415; KW x416 = k_bnode(c, 2); c->H[KIX(c, x416) + 0] = x416_0; c->H[KIX(c, x416) + 1] = x416_1; x416; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 411: {
sp -= 3; KW x412_0 = KQ_ST(sp + 0); KW x412 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x413_0 = KF_U32_dadd(c, x412_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x412; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 414; sp += 4;
A0 = x413_0; pc = 396; break; }
break;
}
case 394: {
KW x395_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x410_0 = KF_U32_dinc(c, x395_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x395_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 411; sp += 4;
A0 = x410_0; pc = 396; break; }
break;
}
case 421: {
sp -= 3; KW x422_0 = KQ_ST(sp + 0); KW x422 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x423_0 = x422_0; KAUTO x423_1 = x422; KW x423 = k_bnode(c, 2); c->H[KIX(c, x423) + 0] = x423_0; c->H[KIX(c, x423) + 1] = x423_1; x423; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 418: {
sp -= 3; KW x419_0 = KQ_ST(sp + 0); KW x419 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x420_0 = KF_U32_dadd(c, x419_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x419; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 421; sp += 4;
A0 = x420_0; pc = 394; break; }
break;
}
case 392: {
KW x393_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x417_0 = KF_U32_dinc(c, x393_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x393_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 418; sp += 4;
A0 = x417_0; pc = 394; break; }
break;
}
case 428: {
sp -= 3; KW x429_0 = KQ_ST(sp + 0); KW x429 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x430_0 = x429_0; KAUTO x430_1 = x429; KW x430 = k_bnode(c, 2); c->H[KIX(c, x430) + 0] = x430_0; c->H[KIX(c, x430) + 1] = x430_1; x430; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 425: {
sp -= 3; KW x426_0 = KQ_ST(sp + 0); KW x426 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x427_0 = KF_U32_dadd(c, x426_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x426; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 428; sp += 4;
A0 = x427_0; pc = 392; break; }
break;
}
case 390: {
KW x391_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x424_0 = KF_U32_dinc(c, x391_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x391_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 425; sp += 4;
A0 = x424_0; pc = 392; break; }
break;
}
case 435: {
sp -= 3; KW x436_0 = KQ_ST(sp + 0); KW x436 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x437_0 = x436_0; KAUTO x437_1 = x436; KW x437 = k_bnode(c, 2); c->H[KIX(c, x437) + 0] = x437_0; c->H[KIX(c, x437) + 1] = x437_1; x437; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 432: {
sp -= 3; KW x433_0 = KQ_ST(sp + 0); KW x433 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x434_0 = KF_U32_dadd(c, x433_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x433; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 435; sp += 4;
A0 = x434_0; pc = 390; break; }
break;
}
case 388: {
KW x389_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x431_0 = KF_U32_dinc(c, x389_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x389_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 432; sp += 4;
A0 = x431_0; pc = 390; break; }
break;
}
case 442: {
sp -= 3; KW x443_0 = KQ_ST(sp + 0); KW x443 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x444_0 = x443_0; KAUTO x444_1 = x443; KW x444 = k_bnode(c, 2); c->H[KIX(c, x444) + 0] = x444_0; c->H[KIX(c, x444) + 1] = x444_1; x444; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 439: {
sp -= 3; KW x440_0 = KQ_ST(sp + 0); KW x440 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x441_0 = KF_U32_dadd(c, x440_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x440; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 442; sp += 4;
A0 = x441_0; pc = 388; break; }
break;
}
case 386: {
KW x387_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x438_0 = KF_U32_dinc(c, x387_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x387_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 439; sp += 4;
A0 = x438_0; pc = 388; break; }
break;
}
case 449: {
sp -= 3; KW x450_0 = KQ_ST(sp + 0); KW x450 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x451_0 = x450_0; KAUTO x451_1 = x450; KW x451 = k_bnode(c, 2); c->H[KIX(c, x451) + 0] = x451_0; c->H[KIX(c, x451) + 1] = x451_1; x451; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 446: {
sp -= 3; KW x447_0 = KQ_ST(sp + 0); KW x447 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x448_0 = KF_U32_dadd(c, x447_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x447; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 449; sp += 4;
A0 = x448_0; pc = 386; break; }
break;
}
case 384: {
KW x385_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x445_0 = KF_U32_dinc(c, x385_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x385_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 446; sp += 4;
A0 = x445_0; pc = 386; break; }
break;
}
case 456: {
sp -= 3; KW x457_0 = KQ_ST(sp + 0); KW x457 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x458_0 = x457_0; KAUTO x458_1 = x457; KW x458 = k_bnode(c, 2); c->H[KIX(c, x458) + 0] = x458_0; c->H[KIX(c, x458) + 1] = x458_1; x458; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 453: {
sp -= 3; KW x454_0 = KQ_ST(sp + 0); KW x454 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x455_0 = KF_U32_dadd(c, x454_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x454; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 456; sp += 4;
A0 = x455_0; pc = 384; break; }
break;
}
case 382: {
KW x383_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x452_0 = KF_U32_dinc(c, x383_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x383_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 453; sp += 4;
A0 = x452_0; pc = 384; break; }
break;
}
case 463: {
sp -= 3; KW x464_0 = KQ_ST(sp + 0); KW x464 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x465_0 = x464_0; KAUTO x465_1 = x464; KW x465 = k_bnode(c, 2); c->H[KIX(c, x465) + 0] = x465_0; c->H[KIX(c, x465) + 1] = x465_1; x465; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 460: {
sp -= 3; KW x461_0 = KQ_ST(sp + 0); KW x461 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x462_0 = KF_U32_dadd(c, x461_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x461; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 463; sp += 4;
A0 = x462_0; pc = 382; break; }
break;
}
case 380: {
KW x381_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x459_0 = KF_U32_dinc(c, x381_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x381_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 460; sp += 4;
A0 = x459_0; pc = 382; break; }
break;
}
case 470: {
sp -= 3; KW x471_0 = KQ_ST(sp + 0); KW x471 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x472_0 = x471_0; KAUTO x472_1 = x471; KW x472 = k_bnode(c, 2); c->H[KIX(c, x472) + 0] = x472_0; c->H[KIX(c, x472) + 1] = x472_1; x472; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 467: {
sp -= 3; KW x468_0 = KQ_ST(sp + 0); KW x468 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x469_0 = KF_U32_dadd(c, x468_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x468; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 470; sp += 4;
A0 = x469_0; pc = 380; break; }
break;
}
case 378: {
KW x379_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x466_0 = KF_U32_dinc(c, x379_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x379_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 467; sp += 4;
A0 = x466_0; pc = 380; break; }
break;
}
case 477: {
sp -= 3; KW x478_0 = KQ_ST(sp + 0); KW x478 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x479_0 = x478_0; KAUTO x479_1 = x478; KW x479 = k_bnode(c, 2); c->H[KIX(c, x479) + 0] = x479_0; c->H[KIX(c, x479) + 1] = x479_1; x479; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 474: {
sp -= 3; KW x475_0 = KQ_ST(sp + 0); KW x475 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x476_0 = KF_U32_dadd(c, x475_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x475; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 477; sp += 4;
A0 = x476_0; pc = 378; break; }
break;
}
case 376: {
KW x377_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x473_0 = KF_U32_dinc(c, x377_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x377_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 474; sp += 4;
A0 = x473_0; pc = 378; break; }
break;
}
case 484: {
sp -= 3; KW x485_0 = KQ_ST(sp + 0); KW x485 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x486_0 = x485_0; KAUTO x486_1 = x485; KW x486 = k_bnode(c, 2); c->H[KIX(c, x486) + 0] = x486_0; c->H[KIX(c, x486) + 1] = x486_1; x486; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 481: {
sp -= 3; KW x482_0 = KQ_ST(sp + 0); KW x482 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x483_0 = KF_U32_dadd(c, x482_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x482; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 484; sp += 4;
A0 = x483_0; pc = 376; break; }
break;
}
case 374: {
KW x375_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x480_0 = KF_U32_dinc(c, x375_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x375_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 481; sp += 4;
A0 = x480_0; pc = 376; break; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_make_x37s2689494263x247252979(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 503, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 525: {
KW x526_0 = A0; 
K_TREE_MARK(34);
KW x527 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x526_0))));
KW x528 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x526_0, 2u))));
RV = ({ KAUTO x529_0 = x527; KAUTO x529_1 = x528; KW x529 = k_bnode(c, 2); c->H[KIX(c, x529) + 0] = x529_0; c->H[KIX(c, x529) + 1] = x529_1; x529; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 534: {
sp -= 3; KW x535_0 = KQ_ST(sp + 0); KW x535 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x536_0 = x535_0; KAUTO x536_1 = x535; KW x536 = k_bnode(c, 2); c->H[KIX(c, x536) + 0] = x536_0; c->H[KIX(c, x536) + 1] = x536_1; x536; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 531: {
sp -= 3; KW x532_0 = KQ_ST(sp + 0); KW x532 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x533_0 = KF_U32_dadd(c, x532_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x532; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 534; sp += 4;
A0 = x533_0; pc = 525; break; }
break;
}
case 523: {
KW x524_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x530_0 = KF_U32_dinc(c, x524_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x524_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 531; sp += 4;
A0 = x530_0; pc = 525; break; }
break;
}
case 541: {
sp -= 3; KW x542_0 = KQ_ST(sp + 0); KW x542 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x543_0 = x542_0; KAUTO x543_1 = x542; KW x543 = k_bnode(c, 2); c->H[KIX(c, x543) + 0] = x543_0; c->H[KIX(c, x543) + 1] = x543_1; x543; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 538: {
sp -= 3; KW x539_0 = KQ_ST(sp + 0); KW x539 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x540_0 = KF_U32_dadd(c, x539_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x539; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 541; sp += 4;
A0 = x540_0; pc = 523; break; }
break;
}
case 521: {
KW x522_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x537_0 = KF_U32_dinc(c, x522_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x522_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 538; sp += 4;
A0 = x537_0; pc = 523; break; }
break;
}
case 548: {
sp -= 3; KW x549_0 = KQ_ST(sp + 0); KW x549 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x550_0 = x549_0; KAUTO x550_1 = x549; KW x550 = k_bnode(c, 2); c->H[KIX(c, x550) + 0] = x550_0; c->H[KIX(c, x550) + 1] = x550_1; x550; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 545: {
sp -= 3; KW x546_0 = KQ_ST(sp + 0); KW x546 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x547_0 = KF_U32_dadd(c, x546_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x546; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 548; sp += 4;
A0 = x547_0; pc = 521; break; }
break;
}
case 519: {
KW x520_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x544_0 = KF_U32_dinc(c, x520_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x520_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 545; sp += 4;
A0 = x544_0; pc = 521; break; }
break;
}
case 555: {
sp -= 3; KW x556_0 = KQ_ST(sp + 0); KW x556 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x557_0 = x556_0; KAUTO x557_1 = x556; KW x557 = k_bnode(c, 2); c->H[KIX(c, x557) + 0] = x557_0; c->H[KIX(c, x557) + 1] = x557_1; x557; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 552: {
sp -= 3; KW x553_0 = KQ_ST(sp + 0); KW x553 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x554_0 = KF_U32_dadd(c, x553_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x553; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 555; sp += 4;
A0 = x554_0; pc = 519; break; }
break;
}
case 517: {
KW x518_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x551_0 = KF_U32_dinc(c, x518_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x518_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 552; sp += 4;
A0 = x551_0; pc = 519; break; }
break;
}
case 562: {
sp -= 3; KW x563_0 = KQ_ST(sp + 0); KW x563 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x564_0 = x563_0; KAUTO x564_1 = x563; KW x564 = k_bnode(c, 2); c->H[KIX(c, x564) + 0] = x564_0; c->H[KIX(c, x564) + 1] = x564_1; x564; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 559: {
sp -= 3; KW x560_0 = KQ_ST(sp + 0); KW x560 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x561_0 = KF_U32_dadd(c, x560_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x560; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 562; sp += 4;
A0 = x561_0; pc = 517; break; }
break;
}
case 515: {
KW x516_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x558_0 = KF_U32_dinc(c, x516_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x516_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 559; sp += 4;
A0 = x558_0; pc = 517; break; }
break;
}
case 569: {
sp -= 3; KW x570_0 = KQ_ST(sp + 0); KW x570 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x571_0 = x570_0; KAUTO x571_1 = x570; KW x571 = k_bnode(c, 2); c->H[KIX(c, x571) + 0] = x571_0; c->H[KIX(c, x571) + 1] = x571_1; x571; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 566: {
sp -= 3; KW x567_0 = KQ_ST(sp + 0); KW x567 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x568_0 = KF_U32_dadd(c, x567_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x567; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 569; sp += 4;
A0 = x568_0; pc = 515; break; }
break;
}
case 513: {
KW x514_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x565_0 = KF_U32_dinc(c, x514_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x514_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 566; sp += 4;
A0 = x565_0; pc = 515; break; }
break;
}
case 576: {
sp -= 3; KW x577_0 = KQ_ST(sp + 0); KW x577 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x578_0 = x577_0; KAUTO x578_1 = x577; KW x578 = k_bnode(c, 2); c->H[KIX(c, x578) + 0] = x578_0; c->H[KIX(c, x578) + 1] = x578_1; x578; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 573: {
sp -= 3; KW x574_0 = KQ_ST(sp + 0); KW x574 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x575_0 = KF_U32_dadd(c, x574_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x574; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 576; sp += 4;
A0 = x575_0; pc = 513; break; }
break;
}
case 511: {
KW x512_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x572_0 = KF_U32_dinc(c, x512_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x512_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 573; sp += 4;
A0 = x572_0; pc = 513; break; }
break;
}
case 583: {
sp -= 3; KW x584_0 = KQ_ST(sp + 0); KW x584 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x585_0 = x584_0; KAUTO x585_1 = x584; KW x585 = k_bnode(c, 2); c->H[KIX(c, x585) + 0] = x585_0; c->H[KIX(c, x585) + 1] = x585_1; x585; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 580: {
sp -= 3; KW x581_0 = KQ_ST(sp + 0); KW x581 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x582_0 = KF_U32_dadd(c, x581_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x581; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 583; sp += 4;
A0 = x582_0; pc = 511; break; }
break;
}
case 509: {
KW x510_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x579_0 = KF_U32_dinc(c, x510_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x510_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 580; sp += 4;
A0 = x579_0; pc = 511; break; }
break;
}
case 590: {
sp -= 3; KW x591_0 = KQ_ST(sp + 0); KW x591 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x592_0 = x591_0; KAUTO x592_1 = x591; KW x592 = k_bnode(c, 2); c->H[KIX(c, x592) + 0] = x592_0; c->H[KIX(c, x592) + 1] = x592_1; x592; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 587: {
sp -= 3; KW x588_0 = KQ_ST(sp + 0); KW x588 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x589_0 = KF_U32_dadd(c, x588_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x588; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 590; sp += 4;
A0 = x589_0; pc = 509; break; }
break;
}
case 507: {
KW x508_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x586_0 = KF_U32_dinc(c, x508_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x508_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 587; sp += 4;
A0 = x586_0; pc = 509; break; }
break;
}
case 597: {
sp -= 3; KW x598_0 = KQ_ST(sp + 0); KW x598 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x599_0 = x598_0; KAUTO x599_1 = x598; KW x599 = k_bnode(c, 2); c->H[KIX(c, x599) + 0] = x599_0; c->H[KIX(c, x599) + 1] = x599_1; x599; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 594: {
sp -= 3; KW x595_0 = KQ_ST(sp + 0); KW x595 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x596_0 = KF_U32_dadd(c, x595_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x595; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 597; sp += 4;
A0 = x596_0; pc = 507; break; }
break;
}
case 505: {
KW x506_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x593_0 = KF_U32_dinc(c, x506_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x506_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 594; sp += 4;
A0 = x593_0; pc = 507; break; }
break;
}
case 604: {
sp -= 3; KW x605_0 = KQ_ST(sp + 0); KW x605 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x606_0 = x605_0; KAUTO x606_1 = x605; KW x606 = k_bnode(c, 2); c->H[KIX(c, x606) + 0] = x606_0; c->H[KIX(c, x606) + 1] = x606_1; x606; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 601: {
sp -= 3; KW x602_0 = KQ_ST(sp + 0); KW x602 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x603_0 = KF_U32_dadd(c, x602_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x602; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 604; sp += 4;
A0 = x603_0; pc = 505; break; }
break;
}
case 503: {
KW x504_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x600_0 = KF_U32_dinc(c, x504_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x504_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 601; sp += 4;
A0 = x600_0; pc = 505; break; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_make_x37s4233607528x247223188(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 623, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 643: {
KW x644_0 = A0; 
K_TREE_MARK(34);
KW x645 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x644_0))));
KW x646 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x644_0, 2u))));
RV = ({ KAUTO x647_0 = x645; KAUTO x647_1 = x646; KW x647 = k_bnode(c, 2); c->H[KIX(c, x647) + 0] = x647_0; c->H[KIX(c, x647) + 1] = x647_1; x647; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 652: {
sp -= 3; KW x653_0 = KQ_ST(sp + 0); KW x653 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x654_0 = x653_0; KAUTO x654_1 = x653; KW x654 = k_bnode(c, 2); c->H[KIX(c, x654) + 0] = x654_0; c->H[KIX(c, x654) + 1] = x654_1; x654; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 649: {
sp -= 3; KW x650_0 = KQ_ST(sp + 0); KW x650 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x651_0 = KF_U32_dadd(c, x650_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x650; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 652; sp += 4;
A0 = x651_0; pc = 643; break; }
break;
}
case 641: {
KW x642_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x648_0 = KF_U32_dinc(c, x642_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x642_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 649; sp += 4;
A0 = x648_0; pc = 643; break; }
break;
}
case 659: {
sp -= 3; KW x660_0 = KQ_ST(sp + 0); KW x660 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x661_0 = x660_0; KAUTO x661_1 = x660; KW x661 = k_bnode(c, 2); c->H[KIX(c, x661) + 0] = x661_0; c->H[KIX(c, x661) + 1] = x661_1; x661; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 656: {
sp -= 3; KW x657_0 = KQ_ST(sp + 0); KW x657 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x658_0 = KF_U32_dadd(c, x657_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x657; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 659; sp += 4;
A0 = x658_0; pc = 641; break; }
break;
}
case 639: {
KW x640_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x655_0 = KF_U32_dinc(c, x640_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x640_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 656; sp += 4;
A0 = x655_0; pc = 641; break; }
break;
}
case 666: {
sp -= 3; KW x667_0 = KQ_ST(sp + 0); KW x667 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x668_0 = x667_0; KAUTO x668_1 = x667; KW x668 = k_bnode(c, 2); c->H[KIX(c, x668) + 0] = x668_0; c->H[KIX(c, x668) + 1] = x668_1; x668; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 663: {
sp -= 3; KW x664_0 = KQ_ST(sp + 0); KW x664 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x665_0 = KF_U32_dadd(c, x664_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x664; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 666; sp += 4;
A0 = x665_0; pc = 639; break; }
break;
}
case 637: {
KW x638_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x662_0 = KF_U32_dinc(c, x638_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x638_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 663; sp += 4;
A0 = x662_0; pc = 639; break; }
break;
}
case 673: {
sp -= 3; KW x674_0 = KQ_ST(sp + 0); KW x674 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x675_0 = x674_0; KAUTO x675_1 = x674; KW x675 = k_bnode(c, 2); c->H[KIX(c, x675) + 0] = x675_0; c->H[KIX(c, x675) + 1] = x675_1; x675; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 670: {
sp -= 3; KW x671_0 = KQ_ST(sp + 0); KW x671 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x672_0 = KF_U32_dadd(c, x671_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x671; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 673; sp += 4;
A0 = x672_0; pc = 637; break; }
break;
}
case 635: {
KW x636_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x669_0 = KF_U32_dinc(c, x636_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x636_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 670; sp += 4;
A0 = x669_0; pc = 637; break; }
break;
}
case 680: {
sp -= 3; KW x681_0 = KQ_ST(sp + 0); KW x681 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x682_0 = x681_0; KAUTO x682_1 = x681; KW x682 = k_bnode(c, 2); c->H[KIX(c, x682) + 0] = x682_0; c->H[KIX(c, x682) + 1] = x682_1; x682; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 677: {
sp -= 3; KW x678_0 = KQ_ST(sp + 0); KW x678 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x679_0 = KF_U32_dadd(c, x678_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x678; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 680; sp += 4;
A0 = x679_0; pc = 635; break; }
break;
}
case 633: {
KW x634_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x676_0 = KF_U32_dinc(c, x634_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x634_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 677; sp += 4;
A0 = x676_0; pc = 635; break; }
break;
}
case 687: {
sp -= 3; KW x688_0 = KQ_ST(sp + 0); KW x688 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x689_0 = x688_0; KAUTO x689_1 = x688; KW x689 = k_bnode(c, 2); c->H[KIX(c, x689) + 0] = x689_0; c->H[KIX(c, x689) + 1] = x689_1; x689; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 684: {
sp -= 3; KW x685_0 = KQ_ST(sp + 0); KW x685 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x686_0 = KF_U32_dadd(c, x685_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x685; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 687; sp += 4;
A0 = x686_0; pc = 633; break; }
break;
}
case 631: {
KW x632_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x683_0 = KF_U32_dinc(c, x632_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x632_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 684; sp += 4;
A0 = x683_0; pc = 633; break; }
break;
}
case 694: {
sp -= 3; KW x695_0 = KQ_ST(sp + 0); KW x695 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x696_0 = x695_0; KAUTO x696_1 = x695; KW x696 = k_bnode(c, 2); c->H[KIX(c, x696) + 0] = x696_0; c->H[KIX(c, x696) + 1] = x696_1; x696; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 691: {
sp -= 3; KW x692_0 = KQ_ST(sp + 0); KW x692 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x693_0 = KF_U32_dadd(c, x692_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x692; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 694; sp += 4;
A0 = x693_0; pc = 631; break; }
break;
}
case 629: {
KW x630_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x690_0 = KF_U32_dinc(c, x630_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x630_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 691; sp += 4;
A0 = x690_0; pc = 631; break; }
break;
}
case 701: {
sp -= 3; KW x702_0 = KQ_ST(sp + 0); KW x702 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x703_0 = x702_0; KAUTO x703_1 = x702; KW x703 = k_bnode(c, 2); c->H[KIX(c, x703) + 0] = x703_0; c->H[KIX(c, x703) + 1] = x703_1; x703; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 698: {
sp -= 3; KW x699_0 = KQ_ST(sp + 0); KW x699 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x700_0 = KF_U32_dadd(c, x699_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x699; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 701; sp += 4;
A0 = x700_0; pc = 629; break; }
break;
}
case 627: {
KW x628_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x697_0 = KF_U32_dinc(c, x628_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x628_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 698; sp += 4;
A0 = x697_0; pc = 629; break; }
break;
}
case 708: {
sp -= 3; KW x709_0 = KQ_ST(sp + 0); KW x709 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x710_0 = x709_0; KAUTO x710_1 = x709; KW x710 = k_bnode(c, 2); c->H[KIX(c, x710) + 0] = x710_0; c->H[KIX(c, x710) + 1] = x710_1; x710; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 705: {
sp -= 3; KW x706_0 = KQ_ST(sp + 0); KW x706 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x707_0 = KF_U32_dadd(c, x706_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x706; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 708; sp += 4;
A0 = x707_0; pc = 627; break; }
break;
}
case 625: {
KW x626_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x704_0 = KF_U32_dinc(c, x626_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x626_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 705; sp += 4;
A0 = x704_0; pc = 627; break; }
break;
}
case 715: {
sp -= 3; KW x716_0 = KQ_ST(sp + 0); KW x716 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x717_0 = x716_0; KAUTO x717_1 = x716; KW x717 = k_bnode(c, 2); c->H[KIX(c, x717) + 0] = x717_0; c->H[KIX(c, x717) + 1] = x717_1; x717; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 712: {
sp -= 3; KW x713_0 = KQ_ST(sp + 0); KW x713 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x714_0 = KF_U32_dadd(c, x713_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x713; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 715; sp += 4;
A0 = x714_0; pc = 625; break; }
break;
}
case 623: {
KW x624_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x711_0 = KF_U32_dinc(c, x624_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x624_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 712; sp += 4;
A0 = x711_0; pc = 625; break; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_make_x37s1953093269x247193397(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 734, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 752: {
KW x753_0 = A0; 
K_TREE_MARK(34);
KW x754 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x753_0))));
KW x755 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x753_0, 2u))));
RV = ({ KAUTO x756_0 = x754; KAUTO x756_1 = x755; KW x756 = k_bnode(c, 2); c->H[KIX(c, x756) + 0] = x756_0; c->H[KIX(c, x756) + 1] = x756_1; x756; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 761: {
sp -= 3; KW x762_0 = KQ_ST(sp + 0); KW x762 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x763_0 = x762_0; KAUTO x763_1 = x762; KW x763 = k_bnode(c, 2); c->H[KIX(c, x763) + 0] = x763_0; c->H[KIX(c, x763) + 1] = x763_1; x763; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 758: {
sp -= 3; KW x759_0 = KQ_ST(sp + 0); KW x759 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x760_0 = KF_U32_dadd(c, x759_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x759; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 761; sp += 4;
A0 = x760_0; pc = 752; break; }
break;
}
case 750: {
KW x751_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x757_0 = KF_U32_dinc(c, x751_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x751_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 758; sp += 4;
A0 = x757_0; pc = 752; break; }
break;
}
case 768: {
sp -= 3; KW x769_0 = KQ_ST(sp + 0); KW x769 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x770_0 = x769_0; KAUTO x770_1 = x769; KW x770 = k_bnode(c, 2); c->H[KIX(c, x770) + 0] = x770_0; c->H[KIX(c, x770) + 1] = x770_1; x770; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 765: {
sp -= 3; KW x766_0 = KQ_ST(sp + 0); KW x766 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x767_0 = KF_U32_dadd(c, x766_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x766; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 768; sp += 4;
A0 = x767_0; pc = 750; break; }
break;
}
case 748: {
KW x749_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x764_0 = KF_U32_dinc(c, x749_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x749_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 765; sp += 4;
A0 = x764_0; pc = 750; break; }
break;
}
case 775: {
sp -= 3; KW x776_0 = KQ_ST(sp + 0); KW x776 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x777_0 = x776_0; KAUTO x777_1 = x776; KW x777 = k_bnode(c, 2); c->H[KIX(c, x777) + 0] = x777_0; c->H[KIX(c, x777) + 1] = x777_1; x777; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 772: {
sp -= 3; KW x773_0 = KQ_ST(sp + 0); KW x773 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x774_0 = KF_U32_dadd(c, x773_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x773; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 775; sp += 4;
A0 = x774_0; pc = 748; break; }
break;
}
case 746: {
KW x747_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x771_0 = KF_U32_dinc(c, x747_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x747_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 772; sp += 4;
A0 = x771_0; pc = 748; break; }
break;
}
case 782: {
sp -= 3; KW x783_0 = KQ_ST(sp + 0); KW x783 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x784_0 = x783_0; KAUTO x784_1 = x783; KW x784 = k_bnode(c, 2); c->H[KIX(c, x784) + 0] = x784_0; c->H[KIX(c, x784) + 1] = x784_1; x784; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 779: {
sp -= 3; KW x780_0 = KQ_ST(sp + 0); KW x780 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x781_0 = KF_U32_dadd(c, x780_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x780; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 782; sp += 4;
A0 = x781_0; pc = 746; break; }
break;
}
case 744: {
KW x745_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x778_0 = KF_U32_dinc(c, x745_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x745_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 779; sp += 4;
A0 = x778_0; pc = 746; break; }
break;
}
case 789: {
sp -= 3; KW x790_0 = KQ_ST(sp + 0); KW x790 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x791_0 = x790_0; KAUTO x791_1 = x790; KW x791 = k_bnode(c, 2); c->H[KIX(c, x791) + 0] = x791_0; c->H[KIX(c, x791) + 1] = x791_1; x791; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 786: {
sp -= 3; KW x787_0 = KQ_ST(sp + 0); KW x787 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x788_0 = KF_U32_dadd(c, x787_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x787; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 789; sp += 4;
A0 = x788_0; pc = 744; break; }
break;
}
case 742: {
KW x743_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x785_0 = KF_U32_dinc(c, x743_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x743_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 786; sp += 4;
A0 = x785_0; pc = 744; break; }
break;
}
case 796: {
sp -= 3; KW x797_0 = KQ_ST(sp + 0); KW x797 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x798_0 = x797_0; KAUTO x798_1 = x797; KW x798 = k_bnode(c, 2); c->H[KIX(c, x798) + 0] = x798_0; c->H[KIX(c, x798) + 1] = x798_1; x798; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 793: {
sp -= 3; KW x794_0 = KQ_ST(sp + 0); KW x794 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x795_0 = KF_U32_dadd(c, x794_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x794; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 796; sp += 4;
A0 = x795_0; pc = 742; break; }
break;
}
case 740: {
KW x741_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x792_0 = KF_U32_dinc(c, x741_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x741_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 793; sp += 4;
A0 = x792_0; pc = 742; break; }
break;
}
case 803: {
sp -= 3; KW x804_0 = KQ_ST(sp + 0); KW x804 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x805_0 = x804_0; KAUTO x805_1 = x804; KW x805 = k_bnode(c, 2); c->H[KIX(c, x805) + 0] = x805_0; c->H[KIX(c, x805) + 1] = x805_1; x805; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 800: {
sp -= 3; KW x801_0 = KQ_ST(sp + 0); KW x801 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x802_0 = KF_U32_dadd(c, x801_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x801; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 803; sp += 4;
A0 = x802_0; pc = 740; break; }
break;
}
case 738: {
KW x739_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x799_0 = KF_U32_dinc(c, x739_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x739_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 800; sp += 4;
A0 = x799_0; pc = 740; break; }
break;
}
case 810: {
sp -= 3; KW x811_0 = KQ_ST(sp + 0); KW x811 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x812_0 = x811_0; KAUTO x812_1 = x811; KW x812 = k_bnode(c, 2); c->H[KIX(c, x812) + 0] = x812_0; c->H[KIX(c, x812) + 1] = x812_1; x812; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 807: {
sp -= 3; KW x808_0 = KQ_ST(sp + 0); KW x808 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x809_0 = KF_U32_dadd(c, x808_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x808; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 810; sp += 4;
A0 = x809_0; pc = 738; break; }
break;
}
case 736: {
KW x737_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x806_0 = KF_U32_dinc(c, x737_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x737_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 807; sp += 4;
A0 = x806_0; pc = 738; break; }
break;
}
case 817: {
sp -= 3; KW x818_0 = KQ_ST(sp + 0); KW x818 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x819_0 = x818_0; KAUTO x819_1 = x818; KW x819 = k_bnode(c, 2); c->H[KIX(c, x819) + 0] = x819_0; c->H[KIX(c, x819) + 1] = x819_1; x819; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 814: {
sp -= 3; KW x815_0 = KQ_ST(sp + 0); KW x815 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x816_0 = KF_U32_dadd(c, x815_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x815; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 817; sp += 4;
A0 = x816_0; pc = 736; break; }
break;
}
case 734: {
KW x735_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x813_0 = KF_U32_dinc(c, x735_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x735_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 814; sp += 4;
A0 = x813_0; pc = 736; break; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_make_x37s3305376709x8269577(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 836, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 852: {
KW x853_0 = A0; 
K_TREE_MARK(34);
KW x854 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x853_0))));
KW x855 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x853_0, 2u))));
RV = ({ KAUTO x856_0 = x854; KAUTO x856_1 = x855; KW x856 = k_bnode(c, 2); c->H[KIX(c, x856) + 0] = x856_0; c->H[KIX(c, x856) + 1] = x856_1; x856; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 861: {
sp -= 3; KW x862_0 = KQ_ST(sp + 0); KW x862 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x863_0 = x862_0; KAUTO x863_1 = x862; KW x863 = k_bnode(c, 2); c->H[KIX(c, x863) + 0] = x863_0; c->H[KIX(c, x863) + 1] = x863_1; x863; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 858: {
sp -= 3; KW x859_0 = KQ_ST(sp + 0); KW x859 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x860_0 = KF_U32_dadd(c, x859_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x859; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 861; sp += 4;
A0 = x860_0; pc = 852; break; }
break;
}
case 850: {
KW x851_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x857_0 = KF_U32_dinc(c, x851_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x851_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 858; sp += 4;
A0 = x857_0; pc = 852; break; }
break;
}
case 868: {
sp -= 3; KW x869_0 = KQ_ST(sp + 0); KW x869 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x870_0 = x869_0; KAUTO x870_1 = x869; KW x870 = k_bnode(c, 2); c->H[KIX(c, x870) + 0] = x870_0; c->H[KIX(c, x870) + 1] = x870_1; x870; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 865: {
sp -= 3; KW x866_0 = KQ_ST(sp + 0); KW x866 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x867_0 = KF_U32_dadd(c, x866_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x866; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 868; sp += 4;
A0 = x867_0; pc = 850; break; }
break;
}
case 848: {
KW x849_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x864_0 = KF_U32_dinc(c, x849_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x849_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 865; sp += 4;
A0 = x864_0; pc = 850; break; }
break;
}
case 875: {
sp -= 3; KW x876_0 = KQ_ST(sp + 0); KW x876 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x877_0 = x876_0; KAUTO x877_1 = x876; KW x877 = k_bnode(c, 2); c->H[KIX(c, x877) + 0] = x877_0; c->H[KIX(c, x877) + 1] = x877_1; x877; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 872: {
sp -= 3; KW x873_0 = KQ_ST(sp + 0); KW x873 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x874_0 = KF_U32_dadd(c, x873_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x873; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 875; sp += 4;
A0 = x874_0; pc = 848; break; }
break;
}
case 846: {
KW x847_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x871_0 = KF_U32_dinc(c, x847_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x847_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 872; sp += 4;
A0 = x871_0; pc = 848; break; }
break;
}
case 882: {
sp -= 3; KW x883_0 = KQ_ST(sp + 0); KW x883 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x884_0 = x883_0; KAUTO x884_1 = x883; KW x884 = k_bnode(c, 2); c->H[KIX(c, x884) + 0] = x884_0; c->H[KIX(c, x884) + 1] = x884_1; x884; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 879: {
sp -= 3; KW x880_0 = KQ_ST(sp + 0); KW x880 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x881_0 = KF_U32_dadd(c, x880_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x880; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 882; sp += 4;
A0 = x881_0; pc = 846; break; }
break;
}
case 844: {
KW x845_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x878_0 = KF_U32_dinc(c, x845_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x845_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 879; sp += 4;
A0 = x878_0; pc = 846; break; }
break;
}
case 889: {
sp -= 3; KW x890_0 = KQ_ST(sp + 0); KW x890 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x891_0 = x890_0; KAUTO x891_1 = x890; KW x891 = k_bnode(c, 2); c->H[KIX(c, x891) + 0] = x891_0; c->H[KIX(c, x891) + 1] = x891_1; x891; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 886: {
sp -= 3; KW x887_0 = KQ_ST(sp + 0); KW x887 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x888_0 = KF_U32_dadd(c, x887_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x887; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 889; sp += 4;
A0 = x888_0; pc = 844; break; }
break;
}
case 842: {
KW x843_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x885_0 = KF_U32_dinc(c, x843_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x843_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 886; sp += 4;
A0 = x885_0; pc = 844; break; }
break;
}
case 896: {
sp -= 3; KW x897_0 = KQ_ST(sp + 0); KW x897 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x898_0 = x897_0; KAUTO x898_1 = x897; KW x898 = k_bnode(c, 2); c->H[KIX(c, x898) + 0] = x898_0; c->H[KIX(c, x898) + 1] = x898_1; x898; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 893: {
sp -= 3; KW x894_0 = KQ_ST(sp + 0); KW x894 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x895_0 = KF_U32_dadd(c, x894_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x894; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 896; sp += 4;
A0 = x895_0; pc = 842; break; }
break;
}
case 840: {
KW x841_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x892_0 = KF_U32_dinc(c, x841_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x841_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 893; sp += 4;
A0 = x892_0; pc = 842; break; }
break;
}
case 903: {
sp -= 3; KW x904_0 = KQ_ST(sp + 0); KW x904 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x905_0 = x904_0; KAUTO x905_1 = x904; KW x905 = k_bnode(c, 2); c->H[KIX(c, x905) + 0] = x905_0; c->H[KIX(c, x905) + 1] = x905_1; x905; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 900: {
sp -= 3; KW x901_0 = KQ_ST(sp + 0); KW x901 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x902_0 = KF_U32_dadd(c, x901_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x901; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 903; sp += 4;
A0 = x902_0; pc = 840; break; }
break;
}
case 838: {
KW x839_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x899_0 = KF_U32_dinc(c, x839_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x839_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 900; sp += 4;
A0 = x899_0; pc = 840; break; }
break;
}
case 910: {
sp -= 3; KW x911_0 = KQ_ST(sp + 0); KW x911 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x912_0 = x911_0; KAUTO x912_1 = x911; KW x912 = k_bnode(c, 2); c->H[KIX(c, x912) + 0] = x912_0; c->H[KIX(c, x912) + 1] = x912_1; x912; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 907: {
sp -= 3; KW x908_0 = KQ_ST(sp + 0); KW x908 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x909_0 = KF_U32_dadd(c, x908_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x908; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 910; sp += 4;
A0 = x909_0; pc = 838; break; }
break;
}
case 836: {
KW x837_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x906_0 = KF_U32_dinc(c, x837_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x837_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 907; sp += 4;
A0 = x906_0; pc = 838; break; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_make_x37s2491568216x8239786(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 929, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 943: {
KW x944_0 = A0; 
K_TREE_MARK(34);
KW x945 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x944_0))));
KW x946 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x944_0, 2u))));
RV = ({ KAUTO x947_0 = x945; KAUTO x947_1 = x946; KW x947 = k_bnode(c, 2); c->H[KIX(c, x947) + 0] = x947_0; c->H[KIX(c, x947) + 1] = x947_1; x947; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 952: {
sp -= 3; KW x953_0 = KQ_ST(sp + 0); KW x953 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x954_0 = x953_0; KAUTO x954_1 = x953; KW x954 = k_bnode(c, 2); c->H[KIX(c, x954) + 0] = x954_0; c->H[KIX(c, x954) + 1] = x954_1; x954; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 949: {
sp -= 3; KW x950_0 = KQ_ST(sp + 0); KW x950 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x951_0 = KF_U32_dadd(c, x950_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x950; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 952; sp += 4;
A0 = x951_0; pc = 943; break; }
break;
}
case 941: {
KW x942_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x948_0 = KF_U32_dinc(c, x942_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x942_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 949; sp += 4;
A0 = x948_0; pc = 943; break; }
break;
}
case 959: {
sp -= 3; KW x960_0 = KQ_ST(sp + 0); KW x960 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x961_0 = x960_0; KAUTO x961_1 = x960; KW x961 = k_bnode(c, 2); c->H[KIX(c, x961) + 0] = x961_0; c->H[KIX(c, x961) + 1] = x961_1; x961; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 956: {
sp -= 3; KW x957_0 = KQ_ST(sp + 0); KW x957 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x958_0 = KF_U32_dadd(c, x957_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x957; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 959; sp += 4;
A0 = x958_0; pc = 941; break; }
break;
}
case 939: {
KW x940_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x955_0 = KF_U32_dinc(c, x940_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x940_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 956; sp += 4;
A0 = x955_0; pc = 941; break; }
break;
}
case 966: {
sp -= 3; KW x967_0 = KQ_ST(sp + 0); KW x967 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x968_0 = x967_0; KAUTO x968_1 = x967; KW x968 = k_bnode(c, 2); c->H[KIX(c, x968) + 0] = x968_0; c->H[KIX(c, x968) + 1] = x968_1; x968; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 963: {
sp -= 3; KW x964_0 = KQ_ST(sp + 0); KW x964 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x965_0 = KF_U32_dadd(c, x964_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x964; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 966; sp += 4;
A0 = x965_0; pc = 939; break; }
break;
}
case 937: {
KW x938_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x962_0 = KF_U32_dinc(c, x938_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x938_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 963; sp += 4;
A0 = x962_0; pc = 939; break; }
break;
}
case 973: {
sp -= 3; KW x974_0 = KQ_ST(sp + 0); KW x974 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x975_0 = x974_0; KAUTO x975_1 = x974; KW x975 = k_bnode(c, 2); c->H[KIX(c, x975) + 0] = x975_0; c->H[KIX(c, x975) + 1] = x975_1; x975; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 970: {
sp -= 3; KW x971_0 = KQ_ST(sp + 0); KW x971 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x972_0 = KF_U32_dadd(c, x971_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x971; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 973; sp += 4;
A0 = x972_0; pc = 937; break; }
break;
}
case 935: {
KW x936_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x969_0 = KF_U32_dinc(c, x936_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x936_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 970; sp += 4;
A0 = x969_0; pc = 937; break; }
break;
}
case 980: {
sp -= 3; KW x981_0 = KQ_ST(sp + 0); KW x981 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x982_0 = x981_0; KAUTO x982_1 = x981; KW x982 = k_bnode(c, 2); c->H[KIX(c, x982) + 0] = x982_0; c->H[KIX(c, x982) + 1] = x982_1; x982; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 977: {
sp -= 3; KW x978_0 = KQ_ST(sp + 0); KW x978 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x979_0 = KF_U32_dadd(c, x978_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x978; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 980; sp += 4;
A0 = x979_0; pc = 935; break; }
break;
}
case 933: {
KW x934_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x976_0 = KF_U32_dinc(c, x934_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x934_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 977; sp += 4;
A0 = x976_0; pc = 935; break; }
break;
}
case 987: {
sp -= 3; KW x988_0 = KQ_ST(sp + 0); KW x988 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x989_0 = x988_0; KAUTO x989_1 = x988; KW x989 = k_bnode(c, 2); c->H[KIX(c, x989) + 0] = x989_0; c->H[KIX(c, x989) + 1] = x989_1; x989; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 984: {
sp -= 3; KW x985_0 = KQ_ST(sp + 0); KW x985 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x986_0 = KF_U32_dadd(c, x985_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x985; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 987; sp += 4;
A0 = x986_0; pc = 933; break; }
break;
}
case 931: {
KW x932_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x983_0 = KF_U32_dinc(c, x932_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x932_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 984; sp += 4;
A0 = x983_0; pc = 933; break; }
break;
}
case 994: {
sp -= 3; KW x995_0 = KQ_ST(sp + 0); KW x995 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x996_0 = x995_0; KAUTO x996_1 = x995; KW x996 = k_bnode(c, 2); c->H[KIX(c, x996) + 0] = x996_0; c->H[KIX(c, x996) + 1] = x996_1; x996; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 991: {
sp -= 3; KW x992_0 = KQ_ST(sp + 0); KW x992 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x993_0 = KF_U32_dadd(c, x992_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x992; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 994; sp += 4;
A0 = x993_0; pc = 931; break; }
break;
}
case 929: {
KW x930_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x990_0 = KF_U32_dinc(c, x930_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x930_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 991; sp += 4;
A0 = x990_0; pc = 931; break; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_make_x37s1291691603x8209995(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 1013, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 1025: {
KW x1026_0 = A0; 
K_TREE_MARK(34);
KW x1027 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x1026_0))));
KW x1028 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x1026_0, 2u))));
RV = ({ KAUTO x1029_0 = x1027; KAUTO x1029_1 = x1028; KW x1029 = k_bnode(c, 2); c->H[KIX(c, x1029) + 0] = x1029_0; c->H[KIX(c, x1029) + 1] = x1029_1; x1029; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1034: {
sp -= 3; KW x1035_0 = KQ_ST(sp + 0); KW x1035 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1036_0 = x1035_0; KAUTO x1036_1 = x1035; KW x1036 = k_bnode(c, 2); c->H[KIX(c, x1036) + 0] = x1036_0; c->H[KIX(c, x1036) + 1] = x1036_1; x1036; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1031: {
sp -= 3; KW x1032_0 = KQ_ST(sp + 0); KW x1032 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1033_0 = KF_U32_dadd(c, x1032_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1032; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1034; sp += 4;
A0 = x1033_0; pc = 1025; break; }
break;
}
case 1023: {
KW x1024_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1030_0 = KF_U32_dinc(c, x1024_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1024_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1031; sp += 4;
A0 = x1030_0; pc = 1025; break; }
break;
}
case 1041: {
sp -= 3; KW x1042_0 = KQ_ST(sp + 0); KW x1042 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1043_0 = x1042_0; KAUTO x1043_1 = x1042; KW x1043 = k_bnode(c, 2); c->H[KIX(c, x1043) + 0] = x1043_0; c->H[KIX(c, x1043) + 1] = x1043_1; x1043; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1038: {
sp -= 3; KW x1039_0 = KQ_ST(sp + 0); KW x1039 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1040_0 = KF_U32_dadd(c, x1039_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1039; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1041; sp += 4;
A0 = x1040_0; pc = 1023; break; }
break;
}
case 1021: {
KW x1022_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1037_0 = KF_U32_dinc(c, x1022_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1022_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1038; sp += 4;
A0 = x1037_0; pc = 1023; break; }
break;
}
case 1048: {
sp -= 3; KW x1049_0 = KQ_ST(sp + 0); KW x1049 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1050_0 = x1049_0; KAUTO x1050_1 = x1049; KW x1050 = k_bnode(c, 2); c->H[KIX(c, x1050) + 0] = x1050_0; c->H[KIX(c, x1050) + 1] = x1050_1; x1050; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1045: {
sp -= 3; KW x1046_0 = KQ_ST(sp + 0); KW x1046 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1047_0 = KF_U32_dadd(c, x1046_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1046; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1048; sp += 4;
A0 = x1047_0; pc = 1021; break; }
break;
}
case 1019: {
KW x1020_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1044_0 = KF_U32_dinc(c, x1020_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1020_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1045; sp += 4;
A0 = x1044_0; pc = 1021; break; }
break;
}
case 1055: {
sp -= 3; KW x1056_0 = KQ_ST(sp + 0); KW x1056 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1057_0 = x1056_0; KAUTO x1057_1 = x1056; KW x1057 = k_bnode(c, 2); c->H[KIX(c, x1057) + 0] = x1057_0; c->H[KIX(c, x1057) + 1] = x1057_1; x1057; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1052: {
sp -= 3; KW x1053_0 = KQ_ST(sp + 0); KW x1053 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1054_0 = KF_U32_dadd(c, x1053_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1053; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1055; sp += 4;
A0 = x1054_0; pc = 1019; break; }
break;
}
case 1017: {
KW x1018_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1051_0 = KF_U32_dinc(c, x1018_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1018_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1052; sp += 4;
A0 = x1051_0; pc = 1019; break; }
break;
}
case 1062: {
sp -= 3; KW x1063_0 = KQ_ST(sp + 0); KW x1063 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1064_0 = x1063_0; KAUTO x1064_1 = x1063; KW x1064 = k_bnode(c, 2); c->H[KIX(c, x1064) + 0] = x1064_0; c->H[KIX(c, x1064) + 1] = x1064_1; x1064; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1059: {
sp -= 3; KW x1060_0 = KQ_ST(sp + 0); KW x1060 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1061_0 = KF_U32_dadd(c, x1060_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1060; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1062; sp += 4;
A0 = x1061_0; pc = 1017; break; }
break;
}
case 1015: {
KW x1016_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1058_0 = KF_U32_dinc(c, x1016_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1016_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1059; sp += 4;
A0 = x1058_0; pc = 1017; break; }
break;
}
case 1069: {
sp -= 3; KW x1070_0 = KQ_ST(sp + 0); KW x1070 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1071_0 = x1070_0; KAUTO x1071_1 = x1070; KW x1071 = k_bnode(c, 2); c->H[KIX(c, x1071) + 0] = x1071_0; c->H[KIX(c, x1071) + 1] = x1071_1; x1071; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1066: {
sp -= 3; KW x1067_0 = KQ_ST(sp + 0); KW x1067 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1068_0 = KF_U32_dadd(c, x1067_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1067; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1069; sp += 4;
A0 = x1068_0; pc = 1015; break; }
break;
}
case 1013: {
KW x1014_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1065_0 = KF_U32_dinc(c, x1014_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1014_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1066; sp += 4;
A0 = x1065_0; pc = 1015; break; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_make_x37s32637286x8180204(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 1088, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 1098: {
KW x1099_0 = A0; 
K_TREE_MARK(34);
KW x1100 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x1099_0))));
KW x1101 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x1099_0, 2u))));
RV = ({ KAUTO x1102_0 = x1100; KAUTO x1102_1 = x1101; KW x1102 = k_bnode(c, 2); c->H[KIX(c, x1102) + 0] = x1102_0; c->H[KIX(c, x1102) + 1] = x1102_1; x1102; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1107: {
sp -= 3; KW x1108_0 = KQ_ST(sp + 0); KW x1108 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1109_0 = x1108_0; KAUTO x1109_1 = x1108; KW x1109 = k_bnode(c, 2); c->H[KIX(c, x1109) + 0] = x1109_0; c->H[KIX(c, x1109) + 1] = x1109_1; x1109; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1104: {
sp -= 3; KW x1105_0 = KQ_ST(sp + 0); KW x1105 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1106_0 = KF_U32_dadd(c, x1105_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1105; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1107; sp += 4;
A0 = x1106_0; pc = 1098; break; }
break;
}
case 1096: {
KW x1097_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1103_0 = KF_U32_dinc(c, x1097_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1097_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1104; sp += 4;
A0 = x1103_0; pc = 1098; break; }
break;
}
case 1114: {
sp -= 3; KW x1115_0 = KQ_ST(sp + 0); KW x1115 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1116_0 = x1115_0; KAUTO x1116_1 = x1115; KW x1116 = k_bnode(c, 2); c->H[KIX(c, x1116) + 0] = x1116_0; c->H[KIX(c, x1116) + 1] = x1116_1; x1116; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1111: {
sp -= 3; KW x1112_0 = KQ_ST(sp + 0); KW x1112 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1113_0 = KF_U32_dadd(c, x1112_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1112; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1114; sp += 4;
A0 = x1113_0; pc = 1096; break; }
break;
}
case 1094: {
KW x1095_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1110_0 = KF_U32_dinc(c, x1095_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1095_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1111; sp += 4;
A0 = x1110_0; pc = 1096; break; }
break;
}
case 1121: {
sp -= 3; KW x1122_0 = KQ_ST(sp + 0); KW x1122 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1123_0 = x1122_0; KAUTO x1123_1 = x1122; KW x1123 = k_bnode(c, 2); c->H[KIX(c, x1123) + 0] = x1123_0; c->H[KIX(c, x1123) + 1] = x1123_1; x1123; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1118: {
sp -= 3; KW x1119_0 = KQ_ST(sp + 0); KW x1119 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1120_0 = KF_U32_dadd(c, x1119_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1119; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1121; sp += 4;
A0 = x1120_0; pc = 1094; break; }
break;
}
case 1092: {
KW x1093_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1117_0 = KF_U32_dinc(c, x1093_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1093_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1118; sp += 4;
A0 = x1117_0; pc = 1094; break; }
break;
}
case 1128: {
sp -= 3; KW x1129_0 = KQ_ST(sp + 0); KW x1129 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1130_0 = x1129_0; KAUTO x1130_1 = x1129; KW x1130 = k_bnode(c, 2); c->H[KIX(c, x1130) + 0] = x1130_0; c->H[KIX(c, x1130) + 1] = x1130_1; x1130; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1125: {
sp -= 3; KW x1126_0 = KQ_ST(sp + 0); KW x1126 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1127_0 = KF_U32_dadd(c, x1126_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1126; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1128; sp += 4;
A0 = x1127_0; pc = 1092; break; }
break;
}
case 1090: {
KW x1091_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1124_0 = KF_U32_dinc(c, x1091_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1091_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1125; sp += 4;
A0 = x1124_0; pc = 1092; break; }
break;
}
case 1135: {
sp -= 3; KW x1136_0 = KQ_ST(sp + 0); KW x1136 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1137_0 = x1136_0; KAUTO x1137_1 = x1136; KW x1137 = k_bnode(c, 2); c->H[KIX(c, x1137) + 0] = x1137_0; c->H[KIX(c, x1137) + 1] = x1137_1; x1137; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1132: {
sp -= 3; KW x1133_0 = KQ_ST(sp + 0); KW x1133 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1134_0 = KF_U32_dadd(c, x1133_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1133; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1135; sp += 4;
A0 = x1134_0; pc = 1090; break; }
break;
}
case 1088: {
KW x1089_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1131_0 = KF_U32_dinc(c, x1089_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1089_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1132; sp += 4;
A0 = x1131_0; pc = 1090; break; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_make_x37s3239606481x8150413(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 1154, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 1162: {
KW x1163_0 = A0; 
K_TREE_MARK(34);
KW x1164 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x1163_0))));
KW x1165 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x1163_0, 2u))));
RV = ({ KAUTO x1166_0 = x1164; KAUTO x1166_1 = x1165; KW x1166 = k_bnode(c, 2); c->H[KIX(c, x1166) + 0] = x1166_0; c->H[KIX(c, x1166) + 1] = x1166_1; x1166; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1171: {
sp -= 3; KW x1172_0 = KQ_ST(sp + 0); KW x1172 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1173_0 = x1172_0; KAUTO x1173_1 = x1172; KW x1173 = k_bnode(c, 2); c->H[KIX(c, x1173) + 0] = x1173_0; c->H[KIX(c, x1173) + 1] = x1173_1; x1173; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1168: {
sp -= 3; KW x1169_0 = KQ_ST(sp + 0); KW x1169 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1170_0 = KF_U32_dadd(c, x1169_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1169; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1171; sp += 4;
A0 = x1170_0; pc = 1162; break; }
break;
}
case 1160: {
KW x1161_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1167_0 = KF_U32_dinc(c, x1161_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1161_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1168; sp += 4;
A0 = x1167_0; pc = 1162; break; }
break;
}
case 1178: {
sp -= 3; KW x1179_0 = KQ_ST(sp + 0); KW x1179 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1180_0 = x1179_0; KAUTO x1180_1 = x1179; KW x1180 = k_bnode(c, 2); c->H[KIX(c, x1180) + 0] = x1180_0; c->H[KIX(c, x1180) + 1] = x1180_1; x1180; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1175: {
sp -= 3; KW x1176_0 = KQ_ST(sp + 0); KW x1176 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1177_0 = KF_U32_dadd(c, x1176_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1176; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1178; sp += 4;
A0 = x1177_0; pc = 1160; break; }
break;
}
case 1158: {
KW x1159_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1174_0 = KF_U32_dinc(c, x1159_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1159_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1175; sp += 4;
A0 = x1174_0; pc = 1160; break; }
break;
}
case 1185: {
sp -= 3; KW x1186_0 = KQ_ST(sp + 0); KW x1186 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1187_0 = x1186_0; KAUTO x1187_1 = x1186; KW x1187 = k_bnode(c, 2); c->H[KIX(c, x1187) + 0] = x1187_0; c->H[KIX(c, x1187) + 1] = x1187_1; x1187; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1182: {
sp -= 3; KW x1183_0 = KQ_ST(sp + 0); KW x1183 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1184_0 = KF_U32_dadd(c, x1183_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1183; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1185; sp += 4;
A0 = x1184_0; pc = 1158; break; }
break;
}
case 1156: {
KW x1157_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1181_0 = KF_U32_dinc(c, x1157_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1157_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1182; sp += 4;
A0 = x1181_0; pc = 1158; break; }
break;
}
case 1192: {
sp -= 3; KW x1193_0 = KQ_ST(sp + 0); KW x1193 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1194_0 = x1193_0; KAUTO x1194_1 = x1193; KW x1194 = k_bnode(c, 2); c->H[KIX(c, x1194) + 0] = x1194_0; c->H[KIX(c, x1194) + 1] = x1194_1; x1194; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1189: {
sp -= 3; KW x1190_0 = KQ_ST(sp + 0); KW x1190 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1191_0 = KF_U32_dadd(c, x1190_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1190; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1192; sp += 4;
A0 = x1191_0; pc = 1156; break; }
break;
}
case 1154: {
KW x1155_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1188_0 = KF_U32_dinc(c, x1155_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1155_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1189; sp += 4;
A0 = x1188_0; pc = 1156; break; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_make_x37s2405009636x8120622(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 1211, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 1217: {
KW x1218_0 = A0; 
K_TREE_MARK(34);
KW x1219 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x1218_0))));
KW x1220 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x1218_0, 2u))));
RV = ({ KAUTO x1221_0 = x1219; KAUTO x1221_1 = x1220; KW x1221 = k_bnode(c, 2); c->H[KIX(c, x1221) + 0] = x1221_0; c->H[KIX(c, x1221) + 1] = x1221_1; x1221; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1226: {
sp -= 3; KW x1227_0 = KQ_ST(sp + 0); KW x1227 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1228_0 = x1227_0; KAUTO x1228_1 = x1227; KW x1228 = k_bnode(c, 2); c->H[KIX(c, x1228) + 0] = x1228_0; c->H[KIX(c, x1228) + 1] = x1228_1; x1228; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1223: {
sp -= 3; KW x1224_0 = KQ_ST(sp + 0); KW x1224 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1225_0 = KF_U32_dadd(c, x1224_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1224; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1226; sp += 4;
A0 = x1225_0; pc = 1217; break; }
break;
}
case 1215: {
KW x1216_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1222_0 = KF_U32_dinc(c, x1216_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1216_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1223; sp += 4;
A0 = x1222_0; pc = 1217; break; }
break;
}
case 1233: {
sp -= 3; KW x1234_0 = KQ_ST(sp + 0); KW x1234 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1235_0 = x1234_0; KAUTO x1235_1 = x1234; KW x1235 = k_bnode(c, 2); c->H[KIX(c, x1235) + 0] = x1235_0; c->H[KIX(c, x1235) + 1] = x1235_1; x1235; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1230: {
sp -= 3; KW x1231_0 = KQ_ST(sp + 0); KW x1231 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1232_0 = KF_U32_dadd(c, x1231_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1231; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1233; sp += 4;
A0 = x1232_0; pc = 1215; break; }
break;
}
case 1213: {
KW x1214_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1229_0 = KF_U32_dinc(c, x1214_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1214_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1230; sp += 4;
A0 = x1229_0; pc = 1215; break; }
break;
}
case 1240: {
sp -= 3; KW x1241_0 = KQ_ST(sp + 0); KW x1241 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1242_0 = x1241_0; KAUTO x1242_1 = x1241; KW x1242 = k_bnode(c, 2); c->H[KIX(c, x1242) + 0] = x1242_0; c->H[KIX(c, x1242) + 1] = x1242_1; x1242; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1237: {
sp -= 3; KW x1238_0 = KQ_ST(sp + 0); KW x1238 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1239_0 = KF_U32_dadd(c, x1238_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1238; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1240; sp += 4;
A0 = x1239_0; pc = 1213; break; }
break;
}
case 1211: {
KW x1212_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1236_0 = KF_U32_dinc(c, x1212_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1212_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1237; sp += 4;
A0 = x1236_0; pc = 1213; break; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_make_x37s1586577935x8090831(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 1259, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 1263: {
KW x1264_0 = A0; 
K_TREE_MARK(34);
KW x1265 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x1264_0))));
KW x1266 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x1264_0, 2u))));
RV = ({ KAUTO x1267_0 = x1265; KAUTO x1267_1 = x1266; KW x1267 = k_bnode(c, 2); c->H[KIX(c, x1267) + 0] = x1267_0; c->H[KIX(c, x1267) + 1] = x1267_1; x1267; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1272: {
sp -= 3; KW x1273_0 = KQ_ST(sp + 0); KW x1273 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1274_0 = x1273_0; KAUTO x1274_1 = x1273; KW x1274 = k_bnode(c, 2); c->H[KIX(c, x1274) + 0] = x1274_0; c->H[KIX(c, x1274) + 1] = x1274_1; x1274; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1269: {
sp -= 3; KW x1270_0 = KQ_ST(sp + 0); KW x1270 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1271_0 = KF_U32_dadd(c, x1270_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1270; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1272; sp += 4;
A0 = x1271_0; pc = 1263; break; }
break;
}
case 1261: {
KW x1262_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1268_0 = KF_U32_dinc(c, x1262_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1262_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1269; sp += 4;
A0 = x1268_0; pc = 1263; break; }
break;
}
case 1279: {
sp -= 3; KW x1280_0 = KQ_ST(sp + 0); KW x1280 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1281_0 = x1280_0; KAUTO x1281_1 = x1280; KW x1281 = k_bnode(c, 2); c->H[KIX(c, x1281) + 0] = x1281_0; c->H[KIX(c, x1281) + 1] = x1281_1; x1281; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1276: {
sp -= 3; KW x1277_0 = KQ_ST(sp + 0); KW x1277 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1278_0 = KF_U32_dadd(c, x1277_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1277; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1279; sp += 4;
A0 = x1278_0; pc = 1261; break; }
break;
}
case 1259: {
KW x1260_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1275_0 = KF_U32_dinc(c, x1260_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1260_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1276; sp += 4;
A0 = x1275_0; pc = 1261; break; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_make_x37s3867092194x8061040(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 1298, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 1300: {
KW x1301_0 = A0; 
K_TREE_MARK(34);
KW x1302 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x1301_0))));
KW x1303 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x1301_0, 2u))));
RV = ({ KAUTO x1304_0 = x1302; KAUTO x1304_1 = x1303; KW x1304 = k_bnode(c, 2); c->H[KIX(c, x1304) + 0] = x1304_0; c->H[KIX(c, x1304) + 1] = x1304_1; x1304; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1309: {
sp -= 3; KW x1310_0 = KQ_ST(sp + 0); KW x1310 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
RV = ({ KAUTO x1311_0 = x1310_0; KAUTO x1311_1 = x1310; KW x1311 = k_bnode(c, 2); c->H[KIX(c, x1311) + 0] = x1311_0; c->H[KIX(c, x1311) + 1] = x1311_1; x1311; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
case 1306: {
sp -= 3; KW x1307_0 = KQ_ST(sp + 0); KW x1307 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);
{ KAUTO x1308_0 = KF_U32_dadd(c, x1307_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1307; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1309; sp += 4;
A0 = x1308_0; pc = 1300; break; }
break;
}
case 1298: {
KW x1299_0 = A0; 
K_TREE_MARK(34);
{ KAUTO x1305_0 = KF_U32_dinc(c, x1299_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }
KQ_ST(sp + 0) = x1299_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1306; sp += 4;
A0 = x1305_0; pc = 1300; break; }
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW KQ_make_x37s1860454509x8031249(KTHR KCtx *c, KW p0, KTHR bool *ok) {
KQ_STACK; K_TREE_STACK;
KW sp = 0, pc = 1319, RV = 0, st = c->kqlim;
KW A0 = p0;
KW A1 = 0;
KW A2 = 0;
KW A3 = 0;
KW A4 = 0;
KW A5 = 0;
KW A6 = 0;
KW A7 = 0;
KW A8 = 0;
KW A9 = 0;
KW A10 = 0;
KW A11 = 0;
for (;;) {
if (st-- == 0 || c->err != 0) { *ok = false; return 0; }
switch (pc) {
case 1319: {
KW x1320_0 = A0; 
K_TREE_MARK(34);
KW x1321 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x1320_0))));
KW x1322 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x1320_0, 2u))));
RV = ({ KAUTO x1323_0 = x1321; KAUTO x1323_1 = x1322; KW x1323 = k_bnode(c, 2); c->H[KIX(c, x1323) + 0] = x1323_0; c->H[KIX(c, x1323) + 1] = x1323_1; x1323; });
K_TREE_RET;
if (sp == 0) return RV;
sp -= 1; pc = KQ_ST(sp); break;
break;
}
default:
*ok = false;
return 0;
}
}
}

KINLINE KW k_kq(KTHR KCtx *c, KTHR bool *ok) {
switch (c->kq) {
case 1286: return KQ_make_x37s1860454509x8031249(c, c->kqa[0], ok);
case 1247: return KQ_make_x37s3867092194x8061040(c, c->kqa[0], ok);
case 1199: return KQ_make_x37s1586577935x8090831(c, c->kqa[0], ok);
case 1142: return KQ_make_x37s2405009636x8120622(c, c->kqa[0], ok);
case 1076: return KQ_make_x37s3239606481x8150413(c, c->kqa[0], ok);
case 1001: return KQ_make_x37s32637286x8180204(c, c->kqa[0], ok);
case 917: return KQ_make_x37s1291691603x8209995(c, c->kqa[0], ok);
case 824: return KQ_make_x37s2491568216x8239786(c, c->kqa[0], ok);
case 722: return KQ_make_x37s3305376709x8269577(c, c->kqa[0], ok);
case 611: return KQ_make_x37s1953093269x247193397(c, c->kqa[0], ok);
case 491: return KQ_make_x37s4233607528x247223188(c, c->kqa[0], ok);
case 362: return KQ_make_x37s2689494263x247252979(c, c->kqa[0], ok);
case 224: return KQ_make_x37s675041226x247282770(c, c->kqa[0], ok);
case 48: return KQ_make_x37s3795296409x247312561(c, c->kqa[0], ok);
case 8: return KQ_sum(c, c->kqa[0], ok);
case 10: return KQ_rounds(c, c->kqa[0], c->kqa[1], ok);
case 12: return KQ_make(c, c->kqa[0], c->kqa[1], ok);
default:
*ok = false;
return 0;
}
}
#ifndef __METAL_VERSION__
#define K_KQH_LIST 
#endif

KINLINE void k_cases(KTHR KCtx *c) {
switch (c->pc) {
case 13: {
{ KW nf = KPUSH(14, 12);
KARG(nf, 0) = KS(0);
KARG(nf, 1) = KS(1);
KFP = nf; KPC = 12; }
break;
}
case 14: {
KS(2) = KRV;
KRET(KS(2));
break;
}
case 12: {
KS(2) = KS(0);
if ((KS(2)) == 0) { KPC = 15; } else if (k_nge(c, KS(2), 1)) { KPC = 16; } else { k_fail(c, KE_MATCH); }
break;
}
case 15: {
KS(3) = KS(1);
KRET(KLI(0, KS(3)));
break;
}
case 16: {
KPC = KFORK ? 17 : 18;
break;
}
case 18: {
KS(7) = ((KS(2)) - 1);
KS(8) = KS(1);
KS(9) = KF_U32_dinc(c, KS(8));
c->kq = 12; c->kqret = 21; c->kqfb = 23;
c->kqa[0] = KS(7);
c->kqa[1] = KS(9);
KPC = PC_KQ;
break;
}
case 23: {
{ KW nf = KPUSH(21, 12);
KARG(nf, 0) = c->kqa[0];
KARG(nf, 1) = c->kqa[1];
KFP = nf; KPC = 12; }
break;
}
case 21: {
KS(4) = KRV;
KPC = 22;
break;
}
case 22: {
KS(10) = ((KS(2)) - 1);
KS(11) = KS(1);
KS(12) = 2u;
KS(13) = KF_U32_dadd(c, KS(11), KS(12));
c->kq = 12; c->kqret = 24; c->kqfb = 26;
c->kqa[0] = KS(10);
c->kqa[1] = KS(13);
KPC = PC_KQ;
break;
}
case 26: {
{ KW nf = KPUSH(24, 12);
KARG(nf, 0) = c->kqa[0];
KARG(nf, 1) = c->kqa[1];
KFP = nf; KPC = 12; }
break;
}
case 24: {
KS(5) = KRV;
KPC = 25;
break;
}
case 25: {
KPC = 20;
break;
}
case 27: {
KS(3) = KS(1);
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
{ KW nf = KPUSH(28, 12);
KARG(nf, 0) = KS(3);
KARG(nf, 1) = KS(5);
KFP = nf; KPC = 12; }
break;
}
case 28: {
KS(6) = KRV;
KRET(KS(6));
break;
}
case 29: {
KS(3) = KS(1);
KS(4) = KS(0);
KS(5) = 2u;
KS(6) = KF_U32_dadd(c, KS(4), KS(5));
{ KW nf = KPUSH(30, 12);
KARG(nf, 0) = KS(3);
KARG(nf, 1) = KS(6);
KFP = nf; KPC = 12; }
break;
}
case 30: {
KS(7) = KRV;
KRET(KS(7));
break;
}
case 17: {
{ KW p = k_alloc(c, 5); KW w = KIX(c, p);
c->H[w] = KCLO | 27; c->H[w + 1] = 3; c->H[w + 2] = 2;
c->H[w + 3] = KS(1);
c->H[w + 4] = ((KS(2)) - 1);
KS(14) = p; }
KS(15) = KS(14);
{ KW p = k_alloc(c, 5); KW w = KIX(c, p);
c->H[w] = KCLO | 29; c->H[w + 1] = 3; c->H[w + 2] = 2;
c->H[w + 3] = KS(1);
c->H[w + 4] = ((KS(2)) - 1);
KS(16) = p; }
KS(17) = KS(16);
KS(6) = k_join_new(c, 2, 19);
if (!k_push_task(c, PC_TASK, KS(6), KS(15), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(17), 0, 31);
break;
}
case 31: {
KS(18) = KRV;
k_arrive(c, KS(6), 1, KS(18));
break;
}
case 19: {
KS(4) = c->H[KS(6) + 4];
KS(5) = c->H[KS(6) + 5];
KPC = 20;
break;
}
case 20: {
KS(19) = KS(4);
KS(20) = KS(5);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(19);
c->H[w + 1] = KS(20);
KS(21) = p; }
KRET(KS(21));
break;
}
case 11: {
c->kq = 10; c->kqret = 43; c->kqfb = 45 | K_KQLIM;
c->kqa[0] = KS(0);
c->kqa[1] = KS(1);
KPC = PC_KQ;
break;
}
case 45: {
{ KW nf = KPUSH(43, 10);
KARG(nf, 0) = c->kqa[0];
KARG(nf, 1) = c->kqa[1];
KFP = nf; KPC = 10; }
break;
}
case 43: {
KS(2) = KRV;
KPC = 44;
break;
}
case 44: {
KRET(KS(2));
break;
}
case 10: {
KS(2) = KS(0);
if ((KS(2)) == 0) { KPC = 46; } else if (k_nge(c, KS(2), 1)) { KPC = 47; } else { k_fail(c, KE_MATCH); }
break;
}
case 46: {
KRET(KS(1));
break;
}
case 47: {
KS(3) = ((KS(2)) - 1);
KS(4) = KS(1);
KS(5) = 1u;
{ KW nf = KPUSH(49, 48);
KARG(nf, 0) = KS(5);
KFP = nf; KPC = 48; }
break;
}
case 49: {
KS(6) = KRV;
KS(7) = KS(6);
{ KW nf = KPUSH(50, 8);
KARG(nf, 0) = KS(7);
KFP = nf; KPC = 8; }
break;
}
case 50: {
KS(8) = KRV;
KS(9) = KS(8);
KS(10) = KF_U32_dadd(c, KS(4), KS(9));
{ KS(0) = KS(3); KS(1) = KS(10); KPC = 10; }
break;
}
case 9: {
{ KW nf = KPUSH(193, 8);
KARG(nf, 0) = KS(0);
KFP = nf; KPC = 8; }
break;
}
case 193: {
KS(1) = KRV;
KRET(KS(1));
break;
}
case 8: {
KS(1) = KS(0);
if (KIS_LI(KS(1), 0)) { KPC = 194; } else if (!((KS(1)) & 1)) { KPC = 195; } else { k_fail(c, KE_MATCH); }
break;
}
case 194: {
KRET(KLI_V(KS(1)));
break;
}
case 195: {
KPC = KFORK ? 196 : 197;
break;
}
case 197: {
KS(5) = KFLB(KS(1), 0);
c->kq = 8; c->kqret = 200; c->kqfb = 202;
c->kqa[0] = KS(5);
KPC = PC_KQ;
break;
}
case 202: {
{ KW nf = KPUSH(200, 8);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 8; }
break;
}
case 200: {
KS(2) = KRV;
KPC = 201;
break;
}
case 201: {
KS(6) = KFLB(KS(1), 1);
c->kq = 8; c->kqret = 203; c->kqfb = 205;
c->kqa[0] = KS(6);
KPC = PC_KQ;
break;
}
case 205: {
{ KW nf = KPUSH(203, 8);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 8; }
break;
}
case 203: {
KS(3) = KRV;
KPC = 204;
break;
}
case 204: {
KPC = 199;
break;
}
case 206: {
KS(2) = KS(0);
{ KW nf = KPUSH(207, 8);
KARG(nf, 0) = KS(2);
KFP = nf; KPC = 8; }
break;
}
case 207: {
KS(3) = KRV;
KRET(KS(3));
break;
}
case 208: {
KS(2) = KS(0);
{ KW nf = KPUSH(209, 8);
KARG(nf, 0) = KS(2);
KFP = nf; KPC = 8; }
break;
}
case 209: {
KS(3) = KRV;
KRET(KS(3));
break;
}
case 196: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 206; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KFLB(KS(1), 0);
KS(7) = p; }
KS(8) = KS(7);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 208; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KFLB(KS(1), 1);
KS(9) = p; }
KS(10) = KS(9);
KS(4) = k_join_new(c, 2, 198);
if (!k_push_task(c, PC_TASK, KS(4), KS(8), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(10), 0, 210);
break;
}
case 210: {
KS(11) = KRV;
k_arrive(c, KS(4), 1, KS(11));
break;
}
case 198: {
KS(2) = c->H[KS(4) + 4];
KS(3) = c->H[KS(4) + 5];
KPC = 199;
break;
}
case 199: {
KS(12) = KS(2);
KS(13) = KS(3);
KRET(KF_U32_dadd(c, KS(12), KS(13)));
break;
}
case 48: {
KPC = KFORK ? 220 : 221;
break;
}
case 221: {
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
c->kq = 224; c->kqret = 225; c->kqfb = 227;
c->kqa[0] = KS(5);
KPC = PC_KQ;
break;
}
case 227: {
{ KW nf = KPUSH(225, 224);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 224; }
break;
}
case 225: {
KS(1) = KRV;
KPC = 226;
break;
}
case 226: {
KS(6) = KS(0);
KS(7) = 2u;
KS(8) = KF_U32_dadd(c, KS(6), KS(7));
c->kq = 224; c->kqret = 228; c->kqfb = 230;
c->kqa[0] = KS(8);
KPC = PC_KQ;
break;
}
case 230: {
{ KW nf = KPUSH(228, 224);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 224; }
break;
}
case 228: {
KS(2) = KRV;
KPC = 229;
break;
}
case 229: {
KPC = 223;
break;
}
case 231: {
KS(2) = KS(0);
KS(3) = KF_U32_dinc(c, KS(2));
{ KW nf = KPUSH(232, 224);
KARG(nf, 0) = KS(3);
KFP = nf; KPC = 224; }
break;
}
case 232: {
KS(4) = KRV;
KRET(KS(4));
break;
}
case 233: {
KS(2) = KS(0);
KS(3) = 2u;
KS(4) = KF_U32_dadd(c, KS(2), KS(3));
{ KW nf = KPUSH(234, 224);
KARG(nf, 0) = KS(4);
KFP = nf; KPC = 224; }
break;
}
case 234: {
KS(5) = KRV;
KRET(KS(5));
break;
}
case 220: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 231; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(9) = p; }
KS(10) = KS(9);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 233; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(11) = p; }
KS(12) = KS(11);
KS(3) = k_join_new(c, 2, 222);
if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(12), 0, 235);
break;
}
case 235: {
KS(13) = KRV;
k_arrive(c, KS(3), 1, KS(13));
break;
}
case 222: {
KS(1) = c->H[KS(3) + 4];
KS(2) = c->H[KS(3) + 5];
KPC = 223;
break;
}
case 223: {
KS(14) = KS(1);
KS(15) = KS(2);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(14);
c->H[w + 1] = KS(15);
KS(16) = p; }
KRET(KS(16));
break;
}
case 224: {
KPC = KFORK ? 358 : 359;
break;
}
case 359: {
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
c->kq = 362; c->kqret = 363; c->kqfb = 365;
c->kqa[0] = KS(5);
KPC = PC_KQ;
break;
}
case 365: {
{ KW nf = KPUSH(363, 362);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 362; }
break;
}
case 363: {
KS(1) = KRV;
KPC = 364;
break;
}
case 364: {
KS(6) = KS(0);
KS(7) = 2u;
KS(8) = KF_U32_dadd(c, KS(6), KS(7));
c->kq = 362; c->kqret = 366; c->kqfb = 368;
c->kqa[0] = KS(8);
KPC = PC_KQ;
break;
}
case 368: {
{ KW nf = KPUSH(366, 362);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 362; }
break;
}
case 366: {
KS(2) = KRV;
KPC = 367;
break;
}
case 367: {
KPC = 361;
break;
}
case 369: {
KS(2) = KS(0);
KS(3) = KF_U32_dinc(c, KS(2));
{ KW nf = KPUSH(370, 362);
KARG(nf, 0) = KS(3);
KFP = nf; KPC = 362; }
break;
}
case 370: {
KS(4) = KRV;
KRET(KS(4));
break;
}
case 371: {
KS(2) = KS(0);
KS(3) = 2u;
KS(4) = KF_U32_dadd(c, KS(2), KS(3));
{ KW nf = KPUSH(372, 362);
KARG(nf, 0) = KS(4);
KFP = nf; KPC = 362; }
break;
}
case 372: {
KS(5) = KRV;
KRET(KS(5));
break;
}
case 358: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 369; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(9) = p; }
KS(10) = KS(9);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 371; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(11) = p; }
KS(12) = KS(11);
KS(3) = k_join_new(c, 2, 360);
if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(12), 0, 373);
break;
}
case 373: {
KS(13) = KRV;
k_arrive(c, KS(3), 1, KS(13));
break;
}
case 360: {
KS(1) = c->H[KS(3) + 4];
KS(2) = c->H[KS(3) + 5];
KPC = 361;
break;
}
case 361: {
KS(14) = KS(1);
KS(15) = KS(2);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(14);
c->H[w + 1] = KS(15);
KS(16) = p; }
KRET(KS(16));
break;
}
case 362: {
KPC = KFORK ? 487 : 488;
break;
}
case 488: {
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
c->kq = 491; c->kqret = 492; c->kqfb = 494;
c->kqa[0] = KS(5);
KPC = PC_KQ;
break;
}
case 494: {
{ KW nf = KPUSH(492, 491);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 491; }
break;
}
case 492: {
KS(1) = KRV;
KPC = 493;
break;
}
case 493: {
KS(6) = KS(0);
KS(7) = 2u;
KS(8) = KF_U32_dadd(c, KS(6), KS(7));
c->kq = 491; c->kqret = 495; c->kqfb = 497;
c->kqa[0] = KS(8);
KPC = PC_KQ;
break;
}
case 497: {
{ KW nf = KPUSH(495, 491);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 491; }
break;
}
case 495: {
KS(2) = KRV;
KPC = 496;
break;
}
case 496: {
KPC = 490;
break;
}
case 498: {
KS(2) = KS(0);
KS(3) = KF_U32_dinc(c, KS(2));
{ KW nf = KPUSH(499, 491);
KARG(nf, 0) = KS(3);
KFP = nf; KPC = 491; }
break;
}
case 499: {
KS(4) = KRV;
KRET(KS(4));
break;
}
case 500: {
KS(2) = KS(0);
KS(3) = 2u;
KS(4) = KF_U32_dadd(c, KS(2), KS(3));
{ KW nf = KPUSH(501, 491);
KARG(nf, 0) = KS(4);
KFP = nf; KPC = 491; }
break;
}
case 501: {
KS(5) = KRV;
KRET(KS(5));
break;
}
case 487: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 498; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(9) = p; }
KS(10) = KS(9);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 500; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(11) = p; }
KS(12) = KS(11);
KS(3) = k_join_new(c, 2, 489);
if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(12), 0, 502);
break;
}
case 502: {
KS(13) = KRV;
k_arrive(c, KS(3), 1, KS(13));
break;
}
case 489: {
KS(1) = c->H[KS(3) + 4];
KS(2) = c->H[KS(3) + 5];
KPC = 490;
break;
}
case 490: {
KS(14) = KS(1);
KS(15) = KS(2);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(14);
c->H[w + 1] = KS(15);
KS(16) = p; }
KRET(KS(16));
break;
}
case 491: {
KPC = KFORK ? 607 : 608;
break;
}
case 608: {
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
c->kq = 611; c->kqret = 612; c->kqfb = 614;
c->kqa[0] = KS(5);
KPC = PC_KQ;
break;
}
case 614: {
{ KW nf = KPUSH(612, 611);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 611; }
break;
}
case 612: {
KS(1) = KRV;
KPC = 613;
break;
}
case 613: {
KS(6) = KS(0);
KS(7) = 2u;
KS(8) = KF_U32_dadd(c, KS(6), KS(7));
c->kq = 611; c->kqret = 615; c->kqfb = 617;
c->kqa[0] = KS(8);
KPC = PC_KQ;
break;
}
case 617: {
{ KW nf = KPUSH(615, 611);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 611; }
break;
}
case 615: {
KS(2) = KRV;
KPC = 616;
break;
}
case 616: {
KPC = 610;
break;
}
case 618: {
KS(2) = KS(0);
KS(3) = KF_U32_dinc(c, KS(2));
{ KW nf = KPUSH(619, 611);
KARG(nf, 0) = KS(3);
KFP = nf; KPC = 611; }
break;
}
case 619: {
KS(4) = KRV;
KRET(KS(4));
break;
}
case 620: {
KS(2) = KS(0);
KS(3) = 2u;
KS(4) = KF_U32_dadd(c, KS(2), KS(3));
{ KW nf = KPUSH(621, 611);
KARG(nf, 0) = KS(4);
KFP = nf; KPC = 611; }
break;
}
case 621: {
KS(5) = KRV;
KRET(KS(5));
break;
}
case 607: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 618; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(9) = p; }
KS(10) = KS(9);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 620; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(11) = p; }
KS(12) = KS(11);
KS(3) = k_join_new(c, 2, 609);
if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(12), 0, 622);
break;
}
case 622: {
KS(13) = KRV;
k_arrive(c, KS(3), 1, KS(13));
break;
}
case 609: {
KS(1) = c->H[KS(3) + 4];
KS(2) = c->H[KS(3) + 5];
KPC = 610;
break;
}
case 610: {
KS(14) = KS(1);
KS(15) = KS(2);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(14);
c->H[w + 1] = KS(15);
KS(16) = p; }
KRET(KS(16));
break;
}
case 611: {
KPC = KFORK ? 718 : 719;
break;
}
case 719: {
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
c->kq = 722; c->kqret = 723; c->kqfb = 725;
c->kqa[0] = KS(5);
KPC = PC_KQ;
break;
}
case 725: {
{ KW nf = KPUSH(723, 722);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 722; }
break;
}
case 723: {
KS(1) = KRV;
KPC = 724;
break;
}
case 724: {
KS(6) = KS(0);
KS(7) = 2u;
KS(8) = KF_U32_dadd(c, KS(6), KS(7));
c->kq = 722; c->kqret = 726; c->kqfb = 728;
c->kqa[0] = KS(8);
KPC = PC_KQ;
break;
}
case 728: {
{ KW nf = KPUSH(726, 722);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 722; }
break;
}
case 726: {
KS(2) = KRV;
KPC = 727;
break;
}
case 727: {
KPC = 721;
break;
}
case 729: {
KS(2) = KS(0);
KS(3) = KF_U32_dinc(c, KS(2));
{ KW nf = KPUSH(730, 722);
KARG(nf, 0) = KS(3);
KFP = nf; KPC = 722; }
break;
}
case 730: {
KS(4) = KRV;
KRET(KS(4));
break;
}
case 731: {
KS(2) = KS(0);
KS(3) = 2u;
KS(4) = KF_U32_dadd(c, KS(2), KS(3));
{ KW nf = KPUSH(732, 722);
KARG(nf, 0) = KS(4);
KFP = nf; KPC = 722; }
break;
}
case 732: {
KS(5) = KRV;
KRET(KS(5));
break;
}
case 718: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 729; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(9) = p; }
KS(10) = KS(9);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 731; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(11) = p; }
KS(12) = KS(11);
KS(3) = k_join_new(c, 2, 720);
if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(12), 0, 733);
break;
}
case 733: {
KS(13) = KRV;
k_arrive(c, KS(3), 1, KS(13));
break;
}
case 720: {
KS(1) = c->H[KS(3) + 4];
KS(2) = c->H[KS(3) + 5];
KPC = 721;
break;
}
case 721: {
KS(14) = KS(1);
KS(15) = KS(2);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(14);
c->H[w + 1] = KS(15);
KS(16) = p; }
KRET(KS(16));
break;
}
case 722: {
KPC = KFORK ? 820 : 821;
break;
}
case 821: {
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
c->kq = 824; c->kqret = 825; c->kqfb = 827;
c->kqa[0] = KS(5);
KPC = PC_KQ;
break;
}
case 827: {
{ KW nf = KPUSH(825, 824);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 824; }
break;
}
case 825: {
KS(1) = KRV;
KPC = 826;
break;
}
case 826: {
KS(6) = KS(0);
KS(7) = 2u;
KS(8) = KF_U32_dadd(c, KS(6), KS(7));
c->kq = 824; c->kqret = 828; c->kqfb = 830;
c->kqa[0] = KS(8);
KPC = PC_KQ;
break;
}
case 830: {
{ KW nf = KPUSH(828, 824);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 824; }
break;
}
case 828: {
KS(2) = KRV;
KPC = 829;
break;
}
case 829: {
KPC = 823;
break;
}
case 831: {
KS(2) = KS(0);
KS(3) = KF_U32_dinc(c, KS(2));
{ KW nf = KPUSH(832, 824);
KARG(nf, 0) = KS(3);
KFP = nf; KPC = 824; }
break;
}
case 832: {
KS(4) = KRV;
KRET(KS(4));
break;
}
case 833: {
KS(2) = KS(0);
KS(3) = 2u;
KS(4) = KF_U32_dadd(c, KS(2), KS(3));
{ KW nf = KPUSH(834, 824);
KARG(nf, 0) = KS(4);
KFP = nf; KPC = 824; }
break;
}
case 834: {
KS(5) = KRV;
KRET(KS(5));
break;
}
case 820: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 831; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(9) = p; }
KS(10) = KS(9);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 833; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(11) = p; }
KS(12) = KS(11);
KS(3) = k_join_new(c, 2, 822);
if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(12), 0, 835);
break;
}
case 835: {
KS(13) = KRV;
k_arrive(c, KS(3), 1, KS(13));
break;
}
case 822: {
KS(1) = c->H[KS(3) + 4];
KS(2) = c->H[KS(3) + 5];
KPC = 823;
break;
}
case 823: {
KS(14) = KS(1);
KS(15) = KS(2);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(14);
c->H[w + 1] = KS(15);
KS(16) = p; }
KRET(KS(16));
break;
}
case 824: {
KPC = KFORK ? 913 : 914;
break;
}
case 914: {
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
c->kq = 917; c->kqret = 918; c->kqfb = 920;
c->kqa[0] = KS(5);
KPC = PC_KQ;
break;
}
case 920: {
{ KW nf = KPUSH(918, 917);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 917; }
break;
}
case 918: {
KS(1) = KRV;
KPC = 919;
break;
}
case 919: {
KS(6) = KS(0);
KS(7) = 2u;
KS(8) = KF_U32_dadd(c, KS(6), KS(7));
c->kq = 917; c->kqret = 921; c->kqfb = 923;
c->kqa[0] = KS(8);
KPC = PC_KQ;
break;
}
case 923: {
{ KW nf = KPUSH(921, 917);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 917; }
break;
}
case 921: {
KS(2) = KRV;
KPC = 922;
break;
}
case 922: {
KPC = 916;
break;
}
case 924: {
KS(2) = KS(0);
KS(3) = KF_U32_dinc(c, KS(2));
{ KW nf = KPUSH(925, 917);
KARG(nf, 0) = KS(3);
KFP = nf; KPC = 917; }
break;
}
case 925: {
KS(4) = KRV;
KRET(KS(4));
break;
}
case 926: {
KS(2) = KS(0);
KS(3) = 2u;
KS(4) = KF_U32_dadd(c, KS(2), KS(3));
{ KW nf = KPUSH(927, 917);
KARG(nf, 0) = KS(4);
KFP = nf; KPC = 917; }
break;
}
case 927: {
KS(5) = KRV;
KRET(KS(5));
break;
}
case 913: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 924; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(9) = p; }
KS(10) = KS(9);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 926; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(11) = p; }
KS(12) = KS(11);
KS(3) = k_join_new(c, 2, 915);
if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(12), 0, 928);
break;
}
case 928: {
KS(13) = KRV;
k_arrive(c, KS(3), 1, KS(13));
break;
}
case 915: {
KS(1) = c->H[KS(3) + 4];
KS(2) = c->H[KS(3) + 5];
KPC = 916;
break;
}
case 916: {
KS(14) = KS(1);
KS(15) = KS(2);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(14);
c->H[w + 1] = KS(15);
KS(16) = p; }
KRET(KS(16));
break;
}
case 917: {
KPC = KFORK ? 997 : 998;
break;
}
case 998: {
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
c->kq = 1001; c->kqret = 1002; c->kqfb = 1004;
c->kqa[0] = KS(5);
KPC = PC_KQ;
break;
}
case 1004: {
{ KW nf = KPUSH(1002, 1001);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 1001; }
break;
}
case 1002: {
KS(1) = KRV;
KPC = 1003;
break;
}
case 1003: {
KS(6) = KS(0);
KS(7) = 2u;
KS(8) = KF_U32_dadd(c, KS(6), KS(7));
c->kq = 1001; c->kqret = 1005; c->kqfb = 1007;
c->kqa[0] = KS(8);
KPC = PC_KQ;
break;
}
case 1007: {
{ KW nf = KPUSH(1005, 1001);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 1001; }
break;
}
case 1005: {
KS(2) = KRV;
KPC = 1006;
break;
}
case 1006: {
KPC = 1000;
break;
}
case 1008: {
KS(2) = KS(0);
KS(3) = KF_U32_dinc(c, KS(2));
{ KW nf = KPUSH(1009, 1001);
KARG(nf, 0) = KS(3);
KFP = nf; KPC = 1001; }
break;
}
case 1009: {
KS(4) = KRV;
KRET(KS(4));
break;
}
case 1010: {
KS(2) = KS(0);
KS(3) = 2u;
KS(4) = KF_U32_dadd(c, KS(2), KS(3));
{ KW nf = KPUSH(1011, 1001);
KARG(nf, 0) = KS(4);
KFP = nf; KPC = 1001; }
break;
}
case 1011: {
KS(5) = KRV;
KRET(KS(5));
break;
}
case 997: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 1008; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(9) = p; }
KS(10) = KS(9);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 1010; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(11) = p; }
KS(12) = KS(11);
KS(3) = k_join_new(c, 2, 999);
if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(12), 0, 1012);
break;
}
case 1012: {
KS(13) = KRV;
k_arrive(c, KS(3), 1, KS(13));
break;
}
case 999: {
KS(1) = c->H[KS(3) + 4];
KS(2) = c->H[KS(3) + 5];
KPC = 1000;
break;
}
case 1000: {
KS(14) = KS(1);
KS(15) = KS(2);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(14);
c->H[w + 1] = KS(15);
KS(16) = p; }
KRET(KS(16));
break;
}
case 1001: {
KPC = KFORK ? 1072 : 1073;
break;
}
case 1073: {
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
c->kq = 1076; c->kqret = 1077; c->kqfb = 1079;
c->kqa[0] = KS(5);
KPC = PC_KQ;
break;
}
case 1079: {
{ KW nf = KPUSH(1077, 1076);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 1076; }
break;
}
case 1077: {
KS(1) = KRV;
KPC = 1078;
break;
}
case 1078: {
KS(6) = KS(0);
KS(7) = 2u;
KS(8) = KF_U32_dadd(c, KS(6), KS(7));
c->kq = 1076; c->kqret = 1080; c->kqfb = 1082;
c->kqa[0] = KS(8);
KPC = PC_KQ;
break;
}
case 1082: {
{ KW nf = KPUSH(1080, 1076);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 1076; }
break;
}
case 1080: {
KS(2) = KRV;
KPC = 1081;
break;
}
case 1081: {
KPC = 1075;
break;
}
case 1083: {
KS(2) = KS(0);
KS(3) = KF_U32_dinc(c, KS(2));
{ KW nf = KPUSH(1084, 1076);
KARG(nf, 0) = KS(3);
KFP = nf; KPC = 1076; }
break;
}
case 1084: {
KS(4) = KRV;
KRET(KS(4));
break;
}
case 1085: {
KS(2) = KS(0);
KS(3) = 2u;
KS(4) = KF_U32_dadd(c, KS(2), KS(3));
{ KW nf = KPUSH(1086, 1076);
KARG(nf, 0) = KS(4);
KFP = nf; KPC = 1076; }
break;
}
case 1086: {
KS(5) = KRV;
KRET(KS(5));
break;
}
case 1072: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 1083; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(9) = p; }
KS(10) = KS(9);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 1085; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(11) = p; }
KS(12) = KS(11);
KS(3) = k_join_new(c, 2, 1074);
if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(12), 0, 1087);
break;
}
case 1087: {
KS(13) = KRV;
k_arrive(c, KS(3), 1, KS(13));
break;
}
case 1074: {
KS(1) = c->H[KS(3) + 4];
KS(2) = c->H[KS(3) + 5];
KPC = 1075;
break;
}
case 1075: {
KS(14) = KS(1);
KS(15) = KS(2);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(14);
c->H[w + 1] = KS(15);
KS(16) = p; }
KRET(KS(16));
break;
}
case 1076: {
KPC = KFORK ? 1138 : 1139;
break;
}
case 1139: {
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
c->kq = 1142; c->kqret = 1143; c->kqfb = 1145;
c->kqa[0] = KS(5);
KPC = PC_KQ;
break;
}
case 1145: {
{ KW nf = KPUSH(1143, 1142);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 1142; }
break;
}
case 1143: {
KS(1) = KRV;
KPC = 1144;
break;
}
case 1144: {
KS(6) = KS(0);
KS(7) = 2u;
KS(8) = KF_U32_dadd(c, KS(6), KS(7));
c->kq = 1142; c->kqret = 1146; c->kqfb = 1148;
c->kqa[0] = KS(8);
KPC = PC_KQ;
break;
}
case 1148: {
{ KW nf = KPUSH(1146, 1142);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 1142; }
break;
}
case 1146: {
KS(2) = KRV;
KPC = 1147;
break;
}
case 1147: {
KPC = 1141;
break;
}
case 1149: {
KS(2) = KS(0);
KS(3) = KF_U32_dinc(c, KS(2));
{ KW nf = KPUSH(1150, 1142);
KARG(nf, 0) = KS(3);
KFP = nf; KPC = 1142; }
break;
}
case 1150: {
KS(4) = KRV;
KRET(KS(4));
break;
}
case 1151: {
KS(2) = KS(0);
KS(3) = 2u;
KS(4) = KF_U32_dadd(c, KS(2), KS(3));
{ KW nf = KPUSH(1152, 1142);
KARG(nf, 0) = KS(4);
KFP = nf; KPC = 1142; }
break;
}
case 1152: {
KS(5) = KRV;
KRET(KS(5));
break;
}
case 1138: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 1149; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(9) = p; }
KS(10) = KS(9);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 1151; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(11) = p; }
KS(12) = KS(11);
KS(3) = k_join_new(c, 2, 1140);
if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(12), 0, 1153);
break;
}
case 1153: {
KS(13) = KRV;
k_arrive(c, KS(3), 1, KS(13));
break;
}
case 1140: {
KS(1) = c->H[KS(3) + 4];
KS(2) = c->H[KS(3) + 5];
KPC = 1141;
break;
}
case 1141: {
KS(14) = KS(1);
KS(15) = KS(2);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(14);
c->H[w + 1] = KS(15);
KS(16) = p; }
KRET(KS(16));
break;
}
case 1142: {
KPC = KFORK ? 1195 : 1196;
break;
}
case 1196: {
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
c->kq = 1199; c->kqret = 1200; c->kqfb = 1202;
c->kqa[0] = KS(5);
KPC = PC_KQ;
break;
}
case 1202: {
{ KW nf = KPUSH(1200, 1199);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 1199; }
break;
}
case 1200: {
KS(1) = KRV;
KPC = 1201;
break;
}
case 1201: {
KS(6) = KS(0);
KS(7) = 2u;
KS(8) = KF_U32_dadd(c, KS(6), KS(7));
c->kq = 1199; c->kqret = 1203; c->kqfb = 1205;
c->kqa[0] = KS(8);
KPC = PC_KQ;
break;
}
case 1205: {
{ KW nf = KPUSH(1203, 1199);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 1199; }
break;
}
case 1203: {
KS(2) = KRV;
KPC = 1204;
break;
}
case 1204: {
KPC = 1198;
break;
}
case 1206: {
KS(2) = KS(0);
KS(3) = KF_U32_dinc(c, KS(2));
{ KW nf = KPUSH(1207, 1199);
KARG(nf, 0) = KS(3);
KFP = nf; KPC = 1199; }
break;
}
case 1207: {
KS(4) = KRV;
KRET(KS(4));
break;
}
case 1208: {
KS(2) = KS(0);
KS(3) = 2u;
KS(4) = KF_U32_dadd(c, KS(2), KS(3));
{ KW nf = KPUSH(1209, 1199);
KARG(nf, 0) = KS(4);
KFP = nf; KPC = 1199; }
break;
}
case 1209: {
KS(5) = KRV;
KRET(KS(5));
break;
}
case 1195: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 1206; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(9) = p; }
KS(10) = KS(9);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 1208; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(11) = p; }
KS(12) = KS(11);
KS(3) = k_join_new(c, 2, 1197);
if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(12), 0, 1210);
break;
}
case 1210: {
KS(13) = KRV;
k_arrive(c, KS(3), 1, KS(13));
break;
}
case 1197: {
KS(1) = c->H[KS(3) + 4];
KS(2) = c->H[KS(3) + 5];
KPC = 1198;
break;
}
case 1198: {
KS(14) = KS(1);
KS(15) = KS(2);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(14);
c->H[w + 1] = KS(15);
KS(16) = p; }
KRET(KS(16));
break;
}
case 1199: {
KPC = KFORK ? 1243 : 1244;
break;
}
case 1244: {
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
c->kq = 1247; c->kqret = 1248; c->kqfb = 1250;
c->kqa[0] = KS(5);
KPC = PC_KQ;
break;
}
case 1250: {
{ KW nf = KPUSH(1248, 1247);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 1247; }
break;
}
case 1248: {
KS(1) = KRV;
KPC = 1249;
break;
}
case 1249: {
KS(6) = KS(0);
KS(7) = 2u;
KS(8) = KF_U32_dadd(c, KS(6), KS(7));
c->kq = 1247; c->kqret = 1251; c->kqfb = 1253;
c->kqa[0] = KS(8);
KPC = PC_KQ;
break;
}
case 1253: {
{ KW nf = KPUSH(1251, 1247);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 1247; }
break;
}
case 1251: {
KS(2) = KRV;
KPC = 1252;
break;
}
case 1252: {
KPC = 1246;
break;
}
case 1254: {
KS(2) = KS(0);
KS(3) = KF_U32_dinc(c, KS(2));
{ KW nf = KPUSH(1255, 1247);
KARG(nf, 0) = KS(3);
KFP = nf; KPC = 1247; }
break;
}
case 1255: {
KS(4) = KRV;
KRET(KS(4));
break;
}
case 1256: {
KS(2) = KS(0);
KS(3) = 2u;
KS(4) = KF_U32_dadd(c, KS(2), KS(3));
{ KW nf = KPUSH(1257, 1247);
KARG(nf, 0) = KS(4);
KFP = nf; KPC = 1247; }
break;
}
case 1257: {
KS(5) = KRV;
KRET(KS(5));
break;
}
case 1243: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 1254; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(9) = p; }
KS(10) = KS(9);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 1256; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(11) = p; }
KS(12) = KS(11);
KS(3) = k_join_new(c, 2, 1245);
if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(12), 0, 1258);
break;
}
case 1258: {
KS(13) = KRV;
k_arrive(c, KS(3), 1, KS(13));
break;
}
case 1245: {
KS(1) = c->H[KS(3) + 4];
KS(2) = c->H[KS(3) + 5];
KPC = 1246;
break;
}
case 1246: {
KS(14) = KS(1);
KS(15) = KS(2);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(14);
c->H[w + 1] = KS(15);
KS(16) = p; }
KRET(KS(16));
break;
}
case 1247: {
KPC = KFORK ? 1282 : 1283;
break;
}
case 1283: {
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
c->kq = 1286; c->kqret = 1287; c->kqfb = 1289;
c->kqa[0] = KS(5);
KPC = PC_KQ;
break;
}
case 1289: {
{ KW nf = KPUSH(1287, 1286);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 1286; }
break;
}
case 1287: {
KS(1) = KRV;
KPC = 1288;
break;
}
case 1288: {
KS(6) = KS(0);
KS(7) = 2u;
KS(8) = KF_U32_dadd(c, KS(6), KS(7));
c->kq = 1286; c->kqret = 1290; c->kqfb = 1292;
c->kqa[0] = KS(8);
KPC = PC_KQ;
break;
}
case 1292: {
{ KW nf = KPUSH(1290, 1286);
KARG(nf, 0) = c->kqa[0];
KFP = nf; KPC = 1286; }
break;
}
case 1290: {
KS(2) = KRV;
KPC = 1291;
break;
}
case 1291: {
KPC = 1285;
break;
}
case 1293: {
KS(2) = KS(0);
KS(3) = KF_U32_dinc(c, KS(2));
{ KW nf = KPUSH(1294, 1286);
KARG(nf, 0) = KS(3);
KFP = nf; KPC = 1286; }
break;
}
case 1294: {
KS(4) = KRV;
KRET(KS(4));
break;
}
case 1295: {
KS(2) = KS(0);
KS(3) = 2u;
KS(4) = KF_U32_dadd(c, KS(2), KS(3));
{ KW nf = KPUSH(1296, 1286);
KARG(nf, 0) = KS(4);
KFP = nf; KPC = 1286; }
break;
}
case 1296: {
KS(5) = KRV;
KRET(KS(5));
break;
}
case 1282: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 1293; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(9) = p; }
KS(10) = KS(9);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 1295; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(11) = p; }
KS(12) = KS(11);
KS(3) = k_join_new(c, 2, 1284);
if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(12), 0, 1297);
break;
}
case 1297: {
KS(13) = KRV;
k_arrive(c, KS(3), 1, KS(13));
break;
}
case 1284: {
KS(1) = c->H[KS(3) + 4];
KS(2) = c->H[KS(3) + 5];
KPC = 1285;
break;
}
case 1285: {
KS(14) = KS(1);
KS(15) = KS(2);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(14);
c->H[w + 1] = KS(15);
KS(16) = p; }
KRET(KS(16));
break;
}
case 1286: {
KPC = KFORK ? 1312 : 1313;
break;
}
case 1313: {
KS(4) = KS(0);
KS(5) = KF_U32_dinc(c, KS(4));
KS(1) = KREG(((KX_make_x37s509762208x8001458(c, KS(5)))));
KS(6) = KS(0);
KS(7) = 2u;
KS(8) = KF_U32_dadd(c, KS(6), KS(7));
KS(2) = KREG(((KX_make_x37s509762208x8001458(c, KS(8)))));
KPC = 1315;
break;
}
case 1316: {
KS(2) = KS(0);
KS(3) = KF_U32_dinc(c, KS(2));
KRET(KREG(((KX_make_x37s509762208x8001458(c, KS(3))))));
break;
}
case 1317: {
KS(2) = KS(0);
KS(3) = 2u;
KS(4) = KF_U32_dadd(c, KS(2), KS(3));
KRET(KREG(((KX_make_x37s509762208x8001458(c, KS(4))))));
break;
}
case 1312: {
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 1316; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(9) = p; }
KS(10) = KS(9);
{ KW p = k_alloc(c, 4); KW w = KIX(c, p);
c->H[w] = KCLO | 1317; c->H[w + 1] = 2; c->H[w + 2] = 1;
c->H[w + 3] = KS(0);
KS(11) = p; }
KS(12) = KS(11);
KS(3) = k_join_new(c, 2, 1314);
if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);
c->dep += 1;
k_call_clo(c, KS(12), 0, 1318);
break;
}
case 1318: {
KS(13) = KRV;
k_arrive(c, KS(3), 1, KS(13));
break;
}
case 1314: {
KS(1) = c->H[KS(3) + 4];
KS(2) = c->H[KS(3) + 5];
KPC = 1315;
break;
}
case 1315: {
KS(14) = KS(1);
KS(15) = KS(2);
{ KW p = k_bnode(c, 2); KW w = KIX(c, p);
c->H[w + 0] = KS(14);
c->H[w + 1] = KS(15);
KS(16) = p; }
KRET(KS(16));
break;
}
default: {
k_fail(c, KE_PC);
break;
}
}
}

#include "gpuhost.h"

static const char K_SRC[] =
"#define K_NLABELS 1324\n"
"#define KL_make_x37s1860454509x8031249 1286\n"
"#define KL_make_x37s3867092194x8061040 1247\n"
"#define KL_make_x37s1586577935x8090831 1199\n"
"#define KL_make_x37s2405009636x8120622 1142\n"
"#define KL_make_x37s3239606481x8150413 1076\n"
"#define KL_make_x37s32637286x8180204 1001\n"
"#define KL_make_x37s1291691603x8209995 917\n"
"#define KL_make_x37s2491568216x8239786 824\n"
"#define KL_make_x37s3305376709x8269577 722\n"
"#define KL_make_x37s1953093269x247193397 611\n"
"#define KL_make_x37s4233607528x247223188 491\n"
"#define KL_make_x37s2689494263x247252979 362\n"
"#define KL_make_x37s675041226x247282770 224\n"
"#define KL_make_x37s3795296409x247312561 48\n"
"#define KLW_make 13\n"
"#define KL_make 12\n"
"#define KLW_rounds 11\n"
"#define KL_rounds 10\n"
"#define KLW_sum 9\n"
"#define KL_sum 8\n"
"KCONST KW K_FRAME[] = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 18u, 6u, 15u, 7u, 26u, 7u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 11u, 0u, 12u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 8u, 0u, 8u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 21u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 8u, 9u, 0u, 0u, 0u, 0u, 0u, 0u, 0};\n"
"\n"
"KINLINE KW k_frame_size(KW l) {\n"
"  return l < K_NLABELS ? K_FRAME[l] : 0;\n"
"}\n"
"\n"
"KCONST KW K_TREE_EMPTY[] = {0};\n"
"KCONST KW K_TREE_53[] = {0};\n"
"KCONST KW K_TREE_34[] = {2, 0, 2147483651};\n"
"KINLINE KCP KW *k_tree_schema(KW id) {\n"
"switch(id) {\n"
"case 53: return K_TREE_53;\n"
"case 34: return K_TREE_34;\n"
"default: return K_TREE_EMPTY;\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make(KTHR KCtx *c, KW p0, KW p1, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 32, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = p1;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 40: {\n"
"sp -= 1; KW x41_0 = KQ_ST(sp + 0); KW x41 = RV;\n"
"RV = ({ KAUTO x42_0 = x41_0; KAUTO x42_1 = x41; KW x42 = k_bnode(c, 2); c->H[KIX(c, x42) + 0] = x42_0; c->H[KIX(c, x42) + 1] = x42_1; x42; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 37: {\n"
"sp -= 2; KW x38_0 = KQ_ST(sp + 0); KW x38_1 = KQ_ST(sp + 1); KW x38 = RV;\n"
"{ KAUTO x39_0 = x38_0; KAUTO x39_1 = KF_U32_dadd(c, x38_1, 2u); if (sp + 2 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x38; KQ_ST(sp + 1) = 40; sp += 2;\n"
"A0 = x39_0; A1 = x39_1; pc = 32; break; }\n"
"break;\n"
"}\n"
"case 32: {\n"
"KW x33_0 = A0; KW x33_1 = A1; \n"
"K_TREE_MARK(34);\n"
"KAUTO x35 = x33_0;\n"
"if ((x35) == 0) {\n"
"RV = KLI(0, x33_1);\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"} else if (k_nge(c, x35, 1)) {\n"
"{ KAUTO x36_0 = ((x35) - 1); KAUTO x36_1 = KF_U32_dinc(c, x33_1); if (sp + 3 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = ((x35) - 1); KQ_ST(sp + 1) = x33_1; KQ_ST(sp + 2) = 37; sp += 3;\n"
"A0 = x36_0; A1 = x36_1; pc = 32; break; }\n"
"} else { k_fail(c, KE_MATCH); *ok = false; return 0; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"KINLINE KW KX_make_x37s509762208x8001458(KTHR KCtx *c, KU a0) {\n"
"for (;;) {\n"
"return KLI(0, a0);\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_rounds(KTHR KCtx *c, KW p0, KW p1, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 51, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = p1;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 81: {\n"
"KW x82_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x83 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x82_0))));\n"
"KW x84 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x82_0, 2u))));\n"
"RV = ({ KAUTO x85_0 = x83; KAUTO x85_1 = x84; KW x85 = k_bnode(c, 2); c->H[KIX(c, x85) + 0] = x85_0; c->H[KIX(c, x85) + 1] = x85_1; x85; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 90: {\n"
"sp -= 3; KW x91_0 = KQ_ST(sp + 0); KW x91 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x92_0 = x91_0; KAUTO x92_1 = x91; KW x92 = k_bnode(c, 2); c->H[KIX(c, x92) + 0] = x92_0; c->H[KIX(c, x92) + 1] = x92_1; x92; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 87: {\n"
"sp -= 3; KW x88_0 = KQ_ST(sp + 0); KW x88 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x89_0 = KF_U32_dadd(c, x88_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x88; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 90; sp += 4;\n"
"A0 = x89_0; pc = 81; break; }\n"
"break;\n"
"}\n"
"case 79: {\n"
"KW x80_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x86_0 = KF_U32_dinc(c, x80_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x80_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 87; sp += 4;\n"
"A0 = x86_0; pc = 81; break; }\n"
"break;\n"
"}\n"
"case 97: {\n"
"sp -= 3; KW x98_0 = KQ_ST(sp + 0); KW x98 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x99_0 = x98_0; KAUTO x99_1 = x98; KW x99 = k_bnode(c, 2); c->H[KIX(c, x99) + 0] = x99_0; c->H[KIX(c, x99) + 1] = x99_1; x99; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 94: {\n"
"sp -= 3; KW x95_0 = KQ_ST(sp + 0); KW x95 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x96_0 = KF_U32_dadd(c, x95_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x95; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 97; sp += 4;\n"
"A0 = x96_0; pc = 79; break; }\n"
"break;\n"
"}\n"
"case 77: {\n"
"KW x78_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x93_0 = KF_U32_dinc(c, x78_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x78_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 94; sp += 4;\n"
"A0 = x93_0; pc = 79; break; }\n"
"break;\n"
"}\n"
"case 104: {\n"
"sp -= 3; KW x105_0 = KQ_ST(sp + 0); KW x105 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x106_0 = x105_0; KAUTO x106_1 = x105; KW x106 = k_bnode(c, 2); c->H[KIX(c, x106) + 0] = x106_0; c->H[KIX(c, x106) + 1] = x106_1; x106; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 101: {\n"
"sp -= 3; KW x102_0 = KQ_ST(sp + 0); KW x102 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x103_0 = KF_U32_dadd(c, x102_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x102; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 104; sp += 4;\n"
"A0 = x103_0; pc = 77; break; }\n"
"break;\n"
"}\n"
"case 75: {\n"
"KW x76_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x100_0 = KF_U32_dinc(c, x76_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x76_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 101; sp += 4;\n"
"A0 = x100_0; pc = 77; break; }\n"
"break;\n"
"}\n"
"case 111: {\n"
"sp -= 3; KW x112_0 = KQ_ST(sp + 0); KW x112 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x113_0 = x112_0; KAUTO x113_1 = x112; KW x113 = k_bnode(c, 2); c->H[KIX(c, x113) + 0] = x113_0; c->H[KIX(c, x113) + 1] = x113_1; x113; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 108: {\n"
"sp -= 3; KW x109_0 = KQ_ST(sp + 0); KW x109 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x110_0 = KF_U32_dadd(c, x109_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x109; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 111; sp += 4;\n"
"A0 = x110_0; pc = 75; break; }\n"
"break;\n"
"}\n"
"case 73: {\n"
"KW x74_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x107_0 = KF_U32_dinc(c, x74_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x74_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 108; sp += 4;\n"
"A0 = x107_0; pc = 75; break; }\n"
"break;\n"
"}\n"
"case 118: {\n"
"sp -= 3; KW x119_0 = KQ_ST(sp + 0); KW x119 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x120_0 = x119_0; KAUTO x120_1 = x119; KW x120 = k_bnode(c, 2); c->H[KIX(c, x120) + 0] = x120_0; c->H[KIX(c, x120) + 1] = x120_1; x120; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 115: {\n"
"sp -= 3; KW x116_0 = KQ_ST(sp + 0); KW x116 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x117_0 = KF_U32_dadd(c, x116_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x116; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 118; sp += 4;\n"
"A0 = x117_0; pc = 73; break; }\n"
"break;\n"
"}\n"
"case 71: {\n"
"KW x72_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x114_0 = KF_U32_dinc(c, x72_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x72_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 115; sp += 4;\n"
"A0 = x114_0; pc = 73; break; }\n"
"break;\n"
"}\n"
"case 125: {\n"
"sp -= 3; KW x126_0 = KQ_ST(sp + 0); KW x126 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x127_0 = x126_0; KAUTO x127_1 = x126; KW x127 = k_bnode(c, 2); c->H[KIX(c, x127) + 0] = x127_0; c->H[KIX(c, x127) + 1] = x127_1; x127; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 122: {\n"
"sp -= 3; KW x123_0 = KQ_ST(sp + 0); KW x123 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x124_0 = KF_U32_dadd(c, x123_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x123; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 125; sp += 4;\n"
"A0 = x124_0; pc = 71; break; }\n"
"break;\n"
"}\n"
"case 69: {\n"
"KW x70_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x121_0 = KF_U32_dinc(c, x70_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x70_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 122; sp += 4;\n"
"A0 = x121_0; pc = 71; break; }\n"
"break;\n"
"}\n"
"case 132: {\n"
"sp -= 3; KW x133_0 = KQ_ST(sp + 0); KW x133 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x134_0 = x133_0; KAUTO x134_1 = x133; KW x134 = k_bnode(c, 2); c->H[KIX(c, x134) + 0] = x134_0; c->H[KIX(c, x134) + 1] = x134_1; x134; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 129: {\n"
"sp -= 3; KW x130_0 = KQ_ST(sp + 0); KW x130 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x131_0 = KF_U32_dadd(c, x130_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x130; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 132; sp += 4;\n"
"A0 = x131_0; pc = 69; break; }\n"
"break;\n"
"}\n"
"case 67: {\n"
"KW x68_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x128_0 = KF_U32_dinc(c, x68_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x68_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 129; sp += 4;\n"
"A0 = x128_0; pc = 69; break; }\n"
"break;\n"
"}\n"
"case 139: {\n"
"sp -= 3; KW x140_0 = KQ_ST(sp + 0); KW x140 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x141_0 = x140_0; KAUTO x141_1 = x140; KW x141 = k_bnode(c, 2); c->H[KIX(c, x141) + 0] = x141_0; c->H[KIX(c, x141) + 1] = x141_1; x141; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 136: {\n"
"sp -= 3; KW x137_0 = KQ_ST(sp + 0); KW x137 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x138_0 = KF_U32_dadd(c, x137_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x137; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 139; sp += 4;\n"
"A0 = x138_0; pc = 67; break; }\n"
"break;\n"
"}\n"
"case 65: {\n"
"KW x66_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x135_0 = KF_U32_dinc(c, x66_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x66_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 136; sp += 4;\n"
"A0 = x135_0; pc = 67; break; }\n"
"break;\n"
"}\n"
"case 146: {\n"
"sp -= 3; KW x147_0 = KQ_ST(sp + 0); KW x147 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x148_0 = x147_0; KAUTO x148_1 = x147; KW x148 = k_bnode(c, 2); c->H[KIX(c, x148) + 0] = x148_0; c->H[KIX(c, x148) + 1] = x148_1; x148; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 143: {\n"
"sp -= 3; KW x144_0 = KQ_ST(sp + 0); KW x144 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x145_0 = KF_U32_dadd(c, x144_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x144; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 146; sp += 4;\n"
"A0 = x145_0; pc = 65; break; }\n"
"break;\n"
"}\n"
"case 63: {\n"
"KW x64_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x142_0 = KF_U32_dinc(c, x64_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x64_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 143; sp += 4;\n"
"A0 = x142_0; pc = 65; break; }\n"
"break;\n"
"}\n"
"case 153: {\n"
"sp -= 3; KW x154_0 = KQ_ST(sp + 0); KW x154 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x155_0 = x154_0; KAUTO x155_1 = x154; KW x155 = k_bnode(c, 2); c->H[KIX(c, x155) + 0] = x155_0; c->H[KIX(c, x155) + 1] = x155_1; x155; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 150: {\n"
"sp -= 3; KW x151_0 = KQ_ST(sp + 0); KW x151 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x152_0 = KF_U32_dadd(c, x151_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x151; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 153; sp += 4;\n"
"A0 = x152_0; pc = 63; break; }\n"
"break;\n"
"}\n"
"case 61: {\n"
"KW x62_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x149_0 = KF_U32_dinc(c, x62_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x62_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 150; sp += 4;\n"
"A0 = x149_0; pc = 63; break; }\n"
"break;\n"
"}\n"
"case 160: {\n"
"sp -= 3; KW x161_0 = KQ_ST(sp + 0); KW x161 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x162_0 = x161_0; KAUTO x162_1 = x161; KW x162 = k_bnode(c, 2); c->H[KIX(c, x162) + 0] = x162_0; c->H[KIX(c, x162) + 1] = x162_1; x162; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 157: {\n"
"sp -= 3; KW x158_0 = KQ_ST(sp + 0); KW x158 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x159_0 = KF_U32_dadd(c, x158_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x158; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 160; sp += 4;\n"
"A0 = x159_0; pc = 61; break; }\n"
"break;\n"
"}\n"
"case 59: {\n"
"KW x60_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x156_0 = KF_U32_dinc(c, x60_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x60_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 157; sp += 4;\n"
"A0 = x156_0; pc = 61; break; }\n"
"break;\n"
"}\n"
"case 167: {\n"
"sp -= 3; KW x168_0 = KQ_ST(sp + 0); KW x168 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x169_0 = x168_0; KAUTO x169_1 = x168; KW x169 = k_bnode(c, 2); c->H[KIX(c, x169) + 0] = x169_0; c->H[KIX(c, x169) + 1] = x169_1; x169; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 164: {\n"
"sp -= 3; KW x165_0 = KQ_ST(sp + 0); KW x165 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x166_0 = KF_U32_dadd(c, x165_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x165; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 167; sp += 4;\n"
"A0 = x166_0; pc = 59; break; }\n"
"break;\n"
"}\n"
"case 57: {\n"
"KW x58_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x163_0 = KF_U32_dinc(c, x58_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x58_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 164; sp += 4;\n"
"A0 = x163_0; pc = 59; break; }\n"
"break;\n"
"}\n"
"case 174: {\n"
"sp -= 3; KW x175_0 = KQ_ST(sp + 0); KW x175 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x176_0 = x175_0; KAUTO x176_1 = x175; KW x176 = k_bnode(c, 2); c->H[KIX(c, x176) + 0] = x176_0; c->H[KIX(c, x176) + 1] = x176_1; x176; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 171: {\n"
"sp -= 3; KW x172_0 = KQ_ST(sp + 0); KW x172 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x173_0 = KF_U32_dadd(c, x172_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x172; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 174; sp += 4;\n"
"A0 = x173_0; pc = 57; break; }\n"
"break;\n"
"}\n"
"case 55: {\n"
"KW x56_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x170_0 = KF_U32_dinc(c, x56_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x56_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 171; sp += 4;\n"
"A0 = x170_0; pc = 57; break; }\n"
"break;\n"
"}\n"
"case 187: {\n"
"sp -= 1; KW x188_0 = KQ_ST(sp + 0); KW x188 = RV;\n"
"RV = KF_U32_dadd(c, x188_0, x188);\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 184: {\n"
"sp -= 1; KW x185_0 = KQ_ST(sp + 0); KW x185 = RV;\n"
"{ KAUTO x186_0 = x185_0; if (sp + 2 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x185; KQ_ST(sp + 1) = 187; sp += 2;\n"
"A0 = x186_0; pc = 180; break; }\n"
"break;\n"
"}\n"
"case 180: {\n"
"KW x181_0 = A0; \n"
"KAUTO x182 = x181_0;\n"
"if (KIS_LI(x182, 0)) {\n"
"RV = KLI_V(x182);\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"} else if (!((x182) & 1)) {\n"
"{ KAUTO x183_0 = KFLB(x182, 0); if (sp + 2 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = KFLB(x182, 1); KQ_ST(sp + 1) = 184; sp += 2;\n"
"A0 = x183_0; pc = 180; break; }\n"
"} else { k_fail(c, KE_MATCH); *ok = false; return 0; }\n"
"break;\n"
"}\n"
"case 190: {\n"
"sp -= 2; KW x191_0 = KQ_ST(sp + 0); KW x191_1 = KQ_ST(sp + 1); KW x191 = RV;\n"
"{ KAUTO x192_0 = x191_0; KAUTO x192_1 = KF_U32_dadd(c, x191_1, x191); A0 = x192_0; A1 = x192_1; if (c->err) { *ok = false; return 0; }\n"
"pc = 51; break; }\n"
"break;\n"
"}\n"
"case 178: {\n"
"sp -= 4; KW x179_0 = KQ_ST(sp + 0); KW x179_1 = KQ_ST(sp + 1); KW x179 = k_region(c, KQ_ST(sp + 2), KQ_ST(sp + 3), RV);\n"
"{ KAUTO x189_0 = x179; if (sp + 3 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x179_0; KQ_ST(sp + 1) = x179_1; KQ_ST(sp + 2) = 190; sp += 3;\n"
"A0 = x189_0; pc = 180; break; }\n"
"break;\n"
"}\n"
"case 51: {\n"
"KW x52_0 = A0; KW x52_1 = A1; \n"
"K_TREE_MARK(53);\n"
"KAUTO x54 = x52_0;\n"
"if ((x54) == 0) {\n"
"RV = x52_1;\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"} else if (k_nge(c, x54, 1)) {\n"
"{ KAUTO x177_0 = 1u; if (sp + 5 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = ((x54) - 1); KQ_ST(sp + 1) = x52_1; KQ_ST(sp + 2) = c->hp; KQ_ST(sp + 3) = c->he; KQ_ST(sp + 4) = 178; sp += 5;\n"
"A0 = x177_0; pc = 55; break; }\n"
"} else { k_fail(c, KE_MATCH); *ok = false; return 0; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_sum(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 211, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 218: {\n"
"sp -= 1; KW x219_0 = KQ_ST(sp + 0); KW x219 = RV;\n"
"RV = KF_U32_dadd(c, x219_0, x219);\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 215: {\n"
"sp -= 1; KW x216_0 = KQ_ST(sp + 0); KW x216 = RV;\n"
"{ KAUTO x217_0 = x216_0; if (sp + 2 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x216; KQ_ST(sp + 1) = 218; sp += 2;\n"
"A0 = x217_0; pc = 211; break; }\n"
"break;\n"
"}\n"
"case 211: {\n"
"KW x212_0 = A0; \n"
"KAUTO x213 = x212_0;\n"
"if (KIS_LI(x213, 0)) {\n"
"RV = KLI_V(x213);\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"} else if (!((x213) & 1)) {\n"
"{ KAUTO x214_0 = KFLB(x213, 0); if (sp + 2 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = KFLB(x213, 1); KQ_ST(sp + 1) = 215; sp += 2;\n"
"A0 = x214_0; pc = 211; break; }\n"
"} else { k_fail(c, KE_MATCH); *ok = false; return 0; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make_x37s3795296409x247312561(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 236, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 262: {\n"
"KW x263_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x264 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x263_0))));\n"
"KW x265 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x263_0, 2u))));\n"
"RV = ({ KAUTO x266_0 = x264; KAUTO x266_1 = x265; KW x266 = k_bnode(c, 2); c->H[KIX(c, x266) + 0] = x266_0; c->H[KIX(c, x266) + 1] = x266_1; x266; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 271: {\n"
"sp -= 3; KW x272_0 = KQ_ST(sp + 0); KW x272 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x273_0 = x272_0; KAUTO x273_1 = x272; KW x273 = k_bnode(c, 2); c->H[KIX(c, x273) + 0] = x273_0; c->H[KIX(c, x273) + 1] = x273_1; x273; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 268: {\n"
"sp -= 3; KW x269_0 = KQ_ST(sp + 0); KW x269 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x270_0 = KF_U32_dadd(c, x269_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x269; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 271; sp += 4;\n"
"A0 = x270_0; pc = 262; break; }\n"
"break;\n"
"}\n"
"case 260: {\n"
"KW x261_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x267_0 = KF_U32_dinc(c, x261_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x261_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 268; sp += 4;\n"
"A0 = x267_0; pc = 262; break; }\n"
"break;\n"
"}\n"
"case 278: {\n"
"sp -= 3; KW x279_0 = KQ_ST(sp + 0); KW x279 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x280_0 = x279_0; KAUTO x280_1 = x279; KW x280 = k_bnode(c, 2); c->H[KIX(c, x280) + 0] = x280_0; c->H[KIX(c, x280) + 1] = x280_1; x280; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 275: {\n"
"sp -= 3; KW x276_0 = KQ_ST(sp + 0); KW x276 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x277_0 = KF_U32_dadd(c, x276_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x276; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 278; sp += 4;\n"
"A0 = x277_0; pc = 260; break; }\n"
"break;\n"
"}\n"
"case 258: {\n"
"KW x259_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x274_0 = KF_U32_dinc(c, x259_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x259_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 275; sp += 4;\n"
"A0 = x274_0; pc = 260; break; }\n"
"break;\n"
"}\n"
"case 285: {\n"
"sp -= 3; KW x286_0 = KQ_ST(sp + 0); KW x286 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x287_0 = x286_0; KAUTO x287_1 = x286; KW x287 = k_bnode(c, 2); c->H[KIX(c, x287) + 0] = x287_0; c->H[KIX(c, x287) + 1] = x287_1; x287; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 282: {\n"
"sp -= 3; KW x283_0 = KQ_ST(sp + 0); KW x283 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x284_0 = KF_U32_dadd(c, x283_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x283; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 285; sp += 4;\n"
"A0 = x284_0; pc = 258; break; }\n"
"break;\n"
"}\n"
"case 256: {\n"
"KW x257_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x281_0 = KF_U32_dinc(c, x257_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x257_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 282; sp += 4;\n"
"A0 = x281_0; pc = 258; break; }\n"
"break;\n"
"}\n"
"case 292: {\n"
"sp -= 3; KW x293_0 = KQ_ST(sp + 0); KW x293 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x294_0 = x293_0; KAUTO x294_1 = x293; KW x294 = k_bnode(c, 2); c->H[KIX(c, x294) + 0] = x294_0; c->H[KIX(c, x294) + 1] = x294_1; x294; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 289: {\n"
"sp -= 3; KW x290_0 = KQ_ST(sp + 0); KW x290 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x291_0 = KF_U32_dadd(c, x290_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x290; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 292; sp += 4;\n"
"A0 = x291_0; pc = 256; break; }\n"
"break;\n"
"}\n"
"case 254: {\n"
"KW x255_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x288_0 = KF_U32_dinc(c, x255_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x255_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 289; sp += 4;\n"
"A0 = x288_0; pc = 256; break; }\n"
"break;\n"
"}\n"
"case 299: {\n"
"sp -= 3; KW x300_0 = KQ_ST(sp + 0); KW x300 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x301_0 = x300_0; KAUTO x301_1 = x300; KW x301 = k_bnode(c, 2); c->H[KIX(c, x301) + 0] = x301_0; c->H[KIX(c, x301) + 1] = x301_1; x301; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 296: {\n"
"sp -= 3; KW x297_0 = KQ_ST(sp + 0); KW x297 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x298_0 = KF_U32_dadd(c, x297_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x297; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 299; sp += 4;\n"
"A0 = x298_0; pc = 254; break; }\n"
"break;\n"
"}\n"
"case 252: {\n"
"KW x253_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x295_0 = KF_U32_dinc(c, x253_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x253_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 296; sp += 4;\n"
"A0 = x295_0; pc = 254; break; }\n"
"break;\n"
"}\n"
"case 306: {\n"
"sp -= 3; KW x307_0 = KQ_ST(sp + 0); KW x307 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x308_0 = x307_0; KAUTO x308_1 = x307; KW x308 = k_bnode(c, 2); c->H[KIX(c, x308) + 0] = x308_0; c->H[KIX(c, x308) + 1] = x308_1; x308; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 303: {\n"
"sp -= 3; KW x304_0 = KQ_ST(sp + 0); KW x304 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x305_0 = KF_U32_dadd(c, x304_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x304; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 306; sp += 4;\n"
"A0 = x305_0; pc = 252; break; }\n"
"break;\n"
"}\n"
"case 250: {\n"
"KW x251_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x302_0 = KF_U32_dinc(c, x251_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x251_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 303; sp += 4;\n"
"A0 = x302_0; pc = 252; break; }\n"
"break;\n"
"}\n"
"case 313: {\n"
"sp -= 3; KW x314_0 = KQ_ST(sp + 0); KW x314 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x315_0 = x314_0; KAUTO x315_1 = x314; KW x315 = k_bnode(c, 2); c->H[KIX(c, x315) + 0] = x315_0; c->H[KIX(c, x315) + 1] = x315_1; x315; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 310: {\n"
"sp -= 3; KW x311_0 = KQ_ST(sp + 0); KW x311 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x312_0 = KF_U32_dadd(c, x311_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x311; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 313; sp += 4;\n"
"A0 = x312_0; pc = 250; break; }\n"
"break;\n"
"}\n"
"case 248: {\n"
"KW x249_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x309_0 = KF_U32_dinc(c, x249_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x249_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 310; sp += 4;\n"
"A0 = x309_0; pc = 250; break; }\n"
"break;\n"
"}\n"
"case 320: {\n"
"sp -= 3; KW x321_0 = KQ_ST(sp + 0); KW x321 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x322_0 = x321_0; KAUTO x322_1 = x321; KW x322 = k_bnode(c, 2); c->H[KIX(c, x322) + 0] = x322_0; c->H[KIX(c, x322) + 1] = x322_1; x322; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 317: {\n"
"sp -= 3; KW x318_0 = KQ_ST(sp + 0); KW x318 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x319_0 = KF_U32_dadd(c, x318_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x318; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 320; sp += 4;\n"
"A0 = x319_0; pc = 248; break; }\n"
"break;\n"
"}\n"
"case 246: {\n"
"KW x247_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x316_0 = KF_U32_dinc(c, x247_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x247_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 317; sp += 4;\n"
"A0 = x316_0; pc = 248; break; }\n"
"break;\n"
"}\n"
"case 327: {\n"
"sp -= 3; KW x328_0 = KQ_ST(sp + 0); KW x328 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x329_0 = x328_0; KAUTO x329_1 = x328; KW x329 = k_bnode(c, 2); c->H[KIX(c, x329) + 0] = x329_0; c->H[KIX(c, x329) + 1] = x329_1; x329; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 324: {\n"
"sp -= 3; KW x325_0 = KQ_ST(sp + 0); KW x325 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x326_0 = KF_U32_dadd(c, x325_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x325; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 327; sp += 4;\n"
"A0 = x326_0; pc = 246; break; }\n"
"break;\n"
"}\n"
"case 244: {\n"
"KW x245_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x323_0 = KF_U32_dinc(c, x245_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x245_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 324; sp += 4;\n"
"A0 = x323_0; pc = 246; break; }\n"
"break;\n"
"}\n"
"case 334: {\n"
"sp -= 3; KW x335_0 = KQ_ST(sp + 0); KW x335 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x336_0 = x335_0; KAUTO x336_1 = x335; KW x336 = k_bnode(c, 2); c->H[KIX(c, x336) + 0] = x336_0; c->H[KIX(c, x336) + 1] = x336_1; x336; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 331: {\n"
"sp -= 3; KW x332_0 = KQ_ST(sp + 0); KW x332 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x333_0 = KF_U32_dadd(c, x332_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x332; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 334; sp += 4;\n"
"A0 = x333_0; pc = 244; break; }\n"
"break;\n"
"}\n"
"case 242: {\n"
"KW x243_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x330_0 = KF_U32_dinc(c, x243_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x243_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 331; sp += 4;\n"
"A0 = x330_0; pc = 244; break; }\n"
"break;\n"
"}\n"
"case 341: {\n"
"sp -= 3; KW x342_0 = KQ_ST(sp + 0); KW x342 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x343_0 = x342_0; KAUTO x343_1 = x342; KW x343 = k_bnode(c, 2); c->H[KIX(c, x343) + 0] = x343_0; c->H[KIX(c, x343) + 1] = x343_1; x343; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 338: {\n"
"sp -= 3; KW x339_0 = KQ_ST(sp + 0); KW x339 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x340_0 = KF_U32_dadd(c, x339_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x339; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 341; sp += 4;\n"
"A0 = x340_0; pc = 242; break; }\n"
"break;\n"
"}\n"
"case 240: {\n"
"KW x241_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x337_0 = KF_U32_dinc(c, x241_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x241_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 338; sp += 4;\n"
"A0 = x337_0; pc = 242; break; }\n"
"break;\n"
"}\n"
"case 348: {\n"
"sp -= 3; KW x349_0 = KQ_ST(sp + 0); KW x349 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x350_0 = x349_0; KAUTO x350_1 = x349; KW x350 = k_bnode(c, 2); c->H[KIX(c, x350) + 0] = x350_0; c->H[KIX(c, x350) + 1] = x350_1; x350; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 345: {\n"
"sp -= 3; KW x346_0 = KQ_ST(sp + 0); KW x346 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x347_0 = KF_U32_dadd(c, x346_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x346; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 348; sp += 4;\n"
"A0 = x347_0; pc = 240; break; }\n"
"break;\n"
"}\n"
"case 238: {\n"
"KW x239_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x344_0 = KF_U32_dinc(c, x239_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x239_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 345; sp += 4;\n"
"A0 = x344_0; pc = 240; break; }\n"
"break;\n"
"}\n"
"case 355: {\n"
"sp -= 3; KW x356_0 = KQ_ST(sp + 0); KW x356 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x357_0 = x356_0; KAUTO x357_1 = x356; KW x357 = k_bnode(c, 2); c->H[KIX(c, x357) + 0] = x357_0; c->H[KIX(c, x357) + 1] = x357_1; x357; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 352: {\n"
"sp -= 3; KW x353_0 = KQ_ST(sp + 0); KW x353 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x354_0 = KF_U32_dadd(c, x353_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x353; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 355; sp += 4;\n"
"A0 = x354_0; pc = 238; break; }\n"
"break;\n"
"}\n"
"case 236: {\n"
"KW x237_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x351_0 = KF_U32_dinc(c, x237_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x237_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 352; sp += 4;\n"
"A0 = x351_0; pc = 238; break; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make_x37s675041226x247282770(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 374, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 398: {\n"
"KW x399_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x400 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x399_0))));\n"
"KW x401 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x399_0, 2u))));\n"
"RV = ({ KAUTO x402_0 = x400; KAUTO x402_1 = x401; KW x402 = k_bnode(c, 2); c->H[KIX(c, x402) + 0] = x402_0; c->H[KIX(c, x402) + 1] = x402_1; x402; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 407: {\n"
"sp -= 3; KW x408_0 = KQ_ST(sp + 0); KW x408 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x409_0 = x408_0; KAUTO x409_1 = x408; KW x409 = k_bnode(c, 2); c->H[KIX(c, x409) + 0] = x409_0; c->H[KIX(c, x409) + 1] = x409_1; x409; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 404: {\n"
"sp -= 3; KW x405_0 = KQ_ST(sp + 0); KW x405 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x406_0 = KF_U32_dadd(c, x405_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x405; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 407; sp += 4;\n"
"A0 = x406_0; pc = 398; break; }\n"
"break;\n"
"}\n"
"case 396: {\n"
"KW x397_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x403_0 = KF_U32_dinc(c, x397_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x397_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 404; sp += 4;\n"
"A0 = x403_0; pc = 398; break; }\n"
"break;\n"
"}\n"
"case 414: {\n"
"sp -= 3; KW x415_0 = KQ_ST(sp + 0); KW x415 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x416_0 = x415_0; KAUTO x416_1 = x415; KW x416 = k_bnode(c, 2); c->H[KIX(c, x416) + 0] = x416_0; c->H[KIX(c, x416) + 1] = x416_1; x416; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 411: {\n"
"sp -= 3; KW x412_0 = KQ_ST(sp + 0); KW x412 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x413_0 = KF_U32_dadd(c, x412_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x412; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 414; sp += 4;\n"
"A0 = x413_0; pc = 396; break; }\n"
"break;\n"
"}\n"
"case 394: {\n"
"KW x395_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x410_0 = KF_U32_dinc(c, x395_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x395_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 411; sp += 4;\n"
"A0 = x410_0; pc = 396; break; }\n"
"break;\n"
"}\n"
"case 421: {\n"
"sp -= 3; KW x422_0 = KQ_ST(sp + 0); KW x422 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x423_0 = x422_0; KAUTO x423_1 = x422; KW x423 = k_bnode(c, 2); c->H[KIX(c, x423) + 0] = x423_0; c->H[KIX(c, x423) + 1] = x423_1; x423; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 418: {\n"
"sp -= 3; KW x419_0 = KQ_ST(sp + 0); KW x419 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x420_0 = KF_U32_dadd(c, x419_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x419; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 421; sp += 4;\n"
"A0 = x420_0; pc = 394; break; }\n"
"break;\n"
"}\n"
"case 392: {\n"
"KW x393_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x417_0 = KF_U32_dinc(c, x393_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x393_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 418; sp += 4;\n"
"A0 = x417_0; pc = 394; break; }\n"
"break;\n"
"}\n"
"case 428: {\n"
"sp -= 3; KW x429_0 = KQ_ST(sp + 0); KW x429 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x430_0 = x429_0; KAUTO x430_1 = x429; KW x430 = k_bnode(c, 2); c->H[KIX(c, x430) + 0] = x430_0; c->H[KIX(c, x430) + 1] = x430_1; x430; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 425: {\n"
"sp -= 3; KW x426_0 = KQ_ST(sp + 0); KW x426 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x427_0 = KF_U32_dadd(c, x426_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x426; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 428; sp += 4;\n"
"A0 = x427_0; pc = 392; break; }\n"
"break;\n"
"}\n"
"case 390: {\n"
"KW x391_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x424_0 = KF_U32_dinc(c, x391_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x391_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 425; sp += 4;\n"
"A0 = x424_0; pc = 392; break; }\n"
"break;\n"
"}\n"
"case 435: {\n"
"sp -= 3; KW x436_0 = KQ_ST(sp + 0); KW x436 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x437_0 = x436_0; KAUTO x437_1 = x436; KW x437 = k_bnode(c, 2); c->H[KIX(c, x437) + 0] = x437_0; c->H[KIX(c, x437) + 1] = x437_1; x437; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 432: {\n"
"sp -= 3; KW x433_0 = KQ_ST(sp + 0); KW x433 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x434_0 = KF_U32_dadd(c, x433_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x433; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 435; sp += 4;\n"
"A0 = x434_0; pc = 390; break; }\n"
"break;\n"
"}\n"
"case 388: {\n"
"KW x389_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x431_0 = KF_U32_dinc(c, x389_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x389_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 432; sp += 4;\n"
"A0 = x431_0; pc = 390; break; }\n"
"break;\n"
"}\n"
"case 442: {\n"
"sp -= 3; KW x443_0 = KQ_ST(sp + 0); KW x443 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x444_0 = x443_0; KAUTO x444_1 = x443; KW x444 = k_bnode(c, 2); c->H[KIX(c, x444) + 0] = x444_0; c->H[KIX(c, x444) + 1] = x444_1; x444; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 439: {\n"
"sp -= 3; KW x440_0 = KQ_ST(sp + 0); KW x440 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x441_0 = KF_U32_dadd(c, x440_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x440; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 442; sp += 4;\n"
"A0 = x441_0; pc = 388; break; }\n"
"break;\n"
"}\n"
"case 386: {\n"
"KW x387_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x438_0 = KF_U32_dinc(c, x387_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x387_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 439; sp += 4;\n"
"A0 = x438_0; pc = 388; break; }\n"
"break;\n"
"}\n"
"case 449: {\n"
"sp -= 3; KW x450_0 = KQ_ST(sp + 0); KW x450 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x451_0 = x450_0; KAUTO x451_1 = x450; KW x451 = k_bnode(c, 2); c->H[KIX(c, x451) + 0] = x451_0; c->H[KIX(c, x451) + 1] = x451_1; x451; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 446: {\n"
"sp -= 3; KW x447_0 = KQ_ST(sp + 0); KW x447 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x448_0 = KF_U32_dadd(c, x447_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x447; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 449; sp += 4;\n"
"A0 = x448_0; pc = 386; break; }\n"
"break;\n"
"}\n"
"case 384: {\n"
"KW x385_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x445_0 = KF_U32_dinc(c, x385_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x385_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 446; sp += 4;\n"
"A0 = x445_0; pc = 386; break; }\n"
"break;\n"
"}\n"
"case 456: {\n"
"sp -= 3; KW x457_0 = KQ_ST(sp + 0); KW x457 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x458_0 = x457_0; KAUTO x458_1 = x457; KW x458 = k_bnode(c, 2); c->H[KIX(c, x458) + 0] = x458_0; c->H[KIX(c, x458) + 1] = x458_1; x458; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 453: {\n"
"sp -= 3; KW x454_0 = KQ_ST(sp + 0); KW x454 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x455_0 = KF_U32_dadd(c, x454_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x454; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 456; sp += 4;\n"
"A0 = x455_0; pc = 384; break; }\n"
"break;\n"
"}\n"
"case 382: {\n"
"KW x383_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x452_0 = KF_U32_dinc(c, x383_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x383_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 453; sp += 4;\n"
"A0 = x452_0; pc = 384; break; }\n"
"break;\n"
"}\n"
"case 463: {\n"
"sp -= 3; KW x464_0 = KQ_ST(sp + 0); KW x464 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x465_0 = x464_0; KAUTO x465_1 = x464; KW x465 = k_bnode(c, 2); c->H[KIX(c, x465) + 0] = x465_0; c->H[KIX(c, x465) + 1] = x465_1; x465; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 460: {\n"
"sp -= 3; KW x461_0 = KQ_ST(sp + 0); KW x461 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x462_0 = KF_U32_dadd(c, x461_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x461; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 463; sp += 4;\n"
"A0 = x462_0; pc = 382; break; }\n"
"break;\n"
"}\n"
"case 380: {\n"
"KW x381_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x459_0 = KF_U32_dinc(c, x381_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x381_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 460; sp += 4;\n"
"A0 = x459_0; pc = 382; break; }\n"
"break;\n"
"}\n"
"case 470: {\n"
"sp -= 3; KW x471_0 = KQ_ST(sp + 0); KW x471 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x472_0 = x471_0; KAUTO x472_1 = x471; KW x472 = k_bnode(c, 2); c->H[KIX(c, x472) + 0] = x472_0; c->H[KIX(c, x472) + 1] = x472_1; x472; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 467: {\n"
"sp -= 3; KW x468_0 = KQ_ST(sp + 0); KW x468 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x469_0 = KF_U32_dadd(c, x468_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x468; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 470; sp += 4;\n"
"A0 = x469_0; pc = 380; break; }\n"
"break;\n"
"}\n"
"case 378: {\n"
"KW x379_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x466_0 = KF_U32_dinc(c, x379_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x379_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 467; sp += 4;\n"
"A0 = x466_0; pc = 380; break; }\n"
"break;\n"
"}\n"
"case 477: {\n"
"sp -= 3; KW x478_0 = KQ_ST(sp + 0); KW x478 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x479_0 = x478_0; KAUTO x479_1 = x478; KW x479 = k_bnode(c, 2); c->H[KIX(c, x479) + 0] = x479_0; c->H[KIX(c, x479) + 1] = x479_1; x479; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 474: {\n"
"sp -= 3; KW x475_0 = KQ_ST(sp + 0); KW x475 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x476_0 = KF_U32_dadd(c, x475_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x475; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 477; sp += 4;\n"
"A0 = x476_0; pc = 378; break; }\n"
"break;\n"
"}\n"
"case 376: {\n"
"KW x377_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x473_0 = KF_U32_dinc(c, x377_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x377_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 474; sp += 4;\n"
"A0 = x473_0; pc = 378; break; }\n"
"break;\n"
"}\n"
"case 484: {\n"
"sp -= 3; KW x485_0 = KQ_ST(sp + 0); KW x485 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x486_0 = x485_0; KAUTO x486_1 = x485; KW x486 = k_bnode(c, 2); c->H[KIX(c, x486) + 0] = x486_0; c->H[KIX(c, x486) + 1] = x486_1; x486; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 481: {\n"
"sp -= 3; KW x482_0 = KQ_ST(sp + 0); KW x482 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x483_0 = KF_U32_dadd(c, x482_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x482; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 484; sp += 4;\n"
"A0 = x483_0; pc = 376; break; }\n"
"break;\n"
"}\n"
"case 374: {\n"
"KW x375_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x480_0 = KF_U32_dinc(c, x375_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x375_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 481; sp += 4;\n"
"A0 = x480_0; pc = 376; break; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make_x37s2689494263x247252979(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 503, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 525: {\n"
"KW x526_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x527 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x526_0))));\n"
"KW x528 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x526_0, 2u))));\n"
"RV = ({ KAUTO x529_0 = x527; KAUTO x529_1 = x528; KW x529 = k_bnode(c, 2); c->H[KIX(c, x529) + 0] = x529_0; c->H[KIX(c, x529) + 1] = x529_1; x529; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 534: {\n"
"sp -= 3; KW x535_0 = KQ_ST(sp + 0); KW x535 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x536_0 = x535_0; KAUTO x536_1 = x535; KW x536 = k_bnode(c, 2); c->H[KIX(c, x536) + 0] = x536_0; c->H[KIX(c, x536) + 1] = x536_1; x536; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 531: {\n"
"sp -= 3; KW x532_0 = KQ_ST(sp + 0); KW x532 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x533_0 = KF_U32_dadd(c, x532_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x532; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 534; sp += 4;\n"
"A0 = x533_0; pc = 525; break; }\n"
"break;\n"
"}\n"
"case 523: {\n"
"KW x524_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x530_0 = KF_U32_dinc(c, x524_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x524_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 531; sp += 4;\n"
"A0 = x530_0; pc = 525; break; }\n"
"break;\n"
"}\n"
"case 541: {\n"
"sp -= 3; KW x542_0 = KQ_ST(sp + 0); KW x542 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x543_0 = x542_0; KAUTO x543_1 = x542; KW x543 = k_bnode(c, 2); c->H[KIX(c, x543) + 0] = x543_0; c->H[KIX(c, x543) + 1] = x543_1; x543; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 538: {\n"
"sp -= 3; KW x539_0 = KQ_ST(sp + 0); KW x539 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x540_0 = KF_U32_dadd(c, x539_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x539; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 541; sp += 4;\n"
"A0 = x540_0; pc = 523; break; }\n"
"break;\n"
"}\n"
"case 521: {\n"
"KW x522_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x537_0 = KF_U32_dinc(c, x522_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x522_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 538; sp += 4;\n"
"A0 = x537_0; pc = 523; break; }\n"
"break;\n"
"}\n"
"case 548: {\n"
"sp -= 3; KW x549_0 = KQ_ST(sp + 0); KW x549 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x550_0 = x549_0; KAUTO x550_1 = x549; KW x550 = k_bnode(c, 2); c->H[KIX(c, x550) + 0] = x550_0; c->H[KIX(c, x550) + 1] = x550_1; x550; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 545: {\n"
"sp -= 3; KW x546_0 = KQ_ST(sp + 0); KW x546 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x547_0 = KF_U32_dadd(c, x546_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x546; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 548; sp += 4;\n"
"A0 = x547_0; pc = 521; break; }\n"
"break;\n"
"}\n"
"case 519: {\n"
"KW x520_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x544_0 = KF_U32_dinc(c, x520_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x520_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 545; sp += 4;\n"
"A0 = x544_0; pc = 521; break; }\n"
"break;\n"
"}\n"
"case 555: {\n"
"sp -= 3; KW x556_0 = KQ_ST(sp + 0); KW x556 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x557_0 = x556_0; KAUTO x557_1 = x556; KW x557 = k_bnode(c, 2); c->H[KIX(c, x557) + 0] = x557_0; c->H[KIX(c, x557) + 1] = x557_1; x557; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 552: {\n"
"sp -= 3; KW x553_0 = KQ_ST(sp + 0); KW x553 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x554_0 = KF_U32_dadd(c, x553_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x553; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 555; sp += 4;\n"
"A0 = x554_0; pc = 519; break; }\n"
"break;\n"
"}\n"
"case 517: {\n"
"KW x518_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x551_0 = KF_U32_dinc(c, x518_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x518_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 552; sp += 4;\n"
"A0 = x551_0; pc = 519; break; }\n"
"break;\n"
"}\n"
"case 562: {\n"
"sp -= 3; KW x563_0 = KQ_ST(sp + 0); KW x563 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x564_0 = x563_0; KAUTO x564_1 = x563; KW x564 = k_bnode(c, 2); c->H[KIX(c, x564) + 0] = x564_0; c->H[KIX(c, x564) + 1] = x564_1; x564; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 559: {\n"
"sp -= 3; KW x560_0 = KQ_ST(sp + 0); KW x560 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x561_0 = KF_U32_dadd(c, x560_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x560; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 562; sp += 4;\n"
"A0 = x561_0; pc = 517; break; }\n"
"break;\n"
"}\n"
"case 515: {\n"
"KW x516_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x558_0 = KF_U32_dinc(c, x516_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x516_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 559; sp += 4;\n"
"A0 = x558_0; pc = 517; break; }\n"
"break;\n"
"}\n"
"case 569: {\n"
"sp -= 3; KW x570_0 = KQ_ST(sp + 0); KW x570 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x571_0 = x570_0; KAUTO x571_1 = x570; KW x571 = k_bnode(c, 2); c->H[KIX(c, x571) + 0] = x571_0; c->H[KIX(c, x571) + 1] = x571_1; x571; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 566: {\n"
"sp -= 3; KW x567_0 = KQ_ST(sp + 0); KW x567 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x568_0 = KF_U32_dadd(c, x567_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x567; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 569; sp += 4;\n"
"A0 = x568_0; pc = 515; break; }\n"
"break;\n"
"}\n"
"case 513: {\n"
"KW x514_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x565_0 = KF_U32_dinc(c, x514_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x514_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 566; sp += 4;\n"
"A0 = x565_0; pc = 515; break; }\n"
"break;\n"
"}\n"
"case 576: {\n"
"sp -= 3; KW x577_0 = KQ_ST(sp + 0); KW x577 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x578_0 = x577_0; KAUTO x578_1 = x577; KW x578 = k_bnode(c, 2); c->H[KIX(c, x578) + 0] = x578_0; c->H[KIX(c, x578) + 1] = x578_1; x578; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 573: {\n"
"sp -= 3; KW x574_0 = KQ_ST(sp + 0); KW x574 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x575_0 = KF_U32_dadd(c, x574_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x574; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 576; sp += 4;\n"
"A0 = x575_0; pc = 513; break; }\n"
"break;\n"
"}\n"
"case 511: {\n"
"KW x512_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x572_0 = KF_U32_dinc(c, x512_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x512_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 573; sp += 4;\n"
"A0 = x572_0; pc = 513; break; }\n"
"break;\n"
"}\n"
"case 583: {\n"
"sp -= 3; KW x584_0 = KQ_ST(sp + 0); KW x584 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x585_0 = x584_0; KAUTO x585_1 = x584; KW x585 = k_bnode(c, 2); c->H[KIX(c, x585) + 0] = x585_0; c->H[KIX(c, x585) + 1] = x585_1; x585; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 580: {\n"
"sp -= 3; KW x581_0 = KQ_ST(sp + 0); KW x581 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x582_0 = KF_U32_dadd(c, x581_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x581; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 583; sp += 4;\n"
"A0 = x582_0; pc = 511; break; }\n"
"break;\n"
"}\n"
"case 509: {\n"
"KW x510_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x579_0 = KF_U32_dinc(c, x510_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x510_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 580; sp += 4;\n"
"A0 = x579_0; pc = 511; break; }\n"
"break;\n"
"}\n"
"case 590: {\n"
"sp -= 3; KW x591_0 = KQ_ST(sp + 0); KW x591 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x592_0 = x591_0; KAUTO x592_1 = x591; KW x592 = k_bnode(c, 2); c->H[KIX(c, x592) + 0] = x592_0; c->H[KIX(c, x592) + 1] = x592_1; x592; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 587: {\n"
"sp -= 3; KW x588_0 = KQ_ST(sp + 0); KW x588 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x589_0 = KF_U32_dadd(c, x588_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x588; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 590; sp += 4;\n"
"A0 = x589_0; pc = 509; break; }\n"
"break;\n"
"}\n"
"case 507: {\n"
"KW x508_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x586_0 = KF_U32_dinc(c, x508_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x508_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 587; sp += 4;\n"
"A0 = x586_0; pc = 509; break; }\n"
"break;\n"
"}\n"
"case 597: {\n"
"sp -= 3; KW x598_0 = KQ_ST(sp + 0); KW x598 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x599_0 = x598_0; KAUTO x599_1 = x598; KW x599 = k_bnode(c, 2); c->H[KIX(c, x599) + 0] = x599_0; c->H[KIX(c, x599) + 1] = x599_1; x599; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 594: {\n"
"sp -= 3; KW x595_0 = KQ_ST(sp + 0); KW x595 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x596_0 = KF_U32_dadd(c, x595_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x595; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 597; sp += 4;\n"
"A0 = x596_0; pc = 507; break; }\n"
"break;\n"
"}\n"
"case 505: {\n"
"KW x506_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x593_0 = KF_U32_dinc(c, x506_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x506_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 594; sp += 4;\n"
"A0 = x593_0; pc = 507; break; }\n"
"break;\n"
"}\n"
"case 604: {\n"
"sp -= 3; KW x605_0 = KQ_ST(sp + 0); KW x605 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x606_0 = x605_0; KAUTO x606_1 = x605; KW x606 = k_bnode(c, 2); c->H[KIX(c, x606) + 0] = x606_0; c->H[KIX(c, x606) + 1] = x606_1; x606; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 601: {\n"
"sp -= 3; KW x602_0 = KQ_ST(sp + 0); KW x602 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x603_0 = KF_U32_dadd(c, x602_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x602; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 604; sp += 4;\n"
"A0 = x603_0; pc = 505; break; }\n"
"break;\n"
"}\n"
"case 503: {\n"
"KW x504_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x600_0 = KF_U32_dinc(c, x504_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x504_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 601; sp += 4;\n"
"A0 = x600_0; pc = 505; break; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make_x37s4233607528x247223188(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 623, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 643: {\n"
"KW x644_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x645 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x644_0))));\n"
"KW x646 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x644_0, 2u))));\n"
"RV = ({ KAUTO x647_0 = x645; KAUTO x647_1 = x646; KW x647 = k_bnode(c, 2); c->H[KIX(c, x647) + 0] = x647_0; c->H[KIX(c, x647) + 1] = x647_1; x647; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 652: {\n"
"sp -= 3; KW x653_0 = KQ_ST(sp + 0); KW x653 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x654_0 = x653_0; KAUTO x654_1 = x653; KW x654 = k_bnode(c, 2); c->H[KIX(c, x654) + 0] = x654_0; c->H[KIX(c, x654) + 1] = x654_1; x654; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 649: {\n"
"sp -= 3; KW x650_0 = KQ_ST(sp + 0); KW x650 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x651_0 = KF_U32_dadd(c, x650_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x650; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 652; sp += 4;\n"
"A0 = x651_0; pc = 643; break; }\n"
"break;\n"
"}\n"
"case 641: {\n"
"KW x642_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x648_0 = KF_U32_dinc(c, x642_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x642_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 649; sp += 4;\n"
"A0 = x648_0; pc = 643; break; }\n"
"break;\n"
"}\n"
"case 659: {\n"
"sp -= 3; KW x660_0 = KQ_ST(sp + 0); KW x660 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x661_0 = x660_0; KAUTO x661_1 = x660; KW x661 = k_bnode(c, 2); c->H[KIX(c, x661) + 0] = x661_0; c->H[KIX(c, x661) + 1] = x661_1; x661; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 656: {\n"
"sp -= 3; KW x657_0 = KQ_ST(sp + 0); KW x657 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x658_0 = KF_U32_dadd(c, x657_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x657; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 659; sp += 4;\n"
"A0 = x658_0; pc = 641; break; }\n"
"break;\n"
"}\n"
"case 639: {\n"
"KW x640_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x655_0 = KF_U32_dinc(c, x640_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x640_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 656; sp += 4;\n"
"A0 = x655_0; pc = 641; break; }\n"
"break;\n"
"}\n"
"case 666: {\n"
"sp -= 3; KW x667_0 = KQ_ST(sp + 0); KW x667 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x668_0 = x667_0; KAUTO x668_1 = x667; KW x668 = k_bnode(c, 2); c->H[KIX(c, x668) + 0] = x668_0; c->H[KIX(c, x668) + 1] = x668_1; x668; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 663: {\n"
"sp -= 3; KW x664_0 = KQ_ST(sp + 0); KW x664 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x665_0 = KF_U32_dadd(c, x664_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x664; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 666; sp += 4;\n"
"A0 = x665_0; pc = 639; break; }\n"
"break;\n"
"}\n"
"case 637: {\n"
"KW x638_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x662_0 = KF_U32_dinc(c, x638_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x638_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 663; sp += 4;\n"
"A0 = x662_0; pc = 639; break; }\n"
"break;\n"
"}\n"
"case 673: {\n"
"sp -= 3; KW x674_0 = KQ_ST(sp + 0); KW x674 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x675_0 = x674_0; KAUTO x675_1 = x674; KW x675 = k_bnode(c, 2); c->H[KIX(c, x675) + 0] = x675_0; c->H[KIX(c, x675) + 1] = x675_1; x675; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 670: {\n"
"sp -= 3; KW x671_0 = KQ_ST(sp + 0); KW x671 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x672_0 = KF_U32_dadd(c, x671_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x671; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 673; sp += 4;\n"
"A0 = x672_0; pc = 637; break; }\n"
"break;\n"
"}\n"
"case 635: {\n"
"KW x636_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x669_0 = KF_U32_dinc(c, x636_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x636_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 670; sp += 4;\n"
"A0 = x669_0; pc = 637; break; }\n"
"break;\n"
"}\n"
"case 680: {\n"
"sp -= 3; KW x681_0 = KQ_ST(sp + 0); KW x681 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x682_0 = x681_0; KAUTO x682_1 = x681; KW x682 = k_bnode(c, 2); c->H[KIX(c, x682) + 0] = x682_0; c->H[KIX(c, x682) + 1] = x682_1; x682; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 677: {\n"
"sp -= 3; KW x678_0 = KQ_ST(sp + 0); KW x678 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x679_0 = KF_U32_dadd(c, x678_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x678; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 680; sp += 4;\n"
"A0 = x679_0; pc = 635; break; }\n"
"break;\n"
"}\n"
"case 633: {\n"
"KW x634_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x676_0 = KF_U32_dinc(c, x634_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x634_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 677; sp += 4;\n"
"A0 = x676_0; pc = 635; break; }\n"
"break;\n"
"}\n"
"case 687: {\n"
"sp -= 3; KW x688_0 = KQ_ST(sp + 0); KW x688 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x689_0 = x688_0; KAUTO x689_1 = x688; KW x689 = k_bnode(c, 2); c->H[KIX(c, x689) + 0] = x689_0; c->H[KIX(c, x689) + 1] = x689_1; x689; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 684: {\n"
"sp -= 3; KW x685_0 = KQ_ST(sp + 0); KW x685 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x686_0 = KF_U32_dadd(c, x685_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x685; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 687; sp += 4;\n"
"A0 = x686_0; pc = 633; break; }\n"
"break;\n"
"}\n"
"case 631: {\n"
"KW x632_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x683_0 = KF_U32_dinc(c, x632_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x632_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 684; sp += 4;\n"
"A0 = x683_0; pc = 633; break; }\n"
"break;\n"
"}\n"
"case 694: {\n"
"sp -= 3; KW x695_0 = KQ_ST(sp + 0); KW x695 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x696_0 = x695_0; KAUTO x696_1 = x695; KW x696 = k_bnode(c, 2); c->H[KIX(c, x696) + 0] = x696_0; c->H[KIX(c, x696) + 1] = x696_1; x696; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 691: {\n"
"sp -= 3; KW x692_0 = KQ_ST(sp + 0); KW x692 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x693_0 = KF_U32_dadd(c, x692_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x692; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 694; sp += 4;\n"
"A0 = x693_0; pc = 631; break; }\n"
"break;\n"
"}\n"
"case 629: {\n"
"KW x630_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x690_0 = KF_U32_dinc(c, x630_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x630_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 691; sp += 4;\n"
"A0 = x690_0; pc = 631; break; }\n"
"break;\n"
"}\n"
"case 701: {\n"
"sp -= 3; KW x702_0 = KQ_ST(sp + 0); KW x702 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x703_0 = x702_0; KAUTO x703_1 = x702; KW x703 = k_bnode(c, 2); c->H[KIX(c, x703) + 0] = x703_0; c->H[KIX(c, x703) + 1] = x703_1; x703; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 698: {\n"
"sp -= 3; KW x699_0 = KQ_ST(sp + 0); KW x699 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x700_0 = KF_U32_dadd(c, x699_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x699; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 701; sp += 4;\n"
"A0 = x700_0; pc = 629; break; }\n"
"break;\n"
"}\n"
"case 627: {\n"
"KW x628_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x697_0 = KF_U32_dinc(c, x628_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x628_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 698; sp += 4;\n"
"A0 = x697_0; pc = 629; break; }\n"
"break;\n"
"}\n"
"case 708: {\n"
"sp -= 3; KW x709_0 = KQ_ST(sp + 0); KW x709 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x710_0 = x709_0; KAUTO x710_1 = x709; KW x710 = k_bnode(c, 2); c->H[KIX(c, x710) + 0] = x710_0; c->H[KIX(c, x710) + 1] = x710_1; x710; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 705: {\n"
"sp -= 3; KW x706_0 = KQ_ST(sp + 0); KW x706 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x707_0 = KF_U32_dadd(c, x706_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x706; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 708; sp += 4;\n"
"A0 = x707_0; pc = 627; break; }\n"
"break;\n"
"}\n"
"case 625: {\n"
"KW x626_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x704_0 = KF_U32_dinc(c, x626_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x626_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 705; sp += 4;\n"
"A0 = x704_0; pc = 627; break; }\n"
"break;\n"
"}\n"
"case 715: {\n"
"sp -= 3; KW x716_0 = KQ_ST(sp + 0); KW x716 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x717_0 = x716_0; KAUTO x717_1 = x716; KW x717 = k_bnode(c, 2); c->H[KIX(c, x717) + 0] = x717_0; c->H[KIX(c, x717) + 1] = x717_1; x717; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 712: {\n"
"sp -= 3; KW x713_0 = KQ_ST(sp + 0); KW x713 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x714_0 = KF_U32_dadd(c, x713_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x713; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 715; sp += 4;\n"
"A0 = x714_0; pc = 625; break; }\n"
"break;\n"
"}\n"
"case 623: {\n"
"KW x624_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x711_0 = KF_U32_dinc(c, x624_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x624_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 712; sp += 4;\n"
"A0 = x711_0; pc = 625; break; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make_x37s1953093269x247193397(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 734, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 752: {\n"
"KW x753_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x754 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x753_0))));\n"
"KW x755 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x753_0, 2u))));\n"
"RV = ({ KAUTO x756_0 = x754; KAUTO x756_1 = x755; KW x756 = k_bnode(c, 2); c->H[KIX(c, x756) + 0] = x756_0; c->H[KIX(c, x756) + 1] = x756_1; x756; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 761: {\n"
"sp -= 3; KW x762_0 = KQ_ST(sp + 0); KW x762 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x763_0 = x762_0; KAUTO x763_1 = x762; KW x763 = k_bnode(c, 2); c->H[KIX(c, x763) + 0] = x763_0; c->H[KIX(c, x763) + 1] = x763_1; x763; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 758: {\n"
"sp -= 3; KW x759_0 = KQ_ST(sp + 0); KW x759 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x760_0 = KF_U32_dadd(c, x759_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x759; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 761; sp += 4;\n"
"A0 = x760_0; pc = 752; break; }\n"
"break;\n"
"}\n"
"case 750: {\n"
"KW x751_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x757_0 = KF_U32_dinc(c, x751_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x751_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 758; sp += 4;\n"
"A0 = x757_0; pc = 752; break; }\n"
"break;\n"
"}\n"
"case 768: {\n"
"sp -= 3; KW x769_0 = KQ_ST(sp + 0); KW x769 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x770_0 = x769_0; KAUTO x770_1 = x769; KW x770 = k_bnode(c, 2); c->H[KIX(c, x770) + 0] = x770_0; c->H[KIX(c, x770) + 1] = x770_1; x770; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 765: {\n"
"sp -= 3; KW x766_0 = KQ_ST(sp + 0); KW x766 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x767_0 = KF_U32_dadd(c, x766_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x766; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 768; sp += 4;\n"
"A0 = x767_0; pc = 750; break; }\n"
"break;\n"
"}\n"
"case 748: {\n"
"KW x749_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x764_0 = KF_U32_dinc(c, x749_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x749_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 765; sp += 4;\n"
"A0 = x764_0; pc = 750; break; }\n"
"break;\n"
"}\n"
"case 775: {\n"
"sp -= 3; KW x776_0 = KQ_ST(sp + 0); KW x776 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x777_0 = x776_0; KAUTO x777_1 = x776; KW x777 = k_bnode(c, 2); c->H[KIX(c, x777) + 0] = x777_0; c->H[KIX(c, x777) + 1] = x777_1; x777; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 772: {\n"
"sp -= 3; KW x773_0 = KQ_ST(sp + 0); KW x773 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x774_0 = KF_U32_dadd(c, x773_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x773; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 775; sp += 4;\n"
"A0 = x774_0; pc = 748; break; }\n"
"break;\n"
"}\n"
"case 746: {\n"
"KW x747_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x771_0 = KF_U32_dinc(c, x747_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x747_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 772; sp += 4;\n"
"A0 = x771_0; pc = 748; break; }\n"
"break;\n"
"}\n"
"case 782: {\n"
"sp -= 3; KW x783_0 = KQ_ST(sp + 0); KW x783 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x784_0 = x783_0; KAUTO x784_1 = x783; KW x784 = k_bnode(c, 2); c->H[KIX(c, x784) + 0] = x784_0; c->H[KIX(c, x784) + 1] = x784_1; x784; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 779: {\n"
"sp -= 3; KW x780_0 = KQ_ST(sp + 0); KW x780 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x781_0 = KF_U32_dadd(c, x780_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x780; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 782; sp += 4;\n"
"A0 = x781_0; pc = 746; break; }\n"
"break;\n"
"}\n"
"case 744: {\n"
"KW x745_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x778_0 = KF_U32_dinc(c, x745_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x745_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 779; sp += 4;\n"
"A0 = x778_0; pc = 746; break; }\n"
"break;\n"
"}\n"
"case 789: {\n"
"sp -= 3; KW x790_0 = KQ_ST(sp + 0); KW x790 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x791_0 = x790_0; KAUTO x791_1 = x790; KW x791 = k_bnode(c, 2); c->H[KIX(c, x791) + 0] = x791_0; c->H[KIX(c, x791) + 1] = x791_1; x791; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 786: {\n"
"sp -= 3; KW x787_0 = KQ_ST(sp + 0); KW x787 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x788_0 = KF_U32_dadd(c, x787_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x787; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 789; sp += 4;\n"
"A0 = x788_0; pc = 744; break; }\n"
"break;\n"
"}\n"
"case 742: {\n"
"KW x743_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x785_0 = KF_U32_dinc(c, x743_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x743_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 786; sp += 4;\n"
"A0 = x785_0; pc = 744; break; }\n"
"break;\n"
"}\n"
"case 796: {\n"
"sp -= 3; KW x797_0 = KQ_ST(sp + 0); KW x797 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x798_0 = x797_0; KAUTO x798_1 = x797; KW x798 = k_bnode(c, 2); c->H[KIX(c, x798) + 0] = x798_0; c->H[KIX(c, x798) + 1] = x798_1; x798; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 793: {\n"
"sp -= 3; KW x794_0 = KQ_ST(sp + 0); KW x794 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x795_0 = KF_U32_dadd(c, x794_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x794; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 796; sp += 4;\n"
"A0 = x795_0; pc = 742; break; }\n"
"break;\n"
"}\n"
"case 740: {\n"
"KW x741_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x792_0 = KF_U32_dinc(c, x741_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x741_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 793; sp += 4;\n"
"A0 = x792_0; pc = 742; break; }\n"
"break;\n"
"}\n"
"case 803: {\n"
"sp -= 3; KW x804_0 = KQ_ST(sp + 0); KW x804 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x805_0 = x804_0; KAUTO x805_1 = x804; KW x805 = k_bnode(c, 2); c->H[KIX(c, x805) + 0] = x805_0; c->H[KIX(c, x805) + 1] = x805_1; x805; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 800: {\n"
"sp -= 3; KW x801_0 = KQ_ST(sp + 0); KW x801 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x802_0 = KF_U32_dadd(c, x801_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x801; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 803; sp += 4;\n"
"A0 = x802_0; pc = 740; break; }\n"
"break;\n"
"}\n"
"case 738: {\n"
"KW x739_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x799_0 = KF_U32_dinc(c, x739_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x739_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 800; sp += 4;\n"
"A0 = x799_0; pc = 740; break; }\n"
"break;\n"
"}\n"
"case 810: {\n"
"sp -= 3; KW x811_0 = KQ_ST(sp + 0); KW x811 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x812_0 = x811_0; KAUTO x812_1 = x811; KW x812 = k_bnode(c, 2); c->H[KIX(c, x812) + 0] = x812_0; c->H[KIX(c, x812) + 1] = x812_1; x812; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 807: {\n"
"sp -= 3; KW x808_0 = KQ_ST(sp + 0); KW x808 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x809_0 = KF_U32_dadd(c, x808_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x808; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 810; sp += 4;\n"
"A0 = x809_0; pc = 738; break; }\n"
"break;\n"
"}\n"
"case 736: {\n"
"KW x737_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x806_0 = KF_U32_dinc(c, x737_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x737_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 807; sp += 4;\n"
"A0 = x806_0; pc = 738; break; }\n"
"break;\n"
"}\n"
"case 817: {\n"
"sp -= 3; KW x818_0 = KQ_ST(sp + 0); KW x818 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x819_0 = x818_0; KAUTO x819_1 = x818; KW x819 = k_bnode(c, 2); c->H[KIX(c, x819) + 0] = x819_0; c->H[KIX(c, x819) + 1] = x819_1; x819; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 814: {\n"
"sp -= 3; KW x815_0 = KQ_ST(sp + 0); KW x815 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x816_0 = KF_U32_dadd(c, x815_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x815; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 817; sp += 4;\n"
"A0 = x816_0; pc = 736; break; }\n"
"break;\n"
"}\n"
"case 734: {\n"
"KW x735_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x813_0 = KF_U32_dinc(c, x735_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x735_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 814; sp += 4;\n"
"A0 = x813_0; pc = 736; break; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make_x37s3305376709x8269577(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 836, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 852: {\n"
"KW x853_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x854 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x853_0))));\n"
"KW x855 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x853_0, 2u))));\n"
"RV = ({ KAUTO x856_0 = x854; KAUTO x856_1 = x855; KW x856 = k_bnode(c, 2); c->H[KIX(c, x856) + 0] = x856_0; c->H[KIX(c, x856) + 1] = x856_1; x856; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 861: {\n"
"sp -= 3; KW x862_0 = KQ_ST(sp + 0); KW x862 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x863_0 = x862_0; KAUTO x863_1 = x862; KW x863 = k_bnode(c, 2); c->H[KIX(c, x863) + 0] = x863_0; c->H[KIX(c, x863) + 1] = x863_1; x863; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 858: {\n"
"sp -= 3; KW x859_0 = KQ_ST(sp + 0); KW x859 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x860_0 = KF_U32_dadd(c, x859_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x859; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 861; sp += 4;\n"
"A0 = x860_0; pc = 852; break; }\n"
"break;\n"
"}\n"
"case 850: {\n"
"KW x851_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x857_0 = KF_U32_dinc(c, x851_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x851_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 858; sp += 4;\n"
"A0 = x857_0; pc = 852; break; }\n"
"break;\n"
"}\n"
"case 868: {\n"
"sp -= 3; KW x869_0 = KQ_ST(sp + 0); KW x869 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x870_0 = x869_0; KAUTO x870_1 = x869; KW x870 = k_bnode(c, 2); c->H[KIX(c, x870) + 0] = x870_0; c->H[KIX(c, x870) + 1] = x870_1; x870; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 865: {\n"
"sp -= 3; KW x866_0 = KQ_ST(sp + 0); KW x866 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x867_0 = KF_U32_dadd(c, x866_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x866; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 868; sp += 4;\n"
"A0 = x867_0; pc = 850; break; }\n"
"break;\n"
"}\n"
"case 848: {\n"
"KW x849_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x864_0 = KF_U32_dinc(c, x849_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x849_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 865; sp += 4;\n"
"A0 = x864_0; pc = 850; break; }\n"
"break;\n"
"}\n"
"case 875: {\n"
"sp -= 3; KW x876_0 = KQ_ST(sp + 0); KW x876 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x877_0 = x876_0; KAUTO x877_1 = x876; KW x877 = k_bnode(c, 2); c->H[KIX(c, x877) + 0] = x877_0; c->H[KIX(c, x877) + 1] = x877_1; x877; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 872: {\n"
"sp -= 3; KW x873_0 = KQ_ST(sp + 0); KW x873 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x874_0 = KF_U32_dadd(c, x873_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x873; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 875; sp += 4;\n"
"A0 = x874_0; pc = 848; break; }\n"
"break;\n"
"}\n"
"case 846: {\n"
"KW x847_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x871_0 = KF_U32_dinc(c, x847_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x847_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 872; sp += 4;\n"
"A0 = x871_0; pc = 848; break; }\n"
"break;\n"
"}\n"
"case 882: {\n"
"sp -= 3; KW x883_0 = KQ_ST(sp + 0); KW x883 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x884_0 = x883_0; KAUTO x884_1 = x883; KW x884 = k_bnode(c, 2); c->H[KIX(c, x884) + 0] = x884_0; c->H[KIX(c, x884) + 1] = x884_1; x884; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 879: {\n"
"sp -= 3; KW x880_0 = KQ_ST(sp + 0); KW x880 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x881_0 = KF_U32_dadd(c, x880_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x880; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 882; sp += 4;\n"
"A0 = x881_0; pc = 846; break; }\n"
"break;\n"
"}\n"
"case 844: {\n"
"KW x845_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x878_0 = KF_U32_dinc(c, x845_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x845_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 879; sp += 4;\n"
"A0 = x878_0; pc = 846; break; }\n"
"break;\n"
"}\n"
"case 889: {\n"
"sp -= 3; KW x890_0 = KQ_ST(sp + 0); KW x890 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x891_0 = x890_0; KAUTO x891_1 = x890; KW x891 = k_bnode(c, 2); c->H[KIX(c, x891) + 0] = x891_0; c->H[KIX(c, x891) + 1] = x891_1; x891; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 886: {\n"
"sp -= 3; KW x887_0 = KQ_ST(sp + 0); KW x887 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x888_0 = KF_U32_dadd(c, x887_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x887; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 889; sp += 4;\n"
"A0 = x888_0; pc = 844; break; }\n"
"break;\n"
"}\n"
"case 842: {\n"
"KW x843_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x885_0 = KF_U32_dinc(c, x843_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x843_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 886; sp += 4;\n"
"A0 = x885_0; pc = 844; break; }\n"
"break;\n"
"}\n"
"case 896: {\n"
"sp -= 3; KW x897_0 = KQ_ST(sp + 0); KW x897 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x898_0 = x897_0; KAUTO x898_1 = x897; KW x898 = k_bnode(c, 2); c->H[KIX(c, x898) + 0] = x898_0; c->H[KIX(c, x898) + 1] = x898_1; x898; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 893: {\n"
"sp -= 3; KW x894_0 = KQ_ST(sp + 0); KW x894 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x895_0 = KF_U32_dadd(c, x894_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x894; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 896; sp += 4;\n"
"A0 = x895_0; pc = 842; break; }\n"
"break;\n"
"}\n"
"case 840: {\n"
"KW x841_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x892_0 = KF_U32_dinc(c, x841_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x841_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 893; sp += 4;\n"
"A0 = x892_0; pc = 842; break; }\n"
"break;\n"
"}\n"
"case 903: {\n"
"sp -= 3; KW x904_0 = KQ_ST(sp + 0); KW x904 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x905_0 = x904_0; KAUTO x905_1 = x904; KW x905 = k_bnode(c, 2); c->H[KIX(c, x905) + 0] = x905_0; c->H[KIX(c, x905) + 1] = x905_1; x905; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 900: {\n"
"sp -= 3; KW x901_0 = KQ_ST(sp + 0); KW x901 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x902_0 = KF_U32_dadd(c, x901_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x901; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 903; sp += 4;\n"
"A0 = x902_0; pc = 840; break; }\n"
"break;\n"
"}\n"
"case 838: {\n"
"KW x839_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x899_0 = KF_U32_dinc(c, x839_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x839_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 900; sp += 4;\n"
"A0 = x899_0; pc = 840; break; }\n"
"break;\n"
"}\n"
"case 910: {\n"
"sp -= 3; KW x911_0 = KQ_ST(sp + 0); KW x911 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x912_0 = x911_0; KAUTO x912_1 = x911; KW x912 = k_bnode(c, 2); c->H[KIX(c, x912) + 0] = x912_0; c->H[KIX(c, x912) + 1] = x912_1; x912; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 907: {\n"
"sp -= 3; KW x908_0 = KQ_ST(sp + 0); KW x908 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x909_0 = KF_U32_dadd(c, x908_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x908; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 910; sp += 4;\n"
"A0 = x909_0; pc = 838; break; }\n"
"break;\n"
"}\n"
"case 836: {\n"
"KW x837_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x906_0 = KF_U32_dinc(c, x837_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x837_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 907; sp += 4;\n"
"A0 = x906_0; pc = 838; break; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make_x37s2491568216x8239786(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 929, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 943: {\n"
"KW x944_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x945 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x944_0))));\n"
"KW x946 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x944_0, 2u))));\n"
"RV = ({ KAUTO x947_0 = x945; KAUTO x947_1 = x946; KW x947 = k_bnode(c, 2); c->H[KIX(c, x947) + 0] = x947_0; c->H[KIX(c, x947) + 1] = x947_1; x947; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 952: {\n"
"sp -= 3; KW x953_0 = KQ_ST(sp + 0); KW x953 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x954_0 = x953_0; KAUTO x954_1 = x953; KW x954 = k_bnode(c, 2); c->H[KIX(c, x954) + 0] = x954_0; c->H[KIX(c, x954) + 1] = x954_1; x954; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 949: {\n"
"sp -= 3; KW x950_0 = KQ_ST(sp + 0); KW x950 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x951_0 = KF_U32_dadd(c, x950_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x950; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 952; sp += 4;\n"
"A0 = x951_0; pc = 943; break; }\n"
"break;\n"
"}\n"
"case 941: {\n"
"KW x942_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x948_0 = KF_U32_dinc(c, x942_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x942_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 949; sp += 4;\n"
"A0 = x948_0; pc = 943; break; }\n"
"break;\n"
"}\n"
"case 959: {\n"
"sp -= 3; KW x960_0 = KQ_ST(sp + 0); KW x960 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x961_0 = x960_0; KAUTO x961_1 = x960; KW x961 = k_bnode(c, 2); c->H[KIX(c, x961) + 0] = x961_0; c->H[KIX(c, x961) + 1] = x961_1; x961; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 956: {\n"
"sp -= 3; KW x957_0 = KQ_ST(sp + 0); KW x957 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x958_0 = KF_U32_dadd(c, x957_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x957; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 959; sp += 4;\n"
"A0 = x958_0; pc = 941; break; }\n"
"break;\n"
"}\n"
"case 939: {\n"
"KW x940_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x955_0 = KF_U32_dinc(c, x940_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x940_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 956; sp += 4;\n"
"A0 = x955_0; pc = 941; break; }\n"
"break;\n"
"}\n"
"case 966: {\n"
"sp -= 3; KW x967_0 = KQ_ST(sp + 0); KW x967 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x968_0 = x967_0; KAUTO x968_1 = x967; KW x968 = k_bnode(c, 2); c->H[KIX(c, x968) + 0] = x968_0; c->H[KIX(c, x968) + 1] = x968_1; x968; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 963: {\n"
"sp -= 3; KW x964_0 = KQ_ST(sp + 0); KW x964 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x965_0 = KF_U32_dadd(c, x964_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x964; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 966; sp += 4;\n"
"A0 = x965_0; pc = 939; break; }\n"
"break;\n"
"}\n"
"case 937: {\n"
"KW x938_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x962_0 = KF_U32_dinc(c, x938_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x938_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 963; sp += 4;\n"
"A0 = x962_0; pc = 939; break; }\n"
"break;\n"
"}\n"
"case 973: {\n"
"sp -= 3; KW x974_0 = KQ_ST(sp + 0); KW x974 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x975_0 = x974_0; KAUTO x975_1 = x974; KW x975 = k_bnode(c, 2); c->H[KIX(c, x975) + 0] = x975_0; c->H[KIX(c, x975) + 1] = x975_1; x975; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 970: {\n"
"sp -= 3; KW x971_0 = KQ_ST(sp + 0); KW x971 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x972_0 = KF_U32_dadd(c, x971_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x971; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 973; sp += 4;\n"
"A0 = x972_0; pc = 937; break; }\n"
"break;\n"
"}\n"
"case 935: {\n"
"KW x936_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x969_0 = KF_U32_dinc(c, x936_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x936_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 970; sp += 4;\n"
"A0 = x969_0; pc = 937; break; }\n"
"break;\n"
"}\n"
"case 980: {\n"
"sp -= 3; KW x981_0 = KQ_ST(sp + 0); KW x981 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x982_0 = x981_0; KAUTO x982_1 = x981; KW x982 = k_bnode(c, 2); c->H[KIX(c, x982) + 0] = x982_0; c->H[KIX(c, x982) + 1] = x982_1; x982; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 977: {\n"
"sp -= 3; KW x978_0 = KQ_ST(sp + 0); KW x978 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x979_0 = KF_U32_dadd(c, x978_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x978; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 980; sp += 4;\n"
"A0 = x979_0; pc = 935; break; }\n"
"break;\n"
"}\n"
"case 933: {\n"
"KW x934_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x976_0 = KF_U32_dinc(c, x934_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x934_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 977; sp += 4;\n"
"A0 = x976_0; pc = 935; break; }\n"
"break;\n"
"}\n"
"case 987: {\n"
"sp -= 3; KW x988_0 = KQ_ST(sp + 0); KW x988 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x989_0 = x988_0; KAUTO x989_1 = x988; KW x989 = k_bnode(c, 2); c->H[KIX(c, x989) + 0] = x989_0; c->H[KIX(c, x989) + 1] = x989_1; x989; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 984: {\n"
"sp -= 3; KW x985_0 = KQ_ST(sp + 0); KW x985 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x986_0 = KF_U32_dadd(c, x985_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x985; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 987; sp += 4;\n"
"A0 = x986_0; pc = 933; break; }\n"
"break;\n"
"}\n"
"case 931: {\n"
"KW x932_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x983_0 = KF_U32_dinc(c, x932_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x932_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 984; sp += 4;\n"
"A0 = x983_0; pc = 933; break; }\n"
"break;\n"
"}\n"
"case 994: {\n"
"sp -= 3; KW x995_0 = KQ_ST(sp + 0); KW x995 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x996_0 = x995_0; KAUTO x996_1 = x995; KW x996 = k_bnode(c, 2); c->H[KIX(c, x996) + 0] = x996_0; c->H[KIX(c, x996) + 1] = x996_1; x996; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 991: {\n"
"sp -= 3; KW x992_0 = KQ_ST(sp + 0); KW x992 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x993_0 = KF_U32_dadd(c, x992_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x992; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 994; sp += 4;\n"
"A0 = x993_0; pc = 931; break; }\n"
"break;\n"
"}\n"
"case 929: {\n"
"KW x930_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x990_0 = KF_U32_dinc(c, x930_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x930_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 991; sp += 4;\n"
"A0 = x990_0; pc = 931; break; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make_x37s1291691603x8209995(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 1013, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 1025: {\n"
"KW x1026_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x1027 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x1026_0))));\n"
"KW x1028 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x1026_0, 2u))));\n"
"RV = ({ KAUTO x1029_0 = x1027; KAUTO x1029_1 = x1028; KW x1029 = k_bnode(c, 2); c->H[KIX(c, x1029) + 0] = x1029_0; c->H[KIX(c, x1029) + 1] = x1029_1; x1029; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1034: {\n"
"sp -= 3; KW x1035_0 = KQ_ST(sp + 0); KW x1035 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1036_0 = x1035_0; KAUTO x1036_1 = x1035; KW x1036 = k_bnode(c, 2); c->H[KIX(c, x1036) + 0] = x1036_0; c->H[KIX(c, x1036) + 1] = x1036_1; x1036; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1031: {\n"
"sp -= 3; KW x1032_0 = KQ_ST(sp + 0); KW x1032 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1033_0 = KF_U32_dadd(c, x1032_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1032; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1034; sp += 4;\n"
"A0 = x1033_0; pc = 1025; break; }\n"
"break;\n"
"}\n"
"case 1023: {\n"
"KW x1024_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1030_0 = KF_U32_dinc(c, x1024_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1024_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1031; sp += 4;\n"
"A0 = x1030_0; pc = 1025; break; }\n"
"break;\n"
"}\n"
"case 1041: {\n"
"sp -= 3; KW x1042_0 = KQ_ST(sp + 0); KW x1042 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1043_0 = x1042_0; KAUTO x1043_1 = x1042; KW x1043 = k_bnode(c, 2); c->H[KIX(c, x1043) + 0] = x1043_0; c->H[KIX(c, x1043) + 1] = x1043_1; x1043; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1038: {\n"
"sp -= 3; KW x1039_0 = KQ_ST(sp + 0); KW x1039 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1040_0 = KF_U32_dadd(c, x1039_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1039; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1041; sp += 4;\n"
"A0 = x1040_0; pc = 1023; break; }\n"
"break;\n"
"}\n"
"case 1021: {\n"
"KW x1022_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1037_0 = KF_U32_dinc(c, x1022_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1022_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1038; sp += 4;\n"
"A0 = x1037_0; pc = 1023; break; }\n"
"break;\n"
"}\n"
"case 1048: {\n"
"sp -= 3; KW x1049_0 = KQ_ST(sp + 0); KW x1049 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1050_0 = x1049_0; KAUTO x1050_1 = x1049; KW x1050 = k_bnode(c, 2); c->H[KIX(c, x1050) + 0] = x1050_0; c->H[KIX(c, x1050) + 1] = x1050_1; x1050; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1045: {\n"
"sp -= 3; KW x1046_0 = KQ_ST(sp + 0); KW x1046 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1047_0 = KF_U32_dadd(c, x1046_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1046; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1048; sp += 4;\n"
"A0 = x1047_0; pc = 1021; break; }\n"
"break;\n"
"}\n"
"case 1019: {\n"
"KW x1020_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1044_0 = KF_U32_dinc(c, x1020_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1020_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1045; sp += 4;\n"
"A0 = x1044_0; pc = 1021; break; }\n"
"break;\n"
"}\n"
"case 1055: {\n"
"sp -= 3; KW x1056_0 = KQ_ST(sp + 0); KW x1056 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1057_0 = x1056_0; KAUTO x1057_1 = x1056; KW x1057 = k_bnode(c, 2); c->H[KIX(c, x1057) + 0] = x1057_0; c->H[KIX(c, x1057) + 1] = x1057_1; x1057; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1052: {\n"
"sp -= 3; KW x1053_0 = KQ_ST(sp + 0); KW x1053 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1054_0 = KF_U32_dadd(c, x1053_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1053; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1055; sp += 4;\n"
"A0 = x1054_0; pc = 1019; break; }\n"
"break;\n"
"}\n"
"case 1017: {\n"
"KW x1018_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1051_0 = KF_U32_dinc(c, x1018_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1018_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1052; sp += 4;\n"
"A0 = x1051_0; pc = 1019; break; }\n"
"break;\n"
"}\n"
"case 1062: {\n"
"sp -= 3; KW x1063_0 = KQ_ST(sp + 0); KW x1063 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1064_0 = x1063_0; KAUTO x1064_1 = x1063; KW x1064 = k_bnode(c, 2); c->H[KIX(c, x1064) + 0] = x1064_0; c->H[KIX(c, x1064) + 1] = x1064_1; x1064; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1059: {\n"
"sp -= 3; KW x1060_0 = KQ_ST(sp + 0); KW x1060 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1061_0 = KF_U32_dadd(c, x1060_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1060; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1062; sp += 4;\n"
"A0 = x1061_0; pc = 1017; break; }\n"
"break;\n"
"}\n"
"case 1015: {\n"
"KW x1016_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1058_0 = KF_U32_dinc(c, x1016_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1016_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1059; sp += 4;\n"
"A0 = x1058_0; pc = 1017; break; }\n"
"break;\n"
"}\n"
"case 1069: {\n"
"sp -= 3; KW x1070_0 = KQ_ST(sp + 0); KW x1070 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1071_0 = x1070_0; KAUTO x1071_1 = x1070; KW x1071 = k_bnode(c, 2); c->H[KIX(c, x1071) + 0] = x1071_0; c->H[KIX(c, x1071) + 1] = x1071_1; x1071; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1066: {\n"
"sp -= 3; KW x1067_0 = KQ_ST(sp + 0); KW x1067 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1068_0 = KF_U32_dadd(c, x1067_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1067; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1069; sp += 4;\n"
"A0 = x1068_0; pc = 1015; break; }\n"
"break;\n"
"}\n"
"case 1013: {\n"
"KW x1014_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1065_0 = KF_U32_dinc(c, x1014_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1014_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1066; sp += 4;\n"
"A0 = x1065_0; pc = 1015; break; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make_x37s32637286x8180204(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 1088, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 1098: {\n"
"KW x1099_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x1100 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x1099_0))));\n"
"KW x1101 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x1099_0, 2u))));\n"
"RV = ({ KAUTO x1102_0 = x1100; KAUTO x1102_1 = x1101; KW x1102 = k_bnode(c, 2); c->H[KIX(c, x1102) + 0] = x1102_0; c->H[KIX(c, x1102) + 1] = x1102_1; x1102; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1107: {\n"
"sp -= 3; KW x1108_0 = KQ_ST(sp + 0); KW x1108 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1109_0 = x1108_0; KAUTO x1109_1 = x1108; KW x1109 = k_bnode(c, 2); c->H[KIX(c, x1109) + 0] = x1109_0; c->H[KIX(c, x1109) + 1] = x1109_1; x1109; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1104: {\n"
"sp -= 3; KW x1105_0 = KQ_ST(sp + 0); KW x1105 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1106_0 = KF_U32_dadd(c, x1105_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1105; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1107; sp += 4;\n"
"A0 = x1106_0; pc = 1098; break; }\n"
"break;\n"
"}\n"
"case 1096: {\n"
"KW x1097_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1103_0 = KF_U32_dinc(c, x1097_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1097_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1104; sp += 4;\n"
"A0 = x1103_0; pc = 1098; break; }\n"
"break;\n"
"}\n"
"case 1114: {\n"
"sp -= 3; KW x1115_0 = KQ_ST(sp + 0); KW x1115 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1116_0 = x1115_0; KAUTO x1116_1 = x1115; KW x1116 = k_bnode(c, 2); c->H[KIX(c, x1116) + 0] = x1116_0; c->H[KIX(c, x1116) + 1] = x1116_1; x1116; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1111: {\n"
"sp -= 3; KW x1112_0 = KQ_ST(sp + 0); KW x1112 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1113_0 = KF_U32_dadd(c, x1112_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1112; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1114; sp += 4;\n"
"A0 = x1113_0; pc = 1096; break; }\n"
"break;\n"
"}\n"
"case 1094: {\n"
"KW x1095_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1110_0 = KF_U32_dinc(c, x1095_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1095_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1111; sp += 4;\n"
"A0 = x1110_0; pc = 1096; break; }\n"
"break;\n"
"}\n"
"case 1121: {\n"
"sp -= 3; KW x1122_0 = KQ_ST(sp + 0); KW x1122 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1123_0 = x1122_0; KAUTO x1123_1 = x1122; KW x1123 = k_bnode(c, 2); c->H[KIX(c, x1123) + 0] = x1123_0; c->H[KIX(c, x1123) + 1] = x1123_1; x1123; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1118: {\n"
"sp -= 3; KW x1119_0 = KQ_ST(sp + 0); KW x1119 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1120_0 = KF_U32_dadd(c, x1119_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1119; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1121; sp += 4;\n"
"A0 = x1120_0; pc = 1094; break; }\n"
"break;\n"
"}\n"
"case 1092: {\n"
"KW x1093_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1117_0 = KF_U32_dinc(c, x1093_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1093_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1118; sp += 4;\n"
"A0 = x1117_0; pc = 1094; break; }\n"
"break;\n"
"}\n"
"case 1128: {\n"
"sp -= 3; KW x1129_0 = KQ_ST(sp + 0); KW x1129 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1130_0 = x1129_0; KAUTO x1130_1 = x1129; KW x1130 = k_bnode(c, 2); c->H[KIX(c, x1130) + 0] = x1130_0; c->H[KIX(c, x1130) + 1] = x1130_1; x1130; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1125: {\n"
"sp -= 3; KW x1126_0 = KQ_ST(sp + 0); KW x1126 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1127_0 = KF_U32_dadd(c, x1126_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1126; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1128; sp += 4;\n"
"A0 = x1127_0; pc = 1092; break; }\n"
"break;\n"
"}\n"
"case 1090: {\n"
"KW x1091_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1124_0 = KF_U32_dinc(c, x1091_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1091_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1125; sp += 4;\n"
"A0 = x1124_0; pc = 1092; break; }\n"
"break;\n"
"}\n"
"case 1135: {\n"
"sp -= 3; KW x1136_0 = KQ_ST(sp + 0); KW x1136 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1137_0 = x1136_0; KAUTO x1137_1 = x1136; KW x1137 = k_bnode(c, 2); c->H[KIX(c, x1137) + 0] = x1137_0; c->H[KIX(c, x1137) + 1] = x1137_1; x1137; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1132: {\n"
"sp -= 3; KW x1133_0 = KQ_ST(sp + 0); KW x1133 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1134_0 = KF_U32_dadd(c, x1133_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1133; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1135; sp += 4;\n"
"A0 = x1134_0; pc = 1090; break; }\n"
"break;\n"
"}\n"
"case 1088: {\n"
"KW x1089_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1131_0 = KF_U32_dinc(c, x1089_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1089_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1132; sp += 4;\n"
"A0 = x1131_0; pc = 1090; break; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make_x37s3239606481x8150413(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 1154, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 1162: {\n"
"KW x1163_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x1164 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x1163_0))));\n"
"KW x1165 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x1163_0, 2u))));\n"
"RV = ({ KAUTO x1166_0 = x1164; KAUTO x1166_1 = x1165; KW x1166 = k_bnode(c, 2); c->H[KIX(c, x1166) + 0] = x1166_0; c->H[KIX(c, x1166) + 1] = x1166_1; x1166; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1171: {\n"
"sp -= 3; KW x1172_0 = KQ_ST(sp + 0); KW x1172 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1173_0 = x1172_0; KAUTO x1173_1 = x1172; KW x1173 = k_bnode(c, 2); c->H[KIX(c, x1173) + 0] = x1173_0; c->H[KIX(c, x1173) + 1] = x1173_1; x1173; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1168: {\n"
"sp -= 3; KW x1169_0 = KQ_ST(sp + 0); KW x1169 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1170_0 = KF_U32_dadd(c, x1169_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1169; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1171; sp += 4;\n"
"A0 = x1170_0; pc = 1162; break; }\n"
"break;\n"
"}\n"
"case 1160: {\n"
"KW x1161_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1167_0 = KF_U32_dinc(c, x1161_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1161_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1168; sp += 4;\n"
"A0 = x1167_0; pc = 1162; break; }\n"
"break;\n"
"}\n"
"case 1178: {\n"
"sp -= 3; KW x1179_0 = KQ_ST(sp + 0); KW x1179 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1180_0 = x1179_0; KAUTO x1180_1 = x1179; KW x1180 = k_bnode(c, 2); c->H[KIX(c, x1180) + 0] = x1180_0; c->H[KIX(c, x1180) + 1] = x1180_1; x1180; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1175: {\n"
"sp -= 3; KW x1176_0 = KQ_ST(sp + 0); KW x1176 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1177_0 = KF_U32_dadd(c, x1176_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1176; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1178; sp += 4;\n"
"A0 = x1177_0; pc = 1160; break; }\n"
"break;\n"
"}\n"
"case 1158: {\n"
"KW x1159_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1174_0 = KF_U32_dinc(c, x1159_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1159_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1175; sp += 4;\n"
"A0 = x1174_0; pc = 1160; break; }\n"
"break;\n"
"}\n"
"case 1185: {\n"
"sp -= 3; KW x1186_0 = KQ_ST(sp + 0); KW x1186 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1187_0 = x1186_0; KAUTO x1187_1 = x1186; KW x1187 = k_bnode(c, 2); c->H[KIX(c, x1187) + 0] = x1187_0; c->H[KIX(c, x1187) + 1] = x1187_1; x1187; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1182: {\n"
"sp -= 3; KW x1183_0 = KQ_ST(sp + 0); KW x1183 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1184_0 = KF_U32_dadd(c, x1183_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1183; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1185; sp += 4;\n"
"A0 = x1184_0; pc = 1158; break; }\n"
"break;\n"
"}\n"
"case 1156: {\n"
"KW x1157_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1181_0 = KF_U32_dinc(c, x1157_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1157_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1182; sp += 4;\n"
"A0 = x1181_0; pc = 1158; break; }\n"
"break;\n"
"}\n"
"case 1192: {\n"
"sp -= 3; KW x1193_0 = KQ_ST(sp + 0); KW x1193 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1194_0 = x1193_0; KAUTO x1194_1 = x1193; KW x1194 = k_bnode(c, 2); c->H[KIX(c, x1194) + 0] = x1194_0; c->H[KIX(c, x1194) + 1] = x1194_1; x1194; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1189: {\n"
"sp -= 3; KW x1190_0 = KQ_ST(sp + 0); KW x1190 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1191_0 = KF_U32_dadd(c, x1190_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1190; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1192; sp += 4;\n"
"A0 = x1191_0; pc = 1156; break; }\n"
"break;\n"
"}\n"
"case 1154: {\n"
"KW x1155_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1188_0 = KF_U32_dinc(c, x1155_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1155_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1189; sp += 4;\n"
"A0 = x1188_0; pc = 1156; break; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make_x37s2405009636x8120622(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 1211, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 1217: {\n"
"KW x1218_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x1219 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x1218_0))));\n"
"KW x1220 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x1218_0, 2u))));\n"
"RV = ({ KAUTO x1221_0 = x1219; KAUTO x1221_1 = x1220; KW x1221 = k_bnode(c, 2); c->H[KIX(c, x1221) + 0] = x1221_0; c->H[KIX(c, x1221) + 1] = x1221_1; x1221; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1226: {\n"
"sp -= 3; KW x1227_0 = KQ_ST(sp + 0); KW x1227 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1228_0 = x1227_0; KAUTO x1228_1 = x1227; KW x1228 = k_bnode(c, 2); c->H[KIX(c, x1228) + 0] = x1228_0; c->H[KIX(c, x1228) + 1] = x1228_1; x1228; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1223: {\n"
"sp -= 3; KW x1224_0 = KQ_ST(sp + 0); KW x1224 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1225_0 = KF_U32_dadd(c, x1224_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1224; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1226; sp += 4;\n"
"A0 = x1225_0; pc = 1217; break; }\n"
"break;\n"
"}\n"
"case 1215: {\n"
"KW x1216_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1222_0 = KF_U32_dinc(c, x1216_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1216_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1223; sp += 4;\n"
"A0 = x1222_0; pc = 1217; break; }\n"
"break;\n"
"}\n"
"case 1233: {\n"
"sp -= 3; KW x1234_0 = KQ_ST(sp + 0); KW x1234 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1235_0 = x1234_0; KAUTO x1235_1 = x1234; KW x1235 = k_bnode(c, 2); c->H[KIX(c, x1235) + 0] = x1235_0; c->H[KIX(c, x1235) + 1] = x1235_1; x1235; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1230: {\n"
"sp -= 3; KW x1231_0 = KQ_ST(sp + 0); KW x1231 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1232_0 = KF_U32_dadd(c, x1231_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1231; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1233; sp += 4;\n"
"A0 = x1232_0; pc = 1215; break; }\n"
"break;\n"
"}\n"
"case 1213: {\n"
"KW x1214_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1229_0 = KF_U32_dinc(c, x1214_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1214_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1230; sp += 4;\n"
"A0 = x1229_0; pc = 1215; break; }\n"
"break;\n"
"}\n"
"case 1240: {\n"
"sp -= 3; KW x1241_0 = KQ_ST(sp + 0); KW x1241 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1242_0 = x1241_0; KAUTO x1242_1 = x1241; KW x1242 = k_bnode(c, 2); c->H[KIX(c, x1242) + 0] = x1242_0; c->H[KIX(c, x1242) + 1] = x1242_1; x1242; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1237: {\n"
"sp -= 3; KW x1238_0 = KQ_ST(sp + 0); KW x1238 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1239_0 = KF_U32_dadd(c, x1238_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1238; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1240; sp += 4;\n"
"A0 = x1239_0; pc = 1213; break; }\n"
"break;\n"
"}\n"
"case 1211: {\n"
"KW x1212_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1236_0 = KF_U32_dinc(c, x1212_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1212_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1237; sp += 4;\n"
"A0 = x1236_0; pc = 1213; break; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make_x37s1586577935x8090831(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 1259, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 1263: {\n"
"KW x1264_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x1265 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x1264_0))));\n"
"KW x1266 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x1264_0, 2u))));\n"
"RV = ({ KAUTO x1267_0 = x1265; KAUTO x1267_1 = x1266; KW x1267 = k_bnode(c, 2); c->H[KIX(c, x1267) + 0] = x1267_0; c->H[KIX(c, x1267) + 1] = x1267_1; x1267; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1272: {\n"
"sp -= 3; KW x1273_0 = KQ_ST(sp + 0); KW x1273 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1274_0 = x1273_0; KAUTO x1274_1 = x1273; KW x1274 = k_bnode(c, 2); c->H[KIX(c, x1274) + 0] = x1274_0; c->H[KIX(c, x1274) + 1] = x1274_1; x1274; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1269: {\n"
"sp -= 3; KW x1270_0 = KQ_ST(sp + 0); KW x1270 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1271_0 = KF_U32_dadd(c, x1270_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1270; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1272; sp += 4;\n"
"A0 = x1271_0; pc = 1263; break; }\n"
"break;\n"
"}\n"
"case 1261: {\n"
"KW x1262_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1268_0 = KF_U32_dinc(c, x1262_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1262_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1269; sp += 4;\n"
"A0 = x1268_0; pc = 1263; break; }\n"
"break;\n"
"}\n"
"case 1279: {\n"
"sp -= 3; KW x1280_0 = KQ_ST(sp + 0); KW x1280 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1281_0 = x1280_0; KAUTO x1281_1 = x1280; KW x1281 = k_bnode(c, 2); c->H[KIX(c, x1281) + 0] = x1281_0; c->H[KIX(c, x1281) + 1] = x1281_1; x1281; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1276: {\n"
"sp -= 3; KW x1277_0 = KQ_ST(sp + 0); KW x1277 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1278_0 = KF_U32_dadd(c, x1277_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1277; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1279; sp += 4;\n"
"A0 = x1278_0; pc = 1261; break; }\n"
"break;\n"
"}\n"
"case 1259: {\n"
"KW x1260_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1275_0 = KF_U32_dinc(c, x1260_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1260_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1276; sp += 4;\n"
"A0 = x1275_0; pc = 1261; break; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make_x37s3867092194x8061040(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 1298, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 1300: {\n"
"KW x1301_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x1302 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x1301_0))));\n"
"KW x1303 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x1301_0, 2u))));\n"
"RV = ({ KAUTO x1304_0 = x1302; KAUTO x1304_1 = x1303; KW x1304 = k_bnode(c, 2); c->H[KIX(c, x1304) + 0] = x1304_0; c->H[KIX(c, x1304) + 1] = x1304_1; x1304; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1309: {\n"
"sp -= 3; KW x1310_0 = KQ_ST(sp + 0); KW x1310 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"RV = ({ KAUTO x1311_0 = x1310_0; KAUTO x1311_1 = x1310; KW x1311 = k_bnode(c, 2); c->H[KIX(c, x1311) + 0] = x1311_0; c->H[KIX(c, x1311) + 1] = x1311_1; x1311; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"case 1306: {\n"
"sp -= 3; KW x1307_0 = KQ_ST(sp + 0); KW x1307 = k_region(c, KQ_ST(sp + 1), KQ_ST(sp + 2), RV);\n"
"{ KAUTO x1308_0 = KF_U32_dadd(c, x1307_0, 2u); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1307; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1309; sp += 4;\n"
"A0 = x1308_0; pc = 1300; break; }\n"
"break;\n"
"}\n"
"case 1298: {\n"
"KW x1299_0 = A0; \n"
"K_TREE_MARK(34);\n"
"{ KAUTO x1305_0 = KF_U32_dinc(c, x1299_0); if (sp + 4 > KR_WORDS) { *ok = false; return 0; }\n"
"KQ_ST(sp + 0) = x1299_0; KQ_ST(sp + 1) = c->hp; KQ_ST(sp + 2) = c->he; KQ_ST(sp + 3) = 1306; sp += 4;\n"
"A0 = x1305_0; pc = 1300; break; }\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW KQ_make_x37s1860454509x8031249(KTHR KCtx *c, KW p0, KTHR bool *ok) {\n"
"KQ_STACK; K_TREE_STACK;\n"
"KW sp = 0, pc = 1319, RV = 0, st = c->kqlim;\n"
"KW A0 = p0;\n"
"KW A1 = 0;\n"
"KW A2 = 0;\n"
"KW A3 = 0;\n"
"KW A4 = 0;\n"
"KW A5 = 0;\n"
"KW A6 = 0;\n"
"KW A7 = 0;\n"
"KW A8 = 0;\n"
"KW A9 = 0;\n"
"KW A10 = 0;\n"
"KW A11 = 0;\n"
"for (;;) {\n"
"if (st-- == 0 || c->err != 0) { *ok = false; return 0; }\n"
"switch (pc) {\n"
"case 1319: {\n"
"KW x1320_0 = A0; \n"
"K_TREE_MARK(34);\n"
"KW x1321 = ((KX_make_x37s509762208x8001458(c, KF_U32_dinc(c, x1320_0))));\n"
"KW x1322 = ((KX_make_x37s509762208x8001458(c, KF_U32_dadd(c, x1320_0, 2u))));\n"
"RV = ({ KAUTO x1323_0 = x1321; KAUTO x1323_1 = x1322; KW x1323 = k_bnode(c, 2); c->H[KIX(c, x1323) + 0] = x1323_0; c->H[KIX(c, x1323) + 1] = x1323_1; x1323; });\n"
"K_TREE_RET;\n"
"if (sp == 0) return RV;\n"
"sp -= 1; pc = KQ_ST(sp); break;\n"
"break;\n"
"}\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"}\n"
"\n"
"KINLINE KW k_kq(KTHR KCtx *c, KTHR bool *ok) {\n"
"switch (c->kq) {\n"
"case 1286: return KQ_make_x37s1860454509x8031249(c, c->kqa[0], ok);\n"
"case 1247: return KQ_make_x37s3867092194x8061040(c, c->kqa[0], ok);\n"
"case 1199: return KQ_make_x37s1586577935x8090831(c, c->kqa[0], ok);\n"
"case 1142: return KQ_make_x37s2405009636x8120622(c, c->kqa[0], ok);\n"
"case 1076: return KQ_make_x37s3239606481x8150413(c, c->kqa[0], ok);\n"
"case 1001: return KQ_make_x37s32637286x8180204(c, c->kqa[0], ok);\n"
"case 917: return KQ_make_x37s1291691603x8209995(c, c->kqa[0], ok);\n"
"case 824: return KQ_make_x37s2491568216x8239786(c, c->kqa[0], ok);\n"
"case 722: return KQ_make_x37s3305376709x8269577(c, c->kqa[0], ok);\n"
"case 611: return KQ_make_x37s1953093269x247193397(c, c->kqa[0], ok);\n"
"case 491: return KQ_make_x37s4233607528x247223188(c, c->kqa[0], ok);\n"
"case 362: return KQ_make_x37s2689494263x247252979(c, c->kqa[0], ok);\n"
"case 224: return KQ_make_x37s675041226x247282770(c, c->kqa[0], ok);\n"
"case 48: return KQ_make_x37s3795296409x247312561(c, c->kqa[0], ok);\n"
"case 8: return KQ_sum(c, c->kqa[0], ok);\n"
"case 10: return KQ_rounds(c, c->kqa[0], c->kqa[1], ok);\n"
"case 12: return KQ_make(c, c->kqa[0], c->kqa[1], ok);\n"
"default:\n"
"*ok = false;\n"
"return 0;\n"
"}\n"
"}\n"
"#ifndef __METAL_VERSION__\n"
"#define K_KQH_LIST \n"
"#endif\n"
"\n"
"KINLINE void k_cases(KTHR KCtx *c) {\n"
"switch (c->pc) {\n"
"case 13: {\n"
"{ KW nf = KPUSH(14, 12);\n"
"KARG(nf, 0) = KS(0);\n"
"KARG(nf, 1) = KS(1);\n"
"KFP = nf; KPC = 12; }\n"
"break;\n"
"}\n"
"case 14: {\n"
"KS(2) = KRV;\n"
"KRET(KS(2));\n"
"break;\n"
"}\n"
"case 12: {\n"
"KS(2) = KS(0);\n"
"if ((KS(2)) == 0) { KPC = 15; } else if (k_nge(c, KS(2), 1)) { KPC = 16; } else { k_fail(c, KE_MATCH); }\n"
"break;\n"
"}\n"
"case 15: {\n"
"KS(3) = KS(1);\n"
"KRET(KLI(0, KS(3)));\n"
"break;\n"
"}\n"
"case 16: {\n"
"KPC = KFORK ? 17 : 18;\n"
"break;\n"
"}\n"
"case 18: {\n"
"KS(7) = ((KS(2)) - 1);\n"
"KS(8) = KS(1);\n"
"KS(9) = KF_U32_dinc(c, KS(8));\n"
"c->kq = 12; c->kqret = 21; c->kqfb = 23;\n"
"c->kqa[0] = KS(7);\n"
"c->kqa[1] = KS(9);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 23: {\n"
"{ KW nf = KPUSH(21, 12);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KARG(nf, 1) = c->kqa[1];\n"
"KFP = nf; KPC = 12; }\n"
"break;\n"
"}\n"
"case 21: {\n"
"KS(4) = KRV;\n"
"KPC = 22;\n"
"break;\n"
"}\n"
"case 22: {\n"
"KS(10) = ((KS(2)) - 1);\n"
"KS(11) = KS(1);\n"
"KS(12) = 2u;\n"
"KS(13) = KF_U32_dadd(c, KS(11), KS(12));\n"
"c->kq = 12; c->kqret = 24; c->kqfb = 26;\n"
"c->kqa[0] = KS(10);\n"
"c->kqa[1] = KS(13);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 26: {\n"
"{ KW nf = KPUSH(24, 12);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KARG(nf, 1) = c->kqa[1];\n"
"KFP = nf; KPC = 12; }\n"
"break;\n"
"}\n"
"case 24: {\n"
"KS(5) = KRV;\n"
"KPC = 25;\n"
"break;\n"
"}\n"
"case 25: {\n"
"KPC = 20;\n"
"break;\n"
"}\n"
"case 27: {\n"
"KS(3) = KS(1);\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"{ KW nf = KPUSH(28, 12);\n"
"KARG(nf, 0) = KS(3);\n"
"KARG(nf, 1) = KS(5);\n"
"KFP = nf; KPC = 12; }\n"
"break;\n"
"}\n"
"case 28: {\n"
"KS(6) = KRV;\n"
"KRET(KS(6));\n"
"break;\n"
"}\n"
"case 29: {\n"
"KS(3) = KS(1);\n"
"KS(4) = KS(0);\n"
"KS(5) = 2u;\n"
"KS(6) = KF_U32_dadd(c, KS(4), KS(5));\n"
"{ KW nf = KPUSH(30, 12);\n"
"KARG(nf, 0) = KS(3);\n"
"KARG(nf, 1) = KS(6);\n"
"KFP = nf; KPC = 12; }\n"
"break;\n"
"}\n"
"case 30: {\n"
"KS(7) = KRV;\n"
"KRET(KS(7));\n"
"break;\n"
"}\n"
"case 17: {\n"
"{ KW p = k_alloc(c, 5); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 27; c->H[w + 1] = 3; c->H[w + 2] = 2;\n"
"c->H[w + 3] = KS(1);\n"
"c->H[w + 4] = ((KS(2)) - 1);\n"
"KS(14) = p; }\n"
"KS(15) = KS(14);\n"
"{ KW p = k_alloc(c, 5); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 29; c->H[w + 1] = 3; c->H[w + 2] = 2;\n"
"c->H[w + 3] = KS(1);\n"
"c->H[w + 4] = ((KS(2)) - 1);\n"
"KS(16) = p; }\n"
"KS(17) = KS(16);\n"
"KS(6) = k_join_new(c, 2, 19);\n"
"if (!k_push_task(c, PC_TASK, KS(6), KS(15), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(17), 0, 31);\n"
"break;\n"
"}\n"
"case 31: {\n"
"KS(18) = KRV;\n"
"k_arrive(c, KS(6), 1, KS(18));\n"
"break;\n"
"}\n"
"case 19: {\n"
"KS(4) = c->H[KS(6) + 4];\n"
"KS(5) = c->H[KS(6) + 5];\n"
"KPC = 20;\n"
"break;\n"
"}\n"
"case 20: {\n"
"KS(19) = KS(4);\n"
"KS(20) = KS(5);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(19);\n"
"c->H[w + 1] = KS(20);\n"
"KS(21) = p; }\n"
"KRET(KS(21));\n"
"break;\n"
"}\n"
"case 11: {\n"
"c->kq = 10; c->kqret = 43; c->kqfb = 45 | K_KQLIM;\n"
"c->kqa[0] = KS(0);\n"
"c->kqa[1] = KS(1);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 45: {\n"
"{ KW nf = KPUSH(43, 10);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KARG(nf, 1) = c->kqa[1];\n"
"KFP = nf; KPC = 10; }\n"
"break;\n"
"}\n"
"case 43: {\n"
"KS(2) = KRV;\n"
"KPC = 44;\n"
"break;\n"
"}\n"
"case 44: {\n"
"KRET(KS(2));\n"
"break;\n"
"}\n"
"case 10: {\n"
"KS(2) = KS(0);\n"
"if ((KS(2)) == 0) { KPC = 46; } else if (k_nge(c, KS(2), 1)) { KPC = 47; } else { k_fail(c, KE_MATCH); }\n"
"break;\n"
"}\n"
"case 46: {\n"
"KRET(KS(1));\n"
"break;\n"
"}\n"
"case 47: {\n"
"KS(3) = ((KS(2)) - 1);\n"
"KS(4) = KS(1);\n"
"KS(5) = 1u;\n"
"{ KW nf = KPUSH(49, 48);\n"
"KARG(nf, 0) = KS(5);\n"
"KFP = nf; KPC = 48; }\n"
"break;\n"
"}\n"
"case 49: {\n"
"KS(6) = KRV;\n"
"KS(7) = KS(6);\n"
"{ KW nf = KPUSH(50, 8);\n"
"KARG(nf, 0) = KS(7);\n"
"KFP = nf; KPC = 8; }\n"
"break;\n"
"}\n"
"case 50: {\n"
"KS(8) = KRV;\n"
"KS(9) = KS(8);\n"
"KS(10) = KF_U32_dadd(c, KS(4), KS(9));\n"
"{ KS(0) = KS(3); KS(1) = KS(10); KPC = 10; }\n"
"break;\n"
"}\n"
"case 9: {\n"
"{ KW nf = KPUSH(193, 8);\n"
"KARG(nf, 0) = KS(0);\n"
"KFP = nf; KPC = 8; }\n"
"break;\n"
"}\n"
"case 193: {\n"
"KS(1) = KRV;\n"
"KRET(KS(1));\n"
"break;\n"
"}\n"
"case 8: {\n"
"KS(1) = KS(0);\n"
"if (KIS_LI(KS(1), 0)) { KPC = 194; } else if (!((KS(1)) & 1)) { KPC = 195; } else { k_fail(c, KE_MATCH); }\n"
"break;\n"
"}\n"
"case 194: {\n"
"KRET(KLI_V(KS(1)));\n"
"break;\n"
"}\n"
"case 195: {\n"
"KPC = KFORK ? 196 : 197;\n"
"break;\n"
"}\n"
"case 197: {\n"
"KS(5) = KFLB(KS(1), 0);\n"
"c->kq = 8; c->kqret = 200; c->kqfb = 202;\n"
"c->kqa[0] = KS(5);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 202: {\n"
"{ KW nf = KPUSH(200, 8);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 8; }\n"
"break;\n"
"}\n"
"case 200: {\n"
"KS(2) = KRV;\n"
"KPC = 201;\n"
"break;\n"
"}\n"
"case 201: {\n"
"KS(6) = KFLB(KS(1), 1);\n"
"c->kq = 8; c->kqret = 203; c->kqfb = 205;\n"
"c->kqa[0] = KS(6);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 205: {\n"
"{ KW nf = KPUSH(203, 8);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 8; }\n"
"break;\n"
"}\n"
"case 203: {\n"
"KS(3) = KRV;\n"
"KPC = 204;\n"
"break;\n"
"}\n"
"case 204: {\n"
"KPC = 199;\n"
"break;\n"
"}\n"
"case 206: {\n"
"KS(2) = KS(0);\n"
"{ KW nf = KPUSH(207, 8);\n"
"KARG(nf, 0) = KS(2);\n"
"KFP = nf; KPC = 8; }\n"
"break;\n"
"}\n"
"case 207: {\n"
"KS(3) = KRV;\n"
"KRET(KS(3));\n"
"break;\n"
"}\n"
"case 208: {\n"
"KS(2) = KS(0);\n"
"{ KW nf = KPUSH(209, 8);\n"
"KARG(nf, 0) = KS(2);\n"
"KFP = nf; KPC = 8; }\n"
"break;\n"
"}\n"
"case 209: {\n"
"KS(3) = KRV;\n"
"KRET(KS(3));\n"
"break;\n"
"}\n"
"case 196: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 206; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KFLB(KS(1), 0);\n"
"KS(7) = p; }\n"
"KS(8) = KS(7);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 208; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KFLB(KS(1), 1);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"KS(4) = k_join_new(c, 2, 198);\n"
"if (!k_push_task(c, PC_TASK, KS(4), KS(8), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(10), 0, 210);\n"
"break;\n"
"}\n"
"case 210: {\n"
"KS(11) = KRV;\n"
"k_arrive(c, KS(4), 1, KS(11));\n"
"break;\n"
"}\n"
"case 198: {\n"
"KS(2) = c->H[KS(4) + 4];\n"
"KS(3) = c->H[KS(4) + 5];\n"
"KPC = 199;\n"
"break;\n"
"}\n"
"case 199: {\n"
"KS(12) = KS(2);\n"
"KS(13) = KS(3);\n"
"KRET(KF_U32_dadd(c, KS(12), KS(13)));\n"
"break;\n"
"}\n"
"case 48: {\n"
"KPC = KFORK ? 220 : 221;\n"
"break;\n"
"}\n"
"case 221: {\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"c->kq = 224; c->kqret = 225; c->kqfb = 227;\n"
"c->kqa[0] = KS(5);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 227: {\n"
"{ KW nf = KPUSH(225, 224);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 224; }\n"
"break;\n"
"}\n"
"case 225: {\n"
"KS(1) = KRV;\n"
"KPC = 226;\n"
"break;\n"
"}\n"
"case 226: {\n"
"KS(6) = KS(0);\n"
"KS(7) = 2u;\n"
"KS(8) = KF_U32_dadd(c, KS(6), KS(7));\n"
"c->kq = 224; c->kqret = 228; c->kqfb = 230;\n"
"c->kqa[0] = KS(8);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 230: {\n"
"{ KW nf = KPUSH(228, 224);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 224; }\n"
"break;\n"
"}\n"
"case 228: {\n"
"KS(2) = KRV;\n"
"KPC = 229;\n"
"break;\n"
"}\n"
"case 229: {\n"
"KPC = 223;\n"
"break;\n"
"}\n"
"case 231: {\n"
"KS(2) = KS(0);\n"
"KS(3) = KF_U32_dinc(c, KS(2));\n"
"{ KW nf = KPUSH(232, 224);\n"
"KARG(nf, 0) = KS(3);\n"
"KFP = nf; KPC = 224; }\n"
"break;\n"
"}\n"
"case 232: {\n"
"KS(4) = KRV;\n"
"KRET(KS(4));\n"
"break;\n"
"}\n"
"case 233: {\n"
"KS(2) = KS(0);\n"
"KS(3) = 2u;\n"
"KS(4) = KF_U32_dadd(c, KS(2), KS(3));\n"
"{ KW nf = KPUSH(234, 224);\n"
"KARG(nf, 0) = KS(4);\n"
"KFP = nf; KPC = 224; }\n"
"break;\n"
"}\n"
"case 234: {\n"
"KS(5) = KRV;\n"
"KRET(KS(5));\n"
"break;\n"
"}\n"
"case 220: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 231; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 233; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(11) = p; }\n"
"KS(12) = KS(11);\n"
"KS(3) = k_join_new(c, 2, 222);\n"
"if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(12), 0, 235);\n"
"break;\n"
"}\n"
"case 235: {\n"
"KS(13) = KRV;\n"
"k_arrive(c, KS(3), 1, KS(13));\n"
"break;\n"
"}\n"
"case 222: {\n"
"KS(1) = c->H[KS(3) + 4];\n"
"KS(2) = c->H[KS(3) + 5];\n"
"KPC = 223;\n"
"break;\n"
"}\n"
"case 223: {\n"
"KS(14) = KS(1);\n"
"KS(15) = KS(2);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(14);\n"
"c->H[w + 1] = KS(15);\n"
"KS(16) = p; }\n"
"KRET(KS(16));\n"
"break;\n"
"}\n"
"case 224: {\n"
"KPC = KFORK ? 358 : 359;\n"
"break;\n"
"}\n"
"case 359: {\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"c->kq = 362; c->kqret = 363; c->kqfb = 365;\n"
"c->kqa[0] = KS(5);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 365: {\n"
"{ KW nf = KPUSH(363, 362);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 362; }\n"
"break;\n"
"}\n"
"case 363: {\n"
"KS(1) = KRV;\n"
"KPC = 364;\n"
"break;\n"
"}\n"
"case 364: {\n"
"KS(6) = KS(0);\n"
"KS(7) = 2u;\n"
"KS(8) = KF_U32_dadd(c, KS(6), KS(7));\n"
"c->kq = 362; c->kqret = 366; c->kqfb = 368;\n"
"c->kqa[0] = KS(8);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 368: {\n"
"{ KW nf = KPUSH(366, 362);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 362; }\n"
"break;\n"
"}\n"
"case 366: {\n"
"KS(2) = KRV;\n"
"KPC = 367;\n"
"break;\n"
"}\n"
"case 367: {\n"
"KPC = 361;\n"
"break;\n"
"}\n"
"case 369: {\n"
"KS(2) = KS(0);\n"
"KS(3) = KF_U32_dinc(c, KS(2));\n"
"{ KW nf = KPUSH(370, 362);\n"
"KARG(nf, 0) = KS(3);\n"
"KFP = nf; KPC = 362; }\n"
"break;\n"
"}\n"
"case 370: {\n"
"KS(4) = KRV;\n"
"KRET(KS(4));\n"
"break;\n"
"}\n"
"case 371: {\n"
"KS(2) = KS(0);\n"
"KS(3) = 2u;\n"
"KS(4) = KF_U32_dadd(c, KS(2), KS(3));\n"
"{ KW nf = KPUSH(372, 362);\n"
"KARG(nf, 0) = KS(4);\n"
"KFP = nf; KPC = 362; }\n"
"break;\n"
"}\n"
"case 372: {\n"
"KS(5) = KRV;\n"
"KRET(KS(5));\n"
"break;\n"
"}\n"
"case 358: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 369; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 371; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(11) = p; }\n"
"KS(12) = KS(11);\n"
"KS(3) = k_join_new(c, 2, 360);\n"
"if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(12), 0, 373);\n"
"break;\n"
"}\n"
"case 373: {\n"
"KS(13) = KRV;\n"
"k_arrive(c, KS(3), 1, KS(13));\n"
"break;\n"
"}\n"
"case 360: {\n"
"KS(1) = c->H[KS(3) + 4];\n"
"KS(2) = c->H[KS(3) + 5];\n"
"KPC = 361;\n"
"break;\n"
"}\n"
"case 361: {\n"
"KS(14) = KS(1);\n"
"KS(15) = KS(2);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(14);\n"
"c->H[w + 1] = KS(15);\n"
"KS(16) = p; }\n"
"KRET(KS(16));\n"
"break;\n"
"}\n"
"case 362: {\n"
"KPC = KFORK ? 487 : 488;\n"
"break;\n"
"}\n"
"case 488: {\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"c->kq = 491; c->kqret = 492; c->kqfb = 494;\n"
"c->kqa[0] = KS(5);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 494: {\n"
"{ KW nf = KPUSH(492, 491);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 491; }\n"
"break;\n"
"}\n"
"case 492: {\n"
"KS(1) = KRV;\n"
"KPC = 493;\n"
"break;\n"
"}\n"
"case 493: {\n"
"KS(6) = KS(0);\n"
"KS(7) = 2u;\n"
"KS(8) = KF_U32_dadd(c, KS(6), KS(7));\n"
"c->kq = 491; c->kqret = 495; c->kqfb = 497;\n"
"c->kqa[0] = KS(8);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 497: {\n"
"{ KW nf = KPUSH(495, 491);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 491; }\n"
"break;\n"
"}\n"
"case 495: {\n"
"KS(2) = KRV;\n"
"KPC = 496;\n"
"break;\n"
"}\n"
"case 496: {\n"
"KPC = 490;\n"
"break;\n"
"}\n"
"case 498: {\n"
"KS(2) = KS(0);\n"
"KS(3) = KF_U32_dinc(c, KS(2));\n"
"{ KW nf = KPUSH(499, 491);\n"
"KARG(nf, 0) = KS(3);\n"
"KFP = nf; KPC = 491; }\n"
"break;\n"
"}\n"
"case 499: {\n"
"KS(4) = KRV;\n"
"KRET(KS(4));\n"
"break;\n"
"}\n"
"case 500: {\n"
"KS(2) = KS(0);\n"
"KS(3) = 2u;\n"
"KS(4) = KF_U32_dadd(c, KS(2), KS(3));\n"
"{ KW nf = KPUSH(501, 491);\n"
"KARG(nf, 0) = KS(4);\n"
"KFP = nf; KPC = 491; }\n"
"break;\n"
"}\n"
"case 501: {\n"
"KS(5) = KRV;\n"
"KRET(KS(5));\n"
"break;\n"
"}\n"
"case 487: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 498; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 500; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(11) = p; }\n"
"KS(12) = KS(11);\n"
"KS(3) = k_join_new(c, 2, 489);\n"
"if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(12), 0, 502);\n"
"break;\n"
"}\n"
"case 502: {\n"
"KS(13) = KRV;\n"
"k_arrive(c, KS(3), 1, KS(13));\n"
"break;\n"
"}\n"
"case 489: {\n"
"KS(1) = c->H[KS(3) + 4];\n"
"KS(2) = c->H[KS(3) + 5];\n"
"KPC = 490;\n"
"break;\n"
"}\n"
"case 490: {\n"
"KS(14) = KS(1);\n"
"KS(15) = KS(2);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(14);\n"
"c->H[w + 1] = KS(15);\n"
"KS(16) = p; }\n"
"KRET(KS(16));\n"
"break;\n"
"}\n"
"case 491: {\n"
"KPC = KFORK ? 607 : 608;\n"
"break;\n"
"}\n"
"case 608: {\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"c->kq = 611; c->kqret = 612; c->kqfb = 614;\n"
"c->kqa[0] = KS(5);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 614: {\n"
"{ KW nf = KPUSH(612, 611);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 611; }\n"
"break;\n"
"}\n"
"case 612: {\n"
"KS(1) = KRV;\n"
"KPC = 613;\n"
"break;\n"
"}\n"
"case 613: {\n"
"KS(6) = KS(0);\n"
"KS(7) = 2u;\n"
"KS(8) = KF_U32_dadd(c, KS(6), KS(7));\n"
"c->kq = 611; c->kqret = 615; c->kqfb = 617;\n"
"c->kqa[0] = KS(8);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 617: {\n"
"{ KW nf = KPUSH(615, 611);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 611; }\n"
"break;\n"
"}\n"
"case 615: {\n"
"KS(2) = KRV;\n"
"KPC = 616;\n"
"break;\n"
"}\n"
"case 616: {\n"
"KPC = 610;\n"
"break;\n"
"}\n"
"case 618: {\n"
"KS(2) = KS(0);\n"
"KS(3) = KF_U32_dinc(c, KS(2));\n"
"{ KW nf = KPUSH(619, 611);\n"
"KARG(nf, 0) = KS(3);\n"
"KFP = nf; KPC = 611; }\n"
"break;\n"
"}\n"
"case 619: {\n"
"KS(4) = KRV;\n"
"KRET(KS(4));\n"
"break;\n"
"}\n"
"case 620: {\n"
"KS(2) = KS(0);\n"
"KS(3) = 2u;\n"
"KS(4) = KF_U32_dadd(c, KS(2), KS(3));\n"
"{ KW nf = KPUSH(621, 611);\n"
"KARG(nf, 0) = KS(4);\n"
"KFP = nf; KPC = 611; }\n"
"break;\n"
"}\n"
"case 621: {\n"
"KS(5) = KRV;\n"
"KRET(KS(5));\n"
"break;\n"
"}\n"
"case 607: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 618; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 620; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(11) = p; }\n"
"KS(12) = KS(11);\n"
"KS(3) = k_join_new(c, 2, 609);\n"
"if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(12), 0, 622);\n"
"break;\n"
"}\n"
"case 622: {\n"
"KS(13) = KRV;\n"
"k_arrive(c, KS(3), 1, KS(13));\n"
"break;\n"
"}\n"
"case 609: {\n"
"KS(1) = c->H[KS(3) + 4];\n"
"KS(2) = c->H[KS(3) + 5];\n"
"KPC = 610;\n"
"break;\n"
"}\n"
"case 610: {\n"
"KS(14) = KS(1);\n"
"KS(15) = KS(2);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(14);\n"
"c->H[w + 1] = KS(15);\n"
"KS(16) = p; }\n"
"KRET(KS(16));\n"
"break;\n"
"}\n"
"case 611: {\n"
"KPC = KFORK ? 718 : 719;\n"
"break;\n"
"}\n"
"case 719: {\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"c->kq = 722; c->kqret = 723; c->kqfb = 725;\n"
"c->kqa[0] = KS(5);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 725: {\n"
"{ KW nf = KPUSH(723, 722);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 722; }\n"
"break;\n"
"}\n"
"case 723: {\n"
"KS(1) = KRV;\n"
"KPC = 724;\n"
"break;\n"
"}\n"
"case 724: {\n"
"KS(6) = KS(0);\n"
"KS(7) = 2u;\n"
"KS(8) = KF_U32_dadd(c, KS(6), KS(7));\n"
"c->kq = 722; c->kqret = 726; c->kqfb = 728;\n"
"c->kqa[0] = KS(8);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 728: {\n"
"{ KW nf = KPUSH(726, 722);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 722; }\n"
"break;\n"
"}\n"
"case 726: {\n"
"KS(2) = KRV;\n"
"KPC = 727;\n"
"break;\n"
"}\n"
"case 727: {\n"
"KPC = 721;\n"
"break;\n"
"}\n"
"case 729: {\n"
"KS(2) = KS(0);\n"
"KS(3) = KF_U32_dinc(c, KS(2));\n"
"{ KW nf = KPUSH(730, 722);\n"
"KARG(nf, 0) = KS(3);\n"
"KFP = nf; KPC = 722; }\n"
"break;\n"
"}\n"
"case 730: {\n"
"KS(4) = KRV;\n"
"KRET(KS(4));\n"
"break;\n"
"}\n"
"case 731: {\n"
"KS(2) = KS(0);\n"
"KS(3) = 2u;\n"
"KS(4) = KF_U32_dadd(c, KS(2), KS(3));\n"
"{ KW nf = KPUSH(732, 722);\n"
"KARG(nf, 0) = KS(4);\n"
"KFP = nf; KPC = 722; }\n"
"break;\n"
"}\n"
"case 732: {\n"
"KS(5) = KRV;\n"
"KRET(KS(5));\n"
"break;\n"
"}\n"
"case 718: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 729; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 731; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(11) = p; }\n"
"KS(12) = KS(11);\n"
"KS(3) = k_join_new(c, 2, 720);\n"
"if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(12), 0, 733);\n"
"break;\n"
"}\n"
"case 733: {\n"
"KS(13) = KRV;\n"
"k_arrive(c, KS(3), 1, KS(13));\n"
"break;\n"
"}\n"
"case 720: {\n"
"KS(1) = c->H[KS(3) + 4];\n"
"KS(2) = c->H[KS(3) + 5];\n"
"KPC = 721;\n"
"break;\n"
"}\n"
"case 721: {\n"
"KS(14) = KS(1);\n"
"KS(15) = KS(2);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(14);\n"
"c->H[w + 1] = KS(15);\n"
"KS(16) = p; }\n"
"KRET(KS(16));\n"
"break;\n"
"}\n"
"case 722: {\n"
"KPC = KFORK ? 820 : 821;\n"
"break;\n"
"}\n"
"case 821: {\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"c->kq = 824; c->kqret = 825; c->kqfb = 827;\n"
"c->kqa[0] = KS(5);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 827: {\n"
"{ KW nf = KPUSH(825, 824);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 824; }\n"
"break;\n"
"}\n"
"case 825: {\n"
"KS(1) = KRV;\n"
"KPC = 826;\n"
"break;\n"
"}\n"
"case 826: {\n"
"KS(6) = KS(0);\n"
"KS(7) = 2u;\n"
"KS(8) = KF_U32_dadd(c, KS(6), KS(7));\n"
"c->kq = 824; c->kqret = 828; c->kqfb = 830;\n"
"c->kqa[0] = KS(8);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 830: {\n"
"{ KW nf = KPUSH(828, 824);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 824; }\n"
"break;\n"
"}\n"
"case 828: {\n"
"KS(2) = KRV;\n"
"KPC = 829;\n"
"break;\n"
"}\n"
"case 829: {\n"
"KPC = 823;\n"
"break;\n"
"}\n"
"case 831: {\n"
"KS(2) = KS(0);\n"
"KS(3) = KF_U32_dinc(c, KS(2));\n"
"{ KW nf = KPUSH(832, 824);\n"
"KARG(nf, 0) = KS(3);\n"
"KFP = nf; KPC = 824; }\n"
"break;\n"
"}\n"
"case 832: {\n"
"KS(4) = KRV;\n"
"KRET(KS(4));\n"
"break;\n"
"}\n"
"case 833: {\n"
"KS(2) = KS(0);\n"
"KS(3) = 2u;\n"
"KS(4) = KF_U32_dadd(c, KS(2), KS(3));\n"
"{ KW nf = KPUSH(834, 824);\n"
"KARG(nf, 0) = KS(4);\n"
"KFP = nf; KPC = 824; }\n"
"break;\n"
"}\n"
"case 834: {\n"
"KS(5) = KRV;\n"
"KRET(KS(5));\n"
"break;\n"
"}\n"
"case 820: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 831; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 833; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(11) = p; }\n"
"KS(12) = KS(11);\n"
"KS(3) = k_join_new(c, 2, 822);\n"
"if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(12), 0, 835);\n"
"break;\n"
"}\n"
"case 835: {\n"
"KS(13) = KRV;\n"
"k_arrive(c, KS(3), 1, KS(13));\n"
"break;\n"
"}\n"
"case 822: {\n"
"KS(1) = c->H[KS(3) + 4];\n"
"KS(2) = c->H[KS(3) + 5];\n"
"KPC = 823;\n"
"break;\n"
"}\n"
"case 823: {\n"
"KS(14) = KS(1);\n"
"KS(15) = KS(2);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(14);\n"
"c->H[w + 1] = KS(15);\n"
"KS(16) = p; }\n"
"KRET(KS(16));\n"
"break;\n"
"}\n"
"case 824: {\n"
"KPC = KFORK ? 913 : 914;\n"
"break;\n"
"}\n"
"case 914: {\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"c->kq = 917; c->kqret = 918; c->kqfb = 920;\n"
"c->kqa[0] = KS(5);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 920: {\n"
"{ KW nf = KPUSH(918, 917);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 917; }\n"
"break;\n"
"}\n"
"case 918: {\n"
"KS(1) = KRV;\n"
"KPC = 919;\n"
"break;\n"
"}\n"
"case 919: {\n"
"KS(6) = KS(0);\n"
"KS(7) = 2u;\n"
"KS(8) = KF_U32_dadd(c, KS(6), KS(7));\n"
"c->kq = 917; c->kqret = 921; c->kqfb = 923;\n"
"c->kqa[0] = KS(8);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 923: {\n"
"{ KW nf = KPUSH(921, 917);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 917; }\n"
"break;\n"
"}\n"
"case 921: {\n"
"KS(2) = KRV;\n"
"KPC = 922;\n"
"break;\n"
"}\n"
"case 922: {\n"
"KPC = 916;\n"
"break;\n"
"}\n"
"case 924: {\n"
"KS(2) = KS(0);\n"
"KS(3) = KF_U32_dinc(c, KS(2));\n"
"{ KW nf = KPUSH(925, 917);\n"
"KARG(nf, 0) = KS(3);\n"
"KFP = nf; KPC = 917; }\n"
"break;\n"
"}\n"
"case 925: {\n"
"KS(4) = KRV;\n"
"KRET(KS(4));\n"
"break;\n"
"}\n"
"case 926: {\n"
"KS(2) = KS(0);\n"
"KS(3) = 2u;\n"
"KS(4) = KF_U32_dadd(c, KS(2), KS(3));\n"
"{ KW nf = KPUSH(927, 917);\n"
"KARG(nf, 0) = KS(4);\n"
"KFP = nf; KPC = 917; }\n"
"break;\n"
"}\n"
"case 927: {\n"
"KS(5) = KRV;\n"
"KRET(KS(5));\n"
"break;\n"
"}\n"
"case 913: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 924; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 926; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(11) = p; }\n"
"KS(12) = KS(11);\n"
"KS(3) = k_join_new(c, 2, 915);\n"
"if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(12), 0, 928);\n"
"break;\n"
"}\n"
"case 928: {\n"
"KS(13) = KRV;\n"
"k_arrive(c, KS(3), 1, KS(13));\n"
"break;\n"
"}\n"
"case 915: {\n"
"KS(1) = c->H[KS(3) + 4];\n"
"KS(2) = c->H[KS(3) + 5];\n"
"KPC = 916;\n"
"break;\n"
"}\n"
"case 916: {\n"
"KS(14) = KS(1);\n"
"KS(15) = KS(2);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(14);\n"
"c->H[w + 1] = KS(15);\n"
"KS(16) = p; }\n"
"KRET(KS(16));\n"
"break;\n"
"}\n"
"case 917: {\n"
"KPC = KFORK ? 997 : 998;\n"
"break;\n"
"}\n"
"case 998: {\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"c->kq = 1001; c->kqret = 1002; c->kqfb = 1004;\n"
"c->kqa[0] = KS(5);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 1004: {\n"
"{ KW nf = KPUSH(1002, 1001);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 1001; }\n"
"break;\n"
"}\n"
"case 1002: {\n"
"KS(1) = KRV;\n"
"KPC = 1003;\n"
"break;\n"
"}\n"
"case 1003: {\n"
"KS(6) = KS(0);\n"
"KS(7) = 2u;\n"
"KS(8) = KF_U32_dadd(c, KS(6), KS(7));\n"
"c->kq = 1001; c->kqret = 1005; c->kqfb = 1007;\n"
"c->kqa[0] = KS(8);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 1007: {\n"
"{ KW nf = KPUSH(1005, 1001);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 1001; }\n"
"break;\n"
"}\n"
"case 1005: {\n"
"KS(2) = KRV;\n"
"KPC = 1006;\n"
"break;\n"
"}\n"
"case 1006: {\n"
"KPC = 1000;\n"
"break;\n"
"}\n"
"case 1008: {\n"
"KS(2) = KS(0);\n"
"KS(3) = KF_U32_dinc(c, KS(2));\n"
"{ KW nf = KPUSH(1009, 1001);\n"
"KARG(nf, 0) = KS(3);\n"
"KFP = nf; KPC = 1001; }\n"
"break;\n"
"}\n"
"case 1009: {\n"
"KS(4) = KRV;\n"
"KRET(KS(4));\n"
"break;\n"
"}\n"
"case 1010: {\n"
"KS(2) = KS(0);\n"
"KS(3) = 2u;\n"
"KS(4) = KF_U32_dadd(c, KS(2), KS(3));\n"
"{ KW nf = KPUSH(1011, 1001);\n"
"KARG(nf, 0) = KS(4);\n"
"KFP = nf; KPC = 1001; }\n"
"break;\n"
"}\n"
"case 1011: {\n"
"KS(5) = KRV;\n"
"KRET(KS(5));\n"
"break;\n"
"}\n"
"case 997: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 1008; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 1010; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(11) = p; }\n"
"KS(12) = KS(11);\n"
"KS(3) = k_join_new(c, 2, 999);\n"
"if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(12), 0, 1012);\n"
"break;\n"
"}\n"
"case 1012: {\n"
"KS(13) = KRV;\n"
"k_arrive(c, KS(3), 1, KS(13));\n"
"break;\n"
"}\n"
"case 999: {\n"
"KS(1) = c->H[KS(3) + 4];\n"
"KS(2) = c->H[KS(3) + 5];\n"
"KPC = 1000;\n"
"break;\n"
"}\n"
"case 1000: {\n"
"KS(14) = KS(1);\n"
"KS(15) = KS(2);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(14);\n"
"c->H[w + 1] = KS(15);\n"
"KS(16) = p; }\n"
"KRET(KS(16));\n"
"break;\n"
"}\n"
"case 1001: {\n"
"KPC = KFORK ? 1072 : 1073;\n"
"break;\n"
"}\n"
"case 1073: {\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"c->kq = 1076; c->kqret = 1077; c->kqfb = 1079;\n"
"c->kqa[0] = KS(5);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 1079: {\n"
"{ KW nf = KPUSH(1077, 1076);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 1076; }\n"
"break;\n"
"}\n"
"case 1077: {\n"
"KS(1) = KRV;\n"
"KPC = 1078;\n"
"break;\n"
"}\n"
"case 1078: {\n"
"KS(6) = KS(0);\n"
"KS(7) = 2u;\n"
"KS(8) = KF_U32_dadd(c, KS(6), KS(7));\n"
"c->kq = 1076; c->kqret = 1080; c->kqfb = 1082;\n"
"c->kqa[0] = KS(8);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 1082: {\n"
"{ KW nf = KPUSH(1080, 1076);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 1076; }\n"
"break;\n"
"}\n"
"case 1080: {\n"
"KS(2) = KRV;\n"
"KPC = 1081;\n"
"break;\n"
"}\n"
"case 1081: {\n"
"KPC = 1075;\n"
"break;\n"
"}\n"
"case 1083: {\n"
"KS(2) = KS(0);\n"
"KS(3) = KF_U32_dinc(c, KS(2));\n"
"{ KW nf = KPUSH(1084, 1076);\n"
"KARG(nf, 0) = KS(3);\n"
"KFP = nf; KPC = 1076; }\n"
"break;\n"
"}\n"
"case 1084: {\n"
"KS(4) = KRV;\n"
"KRET(KS(4));\n"
"break;\n"
"}\n"
"case 1085: {\n"
"KS(2) = KS(0);\n"
"KS(3) = 2u;\n"
"KS(4) = KF_U32_dadd(c, KS(2), KS(3));\n"
"{ KW nf = KPUSH(1086, 1076);\n"
"KARG(nf, 0) = KS(4);\n"
"KFP = nf; KPC = 1076; }\n"
"break;\n"
"}\n"
"case 1086: {\n"
"KS(5) = KRV;\n"
"KRET(KS(5));\n"
"break;\n"
"}\n"
"case 1072: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 1083; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 1085; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(11) = p; }\n"
"KS(12) = KS(11);\n"
"KS(3) = k_join_new(c, 2, 1074);\n"
"if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(12), 0, 1087);\n"
"break;\n"
"}\n"
"case 1087: {\n"
"KS(13) = KRV;\n"
"k_arrive(c, KS(3), 1, KS(13));\n"
"break;\n"
"}\n"
"case 1074: {\n"
"KS(1) = c->H[KS(3) + 4];\n"
"KS(2) = c->H[KS(3) + 5];\n"
"KPC = 1075;\n"
"break;\n"
"}\n"
"case 1075: {\n"
"KS(14) = KS(1);\n"
"KS(15) = KS(2);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(14);\n"
"c->H[w + 1] = KS(15);\n"
"KS(16) = p; }\n"
"KRET(KS(16));\n"
"break;\n"
"}\n"
"case 1076: {\n"
"KPC = KFORK ? 1138 : 1139;\n"
"break;\n"
"}\n"
"case 1139: {\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"c->kq = 1142; c->kqret = 1143; c->kqfb = 1145;\n"
"c->kqa[0] = KS(5);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 1145: {\n"
"{ KW nf = KPUSH(1143, 1142);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 1142; }\n"
"break;\n"
"}\n"
"case 1143: {\n"
"KS(1) = KRV;\n"
"KPC = 1144;\n"
"break;\n"
"}\n"
"case 1144: {\n"
"KS(6) = KS(0);\n"
"KS(7) = 2u;\n"
"KS(8) = KF_U32_dadd(c, KS(6), KS(7));\n"
"c->kq = 1142; c->kqret = 1146; c->kqfb = 1148;\n"
"c->kqa[0] = KS(8);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 1148: {\n"
"{ KW nf = KPUSH(1146, 1142);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 1142; }\n"
"break;\n"
"}\n"
"case 1146: {\n"
"KS(2) = KRV;\n"
"KPC = 1147;\n"
"break;\n"
"}\n"
"case 1147: {\n"
"KPC = 1141;\n"
"break;\n"
"}\n"
"case 1149: {\n"
"KS(2) = KS(0);\n"
"KS(3) = KF_U32_dinc(c, KS(2));\n"
"{ KW nf = KPUSH(1150, 1142);\n"
"KARG(nf, 0) = KS(3);\n"
"KFP = nf; KPC = 1142; }\n"
"break;\n"
"}\n"
"case 1150: {\n"
"KS(4) = KRV;\n"
"KRET(KS(4));\n"
"break;\n"
"}\n"
"case 1151: {\n"
"KS(2) = KS(0);\n"
"KS(3) = 2u;\n"
"KS(4) = KF_U32_dadd(c, KS(2), KS(3));\n"
"{ KW nf = KPUSH(1152, 1142);\n"
"KARG(nf, 0) = KS(4);\n"
"KFP = nf; KPC = 1142; }\n"
"break;\n"
"}\n"
"case 1152: {\n"
"KS(5) = KRV;\n"
"KRET(KS(5));\n"
"break;\n"
"}\n"
"case 1138: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 1149; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 1151; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(11) = p; }\n"
"KS(12) = KS(11);\n"
"KS(3) = k_join_new(c, 2, 1140);\n"
"if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(12), 0, 1153);\n"
"break;\n"
"}\n"
"case 1153: {\n"
"KS(13) = KRV;\n"
"k_arrive(c, KS(3), 1, KS(13));\n"
"break;\n"
"}\n"
"case 1140: {\n"
"KS(1) = c->H[KS(3) + 4];\n"
"KS(2) = c->H[KS(3) + 5];\n"
"KPC = 1141;\n"
"break;\n"
"}\n"
"case 1141: {\n"
"KS(14) = KS(1);\n"
"KS(15) = KS(2);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(14);\n"
"c->H[w + 1] = KS(15);\n"
"KS(16) = p; }\n"
"KRET(KS(16));\n"
"break;\n"
"}\n"
"case 1142: {\n"
"KPC = KFORK ? 1195 : 1196;\n"
"break;\n"
"}\n"
"case 1196: {\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"c->kq = 1199; c->kqret = 1200; c->kqfb = 1202;\n"
"c->kqa[0] = KS(5);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 1202: {\n"
"{ KW nf = KPUSH(1200, 1199);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 1199; }\n"
"break;\n"
"}\n"
"case 1200: {\n"
"KS(1) = KRV;\n"
"KPC = 1201;\n"
"break;\n"
"}\n"
"case 1201: {\n"
"KS(6) = KS(0);\n"
"KS(7) = 2u;\n"
"KS(8) = KF_U32_dadd(c, KS(6), KS(7));\n"
"c->kq = 1199; c->kqret = 1203; c->kqfb = 1205;\n"
"c->kqa[0] = KS(8);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 1205: {\n"
"{ KW nf = KPUSH(1203, 1199);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 1199; }\n"
"break;\n"
"}\n"
"case 1203: {\n"
"KS(2) = KRV;\n"
"KPC = 1204;\n"
"break;\n"
"}\n"
"case 1204: {\n"
"KPC = 1198;\n"
"break;\n"
"}\n"
"case 1206: {\n"
"KS(2) = KS(0);\n"
"KS(3) = KF_U32_dinc(c, KS(2));\n"
"{ KW nf = KPUSH(1207, 1199);\n"
"KARG(nf, 0) = KS(3);\n"
"KFP = nf; KPC = 1199; }\n"
"break;\n"
"}\n"
"case 1207: {\n"
"KS(4) = KRV;\n"
"KRET(KS(4));\n"
"break;\n"
"}\n"
"case 1208: {\n"
"KS(2) = KS(0);\n"
"KS(3) = 2u;\n"
"KS(4) = KF_U32_dadd(c, KS(2), KS(3));\n"
"{ KW nf = KPUSH(1209, 1199);\n"
"KARG(nf, 0) = KS(4);\n"
"KFP = nf; KPC = 1199; }\n"
"break;\n"
"}\n"
"case 1209: {\n"
"KS(5) = KRV;\n"
"KRET(KS(5));\n"
"break;\n"
"}\n"
"case 1195: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 1206; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 1208; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(11) = p; }\n"
"KS(12) = KS(11);\n"
"KS(3) = k_join_new(c, 2, 1197);\n"
"if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(12), 0, 1210);\n"
"break;\n"
"}\n"
"case 1210: {\n"
"KS(13) = KRV;\n"
"k_arrive(c, KS(3), 1, KS(13));\n"
"break;\n"
"}\n"
"case 1197: {\n"
"KS(1) = c->H[KS(3) + 4];\n"
"KS(2) = c->H[KS(3) + 5];\n"
"KPC = 1198;\n"
"break;\n"
"}\n"
"case 1198: {\n"
"KS(14) = KS(1);\n"
"KS(15) = KS(2);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(14);\n"
"c->H[w + 1] = KS(15);\n"
"KS(16) = p; }\n"
"KRET(KS(16));\n"
"break;\n"
"}\n"
"case 1199: {\n"
"KPC = KFORK ? 1243 : 1244;\n"
"break;\n"
"}\n"
"case 1244: {\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"c->kq = 1247; c->kqret = 1248; c->kqfb = 1250;\n"
"c->kqa[0] = KS(5);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 1250: {\n"
"{ KW nf = KPUSH(1248, 1247);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 1247; }\n"
"break;\n"
"}\n"
"case 1248: {\n"
"KS(1) = KRV;\n"
"KPC = 1249;\n"
"break;\n"
"}\n"
"case 1249: {\n"
"KS(6) = KS(0);\n"
"KS(7) = 2u;\n"
"KS(8) = KF_U32_dadd(c, KS(6), KS(7));\n"
"c->kq = 1247; c->kqret = 1251; c->kqfb = 1253;\n"
"c->kqa[0] = KS(8);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 1253: {\n"
"{ KW nf = KPUSH(1251, 1247);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 1247; }\n"
"break;\n"
"}\n"
"case 1251: {\n"
"KS(2) = KRV;\n"
"KPC = 1252;\n"
"break;\n"
"}\n"
"case 1252: {\n"
"KPC = 1246;\n"
"break;\n"
"}\n"
"case 1254: {\n"
"KS(2) = KS(0);\n"
"KS(3) = KF_U32_dinc(c, KS(2));\n"
"{ KW nf = KPUSH(1255, 1247);\n"
"KARG(nf, 0) = KS(3);\n"
"KFP = nf; KPC = 1247; }\n"
"break;\n"
"}\n"
"case 1255: {\n"
"KS(4) = KRV;\n"
"KRET(KS(4));\n"
"break;\n"
"}\n"
"case 1256: {\n"
"KS(2) = KS(0);\n"
"KS(3) = 2u;\n"
"KS(4) = KF_U32_dadd(c, KS(2), KS(3));\n"
"{ KW nf = KPUSH(1257, 1247);\n"
"KARG(nf, 0) = KS(4);\n"
"KFP = nf; KPC = 1247; }\n"
"break;\n"
"}\n"
"case 1257: {\n"
"KS(5) = KRV;\n"
"KRET(KS(5));\n"
"break;\n"
"}\n"
"case 1243: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 1254; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 1256; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(11) = p; }\n"
"KS(12) = KS(11);\n"
"KS(3) = k_join_new(c, 2, 1245);\n"
"if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(12), 0, 1258);\n"
"break;\n"
"}\n"
"case 1258: {\n"
"KS(13) = KRV;\n"
"k_arrive(c, KS(3), 1, KS(13));\n"
"break;\n"
"}\n"
"case 1245: {\n"
"KS(1) = c->H[KS(3) + 4];\n"
"KS(2) = c->H[KS(3) + 5];\n"
"KPC = 1246;\n"
"break;\n"
"}\n"
"case 1246: {\n"
"KS(14) = KS(1);\n"
"KS(15) = KS(2);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(14);\n"
"c->H[w + 1] = KS(15);\n"
"KS(16) = p; }\n"
"KRET(KS(16));\n"
"break;\n"
"}\n"
"case 1247: {\n"
"KPC = KFORK ? 1282 : 1283;\n"
"break;\n"
"}\n"
"case 1283: {\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"c->kq = 1286; c->kqret = 1287; c->kqfb = 1289;\n"
"c->kqa[0] = KS(5);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 1289: {\n"
"{ KW nf = KPUSH(1287, 1286);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 1286; }\n"
"break;\n"
"}\n"
"case 1287: {\n"
"KS(1) = KRV;\n"
"KPC = 1288;\n"
"break;\n"
"}\n"
"case 1288: {\n"
"KS(6) = KS(0);\n"
"KS(7) = 2u;\n"
"KS(8) = KF_U32_dadd(c, KS(6), KS(7));\n"
"c->kq = 1286; c->kqret = 1290; c->kqfb = 1292;\n"
"c->kqa[0] = KS(8);\n"
"KPC = PC_KQ;\n"
"break;\n"
"}\n"
"case 1292: {\n"
"{ KW nf = KPUSH(1290, 1286);\n"
"KARG(nf, 0) = c->kqa[0];\n"
"KFP = nf; KPC = 1286; }\n"
"break;\n"
"}\n"
"case 1290: {\n"
"KS(2) = KRV;\n"
"KPC = 1291;\n"
"break;\n"
"}\n"
"case 1291: {\n"
"KPC = 1285;\n"
"break;\n"
"}\n"
"case 1293: {\n"
"KS(2) = KS(0);\n"
"KS(3) = KF_U32_dinc(c, KS(2));\n"
"{ KW nf = KPUSH(1294, 1286);\n"
"KARG(nf, 0) = KS(3);\n"
"KFP = nf; KPC = 1286; }\n"
"break;\n"
"}\n"
"case 1294: {\n"
"KS(4) = KRV;\n"
"KRET(KS(4));\n"
"break;\n"
"}\n"
"case 1295: {\n"
"KS(2) = KS(0);\n"
"KS(3) = 2u;\n"
"KS(4) = KF_U32_dadd(c, KS(2), KS(3));\n"
"{ KW nf = KPUSH(1296, 1286);\n"
"KARG(nf, 0) = KS(4);\n"
"KFP = nf; KPC = 1286; }\n"
"break;\n"
"}\n"
"case 1296: {\n"
"KS(5) = KRV;\n"
"KRET(KS(5));\n"
"break;\n"
"}\n"
"case 1282: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 1293; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 1295; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(11) = p; }\n"
"KS(12) = KS(11);\n"
"KS(3) = k_join_new(c, 2, 1284);\n"
"if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(12), 0, 1297);\n"
"break;\n"
"}\n"
"case 1297: {\n"
"KS(13) = KRV;\n"
"k_arrive(c, KS(3), 1, KS(13));\n"
"break;\n"
"}\n"
"case 1284: {\n"
"KS(1) = c->H[KS(3) + 4];\n"
"KS(2) = c->H[KS(3) + 5];\n"
"KPC = 1285;\n"
"break;\n"
"}\n"
"case 1285: {\n"
"KS(14) = KS(1);\n"
"KS(15) = KS(2);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(14);\n"
"c->H[w + 1] = KS(15);\n"
"KS(16) = p; }\n"
"KRET(KS(16));\n"
"break;\n"
"}\n"
"case 1286: {\n"
"KPC = KFORK ? 1312 : 1313;\n"
"break;\n"
"}\n"
"case 1313: {\n"
"KS(4) = KS(0);\n"
"KS(5) = KF_U32_dinc(c, KS(4));\n"
"KS(1) = KREG(((KX_make_x37s509762208x8001458(c, KS(5)))));\n"
"KS(6) = KS(0);\n"
"KS(7) = 2u;\n"
"KS(8) = KF_U32_dadd(c, KS(6), KS(7));\n"
"KS(2) = KREG(((KX_make_x37s509762208x8001458(c, KS(8)))));\n"
"KPC = 1315;\n"
"break;\n"
"}\n"
"case 1316: {\n"
"KS(2) = KS(0);\n"
"KS(3) = KF_U32_dinc(c, KS(2));\n"
"KRET(KREG(((KX_make_x37s509762208x8001458(c, KS(3))))));\n"
"break;\n"
"}\n"
"case 1317: {\n"
"KS(2) = KS(0);\n"
"KS(3) = 2u;\n"
"KS(4) = KF_U32_dadd(c, KS(2), KS(3));\n"
"KRET(KREG(((KX_make_x37s509762208x8001458(c, KS(4))))));\n"
"break;\n"
"}\n"
"case 1312: {\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 1316; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(9) = p; }\n"
"KS(10) = KS(9);\n"
"{ KW p = k_alloc(c, 4); KW w = KIX(c, p);\n"
"c->H[w] = KCLO | 1317; c->H[w + 1] = 2; c->H[w + 2] = 1;\n"
"c->H[w + 3] = KS(0);\n"
"KS(11) = p; }\n"
"KS(12) = KS(11);\n"
"KS(3) = k_join_new(c, 2, 1314);\n"
"if (!k_push_task(c, PC_TASK, KS(3), KS(10), (c->dep + 1) | ((KW)0 << 32))) k_fail(c, KE_QUEUE);\n"
"c->dep += 1;\n"
"k_call_clo(c, KS(12), 0, 1318);\n"
"break;\n"
"}\n"
"case 1318: {\n"
"KS(13) = KRV;\n"
"k_arrive(c, KS(3), 1, KS(13));\n"
"break;\n"
"}\n"
"case 1314: {\n"
"KS(1) = c->H[KS(3) + 4];\n"
"KS(2) = c->H[KS(3) + 5];\n"
"KPC = 1315;\n"
"break;\n"
"}\n"
"case 1315: {\n"
"KS(14) = KS(1);\n"
"KS(15) = KS(2);\n"
"{ KW p = k_bnode(c, 2); KW w = KIX(c, p);\n"
"c->H[w + 0] = KS(14);\n"
"c->H[w + 1] = KS(15);\n"
"KS(16) = p; }\n"
"KRET(KS(16));\n"
"break;\n"
"}\n"
"default: {\n"
"k_fail(c, KE_PC);\n"
"break;\n"
"}\n"
"}\n"
"}\n"
""
;

static const GpuFn K_FNS[] = {{W_make, KLW_make}, {W_rounds, KLW_rounds}, {W_sum, KLW_sum}, {0, 0}};
static const GpuFn K_KQH[] = {K_KQH_LIST {0, 0}};
static GpuProg K_PROG = {K_SRC, bend_kernel, bend_kq, K_FNS, K_KQH};

static V G_sum(V a0) {
V ga[] = {a0, 0}, r;
if (gpu_call(&K_PROG, KL_sum, ga, 1, 1, &r)) return r;
return F_sum(a0);
}
static V G_rounds(V a0, V a1) {
V ga[] = {a0, a1, 0}, r;
if (gpu_call(&K_PROG, KL_rounds, ga, 2, 1, &r)) return r;
return F_rounds(a0, a1);
}
static V G_make(V a0, V a1) {
V ga[] = {a0, a1, 0}, r;
if (gpu_call(&K_PROG, KL_make, ga, 2, 1, &r)) return r;
return F_make(a0, a1);
}

int main(int argc, char **argv) {
#ifdef __TINYC__
  bend_ctors();
#endif
 return bend_run(argc, argv, F_main); }

// Natives, effects and main.
//
// The natives are the functions bendc's C runtime replaces (bendc.bend's
// Natives list, rt/bendrt.h): U32 and F32 are machine words, a Nat is a
// word (a result past 2^48-1 stops the program, as there). Map.bit and
// String.append are also here: the first as bendrt.h has it, the second
// as Base defines it, without its recursion.
//
// An effect of n parameters is a function of n + 2 arguments: its own, the
// answer type (erased) and the continuation, which it calls with the
// answer. bendc uses IO.print, IO.write, IO.print_err, IO.get_env, IO.args
// and File.open, File.size, File.read, File.close.
#include "bendi.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/stat.h>

int prog_argc;
char **prog_argv;

#define BOOL(b) ((V)((b) ? 1 : 0))
#define NAT_MAX (((V)1 << 48) - 1)

static V nat_chk(V x) {
  if (x > NAT_MAX) die("a Nat past the largest immediate 2^48-1");
  return x;
}

static V tuple(V a, V b) {
  V f[2] = {a, b};
  return mk_node(ct_tuple, f);
}

// Strings
// -------

// SCon{c, rest} for each code point, built from the end.
V mk_string(const uint32_t *cp, size_t n, int perm) {
  V s = 0;  // SNil
  for (size_t i = n; i > 0; i--) {
    V *p = perm ? perm_alloc(3) : gc_alloc(3);
    p[0] = MK_HDR(1, 2);
    p[1] = cp[i - 1];
    p[2] = s;
    s = (V)p;
  }
  return s;
}

V mk_cstring(const char *s, size_t n) {
  uint32_t *cp = xmalloc((n + 1) * sizeof(uint32_t));
  size_t m = 0;
  const unsigned char *u = (const unsigned char *)s;
  for (size_t i = 0; i < n;) {
    unsigned char c = u[i];
    uint32_t v;
    int len;
    if (c < 0x80) { v = c; len = 1; }
    else if ((c >> 5) == 6 && i + 1 < n) { v = c & 0x1f; len = 2; }
    else if ((c >> 4) == 14 && i + 2 < n) { v = c & 0x0f; len = 3; }
    else if ((c >> 3) == 30 && i + 3 < n) { v = c & 0x07; len = 4; }
    else { v = c; len = 1; }
    for (int j = 1; j < len; j++) v = (v << 6) | (u[i + j] & 0x3f);
    cp[m++] = v;
    i += (size_t)len;
  }
  V r = mk_string(cp, m, 0);
  free(cp);
  return r;
}

char *string_to_c(V s, size_t *len) {
  size_t cap = 64, n = 0;
  char *b = xmalloc(cap);
  while (is_ptr(s)) {
    uint32_t cp = (uint32_t)FLD(s, 0);
    if (n + 5 > cap) { cap *= 2; b = xrealloc(b, cap); }
    if (cp < 0x80) b[n++] = (char)cp;
    else if (cp < 0x800) { b[n++] = (char)(0xc0 | (cp >> 6)); b[n++] = (char)(0x80 | (cp & 0x3f)); }
    else if (cp < 0x10000) {
      b[n++] = (char)(0xe0 | (cp >> 12)); b[n++] = (char)(0x80 | ((cp >> 6) & 0x3f));
      b[n++] = (char)(0x80 | (cp & 0x3f));
    } else {
      b[n++] = (char)(0xf0 | (cp >> 18)); b[n++] = (char)(0x80 | ((cp >> 12) & 0x3f));
      b[n++] = (char)(0x80 | ((cp >> 6) & 0x3f)); b[n++] = (char)(0x80 | (cp & 0x3f));
    }
    s = FLD(s, 1);
  }
  b[n] = 0;
  if (len) *len = n;
  return b;
}

// a ++ b: a's cells copied, b shared.
static V p_str_append(V *a) {
  V s = a[0], b = a[1];
  if (!is_ptr(s)) return b;
  V head = 0, *last = 0;
  while (is_ptr(s)) {
    V *p = gc_alloc(3);
    p[0] = MK_HDR(1, 2);
    p[1] = FLD(s, 0);
    p[2] = 0;
    if (last) last[2] = (V)p; else head = (V)p;
    last = p;
    s = FLD(s, 1);
  }
  last[2] = b;
  return head;
}

// U32
// ---

#define U(x) ((V)(uint32_t)(x))
static V u_inc(V *a) { return U(a[0] + 1); }
static V u_add(V *a) { return U(a[0] + a[1]); }
static V u_sub(V *a) { return U(a[0] - a[1]); }
static V u_mul(V *a) { return U((uint32_t)a[0] * (uint32_t)a[1]); }
static V u_div(V *a) { return a[1] == 0 ? 0 : U((uint32_t)a[0] / (uint32_t)a[1]); }
static V u_mod(V *a) { return a[1] == 0 ? a[0] : U((uint32_t)a[0] % (uint32_t)a[1]); }
static V u_not(V *a) { return U(~a[0]); }
static V u_and(V *a) { return a[0] & a[1]; }
static V u_or(V *a) { return a[0] | a[1]; }
static V u_xor(V *a) { return a[0] ^ a[1]; }
static V u_shl(V *a) { return U(a[0] << 1); }
static V u_shr(V *a) { return a[0] >> 1; }
static V u_shln(V *a) { return a[1] >= 32 ? 0 : U(a[0] << a[1]); }
static V u_shrn(V *a) { return a[1] >= 32 ? 0 : a[0] >> a[1]; }
static V cmp3(V x, V y) { return x < y ? 0 : x == y ? 1 : 2; }
static V u_cmp(V *a) { return cmp3(a[0], a[1]); }
static V u_eq(V *a) { return BOOL(a[0] == a[1]); }
static V u_ne(V *a) { return BOOL(a[0] != a[1]); }
static V u_lt(V *a) { return BOOL(a[0] < a[1]); }
static V u_le(V *a) { return BOOL(a[0] <= a[1]); }
static V u_gt(V *a) { return BOOL(a[0] > a[1]); }
static V u_ge(V *a) { return BOOL(a[0] >= a[1]); }
static V u_zero(V *a) { return BOOL(a[0] == 0); }
static V u_even(V *a) { return BOOL((a[0] & 1) == 0); }
static V u_to_nat(V *a) { return a[0]; }
static V u_from_nat(V *a) { return U(a[0]); }
static V u_min(V *a) { return a[0] < a[1] ? a[0] : a[1]; }
static V u_max(V *a) { return a[0] < a[1] ? a[1] : a[0]; }
static V u_pow(V *a) {
  V e = a[1];
  uint32_t r = 1, b = (uint32_t)a[0];
  for (; e; e >>= 1) { if (e & 1) r *= b; b *= b; }
  return r;
}
static V u_log2(V *a) {
  V n = a[0], d = 0;
  while (n > 1) { d++; n >>= 1; }
  return d;
}

// F32 (IEEE bits)
// ---------------

static float FV(V v) { union { uint32_t u; float f; } x; x.u = (uint32_t)v; return x.f; }
static V VF(float f) { union { uint32_t u; float f; } x; x.f = f; return x.u; }
static V u_to_f32(V *a) { return VF((float)(uint32_t)a[0]); }
static V f_add(V *a) { return VF(FV(a[0]) + FV(a[1])); }
static V f_sub(V *a) { return VF(FV(a[0]) - FV(a[1])); }
static V f_mul(V *a) { return VF(FV(a[0]) * FV(a[1])); }
static V f_div(V *a) { return VF(FV(a[0]) / FV(a[1])); }
static V f_mod(V *a) { return VF((float)fmod(FV(a[0]), FV(a[1]))); }
static V f_pow(V *a) { return VF((float)pow(FV(a[0]), FV(a[1]))); }
static V f_atan2(V *a) { return VF((float)atan2(FV(a[0]), FV(a[1]))); }
static V f_eq(V *a) { return BOOL(FV(a[0]) == FV(a[1])); }
static V f_ne(V *a) { return BOOL(FV(a[0]) != FV(a[1])); }
static V f_lt(V *a) { return BOOL(FV(a[0]) < FV(a[1])); }
static V f_le(V *a) { return BOOL(FV(a[0]) <= FV(a[1])); }
static V f_gt(V *a) { return BOOL(FV(a[0]) > FV(a[1])); }
static V f_ge(V *a) { return BOOL(FV(a[0]) >= FV(a[1])); }
static V f_neg(V *a) { return VF(-FV(a[0])); }
static V f_abs(V *a) { return VF(fabsf(FV(a[0]))); }
static V f_sqrt(V *a) { return VF(sqrtf(FV(a[0]))); }
static V f_exp(V *a) { return VF((float)exp(FV(a[0]))); }
static V f_log(V *a) { return VF((float)log(FV(a[0]))); }
static V f_log2(V *a) { return VF((float)log2(FV(a[0]))); }
static V f_log10(V *a) { return VF((float)log10(FV(a[0]))); }
static V f_sin(V *a) { return VF((float)sin(FV(a[0]))); }
static V f_cos(V *a) { return VF((float)cos(FV(a[0]))); }
static V f_tan(V *a) { return VF((float)tan(FV(a[0]))); }
static V f_asin(V *a) { return VF((float)asin(FV(a[0]))); }
static V f_acos(V *a) { return VF((float)acos(FV(a[0]))); }
static V f_atan(V *a) { return VF((float)atan(FV(a[0]))); }
static V f_sinh(V *a) { return VF((float)sinh(FV(a[0]))); }
static V f_cosh(V *a) { return VF((float)cosh(FV(a[0]))); }
static V f_tanh(V *a) { return VF((float)tanh(FV(a[0]))); }
static V f_floor(V *a) { return VF(floorf(FV(a[0]))); }
static V f_ceil(V *a) { return VF(ceilf(FV(a[0]))); }
static V f_trunc(V *a) { return VF(truncf(FV(a[0]))); }
static V f_bits(V *a) { return U(a[0]); }
static V f_to_u32(V *a) { float x = FV(a[0]); return !(x > 0) ? 0 : x >= 4294967296.0f ? 0 : (uint32_t)x; }

// The shortest text that reads back, as JavaScript spells a number
// (bendrt.h's f32_text).
static int f32_text(float v, char *buf, size_t n) {
  int k = 0, p = 0;
  if (v != v) return snprintf(buf, n, "nan");
  for (; p < 9; p++) {
    k = snprintf(buf, n, "%.*e", p, (double)v);
    if (strtof(buf, NULL) == v) break;
  }
  char *ep = strchr(buf, 'e');
  if (ep == NULL) return k;
  int ex = atoi(ep + 1);
  if (ex >= 21 || ex <= -7) {
    k = (int)(ep - buf) + snprintf(ep, n - (size_t)(ep - buf), "e%c%d", ex < 0 ? '-' : '+', abs(ex));
  } else if (ex <= p) {
    k = snprintf(buf, n, "%.*f", p - ex, (double)v);
  } else {
    int s = *buf == '-';
    memmove(buf + s + 1, buf + s + 2, (size_t)p);
    memset(buf + s + 1 + p, '0', (size_t)(ex - p));
    k = s + 1 + ex;
    buf[k] = 0;
  }
  return k;
}

static V f_show(V *a) {
  char buf[64];
  f32_text(FV(a[0]), buf, sizeof buf);
  return mk_cstring(buf, strlen(buf));
}

static V f_read(V *a) {
  char *c = string_to_c(a[0], NULL), *end;
  float f = strtof(c, &end);
  int ok = *c && !*end;
  free(c);
  if (!ok) return 0;
  V x = VF(f);
  return mk_node(ct_some, &x);
}

// Nat
// ---

static V n_double(V *a) { return nat_chk(a[0] + a[0]); }
static V n_add(V *a) { return nat_chk(a[0] + a[1]); }
static V n_sub(V *a) { return a[0] > a[1] ? a[0] - a[1] : 0; }
static V n_mul(V *a) {
  if (a[1] != 0 && a[0] > NAT_MAX / a[1]) nat_chk(NAT_MAX + 1);
  return a[0] * a[1];
}
static V n_divmod(V *a) { return a[1] == 0 ? tuple(0, a[0]) : tuple(a[0] / a[1], a[0] % a[1]); }
static V n_div(V *a) { return a[1] == 0 ? 0 : a[0] / a[1]; }
static V n_mod(V *a) { return a[1] == 0 ? a[0] : a[0] % a[1]; }
static V n_pow(V *a) {
  V b = a[0], n = a[1];
  if (b <= 1) return n == 0 ? 1 : b;
  V r = 1;
  for (; n; n--) { V m[2] = {r, b}; r = n_mul(m); }
  return r;
}
static V n_show(V *a) {
  char buf[32];
  nat_chk(a[0] / 10);
  snprintf(buf, sizeof buf, "%llu", (unsigned long long)a[0]);
  return mk_cstring(buf, strlen(buf));
}

// Map.bit(key, pos): bit pos of key as Base's tries read it (char pos / 33;
// offset 0 is "the char exists", offset 1 + b is bit 31 - b of its code),
// and the key.
static V m_bit(V *a) {
  V key = a[0], pos = a[1];
  V ci = pos / 33, off = pos % 33, s = key;
  if (pos >> 63) return tuple(key, 0);
  for (;;) {
    if (!is_ptr(s)) return tuple(key, 0);
    if (ci == 0) break;
    s = FLD(s, 1);
    ci--;
  }
  uint32_t x = (uint32_t)FLD(s, 0);
  return tuple(key, off == 0 ? 1 : (x >> (32 - off)) & 1);
}

// Effects
// -------

static V ok(V x) { return mk_node(ct_done, &x); }

static V fail(int code) {
  const char *m = strerror(code);
  V t = tuple((V)(uint32_t)code, mk_cstring(m, strlen(m)));
  return mk_node(ct_fail, &t);
}

static V answer(V k, V x) { return apply(k, 1, &x); }

static void put_string(FILE *f, V s) {
  size_t n;
  char *c = string_to_c(s, &n);
  fwrite(c, 1, n, f);
  free(c);
}

static V e_print(V *a) { put_string(stdout, a[0]); fputc('\n', stdout); return answer(a[2], 0); }
static V e_write(V *a) { put_string(stdout, a[0]); return answer(a[2], 0); }
static V e_print_err(V *a) {
  fflush(stdout);
  put_string(stderr, a[0]);
  fputc('\n', stderr);
  return answer(a[2], 0);
}

static V e_get_env(V *a) {
  char *name = string_to_c(a[0], NULL);
  const char *v = getenv(name);
  free(name);
  return answer(a[2], v ? ok(mk_cstring(v, strlen(v))) : fail(ENOENT));
}

static V e_args(V *a) {
  V xs = 0;  // Nil
  for (int i = prog_argc; i > 0; i--) {
    V f[2];
    f[0] = mk_cstring(prog_argv[i - 1], strlen(prog_argv[i - 1]));
    f[1] = xs;
    xs = mk_node(ct_con, f);
  }
  return answer(a[1], xs);
}

static V e_file_open(V *a) {
  char *path = string_to_c(a[0], NULL), *mode = string_to_c(a[1], NULL);
  int flags = !strcmp(mode, "r") ? O_RDONLY : !strcmp(mode, "w") ? O_WRONLY | O_CREAT | O_TRUNC
            : !strcmp(mode, "a") ? O_WRONLY | O_CREAT | O_APPEND : -1;
  V r;
  if (flags < 0) r = fail(EINVAL);
  else {
    int fd = open(path, flags, 0644);
    r = fd < 0 ? fail(errno) : ok((V)(uint32_t)fd);
  }
  free(path);
  free(mode);
  return answer(a[3], r);
}

static V e_file_size(V *a) {
  struct stat st;
  V r;
  if (fstat((int)a[0], &st) != 0) r = fail(errno);
  else if (st.st_size > (off_t)UINT32_MAX) r = fail(EOVERFLOW);
  else r = ok((V)(uint32_t)st.st_size);
  return answer(a[2], tuple(a[0], r));
}

static V e_file_read(V *a) {
  size_t max = a[1] < 0x7fffffff ? (size_t)a[1] : 0x7fffffff, n = 0;
  char *buf = xmalloc(max + 1);
  V r;
  for (;;) {
    ssize_t k = read((int)a[0], buf + n, max - n);
    if (k < 0 && errno == EINTR) continue;
    if (k < 0) { r = fail(errno); break; }
    n += (size_t)k;
    if (k == 0 || n == max) { r = ok(mk_cstring(buf, n)); break; }
  }
  free(buf);
  return answer(a[3], tuple(a[0], r));
}

static V e_file_write(V *a) {
  size_t n;
  char *c = string_to_c(a[1], &n);
  size_t w = 0;
  V r = 0;
  while (w < n) {
    ssize_t k = write((int)a[0], c + w, n - w);
    if (k < 0 && errno == EINTR) continue;
    if (k < 0) { r = fail(errno); break; }
    w += (size_t)k;
  }
  free(c);
  if (w == n) r = ok(0);
  return answer(a[3], tuple(a[0], r));
}

static V e_file_close(V *a) {
  close((int)a[0]);
  return answer(a[2], 0);
}

typedef struct { const char *name; int arity; NativeFn f; } Prim;

static const Prim prims[] = {
  {"U32.inc", 1, u_inc}, {"U32.add", 2, u_add}, {"U32.sub", 2, u_sub}, {"U32.mul", 2, u_mul},
  {"U32.div", 2, u_div}, {"U32.mod", 2, u_mod}, {"U32.not", 1, u_not}, {"U32.and", 2, u_and},
  {"U32.or", 2, u_or}, {"U32.xor", 2, u_xor}, {"U32.shl", 1, u_shl}, {"U32.shr", 1, u_shr},
  {"U32.shln", 2, u_shln}, {"U32.shrn", 2, u_shrn}, {"U32.cmp", 2, u_cmp}, {"U32.is_eq", 2, u_eq},
  {"U32.is_ne", 2, u_ne}, {"U32.is_lt", 2, u_lt}, {"U32.is_le", 2, u_le}, {"U32.is_gt", 2, u_gt},
  {"U32.is_ge", 2, u_ge}, {"U32.is_zero", 1, u_zero}, {"U32.is_even", 1, u_even},
  {"U32.to_nat", 1, u_to_nat}, {"U32.from_nat", 1, u_from_nat}, {"U32.min", 2, u_min},
  {"U32.max", 2, u_max}, {"U32.pow", 2, u_pow}, {"U32.log2", 1, u_log2}, {"U32.to_f32", 1, u_to_f32},
  {"Nat.double", 1, n_double}, {"Nat.add", 2, n_add}, {"Nat.sub", 2, n_sub}, {"Nat.mul", 2, n_mul},
  {"Nat.divmod", 2, n_divmod}, {"Nat.div", 2, n_div}, {"Nat.mod", 2, n_mod}, {"Nat.cmp", 2, u_cmp},
  {"Nat.is_eq", 2, u_eq}, {"Nat.is_ne", 2, u_ne}, {"Nat.is_lt", 2, u_lt}, {"Nat.is_le", 2, u_le},
  {"Nat.is_gt", 2, u_gt}, {"Nat.is_ge", 2, u_ge}, {"Nat.min", 2, u_min}, {"Nat.max", 2, u_max},
  {"Nat.pow", 2, n_pow}, {"Nat.show", 1, n_show},
  {"F32.add", 2, f_add}, {"F32.sub", 2, f_sub}, {"F32.mul", 2, f_mul}, {"F32.div", 2, f_div},
  {"F32.mod", 2, f_mod}, {"F32.pow", 2, f_pow}, {"F32.atan2", 2, f_atan2}, {"F32.is_eq", 2, f_eq},
  {"F32.is_ne", 2, f_ne}, {"F32.is_lt", 2, f_lt}, {"F32.is_le", 2, f_le}, {"F32.is_gt", 2, f_gt},
  {"F32.is_ge", 2, f_ge}, {"F32.neg", 1, f_neg}, {"F32.abs", 1, f_abs}, {"F32.sqrt", 1, f_sqrt},
  {"F32.exp", 1, f_exp}, {"F32.log", 1, f_log}, {"F32.log2", 1, f_log2}, {"F32.log10", 1, f_log10},
  {"F32.sin", 1, f_sin}, {"F32.cos", 1, f_cos}, {"F32.tan", 1, f_tan}, {"F32.asin", 1, f_asin},
  {"F32.acos", 1, f_acos}, {"F32.atan", 1, f_atan}, {"F32.sinh", 1, f_sinh}, {"F32.cosh", 1, f_cosh},
  {"F32.tanh", 1, f_tanh}, {"F32.floor", 1, f_floor}, {"F32.ceil", 1, f_ceil}, {"F32.trunc", 1, f_trunc},
  {"F32.bits", 1, f_bits}, {"F32.to_u32", 1, f_to_u32}, {"F32.show", 1, f_show}, {"F32.read", 1, f_read},
  {"Map.bit", 2, m_bit}, {"String.append", 2, p_str_append},
  // effects: their parameters, the answer type, the continuation
  {"IO.print", 3, e_print}, {"IO.write", 3, e_write}, {"IO.print_err", 3, e_print_err},
  {"IO.get_env", 3, e_get_env}, {"IO.args", 2, e_args}, {"File.open", 4, e_file_open},
  {"File.size", 3, e_file_size}, {"File.read", 4, e_file_read}, {"File.write", 4, e_file_write},
  {"File.close", 3, e_file_close},
  {0, 0, 0}};

void install_natives(void) {
  for (int i = 0; prims[i].name; i++) define_native(prims[i].name, prims[i].arity, prims[i].f);
}

// Main
// ----

static const char *base_path, *prog_path;
static int mode;  // 0 run, 1 tokens, 2 ast
static int exit_code;

static V k_done(V *a) { return mk_node(ct_emit, a); }

static void run(void) {
  if (mode) {
    int n;
    uint32_t *src = read_source(prog_path, &n);
    if (mode == 1) {
      int nt;
      Tok *ts = lex_all(src, n, &nt);
      show_toks(stdout, ts, nt);
    } else show_decls(stdout, parse_file(prog_path, src, n));
    return;
  }
  heap_init();
  install_natives();
  Vec ds = load_program(base_path, prog_path);
  compile_program(ds);
  if (!ct_tuple || !ct_con || !ct_done || !ct_fail || !ct_emit || !ct_halt || !ct_some)
    die("Base lacks Tuple, Con, Some, Done, Fail, Emit or Halt");
  define_native("%done", 1, k_done);  // the last continuation: x => Emit{x}
  Fn *kf = find_fn("%done");
  V args[2] = {0, mk_closure(kf, 0, 0)};
  V r = apply(global_value("main"), 2, args);
  fflush(stdout);
  if (is_ptr(r) && HDR_TAG(*(V *)r) == ct_halt->tag && (*(V *)r >> 56) == 2) {
    put_string(stderr, FLD(r, 1));
    fputc('\n', stderr);
    exit_code = (int)(uint32_t)FLD(r, 0);
  }
  if (getenv("BENDI_STATS")) gc_stats();
}

static void *thread_main(void *arg) {
  char base = 0;
  (void)arg;
  set_stack_base(&base + 64);
  run();
  return 0;
}

int main(int argc, char **argv) {
  int i = 1;
  if (i < argc && !strcmp(argv[i], "--tokens")) { mode = 1; i++; }
  else if (i < argc && !strcmp(argv[i], "--ast")) { mode = 2; i++; }
  else if (i + 1 < argc && !strcmp(argv[i], "--base")) { base_path = argv[i + 1]; i += 2; }
  if (i >= argc) {
    fprintf(stderr, "usage: bendi [--base base.bend] prog.bend [args...] | --tokens file | --ast file\n");
    return 2;
  }
  prog_path = argv[i];
  prog_argc = argc - i;
  prog_argv = argv + i;
  if (!base_path) base_path = getenv("BEND_BASE");
  if (!base_path) {
    const char *home = getenv("HOME");
    base_path = cat(home ? home : "", "/.bend/bend2/base.bend");
  }
  static char buf[1 << 20];
  setvbuf(stdout, buf, _IOFBF, sizeof buf);
  // The evaluator recurses as deep as the program does: its thread gets a
  // stack of 32 GB of address space (touched only as far as it is used).
  size_t size = (size_t)1 << 35;
  void *stack = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_NORESERVE, -1, 0);
  if (stack == MAP_FAILED) die("cannot map the stack");
  pthread_attr_t at;
  pthread_attr_init(&at);
  pthread_attr_setstack(&at, stack, size);
  pthread_t th;
  if (pthread_create(&th, &at, thread_main, 0) != 0) die("cannot start the evaluator's thread");
  pthread_join(th, 0);
  fflush(stdout);
  return exit_code;
}

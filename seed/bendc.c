#define CID_UNIT ((1u << 16) | 0u)
#define CID_FALSE ((1u << 16) | 0u)
#define CID_TRUE ((1u << 16) | 1u)
#define CID_LT ((1u << 16) | 0u)
#define CID_EQ ((1u << 16) | 1u)
#define CID_GT ((1u << 16) | 2u)
#define CID_INL 0u
#define CID_INR 1u
#define CID_TUPLE 0u
#define CID_NONE ((1u << 16) | 0u)
#define CID_SOME 1u
#define CID_FAIL 0u
#define CID_DONE 1u
#define CID_NIL ((1u << 16) | 0u)
#define CID_CON 1u
#define CID_WNIL ((1u << 16) | 0u)
#define CID_WCON 0u
#define CID_U32 ((2u << 16) | 0u)
#define CID_F32 ((2u << 16) | 0u)
#define CID_CHR ((2u << 16) | 0u)
#define CID_SNIL ((1u << 16) | 0u)
#define CID_SCON 1u
#define CID_ALEAF 0u
#define CID_ANODE 1u
#define CID_PIX 0u
#define CID_QUA 1u
#define CID_KEY 0u
#define CID_MOUSE 1u
#define CID_MOVE 2u
#define CID_CLOSE ((1u << 16) | 3u)
#define CID_MTIP ((1u << 16) | 0u)
#define CID_MLEAF 1u
#define CID_MNODE 2u
#define CID_EMIT 0u
#define CID_HALT 1u
#define CID_APP 0u
#define CID_IO_PRINT ((3u << 16) | 0u)
#define CID_IO_WRITE ((3u << 16) | 1u)
#define CID_IO_PRINT_ERR ((3u << 16) | 2u)
#define CID_IO_GET_ENV ((3u << 16) | 3u)
#define CID_IO_ARGS ((3u << 16) | 4u)
#define CID_IO_RANDOM_U32 ((3u << 16) | 5u)
#define CID_IO_SPAWN ((3u << 16) | 6u)
#define CID_IO_SLEEP ((3u << 16) | 7u)
#define CID_IO_NOW ((3u << 16) | 8u)
#define CID_CHAN_NEW ((3u << 16) | 9u)
#define CID_CHAN_SEND ((3u << 16) | 10u)
#define CID_CHAN_RECV ((3u << 16) | 11u)
#define CID_CHAN_CLOSE ((3u << 16) | 12u)
#define CID_FILE_OPEN ((3u << 16) | 13u)
#define CID_FILE_READ ((3u << 16) | 14u)
#define CID_FILE_READ_BYTES ((3u << 16) | 15u)
#define CID_FILE_READ_AT ((3u << 16) | 16u)
#define CID_FILE_SIZE ((3u << 16) | 17u)
#define CID_FILE_WRITE ((3u << 16) | 18u)
#define CID_FILE_WRITE_BYTES ((3u << 16) | 19u)
#define CID_FILE_CLOSE ((3u << 16) | 20u)
#define CID_TCP_LISTEN ((3u << 16) | 21u)
#define CID_TCP_ACCEPT ((3u << 16) | 22u)
#define CID_TCP_CONNECT ((3u << 16) | 23u)
#define CID_TCP_SEND ((3u << 16) | 24u)
#define CID_TCP_RECV ((3u << 16) | 25u)
#define CID_TCP_POLL ((3u << 16) | 26u)
#define CID_UDP_BIND ((3u << 16) | 27u)
#define CID_UDP_SEND_TO ((3u << 16) | 28u)
#define CID_UDP_RECV_FROM ((3u << 16) | 29u)
#define CID_UDP_POLL ((3u << 16) | 30u)
#define CID_SOCKET_CLOSE ((3u << 16) | 31u)
#define CID_LISTENER_CLOSE ((3u << 16) | 32u)
#define CID_WINDOW_OPEN ((3u << 16) | 33u)
#define CID_WINDOW_FRAME ((3u << 16) | 34u)
#define CID_WINDOW_SET_TITLE ((3u << 16) | 35u)
#define CID_WINDOW_CLOSE ((3u << 16) | 36u)
#define CID_AUDIO_OPEN ((3u << 16) | 37u)
#define CID_AUDIO_WRITE ((3u << 16) | 38u)
#define CID_AUDIO_CLOSE ((3u << 16) | 39u)
#define CID_CHK_NOSP ((1u << 16) | 0u)
#define CID_CHK_SP 1u
#define CID_CHK_QNONE ((1u << 16) | 0u)
#define CID_CHK_QLONE ((1u << 16) | 1u)
#define CID_CHK_QMANY ((1u << 16) | 2u)
#define CID_CHK_QUND ((1u << 16) | 3u)
#define CID_CHK_LNAT 0u
#define CID_CHK_LSTR 1u
#define CID_CHK_PVAR 0u
#define CID_CHK_PCTR 1u
#define CID_CHK_VAR 0u
#define CID_CHK_CEL 1u
#define CID_CHK_VPL 2u
#define CID_CHK_VRF 3u
#define CID_CHK_REF 4u
#define CID_CHK_SUB 5u
#define CID_CHK_LET 6u
#define CID_CHK_TYP 7u
#define CID_CHK_QNT 8u
#define CID_CHK_TQUA 9u
#define CID_CHK_MIN 10u
#define CID_CHK_ALL 11u
#define CID_CHK_LAM 12u
#define CID_CHK_TAPP 13u
#define CID_CHK_ADT 14u
#define CID_CHK_CTR 15u
#define CID_CHK_LIT 16u
#define CID_CHK_MAT 17u
#define CID_CHK_EFQ 18u
#define CID_CHK_EQL 19u
#define CID_CHK_RFL 20u
#define CID_CHK_RWT 21u
#define CID_CHK_HOL 22u
#define CID_CHK_ANN 23u
#define CID_CHK_CSYN 24u
#define CID_CHK_CLET 25u
#define CID_CHK_CSNF 26u
#define CID_CHK_CEXT 27u
#define CID_CHK_CGOAL 28u
#define CID_CHK_CRWT 29u
#define CID_CHK_CCONST 30u
#define CID_CHK_EB 31u
#define CID_CHK_EPAT 32u
#define CID_CHK_CB 33u
#define CID_CHK_CTRD 0u
#define CID_CHK_TDEF 0u
#define CID_CHK_TADT 1u
#define CID_CHK_BOOK 0u
#define CID_CHK_MNONE ((1u << 16) | 0u)
#define CID_CHK_MSTR 1u
#define CID_CHK_MTM 2u
#define CID_CHK_ERR 0u
#define CID_CHK_SB 0u
#define CID_CHK_CUR 0u
#define CID_CHK_SB2 0u
#define CID_CHK_PS 0u
#define CID_CHK_OP 0u
#define CID_CHK_BMATCH 0u
#define CID_CHK_BLOCAL 1u
#define CID_CHK_BREPLY 2u
#define CID_CHK_ROW 3u
#define CID_CHK_TC 0u
#define CID_CHK_LC 0u
#define CID_CHK_US 0u
#define CID_CHK_LNO ((1u << 16) | 0u)
#define CID_CHK_LH 1u
#define CID_CHK_FAPP 0u
#define CID_CHK_FMAT 1u
#define CID_CHK_FMNA 2u
#define CID_CHK_FMNB 3u
#define CID_CHK_CL 0u
#define CID_CHK_IR 0u
#define CID_CHK_DOM 0u
#define CID_CHK_AD 0u
#define CID_CHK_IMP 0u
#define CID_CHK_HDR 0u
#define CID_CHK_USE 0u
#define CID_DNIL ((1u << 16) | 0u)
#define CID_DSTR 1u
#define CID_DCAT 2u
#define CID_KID 0u
#define CID_KNAT 1u
#define CID_KNATPLUS 2u
#define CID_KNUM 3u
#define CID_KFLT 4u
#define CID_KCHR 5u
#define CID_KSTR 6u
#define CID_KSYM 7u
#define CID_KNL ((1u << 16) | 8u)
#define CID_KIN ((1u << 16) | 9u)
#define CID_KDE ((1u << 16) | 10u)
#define CID_KEOF ((1u << 16) | 11u)
#define CID_KERR 12u
#define CID_TOK 0u
#define CID_LINE 0u
#define CID_LS 0u
#define CID_PVAR 0u
#define CID_PCTOR 1u
#define CID_PNAT 2u
#define CID_PSUCC 3u
#define CID_PNUM 4u
#define CID_EVAR 0u
#define CID_ENUM 1u
#define CID_ENAT 2u
#define CID_EFLT 3u
#define CID_ESTR 4u
#define CID_ECALL 5u
#define CID_ECTOR 6u
#define CID_ELAM 7u
#define CID_ELET 8u
#define CID_EMATCH 9u
#define CID_ECASE 10u
#define CID_ESUCC 11u
#define CID_EOP 12u
#define CID_EANN 13u
#define CID_ETY 14u
#define CID_EERR 15u
#define CID_SLET 0u
#define CID_SBIND 1u
#define CID_SRET 2u
#define CID_SEXP 3u
#define CID_SSKIP ((1u << 16) | 4u)
#define CID_PARAM 0u
#define CID_FIELD 0u
#define CID_CTOR 0u
#define CID_DDEF 0u
#define CID_DEFF 1u
#define CID_DLAW 2u
#define CID_DTYPE 3u
#define CID_DIMPORT 4u
#define CID_OPINFO 0u
#define CID_CINFO 0u
#define CID_DINFO 0u
#define CID_G 0u
#define CID_BIND 0u
#define CID_ST 0u
#define CID_TRET ((1u << 16) | 0u)
#define CID_TSET 1u
#define CID_SELF 0u
#define CID_PATR 0u
#define CID_SPLIT 0u
#define CID_SIG 0u
#define CID_COUT 0u
#define CID_TB 0u
#define CID_QUAL 0u
#define CID_HUB_ENSURE ((3u << 16) | 40u)
#define CID_CS 0u
#include "bendrt.h"

// IO
// ==

Term io_print_err_run(Env e, Term* f, IoWork* w) {
  io_errs(e, f[0]);
  return term_pak(CID_UNIT, 0);
}

static void __attribute__((constructor)) io_print_err_use(void) {
  io_eff(CID_IO_PRINT_ERR, io_print_err_run, 0);
}

// IO
// ==

void io_write(const char* data, uint64_t len) {
  io_out(stdout, data, len);
}

Term io_write_run(Env e, Term* f, IoWork* w) {
  uint64_t n = 0;
  char* text = io_cstr(e, f[0], &n);
  io_write(text, n);
  free(text);
  return term_pak(CID_UNIT, 0);
}

static void __attribute__((constructor)) io_write_use(void) {
  io_eff(CID_IO_WRITE, io_write_run, 0);
}

// File
// ====

Term file_close_run(Env e, Term* f, IoWork* w) {
  close((int)io_hand_v(f[0]));
  return term_pak(CID_UNIT, 0);
}

static void __attribute__((constructor)) file_close_use(void) {
  io_eff(CID_FILE_CLOSE, file_close_run, 0);
}

// File
// ====

static void file_read_call(IoWork* w) {
  int fd = (int)w->hand;
  w->size = io_sys_end(w, read(fd, w->data, w->word));
}

static Term file_read_start(Term file, U32 max, IoWork* w,
  IoCall call, IoPack pack) {
  w->hand = (intptr_t)io_hand_v(file);
  w->word = max < INT32_MAX ? max : INT32_MAX;
  w->data = io_mem(malloc(w->word + 1));
  return io_work(w, call, pack);
}

#ifdef CID_FILE_READ

static Term file_read_pack(Env e, IoWork* w) {
  Term r = w->code ? io_fail(e, w->code, NULL)
    : io_done(e, io_str(e, w->data, w->size));
  free(w->data);
  return io_tup(e, io_hand(w->hand), r);
}

Term file_read_run(Env e, Term* f, IoWork* w) {
  return file_read_start(f[0], f[1], w, file_read_call, file_read_pack);
}

static void __attribute__((constructor)) file_read_use(void) {
  io_eff(CID_FILE_READ, file_read_run, 0);
}

#endif

#if defined(CID_FILE_READ_BYTES) || defined(CID_FILE_READ_AT)

// The bytes as they are (0..255), one List cell each; a text reader
// would decode them as UTF-8.
static Term file_read_bytes_pack(Env e, IoWork* w) {
  Term r;
  if (w->code) {
    r = io_fail(e, w->code, NULL);
  } else {
    Term xs = term_pak(CID_NIL, 0);
    for (u64 i = w->size; i > 0; i -= 1) {
      xs = io_node(e, CID_CON, ((uint8_t*)w->data)[i - 1], xs);
    }
    r = io_done(e, xs);
  }
  free(w->data);
  return io_tup(e, io_hand(w->hand), r);
}

#endif

#ifdef CID_FILE_READ_BYTES

Term file_read_bytes_run(Env e, Term* f, IoWork* w) {
  return file_read_start(f[0], f[1], w, file_read_call, file_read_bytes_pack);
}

static void __attribute__((constructor)) file_read_bytes_use(void) {
  io_eff(CID_FILE_READ_BYTES, file_read_bytes_run, 0);
}

#endif

#ifdef CID_FILE_READ_AT

// The bytes at an offset, as file_read_bytes gives them; the position of
// the file does not move.
static void file_read_at_call(IoWork* w) {
  int fd = (int)w->hand;
  w->size = io_sys_end(w, pread(fd, w->data, w->word, (off_t)w->made));
}

Term file_read_at_run(Env e, Term* f, IoWork* w) {
  w->made = (intptr_t)f[1];
  return file_read_start(f[0], f[2], w, file_read_at_call, file_read_bytes_pack);
}

static void __attribute__((constructor)) file_read_at_use(void) {
  io_eff(CID_FILE_READ_AT, file_read_at_run, 0);
}

#endif

// File
// ====

#include <sys/stat.h>

// The size in bytes, as the host reports it; a file past 4 GiB fails
// with EOVERFLOW.
static void file_size_call(IoWork* w) {
  struct stat st;
  int n = fstat((int)w->hand, &st);
  io_sys_end(w, n);
  if (n == 0) {
    w->code = st.st_size > (off_t)UINT32_MAX ? EOVERFLOW : 0;
    w->word = (u32)st.st_size;
  }
}

static Term file_size_pack(Env e, IoWork* w) {
  Term r = w->code ? io_fail(e, w->code, NULL) : io_done(e, w->word);
  return io_tup(e, io_hand(w->hand), r);
}

Term file_size_run(Env e, Term* f, IoWork* w) {
  w->hand = (intptr_t)io_hand_v(f[0]);
  return io_work(w, file_size_call, file_size_pack);
}

static void __attribute__((constructor)) file_size_use(void) {
  io_eff(CID_FILE_SIZE, file_size_run, 0);
}

// File
// ====

static int file_open_mode(const char* mode) {
  if (strcmp(mode, "r") == 0) {
    return O_RDONLY;
  }
  if (strcmp(mode, "w") == 0) {
    return O_WRONLY | O_CREAT | O_TRUNC;
  }
  if (strcmp(mode, "a") == 0) {
    return O_WRONLY | O_CREAT | O_APPEND;
  }
  return -1;
}

static void file_open_call(IoWork* w) {
  w->made = (intptr_t)io_sys_end(w, open(w->data, (int)w->word, 0644));
}

static Term file_open_pack(Env e, IoWork* w) {
  free(w->data);
  return w->code != 0 ? io_fail(e, w->code, NULL)
    : io_done(e, io_hand(w->made));
}

Term file_open_run(Env e, Term* f, IoWork* w) {
  uint64_t mn = 0;
  w->data = io_cstr(e, f[0], &w->size);
  char* mode = io_cstr(e, f[1], &mn);
  int flags = io_nul(mode, mn) ? -1 : file_open_mode(mode);
  free(mode);
  w->word = (uint32_t)flags;
  if (io_nul(w->data, w->size) || flags < 0) {
    w->code = io_nul(w->data, w->size) ? EILSEQ : EINVAL;
    return file_open_pack(e, w);
  }
  return io_work(w, file_open_call, file_open_pack);
}

static void __attribute__((constructor)) file_open_use(void) {
  io_eff(CID_FILE_OPEN, file_open_run, 0);
}

// Hub imports
// ===========
//
// `import 0x<hash>/path.bend as P` names a package by content hash. As the
// official bend does, the package's files are fetched from the hub (by
// default https://hub.bend-lang.com, or $BEND_HUB) into $BEND_LIB (default
// ~/.bend/lib) the first time: <hub>/<pkg>/manifest lists "sha256 path"
// lines and must hash to the package name; each file must hash to its line.

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

static const uint32_t hub_k[64] = {
  0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
  0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
  0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
  0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
  0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
  0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
  0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
  0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

#define HUB_ROR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

static void hub_block(uint32_t h[8], const unsigned char *p) {
  uint32_t w[64];
  for (int i = 0; i < 16; i++) w[i] = (uint32_t)p[4 * i] << 24 | (uint32_t)p[4 * i + 1] << 16 | (uint32_t)p[4 * i + 2] << 8 | p[4 * i + 3];
  for (int i = 16; i < 64; i++) {
    uint32_t s0 = HUB_ROR(w[i - 15], 7) ^ HUB_ROR(w[i - 15], 18) ^ (w[i - 15] >> 3);
    uint32_t s1 = HUB_ROR(w[i - 2], 17) ^ HUB_ROR(w[i - 2], 19) ^ (w[i - 2] >> 10);
    w[i] = w[i - 16] + s0 + w[i - 7] + s1;
  }
  uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5], g = h[6], k = h[7];
  for (int i = 0; i < 64; i++) {
    uint32_t t1 = k + (HUB_ROR(e, 6) ^ HUB_ROR(e, 11) ^ HUB_ROR(e, 25)) + ((e & f) ^ (~e & g)) + hub_k[i] + w[i];
    uint32_t t2 = (HUB_ROR(a, 2) ^ HUB_ROR(a, 13) ^ HUB_ROR(a, 22)) + ((a & b) ^ (a & c) ^ (b & c));
    k = g; g = f; f = e; e = d + t1; d = c; c = b; b = a; a = t1 + t2;
  }
  h[0] += a; h[1] += b; h[2] += c; h[3] += d; h[4] += e; h[5] += f; h[6] += g; h[7] += k;
}

// The SHA-256 of n bytes, as 64 hex digits.
static void hub_sha256(const char *data, size_t n, char out[65]) {
  uint32_t h[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
  const unsigned char *p = (const unsigned char *)data;
  size_t i = 0;
  for (; i + 64 <= n; i += 64) hub_block(h, p + i);
  unsigned char tail[128] = {0};
  size_t r = n - i;
  memcpy(tail, p + i, r);
  tail[r] = 0x80;
  size_t len = r + 1 + 8 <= 64 ? 64 : 128;
  uint64_t bits = (uint64_t)n * 8;
  for (int j = 0; j < 8; j++) tail[len - 1 - j] = (unsigned char)(bits >> (8 * j));
  hub_block(h, tail);
  if (len == 128) hub_block(h, tail + 64);
  for (int j = 0; j < 8; j++) snprintf(out + 8 * j, 9, "%08x", h[j]);
}

// Only plain path characters reach the shell or the file system.
static int hub_safe(const char *s) {
  if (*s == 0) return 0;
  for (const char *c = s; *c; c++) {
    if (!(isalnum((unsigned char)*c) || strchr("._-/:", *c))) return 0;
  }
  return strstr(s, "..") == NULL;
}

// GETs url with curl; returns a malloc'd body (NULL on failure).
static char *hub_fetch(const char *url, size_t *n) {
  if (!hub_safe(url)) return NULL;
  size_t cl = strlen(url) + 64;
  char *cmd = malloc(cl);
  snprintf(cmd, cl, "curl -fsSL --max-time 60 '%s'", url);
  FILE *p = popen(cmd, "r");
  free(cmd);
  if (p == NULL) return NULL;
  size_t cap = 4096, len = 0;
  char *buf = malloc(cap);
  size_t k;
  while ((k = fread(buf + len, 1, cap - len, p)) > 0) {
    len += k;
    if (len == cap) buf = realloc(buf, cap *= 2);
  }
  int st = pclose(p);
  if (st != 0) { free(buf); return NULL; }
  buf[len] = 0;
  *n = len;
  return buf;
}

static int hub_mkdirs(char *path) {
  for (char *c = path + 1; *c; c++) {
    if (*c == '/') {
      *c = 0;
      if (mkdir(path, 0755) != 0 && errno != EEXIST) { *c = '/'; return -1; }
      *c = '/';
    }
  }
  return 0;
}

static Term hub_err(Env e, const char *hub, const char *sub, const char *hash) {
  size_t n = strlen(hub) + strlen(sub) + strlen(hash) + 64;
  char *m = malloc(n);
  snprintf(m, n, "expected a file at %s/%s hashing to %s", hub, sub, hash);
  Term t = io_fail(e, 1, m);
  free(m);
  return t;
}

// Fetches the hub file sub, checking that its SHA-256 starts with hash.
static char *hub_get(const char *hub, const char *sub, const char *hash, size_t *n) {
  size_t ul = strlen(hub) + strlen(sub) + 2;
  char *url = malloc(ul);
  snprintf(url, ul, "%s/%s", hub, sub);
  char *src = hub_fetch(url, n);
  free(url);
  if (src == NULL) return NULL;
  char sum[65];
  hub_sha256(src, *n, sum);
  if (strlen(hash) < 32 || strncmp(sum, hash, strlen(hash)) != 0) { free(src); return NULL; }
  return src;
}

static Term hub_ensure(Env e, const char *lib, const char *hub, const char *rel) {
  size_t pl = strlen(lib) + strlen(rel) + 2;
  char *at = malloc(pl);
  snprintf(at, pl, "%s/%s", lib, rel);
  struct stat st;
  int have = stat(at, &st) == 0;
  free(at);
  if (have) return io_done(e, term_pak(CID_UNIT, 0));
  const char *slash = strchr(rel, '/');
  if (slash == NULL || rel[0] != '0' || rel[1] != 'x') return io_fail(e, 1, "a hub import (0x<hash>/<path>.bend)");
  char *pkg = strndup(rel, (size_t)(slash - rel));
  char *msub = malloc(strlen(pkg) + 16);
  sprintf(msub, "%s/manifest", pkg);
  size_t mn = 0;
  char *man = hub_get(hub, msub, pkg + 2, &mn);
  if (man == NULL) {
    Term t = hub_err(e, hub, msub, pkg + 2);
    free(msub); free(pkg);
    return t;
  }
  free(msub);
  Term out = io_done(e, term_pak(CID_UNIT, 0));
  for (char *line = strtok(man, "\n"); line != NULL; line = strtok(NULL, "\n")) {
    char *sp = strchr(line, ' ');
    if (sp == NULL) continue;
    *sp = 0;
    const char *h = line, *p = sp + 1;
    size_t sl = strlen(pkg) + strlen(p) + 2;
    char *sub = malloc(sl);
    snprintf(sub, sl, "%s/%s", pkg, p);
    size_t fn = 0;
    char *src = hub_safe(p) && p[0] != '/' ? hub_get(hub, sub, h, &fn) : NULL;
    if (src == NULL) {
      out = hub_err(e, hub, sub, h);
      free(sub);
      break;
    }
    size_t fl = strlen(lib) + strlen(sub) + 2;
    char *file = malloc(fl);
    snprintf(file, fl, "%s/%s", lib, sub);
    FILE *fp = NULL;
    if (hub_mkdirs(file) == 0) fp = fopen(file, "wb");
    int ok = fp != NULL && fwrite(src, 1, fn, fp) == fn;
    if (fp) fclose(fp);
    free(file);
    free(src);
    free(sub);
    if (!ok) { out = io_fail(e, errno ? (u32)errno : 1, NULL); break; }
  }
  free(man);
  free(pkg);
  return out;
}

Term hub_ensure_run(Env e, Term *f, IoWork *w) {
  (void)w;
  u64 n;
  char *lib = io_cstr(e, f[0], &n), *hub = io_cstr(e, f[1], &n), *rel = io_cstr(e, f[2], &n);
  Term r = hub_ensure(e, lib, hub, rel);
  free(lib);
  free(hub);
  free(rel);
  return r;
}

static void __attribute__((constructor)) hub_ensure_use(void) {
  io_eff(CID_HUB_ENSURE, hub_ensure_run, 0);
}

// IO
// ==

uint32_t io_get_env(const char* name, const char** out) {
  const char* value = getenv(name);
  if (value == NULL) {
    return ENOENT;
  }
  *out = value;
  return 0;
}

Term io_get_env_run(Env e, Term* f, IoWork* w) {
  uint64_t n = 0;
  char* name = io_cstr(e, f[0], &n);
  const char* got = NULL;
  uint32_t q;
  if (io_nul(name, n)) {
    q = ENOENT;
  } else {
    q = io_get_env(name, &got);
  }
  free(name);
  if (q != 0) {
    return io_fail(e, q, NULL);
  }
  return io_done(e, io_str(e, got, strlen(got)));
}

static void __attribute__((constructor)) io_get_env_use(void) {
  io_eff(CID_IO_GET_ENV, io_get_env_run, 0);
}

// IO
// ==

void io_print(const char* data, uint64_t len) {
  io_out(stdout, data, len);
  io_out(stdout, "\n", 1);
}

Term io_print_run(Env e, Term* f, IoWork* w) {
  uint64_t n = 0;
  char* text = io_cstr(e, f[0], &n);
  io_print(text, n);
  free(text);
  return term_pak(CID_UNIT, 0);
}

static void __attribute__((constructor)) io_print_use(void) {
  io_eff(CID_IO_PRINT, io_print_run, 0);
}

// IO
// ==

Term io_args_run(Env e, Term* f, IoWork* w) {
  Term xs = term_pak(CID_NIL, 0);
  for (int i = io_argc; i > 0; i -= 1) {
    const char* a = io_argv[i - 1];
    xs = io_node(e, CID_CON, io_str(e, a, strlen(a)), xs);
  }
  return xs;
}

static void __attribute__((constructor)) io_args_use(void) {
  io_eff(CID_IO_ARGS, io_args_run, 0);
}

static V F_main(void);
static V L0(V *a);
static V W_main(V *a);
static V F_IO_dlist2(V a0);
static V W_IO_dlist2(V *a);
static V F_Main_drun(V a0);
static V L3(V *a);
static V L4(V *a);
static V L5(V *a);
static V L6(V *a);
static V S7(void);
static V W_Main_drun(V *a);
static V F_IO_ddie(V a1, V a2);
static V L8(V *a);
static V L9(V *a);
static V W_IO_ddie(V *a);
static V F_Main_dchecked(V a0, V a1, V a2);
static V L13(V *a);
static V W_Main_dchecked(V *a);
static V F_Main_dnormalized(V a0);
static V W_Main_dnormalized(V *a);
static V F_Chk_dmain__has__fun(V a0);
static V W_Chk_dmain__has__fun(V *a);
static V F_Chk_dmain__tld(V a0);
static V S14(void);
static V W_Chk_dmain__tld(V *a);
static V F_Chk_dbook__tld(V a0, V a1);
static V W_Chk_dbook__tld(V *a);
static V F_Chk_dMap_dfind(V a1, V a2);
static V W_Chk_dMap_dfind(V *a);
static V F_Chk_dMap_dfind_dgo(V a1, V a2);
static V W_Chk_dMap_dfind_dgo(V *a);
static V F_Map_dbit(V a0, V a1);
static V W_Map_dbit(V *a);
static V W_Nat_ddivmod(V *a);
static V F_Map_dbit_dat(V a0, V a1);
static V W_Map_dbit_dat(V *a);
static V F_Map_dbit_dgo(V a0, V a1, V a2);
static V W_Map_dbit_dgo(V *a);
static V F_Map_dbit_dgo_drec(V a0, V a1);
static V W_Map_dbit_dgo_drec(V *a);
static V F_Map_dbit_dchr(V a0, V a1);
static V W_Map_dbit_dchr(V *a);
static V W_Nat_dsub(V *a);
static V F_Map_dbit_du(V a0, V a1);
static V W_Map_dbit_du(V *a);
static V W_U32_dshrn(V *a);
static V W_U32_dand(V *a);
static V W_U32_dis__ne(V *a);
static V F_Map_dbit_dgo_dchr(V a0, V a1);
static V W_Map_dbit_dgo_dchr(V *a);
static V F_Pair_dsnd(V a2);
static V W_Pair_dsnd(V *a);
static V F_Chk_dMap_dfind_dnode(V a1, V a2, V a3, V a4);
static V W_Chk_dMap_dfind_dnode(V *a);
static V F_String_deq(V a0, V a1);
static V W_String_deq(V *a);
static V F_String_dcmp(V a0, V a1);
static V W_String_dcmp(V *a);
static V F_Char_dcmp(V a0, V a1);
static V W_Char_dcmp(V *a);
static V W_U32_dcmp(V *a);
static V F_String_dcmp_dfin(V a0, V a1, V a2);
static V W_String_dcmp_dfin(V *a);
static V F_String_dcmp_drec(V a0, V a1, V a2);
static V W_String_dcmp_drec(V *a);
static V F_String_deq_dfin(V a0);
static V W_String_deq_dfin(V *a);
static V F_Cmp_dis__eq(V a0);
static V W_Cmp_dis__eq(V *a);
static V F_Chk_dMap_dfind_dleaf(V a1, V a2);
static V W_Chk_dMap_dfind_dleaf(V *a);
static V F_Chk_dmain__has__fun_dgo(V a0, V a1);
static V W_Chk_dmain__has__fun_dgo(V *a);
static V F_Chk_dhas__fun(V a0, V a1, V a2);
static V W_Chk_dhas__fun(V *a);
static V F_Chk_dterm__wnf(V a0, V a1);
static V W_Chk_dterm__wnf(V *a);
static V F_Chk_dwnf_dgo(V a0, V a1, V a2, V a3);
static V S38(void);
static V W_Chk_dwnf_dgo(V *a);
static V F_Chk_dwnf_dback(V a0, V a1, V a2);
static V W_Chk_dwnf_dback(V *a);
static V F_Chk_dlit__ctr(V a0);
static V W_Chk_dlit__ctr(V *a);
static V F_Chk_dlit__step(V a0);
static V S42(void);
static V S43(void);
static V S44(void);
static V S45(void);
static V W_Chk_dlit__step(V *a);
static V F_Chk_dchr__term(V a0, V a1);
static V S46(void);
static V W_Chk_dchr__term(V *a);
static V F_Chk_du32__to__term(V a0, V a1);
static V S47(void);
static V W_Chk_du32__to__term(V *a);
static V F_Chk_dword__to__term(V a0, V a1);
static V S48(void);
static V W_Chk_dword__to__term(V *a);
static V F_Chk_dword__to__term_dgo(V a0, V a1, V a2, V a3);
static V S50(void);
static V S51(void);
static V S52(void);
static V W_Chk_dword__to__term_dgo(V *a);
static V W_U32_dis__zero(V *a);
static V F_Bool_dpick(V a1, V a2, V a3);
static V W_Bool_dpick(V *a);
static V F_Chk_dwnf_dmatd(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Chk_dwnf_dmatd(V *a);
static V F_Chk_dlhs__or(V a0, V a1);
static V W_Chk_dlhs__or(V *a);
static V F_Chk_dterm__apply(V a0, V a1, V a2, V a3);
static V W_Chk_dterm__apply(V *a);
static V F_Chk_dterm__strip(V a0);
static V W_Chk_dterm__strip(V *a);
static V F_Chk_dterm__force(V a0);
static V W_Chk_dterm__force(V *a);
static V F_Chk_dterm__strip_dgo(V a0);
static V W_Chk_dterm__strip_dgo(V *a);
static V F_Chk_dterm__apply_dgo(V a0, V a1, V a2, V a3);
static V W_Chk_dterm__apply_dgo(V *a);
static V F_Chk_dclo__apply(V a0, V a1, V a2);
static V S60(void);
static V S61(void);
static V S62(void);
static V W_Chk_dclo__apply(V *a);
static V F_Chk_dLst_dhead(V a1, V a2);
static V W_Chk_dLst_dhead(V *a);
static V F_List_dappend(V a2, V a3);
static V W_List_dappend(V *a);
static V F_Chk_dmat__goal(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9);
static V W_Chk_dmat__goal(V *a);
static V F_Chk_dmat__goal_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V W_Chk_dmat__goal_dgo(V *a);
static V F_Chk_dmat__goal_ddem(V a0, V a1);
static V W_Chk_dmat__goal_ddem(V *a);
static V F_Chk_dquant__add(V a0, V a1);
static V W_Chk_dquant__add(V *a);
static V F_Chk_dlhs__ext(V a0, V a1, V a2, V a3, V a4);
static V S71(void);
static V W_Chk_dlhs__ext(V *a);
static V F_Chk_dterm__snf(V a0, V a1);
static V W_Chk_dterm__snf(V *a);
static V F_Chk_dsnf_dgo(V a0, V a1);
static V W_Chk_dsnf_dgo(V *a);
static V F_Chk_dsnfs(V a0, V a1);
static V W_Chk_dsnfs(V *a);
static V F_Chk_dsnf_dfun(V a0, V a1);
static V W_Chk_dsnf_dfun(V *a);
static V F_Chk_denv__sets(V a0, V a1, V a2);
static V W_Chk_denv__sets(V *a);
static V F_Chk_denv__set(V a0, V a1, V a2);
static V W_Chk_denv__set(V *a);
static V F_Chk_dhigher(V a0, V a1, V a2);
static V W_Chk_dhigher(V *a);
static V F_Chk_dhighers(V a0, V a1, V a2);
static V W_Chk_dhighers(V *a);
static V F_Chk_dhigher_dapp(V a0, V a1, V a2, V a3);
static V W_Chk_dhigher_dapp(V *a);
static V F_Chk_dsyn__body(V a0);
static V W_Chk_dsyn__body(V *a);
static V F_Chk_denv__get(V a0, V a1);
static V W_Chk_denv__get(V *a);
static V W_U32_dis__eq(V *a);
static V F_Chk_dhigher_dvar(V a0, V a1, V a2, V a3);
static V W_Chk_dhigher_dvar(V *a);
static V F_Chk_dhigher_dval(V a0, V a1, V a2);
static V W_Chk_dhigher_dval(V *a);
static V F_Chk_dTm_drespan(V a0, V a1);
static V W_Chk_dTm_drespan(V *a);
static V F_Chk_dpatt__term(V a0, V a1);
static V W_Chk_dpatt__term(V *a);
static V F_Chk_dSp_dor(V a0, V a1);
static V W_Chk_dSp_dor(V *a);
static V F_Chk_dpatt__terms(V a0, V a1);
static V W_Chk_dpatt__terms(V *a);
static V F_Chk_dwnf_dwalk(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9);
static V W_Chk_dwnf_dwalk(V *a);
static V F_Chk_dwnf_dwalk_dmat(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11, V a12);
static V W_Chk_dwnf_dwalk_dmat(V *a);
static V F_List_dlength(V a2);
static V W_List_dlength(V *a);
static V F_Chk_dlhs__mat(V a0, V a1, V a2, V a3);
static V W_Chk_dlhs__mat(V *a);
static V W_Nat_dadd(V *a);
static V F_Chk_dapp__frames(V a0, V a1);
static V S93(void);
static V W_Chk_dapp__frames(V *a);
static V F_Chk_dterm__cell(V a0, V a1);
static V W_Chk_dterm__cell(V *a);
static V F_Chk_dTm_dspan(V a0);
static V W_Chk_dTm_dspan(V *a);
static V F_Chk_dwnf_dmnb(V a0, V a1, V a2);
static V W_Chk_dwnf_dmnb(V *a);
static V F_Chk_dTm_dis__qua(V a0);
static V W_Chk_dTm_dis__qua(V *a);
static V F_Chk_dwnf_dmna(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dwnf_dmna(V *a);
static V F_Chk_dwnf_dref(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dwnf_dref(V *a);
static V F_Chk_dfrs__apps(V a0, V a1);
static V W_Chk_dfrs__apps(V *a);
static V W_Nat_dis__lt(V *a);
static V F_Chk_dwnf_dref_ddef(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Chk_dwnf_dref_ddef(V *a);
static V F_Chk_dTm_dref__k(V a0);
static V S104(void);
static V W_Chk_dTm_dref__k(V *a);
static V F_Chk_dwnf_drwt(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Chk_dwnf_drwt(V *a);
static V F_Chk_dwnf_defq(V a0, V a1, V a2, V a3);
static V W_Chk_dwnf_defq(V *a);
static V F_Chk_dwnf_dmat(V a0, V a1, V a2, V a3);
static V W_Chk_dwnf_dmat(V *a);
static V F_Chk_dwnf_dlam(V a0, V a1, V a2, V a3);
static V W_Chk_dwnf_dlam(V *a);
static V F_Chk_dlhs__step(V a0, V a1, V a2, V a3);
static V W_Chk_dlhs__step(V *a);
static V F_Chk_dterm__cells(V a0, V a1);
static V S113(void);
static V W_Chk_dterm__cells(V *a);
static V F_Chk_dhas__fun_dgo(V a0, V a1, V a2);
static V W_Chk_dhas__fun_dgo(V *a);
static V F_Chk_dterm__lower(V a0, V a1, V a2);
static V W_Chk_dterm__lower(V *a);
static V F_Chk_dterm__lower_dgo(V a0, V a1, V a2);
static V W_Chk_dterm__lower_dgo(V *a);
static V F_Chk_dlowers(V a0, V a1, V a2);
static V W_Chk_dlowers(V *a);
static V W_U32_dinc(V *a);
static V W_U32_dadd(V *a);
static V F_Chk_dlet__vars(V a0, V a1);
static V W_Chk_dlet__vars(V *a);
static V F_Chk_dlet__ids(V a0, V a1);
static V W_Chk_dlet__ids(V *a);
static V W_U32_dfrom__nat(V *a);
static V F_Chk_dterm__key(V a0);
static V S121(void);
static V S122(void);
static V S123(void);
static V S124(void);
static V S125(void);
static V S126(void);
static V S127(void);
static V S128(void);
static V S129(void);
static V S130(void);
static V S131(void);
static V S132(void);
static V S133(void);
static V S134(void);
static V S135(void);
static V S136(void);
static V S137(void);
static V S138(void);
static V S139(void);
static V S140(void);
static V S141(void);
static V S142(void);
static V S143(void);
static V S144(void);
static V S145(void);
static V S146(void);
static V S147(void);
static V S148(void);
static V S149(void);
static V S150(void);
static V S151(void);
static V S152(void);
static V S153(void);
static V S154(void);
static V S155(void);
static V S156(void);
static V S157(void);
static V S158(void);
static V S159(void);
static V S160(void);
static V S161(void);
static V S162(void);
static V S163(void);
static V S164(void);
static V S165(void);
static V S166(void);
static V S167(void);
static V S168(void);
static V S169(void);
static V S170(void);
static V S171(void);
static V S172(void);
static V W_Chk_dterm__key(V *a);
static V F_String_dappend(V a0, V a1);
static V W_String_dappend(V *a);
static V F_Chk_dshow_dtext(V a0);
static V S175(void);
static V W_Chk_dshow_dtext(V *a);
static V F_Chk_dshow_dchr(V a0, V a1);
static V S176(void);
static V S177(void);
static V S178(void);
static V S179(void);
static V S180(void);
static V S181(void);
static V S182(void);
static V W_Chk_dshow_dchr(V *a);
static V F_Chk_dStr_dchr(V a0);
static V W_Chk_dStr_dchr(V *a);
static V F_Chk_dU32_dshow__hex(V a0);
static V S183(void);
static V W_Chk_dU32_dshow__hex(V *a);
static V F_Chk_dU32_dshow__hex_dgo(V a0, V a1);
static V W_Chk_dU32_dshow__hex_dgo(V *a);
static V W_U32_dis__lt(V *a);
static V F_Chk_dshow__hex_dmore(V a0, V a1, V a2);
static V W_Chk_dshow__hex_dmore(V *a);
static V W_U32_dis__gt(V *a);
static V W_U32_dis__le(V *a);
static V W_U32_dis__ge(V *a);
static V F_Bool_dand(V a0, V a1);
static V W_Bool_dand(V *a);
static V F_Bool_dor(V a0, V a1);
static V W_Bool_dor(V *a);
static V W_Nat_dshow(V *a);
static V F_Chk_dterm__key_dlist(V a0);
static V S190(void);
static V S191(void);
static V W_Chk_dterm__key_dlist(V *a);
static V F_String_djoin(V a0, V a1);
static V W_String_djoin(V *a);
static V F_String_djoin_dgo(V a0, V a1, V a2);
static V W_String_djoin_dgo(V *a);
static V F_U32_dshow(V a0);
static V W_U32_dshow(V *a);
static V F_U32_dshow_dif(V a0, V a1);
static V W_U32_dshow_dif(V *a);
static V F_U32_dshow_dgo(V a0, V a1, V a2);
static V W_U32_dshow_dgo(V *a);
static V F_U32_dshow_dfin(V a0, V a1, V a2, V a3);
static V W_U32_dshow_dfin(V *a);
static V W_U32_dmod(V *a);
static V W_U32_ddiv(V *a);
static V F_Chk_dquant__show(V a0);
static V S199(void);
static V S200(void);
static V S201(void);
static V W_Chk_dquant__show(V *a);
static V F_Chk_dshow_dqua(V a0);
static V S203(void);
static V S204(void);
static V S205(void);
static V W_Chk_dshow_dqua(V *a);
static V F_Chk_dhas__fun_dadt(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dhas__fun_dadt(V *a);
static V F_Chk_dStr_dhas(V a0, V a1);
static V W_Chk_dStr_dhas(V *a);
static V F_Chk_dhas__fun_dadt_dc(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Chk_dhas__fun_dadt_dc(V *a);
static V F_Chk_dhas__fun_dcs(V a0);
static V W_Chk_dhas__fun_dcs(V *a);
static V F_Chk_dhas__fun_dctrs(V a0, V a1, V a2, V a3);
static V W_Chk_dhas__fun_dctrs(V *a);
static V F_Chk_dhas__fun_dfill(V a0, V a1, V a2);
static V W_Chk_dhas__fun_dfill(V *a);
static V F_Chk_dAll_db(V a0);
static V W_Chk_dAll_db(V *a);
static V F_Chk_dhas__fun_dfields(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dhas__fun_dfields(V *a);
static V F_Chk_dhas__fun_dfield(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dhas__fun_dfield(V *a);
static V F_Chk_dmain__is__io(V a0);
static V W_Chk_dmain__is__io(V *a);
static V F_Chk_dmain__is__io_dgo(V a0, V a1);
static V W_Chk_dmain__is__io_dgo(V *a);
static V F_Chk_dterm__head(V a0);
static V W_Chk_dterm__head(V *a);
static V F_Chk_dterm__unapply(V a0);
static V W_Chk_dterm__unapply(V *a);
static V F_Chk_dterm__unapply_dgo(V a0, V a1);
static V W_Chk_dterm__unapply_dgo(V *a);
static V F_Pair_dfst(V a2);
static V W_Pair_dfst(V *a);
static V F_Chk_dvalid_dio(V a0, V a1);
static V S218(void);
static V W_Chk_dvalid_dio(V *a);
static V F_Chk_dvalid_dio_dbase(V a0);
static V W_Chk_dvalid_dio_dbase(V *a);
static V F_Bool_dnot(V a0);
static V W_Bool_dnot(V *a);
static V F_Main_dchecked_dgo(V a0, V a1, V a2, V a3);
static V W_Main_dchecked_dgo(V *a);
static V F_Main_dbuild(V a0, V a1);
static V L222(V *a);
static V L223(V *a);
static V W_Main_dbuild(V *a);
static V F_Main_dparse(V a0);
static V W_Main_dparse(V *a);
static V F_P_dfile(V a0);
static V W_P_dfile(V *a);
static V F_Lex_dall(V a0);
static V W_Lex_dall(V *a);
static V F_Lex_dlines(V a0);
static V W_Lex_dlines(V *a);
static V F_String_dlines(V a0);
static V W_String_dlines(V *a);
static V F_String_dsplit(V a0, V a1);
static V W_String_dsplit(V *a);
static V F_Char_dis__eq(V a0, V a1);
static V W_Char_dis__eq(V *a);
static V F_String_dsplit_dfin(V a0, V a1, V a2);
static V W_String_dsplit_dfin(V *a);
static V F_String_dsplit_dpush(V a0, V a1);
static V W_String_dsplit_dpush(V *a);
static V F_Lex_dlines_dgo(V a0, V a1);
static V W_Lex_dlines_dgo(V *a);
static V F_Lex_dline(V a0, V a1, V a2, V a3);
static V W_Lex_dline(V *a);
static V F_Lex_dclass(V a0);
static V W_Lex_dclass(V *a);
static V F_Char_dis__digit(V a0);
static V W_Char_dis__digit(V *a);
static V F_Lex_dis__ids(V a0);
static V W_Lex_dis__ids(V *a);
static V F_Char_dto__u32(V a0);
static V W_Char_dto__u32(V *a);
static V F_Char_dis__alpha(V a0);
static V W_Char_dis__alpha(V *a);
static V F_Char_dis__lower(V a0);
static V W_Char_dis__lower(V *a);
static V F_Char_dis__upper(V a0);
static V W_Char_dis__upper(V *a);
static V F_Lex_dline_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Lex_dline_dgo(V *a);
static V F_Lex_dop__of(V a0);
static V W_Lex_dop__of(V *a);
static V F_Lex_dops3(void);
static V S237(void);
static V S238(void);
static V S239(void);
static V S240(void);
static V W_Lex_dops3(V *a);
static V F_Lex_dfind__op(V a0, V a1);
static V W_Lex_dfind__op(V *a);
static V F_String_dstarts__with(V a0, V a1);
static V W_String_dstarts__with(V *a);
static V F_String_dstarts__with_dif(V a0, V a1, V a2);
static V W_String_dstarts__with_dif(V *a);
static V F_Lex_dfind__op_dif(V a0, V a1, V a2, V a3);
static V W_Lex_dfind__op_dif(V *a);
static V F_Lex_dop__of_dgo(V a0, V a1);
static V W_Lex_dop__of_dgo(V *a);
static V F_Lex_dops2(void);
static V S247(void);
static V S248(void);
static V S249(void);
static V S250(void);
static V S251(void);
static V S252(void);
static V S253(void);
static V S254(void);
static V S255(void);
static V S256(void);
static V S257(void);
static V S258(void);
static V S259(void);
static V W_Lex_dops2(V *a);
static V F_Lex_dop__of_dtwo(V a0, V a1);
static V W_Lex_dop__of_dtwo(V *a);
static V F_String_dtake(V a0, V a1);
static V W_String_dtake(V *a);
static V F_Lex_dline_dop(V a0, V a1, V a2, V a3, V a4);
static V W_Lex_dline_dop(V *a);
static V F_String_dlength(V a0);
static V W_String_dlength(V *a);
static V F_String_ddrop(V a0, V a1);
static V W_String_ddrop(V *a);
static V F_Lex_dstr(V a0, V a1);
static V W_Lex_dstr(V *a);
static V F_Lex_dstr_dif(V a0, V a1, V a2, V a3);
static V W_Lex_dstr_dif(V *a);
static V F_Lex_dlit__char(V a0);
static V W_Lex_dlit__char(V *a);
static V F_Lex_dlit__char_dif(V a0, V a1, V a2);
static V W_Lex_dlit__char_dif(V *a);
static V F_Lex_dlit__char_desc(V a0);
static V W_Lex_dlit__char_desc(V *a);
static V F_Lex_desc(V a0);
static V W_Lex_desc(V *a);
static V F_Lex_dstr_dnext(V a0, V a1);
static V W_Lex_dstr_dnext(V *a);
static V F_Str_drev(V a0);
static V W_Str_drev(V *a);
static V F_String_dreverse(V a0);
static V W_String_dreverse(V *a);
static V F_String_dreverse_dgo(V a0, V a1);
static V W_String_dreverse_dgo(V *a);
static V F_Lex_dline_dstr(V a0, V a1, V a2, V a3);
static V W_Lex_dline_dstr(V *a);
static V F_Lex_dline_dchr(V a0, V a1, V a2, V a3);
static V W_Lex_dline_dchr(V *a);
static V F_Lex_ddrop1(V a0);
static V W_Lex_ddrop1(V *a);
static V F_Lex_ddigits(V a0, V a1);
static V W_Lex_ddigits(V *a);
static V F_Lex_ddigits_dif(V a0, V a1, V a2, V a3);
static V W_Lex_ddigits_dif(V *a);
static V W_U32_dsub(V *a);
static V W_U32_dmul(V *a);
static V F_Lex_dline_dnum(V a0, V a1, V a2, V a3);
static V W_Lex_dline_dnum(V *a);
static V F_Lex_dline_dnum_dgo(V a0, V a1, V a2, V a3, V a4);
static V W_Lex_dline_dnum_dgo(V *a);
static V F_Lex_dline_dnum_dif(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Lex_dline_dnum_dif(V *a);
static V F_Lex_ddtext(V a0, V a1);
static V W_Lex_ddtext(V *a);
static V F_Lex_ddtext_dif(V a0, V a1, V a2, V a3);
static V W_Lex_ddtext_dif(V *a);
static V F_Lex_dline_dflt(V a0, V a1, V a2, V a3, V a4);
static V S285(void);
static V W_Lex_dline_dflt(V *a);
static V F_Lex_dline_dnat(V a0, V a1, V a2, V a3, V a4);
static V W_Lex_dline_dnat(V *a);
static V F_Lex_dline_dnat_dif(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Lex_dline_dnat_dif(V *a);
static V F_Lex_did(V a0, V a1);
static V W_Lex_did(V *a);
static V F_Lex_dis__idc(V a0);
static V W_Lex_dis__idc(V *a);
static V F_Lex_did_dif(V a0, V a1, V a2, V a3);
static V W_Lex_did_dif(V *a);
static V F_Lex_dline_did(V a0, V a1, V a2, V a3);
static V W_Lex_dline_did(V *a);
static V F_List_dreverse(V a2);
static V W_List_dreverse(V *a);
static V F_List_dreverse_dgo(V a2, V a3);
static V W_List_dreverse_dgo(V *a);
static V F_Lex_dindent(V a0);
static V W_Lex_dindent(V *a);
static V F_Lex_dindent_dif(V a0, V a1);
static V W_Lex_dindent_dif(V *a);
static V F_Lex_dlines_dput(V a0, V a1);
static V W_Lex_dlines_dput(V *a);
static V F_Lay_dlines(V a0, V a1);
static V W_Lay_dlines(V *a);
static V F_Lay_dline(V a0, V a1);
static V W_Lay_dline(V *a);
static V F_Lay_dline_dgo(V a0, V a1, V a2, V a3, V a4);
static V W_Lay_dline_dgo(V *a);
static V F_Lay_dtoks(V a0, V a1);
static V S303(void);
static V W_Lay_dtoks(V *a);
static V F_Lay_dis__op(V a0);
static V S305(void);
static V S306(void);
static V S307(void);
static V S308(void);
static V S309(void);
static V S310(void);
static V S311(void);
static V S312(void);
static V S313(void);
static V S314(void);
static V S315(void);
static V S316(void);
static V S317(void);
static V W_Lay_dis__op(V *a);
static V F_List_dcontains(V a1, V a2, V a3);
static V W_List_dcontains(V *a);
static V F_Lay_dis__sym(V a0, V a1);
static V W_Lay_dis__sym(V *a);
static V F_Str_deq(V a0, V a1);
static V W_Str_deq(V *a);
static V F_Lay_ddelta(V a0);
static V S320(void);
static V S321(void);
static V S322(void);
static V S323(void);
static V S324(void);
static V S325(void);
static V W_Lay_ddelta(V *a);
static V F_Lay_dstart(V a0, V a1, V a2);
static V W_Lay_dstart(V *a);
static V F_Lay_dstart_dop(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V W_Lay_dstart_dop(V *a);
static V F_Lay_dstart_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Lay_dstart_dgo(V *a);
static V F_Lay_dtok(V a0, V a1);
static V W_Lay_dtok(V *a);
static V F_Lay_dpop(V a0, V a1, V a2, V a3);
static V W_Lay_dpop(V *a);
static V F_Lay_dpop_dif(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Lay_dpop_dif(V *a);
static V F_Lay_ddedent(V a0, V a1, V a2, V a3);
static V W_Lay_ddedent(V *a);
static V F_Lay_dstart_dgt(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Lay_dstart_dgt(V *a);
static V F_Lay_dtop(V a0);
static V W_Lay_dtop(V *a);
static V F_Lay_dfinish(V a0);
static V W_Lay_dfinish(V *a);
static V F_Lay_dfinish_dgo(V a0);
static V W_Lay_dfinish_dgo(V *a);
static V F_P_ddecls(void);
static V L337(V *a);
static V L338(V *a);
static V W_P_ddecls(V *a);
static V F_P_dtok__kind(V a0);
static V W_P_dtok__kind(V *a);
static V F_P_dstuck(V a0);
static V W_P_dstuck(V *a);
static V F_P_ddecls_dgo(V a0);
static V L342(V *a);
static V L343(V *a);
static V W_P_ddecls_dgo(V *a);
static V F_Parser_dpure(V a1);
static V L344(V *a);
static V W_Parser_dpure(V *a);
static V F_Parser_dbind(V a2, V a3);
static V L345(V *a);
static V W_Parser_dbind(V *a);
static V F_Parser_dgo(V a2, V a3);
static V W_Parser_dgo(V *a);
static V F_P_ddecl(void);
static V L347(V *a);
static V S348(void);
static V W_P_ddecl(V *a);
static V F_P_dtok__is(V a0, V a1);
static V W_P_dtok__is(V *a);
static V F_P_ddecl_dat(V a0, V a1);
static V L351(V *a);
static V L352(V *a);
static V L353(V *a);
static V S354(void);
static V S355(void);
static V S356(void);
static V S357(void);
static V W_P_ddecl_dat(V *a);
static V F_P_dtok__which__id(V a0, V a1);
static V W_P_dtok__which__id(V *a);
static V F_P_dwhich(V a0, V a1);
static V W_P_dwhich(V *a);
static V F_P_dwhich_dif(V a0, V a1, V a2);
static V W_P_dwhich_dif(V *a);
static V F_P_ddecl_dgo(V a0);
static V S362(void);
static V L363(V *a);
static V S364(void);
static V S365(void);
static V W_P_ddecl_dgo(V *a);
static V F_P_derr(V a0);
static V L366(V *a);
static V W_P_derr(V *a);
static V F_P_derr_dgo(V a0, V a1);
static V S368(void);
static V S369(void);
static V S370(void);
static V S371(void);
static V S372(void);
static V W_P_derr_dgo(V *a);
static V F_TK_dshow(V a0);
static V S374(void);
static V S375(void);
static V S376(void);
static V S377(void);
static V S378(void);
static V S379(void);
static V S380(void);
static V S381(void);
static V S382(void);
static V S383(void);
static V S384(void);
static V S385(void);
static V W_TK_dshow(V *a);
static V F_P_dimport(void);
static V L386(V *a);
static V L387(V *a);
static V L388(V *a);
static V S389(void);
static V L390(V *a);
static V L391(V *a);
static V W_P_dimport(V *a);
static V F_P_dskip__line(void);
static V L392(V *a);
static V W_P_dskip__line(V *a);
static V F_P_dskip__line_dgo(V a0);
static V W_P_dskip__line_dgo(V *a);
static V F_P_dskip__block_dgo(V a0, V a1);
static V W_P_dskip__block_dgo(V *a);
static V F_P_dskip__block_dde(V a0, V a1, V a2);
static V W_P_dskip__block_dde(V *a);
static V F_P_dtok__is__id(V a0, V a1);
static V W_P_dtok__is__id(V *a);
static V F_P_dimport_dalias(V a0);
static V L398(V *a);
static V S399(void);
static V W_P_dimport_dalias(V *a);
static V F_P_dident(void);
static V L400(V *a);
static V W_P_dident(V *a);
static V F_P_dident_dk(V a0);
static V L402(V *a);
static V S403(void);
static V L404(V *a);
static V S405(void);
static V W_P_dident_dk(V *a);
static V F_P_dskip(void);
static V L406(V *a);
static V W_P_dskip(V *a);
static V F_P_dskip_dgo(V a0);
static V W_P_dskip_dgo(V *a);
static V F_P_dskip_dif(V a0, V a1, V a2);
static V W_P_dskip_dif(V *a);
static V F_P_dpeek(void);
static V L409(V *a);
static V W_P_dpeek(V *a);
static V F_P_dpeek_dgo(V a0);
static V W_P_dpeek_dgo(V *a);
static V F_P_deof__tok(void);
static V W_P_deof__tok(V *a);
static V F_P_dimport_dpath(void);
static V L411(V *a);
static V W_P_dimport_dpath(V *a);
static V F_P_dimport_dpath_dgo(V a0);
static V S413(void);
static V S414(void);
static V W_P_dimport_dpath_dgo(V *a);
static V F_P_dimport_dpath_dcat(V a0, V a1);
static V W_P_dimport_dpath_dcat(V *a);
static V F_P_dimport_dpath_did(V a0, V a1, V a2, V a3, V a4);
static V S417(void);
static V W_P_dimport_dpath_did(V *a);
static V F_P_dlaw(void);
static V L418(V *a);
static V L419(V *a);
static V S420(void);
static V L421(V *a);
static V L422(V *a);
static V L423(V *a);
static V W_P_dlaw(V *a);
static V F_P_dlaw_dlines(void);
static V L424(V *a);
static V L425(V *a);
static V W_P_dlaw_dlines(V *a);
static V F_P_dis__de(V a0);
static V W_P_dis__de(V *a);
static V F_P_dlaw_dgo(V a0, V a1);
static V L428(V *a);
static V S429(void);
static V W_P_dlaw_dgo(V *a);
static V F_P_dlaw_dline(V a0);
static V L431(V *a);
static V L432(V *a);
static V L433(V *a);
static V L434(V *a);
static V L435(V *a);
static V W_P_dlaw_dline(V *a);
static V F_P_dparam(void);
static V L436(V *a);
static V L437(V *a);
static V L438(V *a);
static V L439(V *a);
static V L440(V *a);
static V S441(void);
static V W_P_dparam(V *a);
static V F_P_dparam_dty(V a0, V a1, V a2);
static V L443(V *a);
static V L444(V *a);
static V S445(void);
static V W_P_dparam_dty(V *a);
static V F_P_dhead(V a0);
static V S447(void);
static V W_P_dhead(V *a);
static V F_P_dexpr(void);
static V W_P_dexpr(V *a);
static V F_P_dbin(V a0);
static V L448(V *a);
static V W_P_dbin(V *a);
static V F_P_dbin_dloop(V a0, V a1);
static V L449(V *a);
static V W_P_dbin_dloop(V *a);
static V F_P_dtok__op(V a0);
static V S451(void);
static V W_P_dtok__op(V *a);
static V F_P_dops(void);
static V S452(void);
static V S453(void);
static V S454(void);
static V S455(void);
static V S456(void);
static V S457(void);
static V S458(void);
static V S459(void);
static V S460(void);
static V S461(void);
static V S462(void);
static V S463(void);
static V S464(void);
static V S465(void);
static V S466(void);
static V S467(void);
static V S468(void);
static V S469(void);
static V S470(void);
static V S471(void);
static V S472(void);
static V S473(void);
static V W_P_dops(V *a);
static V F_P_dop__find(V a0, V a1);
static V S475(void);
static V W_P_dop__find(V *a);
static V F_P_dop__find_dif(V a0, V a1, V a2, V a3);
static V W_P_dop__find_dif(V *a);
static V F_P_dbin_dloop_dop(V a0, V a1, V a2);
static V W_P_dbin_dloop_dop(V *a);
static V F_P_dbin_dloop_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V L479(V *a);
static V L480(V *a);
static V W_P_dbin_dloop_dgo(V *a);
static V F_P_dmk__bin(V a0, V a1, V a2);
static V S481(void);
static V S482(void);
static V S483(void);
static V S484(void);
static V S485(void);
static V S486(void);
static V S487(void);
static V S488(void);
static V W_P_dmk__bin(V *a);
static V F_P_dmk__bin_dgo(V a0, V a1, V a2, V a3);
static V S490(void);
static V S491(void);
static V S492(void);
static V S493(void);
static V S494(void);
static V S495(void);
static V S496(void);
static V S497(void);
static V W_P_dmk__bin_dgo(V *a);
static V F_P_dterm(void);
static V L498(V *a);
static V W_P_dterm(V *a);
static V F_P_dpostfix(V a0);
static V L499(V *a);
static V W_P_dpostfix(V *a);
static V F_P_dpostfix_dt(V a0, V a1);
static V S500(void);
static V S501(void);
static V S502(void);
static V W_P_dpostfix_dt(V *a);
static V F_P_dtok__which(V a0, V a1);
static V W_P_dtok__which(V *a);
static V F_P_dtok__sp(V a0);
static V W_P_dtok__sp(V *a);
static V F_P_dpostfix_dk(V a0, V a1);
static V L506(V *a);
static V S507(void);
static V L508(V *a);
static V L509(V *a);
static V L510(V *a);
static V L511(V *a);
static V S512(void);
static V L513(V *a);
static V S514(void);
static V S515(void);
static V W_P_dpostfix_dk(V *a);
static V F_P_dexpect(V a0);
static V L516(V *a);
static V W_P_dexpect(V *a);
static V F_P_dexpect_dif(V a0, V a1);
static V S518(void);
static V S519(void);
static V W_P_dexpect_dif(V *a);
static V F_P_dlist(V a0);
static V L520(V *a);
static V W_P_dlist(V *a);
static V F_P_dlist_dstuck(V a0, V a1, V a2);
static V S522(void);
static V L523(V *a);
static V W_P_dlist_dstuck(V *a);
static V F_P_dlist_dgo(V a0, V a1);
static V L525(V *a);
static V W_P_dlist_dgo(V *a);
static V F_P_dlist_ditem(V a0);
static V L526(V *a);
static V S527(void);
static V L528(V *a);
static V L529(V *a);
static V W_P_dlist_ditem(V *a);
static V F_P_dlist_dmore(V a0, V a1);
static V L531(V *a);
static V W_P_dlist_dmore(V *a);
static V F_P_deat(V a0);
static V L532(V *a);
static V W_P_deat(V *a);
static V F_P_deat_dif(V a0);
static V L534(V *a);
static V W_P_deat_dif(V *a);
static V F_P_dprimary(void);
static V L535(V *a);
static V W_P_dprimary(V *a);
static V F_P_dprimary_dk(V a0);
static V L537(V *a);
static V L538(V *a);
static V L539(V *a);
static V L540(V *a);
static V L541(V *a);
static V L542(V *a);
static V L543(V *a);
static V L544(V *a);
static V L545(V *a);
static V S546(void);
static V S547(void);
static V S548(void);
static V S549(void);
static V S550(void);
static V S551(void);
static V S552(void);
static V S553(void);
static V S554(void);
static V S555(void);
static V L556(V *a);
static V S557(void);
static V W_P_dprimary_dk(V *a);
static V F_P_dprimary_dsym(V a0);
static V L559(V *a);
static V L560(V *a);
static V L561(V *a);
static V L562(V *a);
static V L563(V *a);
static V L564(V *a);
static V L565(V *a);
static V L566(V *a);
static V L567(V *a);
static V S568(void);
static V S569(void);
static V L570(V *a);
static V S571(void);
static V W_P_dprimary_dsym(V *a);
static V F_P_damp_dgo(V a0);
static V L573(V *a);
static V S574(void);
static V W_P_damp_dgo(V *a);
static V F_P_ddep(void);
static V S575(void);
static V L576(V *a);
static V S577(void);
static V L578(V *a);
static V L579(V *a);
static V S580(void);
static V L581(V *a);
static V L582(V *a);
static V S583(void);
static V W_P_ddep(V *a);
static V F_P_dneg(V a0);
static V S585(void);
static V W_P_dneg(V *a);
static V F_P_dbrace(void);
static V L586(V *a);
static V L587(V *a);
static V S588(void);
static V W_P_dbrace(V *a);
static V F_P_dbrace_dgo(V a0);
static V L590(V *a);
static V S591(void);
static V L592(V *a);
static V S593(void);
static V W_P_dbrace_dgo(V *a);
static V F_P_dbrace_dbody(void);
static V L594(V *a);
static V L595(V *a);
static V S596(void);
static V S597(void);
static V S598(void);
static V W_P_dbrace_dbody(V *a);
static V F_P_dbrace_dtail(V a0, V a1);
static V L600(V *a);
static V L601(V *a);
static V S602(void);
static V L603(V *a);
static V L604(V *a);
static V S605(void);
static V L606(V *a);
static V S607(void);
static V L608(V *a);
static V L609(V *a);
static V S610(void);
static V L611(V *a);
static V L612(V *a);
static V S613(void);
static V L614(V *a);
static V S615(void);
static V L616(V *a);
static V L617(V *a);
static V S618(void);
static V L619(V *a);
static V S620(void);
static V L621(V *a);
static V W_P_dbrace_dtail(V *a);
static V F_P_dbrack(void);
static V L622(V *a);
static V L623(V *a);
static V S624(void);
static V W_P_dbrack(V *a);
static V F_P_dbrack_dgo(V a0);
static V L626(V *a);
static V S627(void);
static V W_P_dbrack_dgo(V *a);
static V F_P_dbrack_dbody(void);
static V L628(V *a);
static V L629(V *a);
static V S630(void);
static V W_P_dbrack_dbody(V *a);
static V F_P_dbrack_dtail(V a0, V a1);
static V S632(void);
static V L633(V *a);
static V S634(void);
static V L635(V *a);
static V W_P_dbrack_dtail(V *a);
static V F_P_delist(V a0);
static V S637(void);
static V S638(void);
static V W_P_delist(V *a);
static V F_P_darr(V a0);
static V L639(V *a);
static V L640(V *a);
static V L641(V *a);
static V L642(V *a);
static V L643(V *a);
static V S644(void);
static V L645(V *a);
static V S646(void);
static V L647(V *a);
static V S648(void);
static V S649(void);
static V W_P_darr(V *a);
static V F_P_darr_dsize(V a0, V a1);
static V W_P_darr_dsize(V *a);
static V F_P_darr_dsize_dlit(V a0);
static V L652(V *a);
static V S653(void);
static V L654(V *a);
static V W_P_darr_dsize_dlit(V *a);
static V F_P_dlog2(V a0);
static V W_P_dlog2(V *a);
static V W_U32_dlog2(V *a);
static V F_P_dparen(void);
static V L655(V *a);
static V L656(V *a);
static V S657(void);
static V W_P_dparen(V *a);
static V F_P_dparen_dgo(V a0);
static V L659(V *a);
static V S660(void);
static V W_P_dparen_dgo(V *a);
static V F_P_dparen_dbody(void);
static V L661(V *a);
static V L662(V *a);
static V S663(void);
static V S664(void);
static V W_P_dparen_dbody(V *a);
static V F_P_dparen_dtail(V a0, V a1);
static V L666(V *a);
static V S667(void);
static V L668(V *a);
static V L669(V *a);
static V L670(V *a);
static V S671(void);
static V L672(V *a);
static V S673(void);
static V L674(V *a);
static V W_P_dparen_dtail(V *a);
static V F_P_dtuple(V a0);
static V S676(void);
static V S677(void);
static V W_P_dtuple(V *a);
static V F_P_dafter__id(V a0, V a1);
static V S678(void);
static V S679(void);
static V S680(void);
static V W_P_dafter__id(V *a);
static V F_P_dafter__id_dgo(V a0, V a1, V a2);
static V L682(V *a);
static V L683(V *a);
static V W_P_dafter__id_dgo(V *a);
static V F_P_dafter__id_dk(V a0, V a1);
static V L685(V *a);
static V S686(void);
static V L687(V *a);
static V L688(V *a);
static V L689(V *a);
static V W_P_dafter__id_dk(V *a);
static V F_P_dtyargs(void);
static V L690(V *a);
static V W_P_dtyargs(V *a);
static V F_P_dtyargs_dgo(V a0, V a1);
static V W_P_dtyargs_dgo(V *a);
static V F_P_dis__gt(V a0);
static V S692(void);
static V S693(void);
static V S694(void);
static V W_P_dis__gt(V *a);
static V F_P_dtyargs_dclose(V a0);
static V L696(V *a);
static V W_P_dtyargs_dclose(V *a);
static V F_P_dtyargs_ditem(void);
static V L697(V *a);
static V S698(void);
static V L699(V *a);
static V L700(V *a);
static V W_P_dtyargs_ditem(V *a);
static V F_P_dtyargs_dmore(V a0);
static V L702(V *a);
static V W_P_dtyargs_dmore(V *a);
static V F_P_dgt(void);
static V L703(V *a);
static V W_P_dgt(V *a);
static V F_P_dgt_dgo(V a0);
static V S705(void);
static V S706(void);
static V S707(void);
static V S708(void);
static V W_P_dgt_dgo(V *a);
static V F_P_dgt_dif(V a0, V a1, V a2, V a3, V a4);
static V S710(void);
static V S711(void);
static V S712(void);
static V W_P_dgt_dif(V *a);
static V F_P_dparam_dskip__mode(V a0);
static V W_P_dparam_dskip__mode(V *a);
static V F_P_dparam_dskip__mode_dgo(V a0);
static V W_P_dparam_dskip__mode_dgo(V *a);
static V F_P_dparam_dmode(V a0);
static V S714(void);
static V S715(void);
static V S716(void);
static V W_P_dparam_dmode(V *a);
static V F_P_dnls(void);
static V L717(V *a);
static V W_P_dnls(V *a);
static V F_P_dis__nl(V a0);
static V W_P_dis__nl(V *a);
static V F_P_dnls_dif(V a0);
static V L720(V *a);
static V W_P_dnls_dif(V *a);
static V F_P_dexpect__in(void);
static V L721(V *a);
static V W_P_dexpect__in(V *a);
static V F_P_dis__in(V a0);
static V W_P_dis__in(V *a);
static V F_P_dexpect__in_dgo(V a0);
static V S724(void);
static V W_P_dexpect__in_dgo(V *a);
static V F_P_dtype(void);
static V L725(V *a);
static V L726(V *a);
static V L727(V *a);
static V S728(void);
static V S729(void);
static V L730(V *a);
static V L731(V *a);
static V L732(V *a);
static V S733(void);
static V L734(V *a);
static V L735(V *a);
static V L736(V *a);
static V W_P_dtype(V *a);
static V F_P_dtype_dbody(V a0);
static V L738(V *a);
static V W_P_dtype_dbody(V *a);
static V F_P_dctors(void);
static V L739(V *a);
static V L740(V *a);
static V W_P_dctors(V *a);
static V F_P_dctors_dgo(V a0, V a1);
static V L742(V *a);
static V L743(V *a);
static V S744(void);
static V L745(V *a);
static V L746(V *a);
static V L747(V *a);
static V W_P_dctors_dgo(V *a);
static V F_P_dfields(void);
static V L748(V *a);
static V S749(void);
static V W_P_dfields(V *a);
static V F_P_dfields_dgo(V a0);
static V L751(V *a);
static V S752(void);
static V L753(V *a);
static V S754(void);
static V L755(V *a);
static V L756(V *a);
static V S757(void);
static V L758(V *a);
static V L759(V *a);
static V S760(void);
static V L761(V *a);
static V L762(V *a);
static V W_P_dfields_dgo(V *a);
static V F_P_duntil__is(void);
static V L763(V *a);
static V W_P_duntil__is(V *a);
static V F_P_duntil__is_dgo(V a0);
static V S765(void);
static V W_P_duntil__is_dgo(V *a);
static V F_P_duntil__is_dif(V a0, V a1, V a2);
static V W_P_duntil__is_dif(V *a);
static V F_P_dtparams_dopt(V a0);
static V L768(V *a);
static V L769(V *a);
static V W_P_dtparams_dopt(V *a);
static V F_P_dtparams(void);
static V S770(void);
static V L771(V *a);
static V L772(V *a);
static V L773(V *a);
static V S774(void);
static V L775(V *a);
static V L776(V *a);
static V W_P_dtparams(V *a);
static V F_P_dtparams_dmore(V a0);
static V L778(V *a);
static V W_P_dtparams_dmore(V *a);
static V F_P_dskip__ann(void);
static V L779(V *a);
static V S780(void);
static V W_P_dskip__ann(V *a);
static V F_P_dskip__ann_dgo(V a0);
static V L782(V *a);
static V L783(V *a);
static V W_P_dskip__ann_dgo(V *a);
static V F_P_ddef(void);
static V L784(V *a);
static V L785(V *a);
static V S786(void);
static V L787(V *a);
static V L788(V *a);
static V L789(V *a);
static V S790(void);
static V L791(V *a);
static V S792(void);
static V L793(V *a);
static V L794(V *a);
static V L795(V *a);
static V S796(void);
static V W_P_ddef(V *a);
static V F_P_ddef_dbody(V a0, V a1, V a2, V a3);
static V L798(V *a);
static V L799(V *a);
static V W_P_ddef_dbody(V *a);
static V F_Fold_dplain(V a0);
static V S801(void);
static V S802(void);
static V S803(void);
static V W_Fold_dplain(V *a);
static V F_P_dstmts(void);
static V L804(V *a);
static V L805(V *a);
static V W_P_dstmts(V *a);
static V F_P_dstmts_dgo(V a0, V a1);
static V L807(V *a);
static V L808(V *a);
static V L809(V *a);
static V W_P_dstmts_dgo(V *a);
static V F_P_dstmt(void);
static V L810(V *a);
static V S811(void);
static V W_P_dstmt(V *a);
static V F_P_dstmt_dgo(V a0, V a1);
static V L813(V *a);
static V S814(void);
static V S815(void);
static V S816(void);
static V W_P_dstmt_dgo(V *a);
static V F_P_dstmt_did(V a0);
static V L818(V *a);
static V L819(V *a);
static V L820(V *a);
static V L821(V *a);
static V L822(V *a);
static V W_P_dstmt_did(V *a);
static V F_P_dstmt_dscan(V a0);
static V W_P_dstmt_dscan(V *a);
static V W_U32_dto__nat(V *a);
static V F_P_dstmt_dscan_dgo(V a0);
static V L824(V *a);
static V W_P_dstmt_dscan_dgo(V *a);
static V F_P_dbind__stmt(void);
static V S825(void);
static V L826(V *a);
static V L827(V *a);
static V L828(V *a);
static V S829(void);
static V W_P_dbind__stmt(V *a);
static V F_P_dbind_darr(V a0, V a1);
static V L831(V *a);
static V L832(V *a);
static V S833(void);
static V L834(V *a);
static V S835(void);
static V L836(V *a);
static V L837(V *a);
static V S838(void);
static V S839(void);
static V L840(V *a);
static V S841(void);
static V L842(V *a);
static V L843(V *a);
static V W_P_dbind_darr(V *a);
static V F_P_dlet__stmt(void);
static V S844(void);
static V S845(void);
static V L846(V *a);
static V L847(V *a);
static V S848(void);
static V L849(V *a);
static V L850(V *a);
static V W_P_dlet__stmt(V *a);
static V F_P_dlets_dpar(V a0, V a1);
static V S851(void);
static V S852(void);
static V W_P_dlets_dpar(V *a);
static V F_P_dlets(V a0, V a1);
static V W_P_dlets(V *a);
static V W_Nat_dis__gt(V *a);
static V F_P_dexprs__n(V a0);
static V L856(V *a);
static V L857(V *a);
static V W_P_dexprs__n(V *a);
static V F_P_dpat__seq(V a0);
static V L858(V *a);
static V W_P_dpat__seq(V *a);
static V F_P_dpat__seq_dstop(V a0, V a1);
static V W_P_dpat__seq_dstop(V *a);
static V F_P_dpat__seq_dgo(V a0, V a1, V a2);
static V L860(V *a);
static V L861(V *a);
static V W_P_dpat__seq_dgo(V *a);
static V F_P_dpat(void);
static V L862(V *a);
static V L863(V *a);
static V S864(void);
static V W_P_dpat(V *a);
static V F_P_dpat_dcons(V a0, V a1);
static V L866(V *a);
static V L867(V *a);
static V S868(void);
static V W_P_dpat_dcons(V *a);
static V F_P_dpat1(void);
static V L869(V *a);
static V W_P_dpat1(V *a);
static V F_P_dpat1_dk(V a0);
static V L871(V *a);
static V L872(V *a);
static V S873(void);
static V L874(V *a);
static V L875(V *a);
static V L876(V *a);
static V L877(V *a);
static V L878(V *a);
static V L879(V *a);
static V S880(void);
static V S881(void);
static V S882(void);
static V S883(void);
static V S884(void);
static V L885(V *a);
static V S886(void);
static V W_P_dpat1_dk(V *a);
static V F_P_dpat_dsym(V a0);
static V L888(V *a);
static V L889(V *a);
static V L890(V *a);
static V S891(void);
static V L892(V *a);
static V L893(V *a);
static V S894(void);
static V L895(V *a);
static V S896(void);
static V L897(V *a);
static V S898(void);
static V W_P_dpat_dsym(V *a);
static V F_P_dplist(V a0);
static V S900(void);
static V S901(void);
static V W_P_dplist(V *a);
static V F_P_dpats(V a0);
static V L902(V *a);
static V W_P_dpats(V *a);
static V F_P_dpats_dgo(V a0, V a1, V a2);
static V W_P_dpats_dgo(V *a);
static V F_P_dpats_dclose(V a0, V a1);
static V L905(V *a);
static V W_P_dpats_dclose(V *a);
static V F_P_dpats_ditem(V a0);
static V L906(V *a);
static V S907(void);
static V L908(V *a);
static V L909(V *a);
static V W_P_dpats_ditem(V *a);
static V F_P_dpats_dmore(V a0, V a1);
static V L911(V *a);
static V W_P_dpats_dmore(V *a);
static V F_P_dptuple(V a0);
static V S913(void);
static V S914(void);
static V W_P_dptuple(V *a);
static V F_P_dpstr(V a0);
static V S916(void);
static V S917(void);
static V W_P_dpstr(V *a);
static V F_P_dpat_did(V a0, V a1);
static V L919(V *a);
static V S920(void);
static V L921(V *a);
static V W_P_dpat_did(V *a);
static V F_P_dscan(void);
static V L922(V *a);
static V W_P_dscan(V *a);
static V F_P_dscan_dret(V a0);
static V W_P_dscan_dret(V *a);
static V F_P_dscan_dgo(V a0, V a1);
static V S924(void);
static V S925(void);
static V S926(void);
static V S927(void);
static V S928(void);
static V S929(void);
static V S930(void);
static V S931(void);
static V W_P_dscan_dgo(V *a);
static V F_P_dscan_dend(V a0, V a1, V a2);
static V W_P_dscan_dend(V *a);
static V F_P_dscan_dsym(V a0, V a1, V a2);
static V W_P_dscan_dsym(V *a);
static V F_P_dscan_dtop(V a0, V a1, V a2, V a3);
static V W_P_dscan_dtop(V *a);
static V F_P_ddo(void);
static V L935(V *a);
static V L936(V *a);
static V S937(void);
static V L938(V *a);
static V L939(V *a);
static V S940(void);
static V L941(V *a);
static V L942(V *a);
static V L943(V *a);
static V W_P_ddo(V *a);
static V F_P_dlast(V a0);
static V S945(void);
static V W_P_dlast(V *a);
static V F_P_dinit(V a0);
static V W_P_dinit(V *a);
static V F_Fold_ddo(V a0, V a1, V a2, V a3);
static V S948(void);
static V S949(void);
static V S950(void);
static V S951(void);
static V S952(void);
static V S953(void);
static V S954(void);
static V S955(void);
static V S956(void);
static V W_Fold_ddo(V *a);
static V F_Fold_dapp(V a0, V a1, V a2, V a3);
static V S957(void);
static V W_Fold_dapp(V *a);
static V F_P_dmatch(void);
static V L958(V *a);
static V L959(V *a);
static V S960(void);
static V L961(V *a);
static V L962(V *a);
static V L963(V *a);
static V W_P_dmatch(V *a);
static V F_P_dmatch_dbody(V a0);
static V L965(V *a);
static V W_P_dmatch_dbody(V *a);
static V F_P_dcases(void);
static V L966(V *a);
static V L967(V *a);
static V W_P_dcases(V *a);
static V F_P_dcases_dde(V a0);
static V L969(V *a);
static V L970(V *a);
static V S971(void);
static V W_P_dcases_dde(V *a);
static V F_P_dcases_dgo(V a0);
static V L973(V *a);
static V S974(void);
static V L975(V *a);
static V S976(void);
static V L977(V *a);
static V L978(V *a);
static V L979(V *a);
static V W_P_dcases_dgo(V *a);
static V F_P_dbody(void);
static V L980(V *a);
static V L981(V *a);
static V W_P_dbody(V *a);
static V F_P_dscrs(void);
static V L982(V *a);
static V S983(void);
static V W_P_dscrs(V *a);
static V F_P_dscrs_dgo(V a0, V a1);
static V L985(V *a);
static V L986(V *a);
static V W_P_dscrs_dgo(V *a);
static V F_P_deff_dimports(void);
static V L987(V *a);
static V W_P_deff_dimports(V *a);
static V F_P_deff_dgo(V a0, V a1);
static V W_P_deff_dgo(V *a);
static V F_P_dret_dgo(V a0);
static V L990(V *a);
static V S991(void);
static V W_P_dret_dgo(V *a);
static V F_P_dparams(void);
static V L992(V *a);
static V S993(void);
static V W_P_dparams(V *a);
static V F_P_dparams_dgo(V a0);
static V L995(V *a);
static V L996(V *a);
static V S997(void);
static V L998(V *a);
static V L999(V *a);
static V W_P_dparams_dgo(V *a);
static V F_P_dparams_dmore(V a0);
static V S1001(void);
static V L1002(V *a);
static V W_P_dparams_dmore(V *a);
static V F_P_dfile_dfin(V a0);
static V W_P_dfile_dfin(V *a);
static V F_P_dfile_derr(V a0);
static V S1005(void);
static V W_P_dfile_derr(V *a);
static V F_Main_dparse_dfin(V a0);
static V W_Main_dparse_dfin(V *a);
static V F_String_dis__empty(V a0);
static V W_String_dis__empty(V *a);
static V F_Mod_ddir(V a0);
static V W_Mod_ddir(V *a);
static V F_Mod_ddir_dgo(V a0);
static V W_Mod_ddir_dgo(V *a);
static V F_Mod_ddir_dif(V a0, V a1, V a2);
static V W_Mod_ddir_dif(V *a);
static V F_Main_dresolve(V a0, V a1);
static V W_Main_dresolve(V *a);
static V F_Eff_ddecls(V a0, V a1);
static V W_Eff_ddecls(V *a);
static V F_Eff_ddecl(V a0, V a1);
static V W_Eff_ddecl(V *a);
static V F_Eff_dpaths(V a0, V a1);
static V W_Eff_dpaths(V *a);
static V F_Eff_dpath(V a0, V a1);
static V S1014(void);
static V W_Eff_dpath(V *a);
static V F_Main_dcompile(V a0, V a1);
static V S1017(void);
static V S1018(void);
static V W_Main_dcompile(V *a);
static V F_Gen_dprogram(V a0);
static V W_Gen_dprogram(V *a);
static V F_Gen_dprogram_dm(V a0);
static V S1020(void);
static V L1021(V *a);
static V S1022(void);
static V W_Gen_dprogram_dm(V *a);
static V F_G_dbody(V a0, V a1);
static V S1024(void);
static V S1025(void);
static V W_G_dbody(V *a);
static V F_G_dget(V a1, V a2, V a3);
static V W_G_dget(V *a);
static V F_Map_dget(V a1, V a2, V a3);
static V W_Map_dget(V *a);
static V F_Map_dget_dbit(V a1, V a2, V a3, V a4, V a5);
static V W_Map_dget_dbit(V *a);
static V F_Map_dhi(V a3, V a4, V a5);
static V W_Map_dhi(V *a);
static V F_Map_dlo(V a3, V a4, V a5);
static V W_Map_dlo(V *a);
static V F_Map_dget_dleaf(V a1, V a2, V a3);
static V W_Map_dget_dleaf(V *a);
static V F_Gen_dentry(V a0, V a1);
static V S1034(void);
static V S1035(void);
static V L1036(V *a);
static V S1037(void);
static V W_Gen_dentry(V *a);
static V F_Gen_dpure(V a1);
static V L1038(V *a);
static V W_Gen_dpure(V *a);
static V F_Gen_derror(V a0);
static V L1039(V *a);
static V W_Gen_derror(V *a);
static V F_Gen_derror_dgo(V a0, V a1);
static V W_Gen_derror_dgo(V *a);
static V F_Gen_dbind(V a2, V a3);
static V L1041(V *a);
static V W_Gen_dbind(V *a);
static V F_Gen_dgo(V a2, V a3);
static V W_Gen_dgo(V *a);
static V F_Ty_dhead(V a0);
static V S1044(void);
static V W_Ty_dhead(V *a);
static V F_Gen_dentry_dty(V a0, V a1, V a2);
static V S1046(void);
static V L1047(V *a);
static V S1048(void);
static V S1049(void);
static V W_Gen_dentry_dty(V *a);
static V F_Gen_dprinter(V a0, V a1);
static V L1051(V *a);
static V W_Gen_dprinter(V *a);
static V F_Gen_dprinter_dmemo(V a0, V a1, V a2, V a3);
static V L1053(V *a);
static V S1054(void);
static V L1055(V *a);
static V L1056(V *a);
static V S1057(void);
static V S1058(void);
static V L1059(V *a);
static V L1060(V *a);
static V S1061(void);
static V S1062(void);
static V S1063(void);
static V L1064(V *a);
static V W_Gen_dprinter_dmemo(V *a);
static V F_Doc_dlist(V a0);
static V W_Doc_dlist(V *a);
static V F_Gen_dcode(V a0);
static V L1066(V *a);
static V W_Gen_dcode(V *a);
static V F_Gen_dcode_dgo(V a0, V a1);
static V W_Gen_dcode_dgo(V *a);
static V F_Gen_dprinter_dbody(V a0, V a1, V a2);
static V S1068(void);
static V S1069(void);
static V S1070(void);
static V S1071(void);
static V S1072(void);
static V S1073(void);
static V S1074(void);
static V S1075(void);
static V W_Gen_dprinter_dbody(V *a);
static V F_Gen_dprinter_dhead(V a0, V a1, V a2);
static V S1077(void);
static V S1078(void);
static V S1079(void);
static V S1080(void);
static V S1081(void);
static V L1082(V *a);
static V S1083(void);
static V S1084(void);
static V S1085(void);
static V L1086(V *a);
static V S1087(void);
static V S1088(void);
static V S1089(void);
static V S1090(void);
static V W_Gen_dprinter_dhead(V *a);
static V F_Gen_dprinter_dadt(V a0, V a1, V a2);
static V L1092(V *a);
static V S1093(void);
static V S1094(void);
static V W_Gen_dprinter_dadt(V *a);
static V F_Ty_dargs(V a0);
static V W_Ty_dargs(V *a);
static V F_Ty_dbind(V a0, V a1);
static V W_Ty_dbind(V *a);
static V F_Ty_dbind_dgo(V a0, V a1);
static V W_Ty_dbind_dgo(V *a);
static V F_Gen_dprinter_dctors(V a0, V a1, V a2);
static V L1099(V *a);
static V L1100(V *a);
static V W_Gen_dprinter_dctors(V *a);
static V F_G_dctor(V a0, V a1);
static V W_G_dctor(V *a);
static V F_G_dopt__ctors(V a0);
static V W_G_dopt__ctors(V *a);
static V F_Gen_dprinter_dctor(V a0, V a1, V a2, V a3, V a4);
static V S1104(void);
static V S1105(void);
static V L1106(V *a);
static V S1107(void);
static V S1108(void);
static V S1109(void);
static V W_Gen_dprinter_dctor(V *a);
static V F_Gen_dprinter_dtest(V a0, V a1, V a2);
static V S1110(void);
static V S1111(void);
static V S1112(void);
static V S1113(void);
static V S1114(void);
static V W_Gen_dprinter_dtest(V *a);
static V F_Gen_dprinter_dfields(V a0, V a1, V a2, V a3, V a4);
static V L1116(V *a);
static V L1117(V *a);
static V S1118(void);
static V S1119(void);
static V S1120(void);
static V S1121(void);
static V S1122(void);
static V S1123(void);
static V S1124(void);
static V W_Gen_dprinter_dfields(V *a);
static V F_Ty_dsubst(V a0, V a1);
static V W_Ty_dsubst(V *a);
static V F_Ty_dsubsts(V a0, V a1);
static V W_Ty_dsubsts(V *a);
static V F_Ty_dfind(V a0, V a1);
static V W_Ty_dfind(V *a);
static V F_Ty_dfind_dif(V a0, V a1, V a2, V a3);
static V W_Ty_dfind_dif(V *a);
static V F_Maybe_ddefault(V a2, V a3);
static V W_Maybe_ddefault(V *a);
static V F_Ty_dtuple(V a0);
static V S1131(void);
static V W_Ty_dtuple(V *a);
static V F_Ty_dtuple_dgo(V a0, V a1, V a2);
static V W_Ty_dtuple_dgo(V *a);
static V F_Ty_dtuple_dargs(V a0, V a1);
static V W_Ty_dtuple_dargs(V *a);
static V F_Gen_dprinter_dtuple(V a0, V a1, V a2);
static V L1135(V *a);
static V S1136(void);
static V S1137(void);
static V L1138(V *a);
static V S1139(void);
static V S1140(void);
static V L1141(V *a);
static V S1142(void);
static V S1143(void);
static V W_Gen_dprinter_dtuple(V *a);
static V F_Gen_dproto(V a0);
static V L1144(V *a);
static V W_Gen_dproto(V *a);
static V F_Gen_dproto_dgo(V a0, V a1);
static V W_Gen_dproto_dgo(V *a);
static V F_Gen_dmemo_dadd(V a0);
static V L1146(V *a);
static V W_Gen_dmemo_dadd(V *a);
static V F_Gen_dmemo_dadd_dgo(V a0, V a1);
static V W_Gen_dmemo_dadd_dgo(V *a);
static V F_Gen_dfresh(void);
static V L1148(V *a);
static V W_Gen_dfresh(V *a);
static V F_Gen_dfresh_dgo(V a0);
static V W_Gen_dfresh_dgo(V *a);
static V F_Gen_dmemo_dfind(V a0);
static V L1150(V *a);
static V W_Gen_dmemo_dfind(V *a);
static V F_Gen_dmemo_dfind_dgo(V a0, V a1);
static V W_Gen_dmemo_dfind_dgo(V *a);
static V F_Env_dfind(V a0, V a1);
static V W_Env_dfind(V *a);
static V F_Env_dfind_dif(V a0, V a1, V a2, V a3);
static V W_Env_dfind_dif(V *a);
static V F_Expr_dshow(V a0);
static V S1155(void);
static V S1156(void);
static V S1157(void);
static V S1158(void);
static V S1159(void);
static V S1160(void);
static V S1161(void);
static V S1162(void);
static V S1163(void);
static V S1164(void);
static V S1165(void);
static V S1166(void);
static V S1167(void);
static V S1168(void);
static V S1169(void);
static V S1170(void);
static V S1171(void);
static V S1172(void);
static V S1173(void);
static V S1174(void);
static V S1175(void);
static V S1176(void);
static V S1177(void);
static V S1178(void);
static V S1179(void);
static V S1180(void);
static V S1181(void);
static V S1182(void);
static V S1183(void);
static V S1184(void);
static V S1185(void);
static V S1186(void);
static V S1187(void);
static V S1188(void);
static V W_Expr_dshow(V *a);
static V F_Pats_dshow(V a0);
static V S1190(void);
static V S1191(void);
static V W_Pats_dshow(V *a);
static V F_Pat_dshow(V a0);
static V S1193(void);
static V S1194(void);
static V S1195(void);
static V S1196(void);
static V W_Pat_dshow(V *a);
static V F_Exprs_dshow(V a0);
static V S1198(void);
static V S1199(void);
static V W_Exprs_dshow(V *a);
static V F_Set_dnew(void);
static V W_Set_dnew(V *a);
static V F_Map_dnew(void);
static V W_Map_dnew(V *a);
static V F_Gen_dall(V a0, V a1, V a2);
static V W_Gen_dall(V *a);
static V F_Set_dhas(V a0, V a1);
static V W_Set_dhas(V *a);
static V F_Map_dhas(V a2, V a3);
static V W_Map_dhas(V *a);
static V F_Map_dhas_dbit(V a2, V a3, V a4, V a5);
static V W_Map_dhas_dbit(V *a);
static V F_Map_dhas_dleaf(V a2, V a3);
static V W_Map_dhas_dleaf(V *a);
static V F_Gen_dall_dseen(V a0, V a1, V a2, V a3);
static V W_Gen_dall_dseen(V *a);
static V F_Gen_dall_dgo(V a0, V a1, V a2, V a3, V a4);
static V L1207(V *a);
static V L1208(V *a);
static V W_Gen_dall_dgo(V *a);
static V F_Set_dadd(V a0, V a1);
static V W_Set_dadd(V *a);
static V F_Map_dset(V a2, V a3, V a4);
static V W_Map_dset(V *a);
static V F_Map_dseek(V a2, V a3);
static V W_Map_dseek(V *a);
static V F_Map_dseek_dbit(V a2, V a3, V a4, V a5);
static V W_Map_dseek_dbit(V *a);
static V F_Map_dset_dgo(V a2, V a3);
static V W_Map_dset_dgo(V *a);
static V F_Map_dset_dfin(V a2, V a3, V a4, V a5, V a6);
static V W_Map_dset_dfin(V *a);
static V F_Map_dset_dfin_dgo(V a2, V a3, V a4, V a5);
static V W_Map_dset_dfin_dgo(V *a);
static V F_Map_ddiff(V a0, V a1);
static V W_Map_ddiff(V *a);
static V F_Map_ddiff_dstep(V a0, V a1);
static V W_Map_ddiff_dstep(V *a);
static V W_U32_dxor(V *a);
static V F_Map_ddiff_dchr(V a0);
static V W_Map_ddiff_dchr(V *a);
static V F_Map_dmsb_du(V a0, V a1);
static V W_Map_dmsb_du(V *a);
static V F_Map_dmsb_du_dif(V a0, V a1, V a2);
static V W_Map_dmsb_du_dif(V *a);
static V W_U32_dshr(V *a);
static V F_Map_ddiff_dfin(V a0, V a1, V a2);
static V W_Map_ddiff_dfin(V *a);
static V F_Map_dins(V a2, V a3, V a4, V a5);
static V W_Map_dins(V *a);
static V F_Map_dins_dif(V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V W_Map_dins_dif(V *a);
static V F_Map_dins_ddeep(V a2, V a3, V a4, V a5, V a6, V a7);
static V W_Map_dins_ddeep(V *a);
static V F_Map_dins_dsplice(V a2, V a3, V a4, V a5);
static V W_Map_dins_dsplice(V *a);
static V F_Map_dins_dsplice_dbit(V a2, V a3, V a4, V a5);
static V W_Map_dins_dsplice_dbit(V *a);
static V F_Map_dput(V a2, V a3, V a4);
static V W_Map_dput(V *a);
static V F_Map_dput_dbit(V a2, V a3, V a4, V a5, V a6);
static V W_Map_dput_dbit(V *a);
static V F_Gen_dtake__refs(void);
static V L1234(V *a);
static V W_Gen_dtake__refs(V *a);
static V F_Gen_dtake__refs_dgo(V a0);
static V W_Gen_dtake__refs_dgo(V *a);
static V F_Gen_ddef(V a0, V a1);
static V W_Gen_ddef(V *a);
static V F_G_ddef(V a0, V a1);
static V W_G_ddef(V *a);
static V F_Gen_ddef_ddecl(V a0, V a1, V a2, V a3);
static V W_Gen_ddef_ddecl(V *a);
static V F_Gen_ddef_dlaw(V a0, V a1, V a2);
static V W_Gen_ddef_dlaw(V *a);
static V F_Gen_ddummy__params(V a0);
static V S1241(void);
static V S1242(void);
static V W_Gen_ddummy__params(V *a);
static V F_Gen_dsig(V a0, V a1, V a2, V a3);
static V S1247(void);
static V S1248(void);
static V S1249(void);
static V S1251(void);
static V W_Gen_dsig(V *a);
static V F_Sig_dwargs(V a0);
static V W_Sig_dwargs(V *a);
static V F_Gen_dwrapper(V a0, V a1);
static V S1254(void);
static V S1255(void);
static V L1256(V *a);
static V S1257(void);
static V S1258(void);
static V S1259(void);
static V S1260(void);
static V S1261(void);
static V W_Gen_dwrapper(V *a);
static V F_Gen_df(V a0);
static V S1262(void);
static V W_Gen_df(V *a);
static V F_Gen_dmangle(V a0);
static V S1264(void);
static V W_Gen_dmangle(V *a);
static V F_Gen_dmangle_dchr(V a0);
static V S1265(void);
static V S1266(void);
static V S1267(void);
static V W_Gen_dmangle_dchr(V *a);
static V F_Str_dchr(V a0);
static V W_Str_dchr(V *a);
static V F_Gen_dw(V a0);
static V S1268(void);
static V W_Gen_dw(V *a);
static V F_Gen_ddef_deff(V a0, V a1, V a2);
static V S1272(void);
static V S1274(void);
static V S1275(void);
static V S1276(void);
static V L1277(V *a);
static V S1278(void);
static V S1279(void);
static V L1280(V *a);
static V S1281(void);
static V S1282(void);
static V S1283(void);
static V S1284(void);
static V S1285(void);
static V S1286(void);
static V S1287(void);
static V S1288(void);
static V L1289(V *a);
static V S1290(void);
static V S1291(void);
static V S1292(void);
static V S1293(void);
static V S1294(void);
static V S1295(void);
static V S1296(void);
static V S1297(void);
static V S1298(void);
static V L1299(V *a);
static V W_Gen_ddef_deff(V *a);
static V F_Gen_deff_dargs(V a0, V a1);
static V S1301(void);
static V S1302(void);
static V W_Gen_deff_dargs(V *a);
static V F_Gen_dcid(V a0);
static V S1303(void);
static V W_Gen_dcid(V *a);
static V F_String_dto__upper(V a0);
static V W_String_dto__upper(V *a);
static V F_Char_dto__upper(V a0);
static V W_Char_dto__upper(V *a);
static V F_Bool_dto__u32(V a0);
static V W_Bool_dto__u32(V *a);
static V F_Gen_dhost(V a0);
static V S1307(void);
static V W_Gen_dhost(V *a);
static V F_Gen_dhost_dchr(V a0);
static V S1308(void);
static V W_Gen_dhost_dchr(V *a);
static V F_Gen_deffs(V a0);
static V L1309(V *a);
static V W_Gen_deffs(V *a);
static V F_Gen_deffs_dgo(V a0, V a1);
static V W_Gen_deffs_dgo(V *a);
static V F_Gen_deffs_dc(V a0);
static V S1312(void);
static V W_Gen_deffs_dc(V *a);
static V F_String_dends__with(V a0, V a1);
static V W_String_dends__with(V *a);
static V F_Gen_deffs_dc_dif(V a0, V a1, V a2);
static V W_Gen_deffs_dc_dif(V *a);
static V F_Gen_dcparams(V a0);
static V S1315(void);
static V S1316(void);
static V W_Gen_dcparams(V *a);
static V F_Gen_dcparams_dgo(V a0);
static V S1318(void);
static V W_Gen_dcparams_dgo(V *a);
static V F_Gen_ddef_dnative(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Gen_ddef_dnative(V *a);
static V F_Gen_ddef_dbody(V a0, V a1, V a2, V a3, V a4);
static V S1322(void);
static V S1323(void);
static V S1324(void);
static V S1325(void);
static V L1326(V *a);
static V S1327(void);
static V L1328(V *a);
static V S1329(void);
static V S1330(void);
static V L1331(V *a);
static V W_Gen_ddef_dbody(V *a);
static V F_R_dops(V a0, V a1);
static V S1333(void);
static V W_R_dops(V *a);
static V F_R_dopss(V a0, V a1);
static V W_R_dopss(V *a);
static V F_R_dopname(V a0);
static V S1335(void);
static V S1336(void);
static V S1337(void);
static V S1338(void);
static V S1339(void);
static V S1340(void);
static V S1341(void);
static V S1342(void);
static V S1343(void);
static V S1344(void);
static V S1345(void);
static V S1346(void);
static V S1347(void);
static V S1348(void);
static V W_R_dopname(V *a);
static V F_R_dopname_dgo(V a0);
static V S1350(void);
static V S1351(void);
static V S1352(void);
static V S1353(void);
static V S1354(void);
static V S1355(void);
static V S1356(void);
static V S1357(void);
static V S1358(void);
static V S1359(void);
static V S1360(void);
static V S1361(void);
static V S1362(void);
static V S1363(void);
static V S1364(void);
static V W_R_dopname_dgo(V *a);
static V F_Gen_dstmt(V a0, V a1, V a2, V a3, V a4);
static V L1366(V *a);
static V W_Gen_dstmt(V *a);
static V F_Gen_dret(V a0, V a1);
static V S1368(void);
static V S1369(void);
static V S1370(void);
static V S1371(void);
static V W_Gen_dret(V *a);
static V F_Gen_dexpr(V a0, V a1, V a2);
static V S1373(void);
static V S1374(void);
static V S1375(void);
static V S1376(void);
static V L1377(V *a);
static V S1378(void);
static V S1379(void);
static V S1380(void);
static V S1381(void);
static V S1382(void);
static V L1383(V *a);
static V S1384(void);
static V S1385(void);
static V L1386(V *a);
static V S1387(void);
static V W_Gen_dexpr(V *a);
static V F_Gen_dblock(V a0, V a1, V a2);
static V L1388(V *a);
static V S1389(void);
static V L1390(V *a);
static V L1391(V *a);
static V S1392(void);
static V S1393(void);
static V S1394(void);
static V W_Gen_dblock(V *a);
static V F_Self_dnone(void);
static V S1395(void);
static V W_Self_dnone(V *a);
static V F_Gen_dlam(V a0, V a1, V a2, V a3);
static V L1398(V *a);
static V S1399(void);
static V L1400(V *a);
static V S1401(void);
static V S1402(void);
static V L1403(V *a);
static V S1404(void);
static V S1405(void);
static V L1406(V *a);
static V L1407(V *a);
static V S1408(void);
static V S1409(void);
static V S1410(void);
static V L1411(V *a);
static V S1412(void);
static V S1413(void);
static V S1414(void);
static V S1415(void);
static V S1416(void);
static V W_Gen_dlam(V *a);
static V F_Gen_dcaps_douter(V a0);
static V W_Gen_dcaps_douter(V *a);
static V F_Gen_darr(V a0);
static V S1419(void);
static V S1420(void);
static V S1421(void);
static V W_Gen_darr(V *a);
static V F_Gen_dcommas(V a0);
static V S1422(void);
static V W_Gen_dcommas(V *a);
static V F_Doc_dsep(V a0, V a1);
static V W_Doc_dsep(V *a);
static V F_Doc_dsep_dgo(V a0, V a1);
static V W_Doc_dsep_dgo(V *a);
static V F_Gen_dcaps_dinner(V a0, V a1);
static V S1426(void);
static V S1427(void);
static V W_Gen_dcaps_dinner(V *a);
static V F_Gen_dpat(V a0, V a1, V a2, V a3);
static V S1429(void);
static V S1430(void);
static V S1431(void);
static V S1432(void);
static V S1433(void);
static V S1434(void);
static V S1435(void);
static V S1436(void);
static V S1437(void);
static V S1438(void);
static V W_Gen_dpat(V *a);
static V F_Gen_dpat_dcond(V a0, V a1);
static V W_Gen_dpat_dcond(V *a);
static V F_Gen_dpat_dctor(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1441(void);
static V S1442(void);
static V W_Gen_dpat_dctor(V *a);
static V F_Gen_dpat_dkind(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S1444(void);
static V S1445(void);
static V S1446(void);
static V S1447(void);
static V S1448(void);
static V S1449(void);
static V S1450(void);
static V S1451(void);
static V S1452(void);
static V S1453(void);
static V S1454(void);
static V W_Gen_dpat_dkind(V *a);
static V F_Gen_dpat_dfields(V a0, V a1, V a2, V a3, V a4);
static V S1456(void);
static V S1457(void);
static V S1458(void);
static V W_Gen_dpat_dfields(V *a);
static V F_Gen_dpat_dtag(V a0, V a1, V a2);
static V W_Gen_dpat_dtag(V *a);
static V F_Gen_dpat_dvar(V a0, V a1, V a2);
static V S1461(void);
static V W_Gen_dpat_dvar(V *a);
static V F_PatR_dbinds(V a0);
static V W_PatR_dbinds(V *a);
static V F_Pat_dvars(V a0, V a1);
static V W_Pat_dvars(V *a);
static V F_Pats_dvars(V a0, V a1);
static V W_Pats_dvars(V *a);
static V F_FV_dexpr(V a0, V a1, V a2);
static V W_FV_dexpr(V *a);
static V F_FV_dexprs(V a0, V a1, V a2);
static V W_FV_dexprs(V *a);
static V F_FV_dvar(V a0, V a1, V a2);
static V W_FV_dvar(V *a);
static V F_Str_dhas(V a0, V a1);
static V W_Str_dhas(V *a);
static V F_Gen_dcaps(V a0, V a1);
static V W_Gen_dcaps(V *a);
static V F_Gen_dcaps_dput(V a0, V a1, V a2);
static V W_Gen_dcaps_dput(V *a);
static V F_Gen_dctor(V a0, V a1, V a2, V a3);
static V W_Gen_dctor(V *a);
static V F_Gen_dctor_dinfo(V a0, V a1, V a2, V a3, V a4);
static V S1470(void);
static V L1471(V *a);
static V S1472(void);
static V L1473(V *a);
static V W_Gen_dctor_dinfo(V *a);
static V F_Gen_dctor_dkind(V a0, V a1, V a2);
static V S1475(void);
static V S1476(void);
static V S1477(void);
static V S1478(void);
static V S1479(void);
static V W_Gen_dctor_dkind(V *a);
static V F_Gen_dctor_dnode(V a0, V a1);
static V S1481(void);
static V S1482(void);
static V S1483(void);
static V S1484(void);
static V S1485(void);
static V S1486(void);
static V S1487(void);
static V S1488(void);
static V W_Gen_dctor_dnode(V *a);
static V F_Gen_dlen(V a0);
static V W_Gen_dlen(V *a);
static V F_Gen_dexprs(V a0, V a1, V a2);
static V L1490(V *a);
static V L1491(V *a);
static V W_Gen_dexprs(V *a);
static V F_Gen_dcall(V a0, V a1, V a2, V a3);
static V W_Gen_dcall(V *a);
static V F_Gen_dcall_dlocal(V a0, V a1, V a2, V a3);
static V L1493(V *a);
static V L1494(V *a);
static V W_Gen_dcall_dlocal(V *a);
static V F_Gen_dapply(V a0, V a1);
static V S1496(void);
static V S1497(void);
static V S1498(void);
static V W_Gen_dapply(V *a);
static V F_Env_dhas(V a0, V a1);
static V W_Env_dhas(V *a);
static V F_Maybe_dis__some(V a2);
static V W_Maybe_dis__some(V *a);
static V F_Gen_dcall_dvar(V a0, V a1, V a2, V a3, V a4);
static V W_Gen_dcall_dvar(V *a);
static V F_Gen_dcall_ddef(V a0, V a1, V a2, V a3, V a4);
static V W_Gen_dcall_ddef(V *a);
static V F_Gen_dsplit(V a0, V a1, V a2);
static V S1508(void);
static V W_Gen_dsplit(V *a);
static V F_Gen_dcall_dkind(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1510(void);
static V S1511(void);
static V L1512(V *a);
static V S1513(void);
static V L1514(V *a);
static V W_Gen_dcall_dkind(V *a);
static V F_Gen_dcall_dsplit(V a0, V a1, V a2, V a3, V a4);
static V W_Gen_dcall_dsplit(V *a);
static V F_Gen_dcall_dfull(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L1517(V *a);
static V L1518(V *a);
static V S1519(void);
static V S1520(void);
static V L1521(V *a);
static V S1522(void);
static V S1523(void);
static V S1524(void);
static V S1525(void);
static V S1526(void);
static V W_Gen_dcall_dfull(V *a);
static V F_Gen_dref(V a0);
static V L1527(V *a);
static V W_Gen_dref(V *a);
static V F_Gen_dref_dgo(V a0, V a1);
static V W_Gen_dref_dgo(V *a);
static V F_Gen_dstr(V a0);
static V L1529(V *a);
static V S1530(void);
static V L1531(V *a);
static V S1532(void);
static V S1533(void);
static V L1534(V *a);
static V S1535(void);
static V S1536(void);
static V S1537(void);
static V L1538(V *a);
static V S1539(void);
static V W_Gen_dstr(V *a);
static V F_Gen_dlit(V a0);
static V S1541(void);
static V W_Gen_dlit(V *a);
static V F_Gen_dlit__chr(V a0);
static V S1542(void);
static V S1543(void);
static V S1544(void);
static V W_Gen_dlit__chr(V *a);
static V F_Gen_dutf8(V a0);
static V W_Gen_dutf8(V *a);
static V W_U32_dor(V *a);
static V F_Gen_doct(V a0);
static V S1545(void);
static V W_Gen_doct(V *a);
static V F_Gen_dvar(V a0, V a1, V a2);
static V W_Gen_dvar(V *a);
static V F_Gen_dvar_dfound(V a0, V a1, V a2);
static V S1547(void);
static V W_Gen_dvar_dfound(V *a);
static V F_Gen_dvar_dglobal(V a0, V a1, V a2);
static V S1549(void);
static V W_Gen_dvar_dglobal(V *a);
static V F_Gen_dvar_ddef(V a0, V a1);
static V W_Gen_dvar_ddef(V *a);
static V F_Gen_dvar_dkind(V a0, V a1, V a2);
static V S1552(void);
static V S1553(void);
static V L1554(V *a);
static V S1555(void);
static V L1556(V *a);
static V S1557(void);
static V S1558(void);
static V S1559(void);
static V S1560(void);
static V W_Gen_dvar_dkind(V *a);
static V F_Gen_dis__tail(V a0, V a1, V a2, V a3, V a4);
static V W_Gen_dis__tail(V *a);
static V W_Nat_dis__eq(V *a);
static V F_Gen_dis__ret(V a0);
static V W_Gen_dis__ret(V *a);
static V F_Gen_dstmt_dcall(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L1564(V *a);
static V W_Gen_dstmt_dcall(V *a);
static V F_Gen_dtail_dself(V a0, V a1, V a2, V a3);
static V W_Gen_dtail_dself(V *a);
static V F_Gen_dtail(V a0, V a1, V a2, V a3);
static V L1567(V *a);
static V S1568(void);
static V S1569(void);
static V W_Gen_dtail(V *a);
static V F_Gen_dtail_dassign(V a0, V a1);
static V S1571(void);
static V S1572(void);
static V W_Gen_dtail_dassign(V *a);
static V F_Gen_dtail_dtemps(V a0, V a1);
static V S1574(void);
static V S1575(void);
static V S1576(void);
static V W_Gen_dtail_dtemps(V *a);
static V F_Gen_dmatch(V a0, V a1, V a2, V a3, V a4, V a5);
static V L1577(V *a);
static V W_Gen_dmatch(V *a);
static V F_Gen_dmatch_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V L1579(V *a);
static V W_Gen_dmatch_dgo(V *a);
static V F_Gen_dcases(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1581(void);
static V L1585(V *a);
static V W_Gen_dcases(V *a);
static V F_Gen_dcases_dnext(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V S1587(void);
static V S1588(void);
static V L1589(V *a);
static V S1590(void);
static V S1591(void);
static V S1592(void);
static V W_Gen_dcases_dnext(V *a);
static V F_Gen_dand(V a0);
static V S1594(void);
static V S1595(void);
static V W_Gen_dand(V *a);
static V F_PatR_dconds(V a0);
static V W_PatR_dconds(V *a);
static V F_Gen_dpats(V a0, V a1, V a2, V a3);
static V W_Gen_dpats(V *a);
static V F_Gen_dscrs(V a0, V a1, V a2);
static V L1600(V *a);
static V S1601(void);
static V L1602(V *a);
static V L1603(V *a);
static V L1604(V *a);
static V W_Gen_dscrs(V *a);
static V F_Gen_dscrs_dput(V a0, V a1, V a2);
static V S1606(void);
static V S1607(void);
static V S1608(void);
static V W_Gen_dscrs_dput(V *a);
static V F_Gen_dlet(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S1610(void);
static V S1611(void);
static V W_Gen_dlet(V *a);
static V F_Gen_dlet_dpat(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L1612(V *a);
static V S1613(void);
static V L1614(V *a);
static V L1615(V *a);
static V L1616(V *a);
static V L1617(V *a);
static V S1618(void);
static V S1619(void);
static V S1620(void);
static V W_Gen_dlet_dpat(V *a);
static V F_Gen_dlet_dctor(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V W_Gen_dlet_dctor(V *a);
static V F_Gen_dlet_dpar(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Gen_dlet_dpar(V *a);
static V F_Gen_dpar(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L1623(V *a);
static V L1624(V *a);
static V L1625(V *a);
static V W_Gen_dpar(V *a);
static V F_Gen_dpar_denv(V a0, V a1, V a2, V a3);
static V S1627(void);
static V W_Gen_dpar_denv(V *a);
static V F_Gen_dpar_dname(V a0, V a1);
static V S1628(void);
static V S1629(void);
static V W_Gen_dpar_dname(V *a);
static V F_Gen_dpar_dvals(V a0, V a1, V a2, V a3, V a4);
static V L1631(V *a);
static V S1632(void);
static V S1633(void);
static V S1634(void);
static V S1635(void);
static V L1636(V *a);
static V L1637(V *a);
static V S1638(void);
static V S1639(void);
static V S1640(void);
static V S1641(void);
static V S1642(void);
static V S1643(void);
static V W_Gen_dpar_dvals(V *a);
static V F_Gen_dlet_dvar(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L1645(V *a);
static V L1646(V *a);
static V S1647(void);
static V S1648(void);
static V L1649(V *a);
static V S1650(void);
static V L1651(V *a);
static V L1652(V *a);
static V L1653(V *a);
static V S1654(void);
static V S1655(void);
static V S1656(void);
static V W_Gen_dlet_dvar(V *a);
static V F_Gen_dcids(V a0, V a1, V a2);
static V S1658(void);
static V S1659(void);
static V S1660(void);
static V S1661(void);
static V W_Gen_dcids(V *a);
static V F_Gen_dcids_dctors(V a0, V a1);
static V S1663(void);
static V W_Gen_dcids_dctors(V *a);
static V F_Gen_dcids_dkind(V a0, V a1);
static V S1665(void);
static V W_Gen_dcids_dkind(V *a);
static V F_Gen_dcids_dline(V a0, V a1, V a2);
static V S1667(void);
static V S1668(void);
static V S1669(void);
static V S1670(void);
static V S1671(void);
static V S1672(void);
static V S1673(void);
static V S1674(void);
static V S1675(void);
static V S1676(void);
static V W_Gen_dcids_dline(V *a);
static V F_Gen_dprogram_dfin(V a0, V a1);
static V S1679(void);
static V S1680(void);
static V S1681(void);
static V W_Gen_dprogram_dfin(V *a);
static V F_Doc_dflat(V a0);
static V W_Doc_dflat(V *a);
static V F_Doc_dgo(V a0, V a1);
static V W_Doc_dgo(V *a);
static V F_Gen_ddedup(V a0, V a1);
static V W_Gen_ddedup(V *a);
static V F_G_dnew(V a0);
static V W_G_dnew(V *a);
static V F_G_dlaws(V a0, V a1);
static V W_G_dlaws(V *a);
static V F_G_dbuild(V a0, V a1, V a2);
static V W_G_dbuild(V *a);
static V F_G_dadd(V a0, V a1, V a2);
static V W_G_dadd(V *a);
static V F_G_dadd_deff(V a0, V a1, V a2, V a3);
static V W_G_dadd_deff(V *a);
static V F_G_dmask(V a0);
static V W_G_dmask(V *a);
static V F_G_dkeep(V a0);
static V W_G_dkeep(V *a);
static V F_G_derased__ty(V a0);
static V S1690(void);
static V S1691(void);
static V S1692(void);
static V S1693(void);
static V W_G_derased__ty(V *a);
static V F_G_dadd_ddef(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_G_dadd_ddef(V *a);
static V F_G_dparams(V a0, V a1, V a2);
static V W_G_dparams(V *a);
static V F_G_dparams_dgo(V a0, V a1);
static V W_G_dparams_dgo(V *a);
static V F_G_dis__native(V a0);
static V W_G_dis__native(V *a);
static V F_Natives(void);
static V S1696(void);
static V S1697(void);
static V S1698(void);
static V S1699(void);
static V S1700(void);
static V S1701(void);
static V S1702(void);
static V S1703(void);
static V S1704(void);
static V S1705(void);
static V S1706(void);
static V S1707(void);
static V S1708(void);
static V S1709(void);
static V S1710(void);
static V S1711(void);
static V S1712(void);
static V S1713(void);
static V S1714(void);
static V S1715(void);
static V S1716(void);
static V S1717(void);
static V S1718(void);
static V S1719(void);
static V S1720(void);
static V S1721(void);
static V S1722(void);
static V S1723(void);
static V S1724(void);
static V S1725(void);
static V S1726(void);
static V S1727(void);
static V S1728(void);
static V S1729(void);
static V S1730(void);
static V S1731(void);
static V S1732(void);
static V S1733(void);
static V S1734(void);
static V S1735(void);
static V S1736(void);
static V S1737(void);
static V S1738(void);
static V S1739(void);
static V S1740(void);
static V S1741(void);
static V S1742(void);
static V S1743(void);
static V S1744(void);
static V S1745(void);
static V S1746(void);
static V S1747(void);
static V S1748(void);
static V S1749(void);
static V S1750(void);
static V S1751(void);
static V S1752(void);
static V S1753(void);
static V S1754(void);
static V S1755(void);
static V S1756(void);
static V S1757(void);
static V S1758(void);
static V S1759(void);
static V S1760(void);
static V S1761(void);
static V S1762(void);
static V S1763(void);
static V S1764(void);
static V S1765(void);
static V S1766(void);
static V S1767(void);
static V S1768(void);
static V S1769(void);
static V S1770(void);
static V S1771(void);
static V S1772(void);
static V S1773(void);
static V S1774(void);
static V S1775(void);
static V S1776(void);
static V S1777(void);
static V S1778(void);
static V S1779(void);
static V W_Natives(V *a);
static V F_G_dadd_dlaw(V a0, V a1, V a2);
static V W_G_dadd_dlaw(V *a);
static V F_G_dadd_dtype(V a0, V a1, V a2, V a3);
static V S1783(void);
static V W_G_dadd_dtype(V *a);
static V F_G_dctors(V a0, V a1, V a2, V a3, V a4);
static V W_G_dctors(V *a);
static V F_G_dctor__kind(V a0, V a1, V a2, V a3);
static V S1786(void);
static V S1787(void);
static V W_G_dctor__kind(V *a);
static V F_Main_demit(V a0);
static V S1790(void);
static V L1791(V *a);
static V S1792(void);
static V W_Main_demit(V *a);
static V F_IO_dprint__err(V a0);
static V E_IO_dprint__err(V *a);
static V W_IO_dprint__err(V *a);
static V F_IO_dbind(V a2, V a3);
static V L1793(V *a);
static V L1794(V *a);
static V L1795(V *a);
static V W_IO_dbind(V *a);
static V F_Main_demit_dok(V a0, V a1, V a2);
static V S1796(void);
static V L1797(V *a);
static V W_Main_demit_dok(V *a);
static V F_IO_dwrite(V a0);
static V E_IO_dwrite(V *a);
static V W_IO_dwrite(V *a);
static V F_Main_deffs(V a0, V a1);
static V L1799(V *a);
static V S1800(void);
static V W_Main_deffs(V *a);
static V F_IO_dread__file(V a0);
static V S1801(void);
static V L1802(V *a);
static V L1803(V *a);
static V W_IO_dread__file(V *a);
static V F_IO_dread__fin(V a0);
static V L1805(V *a);
static V W_IO_dread__fin(V *a);
static V F_IO_dpass(V a1);
static V W_IO_dpass(V *a);
static V F_IO_dpure(V a1);
static V L1807(V *a);
static V L1808(V *a);
static V W_IO_dpure(V *a);
static V F_File_dclose(V a0);
static V E_File_dclose(V *a);
static V W_File_dclose(V *a);
static V F_IO_dread__all(V a0);
static V L1809(V *a);
static V W_IO_dread__all(V *a);
static V F_IO_dread__sized(V a0);
static V W_IO_dread__sized(V *a);
static V F_File_dread(V a0, V a1);
static V E_File_dread(V *a);
static V W_File_dread(V *a);
static V F_File_dsize(V a0);
static V E_File_dsize(V *a);
static V W_File_dsize(V *a);
static V F_File_dopen(V a0, V a1);
static V E_File_dopen(V *a);
static V W_File_dopen(V *a);
static V F_IO_dtry(V a1);
static V W_IO_dtry(V *a);
static V F_Main_dload(V a0, V a1);
static V S1813(void);
static V L1814(V *a);
static V W_Main_dload(V *a);
static V F_Main_dload_dparsed(V a0, V a1, V a2, V a3);
static V S1816(void);
static V S1817(void);
static V L1818(V *a);
static V W_Main_dload_dparsed(V *a);
static V F_Main_dimports(V a0, V a1, V a2);
static V S1820(void);
static V W_Main_dimports(V *a);
static V F_Main_dimports_done(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1822(void);
static V L1823(V *a);
static V L1824(V *a);
static V W_Main_dimports_done(V *a);
static V F_Mod_dqualify(V a0, V a1);
static V W_Mod_dqualify(V *a);
static V F_Mod_dnames(V a0, V a1);
static V W_Mod_dnames(V *a);
static V F_Mod_dctor__names(V a0, V a1);
static V W_Mod_dctor__names(V *a);
static V F_Mod_ddecls(V a0, V a1);
static V W_Mod_ddecls(V *a);
static V F_Mod_ddecl(V a0, V a1);
static V W_Mod_ddecl(V *a);
static V F_Mod_dctors(V a0, V a1);
static V W_Mod_dctors(V *a);
static V F_Mod_dfields(V a0, V a1);
static V W_Mod_dfields(V *a);
static V F_Mod_dexpr(V a0, V a1, V a2);
static V W_Mod_dexpr(V *a);
static V F_Mod_dexprs(V a0, V a1, V a2);
static V W_Mod_dexprs(V *a);
static V F_Mod_dvar(V a0, V a1, V a2);
static V W_Mod_dvar(V *a);
static V F_Mod_dq(V a0, V a1);
static V S1834(void);
static V W_Mod_dq(V *a);
static V F_Mod_dpats(V a0, V a1);
static V W_Mod_dpats(V *a);
static V F_Mod_dpat(V a0, V a1);
static V W_Mod_dpat(V *a);
static V F_Mod_dparam__names(V a0);
static V W_Mod_dparam__names(V *a);
static V F_Main_dload_dimport(V a0, V a1, V a2, V a3);
static V W_Main_dload_dimport(V *a);
static V F_Main_dload_dhub(V a0, V a1);
static V L1839(V *a);
static V S1840(void);
static V L1841(V *a);
static V L1842(V *a);
static V S1843(void);
static V W_Main_dload_dhub(V *a);
static V F_Main_dhub_durl(V a0);
static V S1845(void);
static V W_Main_dhub_durl(V *a);
static V F_Hub_densure(V a0, V a1, V a2);
static V E_Hub_densure(V *a);
static V W_Hub_densure(V *a);
static V F_IO_dget__env(V a0);
static V E_IO_dget__env(V *a);
static V W_IO_dget__env(V *a);
static V F_Main_dlib(void);
static V S1846(void);
static V L1847(V *a);
static V W_Main_dlib(V *a);
static V F_Main_dlib_dor(V a0);
static V S1849(void);
static V L1850(V *a);
static V S1851(void);
static V W_Main_dlib_dor(V *a);
static V F_Chk_dshow__main(V a0);
static V W_Chk_dshow__main(V *a);
static V F_Chk_dshow__main_dgo(V a0, V a1);
static V S1853(void);
static V W_Chk_dshow__main_dgo(V *a);
static V F_Chk_dterm__show(V a0, V a1, V a2);
static V W_Chk_dterm__show(V *a);
static V F_Chk_dterm__show_dgo(V a0, V a1, V a2, V a3);
static V S1855(void);
static V S1856(void);
static V S1857(void);
static V S1858(void);
static V S1862(void);
static V S1863(void);
static V S1864(void);
static V S1865(void);
static V S1866(void);
static V S1867(void);
static V S1868(void);
static V S1869(void);
static V S1870(void);
static V S1871(void);
static V S1874(void);
static V S1875(void);
static V S1876(void);
static V S1877(void);
static V S1878(void);
static V S1879(void);
static V S1880(void);
static V S1881(void);
static V S1882(void);
static V S1883(void);
static V S1884(void);
static V S1885(void);
static V S1886(void);
static V S1887(void);
static V S1888(void);
static V S1889(void);
static V S1890(void);
static V S1891(void);
static V S1892(void);
static V S1893(void);
static V S1894(void);
static V W_Chk_dterm__show_dgo(V *a);
static V F_Chk_dshow_drwt(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dshow_drwt(V *a);
static V F_Chk_dshow_drwt_dgo(V a0, V a1, V a2, V a3, V a4);
static V S1896(void);
static V S1897(void);
static V S1898(void);
static V W_Chk_dshow_drwt_dgo(V *a);
static V F_Chk_dshow_drwt_dinner(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S1900(void);
static V S1901(void);
static V S1902(void);
static V S1903(void);
static V S1904(void);
static V S1905(void);
static V S1906(void);
static V S1907(void);
static V W_Chk_dshow_drwt_dinner(V *a);
static V F_Chk_dshow_dparen(V a0, V a1);
static V S1909(void);
static V S1910(void);
static V W_Chk_dshow_dparen(V *a);
static V F_Chk_dshow_darms(V a0, V a1, V a2);
static V S1912(void);
static V W_Chk_dshow_darms(V *a);
static V F_Chk_dshow_djoin(V a0, V a1);
static V W_Chk_dshow_djoin(V *a);
static V F_Chk_dshow_dctr(V a0, V a1, V a2, V a3);
static V S1913(void);
static V W_Chk_dshow_dctr(V *a);
static V F_Chk_du32__from__term(V a0, V a1);
static V W_Chk_du32__from__term(V *a);
static V F_Chk_du32__from__term_dgo(V a0, V a1);
static V W_Chk_du32__from__term_dgo(V *a);
static V F_Chk_du32__from__term_dif(V a0, V a1);
static V W_Chk_du32__from__term_dif(V *a);
static V F_Chk_du32__bits(V a0, V a1, V a2);
static V W_Chk_du32__bits(V *a);
static V F_Chk_du32__bits_dbit(V a0, V a1, V a2, V a3);
static V W_Chk_du32__bits_dbit(V *a);
static V F_Chk_du32__bits_dnext(V a0, V a1, V a2);
static V W_Chk_du32__bits_dnext(V *a);
static V W_U32_dshln(V *a);
static V F_Chk_dshow_dctr_du32(V a0, V a1, V a2, V a3, V a4);
static V S1919(void);
static V W_Chk_dshow_dctr_du32(V *a);
static V F_Chk_dshow_dctr_df32(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dshow_dctr_df32(V *a);
static V F_Chk_dnat__from__term(V a0);
static V W_Chk_dnat__from__term(V *a);
static V F_Chk_dMaybe_dmap__nat(V a0);
static V W_Chk_dMaybe_dmap__nat(V *a);
static V W_Nat_dis__le(V *a);
static V F_Chk_dshow_dctr_dnat(V a0, V a1, V a2, V a3, V a4);
static V S1924(void);
static V S1925(void);
static V W_Chk_dshow_dctr_dnat(V *a);
static V F_Chk_dshow_dchain(V a0, V a1, V a2);
static V W_Chk_dshow_dchain(V *a);
static V F_Chk_dshow_dchain_dif(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dshow_dchain_dif(V *a);
static V F_Chk_dLst_dlast(V a1, V a2);
static V W_Chk_dLst_dlast(V *a);
static V F_Chk_dshow_dchain_dcons(V a0, V a1);
static V W_Chk_dshow_dchain_dcons(V *a);
static V F_Chk_dshow_dctr_dsucc(V a0, V a1, V a2, V a3, V a4);
static V S1932(void);
static V W_Chk_dshow_dctr_dsucc(V *a);
static V F_Chk_dshow_dchr__term(V a0, V a1);
static V S1934(void);
static V W_Chk_dshow_dchr__term(V *a);
static V F_Chk_dshow_dchr__term_du(V a0, V a1);
static V W_Chk_dshow_dchr__term_du(V *a);
static V F_Chk_dshow_dctr_dchr(V a0, V a1, V a2, V a3, V a4);
static V S1937(void);
static V S1938(void);
static V W_Chk_dshow_dctr_dchr(V *a);
static V F_Chk_dshow_dstr(V a0);
static V S1939(void);
static V W_Chk_dshow_dstr(V *a);
static V F_Chk_dshow_dstr_dgo(V a0);
static V W_Chk_dshow_dstr_dgo(V *a);
static V F_Chk_dshow_dstr__tail(V a0);
static V S1942(void);
static V W_Chk_dshow_dstr__tail(V *a);
static V F_Chk_dshow_dchrs(V a0);
static V S1944(void);
static V W_Chk_dshow_dchrs(V *a);
static V F_Chk_dshow_dchrs_dcat(V a0, V a1);
static V W_Chk_dshow_dchrs_dcat(V *a);
static V F_Chk_dshow_dstr_dc(V a0);
static V S1948(void);
static V S1949(void);
static V W_Chk_dshow_dstr_dc(V *a);
static V F_Chk_dshow_dctr_dstr(V a0, V a1, V a2, V a3, V a4);
static V S1951(void);
static V W_Chk_dshow_dctr_dstr(V *a);
static V F_Chk_dshow_dctr_dlst(V a0, V a1, V a2, V a3, V a4);
static V S1955(void);
static V S1956(void);
static V S1957(void);
static V S1958(void);
static V S1959(void);
static V S1960(void);
static V W_Chk_dshow_dctr_dlst(V *a);
static V F_Chk_dshow_dargs(V a0, V a1, V a2, V a3);
static V W_Chk_dshow_dargs(V *a);
static V F_Chk_dshow_dctr_dtup(V a0, V a1, V a2, V a3, V a4);
static V S1964(void);
static V S1965(void);
static V S1966(void);
static V W_Chk_dshow_dctr_dtup(V *a);
static V F_Chk_dshow_darr(V a0, V a1, V a2);
static V W_Chk_dshow_darr(V *a);
static V F_Chk_dshow_darr_dcat(V a0, V a1);
static V W_Chk_dshow_darr_dcat(V *a);
static V F_Chk_dshow_dctr_darr(V a0, V a1, V a2, V a3);
static V S1971(void);
static V S1972(void);
static V S1973(void);
static V W_Chk_dshow_dctr_darr(V *a);
static V F_Chk_dshow_dctr_dplain(V a0, V a1, V a2);
static V S1975(void);
static V S1976(void);
static V S1977(void);
static V S1978(void);
static V W_Chk_dshow_dctr_dplain(V *a);
static V F_Chk_df32__show(V a0);
static V S1980(void);
static V S1981(void);
static V S1982(void);
static V S1983(void);
static V S1984(void);
static V W_Chk_df32__show(V *a);
static V F_String_dcontains(V a0, V a1);
static V W_String_dcontains(V *a);
static V F_String_dcontains_dif(V a0, V a1, V a2);
static V W_String_dcontains_dif(V *a);
static V F_Chk_dF32_dfrom__bits(V a0);
static V W_Chk_dF32_dfrom__bits(V *a);
static V F_Chk_dWord_dfrom__u32(V a0);
static V W_Chk_dWord_dfrom__u32(V *a);
static V W_F32_dshow(V *a);
static V F_Chk_dLst_dempty(V a2);
static V W_Chk_dLst_dempty(V *a);
static V F_Chk_dshow_drems(V a0);
static V S1990(void);
static V S1991(void);
static V S1992(void);
static V W_Chk_dshow_drems(V *a);
static V F_Chk_dshow_dapp(V a0, V a1, V a2, V a3);
static V W_Chk_dshow_dapp(V *a);
static V F_Chk_dshow_dapp_dgo(V a0, V a1, V a2, V a3);
static V S1996(void);
static V S1997(void);
static V S1998(void);
static V S1999(void);
static V S2000(void);
static V S2001(void);
static V W_Chk_dshow_dapp_dgo(V *a);
static V F_Chk_dQ_ddef(V a0);
static V W_Chk_dQ_ddef(V *a);
static V F_Chk_dshow_dtyp(V a0, V a1, V a2);
static V S2004(void);
static V S2005(void);
static V S2006(void);
static V S2007(void);
static V W_Chk_dshow_dtyp(V *a);
static V F_Chk_dshow_dlet__ks(V a0, V a1);
static V W_Chk_dshow_dlet__ks(V *a);
static V F_Chk_dshow_dbound__at(V a0, V a1, V a2, V a3);
static V W_Chk_dshow_dbound__at(V *a);
static V F_Chk_dStr_dindex(V a0, V a1, V a2);
static V W_Chk_dStr_dindex(V *a);
static V F_Chk_dStr_dindex_dif(V a0, V a1, V a2, V a3);
static V W_Chk_dStr_dindex_dif(V *a);
static V F_Chk_dshow_dbound__at_dc(V a0, V a1, V a2);
static V W_Chk_dshow_dbound__at_dc(V *a);
static V F_Main_demit__value(V a0);
static V S2013(void);
static V S2014(void);
static V W_Main_demit__value(V *a);
static V F_Chk_dreport__text(V a0);
static V S2016(void);
static V S2018(void);
static V S2019(void);
static V S2020(void);
static V S2021(void);
static V S2022(void);
static V W_Chk_dreport__text(V *a);
static V F_Chk_dreport__lines(V a0);
static V S2024(void);
static V S2025(void);
static V S2026(void);
static V W_Chk_dreport__lines(V *a);
static V F_IO_dwrite__err(V a0);
static V W_IO_dwrite__err(V *a);
static V F_List_dis__empty(V a2);
static V W_List_dis__empty(V *a);
static V F_Chk_dreport(V a0, V a1);
static V W_Chk_dreport(V *a);
static V F_Chk_dreport_dgo(V a0, V a1, V a2, V a3);
static V W_Chk_dreport_dgo(V *a);
static V F_Chk_dreport_dwalk(V a0, V a1, V a2, V a3);
static V W_Chk_dreport_dwalk(V *a);
static V F_Chk_dreport_dwalk_done(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dreport_dwalk_done(V *a);
static V F_Chk_dreport_duses(V a0, V a1, V a2);
static V W_Chk_dreport_duses(V *a);
static V F_Chk_dtld__refs(V a0);
static V W_Chk_dtld__refs(V *a);
static V F_Chk_dCtrD_dts(V a0);
static V W_Chk_dCtrD_dts(V *a);
static V F_Chk_drefs_dlist(V a0, V a1);
static V W_Chk_drefs_dlist(V *a);
static V F_Chk_dterm__refs(V a0, V a1);
static V W_Chk_dterm__refs(V *a);
static V F_Chk_dtld__refs_dv(V a0);
static V W_Chk_dtld__refs_dv(V *a);
static V F_Chk_dreport_dclose(V a0, V a1, V a2);
static V W_Chk_dreport_dclose(V *a);
static V F_Chk_dreport_dusers(V a0, V a1);
static V W_Chk_dreport_dusers(V *a);
static V F_Chk_dreport_dusers_dif(V a0, V a1, V a2);
static V W_Chk_dreport_dusers_dif(V *a);
static V F_Chk_dreport_dclose_dadd(V a0, V a1, V a2, V a3);
static V W_Chk_dreport_dclose_dadd(V *a);
static V F_Chk_dreport_dclose_dadd_dif(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Chk_dreport_dclose_dadd_dif(V *a);
static V F_Chk_dStr_dfilter__in(V a0, V a1);
static V W_Chk_dStr_dfilter__in(V *a);
static V F_Chk_dStr_dfilter__in_dif(V a0, V a1, V a2);
static V W_Chk_dStr_dfilter__in_dif(V *a);
static V F_Chk_dBook_dtlds(V a0);
static V W_Chk_dBook_dtlds(V *a);
static V F_Map_dkeys(V a2);
static V W_Map_dkeys(V *a);
static V F_Map_dkeys_dgo(V a2, V a3);
static V W_Map_dkeys_dgo(V *a);
static V F_Chk_dreport_dbad__all(V a0, V a1);
static V W_Chk_dreport_dbad__all(V *a);
static V F_Chk_dTld_dbad(V a0);
static V W_Chk_dTld_dbad(V *a);
static V F_Chk_dbook__order(V a0);
static V W_Chk_dbook__order(V *a);
static V F_Chk_dList_ddrop__str2(V a0, V a1);
static V W_Chk_dList_ddrop__str2(V *a);
static V F_Chk_dStr_dunique(V a0, V a1);
static V W_Chk_dStr_dunique(V *a);
static V F_Chk_dStr_dunique_dif(V a0, V a1, V a2, V a3);
static V W_Chk_dStr_dunique_dif(V *a);
static V F_Main_dcheck(V a0, V a1);
static V S2057(void);
static V L2058(V *a);
static V W_Main_dcheck(V *a);
static V F_Main_dcheck_dfin(V a0);
static V W_Main_dcheck_dfin(V *a);
static V F_Chk_dcheck__book(V a0);
static V W_Chk_dcheck__book(V *a);
static V F_Chk_dbook__reset(V a0);
static V W_Chk_dbook__reset(V *a);
static V F_Chk_dbook__valid(V a0, V a1);
static V L2063(V *a);
static V W_Chk_dbook__valid(V *a);
static V F_Chk_dbook__valid_done(V a0, V a1, V a2);
static V L2065(V *a);
static V L2066(V *a);
static V W_Chk_dbook__valid_done(V *a);
static V F_Chk_dvalid_ddef(V a0, V a1, V a2);
static V L2067(V *a);
static V L2068(V *a);
static V L2069(V *a);
static V L2070(V *a);
static V L2071(V *a);
static V L2072(V *a);
static V L2073(V *a);
static V L2074(V *a);
static V L2075(V *a);
static V W_Chk_dvalid_ddef(V *a);
static V F_Chk_dbook__set(V a0, V a1, V a2);
static V W_Chk_dbook__set(V *a);
static V F_Chk_dK_dset__book(V a0);
static V L2077(V *a);
static V W_Chk_dK_dset__book(V *a);
static V F_Chk_dK_dbook(void);
static V L2078(V *a);
static V W_Chk_dK_dbook(V *a);
static V F_Chk_dK_dbind(V a2, V a3);
static V L2079(V *a);
static V W_Chk_dK_dbind(V *a);
static V F_Chk_dK_dgo(V a2, V a3);
static V W_Chk_dK_dgo(V *a);
static V F_Chk_dK_dgo_ddone(V a2, V a3);
static V W_Chk_dK_dgo_ddone(V *a);
static V F_Chk_dK_dpure(V a1);
static V L2082(V *a);
static V W_Chk_dK_dpure(V *a);
static V F_Chk_ddef__check(V a0, V a1, V a2);
static V L2083(V *a);
static V L2084(V *a);
static V L2085(V *a);
static V W_Chk_ddef__check(V *a);
static V F_Chk_dTld_dx__of(V a0);
static V W_Chk_dTld_dx__of(V *a);
static V F_Chk_ddef__check_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2089(V *a);
static V L2090(V *a);
static V W_Chk_ddef__check_dgo(V *a);
static V F_Chk_dTld_ddu(V a0);
static V W_Chk_dTld_ddu(V *a);
static V F_Chk_dTld_ddn(V a0);
static V W_Chk_dTld_ddn(V *a);
static V F_Chk_dterm__check(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2094(V *a);
static V L2095(V *a);
static V L2096(V *a);
static V L2097(V *a);
static V L2098(V *a);
static V L2099(V *a);
static V L2100(V *a);
static V S2101(void);
static V L2102(V *a);
static V L2103(V *a);
static V W_Chk_dterm__check(V *a);
static V F_Chk_dcheck_dinfer(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2104(V *a);
static V L2105(V *a);
static V W_Chk_dcheck_dinfer(V *a);
static V F_Chk_dIR_dty(V a0);
static V W_Chk_dIR_dty(V *a);
static V F_Chk_dterm__compare(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dterm__compare(V *a);
static V F_Chk_dcmp_dwnf(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dcmp_dwnf(V *a);
static V F_Chk_dTm_dis__lam(V a0);
static V W_Chk_dTm_dis__lam(V *a);
static V F_Chk_dcmp_dlam(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Chk_dcmp_dlam(V *a);
static V F_Chk_dcmp_dlit(V a0, V a1);
static V W_Chk_dcmp_dlit(V *a);
static V F_Chk_dTm_dis__ctr(V a0);
static V W_Chk_dTm_dis__ctr(V *a);
static V F_Chk_dTm_dis__lit(V a0);
static V W_Chk_dTm_dis__lit(V *a);
static V F_Chk_dcmp_dgo(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dcmp_dgo(V *a);
static V F_Chk_dcmps(V a0, V a1, V a2, V a3);
static V W_Chk_dcmps(V *a);
static V F_Chk_dStr_dsubset(V a0, V a1);
static V W_Chk_dStr_dsubset(V *a);
static V F_Chk_dQ_deq(V a0, V a1);
static V W_Chk_dQ_deq(V *a);
static V F_Chk_dcmp_dtyp(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dcmp_dtyp(V *a);
static V F_Chk_dcmp_dkind(V a0, V a1, V a2, V a3);
static V W_Chk_dcmp_dkind(V *a);
static V F_Chk_dTm_dis__qua__not__many(V a0);
static V W_Chk_dTm_dis__qua__not__many(V *a);
static V F_Chk_dTm_dis__many(V a0);
static V W_Chk_dTm_dis__many(V *a);
static V F_Chk_dcmp_dkind_dgo(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dcmp_dkind_dgo(V *a);
static V F_Chk_dcmp_dkind_dmin(V a0, V a1, V a2, V a3);
static V W_Chk_dcmp_dkind_dmin(V *a);
static V F_Chk_dcmp_dkind_drmin(V a0, V a1, V a2, V a3);
static V W_Chk_dcmp_dkind_drmin(V *a);
static V F_Chk_dterm__apply1(V a0, V a1, V a2);
static V W_Chk_dterm__apply1(V *a);
static V F_Chk_dTm_dlam__k(V a0, V a1);
static V S2128(void);
static V W_Chk_dTm_dlam__k(V *a);
static V F_Chk_dcheck_dinfer_dcmp(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Chk_dcheck_dinfer_dcmp(V *a);
static V F_Chk_dCL_ddn(V a0);
static V W_Chk_dCL_ddn(V *a);
static V F_Chk_dK_derr(V a1, V a2, V a3, V a4, V a5);
static V L2132(V *a);
static V W_Chk_dK_derr(V *a);
static V F_Chk_derr(V a0, V a1, V a2, V a3, V a4, V a5);
static V S2133(void);
static V W_Chk_derr(V *a);
static V F_Chk_dterm__infer(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2135(V *a);
static V L2136(V *a);
static V L2137(V *a);
static V L2138(V *a);
static V L2139(V *a);
static V L2140(V *a);
static V L2141(V *a);
static V L2142(V *a);
static V L2143(V *a);
static V L2144(V *a);
static V L2145(V *a);
static V L2146(V *a);
static V L2147(V *a);
static V L2148(V *a);
static V W_Chk_dterm__infer(V *a);
static V F_Chk_dinfer_dfail(V a0, V a1, V a2);
static V L2149(V *a);
static V L2150(V *a);
static V L2151(V *a);
static V S2152(void);
static V S2153(void);
static V W_Chk_dinfer_dfail(V *a);
static V F_Chk_dTm_dname(V a0);
static V S2155(void);
static V W_Chk_dTm_dname(V *a);
static V F_Chk_dbook__ctr(V a0, V a1);
static V W_Chk_dbook__ctr(V *a);
static V F_Chk_dtyp(V a0);
static V W_Chk_dtyp(V *a);
static V F_Chk_dinfer_dadt(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V S2157(void);
static V S2158(void);
static V S2159(void);
static V W_Chk_dinfer_dadt(V *a);
static V F_Chk_dAD_dn(V a0);
static V W_Chk_dAD_dn(V *a);
static V F_Chk_dinfer_dadt_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2161(V *a);
static V W_Chk_dinfer_dadt_dgo(V *a);
static V F_Chk_dinfer_dadt_dfin(V a0);
static V W_Chk_dinfer_dadt_dfin(V *a);
static V F_Chk_dAD_dt(V a0);
static V W_Chk_dAD_dt(V *a);
static V F_Chk_dtele__check(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L2165(V *a);
static V L2166(V *a);
static V L2167(V *a);
static V W_Chk_dtele__check(V *a);
static V F_Chk_duses__add(V a0, V a1);
static V W_Chk_duses__add(V *a);
static V F_Chk_duses__merge(V a0, V a1, V a2);
static V W_Chk_duses__merge(V *a);
static V F_Chk_duses__put(V a0, V a1, V a2);
static V W_Chk_duses__put(V *a);
static V F_Chk_dUs_di(V a0);
static V W_Chk_dUs_di(V *a);
static V F_Chk_duses__put_dif(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Chk_duses__put_dif(V *a);
static V F_Chk_dUs_dq(V a0);
static V W_Chk_dUs_dq(V *a);
static V F_Chk_dquant__join(V a0, V a1);
static V W_Chk_dquant__join(V *a);
static V F_Chk_dAll_da(V a0);
static V W_Chk_dAll_da(V *a);
static V F_Chk_dAll_dq(V a0);
static V W_Chk_dAll_dq(V *a);
static V F_Chk_dquant__dem(V a0, V a1);
static V W_Chk_dquant__dem(V *a);
static V F_Chk_dtele__head(V a0, V a1, V a2, V a3);
static V L2178(V *a);
static V W_Chk_dtele__head(V *a);
static V F_Chk_dtele__head_dgo(V a0, V a1, V a2, V a3);
static V S2180(void);
static V W_Chk_dtele__head_dgo(V *a);
static V F_Chk_dK_dif(V a1, V a2, V a3);
static V W_Chk_dK_dif(V *a);
static V F_Chk_dbook__adt(V a0, V a1, V a2);
static V L2182(V *a);
static V W_Chk_dbook__adt(V *a);
static V F_Chk_dbook__adt_dgo(V a0, V a1, V a2, V a3);
static V S2184(void);
static V S2185(void);
static V W_Chk_dbook__adt_dgo(V *a);
static V F_Chk_dADT_dr(V a0);
static V W_Chk_dADT_dr(V *a);
static V F_Chk_dctrs__drop(V a0, V a1);
static V W_Chk_dctrs__drop(V *a);
static V F_Chk_dctrs__drop_dif(V a0, V a1, V a2);
static V W_Chk_dctrs__drop_dif(V *a);
static V F_Chk_dinfer_dapp(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2191(V *a);
static V W_Chk_dinfer_dapp(V *a);
static V F_Chk_dinfer_dapp_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V L2193(V *a);
static V L2194(V *a);
static V S2195(void);
static V W_Chk_dinfer_dapp_dgo(V *a);
static V F_Chk_dctx__bind(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dctx__bind(V *a);
static V F_Chk_dlhs__kind(V a0, V a1);
static V W_Chk_dlhs__kind(V *a);
static V F_Chk_dQ_dis__many(V a0);
static V W_Chk_dQ_dis__many(V *a);
static V F_Chk_dCL_du(V a0);
static V W_Chk_dCL_du(V *a);
static V F_Chk_dinfer_dref(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V S2199(void);
static V W_Chk_dinfer_dref(V *a);
static V F_Chk_dinfer_dref_dlive(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V L2200(V *a);
static V L2201(V *a);
static V L2202(V *a);
static V L2203(V *a);
static V S2204(void);
static V L2205(V *a);
static V W_Chk_dinfer_dref_dlive(V *a);
static V F_Chk_dinfer_dref_dself(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L2206(V *a);
static V S2207(void);
static V L2208(V *a);
static V W_Chk_dinfer_dref_dself(V *a);
static V F_Chk_dinfer_dref_dfin(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2210(void);
static V S2211(void);
static V W_Chk_dinfer_dref_dfin(V *a);
static V F_Chk_dCL_ddecreases(V a0, V a1, V a2);
static V W_Chk_dCL_ddecreases(V *a);
static V F_Chk_dcl_dcols(V a0);
static V W_Chk_dcl_dcols(V *a);
static V F_Chk_dterm__args(V a0);
static V W_Chk_dterm__args(V *a);
static V F_Chk_ddescend_dargs(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_ddescend_dargs(V *a);
static V F_Chk_dterm__descend(V a0, V a1, V a2, V a3);
static V W_Chk_dterm__descend(V *a);
static V F_Chk_ddescend_dlit(V a0, V a1);
static V W_Chk_ddescend_dlit(V *a);
static V F_Chk_ddescend_dgo(V a0, V a1, V a2);
static V W_Chk_ddescend_dgo(V *a);
static V F_Chk_ddescend_dsame(V a0, V a1, V a2);
static V W_Chk_ddescend_dsame(V *a);
static V F_Chk_ddescend_dctr(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_ddescend_dctr(V *a);
static V F_Chk_ddescend_dsub(V a0, V a1, V a2);
static V W_Chk_ddescend_dsub(V *a);
static V F_Chk_dCtr_dxs(V a0);
static V W_Chk_dCtr_dxs(V *a);
static V F_Chk_ddescend_dfields(V a0, V a1, V a2, V a3);
static V W_Chk_ddescend_dfields(V *a);
static V F_Chk_ddescend_dfields_dstep(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_ddescend_dfields_dstep(V *a);
static V F_Chk_ddescend_dfields_dnext(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_ddescend_dfields_dnext(V *a);
static V F_Chk_ddescend_dctr_dfields(V a0, V a1, V a2, V a3);
static V W_Chk_ddescend_dctr_dfields(V *a);
static V F_Chk_ddescend_dvar(V a0, V a1);
static V W_Chk_ddescend_dvar(V *a);
static V F_Chk_ddescend_dargs_dstep(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Chk_ddescend_dargs_dstep(V *a);
static V F_Chk_dinfer_dref_dinst(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V L2226(V *a);
static V L2227(V *a);
static V L2228(V *a);
static V W_Chk_dinfer_dref_dinst(V *a);
static V F_Chk_dList_ddrop__tm(V a0, V a1);
static V W_Chk_dList_ddrop__tm(V *a);
static V F_Chk_ddef__inst(V a0, V a1, V a2, V a3, V a4, V a5);
static V S2233(void);
static V W_Chk_ddef__inst(V *a);
static V F_Chk_ddef__inst_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2234(V *a);
static V L2235(V *a);
static V L2236(V *a);
static V S2237(void);
static V L2238(V *a);
static V S2239(void);
static V S2240(void);
static V W_Chk_ddef__inst_dgo(V *a);
static V F_Chk_dBook_dtmp(V a0, V a1);
static V W_Chk_dBook_dtmp(V *a);
static V F_Chk_ddef__inst_dfind(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L2243(V *a);
static V S2244(void);
static V W_Chk_ddef__inst_dfind(V *a);
static V F_Chk_ddef__inst_dnew(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2246(void);
static V W_Chk_ddef__inst_dnew(V *a);
static V F_Chk_ddef__inst_dmake(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2248(V *a);
static V S2249(void);
static V L2250(V *a);
static V L2251(V *a);
static V L2252(V *a);
static V L2253(V *a);
static V L2254(V *a);
static V L2255(V *a);
static V L2256(V *a);
static V W_Chk_ddef__inst_dmake(V *a);
static V F_Chk_dBook_dadd__tmp(V a0, V a1, V a2, V a3);
static V W_Chk_dBook_dadd__tmp(V *a);
static V F_Chk_dTld_ddval(V a0);
static V W_Chk_dTld_ddval(V *a);
static V F_Chk_dapplys(V a0, V a1, V a2);
static V W_Chk_dapplys(V *a);
static V F_Chk_dBook_dtcnt(V a0, V a1);
static V W_Chk_dBook_dtcnt(V *a);
static V F_Chk_dCL_dz(V a0);
static V W_Chk_dCL_dz(V *a);
static V F_Chk_dTld_dt(V a0);
static V W_Chk_dTld_dt(V *a);
static V F_Chk_dinst_dargs(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2265(V *a);
static V L2266(V *a);
static V L2267(V *a);
static V W_Chk_dinst_dargs(V *a);
static V F_Chk_dinst_dclosed(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2268(V *a);
static V W_Chk_dinst_dclosed(V *a);
static V F_Chk_dinst_dclosed_dgo(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dinst_dclosed_dgo(V *a);
static V F_Chk_dinst_dclosed_derr(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dinst_dclosed_derr(V *a);
static V F_Chk_dinst_dclosed_derr_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2272(void);
static V S2273(void);
static V W_Chk_dinst_dclosed_derr_dgo(V *a);
static V F_Chk_dList_dtake__tm(V a0, V a1);
static V W_Chk_dList_dtake__tm(V *a);
static V F_Chk_dTld_dis__base(V a0);
static V W_Chk_dTld_dis__base(V *a);
static V F_Chk_dTld_dis__open(V a0);
static V W_Chk_dTld_dis__open(V *a);
static V F_Chk_dTld_dx(V a0);
static V W_Chk_dTld_dx(V *a);
static V F_Chk_dQ_dis__none(V a0);
static V W_Chk_dQ_dis__none(V *a);
static V F_Chk_dinfer_dvar(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Chk_dinfer_dvar(V *a);
static V F_Chk_dctx__get(V a0, V a1);
static V W_Chk_dctx__get(V *a);
static V F_Chk_dinfer_dvar_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2282(void);
static V W_Chk_dinfer_dvar_dgo(V *a);
static V F_Chk_duses__one(V a0, V a1);
static V W_Chk_duses__one(V *a);
static V F_Chk_dcheck_drwt(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10);
static V S2284(void);
static V L2285(V *a);
static V L2286(V *a);
static V L2287(V *a);
static V L2288(V *a);
static V L2289(V *a);
static V S2290(void);
static V W_Chk_dcheck_drwt(V *a);
static V F_Chk_dIR_dus(V a0);
static V W_Chk_dIR_dus(V *a);
static V F_Chk_dcheck_drfl(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2293(V *a);
static V W_Chk_dcheck_drfl(V *a);
static V F_Chk_dcheck_dtypeless(V a1, V a2, V a3, V a4, V a5);
static V L2294(V *a);
static V W_Chk_dcheck_dtypeless(V *a);
static V F_Chk_dtypeless__show(V a0, V a1, V a2);
static V S2295(void);
static V S2296(void);
static V W_Chk_dtypeless__show(V *a);
static V F_Chk_dtypeless_dnote(V a0, V a1);
static V S2298(void);
static V S2299(void);
static V S2300(void);
static V S2301(void);
static V W_Chk_dtypeless_dnote(V *a);
static V F_Chk_dTld_dis__adt(V a0);
static V W_Chk_dTld_dis__adt(V *a);
static V F_Chk_dctx__scope(V a0);
static V W_Chk_dctx__scope(V *a);
static V F_Chk_dctx__len(V a0);
static V W_Chk_dctx__len(V *a);
static V W_U32_dmax(V *a);
static V F_Chk_dctx__scope_dgo(V a0, V a1, V a2);
static V W_Chk_dctx__scope_dgo(V *a);
static V F_Chk_dctx__scope_dc(V a0, V a1, V a2, V a3);
static V W_Chk_dctx__scope_dc(V *a);
static V F_Chk_dctx__name(V a0, V a1);
static V S2306(void);
static V W_Chk_dctx__name(V *a);
static V F_Chk_dexpr__show(V a0, V a1, V a2);
static V S2308(void);
static V W_Chk_dexpr__show(V *a);
static V F_Chk_dcheck_delim(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V S2310(void);
static V L2311(V *a);
static V L2312(V *a);
static V W_Chk_dcheck_delim(V *a);
static V F_Chk_dcheck_delim_dadt(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V L2314(V *a);
static V S2315(void);
static V W_Chk_dcheck_delim_dadt(V *a);
static V F_Chk_dAD_dcs(V a0);
static V W_Chk_dAD_dcs(V *a);
static V F_Chk_dcheck_delim_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11);
static V L2318(V *a);
static V S2319(void);
static V S2320(void);
static V W_Chk_dcheck_delim_dgo(V *a);
static V F_Chk_dctrs__find(V a0, V a1);
static V W_Chk_dctrs__find(V *a);
static V F_Chk_dctrs__find_dif(V a0, V a1, V a2, V a3);
static V W_Chk_dctrs__find_dif(V *a);
static V F_Chk_dcheck_dmat(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11, V a12, V a13);
static V S2324(void);
static V S2325(void);
static V L2326(V *a);
static V L2327(V *a);
static V L2328(V *a);
static V L2329(V *a);
static V L2330(V *a);
static V W_Chk_dcheck_dmat(V *a);
static V F_Chk_duses__join(V a0, V a1);
static V W_Chk_duses__join(V *a);
static V F_Chk_dAll_dk(V a0);
static V S2332(void);
static V W_Chk_dAll_dk(V *a);
static V F_Chk_dCL_dext(V a0, V a1, V a2);
static V L2335(V *a);
static V W_Chk_dCL_dext(V *a);
static V F_Chk_dtele__fill(V a0, V a1, V a2, V a3, V a4);
static V L2337(V *a);
static V L2338(V *a);
static V W_Chk_dtele__fill(V *a);
static V F_Chk_dCtrD_dnames(V a0);
static V W_Chk_dCtrD_dnames(V *a);
static V F_Chk_dctx__dead(V a0, V a1);
static V W_Chk_dctx__dead(V *a);
static V F_Chk_dctx__dead_dty(V a0, V a1);
static V W_Chk_dctx__dead_dty(V *a);
static V F_Chk_dctx__dead_dtld(V a0, V a1);
static V W_Chk_dctx__dead_dtld(V *a);
static V F_Chk_dcheck_dlit(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2344(V *a);
static V W_Chk_dcheck_dlit(V *a);
static V F_Chk_dLit_dv(V a0);
static V W_Chk_dLit_dv(V *a);
static V F_Chk_dlit_dctr(V a0);
static V S2347(void);
static V S2348(void);
static V S2349(void);
static V S2350(void);
static V W_Chk_dlit_dctr(V *a);
static V F_Chk_dcheck_dlit_dbase(V a0, V a1, V a2);
static V W_Chk_dcheck_dlit_dbase(V *a);
static V F_Chk_dcheck_dlit_dbase__adt(V a0);
static V W_Chk_dcheck_dlit_dbase__adt(V *a);
static V F_Chk_dcheck_dctr(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V L2353(V *a);
static V L2354(V *a);
static V L2355(V *a);
static V W_Chk_dcheck_dctr(V *a);
static V F_Chk_dbook__fam(V a0, V a1);
static V W_Chk_dbook__fam(V *a);
static V F_Chk_dbook__fam_dctr(V a0, V a1, V a2);
static V W_Chk_dbook__fam_dctr(V *a);
static V F_Chk_dbook__fam_dgo(V a0, V a1, V a2, V a3);
static V W_Chk_dbook__fam_dgo(V *a);
static V F_Chk_dcheck_dctr_dfind(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11);
static V L2359(V *a);
static V S2360(void);
static V S2361(void);
static V S2362(void);
static V S2363(void);
static V S2364(void);
static V S2365(void);
static V S2366(void);
static V W_Chk_dcheck_dctr_dfind(V *a);
static V F_Chk_dcheck_dctr_dfields(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L2367(V *a);
static V L2368(V *a);
static V W_Chk_dcheck_dctr_dfields(V *a);
static V F_Chk_dcheck_dlet_dbody(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10);
static V L2371(V *a);
static V L2372(V *a);
static V L2373(V *a);
static V W_Chk_dcheck_dlet_dbody(V *a);
static V F_Chk_dcheck_dlet_dused(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2376(V *a);
static V W_Chk_dcheck_dlet_dused(V *a);
static V F_Chk_duses__del(V a0, V a1);
static V W_Chk_duses__del(V *a);
static V F_Chk_duses__del_dif(V a0, V a1, V a2);
static V W_Chk_duses__del_dif(V *a);
static V F_Chk_duses__get(V a0, V a1);
static V W_Chk_duses__get(V *a);
static V F_Chk_dquant__used(V a0, V a1, V a2, V a3, V a4, V a5);
static V S2380(void);
static V W_Chk_dquant__used(V *a);
static V F_Chk_dlet_dvars(V a0, V a1, V a2);
static V W_Chk_dlet_dvars(V *a);
static V F_Chk_dcheck_dlets(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9);
static V L2386(V *a);
static V L2387(V *a);
static V W_Chk_dcheck_dlets(V *a);
static V F_Chk_dcheck__kind(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2389(V *a);
static V W_Chk_dcheck__kind(V *a);
static V F_Chk_dcheck__kind_dgo(V a0, V a1, V a2);
static V W_Chk_dcheck__kind_dgo(V *a);
static V F_Chk_dcheck__kind_derr(V a0, V a1, V a2);
static V W_Chk_dcheck__kind_derr(V *a);
static V F_Chk_dMsg_dis__kind(V a0, V a1);
static V W_Chk_dMsg_dis__kind(V *a);
static V F_Chk_dSp_deq(V a0, V a1);
static V W_Chk_dSp_deq(V *a);
static V F_Chk_dcheck_dlam(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9);
static V L2400(V *a);
static V L2401(V *a);
static V L2402(V *a);
static V L2403(V *a);
static V L2404(V *a);
static V W_Chk_dcheck_dlam(V *a);
static V F_Chk_dCL_dunder(V a0, V a1);
static V L2407(V *a);
static V W_Chk_dCL_dunder(V *a);
static V F_Chk_dQ_dis__lone(V a0);
static V W_Chk_dQ_dis__lone(V *a);
static V F_Chk_ddef__check_dtmpl(V a0, V a1, V a2, V a3, V a4);
static V L2410(V *a);
static V S2411(void);
static V L2412(V *a);
static V L2413(V *a);
static V S2414(void);
static V S2415(void);
static V L2416(V *a);
static V L2417(V *a);
static V L2418(V *a);
static V W_Chk_ddef__check_dtmpl(V *a);
static V F_Chk_dbook__has(V a0, V a1);
static V W_Chk_dbook__has(V *a);
static V F_Chk_dtele__unbind(V a0, V a1);
static V W_Chk_dtele__unbind(V *a);
static V F_Chk_dtele__unbind_dgo(V a0, V a1, V a2, V a3);
static V W_Chk_dtele__unbind_dgo(V *a);
static V F_Chk_dDom_dqs(V a0);
static V W_Chk_dDom_dqs(V *a);
static V F_Chk_dTld_dimps(V a0);
static V W_Chk_dTld_dimps(V *a);
static V F_Chk_dvalid_dforeign(V a0, V a1, V a2);
static V L2423(V *a);
static V L2424(V *a);
static V S2425(void);
static V W_Chk_dvalid_dforeign(V *a);
static V F_Chk_dvalid_dret(V a0, V a1, V a2);
static V W_Chk_dvalid_dret(V *a);
static V F_Chk_dCL_dof(V a0, V a1);
static V W_Chk_dCL_dof(V *a);
static V F_Chk_dTld_ddec(V a0);
static V W_Chk_dTld_ddec(V *a);
static V F_Chk_dbook__opened(V a0);
static V W_Chk_dbook__opened(V *a);
static V F_Chk_dTld_dis__law__open(V a0);
static V W_Chk_dTld_dis__law__open(V *a);
static V F_Chk_dvalid_dadt(V a0, V a1, V a2, V a3);
static V L2430(V *a);
static V L2431(V *a);
static V L2432(V *a);
static V L2433(V *a);
static V W_Chk_dvalid_dadt(V *a);
static V F_Chk_dvalid_dctrs(V a0, V a1, V a2, V a3);
static V L2435(V *a);
static V W_Chk_dvalid_dctrs(V *a);
static V F_Chk_dvalid_dfields(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L2437(V *a);
static V L2438(V *a);
static V L2439(V *a);
static V L2440(V *a);
static V L2441(V *a);
static V W_Chk_dvalid_dfields(V *a);
static V F_Chk_dvalid_dtip(V a0, V a1, V a2, V a3, V a4);
static V L2442(V *a);
static V S2443(void);
static V S2444(void);
static V W_Chk_dvalid_dtip(V *a);
static V F_Chk_dvalid_dtip_dok(V a0, V a1, V a2, V a3);
static V W_Chk_dvalid_dtip_dok(V *a);
static V F_Chk_dvalid_dtip_dparams(V a0, V a1, V a2);
static V W_Chk_dvalid_dtip_dparams(V *a);
static V F_Chk_dvalid_dtip_dvar(V a0, V a1);
static V W_Chk_dvalid_dtip_dvar(V *a);
static V W_Nat_dis__ge(V *a);
static V F_Chk_dvalid_dkind(V a0, V a1, V a2);
static V S2450(void);
static V S2451(void);
static V W_Chk_dvalid_dkind(V *a);
static V F_Chk_dDom_dctx(V a0, V a1, V a2);
static V W_Chk_dDom_dctx(V *a);
static V F_Chk_dbook__set__ctrs(V a0, V a1);
static V W_Chk_dbook__set__ctrs(V *a);
static V F_Chk_dbook__set__ctr(V a0, V a1, V a2);
static V W_Chk_dbook__set__ctr(V *a);
static V F_Chk_dcheck__book_dfin(V a0);
static V W_Chk_dcheck__book_dfin(V *a);
static V F_Chk_dcheck__book_dholes(V a0);
static V S2457(void);
static V S2458(void);
static V S2459(void);
static V S2460(void);
static V S2461(void);
static V S2462(void);
static V W_Chk_dcheck__book_dholes(V *a);
static V F_Chk_dbook__nil(void);
static V W_Chk_dbook__nil(V *a);
static V F_Chk_dcheck__book_downed(V a0);
static V S2463(void);
static V S2464(void);
static V S2465(void);
static V S2466(void);
static V S2467(void);
static V W_Chk_dcheck__book_downed(V *a);
static V F_Chk_dTld_dbase__of(V a0);
static V W_Chk_dTld_dbase__of(V *a);
static V F_Chk_dBook_dholes(V a0);
static V W_Chk_dBook_dholes(V *a);
static V F_Main_dcheck_dres(V a0, V a1);
static V W_Main_dcheck_dres(V *a);
static V F_Main_dchk_dfail(V a1);
static V W_Main_dchk_dfail(V *a);
static V F_Chk_dshow__err(V a0);
static V S2472(void);
static V S2473(void);
static V W_Chk_dshow__err(V *a);
static V F_Chk_derr__show(V a0);
static V S2480(void);
static V S2481(void);
static V S2482(void);
static V S2483(void);
static V S2484(void);
static V S2485(void);
static V S2486(void);
static V S2487(void);
static V S2488(void);
static V W_Chk_derr__show(V *a);
static V F_Chk_derr_dlines(V a0);
static V S2490(void);
static V W_Chk_derr_dlines(V *a);
static V F_Chk_dStr_dcount__nl(V a0);
static V W_Chk_dStr_dcount__nl(V *a);
static V F_Chk_derr_dlines_dgo(V a0, V a1);
static V W_Chk_derr_dlines_dgo(V *a);
static V F_Chk_dList_ddrop__str(V a0, V a1);
static V W_Chk_dList_ddrop__str(V *a);
static V F_Chk_derr_dlines_deach(V a0, V a1, V a2, V a3, V a4);
static V S2498(void);
static V W_Chk_derr_dlines_deach(V *a);
static V F_Chk_derr_dlines_done(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2500(void);
static V S2501(void);
static V S2502(void);
static V S2503(void);
static V W_Chk_derr_dlines_done(V *a);
static V F_Chk_dStr_dpadl(V a0, V a1);
static V S2505(void);
static V W_Chk_dStr_dpadl(V *a);
static V F_String_drepeat(V a0, V a1);
static V W_String_drepeat(V *a);
static V W_Nat_dmin(V *a);
static V W_Nat_dmax(V *a);
static V F_Chk_dctx__width(V a0);
static V W_Chk_dctx__width(V *a);
static V F_Chk_dctx__sorted(V a0);
static V W_Chk_dctx__sorted(V *a);
static V F_Chk_derr_dctx__lines(V a0, V a1, V a2, V a3);
static V S2509(void);
static V S2510(void);
static V S2511(void);
static V W_Chk_derr_dctx__lines(V *a);
static V F_Chk_dList_dtake__str(V a0, V a1);
static V W_Chk_dList_dtake__str(V *a);
static V F_Chk_dList_dtake__strn(V a0, V a1);
static V W_Chk_dList_dtake__strn(V *a);
static V F_Chk_dStr_dpad(V a0, V a1);
static V S2515(void);
static V W_Chk_dStr_dpad(V *a);
static V F_Chk_derr_dmsg(V a0, V a1, V a2, V a3);
static V S2517(void);
static V S2518(void);
static V S2519(void);
static V W_Chk_derr_dmsg(V *a);
static V F_Chk_dshow__err_draw(V a0);
static V S2521(void);
static V W_Chk_dshow__err_draw(V *a);
static V F_Main_dchk_dload(V a0, V a1, V a2, V a3, V a4, V a5);
static V S2523(void);
static V W_Main_dchk_dload(V *a);
static V F_Path_dnorm(V a0);
static V S2525(void);
static V S2527(void);
static V S2528(void);
static V S2529(void);
static V W_Path_dnorm(V *a);
static V F_Path_dfold(V a0, V a1, V a2);
static V S2531(void);
static V W_Path_dfold(V *a);
static V F_Path_dpush(V a0, V a1, V a2);
static V S2533(void);
static V S2534(void);
static V S2535(void);
static V S2536(void);
static V S2537(void);
static V W_Path_dpush(V *a);
static V F_CS_dseen(V a0);
static V W_CS_dseen(V *a);
static V F_Chk_dSB2_dfind(V a0, V a1);
static V W_Chk_dSB2_dfind(V *a);
static V F_Chk_dSB2_dfind_dif(V a0, V a1, V a2, V a3);
static V W_Chk_dSB2_dfind_dif(V *a);
static V F_Main_dchk_dseen(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2542(void);
static V S2543(void);
static V S2544(void);
static V S2545(void);
static V S2546(void);
static V L2547(V *a);
static V W_Main_dchk_dseen(V *a);
static V F_Main_dchk_dread(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2549(void);
static V W_Main_dchk_dread(V *a);
static V F_Main_dchk_dsrc(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Main_dchk_dsrc(V *a);
static V F_Chk_dheader(V a0);
static V W_Chk_dheader(V *a);
static V F_Chk_dheader_dgo(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dheader_dgo(V *a);
static V F_Chk_dStr_dtrim(V a0);
static V W_Chk_dStr_dtrim(V *a);
static V F_String_dtrim(V a0);
static V W_String_dtrim(V *a);
static V F_String_dtrim__start(V a0);
static V W_String_dtrim__start(V *a);
static V F_Char_dis__space(V a0);
static V W_Char_dis__space(V *a);
static V F_String_dtrim__start_dif(V a0, V a1, V a2);
static V W_String_dtrim__start_dif(V *a);
static V F_String_dtrim__end(V a0);
static V W_String_dtrim__end(V *a);
static V F_Chk_dheader_dline(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2555(void);
static V S2556(void);
static V S2557(void);
static V W_Chk_dheader_dline(V *a);
static V F_Chk_dheader_dline_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V W_Chk_dheader_dline_dgo(V *a);
static V F_Chk_dheader_drest(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dheader_drest(V *a);
static V F_Chk_dheader_dgo_drest(V a0, V a1, V a2);
static V W_Chk_dheader_dgo_drest(V *a);
static V F_Chk_dStr_dwords(V a0);
static V S2560(void);
static V W_Chk_dStr_dwords(V *a);
static V F_Chk_dStr_dwords_dgo(V a0, V a1, V a2);
static V W_Chk_dStr_dwords_dgo(V *a);
static V F_Chk_dis__space(V a0);
static V W_Chk_dis__space(V *a);
static V F_Chk_dStr_dwords_dchr(V a0, V a1, V a2, V a3, V a4);
static V S2563(void);
static V W_Chk_dStr_dwords_dchr(V *a);
static V F_Chk_dStr_dwords_dpush(V a0, V a1);
static V W_Chk_dStr_dwords_dpush(V *a);
static V F_Chk_dStr_duntil__hash(V a0);
static V S2565(void);
static V W_Chk_dStr_duntil__hash(V *a);
static V F_Chk_dimport_dparse(V a0);
static V S2567(void);
static V S2568(void);
static V W_Chk_dimport_dparse(V *a);
static V F_Chk_dis__ident(V a0);
static V W_Chk_dis__ident(V *a);
static V F_Chk_dis__ident_drest(V a0);
static V W_Chk_dis__ident_drest(V *a);
static V F_Chk_dis__digit(V a0);
static V W_Chk_dis__digit(V *a);
static V F_Chk_dis__head(V a0);
static V W_Chk_dis__head(V *a);
static V F_Chk_dheader_dimp(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V S2573(void);
static V S2574(void);
static V S2575(void);
static V W_Chk_dheader_dimp(V *a);
static V F_Chk_dheader_dimp_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2579(void);
static V W_Chk_dheader_dimp_dgo(V *a);
static V F_Chk_dheader_dgo_dnext(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dheader_dgo_dnext(V *a);
static V F_Chk_dStr_dindex__of(V a0, V a1, V a2);
static V W_Chk_dStr_dindex__of(V *a);
static V F_Chk_derr0(V a0, V a1, V a2);
static V S2581(void);
static V S2582(void);
static V W_Chk_derr0(V *a);
static V F_Chk_dStr_dfirst(V a0);
static V W_Chk_dStr_dfirst(V *a);
static V F_Main_dchk_dhdr(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2586(V *a);
static V W_Main_dchk_dhdr(V *a);
static V F_Main_dchk_dparse(V a0, V a1, V a2, V a3, V a4, V a5);
static V S2590(void);
static V W_Main_dchk_dparse(V *a);
static V F_Chk_dparse__file(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Chk_dparse__file(V *a);
static V F_Chk_dP_ddecls(void);
static V L2591(V *a);
static V L2592(V *a);
static V W_Chk_dP_ddecls(V *a);
static V F_Chk_dP_ddecl(void);
static V L2593(V *a);
static V S2594(void);
static V L2595(V *a);
static V S2596(void);
static V L2597(V *a);
static V S2598(void);
static V L2599(V *a);
static V S2600(void);
static V L2601(V *a);
static V L2602(V *a);
static V W_Chk_dP_ddecl(V *a);
static V F_Chk_dP_ddecl_dgo(V a0, V a1, V a2, V a3);
static V S2604(void);
static V W_Chk_dP_ddecl_dgo(V *a);
static V F_Chk_dP_dfail(V a1);
static V L2605(V *a);
static V L2606(V *a);
static V S2607(void);
static V W_Chk_dP_dfail(V *a);
static V F_Chk_dP_dthrow(V a1);
static V L2608(V *a);
static V W_Chk_dP_dthrow(V *a);
static V F_Chk_dP_dfail_dgo(V a0, V a1);
static V S2611(void);
static V S2612(void);
static V S2613(void);
static V W_Chk_dP_dfail_dgo(V *a);
static V F_Chk_dPS_dsrc(V a0);
static V W_Chk_dPS_dsrc(V *a);
static V F_Chk_dPS_dcur(V a0);
static V W_Chk_dPS_dcur(V *a);
static V F_Chk_dCur_dpos(V a0);
static V W_Chk_dCur_dpos(V *a);
static V F_Chk_dCur_dpeek(V a0);
static V W_Chk_dCur_dpeek(V *a);
static V F_Chk_dP_dgo(V a2, V a3);
static V W_Chk_dP_dgo(V *a);
static V F_Chk_dP_dgo_ddone(V a2, V a3);
static V W_Chk_dP_dgo_ddone(V *a);
static V F_Chk_dP_dlaw(void);
static V S2620(void);
static V L2621(V *a);
static V L2622(V *a);
static V L2623(V *a);
static V L2624(V *a);
static V S2625(void);
static V L2626(V *a);
static V L2627(V *a);
static V L2628(V *a);
static V L2629(V *a);
static V L2630(V *a);
static V L2631(V *a);
static V W_Chk_dP_dlaw(V *a);
static V F_Chk_dP_dlaw_dfin(V a0, V a1, V a2, V a3);
static V W_Chk_dP_dlaw_dfin(V *a);
static V F_Chk_dLC_dbind(V a0, V a1);
static V W_Chk_dLC_dbind(V *a);
static V F_Chk_dLC_dbind_done(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2636(void);
static V W_Chk_dLC_dbind_done(V *a);
static V F_Chk_dhigher0(V a0, V a1);
static V W_Chk_dhigher0(V *a);
static V F_Chk_dLC_dfirst__exs(V a0);
static V W_Chk_dLC_dfirst__exs(V *a);
static V F_Chk_dbook__push(V a0, V a1);
static V W_Chk_dbook__push(V *a);
static V F_Chk_dP_dset__book(V a0);
static V L2639(V *a);
static V W_Chk_dP_dset__book(V *a);
static V F_Chk_dPS_dset__book(V a0, V a1);
static V W_Chk_dPS_dset__book(V *a);
static V F_Chk_dP_dbook(void);
static V L2641(V *a);
static V W_Chk_dP_dbook(V *a);
static V F_Chk_dPS_dbook(V a0);
static V W_Chk_dPS_dbook(V *a);
static V F_Chk_dP_dbind(V a2, V a3);
static V L2643(V *a);
static V W_Chk_dP_dbind(V *a);
static V F_Chk_dP_dclose(V a0);
static V L2644(V *a);
static V W_Chk_dP_dclose(V *a);
static V F_Chk_dP_dclose_dgo(V a0, V a1);
static V W_Chk_dP_dclose_dgo(V *a);
static V F_Chk_dSB_ddrop(V a0, V a1);
static V W_Chk_dSB_ddrop(V *a);
static V F_Chk_dP_dblock(void);
static V L2648(V *a);
static V L2649(V *a);
static V L2650(V *a);
static V W_Chk_dP_dblock(V *a);
static V F_Chk_dP_dflatten(V a0, V a1);
static V W_Chk_dP_dflatten(V *a);
static V F_Chk_dP_dmatch__flatten(V a0, V a1, V a2, V a3);
static V S2654(void);
static V W_Chk_dP_dmatch__flatten(V *a);
static V F_Chk_dP_dmf_dvars(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dP_dmf_dvars(V *a);
static V F_Chk_dTm_dvar__i(V a0);
static V W_Chk_dTm_dvar__i(V *a);
static V F_Chk_dvars_dfind(V a0, V a1);
static V W_Chk_dvars_dfind(V *a);
static V F_Chk_dP_dmf_dcol(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Chk_dP_dmf_dcol(V *a);
static V F_Chk_dP_dmf_dskip(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2659(V *a);
static V W_Chk_dP_dmf_dskip(V *a);
static V F_Chk_dflatten_dlams(V a0, V a1);
static V W_Chk_dflatten_dlams(V *a);
static V F_Chk_dP_dpure(V a1);
static V L2661(V *a);
static V W_Chk_dP_dpure(V *a);
static V F_Chk_drows_dctr(V a0);
static V W_Chk_drows_dctr(V *a);
static V F_Chk_dP_dmf_dcol_dvar(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V W_Chk_dP_dmf_dcol_dvar(V *a);
static V F_Chk_dP_dmf_dctr(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2667(V *a);
static V L2668(V *a);
static V L2669(V *a);
static V L2670(V *a);
static V L2671(V *a);
static V W_Chk_dP_dmf_dctr(V *a);
static V F_Chk_dmf_dothers(V a0, V a1);
static V W_Chk_dmf_dothers(V *a);
static V F_Chk_dmf_dothers_dif(V a0, V a1, V a2);
static V W_Chk_dmf_dothers_dif(V *a);
static V F_Chk_dmf_drows(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dmf_drows(V *a);
static V F_Chk_dPt_di(V a0);
static V W_Chk_dPt_di(V *a);
static V F_Chk_dbody__sub(V a0, V a1, V a2);
static V W_Chk_dbody__sub(V *a);
static V F_Chk_dbody__sub_dscruts(V a0, V a1, V a2);
static V W_Chk_dbody__sub_dscruts(V *a);
static V F_Chk_dbody__sub_dscrut(V a0, V a1, V a2);
static V W_Chk_dbody__sub_dscrut(V *a);
static V F_Chk_dbody__sub_drows(V a0, V a1, V a2);
static V W_Chk_dbody__sub_drows(V *a);
static V F_Chk_dmf_drows_dctr(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9);
static V W_Chk_dmf_drows_dctr(V *a);
static V F_Chk_dPt_ds(V a0);
static V W_Chk_dPt_ds(V *a);
static V F_Chk_dP_dmf_dfields(V a0, V a1);
static V L2683(V *a);
static V L2684(V *a);
static V L2685(V *a);
static V S2686(void);
static V W_Chk_dP_dmf_dfields(V *a);
static V F_Chk_dP_dfresh__id(void);
static V L2687(V *a);
static V W_Chk_dP_dfresh__id(V *a);
static V F_Chk_dP_dfresh__id_dgo(V a0);
static V W_Chk_dP_dfresh__id_dgo(V *a);
static V F_Chk_dPt_dvar__q(V a0);
static V W_Chk_dPt_dvar__q(V *a);
static V F_Chk_dpatt__mark(V a0, V a1);
static V W_Chk_dpatt__mark(V *a);
static V F_Chk_dPt_dsame(V a0, V a1);
static V W_Chk_dPt_dsame(V *a);
static V F_Chk_dP_dif(V a1, V a2, V a3);
static V W_Chk_dP_dif(V *a);
static V F_Chk_dP_dmf_dvarcol(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2693(V *a);
static V W_Chk_dP_dmf_dvarcol(V *a);
static V F_Chk_dvars_dreplace(V a0, V a1);
static V W_Chk_dvars_dreplace(V *a);
static V F_Chk_dP_dmf_dvarrows(V a0, V a1);
static V L2696(V *a);
static V S2697(void);
static V W_Chk_dP_dmf_dvarrows(V *a);
static V F_Chk_dPt_dwith__q(V a0, V a1);
static V W_Chk_dPt_dwith__q(V *a);
static V F_Chk_dTm_dstrip__subs(V a0);
static V W_Chk_dTm_dstrip__subs(V *a);
static V F_Chk_dP_dmf_dbad(V a0, V a1);
static V S2701(void);
static V S2702(void);
static V S2703(void);
static V S2704(void);
static V S2705(void);
static V W_Chk_dP_dmf_dbad(V *a);
static V F_Chk_dP_dflatten_dlocal(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dP_dflatten_dlocal(V *a);
static V F_Chk_dP_dflatten_dlet(V a0, V a1, V a2, V a3, V a4);
static V L2707(V *a);
static V L2708(V *a);
static V S2709(void);
static V W_Chk_dP_dflatten_dlet(V *a);
static V F_Chk_dPt_dqs(V a0, V a1);
static V W_Chk_dPt_dqs(V *a);
static V F_Chk_dPt_dq(V a0);
static V W_Chk_dPt_dq(V *a);
static V F_Chk_dPt_dis(V a0);
static V W_Chk_dPt_dis(V *a);
static V F_Chk_dPt_dks(V a0);
static V W_Chk_dPt_dks(V *a);
static V F_Chk_dPt_dk(V a0);
static V W_Chk_dPt_dk(V *a);
static V F_Chk_dP_dflatten_dstrip(V a0, V a1);
static V S2717(void);
static V W_Chk_dP_dflatten_dstrip(V *a);
static V F_Chk_dP_dbody(V a0);
static V L2718(V *a);
static V L2719(V *a);
static V L2720(V *a);
static V S2721(void);
static V L2722(V *a);
static V W_Chk_dP_dbody(V *a);
static V F_Chk_dP_dbody_dlocal(V a0, V a1, V a2);
static V S2723(void);
static V L2724(V *a);
static V L2725(V *a);
static V L2726(V *a);
static V L2727(V *a);
static V L2728(V *a);
static V L2729(V *a);
static V S2730(void);
static V L2731(V *a);
static V L2732(V *a);
static V L2733(V *a);
static V S2734(void);
static V L2735(V *a);
static V L2736(V *a);
static V S2737(void);
static V L2738(V *a);
static V W_Chk_dP_dbody_dlocal(V *a);
static V F_Chk_dP_dbody_dlocal_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Chk_dP_dbody_dlocal_dgo(V *a);
static V F_Chk_dP_dbody_dlet(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2741(V *a);
static V L2742(V *a);
static V L2743(V *a);
static V S2744(void);
static V L2745(V *a);
static V L2746(V *a);
static V L2747(V *a);
static V L2748(V *a);
static V L2749(V *a);
static V W_Chk_dP_dbody_dlet(V *a);
static V F_Chk_dP_dbody_dbinders(V a0, V a1);
static V S2751(void);
static V L2752(V *a);
static V L2753(V *a);
static V L2754(V *a);
static V W_Chk_dP_dbody_dbinders(V *a);
static V F_Chk_dP_dpatt(V a0);
static V L2756(V *a);
static V W_Chk_dP_dpatt(V *a);
static V F_Chk_dTm_dis__var(V a0);
static V W_Chk_dTm_dis__var(V *a);
static V F_Chk_dP_dpatt_dvar(V a0, V a1);
static V L2759(V *a);
static V L2760(V *a);
static V W_Chk_dP_dpatt_dvar(V *a);
static V F_Chk_dP_dpatt_dother(V a0);
static V L2761(V *a);
static V S2762(void);
static V W_Chk_dP_dpatt_dother(V *a);
static V F_Chk_dP_dpatt_dvar_dgo(V a0, V a1);
static V S2764(void);
static V S2765(void);
static V S2766(void);
static V W_Chk_dP_dpatt_dvar_dgo(V *a);
static V F_Chk_dP_dbinder(V a0);
static V S2768(void);
static V W_Chk_dP_dbinder(V *a);
static V F_Chk_dP_dbinder_dgo(V a0, V a1, V a2);
static V L2769(V *a);
static V W_Chk_dP_dbinder_dgo(V *a);
static V F_Chk_dP_dopen(V a0);
static V L2770(V *a);
static V W_Chk_dP_dopen(V *a);
static V F_Chk_dP_dopen_dgo(V a0, V a1);
static V S2772(void);
static V W_Chk_dP_dopen_dgo(V *a);
static V F_Chk_dPS_dopened(V a0, V a1, V a2, V a3);
static V W_Chk_dPS_dopened(V *a);
static V F_Chk_dPS_dpush(V a0, V a1);
static V W_Chk_dPS_dpush(V *a);
static V F_Chk_dP_dreso(V a0);
static V L2775(V *a);
static V W_Chk_dP_dreso(V *a);
static V F_Chk_dPS_dreso(V a0, V a1);
static V W_Chk_dPS_dreso(V *a);
static V F_Chk_dPS_dal(V a0);
static V W_Chk_dPS_dal(V *a);
static V F_Chk_dPS_dqual(V a0, V a1);
static V S2779(void);
static V W_Chk_dPS_dqual(V *a);
static V F_Chk_dPS_dns(V a0);
static V W_Chk_dPS_dns(V *a);
static V F_Chk_dPS_dreso_dalias(V a0, V a1, V a2, V a3);
static V W_Chk_dPS_dreso_dalias(V *a);
static V F_Chk_dStr_dfirst__dot(V a0);
static V W_Chk_dStr_dfirst__dot(V *a);
static V F_Chk_dlit__full(V a0);
static V W_Chk_dlit__full(V *a);
static V F_Chk_dnat__full(V a0, V a1);
static V S2786(void);
static V S2787(void);
static V W_Chk_dnat__full(V *a);
static V F_Chk_dStr_dcodes(V a0);
static V W_Chk_dStr_dcodes(V *a);
static V F_Chk_dlit__chain(V a0, V a1);
static V S2790(void);
static V S2791(void);
static V W_Chk_dlit__chain(V *a);
static V F_Chk_dP_dpatt_dctr(V a0, V a1, V a2, V a3);
static V S2793(void);
static V S2794(void);
static V W_Chk_dP_dpatt_dctr(V *a);
static V F_Chk_dP_dpatt_dctr_dn(V a0, V a1, V a2, V a3, V a4);
static V S2796(void);
static V S2797(void);
static V S2798(void);
static V S2799(void);
static V L2800(V *a);
static V W_Chk_dP_dpatt_dctr_dn(V *a);
static V F_Chk_dP_dpatts(V a0);
static V L2802(V *a);
static V L2803(V *a);
static V W_Chk_dP_dpatts(V *a);
static V F_Chk_dP_dstn(void);
static V L2804(V *a);
static V W_Chk_dP_dstn(V *a);
static V F_Chk_dPS_dstn(V a0);
static V W_Chk_dPS_dstn(V *a);
static V F_Chk_dP_dtake(V a0);
static V L2806(V *a);
static V W_Chk_dP_dtake(V *a);
static V F_Chk_dP_dtake_dif(V a0, V a1);
static V L2808(V *a);
static V W_Chk_dP_dtake_dif(V *a);
static V F_Chk_dCur_dsteps(V a0, V a1);
static V W_Chk_dCur_dsteps(V *a);
static V F_Chk_dCur_dstep(V a0);
static V W_Chk_dCur_dstep(V *a);
static V F_Chk_dCur_dstep_dgo(V a0, V a1, V a2, V a3);
static V W_Chk_dCur_dstep_dgo(V *a);
static V F_Chk_dPS_dset__cur(V a0, V a1);
static V W_Chk_dPS_dset__cur(V *a);
static V F_Chk_dP_dat(V a0);
static V L2813(V *a);
static V W_Chk_dP_dat(V *a);
static V F_Chk_dCur_drest(V a0);
static V W_Chk_dCur_drest(V *a);
static V F_Chk_dStr_dprefix(V a0, V a1);
static V W_Chk_dStr_dprefix(V *a);
static V F_Chk_dP_dskip(void);
static V L2815(V *a);
static V W_Chk_dP_dskip(V *a);
static V F_Chk_dCur_dskip(V a0);
static V W_Chk_dCur_dskip(V *a);
static V F_Chk_dCur_dskip_dgo(V a0, V a1);
static V W_Chk_dCur_dskip_dgo(V *a);
static V F_Chk_dCur_dskip_dc(V a0, V a1);
static V W_Chk_dCur_dskip_dc(V *a);
static V F_Chk_dCur_dline(V a0);
static V W_Chk_dCur_dline(V *a);
static V F_Chk_dCur_dline_dgo(V a0, V a1);
static V W_Chk_dCur_dline_dgo(V *a);
static V F_Chk_dCur_dline_dc(V a0, V a1);
static V W_Chk_dCur_dline_dc(V *a);
static V F_Chk_dP_dbody_dvals(V a0, V a1);
static V W_Chk_dP_dbody_dvals(V *a);
static V F_Chk_dP_dbody_dvals_dmore(V a0, V a1);
static V L2818(V *a);
static V W_Chk_dP_dbody_dvals_dmore(V *a);
static V F_Chk_dP_dterm0(void);
static V W_Chk_dP_dterm0(V *a);
static V F_Chk_dP_dterm(V a0);
static V L2819(V *a);
static V L2820(V *a);
static V L2821(V *a);
static V L2822(V *a);
static V W_Chk_dP_dterm(V *a);
static V F_Chk_dTm_dspanned(V a0, V a1);
static V W_Chk_dTm_dspanned(V *a);
static V F_Chk_dP_dops(V a0, V a1);
static V L2824(V *a);
static V L2825(V *a);
static V L2826(V *a);
static V L2827(V *a);
static V S2829(void);
static V S2830(void);
static V S2832(void);
static V S2833(void);
static V S2834(void);
static V S2835(void);
static V S2836(void);
static V W_Chk_dP_dops(V *a);
static V F_Chk_dops_dlt(V a0, V a1, V a2);
static V S2838(void);
static V S2839(void);
static V W_Chk_dops_dlt(V *a);
static V F_Chk_dStr_dsecond(V a0);
static V W_Chk_dStr_dsecond(V *a);
static V F_Chk_dP_dops_dgo(V a0, V a1, V a2, V a3, V a4);
static V S2842(void);
static V W_Chk_dP_dops_dgo(V *a);
static V F_Chk_dOPS(void);
static V S2843(void);
static V S2844(void);
static V S2845(void);
static V S2846(void);
static V S2847(void);
static V S2848(void);
static V S2849(void);
static V S2850(void);
static V S2851(void);
static V S2852(void);
static V S2853(void);
static V S2854(void);
static V S2855(void);
static V S2856(void);
static V S2857(void);
static V S2858(void);
static V S2859(void);
static V S2860(void);
static V S2861(void);
static V S2862(void);
static V S2863(void);
static V S2864(void);
static V S2865(void);
static V S2866(void);
static V S2867(void);
static V S2868(void);
static V S2869(void);
static V S2870(void);
static V S2871(void);
static V S2872(void);
static V S2873(void);
static V S2874(void);
static V S2875(void);
static V S2876(void);
static V S2877(void);
static V S2878(void);
static V S2879(void);
static V S2880(void);
static V W_Chk_dOPS(V *a);
static V F_Chk_dop_dfind(V a0, V a1, V a2);
static V W_Chk_dop_dfind(V *a);
static V F_Chk_dop_dok(V a0, V a1, V a2);
static V S2884(void);
static V S2885(void);
static V S2886(void);
static V W_Chk_dop_dok(V *a);
static V F_Chk_dop_dfind_dif(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dop_dfind_dif(V *a);
static V F_Chk_dP_dinfix(V a0, V a1, V a2, V a3);
static V W_Chk_dP_dinfix(V *a);
static V F_Chk_dP_dinfix_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2889(V *a);
static V L2890(V *a);
static V L2891(V *a);
static V L2892(V *a);
static V L2893(V *a);
static V W_Chk_dP_dinfix_dgo(V *a);
static V F_Chk_dinfix_dbuild(V a0, V a1, V a2, V a3, V a4, V a5);
static V S2894(void);
static V S2895(void);
static V S2896(void);
static V S2897(void);
static V S2898(void);
static V S2899(void);
static V W_Chk_dinfix_dbuild(V *a);
static V F_Chk_dspan_dgrow(V a0);
static V W_Chk_dspan_dgrow(V *a);
static V F_Chk_dP_dspan_dfrom(V a0);
static V W_Chk_dP_dspan_dfrom(V *a);
static V F_Chk_dP_dspan(V a0);
static V L2901(V *a);
static V W_Chk_dP_dspan(V *a);
static V F_Chk_dP_dpos(void);
static V L2902(V *a);
static V W_Chk_dP_dpos(V *a);
static V F_Chk_dP_dminq(V a0, V a1);
static V S2903(void);
static V L2904(V *a);
static V L2905(V *a);
static V L2906(V *a);
static V W_Chk_dP_dminq(V *a);
static V F_Chk_dP_darrow(V a0, V a1);
static V S2907(void);
static V L2908(V *a);
static V L2909(V *a);
static V L2910(V *a);
static V S2911(void);
static V L2912(V *a);
static V S2913(void);
static V W_Chk_dP_darrow(V *a);
static V F_Chk_dP_dlam(V a0, V a1);
static V S2914(void);
static V L2915(V *a);
static V L2916(V *a);
static V L2917(V *a);
static V L2918(V *a);
static V L2919(V *a);
static V W_Chk_dP_dlam(V *a);
static V F_Chk_dlam_dbuild(V a0, V a1);
static V W_Chk_dlam_dbuild(V *a);
static V F_Chk_dP_dlt(V a0, V a1);
static V L2921(V *a);
static V L2922(V *a);
static V L2923(V *a);
static V L2924(V *a);
static V L2925(V *a);
static V L2926(V *a);
static V S2927(void);
static V L2928(V *a);
static V S2929(void);
static V L2930(V *a);
static V S2931(void);
static V W_Chk_dP_dlt(V *a);
static V F_Chk_dP_dlt_dadt(V a0, V a1, V a2, V a3);
static V S2932(void);
static V W_Chk_dP_dlt_dadt(V *a);
static V F_Chk_dP_dlt_dadt_dgo(V a0, V a1, V a2, V a3);
static V S2933(void);
static V L2934(V *a);
static V L2935(V *a);
static V S2936(void);
static V L2937(V *a);
static V L2938(V *a);
static V W_Chk_dP_dlt_dadt_dgo(V *a);
static V F_Chk_dP_dfill(V a0, V a1, V a2);
static V L2939(V *a);
static V W_Chk_dP_dfill(V *a);
static V F_Chk_dTld_dadt__fill(V a0, V a1);
static V W_Chk_dTld_dadt__fill(V *a);
static V F_Chk_dfill_dgo(V a0, V a1, V a2);
static V W_Chk_dfill_dgo(V *a);
static V F_Chk_dList_drepeat__tm(V a0, V a1);
static V W_Chk_dList_drepeat__tm(V *a);
static V F_Chk_dP_dargs(V a0);
static V L2943(V *a);
static V L2944(V *a);
static V W_Chk_dP_dargs(V *a);
static V F_Chk_dP_dargs_done(V a0);
static V L2945(V *a);
static V L2946(V *a);
static V S2947(void);
static V L2948(V *a);
static V L2949(V *a);
static V W_Chk_dP_dargs_done(V *a);
static V F_Chk_dTm_dis__ref(V a0);
static V W_Chk_dTm_dis__ref(V *a);
static V F_Chk_dP_dbump(void);
static V L2951(V *a);
static V W_Chk_dP_dbump(V *a);
static V F_Chk_dP_dindex(V a0, V a1);
static V L2952(V *a);
static V L2953(V *a);
static V S2954(void);
static V L2955(V *a);
static V L2956(V *a);
static V S2957(void);
static V L2958(V *a);
static V L2959(V *a);
static V L2960(V *a);
static V S2961(void);
static V L2962(V *a);
static V S2963(void);
static V S2964(void);
static V W_Chk_dP_dindex(V *a);
static V F_Chk_dP_dindex_dset(V a0, V a1, V a2, V a3);
static V L2965(V *a);
static V S2966(void);
static V S2967(void);
static V W_Chk_dP_dindex_dset(V *a);
static V F_Chk_dapps(V a0, V a1, V a2);
static V W_Chk_dapps(V *a);
static V F_Chk_dP_dnl(void);
static V L2969(V *a);
static V W_Chk_dP_dnl(V *a);
static V F_Chk_dCur_dnl(V a0);
static V W_Chk_dCur_dnl(V *a);
static V F_Chk_dP_dns(V a0, V a1);
static V L2972(V *a);
static V W_Chk_dP_dns(V *a);
static V F_Chk_dP_dns_dapp(V a0, V a1);
static V S2975(void);
static V S2976(void);
static V S2977(void);
static V W_Chk_dP_dns_dapp(V *a);
static V F_Chk_dStr_dlast__dot(V a0);
static V W_Chk_dStr_dlast__dot(V *a);
static V F_Chk_dStr_dlast__dot_dgo(V a0, V a1, V a2);
static V W_Chk_dStr_dlast__dot_dgo(V *a);
static V F_Chk_dP_dns_dref(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2981(V *a);
static V W_Chk_dP_dns_dref(V *a);
static V F_Chk_dapps_dspan(V a0, V a1, V a2);
static V W_Chk_dapps_dspan(V *a);
static V F_Chk_dP_dns_dargs(V a0, V a1);
static V L2983(V *a);
static V L2984(V *a);
static V W_Chk_dP_dns_dargs(V *a);
static V F_Chk_dP_dns_dop(V a0, V a1, V a2, V a3, V a4, V a5);
static V S2986(void);
static V S2987(void);
static V W_Chk_dP_dns_dop(V *a);
static V F_Chk_dP_dns_dop_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2988(V *a);
static V L2989(V *a);
static V W_Chk_dP_dns_dop_dgo(V *a);
static V F_Chk_dP_deat(V a0);
static V L2990(V *a);
static V L2991(V *a);
static V W_Chk_dP_deat(V *a);
static V F_Chk_dP_deat_dif(V a0, V a1);
static V S2993(void);
static V S2994(void);
static V W_Chk_dP_deat_dif(V *a);
static V F_Chk_dP_dcall(V a0, V a1);
static V L2995(V *a);
static V S2996(void);
static V L2997(V *a);
static V W_Chk_dP_dcall(V *a);
static V F_Chk_dP_dcall_dargs(V a0, V a1);
static V L2998(V *a);
static V L2999(V *a);
static V S3000(void);
static V L3001(V *a);
static V L3002(V *a);
static V L3003(V *a);
static V S3004(void);
static V L3005(V *a);
static V L3006(V *a);
static V W_Chk_dP_dcall_dargs(V *a);
static V F_Chk_dP_dcall_dtmpl(V a0, V a1, V a2);
static V S3007(void);
static V L3008(V *a);
static V W_Chk_dP_dcall_dtmpl(V *a);
static V F_Chk_dP_dcall_dtmpl_done(V a0, V a1, V a2);
static V S3009(void);
static V S3010(void);
static V S3011(void);
static V W_Chk_dP_dcall_dtmpl_done(V *a);
static V F_Chk_dP_dcall_dtmpl_dgo(V a0, V a1, V a2);
static V L3012(V *a);
static V L3013(V *a);
static V L3014(V *a);
static V S3015(void);
static V L3016(V *a);
static V L3017(V *a);
static V W_Chk_dP_dcall_dtmpl_dgo(V *a);
static V F_Chk_dP_dcall_dbang(V a0, V a1);
static V S3018(void);
static V W_Chk_dP_dcall_dbang(V *a);
static V F_Chk_dP_dcall_dbang_dgo(V a0, V a1);
static V L3019(V *a);
static V W_Chk_dP_dcall_dbang_dgo(V *a);
static V F_Chk_dTm_dbang(V a0);
static V W_Chk_dTm_dbang(V *a);
static V F_Chk_dP_dcall_dhead(V a0);
static V W_Chk_dP_dcall_dhead(V *a);
static V F_Chk_dP_dcall_dhead_dvar(V a0, V a1, V a2);
static V L3022(V *a);
static V L3023(V *a);
static V W_Chk_dP_dcall_dhead_dvar(V *a);
static V F_Chk_dP_dlookup(V a0);
static V L3024(V *a);
static V W_Chk_dP_dlookup(V *a);
static V F_Chk_dPS_dstk(V a0);
static V W_Chk_dPS_dstk(V *a);
static V F_Chk_dSB_dfind(V a0, V a1);
static V W_Chk_dSB_dfind(V *a);
static V F_Chk_dSB_dfind_dif(V a0, V a1, V a2, V a3);
static V W_Chk_dSB_dfind_dif(V *a);
static V F_Chk_dP_dprev(void);
static V L3028(V *a);
static V W_Chk_dP_dprev(V *a);
static V F_Chk_dCur_dprev(V a0);
static V W_Chk_dCur_dprev(V *a);
static V F_Chk_dP_dpeek__rest(void);
static V L3030(V *a);
static V W_Chk_dP_dpeek__rest(V *a);
static V F_Chk_dP_dbase(V a0);
static V L3031(V *a);
static V W_Chk_dP_dbase(V *a);
static V F_Chk_dP_dbase_dgo(V a0, V a1, V a2);
static V L3033(V *a);
static V W_Chk_dP_dbase_dgo(V *a);
static V F_Chk_dP_dbase_dsym(V a0, V a1);
static V S3034(void);
static V S3035(void);
static V S3036(void);
static V S3037(void);
static V S3038(void);
static V S3039(void);
static V S3040(void);
static V S3041(void);
static V S3042(void);
static V S3043(void);
static V S3044(void);
static V W_Chk_dP_dbase_dsym(V *a);
static V F_Chk_dP_dbase_dsym_dgo(V a0, V a1, V a2);
static V L3046(V *a);
static V L3047(V *a);
static V S3048(void);
static V W_Chk_dP_dbase_dsym_dgo(V *a);
static V F_Chk_dP_dhole(V a0);
static V L3049(V *a);
static V L3050(V *a);
static V S3051(void);
static V L3052(V *a);
static V L3053(V *a);
static V W_Chk_dP_dhole(V *a);
static V F_Chk_dP_dcount__hole(void);
static V L3054(V *a);
static V W_Chk_dP_dcount__hole(V *a);
static V F_Chk_dbook__hole(V a0);
static V W_Chk_dbook__hole(V *a);
static V F_Chk_dP_dname(void);
static V L3056(V *a);
static V W_Chk_dP_dname(V *a);
static V F_Chk_dP_dname_dcheck(V a0);
static V W_Chk_dP_dname_dcheck(V *a);
static V F_Chk_dKEYWORDS(void);
static V S3057(void);
static V S3058(void);
static V S3059(void);
static V S3060(void);
static V S3061(void);
static V S3062(void);
static V S3063(void);
static V S3064(void);
static V S3065(void);
static V S3066(void);
static V S3067(void);
static V S3068(void);
static V S3069(void);
static V S3070(void);
static V S3071(void);
static V S3072(void);
static V W_Chk_dKEYWORDS(V *a);
static V F_Chk_dP_dname_dcheck_dc(V a0, V a1);
static V S3074(void);
static V S3075(void);
static V W_Chk_dP_dname_dcheck_dc(V *a);
static V F_Chk_dP_dlexeme(void);
static V L3076(V *a);
static V L3077(V *a);
static V W_Chk_dP_dlexeme(V *a);
static V F_Chk_dP_dlexeme_dif(V a0, V a1);
static V S3079(void);
static V W_Chk_dP_dlexeme_dif(V *a);
static V F_Chk_dP_dlexeme_dgo(V a0);
static V S3080(void);
static V W_Chk_dP_dlexeme_dgo(V *a);
static V F_Chk_dCur_dname(V a0, V a1);
static V W_Chk_dCur_dname(V *a);
static V F_Chk_dCur_dname_dgo(V a0, V a1, V a2);
static V W_Chk_dCur_dname_dgo(V *a);
static V F_Chk_dis__name(V a0);
static V W_Chk_dis__name(V *a);
static V F_Chk_dCur_dname_dc(V a0, V a1, V a2, V a3);
static V W_Chk_dCur_dname_dc(V *a);
static V F_Chk_dP_dlexeme_dfin(V a0);
static V L3083(V *a);
static V W_Chk_dP_dlexeme_dfin(V *a);
static V F_Chk_dP_dlexeme_ddot(V a0);
static V S3084(void);
static V W_Chk_dP_dlexeme_ddot(V *a);
static V F_Chk_dP_dlexeme_ddot_dc(V a0, V a1);
static V S3086(void);
static V W_Chk_dP_dlexeme_ddot_dc(V *a);
static V F_Chk_dP_dset__cur(V a0);
static V L3087(V *a);
static V W_Chk_dP_dset__cur(V *a);
static V F_Chk_dP_dcur(void);
static V L3088(V *a);
static V W_Chk_dP_dcur(V *a);
static V F_Chk_dP_dstr__lit(V a0);
static V L3089(V *a);
static V L3090(V *a);
static V L3091(V *a);
static V W_Chk_dP_dstr__lit(V *a);
static V F_Chk_dlit__of(V a0, V a1);
static V W_Chk_dlit__of(V *a);
static V F_Chk_dStr_dfrom__codes(V a0);
static V W_Chk_dStr_dfrom__codes(V *a);
static V F_Chk_dcodes_dplain(V a0);
static V W_Chk_dcodes_dplain(V *a);
static V F_Chk_dP_dstr_dgo(V a0);
static V S3094(void);
static V L3095(V *a);
static V L3096(V *a);
static V S3097(void);
static V W_Chk_dP_dstr_dgo(V *a);
static V F_Chk_dP_dstr_dmore(V a0);
static V L3098(V *a);
static V W_Chk_dP_dstr_dmore(V *a);
static V F_Chk_dP_dchar(void);
static V S3099(void);
static V L3100(V *a);
static V W_Chk_dP_dchar(V *a);
static V F_Chk_dP_dchar_dplain(void);
static V L3101(V *a);
static V S3102(void);
static V W_Chk_dP_dchar_dplain(V *a);
static V F_Chk_dP_dchar_dtake(V a0);
static V L3103(V *a);
static V W_Chk_dP_dchar_dtake(V *a);
static V F_Chk_dP_dpeek(void);
static V L3104(V *a);
static V W_Chk_dP_dpeek(V *a);
static V F_Chk_dP_descape(void);
static V L3105(V *a);
static V W_Chk_dP_descape(V *a);
static V F_Chk_duesc(V a0);
static V W_Chk_duesc(V *a);
static V F_Chk_duesc_dif(V a0, V a1);
static V W_Chk_duesc_dif(V *a);
static V F_Chk_duesc_dhex(V a0, V a1, V a2);
static V W_Chk_duesc_dhex(V *a);
static V F_Chk_dis__hex(V a0);
static V W_Chk_dis__hex(V *a);
static V F_Chk_duesc_dhex_dif(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Chk_duesc_dhex_dif(V *a);
static V F_Chk_dhex__val(V a0);
static V W_Chk_dhex__val(V *a);
static V F_Chk_dP_descape_du(V a0);
static V L3112(V *a);
static V L3113(V *a);
static V W_Chk_dP_descape_du(V *a);
static V F_Chk_dESCAPES(void);
static V W_Chk_dESCAPES(V *a);
static V F_Chk_descape_dfind(V a0, V a1);
static V W_Chk_descape_dfind(V *a);
static V F_Chk_descape_dfind_dif(V a0, V a1, V a2, V a3);
static V W_Chk_descape_dfind_dif(V *a);
static V F_Chk_dP_descape_dnamed(V a0);
static V S3117(void);
static V W_Chk_dP_descape_dnamed(V *a);
static V F_Chk_dP_descape_du_dgo(V a0);
static V L3120(V *a);
static V W_Chk_dP_descape_du_dgo(V *a);
static V F_Chk_dP_dchr__lit(V a0);
static V L3121(V *a);
static V L3122(V *a);
static V S3123(void);
static V L3124(V *a);
static V W_Chk_dP_dchr__lit(V *a);
static V F_Chk_dP_dchr__lit_dfin(V a0, V a1, V a2);
static V L3126(V *a);
static V S3127(void);
static V S3128(void);
static V W_Chk_dP_dchr__lit_dfin(V *a);
static V F_Chk_dP_dbrack(V a0);
static V L3129(V *a);
static V L3130(V *a);
static V S3131(void);
static V L3132(V *a);
static V W_Chk_dP_dbrack(V *a);
static V F_Chk_dP_dbrack_dfirst(V a0);
static V L3133(V *a);
static V L3134(V *a);
static V S3135(void);
static V L3136(V *a);
static V W_Chk_dP_dbrack_dfirst(V *a);
static V F_Chk_dP_dbrack_dlist(V a0, V a1);
static V S3137(void);
static V L3138(V *a);
static V S3139(void);
static V L3140(V *a);
static V L3141(V *a);
static V W_Chk_dP_dbrack_dlist(V *a);
static V F_Chk_dlist_dbuild(V a0, V a1);
static V S3143(void);
static V S3144(void);
static V W_Chk_dlist_dbuild(V *a);
static V F_Chk_dP_dbrack_darr(V a0, V a1);
static V L3145(V *a);
static V L3146(V *a);
static V S3147(void);
static V L3148(V *a);
static V S3149(void);
static V L3150(V *a);
static V L3151(V *a);
static V S3152(void);
static V L3153(V *a);
static V L3154(V *a);
static V L3155(V *a);
static V L3156(V *a);
static V S3157(void);
static V W_Chk_dP_dbrack_darr(V *a);
static V F_Chk_dP_dbrack_ddepth(V a0, V a1);
static V W_Chk_dP_dbrack_ddepth(V *a);
static V F_Chk_dP_dbrack_dlog2(V a0, V a1);
static V S3160(void);
static V W_Chk_dP_dbrack_dlog2(V *a);
static V F_Chk_dNat_dlog2__exact(V a0);
static V W_Chk_dNat_dlog2__exact(V *a);
static V F_Chk_dNat_dlog2__exact_dgo(V a0, V a1, V a2);
static V W_Chk_dNat_dlog2__exact_dgo(V *a);
static V W_Nat_dcmp(V *a);
static V F_Chk_dNat_dlog2__exact_dcmp(V a0, V a1, V a2, V a3);
static V W_Chk_dNat_dlog2__exact_dcmp(V *a);
static V W_Nat_ddouble(V *a);
static V F_Chk_dP_dbrack_dlog2_dgo(V a0, V a1, V a2);
static V S3163(void);
static V W_Chk_dP_dbrack_dlog2_dgo(V *a);
static V F_Chk_dP_dtup(V a0);
static V L3164(V *a);
static V L3165(V *a);
static V L3166(V *a);
static V L3167(V *a);
static V L3168(V *a);
static V S3169(void);
static V L3170(V *a);
static V W_Chk_dP_dtup(V *a);
static V F_Chk_dP_dtup_dend(V a0);
static V L3171(V *a);
static V S3172(void);
static V L3173(V *a);
static V L3174(V *a);
static V S3175(void);
static V L3176(V *a);
static V W_Chk_dP_dtup_dend(V *a);
static V F_Chk_dP_dtup_dann(V a0);
static V L3177(V *a);
static V W_Chk_dP_dtup_dann(V *a);
static V F_Chk_dP_dtup_dmore(V a0, V a1);
static V L3178(V *a);
static V L3179(V *a);
static V S3180(void);
static V W_Chk_dP_dtup_dmore(V *a);
static V F_Chk_dBody_dreply__x(V a0);
static V W_Chk_dBody_dreply__x(V *a);
static V F_Chk_dBody_dis__reply(V a0);
static V W_Chk_dBody_dis__reply(V *a);
static V F_Chk_dP_dcol(void);
static V L3183(V *a);
static V W_Chk_dP_dcol(V *a);
static V F_Chk_dCur_dcol(V a0);
static V W_Chk_dCur_dcol(V *a);
static V F_Chk_dP_dbrace(V a0);
static V L3185(V *a);
static V L3186(V *a);
static V S3187(void);
static V L3188(V *a);
static V W_Chk_dP_dbrace(V *a);
static V F_Chk_dP_dbrace_dterm(V a0);
static V L3189(V *a);
static V L3190(V *a);
static V S3191(void);
static V L3192(V *a);
static V S3193(void);
static V L3194(V *a);
static V W_Chk_dP_dbrace_dterm(V *a);
static V F_Chk_dP_dbrace_dgo(V a0, V a1, V a2, V a3);
static V L3197(V *a);
static V S3198(void);
static V L3199(V *a);
static V L3200(V *a);
static V S3201(void);
static V L3202(V *a);
static V L3203(V *a);
static V L3204(V *a);
static V L3205(V *a);
static V S3206(void);
static V L3207(V *a);
static V L3208(V *a);
static V S3209(void);
static V L3210(V *a);
static V L3211(V *a);
static V S3212(void);
static V L3213(V *a);
static V S3214(void);
static V S3215(void);
static V S3216(void);
static V L3217(V *a);
static V L3218(V *a);
static V S3219(void);
static V L3220(V *a);
static V W_Chk_dP_dbrace_dgo(V *a);
static V F_Chk_dP_dbrace_drfl(void);
static V S3221(void);
static V L3222(V *a);
static V W_Chk_dP_dbrace_drfl(V *a);
static V F_Chk_dP_drwt(V a0);
static V L3223(V *a);
static V L3224(V *a);
static V L3225(V *a);
static V S3226(void);
static V L3227(V *a);
static V L3228(V *a);
static V W_Chk_dP_drwt(V *a);
static V F_Chk_dP_drwt_dgo(V a0, V a1, V a2);
static V S3231(void);
static V L3232(V *a);
static V L3233(V *a);
static V L3234(V *a);
static V S3235(void);
static V L3236(V *a);
static V L3237(V *a);
static V L3238(V *a);
static V L3239(V *a);
static V L3240(V *a);
static V S3241(void);
static V L3242(V *a);
static V L3243(V *a);
static V L3244(V *a);
static V S3245(void);
static V W_Chk_dP_drwt_dgo(V *a);
static V F_Chk_dP_dpush__scope(V a0);
static V L3246(V *a);
static V W_Chk_dP_dpush__scope(V *a);
static V F_Chk_dP_drwt_dname(V a0, V a1);
static V S3248(void);
static V S3249(void);
static V W_Chk_dP_drwt_dname(V *a);
static V F_Chk_dP_drwt_dnamed(V a0);
static V L3250(V *a);
static V W_Chk_dP_drwt_dnamed(V *a);
static V F_Chk_dP_darms(V a0);
static V L3251(V *a);
static V S3252(void);
static V L3253(V *a);
static V L3254(V *a);
static V L3255(V *a);
static V W_Chk_dP_darms(V *a);
static V F_Chk_dP_darms_dfin(V a0, V a1);
static V W_Chk_dP_darms_dfin(V *a);
static V F_Chk_darms_dbuild(V a0, V a1, V a2);
static V W_Chk_darms_dbuild(V *a);
static V F_Chk_dP_darms_dgo(V a0);
static V L3258(V *a);
static V S3259(void);
static V L3260(V *a);
static V W_Chk_dP_darms_dgo(V *a);
static V F_Chk_dP_darms_ditem(V a0);
static V L3261(V *a);
static V L3262(V *a);
static V L3263(V *a);
static V S3264(void);
static V L3265(V *a);
static V W_Chk_dP_darms_ditem(V *a);
static V F_Chk_dP_darms_dmore(V a0, V a1, V a2);
static V L3267(V *a);
static V L3268(V *a);
static V L3269(V *a);
static V S3270(void);
static V L3271(V *a);
static V L3272(V *a);
static V S3273(void);
static V L3274(V *a);
static V S3275(void);
static V L3276(V *a);
static V W_Chk_dP_darms_dmore(V *a);
static V F_Chk_dP_dplus(V a0);
static V L3277(V *a);
static V L3278(V *a);
static V L3279(V *a);
static V L3280(V *a);
static V L3281(V *a);
static V W_Chk_dP_dplus(V *a);
static V F_Chk_dTld_dadt__ng(V a0);
static V W_Chk_dTld_dadt__ng(V *a);
static V F_Chk_dP_dplus_dgo(V a0, V a1, V a2, V a3);
static V S3284(void);
static V W_Chk_dP_dplus_dgo(V *a);
static V F_Chk_dP_dplus_dadt(V a0, V a1, V a2, V a3);
static V S3288(void);
static V W_Chk_dP_dplus_dadt(V *a);
static V F_Chk_dP_dplus_dxs(V a0, V a1, V a2);
static V W_Chk_dP_dplus_dxs(V *a);
static V F_Chk_dplus_dargs(V a0, V a1);
static V W_Chk_dplus_dargs(V *a);
static V F_Chk_dTm_dis__adt(V a0);
static V W_Chk_dTm_dis__adt(V *a);
static V F_Chk_dP_dplus_dkey(V a0);
static V S3294(void);
static V W_Chk_dP_dplus_dkey(V *a);
static V F_Chk_dP_damp(V a0, V a1);
static V W_Chk_dP_damp(V *a);
static V F_Chk_damp_dcode(V a0);
static V W_Chk_damp_dcode(V *a);
static V F_Chk_dP_damp_dgo(V a0, V a1);
static V L3296(V *a);
static V L3297(V *a);
static V L3298(V *a);
static V W_Chk_dP_damp_dgo(V *a);
static V F_Chk_damp_dq(V a0);
static V W_Chk_damp_dq(V *a);
static V F_Chk_dP_dall(V a0);
static V L3300(V *a);
static V L3301(V *a);
static V L3302(V *a);
static V L3303(V *a);
static V S3304(void);
static V L3305(V *a);
static V L3306(V *a);
static V S3307(void);
static V L3308(V *a);
static V L3309(V *a);
static V L3310(V *a);
static V L3311(V *a);
static V L3312(V *a);
static V L3313(V *a);
static V W_Chk_dP_dall(V *a);
static V F_Chk_dall_dbuild(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S3315(void);
static V W_Chk_dall_dbuild(V *a);
static V F_Chk_dP_dquant(void);
static V L3316(V *a);
static V S3317(void);
static V L3318(V *a);
static V S3319(void);
static V L3320(V *a);
static V W_Chk_dP_dquant(V *a);
static V F_Chk_dP_dnum(void);
static V L3321(V *a);
static V L3322(V *a);
static V L3323(V *a);
static V L3324(V *a);
static V L3325(V *a);
static V L3326(V *a);
static V W_Chk_dP_dnum(V *a);
static V F_Chk_dnum_dkind(V a0);
static V W_Chk_dnum_dkind(V *a);
static V F_Chk_dP_dnum_dgo(V a0, V a1, V a2, V a3);
static V L3329(V *a);
static V L3330(V *a);
static V S3331(void);
static V S3332(void);
static V S3333(void);
static V L3334(V *a);
static V W_Chk_dP_dnum_dgo(V *a);
static V F_Chk_dP_dflt(V a0, V a1, V a2);
static V L3336(V *a);
static V L3337(V *a);
static V W_Chk_dP_dflt(V *a);
static V W_F32_dread(V *a);
static V F_Chk_dP_dflt_dgo(V a0, V a1, V a2);
static V S3339(void);
static V S3340(void);
static V S3341(void);
static V S3342(void);
static V S3343(void);
static V W_Chk_dP_dflt_dgo(V *a);
static V W_F32_dbits(V *a);
static V F_Chk_dF32_dis__finite(V a0);
static V W_Chk_dF32_dis__finite(V *a);
static V F_Chk_dP_dsteps(V a0);
static V L3345(V *a);
static V W_Chk_dP_dsteps(V *a);
static V F_Chk_dflt_dtext(V a0);
static V W_Chk_dflt_dtext(V *a);
static V F_Chk_dflt_dexp(V a0);
static V S3351(void);
static V W_Chk_dflt_dexp(V *a);
static V F_Chk_ddigits_dspan(V a0);
static V W_Chk_ddigits_dspan(V *a);
static V F_Chk_ddigits_dval(V a0, V a1, V a2);
static V W_Chk_ddigits_dval(V *a);
static V W_Nat_dmul(V *a);
static V F_Chk_dP_dnat(V a0, V a1, V a2);
static V S3355(void);
static V S3356(void);
static V W_Chk_dP_dnat(V *a);
static V F_Chk_dP_dnat_dgo(V a0, V a1);
static V S3357(void);
static V L3358(V *a);
static V W_Chk_dP_dnat_dgo(V *a);
static V F_Chk_dP_dnat_dlit(V a0, V a1);
static V L3359(V *a);
static V L3360(V *a);
static V S3361(void);
static V W_Chk_dP_dnat_dlit(V *a);
static V F_Chk_dP_dnat_dplus(V a0, V a1);
static V L3362(V *a);
static V L3363(V *a);
static V W_Chk_dP_dnat_dplus(V *a);
static V F_Chk_dnat_dplus(V a0, V a1, V a2);
static V W_Chk_dnat_dplus(V *a);
static V F_Chk_dnat_dplus_dbig(V a0, V a1, V a2);
static V S3365(void);
static V W_Chk_dnat_dplus_dbig(V *a);
static V F_Chk_dnat_dsuccs(V a0, V a1, V a2);
static V S3367(void);
static V W_Chk_dnat_dsuccs(V *a);
static V F_Chk_dP_dbase_dword(V a0, V a1);
static V S3368(void);
static V S3369(void);
static V S3370(void);
static V S3371(void);
static V S3372(void);
static V S3373(void);
static V S3374(void);
static V S3375(void);
static V W_Chk_dP_dbase_dword(V *a);
static V F_Chk_dP_dbase_dword_dgo(V a0, V a1, V a2);
static V L3377(V *a);
static V L3378(V *a);
static V L3379(V *a);
static V S3380(void);
static V L3381(V *a);
static V L3382(V *a);
static V S3383(void);
static V L3384(V *a);
static V L3385(V *a);
static V S3386(void);
static V S3387(void);
static V S3388(void);
static V S3389(void);
static V S3390(void);
static V W_Chk_dP_dbase_dword_dgo(V *a);
static V F_Chk_dP_dbase_dname(V a0, V a1);
static V S3391(void);
static V L3392(V *a);
static V W_Chk_dP_dbase_dname(V *a);
static V F_Chk_dP_dbase_dvar(V a0, V a1);
static V L3393(V *a);
static V W_Chk_dP_dbase_dvar(V *a);
static V F_Chk_dP_dvar(V a0, V a1);
static V L3394(V *a);
static V W_Chk_dP_dvar(V *a);
static V F_Chk_dP_dvar_dfound(V a0, V a1, V a2);
static V L3396(V *a);
static V W_Chk_dP_dvar_dfound(V *a);
static V F_Chk_dStr_dhas__dot(V a0);
static V W_Chk_dStr_dhas__dot(V *a);
static V F_Chk_dP_dvar_dfree(V a0, V a1, V a2, V a3);
static V L3399(V *a);
static V W_Chk_dP_dvar_dfree(V *a);
static V F_Chk_dP_dbase_dctor(V a0, V a1);
static V L3400(V *a);
static V S3401(void);
static V L3402(V *a);
static V L3403(V *a);
static V L3404(V *a);
static V W_Chk_dP_dbase_dctor(V *a);
static V F_Chk_dP_ddo(V a0);
static V L3405(V *a);
static V S3406(void);
static V L3407(V *a);
static V S3408(void);
static V L3409(V *a);
static V L3410(V *a);
static V L3411(V *a);
static V L3412(V *a);
static V S3413(void);
static V L3414(V *a);
static V L3415(V *a);
static V L3416(V *a);
static V W_Chk_dP_ddo(V *a);
static V F_Chk_dP_ddo__stmt(V a0, V a1, V a2);
static V L3417(V *a);
static V L3418(V *a);
static V S3419(void);
static V L3420(V *a);
static V W_Chk_dP_ddo__stmt(V *a);
static V F_Chk_dP_ddo__step(V a0, V a1, V a2, V a3);
static V L3421(V *a);
static V L3422(V *a);
static V S3423(void);
static V L3424(V *a);
static V L3425(V *a);
static V S3426(void);
static V L3427(V *a);
static V L3428(V *a);
static V S3429(void);
static V L3430(V *a);
static V S3431(void);
static V L3432(V *a);
static V W_Chk_dP_ddo__step(V *a);
static V F_Chk_dP_ddo__step_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V S3434(void);
static V L3435(V *a);
static V W_Chk_dP_ddo__step_dgo(V *a);
static V F_Chk_dP_ddo__arrow(V a0, V a1, V a2, V a3, V a4, V a5);
static V S3436(void);
static V L3437(V *a);
static V W_Chk_dP_ddo__arrow(V *a);
static V F_Chk_dP_ddo__last(V a0, V a1, V a2);
static V L3438(V *a);
static V L3439(V *a);
static V S3440(void);
static V L3441(V *a);
static V W_Chk_dP_ddo__last(V *a);
static V F_Chk_dP_ddocall(V a0, V a1, V a2, V a3, V a4, V a5);
static V L3442(V *a);
static V W_Chk_dP_ddocall(V *a);
static V F_Chk_ddo_dcall(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V W_Chk_ddo_dcall(V *a);
static V F_Chk_dList_dlast__tm(V a0);
static V W_Chk_dList_dlast__tm(V *a);
static V F_Chk_dList_dinit__tm(V a0);
static V W_Chk_dList_dinit__tm(V *a);
static V F_Chk_dP_ddo__bind(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V L3445(V *a);
static V L3446(V *a);
static V S3447(void);
static V L3448(V *a);
static V L3449(V *a);
static V L3450(V *a);
static V S3451(void);
static V L3452(V *a);
static V L3453(V *a);
static V L3454(V *a);
static V S3455(void);
static V W_Chk_dP_ddo__bind(V *a);
static V F_Chk_ddo_dlam(V a0, V a1, V a2);
static V W_Chk_ddo_dlam(V *a);
static V F_Chk_ddo_dlet(V a0, V a1, V a2, V a3);
static V W_Chk_ddo_dlet(V *a);
static V F_Chk_dP_dmore(V a0);
static V S3456(void);
static V L3457(V *a);
static V L3458(V *a);
static V L3459(V *a);
static V W_Chk_dP_dmore(V *a);
static V F_Chk_dP_ddo__ret(V a0, V a1, V a2);
static V L3460(V *a);
static V L3461(V *a);
static V S3462(void);
static V W_Chk_dP_ddo__ret(V *a);
static V F_Chk_dP_dword(V a0);
static V L3463(V *a);
static V W_Chk_dP_dword(V *a);
static V F_Chk_dP_dword_dif(V a0, V a1);
static V W_Chk_dP_dword_dif(V *a);
static V F_Chk_dP_dat__word(V a0);
static V L3465(V *a);
static V L3466(V *a);
static V W_Chk_dP_dat__word(V *a);
static V F_Chk_dP_dbody_dlet_deq(V a0, V a1);
static V S3467(void);
static V L3468(V *a);
static V W_Chk_dP_dbody_dlet_deq(V *a);
static V F_Chk_dP_dbody_dlet_dann(V a0, V a1);
static V L3470(V *a);
static V L3471(V *a);
static V W_Chk_dP_dbody_dlet_dann(V *a);
static V F_Chk_dP_dbody_dreply(V a0, V a1, V a2, V a3);
static V W_Chk_dP_dbody_dreply(V *a);
static V F_Chk_dterm__write(V a0);
static V W_Chk_dterm__write(V *a);
static V F_Chk_dterm__write_dgo(V a0);
static V W_Chk_dterm__write_dgo(V *a);
static V F_Chk_dP_dbody_dreply_dgo(V a0, V a1, V a2, V a3, V a4);
static V L3476(V *a);
static V L3477(V *a);
static V L3478(V *a);
static V W_Chk_dP_dbody_dreply_dgo(V *a);
static V F_Maybe_dis__none(V a2);
static V W_Maybe_dis__none(V *a);
static V F_Chk_dP_dbody_dty__ok(V a0, V a1, V a2);
static V L3481(V *a);
static V W_Chk_dP_dbody_dty__ok(V *a);
static V F_Chk_dP_dbody_dty(void);
static V L3482(V *a);
static V W_Chk_dP_dbody_dty(V *a);
static V F_Chk_dP_dlocal_dnames(V a0, V a1);
static V L3483(V *a);
static V L3484(V *a);
static V L3485(V *a);
static V L3486(V *a);
static V W_Chk_dP_dlocal_dnames(V *a);
static V F_Chk_dP_dlocal_dnames_dmore(V a0, V a1);
static V L3487(V *a);
static V L3488(V *a);
static V W_Chk_dP_dlocal_dnames_dmore(V *a);
static V F_Chk_dStr_dword__at(V a0);
static V S3490(void);
static V W_Chk_dStr_dword__at(V *a);
static V F_Chk_dStr_dword__at_dif(V a0, V a1, V a2);
static V S3492(void);
static V W_Chk_dStr_dword__at_dif(V *a);
static V F_Chk_dP_dbody_derased__name(V a0);
static V L3493(V *a);
static V L3494(V *a);
static V W_Chk_dP_dbody_derased__name(V *a);
static V F_Chk_dP_dbody_dmatch(V a0, V a1);
static V L3495(V *a);
static V L3496(V *a);
static V L3497(V *a);
static V L3498(V *a);
static V L3499(V *a);
static V W_Chk_dP_dbody_dmatch(V *a);
static V F_Chk_dP_drows(V a0, V a1, V a2);
static V S3500(void);
static V L3501(V *a);
static V L3502(V *a);
static V W_Chk_dP_drows(V *a);
static V F_Chk_dP_drow(V a0, V a1, V a2, V a3);
static V S3503(void);
static V L3504(V *a);
static V L3505(V *a);
static V S3506(void);
static V L3507(V *a);
static V L3508(V *a);
static V L3509(V *a);
static V L3510(V *a);
static V L3511(V *a);
static V L3512(V *a);
static V W_Chk_dP_drow(V *a);
static V F_Chk_dP_dterms(void);
static V L3513(V *a);
static V L3514(V *a);
static V S3515(void);
static V L3516(V *a);
static V W_Chk_dP_dterms(V *a);
static V F_Chk_dP_dterms_dmore(V a0);
static V S3517(void);
static V L3518(V *a);
static V L3519(V *a);
static V W_Chk_dP_dterms_dmore(V *a);
static V F_Chk_dP_dclauses(V a0, V a1);
static V S3520(void);
static V L3521(V *a);
static V S3522(void);
static V L3523(V *a);
static V W_Chk_dP_dclauses(V *a);
static V F_Chk_dP_dclause(V a0, V a1, V a2);
static V S3524(void);
static V S3525(void);
static V L3526(V *a);
static V L3527(V *a);
static V S3528(void);
static V L3529(V *a);
static V S3530(void);
static V L3531(V *a);
static V S3532(void);
static V L3533(V *a);
static V L3534(V *a);
static V L3535(V *a);
static V L3536(V *a);
static V L3537(V *a);
static V S3538(void);
static V L3539(V *a);
static V L3540(V *a);
static V S3541(void);
static V L3542(V *a);
static V L3543(V *a);
static V L3544(V *a);
static V W_Chk_dP_dclause(V *a);
static V F_Chk_dP_dclause_dwhere(V a0, V a1, V a2);
static V L3545(V *a);
static V S3546(void);
static V L3547(V *a);
static V L3548(V *a);
static V L3549(V *a);
static V L3550(V *a);
static V L3551(V *a);
static V L3552(V *a);
static V S3553(void);
static V W_Chk_dP_dclause_dwhere(V *a);
static V F_Chk_dP_dfresh(V a0);
static V L3554(V *a);
static V S3555(void);
static V S3556(void);
static V W_Chk_dP_dfresh(V *a);
static V F_Chk_dP_dqual(V a0);
static V L3557(V *a);
static V W_Chk_dP_dqual(V *a);
static V F_Chk_dP_dtype(void);
static V S3558(void);
static V L3559(V *a);
static V L3560(V *a);
static V L3561(V *a);
static V L3562(V *a);
static V L3563(V *a);
static V L3564(V *a);
static V S3565(void);
static V L3566(V *a);
static V S3567(void);
static V L3568(V *a);
static V W_Chk_dP_dtype(V *a);
static V F_Chk_dP_dtype_dgo(V a0, V a1, V a2);
static V S3569(void);
static V L3570(V *a);
static V S3571(void);
static V L3572(V *a);
static V L3573(V *a);
static V S3574(void);
static V L3575(V *a);
static V L3576(V *a);
static V L3577(V *a);
static V L3578(V *a);
static V L3579(V *a);
static V L3580(V *a);
static V L3581(V *a);
static V L3582(V *a);
static V L3583(V *a);
static V W_Chk_dP_dtype_dgo(V *a);
static V F_Chk_dP_dctors(V a0, V a1, V a2);
static V L3584(V *a);
static V L3585(V *a);
static V S3586(void);
static V L3587(V *a);
static V S3588(void);
static V L3589(V *a);
static V S3590(void);
static V L3591(V *a);
static V W_Chk_dP_dctors(V *a);
static V F_Chk_dP_dctor(V a0, V a1, V a2);
static V L3592(V *a);
static V L3593(V *a);
static V L3594(V *a);
static V S3595(void);
static V S3596(void);
static V L3597(V *a);
static V S3598(void);
static V L3599(V *a);
static V L3600(V *a);
static V S3601(void);
static V L3602(V *a);
static V L3603(V *a);
static V L3604(V *a);
static V L3605(V *a);
static V L3606(V *a);
static V L3607(V *a);
static V W_Chk_dP_dctor(V *a);
static V F_Chk_dTC_dparams(V a0);
static V W_Chk_dTC_dparams(V *a);
static V F_Chk_dtele__bind(V a0, V a1);
static V W_Chk_dtele__bind(V *a);
static V F_Chk_dP_dtele(V a0, V a1, V a2);
static V L3610(V *a);
static V L3611(V *a);
static V W_Chk_dP_dtele(V *a);
static V F_Chk_dP_dtele_done(V a0, V a1, V a2);
static V S3613(void);
static V S3615(void);
static V L3616(V *a);
static V S3617(void);
static V L3618(V *a);
static V S3619(void);
static V L3620(V *a);
static V L3621(V *a);
static V L3622(V *a);
static V L3623(V *a);
static V S3624(void);
static V S3625(void);
static V L3626(V *a);
static V L3627(V *a);
static V L3628(V *a);
static V S3629(void);
static V L3630(V *a);
static V L3631(V *a);
static V S3632(void);
static V L3633(V *a);
static V L3634(V *a);
static V L3635(V *a);
static V L3636(V *a);
static V S3637(void);
static V L3638(V *a);
static V W_Chk_dP_dtele_done(V *a);
static V F_Chk_dTC_dnames(V a0);
static V W_Chk_dTC_dnames(V *a);
static V F_Chk_dTC_dk(V a0);
static V W_Chk_dTC_dk(V *a);
static V F_Chk_dTC_dfirst__typed(V a0);
static V W_Chk_dTC_dfirst__typed(V *a);
static V F_Chk_dP_ddef(V a0);
static V S3642(void);
static V L3643(V *a);
static V L3644(V *a);
static V L3645(V *a);
static V L3646(V *a);
static V L3647(V *a);
static V L3648(V *a);
static V L3649(V *a);
static V L3650(V *a);
static V S3651(void);
static V L3652(V *a);
static V L3653(V *a);
static V S3654(void);
static V L3655(V *a);
static V S3656(void);
static V L3657(V *a);
static V S3658(void);
static V L3659(V *a);
static V L3660(V *a);
static V W_Chk_dP_ddef(V *a);
static V F_Chk_dP_ddef_dgo(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dP_ddef_dgo(V *a);
static V F_Chk_dP_ddef_dnew(V a0, V a1, V a2, V a3, V a4);
static V S3663(void);
static V L3664(V *a);
static V S3665(void);
static V S3666(void);
static V L3667(V *a);
static V L3668(V *a);
static V L3669(V *a);
static V L3670(V *a);
static V W_Chk_dP_ddef_dnew(V *a);
static V F_Chk_dP_ddef_dbody(V a0, V a1, V a2);
static V S3671(void);
static V L3672(V *a);
static V S3673(void);
static V L3674(V *a);
static V L3675(V *a);
static V L3676(V *a);
static V L3677(V *a);
static V W_Chk_dP_ddef_dbody(V *a);
static V F_Chk_dP_ddef_dvalue(V a0, V a1);
static V L3678(V *a);
static V L3679(V *a);
static V L3680(V *a);
static V L3681(V *a);
static V W_Chk_dP_ddef_dvalue(V *a);
static V F_Chk_dTld_dwith__v(V a0, V a1);
static V W_Chk_dTld_dwith__v(V *a);
static V F_Chk_dP_dcheck__ops(V a0);
static V W_Chk_dP_dcheck__ops(V *a);
static V F_Chk_dops_dbare(V a0);
static V W_Chk_dops_dbare(V *a);
static V F_Chk_dops_dfirst(V a0, V a1);
static V W_Chk_dops_dfirst(V *a);
static V F_Chk_dops_dbares(V a0);
static V W_Chk_dops_dbares(V *a);
static V F_Chk_dP_dcheck__ops_dc(V a0);
static V W_Chk_dP_dcheck__ops_dc(V *a);
static V F_Chk_dops_derr(V a0);
static V S3688(void);
static V S3689(void);
static V S3690(void);
static V S3691(void);
static V S3692(void);
static V S3693(void);
static V W_Chk_dops_derr(V *a);
static V F_Chk_dops_dtext(V a0, V a1);
static V W_Chk_dops_dtext(V *a);
static V F_Chk_dTC_dvars(V a0);
static V W_Chk_dTC_dvars(V *a);
static V F_Chk_dP_ddef_dforeign(V a0);
static V L3696(V *a);
static V S3697(void);
static V L3698(V *a);
static V L3699(V *a);
static V L3700(V *a);
static V W_Chk_dP_ddef_dforeign(V *a);
static V F_Chk_dTld_dwith__imps(V a0, V a1);
static V W_Chk_dTld_dwith__imps(V *a);
static V F_Chk_dP_dimports(V a0);
static V S3702(void);
static V L3703(V *a);
static V W_Chk_dP_dimports(V *a);
static V F_Chk_dP_dimport1(V a0);
static V S3704(void);
static V L3705(V *a);
static V S3706(void);
static V L3707(V *a);
static V S3708(void);
static V L3709(V *a);
static V S3710(void);
static V S3711(void);
static V S3712(void);
static V L3713(V *a);
static V L3714(V *a);
static V W_Chk_dP_dimport1(V *a);
static V F_Chk_dP_ddir(void);
static V L3715(V *a);
static V W_Chk_dP_ddir(V *a);
static V F_Chk_dPS_ddir(V a0);
static V W_Chk_dPS_ddir(V *a);
static V F_Chk_dP_duntil__quote(V a0);
static V L3717(V *a);
static V W_Chk_dP_duntil__quote(V *a);
static V F_Chk_dP_duntil__quote_dmore(V a0, V a1);
static V L3718(V *a);
static V W_Chk_dP_duntil__quote_dmore(V *a);
static V F_Chk_dTld_dlaw__x(V a0);
static V W_Chk_dTld_dlaw__x(V *a);
static V F_Chk_dP_ddef_dfill(V a0, V a1, V a2, V a3);
static V L3720(V *a);
static V L3721(V *a);
static V S3722(void);
static V L3723(V *a);
static V S3724(void);
static V S3725(void);
static V L3726(V *a);
static V L3727(V *a);
static V L3728(V *a);
static V W_Chk_dP_ddef_dfill(V *a);
static V F_Chk_dTld_dlaw__fill(V a0, V a1, V a2);
static V W_Chk_dTld_dlaw__fill(V *a);
static V F_Chk_dTC_dall__qnt(V a0);
static V W_Chk_dTC_dall__qnt(V *a);
static V F_Chk_dTld_dopen__law(V a0);
static V W_Chk_dTld_dopen__law(V *a);
static V F_Chk_dP_dunsafe(void);
static V S3732(void);
static V L3733(V *a);
static V S3734(void);
static V L3735(V *a);
static V L3736(V *a);
static V S3737(void);
static V L3738(V *a);
static V S3739(void);
static V W_Chk_dP_dunsafe(V *a);
static V F_Chk_dP_dreset__scope(void);
static V L3740(V *a);
static V W_Chk_dP_dreset__scope(V *a);
static V F_Chk_dPS_dset__scope(V a0, V a1, V a2, V a3);
static V W_Chk_dPS_dset__scope(V *a);
static V F_Chk_dparse__file_dfin(V a0);
static V W_Chk_dparse__file_dfin(V *a);
static V F_Main_dchk_dparsed(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Main_dchk_dparsed(V *a);
static V F_Chk_dmark__base(V a0, V a1);
static V W_Chk_dmark__base(V *a);
static V F_Chk_dmark__base_dgo(V a0, V a1, V a2, V a3);
static V W_Chk_dmark__base_dgo(V *a);
static V F_Chk_dmark__base_done(V a0, V a1);
static V W_Chk_dmark__base_done(V *a);
static V F_Chk_dmark__base_dtld(V a0, V a1, V a2);
static V W_Chk_dmark__base_dtld(V *a);
static V F_Chk_dbook__len(V a0);
static V W_Chk_dbook__len(V *a);
static V F_CS_dmark(V a0, V a1);
static V W_CS_dmark(V *a);
static V F_Main_dchk_dloading(void);
static V S3747(void);
static V W_Main_dchk_dloading(V *a);
static V F_Main_dchk_dimps(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L3749(V *a);
static V W_Main_dchk_dimps(V *a);
static V F_Main_dchk_dimps_dnext(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Main_dchk_dimps_dnext(V *a);
static V F_Main_dchk_dimp(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V W_Main_dchk_dimp(V *a);
static V F_Main_dchk_dimp_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10);
static V S3755(void);
static V L3756(V *a);
static V S3757(void);
static V W_Main_dchk_dimp_dgo(V *a);
static V F_Main_dchk_dimp_drel(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10);
static V S3759(void);
static V S3760(void);
static V S3761(void);
static V S3763(void);
static V L3767(V *a);
static V L3768(V *a);
static V W_Main_dchk_dimp_drel(V *a);
static V F_Main_dchk_dhub(V a0);
static V L3769(V *a);
static V S3770(void);
static V L3771(V *a);
static V L3772(V *a);
static V S3773(void);
static V W_Main_dchk_dhub(V *a);
static V F_Path_ddirname(V a0);
static V S3775(void);
static V S3776(void);
static V S3777(void);
static V W_Path_ddirname(V *a);
static V F_Path_djoin(V a0, V a1);
static V S3778(void);
static V W_Path_djoin(V *a);
static V F_Main_dchk_dis__hub(V a0);
static V S3779(void);
static V W_Main_dchk_dis__hub(V *a);
static V F_Main_dchk_dis__hub_dhex(V a0);
static V W_Main_dchk_dis__hub_dhex(V *a);
static V F_Main_dread__opt(V a0);
static V S3781(void);
static V L3782(V *a);
static V W_Main_dread__opt(V *a);
static V F_Main_dread__opt_dopen(V a0);
static V L3784(V *a);
static V W_Main_dread__opt_dopen(V *a);
static V F_Main_dread__opt_dfin(V a0);
static V L3786(V *a);
static V W_Main_dread__opt_dfin(V *a);
static V F_Main_dread__opt_dres(V a0);
static V W_Main_dread__opt_dres(V *a);
static V F_CS_dat__end(V a0);
static V W_CS_dat__end(V *a);
static V F_Main_dcheck__only_dfin(V a0);
static V S3791(void);
static V W_Main_dcheck__only_dfin(V *a);
static V F_Main_dast(V a0);
static V S3793(void);
static V W_Main_dast(V *a);
static V F_Decls_dshow(V a0);
static V W_Decls_dshow(V *a);
static V F_Decls_dshow_dgo(V a0);
static V S3795(void);
static V S3796(void);
static V W_Decls_dshow_dgo(V *a);
static V F_Decl_dshow(V a0);
static V S3798(void);
static V S3799(void);
static V S3800(void);
static V S3801(void);
static V S3802(void);
static V S3803(void);
static V S3804(void);
static V S3805(void);
static V S3806(void);
static V S3807(void);
static V S3808(void);
static V S3809(void);
static V S3810(void);
static V W_Decl_dshow(V *a);
static V F_Ctors_dshow(V a0);
static V S3812(void);
static V S3813(void);
static V W_Ctors_dshow(V *a);
static V F_Ctor_dshow(V a0);
static V S3815(void);
static V S3816(void);
static V W_Ctor_dshow(V *a);
static V F_Fields_dshow(V a0);
static V S3818(void);
static V S3819(void);
static V S3820(void);
static V W_Fields_dshow(V *a);
static V F_Params_dshow(V a0);
static V S3822(void);
static V S3823(void);
static V W_Params_dshow(V *a);
static V F_Param_dshow(V a0);
static V S3825(void);
static V W_Param_dshow(V *a);
static V F_Toks_dshow(V a0);
static V S3827(void);
static V W_Toks_dshow(V *a);
static V F_Tok_dshow(V a0);
static V S3829(void);
static V S3830(void);
static V W_Tok_dshow(V *a);
static V F_IO_dprint(V a0);
static V E_IO_dprint(V *a);
static V W_IO_dprint(V *a);
static V F_IO_dargs(void);
static V E_IO_dargs(V *a);
static V W_IO_dargs(V *a);

static V L0(V *a) {
return F_Main_drun(F_IO_dlist2(a[0]));
}
static V F_main(void) {
top:;
return F_IO_dbind(F_IO_dargs(), mk_clo(L0, 1, 0, 0));
}
static V W_main(V *a) { (void)a; return F_main(); }
static V F_IO_dlist2(V a0) {
top:;
V s1 = a0;
if ((s1) == IMM(0)) {
return IMM(0);
} else if (TAG(s1) == 1) {
return C2(1, FLD(s1, 0), F_IO_dlist2(FLD(s1, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_IO_dlist2(V *a) { (void)a; return F_IO_dlist2(a[0]); }
static V L3(V *a) {
return F_IO_dprint(F_Toks_dshow(F_Lex_dall(a[0])));
}
static V L4(V *a) {
return F_Main_dast(F_Main_dparse(a[0]));
}
static V L5(V *a) {
return F_Main_dcheck__only_dfin(a[0]);
}
static V L6(V *a) {
return F_Main_dchecked(a[1], a[0], a[2]);
}
static V S7(void) { static V c; return STRC(c, "usage: bendc [--check-only | --no-check] <base.bend> <input.bend> | --tokens <file> | --ast <file>"); }
static V F_Main_drun(V a0) {
top:;
V s2 = a0;
if (TAG(s2) == 1 && TAG(FLD(s2, 0)) == 1 && (FLD(FLD(s2, 0), 0)) == 45 && TAG(FLD(FLD(s2, 0), 1)) == 1 && (FLD(FLD(FLD(s2, 0), 1), 0)) == 45 && TAG(FLD(FLD(FLD(s2, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s2, 0), 1), 1), 0)) == 116 && TAG(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 0)) == 111 && TAG(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 0)) == 107 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 0)) == 101 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 0)) == 110 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 0)) == 115 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s2, 1)) == 1 && (FLD(FLD(s2, 1), 1)) == IMM(0)) {
return F_IO_dbind(F_IO_dread__file(FLD(FLD(s2, 1), 0)), mk_clo(L3, 1, 0, 0));
} else if (TAG(s2) == 1 && TAG(FLD(s2, 0)) == 1 && (FLD(FLD(s2, 0), 0)) == 45 && TAG(FLD(FLD(s2, 0), 1)) == 1 && (FLD(FLD(FLD(s2, 0), 1), 0)) == 45 && TAG(FLD(FLD(FLD(s2, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s2, 0), 1), 1), 0)) == 97 && TAG(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 0)) == 115 && TAG(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 0)) == 116 && (FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s2, 1)) == 1 && (FLD(FLD(s2, 1), 1)) == IMM(0)) {
return F_IO_dbind(F_IO_dread__file(FLD(FLD(s2, 1), 0)), mk_clo(L4, 1, 0, 0));
} else if (TAG(s2) == 1 && TAG(FLD(s2, 0)) == 1 && (FLD(FLD(s2, 0), 0)) == 45 && TAG(FLD(FLD(s2, 0), 1)) == 1 && (FLD(FLD(FLD(s2, 0), 1), 0)) == 45 && TAG(FLD(FLD(FLD(s2, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s2, 0), 1), 1), 0)) == 99 && TAG(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 0)) == 104 && TAG(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 0)) == 101 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 0)) == 99 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 0)) == 107 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 0)) == 45 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1), 0)) == 111 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1), 1), 0)) == 110 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1), 1), 1), 0)) == 108 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1), 1), 1), 1), 0)) == 121 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s2, 1)) == 1 && TAG(FLD(FLD(s2, 1), 1)) == 1 && (FLD(FLD(FLD(s2, 1), 1), 1)) == IMM(0)) {
return F_IO_dbind(F_Main_dcheck(FLD(FLD(s2, 1), 0), FLD(FLD(FLD(s2, 1), 1), 0)), mk_clo(L5, 1, 0, 0));
} else if (TAG(s2) == 1 && TAG(FLD(s2, 0)) == 1 && (FLD(FLD(s2, 0), 0)) == 45 && TAG(FLD(FLD(s2, 0), 1)) == 1 && (FLD(FLD(FLD(s2, 0), 1), 0)) == 45 && TAG(FLD(FLD(FLD(s2, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s2, 0), 1), 1), 0)) == 110 && TAG(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 0)) == 111 && TAG(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 0)) == 45 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 0)) == 99 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 0)) == 104 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 0)) == 101 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1), 0)) == 99 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1), 1), 0)) == 107 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s2, 1)) == 1 && TAG(FLD(FLD(s2, 1), 1)) == 1 && (FLD(FLD(FLD(s2, 1), 1), 1)) == IMM(0)) {
return F_Main_dbuild(FLD(FLD(s2, 1), 0), FLD(FLD(FLD(s2, 1), 1), 0));
} else if (TAG(s2) == 1 && TAG(FLD(s2, 1)) == 1 && (FLD(FLD(s2, 1), 1)) == IMM(0)) {
return F_IO_dbind(F_Main_dcheck(FLD(s2, 0), FLD(FLD(s2, 1), 0)), mk_clo(L6, 3, 2, (V[]){FLD(FLD(s2, 1), 0), FLD(s2, 0)}));
} else {
return F_IO_ddie(1u, S7());
}
}
static V W_Main_drun(V *a) { (void)a; return F_Main_drun(a[0]); }
static V L9(V *a) {
return C2(1, a[1], a[0]);
}
static V L8(V *a) {
return mk_clo(L9, 3, 2, (V[]){a[0], a[1]});
}
static V F_IO_ddie(V a1, V a2) {
top:;
return mk_clo(L8, 3, 2, (V[]){a2, a1});
}
static V W_IO_ddie(V *a) { (void)a; return F_IO_ddie(a[1], a[2]); }
static V L13(V *a) {
return F_Main_dchecked_dgo(a[2], a[1], a[0], F_Main_dnormalized(a[0]));
}
static V F_Main_dchecked(V a0, V a1, V a2) {
top:;
V v10 = a2;
V v11 = FLD(v10, 0);
V v12 = F_Chk_dreport(v11, FLD(v10, 1));
return F_IO_dbind(F_Bool_dpick(F_List_dis__empty(v12), F_IO_dpure(IMM(0)), F_IO_dwrite__err(F_Chk_dreport__text(v12))), mk_clo(L13, 4, 3, (V[]){v11, a1, a0}));
}
static V W_Main_dchecked(V *a) { (void)a; return F_Main_dchecked(a[0], a[1], a[2]); }
static V F_Main_dnormalized(V a0) {
top:;
return F_Bool_dand(F_Bool_dnot(F_Chk_dmain__is__io(a0)), F_Chk_dmain__has__fun(a0));
}
static V W_Main_dnormalized(V *a) { (void)a; return F_Main_dnormalized(a[0]); }
static V F_Chk_dmain__has__fun(V a0) {
top:;
return F_Chk_dmain__has__fun_dgo(a0, F_Chk_dmain__tld(a0));
}
static V W_Chk_dmain__has__fun(V *a) { (void)a; return F_Chk_dmain__has__fun(a[0]); }
static V S14(void) { static V c; return STRC(c, "main"); }
static V F_Chk_dmain__tld(V a0) {
top:;
return F_Chk_dbook__tld(a0, S14());
}
static V W_Chk_dmain__tld(V *a) { (void)a; return F_Chk_dmain__tld(a[0]); }
static V F_Chk_dbook__tld(V a0, V a1) {
top:;
V v15 = a0;
return F_Chk_dMap_dfind(FLD(v15, 0), a1);
}
static V W_Chk_dbook__tld(V *a) { (void)a; return F_Chk_dbook__tld(a[0], a[1]); }
static V F_Chk_dMap_dfind(V a1, V a2) {
top:;
return F_Chk_dMap_dfind_dgo(a1, a2);
}
static V W_Chk_dMap_dfind(V *a) { (void)a; return F_Chk_dMap_dfind(a[1], a[2]); }
static V F_Chk_dMap_dfind_dgo(V a1, V a2) {
top:;
V s16 = a1;
if ((s16) == IMM(0)) {
return IMM(0);
} else if (TAG(s16) == 1) {
return F_Chk_dMap_dfind_dleaf(FLD(s16, 1), F_String_deq(FLD(s16, 0), a2));
} else if (TAG(s16) == 2) {
return F_Chk_dMap_dfind_dnode(FLD(s16, 1), FLD(s16, 2), a2, F_Pair_dsnd(F_Map_dbit(a2, FLD(s16, 0))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dMap_dfind_dgo(V *a) { (void)a; return F_Chk_dMap_dfind_dgo(a[1], a[2]); }
static V F_Map_dbit(V a0, V a1) {
top:;
return F_Map_dbit_dat(a0, F_Nat_ddivmod(a1, 33u));
}
static V W_Map_dbit(V *a) { (void)a; return F_Map_dbit(a[0], a[1]); }
static V W_Nat_ddivmod(V *a) { (void)a; return F_Nat_ddivmod(a[0], a[1]); }
static V F_Map_dbit_dat(V a0, V a1) {
top:;
V v17 = a1;
return F_Map_dbit_dgo(a0, FLD(v17, 0), FLD(v17, 1));
}
static V W_Map_dbit_dat(V *a) { (void)a; return F_Map_dbit_dat(a[0], a[1]); }
static V F_Map_dbit_dgo(V a0, V a1, V a2) {
top:;
V s18 = a0;
if ((s18) == IMM(0)) {
return C2(0, IMM(0), IMM(0));
} else if (TAG(s18) == 1) {
V s19 = a1;
if ((s19) == 0) {
return F_Map_dbit_dgo_dchr(FLD(s18, 1), F_Map_dbit_dchr(FLD(s18, 0), a2));
} else if (nat_ge(s19, 1)) {
return F_Map_dbit_dgo_drec(FLD(s18, 0), F_Map_dbit_dgo(FLD(s18, 1), nat_subk(s19, 1), a2));
} else { bend_fail("incomplete match"); }
} else { bend_fail("incomplete match"); }
}
static V W_Map_dbit_dgo(V *a) { (void)a; return F_Map_dbit_dgo(a[0], a[1], a[2]); }
static V F_Map_dbit_dgo_drec(V a0, V a1) {
top:;
V v20 = a1;
return C2(0, C2(1, a0, FLD(v20, 0)), FLD(v20, 1));
}
static V W_Map_dbit_dgo_drec(V *a) { (void)a; return F_Map_dbit_dgo_drec(a[0], a[1]); }
static V F_Map_dbit_dchr(V a0, V a1) {
top:;
V s21 = a0;
V s22 = a1;
if ((s22) == 0) {
return C2(0, s21, IMM(1));
} else if (nat_ge(s22, 1)) {
return C2(0, s21, F_Map_dbit_du(s21, F_Nat_dsub(31u, nat_subk(s22, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dbit_dchr(V *a) { (void)a; return F_Map_dbit_dchr(a[0], a[1]); }
static V W_Nat_dsub(V *a) { (void)a; return F_Nat_dsub(a[0], a[1]); }
static V F_Map_dbit_du(V a0, V a1) {
top:;
return F_U32_dis__ne(F_U32_dand(F_U32_dshrn(a0, a1), 1u), 0u);
}
static V W_Map_dbit_du(V *a) { (void)a; return F_Map_dbit_du(a[0], a[1]); }
static V W_U32_dshrn(V *a) { (void)a; return F_U32_dshrn(a[0], a[1]); }
static V W_U32_dand(V *a) { (void)a; return F_U32_dand(a[0], a[1]); }
static V W_U32_dis__ne(V *a) { (void)a; return F_U32_dis__ne(a[0], a[1]); }
static V F_Map_dbit_dgo_dchr(V a0, V a1) {
top:;
V v23 = a1;
return C2(0, C2(1, FLD(v23, 0), a0), FLD(v23, 1));
}
static V W_Map_dbit_dgo_dchr(V *a) { (void)a; return F_Map_dbit_dgo_dchr(a[0], a[1]); }
static V F_Pair_dsnd(V a2) {
top:;
V v24 = a2;
return FLD(v24, 1);
}
static V W_Pair_dsnd(V *a) { (void)a; return F_Pair_dsnd(a[2]); }
static V F_Chk_dMap_dfind_dnode(V a1, V a2, V a3, V a4) {
top:;
V s25 = a4;
if ((s25) == IMM(1)) {
return F_Chk_dMap_dfind_dgo(a2, a3);
} else if ((s25) == IMM(0)) {
return F_Chk_dMap_dfind_dgo(a1, a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dMap_dfind_dnode(V *a) { (void)a; return F_Chk_dMap_dfind_dnode(a[1], a[2], a[3], a[4]); }
static V F_String_deq(V a0, V a1) {
top:;
return F_String_deq_dfin(F_String_dcmp(a0, a1));
}
static V W_String_deq(V *a) { (void)a; return F_String_deq(a[0], a[1]); }
static V F_String_dcmp(V a0, V a1) {
top:;
V s26 = a0;
V s27 = a1;
if ((s26) == IMM(0) && (s27) == IMM(0)) {
return C2(0, C2(0, IMM(0), IMM(0)), IMM(1));
} else if ((s26) == IMM(0) && TAG(s27) == 1) {
return C2(0, C2(0, IMM(0), C2(1, FLD(s27, 0), FLD(s27, 1))), IMM(0));
} else if (TAG(s26) == 1 && (s27) == IMM(0)) {
return C2(0, C2(0, C2(1, FLD(s26, 0), FLD(s26, 1)), IMM(0)), IMM(2));
} else if (TAG(s26) == 1 && TAG(s27) == 1) {
return F_String_dcmp_dfin(FLD(s26, 1), FLD(s27, 1), F_Char_dcmp(FLD(s26, 0), FLD(s27, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_String_dcmp(V *a) { (void)a; return F_String_dcmp(a[0], a[1]); }
static V F_Char_dcmp(V a0, V a1) {
top:;
V s28 = a0;
V s29 = a1;
{
return C2(0, C2(0, s28, s29), F_U32_dcmp(s28, s29));
}
}
static V W_Char_dcmp(V *a) { (void)a; return F_Char_dcmp(a[0], a[1]); }
static V W_U32_dcmp(V *a) { (void)a; return F_U32_dcmp(a[0], a[1]); }
static V F_String_dcmp_dfin(V a0, V a1, V a2) {
top:;
V v30 = a2;
V s31 = FLD(v30, 1);
if ((s31) == IMM(0)) {
return C2(0, C2(0, C2(1, FLD(FLD(v30, 0), 0), a0), C2(1, FLD(FLD(v30, 0), 1), a1)), IMM(0));
} else if ((s31) == IMM(1)) {
return F_String_dcmp_drec(FLD(FLD(v30, 0), 0), FLD(FLD(v30, 0), 1), F_String_dcmp(a0, a1));
} else if ((s31) == IMM(2)) {
return C2(0, C2(0, C2(1, FLD(FLD(v30, 0), 0), a0), C2(1, FLD(FLD(v30, 0), 1), a1)), IMM(2));
} else { bend_fail("incomplete match"); }
}
static V W_String_dcmp_dfin(V *a) { (void)a; return F_String_dcmp_dfin(a[0], a[1], a[2]); }
static V F_String_dcmp_drec(V a0, V a1, V a2) {
top:;
V v32 = a2;
return C2(0, C2(0, C2(1, a0, FLD(FLD(v32, 0), 0)), C2(1, a1, FLD(FLD(v32, 0), 1))), FLD(v32, 1));
}
static V W_String_dcmp_drec(V *a) { (void)a; return F_String_dcmp_drec(a[0], a[1], a[2]); }
static V F_String_deq_dfin(V a0) {
top:;
V v33 = a0;
return F_Cmp_dis__eq(FLD(v33, 1));
}
static V W_String_deq_dfin(V *a) { (void)a; return F_String_deq_dfin(a[0]); }
static V F_Cmp_dis__eq(V a0) {
top:;
V s34 = a0;
if ((s34) == IMM(0)) {
return IMM(0);
} else if ((s34) == IMM(1)) {
return IMM(1);
} else if ((s34) == IMM(2)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Cmp_dis__eq(V *a) { (void)a; return F_Cmp_dis__eq(a[0]); }
static V F_Chk_dMap_dfind_dleaf(V a1, V a2) {
top:;
V s35 = a2;
if ((s35) == IMM(1)) {
return C1(1, a1);
} else if ((s35) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dMap_dfind_dleaf(V *a) { (void)a; return F_Chk_dMap_dfind_dleaf(a[1], a[2]); }
static V F_Chk_dmain__has__fun_dgo(V a0, V a1) {
top:;
V s36 = a1;
if (TAG(s36) == 1 && TAG(FLD(s36, 0)) == 0) {
return F_Chk_dhas__fun(a0, FLD(FLD(s36, 0), 2), IMM(0));
} else {
return IMM(0);
}
}
static V W_Chk_dmain__has__fun_dgo(V *a) { (void)a; return F_Chk_dmain__has__fun_dgo(a[0], a[1]); }
static V F_Chk_dhas__fun(V a0, V a1, V a2) {
top:;
return F_Chk_dhas__fun_dgo(a0, F_Chk_dterm__wnf(a0, a1), a2);
}
static V W_Chk_dhas__fun(V *a) { (void)a; return F_Chk_dhas__fun(a[0], a[1], a[2]); }
static V F_Chk_dterm__wnf(V a0, V a1) {
top:;
return F_Chk_dwnf_dgo(a0, a1, IMM(0), IMM(0));
}
static V W_Chk_dterm__wnf(V *a) { (void)a; return F_Chk_dterm__wnf(a[0], a[1]); }
static V S38(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dwnf_dgo(V a0, V a1, V a2, V a3) {
top:;
V s37 = a1;
if (TAG(s37) == 1) {
{ V t0 = a0; V t1 = FLD(s37, 2); V t2 = a2; V t3 = IMM(0); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s37) == 3) {
{ V t0 = a0; V t1 = FLD(s37, 3); V t2 = a2; V t3 = IMM(0); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s37) == 23) {
{ V t0 = a0; V t1 = FLD(s37, 0); V t2 = a2; V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s37) == 10) {
{ V t0 = a0; V t1 = FLD(s37, 0); V t2 = C2(1, C2(2, FLD(s37, 1), FLD(s37, 2)), a2); V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s37) == 6) {
{ V t0 = a0; V t1 = F_Chk_dclo__apply(a0, FLD(s37, 3), F_Chk_dterm__cells(FLD(s37, 2), FLD(s37, 0))); V t2 = a2; V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s37) == 13) {
{ V t0 = a0; V t1 = FLD(s37, 0); V t2 = C2(1, C2(0, F_Chk_dterm__cell(FLD(s37, 1), S38()), FLD(s37, 2)), a2); V t3 = IMM(0); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s37) == 12) {
return F_Chk_dwnf_dlam(a0, CN(12, 5, (V[]){FLD(s37, 0), FLD(s37, 1), FLD(s37, 2), FLD(s37, 3), FLD(s37, 4)}), a2, a3);
} else if (TAG(s37) == 17) {
return F_Chk_dwnf_dmat(a0, C4(17, FLD(s37, 0), FLD(s37, 1), FLD(s37, 2), FLD(s37, 3)), a2, a3);
} else if (TAG(s37) == 18) {
return F_Chk_dwnf_defq(a0, C1(18, FLD(s37, 0)), a2, a3);
} else if (TAG(s37) == 21) {
return F_Chk_dwnf_drwt(a0, F_Chk_dterm__wnf(a0, FLD(s37, 0)), C4(21, FLD(s37, 0), FLD(s37, 1), FLD(s37, 2), FLD(s37, 3)), FLD(s37, 2), a2, a3);
} else if (TAG(s37) == 4) {
return F_Chk_dwnf_dref(a0, F_Chk_dbook__tld(a0, FLD(s37, 0)), C3(4, FLD(s37, 0), FLD(s37, 1), FLD(s37, 2)), a2, a3);
} else {
return F_Chk_dwnf_dback(a0, s37, a2);
}
}
static V W_Chk_dwnf_dgo(V *a) { (void)a; return F_Chk_dwnf_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dwnf_dback(V a0, V a1, V a2) {
top:;
V s39 = a2;
if ((s39) == IMM(0)) {
return a1;
} else if (TAG(s39) == 1 && TAG(FLD(s39, 0)) == 0) {
{ V t0 = a0; V t1 = F_Chk_dterm__apply(a0, a1, FLD(FLD(s39, 0), 0), FLD(FLD(s39, 0), 1)); V t2 = FLD(s39, 1); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s39) == 1 && TAG(FLD(s39, 0)) == 2) {
return F_Chk_dwnf_dmna(a0, a1, FLD(FLD(s39, 0), 0), FLD(FLD(s39, 0), 1), FLD(s39, 1));
} else if (TAG(s39) == 1 && TAG(FLD(s39, 0)) == 3) {
{ V t0 = a0; V t1 = F_Chk_dwnf_dmnb(a1, FLD(FLD(s39, 0), 0), FLD(FLD(s39, 0), 1)); V t2 = FLD(s39, 1); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s39) == 1 && TAG(FLD(s39, 0)) == 1) {
return F_Chk_dwnf_dmatd(a0, F_Chk_dlit__ctr(a1), FLD(FLD(s39, 0), 0), FLD(FLD(s39, 0), 1), FLD(FLD(s39, 0), 2), FLD(FLD(s39, 0), 3), FLD(s39, 1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dwnf_dback(V *a) { (void)a; return F_Chk_dwnf_dback(a[0], a[1], a[2]); }
static V F_Chk_dlit__ctr(V a0) {
top:;
V s40 = a0;
if (TAG(s40) == 16) {
return F_Chk_dlit__step(C2(16, FLD(s40, 0), FLD(s40, 1)));
} else {
return s40;
}
}
static V W_Chk_dlit__ctr(V *a) { (void)a; return F_Chk_dlit__ctr(a[0]); }
static V S42(void) { static V c; return STRC(c, "Zero"); }
static V S43(void) { static V c; return STRC(c, "Succ"); }
static V S44(void) { static V c; return STRC(c, "SNil"); }
static V S45(void) { static V c; return STRC(c, "SCon"); }
static V F_Chk_dlit__step(V a0) {
top:;
V s41 = a0;
if (TAG(s41) == 16 && TAG(FLD(s41, 0)) == 0 && (FLD(FLD(s41, 0), 0)) == 0) {
return C3(15, S42(), IMM(0), FLD(s41, 1));
} else if (TAG(s41) == 16 && TAG(FLD(s41, 0)) == 0 && nat_ge(FLD(FLD(s41, 0), 0), 1)) {
return C3(15, S43(), C2(1, C2(16, C1(0, nat_subk(FLD(FLD(s41, 0), 0), 1)), FLD(s41, 1)), IMM(0)), FLD(s41, 1));
} else if (TAG(s41) == 16 && TAG(FLD(s41, 0)) == 1 && (FLD(FLD(s41, 0), 0)) == IMM(0)) {
return C3(15, S44(), IMM(0), FLD(s41, 1));
} else if (TAG(s41) == 16 && TAG(FLD(s41, 0)) == 1 && TAG(FLD(FLD(s41, 0), 0)) == 1) {
return C3(15, S45(), C2(1, F_Chk_dchr__term(FLD(FLD(FLD(s41, 0), 0), 0), FLD(s41, 1)), C2(1, C2(16, C1(1, FLD(FLD(FLD(s41, 0), 0), 1)), FLD(s41, 1)), IMM(0))), FLD(s41, 1));
} else {
return s41;
}
}
static V W_Chk_dlit__step(V *a) { (void)a; return F_Chk_dlit__step(a[0]); }
static V S46(void) { static V c; return STRC(c, "Chr"); }
static V F_Chk_dchr__term(V a0, V a1) {
top:;
return C3(15, S46(), C2(1, F_Chk_du32__to__term(a0, a1), IMM(0)), a1);
}
static V W_Chk_dchr__term(V *a) { (void)a; return F_Chk_dchr__term(a[0], a[1]); }
static V S47(void) { static V c; return STRC(c, "U32"); }
static V F_Chk_du32__to__term(V a0, V a1) {
top:;
return C3(15, S47(), C2(1, F_Chk_dword__to__term(a0, a1), IMM(0)), a1);
}
static V W_Chk_du32__to__term(V *a) { (void)a; return F_Chk_du32__to__term(a[0], a[1]); }
static V S48(void) { static V c; return STRC(c, "WNil"); }
static V F_Chk_dword__to__term(V a0, V a1) {
top:;
return F_Chk_dword__to__term_dgo(a0, 32u, C3(15, S48(), IMM(0), a1), a1);
}
static V W_Chk_dword__to__term(V *a) { (void)a; return F_Chk_dword__to__term(a[0], a[1]); }
static V S50(void) { static V c; return STRC(c, "WCon"); }
static V S51(void) { static V c; return STRC(c, "False"); }
static V S52(void) { static V c; return STRC(c, "True"); }
static V F_Chk_dword__to__term_dgo(V a0, V a1, V a2, V a3) {
top:;
V s49 = a1;
if ((s49) == 0) {
return a2;
} else if (nat_ge(s49, 1)) {
{ V t0 = a0; V t1 = nat_subk(s49, 1); V t2 = C3(15, S50(), C2(1, C3(15, F_Bool_dpick(F_U32_dis__zero(F_U32_dand(F_U32_dshrn(a0, nat_subk(s49, 1)), 1u)), S51(), S52()), IMM(0), a3), C2(1, a2, IMM(0))), a3); V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dword__to__term_dgo(V *a) { (void)a; return F_Chk_dword__to__term_dgo(a[0], a[1], a[2], a[3]); }
static V W_U32_dis__zero(V *a) { (void)a; return F_U32_dis__zero(a[0]); }
static V F_Bool_dpick(V a1, V a2, V a3) {
top:;
V s53 = a1;
if ((s53) == IMM(0)) {
return a3;
} else if ((s53) == IMM(1)) {
return a2;
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dpick(V *a) { (void)a; return F_Bool_dpick(a[1], a[2], a[3]); }
static V F_Chk_dwnf_dmatd(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s54 = a1;
if (TAG(s54) == 15) {
return F_Chk_dwnf_dwalk(a0, FLD(s54, 0), FLD(s54, 1), C3(15, FLD(s54, 0), FLD(s54, 1), FLD(s54, 2)), a2, a2, a3, a4, a5, a6);
} else {
return F_Chk_dwnf_dback(a0, F_Chk_dterm__apply(a0, F_Chk_dlhs__or(a4, a2), a3, a5), a6);
}
}
static V W_Chk_dwnf_dmatd(V *a) { (void)a; return F_Chk_dwnf_dmatd(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dlhs__or(V a0, V a1) {
top:;
V s55 = a0;
if ((s55) == IMM(0)) {
return a1;
} else if (TAG(s55) == 1) {
return FLD(s55, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlhs__or(V *a) { (void)a; return F_Chk_dlhs__or(a[0], a[1]); }
static V F_Chk_dterm__apply(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dterm__apply_dgo(a0, F_Chk_dterm__strip(a1), a2, a3);
}
static V W_Chk_dterm__apply(V *a) { (void)a; return F_Chk_dterm__apply(a[0], a[1], a[2], a[3]); }
static V F_Chk_dterm__strip(V a0) {
top:;
return F_Chk_dterm__strip_dgo(F_Chk_dterm__force(a0));
}
static V W_Chk_dterm__strip(V *a) { (void)a; return F_Chk_dterm__strip(a[0]); }
static V F_Chk_dterm__force(V a0) {
top:;
V s56 = a0;
if (TAG(s56) == 1) {
{ V t0 = FLD(s56, 2); a0 = t0; goto top; }
} else if (TAG(s56) == 3) {
{ V t0 = FLD(s56, 3); a0 = t0; goto top; }
} else {
return s56;
}
}
static V W_Chk_dterm__force(V *a) { (void)a; return F_Chk_dterm__force(a[0]); }
static V F_Chk_dterm__strip_dgo(V a0) {
top:;
V s57 = a0;
if (TAG(s57) == 23) {
return F_Chk_dterm__strip(FLD(s57, 0));
} else {
return s57;
}
}
static V W_Chk_dterm__strip_dgo(V *a) { (void)a; return F_Chk_dterm__strip_dgo(a[0]); }
static V F_Chk_dterm__apply_dgo(V a0, V a1, V a2, V a3) {
top:;
V s58 = a1;
if (TAG(s58) == 12) {
return F_Chk_dclo__apply(a0, FLD(s58, 2), C2(1, a2, IMM(0)));
} else {
return C3(13, s58, a2, a3);
}
}
static V W_Chk_dterm__apply_dgo(V *a) { (void)a; return F_Chk_dterm__apply_dgo(a[0], a[1], a[2], a[3]); }
static V S60(void) { static V c; return STRC(c, "_"); }
static V S61(void) { static V c; return STRC(c, "e"); }
static V S62(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dclo__apply(V a0, V a1, V a2) {
top:;
V s59 = a1;
if (TAG(s59) == 24) {
return F_Chk_dhigher(a0, FLD(s59, 2), F_Chk_denv__set(FLD(s59, 0), FLD(s59, 1), F_Chk_dLst_dhead(C3(0, S60(), 0u, IMM(0)), a2)));
} else if (TAG(s59) == 25) {
return F_Chk_dhigher(a0, FLD(s59, 2), F_Chk_denv__sets(FLD(s59, 0), FLD(s59, 1), a2));
} else if (TAG(s59) == 26) {
return F_Chk_dterm__snf(a0, F_Chk_dclo__apply(a0, FLD(s59, 0), a2));
} else if (TAG(s59) == 27 && nat_ge(FLD(s59, 2), 1)) {
return F_Chk_dlhs__ext(a0, FLD(s59, 0), FLD(s59, 1), nat_subk(FLD(s59, 2), 1), F_List_dappend(FLD(s59, 3), a2));
} else if (TAG(s59) == 28) {
return F_Chk_dmat__goal(a0, F_Chk_dclo__apply(a0, FLD(s59, 0), a2), FLD(s59, 1), F_List_dappend(FLD(s59, 2), a2), FLD(s59, 3), FLD(s59, 4), FLD(s59, 5), FLD(s59, 6), FLD(s59, 7), FLD(s59, 8));
} else if (TAG(s59) == 29) {
return CN(11, 6, (V[]){IMM(1), S61(), 0u, C4(19, FLD(s59, 0), F_Chk_dLst_dhead(C3(0, S62(), 0u, IMM(0)), a2), FLD(s59, 1), IMM(0)), C1(30, C2(7, C2(9, IMM(1), IMM(0)), IMM(0))), FLD(s59, 2)});
} else if (TAG(s59) == 30) {
return FLD(s59, 0);
} else {
return s59;
}
}
static V W_Chk_dclo__apply(V *a) { (void)a; return F_Chk_dclo__apply(a[0], a[1], a[2]); }
static V F_Chk_dLst_dhead(V a1, V a2) {
top:;
V s63 = a2;
if ((s63) == IMM(0)) {
return a1;
} else if (TAG(s63) == 1) {
return FLD(s63, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dLst_dhead(V *a) { (void)a; return F_Chk_dLst_dhead(a[1], a[2]); }
static V F_List_dappend(V a2, V a3) {
top:;
V s64 = a2;
if ((s64) == IMM(0)) {
return a3;
} else if (TAG(s64) == 1) {
return C2(1, FLD(s64, 0), F_List_dappend(FLD(s64, 1), a3));
} else { bend_fail("incomplete match"); }
}
static V W_List_dappend(V *a) { (void)a; return F_List_dappend(a[2], a[3]); }
static V F_Chk_dmat__goal(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9) {
top:;
V s65 = a2;
if ((s65) == 0) {
return F_Chk_dclo__apply(a0, a4, C2(1, C3(15, a5, a3, a6), IMM(0)));
} else if (nat_ge(s65, 1)) {
return F_Chk_dmat__goal_dgo(F_Chk_dterm__wnf(a0, a1), nat_subk(s65, 1), a3, a4, a5, a6, a7, a8, a9);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dmat__goal(V *a) { (void)a; return F_Chk_dmat__goal(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]); }
static V F_Chk_dmat__goal_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s66 = a0;
if (TAG(s66) == 11) {
return CN(11, 6, (V[]){F_Chk_dmat__goal_ddem(FLD(s66, 0), a6), FLD(s66, 1), FLD(s66, 2), FLD(s66, 3), CN(28, 9, (V[]){FLD(s66, 4), a1, a2, a3, a4, a5, a6, a7, a8}), a5});
} else {
return C1(18, a5);
}
}
static V W_Chk_dmat__goal_dgo(V *a) { (void)a; return F_Chk_dmat__goal_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Chk_dmat__goal_ddem(V a0, V a1) {
top:;
V s67 = a0;
if ((s67) == IMM(0)) {
return IMM(0);
} else if ((s67) == IMM(1)) {
return a1;
} else {
return F_Chk_dquant__add(a1, a1);
}
}
static V W_Chk_dmat__goal_ddem(V *a) { (void)a; return F_Chk_dmat__goal_ddem(a[0], a[1]); }
static V F_Chk_dquant__add(V a0, V a1) {
top:;
V s68 = a0;
V s69 = a1;
if ((s68) == IMM(0)) {
return s69;
} else if ((s69) == IMM(0)) {
return s68;
} else {
return IMM(2);
}
}
static V W_Chk_dquant__add(V *a) { (void)a; return F_Chk_dquant__add(a[0], a[1]); }
static V S71(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dlhs__ext(V a0, V a1, V a2, V a3, V a4) {
top:;
V s70 = a3;
if ((s70) == 0) {
return F_Chk_dterm__apply(a0, a1, C3(15, a2, a4, IMM(0)), IMM(0));
} else if (nat_ge(s70, 1)) {
return CN(12, 5, (V[]){S71(), 0u, C4(27, a1, a2, nat_addk(nat_subk(s70, 1), 1), a4), IMM(0), IMM(3)});
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlhs__ext(V *a) { (void)a; return F_Chk_dlhs__ext(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dterm__snf(V a0, V a1) {
top:;
return F_Chk_dsnf_dgo(a0, F_Chk_dterm__wnf(a0, a1));
}
static V W_Chk_dterm__snf(V *a) { (void)a; return F_Chk_dterm__snf(a[0], a[1]); }
static V F_Chk_dsnf_dgo(V a0, V a1) {
top:;
V s72 = a1;
if (TAG(s72) == 0) {
return C3(0, FLD(s72, 0), FLD(s72, 1), FLD(s72, 2));
} else if (TAG(s72) == 4) {
return C3(4, FLD(s72, 0), FLD(s72, 1), FLD(s72, 2));
} else if (TAG(s72) == 5) {
return C4(5, FLD(s72, 0), FLD(s72, 1), F_Chk_dterm__snf(a0, FLD(s72, 2)), FLD(s72, 3));
} else if (TAG(s72) == 7) {
return C2(7, F_Chk_dterm__snf(a0, FLD(s72, 0)), FLD(s72, 1));
} else if (TAG(s72) == 10) {
return C3(10, F_Chk_dterm__snf(a0, FLD(s72, 0)), F_Chk_dterm__snf(a0, FLD(s72, 1)), FLD(s72, 2));
} else if (TAG(s72) == 11) {
return CN(11, 6, (V[]){FLD(s72, 0), FLD(s72, 1), FLD(s72, 2), F_Chk_dterm__snf(a0, FLD(s72, 3)), C1(26, FLD(s72, 4)), FLD(s72, 5)});
} else if (TAG(s72) == 12) {
return CN(12, 5, (V[]){FLD(s72, 0), FLD(s72, 1), C1(26, FLD(s72, 2)), FLD(s72, 3), IMM(3)});
} else if (TAG(s72) == 13) {
return C3(13, F_Chk_dsnf_dfun(a0, FLD(s72, 0)), F_Chk_dterm__snf(a0, FLD(s72, 1)), FLD(s72, 2));
} else if (TAG(s72) == 14) {
return C4(14, FLD(s72, 0), F_Chk_dsnfs(a0, FLD(s72, 1)), FLD(s72, 2), FLD(s72, 3));
} else if (TAG(s72) == 15) {
return C3(15, FLD(s72, 0), F_Chk_dsnfs(a0, FLD(s72, 1)), FLD(s72, 2));
} else if (TAG(s72) == 17) {
return C4(17, FLD(s72, 0), F_Chk_dterm__snf(a0, FLD(s72, 1)), F_Chk_dterm__snf(a0, FLD(s72, 2)), FLD(s72, 3));
} else if (TAG(s72) == 19) {
return C4(19, F_Chk_dterm__snf(a0, FLD(s72, 0)), F_Chk_dterm__snf(a0, FLD(s72, 1)), F_Chk_dterm__snf(a0, FLD(s72, 2)), FLD(s72, 3));
} else if (TAG(s72) == 21) {
return C4(21, F_Chk_dterm__snf(a0, FLD(s72, 0)), F_Chk_dterm__snf(a0, FLD(s72, 1)), F_Chk_dterm__snf(a0, FLD(s72, 2)), FLD(s72, 3));
} else {
return s72;
}
}
static V W_Chk_dsnf_dgo(V *a) { (void)a; return F_Chk_dsnf_dgo(a[0], a[1]); }
static V F_Chk_dsnfs(V a0, V a1) {
top:;
V s73 = a1;
if ((s73) == IMM(0)) {
return IMM(0);
} else if (TAG(s73) == 1) {
return C2(1, F_Chk_dterm__snf(a0, FLD(s73, 0)), F_Chk_dsnfs(a0, FLD(s73, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dsnfs(V *a) { (void)a; return F_Chk_dsnfs(a[0], a[1]); }
static V F_Chk_dsnf_dfun(V a0, V a1) {
top:;
V s74 = a1;
if (TAG(s74) == 4) {
return C3(4, FLD(s74, 0), FLD(s74, 1), FLD(s74, 2));
} else {
return F_Chk_dterm__snf(a0, s74);
}
}
static V W_Chk_dsnf_dfun(V *a) { (void)a; return F_Chk_dsnf_dfun(a[0], a[1]); }
static V F_Chk_denv__sets(V a0, V a1, V a2) {
top:;
V s75 = a1;
V s76 = a2;
if (TAG(s75) == 1 && TAG(s76) == 1) {
{ V t0 = F_Chk_denv__set(a0, FLD(s75, 0), FLD(s76, 0)); V t1 = FLD(s75, 1); V t2 = FLD(s76, 1); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else {
return a0;
}
}
static V W_Chk_denv__sets(V *a) { (void)a; return F_Chk_denv__sets(a[0], a[1], a[2]); }
static V F_Chk_denv__set(V a0, V a1, V a2) {
top:;
return C2(1, C2(31, a1, a2), a0);
}
static V W_Chk_denv__set(V *a) { (void)a; return F_Chk_denv__set(a[0], a[1], a[2]); }
static V F_Chk_dhigher(V a0, V a1, V a2) {
top:;
V s77 = a1;
if (TAG(s77) == 0) {
return F_Chk_dhigher_dvar(a0, F_Chk_denv__get(a2, FLD(s77, 1)), C3(4, FLD(s77, 0), FLD(s77, 2), IMM(0)), FLD(s77, 2));
} else if (TAG(s77) == 3) {
return F_Chk_dhigher_dvar(a0, F_Chk_denv__get(a2, FLD(s77, 1)), FLD(s77, 3), FLD(s77, 2));
} else if (TAG(s77) == 5) {
{ V t0 = a0; V t1 = FLD(s77, 2); V t2 = C2(1, C2(31, FLD(s77, 0), C2(32, FLD(s77, 1), a2)), a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s77) == 6) {
return CN(6, 6, (V[]){FLD(s77, 0), FLD(s77, 1), F_Chk_dhighers(a0, FLD(s77, 2), a2), C3(25, a2, FLD(s77, 1), F_Chk_dsyn__body(FLD(s77, 3))), FLD(s77, 4), FLD(s77, 5)});
} else if (TAG(s77) == 11) {
return CN(11, 6, (V[]){FLD(s77, 0), FLD(s77, 1), FLD(s77, 2), F_Chk_dhigher(a0, FLD(s77, 3), a2), C3(24, a2, FLD(s77, 2), F_Chk_dsyn__body(FLD(s77, 4))), FLD(s77, 5)});
} else if (TAG(s77) == 12) {
return CN(12, 5, (V[]){FLD(s77, 0), FLD(s77, 1), C3(24, a2, FLD(s77, 1), F_Chk_dsyn__body(FLD(s77, 2))), FLD(s77, 3), FLD(s77, 4)});
} else if (TAG(s77) == 7) {
return C2(7, F_Chk_dhigher(a0, FLD(s77, 0), a2), FLD(s77, 1));
} else if (TAG(s77) == 10) {
return C3(10, F_Chk_dhigher(a0, FLD(s77, 0), a2), F_Chk_dhigher(a0, FLD(s77, 1), a2), FLD(s77, 2));
} else if (TAG(s77) == 13) {
return F_Chk_dhigher_dapp(a0, F_Chk_dhigher(a0, FLD(s77, 0), a2), F_Chk_dhigher(a0, FLD(s77, 1), a2), FLD(s77, 2));
} else if (TAG(s77) == 14) {
return C4(14, FLD(s77, 0), F_Chk_dhighers(a0, FLD(s77, 1), a2), FLD(s77, 2), FLD(s77, 3));
} else if (TAG(s77) == 15) {
return C3(15, FLD(s77, 0), F_Chk_dhighers(a0, FLD(s77, 1), a2), FLD(s77, 2));
} else if (TAG(s77) == 17) {
return C4(17, FLD(s77, 0), F_Chk_dhigher(a0, FLD(s77, 1), a2), F_Chk_dhigher(a0, FLD(s77, 2), a2), FLD(s77, 3));
} else if (TAG(s77) == 19) {
return C4(19, F_Chk_dhigher(a0, FLD(s77, 0), a2), F_Chk_dhigher(a0, FLD(s77, 1), a2), F_Chk_dhigher(a0, FLD(s77, 2), a2), FLD(s77, 3));
} else if (TAG(s77) == 21) {
return C4(21, F_Chk_dhigher(a0, FLD(s77, 0), a2), F_Chk_dhigher(a0, FLD(s77, 1), a2), F_Chk_dhigher(a0, FLD(s77, 2), a2), FLD(s77, 3));
} else if (TAG(s77) == 23) {
return C3(23, F_Chk_dhigher(a0, FLD(s77, 0), a2), F_Chk_dhigher(a0, FLD(s77, 1), a2), FLD(s77, 2));
} else {
return s77;
}
}
static V W_Chk_dhigher(V *a) { (void)a; return F_Chk_dhigher(a[0], a[1], a[2]); }
static V F_Chk_dhighers(V a0, V a1, V a2) {
top:;
V s78 = a1;
if ((s78) == IMM(0)) {
return IMM(0);
} else if (TAG(s78) == 1) {
return C2(1, F_Chk_dhigher(a0, FLD(s78, 0), a2), F_Chk_dhighers(a0, FLD(s78, 1), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dhighers(V *a) { (void)a; return F_Chk_dhighers(a[0], a[1], a[2]); }
static V F_Chk_dhigher_dapp(V a0, V a1, V a2, V a3) {
top:;
V s79 = a1;
if (TAG(s79) == 12) {
return F_Chk_dclo__apply(a0, FLD(s79, 2), C2(1, a2, IMM(0)));
} else {
return C3(13, s79, a2, a3);
}
}
static V W_Chk_dhigher_dapp(V *a) { (void)a; return F_Chk_dhigher_dapp(a[0], a[1], a[2], a[3]); }
static V F_Chk_dsyn__body(V a0) {
top:;
V s80 = a0;
if (TAG(s80) == 24) {
return FLD(s80, 2);
} else if (TAG(s80) == 25) {
return FLD(s80, 2);
} else {
return s80;
}
}
static V W_Chk_dsyn__body(V *a) { (void)a; return F_Chk_dsyn__body(a[0]); }
static V F_Chk_denv__get(V a0, V a1) {
top:;
V s81 = a0;
if ((s81) == IMM(0)) {
return IMM(0);
} else if (TAG(s81) == 1 && TAG(FLD(s81, 0)) == 31) {
return F_Bool_dpick(F_U32_dis__eq(a1, FLD(FLD(s81, 0), 0)), C1(1, FLD(FLD(s81, 0), 1)), F_Chk_denv__get(FLD(s81, 1), a1));
} else if (TAG(s81) == 1) {
{ V t0 = FLD(s81, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_denv__get(V *a) { (void)a; return F_Chk_denv__get(a[0], a[1]); }
static V W_U32_dis__eq(V *a) { (void)a; return F_U32_dis__eq(a[0], a[1]); }
static V F_Chk_dhigher_dvar(V a0, V a1, V a2, V a3) {
top:;
V s82 = a1;
if ((s82) == IMM(0)) {
return a2;
} else if (TAG(s82) == 1) {
return F_Chk_dhigher_dval(a0, FLD(s82, 0), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dhigher_dvar(V *a) { (void)a; return F_Chk_dhigher_dvar(a[0], a[1], a[2], a[3]); }
static V F_Chk_dhigher_dval(V a0, V a1, V a2) {
top:;
V s83 = a1;
if (TAG(s83) == 32) {
return F_Chk_dhigher(a0, F_Chk_dpatt__term(FLD(s83, 0), a2), FLD(s83, 1));
} else if (TAG(s83) == 1) {
return C3(1, FLD(s83, 0), FLD(s83, 1), FLD(s83, 2));
} else {
return F_Chk_dTm_drespan(s83, a2);
}
}
static V W_Chk_dhigher_dval(V *a) { (void)a; return F_Chk_dhigher_dval(a[0], a[1], a[2]); }
static V F_Chk_dTm_drespan(V a0, V a1) {
top:;
V s84 = a0;
if (TAG(s84) == 0 && (FLD(s84, 2)) == IMM(0)) {
return C3(0, FLD(s84, 0), FLD(s84, 1), a1);
} else if (TAG(s84) == 4 && (FLD(s84, 1)) == IMM(0)) {
return C3(4, FLD(s84, 0), a1, FLD(s84, 2));
} else if (TAG(s84) == 7 && (FLD(s84, 1)) == IMM(0)) {
return C2(7, FLD(s84, 0), a1);
} else if (TAG(s84) == 8 && (FLD(s84, 0)) == IMM(0)) {
return C1(8, a1);
} else if (TAG(s84) == 9 && (FLD(s84, 1)) == IMM(0)) {
return C2(9, FLD(s84, 0), a1);
} else if (TAG(s84) == 13 && (FLD(s84, 2)) == IMM(0)) {
return C3(13, FLD(s84, 0), FLD(s84, 1), a1);
} else if (TAG(s84) == 14 && (FLD(s84, 2)) == IMM(0)) {
return C4(14, FLD(s84, 0), FLD(s84, 1), a1, FLD(s84, 3));
} else if (TAG(s84) == 15 && (FLD(s84, 2)) == IMM(0)) {
return C3(15, FLD(s84, 0), FLD(s84, 1), a1);
} else if (TAG(s84) == 16 && (FLD(s84, 1)) == IMM(0)) {
return C2(16, FLD(s84, 0), a1);
} else if (TAG(s84) == 20 && (FLD(s84, 0)) == IMM(0)) {
return C1(20, a1);
} else if (TAG(s84) == 22 && (FLD(s84, 1)) == IMM(0)) {
return C2(22, FLD(s84, 0), a1);
} else {
return s84;
}
}
static V W_Chk_dTm_drespan(V *a) { (void)a; return F_Chk_dTm_drespan(a[0], a[1]); }
static V F_Chk_dpatt__term(V a0, V a1) {
top:;
V s85 = a0;
if (TAG(s85) == 0) {
return C3(0, FLD(s85, 0), FLD(s85, 1), F_Chk_dSp_dor(a1, FLD(s85, 3)));
} else if (TAG(s85) == 1) {
return C3(15, FLD(s85, 0), F_Chk_dpatt__terms(FLD(s85, 1), a1), F_Chk_dSp_dor(a1, FLD(s85, 2)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dpatt__term(V *a) { (void)a; return F_Chk_dpatt__term(a[0], a[1]); }
static V F_Chk_dSp_dor(V a0, V a1) {
top:;
V s86 = a0;
if ((s86) == IMM(0)) {
return a1;
} else {
return s86;
}
}
static V W_Chk_dSp_dor(V *a) { (void)a; return F_Chk_dSp_dor(a[0], a[1]); }
static V F_Chk_dpatt__terms(V a0, V a1) {
top:;
V s87 = a0;
if ((s87) == IMM(0)) {
return IMM(0);
} else if (TAG(s87) == 1) {
return C2(1, F_Chk_dpatt__term(FLD(s87, 0), a1), F_Chk_dpatt__terms(FLD(s87, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dpatt__terms(V *a) { (void)a; return F_Chk_dpatt__terms(a[0], a[1]); }
static V F_Chk_dwnf_dwalk(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9) {
top:;
V s88 = a4;
if (TAG(s88) == 23) {
{ V t0 = a0; V t1 = a1; V t2 = a2; V t3 = a3; V t4 = FLD(s88, 0); V t5 = a5; V t6 = a6; V t7 = a7; V t8 = a8; V t9 = a9; a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; a5 = t5; a6 = t6; a7 = t7; a8 = t8; a9 = t9; goto top; }
} else if (TAG(s88) == 17) {
return F_Chk_dwnf_dwalk_dmat(a0, a1, a2, a3, C4(17, FLD(s88, 0), FLD(s88, 1), FLD(s88, 2), FLD(s88, 3)), FLD(s88, 1), FLD(s88, 2), a5, a6, a7, a8, a9, F_String_deq(a1, FLD(s88, 0)));
} else if (TAG(s88) == 18) {
return F_Chk_dwnf_dback(a0, F_Chk_dterm__apply(a0, F_Chk_dlhs__or(a7, a5), a6, a8), a9);
} else {
return F_Chk_dwnf_dgo(a0, s88, C2(1, C2(0, a3, IMM(0)), a9), a7);
}
}
static V W_Chk_dwnf_dwalk(V *a) { (void)a; return F_Chk_dwnf_dwalk(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]); }
static V F_Chk_dwnf_dwalk_dmat(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11, V a12) {
top:;
V s89 = a12;
if ((s89) == IMM(1)) {
return F_Chk_dwnf_dgo(a0, a5, F_Chk_dapp__frames(a2, a11), F_Chk_dlhs__mat(a0, a9, a1, F_List_dlength(a2)));
} else if ((s89) == IMM(0)) {
return F_Chk_dwnf_dwalk(a0, a1, a2, a3, a6, a7, a8, a9, a10, a11);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dwnf_dwalk_dmat(V *a) { (void)a; return F_Chk_dwnf_dwalk_dmat(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12]); }
static V F_List_dlength(V a2) {
top:;
V s90 = a2;
if ((s90) == IMM(0)) {
return 0u;
} else if (TAG(s90) == 1) {
return nat_addk(F_List_dlength(FLD(s90, 1)), 1);
} else { bend_fail("incomplete match"); }
}
static V W_List_dlength(V *a) { (void)a; return F_List_dlength(a[2]); }
static V F_Chk_dlhs__mat(V a0, V a1, V a2, V a3) {
top:;
V s91 = a1;
if ((s91) == IMM(0)) {
return IMM(0);
} else if (TAG(s91) == 1) {
return C2(1, F_Chk_dlhs__ext(a0, FLD(s91, 0), a2, a3, IMM(0)), F_Nat_dadd(F_Nat_dsub(FLD(s91, 1), 1u), a3));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlhs__mat(V *a) { (void)a; return F_Chk_dlhs__mat(a[0], a[1], a[2], a[3]); }
static V W_Nat_dadd(V *a) { (void)a; return F_Nat_dadd(a[0], a[1]); }
static V S93(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dapp__frames(V a0, V a1) {
top:;
V s92 = a0;
if ((s92) == IMM(0)) {
return a1;
} else if (TAG(s92) == 1) {
return C2(1, C2(0, F_Chk_dterm__cell(FLD(s92, 0), S93()), IMM(0)), F_Chk_dapp__frames(FLD(s92, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dapp__frames(V *a) { (void)a; return F_Chk_dapp__frames(a[0], a[1]); }
static V F_Chk_dterm__cell(V a0, V a1) {
top:;
V s94 = a0;
if (TAG(s94) == 1) {
return C3(1, FLD(s94, 0), FLD(s94, 1), FLD(s94, 2));
} else {
return C3(1, a1, F_Chk_dTm_dspan(s94), s94);
}
}
static V W_Chk_dterm__cell(V *a) { (void)a; return F_Chk_dterm__cell(a[0], a[1]); }
static V F_Chk_dTm_dspan(V a0) {
top:;
V s95 = a0;
if (TAG(s95) == 0) {
return FLD(s95, 2);
} else if (TAG(s95) == 1) {
return FLD(s95, 1);
} else if (TAG(s95) == 2) {
return FLD(s95, 1);
} else if (TAG(s95) == 3) {
return FLD(s95, 2);
} else if (TAG(s95) == 4) {
return FLD(s95, 1);
} else if (TAG(s95) == 5) {
return FLD(s95, 3);
} else if (TAG(s95) == 6) {
return FLD(s95, 4);
} else if (TAG(s95) == 7) {
return FLD(s95, 1);
} else if (TAG(s95) == 8) {
return FLD(s95, 0);
} else if (TAG(s95) == 9) {
return FLD(s95, 1);
} else if (TAG(s95) == 10) {
return FLD(s95, 2);
} else if (TAG(s95) == 11) {
return FLD(s95, 5);
} else if (TAG(s95) == 12) {
return FLD(s95, 3);
} else if (TAG(s95) == 13) {
return FLD(s95, 2);
} else if (TAG(s95) == 14) {
return FLD(s95, 2);
} else if (TAG(s95) == 15) {
return FLD(s95, 2);
} else if (TAG(s95) == 16) {
return FLD(s95, 1);
} else if (TAG(s95) == 17) {
return FLD(s95, 3);
} else if (TAG(s95) == 18) {
return FLD(s95, 0);
} else if (TAG(s95) == 19) {
return FLD(s95, 3);
} else if (TAG(s95) == 20) {
return FLD(s95, 0);
} else if (TAG(s95) == 21) {
return FLD(s95, 3);
} else if (TAG(s95) == 22) {
return FLD(s95, 1);
} else if (TAG(s95) == 23) {
return FLD(s95, 2);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dspan(V *a) { (void)a; return F_Chk_dTm_dspan(a[0]); }
static V F_Chk_dwnf_dmnb(V a0, V a1, V a2) {
top:;
V s96 = a0;
if (TAG(s96) == 9 && (FLD(s96, 0)) == IMM(2)) {
return a1;
} else if (TAG(s96) == 9 && (FLD(s96, 0)) == IMM(1)) {
return F_Bool_dpick(F_Chk_dTm_dis__qua(a1), C2(9, IMM(1), FLD(s96, 1)), C3(10, a1, C2(9, IMM(1), FLD(s96, 1)), a2));
} else if (TAG(s96) == 9) {
return C2(9, FLD(s96, 0), FLD(s96, 1));
} else {
return C3(10, a1, s96, a2);
}
}
static V W_Chk_dwnf_dmnb(V *a) { (void)a; return F_Chk_dwnf_dmnb(a[0], a[1], a[2]); }
static V F_Chk_dTm_dis__qua(V a0) {
top:;
V s97 = a0;
if (TAG(s97) == 9) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__qua(V *a) { (void)a; return F_Chk_dTm_dis__qua(a[0]); }
static V F_Chk_dwnf_dmna(V a0, V a1, V a2, V a3, V a4) {
top:;
V s98 = a1;
if (TAG(s98) == 9 && (FLD(s98, 0)) == IMM(2)) {
return F_Chk_dwnf_dgo(a0, a2, a4, IMM(0));
} else if (TAG(s98) == 9 && (FLD(s98, 0)) == IMM(0)) {
return F_Chk_dwnf_dback(a0, C2(9, IMM(0), FLD(s98, 1)), a4);
} else {
return F_Chk_dwnf_dgo(a0, a2, C2(1, C2(3, s98, a3), a4), IMM(0));
}
}
static V W_Chk_dwnf_dmna(V *a) { (void)a; return F_Chk_dwnf_dmna(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dwnf_dref(V a0, V a1, V a2, V a3, V a4) {
top:;
V s99 = a1;
if (TAG(s99) == 1 && TAG(FLD(s99, 0)) == 1 && (FLD(FLD(s99, 0), 0)) == 0) {
return F_Chk_dwnf_dback(a0, C4(14, F_Chk_dTm_dref__k(a2), IMM(0), F_Chk_dTm_dspan(a2), IMM(0)), a3);
} else if (TAG(s99) == 1 && TAG(FLD(s99, 0)) == 0 && TAG(FLD(FLD(s99, 0), 3)) == 1) {
return F_Chk_dwnf_dref_ddef(a0, a2, FLD(FLD(FLD(s99, 0), 3), 0), FLD(FLD(s99, 0), 0), a3, F_Nat_dis__lt(F_Chk_dfrs__apps(a3, FLD(FLD(s99, 0), 0)), FLD(FLD(s99, 0), 0)));
} else {
return F_Chk_dwnf_dback(a0, a2, a3);
}
}
static V W_Chk_dwnf_dref(V *a) { (void)a; return F_Chk_dwnf_dref(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dfrs__apps(V a0, V a1) {
top:;
V s100 = a0;
V s101 = a1;
if ((s101) == 0) {
return 0u;
} else if (TAG(s100) == 1 && TAG(FLD(s100, 0)) == 0 && nat_ge(s101, 1)) {
return nat_addk(F_Chk_dfrs__apps(FLD(s100, 1), nat_subk(s101, 1)), 1);
} else {
return 0u;
}
}
static V W_Chk_dfrs__apps(V *a) { (void)a; return F_Chk_dfrs__apps(a[0], a[1]); }
static V W_Nat_dis__lt(V *a) { (void)a; return F_Nat_dis__lt(a[0], a[1]); }
static V F_Chk_dwnf_dref_ddef(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s102 = a5;
if ((s102) == IMM(1)) {
return F_Chk_dwnf_dback(a0, a1, a4);
} else if ((s102) == IMM(0)) {
return F_Chk_dwnf_dgo(a0, a2, a4, C2(1, a1, a3));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dwnf_dref_ddef(V *a) { (void)a; return F_Chk_dwnf_dref_ddef(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S104(void) { static V c; return STRC(c, ""); }
static V F_Chk_dTm_dref__k(V a0) {
top:;
V s103 = a0;
if (TAG(s103) == 4) {
return FLD(s103, 0);
} else {
return S104();
}
}
static V W_Chk_dTm_dref__k(V *a) { (void)a; return F_Chk_dTm_dref__k(a[0]); }
static V F_Chk_dwnf_drwt(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s105 = a1;
if (TAG(s105) == 20) {
return F_Chk_dwnf_dgo(a0, a3, a4, a5);
} else {
return F_Chk_dwnf_dback(a0, a2, a4);
}
}
static V W_Chk_dwnf_drwt(V *a) { (void)a; return F_Chk_dwnf_drwt(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dwnf_defq(V a0, V a1, V a2, V a3) {
top:;
V s106 = a2;
V s107 = a3;
if (TAG(s106) == 1 && TAG(FLD(s106, 0)) == 0 && TAG(s107) == 1 && nat_ge(FLD(s107, 1), 1)) {
return F_Chk_dwnf_dback(a0, FLD(s107, 0), C2(1, C2(0, FLD(FLD(s106, 0), 0), FLD(FLD(s106, 0), 1)), FLD(s106, 1)));
} else {
return F_Chk_dwnf_dback(a0, a1, s106);
}
}
static V W_Chk_dwnf_defq(V *a) { (void)a; return F_Chk_dwnf_defq(a[0], a[1], a[2], a[3]); }
static V F_Chk_dwnf_dmat(V a0, V a1, V a2, V a3) {
top:;
V s108 = a2;
if (TAG(s108) == 1 && TAG(FLD(s108, 0)) == 0) {
return F_Chk_dwnf_dgo(a0, FLD(FLD(s108, 0), 0), C2(1, C4(1, a1, FLD(FLD(s108, 0), 0), a3, FLD(FLD(s108, 0), 1)), FLD(s108, 1)), IMM(0));
} else {
return F_Chk_dwnf_dback(a0, a1, s108);
}
}
static V W_Chk_dwnf_dmat(V *a) { (void)a; return F_Chk_dwnf_dmat(a[0], a[1], a[2], a[3]); }
static V F_Chk_dwnf_dlam(V a0, V a1, V a2, V a3) {
top:;
V s109 = a2;
if (TAG(s109) == 1 && TAG(FLD(s109, 0)) == 0) {
return F_Chk_dwnf_dgo(a0, F_Chk_dterm__apply(a0, a1, FLD(FLD(s109, 0), 0), FLD(FLD(s109, 0), 1)), FLD(s109, 1), F_Chk_dlhs__step(a0, a3, FLD(FLD(s109, 0), 0), FLD(FLD(s109, 0), 1)));
} else {
return F_Chk_dwnf_dback(a0, a1, s109);
}
}
static V W_Chk_dwnf_dlam(V *a) { (void)a; return F_Chk_dwnf_dlam(a[0], a[1], a[2], a[3]); }
static V F_Chk_dlhs__step(V a0, V a1, V a2, V a3) {
top:;
V s110 = a1;
if ((s110) == IMM(0)) {
return IMM(0);
} else if (TAG(s110) == 1 && (FLD(s110, 1)) == 0) {
return IMM(0);
} else if (TAG(s110) == 1 && nat_ge(FLD(s110, 1), 1)) {
return C2(1, F_Chk_dterm__apply(a0, FLD(s110, 0), a2, a3), nat_subk(FLD(s110, 1), 1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlhs__step(V *a) { (void)a; return F_Chk_dlhs__step(a[0], a[1], a[2], a[3]); }
static V S113(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dterm__cells(V a0, V a1) {
top:;
V s111 = a0;
V s112 = a1;
if (TAG(s111) == 1 && TAG(s112) == 1) {
return C2(1, F_Chk_dterm__cell(FLD(s111, 0), FLD(s112, 0)), F_Chk_dterm__cells(FLD(s111, 1), FLD(s112, 1)));
} else if (TAG(s111) == 1 && (s112) == IMM(0)) {
return C2(1, F_Chk_dterm__cell(FLD(s111, 0), S113()), F_Chk_dterm__cells(FLD(s111, 1), IMM(0)));
} else {
return IMM(0);
}
}
static V W_Chk_dterm__cells(V *a) { (void)a; return F_Chk_dterm__cells(a[0], a[1]); }
static V F_Chk_dhas__fun_dgo(V a0, V a1, V a2) {
top:;
V s114 = a1;
if (TAG(s114) == 11) {
return IMM(1);
} else if (TAG(s114) == 14) {
return F_Chk_dhas__fun_dadt(a0, FLD(s114, 0), FLD(s114, 1), F_Chk_dterm__key(F_Chk_dterm__lower(a0, C4(14, FLD(s114, 0), FLD(s114, 1), FLD(s114, 2), FLD(s114, 3)), 0u)), a2);
} else {
return IMM(0);
}
}
static V W_Chk_dhas__fun_dgo(V *a) { (void)a; return F_Chk_dhas__fun_dgo(a[0], a[1], a[2]); }
static V F_Chk_dterm__lower(V a0, V a1, V a2) {
top:;
return F_Chk_dterm__lower_dgo(a0, F_Chk_dterm__force(a1), a2);
}
static V W_Chk_dterm__lower(V *a) { (void)a; return F_Chk_dterm__lower(a[0], a[1], a[2]); }
static V F_Chk_dterm__lower_dgo(V a0, V a1, V a2) {
top:;
V s115 = a1;
if (TAG(s115) == 0) {
return C3(0, FLD(s115, 0), FLD(s115, 1), FLD(s115, 2));
} else if (TAG(s115) == 5) {
return C4(5, FLD(s115, 0), FLD(s115, 1), F_Chk_dterm__lower(a0, FLD(s115, 2), a2), FLD(s115, 3));
} else if (TAG(s115) == 6) {
V v116 = F_U32_dfrom__nat(F_List_dlength(FLD(s115, 0)));
return CN(6, 6, (V[]){FLD(s115, 0), F_Chk_dlet__ids(FLD(s115, 0), a2), F_Chk_dlowers(a0, FLD(s115, 2), a2), C3(25, IMM(0), IMM(0), F_Chk_dterm__lower(a0, F_Chk_dclo__apply(a0, FLD(s115, 3), F_Chk_dlet__vars(FLD(s115, 0), a2)), F_U32_dadd(a2, v116))), FLD(s115, 4), FLD(s115, 5)});
} else if (TAG(s115) == 7) {
return C2(7, F_Chk_dterm__lower(a0, FLD(s115, 0), a2), FLD(s115, 1));
} else if (TAG(s115) == 10) {
return C3(10, F_Chk_dterm__lower(a0, FLD(s115, 0), a2), F_Chk_dterm__lower(a0, FLD(s115, 1), a2), FLD(s115, 2));
} else if (TAG(s115) == 11) {
return CN(11, 6, (V[]){FLD(s115, 0), FLD(s115, 1), a2, F_Chk_dterm__lower(a0, FLD(s115, 3), a2), C3(24, IMM(0), a2, F_Chk_dterm__lower(a0, F_Chk_dclo__apply(a0, FLD(s115, 4), C2(1, C3(0, FLD(s115, 1), a2, IMM(0)), IMM(0))), F_U32_dinc(a2))), FLD(s115, 5)});
} else if (TAG(s115) == 12) {
return CN(12, 5, (V[]){FLD(s115, 0), a2, C3(24, IMM(0), a2, F_Chk_dterm__lower(a0, F_Chk_dclo__apply(a0, FLD(s115, 2), C2(1, C3(0, FLD(s115, 0), a2, IMM(0)), IMM(0))), F_U32_dinc(a2))), FLD(s115, 3), FLD(s115, 4)});
} else if (TAG(s115) == 13) {
return C3(13, F_Chk_dterm__lower(a0, FLD(s115, 0), a2), F_Chk_dterm__lower(a0, FLD(s115, 1), a2), FLD(s115, 2));
} else if (TAG(s115) == 14) {
return C4(14, FLD(s115, 0), F_Chk_dlowers(a0, FLD(s115, 1), a2), FLD(s115, 2), FLD(s115, 3));
} else if (TAG(s115) == 15) {
return C3(15, FLD(s115, 0), F_Chk_dlowers(a0, FLD(s115, 1), a2), FLD(s115, 2));
} else if (TAG(s115) == 17) {
return C4(17, FLD(s115, 0), F_Chk_dterm__lower(a0, FLD(s115, 1), a2), F_Chk_dterm__lower(a0, FLD(s115, 2), a2), FLD(s115, 3));
} else if (TAG(s115) == 19) {
return C4(19, F_Chk_dterm__lower(a0, FLD(s115, 0), a2), F_Chk_dterm__lower(a0, FLD(s115, 1), a2), F_Chk_dterm__lower(a0, FLD(s115, 2), a2), FLD(s115, 3));
} else if (TAG(s115) == 21) {
return C4(21, F_Chk_dterm__lower(a0, FLD(s115, 0), a2), F_Chk_dterm__lower(a0, FLD(s115, 1), a2), F_Chk_dterm__lower(a0, FLD(s115, 2), a2), FLD(s115, 3));
} else if (TAG(s115) == 23) {
return C3(23, F_Chk_dterm__lower(a0, FLD(s115, 0), a2), F_Chk_dterm__lower(a0, FLD(s115, 1), a2), FLD(s115, 2));
} else {
return s115;
}
}
static V W_Chk_dterm__lower_dgo(V *a) { (void)a; return F_Chk_dterm__lower_dgo(a[0], a[1], a[2]); }
static V F_Chk_dlowers(V a0, V a1, V a2) {
top:;
V s117 = a1;
if ((s117) == IMM(0)) {
return IMM(0);
} else if (TAG(s117) == 1) {
return C2(1, F_Chk_dterm__lower(a0, FLD(s117, 0), a2), F_Chk_dlowers(a0, FLD(s117, 1), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlowers(V *a) { (void)a; return F_Chk_dlowers(a[0], a[1], a[2]); }
static V W_U32_dinc(V *a) { (void)a; return F_U32_dinc(a[0]); }
static V W_U32_dadd(V *a) { (void)a; return F_U32_dadd(a[0], a[1]); }
static V F_Chk_dlet__vars(V a0, V a1) {
top:;
V s118 = a0;
if ((s118) == IMM(0)) {
return IMM(0);
} else if (TAG(s118) == 1) {
return C2(1, C3(0, FLD(s118, 0), a1, IMM(0)), F_Chk_dlet__vars(FLD(s118, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlet__vars(V *a) { (void)a; return F_Chk_dlet__vars(a[0], a[1]); }
static V F_Chk_dlet__ids(V a0, V a1) {
top:;
V s119 = a0;
if ((s119) == IMM(0)) {
return IMM(0);
} else if (TAG(s119) == 1) {
return C2(1, a1, F_Chk_dlet__ids(FLD(s119, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlet__ids(V *a) { (void)a; return F_Chk_dlet__ids(a[0], a[1]); }
static V W_U32_dfrom__nat(V *a) { (void)a; return F_U32_dfrom__nat(a[0]); }
static V S121(void) { static V c; return STRC(c, "V"); }
static V S122(void) { static V c; return STRC(c, "R"); }
static V S123(void) { static V c; return STRC(c, "!"); }
static V S124(void) { static V c; return STRC(c, ""); }
static V S125(void) { static V c; return STRC(c, "L("); }
static V S126(void) { static V c; return STRC(c, ")"); }
static V S127(void) { static V c; return STRC(c, "T("); }
static V S128(void) { static V c; return STRC(c, ")"); }
static V S129(void) { static V c; return STRC(c, "Q"); }
static V S130(void) { static V c; return STRC(c, "&"); }
static V S131(void) { static V c; return STRC(c, "M("); }
static V S132(void) { static V c; return STRC(c, ","); }
static V S133(void) { static V c; return STRC(c, ")"); }
static V S134(void) { static V c; return STRC(c, "A"); }
static V S135(void) { static V c; return STRC(c, "("); }
static V S136(void) { static V c; return STRC(c, ","); }
static V S137(void) { static V c; return STRC(c, ")"); }
static V S138(void) { static V c; return STRC(c, "F"); }
static V S139(void) { static V c; return STRC(c, "("); }
static V S140(void) { static V c; return STRC(c, ")"); }
static V S141(void) { static V c; return STRC(c, "@("); }
static V S142(void) { static V c; return STRC(c, ","); }
static V S143(void) { static V c; return STRC(c, ")"); }
static V S144(void) { static V c; return STRC(c, "D"); }
static V S145(void) { static V c; return STRC(c, "("); }
static V S146(void) { static V c; return STRC(c, ","); }
static V S147(void) { static V c; return STRC(c, ")"); }
static V S148(void) { static V c; return STRC(c, "C"); }
static V S149(void) { static V c; return STRC(c, "("); }
static V S150(void) { static V c; return STRC(c, ")"); }
static V S151(void) { static V c; return STRC(c, "N"); }
static V S152(void) { static V c; return STRC(c, "S\042"); }
static V S153(void) { static V c; return STRC(c, "\042"); }
static V S154(void) { static V c; return STRC(c, "X"); }
static V S155(void) { static V c; return STRC(c, "("); }
static V S156(void) { static V c; return STRC(c, ","); }
static V S157(void) { static V c; return STRC(c, ")"); }
static V S158(void) { static V c; return STRC(c, "E"); }
static V S159(void) { static V c; return STRC(c, "=("); }
static V S160(void) { static V c; return STRC(c, ","); }
static V S161(void) { static V c; return STRC(c, ","); }
static V S162(void) { static V c; return STRC(c, ")"); }
static V S163(void) { static V c; return STRC(c, "r"); }
static V S164(void) { static V c; return STRC(c, "%("); }
static V S165(void) { static V c; return STRC(c, ","); }
static V S166(void) { static V c; return STRC(c, ","); }
static V S167(void) { static V c; return STRC(c, ")"); }
static V S168(void) { static V c; return STRC(c, "\077"); }
static V S169(void) { static V c; return STRC(c, ":("); }
static V S170(void) { static V c; return STRC(c, ","); }
static V S171(void) { static V c; return STRC(c, ")"); }
static V S172(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dterm__key(V a0) {
top:;
V s120 = a0;
if (TAG(s120) == 0) {
return F_String_dappend(S121(), F_U32_dshow(FLD(s120, 1)));
} else if (TAG(s120) == 4) {
return F_String_dappend(S122(), F_String_dappend(FLD(s120, 0), F_Bool_dpick(FLD(s120, 2), S123(), S124())));
} else if (TAG(s120) == 5) {
{ V t0 = FLD(s120, 2); a0 = t0; goto top; }
} else if (TAG(s120) == 6) {
return F_String_dappend(S125(), F_String_dappend(F_Chk_dterm__key_dlist(FLD(s120, 2)), F_String_dappend(F_Chk_dterm__key(F_Chk_dsyn__body(FLD(s120, 3))), S126())));
} else if (TAG(s120) == 7) {
return F_String_dappend(S127(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 0)), S128()));
} else if (TAG(s120) == 8) {
return S129();
} else if (TAG(s120) == 9) {
return F_String_dappend(S130(), F_Chk_dshow_dqua(FLD(s120, 0)));
} else if (TAG(s120) == 10) {
return F_String_dappend(S131(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 0)), F_String_dappend(S132(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 1)), S133()))));
} else if (TAG(s120) == 11) {
return F_String_dappend(S134(), F_String_dappend(F_Chk_dquant__show(FLD(s120, 0)), F_String_dappend(F_U32_dshow(FLD(s120, 2)), F_String_dappend(S135(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 3)), F_String_dappend(S136(), F_String_dappend(F_Chk_dterm__key(F_Chk_dsyn__body(FLD(s120, 4))), S137())))))));
} else if (TAG(s120) == 12) {
return F_String_dappend(S138(), F_String_dappend(F_Chk_dquant__show(FLD(s120, 4)), F_String_dappend(F_U32_dshow(FLD(s120, 1)), F_String_dappend(S139(), F_String_dappend(F_Chk_dterm__key(F_Chk_dsyn__body(FLD(s120, 2))), S140())))));
} else if (TAG(s120) == 13) {
return F_String_dappend(S141(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 0)), F_String_dappend(S142(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 1)), S143()))));
} else if (TAG(s120) == 14) {
return F_String_dappend(S144(), F_String_dappend(FLD(s120, 0), F_String_dappend(S145(), F_String_dappend(F_Chk_dterm__key_dlist(FLD(s120, 1)), F_String_dappend(F_String_djoin(FLD(s120, 3), S146()), S147())))));
} else if (TAG(s120) == 15) {
return F_String_dappend(S148(), F_String_dappend(FLD(s120, 0), F_String_dappend(S149(), F_String_dappend(F_Chk_dterm__key_dlist(FLD(s120, 1)), S150()))));
} else if (TAG(s120) == 16 && TAG(FLD(s120, 0)) == 0) {
return F_String_dappend(S151(), F_Nat_dshow(FLD(FLD(s120, 0), 0)));
} else if (TAG(s120) == 16 && TAG(FLD(s120, 0)) == 1) {
return F_String_dappend(S152(), F_String_dappend(F_Chk_dshow_dtext(FLD(FLD(s120, 0), 0)), S153()));
} else if (TAG(s120) == 17) {
return F_String_dappend(S154(), F_String_dappend(FLD(s120, 0), F_String_dappend(S155(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 1)), F_String_dappend(S156(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 2)), S157()))))));
} else if (TAG(s120) == 18) {
return S158();
} else if (TAG(s120) == 19) {
return F_String_dappend(S159(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 0)), F_String_dappend(S160(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 1)), F_String_dappend(S161(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 2)), S162()))))));
} else if (TAG(s120) == 20) {
return S163();
} else if (TAG(s120) == 21) {
return F_String_dappend(S164(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 0)), F_String_dappend(S165(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 1)), F_String_dappend(S166(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 2)), S167()))))));
} else if (TAG(s120) == 22) {
return F_String_dappend(S168(), FLD(s120, 0));
} else if (TAG(s120) == 23) {
return F_String_dappend(S169(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 0)), F_String_dappend(S170(), F_String_dappend(F_Chk_dterm__key(FLD(s120, 1)), S171()))));
} else {
return S172();
}
}
static V W_Chk_dterm__key(V *a) { (void)a; return F_Chk_dterm__key(a[0]); }
static V F_String_dappend(V a0, V a1) {
top:;
V s173 = a0;
if ((s173) == IMM(0)) {
return a1;
} else if (TAG(s173) == 1) {
return C2(1, FLD(s173, 0), F_String_dappend(FLD(s173, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_String_dappend(V *a) { (void)a; return F_String_dappend(a[0], a[1]); }
static V S175(void) { static V c; return STRC(c, ""); }
static V F_Chk_dshow_dtext(V a0) {
top:;
V s174 = a0;
if ((s174) == IMM(0)) {
return S175();
} else if (TAG(s174) == 1) {
return F_String_dappend(F_Chk_dshow_dchr(FLD(s174, 0), 34u), F_Chk_dshow_dtext(FLD(s174, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dtext(V *a) { (void)a; return F_Chk_dshow_dtext(a[0]); }
static V S176(void) { static V c; return STRC(c, "\134n"); }
static V S177(void) { static V c; return STRC(c, "\134t"); }
static V S178(void) { static V c; return STRC(c, "\134r"); }
static V S179(void) { static V c; return STRC(c, "\1340"); }
static V S180(void) { static V c; return STRC(c, "\134"); }
static V S181(void) { static V c; return STRC(c, "\134u{"); }
static V S182(void) { static V c; return STRC(c, "}"); }
static V F_Chk_dshow_dchr(V a0, V a1) {
top:;
return F_Bool_dpick(F_U32_dis__eq(a0, 10u), S176(), F_Bool_dpick(F_U32_dis__eq(a0, 9u), S177(), F_Bool_dpick(F_U32_dis__eq(a0, 13u), S178(), F_Bool_dpick(F_U32_dis__eq(a0, 0u), S179(), F_Bool_dpick(F_Bool_dor(F_U32_dis__eq(a0, 92u), F_U32_dis__eq(a0, a1)), F_String_dappend(S180(), F_Chk_dStr_dchr(a0)), F_Bool_dpick(F_Bool_dor(F_Bool_dor(F_U32_dis__lt(a0, 32u), F_U32_dis__eq(a0, 127u)), F_Bool_dor(F_Bool_dand(F_U32_dis__ge(a0, 55296u), F_U32_dis__le(a0, 57343u)), F_U32_dis__gt(a0, 1114111u))), F_String_dappend(S181(), F_String_dappend(F_Chk_dU32_dshow__hex(a0), S182())), F_Chk_dStr_dchr(a0)))))));
}
static V W_Chk_dshow_dchr(V *a) { (void)a; return F_Chk_dshow_dchr(a[0], a[1]); }
static V F_Chk_dStr_dchr(V a0) {
top:;
return C2(1, a0, IMM(0));
}
static V W_Chk_dStr_dchr(V *a) { (void)a; return F_Chk_dStr_dchr(a[0]); }
static V S183(void) { static V c; return STRC(c, ""); }
static V F_Chk_dU32_dshow__hex(V a0) {
top:;
return F_Chk_dU32_dshow__hex_dgo(a0, S183());
}
static V W_Chk_dU32_dshow__hex(V *a) { (void)a; return F_Chk_dU32_dshow__hex(a[0]); }
static V F_Chk_dU32_dshow__hex_dgo(V a0, V a1) {
top:;
V v184 = F_U32_dand(a0, 15u);
V v185 = F_Chk_dStr_dchr(F_Bool_dpick(F_U32_dis__lt(v184, 10u), F_U32_dadd(48u, v184), F_U32_dadd(87u, v184)));
return F_Chk_dshow__hex_dmore(a0, F_String_dappend(v185, a1), F_U32_dis__lt(a0, 16u));
}
static V W_Chk_dU32_dshow__hex_dgo(V *a) { (void)a; return F_Chk_dU32_dshow__hex_dgo(a[0], a[1]); }
static V W_U32_dis__lt(V *a) { (void)a; return F_U32_dis__lt(a[0], a[1]); }
static V F_Chk_dshow__hex_dmore(V a0, V a1, V a2) {
top:;
V s186 = a2;
if ((s186) == IMM(1)) {
return a1;
} else if ((s186) == IMM(0)) {
return F_Chk_dU32_dshow__hex_dgo(F_U32_dshrn(a0, 4u), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow__hex_dmore(V *a) { (void)a; return F_Chk_dshow__hex_dmore(a[0], a[1], a[2]); }
static V W_U32_dis__gt(V *a) { (void)a; return F_U32_dis__gt(a[0], a[1]); }
static V W_U32_dis__le(V *a) { (void)a; return F_U32_dis__le(a[0], a[1]); }
static V W_U32_dis__ge(V *a) { (void)a; return F_U32_dis__ge(a[0], a[1]); }
static V F_Bool_dand(V a0, V a1) {
top:;
V s187 = a0;
if ((s187) == IMM(0)) {
return IMM(0);
} else if ((s187) == IMM(1)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dand(V *a) { (void)a; return F_Bool_dand(a[0], a[1]); }
static V F_Bool_dor(V a0, V a1) {
top:;
V s188 = a0;
if ((s188) == IMM(0)) {
return a1;
} else if ((s188) == IMM(1)) {
return IMM(1);
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dor(V *a) { (void)a; return F_Bool_dor(a[0], a[1]); }
static V W_Nat_dshow(V *a) { (void)a; return F_Nat_dshow(a[0]); }
static V S190(void) { static V c; return STRC(c, ""); }
static V S191(void) { static V c; return STRC(c, ","); }
static V F_Chk_dterm__key_dlist(V a0) {
top:;
V s189 = a0;
if ((s189) == IMM(0)) {
return S190();
} else if (TAG(s189) == 1) {
return F_String_dappend(F_Chk_dterm__key(FLD(s189, 0)), F_String_dappend(S191(), F_Chk_dterm__key_dlist(FLD(s189, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dterm__key_dlist(V *a) { (void)a; return F_Chk_dterm__key_dlist(a[0]); }
static V F_String_djoin(V a0, V a1) {
top:;
V s192 = a0;
if ((s192) == IMM(0)) {
return IMM(0);
} else if (TAG(s192) == 1) {
return F_String_djoin_dgo(FLD(s192, 1), FLD(s192, 0), a1);
} else { bend_fail("incomplete match"); }
}
static V W_String_djoin(V *a) { (void)a; return F_String_djoin(a[0], a[1]); }
static V F_String_djoin_dgo(V a0, V a1, V a2) {
top:;
V s193 = a0;
if ((s193) == IMM(0)) {
return a1;
} else if (TAG(s193) == 1) {
return F_String_dappend(a1, F_String_dappend(a2, F_String_djoin_dgo(FLD(s193, 1), FLD(s193, 0), a2)));
} else { bend_fail("incomplete match"); }
}
static V W_String_djoin_dgo(V *a) { (void)a; return F_String_djoin_dgo(a[0], a[1], a[2]); }
static V F_U32_dshow(V a0) {
top:;
V v194 = a0;
return F_U32_dshow_dif(v194, F_U32_dis__zero(v194));
}
static V W_U32_dshow(V *a) { (void)a; return F_U32_dshow(a[0]); }
static V F_U32_dshow_dif(V a0, V a1) {
top:;
V s195 = a1;
if ((s195) == IMM(1)) {
return C2(1, 48u, IMM(0));
} else if ((s195) == IMM(0)) {
return F_U32_dshow_dgo(10u, a0, IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_U32_dshow_dif(V *a) { (void)a; return F_U32_dshow_dif(a[0], a[1]); }
static V F_U32_dshow_dgo(V a0, V a1, V a2) {
top:;
V s196 = a0;
if ((s196) == 0) {
return a2;
} else if (nat_ge(s196, 1)) {
return F_U32_dshow_dfin(nat_subk(s196, 1), a2, a1, F_U32_dis__zero(a1));
} else { bend_fail("incomplete match"); }
}
static V W_U32_dshow_dgo(V *a) { (void)a; return F_U32_dshow_dgo(a[0], a[1], a[2]); }
static V F_U32_dshow_dfin(V a0, V a1, V a2, V a3) {
top:;
V s197 = a3;
if ((s197) == IMM(1)) {
return a1;
} else if ((s197) == IMM(0)) {
return F_U32_dshow_dgo(a0, F_U32_ddiv(a2, 10u), C2(1, F_U32_dadd(48u, F_U32_dmod(a2, 10u)), a1));
} else { bend_fail("incomplete match"); }
}
static V W_U32_dshow_dfin(V *a) { (void)a; return F_U32_dshow_dfin(a[0], a[1], a[2], a[3]); }
static V W_U32_dmod(V *a) { (void)a; return F_U32_dmod(a[0], a[1]); }
static V W_U32_ddiv(V *a) { (void)a; return F_U32_ddiv(a[0], a[1]); }
static V S199(void) { static V c; return STRC(c, "-"); }
static V S200(void) { static V c; return STRC(c, "+"); }
static V S201(void) { static V c; return STRC(c, ""); }
static V F_Chk_dquant__show(V a0) {
top:;
V s198 = a0;
if ((s198) == IMM(0)) {
return S199();
} else if ((s198) == IMM(2)) {
return S200();
} else {
return S201();
}
}
static V W_Chk_dquant__show(V *a) { (void)a; return F_Chk_dquant__show(a[0]); }
static V S203(void) { static V c; return STRC(c, "&0"); }
static V S204(void) { static V c; return STRC(c, "&2"); }
static V S205(void) { static V c; return STRC(c, "&1"); }
static V F_Chk_dshow_dqua(V a0) {
top:;
V s202 = a0;
if ((s202) == IMM(0)) {
return S203();
} else if ((s202) == IMM(2)) {
return S204();
} else {
return S205();
}
}
static V W_Chk_dshow_dqua(V *a) { (void)a; return F_Chk_dshow_dqua(a[0]); }
static V F_Chk_dhas__fun_dadt(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Chk_dhas__fun_dadt_dc(a0, a1, a2, a3, a4, F_Chk_dStr_dhas(a4, a3));
}
static V W_Chk_dhas__fun_dadt(V *a) { (void)a; return F_Chk_dhas__fun_dadt(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dStr_dhas(V a0, V a1) {
top:;
V s206 = a0;
if ((s206) == IMM(0)) {
return IMM(0);
} else if (TAG(s206) == 1) {
return F_Bool_dor(F_String_deq(FLD(s206, 0), a1), F_Chk_dStr_dhas(FLD(s206, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dhas(V *a) { (void)a; return F_Chk_dStr_dhas(a[0], a[1]); }
static V F_Chk_dhas__fun_dadt_dc(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s207 = a5;
if ((s207) == IMM(1)) {
return IMM(0);
} else if ((s207) == IMM(0)) {
return F_Chk_dhas__fun_dctrs(a0, a2, F_Chk_dhas__fun_dcs(F_Chk_dbook__tld(a0, a1)), C2(1, a3, a4));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dhas__fun_dadt_dc(V *a) { (void)a; return F_Chk_dhas__fun_dadt_dc(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dhas__fun_dcs(V a0) {
top:;
V s208 = a0;
if (TAG(s208) == 1 && TAG(FLD(s208, 0)) == 1) {
return FLD(FLD(s208, 0), 3);
} else {
return IMM(0);
}
}
static V W_Chk_dhas__fun_dcs(V *a) { (void)a; return F_Chk_dhas__fun_dcs(a[0]); }
static V F_Chk_dhas__fun_dctrs(V a0, V a1, V a2, V a3) {
top:;
V s209 = a2;
if ((s209) == IMM(0)) {
return IMM(0);
} else if (TAG(s209) == 1) {
return F_Bool_dor(F_Chk_dhas__fun_dfields(a0, F_Chk_dhas__fun_dfill(a0, FLD(FLD(s209, 0), 2), a1), FLD(FLD(s209, 0), 1), 0u, a3), F_Chk_dhas__fun_dctrs(a0, a1, FLD(s209, 1), a3));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dhas__fun_dctrs(V *a) { (void)a; return F_Chk_dhas__fun_dctrs(a[0], a[1], a[2], a[3]); }
static V F_Chk_dhas__fun_dfill(V a0, V a1, V a2) {
top:;
V s210 = a2;
if ((s210) == IMM(0)) {
return a1;
} else if (TAG(s210) == 1) {
{ V t0 = a0; V t1 = F_Chk_dclo__apply(a0, F_Chk_dAll_db(F_Chk_dterm__wnf(a0, a1)), C2(1, FLD(s210, 0), IMM(0))); V t2 = FLD(s210, 1); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dhas__fun_dfill(V *a) { (void)a; return F_Chk_dhas__fun_dfill(a[0], a[1], a[2]); }
static V F_Chk_dAll_db(V a0) {
top:;
V s211 = a0;
if (TAG(s211) == 11) {
return FLD(s211, 4);
} else {
return C1(30, s211);
}
}
static V W_Chk_dAll_db(V *a) { (void)a; return F_Chk_dAll_db(a[0]); }
static V F_Chk_dhas__fun_dfields(V a0, V a1, V a2, V a3, V a4) {
top:;
V s212 = a2;
if ((s212) == 0) {
return IMM(0);
} else if (nat_ge(s212, 1)) {
return F_Chk_dhas__fun_dfield(a0, F_Chk_dterm__wnf(a0, a1), nat_subk(s212, 1), a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dhas__fun_dfields(V *a) { (void)a; return F_Chk_dhas__fun_dfields(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dhas__fun_dfield(V a0, V a1, V a2, V a3, V a4) {
top:;
V s213 = a1;
if (TAG(s213) == 11) {
return F_Bool_dor(F_Chk_dhas__fun(a0, FLD(s213, 3), a4), F_Chk_dhas__fun_dfields(a0, F_Chk_dclo__apply(a0, FLD(s213, 4), C2(1, C3(0, FLD(s213, 1), a3, IMM(0)), IMM(0))), a2, F_U32_dinc(a3), a4));
} else {
return IMM(0);
}
}
static V W_Chk_dhas__fun_dfield(V *a) { (void)a; return F_Chk_dhas__fun_dfield(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dmain__is__io(V a0) {
top:;
return F_Chk_dmain__is__io_dgo(a0, F_Chk_dmain__tld(a0));
}
static V W_Chk_dmain__is__io(V *a) { (void)a; return F_Chk_dmain__is__io(a[0]); }
static V F_Chk_dmain__is__io_dgo(V a0, V a1) {
top:;
V s214 = a1;
if (TAG(s214) == 1 && TAG(FLD(s214, 0)) == 0) {
return F_Chk_dvalid_dio(a0, F_Chk_dterm__head(F_Chk_dterm__strip(FLD(FLD(s214, 0), 2))));
} else {
return IMM(0);
}
}
static V W_Chk_dmain__is__io_dgo(V *a) { (void)a; return F_Chk_dmain__is__io_dgo(a[0], a[1]); }
static V F_Chk_dterm__head(V a0) {
top:;
return F_Pair_dfst(F_Chk_dterm__unapply(a0));
}
static V W_Chk_dterm__head(V *a) { (void)a; return F_Chk_dterm__head(a[0]); }
static V F_Chk_dterm__unapply(V a0) {
top:;
return F_Chk_dterm__unapply_dgo(a0, IMM(0));
}
static V W_Chk_dterm__unapply(V *a) { (void)a; return F_Chk_dterm__unapply(a[0]); }
static V F_Chk_dterm__unapply_dgo(V a0, V a1) {
top:;
V s215 = a0;
if (TAG(s215) == 13) {
{ V t0 = FLD(s215, 0); V t1 = C2(1, FLD(s215, 1), a1); a0 = t0; a1 = t1; goto top; }
} else {
return C2(0, s215, a1);
}
}
static V W_Chk_dterm__unapply_dgo(V *a) { (void)a; return F_Chk_dterm__unapply_dgo(a[0], a[1]); }
static V F_Pair_dfst(V a2) {
top:;
V v216 = a2;
return FLD(v216, 0);
}
static V W_Pair_dfst(V *a) { (void)a; return F_Pair_dfst(a[2]); }
static V S218(void) { static V c; return STRC(c, "IO"); }
static V F_Chk_dvalid_dio(V a0, V a1) {
top:;
V s217 = a1;
if (TAG(s217) == 4 && TAG(FLD(s217, 0)) == 1 && (FLD(FLD(s217, 0), 0)) == 73 && TAG(FLD(FLD(s217, 0), 1)) == 1 && (FLD(FLD(FLD(s217, 0), 1), 0)) == 79 && (FLD(FLD(FLD(s217, 0), 1), 1)) == IMM(0)) {
return F_Chk_dvalid_dio_dbase(F_Chk_dbook__tld(a0, S218()));
} else {
return IMM(0);
}
}
static V W_Chk_dvalid_dio(V *a) { (void)a; return F_Chk_dvalid_dio(a[0], a[1]); }
static V F_Chk_dvalid_dio_dbase(V a0) {
top:;
V s219 = a0;
if (TAG(s219) == 1 && TAG(FLD(s219, 0)) == 0 && (FLD(FLD(s219, 0), 5)) == IMM(1)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dvalid_dio_dbase(V *a) { (void)a; return F_Chk_dvalid_dio_dbase(a[0]); }
static V F_Bool_dnot(V a0) {
top:;
V s220 = a0;
if ((s220) == IMM(0)) {
return IMM(1);
} else if ((s220) == IMM(1)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dnot(V *a) { (void)a; return F_Bool_dnot(a[0]); }
static V F_Main_dchecked_dgo(V a0, V a1, V a2, V a3) {
top:;
V s221 = a3;
if ((s221) == IMM(1)) {
return F_Main_demit__value(F_Chk_dshow__main(a2));
} else if ((s221) == IMM(0)) {
return F_Main_dbuild(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchecked_dgo(V *a) { (void)a; return F_Main_dchecked_dgo(a[0], a[1], a[2], a[3]); }
static V L223(V *a) {
return F_Main_dcompile(F_Main_dresolve(F_Mod_ddir(a[1]), F_Main_dparse(a[0])), C1(1, a[2]));
}
static V L222(V *a) {
return F_IO_dbind(F_Main_dload(64u, a[1]), mk_clo(L223, 3, 2, (V[]){a[2], a[0]}));
}
static V F_Main_dbuild(V a0, V a1) {
top:;
return F_IO_dbind(F_IO_dread__file(a0), mk_clo(L222, 3, 2, (V[]){a0, a1}));
}
static V W_Main_dbuild(V *a) { (void)a; return F_Main_dbuild(a[0], a[1]); }
static V F_Main_dparse(V a0) {
top:;
return F_Main_dparse_dfin(F_P_dfile(a0));
}
static V W_Main_dparse(V *a) { (void)a; return F_Main_dparse(a[0]); }
static V F_P_dfile(V a0) {
top:;
return F_P_dfile_dfin(apply(F_P_ddecls(), F_Lex_dall(a0)));
}
static V W_P_dfile(V *a) { (void)a; return F_P_dfile(a[0]); }
static V F_Lex_dall(V a0) {
top:;
return F_Lay_dfinish(F_Lay_dlines(F_Lex_dlines(a0), CN(0, 5, (V[]){IMM(0), 0u, IMM(0), C2(1, 0u, IMM(0)), IMM(0)})));
}
static V W_Lex_dall(V *a) { (void)a; return F_Lex_dall(a[0]); }
static V F_Lex_dlines(V a0) {
top:;
return F_Lex_dlines_dgo(F_String_dlines(a0), 1u);
}
static V W_Lex_dlines(V *a) { (void)a; return F_Lex_dlines(a[0]); }
static V F_String_dlines(V a0) {
top:;
return F_String_dsplit(a0, 10u);
}
static V W_String_dlines(V *a) { (void)a; return F_String_dlines(a[0]); }
static V F_String_dsplit(V a0, V a1) {
top:;
V s224 = a0;
if ((s224) == IMM(0)) {
return C2(1, IMM(0), IMM(0));
} else if (TAG(s224) == 1) {
return F_String_dsplit_dfin(FLD(s224, 0), F_String_dsplit(FLD(s224, 1), a1), F_Char_dis__eq(FLD(s224, 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_String_dsplit(V *a) { (void)a; return F_String_dsplit(a[0], a[1]); }
static V F_Char_dis__eq(V a0, V a1) {
top:;
V s225 = a0;
V s226 = a1;
{
return F_U32_dis__eq(s225, s226);
}
}
static V W_Char_dis__eq(V *a) { (void)a; return F_Char_dis__eq(a[0], a[1]); }
static V F_String_dsplit_dfin(V a0, V a1, V a2) {
top:;
V s227 = a2;
if ((s227) == IMM(0)) {
return F_String_dsplit_dpush(a0, a1);
} else if ((s227) == IMM(1)) {
return C2(1, IMM(0), a1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dsplit_dfin(V *a) { (void)a; return F_String_dsplit_dfin(a[0], a[1], a[2]); }
static V F_String_dsplit_dpush(V a0, V a1) {
top:;
V s228 = a1;
if ((s228) == IMM(0)) {
return C2(1, C2(1, a0, IMM(0)), IMM(0));
} else if (TAG(s228) == 1) {
return C2(1, C2(1, a0, FLD(s228, 0)), FLD(s228, 1));
} else { bend_fail("incomplete match"); }
}
static V W_String_dsplit_dpush(V *a) { (void)a; return F_String_dsplit_dpush(a[0], a[1]); }
static V F_Lex_dlines_dgo(V a0, V a1) {
top:;
V s229 = a0;
if ((s229) == IMM(0)) {
return IMM(0);
} else if (TAG(s229) == 1) {
return F_Lex_dlines_dput(C3(0, F_Lex_dindent(FLD(s229, 0)), a1, F_List_dreverse(F_Lex_dline(FLD(s229, 0), IMM(1), a1, IMM(0)))), F_Lex_dlines_dgo(FLD(s229, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlines_dgo(V *a) { (void)a; return F_Lex_dlines_dgo(a[0], a[1]); }
static V F_Lex_dline(V a0, V a1, V a2, V a3) {
top:;
V s230 = a0;
if ((s230) == IMM(0)) {
return a3;
} else if (TAG(s230) == 1) {
return F_Lex_dline_dgo(FLD(s230, 0), FLD(s230, 1), a1, a2, a3, F_Lex_dclass(FLD(s230, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline(V *a) { (void)a; return F_Lex_dline(a[0], a[1], a[2], a[3]); }
static V F_Lex_dclass(V a0) {
top:;
return F_Bool_dpick(F_Bool_dor(F_U32_dis__eq(a0, 32u), F_U32_dis__eq(a0, 9u)), 0u, F_Bool_dpick(F_U32_dis__eq(a0, 35u), 1u, F_Bool_dpick(F_Lex_dis__ids(a0), 2u, F_Bool_dpick(F_Char_dis__digit(a0), 3u, F_Bool_dpick(F_U32_dis__eq(a0, 39u), 4u, F_Bool_dpick(F_U32_dis__eq(a0, 34u), 5u, F_Bool_dpick(F_U32_dis__eq(a0, 13u), 0u, 6u)))))));
}
static V W_Lex_dclass(V *a) { (void)a; return F_Lex_dclass(a[0]); }
static V F_Char_dis__digit(V a0) {
top:;
V s231 = a0;
{
return F_Bool_dand(F_U32_dis__ge(s231, 48u), F_U32_dis__le(s231, 57u));
}
}
static V W_Char_dis__digit(V *a) { (void)a; return F_Char_dis__digit(a[0]); }
static V F_Lex_dis__ids(V a0) {
top:;
return F_Bool_dor(F_Char_dis__alpha(a0), F_U32_dis__eq(F_Char_dto__u32(a0), 95u));
}
static V W_Lex_dis__ids(V *a) { (void)a; return F_Lex_dis__ids(a[0]); }
static V F_Char_dto__u32(V a0) {
top:;
V s232 = a0;
{
return s232;
}
}
static V W_Char_dto__u32(V *a) { (void)a; return F_Char_dto__u32(a[0]); }
static V F_Char_dis__alpha(V a0) {
top:;
return F_Bool_dor(F_Char_dis__upper(a0), F_Char_dis__lower(a0));
}
static V W_Char_dis__alpha(V *a) { (void)a; return F_Char_dis__alpha(a[0]); }
static V F_Char_dis__lower(V a0) {
top:;
V s233 = a0;
{
return F_Bool_dand(F_U32_dis__ge(s233, 97u), F_U32_dis__le(s233, 122u));
}
}
static V W_Char_dis__lower(V *a) { (void)a; return F_Char_dis__lower(a[0]); }
static V F_Char_dis__upper(V a0) {
top:;
V s234 = a0;
{
return F_Bool_dand(F_U32_dis__ge(s234, 65u), F_U32_dis__le(s234, 90u));
}
}
static V W_Char_dis__upper(V *a) { (void)a; return F_Char_dis__upper(a[0]); }
static V F_Lex_dline_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s235 = a5;
if ((s235) == 0) {
return F_Lex_dline(a1, IMM(1), a3, a4);
} else if ((s235) == 1) {
return a4;
} else if ((s235) == 2) {
return F_Lex_dline_did(a2, a3, a4, F_Lex_did(C2(1, a0, a1), IMM(0)));
} else if ((s235) == 3) {
return F_Lex_dline_dnum(a2, a3, a4, F_Lex_ddigits(C2(1, a0, a1), 0u));
} else if ((s235) == 4) {
return F_Lex_dline_dchr(a2, a3, a4, F_Lex_dlit__char(a1));
} else if ((s235) == 5) {
return F_Lex_dline_dstr(a2, a3, a4, F_Lex_dstr(a1, IMM(0)));
} else if (nat_ge(s235, 6)) {
V v236 = C2(1, a0, a1);
return F_Lex_dline_dop(v236, a2, a3, a4, F_Lex_dop__of(v236));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dgo(V *a) { (void)a; return F_Lex_dline_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Lex_dop__of(V a0) {
top:;
return F_Lex_dop__of_dgo(F_Lex_dfind__op(F_Lex_dops3(), a0), a0);
}
static V W_Lex_dop__of(V *a) { (void)a; return F_Lex_dop__of(a[0]); }
static V S237(void) { static V c; return STRC(c, ".&."); }
static V S238(void) { static V c; return STRC(c, ".|."); }
static V S239(void) { static V c; return STRC(c, ".^."); }
static V S240(void) { static V c; return STRC(c, "<&>"); }
static V F_Lex_dops3(void) {
top:;
return C2(1, S237(), C2(1, S238(), C2(1, S239(), C2(1, S240(), IMM(0)))));
}
static V W_Lex_dops3(V *a) { (void)a; return F_Lex_dops3(); }
static V F_Lex_dfind__op(V a0, V a1) {
top:;
V s241 = a0;
if ((s241) == IMM(0)) {
return IMM(0);
} else if (TAG(s241) == 1) {
return F_Lex_dfind__op_dif(FLD(s241, 0), FLD(s241, 1), a1, F_String_dstarts__with(a1, FLD(s241, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dfind__op(V *a) { (void)a; return F_Lex_dfind__op(a[0], a[1]); }
static V F_String_dstarts__with(V a0, V a1) {
top:;
V s242 = a0;
V s243 = a1;
if ((s242) == IMM(0) && (s243) == IMM(0)) {
return IMM(1);
} else if ((s242) == IMM(0) && TAG(s243) == 1) {
return IMM(0);
} else if (TAG(s242) == 1 && (s243) == IMM(0)) {
return IMM(1);
} else if (TAG(s242) == 1 && TAG(s243) == 1) {
return F_String_dstarts__with_dif(FLD(s242, 1), FLD(s243, 1), F_Char_dis__eq(FLD(s242, 0), FLD(s243, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_String_dstarts__with(V *a) { (void)a; return F_String_dstarts__with(a[0], a[1]); }
static V F_String_dstarts__with_dif(V a0, V a1, V a2) {
top:;
V s244 = a2;
if ((s244) == IMM(0)) {
return IMM(0);
} else if ((s244) == IMM(1)) {
return F_String_dstarts__with(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dstarts__with_dif(V *a) { (void)a; return F_String_dstarts__with_dif(a[0], a[1], a[2]); }
static V F_Lex_dfind__op_dif(V a0, V a1, V a2, V a3) {
top:;
V s245 = a3;
if ((s245) == IMM(1)) {
return C1(1, a0);
} else if ((s245) == IMM(0)) {
return F_Lex_dfind__op(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dfind__op_dif(V *a) { (void)a; return F_Lex_dfind__op_dif(a[0], a[1], a[2], a[3]); }
static V F_Lex_dop__of_dgo(V a0, V a1) {
top:;
V s246 = a0;
if (TAG(s246) == 1) {
return FLD(s246, 0);
} else if ((s246) == IMM(0)) {
return F_Lex_dop__of_dtwo(F_Lex_dfind__op(F_Lex_dops2(), a1), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dop__of_dgo(V *a) { (void)a; return F_Lex_dop__of_dgo(a[0], a[1]); }
static V S247(void) { static V c; return STRC(c, "=>"); }
static V S248(void) { static V c; return STRC(c, "->"); }
static V S249(void) { static V c; return STRC(c, "<-"); }
static V S250(void) { static V c; return STRC(c, "<>"); }
static V S251(void) { static V c; return STRC(c, "<="); }
static V S252(void) { static V c; return STRC(c, ">="); }
static V S253(void) { static V c; return STRC(c, "=="); }
static V S254(void) { static V c; return STRC(c, "!="); }
static V S255(void) { static V c; return STRC(c, "++"); }
static V S256(void) { static V c; return STRC(c, "&&"); }
static V S257(void) { static V c; return STRC(c, "||"); }
static V S258(void) { static V c; return STRC(c, ">>"); }
static V S259(void) { static V c; return STRC(c, "<<"); }
static V F_Lex_dops2(void) {
top:;
return C2(1, S247(), C2(1, S248(), C2(1, S249(), C2(1, S250(), C2(1, S251(), C2(1, S252(), C2(1, S253(), C2(1, S254(), C2(1, S255(), C2(1, S256(), C2(1, S257(), C2(1, S258(), C2(1, S259(), IMM(0))))))))))))));
}
static V W_Lex_dops2(V *a) { (void)a; return F_Lex_dops2(); }
static V F_Lex_dop__of_dtwo(V a0, V a1) {
top:;
V s260 = a0;
if (TAG(s260) == 1) {
return FLD(s260, 0);
} else if ((s260) == IMM(0)) {
return F_String_dtake(a1, 1u);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dop__of_dtwo(V *a) { (void)a; return F_Lex_dop__of_dtwo(a[0], a[1]); }
static V F_String_dtake(V a0, V a1) {
top:;
V s261 = a0;
V s262 = a1;
if ((s261) == IMM(0)) {
return IMM(0);
} else if (TAG(s261) == 1 && (s262) == 0) {
return IMM(0);
} else if (TAG(s261) == 1 && nat_ge(s262, 1)) {
return C2(1, FLD(s261, 0), F_String_dtake(FLD(s261, 1), nat_subk(s262, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_String_dtake(V *a) { (void)a; return F_String_dtake(a[0], a[1]); }
static V F_Lex_dline_dop(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Lex_dline(F_String_ddrop(a0, F_String_dlength(a4)), IMM(0), a2, C2(1, C3(0, C1(7, a4), a1, a2), a3));
}
static V W_Lex_dline_dop(V *a) { (void)a; return F_Lex_dline_dop(a[0], a[1], a[2], a[3], a[4]); }
static V F_String_dlength(V a0) {
top:;
V s263 = a0;
if ((s263) == IMM(0)) {
return 0u;
} else if (TAG(s263) == 1) {
return nat_addk(F_String_dlength(FLD(s263, 1)), 1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dlength(V *a) { (void)a; return F_String_dlength(a[0]); }
static V F_String_ddrop(V a0, V a1) {
top:;
V s264 = a0;
V s265 = a1;
if ((s264) == IMM(0)) {
return IMM(0);
} else if (TAG(s264) == 1 && (s265) == 0) {
return C2(1, FLD(s264, 0), FLD(s264, 1));
} else if (TAG(s264) == 1 && nat_ge(s265, 1)) {
{ V t0 = FLD(s264, 1); V t1 = nat_subk(s265, 1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_String_ddrop(V *a) { (void)a; return F_String_ddrop(a[0], a[1]); }
static V F_Lex_dstr(V a0, V a1) {
top:;
V s266 = a0;
if ((s266) == IMM(0)) {
return C2(0, F_Str_drev(a1), IMM(0));
} else if (TAG(s266) == 1) {
return F_Lex_dstr_dif(FLD(s266, 0), FLD(s266, 1), a1, F_U32_dis__eq(FLD(s266, 0), 34u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dstr(V *a) { (void)a; return F_Lex_dstr(a[0], a[1]); }
static V F_Lex_dstr_dif(V a0, V a1, V a2, V a3) {
top:;
V s267 = a3;
if ((s267) == IMM(1)) {
return C2(0, F_Str_drev(a2), a1);
} else if ((s267) == IMM(0)) {
return F_Lex_dstr_dnext(a2, F_Lex_dlit__char(C2(1, a0, a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dstr_dif(V *a) { (void)a; return F_Lex_dstr_dif(a[0], a[1], a[2], a[3]); }
static V F_Lex_dlit__char(V a0) {
top:;
V s268 = a0;
if ((s268) == IMM(0)) {
return C2(0, 0u, IMM(0));
} else if (TAG(s268) == 1) {
return F_Lex_dlit__char_dif(FLD(s268, 0), FLD(s268, 1), F_U32_dis__eq(FLD(s268, 0), 92u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlit__char(V *a) { (void)a; return F_Lex_dlit__char(a[0]); }
static V F_Lex_dlit__char_dif(V a0, V a1, V a2) {
top:;
V s269 = a2;
if ((s269) == IMM(0)) {
return C2(0, a0, a1);
} else if ((s269) == IMM(1)) {
return F_Lex_dlit__char_desc(a1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlit__char_dif(V *a) { (void)a; return F_Lex_dlit__char_dif(a[0], a[1], a[2]); }
static V F_Lex_dlit__char_desc(V a0) {
top:;
V s270 = a0;
if ((s270) == IMM(0)) {
return C2(0, 92u, IMM(0));
} else if (TAG(s270) == 1) {
return C2(0, F_Lex_desc(FLD(s270, 0)), FLD(s270, 1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlit__char_desc(V *a) { (void)a; return F_Lex_dlit__char_desc(a[0]); }
static V F_Lex_desc(V a0) {
top:;
V v271 = a0;
return F_Bool_dpick(F_U32_dis__eq(v271, 110u), 10u, F_Bool_dpick(F_U32_dis__eq(v271, 116u), 9u, F_Bool_dpick(F_U32_dis__eq(v271, 114u), 13u, F_Bool_dpick(F_U32_dis__eq(v271, 48u), 0u, v271))));
}
static V W_Lex_desc(V *a) { (void)a; return F_Lex_desc(a[0]); }
static V F_Lex_dstr_dnext(V a0, V a1) {
top:;
V v272 = a1;
return F_Lex_dstr(FLD(v272, 1), C2(1, FLD(v272, 0), a0));
}
static V W_Lex_dstr_dnext(V *a) { (void)a; return F_Lex_dstr_dnext(a[0], a[1]); }
static V F_Str_drev(V a0) {
top:;
return F_String_dreverse(a0);
}
static V W_Str_drev(V *a) { (void)a; return F_Str_drev(a[0]); }
static V F_String_dreverse(V a0) {
top:;
return F_String_dreverse_dgo(a0, IMM(0));
}
static V W_String_dreverse(V *a) { (void)a; return F_String_dreverse(a[0]); }
static V F_String_dreverse_dgo(V a0, V a1) {
top:;
V s273 = a0;
if ((s273) == IMM(0)) {
return a1;
} else if (TAG(s273) == 1) {
{ V t0 = FLD(s273, 1); V t1 = C2(1, FLD(s273, 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_String_dreverse_dgo(V *a) { (void)a; return F_String_dreverse_dgo(a[0], a[1]); }
static V F_Lex_dline_dstr(V a0, V a1, V a2, V a3) {
top:;
V v274 = a3;
return F_Lex_dline(FLD(v274, 1), IMM(0), a1, C2(1, C3(0, C1(6, FLD(v274, 0)), a0, a1), a2));
}
static V W_Lex_dline_dstr(V *a) { (void)a; return F_Lex_dline_dstr(a[0], a[1], a[2], a[3]); }
static V F_Lex_dline_dchr(V a0, V a1, V a2, V a3) {
top:;
V v275 = a3;
return F_Lex_dline(F_Lex_ddrop1(FLD(v275, 1)), IMM(0), a1, C2(1, C3(0, C1(5, FLD(v275, 0)), a0, a1), a2));
}
static V W_Lex_dline_dchr(V *a) { (void)a; return F_Lex_dline_dchr(a[0], a[1], a[2], a[3]); }
static V F_Lex_ddrop1(V a0) {
top:;
V s276 = a0;
if ((s276) == IMM(0)) {
return IMM(0);
} else if (TAG(s276) == 1) {
return FLD(s276, 1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddrop1(V *a) { (void)a; return F_Lex_ddrop1(a[0]); }
static V F_Lex_ddigits(V a0, V a1) {
top:;
V s277 = a0;
if ((s277) == IMM(0)) {
return C2(0, a1, IMM(0));
} else if (TAG(s277) == 1) {
return F_Lex_ddigits_dif(FLD(s277, 0), FLD(s277, 1), a1, F_Char_dis__digit(FLD(s277, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddigits(V *a) { (void)a; return F_Lex_ddigits(a[0], a[1]); }
static V F_Lex_ddigits_dif(V a0, V a1, V a2, V a3) {
top:;
V s278 = a3;
if ((s278) == IMM(1)) {
return F_Lex_ddigits(a1, F_U32_dadd(F_U32_dmul(a2, 10u), F_U32_dsub(F_Char_dto__u32(a0), 48u)));
} else if ((s278) == IMM(0)) {
return C2(0, a2, C2(1, a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddigits_dif(V *a) { (void)a; return F_Lex_ddigits_dif(a[0], a[1], a[2], a[3]); }
static V W_U32_dsub(V *a) { (void)a; return F_U32_dsub(a[0], a[1]); }
static V W_U32_dmul(V *a) { (void)a; return F_U32_dmul(a[0], a[1]); }
static V F_Lex_dline_dnum(V a0, V a1, V a2, V a3) {
top:;
V v279 = a3;
return F_Lex_dline_dnum_dgo(a0, a1, a2, FLD(v279, 0), FLD(v279, 1));
}
static V W_Lex_dline_dnum(V *a) { (void)a; return F_Lex_dline_dnum(a[0], a[1], a[2], a[3]); }
static V F_Lex_dline_dnum_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s280 = a4;
if ((s280) == IMM(0)) {
return F_Lex_dline(IMM(0), IMM(0), a1, C2(1, C3(0, C1(3, a3), a0, a1), a2));
} else if (TAG(s280) == 1) {
return F_Lex_dline_dnum_dif(a0, a1, a2, a3, FLD(s280, 0), FLD(s280, 1), F_Bool_dpick(F_U32_dis__eq(FLD(s280, 0), 110u), 1u, F_Bool_dpick(F_U32_dis__eq(FLD(s280, 0), 46u), 2u, 0u)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnum_dgo(V *a) { (void)a; return F_Lex_dline_dnum_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V F_Lex_dline_dnum_dif(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s281 = a6;
if ((s281) == 0) {
return F_Lex_dline(C2(1, a4, a5), IMM(0), a1, C2(1, C3(0, C1(3, a3), a0, a1), a2));
} else if ((s281) == 1) {
return F_Lex_dline_dnat(a0, a1, a2, a3, a5);
} else if (nat_ge(s281, 2)) {
return F_Lex_dline_dflt(a0, a1, a2, a3, F_Lex_ddtext(a5, IMM(0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnum_dif(V *a) { (void)a; return F_Lex_dline_dnum_dif(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Lex_ddtext(V a0, V a1) {
top:;
V s282 = a0;
if ((s282) == IMM(0)) {
return C2(0, F_Str_drev(a1), IMM(0));
} else if (TAG(s282) == 1) {
return F_Lex_ddtext_dif(FLD(s282, 0), FLD(s282, 1), a1, F_Char_dis__digit(FLD(s282, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddtext(V *a) { (void)a; return F_Lex_ddtext(a[0], a[1]); }
static V F_Lex_ddtext_dif(V a0, V a1, V a2, V a3) {
top:;
V s283 = a3;
if ((s283) == IMM(1)) {
return F_Lex_ddtext(a1, C2(1, a0, a2));
} else if ((s283) == IMM(0)) {
return C2(0, F_Str_drev(a2), C2(1, a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddtext_dif(V *a) { (void)a; return F_Lex_ddtext_dif(a[0], a[1], a[2], a[3]); }
static V S285(void) { static V c; return STRC(c, "."); }
static V F_Lex_dline_dflt(V a0, V a1, V a2, V a3, V a4) {
top:;
V v284 = a4;
return F_Lex_dline(FLD(v284, 1), IMM(0), a1, C2(1, C3(0, C1(4, F_String_dappend(F_U32_dshow(a3), F_String_dappend(S285(), FLD(v284, 0)))), a0, a1), a2));
}
static V W_Lex_dline_dflt(V *a) { (void)a; return F_Lex_dline_dflt(a[0], a[1], a[2], a[3], a[4]); }
static V F_Lex_dline_dnat(V a0, V a1, V a2, V a3, V a4) {
top:;
V s286 = a4;
if ((s286) == IMM(0)) {
return F_Lex_dline(IMM(0), IMM(0), a1, C2(1, C3(0, C1(1, a3), a0, a1), a2));
} else if (TAG(s286) == 1) {
return F_Lex_dline_dnat_dif(a0, a1, a2, a3, FLD(s286, 0), FLD(s286, 1), F_U32_dis__eq(FLD(s286, 0), 43u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnat(V *a) { (void)a; return F_Lex_dline_dnat(a[0], a[1], a[2], a[3], a[4]); }
static V F_Lex_dline_dnat_dif(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s287 = a6;
if ((s287) == IMM(1)) {
return F_Lex_dline(a5, IMM(0), a1, C2(1, C3(0, C1(2, a3), a0, a1), a2));
} else if ((s287) == IMM(0)) {
return F_Lex_dline(C2(1, a4, a5), IMM(0), a1, C2(1, C3(0, C1(1, a3), a0, a1), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnat_dif(V *a) { (void)a; return F_Lex_dline_dnat_dif(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Lex_did(V a0, V a1) {
top:;
V s288 = a0;
if ((s288) == IMM(0)) {
return C2(0, F_Str_drev(a1), IMM(0));
} else if (TAG(s288) == 1) {
return F_Lex_did_dif(FLD(s288, 0), FLD(s288, 1), a1, F_Lex_dis__idc(FLD(s288, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_did(V *a) { (void)a; return F_Lex_did(a[0], a[1]); }
static V F_Lex_dis__idc(V a0) {
top:;
V v289 = F_Char_dto__u32(a0);
return F_Bool_dor(F_Char_dis__alpha(a0), F_Bool_dor(F_Char_dis__digit(a0), F_Bool_dor(F_U32_dis__eq(v289, 95u), F_U32_dis__eq(v289, 46u))));
}
static V W_Lex_dis__idc(V *a) { (void)a; return F_Lex_dis__idc(a[0]); }
static V F_Lex_did_dif(V a0, V a1, V a2, V a3) {
top:;
V s290 = a3;
if ((s290) == IMM(1)) {
return F_Lex_did(a1, C2(1, a0, a2));
} else if ((s290) == IMM(0)) {
return C2(0, F_Str_drev(a2), C2(1, a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_did_dif(V *a) { (void)a; return F_Lex_did_dif(a[0], a[1], a[2], a[3]); }
static V F_Lex_dline_did(V a0, V a1, V a2, V a3) {
top:;
V v291 = a3;
return F_Lex_dline(FLD(v291, 1), IMM(0), a1, C2(1, C3(0, C1(0, FLD(v291, 0)), a0, a1), a2));
}
static V W_Lex_dline_did(V *a) { (void)a; return F_Lex_dline_did(a[0], a[1], a[2], a[3]); }
static V F_List_dreverse(V a2) {
top:;
return F_List_dreverse_dgo(a2, IMM(0));
}
static V W_List_dreverse(V *a) { (void)a; return F_List_dreverse(a[2]); }
static V F_List_dreverse_dgo(V a2, V a3) {
top:;
V s292 = a2;
if ((s292) == IMM(0)) {
return a3;
} else if (TAG(s292) == 1) {
{ V t0 = FLD(s292, 1); V t1 = C2(1, FLD(s292, 0), a3); a2 = t0; a3 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_List_dreverse_dgo(V *a) { (void)a; return F_List_dreverse_dgo(a[2], a[3]); }
static V F_Lex_dindent(V a0) {
top:;
V s293 = a0;
if ((s293) == IMM(0)) {
return 0u;
} else if (TAG(s293) == 1) {
return F_Lex_dindent_dif(FLD(s293, 1), F_U32_dis__eq(FLD(s293, 0), 32u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dindent(V *a) { (void)a; return F_Lex_dindent(a[0]); }
static V F_Lex_dindent_dif(V a0, V a1) {
top:;
V s294 = a1;
if ((s294) == IMM(1)) {
return F_U32_dinc(F_Lex_dindent(a0));
} else if ((s294) == IMM(0)) {
return 0u;
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dindent_dif(V *a) { (void)a; return F_Lex_dindent_dif(a[0], a[1]); }
static V F_Lex_dlines_dput(V a0, V a1) {
top:;
V s295 = a0;
if ((FLD(s295, 2)) == IMM(0)) {
return a1;
} else if (TAG(FLD(s295, 2)) == 1) {
return C2(1, C3(0, FLD(s295, 0), FLD(s295, 1), C2(1, FLD(FLD(s295, 2), 0), FLD(FLD(s295, 2), 1))), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlines_dput(V *a) { (void)a; return F_Lex_dlines_dput(a[0], a[1]); }
static V F_Lay_dlines(V a0, V a1) {
top:;
V s296 = a0;
if ((s296) == IMM(0)) {
return a1;
} else if (TAG(s296) == 1) {
{ V t0 = FLD(s296, 1); V t1 = F_Lay_dline(FLD(s296, 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dlines(V *a) { (void)a; return F_Lay_dlines(a[0], a[1]); }
static V F_Lay_dline(V a0, V a1) {
top:;
V v297 = a0;
V v298 = a1;
return F_Lay_dline_dgo(FLD(v297, 0), FLD(v297, 1), FLD(v297, 2), CN(0, 5, (V[]){FLD(v298, 0), FLD(v298, 1), FLD(v298, 2), FLD(v298, 3), FLD(v298, 4)}), F_U32_dis__zero(FLD(v298, 1)));
}
static V W_Lay_dline(V *a) { (void)a; return F_Lay_dline(a[0], a[1]); }
static V F_Lay_dline_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s299 = a4;
if ((s299) == IMM(1)) {
return F_Lay_dtoks(a2, F_Lay_dstart(a3, a0, a1));
} else if ((s299) == IMM(0)) {
return F_Lay_dtoks(a2, a3);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dline_dgo(V *a) { (void)a; return F_Lay_dline_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V S303(void) { static V c; return STRC(c, ":"); }
static V F_Lay_dtoks(V a0, V a1) {
top:;
V s300 = a0;
if ((s300) == IMM(0)) {
return a1;
} else if (TAG(s300) == 1) {
V v301 = a1;
V v302 = F_U32_dadd(FLD(v301, 1), F_Lay_ddelta(FLD(FLD(s300, 0), 0)));
{ V t0 = FLD(s300, 1); V t1 = CN(0, 5, (V[]){C2(1, C3(0, FLD(FLD(s300, 0), 0), FLD(FLD(s300, 0), 1), FLD(FLD(s300, 0), 2)), FLD(v301, 0)), v302, F_Bool_dand(F_Lay_dis__sym(FLD(FLD(s300, 0), 0), S303()), F_U32_dis__zero(v302)), FLD(v301, 3), F_Lay_dis__op(FLD(FLD(s300, 0), 0))}); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dtoks(V *a) { (void)a; return F_Lay_dtoks(a[0], a[1]); }
static V S305(void) { static V c; return STRC(c, "->"); }
static V S306(void) { static V c; return STRC(c, "=>"); }
static V S307(void) { static V c; return STRC(c, "&"); }
static V S308(void) { static V c; return STRC(c, "|"); }
static V S309(void) { static V c; return STRC(c, "++"); }
static V S310(void) { static V c; return STRC(c, "<>"); }
static V S311(void) { static V c; return STRC(c, "&&"); }
static V S312(void) { static V c; return STRC(c, "||"); }
static V S313(void) { static V c; return STRC(c, "+"); }
static V S314(void) { static V c; return STRC(c, "*"); }
static V S315(void) { static V c; return STRC(c, ","); }
static V S316(void) { static V c; return STRC(c, "="); }
static V S317(void) { static V c; return STRC(c, "<-"); }
static V F_Lay_dis__op(V a0) {
top:;
V s304 = a0;
if (TAG(s304) == 7) {
return F_List_dcontains(mk_clo(W_String_deq, 2, 0, 0), C2(1, S305(), C2(1, S306(), C2(1, S307(), C2(1, S308(), C2(1, S309(), C2(1, S310(), C2(1, S311(), C2(1, S312(), C2(1, S313(), C2(1, S314(), C2(1, S315(), C2(1, S316(), C2(1, S317(), IMM(0)))))))))))))), FLD(s304, 0));
} else {
return IMM(0);
}
}
static V W_Lay_dis__op(V *a) { (void)a; return F_Lay_dis__op(a[0]); }
static V F_List_dcontains(V a1, V a2, V a3) {
top:;
V s318 = a2;
if ((s318) == IMM(0)) {
return IMM(0);
} else if (TAG(s318) == 1) {
return F_Bool_dor(apply(apply(a1, FLD(s318, 0)), a3), F_List_dcontains(a1, FLD(s318, 1), a3));
} else { bend_fail("incomplete match"); }
}
static V W_List_dcontains(V *a) { (void)a; return F_List_dcontains(a[1], a[2], a[3]); }
static V F_Lay_dis__sym(V a0, V a1) {
top:;
V s319 = a0;
if (TAG(s319) == 7) {
return F_Str_deq(FLD(s319, 0), a1);
} else {
return IMM(0);
}
}
static V W_Lay_dis__sym(V *a) { (void)a; return F_Lay_dis__sym(a[0], a[1]); }
static V F_Str_deq(V a0, V a1) {
top:;
return F_String_deq(a0, a1);
}
static V W_Str_deq(V *a) { (void)a; return F_Str_deq(a[0], a[1]); }
static V S320(void) { static V c; return STRC(c, "("); }
static V S321(void) { static V c; return STRC(c, "["); }
static V S322(void) { static V c; return STRC(c, "{"); }
static V S323(void) { static V c; return STRC(c, ")"); }
static V S324(void) { static V c; return STRC(c, "]"); }
static V S325(void) { static V c; return STRC(c, "}"); }
static V F_Lay_ddelta(V a0) {
top:;
return F_Bool_dpick(F_Bool_dor(F_Lay_dis__sym(a0, S320()), F_Bool_dor(F_Lay_dis__sym(a0, S321()), F_Lay_dis__sym(a0, S322()))), 1u, F_Bool_dpick(F_Bool_dor(F_Lay_dis__sym(a0, S323()), F_Bool_dor(F_Lay_dis__sym(a0, S324()), F_Lay_dis__sym(a0, S325()))), 4294967295u, 0u));
}
static V W_Lay_ddelta(V *a) { (void)a; return F_Lay_ddelta(a[0]); }
static V F_Lay_dstart(V a0, V a1, V a2) {
top:;
V v326 = a0;
V v327 = F_Lay_dtop(FLD(v326, 3));
return F_Lay_dstart_dop(FLD(v326, 0), FLD(v326, 1), FLD(v326, 2), FLD(v326, 3), a1, a2, F_U32_dcmp(a1, v327), FLD(v326, 4));
}
static V W_Lay_dstart(V *a) { (void)a; return F_Lay_dstart(a[0], a[1], a[2]); }
static V F_Lay_dstart_dop(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s328 = a7;
if ((s328) == IMM(1)) {
return CN(0, 5, (V[]){a0, a1, a2, a3, IMM(0)});
} else if ((s328) == IMM(0)) {
return F_Lay_dstart_dgo(a0, a1, a2, a3, a4, a5, a6);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dstart_dop(V *a) { (void)a; return F_Lay_dstart_dop(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V F_Lay_dstart_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s329 = a6;
if ((s329) == IMM(2)) {
return F_Lay_dstart_dgt(a0, a1, a2, a3, a4, a5, a2);
} else if ((s329) == IMM(1)) {
return CN(0, 5, (V[]){C2(1, F_Lay_dtok(IMM(8), a5), a0), a1, a2, a3, IMM(0)});
} else if ((s329) == IMM(0)) {
return F_Lay_ddedent(a1, a2, a5, F_Lay_dpop(a3, a4, C2(1, F_Lay_dtok(IMM(8), a5), a0), a5));
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dstart_dgo(V *a) { (void)a; return F_Lay_dstart_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Lay_dtok(V a0, V a1) {
top:;
return C3(0, a0, IMM(1), a1);
}
static V W_Lay_dtok(V *a) { (void)a; return F_Lay_dtok(a[0], a[1]); }
static V F_Lay_dpop(V a0, V a1, V a2, V a3) {
top:;
V s330 = a0;
if ((s330) == IMM(0)) {
return C2(0, IMM(0), a2);
} else if (TAG(s330) == 1) {
return F_Lay_dpop_dif(FLD(s330, 0), FLD(s330, 1), a1, a2, a3, F_U32_dis__gt(FLD(s330, 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dpop(V *a) { (void)a; return F_Lay_dpop(a[0], a[1], a[2], a[3]); }
static V F_Lay_dpop_dif(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s331 = a5;
if ((s331) == IMM(1)) {
return F_Lay_dpop(a1, a2, C2(1, F_Lay_dtok(IMM(10), a4), a3), a4);
} else if ((s331) == IMM(0)) {
return C2(0, C2(1, a0, a1), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dpop_dif(V *a) { (void)a; return F_Lay_dpop_dif(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Lay_ddedent(V a0, V a1, V a2, V a3) {
top:;
V v332 = a3;
return CN(0, 5, (V[]){FLD(v332, 1), a0, a1, FLD(v332, 0), IMM(0)});
}
static V W_Lay_ddedent(V *a) { (void)a; return F_Lay_ddedent(a[0], a[1], a[2], a[3]); }
static V F_Lay_dstart_dgt(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s333 = a6;
if ((s333) == IMM(1)) {
return CN(0, 5, (V[]){C2(1, F_Lay_dtok(IMM(9), a5), a0), a1, a2, C2(1, a4, a3), IMM(0)});
} else if ((s333) == IMM(0)) {
return CN(0, 5, (V[]){a0, a1, a2, a3, IMM(0)});
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dstart_dgt(V *a) { (void)a; return F_Lay_dstart_dgt(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Lay_dtop(V a0) {
top:;
V s334 = a0;
if ((s334) == IMM(0)) {
return 0u;
} else if (TAG(s334) == 1) {
return FLD(s334, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dtop(V *a) { (void)a; return F_Lay_dtop(a[0]); }
static V F_Lay_dfinish(V a0) {
top:;
V v335 = a0;
return F_Lay_dfinish_dgo(F_Lay_dpop(FLD(v335, 3), 0u, C2(1, F_Lay_dtok(IMM(8), 0u), FLD(v335, 0)), 0u));
}
static V W_Lay_dfinish(V *a) { (void)a; return F_Lay_dfinish(a[0]); }
static V F_Lay_dfinish_dgo(V a0) {
top:;
V v336 = a0;
return F_List_dreverse(C2(1, F_Lay_dtok(IMM(11), 0u), FLD(v336, 1)));
}
static V W_Lay_dfinish_dgo(V *a) { (void)a; return F_Lay_dfinish_dgo(a[0]); }
static V L338(V *a) {
return F_P_ddecls_dgo(F_P_dstuck(F_P_dtok__kind(a[0])));
}
static V L337(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L338, 1, 0, 0));
}
static V F_P_ddecls(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L337, 1, 0, 0));
}
static V W_P_ddecls(V *a) { (void)a; return F_P_ddecls(); }
static V F_P_dtok__kind(V a0) {
top:;
V v339 = a0;
return FLD(v339, 0);
}
static V W_P_dtok__kind(V *a) { (void)a; return F_P_dtok__kind(a[0]); }
static V F_P_dstuck(V a0) {
top:;
V s340 = a0;
if (TAG(s340) == 12) {
return IMM(1);
} else if ((s340) == IMM(11)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dstuck(V *a) { (void)a; return F_P_dstuck(a[0]); }
static V L343(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L342(V *a) {
return F_Parser_dbind(F_P_ddecls(), mk_clo(L343, 2, 1, (V[]){a[0]}));
}
static V F_P_ddecls_dgo(V a0) {
top:;
V s341 = a0;
if ((s341) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s341) == IMM(0)) {
return F_Parser_dbind(F_P_ddecl(), mk_clo(L342, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddecls_dgo(V *a) { (void)a; return F_P_ddecls_dgo(a[0]); }
static V L344(V *a) {
return C2(0, a[0], a[1]);
}
static V F_Parser_dpure(V a1) {
top:;
return mk_clo(L344, 2, 1, (V[]){a1});
}
static V W_Parser_dpure(V *a) { (void)a; return F_Parser_dpure(a[1]); }
static V L345(V *a) {
return F_Parser_dgo(apply(a[1], a[4]), a[0]);
}
static V F_Parser_dbind(V a2, V a3) {
top:;
return mk_clo(L345, 5, 4, (V[]){a3, a2, 0, 0});
}
static V W_Parser_dbind(V *a) { (void)a; return F_Parser_dbind(a[2], a[3]); }
static V F_Parser_dgo(V a2, V a3) {
top:;
V v346 = a2;
return apply(apply(a3, FLD(v346, 0)), FLD(v346, 1));
}
static V W_Parser_dgo(V *a) { (void)a; return F_Parser_dgo(a[2], a[3]); }
static V S348(void) { static V c; return STRC(c, "@"); }
static V L347(V *a) {
return F_P_ddecl_dat(F_P_dtok__is(a[0], S348()), a[0]);
}
static V F_P_ddecl(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L347, 1, 0, 0));
}
static V W_P_ddecl(V *a) { (void)a; return F_P_ddecl(); }
static V F_P_dtok__is(V a0, V a1) {
top:;
V s349 = a0;
if (TAG(FLD(s349, 0)) == 7) {
return F_Str_deq(FLD(FLD(s349, 0), 0), a1);
} else {
return IMM(0);
}
}
static V W_P_dtok__is(V *a) { (void)a; return F_P_dtok__is(a[0], a[1]); }
static V L353(V *a) {
return F_P_ddecl();
}
static V L352(V *a) {
return F_Parser_dbind(F_P_dnls(), mk_clo(L353, 1, 0, 0));
}
static V L351(V *a) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L352, 1, 0, 0));
}
static V S354(void) { static V c; return STRC(c, "def"); }
static V S355(void) { static V c; return STRC(c, "type"); }
static V S356(void) { static V c; return STRC(c, "law"); }
static V S357(void) { static V c; return STRC(c, "import"); }
static V F_P_ddecl_dat(V a0, V a1) {
top:;
V s350 = a0;
if ((s350) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L351, 1, 0, 0));
} else if ((s350) == IMM(0)) {
return F_P_ddecl_dgo(F_P_dtok__which__id(a1, C2(1, S354(), C2(1, S355(), C2(1, S356(), C2(1, S357(), IMM(0)))))));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddecl_dat(V *a) { (void)a; return F_P_ddecl_dat(a[0], a[1]); }
static V F_P_dtok__which__id(V a0, V a1) {
top:;
V s358 = a0;
if (TAG(FLD(s358, 0)) == 0) {
return F_P_dwhich(FLD(FLD(s358, 0), 0), a1);
} else {
return 99u;
}
}
static V W_P_dtok__which__id(V *a) { (void)a; return F_P_dtok__which__id(a[0], a[1]); }
static V F_P_dwhich(V a0, V a1) {
top:;
V s359 = a1;
if ((s359) == IMM(0)) {
return 0u;
} else if (TAG(s359) == 1) {
return F_P_dwhich_dif(a0, FLD(s359, 1), F_String_deq(a0, FLD(s359, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dwhich(V *a) { (void)a; return F_P_dwhich(a[0], a[1]); }
static V F_P_dwhich_dif(V a0, V a1, V a2) {
top:;
V s360 = a2;
if ((s360) == IMM(1)) {
return 0u;
} else if ((s360) == IMM(0)) {
return nat_addk(F_P_dwhich(a0, a1), 1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dwhich_dif(V *a) { (void)a; return F_P_dwhich_dif(a[0], a[1], a[2]); }
static V S362(void) { static V c; return STRC(c, "expected a declaration"); }
static V S364(void) { static V c; return STRC(c, ""); }
static V S365(void) { static V c; return STRC(c, ""); }
static V L363(V *a) {
return F_Parser_dpure(C2(4, S364(), S365()));
}
static V F_P_ddecl_dgo(V a0) {
top:;
V s361 = a0;
if ((s361) == 0) {
return F_P_ddef();
} else if ((s361) == 1) {
return F_P_dtype();
} else if ((s361) == 2) {
return F_P_dlaw();
} else if ((s361) == 3) {
return F_P_dimport();
} else if (nat_ge(s361, 4)) {
return F_Parser_dbind(F_P_derr(S362()), mk_clo(L363, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddecl_dgo(V *a) { (void)a; return F_P_ddecl_dgo(a[0]); }
static V L366(V *a) {
return F_P_derr_dgo(a[0], a[1]);
}
static V F_P_derr(V a0) {
top:;
return mk_clo(L366, 2, 1, (V[]){a0});
}
static V W_P_derr(V *a) { (void)a; return F_P_derr(a[0]); }
static V S368(void) { static V c; return STRC(c, "line "); }
static V S369(void) { static V c; return STRC(c, ": "); }
static V S370(void) { static V c; return STRC(c, " (got '"); }
static V S371(void) { static V c; return STRC(c, "')"); }
static V S372(void) { static V c; return STRC(c, " (at end)"); }
static V F_P_derr_dgo(V a0, V a1) {
top:;
V s367 = a1;
if (TAG(s367) == 1 && TAG(FLD(FLD(s367, 0), 0)) == 12) {
return C2(0, IMM(0), C2(1, C3(0, C1(12, FLD(FLD(FLD(s367, 0), 0), 0)), FLD(FLD(s367, 0), 1), FLD(FLD(s367, 0), 2)), IMM(0)));
} else if (TAG(s367) == 1) {
return C2(0, IMM(0), C2(1, C3(0, C1(12, F_String_dappend(S368(), F_String_dappend(F_U32_dshow(FLD(FLD(s367, 0), 2)), F_String_dappend(S369(), F_String_dappend(a0, F_String_dappend(S370(), F_String_dappend(F_TK_dshow(FLD(FLD(s367, 0), 0)), S371()))))))), FLD(FLD(s367, 0), 1), FLD(FLD(s367, 0), 2)), IMM(0)));
} else if ((s367) == IMM(0)) {
return C2(0, IMM(0), C2(1, C3(0, C1(12, F_String_dappend(a0, S372())), IMM(1), 0u), IMM(0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_derr_dgo(V *a) { (void)a; return F_P_derr_dgo(a[0], a[1]); }
static V S374(void) { static V c; return STRC(c, "n"); }
static V S375(void) { static V c; return STRC(c, "n+"); }
static V S376(void) { static V c; return STRC(c, "'"); }
static V S377(void) { static V c; return STRC(c, "'"); }
static V S378(void) { static V c; return STRC(c, "\042"); }
static V S379(void) { static V c; return STRC(c, "\042"); }
static V S380(void) { static V c; return STRC(c, "<NL>\012"); }
static V S381(void) { static V c; return STRC(c, "<IN>"); }
static V S382(void) { static V c; return STRC(c, "<DE>"); }
static V S383(void) { static V c; return STRC(c, "<EOF>"); }
static V S384(void) { static V c; return STRC(c, "<ERR "); }
static V S385(void) { static V c; return STRC(c, ">"); }
static V F_TK_dshow(V a0) {
top:;
V s373 = a0;
if (TAG(s373) == 0) {
return FLD(s373, 0);
} else if (TAG(s373) == 1) {
return F_String_dappend(F_U32_dshow(FLD(s373, 0)), S374());
} else if (TAG(s373) == 2) {
return F_String_dappend(F_U32_dshow(FLD(s373, 0)), S375());
} else if (TAG(s373) == 3) {
return F_U32_dshow(FLD(s373, 0));
} else if (TAG(s373) == 4) {
return FLD(s373, 0);
} else if (TAG(s373) == 5) {
return F_String_dappend(S376(), F_String_dappend(F_U32_dshow(FLD(s373, 0)), S377()));
} else if (TAG(s373) == 6) {
return F_String_dappend(S378(), F_String_dappend(FLD(s373, 0), S379()));
} else if (TAG(s373) == 7) {
return FLD(s373, 0);
} else if ((s373) == IMM(8)) {
return S380();
} else if ((s373) == IMM(9)) {
return S381();
} else if ((s373) == IMM(10)) {
return S382();
} else if ((s373) == IMM(11)) {
return S383();
} else if (TAG(s373) == 12) {
return F_String_dappend(S384(), F_String_dappend(FLD(s373, 0), S385()));
} else { bend_fail("incomplete match"); }
}
static V W_TK_dshow(V *a) { (void)a; return F_TK_dshow(a[0]); }
static V S389(void) { static V c; return STRC(c, "as"); }
static V L391(V *a) {
return F_Parser_dpure(C2(4, a[1], a[0]));
}
static V L390(V *a) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L391, 3, 2, (V[]){a[1], a[0]}));
}
static V L388(V *a) {
return F_Parser_dbind(F_P_dimport_dalias(F_P_dtok__is__id(a[1], S389())), mk_clo(L390, 2, 1, (V[]){a[0]}));
}
static V L387(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L388, 2, 1, (V[]){a[0]}));
}
static V L386(V *a) {
return F_Parser_dbind(F_P_dimport_dpath(), mk_clo(L387, 1, 0, 0));
}
static V F_P_dimport(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L386, 1, 0, 0));
}
static V W_P_dimport(V *a) { (void)a; return F_P_dimport(); }
static V L392(V *a) {
return C2(0, IMM(0), F_P_dskip__line_dgo(a[0]));
}
static V F_P_dskip__line(void) {
top:;
return mk_clo(L392, 1, 0, 0);
}
static V W_P_dskip__line(V *a) { (void)a; return F_P_dskip__line(); }
static V F_P_dskip__line_dgo(V a0) {
top:;
V s393 = a0;
if ((s393) == IMM(0)) {
return IMM(0);
} else if (TAG(s393) == 1 && (FLD(FLD(s393, 0), 0)) == IMM(8)) {
return C2(1, C3(0, IMM(8), FLD(FLD(s393, 0), 1), FLD(FLD(s393, 0), 2)), FLD(s393, 1));
} else if (TAG(s393) == 1 && (FLD(FLD(s393, 0), 0)) == IMM(10)) {
return C2(1, C3(0, IMM(10), FLD(FLD(s393, 0), 1), FLD(FLD(s393, 0), 2)), FLD(s393, 1));
} else if (TAG(s393) == 1 && (FLD(FLD(s393, 0), 0)) == IMM(11)) {
return C2(1, C3(0, IMM(11), FLD(FLD(s393, 0), 1), FLD(FLD(s393, 0), 2)), FLD(s393, 1));
} else if (TAG(s393) == 1 && TAG(FLD(FLD(s393, 0), 0)) == 12) {
return C2(1, C3(0, C1(12, FLD(FLD(FLD(s393, 0), 0), 0)), FLD(FLD(s393, 0), 1), FLD(FLD(s393, 0), 2)), FLD(s393, 1));
} else if (TAG(s393) == 1 && (FLD(FLD(s393, 0), 0)) == IMM(9)) {
return F_P_dskip__block_dgo(FLD(s393, 1), 1u);
} else if (TAG(s393) == 1) {
{ V t0 = FLD(s393, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__line_dgo(V *a) { (void)a; return F_P_dskip__line_dgo(a[0]); }
static V F_P_dskip__block_dgo(V a0, V a1) {
top:;
V s394 = a0;
if ((s394) == IMM(0)) {
return IMM(0);
} else if (TAG(s394) == 1 && (FLD(FLD(s394, 0), 0)) == IMM(9)) {
{ V t0 = FLD(s394, 1); V t1 = F_U32_dinc(a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s394) == 1 && (FLD(FLD(s394, 0), 0)) == IMM(10)) {
return F_P_dskip__block_dde(FLD(s394, 1), a1, F_U32_dis__eq(a1, 1u));
} else if (TAG(s394) == 1 && (FLD(FLD(s394, 0), 0)) == IMM(11)) {
return C2(1, C3(0, IMM(11), FLD(FLD(s394, 0), 1), FLD(FLD(s394, 0), 2)), FLD(s394, 1));
} else if (TAG(s394) == 1) {
{ V t0 = FLD(s394, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__block_dgo(V *a) { (void)a; return F_P_dskip__block_dgo(a[0], a[1]); }
static V F_P_dskip__block_dde(V a0, V a1, V a2) {
top:;
V s395 = a2;
if ((s395) == IMM(1)) {
return a0;
} else if ((s395) == IMM(0)) {
return F_P_dskip__block_dgo(a0, F_U32_dsub(a1, 1u));
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__block_dde(V *a) { (void)a; return F_P_dskip__block_dde(a[0], a[1], a[2]); }
static V F_P_dtok__is__id(V a0, V a1) {
top:;
V s396 = a0;
if (TAG(FLD(s396, 0)) == 0) {
return F_Str_deq(FLD(FLD(s396, 0), 0), a1);
} else {
return IMM(0);
}
}
static V W_P_dtok__is__id(V *a) { (void)a; return F_P_dtok__is__id(a[0], a[1]); }
static V L398(V *a) {
return F_P_dident();
}
static V S399(void) { static V c; return STRC(c, ""); }
static V F_P_dimport_dalias(V a0) {
top:;
V s397 = a0;
if ((s397) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L398, 1, 0, 0));
} else if ((s397) == IMM(0)) {
return F_Parser_dpure(S399());
} else { bend_fail("incomplete match"); }
}
static V W_P_dimport_dalias(V *a) { (void)a; return F_P_dimport_dalias(a[0]); }
static V L400(V *a) {
return F_P_dident_dk(F_P_dtok__kind(a[0]));
}
static V F_P_dident(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L400, 1, 0, 0));
}
static V W_P_dident(V *a) { (void)a; return F_P_dident(); }
static V L402(V *a) {
return F_Parser_dpure(a[0]);
}
static V S403(void) { static V c; return STRC(c, "expected an identifier"); }
static V S405(void) { static V c; return STRC(c, ""); }
static V L404(V *a) {
return F_Parser_dpure(S405());
}
static V F_P_dident_dk(V a0) {
top:;
V s401 = a0;
if (TAG(s401) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L402, 2, 1, (V[]){FLD(s401, 0)}));
} else {
return F_Parser_dbind(F_P_derr(S403()), mk_clo(L404, 1, 0, 0));
}
}
static V W_P_dident_dk(V *a) { (void)a; return F_P_dident_dk(a[0]); }
static V L406(V *a) {
return F_P_dskip_dgo(a[0]);
}
static V F_P_dskip(void) {
top:;
return mk_clo(L406, 1, 0, 0);
}
static V W_P_dskip(V *a) { (void)a; return F_P_dskip(); }
static V F_P_dskip_dgo(V a0) {
top:;
V s407 = a0;
if ((s407) == IMM(0)) {
return C2(0, IMM(0), IMM(0));
} else if (TAG(s407) == 1) {
return F_P_dskip_dif(C3(0, FLD(FLD(s407, 0), 0), FLD(FLD(s407, 0), 1), FLD(FLD(s407, 0), 2)), FLD(s407, 1), F_P_dstuck(FLD(FLD(s407, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip_dgo(V *a) { (void)a; return F_P_dskip_dgo(a[0]); }
static V F_P_dskip_dif(V a0, V a1, V a2) {
top:;
V s408 = a2;
if ((s408) == IMM(1)) {
return C2(0, IMM(0), C2(1, a0, a1));
} else if ((s408) == IMM(0)) {
return C2(0, IMM(0), a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip_dif(V *a) { (void)a; return F_P_dskip_dif(a[0], a[1], a[2]); }
static V L409(V *a) {
return F_P_dpeek_dgo(a[0]);
}
static V F_P_dpeek(void) {
top:;
return mk_clo(L409, 1, 0, 0);
}
static V W_P_dpeek(V *a) { (void)a; return F_P_dpeek(); }
static V F_P_dpeek_dgo(V a0) {
top:;
V s410 = a0;
if ((s410) == IMM(0)) {
return C2(0, F_P_deof__tok(), IMM(0));
} else if (TAG(s410) == 1) {
return C2(0, FLD(s410, 0), C2(1, FLD(s410, 0), FLD(s410, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpeek_dgo(V *a) { (void)a; return F_P_dpeek_dgo(a[0]); }
static V F_P_deof__tok(void) {
top:;
return C3(0, IMM(11), IMM(1), 0u);
}
static V W_P_deof__tok(V *a) { (void)a; return F_P_deof__tok(); }
static V L411(V *a) {
return F_P_dimport_dpath_dgo(a[0]);
}
static V F_P_dimport_dpath(void) {
top:;
return mk_clo(L411, 1, 0, 0);
}
static V W_P_dimport_dpath(V *a) { (void)a; return F_P_dimport_dpath(); }
static V S413(void) { static V c; return STRC(c, "as"); }
static V S414(void) { static V c; return STRC(c, ""); }
static V F_P_dimport_dpath_dgo(V a0) {
top:;
V s412 = a0;
if (TAG(s412) == 1 && TAG(FLD(FLD(s412, 0), 0)) == 0) {
return F_P_dimport_dpath_did(FLD(FLD(FLD(s412, 0), 0), 0), FLD(FLD(s412, 0), 1), FLD(FLD(s412, 0), 2), FLD(s412, 1), F_Str_deq(FLD(FLD(FLD(s412, 0), 0), 0), S413()));
} else if (TAG(s412) == 1 && TAG(FLD(FLD(s412, 0), 0)) == 7) {
return F_P_dimport_dpath_dcat(FLD(FLD(FLD(s412, 0), 0), 0), F_P_dimport_dpath_dgo(FLD(s412, 1)));
} else if (TAG(s412) == 1 && TAG(FLD(FLD(s412, 0), 0)) == 3) {
return F_P_dimport_dpath_dcat(F_U32_dshow(FLD(FLD(FLD(s412, 0), 0), 0)), F_P_dimport_dpath_dgo(FLD(s412, 1)));
} else {
return C2(0, S414(), s412);
}
}
static V W_P_dimport_dpath_dgo(V *a) { (void)a; return F_P_dimport_dpath_dgo(a[0]); }
static V F_P_dimport_dpath_dcat(V a0, V a1) {
top:;
V v415 = a1;
return C2(0, F_String_dappend(a0, FLD(v415, 0)), FLD(v415, 1));
}
static V W_P_dimport_dpath_dcat(V *a) { (void)a; return F_P_dimport_dpath_dcat(a[0], a[1]); }
static V S417(void) { static V c; return STRC(c, ""); }
static V F_P_dimport_dpath_did(V a0, V a1, V a2, V a3, V a4) {
top:;
V s416 = a4;
if ((s416) == IMM(1)) {
return C2(0, S417(), C2(1, C3(0, C1(0, a0), a1, a2), a3));
} else if ((s416) == IMM(0)) {
return F_P_dimport_dpath_dcat(a0, F_P_dimport_dpath_dgo(a3));
} else { bend_fail("incomplete match"); }
}
static V W_P_dimport_dpath_did(V *a) { (void)a; return F_P_dimport_dpath_did(a[0], a[1], a[2], a[3], a[4]); }
static V S420(void) { static V c; return STRC(c, ":"); }
static V L423(V *a) {
return F_Parser_dpure(C2(2, a[0], a[1]));
}
static V L422(V *a) {
return F_Parser_dbind(F_P_dlaw_dlines(), mk_clo(L423, 2, 1, (V[]){a[0]}));
}
static V L421(V *a) {
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L422, 2, 1, (V[]){a[0]}));
}
static V L419(V *a) {
return F_Parser_dbind(F_P_dexpect(S420()), mk_clo(L421, 2, 1, (V[]){a[0]}));
}
static V L418(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L419, 1, 0, 0));
}
static V F_P_dlaw(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L418, 1, 0, 0));
}
static V W_P_dlaw(V *a) { (void)a; return F_P_dlaw(); }
static V L425(V *a) {
return F_P_dlaw_dgo(a[0], F_Bool_dpick(F_P_dis__de(a[0]), 0u, F_Bool_dpick(F_P_dstuck(F_P_dtok__kind(a[0])), 1u, 2u)));
}
static V L424(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L425, 1, 0, 0));
}
static V F_P_dlaw_dlines(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L424, 1, 0, 0));
}
static V W_P_dlaw_dlines(V *a) { (void)a; return F_P_dlaw_dlines(); }
static V F_P_dis__de(V a0) {
top:;
V s426 = a0;
if ((FLD(s426, 0)) == IMM(10)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dis__de(V *a) { (void)a; return F_P_dis__de(a[0]); }
static V L428(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S429(void) { static V c; return STRC(c, "for"); }
static V F_P_dlaw_dgo(V a0, V a1) {
top:;
V s427 = a1;
if ((s427) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L428, 1, 0, 0));
} else if ((s427) == 1) {
return F_Parser_dpure(IMM(0));
} else if (nat_ge(s427, 2)) {
return F_P_dlaw_dline(F_P_dtok__which__id(a0, C2(1, S429(), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlaw_dgo(V *a) { (void)a; return F_P_dlaw_dgo(a[0], a[1]); }
static V L434(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L433(V *a) {
return F_Parser_dbind(F_P_dlaw_dlines(), mk_clo(L434, 2, 1, (V[]){a[0]}));
}
static V L432(V *a) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L433, 2, 1, (V[]){a[0]}));
}
static V L431(V *a) {
return F_Parser_dbind(F_P_dparam(), mk_clo(L432, 1, 0, 0));
}
static V L435(V *a) {
return F_P_dlaw_dlines();
}
static V F_P_dlaw_dline(V a0) {
top:;
V s430 = a0;
if ((s430) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L431, 1, 0, 0));
} else if (nat_ge(s430, 1)) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L435, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlaw_dline(V *a) { (void)a; return F_P_dlaw_dline(a[0]); }
static V S441(void) { static V c; return STRC(c, ":"); }
static V L440(V *a) {
return F_P_dparam_dty(a[1], a[0], F_P_dtok__is(a[2], S441()));
}
static V L439(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L440, 3, 2, (V[]){a[0], a[1]}));
}
static V L438(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L439, 2, 1, (V[]){a[0]}));
}
static V L437(V *a) {
return F_Parser_dbind(F_P_dparam_dskip__mode(a[0]), mk_clo(L438, 2, 1, (V[]){a[0]}));
}
static V L436(V *a) {
return F_Parser_dbind(F_Parser_dpure(F_P_dparam_dmode(a[0])), mk_clo(L437, 1, 0, 0));
}
static V F_P_dparam(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L436, 1, 0, 0));
}
static V W_P_dparam(V *a) { (void)a; return F_P_dparam(); }
static V L444(V *a) {
return F_Parser_dpure(C3(0, a[1], a[0], F_P_dhead(a[2])));
}
static V L443(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L444, 3, 2, (V[]){a[0], a[1]}));
}
static V S445(void) { static V c; return STRC(c, ""); }
static V F_P_dparam_dty(V a0, V a1, V a2) {
top:;
V s442 = a2;
if ((s442) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L443, 3, 2, (V[]){a1, a0}));
} else if ((s442) == IMM(0)) {
return F_Parser_dpure(C3(0, a0, F_Bool_dpick(F_U32_dis__zero(a1), 4u, a1), S445()));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparam_dty(V *a) { (void)a; return F_P_dparam_dty(a[0], a[1], a[2]); }
static V S447(void) { static V c; return STRC(c, ""); }
static V F_P_dhead(V a0) {
top:;
V s446 = a0;
if (TAG(s446) == 0) {
return FLD(s446, 0);
} else if (TAG(s446) == 5 && TAG(FLD(s446, 0)) == 0) {
return FLD(FLD(s446, 0), 0);
} else if (TAG(s446) == 14) {
return FLD(s446, 0);
} else {
return S447();
}
}
static V W_P_dhead(V *a) { (void)a; return F_P_dhead(a[0]); }
static V F_P_dexpr(void) {
top:;
return F_P_dbin(1u);
}
static V W_P_dexpr(V *a) { (void)a; return F_P_dexpr(); }
static V L448(V *a) {
return F_P_dbin_dloop(a[0], a[1]);
}
static V F_P_dbin(V a0) {
top:;
return F_Parser_dbind(F_P_dterm(), mk_clo(L448, 2, 1, (V[]){a0}));
}
static V W_P_dbin(V *a) { (void)a; return F_P_dbin(a[0]); }
static V L449(V *a) {
return F_P_dbin_dloop_dop(a[1], a[0], F_P_dtok__op(a[2]));
}
static V F_P_dbin_dloop(V a0, V a1) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L449, 3, 2, (V[]){a1, a0}));
}
static V W_P_dbin_dloop(V *a) { (void)a; return F_P_dbin_dloop(a[0], a[1]); }
static V S451(void) { static V c; return STRC(c, ""); }
static V F_P_dtok__op(V a0) {
top:;
V s450 = a0;
if (TAG(FLD(s450, 0)) == 7 && (FLD(s450, 1)) == IMM(1)) {
return F_P_dop__find(FLD(FLD(s450, 0), 0), F_P_dops());
} else {
return C3(0, S451(), 0u, IMM(0));
}
}
static V W_P_dtok__op(V *a) { (void)a; return F_P_dtok__op(a[0]); }
static V S452(void) { static V c; return STRC(c, "->"); }
static V S453(void) { static V c; return STRC(c, "|"); }
static V S454(void) { static V c; return STRC(c, "&"); }
static V S455(void) { static V c; return STRC(c, "<&>"); }
static V S456(void) { static V c; return STRC(c, "||"); }
static V S457(void) { static V c; return STRC(c, "&&"); }
static V S458(void) { static V c; return STRC(c, "<>"); }
static V S459(void) { static V c; return STRC(c, "++"); }
static V S460(void) { static V c; return STRC(c, "<"); }
static V S461(void) { static V c; return STRC(c, "<="); }
static V S462(void) { static V c; return STRC(c, ">"); }
static V S463(void) { static V c; return STRC(c, ">="); }
static V S464(void) { static V c; return STRC(c, ".|."); }
static V S465(void) { static V c; return STRC(c, ".^."); }
static V S466(void) { static V c; return STRC(c, ".&."); }
static V S467(void) { static V c; return STRC(c, "<<"); }
static V S468(void) { static V c; return STRC(c, ">>"); }
static V S469(void) { static V c; return STRC(c, "+"); }
static V S470(void) { static V c; return STRC(c, "-"); }
static V S471(void) { static V c; return STRC(c, "*"); }
static V S472(void) { static V c; return STRC(c, "/"); }
static V S473(void) { static V c; return STRC(c, "%"); }
static V F_P_dops(void) {
top:;
return C2(1, C3(0, S452(), 1u, IMM(1)), C2(1, C3(0, S453(), 2u, IMM(1)), C2(1, C3(0, S454(), 3u, IMM(1)), C2(1, C3(0, S455(), 3u, IMM(1)), C2(1, C3(0, S456(), 4u, IMM(0)), C2(1, C3(0, S457(), 5u, IMM(0)), C2(1, C3(0, S458(), 6u, IMM(1)), C2(1, C3(0, S459(), 6u, IMM(1)), C2(1, C3(0, S460(), 7u, IMM(0)), C2(1, C3(0, S461(), 7u, IMM(0)), C2(1, C3(0, S462(), 7u, IMM(0)), C2(1, C3(0, S463(), 7u, IMM(0)), C2(1, C3(0, S464(), 8u, IMM(0)), C2(1, C3(0, S465(), 9u, IMM(0)), C2(1, C3(0, S466(), 10u, IMM(0)), C2(1, C3(0, S467(), 11u, IMM(0)), C2(1, C3(0, S468(), 11u, IMM(0)), C2(1, C3(0, S469(), 12u, IMM(0)), C2(1, C3(0, S470(), 12u, IMM(0)), C2(1, C3(0, S471(), 13u, IMM(0)), C2(1, C3(0, S472(), 13u, IMM(0)), C2(1, C3(0, S473(), 13u, IMM(0)), IMM(0)))))))))))))))))))))));
}
static V W_P_dops(V *a) { (void)a; return F_P_dops(); }
static V S475(void) { static V c; return STRC(c, ""); }
static V F_P_dop__find(V a0, V a1) {
top:;
V s474 = a1;
if ((s474) == IMM(0)) {
return C3(0, S475(), 0u, IMM(0));
} else if (TAG(s474) == 1) {
return F_P_dop__find_dif(a0, FLD(s474, 1), C3(0, FLD(FLD(s474, 0), 0), FLD(FLD(s474, 0), 1), FLD(FLD(s474, 0), 2)), F_String_deq(a0, FLD(FLD(s474, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dop__find(V *a) { (void)a; return F_P_dop__find(a[0], a[1]); }
static V F_P_dop__find_dif(V a0, V a1, V a2, V a3) {
top:;
V s476 = a3;
if ((s476) == IMM(1)) {
return a2;
} else if ((s476) == IMM(0)) {
return F_P_dop__find(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dop__find_dif(V *a) { (void)a; return F_P_dop__find_dif(a[0], a[1], a[2], a[3]); }
static V F_P_dbin_dloop_dop(V a0, V a1, V a2) {
top:;
V v477 = a2;
return F_P_dbin_dloop_dgo(a0, a1, FLD(v477, 0), FLD(v477, 1), FLD(v477, 2), F_Bool_dand(F_U32_dis__ne(FLD(v477, 1), 0u), F_U32_dis__ge(FLD(v477, 1), a0)));
}
static V W_P_dbin_dloop_dop(V *a) { (void)a; return F_P_dbin_dloop_dop(a[0], a[1], a[2]); }
static V L480(V *a) {
return F_P_dbin_dloop(a[2], F_P_dmk__bin(a[1], a[0], a[3]));
}
static V L479(V *a) {
return F_Parser_dbind(F_P_dbin(F_Bool_dpick(a[4], a[3], F_U32_dinc(a[3]))), mk_clo(L480, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_P_dbin_dloop_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s478 = a5;
if ((s478) == IMM(0)) {
return F_Parser_dpure(a1);
} else if ((s478) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L479, 6, 5, (V[]){a1, a2, a0, a3, a4}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbin_dloop_dgo(V *a) { (void)a; return F_P_dbin_dloop_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S481(void) { static V c; return STRC(c, "->"); }
static V S482(void) { static V c; return STRC(c, "|"); }
static V S483(void) { static V c; return STRC(c, "&"); }
static V S484(void) { static V c; return STRC(c, "<&>"); }
static V S485(void) { static V c; return STRC(c, "||"); }
static V S486(void) { static V c; return STRC(c, "&&"); }
static V S487(void) { static V c; return STRC(c, "<>"); }
static V S488(void) { static V c; return STRC(c, "++"); }
static V F_P_dmk__bin(V a0, V a1, V a2) {
top:;
return F_P_dmk__bin_dgo(a0, a1, a2, F_P_dwhich(a0, C2(1, S481(), C2(1, S482(), C2(1, S483(), C2(1, S484(), C2(1, S485(), C2(1, S486(), C2(1, S487(), C2(1, S488(), IMM(0)))))))))));
}
static V W_P_dmk__bin(V *a) { (void)a; return F_P_dmk__bin(a[0], a[1], a[2]); }
static V S490(void) { static V c; return STRC(c, "->"); }
static V S491(void) { static V c; return STRC(c, "|"); }
static V S492(void) { static V c; return STRC(c, "&"); }
static V S493(void) { static V c; return STRC(c, "#q"); }
static V S494(void) { static V c; return STRC(c, "Bool.or"); }
static V S495(void) { static V c; return STRC(c, "Bool.and"); }
static V S496(void) { static V c; return STRC(c, "Con"); }
static V S497(void) { static V c; return STRC(c, "String.append"); }
static V F_P_dmk__bin_dgo(V a0, V a1, V a2, V a3) {
top:;
V s489 = a3;
if ((s489) == 0) {
return C2(14, S490(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s489) == 1) {
return C2(14, S491(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s489) == 2) {
return C2(14, S492(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s489) == 3) {
return C2(14, S493(), IMM(0));
} else if ((s489) == 4) {
return C2(5, C1(0, S494()), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s489) == 5) {
return C2(5, C1(0, S495()), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s489) == 6) {
return C2(6, S496(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s489) == 7) {
return C2(5, C1(0, S497()), C2(1, a1, C2(1, a2, IMM(0))));
} else if (nat_ge(s489, 8)) {
return C3(12, a0, a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_P_dmk__bin_dgo(V *a) { (void)a; return F_P_dmk__bin_dgo(a[0], a[1], a[2], a[3]); }
static V L498(V *a) {
return F_P_dpostfix(a[0]);
}
static V F_P_dterm(void) {
top:;
return F_Parser_dbind(F_P_dprimary(), mk_clo(L498, 1, 0, 0));
}
static V W_P_dterm(V *a) { (void)a; return F_P_dterm(); }
static V L499(V *a) {
return F_P_dpostfix_dt(a[0], a[1]);
}
static V F_P_dpostfix(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L499, 2, 1, (V[]){a0}));
}
static V W_P_dpostfix(V *a) { (void)a; return F_P_dpostfix(a[0]); }
static V S500(void) { static V c; return STRC(c, "("); }
static V S501(void) { static V c; return STRC(c, "!"); }
static V S502(void) { static V c; return STRC(c, "["); }
static V F_P_dpostfix_dt(V a0, V a1) {
top:;
return F_P_dpostfix_dk(a0, F_Bool_dpick(F_P_dtok__sp(a1), 9u, F_P_dtok__which(a1, C2(1, S500(), C2(1, S501(), C2(1, S502(), IMM(0)))))));
}
static V W_P_dpostfix_dt(V *a) { (void)a; return F_P_dpostfix_dt(a[0], a[1]); }
static V F_P_dtok__which(V a0, V a1) {
top:;
V s503 = a0;
if (TAG(FLD(s503, 0)) == 7) {
return F_P_dwhich(FLD(FLD(s503, 0), 0), a1);
} else {
return 99u;
}
}
static V W_P_dtok__which(V *a) { (void)a; return F_P_dtok__which(a[0], a[1]); }
static V F_P_dtok__sp(V a0) {
top:;
V v504 = a0;
return FLD(v504, 1);
}
static V W_P_dtok__sp(V *a) { (void)a; return F_P_dtok__sp(a[0]); }
static V S507(void) { static V c; return STRC(c, ")"); }
static V L508(V *a) {
return F_P_dpostfix(C2(5, a[0], a[1]));
}
static V L506(V *a) {
return F_Parser_dbind(F_P_dlist(S507()), mk_clo(L508, 2, 1, (V[]){a[0]}));
}
static V L509(V *a) {
return F_P_dpostfix(a[0]);
}
static V S512(void) { static V c; return STRC(c, "]"); }
static V S514(void) { static V c; return STRC(c, "Array.get"); }
static V S515(void) { static V c; return STRC(c, "U32"); }
static V L513(V *a) {
return F_P_dpostfix(C2(5, C1(0, S514()), C2(1, C2(14, S515(), IMM(0)), C2(1, a[1], C2(1, a[0], IMM(0))))));
}
static V L511(V *a) {
return F_Parser_dbind(F_P_dexpect(S512()), mk_clo(L513, 3, 2, (V[]){a[1], a[0]}));
}
static V L510(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L511, 2, 1, (V[]){a[0]}));
}
static V F_P_dpostfix_dk(V a0, V a1) {
top:;
V s505 = a1;
if ((s505) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L506, 2, 1, (V[]){a0}));
} else if ((s505) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L509, 2, 1, (V[]){a0}));
} else if ((s505) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L510, 2, 1, (V[]){a0}));
} else if (nat_ge(s505, 3)) {
return F_Parser_dpure(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dpostfix_dk(V *a) { (void)a; return F_P_dpostfix_dk(a[0], a[1]); }
static V L516(V *a) {
return F_P_dexpect_dif(a[0], F_P_dtok__is(a[1], a[0]));
}
static V F_P_dexpect(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L516, 2, 1, (V[]){a0}));
}
static V W_P_dexpect(V *a) { (void)a; return F_P_dexpect(a[0]); }
static V S518(void) { static V c; return STRC(c, "expected '"); }
static V S519(void) { static V c; return STRC(c, "'"); }
static V F_P_dexpect_dif(V a0, V a1) {
top:;
V s517 = a1;
if ((s517) == IMM(1)) {
return F_P_dskip();
} else if ((s517) == IMM(0)) {
return F_P_derr(F_String_dappend(S518(), F_String_dappend(a0, S519())));
} else { bend_fail("incomplete match"); }
}
static V W_P_dexpect_dif(V *a) { (void)a; return F_P_dexpect_dif(a[0], a[1]); }
static V L520(V *a) {
return F_P_dlist_dstuck(a[0], a[1], F_P_dstuck(F_P_dtok__kind(a[1])));
}
static V F_P_dlist(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L520, 2, 1, (V[]){a0}));
}
static V W_P_dlist(V *a) { (void)a; return F_P_dlist(a[0]); }
static V S522(void) { static V c; return STRC(c, "unterminated list"); }
static V L523(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dlist_dstuck(V a0, V a1, V a2) {
top:;
V s521 = a2;
if ((s521) == IMM(1)) {
return F_Parser_dbind(F_P_derr(S522()), mk_clo(L523, 1, 0, 0));
} else if ((s521) == IMM(0)) {
return F_P_dlist_dgo(a0, F_P_dtok__is(a1, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlist_dstuck(V *a) { (void)a; return F_P_dlist_dstuck(a[0], a[1], a[2]); }
static V L525(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dlist_dgo(V a0, V a1) {
top:;
V s524 = a1;
if ((s524) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L525, 1, 0, 0));
} else if ((s524) == IMM(0)) {
return F_P_dlist_ditem(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dlist_dgo(V *a) { (void)a; return F_P_dlist_dgo(a[0], a[1]); }
static V S527(void) { static V c; return STRC(c, ","); }
static V L529(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L528(V *a) {
return F_Parser_dbind(F_P_dlist_dmore(a[1], a[2]), mk_clo(L529, 2, 1, (V[]){a[0]}));
}
static V L526(V *a) {
return F_Parser_dbind(F_P_deat(S527()), mk_clo(L528, 3, 2, (V[]){a[1], a[0]}));
}
static V F_P_dlist_ditem(V a0) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L526, 2, 1, (V[]){a0}));
}
static V W_P_dlist_ditem(V *a) { (void)a; return F_P_dlist_ditem(a[0]); }
static V L531(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dlist_dmore(V a0, V a1) {
top:;
V s530 = a1;
if ((s530) == IMM(1)) {
return F_P_dlist(a0);
} else if ((s530) == IMM(0)) {
return F_Parser_dbind(F_P_dexpect(a0), mk_clo(L531, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlist_dmore(V *a) { (void)a; return F_P_dlist_dmore(a[0], a[1]); }
static V L532(V *a) {
return F_P_deat_dif(F_P_dtok__is(a[1], a[0]));
}
static V F_P_deat(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L532, 2, 1, (V[]){a0}));
}
static V W_P_deat(V *a) { (void)a; return F_P_deat(a[0]); }
static V L534(V *a) {
return F_Parser_dpure(IMM(1));
}
static V F_P_deat_dif(V a0) {
top:;
V s533 = a0;
if ((s533) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L534, 1, 0, 0));
} else if ((s533) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_deat_dif(V *a) { (void)a; return F_P_deat_dif(a[0]); }
static V L535(V *a) {
return F_P_dprimary_dk(F_P_dtok__kind(a[0]));
}
static V F_P_dprimary(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L535, 1, 0, 0));
}
static V W_P_dprimary(V *a) { (void)a; return F_P_dprimary(); }
static V L538(V *a) {
return F_P_dafter__id(a[0], a[1]);
}
static V L537(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L538, 2, 1, (V[]){a[0]}));
}
static V L539(V *a) {
return F_Parser_dpure(C1(1, a[0]));
}
static V L540(V *a) {
return F_Parser_dpure(C1(2, a[0]));
}
static V L542(V *a) {
return F_Parser_dpure(C2(11, a[0], a[1]));
}
static V L541(V *a) {
return F_Parser_dbind(F_P_dterm(), mk_clo(L542, 2, 1, (V[]){a[0]}));
}
static V L543(V *a) {
return F_Parser_dpure(C1(3, a[0]));
}
static V L544(V *a) {
return F_Parser_dpure(C1(1, a[0]));
}
static V L545(V *a) {
return F_Parser_dpure(C1(4, a[0]));
}
static V S546(void) { static V c; return STRC(c, "("); }
static V S547(void) { static V c; return STRC(c, "["); }
static V S548(void) { static V c; return STRC(c, "{"); }
static V S549(void) { static V c; return STRC(c, "~"); }
static V S550(void) { static V c; return STRC(c, "+"); }
static V S551(void) { static V c; return STRC(c, "-"); }
static V S552(void) { static V c; return STRC(c, "@"); }
static V S553(void) { static V c; return STRC(c, "&"); }
static V S554(void) { static V c; return STRC(c, "\077"); }
static V S555(void) { static V c; return STRC(c, "expected an expression"); }
static V S557(void) { static V c; return STRC(c, ""); }
static V L556(V *a) {
return F_Parser_dpure(C1(15, S557()));
}
static V F_P_dprimary_dk(V a0) {
top:;
V s536 = a0;
if (TAG(s536) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L537, 2, 1, (V[]){FLD(s536, 0)}));
} else if (TAG(s536) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L539, 2, 1, (V[]){FLD(s536, 0)}));
} else if (TAG(s536) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L540, 2, 1, (V[]){FLD(s536, 0)}));
} else if (TAG(s536) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L541, 2, 1, (V[]){FLD(s536, 0)}));
} else if (TAG(s536) == 4) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L543, 2, 1, (V[]){FLD(s536, 0)}));
} else if (TAG(s536) == 5) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L544, 2, 1, (V[]){FLD(s536, 0)}));
} else if (TAG(s536) == 6) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L545, 2, 1, (V[]){FLD(s536, 0)}));
} else if (TAG(s536) == 7) {
return F_P_dprimary_dsym(F_P_dwhich(FLD(s536, 0), C2(1, S546(), C2(1, S547(), C2(1, S548(), C2(1, S549(), C2(1, S550(), C2(1, S551(), C2(1, S552(), C2(1, S553(), C2(1, S554(), IMM(0))))))))))));
} else {
return F_Parser_dbind(F_P_derr(S555()), mk_clo(L556, 1, 0, 0));
}
}
static V W_P_dprimary_dk(V *a) { (void)a; return F_P_dprimary_dk(a[0]); }
static V L559(V *a) {
return F_P_dterm();
}
static V L560(V *a) {
return F_P_dterm();
}
static V L562(V *a) {
return F_Parser_dpure(F_P_dneg(a[0]));
}
static V L561(V *a) {
return F_Parser_dbind(F_P_dterm(), mk_clo(L562, 1, 0, 0));
}
static V L563(V *a) {
return F_P_ddep();
}
static V L565(V *a) {
return F_P_damp_dgo(a[0]);
}
static V L564(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L565, 1, 0, 0));
}
static V S568(void) { static V c; return STRC(c, ""); }
static V L567(V *a) {
return F_Parser_dpure(C2(14, S568(), IMM(0)));
}
static V L566(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L567, 1, 0, 0));
}
static V S569(void) { static V c; return STRC(c, "unexpected symbol"); }
static V S571(void) { static V c; return STRC(c, ""); }
static V L570(V *a) {
return F_Parser_dpure(C1(15, S571()));
}
static V F_P_dprimary_dsym(V a0) {
top:;
V s558 = a0;
if ((s558) == 0) {
return F_P_dparen();
} else if ((s558) == 1) {
return F_P_dbrack();
} else if ((s558) == 2) {
return F_P_dbrace();
} else if ((s558) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L559, 1, 0, 0));
} else if ((s558) == 4) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L560, 1, 0, 0));
} else if ((s558) == 5) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L561, 1, 0, 0));
} else if ((s558) == 6) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L563, 1, 0, 0));
} else if ((s558) == 7) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L564, 1, 0, 0));
} else if ((s558) == 8) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L566, 1, 0, 0));
} else if (nat_ge(s558, 9)) {
return F_Parser_dbind(F_P_derr(S569()), mk_clo(L570, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dprimary_dsym(V *a) { (void)a; return F_P_dprimary_dsym(a[0]); }
static V S574(void) { static V c; return STRC(c, "#q"); }
static V L573(V *a) {
return F_Parser_dpure(C2(14, S574(), IMM(0)));
}
static V F_P_damp_dgo(V a0) {
top:;
V s572 = a0;
if (TAG(FLD(s572, 0)) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L573, 1, 0, 0));
} else {
return F_P_ddep();
}
}
static V W_P_damp_dgo(V *a) { (void)a; return F_P_damp_dgo(a[0]); }
static V S575(void) { static V c; return STRC(c, "-"); }
static V S577(void) { static V c; return STRC(c, "+"); }
static V S580(void) { static V c; return STRC(c, ":"); }
static V S583(void) { static V c; return STRC(c, ""); }
static V L582(V *a) {
return F_Parser_dpure(C2(14, S583(), IMM(0)));
}
static V L581(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L582, 1, 0, 0));
}
static V L579(V *a) {
return F_Parser_dbind(F_P_dexpect(S580()), mk_clo(L581, 1, 0, 0));
}
static V L578(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L579, 1, 0, 0));
}
static V L576(V *a) {
return F_Parser_dbind(F_P_deat(S577()), mk_clo(L578, 1, 0, 0));
}
static V F_P_ddep(void) {
top:;
return F_Parser_dbind(F_P_deat(S575()), mk_clo(L576, 1, 0, 0));
}
static V W_P_ddep(V *a) { (void)a; return F_P_ddep(); }
static V S585(void) { static V c; return STRC(c, "-"); }
static V F_P_dneg(V a0) {
top:;
V s584 = a0;
if (TAG(s584) == 1) {
return C1(1, F_U32_dsub(0u, FLD(s584, 0)));
} else if (TAG(s584) == 3) {
return C1(3, F_String_dappend(S585(), FLD(s584, 0)));
} else {
return s584;
}
}
static V W_P_dneg(V *a) { (void)a; return F_P_dneg(a[0]); }
static V S588(void) { static V c; return STRC(c, "=="); }
static V L587(V *a) {
return F_P_dbrace_dgo(F_P_dtok__is(a[0], S588()));
}
static V L586(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L587, 1, 0, 0));
}
static V F_P_dbrace(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L586, 1, 0, 0));
}
static V W_P_dbrace(V *a) { (void)a; return F_P_dbrace(); }
static V S591(void) { static V c; return STRC(c, "}"); }
static V S593(void) { static V c; return STRC(c, ""); }
static V L592(V *a) {
return F_Parser_dpure(C2(14, S593(), IMM(0)));
}
static V L590(V *a) {
return F_Parser_dbind(F_P_dexpect(S591()), mk_clo(L592, 1, 0, 0));
}
static V F_P_dbrace_dgo(V a0) {
top:;
V s589 = a0;
if ((s589) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L590, 1, 0, 0));
} else if ((s589) == IMM(0)) {
return F_P_dbrace_dbody();
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrace_dgo(V *a) { (void)a; return F_P_dbrace_dgo(a[0]); }
static V S596(void) { static V c; return STRC(c, "=="); }
static V S597(void) { static V c; return STRC(c, "!="); }
static V S598(void) { static V c; return STRC(c, ":"); }
static V L595(V *a) {
return F_P_dbrace_dtail(a[0], F_P_dtok__which(a[1], C2(1, S596(), C2(1, S597(), C2(1, S598(), IMM(0))))));
}
static V L594(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L595, 2, 1, (V[]){a[0]}));
}
static V F_P_dbrace_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L594, 1, 0, 0));
}
static V W_P_dbrace_dbody(V *a) { (void)a; return F_P_dbrace_dbody(); }
static V S602(void) { static V c; return STRC(c, ":"); }
static V S605(void) { static V c; return STRC(c, "}"); }
static V S607(void) { static V c; return STRC(c, ""); }
static V L606(V *a) {
return F_Parser_dpure(C2(14, S607(), IMM(0)));
}
static V L604(V *a) {
return F_Parser_dbind(F_P_dexpect(S605()), mk_clo(L606, 1, 0, 0));
}
static V L603(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L604, 1, 0, 0));
}
static V L601(V *a) {
return F_Parser_dbind(F_P_dexpect(S602()), mk_clo(L603, 1, 0, 0));
}
static V L600(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L601, 1, 0, 0));
}
static V S610(void) { static V c; return STRC(c, ":"); }
static V S613(void) { static V c; return STRC(c, "}"); }
static V S615(void) { static V c; return STRC(c, ""); }
static V L614(V *a) {
return F_Parser_dpure(C2(14, S615(), IMM(0)));
}
static V L612(V *a) {
return F_Parser_dbind(F_P_dexpect(S613()), mk_clo(L614, 1, 0, 0));
}
static V L611(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L612, 1, 0, 0));
}
static V L609(V *a) {
return F_Parser_dbind(F_P_dexpect(S610()), mk_clo(L611, 1, 0, 0));
}
static V L608(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L609, 1, 0, 0));
}
static V S618(void) { static V c; return STRC(c, "}"); }
static V L619(V *a) {
return F_Parser_dpure(C2(13, a[1], F_P_dhead(a[0])));
}
static V L617(V *a) {
return F_Parser_dbind(F_P_dexpect(S618()), mk_clo(L619, 3, 2, (V[]){a[1], a[0]}));
}
static V L616(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L617, 2, 1, (V[]){a[0]}));
}
static V S620(void) { static V c; return STRC(c, "}"); }
static V L621(V *a) {
return F_Parser_dpure(a[0]);
}
static V F_P_dbrace_dtail(V a0, V a1) {
top:;
V s599 = a1;
if ((s599) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L600, 1, 0, 0));
} else if ((s599) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L608, 1, 0, 0));
} else if ((s599) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L616, 2, 1, (V[]){a0}));
} else if (nat_ge(s599, 3)) {
return F_Parser_dbind(F_P_dexpect(S620()), mk_clo(L621, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrace_dtail(V *a) { (void)a; return F_P_dbrace_dtail(a[0], a[1]); }
static V S624(void) { static V c; return STRC(c, "]"); }
static V L623(V *a) {
return F_P_dbrack_dgo(F_P_dtok__is(a[0], S624()));
}
static V L622(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L623, 1, 0, 0));
}
static V F_P_dbrack(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L622, 1, 0, 0));
}
static V W_P_dbrack(V *a) { (void)a; return F_P_dbrack(); }
static V S627(void) { static V c; return STRC(c, "Nil"); }
static V L626(V *a) {
return F_Parser_dpure(C2(6, S627(), IMM(0)));
}
static V F_P_dbrack_dgo(V a0) {
top:;
V s625 = a0;
if ((s625) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L626, 1, 0, 0));
} else if ((s625) == IMM(0)) {
return F_P_dbrack_dbody();
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrack_dgo(V *a) { (void)a; return F_P_dbrack_dgo(a[0]); }
static V S630(void) { static V c; return STRC(c, ":"); }
static V L629(V *a) {
return F_P_dbrack_dtail(a[0], F_P_dtok__is(a[1], S630()));
}
static V L628(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L629, 2, 1, (V[]){a[0]}));
}
static V F_P_dbrack_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L628, 1, 0, 0));
}
static V W_P_dbrack_dbody(V *a) { (void)a; return F_P_dbrack_dbody(); }
static V S632(void) { static V c; return STRC(c, ","); }
static V S634(void) { static V c; return STRC(c, "]"); }
static V L635(V *a) {
return F_Parser_dpure(F_P_delist(C2(1, a[0], a[1])));
}
static V L633(V *a) {
return F_Parser_dbind(F_P_dlist(S634()), mk_clo(L635, 2, 1, (V[]){a[0]}));
}
static V F_P_dbrack_dtail(V a0, V a1) {
top:;
V s631 = a1;
if ((s631) == IMM(1)) {
return F_P_darr(a0);
} else if ((s631) == IMM(0)) {
return F_Parser_dbind(F_P_deat(S632()), mk_clo(L633, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrack_dtail(V *a) { (void)a; return F_P_dbrack_dtail(a[0], a[1]); }
static V S637(void) { static V c; return STRC(c, "Nil"); }
static V S638(void) { static V c; return STRC(c, "Con"); }
static V F_P_delist(V a0) {
top:;
V s636 = a0;
if ((s636) == IMM(0)) {
return C2(6, S637(), IMM(0));
} else if (TAG(s636) == 1) {
return C2(6, S638(), C2(1, FLD(s636, 0), C2(1, F_P_delist(FLD(s636, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_delist(V *a) { (void)a; return F_P_delist(a[0]); }
static V S644(void) { static V c; return STRC(c, "^"); }
static V S646(void) { static V c; return STRC(c, "]"); }
static V S648(void) { static V c; return STRC(c, "Array.new"); }
static V S649(void) { static V c; return STRC(c, ""); }
static V L647(V *a) {
return F_Parser_dpure(C2(5, C1(0, S648()), C2(1, C2(14, S649(), IMM(0)), C2(1, a[1], C2(1, a[0], IMM(0))))));
}
static V L645(V *a) {
return F_Parser_dbind(F_P_dexpect(S646()), mk_clo(L647, 3, 2, (V[]){a[0], a[1]}));
}
static V L643(V *a) {
return F_Parser_dbind(F_P_darr_dsize(F_P_dtok__is(a[1], S644()), a[2]), mk_clo(L645, 2, 1, (V[]){a[0]}));
}
static V L642(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L643, 3, 2, (V[]){a[0], a[1]}));
}
static V L641(V *a) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L642, 3, 2, (V[]){a[0], a[1]}));
}
static V L640(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L641, 2, 1, (V[]){a[0]}));
}
static V L639(V *a) {
return F_Parser_dbind(F_P_dterm(), mk_clo(L640, 2, 1, (V[]){a[0]}));
}
static V F_P_darr(V a0) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L639, 2, 1, (V[]){a0}));
}
static V W_P_darr(V *a) { (void)a; return F_P_darr(a[0]); }
static V F_P_darr_dsize(V a0, V a1) {
top:;
V s650 = a0;
if ((s650) == IMM(1)) {
return F_P_dterm();
} else if ((s650) == IMM(0)) {
return F_P_darr_dsize_dlit(a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_darr_dsize(V *a) { (void)a; return F_P_darr_dsize(a[0], a[1]); }
static V L652(V *a) {
return F_Parser_dpure(C1(2, F_P_dlog2(a[0])));
}
static V S653(void) { static V c; return STRC(c, "expected an array size"); }
static V L654(V *a) {
return F_Parser_dpure(C1(2, 0u));
}
static V F_P_darr_dsize_dlit(V a0) {
top:;
V s651 = a0;
if (TAG(FLD(s651, 0)) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L652, 2, 1, (V[]){FLD(FLD(s651, 0), 0)}));
} else {
return F_Parser_dbind(F_P_derr(S653()), mk_clo(L654, 1, 0, 0));
}
}
static V W_P_darr_dsize_dlit(V *a) { (void)a; return F_P_darr_dsize_dlit(a[0]); }
static V F_P_dlog2(V a0) {
top:;
return F_U32_dfrom__nat(F_U32_dlog2(a0));
}
static V W_P_dlog2(V *a) { (void)a; return F_P_dlog2(a[0]); }
static V W_U32_dlog2(V *a) { (void)a; return F_U32_dlog2(a[0]); }
static V S657(void) { static V c; return STRC(c, ")"); }
static V L656(V *a) {
return F_P_dparen_dgo(F_P_dtok__is(a[0], S657()));
}
static V L655(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L656, 1, 0, 0));
}
static V F_P_dparen(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L655, 1, 0, 0));
}
static V W_P_dparen(V *a) { (void)a; return F_P_dparen(); }
static V S660(void) { static V c; return STRC(c, "Unit"); }
static V L659(V *a) {
return F_Parser_dpure(C2(6, S660(), IMM(0)));
}
static V F_P_dparen_dgo(V a0) {
top:;
V s658 = a0;
if ((s658) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L659, 1, 0, 0));
} else if ((s658) == IMM(0)) {
return F_P_dparen_dbody();
} else { bend_fail("incomplete match"); }
}
static V W_P_dparen_dgo(V *a) { (void)a; return F_P_dparen_dgo(a[0]); }
static V S663(void) { static V c; return STRC(c, ","); }
static V S664(void) { static V c; return STRC(c, ":"); }
static V L662(V *a) {
return F_P_dparen_dtail(a[0], F_P_dtok__which(a[1], C2(1, S663(), C2(1, S664(), IMM(0)))));
}
static V L661(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L662, 2, 1, (V[]){a[0]}));
}
static V F_P_dparen_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L661, 1, 0, 0));
}
static V W_P_dparen_dbody(V *a) { (void)a; return F_P_dparen_dbody(); }
static V S667(void) { static V c; return STRC(c, ")"); }
static V L668(V *a) {
return F_Parser_dpure(F_P_dtuple(C2(1, a[0], a[1])));
}
static V L666(V *a) {
return F_Parser_dbind(F_P_dlist(S667()), mk_clo(L668, 2, 1, (V[]){a[0]}));
}
static V S671(void) { static V c; return STRC(c, ")"); }
static V L672(V *a) {
return F_Parser_dpure(C2(13, a[1], F_P_dhead(a[0])));
}
static V L670(V *a) {
return F_Parser_dbind(F_P_dexpect(S671()), mk_clo(L672, 3, 2, (V[]){a[1], a[0]}));
}
static V L669(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L670, 2, 1, (V[]){a[0]}));
}
static V S673(void) { static V c; return STRC(c, ")"); }
static V L674(V *a) {
return F_Parser_dpure(a[0]);
}
static V F_P_dparen_dtail(V a0, V a1) {
top:;
V s665 = a1;
if ((s665) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L666, 2, 1, (V[]){a0}));
} else if ((s665) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L669, 2, 1, (V[]){a0}));
} else if (nat_ge(s665, 2)) {
return F_Parser_dbind(F_P_dexpect(S673()), mk_clo(L674, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparen_dtail(V *a) { (void)a; return F_P_dparen_dtail(a[0], a[1]); }
static V S676(void) { static V c; return STRC(c, "Unit"); }
static V S677(void) { static V c; return STRC(c, "Tuple"); }
static V F_P_dtuple(V a0) {
top:;
V s675 = a0;
if ((s675) == IMM(0)) {
return C2(6, S676(), IMM(0));
} else if (TAG(s675) == 1 && (FLD(s675, 1)) == IMM(0)) {
return FLD(s675, 0);
} else if (TAG(s675) == 1) {
return C2(6, S677(), C2(1, FLD(s675, 0), C2(1, F_P_dtuple(FLD(s675, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtuple(V *a) { (void)a; return F_P_dtuple(a[0]); }
static V S678(void) { static V c; return STRC(c, "{"); }
static V S679(void) { static V c; return STRC(c, "<"); }
static V S680(void) { static V c; return STRC(c, "=>"); }
static V F_P_dafter__id(V a0, V a1) {
top:;
return F_P_dafter__id_dgo(a0, F_Bool_dpick(F_P_dtok__sp(a1), 3u, F_P_dtok__which(a1, C2(1, S678(), C2(1, S679(), IMM(0))))), F_P_dtok__is(a1, S680()));
}
static V W_P_dafter__id(V *a) { (void)a; return F_P_dafter__id(a[0], a[1]); }
static V L683(V *a) {
return F_Parser_dpure(C2(7, C1(0, a[0]), a[1]));
}
static V L682(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L683, 2, 1, (V[]){a[0]}));
}
static V F_P_dafter__id_dgo(V a0, V a1, V a2) {
top:;
V s681 = a2;
if ((s681) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L682, 2, 1, (V[]){a0}));
} else if ((s681) == IMM(0)) {
return F_P_dafter__id_dk(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dafter__id_dgo(V *a) { (void)a; return F_P_dafter__id_dgo(a[0], a[1], a[2]); }
static V S686(void) { static V c; return STRC(c, "}"); }
static V L687(V *a) {
return F_Parser_dpure(C2(6, a[0], a[1]));
}
static V L685(V *a) {
return F_Parser_dbind(F_P_dlist(S686()), mk_clo(L687, 2, 1, (V[]){a[0]}));
}
static V L689(V *a) {
return F_Parser_dpure(C2(14, a[0], a[1]));
}
static V L688(V *a) {
return F_Parser_dbind(F_P_dtyargs(), mk_clo(L689, 2, 1, (V[]){a[0]}));
}
static V F_P_dafter__id_dk(V a0, V a1) {
top:;
V s684 = a1;
if ((s684) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L685, 2, 1, (V[]){a0}));
} else if ((s684) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L688, 2, 1, (V[]){a0}));
} else if (nat_ge(s684, 2)) {
return F_Parser_dpure(C1(0, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dafter__id_dk(V *a) { (void)a; return F_P_dafter__id_dk(a[0], a[1]); }
static V L690(V *a) {
return F_P_dtyargs_dgo(a[0], F_P_dstuck(F_P_dtok__kind(a[0])));
}
static V F_P_dtyargs(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L690, 1, 0, 0));
}
static V W_P_dtyargs(V *a) { (void)a; return F_P_dtyargs(); }
static V F_P_dtyargs_dgo(V a0, V a1) {
top:;
V s691 = a1;
if ((s691) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s691) == IMM(0)) {
return F_P_dtyargs_dclose(F_P_dis__gt(a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtyargs_dgo(V *a) { (void)a; return F_P_dtyargs_dgo(a[0], a[1]); }
static V S692(void) { static V c; return STRC(c, ">"); }
static V S693(void) { static V c; return STRC(c, ">>"); }
static V S694(void) { static V c; return STRC(c, ">="); }
static V F_P_dis__gt(V a0) {
top:;
return F_Bool_dor(F_P_dtok__is(a0, S692()), F_Bool_dor(F_P_dtok__is(a0, S693()), F_P_dtok__is(a0, S694())));
}
static V W_P_dis__gt(V *a) { (void)a; return F_P_dis__gt(a[0]); }
static V L696(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dtyargs_dclose(V a0) {
top:;
V s695 = a0;
if ((s695) == IMM(1)) {
return F_Parser_dbind(F_P_dgt(), mk_clo(L696, 1, 0, 0));
} else if ((s695) == IMM(0)) {
return F_P_dtyargs_ditem();
} else { bend_fail("incomplete match"); }
}
static V W_P_dtyargs_dclose(V *a) { (void)a; return F_P_dtyargs_dclose(a[0]); }
static V S698(void) { static V c; return STRC(c, ","); }
static V L700(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L699(V *a) {
return F_Parser_dbind(F_P_dtyargs_dmore(a[1]), mk_clo(L700, 2, 1, (V[]){a[0]}));
}
static V L697(V *a) {
return F_Parser_dbind(F_P_deat(S698()), mk_clo(L699, 2, 1, (V[]){a[0]}));
}
static V F_P_dtyargs_ditem(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L697, 1, 0, 0));
}
static V W_P_dtyargs_ditem(V *a) { (void)a; return F_P_dtyargs_ditem(); }
static V L702(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dtyargs_dmore(V a0) {
top:;
V s701 = a0;
if ((s701) == IMM(1)) {
return F_P_dtyargs();
} else if ((s701) == IMM(0)) {
return F_Parser_dbind(F_P_dgt(), mk_clo(L702, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtyargs_dmore(V *a) { (void)a; return F_P_dtyargs_dmore(a[0]); }
static V L703(V *a) {
return F_P_dgt_dgo(a[0]);
}
static V F_P_dgt(void) {
top:;
return mk_clo(L703, 1, 0, 0);
}
static V W_P_dgt(V *a) { (void)a; return F_P_dgt(); }
static V S705(void) { static V c; return STRC(c, ">"); }
static V S706(void) { static V c; return STRC(c, ">>"); }
static V S707(void) { static V c; return STRC(c, ">="); }
static V S708(void) { static V c; return STRC(c, "expected '>'"); }
static V F_P_dgt_dgo(V a0) {
top:;
V s704 = a0;
if (TAG(s704) == 1 && TAG(FLD(FLD(s704, 0), 0)) == 7) {
return F_P_dgt_dif(FLD(FLD(FLD(s704, 0), 0), 0), FLD(FLD(s704, 0), 1), FLD(FLD(s704, 0), 2), FLD(s704, 1), F_P_dwhich(FLD(FLD(FLD(s704, 0), 0), 0), C2(1, S705(), C2(1, S706(), C2(1, S707(), IMM(0))))));
} else {
return F_P_derr_dgo(S708(), s704);
}
}
static V W_P_dgt_dgo(V *a) { (void)a; return F_P_dgt_dgo(a[0]); }
static V S710(void) { static V c; return STRC(c, ">"); }
static V S711(void) { static V c; return STRC(c, "="); }
static V S712(void) { static V c; return STRC(c, "expected '>'"); }
static V F_P_dgt_dif(V a0, V a1, V a2, V a3, V a4) {
top:;
V s709 = a4;
if ((s709) == 0) {
return C2(0, IMM(0), a3);
} else if ((s709) == 1) {
return C2(0, IMM(0), C2(1, C3(0, C1(7, S710()), IMM(0), a2), a3));
} else if ((s709) == 2) {
return C2(0, IMM(0), C2(1, C3(0, C1(7, S711()), IMM(0), a2), a3));
} else if (nat_ge(s709, 3)) {
return F_P_derr_dgo(S712(), C2(1, C3(0, C1(7, a0), a1, a2), a3));
} else { bend_fail("incomplete match"); }
}
static V W_P_dgt_dif(V *a) { (void)a; return F_P_dgt_dif(a[0], a[1], a[2], a[3], a[4]); }
static V F_P_dparam_dskip__mode(V a0) {
top:;
return F_P_dparam_dskip__mode_dgo(F_U32_dis__zero(a0));
}
static V W_P_dparam_dskip__mode(V *a) { (void)a; return F_P_dparam_dskip__mode(a[0]); }
static V F_P_dparam_dskip__mode_dgo(V a0) {
top:;
V s713 = a0;
if ((s713) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s713) == IMM(0)) {
return F_P_dskip();
} else { bend_fail("incomplete match"); }
}
static V W_P_dparam_dskip__mode_dgo(V *a) { (void)a; return F_P_dparam_dskip__mode_dgo(a[0]); }
static V S714(void) { static V c; return STRC(c, "-"); }
static V S715(void) { static V c; return STRC(c, "+"); }
static V S716(void) { static V c; return STRC(c, "~"); }
static V F_P_dparam_dmode(V a0) {
top:;
return F_Bool_dpick(F_P_dtok__is(a0, S714()), 1u, F_Bool_dpick(F_P_dtok__is(a0, S715()), 2u, F_Bool_dpick(F_P_dtok__is(a0, S716()), 3u, 0u)));
}
static V W_P_dparam_dmode(V *a) { (void)a; return F_P_dparam_dmode(a[0]); }
static V L717(V *a) {
return F_P_dnls_dif(F_P_dis__nl(a[0]));
}
static V F_P_dnls(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L717, 1, 0, 0));
}
static V W_P_dnls(V *a) { (void)a; return F_P_dnls(); }
static V F_P_dis__nl(V a0) {
top:;
V s718 = a0;
if ((FLD(s718, 0)) == IMM(8)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dis__nl(V *a) { (void)a; return F_P_dis__nl(a[0]); }
static V L720(V *a) {
return F_P_dnls();
}
static V F_P_dnls_dif(V a0) {
top:;
V s719 = a0;
if ((s719) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L720, 1, 0, 0));
} else if ((s719) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dnls_dif(V *a) { (void)a; return F_P_dnls_dif(a[0]); }
static V L721(V *a) {
return F_P_dexpect__in_dgo(F_P_dis__in(a[0]));
}
static V F_P_dexpect__in(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L721, 1, 0, 0));
}
static V W_P_dexpect__in(V *a) { (void)a; return F_P_dexpect__in(); }
static V F_P_dis__in(V a0) {
top:;
V s722 = a0;
if ((FLD(s722, 0)) == IMM(9)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dis__in(V *a) { (void)a; return F_P_dis__in(a[0]); }
static V S724(void) { static V c; return STRC(c, "expected an indented block"); }
static V F_P_dexpect__in_dgo(V a0) {
top:;
V s723 = a0;
if ((s723) == IMM(1)) {
return F_P_dskip();
} else if ((s723) == IMM(0)) {
return F_P_derr(S724());
} else { bend_fail("incomplete match"); }
}
static V W_P_dexpect__in_dgo(V *a) { (void)a; return F_P_dexpect__in_dgo(a[0]); }
static V S728(void) { static V c; return STRC(c, "<"); }
static V S729(void) { static V c; return STRC(c, "<-"); }
static V S733(void) { static V c; return STRC(c, ":"); }
static V L736(V *a) {
return F_Parser_dpure(C3(3, a[1], a[0], a[2]));
}
static V L735(V *a) {
return F_Parser_dbind(F_P_dtype_dbody(F_P_dis__in(a[2])), mk_clo(L736, 3, 2, (V[]){a[0], a[1]}));
}
static V L734(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L735, 3, 2, (V[]){a[0], a[1]}));
}
static V L732(V *a) {
return F_Parser_dbind(F_P_dexpect(S733()), mk_clo(L734, 3, 2, (V[]){a[0], a[1]}));
}
static V L731(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L732, 3, 2, (V[]){a[0], a[1]}));
}
static V L730(V *a) {
return F_Parser_dbind(F_P_duntil__is(), mk_clo(L731, 3, 2, (V[]){a[1], a[0]}));
}
static V L727(V *a) {
return F_Parser_dbind(F_P_dtparams_dopt(F_P_dtok__which(a[1], C2(1, S728(), C2(1, S729(), IMM(0))))), mk_clo(L730, 2, 1, (V[]){a[0]}));
}
static V L726(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L727, 2, 1, (V[]){a[0]}));
}
static V L725(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L726, 1, 0, 0));
}
static V F_P_dtype(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L725, 1, 0, 0));
}
static V W_P_dtype(V *a) { (void)a; return F_P_dtype(); }
static V L738(V *a) {
return F_P_dctors();
}
static V F_P_dtype_dbody(V a0) {
top:;
V s737 = a0;
if ((s737) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L738, 1, 0, 0));
} else if ((s737) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtype_dbody(V *a) { (void)a; return F_P_dtype_dbody(a[0]); }
static V L740(V *a) {
return F_P_dctors_dgo(a[0], F_Bool_dpick(F_P_dis__de(a[0]), 0u, F_Bool_dpick(F_P_dstuck(F_P_dtok__kind(a[0])), 1u, 2u)));
}
static V L739(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L740, 1, 0, 0));
}
static V F_P_dctors(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L739, 1, 0, 0));
}
static V W_P_dctors(V *a) { (void)a; return F_P_dctors(); }
static V L742(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S744(void) { static V c; return STRC(c, "{"); }
static V L747(V *a) {
return F_Parser_dpure(C2(1, C2(0, a[1], a[0]), a[2]));
}
static V L746(V *a) {
return F_Parser_dbind(F_P_dctors(), mk_clo(L747, 3, 2, (V[]){a[1], a[0]}));
}
static V L745(V *a) {
return F_Parser_dbind(F_P_dfields(), mk_clo(L746, 2, 1, (V[]){a[0]}));
}
static V L743(V *a) {
return F_Parser_dbind(F_P_dexpect(S744()), mk_clo(L745, 2, 1, (V[]){a[0]}));
}
static V F_P_dctors_dgo(V a0, V a1) {
top:;
V s741 = a1;
if ((s741) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L742, 1, 0, 0));
} else if ((s741) == 1) {
return F_Parser_dpure(IMM(0));
} else if (nat_ge(s741, 2)) {
return F_Parser_dbind(F_P_dident(), mk_clo(L743, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dctors_dgo(V *a) { (void)a; return F_P_dctors_dgo(a[0], a[1]); }
static V S749(void) { static V c; return STRC(c, "}"); }
static V L748(V *a) {
return F_P_dfields_dgo(F_Bool_dor(F_P_dtok__is(a[0], S749()), F_P_dstuck(F_P_dtok__kind(a[0]))));
}
static V F_P_dfields(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L748, 1, 0, 0));
}
static V W_P_dfields(V *a) { (void)a; return F_P_dfields(); }
static V L751(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S752(void) { static V c; return STRC(c, "+"); }
static V S754(void) { static V c; return STRC(c, "-"); }
static V S757(void) { static V c; return STRC(c, ":"); }
static V S760(void) { static V c; return STRC(c, ","); }
static V L762(V *a) {
return F_Parser_dpure(C2(1, C2(0, a[1], a[0]), a[2]));
}
static V L761(V *a) {
return F_Parser_dbind(F_P_dfields(), mk_clo(L762, 3, 2, (V[]){a[0], a[1]}));
}
static V L759(V *a) {
return F_Parser_dbind(F_P_deat(S760()), mk_clo(L761, 3, 2, (V[]){a[1], a[0]}));
}
static V L758(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L759, 2, 1, (V[]){a[0]}));
}
static V L756(V *a) {
return F_Parser_dbind(F_P_dexpect(S757()), mk_clo(L758, 2, 1, (V[]){a[0]}));
}
static V L755(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L756, 1, 0, 0));
}
static V L753(V *a) {
return F_Parser_dbind(F_P_deat(S754()), mk_clo(L755, 1, 0, 0));
}
static V F_P_dfields_dgo(V a0) {
top:;
V s750 = a0;
if ((s750) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L751, 1, 0, 0));
} else if ((s750) == IMM(0)) {
return F_Parser_dbind(F_P_deat(S752()), mk_clo(L753, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dfields_dgo(V *a) { (void)a; return F_P_dfields_dgo(a[0]); }
static V L763(V *a) {
return C2(0, IMM(0), F_P_duntil__is_dgo(a[0]));
}
static V F_P_duntil__is(void) {
top:;
return mk_clo(L763, 1, 0, 0);
}
static V W_P_duntil__is(V *a) { (void)a; return F_P_duntil__is(); }
static V S765(void) { static V c; return STRC(c, "is"); }
static V F_P_duntil__is_dgo(V a0) {
top:;
V s764 = a0;
if ((s764) == IMM(0)) {
return IMM(0);
} else if (TAG(s764) == 1 && TAG(FLD(FLD(s764, 0), 0)) == 0) {
return F_P_duntil__is_dif(C3(0, C1(0, FLD(FLD(FLD(s764, 0), 0), 0)), FLD(FLD(s764, 0), 1), FLD(FLD(s764, 0), 2)), FLD(s764, 1), F_Str_deq(FLD(FLD(FLD(s764, 0), 0), 0), S765()));
} else if (TAG(s764) == 1 && (FLD(FLD(s764, 0), 0)) == IMM(11)) {
return C2(1, C3(0, IMM(11), FLD(FLD(s764, 0), 1), FLD(FLD(s764, 0), 2)), FLD(s764, 1));
} else if (TAG(s764) == 1 && TAG(FLD(FLD(s764, 0), 0)) == 12) {
return C2(1, C3(0, C1(12, FLD(FLD(FLD(s764, 0), 0), 0)), FLD(FLD(s764, 0), 1), FLD(FLD(s764, 0), 2)), FLD(s764, 1));
} else if (TAG(s764) == 1) {
{ V t0 = FLD(s764, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_duntil__is_dgo(V *a) { (void)a; return F_P_duntil__is_dgo(a[0]); }
static V F_P_duntil__is_dif(V a0, V a1, V a2) {
top:;
V s766 = a2;
if ((s766) == IMM(1)) {
return a1;
} else if ((s766) == IMM(0)) {
return F_P_duntil__is_dgo(a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_duntil__is_dif(V *a) { (void)a; return F_P_duntil__is_dif(a[0], a[1], a[2]); }
static V L768(V *a) {
return F_P_dtparams();
}
static V L769(V *a) {
return F_P_dtparams();
}
static V F_P_dtparams_dopt(V a0) {
top:;
V s767 = a0;
if ((s767) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L768, 1, 0, 0));
} else if ((s767) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L769, 1, 0, 0));
} else if (nat_ge(s767, 2)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtparams_dopt(V *a) { (void)a; return F_P_dtparams_dopt(a[0]); }
static V S770(void) { static V c; return STRC(c, "-"); }
static V S774(void) { static V c; return STRC(c, ","); }
static V L776(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L775(V *a) {
return F_Parser_dbind(F_P_dtparams_dmore(a[1]), mk_clo(L776, 2, 1, (V[]){a[0]}));
}
static V L773(V *a) {
return F_Parser_dbind(F_P_deat(S774()), mk_clo(L775, 2, 1, (V[]){a[0]}));
}
static V L772(V *a) {
return F_Parser_dbind(F_P_dskip__ann(), mk_clo(L773, 2, 1, (V[]){a[0]}));
}
static V L771(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L772, 1, 0, 0));
}
static V F_P_dtparams(void) {
top:;
return F_Parser_dbind(F_P_deat(S770()), mk_clo(L771, 1, 0, 0));
}
static V W_P_dtparams(V *a) { (void)a; return F_P_dtparams(); }
static V L778(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dtparams_dmore(V a0) {
top:;
V s777 = a0;
if ((s777) == IMM(1)) {
return F_P_dtparams();
} else if ((s777) == IMM(0)) {
return F_Parser_dbind(F_P_dgt(), mk_clo(L778, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtparams_dmore(V *a) { (void)a; return F_P_dtparams_dmore(a[0]); }
static V S780(void) { static V c; return STRC(c, ":"); }
static V L779(V *a) {
return F_P_dskip__ann_dgo(F_P_dtok__is(a[0], S780()));
}
static V F_P_dskip__ann(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L779, 1, 0, 0));
}
static V W_P_dskip__ann(V *a) { (void)a; return F_P_dskip__ann(); }
static V L783(V *a) {
return F_Parser_dpure(IMM(0));
}
static V L782(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L783, 1, 0, 0));
}
static V F_P_dskip__ann_dgo(V a0) {
top:;
V s781 = a0;
if ((s781) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L782, 1, 0, 0));
} else if ((s781) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__ann_dgo(V *a) { (void)a; return F_P_dskip__ann_dgo(a[0]); }
static V S786(void) { static V c; return STRC(c, "("); }
static V S790(void) { static V c; return STRC(c, "->"); }
static V S792(void) { static V c; return STRC(c, ":"); }
static V S796(void) { static V c; return STRC(c, "import"); }
static V L795(V *a) {
return F_P_ddef_dbody(a[2], a[1], a[0], F_P_dtok__is__id(a[3], S796()));
}
static V L794(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L795, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L793(V *a) {
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L794, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L791(V *a) {
return F_Parser_dbind(F_P_dexpect(S792()), mk_clo(L793, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L789(V *a) {
return F_Parser_dbind(F_P_dret_dgo(F_P_dtok__is(a[2], S790())), mk_clo(L791, 3, 2, (V[]){a[0], a[1]}));
}
static V L788(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L789, 3, 2, (V[]){a[1], a[0]}));
}
static V L787(V *a) {
return F_Parser_dbind(F_P_dparams(), mk_clo(L788, 2, 1, (V[]){a[0]}));
}
static V L785(V *a) {
return F_Parser_dbind(F_P_dexpect(S786()), mk_clo(L787, 2, 1, (V[]){a[0]}));
}
static V L784(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L785, 1, 0, 0));
}
static V F_P_ddef(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L784, 1, 0, 0));
}
static V W_P_ddef(V *a) { (void)a; return F_P_ddef(); }
static V L798(V *a) {
return F_Parser_dpure(C3(1, a[1], a[0], a[2]));
}
static V L799(V *a) {
return F_Parser_dpure(C4(0, a[2], a[1], F_Fold_dplain(a[3]), a[0]));
}
static V F_P_ddef_dbody(V a0, V a1, V a2, V a3) {
top:;
V s797 = a3;
if ((s797) == IMM(1)) {
return F_Parser_dbind(F_P_deff_dimports(), mk_clo(L798, 3, 2, (V[]){a1, a0}));
} else if ((s797) == IMM(0)) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L799, 4, 3, (V[]){a2, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddef_dbody(V *a) { (void)a; return F_P_ddef_dbody(a[0], a[1], a[2], a[3]); }
static V S801(void) { static V c; return STRC(c, "empty block"); }
static V S802(void) { static V c; return STRC(c, ""); }
static V S803(void) { static V c; return STRC(c, "_"); }
static V F_Fold_dplain(V a0) {
top:;
V s800 = a0;
if ((s800) == IMM(0)) {
return C1(15, S801());
} else if (TAG(s800) == 1 && TAG(FLD(s800, 0)) == 0 && (FLD(s800, 1)) == IMM(0)) {
return FLD(FLD(s800, 0), 1);
} else if (TAG(s800) == 1 && TAG(FLD(s800, 0)) == 1 && (FLD(s800, 1)) == IMM(0)) {
return FLD(FLD(s800, 0), 1);
} else if (TAG(s800) == 1 && TAG(FLD(s800, 0)) == 2 && (FLD(s800, 1)) == IMM(0)) {
return FLD(FLD(s800, 0), 0);
} else if (TAG(s800) == 1 && TAG(FLD(s800, 0)) == 3 && (FLD(s800, 1)) == IMM(0)) {
return FLD(FLD(s800, 0), 0);
} else if (TAG(s800) == 1 && (FLD(s800, 0)) == IMM(4) && (FLD(s800, 1)) == IMM(0)) {
return C2(14, S802(), IMM(0));
} else if (TAG(s800) == 1 && TAG(FLD(s800, 0)) == 0) {
return C3(8, FLD(FLD(s800, 0), 0), FLD(FLD(s800, 0), 1), F_Fold_dplain(FLD(s800, 1)));
} else if (TAG(s800) == 1 && TAG(FLD(s800, 0)) == 1) {
return C3(8, C1(0, FLD(FLD(s800, 0), 0)), FLD(FLD(s800, 0), 1), F_Fold_dplain(FLD(s800, 1)));
} else if (TAG(s800) == 1 && TAG(FLD(s800, 0)) == 2) {
return FLD(FLD(s800, 0), 0);
} else if (TAG(s800) == 1 && TAG(FLD(s800, 0)) == 3) {
return C3(8, C1(0, S803()), FLD(FLD(s800, 0), 0), F_Fold_dplain(FLD(s800, 1)));
} else if (TAG(s800) == 1 && (FLD(s800, 0)) == IMM(4)) {
{ V t0 = FLD(s800, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Fold_dplain(V *a) { (void)a; return F_Fold_dplain(a[0]); }
static V L805(V *a) {
return F_P_dstmts_dgo(a[0], F_Bool_dpick(F_P_dis__de(a[0]), 0u, F_Bool_dpick(F_P_dstuck(F_P_dtok__kind(a[0])), 1u, 2u)));
}
static V L804(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L805, 1, 0, 0));
}
static V F_P_dstmts(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L804, 1, 0, 0));
}
static V W_P_dstmts(V *a) { (void)a; return F_P_dstmts(); }
static V L807(V *a) {
return F_Parser_dpure(IMM(0));
}
static V L809(V *a) {
return F_Parser_dpure(F_List_dappend(a[0], a[1]));
}
static V L808(V *a) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L809, 2, 1, (V[]){a[0]}));
}
static V F_P_dstmts_dgo(V a0, V a1) {
top:;
V s806 = a1;
if ((s806) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L807, 1, 0, 0));
} else if ((s806) == 1) {
return F_Parser_dpure(IMM(0));
} else if (nat_ge(s806, 2)) {
return F_Parser_dbind(F_P_dstmt(), mk_clo(L808, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmts_dgo(V *a) { (void)a; return F_P_dstmts_dgo(a[0], a[1]); }
static V S811(void) { static V c; return STRC(c, "%"); }
static V L810(V *a) {
return F_P_dstmt_dgo(a[0], F_P_dtok__is(a[0], S811()));
}
static V F_P_dstmt(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L810, 1, 0, 0));
}
static V W_P_dstmt(V *a) { (void)a; return F_P_dstmt(); }
static V L813(V *a) {
return F_Parser_dpure(C2(1, IMM(4), IMM(0)));
}
static V S814(void) { static V c; return STRC(c, "match"); }
static V S815(void) { static V c; return STRC(c, "return"); }
static V S816(void) { static V c; return STRC(c, "do"); }
static V F_P_dstmt_dgo(V a0, V a1) {
top:;
V s812 = a1;
if ((s812) == IMM(1)) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L813, 1, 0, 0));
} else if ((s812) == IMM(0)) {
return F_P_dstmt_did(F_P_dtok__which__id(a0, C2(1, S814(), C2(1, S815(), C2(1, S816(), IMM(0))))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmt_dgo(V *a) { (void)a; return F_P_dstmt_dgo(a[0], a[1]); }
static V L818(V *a) {
return F_Parser_dpure(C2(1, C1(3, a[0]), IMM(0)));
}
static V L820(V *a) {
return F_Parser_dpure(C2(1, C1(2, a[0]), IMM(0)));
}
static V L819(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L820, 1, 0, 0));
}
static V L821(V *a) {
return F_Parser_dpure(C2(1, C1(3, a[0]), IMM(0)));
}
static V L822(V *a) {
return F_P_dstmt_dscan(a[0]);
}
static V F_P_dstmt_did(V a0) {
top:;
V s817 = a0;
if ((s817) == 0) {
return F_Parser_dbind(F_P_dmatch(), mk_clo(L818, 1, 0, 0));
} else if ((s817) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L819, 1, 0, 0));
} else if ((s817) == 2) {
return F_Parser_dbind(F_P_ddo(), mk_clo(L821, 1, 0, 0));
} else if (nat_ge(s817, 3)) {
return F_Parser_dbind(F_P_dscan(), mk_clo(L822, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmt_did(V *a) { (void)a; return F_P_dstmt_did(a[0]); }
static V F_P_dstmt_dscan(V a0) {
top:;
return F_P_dstmt_dscan_dgo(F_U32_dto__nat(a0));
}
static V W_P_dstmt_dscan(V *a) { (void)a; return F_P_dstmt_dscan(a[0]); }
static V W_U32_dto__nat(V *a) { (void)a; return F_U32_dto__nat(a[0]); }
static V L824(V *a) {
return F_Parser_dpure(C2(1, C1(3, a[0]), IMM(0)));
}
static V F_P_dstmt_dscan_dgo(V a0) {
top:;
V s823 = a0;
if ((s823) == 0) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L824, 1, 0, 0));
} else if ((s823) == 1) {
return F_P_dlet__stmt();
} else if (nat_ge(s823, 2)) {
return F_P_dbind__stmt();
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmt_dscan_dgo(V *a) { (void)a; return F_P_dstmt_dscan_dgo(a[0]); }
static V S825(void) { static V c; return STRC(c, "+"); }
static V S829(void) { static V c; return STRC(c, "["); }
static V L828(V *a) {
return F_P_dbind_darr(a[0], F_Bool_dand(F_P_dtok__is(a[1], S829()), F_Bool_dnot(F_P_dtok__sp(a[1]))));
}
static V L827(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L828, 2, 1, (V[]){a[0]}));
}
static V L826(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L827, 1, 0, 0));
}
static V F_P_dbind__stmt(void) {
top:;
return F_Parser_dbind(F_P_deat(S825()), mk_clo(L826, 1, 0, 0));
}
static V W_P_dbind__stmt(V *a) { (void)a; return F_P_dbind__stmt(); }
static V S833(void) { static V c; return STRC(c, "]"); }
static V S835(void) { static V c; return STRC(c, "<-"); }
static V S838(void) { static V c; return STRC(c, "Array.set"); }
static V S839(void) { static V c; return STRC(c, "U32"); }
static V L837(V *a) {
return F_Parser_dpure(C2(1, C2(0, C1(0, a[1]), C2(5, C1(0, S838()), C2(1, C2(14, S839(), IMM(0)), C2(1, C1(0, a[1]), C2(1, a[0], C2(1, a[2], IMM(0))))))), IMM(0)));
}
static V L836(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L837, 3, 2, (V[]){a[0], a[1]}));
}
static V L834(V *a) {
return F_Parser_dbind(F_P_dexpect(S835()), mk_clo(L836, 3, 2, (V[]){a[0], a[1]}));
}
static V L832(V *a) {
return F_Parser_dbind(F_P_dexpect(S833()), mk_clo(L834, 3, 2, (V[]){a[1], a[0]}));
}
static V L831(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L832, 2, 1, (V[]){a[0]}));
}
static V S841(void) { static V c; return STRC(c, "<-"); }
static V L843(V *a) {
return F_Parser_dpure(C2(1, C2(1, a[0], a[1]), IMM(0)));
}
static V L842(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L843, 2, 1, (V[]){a[0]}));
}
static V L840(V *a) {
return F_Parser_dbind(F_P_dexpect(S841()), mk_clo(L842, 2, 1, (V[]){a[0]}));
}
static V F_P_dbind_darr(V a0, V a1) {
top:;
V s830 = a1;
if ((s830) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L831, 2, 1, (V[]){a0}));
} else if ((s830) == IMM(0)) {
return F_Parser_dbind(F_P_dskip__ann(), mk_clo(L840, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbind_darr(V *a) { (void)a; return F_P_dbind_darr(a[0], a[1]); }
static V S844(void) { static V c; return STRC(c, "="); }
static V S845(void) { static V c; return STRC(c, ":"); }
static V S848(void) { static V c; return STRC(c, "="); }
static V L850(V *a) {
return F_Parser_dpure(F_P_dlets_dpar(a[0], a[1]));
}
static V L849(V *a) {
return F_Parser_dbind(F_P_dexprs__n(F_List_dlength(a[0])), mk_clo(L850, 2, 1, (V[]){a[0]}));
}
static V L847(V *a) {
return F_Parser_dbind(F_P_dexpect(S848()), mk_clo(L849, 2, 1, (V[]){a[0]}));
}
static V L846(V *a) {
return F_Parser_dbind(F_P_dskip__ann(), mk_clo(L847, 2, 1, (V[]){a[0]}));
}
static V F_P_dlet__stmt(void) {
top:;
return F_Parser_dbind(F_P_dpat__seq(C2(1, S844(), C2(1, S845(), IMM(0)))), mk_clo(L846, 1, 0, 0));
}
static V W_P_dlet__stmt(V *a) { (void)a; return F_P_dlet__stmt(); }
static V S851(void) { static V c; return STRC(c, "%par"); }
static V S852(void) { static V c; return STRC(c, "%par"); }
static V F_P_dlets_dpar(V a0, V a1) {
top:;
return F_Bool_dpick(F_Nat_dis__gt(F_List_dlength(a0), 1u), C2(1, C2(0, C2(1, S851(), a0), C2(6, S852(), a1)), IMM(0)), F_P_dlets(a0, a1));
}
static V W_P_dlets_dpar(V *a) { (void)a; return F_P_dlets_dpar(a[0], a[1]); }
static V F_P_dlets(V a0, V a1) {
top:;
V s853 = a0;
V s854 = a1;
if (TAG(s853) == 1 && TAG(s854) == 1) {
return C2(1, C2(0, FLD(s853, 0), FLD(s854, 0)), F_P_dlets(FLD(s853, 1), FLD(s854, 1)));
} else {
return IMM(0);
}
}
static V W_P_dlets(V *a) { (void)a; return F_P_dlets(a[0], a[1]); }
static V W_Nat_dis__gt(V *a) { (void)a; return F_Nat_dis__gt(a[0], a[1]); }
static V L857(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L856(V *a) {
return F_Parser_dbind(F_P_dexprs__n(a[0]), mk_clo(L857, 2, 1, (V[]){a[1]}));
}
static V F_P_dexprs__n(V a0) {
top:;
V s855 = a0;
if ((s855) == 0) {
return F_Parser_dpure(IMM(0));
} else if (nat_ge(s855, 1)) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L856, 2, 1, (V[]){nat_subk(s855, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dexprs__n(V *a) { (void)a; return F_P_dexprs__n(a[0]); }
static V L858(V *a) {
return F_P_dpat__seq_dgo(a[0], a[1], F_P_dpat__seq_dstop(a[0], a[1]));
}
static V F_P_dpat__seq(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L858, 2, 1, (V[]){a0}));
}
static V W_P_dpat__seq(V *a) { (void)a; return F_P_dpat__seq(a[0]); }
static V F_P_dpat__seq_dstop(V a0, V a1) {
top:;
return F_Bool_dor(F_P_dstuck(F_P_dtok__kind(a1)), F_Bool_dor(F_P_dis__nl(a1), F_Nat_dis__lt(F_P_dtok__which(a1, a0), F_List_dlength(a0))));
}
static V W_P_dpat__seq_dstop(V *a) { (void)a; return F_P_dpat__seq_dstop(a[0], a[1]); }
static V L861(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L860(V *a) {
return F_Parser_dbind(F_P_dpat__seq(a[0]), mk_clo(L861, 2, 1, (V[]){a[1]}));
}
static V F_P_dpat__seq_dgo(V a0, V a1, V a2) {
top:;
V s859 = a2;
if ((s859) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s859) == IMM(0)) {
return F_Parser_dbind(F_P_dpat(), mk_clo(L860, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat__seq_dgo(V *a) { (void)a; return F_P_dpat__seq_dgo(a[0], a[1], a[2]); }
static V S864(void) { static V c; return STRC(c, "<>"); }
static V L863(V *a) {
return F_P_dpat_dcons(a[0], F_P_dtok__is(a[1], S864()));
}
static V L862(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L863, 2, 1, (V[]){a[0]}));
}
static V F_P_dpat(void) {
top:;
return F_Parser_dbind(F_P_dpat1(), mk_clo(L862, 1, 0, 0));
}
static V W_P_dpat(V *a) { (void)a; return F_P_dpat(); }
static V S868(void) { static V c; return STRC(c, "Con"); }
static V L867(V *a) {
return F_Parser_dpure(C2(1, S868(), C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V L866(V *a) {
return F_Parser_dbind(F_P_dpat(), mk_clo(L867, 2, 1, (V[]){a[0]}));
}
static V F_P_dpat_dcons(V a0, V a1) {
top:;
V s865 = a1;
if ((s865) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L866, 2, 1, (V[]){a0}));
} else if ((s865) == IMM(0)) {
return F_Parser_dpure(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat_dcons(V *a) { (void)a; return F_P_dpat_dcons(a[0], a[1]); }
static V L869(V *a) {
return F_P_dpat1_dk(F_P_dtok__kind(a[0]));
}
static V F_P_dpat1(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L869, 1, 0, 0));
}
static V W_P_dpat1(V *a) { (void)a; return F_P_dpat1(); }
static V S873(void) { static V c; return STRC(c, "{"); }
static V L872(V *a) {
return F_P_dpat_did(a[0], F_Bool_dand(F_P_dtok__is(a[1], S873()), F_Bool_dnot(F_P_dtok__sp(a[1]))));
}
static V L871(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L872, 2, 1, (V[]){a[0]}));
}
static V L874(V *a) {
return F_Parser_dpure(C1(2, a[0]));
}
static V L876(V *a) {
return F_Parser_dpure(C2(3, a[0], a[1]));
}
static V L875(V *a) {
return F_Parser_dbind(F_P_dpat1(), mk_clo(L876, 2, 1, (V[]){a[0]}));
}
static V L877(V *a) {
return F_Parser_dpure(C1(4, a[0]));
}
static V L878(V *a) {
return F_Parser_dpure(C1(4, a[0]));
}
static V L879(V *a) {
return F_Parser_dpure(F_P_dpstr(a[0]));
}
static V S880(void) { static V c; return STRC(c, "+"); }
static V S881(void) { static V c; return STRC(c, "-"); }
static V S882(void) { static V c; return STRC(c, "("); }
static V S883(void) { static V c; return STRC(c, "["); }
static V S884(void) { static V c; return STRC(c, "expected a pattern"); }
static V S886(void) { static V c; return STRC(c, "_"); }
static V L885(V *a) {
return F_Parser_dpure(C1(0, S886()));
}
static V F_P_dpat1_dk(V a0) {
top:;
V s870 = a0;
if (TAG(s870) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L871, 2, 1, (V[]){FLD(s870, 0)}));
} else if (TAG(s870) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L874, 2, 1, (V[]){FLD(s870, 0)}));
} else if (TAG(s870) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L875, 2, 1, (V[]){FLD(s870, 0)}));
} else if (TAG(s870) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L877, 2, 1, (V[]){FLD(s870, 0)}));
} else if (TAG(s870) == 5) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L878, 2, 1, (V[]){FLD(s870, 0)}));
} else if (TAG(s870) == 6) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L879, 2, 1, (V[]){FLD(s870, 0)}));
} else if (TAG(s870) == 7) {
return F_P_dpat_dsym(F_P_dwhich(FLD(s870, 0), C2(1, S880(), C2(1, S881(), C2(1, S882(), C2(1, S883(), IMM(0)))))));
} else {
return F_Parser_dbind(F_P_derr(S884()), mk_clo(L885, 1, 0, 0));
}
}
static V W_P_dpat1_dk(V *a) { (void)a; return F_P_dpat1_dk(a[0]); }
static V L888(V *a) {
return F_P_dpat1();
}
static V L889(V *a) {
return F_P_dpat1();
}
static V S891(void) { static V c; return STRC(c, ")"); }
static V L892(V *a) {
return F_Parser_dpure(F_P_dptuple(a[0]));
}
static V L890(V *a) {
return F_Parser_dbind(F_P_dpats(S891()), mk_clo(L892, 1, 0, 0));
}
static V S894(void) { static V c; return STRC(c, "]"); }
static V L895(V *a) {
return F_Parser_dpure(F_P_dplist(a[0]));
}
static V L893(V *a) {
return F_Parser_dbind(F_P_dpats(S894()), mk_clo(L895, 1, 0, 0));
}
static V S896(void) { static V c; return STRC(c, "expected a pattern"); }
static V S898(void) { static V c; return STRC(c, "_"); }
static V L897(V *a) {
return F_Parser_dpure(C1(0, S898()));
}
static V F_P_dpat_dsym(V a0) {
top:;
V s887 = a0;
if ((s887) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L888, 1, 0, 0));
} else if ((s887) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L889, 1, 0, 0));
} else if ((s887) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L890, 1, 0, 0));
} else if ((s887) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L893, 1, 0, 0));
} else if (nat_ge(s887, 4)) {
return F_Parser_dbind(F_P_derr(S896()), mk_clo(L897, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat_dsym(V *a) { (void)a; return F_P_dpat_dsym(a[0]); }
static V S900(void) { static V c; return STRC(c, "Nil"); }
static V S901(void) { static V c; return STRC(c, "Con"); }
static V F_P_dplist(V a0) {
top:;
V s899 = a0;
if ((s899) == IMM(0)) {
return C2(1, S900(), IMM(0));
} else if (TAG(s899) == 1) {
return C2(1, S901(), C2(1, FLD(s899, 0), C2(1, F_P_dplist(FLD(s899, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dplist(V *a) { (void)a; return F_P_dplist(a[0]); }
static V L902(V *a) {
return F_P_dpats_dgo(a[0], a[1], F_P_dstuck(F_P_dtok__kind(a[1])));
}
static V F_P_dpats(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L902, 2, 1, (V[]){a0}));
}
static V W_P_dpats(V *a) { (void)a; return F_P_dpats(a[0]); }
static V F_P_dpats_dgo(V a0, V a1, V a2) {
top:;
V s903 = a2;
if ((s903) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s903) == IMM(0)) {
return F_P_dpats_dclose(a0, F_P_dtok__is(a1, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpats_dgo(V *a) { (void)a; return F_P_dpats_dgo(a[0], a[1], a[2]); }
static V L905(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dpats_dclose(V a0, V a1) {
top:;
V s904 = a1;
if ((s904) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L905, 1, 0, 0));
} else if ((s904) == IMM(0)) {
return F_P_dpats_ditem(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dpats_dclose(V *a) { (void)a; return F_P_dpats_dclose(a[0], a[1]); }
static V S907(void) { static V c; return STRC(c, ","); }
static V L909(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L908(V *a) {
return F_Parser_dbind(F_P_dpats_dmore(a[1], a[2]), mk_clo(L909, 2, 1, (V[]){a[0]}));
}
static V L906(V *a) {
return F_Parser_dbind(F_P_deat(S907()), mk_clo(L908, 3, 2, (V[]){a[1], a[0]}));
}
static V F_P_dpats_ditem(V a0) {
top:;
return F_Parser_dbind(F_P_dpat(), mk_clo(L906, 2, 1, (V[]){a0}));
}
static V W_P_dpats_ditem(V *a) { (void)a; return F_P_dpats_ditem(a[0]); }
static V L911(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dpats_dmore(V a0, V a1) {
top:;
V s910 = a1;
if ((s910) == IMM(1)) {
return F_P_dpats(a0);
} else if ((s910) == IMM(0)) {
return F_Parser_dbind(F_P_dexpect(a0), mk_clo(L911, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpats_dmore(V *a) { (void)a; return F_P_dpats_dmore(a[0], a[1]); }
static V S913(void) { static V c; return STRC(c, "Unit"); }
static V S914(void) { static V c; return STRC(c, "Tuple"); }
static V F_P_dptuple(V a0) {
top:;
V s912 = a0;
if ((s912) == IMM(0)) {
return C2(1, S913(), IMM(0));
} else if (TAG(s912) == 1 && (FLD(s912, 1)) == IMM(0)) {
return FLD(s912, 0);
} else if (TAG(s912) == 1) {
return C2(1, S914(), C2(1, FLD(s912, 0), C2(1, F_P_dptuple(FLD(s912, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dptuple(V *a) { (void)a; return F_P_dptuple(a[0]); }
static V S916(void) { static V c; return STRC(c, "SNil"); }
static V S917(void) { static V c; return STRC(c, "SCon"); }
static V F_P_dpstr(V a0) {
top:;
V s915 = a0;
if ((s915) == IMM(0)) {
return C2(1, S916(), IMM(0));
} else if (TAG(s915) == 1) {
return C2(1, S917(), C2(1, C1(4, FLD(s915, 0)), C2(1, F_P_dpstr(FLD(s915, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpstr(V *a) { (void)a; return F_P_dpstr(a[0]); }
static V S920(void) { static V c; return STRC(c, "}"); }
static V L921(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L919(V *a) {
return F_Parser_dbind(F_P_dpats(S920()), mk_clo(L921, 2, 1, (V[]){a[0]}));
}
static V F_P_dpat_did(V a0, V a1) {
top:;
V s918 = a1;
if ((s918) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L919, 2, 1, (V[]){a0}));
} else if ((s918) == IMM(0)) {
return F_Parser_dpure(C1(0, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat_did(V *a) { (void)a; return F_P_dpat_did(a[0], a[1]); }
static V L922(V *a) {
return F_P_dscan_dret(a[0]);
}
static V F_P_dscan(void) {
top:;
return mk_clo(L922, 1, 0, 0);
}
static V W_P_dscan(V *a) { (void)a; return F_P_dscan(); }
static V F_P_dscan_dret(V a0) {
top:;
return C2(0, F_P_dscan_dgo(a0, 0u), a0);
}
static V W_P_dscan_dret(V *a) { (void)a; return F_P_dscan_dret(a[0]); }
static V S924(void) { static V c; return STRC(c, "="); }
static V S925(void) { static V c; return STRC(c, "<-"); }
static V S926(void) { static V c; return STRC(c, "("); }
static V S927(void) { static V c; return STRC(c, "["); }
static V S928(void) { static V c; return STRC(c, "{"); }
static V S929(void) { static V c; return STRC(c, ")"); }
static V S930(void) { static V c; return STRC(c, "]"); }
static V S931(void) { static V c; return STRC(c, "}"); }
static V F_P_dscan_dgo(V a0, V a1) {
top:;
V s923 = a0;
if ((s923) == IMM(0)) {
return 0u;
} else if (TAG(s923) == 1 && TAG(FLD(FLD(s923, 0), 0)) == 7) {
return F_P_dscan_dsym(FLD(s923, 1), a1, F_P_dwhich(FLD(FLD(FLD(s923, 0), 0), 0), C2(1, S924(), C2(1, S925(), C2(1, S926(), C2(1, S927(), C2(1, S928(), C2(1, S929(), C2(1, S930(), C2(1, S931(), IMM(0)))))))))));
} else if (TAG(s923) == 1 && TAG(FLD(FLD(s923, 0), 0)) == 0) {
{ V t0 = FLD(s923, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else if (TAG(s923) == 1 && (FLD(FLD(s923, 0), 0)) == IMM(8)) {
return F_P_dscan_dend(FLD(s923, 1), a1, F_U32_dis__zero(a1));
} else if (TAG(s923) == 1 && (FLD(FLD(s923, 0), 0)) == IMM(9)) {
return 0u;
} else if (TAG(s923) == 1 && (FLD(FLD(s923, 0), 0)) == IMM(10)) {
return 0u;
} else if (TAG(s923) == 1 && (FLD(FLD(s923, 0), 0)) == IMM(11)) {
return 0u;
} else if (TAG(s923) == 1 && TAG(FLD(FLD(s923, 0), 0)) == 12) {
return 0u;
} else if (TAG(s923) == 1) {
{ V t0 = FLD(s923, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dgo(V *a) { (void)a; return F_P_dscan_dgo(a[0], a[1]); }
static V F_P_dscan_dend(V a0, V a1, V a2) {
top:;
V s932 = a2;
if ((s932) == IMM(1)) {
return 0u;
} else if ((s932) == IMM(0)) {
return F_P_dscan_dgo(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dend(V *a) { (void)a; return F_P_dscan_dend(a[0], a[1], a[2]); }
static V F_P_dscan_dsym(V a0, V a1, V a2) {
top:;
V s933 = a2;
if ((s933) == 0) {
return F_P_dscan_dtop(a0, a1, 1u, F_U32_dis__zero(a1));
} else if ((s933) == 1) {
return F_P_dscan_dtop(a0, a1, 2u, F_U32_dis__zero(a1));
} else if ((s933) == 2) {
return F_P_dscan_dgo(a0, F_U32_dinc(a1));
} else if ((s933) == 3) {
return F_P_dscan_dgo(a0, F_U32_dinc(a1));
} else if ((s933) == 4) {
return F_P_dscan_dgo(a0, F_U32_dinc(a1));
} else if ((s933) == 5) {
return F_P_dscan_dgo(a0, F_U32_dsub(a1, 1u));
} else if ((s933) == 6) {
return F_P_dscan_dgo(a0, F_U32_dsub(a1, 1u));
} else if ((s933) == 7) {
return F_P_dscan_dgo(a0, F_U32_dsub(a1, 1u));
} else if (nat_ge(s933, 8)) {
return F_P_dscan_dgo(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dsym(V *a) { (void)a; return F_P_dscan_dsym(a[0], a[1], a[2]); }
static V F_P_dscan_dtop(V a0, V a1, V a2, V a3) {
top:;
V s934 = a3;
if ((s934) == IMM(1)) {
return a2;
} else if ((s934) == IMM(0)) {
return F_P_dscan_dgo(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dtop(V *a) { (void)a; return F_P_dscan_dtop(a[0], a[1], a[2], a[3]); }
static V S937(void) { static V c; return STRC(c, "<"); }
static V S940(void) { static V c; return STRC(c, ":"); }
static V L943(V *a) {
return F_Parser_dpure(F_Fold_ddo(a[1], F_P_dinit(a[0]), F_P_dlast(a[0]), a[2]));
}
static V L942(V *a) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L943, 3, 2, (V[]){a[0], a[1]}));
}
static V L941(V *a) {
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L942, 3, 2, (V[]){a[0], a[1]}));
}
static V L939(V *a) {
return F_Parser_dbind(F_P_dexpect(S940()), mk_clo(L941, 3, 2, (V[]){a[1], a[0]}));
}
static V L938(V *a) {
return F_Parser_dbind(F_P_dtyargs(), mk_clo(L939, 2, 1, (V[]){a[0]}));
}
static V L936(V *a) {
return F_Parser_dbind(F_P_dexpect(S937()), mk_clo(L938, 2, 1, (V[]){a[0]}));
}
static V L935(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L936, 1, 0, 0));
}
static V F_P_ddo(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L935, 1, 0, 0));
}
static V W_P_ddo(V *a) { (void)a; return F_P_ddo(); }
static V S945(void) { static V c; return STRC(c, ""); }
static V F_P_dlast(V a0) {
top:;
V s944 = a0;
if ((s944) == IMM(0)) {
return C2(14, S945(), IMM(0));
} else if (TAG(s944) == 1 && (FLD(s944, 1)) == IMM(0)) {
return FLD(s944, 0);
} else if (TAG(s944) == 1) {
{ V t0 = FLD(s944, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dlast(V *a) { (void)a; return F_P_dlast(a[0]); }
static V F_P_dinit(V a0) {
top:;
V s946 = a0;
if ((s946) == IMM(0)) {
return IMM(0);
} else if (TAG(s946) == 1 && (FLD(s946, 1)) == IMM(0)) {
return IMM(0);
} else if (TAG(s946) == 1) {
return C2(1, FLD(s946, 0), F_P_dinit(FLD(s946, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dinit(V *a) { (void)a; return F_P_dinit(a[0]); }
static V S948(void) { static V c; return STRC(c, "empty do block"); }
static V S949(void) { static V c; return STRC(c, "pure"); }
static V S950(void) { static V c; return STRC(c, ""); }
static V S951(void) { static V c; return STRC(c, "bind"); }
static V S952(void) { static V c; return STRC(c, ""); }
static V S953(void) { static V c; return STRC(c, "pure"); }
static V S954(void) { static V c; return STRC(c, "bind"); }
static V S955(void) { static V c; return STRC(c, ""); }
static V S956(void) { static V c; return STRC(c, "_"); }
static V F_Fold_ddo(V a0, V a1, V a2, V a3) {
top:;
V s947 = a3;
if ((s947) == IMM(0)) {
return C1(15, S948());
} else if (TAG(s947) == 1 && TAG(FLD(s947, 0)) == 0 && (FLD(s947, 1)) == IMM(0)) {
return FLD(FLD(s947, 0), 1);
} else if (TAG(s947) == 1 && TAG(FLD(s947, 0)) == 1 && (FLD(s947, 1)) == IMM(0)) {
return FLD(FLD(s947, 0), 1);
} else if (TAG(s947) == 1 && TAG(FLD(s947, 0)) == 2 && (FLD(s947, 1)) == IMM(0)) {
return F_Fold_dapp(a0, S949(), a1, C2(1, a2, C2(1, FLD(FLD(s947, 0), 0), IMM(0))));
} else if (TAG(s947) == 1 && TAG(FLD(s947, 0)) == 3 && (FLD(s947, 1)) == IMM(0)) {
return FLD(FLD(s947, 0), 0);
} else if (TAG(s947) == 1 && (FLD(s947, 0)) == IMM(4) && (FLD(s947, 1)) == IMM(0)) {
return C2(14, S950(), IMM(0));
} else if (TAG(s947) == 1 && TAG(FLD(s947, 0)) == 0) {
return C3(8, FLD(FLD(s947, 0), 0), FLD(FLD(s947, 0), 1), F_Fold_ddo(a0, a1, a2, FLD(s947, 1)));
} else if (TAG(s947) == 1 && TAG(FLD(s947, 0)) == 1) {
return F_Fold_dapp(a0, S951(), a1, C2(1, C2(14, S952(), IMM(0)), C2(1, a2, C2(1, FLD(FLD(s947, 0), 1), C2(1, C2(7, C1(0, FLD(FLD(s947, 0), 0)), F_Fold_ddo(a0, a1, a2, FLD(s947, 1))), IMM(0))))));
} else if (TAG(s947) == 1 && TAG(FLD(s947, 0)) == 2) {
return F_Fold_dapp(a0, S953(), a1, C2(1, a2, C2(1, FLD(FLD(s947, 0), 0), IMM(0))));
} else if (TAG(s947) == 1 && TAG(FLD(s947, 0)) == 3) {
return F_Fold_dapp(a0, S954(), a1, C2(1, C2(14, S955(), IMM(0)), C2(1, a2, C2(1, FLD(FLD(s947, 0), 0), C2(1, C2(7, C1(0, S956()), F_Fold_ddo(a0, a1, a2, FLD(s947, 1))), IMM(0))))));
} else if (TAG(s947) == 1 && (FLD(s947, 0)) == IMM(4)) {
{ V t0 = a0; V t1 = a1; V t2 = a2; V t3 = FLD(s947, 1); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Fold_ddo(V *a) { (void)a; return F_Fold_ddo(a[0], a[1], a[2], a[3]); }
static V S957(void) { static V c; return STRC(c, "."); }
static V F_Fold_dapp(V a0, V a1, V a2, V a3) {
top:;
return C2(5, C1(0, F_String_dappend(a0, F_String_dappend(S957(), a1))), F_List_dappend(a2, a3));
}
static V W_Fold_dapp(V *a) { (void)a; return F_Fold_dapp(a[0], a[1], a[2], a[3]); }
static V S960(void) { static V c; return STRC(c, ":"); }
static V L963(V *a) {
return F_Parser_dpure(C2(9, a[0], a[1]));
}
static V L962(V *a) {
return F_Parser_dbind(F_P_dmatch_dbody(F_P_dis__in(a[1])), mk_clo(L963, 2, 1, (V[]){a[0]}));
}
static V L961(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L962, 2, 1, (V[]){a[0]}));
}
static V L959(V *a) {
return F_Parser_dbind(F_P_dexpect(S960()), mk_clo(L961, 2, 1, (V[]){a[0]}));
}
static V L958(V *a) {
return F_Parser_dbind(F_P_dscrs(), mk_clo(L959, 1, 0, 0));
}
static V F_P_dmatch(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L958, 1, 0, 0));
}
static V W_P_dmatch(V *a) { (void)a; return F_P_dmatch(); }
static V L965(V *a) {
return F_P_dcases();
}
static V F_P_dmatch_dbody(V a0) {
top:;
V s964 = a0;
if ((s964) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L965, 1, 0, 0));
} else if ((s964) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dmatch_dbody(V *a) { (void)a; return F_P_dmatch_dbody(a[0]); }
static V L967(V *a) {
return F_P_dcases_dde(F_P_dis__de(a[0]));
}
static V L966(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L967, 1, 0, 0));
}
static V F_P_dcases(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L966, 1, 0, 0));
}
static V W_P_dcases(V *a) { (void)a; return F_P_dcases(); }
static V L969(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S971(void) { static V c; return STRC(c, "case"); }
static V L970(V *a) {
return F_P_dcases_dgo(F_P_dtok__which__id(a[0], C2(1, S971(), IMM(0))));
}
static V F_P_dcases_dde(V a0) {
top:;
V s968 = a0;
if ((s968) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L969, 1, 0, 0));
} else if ((s968) == IMM(0)) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L970, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dcases_dde(V *a) { (void)a; return F_P_dcases_dde(a[0]); }
static V S974(void) { static V c; return STRC(c, ":"); }
static V S976(void) { static V c; return STRC(c, ":"); }
static V L979(V *a) {
return F_Parser_dpure(C2(1, C2(10, a[1], a[0]), a[2]));
}
static V L978(V *a) {
return F_Parser_dbind(F_P_dcases(), mk_clo(L979, 3, 2, (V[]){a[1], a[0]}));
}
static V L977(V *a) {
return F_Parser_dbind(F_P_dbody(), mk_clo(L978, 2, 1, (V[]){a[0]}));
}
static V L975(V *a) {
return F_Parser_dbind(F_P_dexpect(S976()), mk_clo(L977, 2, 1, (V[]){a[0]}));
}
static V L973(V *a) {
return F_Parser_dbind(F_P_dpat__seq(C2(1, S974(), IMM(0))), mk_clo(L975, 1, 0, 0));
}
static V F_P_dcases_dgo(V a0) {
top:;
V s972 = a0;
if ((s972) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L973, 1, 0, 0));
} else if (nat_ge(s972, 1)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dcases_dgo(V *a) { (void)a; return F_P_dcases_dgo(a[0]); }
static V L981(V *a) {
return F_Parser_dpure(F_Fold_dplain(a[0]));
}
static V L980(V *a) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L981, 1, 0, 0));
}
static V F_P_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L980, 1, 0, 0));
}
static V W_P_dbody(V *a) { (void)a; return F_P_dbody(); }
static V S983(void) { static V c; return STRC(c, ":"); }
static V L982(V *a) {
return F_P_dscrs_dgo(a[0], F_Bool_dor(F_P_dtok__is(a[0], S983()), F_P_dstuck(F_P_dtok__kind(a[0]))));
}
static V F_P_dscrs(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L982, 1, 0, 0));
}
static V W_P_dscrs(V *a) { (void)a; return F_P_dscrs(); }
static V L986(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L985(V *a) {
return F_Parser_dbind(F_P_dscrs(), mk_clo(L986, 2, 1, (V[]){a[0]}));
}
static V F_P_dscrs_dgo(V a0, V a1) {
top:;
V s984 = a1;
if ((s984) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s984) == IMM(0)) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L985, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dscrs_dgo(V *a) { (void)a; return F_P_dscrs_dgo(a[0], a[1]); }
static V L987(V *a) {
return F_P_deff_dgo(a[0], IMM(0));
}
static V F_P_deff_dimports(void) {
top:;
return mk_clo(L987, 1, 0, 0);
}
static V W_P_deff_dimports(V *a) { (void)a; return F_P_deff_dimports(); }
static V F_P_deff_dgo(V a0, V a1) {
top:;
V s988 = a0;
if ((s988) == IMM(0)) {
return C2(0, a1, IMM(0));
} else if (TAG(s988) == 1 && TAG(FLD(FLD(s988, 0), 0)) == 6) {
{ V t0 = FLD(s988, 1); V t1 = F_List_dappend(a1, C2(1, FLD(FLD(FLD(s988, 0), 0), 0), IMM(0))); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s988) == 1 && (FLD(FLD(s988, 0), 0)) == IMM(10)) {
return C2(0, a1, FLD(s988, 1));
} else if (TAG(s988) == 1 && (FLD(FLD(s988, 0), 0)) == IMM(11)) {
return C2(0, a1, C2(1, C3(0, IMM(11), FLD(FLD(s988, 0), 1), FLD(FLD(s988, 0), 2)), FLD(s988, 1)));
} else if (TAG(s988) == 1 && TAG(FLD(FLD(s988, 0), 0)) == 12) {
return C2(0, a1, C2(1, C3(0, C1(12, FLD(FLD(FLD(s988, 0), 0), 0)), FLD(FLD(s988, 0), 1), FLD(FLD(s988, 0), 2)), FLD(s988, 1)));
} else if (TAG(s988) == 1) {
{ V t0 = FLD(s988, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_deff_dgo(V *a) { (void)a; return F_P_deff_dgo(a[0], a[1]); }
static V L990(V *a) {
return F_P_dexpr();
}
static V S991(void) { static V c; return STRC(c, ""); }
static V F_P_dret_dgo(V a0) {
top:;
V s989 = a0;
if ((s989) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L990, 1, 0, 0));
} else if ((s989) == IMM(0)) {
return F_Parser_dpure(C2(14, S991(), IMM(0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dret_dgo(V *a) { (void)a; return F_P_dret_dgo(a[0]); }
static V S993(void) { static V c; return STRC(c, ")"); }
static V L992(V *a) {
return F_P_dparams_dgo(F_Bool_dor(F_P_dtok__is(a[0], S993()), F_P_dstuck(F_P_dtok__kind(a[0]))));
}
static V F_P_dparams(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L992, 1, 0, 0));
}
static V W_P_dparams(V *a) { (void)a; return F_P_dparams(); }
static V L995(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S997(void) { static V c; return STRC(c, ","); }
static V L999(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L998(V *a) {
return F_Parser_dbind(F_P_dparams_dmore(a[1]), mk_clo(L999, 2, 1, (V[]){a[0]}));
}
static V L996(V *a) {
return F_Parser_dbind(F_P_deat(S997()), mk_clo(L998, 2, 1, (V[]){a[0]}));
}
static V F_P_dparams_dgo(V a0) {
top:;
V s994 = a0;
if ((s994) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L995, 1, 0, 0));
} else if ((s994) == IMM(0)) {
return F_Parser_dbind(F_P_dparam(), mk_clo(L996, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparams_dgo(V *a) { (void)a; return F_P_dparams_dgo(a[0]); }
static V S1001(void) { static V c; return STRC(c, ")"); }
static V L1002(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dparams_dmore(V a0) {
top:;
V s1000 = a0;
if ((s1000) == IMM(1)) {
return F_P_dparams();
} else if ((s1000) == IMM(0)) {
return F_Parser_dbind(F_P_dexpect(S1001()), mk_clo(L1002, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparams_dmore(V *a) { (void)a; return F_P_dparams_dmore(a[0]); }
static V F_P_dfile_dfin(V a0) {
top:;
V v1003 = a0;
return C2(0, FLD(v1003, 0), F_P_dfile_derr(FLD(v1003, 1)));
}
static V W_P_dfile_dfin(V *a) { (void)a; return F_P_dfile_dfin(a[0]); }
static V S1005(void) { static V c; return STRC(c, ""); }
static V F_P_dfile_derr(V a0) {
top:;
V s1004 = a0;
if (TAG(s1004) == 1 && TAG(FLD(FLD(s1004, 0), 0)) == 12) {
return FLD(FLD(FLD(s1004, 0), 0), 0);
} else {
return S1005();
}
}
static V W_P_dfile_derr(V *a) { (void)a; return F_P_dfile_derr(a[0]); }
static V F_Main_dparse_dfin(V a0) {
top:;
V v1006 = a0;
return F_Bool_dpick(F_String_dis__empty(FLD(v1006, 1)), C1(1, FLD(v1006, 0)), C1(0, FLD(v1006, 1)));
}
static V W_Main_dparse_dfin(V *a) { (void)a; return F_Main_dparse_dfin(a[0]); }
static V F_String_dis__empty(V a0) {
top:;
V s1007 = a0;
if ((s1007) == IMM(0)) {
return IMM(1);
} else if (TAG(s1007) == 1) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_String_dis__empty(V *a) { (void)a; return F_String_dis__empty(a[0]); }
static V F_Mod_ddir(V a0) {
top:;
return F_Str_drev(F_Mod_ddir_dgo(F_Str_drev(a0)));
}
static V W_Mod_ddir(V *a) { (void)a; return F_Mod_ddir(a[0]); }
static V F_Mod_ddir_dgo(V a0) {
top:;
V s1008 = a0;
if ((s1008) == IMM(0)) {
return IMM(0);
} else if (TAG(s1008) == 1) {
return F_Mod_ddir_dif(FLD(s1008, 0), FLD(s1008, 1), F_U32_dis__eq(FLD(s1008, 0), 47u));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddir_dgo(V *a) { (void)a; return F_Mod_ddir_dgo(a[0]); }
static V F_Mod_ddir_dif(V a0, V a1, V a2) {
top:;
V s1009 = a2;
if ((s1009) == IMM(1)) {
return C2(1, a0, a1);
} else if ((s1009) == IMM(0)) {
return F_Mod_ddir_dgo(a1);
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddir_dif(V *a) { (void)a; return F_Mod_ddir_dif(a[0], a[1], a[2]); }
static V F_Main_dresolve(V a0, V a1) {
top:;
V s1010 = a1;
if (TAG(s1010) == 0) {
return C1(0, FLD(s1010, 0));
} else if (TAG(s1010) == 1) {
return C1(1, F_Eff_ddecls(a0, FLD(s1010, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dresolve(V *a) { (void)a; return F_Main_dresolve(a[0], a[1]); }
static V F_Eff_ddecls(V a0, V a1) {
top:;
V s1011 = a1;
if ((s1011) == IMM(0)) {
return IMM(0);
} else if (TAG(s1011) == 1) {
return C2(1, F_Eff_ddecl(a0, FLD(s1011, 0)), F_Eff_ddecls(a0, FLD(s1011, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Eff_ddecls(V *a) { (void)a; return F_Eff_ddecls(a[0], a[1]); }
static V F_Eff_ddecl(V a0, V a1) {
top:;
V s1012 = a1;
if (TAG(s1012) == 1) {
return C3(1, FLD(s1012, 0), FLD(s1012, 1), F_Eff_dpaths(a0, FLD(s1012, 2)));
} else {
return s1012;
}
}
static V W_Eff_ddecl(V *a) { (void)a; return F_Eff_ddecl(a[0], a[1]); }
static V F_Eff_dpaths(V a0, V a1) {
top:;
V s1013 = a1;
if ((s1013) == IMM(0)) {
return IMM(0);
} else if (TAG(s1013) == 1) {
return C2(1, F_Eff_dpath(a0, FLD(s1013, 0)), F_Eff_dpaths(a0, FLD(s1013, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Eff_dpaths(V *a) { (void)a; return F_Eff_dpaths(a[0], a[1]); }
static V S1014(void) { static V c; return STRC(c, "/"); }
static V F_Eff_dpath(V a0, V a1) {
top:;
return F_Bool_dpick(F_String_dstarts__with(a1, S1014()), a1, F_String_dappend(a0, a1));
}
static V W_Eff_dpath(V *a) { (void)a; return F_Eff_dpath(a[0], a[1]); }
static V S1017(void) { static V c; return STRC(c, "bendc: parse error in base: "); }
static V S1018(void) { static V c; return STRC(c, "bendc: parse error: "); }
static V F_Main_dcompile(V a0, V a1) {
top:;
V s1015 = a0;
V s1016 = a1;
if (TAG(s1015) == 0) {
return F_IO_ddie(1u, F_String_dappend(S1017(), FLD(s1015, 0)));
} else if (TAG(s1015) == 1 && TAG(s1016) == 0) {
return F_IO_ddie(1u, F_String_dappend(S1018(), FLD(s1016, 0)));
} else if (TAG(s1015) == 1 && TAG(s1016) == 1) {
return F_Main_demit(F_Gen_dprogram(F_List_dappend(FLD(s1015, 0), FLD(s1016, 0))));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dcompile(V *a) { (void)a; return F_Main_dcompile(a[0], a[1]); }
static V F_Gen_dprogram(V a0) {
top:;
V v1019 = F_G_dnew(a0);
return F_Gen_dprogram_dfin(F_Gen_dcids(v1019, a0, 0u), apply(F_Gen_dprogram_dm(v1019), CN(0, 7, (V[]){0u, IMM(0), IMM(0), IMM(0), IMM(0), IMM(0), IMM(0)})));
}
static V W_Gen_dprogram(V *a) { (void)a; return F_Gen_dprogram(a[0]); }
static V S1020(void) { static V c; return STRC(c, "main"); }
static V S1022(void) { static V c; return STRC(c, "main"); }
static V L1021(V *a) {
return F_Gen_dentry(a[0], F_G_dbody(a[0], S1022()));
}
static V F_Gen_dprogram_dm(V a0) {
top:;
return F_Gen_dbind(F_Gen_dall(a0, C2(1, S1020(), IMM(0)), F_Set_dnew()), mk_clo(L1021, 2, 1, (V[]){a0}));
}
static V W_Gen_dprogram_dm(V *a) { (void)a; return F_Gen_dprogram_dm(a[0]); }
static V S1024(void) { static V c; return STRC(c, ""); }
static V S1025(void) { static V c; return STRC(c, ""); }
static V F_G_dbody(V a0, V a1) {
top:;
V v1023 = a0;
return F_G_dget(C2(4, S1024(), S1025()), FLD(v1023, 2), a1);
}
static V W_G_dbody(V *a) { (void)a; return F_G_dbody(a[0], a[1]); }
static V F_G_dget(V a1, V a2, V a3) {
top:;
return F_Pair_dsnd(F_Map_dget(a1, a2, a3));
}
static V W_G_dget(V *a) { (void)a; return F_G_dget(a[1], a[2], a[3]); }
static V F_Map_dget(V a1, V a2, V a3) {
top:;
V s1026 = a2;
if ((s1026) == IMM(0)) {
return C2(0, IMM(0), a1);
} else if (TAG(s1026) == 1) {
return F_Map_dget_dleaf(a1, FLD(s1026, 1), F_String_dcmp(a3, FLD(s1026, 0)));
} else if (TAG(s1026) == 2) {
return F_Map_dget_dbit(a1, FLD(s1026, 1), FLD(s1026, 2), FLD(s1026, 0), F_Map_dbit(a3, FLD(s1026, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dget(V *a) { (void)a; return F_Map_dget(a[1], a[2], a[3]); }
static V F_Map_dget_dbit(V a1, V a2, V a3, V a4, V a5) {
top:;
V v1027 = a5;
V s1028 = FLD(v1027, 1);
if ((s1028) == IMM(0)) {
return F_Map_dlo(a4, a3, F_Map_dget(a1, a2, FLD(v1027, 0)));
} else if ((s1028) == IMM(1)) {
return F_Map_dhi(a4, a2, F_Map_dget(a1, a3, FLD(v1027, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dget_dbit(V *a) { (void)a; return F_Map_dget_dbit(a[1], a[2], a[3], a[4], a[5]); }
static V F_Map_dhi(V a3, V a4, V a5) {
top:;
V v1029 = a5;
return C2(0, C3(2, a3, a4, FLD(v1029, 0)), FLD(v1029, 1));
}
static V W_Map_dhi(V *a) { (void)a; return F_Map_dhi(a[3], a[4], a[5]); }
static V F_Map_dlo(V a3, V a4, V a5) {
top:;
V v1030 = a5;
return C2(0, C3(2, a3, FLD(v1030, 0), a4), FLD(v1030, 1));
}
static V W_Map_dlo(V *a) { (void)a; return F_Map_dlo(a[3], a[4], a[5]); }
static V F_Map_dget_dleaf(V a1, V a2, V a3) {
top:;
V v1031 = a3;
V s1032 = FLD(v1031, 1);
if ((s1032) == IMM(0)) {
return C2(0, C2(1, FLD(FLD(v1031, 0), 1), a2), a1);
} else if ((s1032) == IMM(1)) {
return C2(0, C2(1, FLD(FLD(v1031, 0), 1), a2), a2);
} else if ((s1032) == IMM(2)) {
return C2(0, C2(1, FLD(FLD(v1031, 0), 1), a2), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Map_dget_dleaf(V *a) { (void)a; return F_Map_dget_dleaf(a[1], a[2], a[3]); }
static V S1034(void) { static V c; return STRC(c, "IO"); }
static V S1035(void) { static V c; return STRC(c, "no main definition"); }
static V S1037(void) { static V c; return STRC(c, ""); }
static V L1036(V *a) {
return F_Gen_dpure(S1037());
}
static V F_Gen_dentry(V a0, V a1) {
top:;
V s1033 = a1;
if (TAG(s1033) == 0) {
return F_Gen_dentry_dty(a0, FLD(s1033, 3), F_Str_deq(F_Ty_dhead(FLD(s1033, 3)), S1034()));
} else {
return F_Gen_dbind(F_Gen_derror(S1035()), mk_clo(L1036, 1, 0, 0));
}
}
static V W_Gen_dentry(V *a) { (void)a; return F_Gen_dentry(a[0], a[1]); }
static V L1038(V *a) {
return C2(0, a[0], a[1]);
}
static V F_Gen_dpure(V a1) {
top:;
return mk_clo(L1038, 2, 1, (V[]){a1});
}
static V W_Gen_dpure(V *a) { (void)a; return F_Gen_dpure(a[1]); }
static V L1039(V *a) {
return F_Gen_derror_dgo(a[0], a[1]);
}
static V F_Gen_derror(V a0) {
top:;
return mk_clo(L1039, 2, 1, (V[]){a0});
}
static V W_Gen_derror(V *a) { (void)a; return F_Gen_derror(a[0]); }
static V F_Gen_derror_dgo(V a0, V a1) {
top:;
V v1040 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v1040, 0), FLD(v1040, 1), FLD(v1040, 2), FLD(v1040, 3), C2(1, a0, FLD(v1040, 4)), FLD(v1040, 5), FLD(v1040, 6)}));
}
static V W_Gen_derror_dgo(V *a) { (void)a; return F_Gen_derror_dgo(a[0], a[1]); }
static V L1041(V *a) {
return F_Gen_dgo(apply(a[1], a[4]), a[0]);
}
static V F_Gen_dbind(V a2, V a3) {
top:;
return mk_clo(L1041, 5, 4, (V[]){a3, a2, 0, 0});
}
static V W_Gen_dbind(V *a) { (void)a; return F_Gen_dbind(a[2], a[3]); }
static V F_Gen_dgo(V a2, V a3) {
top:;
V v1042 = a2;
return apply(apply(a3, FLD(v1042, 0)), FLD(v1042, 1));
}
static V W_Gen_dgo(V *a) { (void)a; return F_Gen_dgo(a[2], a[3]); }
static V S1044(void) { static V c; return STRC(c, "\077"); }
static V F_Ty_dhead(V a0) {
top:;
V s1043 = a0;
if (TAG(s1043) == 0) {
return FLD(s1043, 0);
} else if (TAG(s1043) == 14) {
return FLD(s1043, 0);
} else if (TAG(s1043) == 5 && TAG(FLD(s1043, 0)) == 0) {
return FLD(FLD(s1043, 0), 0);
} else {
return S1044();
}
}
static V W_Ty_dhead(V *a) { (void)a; return F_Ty_dhead(a[0]); }
static V S1046(void) { static V c; return STRC(c, "int main(int argc, char **argv) { return bend_run(argc, argv, F_main); }\012"); }
static V S1048(void) { static V c; return STRC(c, "int main(int argc, char **argv) { return bend_run_value(argc, argv, F_main, "); }
static V S1049(void) { static V c; return STRC(c, "); }\012"); }
static V L1047(V *a) {
return F_Gen_dpure(F_String_dappend(S1048(), F_String_dappend(a[0], S1049())));
}
static V F_Gen_dentry_dty(V a0, V a1, V a2) {
top:;
V s1045 = a2;
if ((s1045) == IMM(1)) {
return F_Gen_dpure(S1046());
} else if ((s1045) == IMM(0)) {
return F_Gen_dbind(F_Gen_dprinter(a0, a1), mk_clo(L1047, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dentry_dty(V *a) { (void)a; return F_Gen_dentry_dty(a[0], a[1], a[2]); }
static V L1051(V *a) {
return F_Gen_dprinter_dmemo(a[2], a[1], a[0], a[3]);
}
static V F_Gen_dprinter(V a0, V a1) {
top:;
V v1050 = F_Expr_dshow(a1);
return F_Gen_dbind(F_Gen_dmemo_dfind(v1050), mk_clo(L1051, 4, 3, (V[]){v1050, a1, a0}));
}
static V W_Gen_dprinter(V *a) { (void)a; return F_Gen_dprinter(a[0], a[1]); }
static V S1054(void) { static V c; return STRC(c, "P"); }
static V S1057(void) { static V c; return STRC(c, "static void "); }
static V S1058(void) { static V c; return STRC(c, "(V v);\012"); }
static V S1061(void) { static V c; return STRC(c, "static void "); }
static V S1062(void) { static V c; return STRC(c, "(V v) {\012"); }
static V S1063(void) { static V c; return STRC(c, "}\012"); }
static V L1064(V *a) {
return F_Gen_dpure(a[0]);
}
static V L1060(V *a) {
return F_Gen_dbind(F_Gen_dcode(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1061(), F_String_dappend(a[0], S1062()))), C2(1, a[1], C2(1, C1(1, S1063()), IMM(0)))))), mk_clo(L1064, 2, 1, (V[]){a[0]}));
}
static V L1059(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dbody(a[2], a[1], F_Ty_dhead(a[1])), mk_clo(L1060, 2, 1, (V[]){a[0]}));
}
static V L1056(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S1057(), F_String_dappend(a[2], S1058())))), mk_clo(L1059, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L1055(V *a) {
return F_Gen_dbind(F_Gen_dmemo_dadd(C2(0, a[2], a[3])), mk_clo(L1056, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V L1053(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1054(), F_U32_dshow(a[3]))), mk_clo(L1055, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Gen_dprinter_dmemo(V a0, V a1, V a2, V a3) {
top:;
V s1052 = a3;
if (TAG(s1052) == 1) {
return F_Gen_dpure(FLD(s1052, 0));
} else if ((s1052) == IMM(0)) {
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1053, 4, 3, (V[]){a1, a0, a2}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dmemo(V *a) { (void)a; return F_Gen_dprinter_dmemo(a[0], a[1], a[2], a[3]); }
static V F_Doc_dlist(V a0) {
top:;
V s1065 = a0;
if ((s1065) == IMM(0)) {
return IMM(0);
} else if (TAG(s1065) == 1) {
return C2(2, FLD(s1065, 0), F_Doc_dlist(FLD(s1065, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dlist(V *a) { (void)a; return F_Doc_dlist(a[0]); }
static V L1066(V *a) {
return F_Gen_dcode_dgo(a[0], a[1]);
}
static V F_Gen_dcode(V a0) {
top:;
return mk_clo(L1066, 2, 1, (V[]){a0});
}
static V W_Gen_dcode(V *a) { (void)a; return F_Gen_dcode(a[0]); }
static V F_Gen_dcode_dgo(V a0, V a1) {
top:;
V v1067 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v1067, 0), FLD(v1067, 1), C2(2, FLD(v1067, 2), a0), FLD(v1067, 3), FLD(v1067, 4), FLD(v1067, 5), FLD(v1067, 6)}));
}
static V W_Gen_dcode_dgo(V *a) { (void)a; return F_Gen_dcode_dgo(a[0], a[1]); }
static V S1068(void) { static V c; return STRC(c, "U32"); }
static V S1069(void) { static V c; return STRC(c, "Nat"); }
static V S1070(void) { static V c; return STRC(c, "F32"); }
static V S1071(void) { static V c; return STRC(c, "Char"); }
static V S1072(void) { static V c; return STRC(c, "String"); }
static V S1073(void) { static V c; return STRC(c, "List"); }
static V S1074(void) { static V c; return STRC(c, "&"); }
static V S1075(void) { static V c; return STRC(c, "->"); }
static V F_Gen_dprinter_dbody(V a0, V a1, V a2) {
top:;
return F_Gen_dprinter_dhead(a0, a1, F_P_dwhich(a2, C2(1, S1068(), C2(1, S1069(), C2(1, S1070(), C2(1, S1071(), C2(1, S1072(), C2(1, S1073(), C2(1, S1074(), C2(1, S1075(), IMM(0)))))))))));
}
static V W_Gen_dprinter_dbody(V *a) { (void)a; return F_Gen_dprinter_dbody(a[0], a[1], a[2]); }
static V S1077(void) { static V c; return STRC(c, "pr_u32(v);\012"); }
static V S1078(void) { static V c; return STRC(c, "pr_nat(v);\012"); }
static V S1079(void) { static V c; return STRC(c, "pr_f32(v);\012"); }
static V S1080(void) { static V c; return STRC(c, "pr_char(v);\012"); }
static V S1081(void) { static V c; return STRC(c, "pr_str(v);\012"); }
static V S1083(void) { static V c; return STRC(c, "pr_s(\042[\042);\012for (int i = 0; TAG(v) == 1; i++) { if (i) pr_s(\042, \042); "); }
static V S1084(void) { static V c; return STRC(c, "(FLD(v, 0)); v = FLD(v, 1); }\012pr_s(\042]\042);\012"); }
static V L1082(V *a) {
return F_Gen_dpure(C1(1, F_String_dappend(S1083(), F_String_dappend(a[0], S1084()))));
}
static V S1085(void) { static V c; return STRC(c, "v"); }
static V S1087(void) { static V c; return STRC(c, "pr_s(\042(\042);\012"); }
static V S1088(void) { static V c; return STRC(c, "pr_s(\042)\042);\012"); }
static V L1086(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1087()), C2(1, a[0], C2(1, C1(1, S1088()), IMM(0))))));
}
static V S1089(void) { static V c; return STRC(c, "(void)v; pr_s(\042<function>\042);\012"); }
static V S1090(void) { static V c; return STRC(c, "%"); }
static V F_Gen_dprinter_dhead(V a0, V a1, V a2) {
top:;
V s1076 = a2;
if ((s1076) == 0) {
return F_Gen_dpure(C1(1, S1077()));
} else if ((s1076) == 1) {
return F_Gen_dpure(C1(1, S1078()));
} else if ((s1076) == 2) {
return F_Gen_dpure(C1(1, S1079()));
} else if ((s1076) == 3) {
return F_Gen_dpure(C1(1, S1080()));
} else if ((s1076) == 4) {
return F_Gen_dpure(C1(1, S1081()));
} else if ((s1076) == 5) {
return F_Gen_dbind(F_Gen_dprinter(a0, F_P_dlast(F_Ty_dargs(a1))), mk_clo(L1082, 1, 0, 0));
} else if ((s1076) == 6) {
return F_Gen_dbind(F_Gen_dprinter_dtuple(a0, F_Ty_dtuple(a1), S1085()), mk_clo(L1086, 1, 0, 0));
} else if ((s1076) == 7) {
return F_Gen_dpure(C1(1, S1089()));
} else if (nat_ge(s1076, 8)) {
return F_Gen_dprinter_dadt(a0, a1, F_G_dbody(a0, F_String_dappend(S1090(), F_Ty_dhead(a1))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dhead(V *a) { (void)a; return F_Gen_dprinter_dhead(a[0], a[1], a[2]); }
static V S1093(void) { static V c; return STRC(c, "pr_s(\042\077\042);\012"); }
static V L1092(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, C1(1, S1093()), IMM(0)))));
}
static V S1094(void) { static V c; return STRC(c, "(void)v; pr_s(\042\077\042);\012"); }
static V F_Gen_dprinter_dadt(V a0, V a1, V a2) {
top:;
V s1091 = a2;
if (TAG(s1091) == 3) {
return F_Gen_dbind(F_Gen_dprinter_dctors(a0, F_Ty_dbind(FLD(s1091, 1), F_Ty_dargs(a1)), FLD(s1091, 2)), mk_clo(L1092, 1, 0, 0));
} else {
return F_Gen_dpure(C1(1, S1094()));
}
}
static V W_Gen_dprinter_dadt(V *a) { (void)a; return F_Gen_dprinter_dadt(a[0], a[1], a[2]); }
static V F_Ty_dargs(V a0) {
top:;
V s1095 = a0;
if (TAG(s1095) == 14) {
return FLD(s1095, 1);
} else if (TAG(s1095) == 5) {
return FLD(s1095, 1);
} else {
return IMM(0);
}
}
static V W_Ty_dargs(V *a) { (void)a; return F_Ty_dargs(a[0]); }
static V F_Ty_dbind(V a0, V a1) {
top:;
return F_Ty_dbind_dgo(F_List_dreverse(a0), F_List_dreverse(a1));
}
static V W_Ty_dbind(V *a) { (void)a; return F_Ty_dbind(a[0], a[1]); }
static V F_Ty_dbind_dgo(V a0, V a1) {
top:;
V s1096 = a0;
V s1097 = a1;
if (TAG(s1096) == 1 && TAG(s1097) == 1) {
return C2(1, C2(0, FLD(s1096, 0), FLD(s1097, 0)), F_Ty_dbind_dgo(FLD(s1096, 1), FLD(s1097, 1)));
} else {
return IMM(0);
}
}
static V W_Ty_dbind_dgo(V *a) { (void)a; return F_Ty_dbind_dgo(a[0], a[1]); }
static V L1100(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V L1099(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dctors(a[2], a[1], a[0]), mk_clo(L1100, 2, 1, (V[]){a[3]}));
}
static V F_Gen_dprinter_dctors(V a0, V a1, V a2) {
top:;
V s1098 = a2;
if ((s1098) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1098) == 1) {
return F_Gen_dbind(F_Gen_dprinter_dctor(a0, a1, FLD(FLD(s1098, 0), 0), FLD(FLD(s1098, 0), 1), F_G_dctor(a0, FLD(FLD(s1098, 0), 0))), mk_clo(L1099, 4, 3, (V[]){FLD(s1098, 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dctors(V *a) { (void)a; return F_Gen_dprinter_dctors(a[0], a[1], a[2]); }
static V F_G_dctor(V a0, V a1) {
top:;
V v1101 = a0;
return F_Pair_dsnd(F_Map_dget(IMM(0), F_G_dopt__ctors(FLD(v1101, 0)), a1));
}
static V W_G_dctor(V *a) { (void)a; return F_G_dctor(a[0], a[1]); }
static V F_G_dopt__ctors(V a0) {
top:;
V s1102 = a0;
if ((s1102) == IMM(0)) {
return IMM(0);
} else if (TAG(s1102) == 1) {
return C2(1, FLD(s1102, 0), C1(1, FLD(s1102, 1)));
} else if (TAG(s1102) == 2) {
return C3(2, FLD(s1102, 0), F_G_dopt__ctors(FLD(s1102, 1)), F_G_dopt__ctors(FLD(s1102, 2)));
} else { bend_fail("incomplete match"); }
}
static V W_G_dopt__ctors(V *a) { (void)a; return F_G_dopt__ctors(a[0]); }
static V S1104(void) { static V c; return STRC(c, "v"); }
static V S1105(void) { static V c; return STRC(c, "FLD(v, "); }
static V S1107(void) { static V c; return STRC(c, " { pr_s(\042"); }
static V S1108(void) { static V c; return STRC(c, "{\042);\012"); }
static V S1109(void) { static V c; return STRC(c, "pr_s(\042}\042); return; }\012"); }
static V L1106(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(F_Gen_dprinter_dtest(a[3], a[2], a[1]), F_String_dappend(S1107(), F_String_dappend(a[0], S1108())))), C2(1, a[4], C2(1, C1(1, S1109()), IMM(0))))));
}
static V F_Gen_dprinter_dctor(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1103 = a4;
if ((s1103) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1103) == 1) {
return F_Gen_dbind(F_Gen_dprinter_dfields(a0, a1, a3, F_Bool_dpick(F_U32_dis__eq(FLD(FLD(s1103, 0), 2), 2u), S1104(), S1105()), 0u), mk_clo(L1106, 5, 4, (V[]){a2, FLD(FLD(s1103, 0), 3), FLD(FLD(s1103, 0), 0), FLD(FLD(s1103, 0), 2)}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dctor(V *a) { (void)a; return F_Gen_dprinter_dctor(a[0], a[1], a[2], a[3], a[4]); }
static V S1110(void) { static V c; return STRC(c, "if (1)"); }
static V S1111(void) { static V c; return STRC(c, "if (v == IMM("); }
static V S1112(void) { static V c; return STRC(c, "))"); }
static V S1113(void) { static V c; return STRC(c, "if (!(v & 1) && TAG(v) == "); }
static V S1114(void) { static V c; return STRC(c, ")"); }
static V F_Gen_dprinter_dtest(V a0, V a1, V a2) {
top:;
return F_Bool_dpick(a2, S1110(), F_Bool_dpick(F_U32_dis__eq(a0, 1u), F_String_dappend(S1111(), F_String_dappend(F_U32_dshow(a1), S1112())), F_String_dappend(S1113(), F_String_dappend(F_U32_dshow(a1), S1114()))));
}
static V W_Gen_dprinter_dtest(V *a) { (void)a; return F_Gen_dprinter_dtest(a[0], a[1], a[2]); }
static V S1118(void) { static V c; return STRC(c, ""); }
static V S1119(void) { static V c; return STRC(c, "pr_s(\042, \042);\012"); }
static V S1120(void) { static V c; return STRC(c, "("); }
static V S1121(void) { static V c; return STRC(c, "v"); }
static V S1122(void) { static V c; return STRC(c, "v"); }
static V S1123(void) { static V c; return STRC(c, ")"); }
static V S1124(void) { static V c; return STRC(c, ");\012"); }
static V L1117(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(F_Bool_dpick(F_U32_dis__zero(a[2]), S1118(), S1119()), F_String_dappend(a[1], F_String_dappend(S1120(), F_String_dappend(F_Bool_dpick(F_Str_deq(a[0], S1121()), S1122(), F_String_dappend(a[0], F_String_dappend(F_U32_dshow(a[2]), S1123()))), S1124()))))), C2(1, a[3], IMM(0)))));
}
static V L1116(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dfields(a[4], a[3], a[2], a[1], F_U32_dinc(a[0])), mk_clo(L1117, 4, 3, (V[]){a[1], a[5], a[0]}));
}
static V F_Gen_dprinter_dfields(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1115 = a2;
if ((s1115) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1115) == 1) {
return F_Gen_dbind(F_Gen_dprinter(a0, F_Ty_dsubst(FLD(FLD(s1115, 0), 1), a1)), mk_clo(L1116, 6, 5, (V[]){a4, a3, FLD(s1115, 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dfields(V *a) { (void)a; return F_Gen_dprinter_dfields(a[0], a[1], a[2], a[3], a[4]); }
static V F_Ty_dsubst(V a0, V a1) {
top:;
V s1125 = a0;
if (TAG(s1125) == 0) {
return F_Maybe_ddefault(F_Ty_dfind(a1, FLD(s1125, 0)), C1(0, FLD(s1125, 0)));
} else if (TAG(s1125) == 14) {
return C2(14, FLD(s1125, 0), F_Ty_dsubsts(FLD(s1125, 1), a1));
} else if (TAG(s1125) == 5) {
return C2(5, FLD(s1125, 0), F_Ty_dsubsts(FLD(s1125, 1), a1));
} else {
return s1125;
}
}
static V W_Ty_dsubst(V *a) { (void)a; return F_Ty_dsubst(a[0], a[1]); }
static V F_Ty_dsubsts(V a0, V a1) {
top:;
V s1126 = a0;
if ((s1126) == IMM(0)) {
return IMM(0);
} else if (TAG(s1126) == 1) {
return C2(1, F_Ty_dsubst(FLD(s1126, 0), a1), F_Ty_dsubsts(FLD(s1126, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dsubsts(V *a) { (void)a; return F_Ty_dsubsts(a[0], a[1]); }
static V F_Ty_dfind(V a0, V a1) {
top:;
V s1127 = a0;
if ((s1127) == IMM(0)) {
return IMM(0);
} else if (TAG(s1127) == 1) {
return F_Ty_dfind_dif(FLD(FLD(s1127, 0), 1), FLD(s1127, 1), a1, F_String_deq(FLD(FLD(s1127, 0), 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dfind(V *a) { (void)a; return F_Ty_dfind(a[0], a[1]); }
static V F_Ty_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s1128 = a3;
if ((s1128) == IMM(1)) {
return C1(1, a0);
} else if ((s1128) == IMM(0)) {
return F_Ty_dfind(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dfind_dif(V *a) { (void)a; return F_Ty_dfind_dif(a[0], a[1], a[2], a[3]); }
static V F_Maybe_ddefault(V a2, V a3) {
top:;
V s1129 = a2;
if ((s1129) == IMM(0)) {
return a3;
} else if (TAG(s1129) == 1) {
return FLD(s1129, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Maybe_ddefault(V *a) { (void)a; return F_Maybe_ddefault(a[2], a[3]); }
static V S1131(void) { static V c; return STRC(c, "&"); }
static V F_Ty_dtuple(V a0) {
top:;
V s1130 = a0;
if (TAG(s1130) == 14) {
return F_Ty_dtuple_dgo(C2(14, FLD(s1130, 0), FLD(s1130, 1)), FLD(s1130, 1), F_Str_deq(FLD(s1130, 0), S1131()));
} else {
return C2(1, s1130, IMM(0));
}
}
static V W_Ty_dtuple(V *a) { (void)a; return F_Ty_dtuple(a[0]); }
static V F_Ty_dtuple_dgo(V a0, V a1, V a2) {
top:;
V s1132 = a2;
if ((s1132) == IMM(1)) {
return F_Ty_dtuple_dargs(a0, a1);
} else if ((s1132) == IMM(0)) {
return C2(1, a0, IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dtuple_dgo(V *a) { (void)a; return F_Ty_dtuple_dgo(a[0], a[1], a[2]); }
static V F_Ty_dtuple_dargs(V a0, V a1) {
top:;
V s1133 = a1;
if (TAG(s1133) == 1 && TAG(FLD(s1133, 1)) == 1 && (FLD(FLD(s1133, 1), 1)) == IMM(0)) {
return C2(1, FLD(s1133, 0), F_Ty_dtuple(FLD(FLD(s1133, 1), 0)));
} else {
return C2(1, a0, IMM(0));
}
}
static V W_Ty_dtuple_dargs(V *a) { (void)a; return F_Ty_dtuple_dargs(a[0], a[1]); }
static V S1136(void) { static V c; return STRC(c, "("); }
static V S1137(void) { static V c; return STRC(c, ");\012"); }
static V L1135(V *a) {
return F_Gen_dpure(C1(1, F_String_dappend(a[1], F_String_dappend(S1136(), F_String_dappend(a[0], S1137())))));
}
static V S1139(void) { static V c; return STRC(c, "FLD("); }
static V S1140(void) { static V c; return STRC(c, ", 1)"); }
static V S1142(void) { static V c; return STRC(c, "(FLD("); }
static V S1143(void) { static V c; return STRC(c, ", 0));\012pr_s(\042, \042);\012"); }
static V L1141(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(a[1], F_String_dappend(S1142(), F_String_dappend(a[0], S1143())))), C2(1, a[2], IMM(0)))));
}
static V L1138(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dtuple(a[2], a[1], F_String_dappend(S1139(), F_String_dappend(a[0], S1140()))), mk_clo(L1141, 3, 2, (V[]){a[0], a[3]}));
}
static V F_Gen_dprinter_dtuple(V a0, V a1, V a2) {
top:;
V s1134 = a1;
if ((s1134) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1134) == 1 && (FLD(s1134, 1)) == IMM(0)) {
return F_Gen_dbind(F_Gen_dprinter(a0, FLD(s1134, 0)), mk_clo(L1135, 2, 1, (V[]){a2}));
} else if (TAG(s1134) == 1) {
return F_Gen_dbind(F_Gen_dprinter(a0, FLD(s1134, 0)), mk_clo(L1138, 4, 3, (V[]){a2, FLD(s1134, 1), a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dtuple(V *a) { (void)a; return F_Gen_dprinter_dtuple(a[0], a[1], a[2]); }
static V L1144(V *a) {
return F_Gen_dproto_dgo(a[0], a[1]);
}
static V F_Gen_dproto(V a0) {
top:;
return mk_clo(L1144, 2, 1, (V[]){a0});
}
static V W_Gen_dproto(V *a) { (void)a; return F_Gen_dproto(a[0]); }
static V F_Gen_dproto_dgo(V a0, V a1) {
top:;
V v1145 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v1145, 0), C2(2, FLD(v1145, 1), a0), FLD(v1145, 2), FLD(v1145, 3), FLD(v1145, 4), FLD(v1145, 5), FLD(v1145, 6)}));
}
static V W_Gen_dproto_dgo(V *a) { (void)a; return F_Gen_dproto_dgo(a[0], a[1]); }
static V L1146(V *a) {
return F_Gen_dmemo_dadd_dgo(a[1], a[0]);
}
static V F_Gen_dmemo_dadd(V a0) {
top:;
return mk_clo(L1146, 2, 1, (V[]){a0});
}
static V W_Gen_dmemo_dadd(V *a) { (void)a; return F_Gen_dmemo_dadd(a[0]); }
static V F_Gen_dmemo_dadd_dgo(V a0, V a1) {
top:;
V v1147 = a0;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v1147, 0), FLD(v1147, 1), FLD(v1147, 2), FLD(v1147, 3), FLD(v1147, 4), C2(1, a1, FLD(v1147, 5)), FLD(v1147, 6)}));
}
static V W_Gen_dmemo_dadd_dgo(V *a) { (void)a; return F_Gen_dmemo_dadd_dgo(a[0], a[1]); }
static V L1148(V *a) {
return F_Gen_dfresh_dgo(a[0]);
}
static V F_Gen_dfresh(void) {
top:;
return mk_clo(L1148, 1, 0, 0);
}
static V W_Gen_dfresh(V *a) { (void)a; return F_Gen_dfresh(); }
static V F_Gen_dfresh_dgo(V a0) {
top:;
V v1149 = a0;
return C2(0, FLD(v1149, 0), CN(0, 7, (V[]){F_U32_dinc(FLD(v1149, 0)), FLD(v1149, 1), FLD(v1149, 2), FLD(v1149, 3), FLD(v1149, 4), FLD(v1149, 5), FLD(v1149, 6)}));
}
static V W_Gen_dfresh_dgo(V *a) { (void)a; return F_Gen_dfresh_dgo(a[0]); }
static V L1150(V *a) {
return F_Gen_dmemo_dfind_dgo(a[1], a[0]);
}
static V F_Gen_dmemo_dfind(V a0) {
top:;
return mk_clo(L1150, 2, 1, (V[]){a0});
}
static V W_Gen_dmemo_dfind(V *a) { (void)a; return F_Gen_dmemo_dfind(a[0]); }
static V F_Gen_dmemo_dfind_dgo(V a0, V a1) {
top:;
V v1151 = a0;
return C2(0, F_Env_dfind(FLD(v1151, 5), a1), CN(0, 7, (V[]){FLD(v1151, 0), FLD(v1151, 1), FLD(v1151, 2), FLD(v1151, 3), FLD(v1151, 4), FLD(v1151, 5), FLD(v1151, 6)}));
}
static V W_Gen_dmemo_dfind_dgo(V *a) { (void)a; return F_Gen_dmemo_dfind_dgo(a[0], a[1]); }
static V F_Env_dfind(V a0, V a1) {
top:;
V s1152 = a0;
if ((s1152) == IMM(0)) {
return IMM(0);
} else if (TAG(s1152) == 1) {
return F_Env_dfind_dif(FLD(FLD(s1152, 0), 1), FLD(s1152, 1), a1, F_String_deq(FLD(FLD(s1152, 0), 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Env_dfind(V *a) { (void)a; return F_Env_dfind(a[0], a[1]); }
static V F_Env_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s1153 = a3;
if ((s1153) == IMM(1)) {
return C1(1, a0);
} else if ((s1153) == IMM(0)) {
return F_Env_dfind(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Env_dfind_dif(V *a) { (void)a; return F_Env_dfind_dif(a[0], a[1], a[2], a[3]); }
static V S1155(void) { static V c; return STRC(c, "n"); }
static V S1156(void) { static V c; return STRC(c, "\042"); }
static V S1157(void) { static V c; return STRC(c, "\042"); }
static V S1158(void) { static V c; return STRC(c, "("); }
static V S1159(void) { static V c; return STRC(c, " "); }
static V S1160(void) { static V c; return STRC(c, ")"); }
static V S1161(void) { static V c; return STRC(c, "{"); }
static V S1162(void) { static V c; return STRC(c, "}"); }
static V S1163(void) { static V c; return STRC(c, "(\134"); }
static V S1164(void) { static V c; return STRC(c, " "); }
static V S1165(void) { static V c; return STRC(c, ")"); }
static V S1166(void) { static V c; return STRC(c, "(let "); }
static V S1167(void) { static V c; return STRC(c, " "); }
static V S1168(void) { static V c; return STRC(c, " "); }
static V S1169(void) { static V c; return STRC(c, ")"); }
static V S1170(void) { static V c; return STRC(c, "(match ["); }
static V S1171(void) { static V c; return STRC(c, "] "); }
static V S1172(void) { static V c; return STRC(c, ")"); }
static V S1173(void) { static V c; return STRC(c, "(case "); }
static V S1174(void) { static V c; return STRC(c, " => "); }
static V S1175(void) { static V c; return STRC(c, ")"); }
static V S1176(void) { static V c; return STRC(c, "("); }
static V S1177(void) { static V c; return STRC(c, "n+ "); }
static V S1178(void) { static V c; return STRC(c, ")"); }
static V S1179(void) { static V c; return STRC(c, "("); }
static V S1180(void) { static V c; return STRC(c, " "); }
static V S1181(void) { static V c; return STRC(c, " "); }
static V S1182(void) { static V c; return STRC(c, ")"); }
static V S1183(void) { static V c; return STRC(c, "(: "); }
static V S1184(void) { static V c; return STRC(c, " "); }
static V S1185(void) { static V c; return STRC(c, ")"); }
static V S1186(void) { static V c; return STRC(c, "#"); }
static V S1187(void) { static V c; return STRC(c, "(ERR "); }
static V S1188(void) { static V c; return STRC(c, ")"); }
static V F_Expr_dshow(V a0) {
top:;
V s1154 = a0;
if (TAG(s1154) == 0) {
return FLD(s1154, 0);
} else if (TAG(s1154) == 1) {
return F_U32_dshow(FLD(s1154, 0));
} else if (TAG(s1154) == 2) {
return F_String_dappend(F_U32_dshow(FLD(s1154, 0)), S1155());
} else if (TAG(s1154) == 3) {
return FLD(s1154, 0);
} else if (TAG(s1154) == 4) {
return F_String_dappend(S1156(), F_String_dappend(FLD(s1154, 0), S1157()));
} else if (TAG(s1154) == 5) {
return F_String_dappend(S1158(), F_String_dappend(F_Expr_dshow(FLD(s1154, 0)), F_String_dappend(S1159(), F_String_dappend(F_Exprs_dshow(FLD(s1154, 1)), S1160()))));
} else if (TAG(s1154) == 6) {
return F_String_dappend(FLD(s1154, 0), F_String_dappend(S1161(), F_String_dappend(F_Exprs_dshow(FLD(s1154, 1)), S1162())));
} else if (TAG(s1154) == 7) {
return F_String_dappend(S1163(), F_String_dappend(F_Pat_dshow(FLD(s1154, 0)), F_String_dappend(S1164(), F_String_dappend(F_Expr_dshow(FLD(s1154, 1)), S1165()))));
} else if (TAG(s1154) == 8) {
return F_String_dappend(S1166(), F_String_dappend(F_Pat_dshow(FLD(s1154, 0)), F_String_dappend(S1167(), F_String_dappend(F_Expr_dshow(FLD(s1154, 1)), F_String_dappend(S1168(), F_String_dappend(F_Expr_dshow(FLD(s1154, 2)), S1169()))))));
} else if (TAG(s1154) == 9) {
return F_String_dappend(S1170(), F_String_dappend(F_Exprs_dshow(FLD(s1154, 0)), F_String_dappend(S1171(), F_String_dappend(F_Exprs_dshow(FLD(s1154, 1)), S1172()))));
} else if (TAG(s1154) == 10) {
return F_String_dappend(S1173(), F_String_dappend(F_Pats_dshow(FLD(s1154, 0)), F_String_dappend(S1174(), F_String_dappend(F_Expr_dshow(FLD(s1154, 1)), S1175()))));
} else if (TAG(s1154) == 11) {
return F_String_dappend(S1176(), F_String_dappend(F_U32_dshow(FLD(s1154, 0)), F_String_dappend(S1177(), F_String_dappend(F_Expr_dshow(FLD(s1154, 1)), S1178()))));
} else if (TAG(s1154) == 12) {
return F_String_dappend(S1179(), F_String_dappend(FLD(s1154, 0), F_String_dappend(S1180(), F_String_dappend(F_Expr_dshow(FLD(s1154, 1)), F_String_dappend(S1181(), F_String_dappend(F_Expr_dshow(FLD(s1154, 2)), S1182()))))));
} else if (TAG(s1154) == 13) {
return F_String_dappend(S1183(), F_String_dappend(F_Expr_dshow(FLD(s1154, 0)), F_String_dappend(S1184(), F_String_dappend(FLD(s1154, 1), S1185()))));
} else if (TAG(s1154) == 14) {
return F_String_dappend(S1186(), FLD(s1154, 0));
} else if (TAG(s1154) == 15) {
return F_String_dappend(S1187(), F_String_dappend(FLD(s1154, 0), S1188()));
} else { bend_fail("incomplete match"); }
}
static V W_Expr_dshow(V *a) { (void)a; return F_Expr_dshow(a[0]); }
static V S1190(void) { static V c; return STRC(c, ""); }
static V S1191(void) { static V c; return STRC(c, " "); }
static V F_Pats_dshow(V a0) {
top:;
V s1189 = a0;
if ((s1189) == IMM(0)) {
return S1190();
} else if (TAG(s1189) == 1 && (FLD(s1189, 1)) == IMM(0)) {
return F_Pat_dshow(FLD(s1189, 0));
} else if (TAG(s1189) == 1) {
return F_String_dappend(F_Pat_dshow(FLD(s1189, 0)), F_String_dappend(S1191(), F_Pats_dshow(FLD(s1189, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Pats_dshow(V *a) { (void)a; return F_Pats_dshow(a[0]); }
static V S1193(void) { static V c; return STRC(c, "{"); }
static V S1194(void) { static V c; return STRC(c, "}"); }
static V S1195(void) { static V c; return STRC(c, "n"); }
static V S1196(void) { static V c; return STRC(c, "n+"); }
static V F_Pat_dshow(V a0) {
top:;
V s1192 = a0;
if (TAG(s1192) == 0) {
return FLD(s1192, 0);
} else if (TAG(s1192) == 1) {
return F_String_dappend(FLD(s1192, 0), F_String_dappend(S1193(), F_String_dappend(F_Pats_dshow(FLD(s1192, 1)), S1194())));
} else if (TAG(s1192) == 2) {
return F_String_dappend(F_U32_dshow(FLD(s1192, 0)), S1195());
} else if (TAG(s1192) == 3) {
return F_String_dappend(F_U32_dshow(FLD(s1192, 0)), F_String_dappend(S1196(), F_Pat_dshow(FLD(s1192, 1))));
} else if (TAG(s1192) == 4) {
return F_U32_dshow(FLD(s1192, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Pat_dshow(V *a) { (void)a; return F_Pat_dshow(a[0]); }
static V S1198(void) { static V c; return STRC(c, ""); }
static V S1199(void) { static V c; return STRC(c, " "); }
static V F_Exprs_dshow(V a0) {
top:;
V s1197 = a0;
if ((s1197) == IMM(0)) {
return S1198();
} else if (TAG(s1197) == 1 && (FLD(s1197, 1)) == IMM(0)) {
return F_Expr_dshow(FLD(s1197, 0));
} else if (TAG(s1197) == 1) {
return F_String_dappend(F_Expr_dshow(FLD(s1197, 0)), F_String_dappend(S1199(), F_Exprs_dshow(FLD(s1197, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Exprs_dshow(V *a) { (void)a; return F_Exprs_dshow(a[0]); }
static V F_Set_dnew(void) {
top:;
return F_Map_dnew();
}
static V W_Set_dnew(V *a) { (void)a; return F_Set_dnew(); }
static V F_Map_dnew(void) {
top:;
return IMM(0);
}
static V W_Map_dnew(V *a) { (void)a; return F_Map_dnew(); }
static V F_Gen_dall(V a0, V a1, V a2) {
top:;
V s1200 = a1;
if ((s1200) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1200) == 1) {
return F_Gen_dall_dseen(a0, FLD(s1200, 0), FLD(s1200, 1), F_Set_dhas(a2, FLD(s1200, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dall(V *a) { (void)a; return F_Gen_dall(a[0], a[1], a[2]); }
static V F_Set_dhas(V a0, V a1) {
top:;
return F_Map_dhas(a0, a1);
}
static V W_Set_dhas(V *a) { (void)a; return F_Set_dhas(a[0], a[1]); }
static V F_Map_dhas(V a2, V a3) {
top:;
V s1201 = a2;
if ((s1201) == IMM(0)) {
return C2(0, IMM(0), IMM(0));
} else if (TAG(s1201) == 1) {
return F_Map_dhas_dleaf(FLD(s1201, 1), F_String_dcmp(a3, FLD(s1201, 0)));
} else if (TAG(s1201) == 2) {
return F_Map_dhas_dbit(FLD(s1201, 1), FLD(s1201, 2), FLD(s1201, 0), F_Map_dbit(a3, FLD(s1201, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dhas(V *a) { (void)a; return F_Map_dhas(a[2], a[3]); }
static V F_Map_dhas_dbit(V a2, V a3, V a4, V a5) {
top:;
V v1202 = a5;
V s1203 = FLD(v1202, 1);
if ((s1203) == IMM(0)) {
return F_Map_dlo(a4, a3, F_Map_dhas(a2, FLD(v1202, 0)));
} else if ((s1203) == IMM(1)) {
return F_Map_dhi(a4, a2, F_Map_dhas(a3, FLD(v1202, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dhas_dbit(V *a) { (void)a; return F_Map_dhas_dbit(a[2], a[3], a[4], a[5]); }
static V F_Map_dhas_dleaf(V a2, V a3) {
top:;
V v1204 = a3;
return C2(0, C2(1, FLD(FLD(v1204, 0), 1), a2), F_Cmp_dis__eq(FLD(v1204, 1)));
}
static V W_Map_dhas_dleaf(V *a) { (void)a; return F_Map_dhas_dleaf(a[2], a[3]); }
static V F_Gen_dall_dseen(V a0, V a1, V a2, V a3) {
top:;
V v1205 = a3;
return F_Gen_dall_dgo(a0, a1, a2, FLD(v1205, 0), FLD(v1205, 1));
}
static V W_Gen_dall_dseen(V *a) { (void)a; return F_Gen_dall_dseen(a[0], a[1], a[2], a[3]); }
static V L1208(V *a) {
return F_Gen_dall(a[3], F_List_dappend(a[4], a[2]), F_Set_dadd(a[1], a[0]));
}
static V L1207(V *a) {
return F_Gen_dbind(F_Gen_dtake__refs(), mk_clo(L1208, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Gen_dall_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1206 = a4;
if ((s1206) == IMM(1)) {
return F_Gen_dall(a0, a2, a3);
} else if ((s1206) == IMM(0)) {
return F_Gen_dbind(F_Gen_ddef(a0, a1), mk_clo(L1207, 5, 4, (V[]){a1, a3, a2, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dall_dgo(V *a) { (void)a; return F_Gen_dall_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V F_Set_dadd(V a0, V a1) {
top:;
return F_Map_dset(a0, a1, IMM(0));
}
static V W_Set_dadd(V *a) { (void)a; return F_Set_dadd(a[0], a[1]); }
static V F_Map_dset(V a2, V a3, V a4) {
top:;
return F_Map_dset_dgo(a4, F_Map_dseek(a2, a3));
}
static V W_Map_dset(V *a) { (void)a; return F_Map_dset(a[2], a[3], a[4]); }
static V F_Map_dseek(V a2, V a3) {
top:;
V s1209 = a2;
if ((s1209) == IMM(0)) {
return C2(0, IMM(0), C2(0, a3, IMM(0)));
} else if (TAG(s1209) == 1) {
return C2(0, C2(1, FLD(s1209, 0), FLD(s1209, 1)), C2(0, a3, C1(1, FLD(s1209, 0))));
} else if (TAG(s1209) == 2) {
return F_Map_dseek_dbit(FLD(s1209, 1), FLD(s1209, 2), FLD(s1209, 0), F_Map_dbit(a3, FLD(s1209, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dseek(V *a) { (void)a; return F_Map_dseek(a[2], a[3]); }
static V F_Map_dseek_dbit(V a2, V a3, V a4, V a5) {
top:;
V v1210 = a5;
V s1211 = FLD(v1210, 1);
if ((s1211) == IMM(0)) {
return F_Map_dlo(a4, a3, F_Map_dseek(a2, FLD(v1210, 0)));
} else if ((s1211) == IMM(1)) {
return F_Map_dhi(a4, a2, F_Map_dseek(a3, FLD(v1210, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dseek_dbit(V *a) { (void)a; return F_Map_dseek_dbit(a[2], a[3], a[4], a[5]); }
static V F_Map_dset_dgo(V a2, V a3) {
top:;
V v1212 = a3;
V s1213 = FLD(FLD(v1212, 1), 1);
if ((s1213) == IMM(0)) {
return C2(1, FLD(FLD(v1212, 1), 0), a2);
} else if (TAG(s1213) == 1) {
V v1214 = FLD(FLD(v1212, 1), 0);
return F_Map_dset_dfin(FLD(v1212, 0), v1214, a2, v1214, FLD(s1213, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dset_dgo(V *a) { (void)a; return F_Map_dset_dgo(a[2], a[3]); }
static V F_Map_dset_dfin(V a2, V a3, V a4, V a5, V a6) {
top:;
return F_Map_dset_dfin_dgo(a2, a3, a4, F_String_dcmp(a5, a6));
}
static V W_Map_dset_dfin(V *a) { (void)a; return F_Map_dset_dfin(a[2], a[3], a[4], a[5], a[6]); }
static V F_Map_dset_dfin_dgo(V a2, V a3, V a4, V a5) {
top:;
V v1215 = a5;
V s1216 = FLD(v1215, 1);
if ((s1216) == IMM(0)) {
return F_Map_dins(a2, a3, a4, F_Map_ddiff(FLD(FLD(v1215, 0), 0), FLD(FLD(v1215, 0), 1)));
} else if ((s1216) == IMM(1)) {
return F_Map_dput(a2, a3, a4);
} else if ((s1216) == IMM(2)) {
return F_Map_dins(a2, a3, a4, F_Map_ddiff(FLD(FLD(v1215, 0), 0), FLD(FLD(v1215, 0), 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dset_dfin_dgo(V *a) { (void)a; return F_Map_dset_dfin_dgo(a[2], a[3], a[4], a[5]); }
static V F_Map_ddiff(V a0, V a1) {
top:;
V s1217 = a0;
V s1218 = a1;
if ((s1217) == IMM(0) && (s1218) == IMM(0)) {
return 0u;
} else if ((s1217) == IMM(0) && TAG(s1218) == 1) {
return 0u;
} else if (TAG(s1217) == 1 && (s1218) == IMM(0)) {
return 0u;
} else if (TAG(s1217) == 1 && TAG(s1218) == 1) {
return F_Map_ddiff_dfin(FLD(s1217, 1), FLD(s1218, 1), F_Map_ddiff_dstep(FLD(s1217, 0), FLD(s1218, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_ddiff(V *a) { (void)a; return F_Map_ddiff(a[0], a[1]); }
static V F_Map_ddiff_dstep(V a0, V a1) {
top:;
V s1219 = a0;
V s1220 = a1;
{
return C2(0, F_Map_ddiff_dchr(F_U32_dxor(s1219, s1220)), F_U32_dis__eq(s1219, s1220));
}
}
static V W_Map_ddiff_dstep(V *a) { (void)a; return F_Map_ddiff_dstep(a[0], a[1]); }
static V W_U32_dxor(V *a) { (void)a; return F_U32_dxor(a[0], a[1]); }
static V F_Map_ddiff_dchr(V a0) {
top:;
return F_Nat_dsub(33u, F_Map_dmsb_du(32u, a0));
}
static V W_Map_ddiff_dchr(V *a) { (void)a; return F_Map_ddiff_dchr(a[0]); }
static V F_Map_dmsb_du(V a0, V a1) {
top:;
V s1221 = a0;
if ((s1221) == 0) {
return 0u;
} else if (nat_ge(s1221, 1)) {
return F_Map_dmsb_du_dif(nat_subk(s1221, 1), a1, F_U32_dis__zero(a1));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dmsb_du(V *a) { (void)a; return F_Map_dmsb_du(a[0], a[1]); }
static V F_Map_dmsb_du_dif(V a0, V a1, V a2) {
top:;
V s1222 = a2;
if ((s1222) == IMM(1)) {
return 0u;
} else if ((s1222) == IMM(0)) {
return F_Nat_dadd(1u, F_Map_dmsb_du(a0, F_U32_dshr(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dmsb_du_dif(V *a) { (void)a; return F_Map_dmsb_du_dif(a[0], a[1], a[2]); }
static V W_U32_dshr(V *a) { (void)a; return F_U32_dshr(a[0]); }
static V F_Map_ddiff_dfin(V a0, V a1, V a2) {
top:;
V v1223 = a2;
V s1224 = FLD(v1223, 1);
if ((s1224) == IMM(1)) {
return F_Nat_dadd(33u, F_Map_ddiff(a0, a1));
} else if ((s1224) == IMM(0)) {
return FLD(v1223, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Map_ddiff_dfin(V *a) { (void)a; return F_Map_ddiff_dfin(a[0], a[1], a[2]); }
static V F_Map_dins(V a2, V a3, V a4, V a5) {
top:;
V s1225 = a2;
if ((s1225) == IMM(0)) {
return C2(1, a3, a4);
} else if (TAG(s1225) == 1) {
return F_Map_dins_dsplice(a5, a3, a4, C2(1, FLD(s1225, 0), FLD(s1225, 1)));
} else if (TAG(s1225) == 2) {
return F_Map_dins_dif(a3, a4, FLD(s1225, 1), FLD(s1225, 2), FLD(s1225, 0), a5, F_Nat_dis__lt(FLD(s1225, 0), a5));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dins(V *a) { (void)a; return F_Map_dins(a[2], a[3], a[4], a[5]); }
static V F_Map_dins_dif(V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s1226 = a8;
if ((s1226) == IMM(0)) {
return F_Map_dins_dsplice(a7, a2, a3, C3(2, a6, a4, a5));
} else if ((s1226) == IMM(1)) {
return F_Map_dins_ddeep(a3, a4, a5, a7, a6, F_Map_dbit(a2, a6));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dins_dif(V *a) { (void)a; return F_Map_dins_dif(a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Map_dins_ddeep(V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V v1227 = a7;
V s1228 = FLD(v1227, 1);
if ((s1228) == IMM(0)) {
return C3(2, a6, F_Map_dins(a3, FLD(v1227, 0), a2, a5), a4);
} else if ((s1228) == IMM(1)) {
return C3(2, a6, a3, F_Map_dins(a4, FLD(v1227, 0), a2, a5));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dins_ddeep(V *a) { (void)a; return F_Map_dins_ddeep(a[2], a[3], a[4], a[5], a[6], a[7]); }
static V F_Map_dins_dsplice(V a2, V a3, V a4, V a5) {
top:;
return F_Map_dins_dsplice_dbit(a4, a5, a2, F_Map_dbit(a3, a2));
}
static V W_Map_dins_dsplice(V *a) { (void)a; return F_Map_dins_dsplice(a[2], a[3], a[4], a[5]); }
static V F_Map_dins_dsplice_dbit(V a2, V a3, V a4, V a5) {
top:;
V v1229 = a5;
V s1230 = FLD(v1229, 1);
if ((s1230) == IMM(0)) {
return C3(2, a4, C2(1, FLD(v1229, 0), a2), a3);
} else if ((s1230) == IMM(1)) {
return C3(2, a4, a3, C2(1, FLD(v1229, 0), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dins_dsplice_dbit(V *a) { (void)a; return F_Map_dins_dsplice_dbit(a[2], a[3], a[4], a[5]); }
static V F_Map_dput(V a2, V a3, V a4) {
top:;
V s1231 = a2;
if ((s1231) == IMM(0)) {
return C2(1, a3, a4);
} else if (TAG(s1231) == 1) {
return C2(1, FLD(s1231, 0), a4);
} else if (TAG(s1231) == 2) {
return F_Map_dput_dbit(a4, FLD(s1231, 0), FLD(s1231, 1), FLD(s1231, 2), F_Map_dbit(a3, FLD(s1231, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dput(V *a) { (void)a; return F_Map_dput(a[2], a[3], a[4]); }
static V F_Map_dput_dbit(V a2, V a3, V a4, V a5, V a6) {
top:;
V v1232 = a6;
V s1233 = FLD(v1232, 1);
if ((s1233) == IMM(0)) {
return C3(2, a3, F_Map_dput(a4, FLD(v1232, 0), a2), a5);
} else if ((s1233) == IMM(1)) {
return C3(2, a3, a4, F_Map_dput(a5, FLD(v1232, 0), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dput_dbit(V *a) { (void)a; return F_Map_dput_dbit(a[2], a[3], a[4], a[5], a[6]); }
static V L1234(V *a) {
return F_Gen_dtake__refs_dgo(a[0]);
}
static V F_Gen_dtake__refs(void) {
top:;
return mk_clo(L1234, 1, 0, 0);
}
static V W_Gen_dtake__refs(V *a) { (void)a; return F_Gen_dtake__refs(); }
static V F_Gen_dtake__refs_dgo(V a0) {
top:;
V v1235 = a0;
return C2(0, FLD(v1235, 3), CN(0, 7, (V[]){FLD(v1235, 0), FLD(v1235, 1), FLD(v1235, 2), IMM(0), FLD(v1235, 4), FLD(v1235, 5), FLD(v1235, 6)}));
}
static V W_Gen_dtake__refs_dgo(V *a) { (void)a; return F_Gen_dtake__refs_dgo(a[0]); }
static V F_Gen_ddef(V a0, V a1) {
top:;
return F_Gen_ddef_ddecl(a0, a1, F_G_ddef(a0, a1), F_G_dbody(a0, a1));
}
static V W_Gen_ddef(V *a) { (void)a; return F_Gen_ddef(a[0], a[1]); }
static V F_G_ddef(V a0, V a1) {
top:;
V v1236 = a0;
return F_G_dget(C2(0, 99u, IMM(0)), FLD(v1236, 1), a1);
}
static V W_G_ddef(V *a) { (void)a; return F_G_ddef(a[0], a[1]); }
static V F_Gen_ddef_ddecl(V a0, V a1, V a2, V a3) {
top:;
V v1237 = a2;
V s1238 = a3;
if (TAG(s1238) == 0) {
return F_Gen_ddef_dnative(a0, a1, FLD(v1237, 1), FLD(s1238, 2), F_Gen_dsig(FLD(s1238, 1), FLD(v1237, 1), 0u, C3(0, IMM(0), IMM(0), IMM(0))), F_U32_dis__eq(FLD(v1237, 0), 2u));
} else if (TAG(s1238) == 1) {
return F_Gen_ddef_deff(a1, F_Gen_dsig(FLD(s1238, 1), FLD(v1237, 1), 0u, C3(0, IMM(0), IMM(0), IMM(0))), FLD(s1238, 2));
} else {
return F_Gen_ddef_dlaw(a1, FLD(v1237, 1), F_U32_dis__eq(FLD(v1237, 0), 2u));
}
}
static V W_Gen_ddef_ddecl(V *a) { (void)a; return F_Gen_ddef_ddecl(a[0], a[1], a[2], a[3]); }
static V F_Gen_ddef_dlaw(V a0, V a1, V a2) {
top:;
V s1239 = a2;
if ((s1239) == IMM(1)) {
return F_Gen_dwrapper(a0, F_Sig_dwargs(F_Gen_dsig(F_Gen_ddummy__params(a1), a1, 0u, C3(0, IMM(0), IMM(0), IMM(0)))));
} else if ((s1239) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_ddef_dlaw(V *a) { (void)a; return F_Gen_ddef_dlaw(a[0], a[1], a[2]); }
static V S1241(void) { static V c; return STRC(c, "_"); }
static V S1242(void) { static V c; return STRC(c, ""); }
static V F_Gen_ddummy__params(V a0) {
top:;
V s1240 = a0;
if ((s1240) == IMM(0)) {
return IMM(0);
} else if (TAG(s1240) == 1) {
return C2(1, C3(0, S1241(), 0u, S1242()), F_Gen_ddummy__params(FLD(s1240, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_ddummy__params(V *a) { (void)a; return F_Gen_ddummy__params(a[0]); }
static V S1247(void) { static V c; return STRC(c, "a"); }
static V S1248(void) { static V c; return STRC(c, "a["); }
static V S1249(void) { static V c; return STRC(c, "]"); }
static V S1251(void) { static V c; return STRC(c, "0"); }
static V F_Gen_dsig(V a0, V a1, V a2, V a3) {
top:;
V s1243 = a0;
V s1244 = a1;
if (TAG(s1243) == 1 && TAG(s1244) == 1 && (FLD(s1244, 0)) == IMM(1)) {
V v1245 = a3;
V v1246 = F_String_dappend(S1247(), F_U32_dshow(a2));
{ V t0 = FLD(s1243, 1); V t1 = FLD(s1244, 1); V t2 = F_U32_dinc(a2); V t3 = C3(0, F_List_dappend(FLD(v1245, 0), C2(1, v1246, IMM(0))), C2(1, C2(0, FLD(FLD(s1243, 0), 0), v1246), FLD(v1245, 1)), F_List_dappend(FLD(v1245, 2), C2(1, F_String_dappend(S1248(), F_String_dappend(F_U32_dshow(a2), S1249())), IMM(0)))); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1243) == 1 && TAG(s1244) == 1 && (FLD(s1244, 0)) == IMM(0)) {
V v1250 = a3;
{ V t0 = FLD(s1243, 1); V t1 = FLD(s1244, 1); V t2 = F_U32_dinc(a2); V t3 = C3(0, FLD(v1250, 0), C2(1, C2(0, FLD(FLD(s1243, 0), 0), S1251()), FLD(v1250, 1)), FLD(v1250, 2)); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else {
return a3;
}
}
static V W_Gen_dsig(V *a) { (void)a; return F_Gen_dsig(a[0], a[1], a[2], a[3]); }
static V F_Sig_dwargs(V a0) {
top:;
V v1252 = a0;
return FLD(v1252, 2);
}
static V W_Sig_dwargs(V *a) { (void)a; return F_Sig_dwargs(a[0]); }
static V S1254(void) { static V c; return STRC(c, "static V "); }
static V S1255(void) { static V c; return STRC(c, "(V *a);\012"); }
static V S1257(void) { static V c; return STRC(c, "static V "); }
static V S1258(void) { static V c; return STRC(c, "(V *a) { (void)a; return "); }
static V S1259(void) { static V c; return STRC(c, "("); }
static V S1260(void) { static V c; return STRC(c, ", "); }
static V S1261(void) { static V c; return STRC(c, "); }\012"); }
static V L1256(V *a) {
return F_Gen_dcode(C1(1, F_String_dappend(S1257(), F_String_dappend(a[2], F_String_dappend(S1258(), F_String_dappend(F_Gen_df(a[1]), F_String_dappend(S1259(), F_String_dappend(F_String_djoin(a[0], S1260()), S1261()))))))));
}
static V F_Gen_dwrapper(V a0, V a1) {
top:;
V v1253 = F_Gen_dw(a0);
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S1254(), F_String_dappend(v1253, S1255())))), mk_clo(L1256, 4, 3, (V[]){a1, a0, v1253}));
}
static V W_Gen_dwrapper(V *a) { (void)a; return F_Gen_dwrapper(a[0], a[1]); }
static V S1262(void) { static V c; return STRC(c, "F_"); }
static V F_Gen_df(V a0) {
top:;
return F_String_dappend(S1262(), F_Gen_dmangle(a0));
}
static V W_Gen_df(V *a) { (void)a; return F_Gen_df(a[0]); }
static V S1264(void) { static V c; return STRC(c, ""); }
static V F_Gen_dmangle(V a0) {
top:;
V s1263 = a0;
if ((s1263) == IMM(0)) {
return S1264();
} else if (TAG(s1263) == 1) {
return F_String_dappend(F_Gen_dmangle_dchr(FLD(s1263, 0)), F_Gen_dmangle(FLD(s1263, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dmangle(V *a) { (void)a; return F_Gen_dmangle(a[0]); }
static V S1265(void) { static V c; return STRC(c, "_d"); }
static V S1266(void) { static V c; return STRC(c, "__"); }
static V S1267(void) { static V c; return STRC(c, "_x"); }
static V F_Gen_dmangle_dchr(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__eq(a0, 46u), S1265(), F_Bool_dpick(F_U32_dis__eq(a0, 95u), S1266(), F_Bool_dpick(F_Bool_dor(F_Char_dis__alpha(a0), F_Char_dis__digit(a0)), F_Str_dchr(a0), F_String_dappend(S1267(), F_U32_dshow(a0)))));
}
static V W_Gen_dmangle_dchr(V *a) { (void)a; return F_Gen_dmangle_dchr(a[0]); }
static V F_Str_dchr(V a0) {
top:;
return C2(1, a0, IMM(0));
}
static V W_Str_dchr(V *a) { (void)a; return F_Str_dchr(a[0]); }
static V S1268(void) { static V c; return STRC(c, "W_"); }
static V F_Gen_dw(V a0) {
top:;
return F_String_dappend(S1268(), F_Gen_dmangle(a0));
}
static V W_Gen_dw(V *a) { (void)a; return F_Gen_dw(a[0]); }
static V S1272(void) { static V c; return STRC(c, "E_"); }
static V S1274(void) { static V c; return STRC(c, "static V "); }
static V S1275(void) { static V c; return STRC(c, "("); }
static V S1276(void) { static V c; return STRC(c, ")"); }
static V S1278(void) { static V c; return STRC(c, ";\012static V "); }
static V S1279(void) { static V c; return STRC(c, "(V *a);\012"); }
static V S1281(void) { static V c; return STRC(c, "static V "); }
static V S1282(void) { static V c; return STRC(c, "(V *a) { return io_req("); }
static V S1283(void) { static V c; return STRC(c, ", "); }
static V S1284(void) { static V c; return STRC(c, ", (V[]){"); }
static V S1285(void) { static V c; return STRC(c, "a["); }
static V S1286(void) { static V c; return STRC(c, "]"); }
static V S1287(void) { static V c; return STRC(c, ", "); }
static V S1288(void) { static V c; return STRC(c, "}); }\012"); }
static V S1290(void) { static V c; return STRC(c, " { return mk_clo("); }
static V S1291(void) { static V c; return STRC(c, ", "); }
static V S1292(void) { static V c; return STRC(c, ", "); }
static V S1293(void) { static V c; return STRC(c, ", "); }
static V S1294(void) { static V c; return STRC(c, "0"); }
static V S1295(void) { static V c; return STRC(c, "(V[]){"); }
static V S1296(void) { static V c; return STRC(c, ", "); }
static V S1297(void) { static V c; return STRC(c, "}"); }
static V S1298(void) { static V c; return STRC(c, "); }\012"); }
static V L1299(V *a) {
return F_Gen_dwrapper(a[1], a[0]);
}
static V L1289(V *a) {
return F_Gen_dbind(F_Gen_dcode(C1(1, F_String_dappend(a[5], F_String_dappend(S1290(), F_String_dappend(a[4], F_String_dappend(S1291(), F_String_dappend(F_U32_dshow(F_U32_dadd(a[3], 2u)), F_String_dappend(S1292(), F_String_dappend(F_U32_dshow(a[3]), F_String_dappend(S1293(), F_String_dappend(F_Bool_dpick(F_U32_dis__zero(a[3]), S1294(), F_String_dappend(S1295(), F_String_dappend(F_String_djoin(a[2], S1296()), S1297()))), S1298()))))))))))), mk_clo(L1299, 3, 2, (V[]){a[0], a[1]}));
}
static V L1280(V *a) {
return F_Gen_dbind(F_Gen_dcode(C1(1, F_String_dappend(S1281(), F_String_dappend(a[5], F_String_dappend(S1282(), F_String_dappend(F_Gen_dcid(a[4]), F_String_dappend(S1283(), F_String_dappend(F_U32_dshow(F_U32_dinc(a[3])), F_String_dappend(S1284(), F_String_dappend(F_String_djoin(F_List_dappend(F_Gen_deff_dargs(F_U32_dto__nat(a[3]), 0u), C2(1, F_String_dappend(S1285(), F_String_dappend(F_U32_dshow(F_U32_dinc(a[3])), S1286())), IMM(0))), S1287()), S1288())))))))))), mk_clo(L1289, 7, 6, (V[]){a[0], a[4], a[1], a[3], a[5], a[2]}));
}
static V L1277(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(a[5], F_String_dappend(S1278(), F_String_dappend(a[4], S1279()))))), mk_clo(L1280, 7, 6, (V[]){a[0], a[1], a[5], a[2], a[3], a[4]}));
}
static V F_Gen_ddef_deff(V a0, V a1, V a2) {
top:;
V v1269 = a1;
V v1270 = F_U32_dfrom__nat(F_List_dlength(FLD(v1269, 0)));
V v1271 = F_String_dappend(S1272(), F_Gen_dmangle(a0));
V v1273 = F_String_dappend(S1274(), F_String_dappend(F_Gen_df(a0), F_String_dappend(S1275(), F_String_dappend(F_Gen_dcparams(FLD(v1269, 0)), S1276()))));
return F_Gen_dbind(F_Gen_deffs(a2), mk_clo(L1277, 7, 6, (V[]){FLD(v1269, 2), FLD(v1269, 0), v1270, a0, v1271, v1273}));
}
static V W_Gen_ddef_deff(V *a) { (void)a; return F_Gen_ddef_deff(a[0], a[1], a[2]); }
static V S1301(void) { static V c; return STRC(c, "a["); }
static V S1302(void) { static V c; return STRC(c, "]"); }
static V F_Gen_deff_dargs(V a0, V a1) {
top:;
V s1300 = a0;
if ((s1300) == 0) {
return IMM(0);
} else if (nat_ge(s1300, 1)) {
return C2(1, F_String_dappend(S1301(), F_String_dappend(F_U32_dshow(a1), S1302())), F_Gen_deff_dargs(nat_subk(s1300, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_deff_dargs(V *a) { (void)a; return F_Gen_deff_dargs(a[0], a[1]); }
static V S1303(void) { static V c; return STRC(c, "CID_"); }
static V F_Gen_dcid(V a0) {
top:;
return F_String_dappend(S1303(), F_Gen_dhost(F_String_dto__upper(a0)));
}
static V W_Gen_dcid(V *a) { (void)a; return F_Gen_dcid(a[0]); }
static V F_String_dto__upper(V a0) {
top:;
V s1304 = a0;
if ((s1304) == IMM(0)) {
return IMM(0);
} else if (TAG(s1304) == 1) {
return C2(1, F_Char_dto__upper(FLD(s1304, 0)), F_String_dto__upper(FLD(s1304, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_String_dto__upper(V *a) { (void)a; return F_String_dto__upper(a[0]); }
static V F_Char_dto__upper(V a0) {
top:;
return F_U32_dsub(F_Char_dto__u32(a0), F_U32_dmul(F_Bool_dto__u32(F_Char_dis__lower(a0)), 32u));
}
static V W_Char_dto__upper(V *a) { (void)a; return F_Char_dto__upper(a[0]); }
static V F_Bool_dto__u32(V a0) {
top:;
V s1305 = a0;
if ((s1305) == IMM(0)) {
return 0u;
} else if ((s1305) == IMM(1)) {
return 1u;
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dto__u32(V *a) { (void)a; return F_Bool_dto__u32(a[0]); }
static V S1307(void) { static V c; return STRC(c, ""); }
static V F_Gen_dhost(V a0) {
top:;
V s1306 = a0;
if ((s1306) == IMM(0)) {
return S1307();
} else if (TAG(s1306) == 1) {
return F_String_dappend(F_Gen_dhost_dchr(FLD(s1306, 0)), F_Gen_dhost(FLD(s1306, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dhost(V *a) { (void)a; return F_Gen_dhost(a[0]); }
static V S1308(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dhost_dchr(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__eq(a0, 46u), S1308(), F_Str_dchr(a0));
}
static V W_Gen_dhost_dchr(V *a) { (void)a; return F_Gen_dhost_dchr(a[0]); }
static V L1309(V *a) {
return F_Gen_deffs_dgo(a[0], a[1]);
}
static V F_Gen_deffs(V a0) {
top:;
return mk_clo(L1309, 2, 1, (V[]){a0});
}
static V W_Gen_deffs(V *a) { (void)a; return F_Gen_deffs(a[0]); }
static V F_Gen_deffs_dgo(V a0, V a1) {
top:;
V v1310 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v1310, 0), FLD(v1310, 1), FLD(v1310, 2), FLD(v1310, 3), FLD(v1310, 4), FLD(v1310, 5), F_List_dappend(F_Gen_deffs_dc(a0), FLD(v1310, 6))}));
}
static V W_Gen_deffs_dgo(V *a) { (void)a; return F_Gen_deffs_dgo(a[0], a[1]); }
static V S1312(void) { static V c; return STRC(c, ".c"); }
static V F_Gen_deffs_dc(V a0) {
top:;
V s1311 = a0;
if ((s1311) == IMM(0)) {
return IMM(0);
} else if (TAG(s1311) == 1) {
return F_Gen_deffs_dc_dif(FLD(s1311, 0), F_Gen_deffs_dc(FLD(s1311, 1)), F_String_dends__with(FLD(s1311, 0), S1312()));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_deffs_dc(V *a) { (void)a; return F_Gen_deffs_dc(a[0]); }
static V F_String_dends__with(V a0, V a1) {
top:;
return F_String_dstarts__with(F_String_dreverse(a0), F_String_dreverse(a1));
}
static V W_String_dends__with(V *a) { (void)a; return F_String_dends__with(a[0], a[1]); }
static V F_Gen_deffs_dc_dif(V a0, V a1, V a2) {
top:;
V s1313 = a2;
if ((s1313) == IMM(1)) {
return C2(1, a0, a1);
} else if ((s1313) == IMM(0)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Gen_deffs_dc_dif(V *a) { (void)a; return F_Gen_deffs_dc_dif(a[0], a[1], a[2]); }
static V S1315(void) { static V c; return STRC(c, "void"); }
static V S1316(void) { static V c; return STRC(c, ", "); }
static V F_Gen_dcparams(V a0) {
top:;
V s1314 = a0;
if ((s1314) == IMM(0)) {
return S1315();
} else if (TAG(s1314) == 1) {
return F_String_djoin(F_Gen_dcparams_dgo(C2(1, FLD(s1314, 0), FLD(s1314, 1))), S1316());
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcparams(V *a) { (void)a; return F_Gen_dcparams(a[0]); }
static V S1318(void) { static V c; return STRC(c, "V "); }
static V F_Gen_dcparams_dgo(V a0) {
top:;
V s1317 = a0;
if ((s1317) == IMM(0)) {
return IMM(0);
} else if (TAG(s1317) == 1) {
return C2(1, F_String_dappend(S1318(), FLD(s1317, 0)), F_Gen_dcparams_dgo(FLD(s1317, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcparams_dgo(V *a) { (void)a; return F_Gen_dcparams_dgo(a[0]); }
static V F_Gen_ddef_dnative(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1319 = a5;
if ((s1319) == IMM(1)) {
return F_Gen_dwrapper(a1, F_Sig_dwargs(a4));
} else if ((s1319) == IMM(0)) {
return F_Gen_ddef_dbody(a0, a1, a2, a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_ddef_dnative(V *a) { (void)a; return F_Gen_ddef_dnative(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1322(void) { static V c; return STRC(c, "static V "); }
static V S1323(void) { static V c; return STRC(c, "("); }
static V S1324(void) { static V c; return STRC(c, ")"); }
static V S1325(void) { static V c; return STRC(c, ";\012"); }
static V S1327(void) { static V c; return STRC(c, "Nat"); }
static V S1329(void) { static V c; return STRC(c, " {\012top:;\012"); }
static V S1330(void) { static V c; return STRC(c, "}\012"); }
static V L1331(V *a) {
return F_Gen_dwrapper(a[1], a[0]);
}
static V L1328(V *a) {
return F_Gen_dbind(F_Gen_dcode(F_Doc_dlist(C2(1, C1(1, F_String_dappend(a[2], S1329())), C2(1, a[3], C2(1, C1(1, S1330()), IMM(0)))))), mk_clo(L1331, 3, 2, (V[]){a[0], a[1]}));
}
static V L1326(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[7], a[6], C3(0, a[5], a[4], a[3]), IMM(0), F_R_dops(a[2], S1327())), mk_clo(L1328, 4, 3, (V[]){a[0], a[5], a[1]}));
}
static V F_Gen_ddef_dbody(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1320 = a4;
V v1321 = F_String_dappend(S1322(), F_String_dappend(F_Gen_df(a1), F_String_dappend(S1323(), F_String_dappend(F_Gen_dcparams(FLD(v1320, 0)), S1324()))));
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(v1321, S1325()))), mk_clo(L1326, 9, 8, (V[]){FLD(v1320, 2), v1321, a3, FLD(v1320, 0), a2, a1, FLD(v1320, 1), a0}));
}
static V W_Gen_ddef_dbody(V *a) { (void)a; return F_Gen_ddef_dbody(a[0], a[1], a[2], a[3], a[4]); }
static V S1333(void) { static V c; return STRC(c, "."); }
static V F_R_dops(V a0, V a1) {
top:;
V s1332 = a0;
if (TAG(s1332) == 12) {
return C2(5, C1(0, F_String_dappend(a1, F_String_dappend(S1333(), F_R_dopname(FLD(s1332, 0))))), C2(1, F_R_dops(FLD(s1332, 1), a1), C2(1, F_R_dops(FLD(s1332, 2), a1), IMM(0))));
} else if (TAG(s1332) == 13) {
{ V t0 = FLD(s1332, 0); V t1 = F_Bool_dpick(F_String_dis__empty(FLD(s1332, 1)), a1, FLD(s1332, 1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1332) == 5) {
return C2(5, F_R_dops(FLD(s1332, 0), a1), F_R_dopss(FLD(s1332, 1), a1));
} else if (TAG(s1332) == 6) {
return C2(6, FLD(s1332, 0), F_R_dopss(FLD(s1332, 1), a1));
} else if (TAG(s1332) == 7) {
return C2(7, FLD(s1332, 0), F_R_dops(FLD(s1332, 1), a1));
} else if (TAG(s1332) == 8) {
return C3(8, FLD(s1332, 0), F_R_dops(FLD(s1332, 1), a1), F_R_dops(FLD(s1332, 2), a1));
} else if (TAG(s1332) == 9) {
return C2(9, F_R_dopss(FLD(s1332, 0), a1), F_R_dopss(FLD(s1332, 1), a1));
} else if (TAG(s1332) == 10) {
return C2(10, FLD(s1332, 0), F_R_dops(FLD(s1332, 1), a1));
} else if (TAG(s1332) == 11) {
return C2(11, FLD(s1332, 0), F_R_dops(FLD(s1332, 1), a1));
} else {
return s1332;
}
}
static V W_R_dops(V *a) { (void)a; return F_R_dops(a[0], a[1]); }
static V F_R_dopss(V a0, V a1) {
top:;
V s1334 = a0;
if ((s1334) == IMM(0)) {
return IMM(0);
} else if (TAG(s1334) == 1) {
return C2(1, F_R_dops(FLD(s1334, 0), a1), F_R_dopss(FLD(s1334, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_R_dopss(V *a) { (void)a; return F_R_dopss(a[0], a[1]); }
static V S1335(void) { static V c; return STRC(c, "+"); }
static V S1336(void) { static V c; return STRC(c, "-"); }
static V S1337(void) { static V c; return STRC(c, "*"); }
static V S1338(void) { static V c; return STRC(c, "/"); }
static V S1339(void) { static V c; return STRC(c, "%"); }
static V S1340(void) { static V c; return STRC(c, "<"); }
static V S1341(void) { static V c; return STRC(c, "<="); }
static V S1342(void) { static V c; return STRC(c, ">"); }
static V S1343(void) { static V c; return STRC(c, ">="); }
static V S1344(void) { static V c; return STRC(c, ".&."); }
static V S1345(void) { static V c; return STRC(c, ".|."); }
static V S1346(void) { static V c; return STRC(c, ".^."); }
static V S1347(void) { static V c; return STRC(c, "<<"); }
static V S1348(void) { static V c; return STRC(c, ">>"); }
static V F_R_dopname(V a0) {
top:;
return F_R_dopname_dgo(F_P_dwhich(a0, C2(1, S1335(), C2(1, S1336(), C2(1, S1337(), C2(1, S1338(), C2(1, S1339(), C2(1, S1340(), C2(1, S1341(), C2(1, S1342(), C2(1, S1343(), C2(1, S1344(), C2(1, S1345(), C2(1, S1346(), C2(1, S1347(), C2(1, S1348(), IMM(0)))))))))))))))));
}
static V W_R_dopname(V *a) { (void)a; return F_R_dopname(a[0]); }
static V S1350(void) { static V c; return STRC(c, "add"); }
static V S1351(void) { static V c; return STRC(c, "sub"); }
static V S1352(void) { static V c; return STRC(c, "mul"); }
static V S1353(void) { static V c; return STRC(c, "div"); }
static V S1354(void) { static V c; return STRC(c, "mod"); }
static V S1355(void) { static V c; return STRC(c, "is_lt"); }
static V S1356(void) { static V c; return STRC(c, "is_le"); }
static V S1357(void) { static V c; return STRC(c, "is_gt"); }
static V S1358(void) { static V c; return STRC(c, "is_ge"); }
static V S1359(void) { static V c; return STRC(c, "and"); }
static V S1360(void) { static V c; return STRC(c, "or"); }
static V S1361(void) { static V c; return STRC(c, "xor"); }
static V S1362(void) { static V c; return STRC(c, "shln"); }
static V S1363(void) { static V c; return STRC(c, "shrn"); }
static V S1364(void) { static V c; return STRC(c, "\077"); }
static V F_R_dopname_dgo(V a0) {
top:;
V s1349 = a0;
if ((s1349) == 0) {
return S1350();
} else if ((s1349) == 1) {
return S1351();
} else if ((s1349) == 2) {
return S1352();
} else if ((s1349) == 3) {
return S1353();
} else if ((s1349) == 4) {
return S1354();
} else if ((s1349) == 5) {
return S1355();
} else if ((s1349) == 6) {
return S1356();
} else if ((s1349) == 7) {
return S1357();
} else if ((s1349) == 8) {
return S1358();
} else if ((s1349) == 9) {
return S1359();
} else if ((s1349) == 10) {
return S1360();
} else if ((s1349) == 11) {
return S1361();
} else if ((s1349) == 12) {
return S1362();
} else if ((s1349) == 13) {
return S1363();
} else if (nat_ge(s1349, 14)) {
return S1364();
} else { bend_fail("incomplete match"); }
}
static V W_R_dopname_dgo(V *a) { (void)a; return F_R_dopname_dgo(a[0]); }
static V L1366(V *a) {
return F_Gen_dpure(F_Gen_dret(a[0], a[1]));
}
static V F_Gen_dstmt(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1365 = a4;
if (TAG(s1365) == 8) {
return F_Gen_dlet(a0, a1, a2, a3, FLD(s1365, 0), FLD(s1365, 1), FLD(s1365, 2));
} else if (TAG(s1365) == 9) {
return F_Gen_dmatch(a0, a1, a2, a3, FLD(s1365, 0), FLD(s1365, 1));
} else if (TAG(s1365) == 5 && TAG(FLD(s1365, 0)) == 0) {
return F_Gen_dstmt_dcall(a0, a1, a2, a3, FLD(FLD(s1365, 0), 0), FLD(s1365, 1), F_Gen_dis__tail(a1, a2, a3, FLD(FLD(s1365, 0), 0), FLD(s1365, 1)));
} else {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, s1365), mk_clo(L1366, 2, 1, (V[]){a3}));
}
}
static V W_Gen_dstmt(V *a) { (void)a; return F_Gen_dstmt(a[0], a[1], a[2], a[3], a[4]); }
static V S1368(void) { static V c; return STRC(c, "return "); }
static V S1369(void) { static V c; return STRC(c, ";\012"); }
static V S1370(void) { static V c; return STRC(c, " = "); }
static V S1371(void) { static V c; return STRC(c, ";\012"); }
static V F_Gen_dret(V a0, V a1) {
top:;
V s1367 = a0;
if ((s1367) == IMM(0)) {
return F_Doc_dlist(C2(1, C1(1, S1368()), C2(1, a1, C2(1, C1(1, S1369()), IMM(0)))));
} else if (TAG(s1367) == 1) {
return F_Doc_dlist(C2(1, C1(1, FLD(s1367, 0)), C2(1, C1(1, S1370()), C2(1, a1, C2(1, C1(1, S1371()), IMM(0))))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dret(V *a) { (void)a; return F_Gen_dret(a[0], a[1]); }
static V S1373(void) { static V c; return STRC(c, "u"); }
static V S1374(void) { static V c; return STRC(c, "u"); }
static V S1375(void) { static V c; return STRC(c, "VF("); }
static V S1376(void) { static V c; return STRC(c, "f)"); }
static V S1378(void) { static V c; return STRC(c, "nat_addk("); }
static V S1379(void) { static V c; return STRC(c, ", "); }
static V S1380(void) { static V c; return STRC(c, ")"); }
static V L1377(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1378()), C2(1, a[1], C2(1, C1(1, F_String_dappend(S1379(), F_String_dappend(F_U32_dshow(a[0]), S1380()))), IMM(0))))));
}
static V S1381(void) { static V c; return STRC(c, "0"); }
static V S1382(void) { static V c; return STRC(c, "parse error: "); }
static V S1384(void) { static V c; return STRC(c, "0"); }
static V L1383(V *a) {
return F_Gen_dpure(C1(1, S1384()));
}
static V S1385(void) { static V c; return STRC(c, "unexpected expression: "); }
static V S1387(void) { static V c; return STRC(c, "0"); }
static V L1386(V *a) {
return F_Gen_dpure(C1(1, S1387()));
}
static V F_Gen_dexpr(V a0, V a1, V a2) {
top:;
V s1372 = a2;
if (TAG(s1372) == 0) {
return F_Gen_dvar(a0, a1, FLD(s1372, 0));
} else if (TAG(s1372) == 1) {
return F_Gen_dpure(C1(1, F_String_dappend(F_U32_dshow(FLD(s1372, 0)), S1373())));
} else if (TAG(s1372) == 2) {
return F_Gen_dpure(C1(1, F_String_dappend(F_U32_dshow(FLD(s1372, 0)), S1374())));
} else if (TAG(s1372) == 3) {
return F_Gen_dpure(C1(1, F_String_dappend(S1375(), F_String_dappend(FLD(s1372, 0), S1376()))));
} else if (TAG(s1372) == 4) {
return F_Gen_dstr(FLD(s1372, 0));
} else if (TAG(s1372) == 5) {
return F_Gen_dcall(a0, a1, FLD(s1372, 0), FLD(s1372, 1));
} else if (TAG(s1372) == 6) {
return F_Gen_dctor(a0, a1, FLD(s1372, 0), FLD(s1372, 1));
} else if (TAG(s1372) == 7) {
return F_Gen_dlam(a0, a1, FLD(s1372, 0), FLD(s1372, 1));
} else if (TAG(s1372) == 8) {
return F_Gen_dblock(a0, a1, C3(8, FLD(s1372, 0), FLD(s1372, 1), FLD(s1372, 2)));
} else if (TAG(s1372) == 9) {
return F_Gen_dblock(a0, a1, C2(9, FLD(s1372, 0), FLD(s1372, 1)));
} else if (TAG(s1372) == 11) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, FLD(s1372, 1)), mk_clo(L1377, 2, 1, (V[]){FLD(s1372, 0)}));
} else if (TAG(s1372) == 14) {
return F_Gen_dpure(C1(1, S1381()));
} else if (TAG(s1372) == 15) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1382(), FLD(s1372, 0))), mk_clo(L1383, 1, 0, 0));
} else {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1385(), F_Expr_dshow(s1372))), mk_clo(L1386, 1, 0, 0));
}
}
static V W_Gen_dexpr(V *a) { (void)a; return F_Gen_dexpr(a[0], a[1], a[2]); }
static V S1389(void) { static V c; return STRC(c, "r"); }
static V S1392(void) { static V c; return STRC(c, "({ V "); }
static V S1393(void) { static V c; return STRC(c, ";\012"); }
static V S1394(void) { static V c; return STRC(c, "; })"); }
static V L1391(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1392(), F_String_dappend(a[0], S1393()))), C2(1, a[1], C2(1, C1(1, F_String_dappend(a[0], S1394())), IMM(0))))));
}
static V L1390(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[2], a[1], F_Self_dnone(), C1(1, a[3]), a[0]), mk_clo(L1391, 2, 1, (V[]){a[3]}));
}
static V L1388(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1389(), F_U32_dshow(a[3]))), mk_clo(L1390, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Gen_dblock(V a0, V a1, V a2) {
top:;
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1388, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Gen_dblock(V *a) { (void)a; return F_Gen_dblock(a[0], a[1], a[2]); }
static V S1395(void) { static V c; return STRC(c, ""); }
static V F_Self_dnone(void) {
top:;
return C3(0, S1395(), IMM(0), IMM(0));
}
static V W_Self_dnone(V *a) { (void)a; return F_Self_dnone(); }
static V S1399(void) { static V c; return STRC(c, "L"); }
static V S1401(void) { static V c; return STRC(c, "static V "); }
static V S1402(void) { static V c; return STRC(c, "(V *a);\012"); }
static V S1404(void) { static V c; return STRC(c, "a["); }
static V S1405(void) { static V c; return STRC(c, "]"); }
static V S1408(void) { static V c; return STRC(c, "static V "); }
static V S1409(void) { static V c; return STRC(c, "(V *a) {\012"); }
static V S1410(void) { static V c; return STRC(c, "}\012"); }
static V S1412(void) { static V c; return STRC(c, "mk_clo("); }
static V S1413(void) { static V c; return STRC(c, ", "); }
static V S1414(void) { static V c; return STRC(c, ", "); }
static V S1415(void) { static V c; return STRC(c, ", "); }
static V S1416(void) { static V c; return STRC(c, ")"); }
static V L1411(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1412(), F_String_dappend(a[2], F_String_dappend(S1413(), F_String_dappend(F_U32_dshow(F_U32_dinc(a[1])), F_String_dappend(S1414(), F_String_dappend(F_U32_dshow(a[1]), S1415()))))))), C2(1, F_Gen_darr(F_Gen_dcaps_douter(a[0])), C2(1, C1(1, S1416()), IMM(0))))));
}
static V L1407(V *a) {
return F_Gen_dbind(F_Gen_dcode(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1408(), F_String_dappend(a[2], S1409()))), C2(1, a[3], C2(1, C1(1, S1410()), IMM(0)))))), mk_clo(L1411, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L1406(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[4], F_List_dappend(a[5], F_Gen_dcaps_dinner(a[3], 0u)), F_Self_dnone(), IMM(0), a[2]), mk_clo(L1407, 4, 3, (V[]){a[3], a[0], a[1]}));
}
static V L1403(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_PatR_dbinds(F_Gen_dpat(a[5], a[4], F_String_dappend(S1404(), F_String_dappend(F_U32_dshow(a[3]), S1405())), C2(0, IMM(0), IMM(0))))), mk_clo(L1406, 6, 5, (V[]){a[3], a[0], a[1], a[2], a[5]}));
}
static V L1400(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S1401(), F_String_dappend(a[5], S1402())))), mk_clo(L1403, 7, 6, (V[]){a[5], a[0], a[1], a[2], a[3], a[4]}));
}
static V L1398(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1399(), F_U32_dshow(a[5]))), mk_clo(L1400, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V F_Gen_dlam(V a0, V a1, V a2, V a3) {
top:;
V v1396 = F_Gen_dcaps(F_FV_dexpr(a3, F_Pat_dvars(a2, IMM(0)), IMM(0)), a1);
V v1397 = F_U32_dfrom__nat(F_List_dlength(v1396));
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1398, 6, 5, (V[]){a3, v1396, v1397, a2, a0}));
}
static V W_Gen_dlam(V *a) { (void)a; return F_Gen_dlam(a[0], a[1], a[2], a[3]); }
static V F_Gen_dcaps_douter(V a0) {
top:;
V s1417 = a0;
if ((s1417) == IMM(0)) {
return IMM(0);
} else if (TAG(s1417) == 1) {
return C2(1, C1(1, FLD(FLD(s1417, 0), 1)), F_Gen_dcaps_douter(FLD(s1417, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps_douter(V *a) { (void)a; return F_Gen_dcaps_douter(a[0]); }
static V S1419(void) { static V c; return STRC(c, "0"); }
static V S1420(void) { static V c; return STRC(c, "(V[]){"); }
static V S1421(void) { static V c; return STRC(c, "}"); }
static V F_Gen_darr(V a0) {
top:;
V s1418 = a0;
if ((s1418) == IMM(0)) {
return C1(1, S1419());
} else if (TAG(s1418) == 1) {
return F_Doc_dlist(C2(1, C1(1, S1420()), C2(1, F_Gen_dcommas(C2(1, FLD(s1418, 0), FLD(s1418, 1))), C2(1, C1(1, S1421()), IMM(0)))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_darr(V *a) { (void)a; return F_Gen_darr(a[0]); }
static V S1422(void) { static V c; return STRC(c, ", "); }
static V F_Gen_dcommas(V a0) {
top:;
return F_Doc_dsep(a0, S1422());
}
static V W_Gen_dcommas(V *a) { (void)a; return F_Gen_dcommas(a[0]); }
static V F_Doc_dsep(V a0, V a1) {
top:;
V s1423 = a0;
if ((s1423) == IMM(0)) {
return IMM(0);
} else if (TAG(s1423) == 1) {
return C2(2, FLD(s1423, 0), F_Doc_dsep_dgo(FLD(s1423, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dsep(V *a) { (void)a; return F_Doc_dsep(a[0], a[1]); }
static V F_Doc_dsep_dgo(V a0, V a1) {
top:;
V s1424 = a0;
if ((s1424) == IMM(0)) {
return IMM(0);
} else if (TAG(s1424) == 1) {
return C2(2, C1(1, a1), C2(2, FLD(s1424, 0), F_Doc_dsep_dgo(FLD(s1424, 1), a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dsep_dgo(V *a) { (void)a; return F_Doc_dsep_dgo(a[0], a[1]); }
static V S1426(void) { static V c; return STRC(c, "a["); }
static V S1427(void) { static V c; return STRC(c, "]"); }
static V F_Gen_dcaps_dinner(V a0, V a1) {
top:;
V s1425 = a0;
if ((s1425) == IMM(0)) {
return IMM(0);
} else if (TAG(s1425) == 1) {
return C2(1, C2(0, FLD(FLD(s1425, 0), 0), F_String_dappend(S1426(), F_String_dappend(F_U32_dshow(a1), S1427()))), F_Gen_dcaps_dinner(FLD(s1425, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps_dinner(V *a) { (void)a; return F_Gen_dcaps_dinner(a[0], a[1]); }
static V S1429(void) { static V c; return STRC(c, "("); }
static V S1430(void) { static V c; return STRC(c, ") == "); }
static V S1431(void) { static V c; return STRC(c, "nat_subk("); }
static V S1432(void) { static V c; return STRC(c, ", "); }
static V S1433(void) { static V c; return STRC(c, ")"); }
static V S1434(void) { static V c; return STRC(c, "nat_ge("); }
static V S1435(void) { static V c; return STRC(c, ", "); }
static V S1436(void) { static V c; return STRC(c, ")"); }
static V S1437(void) { static V c; return STRC(c, "("); }
static V S1438(void) { static V c; return STRC(c, ") == "); }
static V F_Gen_dpat(V a0, V a1, V a2, V a3) {
top:;
V s1428 = a1;
if (TAG(s1428) == 0) {
return F_Gen_dpat_dvar(FLD(s1428, 0), a2, a3);
} else if (TAG(s1428) == 1) {
return F_Gen_dpat_dctor(a0, F_G_dctor(a0, FLD(s1428, 0)), FLD(s1428, 0), FLD(s1428, 1), a2, a3);
} else if (TAG(s1428) == 2) {
return F_Gen_dpat_dcond(F_String_dappend(S1429(), F_String_dappend(a2, F_String_dappend(S1430(), F_U32_dshow(FLD(s1428, 0))))), a3);
} else if (TAG(s1428) == 3) {
{ V t0 = a0; V t1 = FLD(s1428, 1); V t2 = F_String_dappend(S1431(), F_String_dappend(a2, F_String_dappend(S1432(), F_String_dappend(F_U32_dshow(FLD(s1428, 0)), S1433())))); V t3 = F_Gen_dpat_dcond(F_String_dappend(S1434(), F_String_dappend(a2, F_String_dappend(S1435(), F_String_dappend(F_U32_dshow(FLD(s1428, 0)), S1436())))), a3); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1428) == 4) {
return F_Gen_dpat_dcond(F_String_dappend(S1437(), F_String_dappend(a2, F_String_dappend(S1438(), F_U32_dshow(FLD(s1428, 0))))), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat(V *a) { (void)a; return F_Gen_dpat(a[0], a[1], a[2], a[3]); }
static V F_Gen_dpat_dcond(V a0, V a1) {
top:;
V v1439 = a1;
return C2(0, C2(1, a0, FLD(v1439, 0)), FLD(v1439, 1));
}
static V W_Gen_dpat_dcond(V *a) { (void)a; return F_Gen_dpat_dcond(a[0], a[1]); }
static V S1441(void) { static V c; return STRC(c, "0 /* unknown constructor "); }
static V S1442(void) { static V c; return STRC(c, " */"); }
static V F_Gen_dpat_dctor(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1440 = a1;
if ((s1440) == IMM(0)) {
return F_Gen_dpat_dcond(F_String_dappend(S1441(), F_String_dappend(a2, S1442())), a5);
} else if (TAG(s1440) == 1) {
return F_Gen_dpat_dkind(a0, F_U32_dto__nat(FLD(FLD(s1440, 0), 2)), FLD(FLD(s1440, 0), 0), FLD(FLD(s1440, 0), 3), a3, a4, a5);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dctor(V *a) { (void)a; return F_Gen_dpat_dctor(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1444(void) { static V c; return STRC(c, "TAG("); }
static V S1445(void) { static V c; return STRC(c, ") == "); }
static V S1446(void) { static V c; return STRC(c, "("); }
static V S1447(void) { static V c; return STRC(c, ") == IMM("); }
static V S1448(void) { static V c; return STRC(c, ")"); }
static V S1449(void) { static V c; return STRC(c, "("); }
static V S1450(void) { static V c; return STRC(c, ") == 0"); }
static V S1451(void) { static V c; return STRC(c, "nat_subk("); }
static V S1452(void) { static V c; return STRC(c, ", 1)"); }
static V S1453(void) { static V c; return STRC(c, "("); }
static V S1454(void) { static V c; return STRC(c, ") != 0"); }
static V F_Gen_dpat_dkind(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1443 = a1;
if ((s1443) == 0) {
return F_Gen_dpat_dfields(a0, a4, a5, 0u, F_Gen_dpat_dtag(a3, F_String_dappend(S1444(), F_String_dappend(a5, F_String_dappend(S1445(), F_U32_dshow(a2)))), a6));
} else if ((s1443) == 1) {
return F_Gen_dpat_dtag(a3, F_String_dappend(S1446(), F_String_dappend(a5, F_String_dappend(S1447(), F_String_dappend(F_U32_dshow(a2), S1448())))), a6);
} else if ((s1443) == 2) {
return F_Gen_dpat_dfields(a0, a4, a5, 99u, a6);
} else if ((s1443) == 3) {
return F_Gen_dpat_dcond(F_String_dappend(S1449(), F_String_dappend(a5, S1450())), a6);
} else if (nat_ge(s1443, 4)) {
return F_Gen_dpat_dfields(a0, a4, F_String_dappend(S1451(), F_String_dappend(a5, S1452())), 99u, F_Gen_dpat_dcond(F_String_dappend(S1453(), F_String_dappend(a5, S1454())), a6));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dkind(V *a) { (void)a; return F_Gen_dpat_dkind(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S1456(void) { static V c; return STRC(c, "FLD("); }
static V S1457(void) { static V c; return STRC(c, ", "); }
static V S1458(void) { static V c; return STRC(c, ")"); }
static V F_Gen_dpat_dfields(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1455 = a1;
if ((s1455) == IMM(0)) {
return a4;
} else if (TAG(s1455) == 1) {
{ V t0 = a0; V t1 = FLD(s1455, 1); V t2 = a2; V t3 = F_U32_dinc(a3); V t4 = F_Gen_dpat(a0, FLD(s1455, 0), F_Bool_dpick(F_U32_dis__eq(a3, 99u), a2, F_String_dappend(S1456(), F_String_dappend(a2, F_String_dappend(S1457(), F_String_dappend(F_U32_dshow(a3), S1458()))))), a4); a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dfields(V *a) { (void)a; return F_Gen_dpat_dfields(a[0], a[1], a[2], a[3], a[4]); }
static V F_Gen_dpat_dtag(V a0, V a1, V a2) {
top:;
V s1459 = a0;
if ((s1459) == IMM(1)) {
return a2;
} else if ((s1459) == IMM(0)) {
return F_Gen_dpat_dcond(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dtag(V *a) { (void)a; return F_Gen_dpat_dtag(a[0], a[1], a[2]); }
static V S1461(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dpat_dvar(V a0, V a1, V a2) {
top:;
V v1460 = a2;
return C2(0, FLD(v1460, 0), F_Bool_dpick(F_Str_deq(a0, S1461()), FLD(v1460, 1), C2(1, C2(0, a0, a1), FLD(v1460, 1))));
}
static V W_Gen_dpat_dvar(V *a) { (void)a; return F_Gen_dpat_dvar(a[0], a[1], a[2]); }
static V F_PatR_dbinds(V a0) {
top:;
V v1462 = a0;
return FLD(v1462, 1);
}
static V W_PatR_dbinds(V *a) { (void)a; return F_PatR_dbinds(a[0]); }
static V F_Pat_dvars(V a0, V a1) {
top:;
V s1463 = a0;
if (TAG(s1463) == 0) {
return C2(1, FLD(s1463, 0), a1);
} else if (TAG(s1463) == 1) {
return F_Pats_dvars(FLD(s1463, 1), a1);
} else if (TAG(s1463) == 3) {
{ V t0 = FLD(s1463, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else {
return a1;
}
}
static V W_Pat_dvars(V *a) { (void)a; return F_Pat_dvars(a[0], a[1]); }
static V F_Pats_dvars(V a0, V a1) {
top:;
V s1464 = a0;
if ((s1464) == IMM(0)) {
return a1;
} else if (TAG(s1464) == 1) {
{ V t0 = FLD(s1464, 1); V t1 = F_Pat_dvars(FLD(s1464, 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Pats_dvars(V *a) { (void)a; return F_Pats_dvars(a[0], a[1]); }
static V F_FV_dexpr(V a0, V a1, V a2) {
top:;
V s1465 = a0;
if (TAG(s1465) == 0) {
return F_FV_dvar(FLD(s1465, 0), a1, a2);
} else if (TAG(s1465) == 5) {
return F_FV_dexprs(FLD(s1465, 1), a1, F_FV_dexpr(FLD(s1465, 0), a1, a2));
} else if (TAG(s1465) == 6) {
return F_FV_dexprs(FLD(s1465, 1), a1, a2);
} else if (TAG(s1465) == 7) {
{ V t0 = FLD(s1465, 1); V t1 = F_Pat_dvars(FLD(s1465, 0), a1); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1465) == 8) {
{ V t0 = FLD(s1465, 2); V t1 = F_Pat_dvars(FLD(s1465, 0), a1); V t2 = F_FV_dexpr(FLD(s1465, 1), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1465) == 9) {
return F_FV_dexprs(FLD(s1465, 1), a1, F_FV_dexprs(FLD(s1465, 0), a1, a2));
} else if (TAG(s1465) == 10) {
{ V t0 = FLD(s1465, 1); V t1 = F_Pats_dvars(FLD(s1465, 0), a1); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1465) == 11) {
{ V t0 = FLD(s1465, 1); V t1 = a1; V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1465) == 12) {
{ V t0 = FLD(s1465, 2); V t1 = a1; V t2 = F_FV_dexpr(FLD(s1465, 1), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1465) == 13) {
{ V t0 = FLD(s1465, 0); V t1 = a1; V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else {
return a2;
}
}
static V W_FV_dexpr(V *a) { (void)a; return F_FV_dexpr(a[0], a[1], a[2]); }
static V F_FV_dexprs(V a0, V a1, V a2) {
top:;
V s1466 = a0;
if ((s1466) == IMM(0)) {
return a2;
} else if (TAG(s1466) == 1) {
{ V t0 = FLD(s1466, 1); V t1 = a1; V t2 = F_FV_dexpr(FLD(s1466, 0), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_FV_dexprs(V *a) { (void)a; return F_FV_dexprs(a[0], a[1], a[2]); }
static V F_FV_dvar(V a0, V a1, V a2) {
top:;
return F_Bool_dpick(F_Bool_dor(F_Str_dhas(a1, a0), F_Str_dhas(a2, a0)), a2, C2(1, a0, a2));
}
static V W_FV_dvar(V *a) { (void)a; return F_FV_dvar(a[0], a[1], a[2]); }
static V F_Str_dhas(V a0, V a1) {
top:;
return F_List_dcontains(mk_clo(W_String_deq, 2, 0, 0), a0, a1);
}
static V W_Str_dhas(V *a) { (void)a; return F_Str_dhas(a[0], a[1]); }
static V F_Gen_dcaps(V a0, V a1) {
top:;
V s1467 = a0;
if ((s1467) == IMM(0)) {
return IMM(0);
} else if (TAG(s1467) == 1) {
return F_Gen_dcaps_dput(FLD(s1467, 0), F_Env_dfind(a1, FLD(s1467, 0)), F_Gen_dcaps(FLD(s1467, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps(V *a) { (void)a; return F_Gen_dcaps(a[0], a[1]); }
static V F_Gen_dcaps_dput(V a0, V a1, V a2) {
top:;
V s1468 = a1;
if ((s1468) == IMM(0)) {
return a2;
} else if (TAG(s1468) == 1) {
return C2(1, C2(0, a0, FLD(s1468, 0)), a2);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps_dput(V *a) { (void)a; return F_Gen_dcaps_dput(a[0], a[1], a[2]); }
static V F_Gen_dctor(V a0, V a1, V a2, V a3) {
top:;
return F_Gen_dctor_dinfo(a0, a1, a2, F_G_dctor(a0, a2), a3);
}
static V W_Gen_dctor(V *a) { (void)a; return F_Gen_dctor(a[0], a[1], a[2], a[3]); }
static V S1470(void) { static V c; return STRC(c, "unknown constructor: "); }
static V S1472(void) { static V c; return STRC(c, "0"); }
static V L1471(V *a) {
return F_Gen_dpure(C1(1, S1472()));
}
static V L1473(V *a) {
return F_Gen_dpure(F_Gen_dctor_dkind(a[1], F_U32_dto__nat(a[0]), a[2]));
}
static V F_Gen_dctor_dinfo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1469 = a3;
if ((s1469) == IMM(0)) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1470(), a2)), mk_clo(L1471, 1, 0, 0));
} else if (TAG(s1469) == 1) {
return F_Gen_dbind(F_Gen_dexprs(a0, a1, a4), mk_clo(L1473, 3, 2, (V[]){FLD(FLD(s1469, 0), 2), FLD(FLD(s1469, 0), 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dctor_dinfo(V *a) { (void)a; return F_Gen_dctor_dinfo(a[0], a[1], a[2], a[3], a[4]); }
static V S1475(void) { static V c; return STRC(c, "IMM("); }
static V S1476(void) { static V c; return STRC(c, ")"); }
static V S1477(void) { static V c; return STRC(c, "0"); }
static V S1478(void) { static V c; return STRC(c, "nat_addk("); }
static V S1479(void) { static V c; return STRC(c, ", 1)"); }
static V F_Gen_dctor_dkind(V a0, V a1, V a2) {
top:;
V s1474 = a1;
if ((s1474) == 0) {
return F_Gen_dctor_dnode(a0, a2);
} else if ((s1474) == 1) {
return C1(1, F_String_dappend(S1475(), F_String_dappend(F_U32_dshow(a0), S1476())));
} else if ((s1474) == 2) {
return F_Doc_dlist(a2);
} else if ((s1474) == 3) {
return C1(1, S1477());
} else if (nat_ge(s1474, 4)) {
return F_Doc_dlist(C2(1, C1(1, S1478()), C2(1, F_Doc_dlist(a2), C2(1, C1(1, S1479()), IMM(0)))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dctor_dkind(V *a) { (void)a; return F_Gen_dctor_dkind(a[0], a[1], a[2]); }
static V S1481(void) { static V c; return STRC(c, "C"); }
static V S1482(void) { static V c; return STRC(c, "("); }
static V S1483(void) { static V c; return STRC(c, ", "); }
static V S1484(void) { static V c; return STRC(c, ")"); }
static V S1485(void) { static V c; return STRC(c, "CN("); }
static V S1486(void) { static V c; return STRC(c, ", "); }
static V S1487(void) { static V c; return STRC(c, ", "); }
static V S1488(void) { static V c; return STRC(c, ")"); }
static V F_Gen_dctor_dnode(V a0, V a1) {
top:;
V v1480 = F_Gen_dlen(a1);
return F_Bool_dpick(F_U32_dis__le(v1480, 4u), F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1481(), F_String_dappend(F_U32_dshow(v1480), F_String_dappend(S1482(), F_String_dappend(F_U32_dshow(a0), S1483()))))), C2(1, F_Gen_dcommas(a1), C2(1, C1(1, S1484()), IMM(0))))), F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1485(), F_String_dappend(F_U32_dshow(a0), F_String_dappend(S1486(), F_String_dappend(F_U32_dshow(v1480), S1487()))))), C2(1, F_Gen_darr(a1), C2(1, C1(1, S1488()), IMM(0))))));
}
static V W_Gen_dctor_dnode(V *a) { (void)a; return F_Gen_dctor_dnode(a[0], a[1]); }
static V F_Gen_dlen(V a0) {
top:;
return F_U32_dfrom__nat(F_List_dlength(a0));
}
static V W_Gen_dlen(V *a) { (void)a; return F_Gen_dlen(a[0]); }
static V L1491(V *a) {
return F_Gen_dpure(C2(1, a[0], a[1]));
}
static V L1490(V *a) {
return F_Gen_dbind(F_Gen_dexprs(a[2], a[1], a[0]), mk_clo(L1491, 2, 1, (V[]){a[3]}));
}
static V F_Gen_dexprs(V a0, V a1, V a2) {
top:;
V s1489 = a2;
if ((s1489) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1489) == 1) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, FLD(s1489, 0)), mk_clo(L1490, 4, 3, (V[]){FLD(s1489, 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dexprs(V *a) { (void)a; return F_Gen_dexprs(a[0], a[1], a[2]); }
static V F_Gen_dcall(V a0, V a1, V a2, V a3) {
top:;
V s1492 = a2;
if (TAG(s1492) == 0) {
return F_Gen_dcall_dvar(a0, a1, FLD(s1492, 0), a3, F_Env_dhas(a1, FLD(s1492, 0)));
} else {
return F_Gen_dcall_dlocal(a0, a1, s1492, a3);
}
}
static V W_Gen_dcall(V *a) { (void)a; return F_Gen_dcall(a[0], a[1], a[2], a[3]); }
static V L1494(V *a) {
return F_Gen_dpure(F_Gen_dapply(a[1], a[0]));
}
static V L1493(V *a) {
return F_Gen_dbind(F_Gen_dexprs(a[2], a[1], a[0]), mk_clo(L1494, 2, 1, (V[]){a[3]}));
}
static V F_Gen_dcall_dlocal(V a0, V a1, V a2, V a3) {
top:;
return F_Gen_dbind(F_Gen_dexpr(a0, a1, a2), mk_clo(L1493, 4, 3, (V[]){a3, a1, a0}));
}
static V W_Gen_dcall_dlocal(V *a) { (void)a; return F_Gen_dcall_dlocal(a[0], a[1], a[2], a[3]); }
static V S1496(void) { static V c; return STRC(c, "apply("); }
static V S1497(void) { static V c; return STRC(c, ", "); }
static V S1498(void) { static V c; return STRC(c, ")"); }
static V F_Gen_dapply(V a0, V a1) {
top:;
V s1495 = a0;
if ((s1495) == IMM(0)) {
return a1;
} else if (TAG(s1495) == 1) {
{ V t0 = FLD(s1495, 1); V t1 = F_Doc_dlist(C2(1, C1(1, S1496()), C2(1, a1, C2(1, C1(1, S1497()), C2(1, FLD(s1495, 0), C2(1, C1(1, S1498()), IMM(0))))))); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dapply(V *a) { (void)a; return F_Gen_dapply(a[0], a[1]); }
static V F_Env_dhas(V a0, V a1) {
top:;
return F_Maybe_dis__some(F_Env_dfind(a0, a1));
}
static V W_Env_dhas(V *a) { (void)a; return F_Env_dhas(a[0], a[1]); }
static V F_Maybe_dis__some(V a2) {
top:;
V s1499 = a2;
if ((s1499) == IMM(0)) {
return IMM(0);
} else if (TAG(s1499) == 1) {
return IMM(1);
} else { bend_fail("incomplete match"); }
}
static V W_Maybe_dis__some(V *a) { (void)a; return F_Maybe_dis__some(a[2]); }
static V F_Gen_dcall_dvar(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1500 = a4;
if ((s1500) == IMM(1)) {
return F_Gen_dcall_dlocal(a0, a1, C1(0, a2), a3);
} else if ((s1500) == IMM(0)) {
return F_Gen_dcall_ddef(a0, a1, a2, F_G_ddef(a0, a2), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcall_dvar(V *a) { (void)a; return F_Gen_dcall_dvar(a[0], a[1], a[2], a[3], a[4]); }
static V F_Gen_dcall_ddef(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1501 = a3;
return F_Gen_dcall_dkind(a0, a1, a2, F_U32_dto__nat(FLD(v1501, 0)), FLD(v1501, 1), F_Gen_dsplit(FLD(v1501, 1), a4, C4(0, IMM(0), IMM(0), IMM(0), IMM(0))));
}
static V W_Gen_dcall_ddef(V *a) { (void)a; return F_Gen_dcall_ddef(a[0], a[1], a[2], a[3], a[4]); }
static V S1508(void) { static V c; return STRC(c, ""); }
static V F_Gen_dsplit(V a0, V a1, V a2) {
top:;
V s1502 = a0;
V s1503 = a1;
if ((s1502) == IMM(0)) {
V v1504 = a2;
return C4(0, FLD(v1504, 0), FLD(v1504, 1), s1503, IMM(1));
} else if (TAG(s1502) == 1 && (s1503) == IMM(0)) {
V v1505 = a2;
return C4(0, FLD(v1505, 0), FLD(v1505, 1), IMM(0), IMM(0));
} else if (TAG(s1502) == 1 && (FLD(s1502, 0)) == IMM(1) && TAG(s1503) == 1) {
V v1506 = a2;
{ V t0 = FLD(s1502, 1); V t1 = FLD(s1503, 1); V t2 = C4(0, F_List_dappend(FLD(v1506, 0), C2(1, FLD(s1503, 0), IMM(0))), F_List_dappend(FLD(v1506, 1), C2(1, FLD(s1503, 0), IMM(0))), FLD(v1506, 2), FLD(v1506, 3)); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1502) == 1 && (FLD(s1502, 0)) == IMM(0) && TAG(s1503) == 1) {
V v1507 = a2;
{ V t0 = FLD(s1502, 1); V t1 = FLD(s1503, 1); V t2 = C4(0, FLD(v1507, 0), F_List_dappend(FLD(v1507, 1), C2(1, C2(14, S1508(), IMM(0)), IMM(0))), FLD(v1507, 2), FLD(v1507, 3)); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dsplit(V *a) { (void)a; return F_Gen_dsplit(a[0], a[1], a[2]); }
static V S1510(void) { static V c; return STRC(c, "0"); }
static V S1511(void) { static V c; return STRC(c, "unknown function: "); }
static V S1513(void) { static V c; return STRC(c, "0"); }
static V L1512(V *a) {
return F_Gen_dpure(C1(1, S1513()));
}
static V L1514(V *a) {
return F_Gen_dcall_dsplit(a[4], a[3], a[2], a[1], a[0]);
}
static V F_Gen_dcall_dkind(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1509 = a3;
if ((s1509) == 3) {
return F_Gen_dpure(C1(1, S1510()));
} else if ((s1509) == 99) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1511(), a2)), mk_clo(L1512, 1, 0, 0));
} else {
return F_Gen_dbind(F_Gen_dref(a2), mk_clo(L1514, 6, 5, (V[]){a5, a4, a2, a1, a0}));
}
}
static V W_Gen_dcall_dkind(V *a) { (void)a; return F_Gen_dcall_dkind(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Gen_dcall_dsplit(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1515 = a4;
return F_Gen_dcall_dfull(a0, a1, a2, a3, FLD(v1515, 0), FLD(v1515, 1), FLD(v1515, 2), FLD(v1515, 3));
}
static V W_Gen_dcall_dsplit(V *a) { (void)a; return F_Gen_dcall_dsplit(a[0], a[1], a[2], a[3], a[4]); }
static V S1519(void) { static V c; return STRC(c, "("); }
static V S1520(void) { static V c; return STRC(c, ")"); }
static V L1518(V *a) {
return F_Gen_dpure(F_Gen_dapply(a[2], F_Doc_dlist(C2(1, C1(1, F_String_dappend(F_Gen_df(a[1]), S1519())), C2(1, F_Gen_dcommas(a[0]), C2(1, C1(1, S1520()), IMM(0)))))));
}
static V L1517(V *a) {
return F_Gen_dbind(F_Gen_dexprs(a[3], a[2], a[1]), mk_clo(L1518, 3, 2, (V[]){a[4], a[0]}));
}
static V S1522(void) { static V c; return STRC(c, "mk_clo("); }
static V S1523(void) { static V c; return STRC(c, ", "); }
static V S1524(void) { static V c; return STRC(c, ", "); }
static V S1525(void) { static V c; return STRC(c, ", "); }
static V S1526(void) { static V c; return STRC(c, ")"); }
static V L1521(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1522(), F_String_dappend(F_Gen_dw(a[1]), F_String_dappend(S1523(), F_String_dappend(F_U32_dshow(F_U32_dfrom__nat(F_List_dlength(a[0]))), F_String_dappend(S1524(), F_String_dappend(F_U32_dshow(F_Gen_dlen(a[2])), S1525()))))))), C2(1, F_Gen_darr(a[2]), C2(1, C1(1, S1526()), IMM(0))))));
}
static V F_Gen_dcall_dfull(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s1516 = a7;
if ((s1516) == IMM(1)) {
return F_Gen_dbind(F_Gen_dexprs(a0, a1, a4), mk_clo(L1517, 5, 4, (V[]){a2, a6, a1, a0}));
} else if ((s1516) == IMM(0)) {
return F_Gen_dbind(F_Gen_dexprs(a0, a1, a5), mk_clo(L1521, 3, 2, (V[]){a3, a2}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcall_dfull(V *a) { (void)a; return F_Gen_dcall_dfull(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V L1527(V *a) {
return F_Gen_dref_dgo(a[0], a[1]);
}
static V F_Gen_dref(V a0) {
top:;
return mk_clo(L1527, 2, 1, (V[]){a0});
}
static V W_Gen_dref(V *a) { (void)a; return F_Gen_dref(a[0]); }
static V F_Gen_dref_dgo(V a0, V a1) {
top:;
V v1528 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v1528, 0), FLD(v1528, 1), FLD(v1528, 2), C2(1, a0, FLD(v1528, 3)), FLD(v1528, 4), FLD(v1528, 5), FLD(v1528, 6)}));
}
static V W_Gen_dref_dgo(V *a) { (void)a; return F_Gen_dref_dgo(a[0], a[1]); }
static V S1530(void) { static V c; return STRC(c, "S"); }
static V S1532(void) { static V c; return STRC(c, "static V "); }
static V S1533(void) { static V c; return STRC(c, "(void);\012"); }
static V S1535(void) { static V c; return STRC(c, "static V "); }
static V S1536(void) { static V c; return STRC(c, "(void) { static V c; return STRC(c, \042"); }
static V S1537(void) { static V c; return STRC(c, "\042); }\012"); }
static V S1539(void) { static V c; return STRC(c, "()"); }
static V L1538(V *a) {
return F_Gen_dpure(C1(1, F_String_dappend(a[0], S1539())));
}
static V L1534(V *a) {
return F_Gen_dbind(F_Gen_dcode(C1(1, F_String_dappend(S1535(), F_String_dappend(a[1], F_String_dappend(S1536(), F_String_dappend(F_Gen_dlit(a[0]), S1537())))))), mk_clo(L1538, 2, 1, (V[]){a[1]}));
}
static V L1531(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S1532(), F_String_dappend(a[1], S1533())))), mk_clo(L1534, 3, 2, (V[]){a[0], a[1]}));
}
static V L1529(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1530(), F_U32_dshow(a[1]))), mk_clo(L1531, 2, 1, (V[]){a[0]}));
}
static V F_Gen_dstr(V a0) {
top:;
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1529, 2, 1, (V[]){a0}));
}
static V W_Gen_dstr(V *a) { (void)a; return F_Gen_dstr(a[0]); }
static V S1541(void) { static V c; return STRC(c, ""); }
static V F_Gen_dlit(V a0) {
top:;
V s1540 = a0;
if ((s1540) == IMM(0)) {
return S1541();
} else if (TAG(s1540) == 1) {
return F_String_dappend(F_Gen_dlit__chr(FLD(s1540, 0)), F_Gen_dlit(FLD(s1540, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dlit(V *a) { (void)a; return F_Gen_dlit(a[0]); }
static V S1542(void) { static V c; return STRC(c, "\042"); }
static V S1543(void) { static V c; return STRC(c, "\134"); }
static V S1544(void) { static V c; return STRC(c, "\077"); }
static V F_Gen_dlit__chr(V a0) {
top:;
return F_Bool_dpick(F_Bool_dand(F_Bool_dand(F_U32_dis__ge(a0, 32u), F_U32_dis__lt(a0, 127u)), F_Bool_dnot(F_Str_dhas(C2(1, S1542(), C2(1, S1543(), C2(1, S1544(), IMM(0)))), F_Str_dchr(a0)))), F_Str_dchr(a0), F_Gen_dutf8(a0));
}
static V W_Gen_dlit__chr(V *a) { (void)a; return F_Gen_dlit__chr(a[0]); }
static V F_Gen_dutf8(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__lt(a0, 128u), F_Gen_doct(a0), F_Bool_dpick(F_U32_dis__lt(a0, 2048u), F_String_dappend(F_Gen_doct(F_U32_dor(192u, F_U32_dshrn(a0, 6u))), F_Gen_doct(F_U32_dor(128u, F_U32_dand(a0, 63u)))), F_Bool_dpick(F_U32_dis__lt(a0, 65536u), F_String_dappend(F_Gen_doct(F_U32_dor(224u, F_U32_dshrn(a0, 12u))), F_String_dappend(F_Gen_doct(F_U32_dor(128u, F_U32_dand(F_U32_dshrn(a0, 6u), 63u))), F_Gen_doct(F_U32_dor(128u, F_U32_dand(a0, 63u))))), F_String_dappend(F_Gen_doct(F_U32_dor(240u, F_U32_dshrn(a0, 18u))), F_String_dappend(F_Gen_doct(F_U32_dor(128u, F_U32_dand(F_U32_dshrn(a0, 12u), 63u))), F_String_dappend(F_Gen_doct(F_U32_dor(128u, F_U32_dand(F_U32_dshrn(a0, 6u), 63u))), F_Gen_doct(F_U32_dor(128u, F_U32_dand(a0, 63u)))))))));
}
static V W_Gen_dutf8(V *a) { (void)a; return F_Gen_dutf8(a[0]); }
static V W_U32_dor(V *a) { (void)a; return F_U32_dor(a[0], a[1]); }
static V S1545(void) { static V c; return STRC(c, "\134"); }
static V F_Gen_doct(V a0) {
top:;
return F_String_dappend(S1545(), F_String_dappend(F_Str_dchr(F_U32_dadd(48u, F_U32_dand(F_U32_dshrn(a0, 6u), 7u))), F_String_dappend(F_Str_dchr(F_U32_dadd(48u, F_U32_dand(F_U32_dshrn(a0, 3u), 7u))), F_Str_dchr(F_U32_dadd(48u, F_U32_dand(a0, 7u))))));
}
static V W_Gen_doct(V *a) { (void)a; return F_Gen_doct(a[0]); }
static V F_Gen_dvar(V a0, V a1, V a2) {
top:;
return F_Gen_dvar_dfound(a0, a2, F_Env_dfind(a1, a2));
}
static V W_Gen_dvar(V *a) { (void)a; return F_Gen_dvar(a[0], a[1], a[2]); }
static V S1547(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dvar_dfound(V a0, V a1, V a2) {
top:;
V s1546 = a2;
if (TAG(s1546) == 1) {
return F_Gen_dpure(C1(1, FLD(s1546, 0)));
} else if ((s1546) == IMM(0)) {
return F_Gen_dvar_dglobal(a0, a1, F_Str_deq(a1, S1547()));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dvar_dfound(V *a) { (void)a; return F_Gen_dvar_dfound(a[0], a[1], a[2]); }
static V S1549(void) { static V c; return STRC(c, "0"); }
static V F_Gen_dvar_dglobal(V a0, V a1, V a2) {
top:;
V s1548 = a2;
if ((s1548) == IMM(1)) {
return F_Gen_dpure(C1(1, S1549()));
} else if ((s1548) == IMM(0)) {
return F_Gen_dvar_ddef(a1, F_G_ddef(a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dvar_dglobal(V *a) { (void)a; return F_Gen_dvar_dglobal(a[0], a[1], a[2]); }
static V F_Gen_dvar_ddef(V a0, V a1) {
top:;
V v1550 = a1;
return F_Gen_dvar_dkind(a0, F_U32_dto__nat(FLD(v1550, 0)), F_U32_dfrom__nat(F_List_dlength(FLD(v1550, 1))));
}
static V W_Gen_dvar_ddef(V *a) { (void)a; return F_Gen_dvar_ddef(a[0], a[1]); }
static V S1552(void) { static V c; return STRC(c, "0"); }
static V S1553(void) { static V c; return STRC(c, "unknown name: "); }
static V S1555(void) { static V c; return STRC(c, "0"); }
static V L1554(V *a) {
return F_Gen_dpure(C1(1, S1555()));
}
static V S1557(void) { static V c; return STRC(c, "()"); }
static V S1558(void) { static V c; return STRC(c, "mk_clo("); }
static V S1559(void) { static V c; return STRC(c, ", "); }
static V S1560(void) { static V c; return STRC(c, ", 0, 0)"); }
static V L1556(V *a) {
return F_Gen_dpure(F_Bool_dpick(F_U32_dis__zero(a[1]), C1(1, F_String_dappend(F_Gen_df(a[0]), S1557())), C1(1, F_String_dappend(S1558(), F_String_dappend(F_Gen_dw(a[0]), F_String_dappend(S1559(), F_String_dappend(F_U32_dshow(a[1]), S1560())))))));
}
static V F_Gen_dvar_dkind(V a0, V a1, V a2) {
top:;
V s1551 = a1;
if ((s1551) == 3) {
return F_Gen_dpure(C1(1, S1552()));
} else if ((s1551) == 99) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1553(), a0)), mk_clo(L1554, 1, 0, 0));
} else {
return F_Gen_dbind(F_Gen_dref(a0), mk_clo(L1556, 3, 2, (V[]){a0, a2}));
}
}
static V W_Gen_dvar_dkind(V *a) { (void)a; return F_Gen_dvar_dkind(a[0], a[1], a[2]); }
static V F_Gen_dis__tail(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1561 = a1;
return F_Bool_dand(F_Bool_dand(F_Gen_dis__ret(a2), F_Str_deq(FLD(v1561, 0), a3)), F_Bool_dand(F_Bool_dnot(F_Env_dhas(a0, a3)), F_Nat_dis__eq(F_List_dlength(FLD(v1561, 1)), F_List_dlength(a4))));
}
static V W_Gen_dis__tail(V *a) { (void)a; return F_Gen_dis__tail(a[0], a[1], a[2], a[3], a[4]); }
static V W_Nat_dis__eq(V *a) { (void)a; return F_Nat_dis__eq(a[0], a[1]); }
static V F_Gen_dis__ret(V a0) {
top:;
V s1562 = a0;
if ((s1562) == IMM(0)) {
return IMM(1);
} else if (TAG(s1562) == 1) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dis__ret(V *a) { (void)a; return F_Gen_dis__ret(a[0]); }
static V L1564(V *a) {
return F_Gen_dpure(F_Gen_dret(a[0], a[1]));
}
static V F_Gen_dstmt_dcall(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1563 = a6;
if ((s1563) == IMM(1)) {
return F_Gen_dtail_dself(a0, a1, a2, a5);
} else if ((s1563) == IMM(0)) {
return F_Gen_dbind(F_Gen_dcall(a0, a1, C1(0, a4), a5), mk_clo(L1564, 2, 1, (V[]){a3}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dstmt_dcall(V *a) { (void)a; return F_Gen_dstmt_dcall(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Gen_dtail_dself(V a0, V a1, V a2, V a3) {
top:;
V v1565 = a2;
return F_Gen_dtail(a0, a1, FLD(v1565, 2), F_Gen_dsplit(FLD(v1565, 1), a3, C4(0, IMM(0), IMM(0), IMM(0), IMM(0))));
}
static V W_Gen_dtail_dself(V *a) { (void)a; return F_Gen_dtail_dself(a[0], a[1], a[2], a[3]); }
static V S1568(void) { static V c; return STRC(c, "{ "); }
static V S1569(void) { static V c; return STRC(c, "goto top; }\012"); }
static V L1567(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1568()), C2(1, F_Gen_dtail_dtemps(a[1], 0u), C2(1, F_Gen_dtail_dassign(a[0], 0u), C2(1, C1(1, S1569()), IMM(0)))))));
}
static V F_Gen_dtail(V a0, V a1, V a2, V a3) {
top:;
V v1566 = a3;
return F_Gen_dbind(F_Gen_dexprs(a0, a1, FLD(v1566, 0)), mk_clo(L1567, 2, 1, (V[]){a2}));
}
static V W_Gen_dtail(V *a) { (void)a; return F_Gen_dtail(a[0], a[1], a[2], a[3]); }
static V S1571(void) { static V c; return STRC(c, " = t"); }
static V S1572(void) { static V c; return STRC(c, "; "); }
static V F_Gen_dtail_dassign(V a0, V a1) {
top:;
V s1570 = a0;
if ((s1570) == IMM(0)) {
return IMM(0);
} else if (TAG(s1570) == 1) {
return F_Doc_dlist(C2(1, C1(1, F_String_dappend(FLD(s1570, 0), F_String_dappend(S1571(), F_String_dappend(F_U32_dshow(a1), S1572())))), C2(1, F_Gen_dtail_dassign(FLD(s1570, 1), F_U32_dinc(a1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dtail_dassign(V *a) { (void)a; return F_Gen_dtail_dassign(a[0], a[1]); }
static V S1574(void) { static V c; return STRC(c, "V t"); }
static V S1575(void) { static V c; return STRC(c, " = "); }
static V S1576(void) { static V c; return STRC(c, "; "); }
static V F_Gen_dtail_dtemps(V a0, V a1) {
top:;
V s1573 = a0;
if ((s1573) == IMM(0)) {
return IMM(0);
} else if (TAG(s1573) == 1) {
return F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1574(), F_String_dappend(F_U32_dshow(a1), S1575()))), C2(1, FLD(s1573, 0), C2(1, C1(1, S1576()), C2(1, F_Gen_dtail_dtemps(FLD(s1573, 1), F_U32_dinc(a1)), IMM(0))))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dtail_dtemps(V *a) { (void)a; return F_Gen_dtail_dtemps(a[0], a[1]); }
static V L1577(V *a) {
return F_Gen_dmatch_dgo(a[4], a[3], a[2], a[1], a[0], a[5]);
}
static V F_Gen_dmatch(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Gen_dbind(F_Gen_dscrs(a0, a1, a4), mk_clo(L1577, 6, 5, (V[]){a5, a3, a2, a1, a0}));
}
static V W_Gen_dmatch(V *a) { (void)a; return F_Gen_dmatch(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L1579(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V F_Gen_dmatch_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v1578 = a5;
return F_Gen_dbind(F_Gen_dcases(a0, a1, a2, a3, FLD(v1578, 0), a4), mk_clo(L1579, 2, 1, (V[]){FLD(v1578, 1)}));
}
static V W_Gen_dmatch_dgo(V *a) { (void)a; return F_Gen_dmatch_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1581(void) { static V c; return STRC(c, "{ bend_fail(\042incomplete match\042); }\012"); }
static V L1585(V *a) {
return F_Gen_dcases_dnext(a[6], a[5], a[4], a[3], a[2], a[1], F_List_dreverse(a[0]), a[7]);
}
static V F_Gen_dcases(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1580 = a5;
if ((s1580) == IMM(0)) {
return F_Gen_dpure(C1(1, S1581()));
} else if (TAG(s1580) == 1 && TAG(FLD(s1580, 0)) == 10) {
V v1582 = F_Gen_dpats(a0, FLD(FLD(s1580, 0), 0), a4, C2(0, IMM(0), IMM(0)));
V v1583 = F_PatR_dconds(v1582);
V v1584 = F_PatR_dbinds(v1582);
return F_Gen_dbind(F_Gen_dstmt(a0, F_List_dappend(v1584, a1), a2, a3, FLD(FLD(s1580, 0), 1)), mk_clo(L1585, 8, 7, (V[]){v1583, FLD(s1580, 1), a4, a3, a2, a1, a0}));
} else if (TAG(s1580) == 1) {
{ V t0 = a0; V t1 = a1; V t2 = a2; V t3 = a3; V t4 = a4; V t5 = FLD(s1580, 1); a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; a5 = t5; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcases(V *a) { (void)a; return F_Gen_dcases(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1587(void) { static V c; return STRC(c, "{\012"); }
static V S1588(void) { static V c; return STRC(c, "}\012"); }
static V S1590(void) { static V c; return STRC(c, "if ("); }
static V S1591(void) { static V c; return STRC(c, ") {\012"); }
static V S1592(void) { static V c; return STRC(c, "} else "); }
static V L1589(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1590(), F_String_dappend(F_Gen_dand(C2(1, a[2], a[1])), S1591()))), C2(1, a[0], C2(1, C1(1, S1592()), C2(1, a[3], IMM(0)))))));
}
static V F_Gen_dcases_dnext(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s1586 = a6;
if ((s1586) == IMM(0)) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1587()), C2(1, a7, C2(1, C1(1, S1588()), IMM(0))))));
} else if (TAG(s1586) == 1) {
return F_Gen_dbind(F_Gen_dcases(a0, a1, a2, a3, a4, a5), mk_clo(L1589, 4, 3, (V[]){a7, FLD(s1586, 1), FLD(s1586, 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcases_dnext(V *a) { (void)a; return F_Gen_dcases_dnext(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S1594(void) { static V c; return STRC(c, "1"); }
static V S1595(void) { static V c; return STRC(c, " && "); }
static V F_Gen_dand(V a0) {
top:;
V s1593 = a0;
if ((s1593) == IMM(0)) {
return S1594();
} else if (TAG(s1593) == 1 && (FLD(s1593, 1)) == IMM(0)) {
return FLD(s1593, 0);
} else if (TAG(s1593) == 1) {
return F_String_dappend(FLD(s1593, 0), F_String_dappend(S1595(), F_Gen_dand(FLD(s1593, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dand(V *a) { (void)a; return F_Gen_dand(a[0]); }
static V F_PatR_dconds(V a0) {
top:;
V v1596 = a0;
return FLD(v1596, 0);
}
static V W_PatR_dconds(V *a) { (void)a; return F_PatR_dconds(a[0]); }
static V F_Gen_dpats(V a0, V a1, V a2, V a3) {
top:;
V s1597 = a1;
V s1598 = a2;
if (TAG(s1597) == 1 && TAG(s1598) == 1) {
{ V t0 = a0; V t1 = FLD(s1597, 1); V t2 = FLD(s1598, 1); V t3 = F_Gen_dpat(a0, FLD(s1597, 0), FLD(s1598, 0), a3); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else {
return a3;
}
}
static V W_Gen_dpats(V *a) { (void)a; return F_Gen_dpats(a[0], a[1], a[2], a[3]); }
static V S1601(void) { static V c; return STRC(c, "s"); }
static V L1604(V *a) {
return F_Gen_dpure(F_Gen_dscrs_dput(a[1], a[0], a[2]));
}
static V L1603(V *a) {
return F_Gen_dbind(F_Gen_dscrs(a[3], a[2], a[1]), mk_clo(L1604, 3, 2, (V[]){a[4], a[0]}));
}
static V L1602(V *a) {
return F_Gen_dbind(F_Gen_dexpr(a[3], a[2], a[1]), mk_clo(L1603, 5, 4, (V[]){a[4], a[0], a[2], a[3]}));
}
static V L1600(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1601(), F_U32_dshow(a[4]))), mk_clo(L1602, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Gen_dscrs(V a0, V a1, V a2) {
top:;
V s1599 = a2;
if ((s1599) == IMM(0)) {
return F_Gen_dpure(C2(0, IMM(0), IMM(0)));
} else if (TAG(s1599) == 1) {
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1600, 5, 4, (V[]){FLD(s1599, 1), FLD(s1599, 0), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dscrs(V *a) { (void)a; return F_Gen_dscrs(a[0], a[1], a[2]); }
static V S1606(void) { static V c; return STRC(c, "V "); }
static V S1607(void) { static V c; return STRC(c, " = "); }
static V S1608(void) { static V c; return STRC(c, ";\012"); }
static V F_Gen_dscrs_dput(V a0, V a1, V a2) {
top:;
V v1605 = a2;
return C2(0, C2(1, a0, FLD(v1605, 0)), F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1606(), F_String_dappend(a0, S1607()))), C2(1, a1, C2(1, C1(1, S1608()), C2(1, FLD(v1605, 1), IMM(0)))))));
}
static V W_Gen_dscrs_dput(V *a) { (void)a; return F_Gen_dscrs_dput(a[0], a[1], a[2]); }
static V S1610(void) { static V c; return STRC(c, "_"); }
static V S1611(void) { static V c; return STRC(c, "%par"); }
static V F_Gen_dlet(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1609 = a4;
if (TAG(s1609) == 0) {
return F_Gen_dlet_dvar(a0, a1, a2, a3, FLD(s1609, 0), a5, a6, F_Str_deq(FLD(s1609, 0), S1610()));
} else if (TAG(s1609) == 1) {
return F_Gen_dlet_dctor(a0, a1, a2, a3, FLD(s1609, 0), FLD(s1609, 1), a5, a6, F_Str_deq(FLD(s1609, 0), S1611()));
} else {
return F_Gen_dlet_dpat(a0, a1, a2, a3, s1609, a5, a6);
}
}
static V W_Gen_dlet(V *a) { (void)a; return F_Gen_dlet(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S1613(void) { static V c; return STRC(c, "v"); }
static V S1618(void) { static V c; return STRC(c, "V "); }
static V S1619(void) { static V c; return STRC(c, " = "); }
static V S1620(void) { static V c; return STRC(c, ";\012"); }
static V L1617(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1618(), F_String_dappend(a[1], S1619()))), C2(1, a[0], C2(1, C1(1, S1620()), C2(1, a[2], IMM(0)))))));
}
static V L1616(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[6], F_List_dappend(a[7], a[5]), a[4], a[3], a[2]), mk_clo(L1617, 3, 2, (V[]){a[0], a[1]}));
}
static V L1615(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_PatR_dbinds(F_Gen_dpat(a[6], a[5], a[4], C2(0, IMM(0), IMM(0))))), mk_clo(L1616, 8, 7, (V[]){a[7], a[4], a[0], a[1], a[2], a[3], a[6]}));
}
static V L1614(V *a) {
return F_Gen_dbind(F_Gen_dexpr(a[6], a[5], a[4]), mk_clo(L1615, 8, 7, (V[]){a[0], a[1], a[2], a[5], a[7], a[3], a[6]}));
}
static V L1612(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1613(), F_U32_dshow(a[7]))), mk_clo(L1614, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V F_Gen_dlet_dpat(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1612, 8, 7, (V[]){a6, a3, a2, a4, a5, a1, a0}));
}
static V W_Gen_dlet_dpat(V *a) { (void)a; return F_Gen_dlet_dpat(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Gen_dlet_dctor(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s1621 = a8;
if ((s1621) == IMM(1)) {
return F_Gen_dlet_dpar(a0, a1, a2, a3, a5, a6, a7);
} else if ((s1621) == IMM(0)) {
return F_Gen_dlet_dpat(a0, a1, a2, a3, C2(1, a4, a5), a6, a7);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dlet_dctor(V *a) { (void)a; return F_Gen_dlet_dctor(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Gen_dlet_dpar(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1622 = a5;
if (TAG(s1622) == 6) {
return F_Gen_dpar(a0, a1, a2, a3, a4, FLD(s1622, 1), a6);
} else {
return F_Gen_dpar(a0, a1, a2, a3, a4, C2(1, s1622, IMM(0)), a6);
}
}
static V W_Gen_dlet_dpar(V *a) { (void)a; return F_Gen_dlet_dpar(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V L1625(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V L1624(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[6], F_Gen_dpar_denv(a[5], a[4], 0u, a[3]), a[2], a[1], a[0]), mk_clo(L1625, 2, 1, (V[]){a[7]}));
}
static V L1623(V *a) {
return F_Gen_dbind(F_Gen_dpar_dvals(a[6], a[5], a[7], 0u, a[4]), mk_clo(L1624, 8, 7, (V[]){a[0], a[1], a[2], a[5], a[7], a[3], a[6]}));
}
static V F_Gen_dpar(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1623, 8, 7, (V[]){a6, a3, a2, a4, a5, a1, a0}));
}
static V W_Gen_dpar(V *a) { (void)a; return F_Gen_dpar(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S1627(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dpar_denv(V a0, V a1, V a2, V a3) {
top:;
V s1626 = a0;
if ((s1626) == IMM(0)) {
return a3;
} else if (TAG(s1626) == 1 && TAG(FLD(s1626, 0)) == 0) {
{ V t0 = FLD(s1626, 1); V t1 = a1; V t2 = F_U32_dinc(a2); V t3 = F_Bool_dpick(F_Str_deq(FLD(FLD(s1626, 0), 0), S1627()), a3, C2(1, C2(0, FLD(FLD(s1626, 0), 0), F_Gen_dpar_dname(a1, a2)), a3)); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1626) == 1) {
{ V t0 = FLD(s1626, 1); V t1 = a1; V t2 = F_U32_dinc(a2); V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpar_denv(V *a) { (void)a; return F_Gen_dpar_denv(a[0], a[1], a[2], a[3]); }
static V S1628(void) { static V c; return STRC(c, "p"); }
static V S1629(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dpar_dname(V a0, V a1) {
top:;
return F_String_dappend(S1628(), F_String_dappend(F_U32_dshow(a0), F_String_dappend(S1629(), F_U32_dshow(a1))));
}
static V W_Gen_dpar_dname(V *a) { (void)a; return F_Gen_dpar_dname(a[0], a[1]); }
static V S1632(void) { static V c; return STRC(c, "V "); }
static V S1633(void) { static V c; return STRC(c, " = "); }
static V S1634(void) { static V c; return STRC(c, ";\012"); }
static V L1631(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1632(), F_String_dappend(F_Gen_dpar_dname(a[1], a[0]), S1633()))), C2(1, a[2], C2(1, C1(1, S1634()), IMM(0))))));
}
static V S1635(void) { static V c; return STRC(c, "_"); }
static V S1638(void) { static V c; return STRC(c, "V "); }
static V S1639(void) { static V c; return STRC(c, "t = par_fork("); }
static V S1640(void) { static V c; return STRC(c, ");\012"); }
static V S1641(void) { static V c; return STRC(c, "V "); }
static V S1642(void) { static V c; return STRC(c, " = par_join("); }
static V S1643(void) { static V c; return STRC(c, "t);\012"); }
static V L1637(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1638(), F_String_dappend(F_Gen_dpar_dname(a[2], a[1]), S1639()))), C2(1, a[0], C2(1, C1(1, S1640()), C2(1, a[3], C2(1, C1(1, F_String_dappend(S1641(), F_String_dappend(F_Gen_dpar_dname(a[2], a[1]), F_String_dappend(S1642(), F_String_dappend(F_Gen_dpar_dname(a[2], a[1]), S1643()))))), IMM(0))))))));
}
static V L1636(V *a) {
return F_Gen_dbind(F_Gen_dpar_dvals(a[4], a[3], a[2], F_U32_dinc(a[1]), a[0]), mk_clo(L1637, 4, 3, (V[]){a[5], a[1], a[2]}));
}
static V F_Gen_dpar_dvals(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1630 = a4;
if ((s1630) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1630) == 1 && (FLD(s1630, 1)) == IMM(0)) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, FLD(s1630, 0)), mk_clo(L1631, 3, 2, (V[]){a3, a2}));
} else if (TAG(s1630) == 1) {
return F_Gen_dbind(F_Gen_dlam(a0, a1, C1(0, S1635()), FLD(s1630, 0)), mk_clo(L1636, 6, 5, (V[]){FLD(s1630, 1), a3, a2, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpar_dvals(V *a) { (void)a; return F_Gen_dpar_dvals(a[0], a[1], a[2], a[3], a[4]); }
static V S1647(void) { static V c; return STRC(c, "(void)("); }
static V S1648(void) { static V c; return STRC(c, ");\012"); }
static V L1646(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1647()), C2(1, a[0], C2(1, C1(1, S1648()), C2(1, a[1], IMM(0)))))));
}
static V L1645(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[4], a[3], a[2], a[1], a[0]), mk_clo(L1646, 2, 1, (V[]){a[5]}));
}
static V S1650(void) { static V c; return STRC(c, "v"); }
static V S1654(void) { static V c; return STRC(c, "V "); }
static V S1655(void) { static V c; return STRC(c, " = "); }
static V S1656(void) { static V c; return STRC(c, ";\012"); }
static V L1653(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1654(), F_String_dappend(a[1], S1655()))), C2(1, a[0], C2(1, C1(1, S1656()), C2(1, a[2], IMM(0)))))));
}
static V L1652(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[6], C2(1, C2(0, a[5], a[4]), a[3]), a[2], a[1], a[0]), mk_clo(L1653, 3, 2, (V[]){a[7], a[4]}));
}
static V L1651(V *a) {
return F_Gen_dbind(F_Gen_dexpr(a[6], a[5], a[4]), mk_clo(L1652, 8, 7, (V[]){a[0], a[1], a[2], a[5], a[7], a[3], a[6]}));
}
static V L1649(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1650(), F_U32_dshow(a[7]))), mk_clo(L1651, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V F_Gen_dlet_dvar(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s1644 = a7;
if ((s1644) == IMM(1)) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, a5), mk_clo(L1645, 6, 5, (V[]){a6, a3, a2, a1, a0}));
} else if ((s1644) == IMM(0)) {
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1649, 8, 7, (V[]){a6, a3, a2, a4, a5, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dlet_dvar(V *a) { (void)a; return F_Gen_dlet_dvar(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S1658(void) { static V c; return STRC(c, ""); }
static V S1659(void) { static V c; return STRC(c, "#define "); }
static V S1660(void) { static V c; return STRC(c, " ((3u << 16) | "); }
static V S1661(void) { static V c; return STRC(c, "u)\012"); }
static V F_Gen_dcids(V a0, V a1, V a2) {
top:;
V s1657 = a1;
if ((s1657) == IMM(0)) {
return S1658();
} else if (TAG(s1657) == 1 && TAG(FLD(s1657, 0)) == 3) {
return F_String_dappend(F_Gen_dcids_dctors(a0, FLD(FLD(s1657, 0), 2)), F_Gen_dcids(a0, FLD(s1657, 1), a2));
} else if (TAG(s1657) == 1 && TAG(FLD(s1657, 0)) == 1) {
return F_String_dappend(S1659(), F_String_dappend(F_Gen_dcid(FLD(FLD(s1657, 0), 0)), F_String_dappend(S1660(), F_String_dappend(F_U32_dshow(a2), F_String_dappend(S1661(), F_Gen_dcids(a0, FLD(s1657, 1), F_U32_dinc(a2)))))));
} else if (TAG(s1657) == 1) {
{ V t0 = a0; V t1 = FLD(s1657, 1); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcids(V *a) { (void)a; return F_Gen_dcids(a[0], a[1], a[2]); }
static V S1663(void) { static V c; return STRC(c, ""); }
static V F_Gen_dcids_dctors(V a0, V a1) {
top:;
V s1662 = a1;
if ((s1662) == IMM(0)) {
return S1663();
} else if (TAG(s1662) == 1) {
return F_String_dappend(F_Gen_dcids_dkind(FLD(FLD(s1662, 0), 0), F_G_dctor(a0, FLD(FLD(s1662, 0), 0))), F_Gen_dcids_dctors(a0, FLD(s1662, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcids_dctors(V *a) { (void)a; return F_Gen_dcids_dctors(a[0], a[1]); }
static V S1665(void) { static V c; return STRC(c, ""); }
static V F_Gen_dcids_dkind(V a0, V a1) {
top:;
V s1664 = a1;
if ((s1664) == IMM(0)) {
return S1665();
} else if (TAG(s1664) == 1) {
return F_Gen_dcids_dline(a0, F_U32_dto__nat(FLD(FLD(s1664, 0), 2)), FLD(FLD(s1664, 0), 0));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcids_dkind(V *a) { (void)a; return F_Gen_dcids_dkind(a[0], a[1]); }
static V S1667(void) { static V c; return STRC(c, "#define "); }
static V S1668(void) { static V c; return STRC(c, " "); }
static V S1669(void) { static V c; return STRC(c, "u\012"); }
static V S1670(void) { static V c; return STRC(c, "#define "); }
static V S1671(void) { static V c; return STRC(c, " ((1u << 16) | "); }
static V S1672(void) { static V c; return STRC(c, "u)\012"); }
static V S1673(void) { static V c; return STRC(c, "#define "); }
static V S1674(void) { static V c; return STRC(c, " ((2u << 16) | "); }
static V S1675(void) { static V c; return STRC(c, "u)\012"); }
static V S1676(void) { static V c; return STRC(c, ""); }
static V F_Gen_dcids_dline(V a0, V a1, V a2) {
top:;
V s1666 = a1;
if ((s1666) == 0) {
return F_String_dappend(S1667(), F_String_dappend(F_Gen_dcid(a0), F_String_dappend(S1668(), F_String_dappend(F_U32_dshow(a2), S1669()))));
} else if ((s1666) == 1) {
return F_String_dappend(S1670(), F_String_dappend(F_Gen_dcid(a0), F_String_dappend(S1671(), F_String_dappend(F_U32_dshow(a2), S1672()))));
} else if ((s1666) == 2) {
return F_String_dappend(S1673(), F_String_dappend(F_Gen_dcid(a0), F_String_dappend(S1674(), F_String_dappend(F_U32_dshow(a2), S1675()))));
} else {
return S1676();
}
}
static V W_Gen_dcids_dline(V *a) { (void)a; return F_Gen_dcids_dline(a[0], a[1], a[2]); }
static V S1679(void) { static V c; return STRC(c, "#include \042bendrt.h\042\012\012"); }
static V S1680(void) { static V c; return STRC(c, "\012"); }
static V S1681(void) { static V c; return STRC(c, "\012"); }
static V F_Gen_dprogram_dfin(V a0, V a1) {
top:;
V v1677 = a1;
V v1678 = FLD(v1677, 1);
return C4(0, F_String_dappend(a0, S1679()), F_Gen_ddedup(F_List_dreverse(FLD(v1678, 6)), IMM(0)), F_Doc_dflat(F_Doc_dlist(C2(1, FLD(v1678, 1), C2(1, C1(1, S1680()), C2(1, FLD(v1678, 2), C2(1, C1(1, F_String_dappend(S1681(), FLD(v1677, 0))), IMM(0))))))), FLD(v1678, 4));
}
static V W_Gen_dprogram_dfin(V *a) { (void)a; return F_Gen_dprogram_dfin(a[0], a[1]); }
static V F_Doc_dflat(V a0) {
top:;
return F_Doc_dgo(a0, IMM(0));
}
static V W_Doc_dflat(V *a) { (void)a; return F_Doc_dflat(a[0]); }
static V F_Doc_dgo(V a0, V a1) {
top:;
V s1682 = a0;
if ((s1682) == IMM(0)) {
return a1;
} else if (TAG(s1682) == 1) {
return F_String_dappend(FLD(s1682, 0), a1);
} else if (TAG(s1682) == 2) {
{ V t0 = FLD(s1682, 0); V t1 = F_Doc_dgo(FLD(s1682, 1), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dgo(V *a) { (void)a; return F_Doc_dgo(a[0], a[1]); }
static V F_Gen_ddedup(V a0, V a1) {
top:;
V s1683 = a0;
if ((s1683) == IMM(0)) {
return F_List_dreverse(a1);
} else if (TAG(s1683) == 1) {
{ V t0 = FLD(s1683, 1); V t1 = F_Bool_dpick(F_Str_dhas(a1, FLD(s1683, 0)), a1, C2(1, FLD(s1683, 0), a1)); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_ddedup(V *a) { (void)a; return F_Gen_ddedup(a[0], a[1]); }
static V F_G_dnew(V a0) {
top:;
return F_G_dbuild(a0, F_G_dlaws(a0, IMM(0)), C3(0, IMM(0), IMM(0), IMM(0)));
}
static V W_G_dnew(V *a) { (void)a; return F_G_dnew(a[0]); }
static V F_G_dlaws(V a0, V a1) {
top:;
V s1684 = a0;
if ((s1684) == IMM(0)) {
return a1;
} else if (TAG(s1684) == 1 && TAG(FLD(s1684, 0)) == 2) {
{ V t0 = FLD(s1684, 1); V t1 = F_Map_dset(a1, FLD(FLD(s1684, 0), 0), FLD(FLD(s1684, 0), 1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1684) == 1) {
{ V t0 = FLD(s1684, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_G_dlaws(V *a) { (void)a; return F_G_dlaws(a[0], a[1]); }
static V F_G_dbuild(V a0, V a1, V a2) {
top:;
V s1685 = a0;
if ((s1685) == IMM(0)) {
return a2;
} else if (TAG(s1685) == 1) {
{ V t0 = FLD(s1685, 1); V t1 = a1; V t2 = F_G_dadd(FLD(s1685, 0), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_G_dbuild(V *a) { (void)a; return F_G_dbuild(a[0], a[1], a[2]); }
static V F_G_dadd(V a0, V a1, V a2) {
top:;
V s1686 = a0;
if (TAG(s1686) == 3) {
return F_G_dadd_dtype(FLD(s1686, 0), FLD(s1686, 1), FLD(s1686, 2), a2);
} else if (TAG(s1686) == 2) {
return F_G_dadd_dlaw(FLD(s1686, 0), FLD(s1686, 1), a2);
} else if (TAG(s1686) == 0) {
return F_G_dadd_ddef(FLD(s1686, 0), FLD(s1686, 1), FLD(s1686, 2), FLD(s1686, 3), a1, a2);
} else if (TAG(s1686) == 1) {
return F_G_dadd_deff(FLD(s1686, 0), FLD(s1686, 1), FLD(s1686, 2), a2);
} else if (TAG(s1686) == 4) {
return a2;
} else { bend_fail("incomplete match"); }
}
static V W_G_dadd(V *a) { (void)a; return F_G_dadd(a[0], a[1], a[2]); }
static V F_G_dadd_deff(V a0, V a1, V a2, V a3) {
top:;
V v1687 = a3;
return C3(0, FLD(v1687, 0), F_Map_dset(FLD(v1687, 1), a0, C2(0, 1u, F_G_dmask(a1))), F_Map_dset(FLD(v1687, 2), a0, C3(1, a0, a1, a2)));
}
static V W_G_dadd_deff(V *a) { (void)a; return F_G_dadd_deff(a[0], a[1], a[2], a[3]); }
static V F_G_dmask(V a0) {
top:;
V s1688 = a0;
if ((s1688) == IMM(0)) {
return IMM(0);
} else if (TAG(s1688) == 1) {
return C2(1, F_G_dkeep(FLD(s1688, 0)), F_G_dmask(FLD(s1688, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_G_dmask(V *a) { (void)a; return F_G_dmask(a[0]); }
static V F_G_dkeep(V a0) {
top:;
V v1689 = a0;
return F_Bool_dnot(F_Bool_dor(F_Bool_dor(F_U32_dis__eq(FLD(v1689, 1), 1u), F_U32_dis__eq(FLD(v1689, 1), 4u)), F_G_derased__ty(FLD(v1689, 2))));
}
static V W_G_dkeep(V *a) { (void)a; return F_G_dkeep(a[0]); }
static V S1690(void) { static V c; return STRC(c, "Type"); }
static V S1691(void) { static V c; return STRC(c, "Data"); }
static V S1692(void) { static V c; return STRC(c, "Quant"); }
static V S1693(void) { static V c; return STRC(c, "Kind"); }
static V F_G_derased__ty(V a0) {
top:;
return F_Str_dhas(C2(1, S1690(), C2(1, S1691(), C2(1, S1692(), C2(1, S1693(), IMM(0))))), a0);
}
static V W_G_derased__ty(V *a) { (void)a; return F_G_derased__ty(a[0]); }
static V F_G_dadd_ddef(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v1694 = a5;
return C3(0, FLD(v1694, 0), F_Map_dset(FLD(v1694, 1), a0, C2(0, F_Bool_dpick(F_G_dis__native(a0), 2u, 0u), F_G_dmask(F_G_dparams(a4, a0, a1)))), F_Map_dset(FLD(v1694, 2), a0, C4(0, a0, a1, a2, a3)));
}
static V W_G_dadd_ddef(V *a) { (void)a; return F_G_dadd_ddef(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_G_dparams(V a0, V a1, V a2) {
top:;
return F_G_dparams_dgo(F_G_dget(IMM(0), a0, a1), a2);
}
static V W_G_dparams(V *a) { (void)a; return F_G_dparams(a[0], a[1], a[2]); }
static V F_G_dparams_dgo(V a0, V a1) {
top:;
V s1695 = a0;
if ((s1695) == IMM(0)) {
return a1;
} else if (TAG(s1695) == 1) {
return C2(1, FLD(s1695, 0), FLD(s1695, 1));
} else { bend_fail("incomplete match"); }
}
static V W_G_dparams_dgo(V *a) { (void)a; return F_G_dparams_dgo(a[0], a[1]); }
static V F_G_dis__native(V a0) {
top:;
return F_Str_dhas(F_Natives(), a0);
}
static V W_G_dis__native(V *a) { (void)a; return F_G_dis__native(a[0]); }
static V S1696(void) { static V c; return STRC(c, "U32.inc"); }
static V S1697(void) { static V c; return STRC(c, "U32.add"); }
static V S1698(void) { static V c; return STRC(c, "U32.sub"); }
static V S1699(void) { static V c; return STRC(c, "U32.mul"); }
static V S1700(void) { static V c; return STRC(c, "U32.div"); }
static V S1701(void) { static V c; return STRC(c, "U32.mod"); }
static V S1702(void) { static V c; return STRC(c, "U32.not"); }
static V S1703(void) { static V c; return STRC(c, "U32.and"); }
static V S1704(void) { static V c; return STRC(c, "U32.or"); }
static V S1705(void) { static V c; return STRC(c, "U32.xor"); }
static V S1706(void) { static V c; return STRC(c, "U32.shl"); }
static V S1707(void) { static V c; return STRC(c, "U32.shr"); }
static V S1708(void) { static V c; return STRC(c, "U32.shln"); }
static V S1709(void) { static V c; return STRC(c, "U32.shrn"); }
static V S1710(void) { static V c; return STRC(c, "U32.cmp"); }
static V S1711(void) { static V c; return STRC(c, "U32.is_eq"); }
static V S1712(void) { static V c; return STRC(c, "U32.is_ne"); }
static V S1713(void) { static V c; return STRC(c, "U32.is_lt"); }
static V S1714(void) { static V c; return STRC(c, "U32.is_le"); }
static V S1715(void) { static V c; return STRC(c, "U32.is_gt"); }
static V S1716(void) { static V c; return STRC(c, "U32.is_ge"); }
static V S1717(void) { static V c; return STRC(c, "U32.is_zero"); }
static V S1718(void) { static V c; return STRC(c, "U32.is_even"); }
static V S1719(void) { static V c; return STRC(c, "U32.to_nat"); }
static V S1720(void) { static V c; return STRC(c, "U32.from_nat"); }
static V S1721(void) { static V c; return STRC(c, "U32.min"); }
static V S1722(void) { static V c; return STRC(c, "U32.max"); }
static V S1723(void) { static V c; return STRC(c, "U32.pow"); }
static V S1724(void) { static V c; return STRC(c, "U32.log2"); }
static V S1725(void) { static V c; return STRC(c, "U32.to_f32"); }
static V S1726(void) { static V c; return STRC(c, "Nat.double"); }
static V S1727(void) { static V c; return STRC(c, "Nat.add"); }
static V S1728(void) { static V c; return STRC(c, "Nat.sub"); }
static V S1729(void) { static V c; return STRC(c, "Nat.mul"); }
static V S1730(void) { static V c; return STRC(c, "Nat.divmod"); }
static V S1731(void) { static V c; return STRC(c, "Nat.div"); }
static V S1732(void) { static V c; return STRC(c, "Nat.mod"); }
static V S1733(void) { static V c; return STRC(c, "Nat.cmp"); }
static V S1734(void) { static V c; return STRC(c, "Nat.is_eq"); }
static V S1735(void) { static V c; return STRC(c, "Nat.is_ne"); }
static V S1736(void) { static V c; return STRC(c, "Nat.is_lt"); }
static V S1737(void) { static V c; return STRC(c, "Nat.is_le"); }
static V S1738(void) { static V c; return STRC(c, "Nat.is_gt"); }
static V S1739(void) { static V c; return STRC(c, "Nat.is_ge"); }
static V S1740(void) { static V c; return STRC(c, "Nat.min"); }
static V S1741(void) { static V c; return STRC(c, "Nat.max"); }
static V S1742(void) { static V c; return STRC(c, "Nat.pow"); }
static V S1743(void) { static V c; return STRC(c, "Nat.show"); }
static V S1744(void) { static V c; return STRC(c, "F32.add"); }
static V S1745(void) { static V c; return STRC(c, "F32.sub"); }
static V S1746(void) { static V c; return STRC(c, "F32.mul"); }
static V S1747(void) { static V c; return STRC(c, "F32.div"); }
static V S1748(void) { static V c; return STRC(c, "F32.mod"); }
static V S1749(void) { static V c; return STRC(c, "F32.pow"); }
static V S1750(void) { static V c; return STRC(c, "F32.atan2"); }
static V S1751(void) { static V c; return STRC(c, "F32.is_eq"); }
static V S1752(void) { static V c; return STRC(c, "F32.is_ne"); }
static V S1753(void) { static V c; return STRC(c, "F32.is_lt"); }
static V S1754(void) { static V c; return STRC(c, "F32.is_le"); }
static V S1755(void) { static V c; return STRC(c, "F32.is_gt"); }
static V S1756(void) { static V c; return STRC(c, "F32.is_ge"); }
static V S1757(void) { static V c; return STRC(c, "F32.neg"); }
static V S1758(void) { static V c; return STRC(c, "F32.abs"); }
static V S1759(void) { static V c; return STRC(c, "F32.sqrt"); }
static V S1760(void) { static V c; return STRC(c, "F32.exp"); }
static V S1761(void) { static V c; return STRC(c, "F32.log"); }
static V S1762(void) { static V c; return STRC(c, "F32.log2"); }
static V S1763(void) { static V c; return STRC(c, "F32.log10"); }
static V S1764(void) { static V c; return STRC(c, "F32.sin"); }
static V S1765(void) { static V c; return STRC(c, "F32.cos"); }
static V S1766(void) { static V c; return STRC(c, "F32.tan"); }
static V S1767(void) { static V c; return STRC(c, "F32.asin"); }
static V S1768(void) { static V c; return STRC(c, "F32.acos"); }
static V S1769(void) { static V c; return STRC(c, "F32.atan"); }
static V S1770(void) { static V c; return STRC(c, "F32.sinh"); }
static V S1771(void) { static V c; return STRC(c, "F32.cosh"); }
static V S1772(void) { static V c; return STRC(c, "F32.tanh"); }
static V S1773(void) { static V c; return STRC(c, "F32.floor"); }
static V S1774(void) { static V c; return STRC(c, "F32.ceil"); }
static V S1775(void) { static V c; return STRC(c, "F32.trunc"); }
static V S1776(void) { static V c; return STRC(c, "F32.bits"); }
static V S1777(void) { static V c; return STRC(c, "F32.to_u32"); }
static V S1778(void) { static V c; return STRC(c, "F32.show"); }
static V S1779(void) { static V c; return STRC(c, "F32.read"); }
static V F_Natives(void) {
top:;
return C2(1, S1696(), C2(1, S1697(), C2(1, S1698(), C2(1, S1699(), C2(1, S1700(), C2(1, S1701(), C2(1, S1702(), C2(1, S1703(), C2(1, S1704(), C2(1, S1705(), C2(1, S1706(), C2(1, S1707(), C2(1, S1708(), C2(1, S1709(), C2(1, S1710(), C2(1, S1711(), C2(1, S1712(), C2(1, S1713(), C2(1, S1714(), C2(1, S1715(), C2(1, S1716(), C2(1, S1717(), C2(1, S1718(), C2(1, S1719(), C2(1, S1720(), C2(1, S1721(), C2(1, S1722(), C2(1, S1723(), C2(1, S1724(), C2(1, S1725(), C2(1, S1726(), C2(1, S1727(), C2(1, S1728(), C2(1, S1729(), C2(1, S1730(), C2(1, S1731(), C2(1, S1732(), C2(1, S1733(), C2(1, S1734(), C2(1, S1735(), C2(1, S1736(), C2(1, S1737(), C2(1, S1738(), C2(1, S1739(), C2(1, S1740(), C2(1, S1741(), C2(1, S1742(), C2(1, S1743(), C2(1, S1744(), C2(1, S1745(), C2(1, S1746(), C2(1, S1747(), C2(1, S1748(), C2(1, S1749(), C2(1, S1750(), C2(1, S1751(), C2(1, S1752(), C2(1, S1753(), C2(1, S1754(), C2(1, S1755(), C2(1, S1756(), C2(1, S1757(), C2(1, S1758(), C2(1, S1759(), C2(1, S1760(), C2(1, S1761(), C2(1, S1762(), C2(1, S1763(), C2(1, S1764(), C2(1, S1765(), C2(1, S1766(), C2(1, S1767(), C2(1, S1768(), C2(1, S1769(), C2(1, S1770(), C2(1, S1771(), C2(1, S1772(), C2(1, S1773(), C2(1, S1774(), C2(1, S1775(), C2(1, S1776(), C2(1, S1777(), C2(1, S1778(), C2(1, S1779(), IMM(0)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
}
static V W_Natives(V *a) { (void)a; return F_Natives(); }
static V F_G_dadd_dlaw(V a0, V a1, V a2) {
top:;
V v1780 = a2;
return C3(0, FLD(v1780, 0), F_Map_dset(FLD(v1780, 1), a0, C2(0, F_Bool_dpick(F_G_dis__native(a0), 2u, 3u), F_G_dmask(a1))), FLD(v1780, 2));
}
static V W_G_dadd_dlaw(V *a) { (void)a; return F_G_dadd_dlaw(a[0], a[1], a[2]); }
static V S1783(void) { static V c; return STRC(c, "%"); }
static V F_G_dadd_dtype(V a0, V a1, V a2, V a3) {
top:;
V v1781 = a3;
V v1782 = F_U32_dfrom__nat(F_List_dlength(a2));
return C3(0, F_G_dctors(a0, a2, 0u, v1782, FLD(v1781, 0)), F_Map_dset(FLD(v1781, 1), a0, C2(0, 3u, IMM(0))), F_Map_dset(FLD(v1781, 2), F_String_dappend(S1783(), a0), C3(3, a0, a1, a2)));
}
static V W_G_dadd_dtype(V *a) { (void)a; return F_G_dadd_dtype(a[0], a[1], a[2], a[3]); }
static V F_G_dctors(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1784 = a1;
if ((s1784) == IMM(0)) {
return a4;
} else if (TAG(s1784) == 1) {
V v1785 = F_U32_dfrom__nat(F_List_dlength(FLD(FLD(s1784, 0), 1)));
{ V t0 = a0; V t1 = FLD(s1784, 1); V t2 = F_U32_dinc(a2); V t3 = a3; V t4 = F_Map_dset(a4, FLD(FLD(s1784, 0), 0), C4(0, a2, v1785, F_G_dctor__kind(a0, FLD(FLD(s1784, 0), 0), a3, v1785), F_U32_dis__eq(a3, 1u))); a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_G_dctors(V *a) { (void)a; return F_G_dctors(a[0], a[1], a[2], a[3], a[4]); }
static V S1786(void) { static V c; return STRC(c, "Nat"); }
static V S1787(void) { static V c; return STRC(c, "Zero"); }
static V F_G_dctor__kind(V a0, V a1, V a2, V a3) {
top:;
return F_Bool_dpick(F_Str_deq(a0, S1786()), F_Bool_dpick(F_Str_deq(a1, S1787()), 3u, 4u), F_Bool_dpick(F_Bool_dand(F_U32_dis__eq(a2, 1u), F_U32_dis__eq(a3, 1u)), 2u, F_Bool_dpick(F_U32_dis__zero(a3), 1u, 0u)));
}
static V W_G_dctor__kind(V *a) { (void)a; return F_G_dctor__kind(a[0], a[1], a[2], a[3]); }
static V S1790(void) { static V c; return STRC(c, "\012"); }
static V S1792(void) { static V c; return STRC(c, "bendc: compilation failed"); }
static V L1791(V *a) {
return F_IO_ddie(1u, S1792());
}
static V F_Main_demit(V a0) {
top:;
V v1788 = a0;
V s1789 = FLD(v1788, 3);
if ((s1789) == IMM(0)) {
return F_Main_demit_dok(FLD(v1788, 0), FLD(v1788, 1), FLD(v1788, 2));
} else if (TAG(s1789) == 1) {
return F_IO_dbind(F_IO_dprint__err(F_String_djoin(F_List_dreverse(C2(1, FLD(s1789, 0), FLD(s1789, 1))), S1790())), mk_clo(L1791, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Main_demit(V *a) { (void)a; return F_Main_demit(a[0]); }
static V E_IO_dprint__err(V *a) { return io_req(CID_IO_PRINT_ERR, 2, (V[]){a[0], a[2]}); }
static V F_IO_dprint__err(V a0) { return mk_clo(E_IO_dprint__err, 3, 1, (V[]){a0}); }
static V W_IO_dprint__err(V *a) { (void)a; return F_IO_dprint__err(a[0]); }
static V L1795(V *a) {
return apply(apply(apply(a[2], a[3]), a[1]), a[0]);
}
static V L1794(V *a) {
return apply(apply(a[2], a[1]), mk_clo(L1795, 4, 3, (V[]){a[3], a[1], a[0]}));
}
static V L1793(V *a) {
return mk_clo(L1794, 4, 3, (V[]){a[0], a[2], a[1]});
}
static V F_IO_dbind(V a2, V a3) {
top:;
return mk_clo(L1793, 3, 2, (V[]){a3, a2});
}
static V W_IO_dbind(V *a) { (void)a; return F_IO_dbind(a[2], a[3]); }
static V S1796(void) { static V c; return STRC(c, ""); }
static V L1797(V *a) {
return F_IO_dwrite(F_String_dappend(a[1], F_String_dappend(a[2], a[0])));
}
static V F_Main_demit_dok(V a0, V a1, V a2) {
top:;
return F_IO_dbind(F_Main_deffs(a1, S1796()), mk_clo(L1797, 3, 2, (V[]){a2, a0}));
}
static V W_Main_demit_dok(V *a) { (void)a; return F_Main_demit_dok(a[0], a[1], a[2]); }
static V E_IO_dwrite(V *a) { return io_req(CID_IO_WRITE, 2, (V[]){a[0], a[2]}); }
static V F_IO_dwrite(V a0) { return mk_clo(E_IO_dwrite, 3, 1, (V[]){a0}); }
static V W_IO_dwrite(V *a) { (void)a; return F_IO_dwrite(a[0]); }
static V S1800(void) { static V c; return STRC(c, "\012"); }
static V L1799(V *a) {
return F_Main_deffs(a[1], F_String_dappend(a[0], F_String_dappend(a[2], S1800())));
}
static V F_Main_deffs(V a0, V a1) {
top:;
V s1798 = a0;
if ((s1798) == IMM(0)) {
return F_IO_dpure(a1);
} else if (TAG(s1798) == 1) {
return F_IO_dbind(F_IO_dread__file(FLD(s1798, 0)), mk_clo(L1799, 3, 2, (V[]){a1, FLD(s1798, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_deffs(V *a) { (void)a; return F_Main_deffs(a[0], a[1]); }
static V S1801(void) { static V c; return STRC(c, "r"); }
static V L1803(V *a) {
return F_IO_dread__fin(a[0]);
}
static V L1802(V *a) {
return F_IO_dbind(F_IO_dread__all(a[0]), mk_clo(L1803, 1, 0, 0));
}
static V F_IO_dread__file(V a0) {
top:;
return F_IO_dbind(F_IO_dtry(F_File_dopen(a0, S1801())), mk_clo(L1802, 1, 0, 0));
}
static V W_IO_dread__file(V *a) { (void)a; return F_IO_dread__file(a[0]); }
static V L1805(V *a) {
return F_IO_dpass(a[0]);
}
static V F_IO_dread__fin(V a0) {
top:;
V v1804 = a0;
return F_IO_dbind(F_File_dclose(FLD(v1804, 0)), mk_clo(L1805, 2, 1, (V[]){FLD(v1804, 1)}));
}
static V W_IO_dread__fin(V *a) { (void)a; return F_IO_dread__fin(a[0]); }
static V F_IO_dpass(V a1) {
top:;
V s1806 = a1;
if (TAG(s1806) == 1) {
return F_IO_dpure(FLD(s1806, 0));
} else if (TAG(s1806) == 0) {
return F_IO_ddie(FLD(FLD(s1806, 0), 0), FLD(FLD(s1806, 0), 1));
} else { bend_fail("incomplete match"); }
}
static V W_IO_dpass(V *a) { (void)a; return F_IO_dpass(a[1]); }
static V L1808(V *a) {
return apply(a[1], a[0]);
}
static V L1807(V *a) {
return mk_clo(L1808, 2, 1, (V[]){a[0]});
}
static V F_IO_dpure(V a1) {
top:;
return mk_clo(L1807, 2, 1, (V[]){a1});
}
static V W_IO_dpure(V *a) { (void)a; return F_IO_dpure(a[1]); }
static V E_File_dclose(V *a) { return io_req(CID_FILE_CLOSE, 2, (V[]){a[0], a[2]}); }
static V F_File_dclose(V a0) { return mk_clo(E_File_dclose, 3, 1, (V[]){a0}); }
static V W_File_dclose(V *a) { (void)a; return F_File_dclose(a[0]); }
static V L1809(V *a) {
return F_IO_dread__sized(a[0]);
}
static V F_IO_dread__all(V a0) {
top:;
return F_IO_dbind(F_File_dsize(a0), mk_clo(L1809, 1, 0, 0));
}
static V W_IO_dread__all(V *a) { (void)a; return F_IO_dread__all(a[0]); }
static V F_IO_dread__sized(V a0) {
top:;
V v1810 = a0;
V s1811 = FLD(v1810, 1);
if (TAG(s1811) == 1) {
return F_File_dread(FLD(v1810, 0), F_U32_dinc(FLD(s1811, 0)));
} else if (TAG(s1811) == 0) {
return F_File_dread(FLD(v1810, 0), 2000000000u);
} else { bend_fail("incomplete match"); }
}
static V W_IO_dread__sized(V *a) { (void)a; return F_IO_dread__sized(a[0]); }
static V E_File_dread(V *a) { return io_req(CID_FILE_READ, 3, (V[]){a[0], a[1], a[3]}); }
static V F_File_dread(V a0, V a1) { return mk_clo(E_File_dread, 4, 2, (V[]){a0, a1}); }
static V W_File_dread(V *a) { (void)a; return F_File_dread(a[0], a[1]); }
static V E_File_dsize(V *a) { return io_req(CID_FILE_SIZE, 2, (V[]){a[0], a[2]}); }
static V F_File_dsize(V a0) { return mk_clo(E_File_dsize, 3, 1, (V[]){a0}); }
static V W_File_dsize(V *a) { (void)a; return F_File_dsize(a[0]); }
static V E_File_dopen(V *a) { return io_req(CID_FILE_OPEN, 3, (V[]){a[0], a[1], a[3]}); }
static V F_File_dopen(V a0, V a1) { return mk_clo(E_File_dopen, 4, 2, (V[]){a0, a1}); }
static V W_File_dopen(V *a) { (void)a; return F_File_dopen(a[0], a[1]); }
static V F_IO_dtry(V a1) {
top:;
return F_IO_dbind(a1, mk_clo(W_IO_dpass, 2, 1, (V[]){0}));
}
static V W_IO_dtry(V *a) { (void)a; return F_IO_dtry(a[1]); }
static V S1813(void) { static V c; return STRC(c, "bendc: imports nested too deeply at "); }
static V L1814(V *a) {
return F_Main_dload_dparsed(a[1], F_Mod_ddir(a[0]), a[0], F_Main_dparse(a[2]));
}
static V F_Main_dload(V a0, V a1) {
top:;
V s1812 = a0;
if ((s1812) == 0) {
return F_IO_ddie(1u, F_String_dappend(S1813(), a1));
} else if (nat_ge(s1812, 1)) {
return F_IO_dbind(F_IO_dread__file(a1), mk_clo(L1814, 3, 2, (V[]){a1, nat_subk(s1812, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dload(V *a) { (void)a; return F_Main_dload(a[0], a[1]); }
static V S1816(void) { static V c; return STRC(c, "bendc: parse error in "); }
static V S1817(void) { static V c; return STRC(c, ": "); }
static V L1818(V *a) {
return F_IO_dpure(F_List_dappend(a[2], F_Eff_ddecls(a[1], a[0])));
}
static V F_Main_dload_dparsed(V a0, V a1, V a2, V a3) {
top:;
V s1815 = a3;
if (TAG(s1815) == 0) {
return F_IO_ddie(1u, F_String_dappend(S1816(), F_String_dappend(a2, F_String_dappend(S1817(), FLD(s1815, 0)))));
} else if (TAG(s1815) == 1) {
return F_IO_dbind(F_Main_dimports(a0, a1, FLD(s1815, 0)), mk_clo(L1818, 3, 2, (V[]){FLD(s1815, 0), a1}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dload_dparsed(V *a) { (void)a; return F_Main_dload_dparsed(a[0], a[1], a[2], a[3]); }
static V S1820(void) { static V c; return STRC(c, "Base"); }
static V F_Main_dimports(V a0, V a1, V a2) {
top:;
V s1819 = a2;
if ((s1819) == IMM(0)) {
return F_IO_dpure(IMM(0));
} else if (TAG(s1819) == 1 && TAG(FLD(s1819, 0)) == 4) {
return F_Main_dimports_done(a0, a1, FLD(FLD(s1819, 0), 0), FLD(FLD(s1819, 0), 1), FLD(s1819, 1), F_Str_deq(FLD(FLD(s1819, 0), 0), S1820()));
} else if (TAG(s1819) == 1) {
{ V t0 = a0; V t1 = a1; V t2 = FLD(s1819, 1); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Main_dimports(V *a) { (void)a; return F_Main_dimports(a[0], a[1], a[2]); }
static V S1822(void) { static V c; return STRC(c, "0x"); }
static V L1824(V *a) {
return F_IO_dpure(F_List_dappend(F_Mod_dqualify(a[1], a[0]), a[2]));
}
static V L1823(V *a) {
return F_IO_dbind(F_Main_dimports(a[3], a[2], a[1]), mk_clo(L1824, 3, 2, (V[]){a[4], a[0]}));
}
static V F_Main_dimports_done(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1821 = a5;
if ((s1821) == IMM(1)) {
return F_Main_dimports(a0, a1, a4);
} else if ((s1821) == IMM(0)) {
return F_IO_dbind(F_Main_dload_dimport(a0, a1, a2, F_String_dstarts__with(a2, S1822())), mk_clo(L1823, 5, 4, (V[]){a3, a4, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dimports_done(V *a) { (void)a; return F_Main_dimports_done(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Mod_dqualify(V a0, V a1) {
top:;
return F_Mod_ddecls(C2(0, a0, F_Mod_dnames(a1, IMM(0))), a1);
}
static V W_Mod_dqualify(V *a) { (void)a; return F_Mod_dqualify(a[0], a[1]); }
static V F_Mod_dnames(V a0, V a1) {
top:;
V s1825 = a0;
if ((s1825) == IMM(0)) {
return a1;
} else if (TAG(s1825) == 1 && TAG(FLD(s1825, 0)) == 0) {
{ V t0 = FLD(s1825, 1); V t1 = C2(1, FLD(FLD(s1825, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1825) == 1 && TAG(FLD(s1825, 0)) == 1) {
{ V t0 = FLD(s1825, 1); V t1 = C2(1, FLD(FLD(s1825, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1825) == 1 && TAG(FLD(s1825, 0)) == 2) {
{ V t0 = FLD(s1825, 1); V t1 = C2(1, FLD(FLD(s1825, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1825) == 1 && TAG(FLD(s1825, 0)) == 3) {
{ V t0 = FLD(s1825, 1); V t1 = C2(1, FLD(FLD(s1825, 0), 0), F_Mod_dctor__names(FLD(FLD(s1825, 0), 2), a1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1825) == 1 && TAG(FLD(s1825, 0)) == 4) {
{ V t0 = FLD(s1825, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dnames(V *a) { (void)a; return F_Mod_dnames(a[0], a[1]); }
static V F_Mod_dctor__names(V a0, V a1) {
top:;
V s1826 = a0;
if ((s1826) == IMM(0)) {
return a1;
} else if (TAG(s1826) == 1) {
{ V t0 = FLD(s1826, 1); V t1 = C2(1, FLD(FLD(s1826, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dctor__names(V *a) { (void)a; return F_Mod_dctor__names(a[0], a[1]); }
static V F_Mod_ddecls(V a0, V a1) {
top:;
V s1827 = a1;
if ((s1827) == IMM(0)) {
return IMM(0);
} else if (TAG(s1827) == 1) {
return C2(1, F_Mod_ddecl(a0, FLD(s1827, 0)), F_Mod_ddecls(a0, FLD(s1827, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddecls(V *a) { (void)a; return F_Mod_ddecls(a[0], a[1]); }
static V F_Mod_ddecl(V a0, V a1) {
top:;
V s1828 = a1;
if (TAG(s1828) == 0) {
return C4(0, F_Mod_dq(a0, FLD(s1828, 0)), FLD(s1828, 1), F_Mod_dexpr(a0, F_Mod_dparam__names(FLD(s1828, 1)), FLD(s1828, 2)), F_Mod_dexpr(a0, IMM(0), FLD(s1828, 3)));
} else if (TAG(s1828) == 1) {
return C3(1, F_Mod_dq(a0, FLD(s1828, 0)), FLD(s1828, 1), FLD(s1828, 2));
} else if (TAG(s1828) == 2) {
return C2(2, F_Mod_dq(a0, FLD(s1828, 0)), FLD(s1828, 1));
} else if (TAG(s1828) == 3) {
return C3(3, F_Mod_dq(a0, FLD(s1828, 0)), FLD(s1828, 1), F_Mod_dctors(a0, FLD(s1828, 2)));
} else if (TAG(s1828) == 4) {
return C2(4, FLD(s1828, 0), FLD(s1828, 1));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddecl(V *a) { (void)a; return F_Mod_ddecl(a[0], a[1]); }
static V F_Mod_dctors(V a0, V a1) {
top:;
V s1829 = a1;
if ((s1829) == IMM(0)) {
return IMM(0);
} else if (TAG(s1829) == 1) {
return C2(1, C2(0, F_Mod_dq(a0, FLD(FLD(s1829, 0), 0)), F_Mod_dfields(a0, FLD(FLD(s1829, 0), 1))), F_Mod_dctors(a0, FLD(s1829, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dctors(V *a) { (void)a; return F_Mod_dctors(a[0], a[1]); }
static V F_Mod_dfields(V a0, V a1) {
top:;
V s1830 = a1;
if ((s1830) == IMM(0)) {
return IMM(0);
} else if (TAG(s1830) == 1) {
return C2(1, C2(0, FLD(FLD(s1830, 0), 0), F_Mod_dexpr(a0, IMM(0), FLD(FLD(s1830, 0), 1))), F_Mod_dfields(a0, FLD(s1830, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dfields(V *a) { (void)a; return F_Mod_dfields(a[0], a[1]); }
static V F_Mod_dexpr(V a0, V a1, V a2) {
top:;
V s1831 = a2;
if (TAG(s1831) == 0) {
return C1(0, F_Mod_dvar(a0, a1, FLD(s1831, 0)));
} else if (TAG(s1831) == 5) {
return C2(5, F_Mod_dexpr(a0, a1, FLD(s1831, 0)), F_Mod_dexprs(a0, a1, FLD(s1831, 1)));
} else if (TAG(s1831) == 6) {
return C2(6, F_Mod_dq(a0, FLD(s1831, 0)), F_Mod_dexprs(a0, a1, FLD(s1831, 1)));
} else if (TAG(s1831) == 7) {
return C2(7, F_Mod_dpat(a0, FLD(s1831, 0)), F_Mod_dexpr(a0, F_Pat_dvars(FLD(s1831, 0), a1), FLD(s1831, 1)));
} else if (TAG(s1831) == 8) {
return C3(8, F_Mod_dpat(a0, FLD(s1831, 0)), F_Mod_dexpr(a0, a1, FLD(s1831, 1)), F_Mod_dexpr(a0, F_Pat_dvars(FLD(s1831, 0), a1), FLD(s1831, 2)));
} else if (TAG(s1831) == 9) {
return C2(9, F_Mod_dexprs(a0, a1, FLD(s1831, 0)), F_Mod_dexprs(a0, a1, FLD(s1831, 1)));
} else if (TAG(s1831) == 10) {
return C2(10, F_Mod_dpats(a0, FLD(s1831, 0)), F_Mod_dexpr(a0, F_Pats_dvars(FLD(s1831, 0), a1), FLD(s1831, 1)));
} else if (TAG(s1831) == 11) {
return C2(11, FLD(s1831, 0), F_Mod_dexpr(a0, a1, FLD(s1831, 1)));
} else if (TAG(s1831) == 12) {
return C3(12, FLD(s1831, 0), F_Mod_dexpr(a0, a1, FLD(s1831, 1)), F_Mod_dexpr(a0, a1, FLD(s1831, 2)));
} else if (TAG(s1831) == 13) {
return C2(13, F_Mod_dexpr(a0, a1, FLD(s1831, 0)), F_Mod_dvar(a0, a1, FLD(s1831, 1)));
} else if (TAG(s1831) == 14) {
return C2(14, F_Mod_dvar(a0, a1, FLD(s1831, 0)), F_Mod_dexprs(a0, a1, FLD(s1831, 1)));
} else {
return s1831;
}
}
static V W_Mod_dexpr(V *a) { (void)a; return F_Mod_dexpr(a[0], a[1], a[2]); }
static V F_Mod_dexprs(V a0, V a1, V a2) {
top:;
V s1832 = a2;
if ((s1832) == IMM(0)) {
return IMM(0);
} else if (TAG(s1832) == 1) {
return C2(1, F_Mod_dexpr(a0, a1, FLD(s1832, 0)), F_Mod_dexprs(a0, a1, FLD(s1832, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dexprs(V *a) { (void)a; return F_Mod_dexprs(a[0], a[1], a[2]); }
static V F_Mod_dvar(V a0, V a1, V a2) {
top:;
return F_Bool_dpick(F_Str_dhas(a1, a2), a2, F_Mod_dq(a0, a2));
}
static V W_Mod_dvar(V *a) { (void)a; return F_Mod_dvar(a[0], a[1], a[2]); }
static V S1834(void) { static V c; return STRC(c, "."); }
static V F_Mod_dq(V a0, V a1) {
top:;
V v1833 = a0;
return F_Bool_dpick(F_Str_dhas(FLD(v1833, 1), a1), F_String_dappend(FLD(v1833, 0), F_String_dappend(S1834(), a1)), a1);
}
static V W_Mod_dq(V *a) { (void)a; return F_Mod_dq(a[0], a[1]); }
static V F_Mod_dpats(V a0, V a1) {
top:;
V s1835 = a1;
if ((s1835) == IMM(0)) {
return IMM(0);
} else if (TAG(s1835) == 1) {
return C2(1, F_Mod_dpat(a0, FLD(s1835, 0)), F_Mod_dpats(a0, FLD(s1835, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dpats(V *a) { (void)a; return F_Mod_dpats(a[0], a[1]); }
static V F_Mod_dpat(V a0, V a1) {
top:;
V s1836 = a1;
if (TAG(s1836) == 1) {
return C2(1, F_Mod_dq(a0, FLD(s1836, 0)), F_Mod_dpats(a0, FLD(s1836, 1)));
} else if (TAG(s1836) == 3) {
return C2(3, FLD(s1836, 0), F_Mod_dpat(a0, FLD(s1836, 1)));
} else {
return s1836;
}
}
static V W_Mod_dpat(V *a) { (void)a; return F_Mod_dpat(a[0], a[1]); }
static V F_Mod_dparam__names(V a0) {
top:;
V s1837 = a0;
if ((s1837) == IMM(0)) {
return IMM(0);
} else if (TAG(s1837) == 1) {
return C2(1, FLD(FLD(s1837, 0), 0), F_Mod_dparam__names(FLD(s1837, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dparam__names(V *a) { (void)a; return F_Mod_dparam__names(a[0]); }
static V F_Main_dload_dimport(V a0, V a1, V a2, V a3) {
top:;
V s1838 = a3;
if ((s1838) == IMM(1)) {
return F_Main_dload_dhub(a0, a2);
} else if ((s1838) == IMM(0)) {
return F_Main_dload(a0, F_Eff_dpath(a1, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dload_dimport(V *a) { (void)a; return F_Main_dload_dimport(a[0], a[1], a[2], a[3]); }
static V S1840(void) { static V c; return STRC(c, "BEND_HUB"); }
static V S1843(void) { static V c; return STRC(c, "/"); }
static V L1842(V *a) {
return F_Main_dload(a[2], F_String_dappend(a[1], F_String_dappend(S1843(), a[0])));
}
static V L1841(V *a) {
return F_IO_dbind(F_IO_dtry(F_Hub_densure(a[2], F_Main_dhub_durl(a[3]), a[1])), mk_clo(L1842, 4, 3, (V[]){a[1], a[2], a[0]}));
}
static V L1839(V *a) {
return F_IO_dbind(F_IO_dget__env(S1840()), mk_clo(L1841, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Main_dload_dhub(V a0, V a1) {
top:;
return F_IO_dbind(F_Main_dlib(), mk_clo(L1839, 3, 2, (V[]){a0, a1}));
}
static V W_Main_dload_dhub(V *a) { (void)a; return F_Main_dload_dhub(a[0], a[1]); }
static V S1845(void) { static V c; return STRC(c, "https://hub.bend-lang.com"); }
static V F_Main_dhub_durl(V a0) {
top:;
V s1844 = a0;
if (TAG(s1844) == 1) {
return FLD(s1844, 0);
} else if (TAG(s1844) == 0) {
return S1845();
} else { bend_fail("incomplete match"); }
}
static V W_Main_dhub_durl(V *a) { (void)a; return F_Main_dhub_durl(a[0]); }
static V E_Hub_densure(V *a) { return io_req(CID_HUB_ENSURE, 4, (V[]){a[0], a[1], a[2], a[4]}); }
static V F_Hub_densure(V a0, V a1, V a2) { return mk_clo(E_Hub_densure, 5, 3, (V[]){a0, a1, a2}); }
static V W_Hub_densure(V *a) { (void)a; return F_Hub_densure(a[0], a[1], a[2]); }
static V E_IO_dget__env(V *a) { return io_req(CID_IO_GET_ENV, 2, (V[]){a[0], a[2]}); }
static V F_IO_dget__env(V a0) { return mk_clo(E_IO_dget__env, 3, 1, (V[]){a0}); }
static V W_IO_dget__env(V *a) { (void)a; return F_IO_dget__env(a[0]); }
static V S1846(void) { static V c; return STRC(c, "BEND_LIB"); }
static V L1847(V *a) {
return F_Main_dlib_dor(a[0]);
}
static V F_Main_dlib(void) {
top:;
return F_IO_dbind(F_IO_dget__env(S1846()), mk_clo(L1847, 1, 0, 0));
}
static V W_Main_dlib(V *a) { (void)a; return F_Main_dlib(); }
static V S1849(void) { static V c; return STRC(c, "HOME"); }
static V S1851(void) { static V c; return STRC(c, "/.bend/lib"); }
static V L1850(V *a) {
return F_IO_dpure(F_String_dappend(a[0], S1851()));
}
static V F_Main_dlib_dor(V a0) {
top:;
V s1848 = a0;
if (TAG(s1848) == 1) {
return F_IO_dpure(FLD(s1848, 0));
} else if (TAG(s1848) == 0) {
return F_IO_dbind(F_IO_dtry(F_IO_dget__env(S1849())), mk_clo(L1850, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dlib_dor(V *a) { (void)a; return F_Main_dlib_dor(a[0]); }
static V F_Chk_dshow__main(V a0) {
top:;
return F_Chk_dshow__main_dgo(a0, F_Chk_dmain__tld(a0));
}
static V W_Chk_dshow__main(V *a) { (void)a; return F_Chk_dshow__main(a[0]); }
static V S1853(void) { static V c; return STRC(c, ""); }
static V F_Chk_dshow__main_dgo(V a0, V a1) {
top:;
V s1852 = a1;
if (TAG(s1852) == 1 && TAG(FLD(s1852, 0)) == 0 && TAG(FLD(FLD(s1852, 0), 3)) == 1) {
return F_Chk_dterm__show(F_Chk_dterm__lower(a0, F_Chk_dterm__snf(a0, FLD(FLD(FLD(s1852, 0), 3), 0)), 0u), 0u, IMM(0));
} else {
return S1853();
}
}
static V W_Chk_dshow__main_dgo(V *a) { (void)a; return F_Chk_dshow__main_dgo(a[0], a[1]); }
static V F_Chk_dterm__show(V a0, V a1, V a2) {
top:;
return F_Chk_dterm__show_dgo(a0, a1, a2, F_List_dlength(a2));
}
static V W_Chk_dterm__show(V *a) { (void)a; return F_Chk_dterm__show(a[0], a[1], a[2]); }
static V S1855(void) { static V c; return STRC(c, "^"); }
static V S1856(void) { static V c; return STRC(c, "^"); }
static V S1857(void) { static V c; return STRC(c, "!"); }
static V S1858(void) { static V c; return STRC(c, ""); }
static V S1862(void) { static V c; return STRC(c, " "); }
static V S1863(void) { static V c; return STRC(c, " = "); }
static V S1864(void) { static V c; return STRC(c, " "); }
static V S1865(void) { static V c; return STRC(c, "; "); }
static V S1866(void) { static V c; return STRC(c, "Quant"); }
static V S1867(void) { static V c; return STRC(c, " <&> "); }
static V S1868(void) { static V c; return STRC(c, "@"); }
static V S1869(void) { static V c; return STRC(c, ":"); }
static V S1870(void) { static V c; return STRC(c, " -> "); }
static V S1871(void) { static V c; return STRC(c, " => "); }
static V S1874(void) { static V c; return STRC(c, ""); }
static V S1875(void) { static V c; return STRC(c, "<"); }
static V S1876(void) { static V c; return STRC(c, ", "); }
static V S1877(void) { static V c; return STRC(c, ">"); }
static V S1878(void) { static V c; return STRC(c, "n"); }
static V S1879(void) { static V c; return STRC(c, "\042"); }
static V S1880(void) { static V c; return STRC(c, "\042"); }
static V S1881(void) { static V c; return STRC(c, "\134{"); }
static V S1882(void) { static V c; return STRC(c, "; "); }
static V S1883(void) { static V c; return STRC(c, "}"); }
static V S1884(void) { static V c; return STRC(c, "\134{}"); }
static V S1885(void) { static V c; return STRC(c, "{"); }
static V S1886(void) { static V c; return STRC(c, " == "); }
static V S1887(void) { static V c; return STRC(c, " : "); }
static V S1888(void) { static V c; return STRC(c, "}"); }
static V S1889(void) { static V c; return STRC(c, "{==}"); }
static V S1890(void) { static V c; return STRC(c, "\077"); }
static V S1891(void) { static V c; return STRC(c, "{"); }
static V S1892(void) { static V c; return STRC(c, " : "); }
static V S1893(void) { static V c; return STRC(c, "}"); }
static V S1894(void) { static V c; return STRC(c, "\077"); }
static V F_Chk_dterm__show_dgo(V a0, V a1, V a2, V a3) {
top:;
V s1854 = a0;
if (TAG(s1854) == 0) {
return F_Bool_dpick(F_Chk_dshow_dbound__at(a2, a3, FLD(s1854, 0), FLD(s1854, 1)), FLD(s1854, 0), F_String_dappend(FLD(s1854, 0), F_String_dappend(S1855(), F_U32_dshow(FLD(s1854, 1)))));
} else if (TAG(s1854) == 4) {
return F_String_dappend(F_Bool_dpick(F_Chk_dStr_dhas(a2, FLD(s1854, 0)), F_String_dappend(FLD(s1854, 0), S1856()), FLD(s1854, 0)), F_Bool_dpick(FLD(s1854, 2), S1857(), S1858()));
} else if (TAG(s1854) == 5) {
{ V t0 = FLD(s1854, 2); V t1 = a1; V t2 = a2; V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1854) == 6) {
V v1859 = F_Chk_dshow_dargs(a2, a3, FLD(s1854, 2), 2u);
V v1860 = F_List_dlength(FLD(s1854, 0));
V v1861 = F_Chk_dterm__show_dgo(F_Chk_dsyn__body(FLD(s1854, 3)), 0u, F_List_dappend(F_List_dreverse(FLD(s1854, 0)), a2), F_Nat_dadd(a3, v1860));
return F_Chk_dshow_dparen(F_U32_dis__ge(a1, 1u), F_String_dappend(F_Chk_dshow_djoin(F_Chk_dshow_dlet__ks(FLD(s1854, 0), FLD(s1854, 5)), S1862()), F_String_dappend(S1863(), F_String_dappend(F_Chk_dshow_djoin(v1859, S1864()), F_String_dappend(S1865(), v1861)))));
} else if (TAG(s1854) == 7) {
return F_Chk_dshow_dtyp(FLD(s1854, 0), a2, a3);
} else if (TAG(s1854) == 8) {
return S1866();
} else if (TAG(s1854) == 9) {
return F_Chk_dshow_dqua(FLD(s1854, 0));
} else if (TAG(s1854) == 10) {
return F_Chk_dshow_dparen(F_U32_dis__gt(a1, 2u), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1854, 0), 3u, a2, a3), F_String_dappend(S1867(), F_Chk_dterm__show_dgo(FLD(s1854, 1), 3u, a2, a3))));
} else if (TAG(s1854) == 11) {
return F_Chk_dshow_dparen(F_U32_dis__gt(a1, 2u), F_String_dappend(S1868(), F_String_dappend(F_Chk_dquant__show(FLD(s1854, 0)), F_String_dappend(FLD(s1854, 1), F_String_dappend(S1869(), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1854, 3), 3u, a2, a3), F_String_dappend(S1870(), F_Chk_dterm__show_dgo(F_Chk_dsyn__body(FLD(s1854, 4)), 2u, C2(1, FLD(s1854, 1), a2), nat_addk(a3, 1)))))))));
} else if (TAG(s1854) == 12) {
return F_Chk_dshow_dparen(F_U32_dis__gt(a1, 1u), F_String_dappend(F_Chk_dquant__show(F_Chk_dQ_ddef(FLD(s1854, 4))), F_String_dappend(FLD(s1854, 0), F_String_dappend(S1871(), F_Chk_dterm__show_dgo(F_Chk_dsyn__body(FLD(s1854, 2)), 0u, C2(1, FLD(s1854, 0), a2), nat_addk(a3, 1))))));
} else if (TAG(s1854) == 13) {
return F_Chk_dshow_dapp(C3(13, FLD(s1854, 0), FLD(s1854, 1), FLD(s1854, 2)), a1, a2, a3);
} else if (TAG(s1854) == 14) {
V v1872 = F_Chk_dshow_drems(FLD(s1854, 3));
V v1873 = F_Chk_dshow_dargs(a2, a3, FLD(s1854, 1), 1u);
return F_Chk_dshow_dparen(F_Bool_dand(F_Bool_dnot(F_String_dis__empty(v1872)), F_U32_dis__gt(a1, 2u)), F_String_dappend(FLD(s1854, 0), F_String_dappend(F_Bool_dpick(F_Bool_dand(F_Chk_dLst_dempty(v1873), F_String_dis__empty(v1872)), S1874(), F_String_dappend(S1875(), F_String_dappend(F_Chk_dshow_djoin(v1873, S1876()), S1877()))), v1872)));
} else if (TAG(s1854) == 15) {
return F_Chk_dshow_dctr(C3(15, FLD(s1854, 0), FLD(s1854, 1), FLD(s1854, 2)), a1, a2, a3);
} else if (TAG(s1854) == 16 && TAG(FLD(s1854, 0)) == 0) {
return F_String_dappend(F_Nat_dshow(FLD(FLD(s1854, 0), 0)), S1878());
} else if (TAG(s1854) == 16 && TAG(FLD(s1854, 0)) == 1) {
return F_String_dappend(S1879(), F_String_dappend(F_Chk_dshow_dtext(FLD(FLD(s1854, 0), 0)), S1880()));
} else if (TAG(s1854) == 17) {
return F_String_dappend(S1881(), F_String_dappend(F_Chk_dshow_djoin(F_Chk_dshow_darms(C4(17, FLD(s1854, 0), FLD(s1854, 1), FLD(s1854, 2), FLD(s1854, 3)), a2, a3), S1882()), S1883()));
} else if (TAG(s1854) == 18) {
return S1884();
} else if (TAG(s1854) == 19) {
return F_String_dappend(S1885(), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1854, 0), 2u, a2, a3), F_String_dappend(S1886(), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1854, 1), 2u, a2, a3), F_String_dappend(S1887(), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1854, 2), 2u, a2, a3), S1888()))))));
} else if (TAG(s1854) == 20) {
return S1889();
} else if (TAG(s1854) == 22) {
return F_String_dappend(S1890(), FLD(s1854, 0));
} else if (TAG(s1854) == 21) {
return F_Chk_dshow_dparen(F_U32_dis__gt(a1, 1u), F_Chk_dshow_drwt(FLD(s1854, 0), FLD(s1854, 1), FLD(s1854, 2), a2, a3));
} else if (TAG(s1854) == 23) {
return F_String_dappend(S1891(), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1854, 0), 2u, a2, a3), F_String_dappend(S1892(), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1854, 1), 2u, a2, a3), S1893()))));
} else if (TAG(s1854) == 1) {
{ V t0 = FLD(s1854, 2); V t1 = a1; V t2 = a2; V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1854) == 3) {
{ V t0 = FLD(s1854, 3); V t1 = a1; V t2 = a2; V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1854) == 2) {
return FLD(s1854, 0);
} else {
return S1894();
}
}
static V W_Chk_dterm__show_dgo(V *a) { (void)a; return F_Chk_dterm__show_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dshow_drwt(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Chk_dshow_drwt_dgo(F_Chk_dterm__show_dgo(a0, 2u, a3, a4), F_Chk_dterm__strip(a1), a2, a3, a4);
}
static V W_Chk_dshow_drwt(V *a) { (void)a; return F_Chk_dshow_drwt(a[0], a[1], a[2], a[3], a[4]); }
static V S1896(void) { static V c; return STRC(c, "%"); }
static V S1897(void) { static V c; return STRC(c, " : "); }
static V S1898(void) { static V c; return STRC(c, "; "); }
static V F_Chk_dshow_drwt_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1895 = a1;
if (TAG(s1895) == 12) {
return F_Chk_dshow_drwt_dinner(a0, CN(12, 5, (V[]){FLD(s1895, 0), FLD(s1895, 1), FLD(s1895, 2), FLD(s1895, 3), FLD(s1895, 4)}), FLD(s1895, 0), F_Chk_dterm__strip(F_Chk_dsyn__body(FLD(s1895, 2))), a2, a3, a4);
} else {
return F_String_dappend(S1896(), F_String_dappend(a0, F_String_dappend(S1897(), F_String_dappend(F_Chk_dterm__show_dgo(s1895, 2u, a3, a4), F_String_dappend(S1898(), F_Chk_dterm__show_dgo(a2, 0u, a3, a4))))));
}
}
static V W_Chk_dshow_drwt_dgo(V *a) { (void)a; return F_Chk_dshow_drwt_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V S1900(void) { static V c; return STRC(c, "%"); }
static V S1901(void) { static V c; return STRC(c, ""); }
static V S1902(void) { static V c; return STRC(c, "@"); }
static V S1903(void) { static V c; return STRC(c, " : "); }
static V S1904(void) { static V c; return STRC(c, "; "); }
static V S1905(void) { static V c; return STRC(c, "%"); }
static V S1906(void) { static V c; return STRC(c, " : "); }
static V S1907(void) { static V c; return STRC(c, "; "); }
static V F_Chk_dshow_drwt_dinner(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1899 = a3;
if (TAG(s1899) == 12) {
return F_String_dappend(S1900(), F_String_dappend(F_Bool_dpick(F_String_dis__empty(FLD(s1899, 0)), S1901(), F_String_dappend(FLD(s1899, 0), S1902())), F_String_dappend(a0, F_String_dappend(S1903(), F_String_dappend(F_Chk_dterm__show_dgo(F_Chk_dsyn__body(FLD(s1899, 2)), 2u, C2(1, FLD(s1899, 0), C2(1, a2, a5)), nat_addk(a6, 2)), F_String_dappend(S1904(), F_Chk_dterm__show_dgo(a4, 0u, a5, a6)))))));
} else {
return F_String_dappend(S1905(), F_String_dappend(a0, F_String_dappend(S1906(), F_String_dappend(F_Chk_dterm__show_dgo(a1, 2u, a5, a6), F_String_dappend(S1907(), F_Chk_dterm__show_dgo(a4, 0u, a5, a6))))));
}
}
static V W_Chk_dshow_drwt_dinner(V *a) { (void)a; return F_Chk_dshow_drwt_dinner(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S1909(void) { static V c; return STRC(c, "("); }
static V S1910(void) { static V c; return STRC(c, ")"); }
static V F_Chk_dshow_dparen(V a0, V a1) {
top:;
V s1908 = a0;
if ((s1908) == IMM(1)) {
return F_String_dappend(S1909(), F_String_dappend(a1, S1910()));
} else if ((s1908) == IMM(0)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dparen(V *a) { (void)a; return F_Chk_dshow_dparen(a[0], a[1]); }
static V S1912(void) { static V c; return STRC(c, ": "); }
static V F_Chk_dshow_darms(V a0, V a1, V a2) {
top:;
V s1911 = a0;
if (TAG(s1911) == 17) {
return C2(1, F_String_dappend(FLD(s1911, 0), F_String_dappend(S1912(), F_Chk_dterm__show_dgo(FLD(s1911, 1), 2u, a1, a2))), F_Chk_dshow_darms(FLD(s1911, 2), a1, a2));
} else if (TAG(s1911) == 18) {
return IMM(0);
} else {
return C2(1, F_Chk_dterm__show_dgo(s1911, 2u, a1, a2), IMM(0));
}
}
static V W_Chk_dshow_darms(V *a) { (void)a; return F_Chk_dshow_darms(a[0], a[1], a[2]); }
static V F_Chk_dshow_djoin(V a0, V a1) {
top:;
return F_String_djoin(a0, a1);
}
static V W_Chk_dshow_djoin(V *a) { (void)a; return F_Chk_dshow_djoin(a[0], a[1]); }
static V S1913(void) { static V c; return STRC(c, "U32"); }
static V F_Chk_dshow_dctr(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dshow_dctr_du32(a0, F_Chk_du32__from__term(a0, S1913()), a1, a2, a3);
}
static V W_Chk_dshow_dctr(V *a) { (void)a; return F_Chk_dshow_dctr(a[0], a[1], a[2], a[3]); }
static V F_Chk_du32__from__term(V a0, V a1) {
top:;
return F_Chk_du32__from__term_dgo(F_Chk_dterm__strip(a0), a1);
}
static V W_Chk_du32__from__term(V *a) { (void)a; return F_Chk_du32__from__term(a[0], a[1]); }
static V F_Chk_du32__from__term_dgo(V a0, V a1) {
top:;
V s1914 = a0;
if (TAG(s1914) == 15 && TAG(FLD(s1914, 1)) == 1 && (FLD(FLD(s1914, 1), 1)) == IMM(0)) {
return F_Chk_du32__from__term_dif(FLD(FLD(s1914, 1), 0), F_String_deq(a1, FLD(s1914, 0)));
} else {
return IMM(0);
}
}
static V W_Chk_du32__from__term_dgo(V *a) { (void)a; return F_Chk_du32__from__term_dgo(a[0], a[1]); }
static V F_Chk_du32__from__term_dif(V a0, V a1) {
top:;
V s1915 = a1;
if ((s1915) == IMM(1)) {
return F_Chk_du32__bits(F_Chk_dterm__strip(a0), 0u, 0u);
} else if ((s1915) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_du32__from__term_dif(V *a) { (void)a; return F_Chk_du32__from__term_dif(a[0], a[1]); }
static V F_Chk_du32__bits(V a0, V a1, V a2) {
top:;
V s1916 = a0;
if (TAG(s1916) == 15 && TAG(FLD(s1916, 0)) == 1 && (FLD(FLD(s1916, 0), 0)) == 87 && TAG(FLD(FLD(s1916, 0), 1)) == 1 && (FLD(FLD(FLD(s1916, 0), 1), 0)) == 67 && TAG(FLD(FLD(FLD(s1916, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1916, 0), 1), 1), 0)) == 111 && TAG(FLD(FLD(FLD(FLD(s1916, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1916, 0), 1), 1), 1), 0)) == 110 && (FLD(FLD(FLD(FLD(FLD(s1916, 0), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s1916, 1)) == 1 && TAG(FLD(FLD(s1916, 1), 1)) == 1 && (FLD(FLD(FLD(s1916, 1), 1), 1)) == IMM(0)) {
return F_Chk_du32__bits_dbit(F_Chk_dterm__strip(FLD(FLD(s1916, 1), 0)), FLD(FLD(FLD(s1916, 1), 1), 0), a1, a2);
} else if (TAG(s1916) == 15 && TAG(FLD(s1916, 0)) == 1 && (FLD(FLD(s1916, 0), 0)) == 87 && TAG(FLD(FLD(s1916, 0), 1)) == 1 && (FLD(FLD(FLD(s1916, 0), 1), 0)) == 78 && TAG(FLD(FLD(FLD(s1916, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1916, 0), 1), 1), 0)) == 105 && TAG(FLD(FLD(FLD(FLD(s1916, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1916, 0), 1), 1), 1), 0)) == 108 && (FLD(FLD(FLD(FLD(FLD(s1916, 0), 1), 1), 1), 1)) == IMM(0) && (FLD(s1916, 1)) == IMM(0)) {
return F_Bool_dpick(F_U32_dis__eq(a1, 32u), C1(1, a2), IMM(0));
} else {
return IMM(0);
}
}
static V W_Chk_du32__bits(V *a) { (void)a; return F_Chk_du32__bits(a[0], a[1], a[2]); }
static V F_Chk_du32__bits_dbit(V a0, V a1, V a2, V a3) {
top:;
V s1917 = a0;
if (TAG(s1917) == 15 && TAG(FLD(s1917, 0)) == 1 && (FLD(FLD(s1917, 0), 0)) == 84 && TAG(FLD(FLD(s1917, 0), 1)) == 1 && (FLD(FLD(FLD(s1917, 0), 1), 0)) == 114 && TAG(FLD(FLD(FLD(s1917, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1917, 0), 1), 1), 0)) == 117 && TAG(FLD(FLD(FLD(FLD(s1917, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1917, 0), 1), 1), 1), 0)) == 101 && (FLD(FLD(FLD(FLD(FLD(s1917, 0), 1), 1), 1), 1)) == IMM(0) && (FLD(s1917, 1)) == IMM(0)) {
return F_Chk_du32__bits_dnext(a1, a2, F_U32_dor(a3, F_U32_dshln(1u, F_U32_dto__nat(a2))));
} else if (TAG(s1917) == 15 && TAG(FLD(s1917, 0)) == 1 && (FLD(FLD(s1917, 0), 0)) == 70 && TAG(FLD(FLD(s1917, 0), 1)) == 1 && (FLD(FLD(FLD(s1917, 0), 1), 0)) == 97 && TAG(FLD(FLD(FLD(s1917, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1917, 0), 1), 1), 0)) == 108 && TAG(FLD(FLD(FLD(FLD(s1917, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1917, 0), 1), 1), 1), 0)) == 115 && TAG(FLD(FLD(FLD(FLD(FLD(s1917, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s1917, 0), 1), 1), 1), 1), 0)) == 101 && (FLD(FLD(FLD(FLD(FLD(FLD(s1917, 0), 1), 1), 1), 1), 1)) == IMM(0) && (FLD(s1917, 1)) == IMM(0)) {
return F_Chk_du32__bits_dnext(a1, a2, a3);
} else {
return IMM(0);
}
}
static V W_Chk_du32__bits_dbit(V *a) { (void)a; return F_Chk_du32__bits_dbit(a[0], a[1], a[2], a[3]); }
static V F_Chk_du32__bits_dnext(V a0, V a1, V a2) {
top:;
return F_Bool_dpick(F_U32_dis__ge(a1, 32u), IMM(0), F_Chk_du32__bits(F_Chk_dterm__strip(a0), F_U32_dinc(a1), a2));
}
static V W_Chk_du32__bits_dnext(V *a) { (void)a; return F_Chk_du32__bits_dnext(a[0], a[1], a[2]); }
static V W_U32_dshln(V *a) { (void)a; return F_U32_dshln(a[0], a[1]); }
static V S1919(void) { static V c; return STRC(c, "F32"); }
static V F_Chk_dshow_dctr_du32(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1918 = a1;
if (TAG(s1918) == 1) {
return F_U32_dshow(FLD(s1918, 0));
} else if ((s1918) == IMM(0)) {
return F_Chk_dshow_dctr_df32(a0, F_Chk_du32__from__term(a0, S1919()), a2, a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_du32(V *a) { (void)a; return F_Chk_dshow_dctr_du32(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dshow_dctr_df32(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1920 = a1;
if (TAG(s1920) == 1) {
return F_Chk_df32__show(FLD(s1920, 0));
} else if ((s1920) == IMM(0)) {
return F_Chk_dshow_dctr_dnat(a0, F_Chk_dnat__from__term(a0), a2, a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_df32(V *a) { (void)a; return F_Chk_dshow_dctr_df32(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dnat__from__term(V a0) {
top:;
V s1921 = a0;
if (TAG(s1921) == 15 && TAG(FLD(s1921, 0)) == 1 && (FLD(FLD(s1921, 0), 0)) == 83 && TAG(FLD(FLD(s1921, 0), 1)) == 1 && (FLD(FLD(FLD(s1921, 0), 1), 0)) == 117 && TAG(FLD(FLD(FLD(s1921, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 0)) == 99 && TAG(FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 1), 0)) == 99 && (FLD(FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s1921, 1)) == 1 && (FLD(FLD(s1921, 1), 1)) == IMM(0)) {
return F_Chk_dMaybe_dmap__nat(F_Chk_dnat__from__term(FLD(FLD(s1921, 1), 0)));
} else if (TAG(s1921) == 15 && TAG(FLD(s1921, 0)) == 1 && (FLD(FLD(s1921, 0), 0)) == 90 && TAG(FLD(FLD(s1921, 0), 1)) == 1 && (FLD(FLD(FLD(s1921, 0), 1), 0)) == 101 && TAG(FLD(FLD(FLD(s1921, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 0)) == 114 && TAG(FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 1), 0)) == 111 && (FLD(FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 1), 1)) == IMM(0) && (FLD(s1921, 1)) == IMM(0)) {
return C1(1, 0u);
} else if (TAG(s1921) == 16 && TAG(FLD(s1921, 0)) == 0) {
return C1(1, FLD(FLD(s1921, 0), 0));
} else {
return IMM(0);
}
}
static V W_Chk_dnat__from__term(V *a) { (void)a; return F_Chk_dnat__from__term(a[0]); }
static V F_Chk_dMaybe_dmap__nat(V a0) {
top:;
V s1922 = a0;
if ((s1922) == IMM(0)) {
return IMM(0);
} else if (TAG(s1922) == 1) {
return F_Bool_dpick(F_Nat_dis__le(nat_addk(FLD(s1922, 0), 1), 4294967295u), C1(1, nat_addk(FLD(s1922, 0), 1)), IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dMaybe_dmap__nat(V *a) { (void)a; return F_Chk_dMaybe_dmap__nat(a[0]); }
static V W_Nat_dis__le(V *a) { (void)a; return F_Nat_dis__le(a[0], a[1]); }
static V S1924(void) { static V c; return STRC(c, "n"); }
static V S1925(void) { static V c; return STRC(c, "Succ"); }
static V F_Chk_dshow_dctr_dnat(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1923 = a1;
if (TAG(s1923) == 1) {
return F_String_dappend(F_Nat_dshow(FLD(s1923, 0)), S1924());
} else if ((s1923) == IMM(0)) {
return F_Chk_dshow_dctr_dsucc(a0, F_Chk_dshow_dchain(a0, S1925(), 1u), a2, a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_dnat(V *a) { (void)a; return F_Chk_dshow_dctr_dnat(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dshow_dchain(V a0, V a1, V a2) {
top:;
V s1926 = a0;
if (TAG(s1926) == 15) {
return F_Chk_dshow_dchain_dif(C3(15, FLD(s1926, 0), FLD(s1926, 1), FLD(s1926, 2)), FLD(s1926, 1), a1, a2, F_Bool_dand(F_String_deq(a1, FLD(s1926, 0)), F_Nat_dis__eq(F_List_dlength(FLD(s1926, 1)), a2)));
} else {
return C2(0, IMM(0), s1926);
}
}
static V W_Chk_dshow_dchain(V *a) { (void)a; return F_Chk_dshow_dchain(a[0], a[1], a[2]); }
static V F_Chk_dshow_dchain_dif(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1927 = a4;
if ((s1927) == IMM(1)) {
return F_Chk_dshow_dchain_dcons(F_Chk_dLst_dhead(a0, a1), F_Chk_dshow_dchain(F_Chk_dLst_dlast(a0, a1), a2, a3));
} else if ((s1927) == IMM(0)) {
return C2(0, IMM(0), a0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dchain_dif(V *a) { (void)a; return F_Chk_dshow_dchain_dif(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dLst_dlast(V a1, V a2) {
top:;
V s1928 = a2;
if ((s1928) == IMM(0)) {
return a1;
} else if (TAG(s1928) == 1 && (FLD(s1928, 1)) == IMM(0)) {
return FLD(s1928, 0);
} else if (TAG(s1928) == 1) {
{ V t0 = a1; V t1 = FLD(s1928, 1); a1 = t0; a2 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dLst_dlast(V *a) { (void)a; return F_Chk_dLst_dlast(a[1], a[2]); }
static V F_Chk_dshow_dchain_dcons(V a0, V a1) {
top:;
V v1929 = a1;
return C2(0, C2(1, a0, FLD(v1929, 0)), FLD(v1929, 1));
}
static V W_Chk_dshow_dchain_dcons(V *a) { (void)a; return F_Chk_dshow_dchain_dcons(a[0], a[1]); }
static V S1932(void) { static V c; return STRC(c, "n+"); }
static V F_Chk_dshow_dctr_dsucc(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1930 = a1;
V s1931 = FLD(v1930, 0);
if ((s1931) == IMM(0)) {
return F_Chk_dshow_dctr_dchr(a0, F_Chk_dshow_dchr__term(a0, 39u), a2, a3, a4);
} else if (TAG(s1931) == 1) {
return F_Chk_dshow_dparen(F_U32_dis__gt(a2, 2u), F_String_dappend(F_Nat_dshow(F_List_dlength(C2(1, FLD(s1931, 0), FLD(s1931, 1)))), F_String_dappend(S1932(), F_Chk_dterm__show_dgo(FLD(v1930, 1), 2u, a3, a4))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_dsucc(V *a) { (void)a; return F_Chk_dshow_dctr_dsucc(a[0], a[1], a[2], a[3], a[4]); }
static V S1934(void) { static V c; return STRC(c, "U32"); }
static V F_Chk_dshow_dchr__term(V a0, V a1) {
top:;
V s1933 = a0;
if (TAG(s1933) == 15 && TAG(FLD(s1933, 0)) == 1 && (FLD(FLD(s1933, 0), 0)) == 67 && TAG(FLD(FLD(s1933, 0), 1)) == 1 && (FLD(FLD(FLD(s1933, 0), 1), 0)) == 104 && TAG(FLD(FLD(FLD(s1933, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1933, 0), 1), 1), 0)) == 114 && (FLD(FLD(FLD(FLD(s1933, 0), 1), 1), 1)) == IMM(0) && TAG(FLD(s1933, 1)) == 1 && (FLD(FLD(s1933, 1), 1)) == IMM(0)) {
return F_Chk_dshow_dchr__term_du(F_Chk_du32__from__term(FLD(FLD(s1933, 1), 0), S1934()), a1);
} else {
return IMM(0);
}
}
static V W_Chk_dshow_dchr__term(V *a) { (void)a; return F_Chk_dshow_dchr__term(a[0], a[1]); }
static V F_Chk_dshow_dchr__term_du(V a0, V a1) {
top:;
V s1935 = a0;
if ((s1935) == IMM(0)) {
return IMM(0);
} else if (TAG(s1935) == 1) {
return C1(1, F_Chk_dshow_dchr(FLD(s1935, 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dchr__term_du(V *a) { (void)a; return F_Chk_dshow_dchr__term_du(a[0], a[1]); }
static V S1937(void) { static V c; return STRC(c, "'"); }
static V S1938(void) { static V c; return STRC(c, "'"); }
static V F_Chk_dshow_dctr_dchr(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1936 = a1;
if (TAG(s1936) == 1) {
return F_String_dappend(S1937(), F_String_dappend(FLD(s1936, 0), S1938()));
} else if ((s1936) == IMM(0)) {
return F_Chk_dshow_dctr_dstr(a0, F_Chk_dshow_dstr(a0), a2, a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_dchr(V *a) { (void)a; return F_Chk_dshow_dctr_dchr(a[0], a[1], a[2], a[3], a[4]); }
static V S1939(void) { static V c; return STRC(c, "SCon"); }
static V F_Chk_dshow_dstr(V a0) {
top:;
return F_Chk_dshow_dstr_dgo(F_Chk_dshow_dchain(a0, S1939(), 2u));
}
static V W_Chk_dshow_dstr(V *a) { (void)a; return F_Chk_dshow_dstr(a[0]); }
static V F_Chk_dshow_dstr_dgo(V a0) {
top:;
V v1940 = a0;
return F_Chk_dshow_dstr_dc(F_Chk_dshow_dchrs_dcat(F_Chk_dshow_dchrs(FLD(v1940, 0)), F_Chk_dshow_dstr__tail(FLD(v1940, 1))));
}
static V W_Chk_dshow_dstr_dgo(V *a) { (void)a; return F_Chk_dshow_dstr_dgo(a[0]); }
static V S1942(void) { static V c; return STRC(c, ""); }
static V F_Chk_dshow_dstr__tail(V a0) {
top:;
V s1941 = a0;
if (TAG(s1941) == 16 && TAG(FLD(s1941, 0)) == 1) {
return C1(1, F_Chk_dshow_dtext(FLD(FLD(s1941, 0), 0)));
} else if (TAG(s1941) == 15 && TAG(FLD(s1941, 0)) == 1 && (FLD(FLD(s1941, 0), 0)) == 83 && TAG(FLD(FLD(s1941, 0), 1)) == 1 && (FLD(FLD(FLD(s1941, 0), 1), 0)) == 78 && TAG(FLD(FLD(FLD(s1941, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1941, 0), 1), 1), 0)) == 105 && TAG(FLD(FLD(FLD(FLD(s1941, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1941, 0), 1), 1), 1), 0)) == 108 && (FLD(FLD(FLD(FLD(FLD(s1941, 0), 1), 1), 1), 1)) == IMM(0) && (FLD(s1941, 1)) == IMM(0)) {
return C1(1, S1942());
} else {
return IMM(0);
}
}
static V W_Chk_dshow_dstr__tail(V *a) { (void)a; return F_Chk_dshow_dstr__tail(a[0]); }
static V S1944(void) { static V c; return STRC(c, ""); }
static V F_Chk_dshow_dchrs(V a0) {
top:;
V s1943 = a0;
if ((s1943) == IMM(0)) {
return C1(1, S1944());
} else if (TAG(s1943) == 1) {
return F_Chk_dshow_dchrs_dcat(F_Chk_dshow_dchr__term(FLD(s1943, 0), 34u), F_Chk_dshow_dchrs(FLD(s1943, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dchrs(V *a) { (void)a; return F_Chk_dshow_dchrs(a[0]); }
static V F_Chk_dshow_dchrs_dcat(V a0, V a1) {
top:;
V s1945 = a0;
V s1946 = a1;
if (TAG(s1945) == 1 && TAG(s1946) == 1) {
return C1(1, F_String_dappend(FLD(s1945, 0), FLD(s1946, 0)));
} else {
return IMM(0);
}
}
static V W_Chk_dshow_dchrs_dcat(V *a) { (void)a; return F_Chk_dshow_dchrs_dcat(a[0], a[1]); }
static V S1948(void) { static V c; return STRC(c, "\042"); }
static V S1949(void) { static V c; return STRC(c, "\042"); }
static V F_Chk_dshow_dstr_dc(V a0) {
top:;
V s1947 = a0;
if ((s1947) == IMM(0)) {
return IMM(0);
} else if (TAG(s1947) == 1) {
return C1(1, F_String_dappend(S1948(), F_String_dappend(FLD(s1947, 0), S1949())));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dstr_dc(V *a) { (void)a; return F_Chk_dshow_dstr_dc(a[0]); }
static V S1951(void) { static V c; return STRC(c, "Con"); }
static V F_Chk_dshow_dctr_dstr(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1950 = a1;
if (TAG(s1950) == 1) {
return FLD(s1950, 0);
} else if ((s1950) == IMM(0)) {
return F_Chk_dshow_dctr_dlst(a0, F_Chk_dshow_dchain(a0, S1951(), 2u), a2, a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_dstr(V *a) { (void)a; return F_Chk_dshow_dctr_dstr(a[0], a[1], a[2], a[3], a[4]); }
static V S1955(void) { static V c; return STRC(c, "["); }
static V S1956(void) { static V c; return STRC(c, ", "); }
static V S1957(void) { static V c; return STRC(c, "]"); }
static V S1958(void) { static V c; return STRC(c, "Tuple"); }
static V S1959(void) { static V c; return STRC(c, " <> "); }
static V S1960(void) { static V c; return STRC(c, " <> "); }
static V F_Chk_dshow_dctr_dlst(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1952 = a1;
V s1953 = FLD(v1952, 0);
V s1954 = FLD(v1952, 1);
if (TAG(s1954) == 15 && TAG(FLD(s1954, 0)) == 1 && (FLD(FLD(s1954, 0), 0)) == 78 && TAG(FLD(FLD(s1954, 0), 1)) == 1 && (FLD(FLD(FLD(s1954, 0), 1), 0)) == 105 && TAG(FLD(FLD(FLD(s1954, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1954, 0), 1), 1), 0)) == 108 && (FLD(FLD(FLD(FLD(s1954, 0), 1), 1), 1)) == IMM(0) && (FLD(s1954, 1)) == IMM(0)) {
return F_String_dappend(S1955(), F_String_dappend(F_Chk_dshow_djoin(F_Chk_dshow_dargs(a3, a4, s1953, 1u), S1956()), S1957()));
} else if ((s1953) == IMM(0)) {
return F_Chk_dshow_dctr_dtup(a0, F_Chk_dshow_dchain(a0, S1958(), 2u), a2, a3, a4);
} else {
return F_Chk_dshow_dparen(F_U32_dis__gt(a2, 2u), F_String_dappend(F_Chk_dshow_djoin(F_Chk_dshow_dargs(a3, a4, s1953, 3u), S1959()), F_String_dappend(S1960(), F_Chk_dterm__show_dgo(s1954, 2u, a3, a4))));
}
}
static V W_Chk_dshow_dctr_dlst(V *a) { (void)a; return F_Chk_dshow_dctr_dlst(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dshow_dargs(V a0, V a1, V a2, V a3) {
top:;
V s1961 = a2;
if ((s1961) == IMM(0)) {
return IMM(0);
} else if (TAG(s1961) == 1) {
return C2(1, F_Chk_dterm__show_dgo(FLD(s1961, 0), a3, a0, a1), F_Chk_dshow_dargs(a0, a1, FLD(s1961, 1), a3));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dargs(V *a) { (void)a; return F_Chk_dshow_dargs(a[0], a[1], a[2], a[3]); }
static V S1964(void) { static V c; return STRC(c, "("); }
static V S1965(void) { static V c; return STRC(c, ", "); }
static V S1966(void) { static V c; return STRC(c, ")"); }
static V F_Chk_dshow_dctr_dtup(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1962 = a1;
V s1963 = FLD(v1962, 0);
if ((s1963) == IMM(0)) {
return F_Chk_dshow_dctr_darr(a0, F_Chk_dshow_darr(a0, a3, a4), a3, a4);
} else if (TAG(s1963) == 1) {
return F_String_dappend(S1964(), F_String_dappend(F_Chk_dshow_djoin(F_Chk_dshow_dargs(a3, a4, F_List_dappend(C2(1, FLD(s1963, 0), FLD(s1963, 1)), C2(1, FLD(v1962, 1), IMM(0))), 1u), S1965()), S1966()));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_dtup(V *a) { (void)a; return F_Chk_dshow_dctr_dtup(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dshow_darr(V a0, V a1, V a2) {
top:;
V s1967 = a0;
if (TAG(s1967) == 15 && TAG(FLD(s1967, 0)) == 1 && (FLD(FLD(s1967, 0), 0)) == 65 && TAG(FLD(FLD(s1967, 0), 1)) == 1 && (FLD(FLD(FLD(s1967, 0), 1), 0)) == 76 && TAG(FLD(FLD(FLD(s1967, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1967, 0), 1), 1), 0)) == 101 && TAG(FLD(FLD(FLD(FLD(s1967, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1967, 0), 1), 1), 1), 0)) == 97 && TAG(FLD(FLD(FLD(FLD(FLD(s1967, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s1967, 0), 1), 1), 1), 1), 0)) == 102 && (FLD(FLD(FLD(FLD(FLD(FLD(s1967, 0), 1), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s1967, 1)) == 1 && (FLD(FLD(s1967, 1), 1)) == IMM(0)) {
return C1(1, C2(1, F_Chk_dterm__show_dgo(FLD(FLD(s1967, 1), 0), 1u, a1, a2), IMM(0)));
} else if (TAG(s1967) == 15 && TAG(FLD(s1967, 0)) == 1 && (FLD(FLD(s1967, 0), 0)) == 65 && TAG(FLD(FLD(s1967, 0), 1)) == 1 && (FLD(FLD(FLD(s1967, 0), 1), 0)) == 78 && TAG(FLD(FLD(FLD(s1967, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1967, 0), 1), 1), 0)) == 111 && TAG(FLD(FLD(FLD(FLD(s1967, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1967, 0), 1), 1), 1), 0)) == 100 && TAG(FLD(FLD(FLD(FLD(FLD(s1967, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s1967, 0), 1), 1), 1), 1), 0)) == 101 && (FLD(FLD(FLD(FLD(FLD(FLD(s1967, 0), 1), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s1967, 1)) == 1 && TAG(FLD(FLD(s1967, 1), 1)) == 1 && (FLD(FLD(FLD(s1967, 1), 1), 1)) == IMM(0)) {
return F_Chk_dshow_darr_dcat(F_Chk_dshow_darr(FLD(FLD(s1967, 1), 0), a1, a2), F_Chk_dshow_darr(FLD(FLD(FLD(s1967, 1), 1), 0), a1, a2));
} else {
return IMM(0);
}
}
static V W_Chk_dshow_darr(V *a) { (void)a; return F_Chk_dshow_darr(a[0], a[1], a[2]); }
static V F_Chk_dshow_darr_dcat(V a0, V a1) {
top:;
V s1968 = a0;
V s1969 = a1;
if (TAG(s1968) == 1 && TAG(s1969) == 1) {
return C1(1, F_List_dappend(FLD(s1968, 0), FLD(s1969, 0)));
} else {
return IMM(0);
}
}
static V W_Chk_dshow_darr_dcat(V *a) { (void)a; return F_Chk_dshow_darr_dcat(a[0], a[1]); }
static V S1971(void) { static V c; return STRC(c, "["); }
static V S1972(void) { static V c; return STRC(c, ", "); }
static V S1973(void) { static V c; return STRC(c, "]"); }
static V F_Chk_dshow_dctr_darr(V a0, V a1, V a2, V a3) {
top:;
V s1970 = a1;
if (TAG(s1970) == 1) {
return F_String_dappend(S1971(), F_String_dappend(F_Chk_dshow_djoin(FLD(s1970, 0), S1972()), S1973()));
} else if ((s1970) == IMM(0)) {
return F_Chk_dshow_dctr_dplain(a0, a2, a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_darr(V *a) { (void)a; return F_Chk_dshow_dctr_darr(a[0], a[1], a[2], a[3]); }
static V S1975(void) { static V c; return STRC(c, "{"); }
static V S1976(void) { static V c; return STRC(c, ", "); }
static V S1977(void) { static V c; return STRC(c, "}"); }
static V S1978(void) { static V c; return STRC(c, "\077"); }
static V F_Chk_dshow_dctr_dplain(V a0, V a1, V a2) {
top:;
V s1974 = a0;
if (TAG(s1974) == 15) {
return F_String_dappend(FLD(s1974, 0), F_String_dappend(S1975(), F_String_dappend(F_Chk_dshow_djoin(F_Chk_dshow_dargs(a1, a2, FLD(s1974, 1), 1u), S1976()), S1977())));
} else {
return S1978();
}
}
static V W_Chk_dshow_dctr_dplain(V *a) { (void)a; return F_Chk_dshow_dctr_dplain(a[0], a[1], a[2]); }
static V S1980(void) { static V c; return STRC(c, "."); }
static V S1981(void) { static V c; return STRC(c, "e"); }
static V S1982(void) { static V c; return STRC(c, "n"); }
static V S1983(void) { static V c; return STRC(c, "i"); }
static V S1984(void) { static V c; return STRC(c, ".0"); }
static V F_Chk_df32__show(V a0) {
top:;
V v1979 = F_F32_dshow(F_Chk_dF32_dfrom__bits(a0));
return F_Bool_dpick(F_Bool_dor(F_String_dcontains(v1979, S1980()), F_Bool_dor(F_String_dcontains(v1979, S1981()), F_Bool_dor(F_String_dcontains(v1979, S1982()), F_String_dcontains(v1979, S1983())))), v1979, F_String_dappend(v1979, S1984()));
}
static V W_Chk_df32__show(V *a) { (void)a; return F_Chk_df32__show(a[0]); }
static V F_String_dcontains(V a0, V a1) {
top:;
V s1985 = a0;
if ((s1985) == IMM(0)) {
return F_String_dis__empty(a1);
} else if (TAG(s1985) == 1) {
return F_String_dcontains_dif(FLD(s1985, 1), a1, F_String_dstarts__with(C2(1, FLD(s1985, 0), FLD(s1985, 1)), a1));
} else { bend_fail("incomplete match"); }
}
static V W_String_dcontains(V *a) { (void)a; return F_String_dcontains(a[0], a[1]); }
static V F_String_dcontains_dif(V a0, V a1, V a2) {
top:;
V s1986 = a2;
if ((s1986) == IMM(0)) {
return F_String_dcontains(a0, a1);
} else if ((s1986) == IMM(1)) {
return IMM(1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dcontains_dif(V *a) { (void)a; return F_String_dcontains_dif(a[0], a[1], a[2]); }
static V F_Chk_dF32_dfrom__bits(V a0) {
top:;
return F_Chk_dWord_dfrom__u32(a0);
}
static V W_Chk_dF32_dfrom__bits(V *a) { (void)a; return F_Chk_dF32_dfrom__bits(a[0]); }
static V F_Chk_dWord_dfrom__u32(V a0) {
top:;
V s1987 = a0;
{
return s1987;
}
}
static V W_Chk_dWord_dfrom__u32(V *a) { (void)a; return F_Chk_dWord_dfrom__u32(a[0]); }
static V W_F32_dshow(V *a) { (void)a; return F_F32_dshow(a[0]); }
static V F_Chk_dLst_dempty(V a2) {
top:;
V s1988 = a2;
if ((s1988) == IMM(0)) {
return IMM(1);
} else if (TAG(s1988) == 1) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dLst_dempty(V *a) { (void)a; return F_Chk_dLst_dempty(a[2]); }
static V S1990(void) { static V c; return STRC(c, ""); }
static V S1991(void) { static V c; return STRC(c, " - "); }
static V S1992(void) { static V c; return STRC(c, "{}"); }
static V F_Chk_dshow_drems(V a0) {
top:;
V s1989 = a0;
if ((s1989) == IMM(0)) {
return S1990();
} else if (TAG(s1989) == 1) {
return F_String_dappend(S1991(), F_String_dappend(FLD(s1989, 0), F_String_dappend(S1992(), F_Chk_dshow_drems(FLD(s1989, 1)))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_drems(V *a) { (void)a; return F_Chk_dshow_drems(a[0]); }
static V F_Chk_dshow_dapp(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dshow_dapp_dgo(F_Chk_dterm__unapply(a0), a1, a2, a3);
}
static V W_Chk_dshow_dapp(V *a) { (void)a; return F_Chk_dshow_dapp(a[0], a[1], a[2], a[3]); }
static V S1996(void) { static V c; return STRC(c, "&"); }
static V S1997(void) { static V c; return STRC(c, ":"); }
static V S1998(void) { static V c; return STRC(c, " -> "); }
static V S1999(void) { static V c; return STRC(c, "("); }
static V S2000(void) { static V c; return STRC(c, ", "); }
static V S2001(void) { static V c; return STRC(c, ")"); }
static V F_Chk_dshow_dapp_dgo(V a0, V a1, V a2, V a3) {
top:;
V v1993 = a0;
V s1994 = FLD(v1993, 0);
V s1995 = FLD(v1993, 1);
if (TAG(s1994) == 4 && TAG(FLD(s1994, 0)) == 1 && (FLD(FLD(s1994, 0), 0)) == 69 && TAG(FLD(FLD(s1994, 0), 1)) == 1 && (FLD(FLD(FLD(s1994, 0), 1), 0)) == 120 && TAG(FLD(FLD(FLD(s1994, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1994, 0), 1), 1), 0)) == 105 && TAG(FLD(FLD(FLD(FLD(s1994, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1994, 0), 1), 1), 1), 0)) == 115 && TAG(FLD(FLD(FLD(FLD(FLD(s1994, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s1994, 0), 1), 1), 1), 1), 0)) == 116 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(s1994, 0), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(s1994, 0), 1), 1), 1), 1), 1), 0)) == 115 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(s1994, 0), 1), 1), 1), 1), 1), 1)) == IMM(0) && TAG(s1995) == 1 && TAG(FLD(s1995, 1)) == 1 && TAG(FLD(FLD(s1995, 1), 0)) == 12 && (FLD(FLD(s1995, 1), 1)) == IMM(0)) {
return F_Chk_dshow_dparen(F_U32_dis__gt(a1, 2u), F_String_dappend(S1996(), F_String_dappend(FLD(FLD(FLD(s1995, 1), 0), 0), F_String_dappend(S1997(), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1995, 0), 3u, a2, a3), F_String_dappend(S1998(), F_Chk_dterm__show_dgo(F_Chk_dsyn__body(FLD(FLD(FLD(s1995, 1), 0), 2)), 2u, C2(1, FLD(FLD(FLD(s1995, 1), 0), 0), a2), nat_addk(a3, 1))))))));
} else {
return F_String_dappend(F_Chk_dterm__show_dgo(s1994, 3u, a2, a3), F_String_dappend(S1999(), F_String_dappend(F_Chk_dshow_djoin(F_Chk_dshow_dargs(a2, a3, s1995, 1u), S2000()), S2001())));
}
}
static V W_Chk_dshow_dapp_dgo(V *a) { (void)a; return F_Chk_dshow_dapp_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dQ_ddef(V a0) {
top:;
V s2002 = a0;
if ((s2002) == IMM(3)) {
return IMM(1);
} else {
return s2002;
}
}
static V W_Chk_dQ_ddef(V *a) { (void)a; return F_Chk_dQ_ddef(a[0]); }
static V S2004(void) { static V c; return STRC(c, "Type"); }
static V S2005(void) { static V c; return STRC(c, "Data"); }
static V S2006(void) { static V c; return STRC(c, "Kind("); }
static V S2007(void) { static V c; return STRC(c, ")"); }
static V F_Chk_dshow_dtyp(V a0, V a1, V a2) {
top:;
V s2003 = a0;
if (TAG(s2003) == 9 && (FLD(s2003, 0)) == IMM(1)) {
return S2004();
} else if (TAG(s2003) == 9 && (FLD(s2003, 0)) == IMM(2)) {
return S2005();
} else {
return F_String_dappend(S2006(), F_String_dappend(F_Chk_dterm__show_dgo(s2003, 1u, a1, a2), S2007()));
}
}
static V W_Chk_dshow_dtyp(V *a) { (void)a; return F_Chk_dshow_dtyp(a[0], a[1], a[2]); }
static V F_Chk_dshow_dlet__ks(V a0, V a1) {
top:;
V s2008 = a0;
V s2009 = a1;
if (TAG(s2008) == 1 && TAG(s2009) == 1) {
return C2(1, F_String_dappend(F_Chk_dquant__show(FLD(s2009, 0)), FLD(s2008, 0)), F_Chk_dshow_dlet__ks(FLD(s2008, 1), FLD(s2009, 1)));
} else if (TAG(s2008) == 1 && (s2009) == IMM(0)) {
return C2(1, FLD(s2008, 0), F_Chk_dshow_dlet__ks(FLD(s2008, 1), IMM(0)));
} else {
return IMM(0);
}
}
static V W_Chk_dshow_dlet__ks(V *a) { (void)a; return F_Chk_dshow_dlet__ks(a[0], a[1]); }
static V F_Chk_dshow_dbound__at(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dshow_dbound__at_dc(a1, a3, F_Chk_dStr_dindex(a0, a2, 0u));
}
static V W_Chk_dshow_dbound__at(V *a) { (void)a; return F_Chk_dshow_dbound__at(a[0], a[1], a[2], a[3]); }
static V F_Chk_dStr_dindex(V a0, V a1, V a2) {
top:;
V s2010 = a0;
if ((s2010) == IMM(0)) {
return IMM(0);
} else if (TAG(s2010) == 1) {
return F_Chk_dStr_dindex_dif(FLD(s2010, 1), a1, a2, F_String_deq(FLD(s2010, 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dindex(V *a) { (void)a; return F_Chk_dStr_dindex(a[0], a[1], a[2]); }
static V F_Chk_dStr_dindex_dif(V a0, V a1, V a2, V a3) {
top:;
V s2011 = a3;
if ((s2011) == IMM(1)) {
return C1(1, a2);
} else if ((s2011) == IMM(0)) {
return F_Chk_dStr_dindex(a0, a1, nat_addk(a2, 1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dindex_dif(V *a) { (void)a; return F_Chk_dStr_dindex_dif(a[0], a[1], a[2], a[3]); }
static V F_Chk_dshow_dbound__at_dc(V a0, V a1, V a2) {
top:;
V s2012 = a2;
if ((s2012) == IMM(0)) {
return IMM(0);
} else if (TAG(s2012) == 1) {
return F_Nat_dis__eq(F_Nat_dsub(F_Nat_dsub(a0, 1u), FLD(s2012, 0)), F_U32_dto__nat(a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dbound__at_dc(V *a) { (void)a; return F_Chk_dshow_dbound__at_dc(a[0], a[1], a[2]); }
static V S2013(void) { static V c; return STRC(c, "#include <stdio.h>\012\012int main(void) {\012  fputs(\042"); }
static V S2014(void) { static V c; return STRC(c, "\134n\042, stdout);\012  return 0;\012}\012"); }
static V F_Main_demit__value(V a0) {
top:;
return F_IO_dwrite(F_String_dappend(S2013(), F_String_dappend(F_Gen_dlit(a0), S2014())));
}
static V W_Main_demit__value(V *a) { (void)a; return F_Main_demit__value(a[0]); }
static V S2016(void) { static V c; return STRC(c, ""); }
static V S2018(void) { static V c; return STRC(c, "All terms check, but "); }
static V S2019(void) { static V c; return STRC(c, " def"); }
static V S2020(void) { static V c; return STRC(c, " relies"); }
static V S2021(void) { static V c; return STRC(c, "s rely"); }
static V S2022(void) { static V c; return STRC(c, " on unsafe or foreign code:\012"); }
static V F_Chk_dreport__text(V a0) {
top:;
V s2015 = a0;
if ((s2015) == IMM(0)) {
return S2016();
} else if (TAG(s2015) == 1) {
V v2017 = F_List_dlength(C2(1, FLD(s2015, 0), FLD(s2015, 1)));
return F_String_dappend(S2018(), F_String_dappend(F_Nat_dshow(v2017), F_String_dappend(S2019(), F_String_dappend(F_Bool_dpick(F_Nat_dis__eq(v2017, 1u), S2020(), S2021()), F_String_dappend(S2022(), F_Chk_dreport__lines(C2(1, FLD(s2015, 0), FLD(s2015, 1))))))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport__text(V *a) { (void)a; return F_Chk_dreport__text(a[0]); }
static V S2024(void) { static V c; return STRC(c, ""); }
static V S2025(void) { static V c; return STRC(c, "- "); }
static V S2026(void) { static V c; return STRC(c, "\012"); }
static V F_Chk_dreport__lines(V a0) {
top:;
V s2023 = a0;
if ((s2023) == IMM(0)) {
return S2024();
} else if (TAG(s2023) == 1) {
return F_String_dappend(S2025(), F_String_dappend(FLD(s2023, 0), F_String_dappend(S2026(), F_Chk_dreport__lines(FLD(s2023, 1)))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport__lines(V *a) { (void)a; return F_Chk_dreport__lines(a[0]); }
static V F_IO_dwrite__err(V a0) {
top:;
return F_IO_dprint__err(F_String_dtake(a0, F_Nat_dsub(F_String_dlength(a0), 1u)));
}
static V W_IO_dwrite__err(V *a) { (void)a; return F_IO_dwrite__err(a[0]); }
static V F_List_dis__empty(V a2) {
top:;
V s2027 = a2;
if ((s2027) == IMM(0)) {
return IMM(1);
} else if (TAG(s2027) == 1) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_List_dis__empty(V *a) { (void)a; return F_List_dis__empty(a[2]); }
static V F_Chk_dreport(V a0, V a1) {
top:;
V v2028 = F_Chk_dStr_dunique(F_Chk_dList_ddrop__str2(F_Chk_dbook__order(a0), a1), IMM(0));
V v2029 = F_Chk_dreport_dbad__all(a0, F_Map_dkeys(F_Chk_dBook_dtlds(a0)));
return F_Chk_dreport_dgo(a0, v2028, v2029, F_Chk_dLst_dempty(v2029));
}
static V W_Chk_dreport(V *a) { (void)a; return F_Chk_dreport(a[0], a[1]); }
static V F_Chk_dreport_dgo(V a0, V a1, V a2, V a3) {
top:;
V s2030 = a3;
if ((s2030) == IMM(1)) {
return IMM(0);
} else if ((s2030) == IMM(0)) {
return F_Chk_dStr_dfilter__in(a1, F_Chk_dreport_dclose(F_Chk_dreport_dwalk(a0, a1, F_Set_dnew(), IMM(0)), a2, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dgo(V *a) { (void)a; return F_Chk_dreport_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dreport_dwalk(V a0, V a1, V a2, V a3) {
top:;
V s2031 = a1;
if ((s2031) == IMM(0)) {
return a3;
} else if (TAG(s2031) == 1) {
return F_Chk_dreport_dwalk_done(a0, FLD(s2031, 0), FLD(s2031, 1), F_Set_dhas(a2, FLD(s2031, 0)), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dwalk(V *a) { (void)a; return F_Chk_dreport_dwalk(a[0], a[1], a[2], a[3]); }
static V F_Chk_dreport_dwalk_done(V a0, V a1, V a2, V a3, V a4) {
top:;
V v2032 = a3;
V s2033 = FLD(v2032, 1);
if ((s2033) == IMM(1)) {
return F_Chk_dreport_dwalk(a0, a2, FLD(v2032, 0), a4);
} else if ((s2033) == IMM(0)) {
V v2034 = F_Chk_dtld__refs(F_Chk_dbook__tld(a0, a1));
return F_Chk_dreport_dwalk(a0, F_List_dappend(v2034, a2), F_Set_dadd(FLD(v2032, 0), a1), F_Chk_dreport_duses(v2034, a1, a4));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dwalk_done(V *a) { (void)a; return F_Chk_dreport_dwalk_done(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dreport_duses(V a0, V a1, V a2) {
top:;
V s2035 = a0;
if ((s2035) == IMM(0)) {
return a2;
} else if (TAG(s2035) == 1) {
{ V t0 = FLD(s2035, 1); V t1 = a1; V t2 = C2(1, C2(0, FLD(s2035, 0), a1), a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_duses(V *a) { (void)a; return F_Chk_dreport_duses(a[0], a[1], a[2]); }
static V F_Chk_dtld__refs(V a0) {
top:;
V s2036 = a0;
if (TAG(s2036) == 1 && TAG(FLD(s2036, 0)) == 0) {
return F_Chk_dterm__refs(FLD(FLD(s2036, 0), 2), F_Chk_dtld__refs_dv(FLD(FLD(s2036, 0), 3)));
} else if (TAG(s2036) == 1 && TAG(FLD(s2036, 0)) == 1) {
return F_Chk_drefs_dlist(F_Chk_dCtrD_dts(FLD(FLD(s2036, 0), 3)), IMM(0));
} else if ((s2036) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dtld__refs(V *a) { (void)a; return F_Chk_dtld__refs(a[0]); }
static V F_Chk_dCtrD_dts(V a0) {
top:;
V s2037 = a0;
if ((s2037) == IMM(0)) {
return IMM(0);
} else if (TAG(s2037) == 1) {
return C2(1, FLD(FLD(s2037, 0), 2), F_Chk_dCtrD_dts(FLD(s2037, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCtrD_dts(V *a) { (void)a; return F_Chk_dCtrD_dts(a[0]); }
static V F_Chk_drefs_dlist(V a0, V a1) {
top:;
V s2038 = a0;
if ((s2038) == IMM(0)) {
return a1;
} else if (TAG(s2038) == 1) {
{ V t0 = FLD(s2038, 1); V t1 = F_Chk_dterm__refs(FLD(s2038, 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_drefs_dlist(V *a) { (void)a; return F_Chk_drefs_dlist(a[0], a[1]); }
static V F_Chk_dterm__refs(V a0, V a1) {
top:;
V s2039 = a0;
if (TAG(s2039) == 4) {
return C2(1, FLD(s2039, 0), a1);
} else if (TAG(s2039) == 14) {
return F_Chk_drefs_dlist(FLD(s2039, 1), C2(1, FLD(s2039, 0), a1));
} else if (TAG(s2039) == 1) {
{ V t0 = FLD(s2039, 2); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 3) {
{ V t0 = FLD(s2039, 3); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 5) {
{ V t0 = FLD(s2039, 2); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 6) {
{ V t0 = FLD(s2039, 3); V t1 = F_Chk_drefs_dlist(FLD(s2039, 2), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 7) {
{ V t0 = FLD(s2039, 0); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 10) {
{ V t0 = FLD(s2039, 1); V t1 = F_Chk_dterm__refs(FLD(s2039, 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 11) {
{ V t0 = FLD(s2039, 4); V t1 = F_Chk_dterm__refs(FLD(s2039, 3), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 12) {
{ V t0 = FLD(s2039, 2); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 13) {
{ V t0 = FLD(s2039, 1); V t1 = F_Chk_dterm__refs(FLD(s2039, 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 15) {
return F_Chk_drefs_dlist(FLD(s2039, 1), a1);
} else if (TAG(s2039) == 17) {
{ V t0 = FLD(s2039, 2); V t1 = F_Chk_dterm__refs(FLD(s2039, 1), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 19) {
{ V t0 = FLD(s2039, 2); V t1 = F_Chk_dterm__refs(FLD(s2039, 1), F_Chk_dterm__refs(FLD(s2039, 0), a1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 21) {
{ V t0 = FLD(s2039, 2); V t1 = F_Chk_dterm__refs(FLD(s2039, 1), F_Chk_dterm__refs(FLD(s2039, 0), a1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 23) {
{ V t0 = FLD(s2039, 1); V t1 = F_Chk_dterm__refs(FLD(s2039, 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 24) {
{ V t0 = FLD(s2039, 2); V t1 = F_Chk_drefs_dlist(FLD(s2039, 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 25) {
{ V t0 = FLD(s2039, 2); V t1 = F_Chk_drefs_dlist(FLD(s2039, 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2039) == 31) {
{ V t0 = FLD(s2039, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else {
return a1;
}
}
static V W_Chk_dterm__refs(V *a) { (void)a; return F_Chk_dterm__refs(a[0], a[1]); }
static V F_Chk_dtld__refs_dv(V a0) {
top:;
V s2040 = a0;
if (TAG(s2040) == 1) {
return F_Chk_dterm__refs(FLD(s2040, 0), IMM(0));
} else if ((s2040) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dtld__refs_dv(V *a) { (void)a; return F_Chk_dtld__refs_dv(a[0]); }
static V F_Chk_dreport_dclose(V a0, V a1, V a2) {
top:;
V s2041 = a1;
if ((s2041) == IMM(0)) {
return a2;
} else if (TAG(s2041) == 1) {
return F_Chk_dreport_dclose_dadd(a0, FLD(s2041, 1), a2, F_Chk_dreport_dusers(a0, FLD(s2041, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dclose(V *a) { (void)a; return F_Chk_dreport_dclose(a[0], a[1], a[2]); }
static V F_Chk_dreport_dusers(V a0, V a1) {
top:;
V s2042 = a0;
if ((s2042) == IMM(0)) {
return IMM(0);
} else if (TAG(s2042) == 1) {
return F_Chk_dreport_dusers_dif(FLD(FLD(s2042, 0), 1), F_Chk_dreport_dusers(FLD(s2042, 1), a1), F_String_deq(FLD(FLD(s2042, 0), 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dusers(V *a) { (void)a; return F_Chk_dreport_dusers(a[0], a[1]); }
static V F_Chk_dreport_dusers_dif(V a0, V a1, V a2) {
top:;
V s2043 = a2;
if ((s2043) == IMM(1)) {
return C2(1, a0, a1);
} else if ((s2043) == IMM(0)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dusers_dif(V *a) { (void)a; return F_Chk_dreport_dusers_dif(a[0], a[1], a[2]); }
static V F_Chk_dreport_dclose_dadd(V a0, V a1, V a2, V a3) {
top:;
V s2044 = a3;
if ((s2044) == IMM(0)) {
return F_Chk_dreport_dclose(a0, a1, a2);
} else if (TAG(s2044) == 1) {
return F_Chk_dreport_dclose_dadd_dif(a0, a1, a2, FLD(s2044, 0), FLD(s2044, 1), F_Chk_dStr_dhas(a2, FLD(s2044, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dclose_dadd(V *a) { (void)a; return F_Chk_dreport_dclose_dadd(a[0], a[1], a[2], a[3]); }
static V F_Chk_dreport_dclose_dadd_dif(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2045 = a5;
if ((s2045) == IMM(1)) {
return F_Chk_dreport_dclose_dadd(a0, a1, a2, a4);
} else if ((s2045) == IMM(0)) {
return F_Chk_dreport_dclose_dadd(a0, F_List_dappend(a1, C2(1, a3, IMM(0))), C2(1, a3, a2), a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dclose_dadd_dif(V *a) { (void)a; return F_Chk_dreport_dclose_dadd_dif(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dStr_dfilter__in(V a0, V a1) {
top:;
V s2046 = a0;
if ((s2046) == IMM(0)) {
return IMM(0);
} else if (TAG(s2046) == 1) {
return F_Chk_dStr_dfilter__in_dif(FLD(s2046, 0), F_Chk_dStr_dfilter__in(FLD(s2046, 1), a1), F_Chk_dStr_dhas(a1, FLD(s2046, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dfilter__in(V *a) { (void)a; return F_Chk_dStr_dfilter__in(a[0], a[1]); }
static V F_Chk_dStr_dfilter__in_dif(V a0, V a1, V a2) {
top:;
V s2047 = a2;
if ((s2047) == IMM(1)) {
return C2(1, a0, a1);
} else if ((s2047) == IMM(0)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dfilter__in_dif(V *a) { (void)a; return F_Chk_dStr_dfilter__in_dif(a[0], a[1], a[2]); }
static V F_Chk_dBook_dtlds(V a0) {
top:;
V v2048 = a0;
return FLD(v2048, 0);
}
static V W_Chk_dBook_dtlds(V *a) { (void)a; return F_Chk_dBook_dtlds(a[0]); }
static V F_Map_dkeys(V a2) {
top:;
return F_Map_dkeys_dgo(a2, IMM(0));
}
static V W_Map_dkeys(V *a) { (void)a; return F_Map_dkeys(a[2]); }
static V F_Map_dkeys_dgo(V a2, V a3) {
top:;
V s2049 = a2;
if ((s2049) == IMM(0)) {
return a3;
} else if (TAG(s2049) == 1) {
return C2(1, FLD(s2049, 0), a3);
} else if (TAG(s2049) == 2) {
{ V t0 = FLD(s2049, 1); V t1 = F_Map_dkeys_dgo(FLD(s2049, 2), a3); a2 = t0; a3 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Map_dkeys_dgo(V *a) { (void)a; return F_Map_dkeys_dgo(a[2], a[3]); }
static V F_Chk_dreport_dbad__all(V a0, V a1) {
top:;
V s2050 = a1;
if ((s2050) == IMM(0)) {
return IMM(0);
} else if (TAG(s2050) == 1) {
return F_Chk_dStr_dfilter__in_dif(FLD(s2050, 0), F_Chk_dreport_dbad__all(a0, FLD(s2050, 1)), F_Chk_dTld_dbad(F_Chk_dbook__tld(a0, FLD(s2050, 0))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dbad__all(V *a) { (void)a; return F_Chk_dreport_dbad__all(a[0], a[1]); }
static V F_Chk_dTld_dbad(V a0) {
top:;
V s2051 = a0;
if (TAG(s2051) == 1 && TAG(FLD(s2051, 0)) == 0) {
return F_Bool_dor(FLD(FLD(s2051, 0), 4), F_Bool_dand(F_Maybe_dis__some(FLD(FLD(s2051, 0), 6)), F_Bool_dnot(FLD(FLD(s2051, 0), 5))));
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dbad(V *a) { (void)a; return F_Chk_dTld_dbad(a[0]); }
static V F_Chk_dbook__order(V a0) {
top:;
V v2052 = a0;
return F_List_dreverse(FLD(v2052, 2));
}
static V W_Chk_dbook__order(V *a) { (void)a; return F_Chk_dbook__order(a[0]); }
static V F_Chk_dList_ddrop__str2(V a0, V a1) {
top:;
V s2053 = a0;
V s2054 = a1;
if ((s2054) == 0) {
return s2053;
} else if (TAG(s2053) == 1 && nat_ge(s2054, 1)) {
{ V t0 = FLD(s2053, 1); V t1 = nat_subk(s2054, 1); a0 = t0; a1 = t1; goto top; }
} else if ((s2053) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dList_ddrop__str2(V *a) { (void)a; return F_Chk_dList_ddrop__str2(a[0], a[1]); }
static V F_Chk_dStr_dunique(V a0, V a1) {
top:;
V s2055 = a0;
if ((s2055) == IMM(0)) {
return IMM(0);
} else if (TAG(s2055) == 1) {
return F_Chk_dStr_dunique_dif(FLD(s2055, 0), FLD(s2055, 1), a1, F_Chk_dStr_dhas(a1, FLD(s2055, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dunique(V *a) { (void)a; return F_Chk_dStr_dunique(a[0], a[1]); }
static V F_Chk_dStr_dunique_dif(V a0, V a1, V a2, V a3) {
top:;
V s2056 = a3;
if ((s2056) == IMM(1)) {
return F_Chk_dStr_dunique(a1, a2);
} else if ((s2056) == IMM(0)) {
return C2(1, a0, F_Chk_dStr_dunique(a1, C2(1, a0, a2)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dunique_dif(V *a) { (void)a; return F_Chk_dStr_dunique_dif(a[0], a[1], a[2], a[3]); }
static V S2057(void) { static V c; return STRC(c, ""); }
static V L2058(V *a) {
return F_Main_dcheck_dfin(a[0]);
}
static V F_Main_dcheck(V a0, V a1) {
top:;
return F_IO_dbind(F_Main_dchk_dload(64u, a0, a1, S2057(), IMM(0), C3(0, F_Chk_dbook__nil(), IMM(0), 0u)), mk_clo(L2058, 1, 0, 0));
}
static V W_Main_dcheck(V *a) { (void)a; return F_Main_dcheck(a[0], a[1]); }
static V F_Main_dcheck_dfin(V a0) {
top:;
V v2059 = a0;
return F_Main_dcheck_dres(FLD(v2059, 2), F_Chk_dcheck__book(FLD(v2059, 0)));
}
static V W_Main_dcheck_dfin(V *a) { (void)a; return F_Main_dcheck_dfin(a[0]); }
static V F_Chk_dcheck__book(V a0) {
top:;
V v2060 = a0;
return F_Chk_dcheck__book_dfin(apply(F_Chk_dbook__valid(F_Chk_dbook__order(v2060), v2060), F_Chk_dbook__reset(v2060)));
}
static V W_Chk_dcheck__book(V *a) { (void)a; return F_Chk_dcheck__book(a[0]); }
static V F_Chk_dbook__reset(V a0) {
top:;
V v2061 = a0;
return CN(0, 7, (V[]){IMM(0), IMM(0), FLD(v2061, 2), FLD(v2061, 3), FLD(v2061, 4), FLD(v2061, 5), FLD(v2061, 6)});
}
static V W_Chk_dbook__reset(V *a) { (void)a; return F_Chk_dbook__reset(a[0]); }
static V L2063(V *a) {
return F_Chk_dbook__valid(a[1], a[0]);
}
static V F_Chk_dbook__valid(V a0, V a1) {
top:;
V s2062 = a0;
if ((s2062) == IMM(0)) {
return F_Chk_dK_dpure(IMM(0));
} else if (TAG(s2062) == 1) {
return F_Chk_dK_dbind(F_Chk_dbook__valid_done(FLD(s2062, 0), F_Maybe_ddefault(F_Chk_dbook__tld(a1, FLD(s2062, 0)), CN(1, 5, (V[]){0u, 0u, C1(8, IMM(0)), IMM(0), IMM(0)})), F_Bool_dnot(F_Chk_dStr_dhas(FLD(s2062, 1), FLD(s2062, 0)))), mk_clo(L2063, 3, 2, (V[]){a1, FLD(s2062, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dbook__valid(V *a) { (void)a; return F_Chk_dbook__valid(a[0], a[1]); }
static V L2066(V *a) {
return F_Chk_dvalid_dadt(a[3], a[2], a[1], a[0]);
}
static V L2065(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dset__book(F_Chk_dbook__set__ctrs(F_Chk_dbook__set(a[5], a[4], a[3]), a[2])), mk_clo(L2066, 5, 4, (V[]){a[2], a[0], a[1], a[4]}));
}
static V F_Chk_dbook__valid_done(V a0, V a1, V a2) {
top:;
V s2064 = a1;
if (TAG(s2064) == 1) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2065, 6, 5, (V[]){FLD(s2064, 2), FLD(s2064, 0), FLD(s2064, 3), a1, a0}));
} else if (TAG(s2064) == 0) {
return F_Chk_dvalid_ddef(a0, a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dbook__valid_done(V *a) { (void)a; return F_Chk_dbook__valid_done(a[0], a[1], a[2]); }
static V L2075(V *a) {
return F_Chk_dK_dset__book(F_Chk_dbook__set(a[2], a[1], a[0]));
}
static V L2074(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2075, 3, 2, (V[]){a[0], a[1]}));
}
static V L2073(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dif(F_Maybe_dis__some(F_Chk_dTld_ddval(a[1])), F_Chk_ddef__check(a[0], a[1], 0u), F_Chk_dK_dpure(IMM(0))), mk_clo(L2074, 3, 2, (V[]){a[1], a[0]}));
}
static V L2072(V *a) {
return F_Chk_dK_dbind(F_Chk_dvalid_dforeign(a[1], a[0], F_Chk_dTld_dimps(a[0])), mk_clo(L2073, 3, 2, (V[]){a[1], a[0]}));
}
static V L2071(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(F_Chk_dCL_dof(a[0], F_Chk_dTld_ddu(a[1])), F_Chk_dTld_dt(a[1]), IMM(0), F_Chk_dtyp(IMM(1)), IMM(0), 0u), mk_clo(L2072, 3, 2, (V[]){a[1], a[0]}));
}
static V L2070(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Bool_dpick(a[2], a[1], F_Chk_dTld_ddec(a[1]))), mk_clo(L2071, 2, 1, (V[]){a[0]}));
}
static V L2069(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dset__book(F_Chk_dbook__set(a[3], a[2], F_Chk_dTld_ddec(a[1]))), mk_clo(L2070, 4, 3, (V[]){a[2], a[1], a[0]}));
}
static V L2068(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Bool_dpick(a[4], F_Chk_dbook__opened(a[3]), a[3])), mk_clo(L2069, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L2067(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Bool_dand(a[2], F_Chk_dTld_dis__law__open(a[1]))), mk_clo(L2068, 5, 4, (V[]){a[2], a[1], a[0], a[3]}));
}
static V F_Chk_dvalid_ddef(V a0, V a1, V a2) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2067, 4, 3, (V[]){a0, a1, a2}));
}
static V W_Chk_dvalid_ddef(V *a) { (void)a; return F_Chk_dvalid_ddef(a[0], a[1], a[2]); }
static V F_Chk_dbook__set(V a0, V a1, V a2) {
top:;
V v2076 = a0;
return CN(0, 7, (V[]){F_Map_dset(FLD(v2076, 0), a1, a2), FLD(v2076, 1), FLD(v2076, 2), FLD(v2076, 3), FLD(v2076, 4), FLD(v2076, 5), FLD(v2076, 6)});
}
static V W_Chk_dbook__set(V *a) { (void)a; return F_Chk_dbook__set(a[0], a[1], a[2]); }
static V L2077(V *a) {
return C1(1, C2(0, IMM(0), a[0]));
}
static V F_Chk_dK_dset__book(V a0) {
top:;
return mk_clo(L2077, 2, 1, (V[]){a0});
}
static V W_Chk_dK_dset__book(V *a) { (void)a; return F_Chk_dK_dset__book(a[0]); }
static V L2078(V *a) {
return C1(1, C2(0, a[0], a[0]));
}
static V F_Chk_dK_dbook(void) {
top:;
return mk_clo(L2078, 1, 0, 0);
}
static V W_Chk_dK_dbook(V *a) { (void)a; return F_Chk_dK_dbook(); }
static V L2079(V *a) {
return F_Chk_dK_dgo(apply(a[1], a[4]), a[0]);
}
static V F_Chk_dK_dbind(V a2, V a3) {
top:;
return mk_clo(L2079, 5, 4, (V[]){a3, a2, 0, 0});
}
static V W_Chk_dK_dbind(V *a) { (void)a; return F_Chk_dK_dbind(a[2], a[3]); }
static V F_Chk_dK_dgo(V a2, V a3) {
top:;
V s2080 = a2;
if (TAG(s2080) == 0) {
return C1(0, FLD(s2080, 0));
} else if (TAG(s2080) == 1) {
return F_Chk_dK_dgo_ddone(FLD(s2080, 0), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dK_dgo(V *a) { (void)a; return F_Chk_dK_dgo(a[2], a[3]); }
static V F_Chk_dK_dgo_ddone(V a2, V a3) {
top:;
V v2081 = a2;
return apply(apply(a3, FLD(v2081, 0)), FLD(v2081, 1));
}
static V W_Chk_dK_dgo_ddone(V *a) { (void)a; return F_Chk_dK_dgo_ddone(a[2], a[3]); }
static V L2082(V *a) {
return C1(1, C2(0, a[0], a[1]));
}
static V F_Chk_dK_dpure(V a1) {
top:;
return mk_clo(L2082, 2, 1, (V[]){a1});
}
static V W_Chk_dK_dpure(V *a) { (void)a; return F_Chk_dK_dpure(a[1]); }
static V L2085(V *a) {
return F_Chk_ddef__check_dgo(a[4], a[3], a[2], a[1], a[5], a[0], F_Nat_dis__gt(F_Chk_dTld_dx__of(a[3]), 0u));
}
static V L2084(V *a) {
return F_Chk_dK_dbind(F_Chk_ddef__check_dtmpl(a[3], F_Chk_dTld_dx__of(a[2]), C3(4, a[3], IMM(0), IMM(0)), F_Maybe_ddefault(F_Chk_dTld_ddval(a[2]), C1(18, IMM(0))), F_Chk_dTld_dt(a[2])), mk_clo(L2085, 6, 5, (V[]){a[0], a[4], a[1], a[2], a[3]}));
}
static V L2083(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dDom_dqs(F_Pair_dfst(F_Chk_dtele__unbind(a[3], F_Chk_dTld_dt(a[2]))))), mk_clo(L2084, 5, 4, (V[]){a[3], a[0], a[2], a[1]}));
}
static V F_Chk_ddef__check(V a0, V a1, V a2) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2083, 4, 3, (V[]){a2, a0, a1}));
}
static V W_Chk_ddef__check(V *a) { (void)a; return F_Chk_ddef__check(a[0], a[1], a[2]); }
static V F_Chk_dTld_dx__of(V a0) {
top:;
V s2086 = a0;
if (TAG(s2086) == 0) {
return FLD(s2086, 1);
} else {
return 0u;
}
}
static V W_Chk_dTld_dx__of(V *a) { (void)a; return F_Chk_dTld_dx__of(a[0]); }
static V L2090(V *a) {
return F_Chk_dK_dset__book(F_Bool_dpick(a[1], a[0], a[2]));
}
static V L2089(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2090, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_ddef__check_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2087 = a4;
V v2088 = FLD(v2087, 1);
return F_Chk_dK_dbind(F_Chk_dterm__check(CN(0, 6, (V[]){FLD(v2087, 0), F_Nat_dsub(F_Chk_dTld_ddn(a1), F_Chk_dTld_dx__of(a1)), a0, a3, F_Chk_dTld_ddu(a1), a2}), FLD(v2088, 0), IMM(1), FLD(v2088, 1), IMM(0), 0u), mk_clo(L2089, 3, 2, (V[]){a5, a6}));
}
static V W_Chk_ddef__check_dgo(V *a) { (void)a; return F_Chk_ddef__check_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dTld_ddu(V a0) {
top:;
V s2091 = a0;
if (TAG(s2091) == 0) {
return FLD(s2091, 4);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_ddu(V *a) { (void)a; return F_Chk_dTld_ddu(a[0]); }
static V F_Chk_dTld_ddn(V a0) {
top:;
V s2092 = a0;
if (TAG(s2092) == 0) {
return FLD(s2092, 0);
} else {
return 0u;
}
}
static V W_Chk_dTld_ddn(V *a) { (void)a; return F_Chk_dTld_ddn(a[0]); }
static V L2094(V *a) {
return F_Chk_dcheck_dlam(a[8], a[7], a[6], a[5], a[4], F_Chk_dterm__wnf(a[9], a[3]), a[2], a[3], a[1], a[0]);
}
static V L2095(V *a) {
return F_Chk_dcheck_dlet_dbody(a[9], a[8], a[7], a[6], a[5], a[4], a[3], a[2], a[1], a[0], a[10]);
}
static V L2096(V *a) {
return F_Chk_dcheck_dctr(a[7], a[6], a[5], a[4], F_Chk_dterm__wnf(a[8], a[3]), a[2], a[3], a[1], a[0]);
}
static V L2097(V *a) {
return F_Chk_dcheck_dlit(a[6], C2(16, a[5], a[4]), F_Chk_dterm__wnf(a[7], a[3]), a[2], a[3], a[1], a[0]);
}
static V L2098(V *a) {
return F_Chk_dcheck_delim(a[8], C4(17, a[7], a[6], a[5], a[4]), a[4], F_Chk_dterm__wnf(a[9], a[3]), a[2], a[3], a[1], a[0]);
}
static V L2099(V *a) {
return F_Chk_dcheck_delim(a[5], C1(18, a[4]), a[4], F_Chk_dterm__wnf(a[6], a[3]), a[2], a[3], a[1], a[0]);
}
static V L2100(V *a) {
return F_Chk_dcheck_drfl(a[4], a[3], F_Chk_dterm__wnf(a[5], a[2]), a[2], a[1], a[0]);
}
static V S2101(void) { static V c; return STRC(c, "TODO"); }
static V L2103(V *a) {
return F_Chk_dcheck_drwt(a[9], a[8], a[7], a[6], a[5], a[4], F_Chk_dterm__wnf(a[10], F_Chk_dIR_dty(a[4])), a[3], a[2], a[1], a[0]);
}
static V L2102(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2103, 11, 10, (V[]){a[0], a[1], a[2], a[3], a[9], a[4], a[5], a[6], a[7], a[8]}));
}
static V F_Chk_dterm__check(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2093 = a1;
if (TAG(s2093) == 1) {
{ V t0 = a0; V t1 = FLD(s2093, 2); V t2 = a2; V t3 = a3; V t4 = a4; V t5 = a5; a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; a5 = t5; goto top; }
} else if (TAG(s2093) == 12) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2094, 10, 9, (V[]){a5, a4, a2, a3, FLD(s2093, 4), FLD(s2093, 3), FLD(s2093, 2), FLD(s2093, 0), a0}));
} else if (TAG(s2093) == 6) {
return F_Chk_dK_dbind(F_Chk_dcheck_dlets(a0, FLD(s2093, 0), FLD(s2093, 2), FLD(s2093, 5), a2, a4, a4, a5, 0u, IMM(0)), mk_clo(L2095, 11, 10, (V[]){a5, a4, a3, a2, FLD(s2093, 5), FLD(s2093, 4), FLD(s2093, 3), FLD(s2093, 2), FLD(s2093, 0), a0}));
} else if (TAG(s2093) == 15) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2096, 9, 8, (V[]){a5, a4, a2, a3, FLD(s2093, 2), FLD(s2093, 1), FLD(s2093, 0), a0}));
} else if (TAG(s2093) == 16) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2097, 8, 7, (V[]){a5, a4, a2, a3, FLD(s2093, 1), FLD(s2093, 0), a0}));
} else if (TAG(s2093) == 17) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2098, 10, 9, (V[]){a5, a4, a2, a3, FLD(s2093, 3), FLD(s2093, 2), FLD(s2093, 1), FLD(s2093, 0), a0}));
} else if (TAG(s2093) == 18) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2099, 7, 6, (V[]){a5, a4, a2, a3, FLD(s2093, 0), a0}));
} else if (TAG(s2093) == 20) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2100, 6, 5, (V[]){a5, a4, a3, FLD(s2093, 0), a0}));
} else if (TAG(s2093) == 22) {
return F_Chk_dK_dif(F_String_deq(FLD(s2093, 0), S2101()), F_Chk_dK_dpure(IMM(0)), F_Chk_dK_derr(a4, C1(2, a3), C1(2, C2(22, FLD(s2093, 0), FLD(s2093, 1))), FLD(s2093, 1), F_Chk_dCL_ddn(a0)));
} else if (TAG(s2093) == 21) {
return F_Chk_dK_dbind(F_Chk_dterm__infer(a0, FLD(s2093, 0), a2, a4, a5, IMM(0)), mk_clo(L2102, 10, 9, (V[]){a5, a4, a3, a2, FLD(s2093, 3), FLD(s2093, 2), FLD(s2093, 1), FLD(s2093, 0), a0}));
} else {
return F_Chk_dcheck_dinfer(a0, s2093, a2, a3, a4, a5);
}
}
static V W_Chk_dterm__check(V *a) { (void)a; return F_Chk_dterm__check(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L2105(V *a) {
return F_Chk_dcheck_dinfer_dcmp(a[5], a[4], a[3], a[2], a[1], a[0], F_Chk_dterm__compare(IMM(1), a[6], F_Chk_dIR_dty(a[3]), a[2], a[0]));
}
static V L2104(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2105, 7, 6, (V[]){a[0], a[1], a[2], a[5], a[3], a[4]}));
}
static V F_Chk_dcheck_dinfer(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dK_dbind(F_Chk_dterm__infer(a0, a1, a2, a4, a5, IMM(0)), mk_clo(L2104, 6, 5, (V[]){a5, a4, a3, a1, a0}));
}
static V W_Chk_dcheck_dinfer(V *a) { (void)a; return F_Chk_dcheck_dinfer(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dIR_dty(V a0) {
top:;
V v2106 = a0;
return FLD(v2106, 0);
}
static V W_Chk_dIR_dty(V *a) { (void)a; return F_Chk_dIR_dty(a[0]); }
static V F_Chk_dterm__compare(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Chk_dcmp_dwnf(a0, a1, F_Chk_dterm__wnf(a1, a2), F_Chk_dterm__wnf(a1, a3), a4);
}
static V W_Chk_dterm__compare(V *a) { (void)a; return F_Chk_dterm__compare(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dcmp_dwnf(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Chk_dcmp_dlam(a0, a1, a2, a3, a4, F_Bool_dor(F_Chk_dTm_dis__lam(a2), F_Chk_dTm_dis__lam(a3)));
}
static V W_Chk_dcmp_dwnf(V *a) { (void)a; return F_Chk_dcmp_dwnf(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dTm_dis__lam(V a0) {
top:;
V s2107 = a0;
if (TAG(s2107) == 12) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__lam(V *a) { (void)a; return F_Chk_dTm_dis__lam(a[0]); }
static V F_Chk_dcmp_dlam(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2108 = a5;
if ((s2108) == IMM(1)) {
V v2109 = C3(0, F_Chk_dTm_dlam__k(a2, a3), a4, IMM(0));
return F_Chk_dterm__compare(a0, a1, F_Chk_dterm__apply1(a1, a2, v2109), F_Chk_dterm__apply1(a1, a3, v2109), F_U32_dinc(a4));
} else if ((s2108) == IMM(0)) {
return F_Chk_dcmp_dgo(a0, a1, F_Chk_dcmp_dlit(a2, a3), F_Chk_dcmp_dlit(a3, a2), a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcmp_dlam(V *a) { (void)a; return F_Chk_dcmp_dlam(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dcmp_dlit(V a0, V a1) {
top:;
return F_Bool_dpick(F_Bool_dand(F_Chk_dTm_dis__lit(a0), F_Chk_dTm_dis__ctr(a1)), F_Chk_dlit__step(a0), a0);
}
static V W_Chk_dcmp_dlit(V *a) { (void)a; return F_Chk_dcmp_dlit(a[0], a[1]); }
static V F_Chk_dTm_dis__ctr(V a0) {
top:;
V s2110 = a0;
if (TAG(s2110) == 15) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__ctr(V *a) { (void)a; return F_Chk_dTm_dis__ctr(a[0]); }
static V F_Chk_dTm_dis__lit(V a0) {
top:;
V s2111 = a0;
if (TAG(s2111) == 16) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__lit(V *a) { (void)a; return F_Chk_dTm_dis__lit(a[0]); }
static V F_Chk_dcmp_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2112 = a2;
V s2113 = a3;
if (TAG(s2112) == 0 && TAG(s2113) == 0) {
return F_U32_dis__eq(FLD(s2112, 1), FLD(s2113, 1));
} else if (TAG(s2112) == 4 && TAG(s2113) == 4) {
return F_String_deq(FLD(s2112, 0), FLD(s2113, 0));
} else if (TAG(s2112) == 7 && TAG(s2113) == 7) {
return F_Chk_dcmp_dtyp(a0, a1, FLD(s2112, 0), FLD(s2113, 0), a4);
} else if (TAG(s2112) == 8 && TAG(s2113) == 8) {
return IMM(1);
} else if (TAG(s2112) == 9 && TAG(s2113) == 9) {
return F_Chk_dQ_deq(FLD(s2112, 0), FLD(s2113, 0));
} else if (TAG(s2112) == 10 && TAG(s2113) == 10) {
return F_Bool_dand(F_Chk_dterm__compare(IMM(0), a1, FLD(s2112, 0), FLD(s2113, 0), a4), F_Chk_dterm__compare(IMM(0), a1, FLD(s2112, 1), FLD(s2113, 1), a4));
} else if (TAG(s2112) == 11 && TAG(s2113) == 11) {
V v2114 = C3(0, FLD(s2112, 1), a4, IMM(0));
return F_Bool_dand(F_Chk_dQ_deq(FLD(s2112, 0), FLD(s2113, 0)), F_Bool_dand(F_Chk_dterm__compare(a0, a1, FLD(s2113, 3), FLD(s2112, 3), a4), F_Chk_dterm__compare(a0, a1, F_Chk_dclo__apply(a1, FLD(s2112, 4), C2(1, v2114, IMM(0))), F_Chk_dclo__apply(a1, FLD(s2113, 4), C2(1, v2114, IMM(0))), F_U32_dinc(a4))));
} else if (TAG(s2112) == 13 && TAG(s2113) == 13) {
return F_Bool_dand(F_Chk_dterm__compare(IMM(0), a1, FLD(s2112, 0), FLD(s2113, 0), a4), F_Chk_dterm__compare(IMM(0), a1, FLD(s2112, 1), FLD(s2113, 1), a4));
} else if (TAG(s2112) == 14 && TAG(s2113) == 14) {
return F_Bool_dand(F_Bool_dand(F_String_deq(FLD(s2112, 0), FLD(s2113, 0)), F_Nat_dis__eq(F_List_dlength(FLD(s2112, 1)), F_List_dlength(FLD(s2113, 1)))), F_Bool_dand(F_Bool_dor(a0, F_Nat_dis__eq(F_List_dlength(FLD(s2112, 3)), F_List_dlength(FLD(s2113, 3)))), F_Bool_dand(F_Chk_dStr_dsubset(FLD(s2113, 3), FLD(s2112, 3)), F_Chk_dcmps(FLD(s2112, 1), FLD(s2113, 1), a1, a4))));
} else if (TAG(s2112) == 15 && TAG(s2113) == 15) {
return F_Bool_dand(F_Bool_dand(F_String_deq(FLD(s2112, 0), FLD(s2113, 0)), F_Nat_dis__eq(F_List_dlength(FLD(s2112, 1)), F_List_dlength(FLD(s2113, 1)))), F_Chk_dcmps(FLD(s2112, 1), FLD(s2113, 1), a1, a4));
} else if (TAG(s2112) == 16 && TAG(FLD(s2112, 0)) == 0 && TAG(s2113) == 16 && TAG(FLD(s2113, 0)) == 0) {
return F_Nat_dis__eq(FLD(FLD(s2112, 0), 0), FLD(FLD(s2113, 0), 0));
} else if (TAG(s2112) == 16 && TAG(FLD(s2112, 0)) == 1 && TAG(s2113) == 16 && TAG(FLD(s2113, 0)) == 1) {
return F_String_deq(FLD(FLD(s2112, 0), 0), FLD(FLD(s2113, 0), 0));
} else if (TAG(s2112) == 17 && TAG(s2113) == 17) {
return F_Bool_dand(F_String_deq(FLD(s2112, 0), FLD(s2113, 0)), F_Bool_dand(F_Chk_dterm__compare(IMM(0), a1, FLD(s2112, 1), FLD(s2113, 1), a4), F_Chk_dterm__compare(IMM(0), a1, FLD(s2112, 2), FLD(s2113, 2), a4)));
} else if (TAG(s2112) == 18 && TAG(s2113) == 18) {
return IMM(1);
} else if (TAG(s2112) == 19 && TAG(s2113) == 19) {
return F_Bool_dand(F_Chk_dterm__compare(IMM(0), a1, FLD(s2112, 0), FLD(s2113, 0), a4), F_Bool_dand(F_Chk_dterm__compare(IMM(0), a1, FLD(s2112, 1), FLD(s2113, 1), a4), F_Chk_dterm__compare(IMM(0), a1, FLD(s2112, 2), FLD(s2113, 2), a4)));
} else if (TAG(s2112) == 20 && TAG(s2113) == 20) {
return IMM(1);
} else if (TAG(s2112) == 22 && TAG(s2113) == 22) {
return F_String_deq(FLD(s2112, 0), FLD(s2113, 0));
} else if (TAG(s2112) == 21 && TAG(s2113) == 21) {
return F_Bool_dand(F_Chk_dterm__compare(IMM(0), a1, FLD(s2112, 0), FLD(s2113, 0), a4), F_Bool_dand(F_Chk_dterm__compare(IMM(0), a1, FLD(s2112, 1), FLD(s2113, 1), a4), F_Chk_dterm__compare(IMM(0), a1, FLD(s2112, 2), FLD(s2113, 2), a4)));
} else {
return IMM(0);
}
}
static V W_Chk_dcmp_dgo(V *a) { (void)a; return F_Chk_dcmp_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dcmps(V a0, V a1, V a2, V a3) {
top:;
V s2115 = a0;
V s2116 = a1;
if (TAG(s2115) == 1 && TAG(s2116) == 1) {
return F_Bool_dand(F_Chk_dterm__compare(IMM(0), a2, FLD(s2115, 0), FLD(s2116, 0), a3), F_Chk_dcmps(FLD(s2115, 1), FLD(s2116, 1), a2, a3));
} else if ((s2115) == IMM(0) && (s2116) == IMM(0)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dcmps(V *a) { (void)a; return F_Chk_dcmps(a[0], a[1], a[2], a[3]); }
static V F_Chk_dStr_dsubset(V a0, V a1) {
top:;
V s2117 = a0;
if ((s2117) == IMM(0)) {
return IMM(1);
} else if (TAG(s2117) == 1) {
return F_Bool_dand(F_Chk_dStr_dhas(a1, FLD(s2117, 0)), F_Chk_dStr_dsubset(FLD(s2117, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dsubset(V *a) { (void)a; return F_Chk_dStr_dsubset(a[0], a[1]); }
static V F_Chk_dQ_deq(V a0, V a1) {
top:;
V s2118 = a0;
V s2119 = a1;
if ((s2118) == IMM(0) && (s2119) == IMM(0)) {
return IMM(1);
} else if ((s2118) == IMM(1) && (s2119) == IMM(1)) {
return IMM(1);
} else if ((s2118) == IMM(2) && (s2119) == IMM(2)) {
return IMM(1);
} else if ((s2118) == IMM(3) && (s2119) == IMM(3)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dQ_deq(V *a) { (void)a; return F_Chk_dQ_deq(a[0], a[1]); }
static V F_Chk_dcmp_dtyp(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2120 = a0;
if ((s2120) == IMM(0)) {
return F_Chk_dterm__compare(IMM(0), a1, a2, a3, a4);
} else if ((s2120) == IMM(1)) {
return F_Chk_dcmp_dkind(a1, F_Chk_dterm__wnf(a1, a2), F_Chk_dterm__wnf(a1, a3), a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcmp_dtyp(V *a) { (void)a; return F_Chk_dcmp_dtyp(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dcmp_dkind(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dcmp_dkind_dgo(a0, a1, a2, a3, F_Bool_dor(F_Chk_dTm_dis__many(a1), F_Chk_dTm_dis__qua__not__many(a2)));
}
static V W_Chk_dcmp_dkind(V *a) { (void)a; return F_Chk_dcmp_dkind(a[0], a[1], a[2], a[3]); }
static V F_Chk_dTm_dis__qua__not__many(V a0) {
top:;
V s2121 = a0;
if (TAG(s2121) == 9 && (FLD(s2121, 0)) == IMM(2)) {
return IMM(0);
} else if (TAG(s2121) == 9) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__qua__not__many(V *a) { (void)a; return F_Chk_dTm_dis__qua__not__many(a[0]); }
static V F_Chk_dTm_dis__many(V a0) {
top:;
V s2122 = a0;
if (TAG(s2122) == 9 && (FLD(s2122, 0)) == IMM(2)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__many(V *a) { (void)a; return F_Chk_dTm_dis__many(a[0]); }
static V F_Chk_dcmp_dkind_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2123 = a4;
if ((s2123) == IMM(1)) {
return IMM(1);
} else if ((s2123) == IMM(0)) {
return F_Chk_dcmp_dkind_dmin(a0, a1, a2, a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcmp_dkind_dgo(V *a) { (void)a; return F_Chk_dcmp_dkind_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dcmp_dkind_dmin(V a0, V a1, V a2, V a3) {
top:;
V s2124 = a1;
if (TAG(s2124) == 10) {
return F_Bool_dand(F_Chk_dterm__compare(IMM(1), a0, C2(7, FLD(s2124, 0), IMM(0)), C2(7, a2, IMM(0)), a3), F_Chk_dterm__compare(IMM(1), a0, C2(7, FLD(s2124, 1), IMM(0)), C2(7, a2, IMM(0)), a3));
} else {
return F_Chk_dcmp_dkind_drmin(a0, s2124, a2, a3);
}
}
static V W_Chk_dcmp_dkind_dmin(V *a) { (void)a; return F_Chk_dcmp_dkind_dmin(a[0], a[1], a[2], a[3]); }
static V F_Chk_dcmp_dkind_drmin(V a0, V a1, V a2, V a3) {
top:;
V s2125 = a2;
if (TAG(s2125) == 10) {
return F_Bool_dor(F_Chk_dterm__compare(IMM(1), a0, C2(7, a1, IMM(0)), C2(7, FLD(s2125, 0), IMM(0)), a3), F_Chk_dterm__compare(IMM(1), a0, C2(7, a1, IMM(0)), C2(7, FLD(s2125, 1), IMM(0)), a3));
} else {
return F_Chk_dterm__compare(IMM(1), a0, a1, s2125, a3);
}
}
static V W_Chk_dcmp_dkind_drmin(V *a) { (void)a; return F_Chk_dcmp_dkind_drmin(a[0], a[1], a[2], a[3]); }
static V F_Chk_dterm__apply1(V a0, V a1, V a2) {
top:;
return F_Chk_dterm__apply(a0, a1, a2, IMM(0));
}
static V W_Chk_dterm__apply1(V *a) { (void)a; return F_Chk_dterm__apply1(a[0], a[1], a[2]); }
static V S2128(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dTm_dlam__k(V a0, V a1) {
top:;
V s2126 = a0;
V s2127 = a1;
if (TAG(s2126) == 12) {
return FLD(s2126, 0);
} else if (TAG(s2127) == 12) {
return FLD(s2127, 0);
} else {
return S2128();
}
}
static V W_Chk_dTm_dlam__k(V *a) { (void)a; return F_Chk_dTm_dlam__k(a[0], a[1]); }
static V F_Chk_dcheck_dinfer_dcmp(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2129 = a2;
V s2130 = a6;
if ((s2130) == IMM(1)) {
return F_Chk_dK_dpure(FLD(v2129, 1));
} else if ((s2130) == IMM(0)) {
return F_Chk_dK_derr(a4, C1(2, a3), C1(2, FLD(v2129, 0)), F_Chk_dTm_dspan(a1), F_Chk_dCL_ddn(a0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcheck_dinfer_dcmp(V *a) { (void)a; return F_Chk_dcheck_dinfer_dcmp(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dCL_ddn(V a0) {
top:;
V v2131 = a0;
return FLD(v2131, 2);
}
static V W_Chk_dCL_ddn(V *a) { (void)a; return F_Chk_dCL_ddn(a[0]); }
static V L2132(V *a) {
return C1(0, F_Chk_derr(a[5], a[4], a[3], a[2], a[1], a[0]));
}
static V F_Chk_dK_derr(V a1, V a2, V a3, V a4, V a5) {
top:;
return mk_clo(L2132, 6, 5, (V[]){a5, a4, a3, a2, a1});
}
static V W_Chk_dK_derr(V *a) { (void)a; return F_Chk_dK_derr(a[1], a[2], a[3], a[4], a[5]); }
static V S2133(void) { static V c; return STRC(c, ""); }
static V F_Chk_derr(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return CN(0, 7, (V[]){a0, a1, a2, a3, a4, a5, S2133()});
}
static V W_Chk_derr(V *a) { (void)a; return F_Chk_derr(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L2135(V *a) {
return F_Chk_dinfer_dref(a[7], a[6], a[5], a[4], F_Chk_dbook__tld(a[8], a[6]), a[3], a[2], a[1], a[0]);
}
static V L2136(V *a) {
return F_Chk_dK_dpure(C3(0, F_Chk_dtyp(IMM(1)), IMM(0), 0u));
}
static V L2138(V *a) {
return F_Chk_dK_dpure(C3(0, C1(8, a[1]), F_Chk_duses__add(a[0], a[2]), 0u));
}
static V L2137(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[5], a[4], a[3], C1(8, a[2]), a[1], a[0]), mk_clo(L2138, 3, 2, (V[]){a[6], a[2]}));
}
static V L2141(V *a) {
return F_Chk_dK_dpure(C3(0, F_Chk_dtyp(IMM(1)), IMM(0), 0u));
}
static V L2140(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[6], F_Chk_dclo__apply(a[7], a[5], C2(1, C3(0, a[4], a[3], IMM(0)), IMM(0))), IMM(0), F_Chk_dtyp(IMM(1)), F_Chk_dctx__bind(a[2], a[3], a[1], a[4], a[0]), F_U32_dinc(a[3])), mk_clo(L2141, 1, 0, 0));
}
static V L2139(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2140, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L2142(V *a) {
return F_Chk_dinfer_dapp(a[5], a[6], a[4], a[3], a[2], a[1], a[0]);
}
static V L2143(V *a) {
return F_Chk_dinfer_dadt(a[6], a[7], a[5], a[4], a[3], a[2], a[1], a[0]);
}
static V L2146(V *a) {
return F_Chk_dK_dpure(C3(0, F_Chk_dtyp(IMM(2)), IMM(0), 0u));
}
static V L2145(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[4], a[3], IMM(0), a[2], a[1], a[0]), mk_clo(L2146, 1, 0, 0));
}
static V L2144(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[5], a[4], IMM(0), a[3], a[2], a[1]), mk_clo(L2145, 6, 5, (V[]){a[1], a[2], a[3], a[0], a[5]}));
}
static V L2148(V *a) {
return F_Chk_dK_dpure(C3(0, a[0], a[1], 0u));
}
static V L2147(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[5], a[4], a[3], a[2], a[1], a[0]), mk_clo(L2148, 2, 1, (V[]){a[2]}));
}
static V F_Chk_dterm__infer(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2134 = a1;
if (TAG(s2134) == 1) {
{ V t0 = a0; V t1 = FLD(s2134, 2); V t2 = a2; V t3 = a3; V t4 = a4; V t5 = a5; a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; a5 = t5; goto top; }
} else if (TAG(s2134) == 0) {
return F_Chk_dinfer_dvar(C3(0, FLD(s2134, 0), FLD(s2134, 1), FLD(s2134, 2)), FLD(s2134, 1), a2, a3, FLD(s2134, 2), a0);
} else if (TAG(s2134) == 3) {
return F_Chk_dinfer_dvar(C3(0, FLD(s2134, 0), FLD(s2134, 1), FLD(s2134, 2)), FLD(s2134, 1), a2, a3, FLD(s2134, 2), a0);
} else if (TAG(s2134) == 4) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2135, 9, 8, (V[]){a5, a4, a3, a2, FLD(s2134, 2), FLD(s2134, 1), FLD(s2134, 0), a0}));
} else if (TAG(s2134) == 7) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a0, FLD(s2134, 0), IMM(0), C1(8, FLD(s2134, 1)), a3, a4), mk_clo(L2136, 1, 0, 0));
} else if (TAG(s2134) == 8) {
return F_Chk_dK_dpure(C3(0, F_Chk_dtyp(IMM(1)), IMM(0), 0u));
} else if (TAG(s2134) == 9) {
return F_Chk_dK_dpure(C3(0, C1(8, FLD(s2134, 1)), IMM(0), 0u));
} else if (TAG(s2134) == 10) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a0, FLD(s2134, 0), a2, C1(8, FLD(s2134, 2)), a3, a4), mk_clo(L2137, 7, 6, (V[]){a4, a3, FLD(s2134, 2), a2, FLD(s2134, 1), a0}));
} else if (TAG(s2134) == 11) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a0, FLD(s2134, 3), IMM(0), F_Chk_dtyp(F_Chk_dlhs__kind(a0, FLD(s2134, 0))), a3, a4), mk_clo(L2139, 8, 7, (V[]){FLD(s2134, 3), FLD(s2134, 0), a3, a4, FLD(s2134, 1), FLD(s2134, 4), a0}));
} else if (TAG(s2134) == 13) {
return F_Chk_dK_dbind(F_Chk_dterm__infer(a0, FLD(s2134, 0), a2, a3, a4, C2(1, FLD(s2134, 1), a5)), mk_clo(L2142, 7, 6, (V[]){FLD(s2134, 2), a4, a3, a2, FLD(s2134, 1), a0}));
} else if (TAG(s2134) == 14) {
return F_Chk_dK_dbind(F_Chk_dbook__adt(C4(14, FLD(s2134, 0), FLD(s2134, 1), FLD(s2134, 2), FLD(s2134, 3)), a3, F_Chk_dCL_ddn(a0)), mk_clo(L2143, 8, 7, (V[]){a4, a3, a2, FLD(s2134, 2), FLD(s2134, 1), FLD(s2134, 0), a0}));
} else if (TAG(s2134) == 19) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a0, FLD(s2134, 2), IMM(0), F_Chk_dtyp(IMM(1)), a3, a4), mk_clo(L2144, 7, 6, (V[]){FLD(s2134, 1), a4, a3, FLD(s2134, 2), FLD(s2134, 0), a0}));
} else if (TAG(s2134) == 23) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a0, FLD(s2134, 1), IMM(0), F_Chk_dtyp(IMM(1)), a3, a4), mk_clo(L2147, 7, 6, (V[]){a4, a3, FLD(s2134, 1), a2, FLD(s2134, 0), a0}));
} else {
return F_Chk_dinfer_dfail(a0, s2134, a3);
}
}
static V W_Chk_dterm__infer(V *a) { (void)a; return F_Chk_dterm__infer(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S2152(void) { static V c; return STRC(c, "a declared constructor"); }
static V S2153(void) { static V c; return STRC(c, "an annotated term (cannot infer)"); }
static V L2151(V *a) {
return F_Chk_dK_derr(a[2], C1(1, F_Bool_dpick(a[3], S2152(), S2153())), C1(2, a[1]), F_Chk_dTm_dspan(a[1]), F_Chk_dCL_ddn(a[0]));
}
static V L2150(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Bool_dand(F_Chk_dTm_dis__ctr(a[4]), F_Bool_dnot(F_Maybe_dis__some(F_Chk_dbook__ctr(a[3], F_Chk_dTm_dname(a[4])))))), mk_clo(L2151, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L2149(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dlit__ctr(a[2])), mk_clo(L2150, 5, 4, (V[]){a[0], a[2], a[1], a[3]}));
}
static V F_Chk_dinfer_dfail(V a0, V a1, V a2) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2149, 4, 3, (V[]){a0, a2, a1}));
}
static V W_Chk_dinfer_dfail(V *a) { (void)a; return F_Chk_dinfer_dfail(a[0], a[1], a[2]); }
static V S2155(void) { static V c; return STRC(c, ""); }
static V F_Chk_dTm_dname(V a0) {
top:;
V s2154 = a0;
if (TAG(s2154) == 0) {
return FLD(s2154, 0);
} else if (TAG(s2154) == 3) {
return FLD(s2154, 0);
} else if (TAG(s2154) == 2) {
return FLD(s2154, 0);
} else if (TAG(s2154) == 4) {
return FLD(s2154, 0);
} else if (TAG(s2154) == 14) {
return FLD(s2154, 0);
} else if (TAG(s2154) == 15) {
return FLD(s2154, 0);
} else {
return S2155();
}
}
static V W_Chk_dTm_dname(V *a) { (void)a; return F_Chk_dTm_dname(a[0]); }
static V F_Chk_dbook__ctr(V a0, V a1) {
top:;
V v2156 = a0;
return F_Chk_dMap_dfind(FLD(v2156, 1), a1);
}
static V W_Chk_dbook__ctr(V *a) { (void)a; return F_Chk_dbook__ctr(a[0], a[1]); }
static V F_Chk_dtyp(V a0) {
top:;
return C2(7, C2(9, a0, IMM(0)), IMM(0));
}
static V W_Chk_dtyp(V *a) { (void)a; return F_Chk_dtyp(a[0]); }
static V S2157(void) { static V c; return STRC(c, " with "); }
static V S2158(void) { static V c; return STRC(c, " parameter"); }
static V S2159(void) { static V c; return STRC(c, " parameters"); }
static V F_Chk_dinfer_dadt(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
return F_Chk_dK_dif(F_Nat_dis__eq(F_List_dlength(a3), F_Chk_dAD_dn(a1)), F_Chk_dinfer_dadt_dgo(a0, a1, a3, a4, a5, a6, a7), F_Chk_dK_derr(a6, C1(1, F_String_dappend(a2, F_String_dappend(S2157(), F_String_dappend(F_Nat_dshow(F_Chk_dAD_dn(a1)), F_Bool_dpick(F_Nat_dis__eq(F_Chk_dAD_dn(a1), 1u), S2158(), S2159()))))), C1(2, C4(14, a2, a3, a4, IMM(0))), a4, F_Chk_dCL_ddn(a0)));
}
static V W_Chk_dinfer_dadt(V *a) { (void)a; return F_Chk_dinfer_dadt(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V F_Chk_dAD_dn(V a0) {
top:;
V v2160 = a0;
return FLD(v2160, 0);
}
static V W_Chk_dAD_dn(V *a) { (void)a; return F_Chk_dAD_dn(a[0]); }
static V L2161(V *a) {
return F_Chk_dK_dpure(F_Chk_dinfer_dadt_dfin(a[0]));
}
static V F_Chk_dinfer_dadt_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
return F_Chk_dK_dbind(F_Chk_dtele__check(a0, F_Chk_dAD_dt(a1), a2, a4, a5, a6, a3, IMM(0)), mk_clo(L2161, 1, 0, 0));
}
static V W_Chk_dinfer_dadt_dgo(V *a) { (void)a; return F_Chk_dinfer_dadt_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dinfer_dadt_dfin(V a0) {
top:;
V v2162 = a0;
return C3(0, FLD(v2162, 1), FLD(v2162, 0), 0u);
}
static V W_Chk_dinfer_dadt_dfin(V *a) { (void)a; return F_Chk_dinfer_dadt_dfin(a[0]); }
static V F_Chk_dAD_dt(V a0) {
top:;
V v2163 = a0;
return FLD(v2163, 2);
}
static V W_Chk_dAD_dt(V *a) { (void)a; return F_Chk_dAD_dt(a[0]); }
static V L2167(V *a) {
return F_Chk_dtele__check(a[9], F_Chk_dclo__apply(a[10], F_Chk_dAll_db(a[8]), C2(1, a[7], IMM(0))), a[6], a[5], a[4], a[3], a[2], F_Chk_duses__add(a[1], a[0]));
}
static V L2166(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2167, 11, 10, (V[]){a[9], a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]}));
}
static V L2165(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[7], a[6], F_Chk_dquant__dem(F_Chk_dAll_dq(a[8]), a[5]), F_Chk_dAll_da(a[8]), a[4], a[3]), mk_clo(L2166, 10, 9, (V[]){a[0], a[1], a[3], a[4], a[5], a[2], a[6], a[8], a[7]}));
}
static V F_Chk_dtele__check(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s2164 = a2;
if ((s2164) == IMM(0)) {
return F_Chk_dK_dpure(C2(0, a7, a1));
} else if (TAG(s2164) == 1) {
return F_Chk_dK_dbind(F_Chk_dtele__head(a1, a4, F_Chk_dCL_ddn(a0), a6), mk_clo(L2165, 9, 8, (V[]){a7, a6, FLD(s2164, 1), a5, a4, a3, FLD(s2164, 0), a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dtele__check(V *a) { (void)a; return F_Chk_dtele__check(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V F_Chk_duses__add(V a0, V a1) {
top:;
return F_Chk_duses__merge(0u, a0, a1);
}
static V W_Chk_duses__add(V *a) { (void)a; return F_Chk_duses__add(a[0], a[1]); }
static V F_Chk_duses__merge(V a0, V a1, V a2) {
top:;
V s2168 = a2;
if ((s2168) == IMM(0)) {
return a1;
} else if (TAG(s2168) == 1) {
{ V t0 = a0; V t1 = F_Chk_duses__put(a0, FLD(s2168, 0), a1); V t2 = FLD(s2168, 1); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duses__merge(V *a) { (void)a; return F_Chk_duses__merge(a[0], a[1], a[2]); }
static V F_Chk_duses__put(V a0, V a1, V a2) {
top:;
V s2169 = a2;
if ((s2169) == IMM(0)) {
return C2(1, a1, IMM(0));
} else if (TAG(s2169) == 1) {
return F_Chk_duses__put_dif(a0, a1, FLD(FLD(s2169, 0), 0), FLD(FLD(s2169, 0), 1), FLD(s2169, 1), F_U32_dis__eq(F_Chk_dUs_di(a1), FLD(FLD(s2169, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duses__put(V *a) { (void)a; return F_Chk_duses__put(a[0], a[1], a[2]); }
static V F_Chk_dUs_di(V a0) {
top:;
V v2170 = a0;
return FLD(v2170, 0);
}
static V W_Chk_dUs_di(V *a) { (void)a; return F_Chk_dUs_di(a[0]); }
static V F_Chk_duses__put_dif(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2171 = a5;
if ((s2171) == IMM(1)) {
return C2(1, C2(0, a2, F_Bool_dpick(F_U32_dis__zero(a0), F_Chk_dquant__add(a3, F_Chk_dUs_dq(a1)), F_Chk_dquant__join(a3, F_Chk_dUs_dq(a1)))), a4);
} else if ((s2171) == IMM(0)) {
return C2(1, C2(0, a2, a3), F_Chk_duses__put(a0, a1, a4));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duses__put_dif(V *a) { (void)a; return F_Chk_duses__put_dif(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dUs_dq(V a0) {
top:;
V v2172 = a0;
return FLD(v2172, 1);
}
static V W_Chk_dUs_dq(V *a) { (void)a; return F_Chk_dUs_dq(a[0]); }
static V F_Chk_dquant__join(V a0, V a1) {
top:;
V s2173 = a0;
V s2174 = a1;
if ((s2173) == IMM(2)) {
return IMM(2);
} else if ((s2174) == IMM(2)) {
return IMM(2);
} else if ((s2173) == IMM(0)) {
return s2174;
} else {
return s2173;
}
}
static V W_Chk_dquant__join(V *a) { (void)a; return F_Chk_dquant__join(a[0], a[1]); }
static V F_Chk_dAll_da(V a0) {
top:;
V s2175 = a0;
if (TAG(s2175) == 11) {
return FLD(s2175, 3);
} else {
return s2175;
}
}
static V W_Chk_dAll_da(V *a) { (void)a; return F_Chk_dAll_da(a[0]); }
static V F_Chk_dAll_dq(V a0) {
top:;
V s2176 = a0;
if (TAG(s2176) == 11) {
return FLD(s2176, 0);
} else {
return IMM(1);
}
}
static V W_Chk_dAll_dq(V *a) { (void)a; return F_Chk_dAll_dq(a[0]); }
static V F_Chk_dquant__dem(V a0, V a1) {
top:;
V s2177 = a0;
if ((s2177) == IMM(0)) {
return IMM(0);
} else {
return a1;
}
}
static V W_Chk_dquant__dem(V *a) { (void)a; return F_Chk_dquant__dem(a[0], a[1]); }
static V L2178(V *a) {
return F_Chk_dtele__head_dgo(F_Chk_dterm__wnf(a[4], a[3]), a[2], a[1], a[0]);
}
static V F_Chk_dtele__head(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2178, 5, 4, (V[]){a3, a2, a1, a0}));
}
static V W_Chk_dtele__head(V *a) { (void)a; return F_Chk_dtele__head(a[0], a[1], a[2], a[3]); }
static V S2180(void) { static V c; return STRC(c, "unreachable (a telescope binds its parameters and fields)"); }
static V F_Chk_dtele__head_dgo(V a0, V a1, V a2, V a3) {
top:;
V s2179 = a0;
if (TAG(s2179) == 11) {
return F_Chk_dK_dpure(CN(11, 6, (V[]){FLD(s2179, 0), FLD(s2179, 1), FLD(s2179, 2), FLD(s2179, 3), FLD(s2179, 4), FLD(s2179, 5)}));
} else {
return F_Chk_dK_derr(a1, C1(1, S2180()), IMM(0), a3, a2);
}
}
static V W_Chk_dtele__head_dgo(V *a) { (void)a; return F_Chk_dtele__head_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dK_dif(V a1, V a2, V a3) {
top:;
V s2181 = a1;
if ((s2181) == IMM(1)) {
return a2;
} else if ((s2181) == IMM(0)) {
return a3;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dK_dif(V *a) { (void)a; return F_Chk_dK_dif(a[1], a[2], a[3]); }
static V L2182(V *a) {
return F_Chk_dbook__adt_dgo(a[2], F_Chk_dbook__tld(a[3], F_Chk_dTm_dname(a[2])), a[1], a[0]);
}
static V F_Chk_dbook__adt(V a0, V a1, V a2) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2182, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dbook__adt(V *a) { (void)a; return F_Chk_dbook__adt(a[0], a[1], a[2]); }
static V S2184(void) { static V c; return STRC(c, "a declared datatype (unknown: "); }
static V S2185(void) { static V c; return STRC(c, ")"); }
static V F_Chk_dbook__adt_dgo(V a0, V a1, V a2, V a3) {
top:;
V s2183 = a1;
if (TAG(s2183) == 1 && TAG(FLD(s2183, 0)) == 1) {
return F_Chk_dK_dpure(C4(0, FLD(FLD(s2183, 0), 0), FLD(FLD(s2183, 0), 1), FLD(FLD(s2183, 0), 2), F_Chk_dctrs__drop(FLD(FLD(s2183, 0), 3), F_Chk_dADT_dr(a0))));
} else {
return F_Chk_dK_derr(a2, C1(1, F_String_dappend(S2184(), F_String_dappend(F_Chk_dTm_dname(a0), S2185()))), IMM(0), F_Chk_dTm_dspan(a0), a3);
}
}
static V W_Chk_dbook__adt_dgo(V *a) { (void)a; return F_Chk_dbook__adt_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dADT_dr(V a0) {
top:;
V s2186 = a0;
if (TAG(s2186) == 14) {
return FLD(s2186, 3);
} else {
return IMM(0);
}
}
static V W_Chk_dADT_dr(V *a) { (void)a; return F_Chk_dADT_dr(a[0]); }
static V F_Chk_dctrs__drop(V a0, V a1) {
top:;
V s2187 = a0;
if ((s2187) == IMM(0)) {
return IMM(0);
} else if (TAG(s2187) == 1) {
return F_Chk_dctrs__drop_dif(C3(0, FLD(FLD(s2187, 0), 0), FLD(FLD(s2187, 0), 1), FLD(FLD(s2187, 0), 2)), F_Chk_dctrs__drop(FLD(s2187, 1), a1), F_Chk_dStr_dhas(a1, FLD(FLD(s2187, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctrs__drop(V *a) { (void)a; return F_Chk_dctrs__drop(a[0], a[1]); }
static V F_Chk_dctrs__drop_dif(V a0, V a1, V a2) {
top:;
V s2188 = a2;
if ((s2188) == IMM(1)) {
return a1;
} else if ((s2188) == IMM(0)) {
return C2(1, a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctrs__drop_dif(V *a) { (void)a; return F_Chk_dctrs__drop_dif(a[0], a[1], a[2]); }
static V L2191(V *a) {
return F_Chk_dinfer_dapp_dgo(a[7], F_Chk_dterm__wnf(a[8], a[6]), a[6], a[5], a[4], a[3], a[2], a[1], a[0]);
}
static V F_Chk_dinfer_dapp(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2189 = a1;
V s2190 = FLD(v2189, 2);
if (nat_ge(s2190, 1)) {
return F_Chk_dK_dpure(C3(0, FLD(v2189, 0), FLD(v2189, 1), nat_subk(s2190, 1)));
} else if ((s2190) == 0) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2191, 9, 8, (V[]){a6, a5, a4, a3, a2, FLD(v2189, 1), FLD(v2189, 0), a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dinfer_dapp(V *a) { (void)a; return F_Chk_dinfer_dapp(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V L2194(V *a) {
return F_Chk_dK_dpure(C3(0, F_Chk_dclo__apply(a[4], a[3], C2(1, a[2], IMM(0))), F_Chk_duses__add(a[1], a[0]), 0u));
}
static V L2193(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2194, 5, 4, (V[]){a[3], a[0], a[1], a[2]}));
}
static V S2195(void) { static V c; return STRC(c, "a function type"); }
static V F_Chk_dinfer_dapp_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s2192 = a1;
if (TAG(s2192) == 11) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a0, a4, F_Chk_dquant__dem(FLD(s2192, 0), a5), FLD(s2192, 3), a6, a7), mk_clo(L2193, 4, 3, (V[]){a3, a4, FLD(s2192, 4)}));
} else {
return F_Chk_dK_derr(a6, C1(1, S2195()), C1(2, a2), a8, F_Chk_dCL_ddn(a0));
}
}
static V W_Chk_dinfer_dapp_dgo(V *a) { (void)a; return F_Chk_dinfer_dapp_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Chk_dctx__bind(V a0, V a1, V a2, V a3, V a4) {
top:;
return C2(1, C4(33, a1, a2, a3, a4), a0);
}
static V W_Chk_dctx__bind(V *a) { (void)a; return F_Chk_dctx__bind(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dlhs__kind(V a0, V a1) {
top:;
return F_Bool_dpick(F_Bool_dand(F_Chk_dCL_du(a0), F_Chk_dQ_dis__many(a1)), IMM(1), a1);
}
static V W_Chk_dlhs__kind(V *a) { (void)a; return F_Chk_dlhs__kind(a[0], a[1]); }
static V F_Chk_dQ_dis__many(V a0) {
top:;
V s2196 = a0;
if ((s2196) == IMM(2)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dQ_dis__many(V *a) { (void)a; return F_Chk_dQ_dis__many(a[0]); }
static V F_Chk_dCL_du(V a0) {
top:;
V v2197 = a0;
return FLD(v2197, 4);
}
static V W_Chk_dCL_du(V *a) { (void)a; return F_Chk_dCL_du(a[0]); }
static V S2199(void) { static V c; return STRC(c, "a defined name"); }
static V F_Chk_dinfer_dref(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s2198 = a4;
if ((s2198) == IMM(0)) {
return F_Chk_dK_derr(a6, C1(1, S2199()), C1(2, C3(4, a1, a2, a3)), a2, F_Chk_dCL_ddn(a0));
} else if (TAG(s2198) == 1) {
return F_Chk_dK_dif(F_Chk_dQ_dis__none(a5), F_Chk_dinfer_dref_dfin(a0, a1, a2, a3, FLD(s2198, 0), a6, 0u), F_Chk_dinfer_dref_dlive(a0, a1, a2, a3, FLD(s2198, 0), a5, a6, a7, a8));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dinfer_dref(V *a) { (void)a; return F_Chk_dinfer_dref(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V S2204(void) { static V c; return STRC(c, "a filled definition (an unfilled law is a dead claim: live code cannot use it)"); }
static V L2205(V *a) {
return F_Chk_dK_dif(a[9], F_Chk_dinfer_dref_dinst(a[8], a[7], a[6], a[5], a[4], a[3], a[2], a[1], a[0]), F_Chk_dinfer_dref_dself(a[8], a[7], a[6], a[5], a[4], a[2], a[0], 0u));
}
static V L2203(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dif(F_Bool_dand(F_Bool_dand(F_Chk_dTld_dis__open(a[9]), F_Bool_dnot(a[10])), F_Bool_dor(F_Bool_dand(F_Bool_dnot(F_Chk_dTld_dis__base(a[9])), F_Bool_dnot(F_Chk_dCL_du(a[8]))), a[7])), F_Chk_dK_derr(a[6], C1(1, S2204()), C1(2, C3(4, a[5], a[4], a[3])), a[4], F_Chk_dCL_ddn(a[8])), F_Chk_dK_dpure(IMM(0))), mk_clo(L2205, 11, 10, (V[]){a[0], a[1], a[6], a[2], a[9], a[3], a[4], a[5], a[8], a[7]}));
}
static V L2202(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_String_deq(a[8], F_Chk_dCL_ddn(a[7]))), mk_clo(L2203, 11, 10, (V[]){a[0], a[1], a[2], a[3], a[4], a[8], a[5], a[9], a[7], a[6]}));
}
static V L2201(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Bool_dand(F_Nat_dis__gt(F_Chk_dTld_dx__of(a[8]), 0u), F_Nat_dis__eq(0u, a[9]))), mk_clo(L2202, 10, 9, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[8], a[6], a[7]}));
}
static V L2200(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dTld_dx(F_Chk_dbook__tld(a[9], F_Chk_dCL_ddn(a[8])))), mk_clo(L2201, 10, 9, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[8], a[6], a[7]}));
}
static V F_Chk_dinfer_dref_dlive(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2200, 10, 9, (V[]){a8, a7, a5, a3, a2, a6, a1, a4, a0}));
}
static V W_Chk_dinfer_dref_dlive(V *a) { (void)a; return F_Chk_dinfer_dref_dlive(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V S2207(void) { static V c; return STRC(c, "a decreasing self-call (arguments are read left to right: each passed unchanged until one shrinks)"); }
static V L2208(V *a) {
return F_Chk_dinfer_dref_dfin(a[6], a[5], a[4], a[3], a[2], a[1], a[0]);
}
static V L2206(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dif(F_Bool_dand(F_Bool_dand(F_String_deq(a[7], F_Chk_dCL_ddn(a[6])), F_Bool_dnot(F_Chk_dCL_du(a[6]))), F_Bool_dnot(F_Chk_dCL_ddecreases(a[8], a[6], a[5]))), F_Chk_dK_derr(a[4], C1(1, S2207()), C1(2, C3(4, a[7], a[3], a[2])), a[3], F_Chk_dCL_ddn(a[6])), F_Chk_dK_dpure(IMM(0))), mk_clo(L2208, 8, 7, (V[]){a[0], a[4], a[1], a[2], a[3], a[7], a[6]}));
}
static V F_Chk_dinfer_dref_dself(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2206, 9, 8, (V[]){a7, a4, a3, a2, a5, a6, a0, a1}));
}
static V W_Chk_dinfer_dref_dself(V *a) { (void)a; return F_Chk_dinfer_dref_dself(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S2210(void) { static V c; return STRC(c, "a family instance (write "); }
static V S2211(void) { static V c; return STRC(c, "<..>)"); }
static V F_Chk_dinfer_dref_dfin(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2209 = a4;
if (TAG(s2209) == 1) {
return F_Chk_dK_dif(F_Nat_dis__gt(FLD(s2209, 0), 0u), F_Chk_dK_derr(a5, C1(1, F_String_dappend(S2210(), F_String_dappend(a1, S2211()))), C1(2, C3(4, a1, a2, a3)), a2, F_Chk_dCL_ddn(a0)), F_Chk_dK_dpure(C3(0, FLD(s2209, 2), IMM(0), a6)));
} else if (TAG(s2209) == 0) {
return F_Chk_dK_dpure(C3(0, FLD(s2209, 2), IMM(0), a6));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dinfer_dref_dfin(V *a) { (void)a; return F_Chk_dinfer_dref_dfin(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dCL_ddecreases(V a0, V a1, V a2) {
top:;
V v2212 = a1;
return F_U32_dis__eq(F_Chk_ddescend_dargs(a0, FLD(v2212, 3), a2, F_Chk_dcl_dcols(FLD(v2212, 0)), 0u), 1u);
}
static V W_Chk_dCL_ddecreases(V *a) { (void)a; return F_Chk_dCL_ddecreases(a[0], a[1], a[2]); }
static V F_Chk_dcl_dcols(V a0) {
top:;
return F_Chk_dterm__args(a0);
}
static V W_Chk_dcl_dcols(V *a) { (void)a; return F_Chk_dcl_dcols(a[0]); }
static V F_Chk_dterm__args(V a0) {
top:;
return F_Pair_dsnd(F_Chk_dterm__unapply(a0));
}
static V W_Chk_dterm__args(V *a) { (void)a; return F_Chk_dterm__args(a[0]); }
static V F_Chk_ddescend_dargs(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2213 = a1;
V s2214 = a2;
V s2215 = a3;
if (TAG(s2213) == 1 && TAG(s2214) == 1 && TAG(s2215) == 1) {
return F_Chk_ddescend_dargs_dstep(a0, FLD(s2213, 1), FLD(s2214, 1), FLD(s2215, 1), a4, F_Chk_dterm__descend(a0, FLD(s2213, 0), FLD(s2214, 0), FLD(s2215, 0)));
} else {
return a4;
}
}
static V W_Chk_ddescend_dargs(V *a) { (void)a; return F_Chk_ddescend_dargs(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dterm__descend(V a0, V a1, V a2, V a3) {
top:;
V s2216 = a1;
if ((s2216) == IMM(0)) {
return 0u;
} else {
return F_Chk_ddescend_dgo(a0, F_Chk_ddescend_dlit(F_Chk_dterm__strip(a2), F_Chk_dterm__strip(a3)), F_Chk_dterm__strip(a3));
}
}
static V W_Chk_dterm__descend(V *a) { (void)a; return F_Chk_dterm__descend(a[0], a[1], a[2], a[3]); }
static V F_Chk_ddescend_dlit(V a0, V a1) {
top:;
return F_Bool_dpick(F_Bool_dand(F_Chk_dTm_dis__lit(a0), F_Chk_dTm_dis__ctr(a1)), F_Chk_dlit__step(a0), a0);
}
static V W_Chk_ddescend_dlit(V *a) { (void)a; return F_Chk_ddescend_dlit(a[0], a[1]); }
static V F_Chk_ddescend_dgo(V a0, V a1, V a2) {
top:;
V s2217 = a2;
if (TAG(s2217) == 0) {
return F_Chk_ddescend_dvar(a1, FLD(s2217, 1));
} else if (TAG(s2217) == 15) {
return F_Chk_ddescend_dctr(a0, a1, FLD(s2217, 0), FLD(s2217, 1), F_Chk_ddescend_dsame(a1, FLD(s2217, 0), FLD(s2217, 1)));
} else {
return 2u;
}
}
static V W_Chk_ddescend_dgo(V *a) { (void)a; return F_Chk_ddescend_dgo(a[0], a[1], a[2]); }
static V F_Chk_ddescend_dsame(V a0, V a1, V a2) {
top:;
V s2218 = a0;
if (TAG(s2218) == 15) {
return F_Bool_dand(F_String_deq(a1, FLD(s2218, 0)), F_Nat_dis__eq(F_List_dlength(a2), F_List_dlength(FLD(s2218, 1))));
} else {
return IMM(0);
}
}
static V W_Chk_ddescend_dsame(V *a) { (void)a; return F_Chk_ddescend_dsame(a[0], a[1], a[2]); }
static V F_Chk_ddescend_dctr(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2219 = a4;
if ((s2219) == IMM(1)) {
return F_Chk_ddescend_dctr_dfields(a0, a1, a3, F_Chk_ddescend_dfields(a0, F_Chk_dCtr_dxs(a1), a3, 0u));
} else if ((s2219) == IMM(0)) {
return F_Chk_ddescend_dsub(a0, a1, a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_ddescend_dctr(V *a) { (void)a; return F_Chk_ddescend_dctr(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_ddescend_dsub(V a0, V a1, V a2) {
top:;
V s2220 = a2;
if ((s2220) == IMM(0)) {
return 2u;
} else if (TAG(s2220) == 1) {
return F_Bool_dpick(F_U32_dis__eq(F_Chk_dterm__descend(a0, IMM(1), a1, FLD(s2220, 0)), 2u), F_Chk_ddescend_dsub(a0, a1, FLD(s2220, 1)), 1u);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_ddescend_dsub(V *a) { (void)a; return F_Chk_ddescend_dsub(a[0], a[1], a[2]); }
static V F_Chk_dCtr_dxs(V a0) {
top:;
V s2221 = a0;
if (TAG(s2221) == 15) {
return FLD(s2221, 1);
} else {
return IMM(0);
}
}
static V W_Chk_dCtr_dxs(V *a) { (void)a; return F_Chk_dCtr_dxs(a[0]); }
static V F_Chk_ddescend_dfields(V a0, V a1, V a2, V a3) {
top:;
V s2222 = a1;
V s2223 = a2;
if (TAG(s2222) == 1 && TAG(s2223) == 1) {
return F_Chk_ddescend_dfields_dstep(a0, FLD(s2222, 1), FLD(s2223, 1), a3, F_Chk_dterm__descend(a0, IMM(1), FLD(s2222, 0), FLD(s2223, 0)));
} else {
return a3;
}
}
static V W_Chk_ddescend_dfields(V *a) { (void)a; return F_Chk_ddescend_dfields(a[0], a[1], a[2], a[3]); }
static V F_Chk_ddescend_dfields_dstep(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Chk_ddescend_dfields_dnext(a0, a1, a2, F_Bool_dpick(F_U32_dis__eq(a4, 0u), a3, a4), F_U32_dis__eq(a4, 2u));
}
static V W_Chk_ddescend_dfields_dstep(V *a) { (void)a; return F_Chk_ddescend_dfields_dstep(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_ddescend_dfields_dnext(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2224 = a4;
if ((s2224) == IMM(1)) {
return 2u;
} else if ((s2224) == IMM(0)) {
return F_Chk_ddescend_dfields(a0, a1, a2, a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_ddescend_dfields_dnext(V *a) { (void)a; return F_Chk_ddescend_dfields_dnext(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_ddescend_dctr_dfields(V a0, V a1, V a2, V a3) {
top:;
return F_Bool_dpick(F_U32_dis__eq(a3, 2u), F_Chk_ddescend_dsub(a0, a1, a2), a3);
}
static V W_Chk_ddescend_dctr_dfields(V *a) { (void)a; return F_Chk_ddescend_dctr_dfields(a[0], a[1], a[2], a[3]); }
static V F_Chk_ddescend_dvar(V a0, V a1) {
top:;
V s2225 = a0;
if (TAG(s2225) == 0) {
return F_Bool_dpick(F_U32_dis__eq(a1, FLD(s2225, 1)), 0u, 2u);
} else {
return 2u;
}
}
static V W_Chk_ddescend_dvar(V *a) { (void)a; return F_Chk_ddescend_dvar(a[0], a[1]); }
static V F_Chk_ddescend_dargs_dstep(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Bool_dpick(F_U32_dis__eq(a5, 0u), F_Chk_ddescend_dargs(a0, a1, a2, a3, a4), a5);
}
static V W_Chk_ddescend_dargs_dstep(V *a) { (void)a; return F_Chk_ddescend_dargs_dstep(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L2228(V *a) {
return F_Chk_dinfer_dref_dself(a[7], a[6], a[5], a[4], F_Maybe_ddefault(F_Chk_dbook__tld(a[3], a[6]), a[2]), a[1], F_Chk_dList_ddrop__tm(a[0], a[8]), a[8]);
}
static V L2227(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dTld_dx__of(a[6])), mk_clo(L2228, 9, 8, (V[]){a[0], a[1], a[6], a[7], a[2], a[3], a[4], a[5]}));
}
static V L2226(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2227, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[6], a[4], a[5]}));
}
static V F_Chk_dinfer_dref_dinst(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
return F_Chk_dK_dbind(F_Chk_ddef__inst(a0, C3(4, a1, a2, a3), a4, a8, a6, a7), mk_clo(L2226, 7, 6, (V[]){a8, a6, a3, a2, a0, a4}));
}
static V W_Chk_dinfer_dref_dinst(V *a) { (void)a; return F_Chk_dinfer_dref_dinst(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Chk_dList_ddrop__tm(V a0, V a1) {
top:;
V s2229 = a0;
V s2230 = a1;
if ((s2230) == 0) {
return s2229;
} else if (TAG(s2229) == 1 && nat_ge(s2230, 1)) {
{ V t0 = FLD(s2229, 1); V t1 = nat_subk(s2230, 1); a0 = t0; a1 = t1; goto top; }
} else if ((s2229) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dList_ddrop__tm(V *a) { (void)a; return F_Chk_dList_ddrop__tm(a[0], a[1]); }
static V S2233(void) { static V c; return STRC(c, "a template applied to closed ~ arguments (a def parameter is not comptime)"); }
static V F_Chk_ddef__inst(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v2231 = F_Chk_dTld_dx__of(a2);
V v2232 = F_Chk_dList_dtake__tm(a3, v2231);
return F_Chk_dK_dif(F_Nat_dis__lt(F_List_dlength(v2232), v2231), F_Chk_dK_derr(a4, C1(1, S2233()), C1(2, a1), F_Chk_dTm_dspan(a1), F_Chk_dCL_ddn(a0)), F_Chk_ddef__inst_dgo(a0, a1, a2, v2232, a4, a5));
}
static V W_Chk_ddef__inst(V *a) { (void)a; return F_Chk_ddef__inst(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S2237(void) { static V c; return STRC(c, "a ~ argument that stops growing"); }
static V S2239(void) { static V c; return STRC(c, "\012"); }
static V S2240(void) { static V c; return STRC(c, "\012"); }
static V L2238(V *a) {
return F_Chk_ddef__inst_dfind(a[7], a[6], a[5], a[4], a[3], F_String_dappend(F_Chk_dTm_dname(a[6]), F_String_dappend(S2239(), a[2])), a[1], F_Chk_dBook_dtmp(a[0], F_String_dappend(F_Chk_dTm_dname(a[6]), F_String_dappend(S2240(), a[2]))));
}
static V L2236(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dif(F_Nat_dis__gt(F_String_dlength(a[7]), 32768u), F_Chk_dK_derr(a[6], C1(1, S2237()), C1(2, a[5]), F_Chk_dTm_dspan(a[5]), F_Chk_dCL_ddn(a[4])), F_Chk_dK_dpure(IMM(0))), mk_clo(L2238, 9, 8, (V[]){a[0], a[6], a[7], a[1], a[2], a[3], a[5], a[4]}));
}
static V L2235(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dterm__key_dlist(F_Chk_dlowers(a[6], a[5], 0u))), mk_clo(L2236, 8, 7, (V[]){a[6], a[0], a[5], a[1], a[2], a[3], a[4]}));
}
static V L2234(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2235, 7, 6, (V[]){a[5], a[0], a[1], a[2], a[3], a[4]}));
}
static V F_Chk_ddef__inst_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dK_dbind(F_Chk_dinst_dargs(a0, a1, F_Chk_dTld_dt(a2), a3, a4, a5), mk_clo(L2234, 6, 5, (V[]){a2, a0, a1, a4, a3}));
}
static V W_Chk_ddef__inst_dgo(V *a) { (void)a; return F_Chk_ddef__inst_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dBook_dtmp(V a0, V a1) {
top:;
V v2241 = a0;
return F_Chk_dMap_dfind(FLD(v2241, 5), a1);
}
static V W_Chk_dBook_dtmp(V *a) { (void)a; return F_Chk_dBook_dtmp(a[0], a[1]); }
static V S2244(void) { static V c; return STRC(c, "a decreasing self-call (arguments are read left to right: each passed unchanged until one shrinks)"); }
static V L2243(V *a) {
return F_Chk_dK_dif(F_Bool_dand(F_Bool_dnot(F_Maybe_dis__some(F_Chk_dTld_ddval(F_Maybe_ddefault(F_Chk_dbook__tld(a[5], a[4]), a[3])))), F_Bool_dnot(F_String_deq(a[4], F_Chk_dCL_ddn(a[2])))), F_Chk_dK_derr(a[1], C1(1, S2244()), C1(2, a[0]), F_Chk_dTm_dspan(a[0]), F_Chk_dCL_ddn(a[2])), F_Chk_dK_dpure(a[4]));
}
static V F_Chk_ddef__inst_dfind(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s2242 = a7;
if (TAG(s2242) == 1) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2243, 6, 5, (V[]){a1, a6, a0, a2, FLD(s2242, 0)}));
} else if ((s2242) == IMM(0)) {
return F_Chk_ddef__inst_dnew(a0, a1, a2, a3, a4, a5, a6);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_ddef__inst_dfind(V *a) { (void)a; return F_Chk_ddef__inst_dfind(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S2246(void) { static V c; return STRC(c, "a template that stops instantiating itself (64 levels at most)"); }
static V F_Chk_ddef__inst_dnew(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2245 = nat_addk(F_Chk_dCL_dz(a0), 1);
return F_Chk_dK_dif(F_Nat_dis__gt(v2245, 64u), F_Chk_dK_derr(a6, C1(1, S2246()), C1(2, a1), F_Chk_dTm_dspan(a1), F_Chk_dCL_ddn(a0)), F_Chk_ddef__inst_dmake(a1, a2, a3, a4, a5, v2245));
}
static V W_Chk_ddef__inst_dnew(V *a) { (void)a; return F_Chk_ddef__inst_dnew(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S2249(void) { static V c; return STRC(c, "~"); }
static V L2256(V *a) {
return F_Chk_dK_dpure(a[0]);
}
static V L2255(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dset__book(F_Chk_dbook__set(a[5], a[4], CN(0, 7, (V[]){a[3], 0u, a[2], C1(1, a[1]), F_Chk_dTld_ddu(a[0]), IMM(0), IMM(0)}))), mk_clo(L2256, 2, 1, (V[]){a[4]}));
}
static V L2254(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2255, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L2253(V *a) {
return F_Chk_dK_dbind(F_Chk_ddef__check(a[5], CN(0, 7, (V[]){a[4], 0u, a[3], C1(1, a[2]), F_Chk_dTld_ddu(a[1]), IMM(0), IMM(0)}), a[0]), mk_clo(L2254, 6, 5, (V[]){a[1], a[2], a[3], a[4], a[5]}));
}
static V L2252(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dset__book(F_Chk_dbook__set(F_Chk_dBook_dadd__tmp(a[7], a[6], a[5], a[4]), a[4], CN(0, 7, (V[]){a[3], 0u, a[2], IMM(0), F_Chk_dTld_ddu(a[1]), IMM(0), IMM(0)}))), mk_clo(L2253, 7, 6, (V[]){a[0], a[1], a[8], a[2], a[3], a[4]}));
}
static V L2251(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dapplys(a[7], F_Maybe_ddefault(F_Chk_dTld_ddval(a[6]), C1(18, IMM(0))), a[5])), mk_clo(L2252, 9, 8, (V[]){a[0], a[6], a[1], a[8], a[2], a[3], a[4], a[7]}));
}
static V L2250(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Nat_dsub(F_Chk_dTld_ddn(a[6]), F_Chk_dTld_dx__of(a[6]))), mk_clo(L2251, 9, 8, (V[]){a[0], a[1], a[7], a[2], a[3], a[4], a[6], a[5]}));
}
static V L2248(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_String_dappend(a[5], F_String_dappend(S2249(), F_Nat_dshow(F_Chk_dBook_dtcnt(a[6], a[5]))))), mk_clo(L2250, 8, 7, (V[]){a[0], a[1], a[2], a[5], a[3], a[6], a[4]}));
}
static V F_Chk_ddef__inst_dmake(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v2247 = F_Chk_dTm_dname(a0);
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2248, 7, 6, (V[]){a5, a3, a4, a2, a1, v2247}));
}
static V W_Chk_ddef__inst_dmake(V *a) { (void)a; return F_Chk_ddef__inst_dmake(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dBook_dadd__tmp(V a0, V a1, V a2, V a3) {
top:;
V v2257 = a0;
V v2258 = F_Maybe_ddefault(F_Chk_dMap_dfind(FLD(v2257, 6), a1), 0u);
return CN(0, 7, (V[]){FLD(v2257, 0), FLD(v2257, 1), FLD(v2257, 2), FLD(v2257, 3), FLD(v2257, 4), F_Map_dset(FLD(v2257, 5), a2, a3), F_Map_dset(FLD(v2257, 6), a1, nat_addk(v2258, 1))});
}
static V W_Chk_dBook_dadd__tmp(V *a) { (void)a; return F_Chk_dBook_dadd__tmp(a[0], a[1], a[2], a[3]); }
static V F_Chk_dTld_ddval(V a0) {
top:;
V s2259 = a0;
if (TAG(s2259) == 0) {
return FLD(s2259, 3);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_ddval(V *a) { (void)a; return F_Chk_dTld_ddval(a[0]); }
static V F_Chk_dapplys(V a0, V a1, V a2) {
top:;
V s2260 = a2;
if ((s2260) == IMM(0)) {
return a1;
} else if (TAG(s2260) == 1) {
{ V t0 = a0; V t1 = F_Chk_dterm__apply1(a0, a1, FLD(s2260, 0)); V t2 = FLD(s2260, 1); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dapplys(V *a) { (void)a; return F_Chk_dapplys(a[0], a[1], a[2]); }
static V F_Chk_dBook_dtcnt(V a0, V a1) {
top:;
V v2261 = a0;
return F_Maybe_ddefault(F_Chk_dMap_dfind(FLD(v2261, 6), a1), 0u);
}
static V W_Chk_dBook_dtcnt(V *a) { (void)a; return F_Chk_dBook_dtcnt(a[0], a[1]); }
static V F_Chk_dCL_dz(V a0) {
top:;
V v2262 = a0;
return FLD(v2262, 5);
}
static V W_Chk_dCL_dz(V *a) { (void)a; return F_Chk_dCL_dz(a[0]); }
static V F_Chk_dTld_dt(V a0) {
top:;
V s2263 = a0;
if (TAG(s2263) == 0) {
return FLD(s2263, 2);
} else if (TAG(s2263) == 1) {
return FLD(s2263, 2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dTld_dt(V *a) { (void)a; return F_Chk_dTld_dt(a[0]); }
static V L2267(V *a) {
return F_Chk_dinst_dargs(a[6], a[5], F_Chk_dclo__apply(a[7], F_Chk_dAll_db(a[4]), C2(1, a[3], IMM(0))), a[2], a[1], a[0]);
}
static V L2266(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2267, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L2265(V *a) {
return F_Chk_dK_dbind(F_Chk_dinst_dclosed(a[5], a[4], a[3], F_Chk_dAll_da(a[6]), a[2], a[1]), mk_clo(L2266, 8, 7, (V[]){a[1], a[2], a[0], a[3], a[6], a[4], a[5]}));
}
static V F_Chk_dinst_dargs(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2264 = a3;
if ((s2264) == IMM(0)) {
return F_Chk_dK_dpure(a2);
} else if (TAG(s2264) == 1) {
return F_Chk_dK_dbind(F_Chk_dtele__head(a2, a4, F_Chk_dCL_ddn(a0), F_Chk_dTm_dspan(a1)), mk_clo(L2265, 7, 6, (V[]){FLD(s2264, 1), a5, a4, FLD(s2264, 0), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dinst_dargs(V *a) { (void)a; return F_Chk_dinst_dargs(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L2268(V *a) {
return F_Chk_dinst_dclosed_dgo(apply(F_Chk_dterm__check(a[5], a[4], IMM(0), a[3], IMM(0), a[2]), a[6]), a[5], a[1], a[0], a[2]);
}
static V F_Chk_dinst_dclosed(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return mk_clo(L2268, 7, 6, (V[]){a4, a1, a5, a3, a2, a0});
}
static V W_Chk_dinst_dclosed(V *a) { (void)a; return F_Chk_dinst_dclosed(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dinst_dclosed_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2269 = a0;
if (TAG(s2269) == 1) {
return C1(1, FLD(s2269, 0));
} else if (TAG(s2269) == 0) {
return C1(0, F_Chk_dinst_dclosed_derr(FLD(s2269, 0), a1, a2, a3, a4));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dinst_dclosed_dgo(V *a) { (void)a; return F_Chk_dinst_dclosed_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dinst_dclosed_derr(V a0, V a1, V a2, V a3, V a4) {
top:;
V v2270 = a0;
return F_Chk_dinst_dclosed_derr_dgo(CN(0, 7, (V[]){FLD(v2270, 0), FLD(v2270, 1), FLD(v2270, 2), FLD(v2270, 3), FLD(v2270, 4), FLD(v2270, 5), FLD(v2270, 6)}), FLD(v2270, 3), FLD(v2270, 0), a1, a2, a3, a4);
}
static V W_Chk_dinst_dclosed_derr(V *a) { (void)a; return F_Chk_dinst_dclosed_derr(a[0], a[1], a[2], a[3], a[4]); }
static V S2272(void) { static V c; return STRC(c, "a template applied to closed ~ arguments ("); }
static V S2273(void) { static V c; return STRC(c, " is a variable here, not comptime: pass it at run time)"); }
static V F_Chk_dinst_dclosed_derr_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2271 = a1;
if (TAG(s2271) == 2 && TAG(FLD(s2271, 0)) == 0) {
return F_Bool_dpick(F_U32_dis__lt(FLD(FLD(s2271, 0), 1), a6), F_Chk_derr(a2, a5, C1(1, F_String_dappend(S2272(), F_String_dappend(FLD(FLD(s2271, 0), 0), S2273()))), C1(2, a4), F_Chk_dTm_dspan(a4), F_Chk_dCL_ddn(a3)), a0);
} else {
return a0;
}
}
static V W_Chk_dinst_dclosed_derr_dgo(V *a) { (void)a; return F_Chk_dinst_dclosed_derr_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dList_dtake__tm(V a0, V a1) {
top:;
V s2274 = a0;
V s2275 = a1;
if (TAG(s2274) == 1 && nat_ge(s2275, 1)) {
return C2(1, FLD(s2274, 0), F_Chk_dList_dtake__tm(FLD(s2274, 1), nat_subk(s2275, 1)));
} else {
return IMM(0);
}
}
static V W_Chk_dList_dtake__tm(V *a) { (void)a; return F_Chk_dList_dtake__tm(a[0], a[1]); }
static V F_Chk_dTld_dis__base(V a0) {
top:;
V s2276 = a0;
if (TAG(s2276) == 0) {
return FLD(s2276, 5);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dis__base(V *a) { (void)a; return F_Chk_dTld_dis__base(a[0]); }
static V F_Chk_dTld_dis__open(V a0) {
top:;
V s2277 = a0;
if (TAG(s2277) == 0 && (FLD(s2277, 3)) == IMM(0) && (FLD(s2277, 6)) == IMM(0)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dis__open(V *a) { (void)a; return F_Chk_dTld_dis__open(a[0]); }
static V F_Chk_dTld_dx(V a0) {
top:;
V s2278 = a0;
if (TAG(s2278) == 1 && TAG(FLD(s2278, 0)) == 0) {
return FLD(FLD(s2278, 0), 1);
} else {
return 0u;
}
}
static V W_Chk_dTld_dx(V *a) { (void)a; return F_Chk_dTld_dx(a[0]); }
static V F_Chk_dQ_dis__none(V a0) {
top:;
V s2279 = a0;
if ((s2279) == IMM(0)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dQ_dis__none(V *a) { (void)a; return F_Chk_dQ_dis__none(a[0]); }
static V F_Chk_dinfer_dvar(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dinfer_dvar_dgo(a0, a1, a2, a3, a4, a5, F_Chk_dctx__get(a3, a1));
}
static V W_Chk_dinfer_dvar(V *a) { (void)a; return F_Chk_dinfer_dvar(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dctx__get(V a0, V a1) {
top:;
V s2280 = a0;
if ((s2280) == IMM(0)) {
return IMM(0);
} else if (TAG(s2280) == 1 && TAG(FLD(s2280, 0)) == 33) {
return F_Bool_dpick(F_U32_dis__eq(a1, FLD(FLD(s2280, 0), 0)), C1(1, FLD(FLD(s2280, 0), 3)), F_Chk_dctx__get(FLD(s2280, 1), a1));
} else if (TAG(s2280) == 1) {
{ V t0 = FLD(s2280, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctx__get(V *a) { (void)a; return F_Chk_dctx__get(a[0], a[1]); }
static V S2282(void) { static V c; return STRC(c, "a bound variable"); }
static V F_Chk_dinfer_dvar_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2281 = a6;
if ((s2281) == IMM(0)) {
return F_Chk_dK_derr(a3, C1(1, S2282()), C1(2, a0), a4, F_Chk_dCL_ddn(a5));
} else if (TAG(s2281) == 1) {
return F_Chk_dK_dpure(C3(0, FLD(s2281, 0), F_Chk_duses__one(a1, a2), 0u));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dinfer_dvar_dgo(V *a) { (void)a; return F_Chk_dinfer_dvar_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_duses__one(V a0, V a1) {
top:;
return C2(1, C2(0, a0, a1), IMM(0));
}
static V W_Chk_duses__one(V *a) { (void)a; return F_Chk_duses__one(a[0], a[1]); }
static V S2284(void) { static V c; return STRC(c, "_"); }
static V L2289(V *a) {
return F_Chk_dK_dpure(F_Chk_duses__add(F_Chk_dIR_dus(a[0]), a[1]));
}
static V L2288(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[9], a[8], a[7], F_Chk_dterm__apply1(a[6], F_Chk_dterm__apply1(a[6], a[5], a[4]), C1(20, a[3])), a[2], a[1]), mk_clo(L2289, 2, 1, (V[]){a[0]}));
}
static V L2287(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dif(F_Chk_dterm__compare(IMM(1), a[10], a[11], a[9], a[8]), F_Chk_dK_dpure(IMM(0)), F_Chk_dK_derr(a[7], C1(2, a[9]), C1(2, a[11]), a[6], F_Chk_dCL_ddn(a[5]))), mk_clo(L2288, 11, 10, (V[]){a[0], a[8], a[7], a[6], a[1], a[2], a[10], a[3], a[4], a[5]}));
}
static V L2286(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dterm__apply1(a[12], F_Chk_dterm__apply1(a[12], a[11], a[10]), a[9])), mk_clo(L2287, 12, 11, (V[]){a[0], a[1], a[11], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[12]}));
}
static V L2285(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2286, 13, 12, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11]}));
}
static V S2290(void) { static V c; return STRC(c, "an equation {a == b : T}"); }
static V F_Chk_dcheck_drwt(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10) {
top:;
V s2283 = a6;
if (TAG(s2283) == 19) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a0, a2, IMM(0), CN(11, 6, (V[]){IMM(1), S2284(), 0u, FLD(s2283, 2), C3(29, FLD(s2283, 0), FLD(s2283, 2), a4), a4}), a9, a10), mk_clo(L2285, 13, 12, (V[]){a5, FLD(s2283, 0), a7, a3, a0, a4, a9, a10, a8, a1, FLD(s2283, 1), a2}));
} else {
return F_Chk_dK_derr(a9, C1(1, S2290()), C1(2, F_Chk_dIR_dty(a5)), F_Chk_dSp_dor(F_Chk_dTm_dspan(a1), a4), F_Chk_dCL_ddn(a0));
}
}
static V W_Chk_dcheck_drwt(V *a) { (void)a; return F_Chk_dcheck_drwt(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10]); }
static V F_Chk_dIR_dus(V a0) {
top:;
V v2291 = a0;
return FLD(v2291, 1);
}
static V W_Chk_dIR_dus(V *a) { (void)a; return F_Chk_dIR_dus(a[0]); }
static V L2293(V *a) {
return F_Chk_dK_dif(F_Chk_dterm__compare(IMM(0), a[6], a[5], a[4], a[3]), F_Chk_dK_dpure(IMM(0)), F_Chk_dK_derr(a[2], C1(2, a[5]), C1(2, a[4]), a[1], F_Chk_dCL_ddn(a[0])));
}
static V F_Chk_dcheck_drfl(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2292 = a2;
if (TAG(s2292) == 19) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2293, 7, 6, (V[]){a0, a1, a4, a5, FLD(s2292, 1), FLD(s2292, 0)}));
} else {
return F_Chk_dcheck_dtypeless(a0, C1(20, a1), a3, a4, a1);
}
}
static V W_Chk_dcheck_drfl(V *a) { (void)a; return F_Chk_dcheck_drfl(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L2294(V *a) {
return F_Chk_dK_derr(a[4], C1(2, a[3]), C1(1, F_Chk_dtypeless__show(a[6], a[4], a[2])), a[1], F_Chk_dCL_ddn(a[0]));
}
static V F_Chk_dcheck_dtypeless(V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2294, 7, 6, (V[]){a1, a5, a2, a3, a4, 0}));
}
static V W_Chk_dcheck_dtypeless(V *a) { (void)a; return F_Chk_dcheck_dtypeless(a[1], a[2], a[3], a[4], a[5]); }
static V S2295(void) { static V c; return STRC(c, "non-inferrable term '"); }
static V S2296(void) { static V c; return STRC(c, "'"); }
static V F_Chk_dtypeless__show(V a0, V a1, V a2) {
top:;
return F_String_dappend(S2295(), F_String_dappend(F_Chk_dexpr__show(a0, C1(2, a2), F_Chk_dctx__scope(a1)), F_String_dappend(S2296(), F_Chk_dtypeless_dnote(a0, a2))));
}
static V W_Chk_dtypeless__show(V *a) { (void)a; return F_Chk_dtypeless__show(a[0], a[1], a[2]); }
static V S2298(void) { static V c; return STRC(c, " ("); }
static V S2299(void) { static V c; return STRC(c, " is a datatype: write its arguments as <>)"); }
static V S2300(void) { static V c; return STRC(c, ""); }
static V S2301(void) { static V c; return STRC(c, ""); }
static V F_Chk_dtypeless_dnote(V a0, V a1) {
top:;
V s2297 = a1;
if (TAG(s2297) == 15) {
return F_Bool_dpick(F_Chk_dTld_dis__adt(F_Chk_dbook__tld(a0, FLD(s2297, 0))), F_String_dappend(S2298(), F_String_dappend(FLD(s2297, 0), S2299())), S2300());
} else {
return S2301();
}
}
static V W_Chk_dtypeless_dnote(V *a) { (void)a; return F_Chk_dtypeless_dnote(a[0], a[1]); }
static V F_Chk_dTld_dis__adt(V a0) {
top:;
V s2302 = a0;
if (TAG(s2302) == 1 && TAG(FLD(s2302, 0)) == 1) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dis__adt(V *a) { (void)a; return F_Chk_dTld_dis__adt(a[0]); }
static V F_Chk_dctx__scope(V a0) {
top:;
return F_Chk_dctx__scope_dgo(a0, 0u, F_Chk_dctx__len(a0));
}
static V W_Chk_dctx__scope(V *a) { (void)a; return F_Chk_dctx__scope(a[0]); }
static V F_Chk_dctx__len(V a0) {
top:;
V s2303 = a0;
if ((s2303) == IMM(0)) {
return 0u;
} else if (TAG(s2303) == 1 && TAG(FLD(s2303, 0)) == 33) {
return F_U32_dmax(F_U32_dinc(FLD(FLD(s2303, 0), 0)), F_Chk_dctx__len(FLD(s2303, 1)));
} else if (TAG(s2303) == 1) {
{ V t0 = FLD(s2303, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctx__len(V *a) { (void)a; return F_Chk_dctx__len(a[0]); }
static V W_U32_dmax(V *a) { (void)a; return F_U32_dmax(a[0], a[1]); }
static V F_Chk_dctx__scope_dgo(V a0, V a1, V a2) {
top:;
return F_Chk_dctx__scope_dc(a0, a1, a2, F_U32_dis__ge(a1, a2));
}
static V W_Chk_dctx__scope_dgo(V *a) { (void)a; return F_Chk_dctx__scope_dgo(a[0], a[1], a[2]); }
static V F_Chk_dctx__scope_dc(V a0, V a1, V a2, V a3) {
top:;
V s2304 = a3;
if ((s2304) == IMM(1)) {
return IMM(0);
} else if ((s2304) == IMM(0)) {
return C2(1, F_Chk_dctx__name(a0, a1), F_Chk_dctx__scope_dgo(a0, F_U32_dinc(a1), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctx__scope_dc(V *a) { (void)a; return F_Chk_dctx__scope_dc(a[0], a[1], a[2], a[3]); }
static V S2306(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dctx__name(V a0, V a1) {
top:;
V s2305 = a0;
if ((s2305) == IMM(0)) {
return S2306();
} else if (TAG(s2305) == 1 && TAG(FLD(s2305, 0)) == 33) {
return F_Bool_dpick(F_U32_dis__eq(a1, FLD(FLD(s2305, 0), 0)), FLD(FLD(s2305, 0), 2), F_Chk_dctx__name(FLD(s2305, 1), a1));
} else if (TAG(s2305) == 1) {
{ V t0 = FLD(s2305, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctx__name(V *a) { (void)a; return F_Chk_dctx__name(a[0], a[1]); }
static V S2308(void) { static V c; return STRC(c, ""); }
static V F_Chk_dexpr__show(V a0, V a1, V a2) {
top:;
V s2307 = a1;
if ((s2307) == IMM(0)) {
return S2308();
} else if (TAG(s2307) == 1) {
return FLD(s2307, 0);
} else if (TAG(s2307) == 2) {
return F_Chk_dterm__show(F_Chk_dterm__lower(a0, F_Chk_dterm__snf(a0, FLD(s2307, 0)), F_U32_dfrom__nat(F_List_dlength(a2))), 0u, F_List_dreverse(a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dexpr__show(V *a) { (void)a; return F_Chk_dexpr__show(a[0], a[1], a[2]); }
static V S2310(void) { static V c; return STRC(c, "a live scrutinee (a - scrutinee matches only in a dead region)"); }
static V L2312(V *a) {
return F_Chk_dcheck_delim_dadt(a[12], a[11], a[10], CN(11, 6, (V[]){a[9], a[8], a[7], a[6], a[5], a[4]}), F_Chk_dterm__wnf(a[13], a[6]), a[3], a[2], a[1], a[0]);
}
static V L2311(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2312, 14, 13, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12]}));
}
static V F_Chk_dcheck_delim(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s2309 = a3;
if (TAG(s2309) == 11) {
return F_Chk_dK_dbind(F_Chk_dK_dif(F_Bool_dand(F_Bool_dnot(F_Chk_dQ_dis__none(a4)), F_Chk_dQ_dis__none(FLD(s2309, 0))), F_Chk_dK_derr(a6, C1(1, S2310()), IMM(0), a2, F_Chk_dCL_ddn(a0)), F_Chk_dK_dpure(IMM(0))), mk_clo(L2311, 14, 13, (V[]){a7, a6, a5, a4, FLD(s2309, 5), FLD(s2309, 4), FLD(s2309, 3), FLD(s2309, 2), FLD(s2309, 1), FLD(s2309, 0), a2, a1, a0}));
} else {
return F_Chk_dcheck_dtypeless(a0, a1, a5, a6, a2);
}
}
static V W_Chk_dcheck_delim(V *a) { (void)a; return F_Chk_dcheck_delim(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V L2314(V *a) {
return F_Chk_dcheck_delim_dgo(a[10], a[9], a[8], a[7], a[6], a[5], a[4], F_Chk_dAD_dcs(a[11]), a[3], a[2], a[1], a[0]);
}
static V S2315(void) { static V c; return STRC(c, "a datatype"); }
static V F_Chk_dcheck_delim_dadt(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s2313 = a4;
if (TAG(s2313) == 14) {
return F_Chk_dK_dbind(F_Chk_dbook__adt(C4(14, FLD(s2313, 0), FLD(s2313, 1), FLD(s2313, 2), FLD(s2313, 3)), a7, F_Chk_dCL_ddn(a0)), mk_clo(L2314, 12, 11, (V[]){a8, a7, a6, a5, FLD(s2313, 3), FLD(s2313, 1), FLD(s2313, 0), a3, a2, a1, a0}));
} else {
return F_Chk_dK_derr(a7, C1(1, S2315()), C1(2, F_Chk_dAll_da(a3)), a2, F_Chk_dCL_ddn(a0));
}
}
static V W_Chk_dcheck_delim_dadt(V *a) { (void)a; return F_Chk_dcheck_delim_dadt(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Chk_dAD_dcs(V a0) {
top:;
V v2316 = a0;
return FLD(v2316, 3);
}
static V W_Chk_dAD_dcs(V *a) { (void)a; return F_Chk_dAD_dcs(a[0]); }
static V S2319(void) { static V c; return STRC(c, "cases for "); }
static V S2320(void) { static V c; return STRC(c, ", "); }
static V L2318(V *a) {
return F_Chk_dK_dif(F_Bool_dand(F_Bool_dnot(F_Chk_dLst_dempty(a[4])), F_Bool_dnot(F_Chk_dctx__dead(a[5], a[3]))), F_Chk_dK_derr(a[3], C1(1, F_String_dappend(S2319(), F_String_djoin(F_Chk_dCtrD_dnames(a[4]), S2320()))), C1(2, C1(18, a[2])), a[1], F_Chk_dCL_ddn(a[0])), F_Chk_dK_dpure(IMM(0)));
}
static V F_Chk_dcheck_delim_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11) {
top:;
V s2317 = a1;
if (TAG(s2317) == 18) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2318, 6, 5, (V[]){a0, a2, FLD(s2317, 0), a10, a7}));
} else if (TAG(s2317) == 17) {
return F_Chk_dcheck_dmat(a0, FLD(s2317, 0), FLD(s2317, 1), FLD(s2317, 2), a2, a3, a4, a5, a6, F_Chk_dctrs__find(a7, FLD(s2317, 0)), a8, a9, a10, a11);
} else {
return F_Chk_dK_dpure(IMM(0));
}
}
static V W_Chk_dcheck_delim_dgo(V *a) { (void)a; return F_Chk_dcheck_delim_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11]); }
static V F_Chk_dctrs__find(V a0, V a1) {
top:;
V s2321 = a0;
if ((s2321) == IMM(0)) {
return IMM(0);
} else if (TAG(s2321) == 1) {
return F_Chk_dctrs__find_dif(C3(0, FLD(FLD(s2321, 0), 0), FLD(FLD(s2321, 0), 1), FLD(FLD(s2321, 0), 2)), FLD(s2321, 1), a1, F_String_deq(a1, FLD(FLD(s2321, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctrs__find(V *a) { (void)a; return F_Chk_dctrs__find(a[0], a[1]); }
static V F_Chk_dctrs__find_dif(V a0, V a1, V a2, V a3) {
top:;
V s2322 = a3;
if ((s2322) == IMM(1)) {
return C1(1, a0);
} else if ((s2322) == IMM(0)) {
return F_Chk_dctrs__find(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctrs__find_dif(V *a) { (void)a; return F_Chk_dctrs__find_dif(a[0], a[1], a[2], a[3]); }
static V S2324(void) { static V c; return STRC(c, "a constructor of "); }
static V S2325(void) { static V c; return STRC(c, " (missing, or already matched)"); }
static V L2330(V *a) {
return F_Chk_dK_dpure(F_Chk_duses__join(a[0], a[1]));
}
static V L2329(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[10], a[9], a[8], CN(11, 6, (V[]){F_Chk_dAll_dq(a[7]), F_Chk_dAll_dk(a[7]), 0u, C4(14, a[6], a[5], a[4], F_List_dappend(a[3], C2(1, a[2], IMM(0)))), F_Chk_dAll_db(a[7]), a[4]}), a[1], a[0]), mk_clo(L2330, 2, 1, (V[]){a[11]}));
}
static V L2328(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[14], a[13], a[12], F_Chk_dmat__goal(a[15], a[11], a[10], IMM(0), F_Chk_dAll_db(a[9]), a[8], a[7], F_Chk_dAll_dq(a[9]), a[6], F_Chk_dCL_ddn(a[5])), a[6], a[4]), mk_clo(L2329, 12, 11, (V[]){a[4], a[6], a[8], a[0], a[7], a[1], a[2], a[9], a[12], a[3], a[5]}));
}
static V L2327(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2328, 16, 15, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14]}));
}
static V L2326(V *a) {
return F_Chk_dK_dbind(F_Chk_dCL_dext(a[12], a[11], a[10]), mk_clo(L2327, 15, 14, (V[]){a[0], a[1], a[2], a[3], a[4], a[12], a[5], a[6], a[11], a[7], a[10], a[13], a[8], a[9]}));
}
static V F_Chk_dcheck_dmat(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11, V a12, V a13) {
top:;
V s2323 = a9;
if ((s2323) == IMM(0)) {
return F_Chk_dK_derr(a12, C1(1, F_String_dappend(S2324(), F_String_dappend(a6, S2325()))), C1(2, C4(17, a1, a2, a3, a4)), a4, F_Chk_dCL_ddn(a0));
} else if (TAG(s2323) == 1) {
return F_Chk_dK_dbind(F_Chk_dtele__fill(FLD(FLD(s2323, 0), 2), a7, a12, F_Chk_dCL_ddn(a0), a4), mk_clo(L2326, 14, 13, (V[]){a8, a7, a6, a3, a13, a12, a4, a5, a10, a2, FLD(FLD(s2323, 0), 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcheck_dmat(V *a) { (void)a; return F_Chk_dcheck_dmat(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13]); }
static V F_Chk_duses__join(V a0, V a1) {
top:;
return F_Chk_duses__merge(1u, a0, a1);
}
static V W_Chk_duses__join(V *a) { (void)a; return F_Chk_duses__join(a[0], a[1]); }
static V S2332(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dAll_dk(V a0) {
top:;
V s2331 = a0;
if (TAG(s2331) == 11) {
return FLD(s2331, 1);
} else {
return S2332();
}
}
static V W_Chk_dAll_dk(V *a) { (void)a; return F_Chk_dAll_dk(a[0]); }
static V L2335(V *a) {
return F_Chk_dK_dpure(CN(0, 6, (V[]){F_Chk_dlhs__ext(a[8], a[7], a[6], a[5], IMM(0)), F_Nat_dadd(a[4], a[5]), a[3], a[2], a[1], a[0]}));
}
static V F_Chk_dCL_dext(V a0, V a1, V a2) {
top:;
V v2333 = a0;
V s2334 = FLD(v2333, 1);
if ((s2334) == 0) {
return F_Chk_dK_dpure(CN(0, 6, (V[]){FLD(v2333, 0), FLD(v2333, 1), FLD(v2333, 2), FLD(v2333, 3), FLD(v2333, 4), FLD(v2333, 5)}));
} else if (nat_ge(s2334, 1)) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2335, 9, 8, (V[]){FLD(v2333, 5), FLD(v2333, 4), FLD(v2333, 3), FLD(v2333, 2), nat_subk(s2334, 1), a2, a1, FLD(v2333, 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCL_dext(V *a) { (void)a; return F_Chk_dCL_dext(a[0], a[1], a[2]); }
static V L2338(V *a) {
return F_Chk_dtele__fill(F_Chk_dclo__apply(a[6], F_Chk_dAll_db(a[5]), C2(1, a[4], IMM(0))), a[3], a[2], a[1], a[0]);
}
static V L2337(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2338, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V F_Chk_dtele__fill(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2336 = a1;
if ((s2336) == IMM(0)) {
return F_Chk_dK_dpure(a0);
} else if (TAG(s2336) == 1) {
return F_Chk_dK_dbind(F_Chk_dtele__head(a0, a2, a3, a4), mk_clo(L2337, 6, 5, (V[]){a4, a3, a2, FLD(s2336, 1), FLD(s2336, 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dtele__fill(V *a) { (void)a; return F_Chk_dtele__fill(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dCtrD_dnames(V a0) {
top:;
V s2339 = a0;
if ((s2339) == IMM(0)) {
return IMM(0);
} else if (TAG(s2339) == 1) {
return C2(1, FLD(FLD(s2339, 0), 0), F_Chk_dCtrD_dnames(FLD(s2339, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCtrD_dnames(V *a) { (void)a; return F_Chk_dCtrD_dnames(a[0]); }
static V F_Chk_dctx__dead(V a0, V a1) {
top:;
V s2340 = a1;
if ((s2340) == IMM(0)) {
return IMM(0);
} else if (TAG(s2340) == 1 && TAG(FLD(s2340, 0)) == 33) {
return F_Bool_dor(F_Bool_dand(F_Bool_dnot(F_Chk_dQ_dis__none(FLD(FLD(s2340, 0), 1))), F_Chk_dctx__dead_dty(a0, F_Chk_dterm__wnf(a0, FLD(FLD(s2340, 0), 3)))), F_Chk_dctx__dead(a0, FLD(s2340, 1)));
} else if (TAG(s2340) == 1) {
{ V t0 = a0; V t1 = FLD(s2340, 1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctx__dead(V *a) { (void)a; return F_Chk_dctx__dead(a[0], a[1]); }
static V F_Chk_dctx__dead_dty(V a0, V a1) {
top:;
V s2341 = a1;
if (TAG(s2341) == 14) {
return F_Chk_dctx__dead_dtld(F_Chk_dbook__tld(a0, FLD(s2341, 0)), FLD(s2341, 3));
} else {
return IMM(0);
}
}
static V W_Chk_dctx__dead_dty(V *a) { (void)a; return F_Chk_dctx__dead_dty(a[0], a[1]); }
static V F_Chk_dctx__dead_dtld(V a0, V a1) {
top:;
V s2342 = a0;
if (TAG(s2342) == 1 && TAG(FLD(s2342, 0)) == 1) {
return F_Chk_dLst_dempty(F_Chk_dctrs__drop(FLD(FLD(s2342, 0), 3), a1));
} else {
return IMM(0);
}
}
static V W_Chk_dctx__dead_dtld(V *a) { (void)a; return F_Chk_dctx__dead_dtld(a[0], a[1]); }
static V L2344(V *a) {
return F_Chk_dK_dif(F_Chk_dcheck_dlit_dbase(F_Chk_dbook__tld(a[8], a[7]), a[6], F_Chk_dlit_dctr(F_Chk_dLit_dv(a[5]))), F_Chk_dK_dpure(IMM(0)), F_Chk_dterm__check(a[4], F_Chk_dlit__step(a[5]), a[3], a[2], a[1], a[0]));
}
static V F_Chk_dcheck_dlit(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2343 = a2;
if (TAG(s2343) == 14) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2344, 9, 8, (V[]){a6, a5, a4, a3, a0, a1, FLD(s2343, 3), FLD(s2343, 0)}));
} else {
return F_Chk_dterm__check(a0, F_Chk_dlit__step(a1), a3, a4, a5, a6);
}
}
static V W_Chk_dcheck_dlit(V *a) { (void)a; return F_Chk_dcheck_dlit(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dLit_dv(V a0) {
top:;
V s2345 = a0;
if (TAG(s2345) == 16) {
return FLD(s2345, 0);
} else {
return C1(0, 0u);
}
}
static V W_Chk_dLit_dv(V *a) { (void)a; return F_Chk_dLit_dv(a[0]); }
static V S2347(void) { static V c; return STRC(c, "Zero"); }
static V S2348(void) { static V c; return STRC(c, "Succ"); }
static V S2349(void) { static V c; return STRC(c, "SNil"); }
static V S2350(void) { static V c; return STRC(c, "SCon"); }
static V F_Chk_dlit_dctr(V a0) {
top:;
V s2346 = a0;
if (TAG(s2346) == 0 && (FLD(s2346, 0)) == 0) {
return S2347();
} else if (TAG(s2346) == 0) {
return S2348();
} else if (TAG(s2346) == 1 && (FLD(s2346, 0)) == IMM(0)) {
return S2349();
} else if (TAG(s2346) == 1) {
return S2350();
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlit_dctr(V *a) { (void)a; return F_Chk_dlit_dctr(a[0]); }
static V F_Chk_dcheck_dlit_dbase(V a0, V a1, V a2) {
top:;
V s2351 = a0;
if (TAG(s2351) == 1 && TAG(FLD(s2351, 0)) == 1) {
return F_Bool_dand(F_Chk_dcheck_dlit_dbase__adt(FLD(FLD(s2351, 0), 3)), F_Maybe_dis__some(F_Chk_dctrs__find(F_Chk_dctrs__drop(FLD(FLD(s2351, 0), 3), a1), a2)));
} else {
return IMM(0);
}
}
static V W_Chk_dcheck_dlit_dbase(V *a) { (void)a; return F_Chk_dcheck_dlit_dbase(a[0], a[1], a[2]); }
static V F_Chk_dcheck_dlit_dbase__adt(V a0) {
top:;
return IMM(1);
}
static V W_Chk_dcheck_dlit_dbase__adt(V *a) { (void)a; return F_Chk_dcheck_dlit_dbase__adt(a[0]); }
static V L2354(V *a) {
return F_Chk_dcheck_dctr_dfind(a[10], a[9], a[8], a[7], a[6], a[5], F_Chk_dAD_dcs(a[4]), F_Chk_dctrs__find(F_Chk_dAD_dcs(a[4]), a[9]), a[3], a[2], a[1], a[0]);
}
static V L2353(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2354, 12, 11, (V[]){a[0], a[1], a[2], a[3], a[10], a[4], a[5], a[6], a[7], a[8], a[9]}));
}
static V L2355(V *a) {
return F_Chk_dK_dif(F_Maybe_dis__some(F_Chk_dbook__ctr(a[6], a[5])), F_Chk_dK_derr(a[4], C1(2, a[3]), C1(2, C3(4, F_Chk_dbook__fam(a[6], a[5]), a[2], IMM(0))), a[2], F_Chk_dCL_ddn(a[1])), F_Chk_dcheck_dtypeless(a[1], C3(15, a[5], a[0], a[2]), a[3], a[4], a[2]));
}
static V F_Chk_dcheck_dctr(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s2352 = a4;
if (TAG(s2352) == 14) {
return F_Chk_dK_dbind(F_Chk_dbook__adt(C4(14, FLD(s2352, 0), FLD(s2352, 1), FLD(s2352, 2), FLD(s2352, 3)), a7, F_Chk_dCL_ddn(a0)), mk_clo(L2353, 11, 10, (V[]){a8, a7, a6, a5, FLD(s2352, 1), FLD(s2352, 0), a3, a2, a1, a0}));
} else {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2355, 7, 6, (V[]){a2, a0, a3, a6, a7, a1}));
}
}
static V W_Chk_dcheck_dctr(V *a) { (void)a; return F_Chk_dcheck_dctr(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Chk_dbook__fam(V a0, V a1) {
top:;
return F_Chk_dbook__fam_dctr(a0, F_Chk_dbook__ctr(a0, a1), a1);
}
static V W_Chk_dbook__fam(V *a) { (void)a; return F_Chk_dbook__fam(a[0], a[1]); }
static V F_Chk_dbook__fam_dctr(V a0, V a1, V a2) {
top:;
V s2356 = a1;
if (TAG(s2356) == 1) {
return F_Chk_dbook__fam_dgo(a0, F_Chk_dterm__strip(FLD(FLD(s2356, 0), 2)), 0u, a2);
} else if ((s2356) == IMM(0)) {
return a2;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dbook__fam_dctr(V *a) { (void)a; return F_Chk_dbook__fam_dctr(a[0], a[1], a[2]); }
static V F_Chk_dbook__fam_dgo(V a0, V a1, V a2, V a3) {
top:;
V s2357 = a1;
if (TAG(s2357) == 11) {
{ V t0 = a0; V t1 = F_Chk_dterm__strip(F_Chk_dclo__apply(a0, FLD(s2357, 4), C2(1, C3(0, FLD(s2357, 1), a2, IMM(0)), IMM(0)))); V t2 = F_U32_dinc(a2); V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s2357) == 14) {
return FLD(s2357, 0);
} else {
return a3;
}
}
static V W_Chk_dbook__fam_dgo(V *a) { (void)a; return F_Chk_dbook__fam_dgo(a[0], a[1], a[2], a[3]); }
static V S2360(void) { static V c; return STRC(c, "a declared constructor ("); }
static V S2361(void) { static V c; return STRC(c, " declares "); }
static V S2362(void) { static V c; return STRC(c, ", "); }
static V S2363(void) { static V c; return STRC(c, ")"); }
static V L2359(V *a) {
return F_Chk_dK_dif(F_Maybe_dis__some(F_Chk_dbook__ctr(a[8], a[7])), F_Chk_dK_derr(a[6], C1(2, a[5]), C1(2, C3(4, F_Chk_dbook__fam(a[8], a[7]), a[4], IMM(0))), a[4], F_Chk_dCL_ddn(a[3])), F_Chk_dK_derr(a[6], C1(1, F_String_dappend(S2360(), F_String_dappend(a[2], F_String_dappend(S2361(), F_String_dappend(F_String_djoin(F_Chk_dCtrD_dnames(a[1]), S2362()), S2363()))))), C1(2, C3(15, a[7], a[0], a[4])), a[4], F_Chk_dCL_ddn(a[3])));
}
static V S2364(void) { static V c; return STRC(c, " with "); }
static V S2365(void) { static V c; return STRC(c, " field"); }
static V S2366(void) { static V c; return STRC(c, " fields"); }
static V F_Chk_dcheck_dctr_dfind(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11) {
top:;
V s2358 = a7;
if ((s2358) == IMM(0)) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2359, 9, 8, (V[]){a2, a6, a4, a0, a3, a9, a10, a1}));
} else if (TAG(s2358) == 1) {
return F_Chk_dK_dif(F_Nat_dis__eq(FLD(FLD(s2358, 0), 1), F_List_dlength(a2)), F_Chk_dcheck_dctr_dfields(a0, FLD(FLD(s2358, 0), 2), a2, a3, a5, a8, a10, a11), F_Chk_dK_derr(a10, C1(1, F_String_dappend(a1, F_String_dappend(S2364(), F_String_dappend(F_Nat_dshow(FLD(FLD(s2358, 0), 1)), F_Bool_dpick(F_Nat_dis__eq(FLD(FLD(s2358, 0), 1), 1u), S2365(), S2366()))))), C1(2, C3(15, a1, a2, a3)), a3, F_Chk_dCL_ddn(a0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcheck_dctr_dfind(V *a) { (void)a; return F_Chk_dcheck_dctr_dfind(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11]); }
static V L2368(V *a) {
return F_Chk_dK_dpure(F_Pair_dfst(a[0]));
}
static V L2367(V *a) {
return F_Chk_dK_dbind(F_Chk_dtele__check(a[5], a[6], a[4], a[3], a[2], a[1], a[0], IMM(0)), mk_clo(L2368, 1, 0, 0));
}
static V F_Chk_dcheck_dctr_dfields(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
return F_Chk_dK_dbind(F_Chk_dtele__fill(a1, a4, a6, F_Chk_dCL_ddn(a0), a3), mk_clo(L2367, 7, 6, (V[]){a3, a7, a6, a5, a2, a0}));
}
static V W_Chk_dcheck_dctr_dfields(V *a) { (void)a; return F_Chk_dcheck_dctr_dfields(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V L2373(V *a) {
return F_Chk_dK_dpure(F_Chk_duses__add(a[0], a[1]));
}
static V L2372(V *a) {
return F_Chk_dK_dbind(F_Chk_dcheck_dlet_dused(a[6], a[5], a[4], a[3], a[2], a[1], a[7]), mk_clo(L2373, 2, 1, (V[]){a[0]}));
}
static V L2371(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[12], F_Chk_dclo__apply(a[13], a[11], F_Chk_dlet_dvars(a[10], a[9], a[8])), a[7], a[6], a[5], F_U32_dadd(a[8], a[4])), mk_clo(L2372, 8, 7, (V[]){a[0], a[1], a[8], a[2], a[3], a[10], a[12]}));
}
static V F_Chk_dcheck_dlet_dbody(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10) {
top:;
V v2369 = a10;
V v2370 = F_U32_dfrom__nat(F_List_dlength(a1));
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2371, 14, 13, (V[]){FLD(v2369, 1), a4, a8, a5, v2370, FLD(v2369, 0), a7, a6, a9, a2, a1, a3, a0}));
}
static V W_Chk_dcheck_dlet_dbody(V *a) { (void)a; return F_Chk_dcheck_dlet_dbody(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10]); }
static V L2376(V *a) {
return F_Chk_dcheck_dlet_dused(a[6], a[5], a[4], a[3], F_U32_dinc(a[2]), a[1], F_Chk_duses__del(a[0], a[2]));
}
static V F_Chk_dcheck_dlet_dused(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2374 = a1;
V s2375 = a2;
if (TAG(s2374) == 1 && TAG(s2375) == 1) {
return F_Chk_dK_dbind(F_Chk_dquant__used(a3, FLD(s2374, 0), FLD(s2375, 0), F_Chk_duses__get(a6, a4), a5, F_Chk_dCL_ddn(a0)), mk_clo(L2376, 8, 7, (V[]){a6, a5, a4, a3, FLD(s2375, 1), FLD(s2374, 1), a0}));
} else {
return F_Chk_dK_dpure(a6);
}
}
static V W_Chk_dcheck_dlet_dused(V *a) { (void)a; return F_Chk_dcheck_dlet_dused(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_duses__del(V a0, V a1) {
top:;
V s2377 = a0;
if ((s2377) == IMM(0)) {
return IMM(0);
} else if (TAG(s2377) == 1) {
return F_Chk_duses__del_dif(C2(0, FLD(FLD(s2377, 0), 0), FLD(FLD(s2377, 0), 1)), F_Chk_duses__del(FLD(s2377, 1), a1), F_U32_dis__eq(a1, FLD(FLD(s2377, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duses__del(V *a) { (void)a; return F_Chk_duses__del(a[0], a[1]); }
static V F_Chk_duses__del_dif(V a0, V a1, V a2) {
top:;
V s2378 = a2;
if ((s2378) == IMM(1)) {
return a1;
} else if ((s2378) == IMM(0)) {
return C2(1, a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duses__del_dif(V *a) { (void)a; return F_Chk_duses__del_dif(a[0], a[1], a[2]); }
static V F_Chk_duses__get(V a0, V a1) {
top:;
V s2379 = a0;
if ((s2379) == IMM(0)) {
return IMM(0);
} else if (TAG(s2379) == 1) {
return F_Bool_dpick(F_U32_dis__eq(a1, FLD(FLD(s2379, 0), 0)), FLD(FLD(s2379, 0), 1), F_Chk_duses__get(FLD(s2379, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duses__get(V *a) { (void)a; return F_Chk_duses__get(a[0], a[1]); }
static V S2380(void) { static V c; return STRC(c, " (consumed more than once)"); }
static V F_Chk_dquant__used(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dK_dif(F_Chk_dQ_deq(F_Chk_dquant__join(a3, a2), a2), F_Chk_dK_dpure(IMM(0)), F_Chk_dK_derr(a0, C1(1, F_String_dappend(F_Chk_dquant__show(a2), a1)), C1(1, F_Bool_dpick(F_Chk_dQ_dis__many(a3), F_String_dappend(a1, S2380()), F_String_dappend(F_Chk_dquant__show(a3), a1))), a4, a5));
}
static V W_Chk_dquant__used(V *a) { (void)a; return F_Chk_dquant__used(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dlet_dvars(V a0, V a1, V a2) {
top:;
V s2381 = a0;
V s2382 = a1;
if (TAG(s2381) == 1 && TAG(s2382) == 1) {
return C2(1, C4(3, FLD(s2381, 0), a2, IMM(0), FLD(s2382, 0)), F_Chk_dlet_dvars(FLD(s2381, 1), FLD(s2382, 1), F_U32_dinc(a2)));
} else {
return IMM(0);
}
}
static V W_Chk_dlet_dvars(V *a) { (void)a; return F_Chk_dlet_dvars(a[0], a[1], a[2]); }
static V L2387(V *a) {
return F_Chk_dcheck_dlets(a[12], a[11], a[10], a[9], a[8], a[7], F_Chk_dctx__bind(a[6], F_U32_dadd(a[5], a[4]), a[3], a[2], F_Chk_dIR_dty(a[1])), a[5], F_U32_dinc(a[4]), F_Chk_duses__add(a[0], F_Chk_dIR_dus(a[1])));
}
static V L2386(V *a) {
return F_Chk_dK_dbind(F_Chk_dcheck__kind(a[11], F_Chk_dIR_dty(a[12]), a[10], a[9], a[8], IMM(0)), mk_clo(L2387, 14, 13, (V[]){a[0], a[12], a[1], a[10], a[2], a[8], a[3], a[9], a[4], a[5], a[6], a[7], a[11]}));
}
static V F_Chk_dcheck_dlets(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9) {
top:;
V s2383 = a1;
V s2384 = a2;
V s2385 = a3;
if (TAG(s2383) == 1 && TAG(s2384) == 1 && TAG(s2385) == 1) {
return F_Chk_dK_dbind(F_Chk_dterm__infer(a0, FLD(s2384, 0), F_Chk_dquant__dem(FLD(s2385, 0), a4), a5, a7, IMM(0)), mk_clo(L2386, 13, 12, (V[]){a9, FLD(s2383, 0), a8, a6, a4, FLD(s2385, 1), FLD(s2384, 1), FLD(s2383, 1), a7, a5, FLD(s2385, 0), a0}));
} else {
return F_Chk_dK_dpure(C2(0, a6, a9));
}
}
static V W_Chk_dcheck_dlets(V *a) { (void)a; return F_Chk_dcheck_dlets(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]); }
static V L2389(V *a) {
return F_Chk_dcheck__kind_dgo(apply(F_Chk_dterm__check(a[5], a[4], IMM(0), a[3], a[2], a[1]), a[6]), a[3], a[0]);
}
static V F_Chk_dcheck__kind(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v2388 = C2(7, C2(9, F_Chk_dlhs__kind(a0, a2), a5), a5);
return mk_clo(L2389, 7, 6, (V[]){a5, a4, a3, v2388, a1, a0});
}
static V W_Chk_dcheck__kind(V *a) { (void)a; return F_Chk_dcheck__kind(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dcheck__kind_dgo(V a0, V a1, V a2) {
top:;
V s2390 = a0;
if (TAG(s2390) == 1) {
return C1(1, C2(0, IMM(0), F_Pair_dsnd(FLD(s2390, 0))));
} else if (TAG(s2390) == 0) {
return C1(0, F_Chk_dcheck__kind_derr(FLD(s2390, 0), a1, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcheck__kind_dgo(V *a) { (void)a; return F_Chk_dcheck__kind_dgo(a[0], a[1], a[2]); }
static V F_Chk_dcheck__kind_derr(V a0, V a1, V a2) {
top:;
V v2391 = a0;
return CN(0, 7, (V[]){FLD(v2391, 0), FLD(v2391, 1), FLD(v2391, 2), FLD(v2391, 3), F_Bool_dpick(F_Chk_dMsg_dis__kind(FLD(v2391, 2), a1), a2, FLD(v2391, 4)), FLD(v2391, 5), FLD(v2391, 6)});
}
static V W_Chk_dcheck__kind_derr(V *a) { (void)a; return F_Chk_dcheck__kind_derr(a[0], a[1], a[2]); }
static V F_Chk_dMsg_dis__kind(V a0, V a1) {
top:;
V s2392 = a0;
V s2393 = a1;
if (TAG(s2392) == 2 && TAG(FLD(s2392, 0)) == 7 && TAG(FLD(FLD(s2392, 0), 0)) == 9 && TAG(s2393) == 7 && TAG(FLD(s2393, 0)) == 9) {
return F_Bool_dand(F_Chk_dQ_deq(FLD(FLD(FLD(s2392, 0), 0), 0), FLD(FLD(s2393, 0), 0)), F_Chk_dSp_deq(FLD(FLD(FLD(s2392, 0), 0), 1), FLD(FLD(s2393, 0), 1)));
} else {
return IMM(0);
}
}
static V W_Chk_dMsg_dis__kind(V *a) { (void)a; return F_Chk_dMsg_dis__kind(a[0], a[1]); }
static V F_Chk_dSp_deq(V a0, V a1) {
top:;
V s2394 = a0;
V s2395 = a1;
if ((s2394) == IMM(0) && (s2395) == IMM(0)) {
return IMM(1);
} else if (TAG(s2394) == 1 && TAG(s2395) == 1) {
return F_Bool_dand(F_U32_dis__eq(FLD(s2394, 1), FLD(s2395, 1)), F_U32_dis__eq(FLD(s2394, 2), FLD(s2395, 2)));
} else {
return IMM(0);
}
}
static V W_Chk_dSp_deq(V *a) { (void)a; return F_Chk_dSp_deq(a[0], a[1]); }
static V L2404(V *a) {
return F_Chk_dK_dpure(F_Chk_duses__del(a[1], a[0]));
}
static V L2403(V *a) {
return F_Chk_dK_dbind(F_Chk_dquant__used(a[5], a[4], a[3], F_Chk_duses__get(a[6], a[2]), a[1], F_Chk_dCL_ddn(a[0])), mk_clo(L2404, 3, 2, (V[]){a[2], a[6]}));
}
static V L2402(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[11], F_Chk_dclo__apply(a[12], a[10], C2(1, a[9], IMM(0))), a[8], F_Chk_dclo__apply(a[12], a[7], C2(1, a[9], IMM(0))), F_Chk_dctx__bind(a[6], a[5], a[4], a[3], a[2]), F_U32_dinc(a[5])), mk_clo(L2403, 7, 6, (V[]){a[0], a[1], a[5], a[4], a[3], a[6]}));
}
static V L2401(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2402, 13, 12, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11]}));
}
static V L2400(V *a) {
return F_Chk_dK_dbind(F_Chk_dCL_dunder(a[10], a[9]), mk_clo(L2401, 12, 11, (V[]){a[10], a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[9], a[8]}));
}
static V F_Chk_dcheck_dlam(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9) {
top:;
V s2396 = a5;
if (TAG(s2396) == 11) {
V v2397 = C3(0, a1, a9, IMM(0));
V v2398 = F_Bool_dand(F_Chk_dQ_dis__many(a4), F_Chk_dQ_dis__lone(FLD(s2396, 0)));
V v2399 = F_Bool_dpick(v2398, IMM(2), FLD(s2396, 0));
return F_Chk_dK_dbind(F_Chk_dK_dif(v2398, F_Chk_dcheck__kind(a0, FLD(s2396, 3), v2399, a8, a9, a3), F_Chk_dK_dpure(IMM(0))), mk_clo(L2400, 12, 11, (V[]){a3, FLD(s2396, 3), a1, v2399, a9, a8, FLD(s2396, 4), a6, a2, v2397, a0}));
} else {
return F_Chk_dcheck_dtypeless(a0, CN(12, 5, (V[]){a1, 0u, a2, a3, a4}), a7, a8, a3);
}
}
static V W_Chk_dcheck_dlam(V *a) { (void)a; return F_Chk_dcheck_dlam(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]); }
static V L2407(V *a) {
return F_Chk_dK_dpure(CN(0, 6, (V[]){F_Chk_dterm__apply1(a[7], a[6], a[5]), a[4], a[3], a[2], a[1], a[0]}));
}
static V F_Chk_dCL_dunder(V a0, V a1) {
top:;
V v2405 = a0;
V s2406 = FLD(v2405, 1);
if ((s2406) == 0) {
return F_Chk_dK_dpure(CN(0, 6, (V[]){FLD(v2405, 0), FLD(v2405, 1), FLD(v2405, 2), FLD(v2405, 3), FLD(v2405, 4), FLD(v2405, 5)}));
} else if (nat_ge(s2406, 1)) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2407, 8, 7, (V[]){FLD(v2405, 5), FLD(v2405, 4), FLD(v2405, 3), FLD(v2405, 2), nat_subk(s2406, 1), a1, FLD(v2405, 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCL_dunder(V *a) { (void)a; return F_Chk_dCL_dunder(a[0], a[1]); }
static V F_Chk_dQ_dis__lone(V a0) {
top:;
V s2408 = a0;
if ((s2408) == IMM(1)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dQ_dis__lone(V *a) { (void)a; return F_Chk_dQ_dis__lone(a[0]); }
static V S2411(void) { static V c; return STRC(c, "~"); }
static V S2414(void) { static V c; return STRC(c, "a fresh ~ binder name"); }
static V S2415(void) { static V c; return STRC(c, ""); }
static V L2418(V *a) {
return F_Chk_ddef__check_dtmpl(a[5], a[4], C3(13, a[3], C3(4, a[2], IMM(0), IMM(0)), IMM(0)), F_Chk_dterm__apply1(a[6], a[1], C3(4, a[2], IMM(0), IMM(0))), F_Chk_dclo__apply(a[6], F_Chk_dAll_db(a[0]), C2(1, C3(4, a[2], IMM(0), IMM(0)), IMM(0))));
}
static V L2417(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2418, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L2416(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dset__book(F_Chk_dbook__set(a[6], a[5], CN(0, 7, (V[]){0u, 0u, F_Chk_dAll_da(a[4]), IMM(0), IMM(0), IMM(1), IMM(0)}))), mk_clo(L2417, 7, 6, (V[]){a[4], a[0], a[5], a[1], a[2], a[3]}));
}
static V L2413(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dif(F_Chk_dbook__has(a[6], a[5]), F_Chk_dK_derr(IMM(0), C1(1, S2414()), C1(1, F_Chk_dAll_dk(a[4])), IMM(0), S2415()), F_Chk_dK_dpure(IMM(0))), mk_clo(L2416, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L2412(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2413, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L2410(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_String_dappend(a[3], F_String_dappend(S2411(), F_Chk_dAll_dk(a[4])))), mk_clo(L2412, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V F_Chk_ddef__check_dtmpl(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2409 = a1;
if ((s2409) == 0) {
return F_Chk_dK_dpure(C2(0, a2, C2(0, a3, a4)));
} else if (nat_ge(s2409, 1)) {
return F_Chk_dK_dbind(F_Chk_dtele__head(a4, IMM(0), a0, IMM(0)), mk_clo(L2410, 5, 4, (V[]){a3, a2, nat_subk(s2409, 1), a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_ddef__check_dtmpl(V *a) { (void)a; return F_Chk_ddef__check_dtmpl(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dbook__has(V a0, V a1) {
top:;
return F_Maybe_dis__some(F_Chk_dbook__tld(a0, a1));
}
static V W_Chk_dbook__has(V *a) { (void)a; return F_Chk_dbook__has(a[0], a[1]); }
static V F_Chk_dtele__unbind(V a0, V a1) {
top:;
return F_Chk_dtele__unbind_dgo(a0, F_Chk_dterm__wnf(a0, a1), 0u, IMM(0));
}
static V W_Chk_dtele__unbind(V *a) { (void)a; return F_Chk_dtele__unbind(a[0], a[1]); }
static V F_Chk_dtele__unbind_dgo(V a0, V a1, V a2, V a3) {
top:;
V s2419 = a1;
if (TAG(s2419) == 11) {
{ V t0 = a0; V t1 = F_Chk_dterm__wnf(a0, F_Chk_dclo__apply(a0, FLD(s2419, 4), C2(1, C3(0, FLD(s2419, 1), a2, IMM(0)), IMM(0)))); V t2 = F_U32_dinc(a2); V t3 = F_List_dappend(a3, C2(1, C3(0, FLD(s2419, 0), FLD(s2419, 1), FLD(s2419, 3)), IMM(0))); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else {
return C2(0, a3, s2419);
}
}
static V W_Chk_dtele__unbind_dgo(V *a) { (void)a; return F_Chk_dtele__unbind_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dDom_dqs(V a0) {
top:;
V s2420 = a0;
if ((s2420) == IMM(0)) {
return IMM(0);
} else if (TAG(s2420) == 1) {
return C2(1, FLD(FLD(s2420, 0), 0), F_Chk_dDom_dqs(FLD(s2420, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dDom_dqs(V *a) { (void)a; return F_Chk_dDom_dqs(a[0]); }
static V F_Chk_dTld_dimps(V a0) {
top:;
V s2421 = a0;
if (TAG(s2421) == 0) {
return FLD(s2421, 6);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dimps(V *a) { (void)a; return F_Chk_dTld_dimps(a[0]); }
static V S2425(void) { static V c; return STRC(c, "a foreign definition returning base IO(...) directly (return type aliases are not unfolded)"); }
static V L2424(V *a) {
return F_Chk_dK_dif(F_Chk_dvalid_dio(a[1], F_Chk_dterm__head(a[2])), F_Chk_dK_dpure(IMM(0)), F_Chk_dK_derr(IMM(0), C1(1, S2425()), C1(1, a[0]), F_Chk_dTm_dspan(a[2]), a[0]));
}
static V L2423(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dvalid_dret(a[2], F_Chk_dterm__strip(F_Chk_dTld_dt(a[1])), 0u)), mk_clo(L2424, 3, 2, (V[]){a[0], a[2]}));
}
static V F_Chk_dvalid_dforeign(V a0, V a1, V a2) {
top:;
V s2422 = a2;
if ((s2422) == IMM(0)) {
return F_Chk_dK_dpure(IMM(0));
} else if (TAG(s2422) == 1) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2423, 3, 2, (V[]){a0, a1}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dvalid_dforeign(V *a) { (void)a; return F_Chk_dvalid_dforeign(a[0], a[1], a[2]); }
static V F_Chk_dvalid_dret(V a0, V a1, V a2) {
top:;
V s2426 = a1;
if (TAG(s2426) == 11) {
{ V t0 = a0; V t1 = F_Chk_dterm__strip(F_Chk_dclo__apply(a0, FLD(s2426, 4), C2(1, C3(0, FLD(s2426, 1), a2, IMM(0)), IMM(0)))); V t2 = F_U32_dinc(a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else {
return s2426;
}
}
static V W_Chk_dvalid_dret(V *a) { (void)a; return F_Chk_dvalid_dret(a[0], a[1], a[2]); }
static V F_Chk_dCL_dof(V a0, V a1) {
top:;
return CN(0, 6, (V[]){C3(4, a0, IMM(0), IMM(0)), 0u, a0, IMM(0), a1, 0u});
}
static V W_Chk_dCL_dof(V *a) { (void)a; return F_Chk_dCL_dof(a[0], a[1]); }
static V F_Chk_dTld_ddec(V a0) {
top:;
V s2427 = a0;
if (TAG(s2427) == 0) {
return CN(0, 7, (V[]){FLD(s2427, 0), FLD(s2427, 1), FLD(s2427, 2), IMM(0), FLD(s2427, 4), FLD(s2427, 5), FLD(s2427, 6)});
} else {
return s2427;
}
}
static V W_Chk_dTld_ddec(V *a) { (void)a; return F_Chk_dTld_ddec(a[0]); }
static V F_Chk_dbook__opened(V a0) {
top:;
V v2428 = a0;
return CN(0, 7, (V[]){FLD(v2428, 0), FLD(v2428, 1), FLD(v2428, 2), FLD(v2428, 3), nat_addk(FLD(v2428, 4), 1), FLD(v2428, 5), FLD(v2428, 6)});
}
static V W_Chk_dbook__opened(V *a) { (void)a; return F_Chk_dbook__opened(a[0]); }
static V F_Chk_dTld_dis__law__open(V a0) {
top:;
V s2429 = a0;
if (TAG(s2429) == 0 && (FLD(s2429, 3)) == IMM(0) && (FLD(s2429, 5)) == IMM(0) && (FLD(s2429, 6)) == IMM(0)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dis__law__open(V *a) { (void)a; return F_Chk_dTld_dis__law__open(a[0]); }
static V L2433(V *a) {
return F_Chk_dvalid_dctrs(a[2], a[1], a[3], a[0]);
}
static V L2432(V *a) {
return F_Chk_dK_dbind(F_Chk_dvalid_dkind(a[3], a[2], a[4]), mk_clo(L2433, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V L2431(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dtele__unbind(a[4], a[3])), mk_clo(L2432, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V L2430(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2431, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Chk_dvalid_dadt(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dK_dbind(F_Chk_dterm__check(F_Chk_dCL_dof(a0, IMM(0)), a2, IMM(0), F_Chk_dtyp(IMM(1)), IMM(0), 0u), mk_clo(L2430, 5, 4, (V[]){a3, a1, a0, a2}));
}
static V W_Chk_dvalid_dadt(V *a) { (void)a; return F_Chk_dvalid_dadt(a[0], a[1], a[2], a[3]); }
static V L2435(V *a) {
return F_Chk_dvalid_dctrs(a[3], a[2], a[1], a[0]);
}
static V F_Chk_dvalid_dctrs(V a0, V a1, V a2, V a3) {
top:;
V s2434 = a3;
if ((s2434) == IMM(0)) {
return F_Chk_dK_dpure(IMM(0));
} else if (TAG(s2434) == 1) {
return F_Chk_dK_dbind(F_Chk_dvalid_dfields(a0, a1, a2, FLD(FLD(s2434, 0), 0), FLD(FLD(s2434, 0), 2), F_Nat_dadd(a1, FLD(FLD(s2434, 0), 1)), 0u, IMM(0)), mk_clo(L2435, 5, 4, (V[]){FLD(s2434, 1), a2, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dvalid_dctrs(V *a) { (void)a; return F_Chk_dvalid_dctrs(a[0], a[1], a[2], a[3]); }
static V L2440(V *a) {
return F_Chk_dvalid_dfields(a[8], a[7], a[6], a[5], F_Chk_dclo__apply(a[9], F_Chk_dAll_db(a[4]), C2(1, C3(0, F_Chk_dAll_dk(a[4]), a[3], IMM(0)), IMM(0))), a[2], F_U32_dinc(a[3]), F_Chk_dctx__bind(a[1], a[3], a[0], F_Chk_dAll_dk(a[4]), F_Chk_dAll_da(a[4])));
}
static V L2439(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2440, 10, 9, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]}));
}
static V L2438(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(F_Chk_dCL_dof(a[7], IMM(0)), F_Chk_dAll_da(a[6]), IMM(0), F_Bool_dpick(F_Bool_dand(F_Nat_dis__ge(F_U32_dto__nat(a[5]), a[4]), F_Chk_dQ_dis__lone(a[8])), a[3], F_Chk_dtyp(a[8])), a[2], a[5]), mk_clo(L2439, 10, 9, (V[]){a[8], a[2], a[0], a[5], a[6], a[7], a[3], a[4], a[1]}));
}
static V L2437(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dAll_dq(a[7])), mk_clo(L2438, 9, 8, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[7], a[6]}));
}
static V L2441(V *a) {
return F_Chk_dvalid_dtip(a[4], a[3], a[2], F_Chk_dterm__wnf(a[5], a[1]), a[0]);
}
static V F_Chk_dvalid_dfields(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s2436 = a5;
if (nat_ge(s2436, 1)) {
return F_Chk_dK_dbind(F_Chk_dtele__head(a4, a7, a3, IMM(0)), mk_clo(L2437, 8, 7, (V[]){nat_subk(s2436, 1), a0, a7, a2, a1, a6, a3}));
} else if ((s2436) == 0) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2441, 6, 5, (V[]){a7, a4, a3, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dvalid_dfields(V *a) { (void)a; return F_Chk_dvalid_dfields(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S2443(void) { static V c; return STRC(c, "a telescope tipped at "); }
static V S2444(void) { static V c; return STRC(c, " applied to its own parameters"); }
static V L2442(V *a) {
return F_Chk_dK_dif(F_Chk_dvalid_dtip_dok(a[5], a[4], a[3], a[2]), F_Chk_dK_dpure(IMM(0)), F_Chk_dK_derr(a[1], C1(1, F_String_dappend(S2443(), F_String_dappend(a[4], S2444()))), C1(2, a[2]), IMM(0), a[0]));
}
static V F_Chk_dvalid_dtip(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2442, 6, 5, (V[]){a2, a4, a3, a1, a0}));
}
static V W_Chk_dvalid_dtip(V *a) { (void)a; return F_Chk_dvalid_dtip(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dvalid_dtip_dok(V a0, V a1, V a2, V a3) {
top:;
V s2445 = a3;
if (TAG(s2445) == 14) {
return F_Bool_dand(F_Bool_dand(F_String_deq(a1, FLD(s2445, 0)), F_Nat_dis__eq(F_List_dlength(FLD(s2445, 1)), a2)), F_Bool_dand(F_Chk_dLst_dempty(FLD(s2445, 3)), F_Chk_dvalid_dtip_dparams(a0, FLD(s2445, 1), 0u)));
} else {
return IMM(0);
}
}
static V W_Chk_dvalid_dtip_dok(V *a) { (void)a; return F_Chk_dvalid_dtip_dok(a[0], a[1], a[2], a[3]); }
static V F_Chk_dvalid_dtip_dparams(V a0, V a1, V a2) {
top:;
V s2446 = a1;
if ((s2446) == IMM(0)) {
return IMM(1);
} else if (TAG(s2446) == 1) {
return F_Bool_dand(F_Chk_dvalid_dtip_dvar(F_Chk_dterm__wnf(a0, FLD(s2446, 0)), a2), F_Chk_dvalid_dtip_dparams(a0, FLD(s2446, 1), F_U32_dinc(a2)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dvalid_dtip_dparams(V *a) { (void)a; return F_Chk_dvalid_dtip_dparams(a[0], a[1], a[2]); }
static V F_Chk_dvalid_dtip_dvar(V a0, V a1) {
top:;
V s2447 = a0;
if (TAG(s2447) == 0) {
return F_U32_dis__eq(FLD(s2447, 1), a1);
} else {
return IMM(0);
}
}
static V W_Chk_dvalid_dtip_dvar(V *a) { (void)a; return F_Chk_dvalid_dtip_dvar(a[0], a[1]); }
static V W_Nat_dis__ge(V *a) { (void)a; return F_Nat_dis__ge(a[0], a[1]); }
static V S2450(void) { static V c; return STRC(c, "a kind (type "); }
static V S2451(void) { static V c; return STRC(c, "<..> is Kind(g))"); }
static V F_Chk_dvalid_dkind(V a0, V a1, V a2) {
top:;
V v2448 = a2;
V s2449 = FLD(v2448, 1);
if (TAG(s2449) == 7) {
return F_Chk_dK_dpure(C2(7, FLD(s2449, 0), FLD(s2449, 1)));
} else {
return F_Chk_dK_derr(F_Chk_dDom_dctx(FLD(v2448, 0), 0u, IMM(0)), C1(1, F_String_dappend(S2450(), F_String_dappend(a0, S2451()))), C1(2, s2449), F_Chk_dSp_dor(F_Chk_dTm_dspan(s2449), F_Chk_dTm_dspan(a1)), a0);
}
}
static V W_Chk_dvalid_dkind(V *a) { (void)a; return F_Chk_dvalid_dkind(a[0], a[1], a[2]); }
static V F_Chk_dDom_dctx(V a0, V a1, V a2) {
top:;
V s2452 = a0;
if ((s2452) == IMM(0)) {
return a2;
} else if (TAG(s2452) == 1) {
{ V t0 = FLD(s2452, 1); V t1 = F_U32_dinc(a1); V t2 = F_Chk_dctx__bind(a2, a1, FLD(FLD(s2452, 0), 0), FLD(FLD(s2452, 0), 1), FLD(FLD(s2452, 0), 2)); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dDom_dctx(V *a) { (void)a; return F_Chk_dDom_dctx(a[0], a[1], a[2]); }
static V F_Chk_dbook__set__ctrs(V a0, V a1) {
top:;
V s2453 = a1;
if ((s2453) == IMM(0)) {
return a0;
} else if (TAG(s2453) == 1) {
{ V t0 = F_Chk_dbook__set__ctr(a0, FLD(FLD(s2453, 0), 0), C3(0, FLD(FLD(s2453, 0), 0), FLD(FLD(s2453, 0), 1), FLD(FLD(s2453, 0), 2))); V t1 = FLD(s2453, 1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dbook__set__ctrs(V *a) { (void)a; return F_Chk_dbook__set__ctrs(a[0], a[1]); }
static V F_Chk_dbook__set__ctr(V a0, V a1, V a2) {
top:;
V v2454 = a0;
return CN(0, 7, (V[]){FLD(v2454, 0), F_Map_dset(FLD(v2454, 1), a1, a2), FLD(v2454, 2), FLD(v2454, 3), FLD(v2454, 4), FLD(v2454, 5), FLD(v2454, 6)});
}
static V W_Chk_dbook__set__ctr(V *a) { (void)a; return F_Chk_dbook__set__ctr(a[0], a[1], a[2]); }
static V F_Chk_dcheck__book_dfin(V a0) {
top:;
V s2455 = a0;
if (TAG(s2455) == 0) {
return C1(0, FLD(s2455, 0));
} else if (TAG(s2455) == 1) {
return F_Chk_dcheck__book_dholes(F_Pair_dsnd(FLD(s2455, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcheck__book_dfin(V *a) { (void)a; return F_Chk_dcheck__book_dfin(a[0]); }
static V S2457(void) { static V c; return STRC(c, " TODO"); }
static V S2458(void) { static V c; return STRC(c, ""); }
static V S2459(void) { static V c; return STRC(c, "s"); }
static V S2460(void) { static V c; return STRC(c, " found.\012The code is incomplete, and not a valid proof yet."); }
static V S2461(void) { static V c; return STRC(c, ""); }
static V S2462(void) { static V c; return STRC(c, "!raw"); }
static V F_Chk_dcheck__book_dholes(V a0) {
top:;
V v2456 = F_Chk_dBook_dholes(a0);
return F_Bool_dpick(F_Nat_dis__eq(v2456, 0u), F_Chk_dcheck__book_downed(a0), C1(0, CN(0, 7, (V[]){F_Chk_dbook__nil(), IMM(0), C1(1, F_String_dappend(F_Nat_dshow(v2456), F_String_dappend(S2457(), F_String_dappend(F_Bool_dpick(F_Nat_dis__eq(v2456, 1u), S2458(), S2459()), S2460())))), IMM(0), IMM(0), S2461(), S2462()})));
}
static V W_Chk_dcheck__book_dholes(V *a) { (void)a; return F_Chk_dcheck__book_dholes(a[0]); }
static V F_Chk_dbook__nil(void) {
top:;
return CN(0, 7, (V[]){IMM(0), IMM(0), IMM(0), 0u, 0u, IMM(0), IMM(0)});
}
static V W_Chk_dbook__nil(V *a) { (void)a; return F_Chk_dbook__nil(); }
static V S2463(void) { static V c; return STRC(c, "Clo.apply"); }
static V S2464(void) { static V c; return STRC(c, "Clo.apply"); }
static V S2465(void) { static V c; return STRC(c, "Clo.apply is a name the compiler encodes itself: name yours apart"); }
static V S2466(void) { static V c; return STRC(c, ""); }
static V S2467(void) { static V c; return STRC(c, "!raw"); }
static V F_Chk_dcheck__book_downed(V a0) {
top:;
return F_Bool_dpick(F_Bool_dand(F_Chk_dbook__has(a0, S2463()), F_Bool_dnot(F_Chk_dTld_dbase__of(F_Chk_dbook__tld(a0, S2464())))), C1(0, CN(0, 7, (V[]){F_Chk_dbook__nil(), IMM(0), C1(1, S2465()), IMM(0), IMM(0), S2466(), S2467()})), C1(1, a0));
}
static V W_Chk_dcheck__book_downed(V *a) { (void)a; return F_Chk_dcheck__book_downed(a[0]); }
static V F_Chk_dTld_dbase__of(V a0) {
top:;
V s2468 = a0;
if (TAG(s2468) == 1 && TAG(FLD(s2468, 0)) == 0) {
return FLD(FLD(s2468, 0), 5);
} else if (TAG(s2468) == 1 && TAG(FLD(s2468, 0)) == 1) {
return FLD(FLD(s2468, 0), 4);
} else if ((s2468) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dTld_dbase__of(V *a) { (void)a; return F_Chk_dTld_dbase__of(a[0]); }
static V F_Chk_dBook_dholes(V a0) {
top:;
V v2469 = a0;
return F_Nat_dadd(FLD(v2469, 3), FLD(v2469, 4));
}
static V W_Chk_dBook_dholes(V *a) { (void)a; return F_Chk_dBook_dholes(a[0]); }
static V F_Main_dcheck_dres(V a0, V a1) {
top:;
V s2470 = a1;
if (TAG(s2470) == 0) {
return F_Main_dchk_dfail(FLD(s2470, 0));
} else if (TAG(s2470) == 1) {
return F_IO_dpure(C2(0, FLD(s2470, 0), a0));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dcheck_dres(V *a) { (void)a; return F_Main_dcheck_dres(a[0], a[1]); }
static V F_Main_dchk_dfail(V a1) {
top:;
return F_IO_ddie(1u, F_Chk_dshow__err(a1));
}
static V W_Main_dchk_dfail(V *a) { (void)a; return F_Main_dchk_dfail(a[1]); }
static V S2472(void) { static V c; return STRC(c, "!raw"); }
static V S2473(void) { static V c; return STRC(c, "Error: "); }
static V F_Chk_dshow__err(V a0) {
top:;
V v2471 = a0;
return F_Bool_dpick(F_String_deq(FLD(v2471, 6), S2472()), F_String_dappend(S2473(), F_Chk_dshow__err_draw(FLD(v2471, 2))), F_Chk_derr__show(CN(0, 7, (V[]){FLD(v2471, 0), FLD(v2471, 1), FLD(v2471, 2), FLD(v2471, 3), FLD(v2471, 4), FLD(v2471, 5), FLD(v2471, 6)})));
}
static V W_Chk_dshow__err(V *a) { (void)a; return F_Chk_dshow__err(a[0]); }
static V S2480(void) { static V c; return STRC(c, ""); }
static V S2481(void) { static V c; return STRC(c, " "); }
static V S2482(void) { static V c; return STRC(c, "Error:"); }
static V S2483(void) { static V c; return STRC(c, ""); }
static V S2484(void) { static V c; return STRC(c, "\012Context:"); }
static V S2485(void) { static V c; return STRC(c, ""); }
static V S2486(void) { static V c; return STRC(c, "\012Location:"); }
static V S2487(void) { static V c; return STRC(c, ""); }
static V S2488(void) { static V c; return STRC(c, "\012"); }
static V F_Chk_derr__show(V a0) {
top:;
V v2474 = a0;
V v2475 = F_Chk_dctx__scope(FLD(v2474, 1));
V v2476 = F_Chk_derr_dmsg(FLD(v2474, 0), FLD(v2474, 2), FLD(v2474, 3), v2475);
V v2477 = F_Chk_derr_dctx__lines(FLD(v2474, 0), F_Chk_dctx__sorted(FLD(v2474, 1)), v2475, F_Chk_dctx__width(FLD(v2474, 1)));
V v2478 = F_Chk_derr_dlines(FLD(v2474, 4));
V v2479 = F_Bool_dpick(F_String_dis__empty(FLD(v2474, 5)), S2480(), F_String_dappend(S2481(), FLD(v2474, 5)));
return F_String_dappend(S2482(), F_String_dappend(v2476, F_String_dappend(F_Bool_dpick(F_Chk_dLst_dempty(FLD(v2474, 1)), S2483(), S2484()), F_String_dappend(v2477, F_String_dappend(F_Bool_dpick(F_Bool_dand(F_String_dis__empty(v2479), F_String_dis__empty(v2478)), S2485(), F_String_dappend(S2486(), F_String_dappend(v2479, v2478))), F_Bool_dpick(F_String_dis__empty(FLD(v2474, 6)), S2487(), F_String_dappend(S2488(), FLD(v2474, 6))))))));
}
static V W_Chk_derr__show(V *a) { (void)a; return F_Chk_derr__show(a[0]); }
static V S2490(void) { static V c; return STRC(c, ""); }
static V F_Chk_derr_dlines(V a0) {
top:;
V s2489 = a0;
if ((s2489) == IMM(0)) {
return S2490();
} else if (TAG(s2489) == 1) {
return F_Chk_derr_dlines_dgo(F_String_dsplit(FLD(s2489, 0), 10u), F_Nat_dadd(1u, F_Chk_dStr_dcount__nl(F_String_dtake(FLD(s2489, 0), F_U32_dto__nat(FLD(s2489, 1))))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_derr_dlines(V *a) { (void)a; return F_Chk_derr_dlines(a[0]); }
static V F_Chk_dStr_dcount__nl(V a0) {
top:;
V s2491 = a0;
if ((s2491) == IMM(0)) {
return 0u;
} else if (TAG(s2491) == 1) {
return F_Nat_dadd(F_Bool_dpick(F_U32_dis__eq(FLD(s2491, 0), 10u), 1u, 0u), F_Chk_dStr_dcount__nl(FLD(s2491, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dcount__nl(V *a) { (void)a; return F_Chk_dStr_dcount__nl(a[0]); }
static V F_Chk_derr_dlines_dgo(V a0, V a1) {
top:;
V v2492 = F_Nat_dmax(1u, F_Nat_dsub(a1, 1u));
V v2493 = F_Nat_dmin(F_List_dlength(a0), F_Nat_dadd(a1, 1u));
V v2494 = F_String_dlength(F_Nat_dshow(v2493));
return F_Chk_derr_dlines_deach(F_Chk_dList_ddrop__str(a0, F_Nat_dsub(v2492, 1u)), v2492, v2493, a1, v2494);
}
static V W_Chk_derr_dlines_dgo(V *a) { (void)a; return F_Chk_derr_dlines_dgo(a[0], a[1]); }
static V F_Chk_dList_ddrop__str(V a0, V a1) {
top:;
V s2495 = a0;
V s2496 = a1;
if ((s2496) == 0) {
return s2495;
} else if (TAG(s2495) == 1 && nat_ge(s2496, 1)) {
{ V t0 = FLD(s2495, 1); V t1 = nat_subk(s2496, 1); a0 = t0; a1 = t1; goto top; }
} else if ((s2495) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dList_ddrop__str(V *a) { (void)a; return F_Chk_dList_ddrop__str(a[0], a[1]); }
static V S2498(void) { static V c; return STRC(c, ""); }
static V F_Chk_derr_dlines_deach(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2497 = a0;
if ((s2497) == IMM(0)) {
return S2498();
} else if (TAG(s2497) == 1) {
return F_Chk_derr_dlines_done(FLD(s2497, 0), FLD(s2497, 1), a1, a2, a3, a4, F_Nat_dis__gt(a1, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_derr_dlines_deach(V *a) { (void)a; return F_Chk_derr_dlines_deach(a[0], a[1], a[2], a[3], a[4]); }
static V S2500(void) { static V c; return STRC(c, ""); }
static V S2501(void) { static V c; return STRC(c, "\012"); }
static V S2502(void) { static V c; return STRC(c, ">| "); }
static V S2503(void) { static V c; return STRC(c, " | "); }
static V F_Chk_derr_dlines_done(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2499 = a6;
if ((s2499) == IMM(1)) {
return S2500();
} else if ((s2499) == IMM(0)) {
return F_String_dappend(S2501(), F_String_dappend(F_Chk_dStr_dpadl(F_Nat_dshow(a2), a5), F_String_dappend(F_Bool_dpick(F_Nat_dis__eq(a2, a4), S2502(), S2503()), F_String_dappend(a0, F_Chk_derr_dlines_deach(a1, nat_addk(a2, 1), a3, a4, a5)))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_derr_dlines_done(V *a) { (void)a; return F_Chk_derr_dlines_done(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S2505(void) { static V c; return STRC(c, " "); }
static V F_Chk_dStr_dpadl(V a0, V a1) {
top:;
V v2504 = F_String_dlength(a0);
return F_String_dappend(F_String_drepeat(S2505(), F_Nat_dsub(a1, v2504)), a0);
}
static V W_Chk_dStr_dpadl(V *a) { (void)a; return F_Chk_dStr_dpadl(a[0], a[1]); }
static V F_String_drepeat(V a0, V a1) {
top:;
V s2506 = a1;
if ((s2506) == 0) {
return IMM(0);
} else if (nat_ge(s2506, 1)) {
return F_String_dappend(a0, F_String_drepeat(a0, nat_subk(s2506, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_String_drepeat(V *a) { (void)a; return F_String_drepeat(a[0], a[1]); }
static V W_Nat_dmin(V *a) { (void)a; return F_Nat_dmin(a[0], a[1]); }
static V W_Nat_dmax(V *a) { (void)a; return F_Nat_dmax(a[0], a[1]); }
static V F_Chk_dctx__width(V a0) {
top:;
V s2507 = a0;
if ((s2507) == IMM(0)) {
return 0u;
} else if (TAG(s2507) == 1 && TAG(FLD(s2507, 0)) == 33) {
return F_Nat_dmax(F_String_dlength(FLD(FLD(s2507, 0), 2)), F_Chk_dctx__width(FLD(s2507, 1)));
} else if (TAG(s2507) == 1) {
{ V t0 = FLD(s2507, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctx__width(V *a) { (void)a; return F_Chk_dctx__width(a[0]); }
static V F_Chk_dctx__sorted(V a0) {
top:;
return F_List_dreverse(a0);
}
static V W_Chk_dctx__sorted(V *a) { (void)a; return F_Chk_dctx__sorted(a[0]); }
static V S2509(void) { static V c; return STRC(c, ""); }
static V S2510(void) { static V c; return STRC(c, "\012- "); }
static V S2511(void) { static V c; return STRC(c, " : "); }
static V F_Chk_derr_dctx__lines(V a0, V a1, V a2, V a3) {
top:;
V s2508 = a1;
if ((s2508) == IMM(0)) {
return S2509();
} else if (TAG(s2508) == 1 && TAG(FLD(s2508, 0)) == 33) {
return F_String_dappend(S2510(), F_String_dappend(F_Chk_dStr_dpad(FLD(FLD(s2508, 0), 2), a3), F_String_dappend(S2511(), F_String_dappend(F_Chk_dterm__show(F_Chk_dterm__lower(a0, F_Chk_dterm__snf(a0, FLD(FLD(s2508, 0), 3)), FLD(FLD(s2508, 0), 0)), 0u, F_List_dreverse(F_Chk_dList_dtake__str(a2, FLD(FLD(s2508, 0), 0)))), F_Chk_derr_dctx__lines(a0, FLD(s2508, 1), a2, a3)))));
} else if (TAG(s2508) == 1) {
{ V t0 = a0; V t1 = FLD(s2508, 1); V t2 = a2; V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_derr_dctx__lines(V *a) { (void)a; return F_Chk_derr_dctx__lines(a[0], a[1], a[2], a[3]); }
static V F_Chk_dList_dtake__str(V a0, V a1) {
top:;
return F_Chk_dList_dtake__strn(F_U32_dto__nat(a1), a0);
}
static V W_Chk_dList_dtake__str(V *a) { (void)a; return F_Chk_dList_dtake__str(a[0], a[1]); }
static V F_Chk_dList_dtake__strn(V a0, V a1) {
top:;
V s2512 = a0;
V s2513 = a1;
if ((s2512) == 0) {
return IMM(0);
} else if (nat_ge(s2512, 1) && TAG(s2513) == 1) {
return C2(1, FLD(s2513, 0), F_Chk_dList_dtake__strn(nat_subk(s2512, 1), FLD(s2513, 1)));
} else if ((s2513) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dList_dtake__strn(V *a) { (void)a; return F_Chk_dList_dtake__strn(a[0], a[1]); }
static V S2515(void) { static V c; return STRC(c, " "); }
static V F_Chk_dStr_dpad(V a0, V a1) {
top:;
V v2514 = F_String_dlength(a0);
return F_String_dappend(a0, F_String_drepeat(S2515(), F_Nat_dsub(a1, v2514)));
}
static V W_Chk_dStr_dpad(V *a) { (void)a; return F_Chk_dStr_dpad(a[0], a[1]); }
static V S2517(void) { static V c; return STRC(c, "\012- message  : "); }
static V S2518(void) { static V c; return STRC(c, "\012- expected : "); }
static V S2519(void) { static V c; return STRC(c, "\012- observed : "); }
static V F_Chk_derr_dmsg(V a0, V a1, V a2, V a3) {
top:;
V s2516 = a2;
if ((s2516) == IMM(0)) {
return F_String_dappend(S2517(), F_Chk_dexpr__show(a0, a1, a3));
} else {
return F_String_dappend(S2518(), F_String_dappend(F_Chk_dexpr__show(a0, a1, a3), F_String_dappend(S2519(), F_Chk_dexpr__show(a0, s2516, a3))));
}
}
static V W_Chk_derr_dmsg(V *a) { (void)a; return F_Chk_derr_dmsg(a[0], a[1], a[2], a[3]); }
static V S2521(void) { static V c; return STRC(c, ""); }
static V F_Chk_dshow__err_draw(V a0) {
top:;
V s2520 = a0;
if (TAG(s2520) == 1) {
return FLD(s2520, 0);
} else {
return S2521();
}
}
static V W_Chk_dshow__err_draw(V *a) { (void)a; return F_Chk_dshow__err_draw(a[0]); }
static V S2523(void) { static V c; return STRC(c, "bendc: imports nested too deeply at "); }
static V F_Main_dchk_dload(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2522 = a0;
if ((s2522) == 0) {
return F_IO_ddie(1u, F_String_dappend(S2523(), a2));
} else if (nat_ge(s2522, 1)) {
return F_Main_dchk_dseen(nat_subk(s2522, 1), a1, a2, a3, a4, a5, F_Chk_dSB2_dfind(F_CS_dseen(a5), F_Path_dnorm(a2)));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dload(V *a) { (void)a; return F_Main_dchk_dload(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S2525(void) { static V c; return STRC(c, "/"); }
static V S2527(void) { static V c; return STRC(c, "/"); }
static V S2528(void) { static V c; return STRC(c, "/"); }
static V S2529(void) { static V c; return STRC(c, "."); }
static V F_Path_dnorm(V a0) {
top:;
V v2524 = F_String_dstarts__with(a0, S2525());
V v2526 = F_String_djoin(F_List_dreverse(F_Path_dfold(F_String_dsplit(a0, 47u), IMM(0), v2524)), S2527());
return F_Bool_dpick(v2524, F_String_dappend(S2528(), v2526), F_Bool_dpick(F_String_dis__empty(v2526), S2529(), v2526));
}
static V W_Path_dnorm(V *a) { (void)a; return F_Path_dnorm(a[0]); }
static V S2531(void) { static V c; return STRC(c, "."); }
static V F_Path_dfold(V a0, V a1, V a2) {
top:;
V s2530 = a0;
if ((s2530) == IMM(0)) {
return a1;
} else if (TAG(s2530) == 1) {
{ V t0 = FLD(s2530, 1); V t1 = F_Bool_dpick(F_Bool_dor(F_String_dis__empty(FLD(s2530, 0)), F_String_deq(FLD(s2530, 0), S2531())), a1, F_Path_dpush(FLD(s2530, 0), a1, a2)); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Path_dfold(V *a) { (void)a; return F_Path_dfold(a[0], a[1], a[2]); }
static V S2533(void) { static V c; return STRC(c, ".."); }
static V S2534(void) { static V c; return STRC(c, ".."); }
static V S2535(void) { static V c; return STRC(c, ".."); }
static V S2536(void) { static V c; return STRC(c, ".."); }
static V S2537(void) { static V c; return STRC(c, ".."); }
static V F_Path_dpush(V a0, V a1, V a2) {
top:;
V s2532 = a1;
if ((s2532) == IMM(0)) {
return F_Bool_dpick(F_String_deq(a0, S2533()), F_Bool_dpick(a2, IMM(0), C2(1, S2534(), IMM(0))), C2(1, a0, IMM(0)));
} else if (TAG(s2532) == 1) {
return F_Bool_dpick(F_String_deq(a0, S2535()), F_Bool_dpick(F_String_deq(FLD(s2532, 0), S2536()), C2(1, S2537(), C2(1, FLD(s2532, 0), FLD(s2532, 1))), FLD(s2532, 1)), C2(1, a0, C2(1, FLD(s2532, 0), FLD(s2532, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Path_dpush(V *a) { (void)a; return F_Path_dpush(a[0], a[1], a[2]); }
static V F_CS_dseen(V a0) {
top:;
V v2538 = a0;
return FLD(v2538, 1);
}
static V W_CS_dseen(V *a) { (void)a; return F_CS_dseen(a[0]); }
static V F_Chk_dSB2_dfind(V a0, V a1) {
top:;
V s2539 = a0;
if ((s2539) == IMM(0)) {
return IMM(0);
} else if (TAG(s2539) == 1) {
return F_Chk_dSB2_dfind_dif(FLD(s2539, 1), a1, FLD(FLD(s2539, 0), 1), F_String_deq(a1, FLD(FLD(s2539, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dSB2_dfind(V *a) { (void)a; return F_Chk_dSB2_dfind(a[0], a[1]); }
static V F_Chk_dSB2_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s2540 = a3;
if ((s2540) == IMM(1)) {
return C1(1, a2);
} else if ((s2540) == IMM(0)) {
return F_Chk_dSB2_dfind(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dSB2_dfind_dif(V *a) { (void)a; return F_Chk_dSB2_dfind_dif(a[0], a[1], a[2], a[3]); }
static V S2542(void) { static V c; return STRC(c, "an import cycle through "); }
static V S2543(void) { static V c; return STRC(c, "one namespace per file ("); }
static V S2544(void) { static V c; return STRC(c, " is both '"); }
static V S2545(void) { static V c; return STRC(c, "' and '"); }
static V S2546(void) { static V c; return STRC(c, "')"); }
static V L2547(V *a) {
return F_Main_dchk_dread(a[5], a[4], a[3], a[2], a[1], a[0], a[6]);
}
static V F_Main_dchk_dseen(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2541 = a6;
if (TAG(s2541) == 1) {
return F_Bool_dpick(F_String_deq(FLD(s2541, 0), F_Main_dchk_dloading()), F_Main_dchk_dfail(F_Chk_derr0(F_String_dappend(S2542(), a2), IMM(0), a4)), F_Bool_dpick(F_String_deq(FLD(s2541, 0), a3), F_IO_dpure(F_CS_dat__end(a5)), F_Main_dchk_dfail(F_Chk_derr0(F_String_dappend(S2543(), F_String_dappend(a2, F_String_dappend(S2544(), F_String_dappend(FLD(s2541, 0), F_String_dappend(S2545(), F_String_dappend(a3, S2546())))))), IMM(0), a4))));
} else if ((s2541) == IMM(0)) {
return F_IO_dbind(F_Main_dread__opt(a2), mk_clo(L2547, 7, 6, (V[]){a5, a4, a3, a2, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dseen(V *a) { (void)a; return F_Main_dchk_dseen(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S2549(void) { static V c; return STRC(c, "no such file: "); }
static V F_Main_dchk_dread(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2548 = a6;
if ((s2548) == IMM(0)) {
return F_Main_dchk_dfail(F_Chk_derr0(F_String_dappend(S2549(), a2), IMM(0), a4));
} else if (TAG(s2548) == 1) {
return F_Main_dchk_dsrc(a0, a1, a2, a3, FLD(s2548, 0), a5);
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dread(V *a) { (void)a; return F_Main_dchk_dread(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Main_dchk_dsrc(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Main_dchk_dhdr(a0, a1, a2, a3, a4, a5, F_Chk_dheader(a4));
}
static V W_Main_dchk_dsrc(V *a) { (void)a; return F_Main_dchk_dsrc(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dheader(V a0) {
top:;
return F_Chk_dheader_dgo(a0, F_String_dsplit(a0, 10u), 0u, IMM(0), IMM(0));
}
static V W_Chk_dheader(V *a) { (void)a; return F_Chk_dheader(a[0]); }
static V F_Chk_dheader_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2550 = a1;
if ((s2550) == IMM(0)) {
return C3(0, F_List_dreverse(a3), a4, IMM(0));
} else if (TAG(s2550) == 1) {
return F_Chk_dheader_dline(a0, FLD(s2550, 0), FLD(s2550, 1), a2, a3, a4, F_Chk_dStr_dtrim(FLD(s2550, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dheader_dgo(V *a) { (void)a; return F_Chk_dheader_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dStr_dtrim(V a0) {
top:;
return F_String_dtrim(a0);
}
static V W_Chk_dStr_dtrim(V *a) { (void)a; return F_Chk_dStr_dtrim(a[0]); }
static V F_String_dtrim(V a0) {
top:;
return F_String_dtrim__end(F_String_dtrim__start(a0));
}
static V W_String_dtrim(V *a) { (void)a; return F_String_dtrim(a[0]); }
static V F_String_dtrim__start(V a0) {
top:;
V s2551 = a0;
if ((s2551) == IMM(0)) {
return IMM(0);
} else if (TAG(s2551) == 1) {
return F_String_dtrim__start_dif(FLD(s2551, 0), FLD(s2551, 1), F_Char_dis__space(FLD(s2551, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_String_dtrim__start(V *a) { (void)a; return F_String_dtrim__start(a[0]); }
static V F_Char_dis__space(V a0) {
top:;
V s2552 = a0;
{
return F_Bool_dor(F_U32_dis__eq(s2552, 32u), F_Bool_dand(F_U32_dis__ge(s2552, 9u), F_U32_dis__le(s2552, 13u)));
}
}
static V W_Char_dis__space(V *a) { (void)a; return F_Char_dis__space(a[0]); }
static V F_String_dtrim__start_dif(V a0, V a1, V a2) {
top:;
V s2553 = a2;
if ((s2553) == IMM(0)) {
return C2(1, a0, a1);
} else if ((s2553) == IMM(1)) {
return F_String_dtrim__start(a1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dtrim__start_dif(V *a) { (void)a; return F_String_dtrim__start_dif(a[0], a[1], a[2]); }
static V F_String_dtrim__end(V a0) {
top:;
return F_String_dreverse(F_String_dtrim__start(F_String_dreverse(a0)));
}
static V W_String_dtrim__end(V *a) { (void)a; return F_String_dtrim__end(a[0]); }
static V S2555(void) { static V c; return STRC(c, "import"); }
static V S2556(void) { static V c; return STRC(c, "import"); }
static V S2557(void) { static V c; return STRC(c, "#"); }
static V F_Chk_dheader_dline(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2554 = F_Bool_dor(F_String_deq(a6, S2555()), F_Bool_dand(F_String_dstarts__with(a6, S2556()), F_Chk_dis__space(F_Chk_dStr_dfirst(F_String_ddrop(a6, 6u)))));
return F_Chk_dheader_dline_dgo(a0, a1, a2, a3, a4, a5, a6, v2554, F_Bool_dor(F_String_dis__empty(a6), F_String_dstarts__with(a6, S2557())));
}
static V W_Chk_dheader_dline(V *a) { (void)a; return F_Chk_dheader_dline(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dheader_dline_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s2558 = a7;
if ((s2558) == IMM(1)) {
return F_Chk_dheader_dimp(a0, a1, a2, a3, a4, a5, a6, F_Chk_dimport_dparse(F_Chk_dStr_duntil__hash(F_Chk_dStr_dwords(F_String_ddrop(a6, 6u)))));
} else if ((s2558) == IMM(0)) {
return F_Chk_dheader_drest(a1, a2, a4, a5, a8);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dheader_dline_dgo(V *a) { (void)a; return F_Chk_dheader_dline_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Chk_dheader_drest(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2559 = a4;
if ((s2559) == IMM(1)) {
return F_Chk_dheader_dgo_drest(a1, C2(1, a0, a2), a3);
} else if ((s2559) == IMM(0)) {
return C3(0, F_List_dappend(F_List_dreverse(C2(1, a0, a2)), a1), a3, IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dheader_drest(V *a) { (void)a; return F_Chk_dheader_drest(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dheader_dgo_drest(V a0, V a1, V a2) {
top:;
return C3(0, F_List_dappend(F_List_dreverse(a1), a0), a2, IMM(0));
}
static V W_Chk_dheader_dgo_drest(V *a) { (void)a; return F_Chk_dheader_dgo_drest(a[0], a[1], a[2]); }
static V S2560(void) { static V c; return STRC(c, ""); }
static V F_Chk_dStr_dwords(V a0) {
top:;
return F_Chk_dStr_dwords_dgo(a0, S2560(), IMM(0));
}
static V W_Chk_dStr_dwords(V *a) { (void)a; return F_Chk_dStr_dwords(a[0]); }
static V F_Chk_dStr_dwords_dgo(V a0, V a1, V a2) {
top:;
V s2561 = a0;
if ((s2561) == IMM(0)) {
return F_List_dreverse(F_Chk_dStr_dwords_dpush(a1, a2));
} else if (TAG(s2561) == 1) {
return F_Chk_dStr_dwords_dchr(FLD(s2561, 1), FLD(s2561, 0), a1, a2, F_Chk_dis__space(FLD(s2561, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dwords_dgo(V *a) { (void)a; return F_Chk_dStr_dwords_dgo(a[0], a[1], a[2]); }
static V F_Chk_dis__space(V a0) {
top:;
return F_Bool_dor(F_Bool_dor(F_U32_dis__eq(a0, 32u), F_U32_dis__eq(a0, 10u)), F_Bool_dor(F_U32_dis__eq(a0, 13u), F_U32_dis__eq(a0, 9u)));
}
static V W_Chk_dis__space(V *a) { (void)a; return F_Chk_dis__space(a[0]); }
static V S2563(void) { static V c; return STRC(c, ""); }
static V F_Chk_dStr_dwords_dchr(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2562 = a4;
if ((s2562) == IMM(1)) {
return F_Chk_dStr_dwords_dgo(a0, S2563(), F_Chk_dStr_dwords_dpush(a2, a3));
} else if ((s2562) == IMM(0)) {
return F_Chk_dStr_dwords_dgo(a0, F_String_dappend(a2, F_Chk_dStr_dchr(a1)), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dwords_dchr(V *a) { (void)a; return F_Chk_dStr_dwords_dchr(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dStr_dwords_dpush(V a0, V a1) {
top:;
return F_Bool_dpick(F_String_dis__empty(a0), a1, C2(1, a0, a1));
}
static V W_Chk_dStr_dwords_dpush(V *a) { (void)a; return F_Chk_dStr_dwords_dpush(a[0], a[1]); }
static V S2565(void) { static V c; return STRC(c, "#"); }
static V F_Chk_dStr_duntil__hash(V a0) {
top:;
V s2564 = a0;
if ((s2564) == IMM(0)) {
return IMM(0);
} else if (TAG(s2564) == 1) {
return F_Bool_dpick(F_String_dstarts__with(FLD(s2564, 0), S2565()), IMM(0), C2(1, FLD(s2564, 0), F_Chk_dStr_duntil__hash(FLD(s2564, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_duntil__hash(V *a) { (void)a; return F_Chk_dStr_duntil__hash(a[0]); }
static V S2567(void) { static V c; return STRC(c, "Base"); }
static V S2568(void) { static V c; return STRC(c, ""); }
static V F_Chk_dimport_dparse(V a0) {
top:;
V s2566 = a0;
if (TAG(s2566) == 1 && TAG(FLD(s2566, 0)) == 1 && (FLD(FLD(s2566, 0), 0)) == 66 && TAG(FLD(FLD(s2566, 0), 1)) == 1 && (FLD(FLD(FLD(s2566, 0), 1), 0)) == 97 && TAG(FLD(FLD(FLD(s2566, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s2566, 0), 1), 1), 0)) == 115 && TAG(FLD(FLD(FLD(FLD(s2566, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s2566, 0), 1), 1), 1), 0)) == 101 && (FLD(FLD(FLD(FLD(FLD(s2566, 0), 1), 1), 1), 1)) == IMM(0) && (FLD(s2566, 1)) == IMM(0)) {
return C1(1, C2(0, S2567(), S2568()));
} else if (TAG(s2566) == 1 && TAG(FLD(s2566, 1)) == 1 && TAG(FLD(FLD(s2566, 1), 0)) == 1 && (FLD(FLD(FLD(s2566, 1), 0), 0)) == 97 && TAG(FLD(FLD(FLD(s2566, 1), 0), 1)) == 1 && (FLD(FLD(FLD(FLD(s2566, 1), 0), 1), 0)) == 115 && (FLD(FLD(FLD(FLD(s2566, 1), 0), 1), 1)) == IMM(0) && TAG(FLD(FLD(s2566, 1), 1)) == 1 && (FLD(FLD(FLD(s2566, 1), 1), 1)) == IMM(0)) {
return F_Bool_dpick(F_Chk_dis__ident(FLD(FLD(FLD(s2566, 1), 1), 0)), C1(1, C2(0, FLD(s2566, 0), FLD(FLD(FLD(s2566, 1), 1), 0))), IMM(0));
} else {
return IMM(0);
}
}
static V W_Chk_dimport_dparse(V *a) { (void)a; return F_Chk_dimport_dparse(a[0]); }
static V F_Chk_dis__ident(V a0) {
top:;
V s2569 = a0;
if ((s2569) == IMM(0)) {
return IMM(0);
} else if (TAG(s2569) == 1) {
return F_Bool_dand(F_Chk_dis__head(FLD(s2569, 0)), F_Chk_dis__ident_drest(FLD(s2569, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dis__ident(V *a) { (void)a; return F_Chk_dis__ident(a[0]); }
static V F_Chk_dis__ident_drest(V a0) {
top:;
V s2570 = a0;
if ((s2570) == IMM(0)) {
return IMM(1);
} else if (TAG(s2570) == 1) {
return F_Bool_dand(F_Bool_dor(F_Chk_dis__head(FLD(s2570, 0)), F_Chk_dis__digit(FLD(s2570, 0))), F_Chk_dis__ident_drest(FLD(s2570, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dis__ident_drest(V *a) { (void)a; return F_Chk_dis__ident_drest(a[0]); }
static V F_Chk_dis__digit(V a0) {
top:;
return F_Bool_dand(F_U32_dis__ge(a0, 48u), F_U32_dis__le(a0, 57u));
}
static V W_Chk_dis__digit(V *a) { (void)a; return F_Chk_dis__digit(a[0]); }
static V F_Chk_dis__head(V a0) {
top:;
return F_Bool_dor(F_Bool_dor(F_Bool_dand(F_U32_dis__ge(a0, 65u), F_U32_dis__le(a0, 90u)), F_Bool_dand(F_U32_dis__ge(a0, 97u), F_U32_dis__le(a0, 122u))), F_U32_dis__eq(a0, 95u));
}
static V W_Chk_dis__head(V *a) { (void)a; return F_Chk_dis__head(a[0]); }
static V S2573(void) { static V c; return STRC(c, "an import ('import Base', or 'import <path> as <Name>')"); }
static V S2574(void) { static V c; return STRC(c, "'"); }
static V S2575(void) { static V c; return STRC(c, "'"); }
static V F_Chk_dheader_dimp(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s2571 = a7;
if ((s2571) == IMM(0)) {
V v2572 = F_U32_dfrom__nat(F_Nat_dadd(a3, F_Chk_dStr_dindex__of(a1, a6, 0u)));
return C3(0, IMM(0), IMM(0), C1(1, F_Chk_derr0(S2573(), C1(1, F_String_dappend(S2574(), F_String_dappend(a6, S2575()))), C3(1, a0, v2572, v2572))));
} else if (TAG(s2571) == 1) {
return F_Chk_dheader_dimp_dgo(a0, a1, a2, a3, a4, a5, FLD(s2571, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dheader_dimp(V *a) { (void)a; return F_Chk_dheader_dimp(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S2579(void) { static V c; return STRC(c, ""); }
static V F_Chk_dheader_dimp_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2576 = a6;
V v2577 = FLD(v2576, 0);
V v2578 = F_U32_dfrom__nat(F_Nat_dadd(a3, F_Chk_dStr_dindex__of(a1, v2577, 0u)));
return F_Chk_dheader_dgo_dnext(a0, a2, F_Nat_dadd(a3, nat_addk(F_String_dlength(a1), 1)), C2(1, S2579(), a4), F_List_dappend(a5, C2(1, C3(0, v2577, FLD(v2576, 1), v2578), IMM(0))));
}
static V W_Chk_dheader_dimp_dgo(V *a) { (void)a; return F_Chk_dheader_dimp_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dheader_dgo_dnext(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Chk_dheader_dgo(a0, a1, a2, a3, a4);
}
static V W_Chk_dheader_dgo_dnext(V *a) { (void)a; return F_Chk_dheader_dgo_dnext(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dStr_dindex__of(V a0, V a1, V a2) {
top:;
V s2580 = a0;
if ((s2580) == IMM(0)) {
return 0u;
} else if (TAG(s2580) == 1) {
return F_Bool_dpick(F_String_dstarts__with(C2(1, FLD(s2580, 0), FLD(s2580, 1)), a1), a2, F_Chk_dStr_dindex__of(FLD(s2580, 1), a1, nat_addk(a2, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dindex__of(V *a) { (void)a; return F_Chk_dStr_dindex__of(a[0], a[1], a[2]); }
static V S2581(void) { static V c; return STRC(c, ""); }
static V S2582(void) { static V c; return STRC(c, ""); }
static V F_Chk_derr0(V a0, V a1, V a2) {
top:;
return CN(0, 7, (V[]){F_Chk_dbook__nil(), IMM(0), C1(1, a0), a1, a2, S2581(), S2582()});
}
static V W_Chk_derr0(V *a) { (void)a; return F_Chk_derr0(a[0], a[1], a[2]); }
static V F_Chk_dStr_dfirst(V a0) {
top:;
V s2583 = a0;
if ((s2583) == IMM(0)) {
return 0u;
} else if (TAG(s2583) == 1) {
return FLD(s2583, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dfirst(V *a) { (void)a; return F_Chk_dStr_dfirst(a[0]); }
static V L2586(V *a) {
return F_Main_dchk_dparse(a[4], a[3], a[2], a[1], a[0], a[5]);
}
static V F_Main_dchk_dhdr(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2584 = a6;
V s2585 = FLD(v2584, 2);
if (TAG(s2585) == 1) {
return F_Main_dchk_dfail(FLD(s2585, 0));
} else if ((s2585) == IMM(0)) {
return F_IO_dbind(F_Main_dchk_dimps(a0, a1, F_Mod_ddir(a2), a3, a4, FLD(v2584, 1), F_CS_dmark(a5, F_Path_dnorm(a2)), IMM(0)), mk_clo(L2586, 6, 5, (V[]){FLD(v2584, 0), a4, a3, a2, a1}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dhdr(V *a) { (void)a; return F_Main_dchk_dhdr(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S2590(void) { static V c; return STRC(c, "\012"); }
static V F_Main_dchk_dparse(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v2587 = a5;
V v2588 = FLD(v2587, 0);
V v2589 = F_Chk_dbook__len(FLD(v2588, 0));
return F_Main_dchk_dparsed(a0, a1, a2, FLD(v2588, 1), v2589, F_Chk_dparse__file(FLD(v2588, 0), a3, F_String_djoin(a4, S2590()), a2, F_Mod_ddir(a1), FLD(v2587, 1)));
}
static V W_Main_dchk_dparse(V *a) { (void)a; return F_Main_dchk_dparse(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dparse__file(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dparse__file_dfin(apply(F_Chk_dP_ddecls(), CN(0, 9, (V[]){CN(0, 5, (V[]){a2, 0u, 1u, IMM(1), 0u}), IMM(0), 0u, 0u, a0, a1, a3, a4, a5})));
}
static V W_Chk_dparse__file(V *a) { (void)a; return F_Chk_dparse__file(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L2592(V *a) {
return F_Chk_dP_dif(F_U32_dis__zero(a[0]), F_Chk_dP_dpure(IMM(0)), F_Chk_dP_ddecl());
}
static V L2591(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L2592, 1, 0, 0));
}
static V F_Chk_dP_ddecls(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2591, 1, 0, 0));
}
static V W_Chk_dP_ddecls(V *a) { (void)a; return F_Chk_dP_ddecls(); }
static V S2594(void) { static V c; return STRC(c, "@"); }
static V S2596(void) { static V c; return STRC(c, "def"); }
static V S2598(void) { static V c; return STRC(c, "type"); }
static V S2600(void) { static V c; return STRC(c, "law"); }
static V L2602(V *a) {
return F_Chk_dP_ddecls();
}
static V L2601(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_ddecl_dgo(a[2], a[1], a[0], a[3]), mk_clo(L2602, 1, 0, 0));
}
static V L2599(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S2600()), mk_clo(L2601, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L2597(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S2598()), mk_clo(L2599, 3, 2, (V[]){a[1], a[0]}));
}
static V L2595(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S2596()), mk_clo(L2597, 2, 1, (V[]){a[0]}));
}
static V L2593(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2594()), mk_clo(L2595, 1, 0, 0));
}
static V F_Chk_dP_ddecl(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dreset__scope(), mk_clo(L2593, 1, 0, 0));
}
static V W_Chk_dP_ddecl(V *a) { (void)a; return F_Chk_dP_ddecl(); }
static V S2604(void) { static V c; return STRC(c, "'def', 'type' or 'law'"); }
static V F_Chk_dP_ddecl_dgo(V a0, V a1, V a2, V a3) {
top:;
V s2603 = a0;
if ((s2603) == IMM(1)) {
return F_Chk_dP_dunsafe();
} else if ((s2603) == IMM(0)) {
return F_Chk_dP_dif(a1, F_Chk_dP_ddef(IMM(0)), F_Chk_dP_dif(a2, F_Chk_dP_dtype(), F_Chk_dP_dif(a3, F_Chk_dP_dlaw(), F_Chk_dP_dfail(S2604()))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_ddecl_dgo(V *a) { (void)a; return F_Chk_dP_ddecl_dgo(a[0], a[1], a[2], a[3]); }
static V S2607(void) { static V c; return STRC(c, ""); }
static V L2606(V *a) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2607(), IMM(0), IMM(0)));
}
static V L2605(V *a) {
return F_Chk_dP_dgo(F_Chk_dP_dfail_dgo(a[0], a[2]), mk_clo(L2606, 2, 1, (V[]){a[1]}));
}
static V F_Chk_dP_dfail(V a1) {
top:;
return mk_clo(L2605, 3, 2, (V[]){a1, 0});
}
static V W_Chk_dP_dfail(V *a) { (void)a; return F_Chk_dP_dfail(a[1]); }
static V L2608(V *a) {
return C1(0, a[0]);
}
static V F_Chk_dP_dthrow(V a1) {
top:;
return mk_clo(L2608, 2, 1, (V[]){a1});
}
static V W_Chk_dP_dthrow(V *a) { (void)a; return F_Chk_dP_dthrow(a[1]); }
static V S2611(void) { static V c; return STRC(c, "end of input"); }
static V S2612(void) { static V c; return STRC(c, "'"); }
static V S2613(void) { static V c; return STRC(c, "'"); }
static V F_Chk_dP_dfail_dgo(V a0, V a1) {
top:;
V v2609 = F_Chk_dCur_dpeek(F_Chk_dPS_dcur(a1));
V v2610 = F_Chk_dCur_dpos(F_Chk_dPS_dcur(a1));
return C1(0, F_Chk_derr0(a0, C1(1, F_Bool_dpick(F_U32_dis__zero(v2609), S2611(), F_String_dappend(S2612(), F_String_dappend(F_Chk_dStr_dchr(v2609), S2613())))), C3(1, F_Chk_dPS_dsrc(a1), v2610, v2610)));
}
static V W_Chk_dP_dfail_dgo(V *a) { (void)a; return F_Chk_dP_dfail_dgo(a[0], a[1]); }
static V F_Chk_dPS_dsrc(V a0) {
top:;
V v2614 = a0;
return FLD(v2614, 5);
}
static V W_Chk_dPS_dsrc(V *a) { (void)a; return F_Chk_dPS_dsrc(a[0]); }
static V F_Chk_dPS_dcur(V a0) {
top:;
V v2615 = a0;
return FLD(v2615, 0);
}
static V W_Chk_dPS_dcur(V *a) { (void)a; return F_Chk_dPS_dcur(a[0]); }
static V F_Chk_dCur_dpos(V a0) {
top:;
V v2616 = a0;
return FLD(v2616, 1);
}
static V W_Chk_dCur_dpos(V *a) { (void)a; return F_Chk_dCur_dpos(a[0]); }
static V F_Chk_dCur_dpeek(V a0) {
top:;
V v2617 = a0;
return F_Chk_dStr_dfirst(FLD(v2617, 0));
}
static V W_Chk_dCur_dpeek(V *a) { (void)a; return F_Chk_dCur_dpeek(a[0]); }
static V F_Chk_dP_dgo(V a2, V a3) {
top:;
V s2618 = a2;
if (TAG(s2618) == 0) {
return C1(0, FLD(s2618, 0));
} else if (TAG(s2618) == 1) {
return F_Chk_dP_dgo_ddone(FLD(s2618, 0), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dgo(V *a) { (void)a; return F_Chk_dP_dgo(a[2], a[3]); }
static V F_Chk_dP_dgo_ddone(V a2, V a3) {
top:;
V v2619 = a2;
return apply(apply(a3, FLD(v2619, 0)), FLD(v2619, 1));
}
static V W_Chk_dP_dgo_ddone(V *a) { (void)a; return F_Chk_dP_dgo_ddone(a[2], a[3]); }
static V S2620(void) { static V c; return STRC(c, "law"); }
static V S2625(void) { static V c; return STRC(c, ":"); }
static V L2631(V *a) {
return F_Chk_dP_dlaw_dfin(a[2], a[1], a[0], a[3]);
}
static V L2630(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L2631, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L2629(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[2]), mk_clo(L2630, 4, 3, (V[]){a[3], a[0], a[1]}));
}
static V L2628(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dblock(), mk_clo(L2629, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L2627(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclauses(IMM(0), 0u), mk_clo(L2628, 3, 2, (V[]){a[0], a[1]}));
}
static V L2626(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L2627, 2, 1, (V[]){a[0]}));
}
static V L2624(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S2625()), mk_clo(L2626, 2, 1, (V[]){a[0]}));
}
static V L2623(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dfresh(a[0]), mk_clo(L2624, 2, 1, (V[]){a[0]}));
}
static V L2622(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dqual(a[0]), mk_clo(L2623, 1, 0, 0));
}
static V L2621(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L2622, 1, 0, 0));
}
static V F_Chk_dP_dlaw(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(S2620()), mk_clo(L2621, 1, 0, 0));
}
static V W_Chk_dP_dlaw(V *a) { (void)a; return F_Chk_dP_dlaw(); }
static V F_Chk_dP_dlaw_dfin(V a0, V a1, V a2, V a3) {
top:;
V v2632 = a1;
V v2633 = FLD(v2632, 0);
return F_Chk_dP_dset__book(F_Chk_dbook__push(F_Chk_dbook__set(a3, a0, CN(0, 7, (V[]){F_Chk_dLC_dfirst__exs(v2633), FLD(v2632, 1), F_Chk_dhigher0(a3, F_Chk_dLC_dbind(v2633, a2)), IMM(0), IMM(0), IMM(0), IMM(0)})), a0));
}
static V W_Chk_dP_dlaw_dfin(V *a) { (void)a; return F_Chk_dP_dlaw_dfin(a[0], a[1], a[2], a[3]); }
static V F_Chk_dLC_dbind(V a0, V a1) {
top:;
V s2634 = a0;
if ((s2634) == IMM(0)) {
return a1;
} else if (TAG(s2634) == 1) {
return F_Chk_dLC_dbind_done(FLD(FLD(s2634, 0), 0), FLD(FLD(s2634, 0), 1), FLD(FLD(s2634, 0), 2), FLD(FLD(s2634, 0), 3), FLD(FLD(s2634, 0), 4), FLD(FLD(s2634, 0), 5), F_Chk_dLC_dbind(FLD(s2634, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dLC_dbind(V *a) { (void)a; return F_Chk_dLC_dbind(a[0], a[1]); }
static V S2636(void) { static V c; return STRC(c, "Exists"); }
static V F_Chk_dLC_dbind_done(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2635 = a0;
if ((s2635) == IMM(1)) {
return CN(11, 6, (V[]){a1, a2, a3, a4, C3(24, IMM(0), a3, a6), a5});
} else if ((s2635) == IMM(0)) {
return C3(13, C3(13, C3(4, S2636(), a5, IMM(0)), a4, a5), CN(12, 5, (V[]){a2, a3, C3(24, IMM(0), a3, a6), a5, IMM(3)}), a5);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dLC_dbind_done(V *a) { (void)a; return F_Chk_dLC_dbind_done(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dhigher0(V a0, V a1) {
top:;
return F_Chk_dhigher(a0, a1, IMM(0));
}
static V W_Chk_dhigher0(V *a) { (void)a; return F_Chk_dhigher0(a[0], a[1]); }
static V F_Chk_dLC_dfirst__exs(V a0) {
top:;
V s2637 = a0;
if ((s2637) == IMM(0)) {
return 0u;
} else if (TAG(s2637) == 1 && (FLD(FLD(s2637, 0), 0)) == IMM(1)) {
return nat_addk(F_Chk_dLC_dfirst__exs(FLD(s2637, 1)), 1);
} else if (TAG(s2637) == 1) {
return 0u;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dLC_dfirst__exs(V *a) { (void)a; return F_Chk_dLC_dfirst__exs(a[0]); }
static V F_Chk_dbook__push(V a0, V a1) {
top:;
V v2638 = a0;
return CN(0, 7, (V[]){FLD(v2638, 0), FLD(v2638, 1), C2(1, a1, FLD(v2638, 2)), FLD(v2638, 3), FLD(v2638, 4), FLD(v2638, 5), FLD(v2638, 6)});
}
static V W_Chk_dbook__push(V *a) { (void)a; return F_Chk_dbook__push(a[0], a[1]); }
static V L2639(V *a) {
return C1(1, C2(0, IMM(0), F_Chk_dPS_dset__book(a[1], a[0])));
}
static V F_Chk_dP_dset__book(V a0) {
top:;
return mk_clo(L2639, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dset__book(V *a) { (void)a; return F_Chk_dP_dset__book(a[0]); }
static V F_Chk_dPS_dset__book(V a0, V a1) {
top:;
V v2640 = a0;
return CN(0, 9, (V[]){FLD(v2640, 0), FLD(v2640, 1), FLD(v2640, 2), FLD(v2640, 3), a1, FLD(v2640, 5), FLD(v2640, 6), FLD(v2640, 7), FLD(v2640, 8)});
}
static V W_Chk_dPS_dset__book(V *a) { (void)a; return F_Chk_dPS_dset__book(a[0], a[1]); }
static V L2641(V *a) {
return C1(1, C2(0, F_Chk_dPS_dbook(a[0]), a[0]));
}
static V F_Chk_dP_dbook(void) {
top:;
return mk_clo(L2641, 1, 0, 0);
}
static V W_Chk_dP_dbook(V *a) { (void)a; return F_Chk_dP_dbook(); }
static V F_Chk_dPS_dbook(V a0) {
top:;
V v2642 = a0;
return FLD(v2642, 4);
}
static V W_Chk_dPS_dbook(V *a) { (void)a; return F_Chk_dPS_dbook(a[0]); }
static V L2643(V *a) {
return F_Chk_dP_dgo(apply(a[1], a[4]), a[0]);
}
static V F_Chk_dP_dbind(V a2, V a3) {
top:;
return mk_clo(L2643, 5, 4, (V[]){a3, a2, 0, 0});
}
static V W_Chk_dP_dbind(V *a) { (void)a; return F_Chk_dP_dbind(a[2], a[3]); }
static V L2644(V *a) {
return F_Chk_dP_dclose_dgo(a[0], a[1]);
}
static V F_Chk_dP_dclose(V a0) {
top:;
return mk_clo(L2644, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dclose(V *a) { (void)a; return F_Chk_dP_dclose(a[0]); }
static V F_Chk_dP_dclose_dgo(V a0, V a1) {
top:;
V v2645 = a1;
return C1(1, C2(0, IMM(0), CN(0, 9, (V[]){FLD(v2645, 0), F_Chk_dSB_ddrop(FLD(v2645, 1), F_Nat_dsub(FLD(v2645, 2), a0)), F_Nat_dmin(FLD(v2645, 2), a0), FLD(v2645, 3), FLD(v2645, 4), FLD(v2645, 5), FLD(v2645, 6), FLD(v2645, 7), FLD(v2645, 8)})));
}
static V W_Chk_dP_dclose_dgo(V *a) { (void)a; return F_Chk_dP_dclose_dgo(a[0], a[1]); }
static V F_Chk_dSB_ddrop(V a0, V a1) {
top:;
V s2646 = a0;
V s2647 = a1;
if ((s2647) == 0) {
return s2646;
} else if (TAG(s2646) == 1 && nat_ge(s2647, 1)) {
{ V t0 = FLD(s2646, 1); V t1 = nat_subk(s2647, 1); a0 = t0; a1 = t1; goto top; }
} else if ((s2646) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dSB_ddrop(V *a) { (void)a; return F_Chk_dSB_ddrop(a[0], a[1]); }
static V L2650(V *a) {
return F_Chk_dP_dflatten(a[0], IMM(0));
}
static V L2649(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody(F_U32_dsub(a[0], 1u)), mk_clo(L2650, 1, 0, 0));
}
static V L2648(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcol(), mk_clo(L2649, 1, 0, 0));
}
static V F_Chk_dP_dblock(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2648, 1, 0, 0));
}
static V W_Chk_dP_dblock(V *a) { (void)a; return F_Chk_dP_dblock(); }
static V F_Chk_dP_dflatten(V a0, V a1) {
top:;
V s2651 = a0;
if (TAG(s2651) == 2) {
return F_Chk_dP_dpure(F_Chk_dflatten_dlams(a1, FLD(s2651, 0)));
} else if (TAG(s2651) == 1) {
return F_Chk_dP_dflatten_dlocal(FLD(s2651, 0), FLD(s2651, 1), FLD(s2651, 2), FLD(s2651, 3), a1);
} else if (TAG(s2651) == 0) {
return F_Chk_dP_dmatch__flatten(FLD(s2651, 0), FLD(s2651, 1), FLD(s2651, 2), a1);
} else if (TAG(s2651) == 3) {
{ V t0 = FLD(s2651, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dflatten(V *a) { (void)a; return F_Chk_dP_dflatten(a[0], a[1]); }
static V S2654(void) { static V c; return STRC(c, "a case (this match has no row to return)"); }
static V F_Chk_dP_dmatch__flatten(V a0, V a1, V a2, V a3) {
top:;
V s2652 = a0;
V s2653 = a1;
if ((s2652) == IMM(0) && TAG(s2653) == 1 && TAG(FLD(s2653, 0)) == 3) {
return F_Chk_dP_dflatten(FLD(FLD(s2653, 0), 1), a3);
} else if ((s2652) == IMM(0) && TAG(s2653) == 1) {
return F_Chk_dP_dflatten(FLD(s2653, 0), a3);
} else if ((s2652) == IMM(0) && (s2653) == IMM(0)) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2654(), IMM(0), a2));
} else if (TAG(s2652) == 1) {
return F_Chk_dP_dmf_dvars(FLD(s2652, 0), FLD(s2652, 1), s2653, a2, a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dmatch__flatten(V *a) { (void)a; return F_Chk_dP_dmatch__flatten(a[0], a[1], a[2], a[3]); }
static V F_Chk_dP_dmf_dvars(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2655 = a4;
if ((s2655) == IMM(0)) {
return F_Chk_dP_dmf_dbad(F_Chk_dTm_dstrip__subs(a0), a3);
} else if (TAG(s2655) == 1) {
return F_Chk_dP_dmf_dcol(a0, a1, a2, a3, FLD(s2655, 0), FLD(s2655, 1), F_Chk_dvars_dfind(C2(1, FLD(s2655, 0), FLD(s2655, 1)), F_Maybe_ddefault(F_Chk_dTm_dvar__i(a0), 4294967295u)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dmf_dvars(V *a) { (void)a; return F_Chk_dP_dmf_dvars(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dTm_dvar__i(V a0) {
top:;
V s2656 = a0;
if (TAG(s2656) == 0) {
return C1(1, FLD(s2656, 1));
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dvar__i(V *a) { (void)a; return F_Chk_dTm_dvar__i(a[0]); }
static V F_Chk_dvars_dfind(V a0, V a1) {
top:;
V s2657 = a0;
if ((s2657) == IMM(0)) {
return IMM(0);
} else if (TAG(s2657) == 1 && TAG(FLD(s2657, 0)) == 0) {
return F_Bool_dpick(F_U32_dis__eq(a1, FLD(FLD(s2657, 0), 1)), C1(1, C4(0, FLD(FLD(s2657, 0), 0), FLD(FLD(s2657, 0), 1), FLD(FLD(s2657, 0), 2), FLD(FLD(s2657, 0), 3))), F_Chk_dvars_dfind(FLD(s2657, 1), a1));
} else if (TAG(s2657) == 1) {
{ V t0 = FLD(s2657, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dvars_dfind(V *a) { (void)a; return F_Chk_dvars_dfind(a[0], a[1]); }
static V F_Chk_dP_dmf_dcol(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2658 = a6;
if (TAG(s2658) == 1) {
return F_Chk_dP_dmf_dcol_dvar(a0, a1, a2, a3, a4, a5, FLD(s2658, 0), F_Chk_drows_dctr(a2), F_Nat_dis__eq(F_List_dlength(a2), 0u));
} else if ((s2658) == IMM(0)) {
return F_Chk_dP_dmf_dskip(a0, a1, a2, a3, a4, a5);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dmf_dcol(V *a) { (void)a; return F_Chk_dP_dmf_dcol(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V L2659(V *a) {
return F_Chk_dP_dpure(F_Chk_dflatten_dlams(C2(1, a[0], IMM(0)), a[1]));
}
static V F_Chk_dP_dmf_dskip(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dmatch__flatten(C2(1, a0, a1), a2, a3, a5), mk_clo(L2659, 2, 1, (V[]){a4}));
}
static V W_Chk_dP_dmf_dskip(V *a) { (void)a; return F_Chk_dP_dmf_dskip(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dflatten_dlams(V a0, V a1) {
top:;
V s2660 = a0;
if ((s2660) == IMM(0)) {
return a1;
} else if (TAG(s2660) == 1 && TAG(FLD(s2660, 0)) == 0) {
return CN(12, 5, (V[]){FLD(FLD(s2660, 0), 0), FLD(FLD(s2660, 0), 1), C3(24, IMM(0), FLD(FLD(s2660, 0), 1), F_Chk_dflatten_dlams(FLD(s2660, 1), a1)), FLD(FLD(s2660, 0), 3), FLD(FLD(s2660, 0), 2)});
} else if (TAG(s2660) == 1) {
{ V t0 = FLD(s2660, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dflatten_dlams(V *a) { (void)a; return F_Chk_dflatten_dlams(a[0], a[1]); }
static V L2661(V *a) {
return C1(1, C2(0, a[0], a[1]));
}
static V F_Chk_dP_dpure(V a1) {
top:;
return mk_clo(L2661, 2, 1, (V[]){a1});
}
static V W_Chk_dP_dpure(V *a) { (void)a; return F_Chk_dP_dpure(a[1]); }
static V F_Chk_drows_dctr(V a0) {
top:;
V s2662 = a0;
if ((s2662) == IMM(0)) {
return IMM(0);
} else if (TAG(s2662) == 1 && TAG(FLD(s2662, 0)) == 3 && TAG(FLD(FLD(s2662, 0), 0)) == 1 && TAG(FLD(FLD(FLD(s2662, 0), 0), 0)) == 1) {
return C1(1, C3(1, FLD(FLD(FLD(FLD(s2662, 0), 0), 0), 0), FLD(FLD(FLD(FLD(s2662, 0), 0), 0), 1), FLD(FLD(FLD(FLD(s2662, 0), 0), 0), 2)));
} else if (TAG(s2662) == 1) {
{ V t0 = FLD(s2662, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_drows_dctr(V *a) { (void)a; return F_Chk_drows_dctr(a[0]); }
static V F_Chk_dP_dmf_dcol_dvar(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s2663 = a7;
V s2664 = a8;
if ((s2663) == IMM(0) && (s2664) == IMM(0)) {
return F_Chk_dP_dmf_dvarcol(a0, a1, a2, a3, a4, a5, a6);
} else {
return F_Chk_dP_dif(F_Chk_dPt_dsame(a6, a4), F_Chk_dP_dmf_dctr(a0, a1, a2, a3, a4, a5, s2663), F_Chk_dP_dmf_dskip(a0, a1, a2, a3, a4, a5));
}
}
static V W_Chk_dP_dmf_dcol_dvar(V *a) { (void)a; return F_Chk_dP_dmf_dcol_dvar(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V L2671(V *a) {
return F_Chk_dP_dpure(C4(17, a[2], a[1], a[3], a[0]));
}
static V L2670(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dmatch__flatten(C2(1, a[7], a[6]), F_Chk_dmf_dothers(a[5], a[4]), a[3], C2(1, a[2], a[1])), mk_clo(L2671, 4, 3, (V[]){a[0], a[8], a[4]}));
}
static V L2669(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dmatch__flatten(F_List_dappend(F_Chk_dpatt__terms(a[8], IMM(0)), a[7]), a[9], a[6], F_List_dappend(a[8], a[5])), mk_clo(L2670, 9, 8, (V[]){a[0], a[5], a[1], a[6], a[2], a[3], a[7], a[4]}));
}
static V L2668(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_dmf_drows(a[8], a[7], a[6], a[9], a[5])), mk_clo(L2669, 10, 9, (V[]){a[0], a[6], a[7], a[8], a[1], a[2], a[3], a[4], a[5]}));
}
static V L2667(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(C3(1, a[7], a[8], F_Chk_dPt_ds(a[6]))), mk_clo(L2668, 10, 9, (V[]){a[0], a[1], a[2], a[3], a[4], a[8], a[6], a[7], a[5]}));
}
static V F_Chk_dP_dmf_dctr(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2665 = a6;
if ((s2665) == IMM(0)) {
return F_Chk_dP_dpure(C1(18, a3));
} else if (TAG(s2665) == 1 && TAG(FLD(s2665, 0)) == 1) {
V v2666 = F_Chk_dpatt__mark(F_Chk_dPt_dvar__q(a4), a2);
return F_Chk_dP_dbind(F_Chk_dP_dmf_dfields(FLD(FLD(s2665, 0), 1), v2666), mk_clo(L2667, 9, 8, (V[]){FLD(FLD(s2665, 0), 2), a0, a5, a3, a1, a2, a4, FLD(FLD(s2665, 0), 0)}));
} else if (TAG(s2665) == 1) {
return F_Chk_dP_dpure(C1(18, a3));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dmf_dctr(V *a) { (void)a; return F_Chk_dP_dmf_dctr(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dmf_dothers(V a0, V a1) {
top:;
V s2672 = a0;
if ((s2672) == IMM(0)) {
return IMM(0);
} else if (TAG(s2672) == 1 && TAG(FLD(s2672, 0)) == 3 && TAG(FLD(FLD(s2672, 0), 0)) == 1 && TAG(FLD(FLD(FLD(s2672, 0), 0), 0)) == 1) {
return F_Chk_dmf_dothers_dif(C2(3, C2(1, C3(1, FLD(FLD(FLD(FLD(s2672, 0), 0), 0), 0), FLD(FLD(FLD(FLD(s2672, 0), 0), 0), 1), FLD(FLD(FLD(FLD(s2672, 0), 0), 0), 2)), FLD(FLD(FLD(s2672, 0), 0), 1)), FLD(FLD(s2672, 0), 1)), F_Chk_dmf_dothers(FLD(s2672, 1), a1), F_String_deq(FLD(FLD(FLD(FLD(s2672, 0), 0), 0), 0), a1));
} else if (TAG(s2672) == 1) {
return C2(1, FLD(s2672, 0), F_Chk_dmf_dothers(FLD(s2672, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dmf_dothers(V *a) { (void)a; return F_Chk_dmf_dothers(a[0], a[1]); }
static V F_Chk_dmf_dothers_dif(V a0, V a1, V a2) {
top:;
V s2673 = a2;
if ((s2673) == IMM(1)) {
return a1;
} else if ((s2673) == IMM(0)) {
return C2(1, a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dmf_dothers_dif(V *a) { (void)a; return F_Chk_dmf_dothers_dif(a[0], a[1], a[2]); }
static V F_Chk_dmf_drows(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2674 = a0;
if ((s2674) == IMM(0)) {
return IMM(0);
} else if (TAG(s2674) == 1 && TAG(FLD(s2674, 0)) == 3 && TAG(FLD(FLD(s2674, 0), 0)) == 1 && TAG(FLD(FLD(FLD(s2674, 0), 0), 0)) == 1) {
return F_Chk_dmf_drows_dctr(FLD(FLD(FLD(FLD(s2674, 0), 0), 0), 0), FLD(FLD(FLD(FLD(s2674, 0), 0), 0), 1), FLD(FLD(FLD(s2674, 0), 0), 1), FLD(FLD(s2674, 0), 1), a1, a2, a3, a4, F_String_deq(FLD(FLD(FLD(FLD(s2674, 0), 0), 0), 0), a1), F_Chk_dmf_drows(FLD(s2674, 1), a1, a2, a3, a4));
} else if (TAG(s2674) == 1 && TAG(FLD(s2674, 0)) == 3 && TAG(FLD(FLD(s2674, 0), 0)) == 1 && TAG(FLD(FLD(FLD(s2674, 0), 0), 0)) == 0) {
return C2(1, C2(3, F_List_dappend(a4, FLD(FLD(FLD(s2674, 0), 0), 1)), F_Chk_dbody__sub(F_Chk_dbody__sub(FLD(FLD(s2674, 0), 1), FLD(FLD(FLD(FLD(s2674, 0), 0), 0), 1), a2), F_Chk_dPt_di(a2), a3)), F_Chk_dmf_drows(FLD(s2674, 1), a1, a2, a3, a4));
} else if (TAG(s2674) == 1) {
{ V t0 = FLD(s2674, 1); V t1 = a1; V t2 = a2; V t3 = a3; V t4 = a4; a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dmf_drows(V *a) { (void)a; return F_Chk_dmf_drows(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dPt_di(V a0) {
top:;
V s2675 = a0;
if (TAG(s2675) == 0) {
return FLD(s2675, 1);
} else if (TAG(s2675) == 1) {
return 0u;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPt_di(V *a) { (void)a; return F_Chk_dPt_di(a[0]); }
static V F_Chk_dbody__sub(V a0, V a1, V a2) {
top:;
V s2676 = a0;
if (TAG(s2676) == 0) {
return C3(0, F_Chk_dbody__sub_dscruts(a1, a2, FLD(s2676, 0)), F_Chk_dbody__sub_drows(FLD(s2676, 1), a1, a2), FLD(s2676, 2));
} else if (TAG(s2676) == 1) {
return C4(1, FLD(s2676, 0), FLD(s2676, 1), F_Chk_dbody__sub_dscruts(a1, a2, FLD(s2676, 2)), F_Chk_dbody__sub(FLD(s2676, 3), a1, a2));
} else if (TAG(s2676) == 2) {
return C2(2, C4(5, a1, a2, FLD(s2676, 0), IMM(0)), FLD(s2676, 1));
} else if (TAG(s2676) == 3) {
return C2(3, FLD(s2676, 0), F_Chk_dbody__sub(FLD(s2676, 1), a1, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dbody__sub(V *a) { (void)a; return F_Chk_dbody__sub(a[0], a[1], a[2]); }
static V F_Chk_dbody__sub_dscruts(V a0, V a1, V a2) {
top:;
V s2677 = a2;
if ((s2677) == IMM(0)) {
return IMM(0);
} else if (TAG(s2677) == 1) {
return C2(1, F_Chk_dbody__sub_dscrut(a0, a1, FLD(s2677, 0)), F_Chk_dbody__sub_dscruts(a0, a1, FLD(s2677, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dbody__sub_dscruts(V *a) { (void)a; return F_Chk_dbody__sub_dscruts(a[0], a[1], a[2]); }
static V F_Chk_dbody__sub_dscrut(V a0, V a1, V a2) {
top:;
V s2678 = a2;
if (TAG(s2678) == 0) {
return F_Bool_dpick(F_U32_dis__eq(a0, FLD(s2678, 1)), F_Chk_dpatt__term(a1, FLD(s2678, 2)), C3(0, FLD(s2678, 0), FLD(s2678, 1), FLD(s2678, 2)));
} else {
return C4(5, a0, a1, s2678, IMM(0));
}
}
static V W_Chk_dbody__sub_dscrut(V *a) { (void)a; return F_Chk_dbody__sub_dscrut(a[0], a[1], a[2]); }
static V F_Chk_dbody__sub_drows(V a0, V a1, V a2) {
top:;
V s2679 = a0;
if ((s2679) == IMM(0)) {
return IMM(0);
} else if (TAG(s2679) == 1) {
return C2(1, F_Chk_dbody__sub(FLD(s2679, 0), a1, a2), F_Chk_dbody__sub_drows(FLD(s2679, 1), a1, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dbody__sub_drows(V *a) { (void)a; return F_Chk_dbody__sub_drows(a[0], a[1], a[2]); }
static V F_Chk_dmf_drows_dctr(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9) {
top:;
V s2680 = a8;
if ((s2680) == IMM(1)) {
return C2(1, C2(3, F_List_dappend(a1, a2), F_Chk_dbody__sub(a3, F_Chk_dPt_di(a5), a6)), a9);
} else if ((s2680) == IMM(0)) {
return a9;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dmf_drows_dctr(V *a) { (void)a; return F_Chk_dmf_drows_dctr(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]); }
static V F_Chk_dPt_ds(V a0) {
top:;
V s2681 = a0;
if (TAG(s2681) == 0) {
return FLD(s2681, 3);
} else if (TAG(s2681) == 1) {
return FLD(s2681, 2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPt_ds(V *a) { (void)a; return F_Chk_dPt_ds(a[0]); }
static V L2683(V *a) {
return F_Chk_dP_dpure(C2(1, C4(0, a[4], a[3], F_Chk_dquant__join(a[2], a[1]), a[0]), a[5]));
}
static V S2686(void) { static V c; return STRC(c, "_"); }
static V L2685(V *a) {
return F_Chk_dP_dpure(C2(1, C4(0, F_String_dappend(S2686(), F_U32_dshow(a[2])), a[2], a[1], F_Chk_dPt_ds(a[0])), a[3]));
}
static V L2684(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dmf_dfields(a[2], a[1]), mk_clo(L2685, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V F_Chk_dP_dmf_dfields(V a0, V a1) {
top:;
V s2682 = a0;
if ((s2682) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s2682) == 1 && TAG(FLD(s2682, 0)) == 0) {
return F_Chk_dP_dbind(F_Chk_dP_dmf_dfields(FLD(s2682, 1), a1), mk_clo(L2683, 6, 5, (V[]){FLD(FLD(s2682, 0), 3), a1, FLD(FLD(s2682, 0), 2), FLD(FLD(s2682, 0), 1), FLD(FLD(s2682, 0), 0)}));
} else if (TAG(s2682) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dfresh__id(), mk_clo(L2684, 4, 3, (V[]){FLD(s2682, 0), a1, FLD(s2682, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dmf_dfields(V *a) { (void)a; return F_Chk_dP_dmf_dfields(a[0], a[1]); }
static V L2687(V *a) {
return F_Chk_dP_dfresh__id_dgo(a[0]);
}
static V F_Chk_dP_dfresh__id(void) {
top:;
return mk_clo(L2687, 1, 0, 0);
}
static V W_Chk_dP_dfresh__id(V *a) { (void)a; return F_Chk_dP_dfresh__id(); }
static V F_Chk_dP_dfresh__id_dgo(V a0) {
top:;
V v2688 = a0;
return C1(1, C2(0, FLD(v2688, 3), CN(0, 9, (V[]){FLD(v2688, 0), FLD(v2688, 1), FLD(v2688, 2), F_U32_dinc(FLD(v2688, 3)), FLD(v2688, 4), FLD(v2688, 5), FLD(v2688, 6), FLD(v2688, 7), FLD(v2688, 8)})));
}
static V W_Chk_dP_dfresh__id_dgo(V *a) { (void)a; return F_Chk_dP_dfresh__id_dgo(a[0]); }
static V F_Chk_dPt_dvar__q(V a0) {
top:;
V s2689 = a0;
if (TAG(s2689) == 0) {
return FLD(s2689, 2);
} else {
return IMM(1);
}
}
static V W_Chk_dPt_dvar__q(V *a) { (void)a; return F_Chk_dPt_dvar__q(a[0]); }
static V F_Chk_dpatt__mark(V a0, V a1) {
top:;
V s2690 = a1;
if ((s2690) == IMM(0)) {
return a0;
} else if (TAG(s2690) == 1 && TAG(FLD(s2690, 0)) == 3 && TAG(FLD(FLD(s2690, 0), 0)) == 1 && TAG(FLD(FLD(FLD(s2690, 0), 0), 0)) == 0) {
{ V t0 = F_Chk_dquant__join(a0, FLD(FLD(FLD(FLD(s2690, 0), 0), 0), 2)); V t1 = FLD(s2690, 1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2690) == 1) {
{ V t0 = a0; V t1 = FLD(s2690, 1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dpatt__mark(V *a) { (void)a; return F_Chk_dpatt__mark(a[0], a[1]); }
static V F_Chk_dPt_dsame(V a0, V a1) {
top:;
return F_U32_dis__eq(F_Chk_dPt_di(a0), F_Chk_dPt_di(a1));
}
static V W_Chk_dPt_dsame(V *a) { (void)a; return F_Chk_dPt_dsame(a[0], a[1]); }
static V F_Chk_dP_dif(V a1, V a2, V a3) {
top:;
V s2691 = a1;
if ((s2691) == IMM(1)) {
return a2;
} else if ((s2691) == IMM(0)) {
return a3;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dif(V *a) { (void)a; return F_Chk_dP_dif(a[1], a[2], a[3]); }
static V L2693(V *a) {
return F_Chk_dP_dmatch__flatten(a[4], a[5], a[3], F_Chk_dvars_dreplace(C2(1, a[2], a[1]), a[0]));
}
static V F_Chk_dP_dmf_dvarcol(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2692 = F_Chk_dPt_dwith__q(a6, F_Chk_dpatt__mark(F_Chk_dPt_dvar__q(a6), a2));
return F_Chk_dP_dbind(F_Chk_dP_dmf_dvarrows(a2, v2692), mk_clo(L2693, 6, 5, (V[]){v2692, a5, a4, a3, a1}));
}
static V W_Chk_dP_dmf_dvarcol(V *a) { (void)a; return F_Chk_dP_dmf_dvarcol(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dvars_dreplace(V a0, V a1) {
top:;
V s2694 = a0;
if ((s2694) == IMM(0)) {
return IMM(0);
} else if (TAG(s2694) == 1) {
return C2(1, F_Bool_dpick(F_Chk_dPt_dsame(FLD(s2694, 0), a1), a1, FLD(s2694, 0)), F_Chk_dvars_dreplace(FLD(s2694, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dvars_dreplace(V *a) { (void)a; return F_Chk_dvars_dreplace(a[0], a[1]); }
static V L2696(V *a) {
return F_Chk_dP_dpure(C2(1, C2(3, a[3], F_Chk_dbody__sub(a[2], a[1], a[0])), a[4]));
}
static V S2697(void) { static V c; return STRC(c, "a variable pattern (this column has no constructor row)"); }
static V F_Chk_dP_dmf_dvarrows(V a0, V a1) {
top:;
V s2695 = a0;
if ((s2695) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s2695) == 1 && TAG(FLD(s2695, 0)) == 3 && TAG(FLD(FLD(s2695, 0), 0)) == 1 && TAG(FLD(FLD(FLD(s2695, 0), 0), 0)) == 0) {
return F_Chk_dP_dbind(F_Chk_dP_dmf_dvarrows(FLD(s2695, 1), a1), mk_clo(L2696, 5, 4, (V[]){a1, FLD(FLD(FLD(FLD(s2695, 0), 0), 0), 1), FLD(FLD(s2695, 0), 1), FLD(FLD(FLD(s2695, 0), 0), 1)}));
} else if (TAG(s2695) == 1 && TAG(FLD(s2695, 0)) == 3 && TAG(FLD(FLD(s2695, 0), 0)) == 1) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2697(), IMM(0), F_Chk_dPt_ds(FLD(FLD(FLD(s2695, 0), 0), 0))));
} else if (TAG(s2695) == 1) {
{ V t0 = FLD(s2695, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dmf_dvarrows(V *a) { (void)a; return F_Chk_dP_dmf_dvarrows(a[0], a[1]); }
static V F_Chk_dPt_dwith__q(V a0, V a1) {
top:;
V s2698 = a0;
if (TAG(s2698) == 0) {
return C4(0, FLD(s2698, 0), FLD(s2698, 1), a1, FLD(s2698, 3));
} else {
return s2698;
}
}
static V W_Chk_dPt_dwith__q(V *a) { (void)a; return F_Chk_dPt_dwith__q(a[0], a[1]); }
static V F_Chk_dTm_dstrip__subs(V a0) {
top:;
V s2699 = a0;
if (TAG(s2699) == 5) {
{ V t0 = FLD(s2699, 2); a0 = t0; goto top; }
} else {
return s2699;
}
}
static V W_Chk_dTm_dstrip__subs(V *a) { (void)a; return F_Chk_dTm_dstrip__subs(a[0]); }
static V S2701(void) { static V c; return STRC(c, "a match on a parameter or field (this name is a def or a consumed binder: give the value its own def)"); }
static V S2702(void) { static V c; return STRC(c, "a match on a parameter or field (this name is a def or a consumed binder: give the value its own def)"); }
static V S2703(void) { static V c; return STRC(c, "an undestructed scrutinee (this value is already a constructor: bind its fields directly; if an outer match destructed it, fold the pattern into the outer case)"); }
static V S2704(void) { static V c; return STRC(c, "an undestructed scrutinee (this value is already a constructor: bind its fields directly; if an outer match destructed it, fold the pattern into the outer case)"); }
static V S2705(void) { static V c; return STRC(c, "a parameter or field scrutinee (a match cannot scrutinize a computed value: give it its own def)"); }
static V F_Chk_dP_dmf_dbad(V a0, V a1) {
top:;
V s2700 = a0;
if (TAG(s2700) == 0) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2701(), IMM(0), FLD(s2700, 2)));
} else if (TAG(s2700) == 3) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2702(), IMM(0), FLD(s2700, 2)));
} else if (TAG(s2700) == 15) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2703(), IMM(0), a1));
} else if (TAG(s2700) == 16) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2704(), IMM(0), a1));
} else {
return F_Chk_dP_dthrow(F_Chk_derr0(S2705(), IMM(0), F_Chk_dSp_dor(F_Chk_dTm_dspan(s2700), a1)));
}
}
static V W_Chk_dP_dmf_dbad(V *a) { (void)a; return F_Chk_dP_dmf_dbad(a[0], a[1]); }
static V F_Chk_dP_dflatten_dlocal(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2706 = a0;
if (TAG(s2706) == 1 && TAG(FLD(s2706, 0)) == 1 && (FLD(s2706, 1)) == IMM(0)) {
return F_Chk_dP_dmatch__flatten(a2, C2(1, C2(3, C2(1, C3(1, FLD(FLD(s2706, 0), 0), FLD(FLD(s2706, 0), 1), FLD(FLD(s2706, 0), 2)), IMM(0)), a3), IMM(0)), F_Chk_dTm_dspan(F_Chk_dLst_dhead(C1(18, IMM(0)), a2)), a4);
} else {
return F_Chk_dP_dflatten_dlet(s2706, a1, a2, a3, a4);
}
}
static V W_Chk_dP_dflatten_dlocal(V *a) { (void)a; return F_Chk_dP_dflatten_dlocal(a[0], a[1], a[2], a[3], a[4]); }
static V S2709(void) { static V c; return STRC(c, "_"); }
static V L2708(V *a) {
return F_Chk_dP_dpure(F_Chk_dflatten_dlams(a[3], CN(6, 6, (V[]){F_Chk_dPt_dks(a[2]), F_Chk_dPt_dis(a[2]), a[1], C3(25, IMM(0), F_Chk_dPt_dis(a[2]), a[4]), F_Chk_dPt_ds(F_Chk_dLst_dhead(C4(0, S2709(), 0u, IMM(1), IMM(0)), a[2])), F_Chk_dPt_dqs(a[2], a[0])})));
}
static V L2707(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dflatten_dstrip(a[3], a[4]), mk_clo(L2708, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V F_Chk_dP_dflatten_dlet(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dflatten(a3, a0), mk_clo(L2707, 5, 4, (V[]){a1, a2, a4, a0}));
}
static V W_Chk_dP_dflatten_dlet(V *a) { (void)a; return F_Chk_dP_dflatten_dlet(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dPt_dqs(V a0, V a1) {
top:;
V s2710 = a0;
if ((s2710) == IMM(0)) {
return IMM(0);
} else if (TAG(s2710) == 1) {
return C2(1, F_Chk_dquant__dem(a1, F_Chk_dPt_dq(FLD(s2710, 0))), F_Chk_dPt_dqs(FLD(s2710, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPt_dqs(V *a) { (void)a; return F_Chk_dPt_dqs(a[0], a[1]); }
static V F_Chk_dPt_dq(V a0) {
top:;
V s2711 = a0;
if (TAG(s2711) == 0) {
return FLD(s2711, 2);
} else if (TAG(s2711) == 1) {
return IMM(1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPt_dq(V *a) { (void)a; return F_Chk_dPt_dq(a[0]); }
static V F_Chk_dPt_dis(V a0) {
top:;
V s2712 = a0;
if ((s2712) == IMM(0)) {
return IMM(0);
} else if (TAG(s2712) == 1) {
return C2(1, F_Chk_dPt_di(FLD(s2712, 0)), F_Chk_dPt_dis(FLD(s2712, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPt_dis(V *a) { (void)a; return F_Chk_dPt_dis(a[0]); }
static V F_Chk_dPt_dks(V a0) {
top:;
V s2713 = a0;
if ((s2713) == IMM(0)) {
return IMM(0);
} else if (TAG(s2713) == 1) {
return C2(1, F_Chk_dPt_dk(FLD(s2713, 0)), F_Chk_dPt_dks(FLD(s2713, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPt_dks(V *a) { (void)a; return F_Chk_dPt_dks(a[0]); }
static V F_Chk_dPt_dk(V a0) {
top:;
V s2714 = a0;
if (TAG(s2714) == 0) {
return FLD(s2714, 0);
} else if (TAG(s2714) == 1) {
return FLD(s2714, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPt_dk(V *a) { (void)a; return F_Chk_dPt_dk(a[0]); }
static V S2717(void) { static V c; return STRC(c, "a parameter or field scrutinee (a match cannot scrutinize a local binder: give it its own def)"); }
static V F_Chk_dP_dflatten_dstrip(V a0, V a1) {
top:;
V s2715 = a0;
V s2716 = a1;
if ((s2715) == IMM(0)) {
return F_Chk_dP_dpure(s2716);
} else if (TAG(s2715) == 1 && TAG(s2716) == 12) {
{ V t0 = FLD(s2715, 1); V t1 = F_Chk_dsyn__body(FLD(s2716, 2)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2715) == 1) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2717(), IMM(0), F_Chk_dPt_ds(FLD(s2715, 0))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dflatten_dstrip(V *a) { (void)a; return F_Chk_dP_dflatten_dstrip(a[0], a[1]); }
static V S2721(void) { static V c; return STRC(c, "match"); }
static V L2722(V *a) {
return F_Chk_dP_dif(a[3], F_Chk_dP_dbody_dmatch(a[2], a[1]), F_Chk_dP_dbody_dlocal(a[2], a[1], a[0]));
}
static V L2720(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dword(S2721()), mk_clo(L2722, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L2719(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcol(), mk_clo(L2720, 3, 2, (V[]){a[1], a[0]}));
}
static V L2718(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L2719, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dbody(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2718, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbody(V *a) { (void)a; return F_Chk_dP_dbody(a[0]); }
static V S2723(void) { static V c; return STRC(c, "-"); }
static V S2730(void) { static V c; return STRC(c, ":"); }
static V S2734(void) { static V c; return STRC(c, "="); }
static V S2737(void) { static V c; return STRC(c, "=="); }
static V L2738(V *a) {
return F_Chk_dP_dbody_dlocal_dgo(a[6], a[5], a[4], a[3], a[2], a[1], F_Bool_dand(a[0], F_Bool_dnot(a[7])));
}
static V L2736(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S2737()), mk_clo(L2738, 8, 7, (V[]){a[0], a[6], a[1], a[2], a[3], a[4], a[5]}));
}
static V L2735(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody_dty__ok(a[6], a[5], a[7]), mk_clo(L2736, 7, 6, (V[]){a[7], a[0], a[1], a[2], a[3], a[4]}));
}
static V L2733(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S2734()), mk_clo(L2735, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L2732(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2733, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[6], a[5]}));
}
static V L2731(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[6], F_Chk_dP_dbody_dty(), F_Chk_dP_dpure(IMM(0))), mk_clo(L2732, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L2729(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Nat_dis__eq(F_List_dlength(a[4]), 1u), F_Chk_dP_dtake(S2730()), F_Chk_dP_dpure(IMM(0))), mk_clo(L2731, 7, 6, (V[]){a[4], a[0], a[1], a[2], a[3], a[5]}));
}
static V L2728(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcur(), mk_clo(L2729, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L2727(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dlocal_dnames(a[4], C2(1, a[3], IMM(0))), mk_clo(L2728, 5, 4, (V[]){a[4], a[0], a[1], a[2]}));
}
static V L2726(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2727, 6, 5, (V[]){a[0], a[1], a[2], a[4], a[3]}));
}
static V L2725(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[3], F_Chk_dP_dbody_derased__name(a[2]), F_Chk_dP_dterm0()), mk_clo(L2726, 5, 4, (V[]){a[0], a[2], a[1], a[4]}));
}
static V L2724(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Bool_dpick(a[3], IMM(0), IMM(1))), mk_clo(L2725, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Chk_dP_dbody_dlocal(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2723()), mk_clo(L2724, 4, 3, (V[]){a2, a0, a1}));
}
static V W_Chk_dP_dbody_dlocal(V *a) { (void)a; return F_Chk_dP_dbody_dlocal(a[0], a[1], a[2]); }
static V F_Chk_dP_dbody_dlocal_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2739 = F_Nat_dis__eq(F_List_dlength(a4), 1u);
V v2740 = F_Bool_dand(F_Bool_dand(F_Maybe_dis__none(a5), F_Chk_dQ_dis__lone(a3)), F_Bool_dand(v2739, F_Bool_dnot(a6)));
return F_Chk_dP_dif(v2740, F_Chk_dP_dbody_dreply(a0, a1, a2, F_Chk_dLst_dhead(C1(18, IMM(0)), a4)), F_Chk_dP_dbody_dlet(a0, a1, a3, a4, a5, IMM(0)));
}
static V W_Chk_dP_dbody_dlocal_dgo(V *a) { (void)a; return F_Chk_dP_dbody_dlocal_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S2744(void) { static V c; return STRC(c, ";"); }
static V L2749(V *a) {
return F_Chk_dP_dpure(C4(1, a[3], a[2], a[1], a[0]));
}
static V L2748(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[3]), mk_clo(L2749, 5, 4, (V[]){a[4], a[0], a[1], a[2]}));
}
static V L2747(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody(a[3]), mk_clo(L2748, 5, 4, (V[]){a[0], a[1], a[4], a[2]}));
}
static V L2746(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody_dbinders(a[4], F_Bool_dor(F_Nat_dis__gt(F_List_dlength(a[4]), 1u), F_Maybe_dis__some(a[3]))), mk_clo(L2747, 5, 4, (V[]){a[0], a[1], a[5], a[2]}));
}
static V L2745(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L2746, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L2743(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2744()), mk_clo(L2745, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L2742(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2743, 6, 5, (V[]){a[4], a[0], a[1], a[2], a[3]}));
}
static V L2741(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody_dvals(a[4], F_List_dlength(a[3])), mk_clo(L2742, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Chk_dP_dbody_dlet(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Chk_dLst_dempty(a5), F_Chk_dP_dbody_dlet_deq(a1, a4), F_Chk_dP_dpure(a5)), mk_clo(L2741, 5, 4, (V[]){a2, a0, a4, a3}));
}
static V W_Chk_dP_dbody_dlet(V *a) { (void)a; return F_Chk_dP_dbody_dlet(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S2751(void) { static V c; return STRC(c, "a name (a parallel or typed let binds names; destructure in its body)"); }
static V L2754(V *a) {
return F_Chk_dP_dpure(C2(1, a[0], a[1]));
}
static V L2753(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody_dbinders(a[1], a[0]), mk_clo(L2754, 2, 1, (V[]){a[2]}));
}
static V L2752(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpatt(a[2]), mk_clo(L2753, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dbody_dbinders(V a0, V a1) {
top:;
V s2750 = a0;
if ((s2750) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s2750) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Bool_dand(a1, F_Bool_dnot(F_Chk_dTm_dis__var(FLD(s2750, 0)))), F_Chk_dP_dthrow(F_Chk_derr0(S2751(), IMM(0), F_Chk_dTm_dspan(FLD(s2750, 0)))), F_Chk_dP_dpure(IMM(0))), mk_clo(L2752, 4, 3, (V[]){a1, FLD(s2750, 1), FLD(s2750, 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dbody_dbinders(V *a) { (void)a; return F_Chk_dP_dbody_dbinders(a[0], a[1]); }
static V L2756(V *a) {
return F_Chk_dP_dpatt_dctr(a[2], a[1], a[0], F_Chk_dbook__ctr(a[3], a[2]));
}
static V F_Chk_dP_dpatt(V a0) {
top:;
V s2755 = a0;
if (TAG(s2755) == 15) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L2756, 4, 3, (V[]){FLD(s2755, 2), FLD(s2755, 1), FLD(s2755, 0)}));
} else if (TAG(s2755) == 16) {
{ V t0 = F_Chk_dlit__full(C2(16, FLD(s2755, 0), FLD(s2755, 1))); a0 = t0; goto top; }
} else {
return F_Chk_dP_dpatt_dvar(s2755, F_Chk_dTm_dis__var(s2755));
}
}
static V W_Chk_dP_dpatt(V *a) { (void)a; return F_Chk_dP_dpatt(a[0]); }
static V F_Chk_dTm_dis__var(V a0) {
top:;
V s2757 = a0;
if (TAG(s2757) == 0) {
return IMM(1);
} else if (TAG(s2757) == 3) {
return IMM(1);
} else if (TAG(s2757) == 2) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__var(V *a) { (void)a; return F_Chk_dTm_dis__var(a[0]); }
static V L2760(V *a) {
return F_Chk_dP_dpatt_dvar_dgo(a[1], F_Maybe_dis__some(F_Chk_dbook__ctr(a[2], a[0])));
}
static V L2759(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L2760, 3, 2, (V[]){a[1], a[0]}));
}
static V F_Chk_dP_dpatt_dvar(V a0, V a1) {
top:;
V s2758 = a1;
if ((s2758) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(F_Chk_dTm_dname(a0)), mk_clo(L2759, 2, 1, (V[]){a0}));
} else if ((s2758) == IMM(0)) {
return F_Chk_dP_dpatt_dother(a0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dpatt_dvar(V *a) { (void)a; return F_Chk_dP_dpatt_dvar(a[0], a[1]); }
static V S2762(void) { static V c; return STRC(c, "a pattern (a binder or a constructor)"); }
static V L2761(V *a) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2762(), C1(1, F_Chk_dterm__show(F_Chk_dterm__lower(a[1], F_Chk_dhigher0(a[1], a[0]), 0u), 0u, IMM(0))), F_Chk_dTm_dspan(a[0])));
}
static V F_Chk_dP_dpatt_dother(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L2761, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dpatt_dother(V *a) { (void)a; return F_Chk_dP_dpatt_dother(a[0]); }
static V S2764(void) { static V c; return STRC(c, "a braced constructor pattern ("); }
static V S2765(void) { static V c; return STRC(c, " is a constructor: write "); }
static V S2766(void) { static V c; return STRC(c, "{}, or rename the binder)"); }
static V F_Chk_dP_dpatt_dvar_dgo(V a0, V a1) {
top:;
V s2763 = a1;
if ((s2763) == IMM(1)) {
return F_Chk_dP_dthrow(F_Chk_derr0(F_String_dappend(S2764(), F_String_dappend(F_Chk_dTm_dname(a0), F_String_dappend(S2765(), F_String_dappend(F_Chk_dTm_dname(a0), S2766())))), IMM(0), F_Chk_dTm_dspan(a0)));
} else if ((s2763) == IMM(0)) {
return F_Chk_dP_dbinder(a0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dpatt_dvar_dgo(V *a) { (void)a; return F_Chk_dP_dpatt_dvar_dgo(a[0], a[1]); }
static V S2768(void) { static V c; return STRC(c, "a lambda binder (one name: k => body)"); }
static V F_Chk_dP_dbinder(V a0) {
top:;
V s2767 = a0;
if (TAG(s2767) == 0) {
return F_Chk_dP_dbinder_dgo(FLD(s2767, 0), IMM(1), FLD(s2767, 2));
} else if (TAG(s2767) == 3) {
return F_Chk_dP_dbinder_dgo(FLD(s2767, 0), IMM(1), FLD(s2767, 2));
} else if (TAG(s2767) == 2) {
return F_Chk_dP_dbinder_dgo(FLD(s2767, 0), IMM(2), FLD(s2767, 1));
} else {
return F_Chk_dP_dfail(S2768());
}
}
static V W_Chk_dP_dbinder(V *a) { (void)a; return F_Chk_dP_dbinder(a[0]); }
static V L2769(V *a) {
return F_Chk_dP_dpure(C4(0, a[2], a[3], a[1], a[0]));
}
static V F_Chk_dP_dbinder_dgo(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dopen(a0), mk_clo(L2769, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dP_dbinder_dgo(V *a) { (void)a; return F_Chk_dP_dbinder_dgo(a[0], a[1], a[2]); }
static V L2770(V *a) {
return F_Chk_dP_dopen_dgo(a[0], a[1]);
}
static V F_Chk_dP_dopen(V a0) {
top:;
return mk_clo(L2770, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dopen(V *a) { (void)a; return F_Chk_dP_dopen(a[0]); }
static V S2772(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dP_dopen_dgo(V a0, V a1) {
top:;
V v2771 = a1;
return C1(1, C2(0, FLD(v2771, 3), F_Chk_dPS_dopened(CN(0, 9, (V[]){FLD(v2771, 0), FLD(v2771, 1), FLD(v2771, 2), F_U32_dinc(FLD(v2771, 3)), FLD(v2771, 4), FLD(v2771, 5), FLD(v2771, 6), FLD(v2771, 7), FLD(v2771, 8)}), a0, FLD(v2771, 3), F_Bool_dnot(F_String_deq(a0, S2772())))));
}
static V W_Chk_dP_dopen_dgo(V *a) { (void)a; return F_Chk_dP_dopen_dgo(a[0], a[1]); }
static V F_Chk_dPS_dopened(V a0, V a1, V a2, V a3) {
top:;
V s2773 = a3;
if ((s2773) == IMM(1)) {
return F_Chk_dPS_dpush(a0, C2(0, a1, a2));
} else if ((s2773) == IMM(0)) {
return a0;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPS_dopened(V *a) { (void)a; return F_Chk_dPS_dopened(a[0], a[1], a[2], a[3]); }
static V F_Chk_dPS_dpush(V a0, V a1) {
top:;
V v2774 = a0;
return CN(0, 9, (V[]){FLD(v2774, 0), C2(1, a1, FLD(v2774, 1)), nat_addk(FLD(v2774, 2), 1), FLD(v2774, 3), FLD(v2774, 4), FLD(v2774, 5), FLD(v2774, 6), FLD(v2774, 7), FLD(v2774, 8)});
}
static V W_Chk_dPS_dpush(V *a) { (void)a; return F_Chk_dPS_dpush(a[0], a[1]); }
static V L2775(V *a) {
return C1(1, C2(0, F_Chk_dPS_dreso(a[1], a[0]), a[1]));
}
static V F_Chk_dP_dreso(V a0) {
top:;
return mk_clo(L2775, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dreso(V *a) { (void)a; return F_Chk_dP_dreso(a[0]); }
static V F_Chk_dPS_dreso(V a0, V a1) {
top:;
V v2776 = F_Chk_dStr_dfirst__dot(a1);
V v2777 = F_Chk_dPS_dreso_dalias(F_Chk_dPS_dqual(a0, a1), F_Chk_dSB2_dfind(F_Chk_dPS_dal(a0), F_String_dtake(a1, v2776)), F_String_ddrop(a1, v2776), F_Nat_dis__lt(v2776, F_String_dlength(a1)));
return F_Bool_dpick(F_Bool_dor(F_Chk_dbook__has(F_Chk_dPS_dbook(a0), v2777), F_Maybe_dis__some(F_Chk_dbook__ctr(F_Chk_dPS_dbook(a0), v2777))), v2777, a1);
}
static V W_Chk_dPS_dreso(V *a) { (void)a; return F_Chk_dPS_dreso(a[0], a[1]); }
static V F_Chk_dPS_dal(V a0) {
top:;
V v2778 = a0;
return FLD(v2778, 8);
}
static V W_Chk_dPS_dal(V *a) { (void)a; return F_Chk_dPS_dal(a[0]); }
static V S2779(void) { static V c; return STRC(c, "."); }
static V F_Chk_dPS_dqual(V a0, V a1) {
top:;
return F_Bool_dpick(F_String_dis__empty(F_Chk_dPS_dns(a0)), a1, F_String_dappend(F_Chk_dPS_dns(a0), F_String_dappend(S2779(), a1)));
}
static V W_Chk_dPS_dqual(V *a) { (void)a; return F_Chk_dPS_dqual(a[0], a[1]); }
static V F_Chk_dPS_dns(V a0) {
top:;
V v2780 = a0;
return FLD(v2780, 6);
}
static V W_Chk_dPS_dns(V *a) { (void)a; return F_Chk_dPS_dns(a[0]); }
static V F_Chk_dPS_dreso_dalias(V a0, V a1, V a2, V a3) {
top:;
V s2781 = a1;
V s2782 = a3;
if (TAG(s2781) == 1 && (s2782) == IMM(1)) {
return F_String_dappend(FLD(s2781, 0), a2);
} else {
return a0;
}
}
static V W_Chk_dPS_dreso_dalias(V *a) { (void)a; return F_Chk_dPS_dreso_dalias(a[0], a[1], a[2], a[3]); }
static V F_Chk_dStr_dfirst__dot(V a0) {
top:;
V s2783 = a0;
if ((s2783) == IMM(0)) {
return 0u;
} else if (TAG(s2783) == 1) {
return F_Bool_dpick(F_U32_dis__eq(FLD(s2783, 0), 46u), 0u, nat_addk(F_Chk_dStr_dfirst__dot(FLD(s2783, 1)), 1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dfirst__dot(V *a) { (void)a; return F_Chk_dStr_dfirst__dot(a[0]); }
static V F_Chk_dlit__full(V a0) {
top:;
V s2784 = a0;
if (TAG(s2784) == 16 && TAG(FLD(s2784, 0)) == 1) {
return F_Chk_dlit__chain(F_Chk_dStr_dcodes(FLD(FLD(s2784, 0), 0)), FLD(s2784, 1));
} else if (TAG(s2784) == 16 && TAG(FLD(s2784, 0)) == 0) {
return F_Chk_dnat__full(FLD(FLD(s2784, 0), 0), FLD(s2784, 1));
} else {
return s2784;
}
}
static V W_Chk_dlit__full(V *a) { (void)a; return F_Chk_dlit__full(a[0]); }
static V S2786(void) { static V c; return STRC(c, "Zero"); }
static V S2787(void) { static V c; return STRC(c, "Succ"); }
static V F_Chk_dnat__full(V a0, V a1) {
top:;
V s2785 = a0;
if ((s2785) == 0) {
return C3(15, S2786(), IMM(0), a1);
} else if (nat_ge(s2785, 1)) {
return C3(15, S2787(), C2(1, F_Chk_dnat__full(nat_subk(s2785, 1), a1), IMM(0)), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dnat__full(V *a) { (void)a; return F_Chk_dnat__full(a[0], a[1]); }
static V F_Chk_dStr_dcodes(V a0) {
top:;
V s2788 = a0;
if ((s2788) == IMM(0)) {
return IMM(0);
} else if (TAG(s2788) == 1) {
return C2(1, FLD(s2788, 0), F_Chk_dStr_dcodes(FLD(s2788, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dcodes(V *a) { (void)a; return F_Chk_dStr_dcodes(a[0]); }
static V S2790(void) { static V c; return STRC(c, "SNil"); }
static V S2791(void) { static V c; return STRC(c, "SCon"); }
static V F_Chk_dlit__chain(V a0, V a1) {
top:;
V s2789 = a0;
if ((s2789) == IMM(0)) {
return C3(15, S2790(), IMM(0), a1);
} else if (TAG(s2789) == 1) {
return C3(15, S2791(), C2(1, F_Chk_dchr__term(FLD(s2789, 0), a1), C2(1, F_Chk_dlit__chain(FLD(s2789, 1), a1), IMM(0))), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlit__chain(V *a) { (void)a; return F_Chk_dlit__chain(a[0], a[1]); }
static V S2793(void) { static V c; return STRC(c, "a declared constructor (unknown: "); }
static V S2794(void) { static V c; return STRC(c, ")"); }
static V F_Chk_dP_dpatt_dctr(V a0, V a1, V a2, V a3) {
top:;
V s2792 = a3;
if ((s2792) == IMM(0)) {
return F_Chk_dP_dthrow(F_Chk_derr0(F_String_dappend(S2793(), F_String_dappend(a0, S2794())), IMM(0), a2));
} else if (TAG(s2792) == 1) {
return F_Chk_dP_dpatt_dctr_dn(a0, a1, a2, FLD(FLD(s2792, 0), 1), F_Nat_dis__eq(FLD(FLD(s2792, 0), 1), F_List_dlength(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dpatt_dctr(V *a) { (void)a; return F_Chk_dP_dpatt_dctr(a[0], a[1], a[2], a[3]); }
static V S2796(void) { static V c; return STRC(c, "a "); }
static V S2797(void) { static V c; return STRC(c, " pattern with "); }
static V S2798(void) { static V c; return STRC(c, " field"); }
static V S2799(void) { static V c; return STRC(c, " fields"); }
static V L2800(V *a) {
return F_Chk_dP_dpure(C3(1, a[1], a[2], a[0]));
}
static V F_Chk_dP_dpatt_dctr_dn(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2795 = a4;
if ((s2795) == IMM(0)) {
return F_Chk_dP_dthrow(F_Chk_derr0(F_String_dappend(S2796(), F_String_dappend(a0, F_String_dappend(S2797(), F_String_dappend(F_Nat_dshow(a3), F_Bool_dpick(F_Nat_dis__eq(a3, 1u), S2798(), S2799()))))), IMM(0), a2));
} else if ((s2795) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dpatts(a1), mk_clo(L2800, 3, 2, (V[]){a2, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dpatt_dctr_dn(V *a) { (void)a; return F_Chk_dP_dpatt_dctr_dn(a[0], a[1], a[2], a[3], a[4]); }
static V L2803(V *a) {
return F_Chk_dP_dpure(C2(1, a[0], a[1]));
}
static V L2802(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpatts(a[0]), mk_clo(L2803, 2, 1, (V[]){a[1]}));
}
static V F_Chk_dP_dpatts(V a0) {
top:;
V s2801 = a0;
if ((s2801) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s2801) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dpatt(FLD(s2801, 0)), mk_clo(L2802, 2, 1, (V[]){FLD(s2801, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dpatts(V *a) { (void)a; return F_Chk_dP_dpatts(a[0]); }
static V L2804(V *a) {
return C1(1, C2(0, F_Chk_dPS_dstn(a[0]), a[0]));
}
static V F_Chk_dP_dstn(void) {
top:;
return mk_clo(L2804, 1, 0, 0);
}
static V W_Chk_dP_dstn(V *a) { (void)a; return F_Chk_dP_dstn(); }
static V F_Chk_dPS_dstn(V a0) {
top:;
V v2805 = a0;
return FLD(v2805, 2);
}
static V W_Chk_dPS_dstn(V *a) { (void)a; return F_Chk_dPS_dstn(a[0]); }
static V L2806(V *a) {
return F_Chk_dP_dtake_dif(a[0], a[1]);
}
static V F_Chk_dP_dtake(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dat(a0), mk_clo(L2806, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dtake(V *a) { (void)a; return F_Chk_dP_dtake(a[0]); }
static V L2808(V *a) {
return C1(1, C2(0, IMM(1), F_Chk_dPS_dset__cur(a[1], F_Chk_dCur_dsteps(F_Chk_dPS_dcur(a[1]), F_String_dlength(a[0])))));
}
static V F_Chk_dP_dtake_dif(V a0, V a1) {
top:;
V s2807 = a1;
if ((s2807) == IMM(1)) {
return mk_clo(L2808, 2, 1, (V[]){a0});
} else if ((s2807) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dtake_dif(V *a) { (void)a; return F_Chk_dP_dtake_dif(a[0], a[1]); }
static V F_Chk_dCur_dsteps(V a0, V a1) {
top:;
V s2809 = a1;
if ((s2809) == 0) {
return a0;
} else if (nat_ge(s2809, 1)) {
{ V t0 = F_Chk_dCur_dstep(a0); V t1 = nat_subk(s2809, 1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCur_dsteps(V *a) { (void)a; return F_Chk_dCur_dsteps(a[0], a[1]); }
static V F_Chk_dCur_dstep(V a0) {
top:;
V v2810 = a0;
return F_Chk_dCur_dstep_dgo(FLD(v2810, 0), FLD(v2810, 1), FLD(v2810, 2), FLD(v2810, 3));
}
static V W_Chk_dCur_dstep(V *a) { (void)a; return F_Chk_dCur_dstep(a[0]); }
static V F_Chk_dCur_dstep_dgo(V a0, V a1, V a2, V a3) {
top:;
V s2811 = a0;
if ((s2811) == IMM(0)) {
return CN(0, 5, (V[]){IMM(0), a1, a2, a3, 0u});
} else if (TAG(s2811) == 1) {
return CN(0, 5, (V[]){FLD(s2811, 1), F_U32_dinc(a1), F_Bool_dpick(F_U32_dis__eq(FLD(s2811, 0), 10u), 1u, F_U32_dinc(a2)), F_Bool_dpick(F_U32_dis__eq(FLD(s2811, 0), 10u), IMM(1), F_Bool_dpick(F_Bool_dor(F_U32_dis__eq(FLD(s2811, 0), 32u), F_Bool_dor(F_U32_dis__eq(FLD(s2811, 0), 13u), F_U32_dis__eq(FLD(s2811, 0), 9u))), a3, IMM(0))), FLD(s2811, 0)});
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCur_dstep_dgo(V *a) { (void)a; return F_Chk_dCur_dstep_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dPS_dset__cur(V a0, V a1) {
top:;
V v2812 = a0;
return CN(0, 9, (V[]){a1, FLD(v2812, 1), FLD(v2812, 2), FLD(v2812, 3), FLD(v2812, 4), FLD(v2812, 5), FLD(v2812, 6), FLD(v2812, 7), FLD(v2812, 8)});
}
static V W_Chk_dPS_dset__cur(V *a) { (void)a; return F_Chk_dPS_dset__cur(a[0], a[1]); }
static V L2813(V *a) {
return C1(1, C2(0, F_Chk_dStr_dprefix(F_Chk_dCur_drest(F_Chk_dPS_dcur(a[1])), a[0]), a[1]));
}
static V F_Chk_dP_dat(V a0) {
top:;
return mk_clo(L2813, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dat(V *a) { (void)a; return F_Chk_dP_dat(a[0]); }
static V F_Chk_dCur_drest(V a0) {
top:;
V v2814 = a0;
return FLD(v2814, 0);
}
static V W_Chk_dCur_drest(V *a) { (void)a; return F_Chk_dCur_drest(a[0]); }
static V F_Chk_dStr_dprefix(V a0, V a1) {
top:;
return F_String_dstarts__with(a0, a1);
}
static V W_Chk_dStr_dprefix(V *a) { (void)a; return F_Chk_dStr_dprefix(a[0], a[1]); }
static V L2815(V *a) {
return C1(1, C2(0, IMM(0), F_Chk_dPS_dset__cur(a[0], F_Chk_dCur_dskip(F_Chk_dPS_dcur(a[0])))));
}
static V F_Chk_dP_dskip(void) {
top:;
return mk_clo(L2815, 1, 0, 0);
}
static V W_Chk_dP_dskip(V *a) { (void)a; return F_Chk_dP_dskip(); }
static V F_Chk_dCur_dskip(V a0) {
top:;
return F_Chk_dCur_dskip_dgo(F_Chk_dCur_dpeek(a0), a0);
}
static V W_Chk_dCur_dskip(V *a) { (void)a; return F_Chk_dCur_dskip(a[0]); }
static V F_Chk_dCur_dskip_dgo(V a0, V a1) {
top:;
return F_Chk_dCur_dskip_dc(a1, F_Bool_dpick(F_Chk_dis__space(a0), 1u, F_Bool_dpick(F_U32_dis__eq(a0, 35u), 2u, 0u)));
}
static V W_Chk_dCur_dskip_dgo(V *a) { (void)a; return F_Chk_dCur_dskip_dgo(a[0], a[1]); }
static V F_Chk_dCur_dskip_dc(V a0, V a1) {
top:;
V s2816 = a1;
if ((s2816) == 0) {
return a0;
} else if ((s2816) == 1) {
return F_Chk_dCur_dskip(F_Chk_dCur_dstep(a0));
} else if (nat_ge(s2816, 2)) {
return F_Chk_dCur_dskip(F_Chk_dCur_dline(a0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCur_dskip_dc(V *a) { (void)a; return F_Chk_dCur_dskip_dc(a[0], a[1]); }
static V F_Chk_dCur_dline(V a0) {
top:;
return F_Chk_dCur_dline_dgo(F_Chk_dCur_dpeek(a0), a0);
}
static V W_Chk_dCur_dline(V *a) { (void)a; return F_Chk_dCur_dline(a[0]); }
static V F_Chk_dCur_dline_dgo(V a0, V a1) {
top:;
return F_Chk_dCur_dline_dc(a1, F_Bool_dor(F_U32_dis__eq(a0, 10u), F_U32_dis__zero(a0)));
}
static V W_Chk_dCur_dline_dgo(V *a) { (void)a; return F_Chk_dCur_dline_dgo(a[0], a[1]); }
static V F_Chk_dCur_dline_dc(V a0, V a1) {
top:;
V s2817 = a1;
if ((s2817) == IMM(1)) {
return a0;
} else if ((s2817) == IMM(0)) {
return F_Chk_dCur_dline(F_Chk_dCur_dstep(a0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCur_dline_dc(V *a) { (void)a; return F_Chk_dCur_dline_dc(a[0], a[1]); }
static V F_Chk_dP_dbody_dvals(V a0, V a1) {
top:;
return F_Chk_dP_dif(F_Nat_dis__ge(F_List_dlength(a0), a1), F_Chk_dP_dpure(a0), F_Chk_dP_dbody_dvals_dmore(a0, a1));
}
static V W_Chk_dP_dbody_dvals(V *a) { (void)a; return F_Chk_dP_dbody_dvals(a[0], a[1]); }
static V L2818(V *a) {
return F_Chk_dP_dbody_dvals(F_List_dappend(a[1], C2(1, a[2], IMM(0))), a[0]);
}
static V F_Chk_dP_dbody_dvals_dmore(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L2818, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dbody_dvals_dmore(V *a) { (void)a; return F_Chk_dP_dbody_dvals_dmore(a[0], a[1]); }
static V F_Chk_dP_dterm0(void) {
top:;
return F_Chk_dP_dterm(0u);
}
static V W_Chk_dP_dterm0(V *a) { (void)a; return F_Chk_dP_dterm0(); }
static V L2822(V *a) {
return F_Chk_dP_dops(F_Chk_dTm_dspanned(a[1], a[2]), a[0]);
}
static V L2821(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L2822, 3, 2, (V[]){a[0], a[2]}));
}
static V L2820(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbase(a[1]), mk_clo(L2821, 3, 2, (V[]){a[0], a[1]}));
}
static V L2819(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L2820, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dterm(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2819, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dterm(V *a) { (void)a; return F_Chk_dP_dterm(a[0]); }
static V F_Chk_dTm_dspanned(V a0, V a1) {
top:;
V s2823 = a0;
if (TAG(s2823) == 6 && (FLD(s2823, 4)) == IMM(0)) {
return CN(6, 6, (V[]){FLD(s2823, 0), FLD(s2823, 1), FLD(s2823, 2), FLD(s2823, 3), a1, FLD(s2823, 5)});
} else if (TAG(s2823) == 10 && (FLD(s2823, 2)) == IMM(0)) {
return C3(10, FLD(s2823, 0), FLD(s2823, 1), a1);
} else if (TAG(s2823) == 11 && (FLD(s2823, 5)) == IMM(0)) {
return CN(11, 6, (V[]){FLD(s2823, 0), FLD(s2823, 1), FLD(s2823, 2), FLD(s2823, 3), FLD(s2823, 4), a1});
} else if (TAG(s2823) == 12 && (FLD(s2823, 3)) == IMM(0)) {
return CN(12, 5, (V[]){FLD(s2823, 0), FLD(s2823, 1), FLD(s2823, 2), a1, FLD(s2823, 4)});
} else if (TAG(s2823) == 17 && (FLD(s2823, 3)) == IMM(0)) {
return C4(17, FLD(s2823, 0), FLD(s2823, 1), FLD(s2823, 2), a1);
} else if (TAG(s2823) == 18 && (FLD(s2823, 0)) == IMM(0)) {
return C1(18, a1);
} else if (TAG(s2823) == 19 && (FLD(s2823, 3)) == IMM(0)) {
return C4(19, FLD(s2823, 0), FLD(s2823, 1), FLD(s2823, 2), a1);
} else if (TAG(s2823) == 21 && (FLD(s2823, 3)) == IMM(0)) {
return C4(21, FLD(s2823, 0), FLD(s2823, 1), FLD(s2823, 2), a1);
} else if (TAG(s2823) == 23 && (FLD(s2823, 2)) == IMM(0)) {
return C3(23, FLD(s2823, 0), FLD(s2823, 1), a1);
} else if (TAG(s2823) == 2 && (FLD(s2823, 1)) == IMM(0)) {
return C2(2, FLD(s2823, 0), a1);
} else if (TAG(s2823) == 3 && (FLD(s2823, 2)) == IMM(0)) {
return C4(3, FLD(s2823, 0), FLD(s2823, 1), a1, FLD(s2823, 3));
} else if (TAG(s2823) == 5 && (FLD(s2823, 3)) == IMM(0)) {
return C4(5, FLD(s2823, 0), FLD(s2823, 1), FLD(s2823, 2), a1);
} else {
return F_Chk_dTm_drespan(s2823, a1);
}
}
static V W_Chk_dTm_dspanned(V *a) { (void)a; return F_Chk_dTm_dspanned(a[0], a[1]); }
static V S2829(void) { static V c; return STRC(c, "("); }
static V S2830(void) { static V c; return STRC(c, "!("); }
static V S2832(void) { static V c; return STRC(c, "["); }
static V S2833(void) { static V c; return STRC(c, "("); }
static V S2834(void) { static V c; return STRC(c, "=>"); }
static V S2835(void) { static V c; return STRC(c, "->"); }
static V S2836(void) { static V c; return STRC(c, "<&>"); }
static V L2827(V *a) {
V v2828 = F_Bool_dor(F_Chk_dStr_dprefix(a[3], S2829()), F_Chk_dStr_dprefix(a[3], S2830()));
V v2831 = F_Chk_dStr_dprefix(a[3], S2832());
return F_Chk_dP_dops_dgo(a[2], a[1], a[3], a[4], F_Bool_dpick(F_Bool_dand(a[0], F_Bool_dor(F_Chk_dStr_dprefix(a[3], S2833()), v2831)), 0u, F_Bool_dpick(v2828, 1u, F_Bool_dpick(v2831, 2u, F_Bool_dpick(F_Chk_dops_dlt(a[3], a[1], a[4]), 3u, F_Bool_dpick(F_Bool_dand(F_U32_dis__zero(a[1]), F_Chk_dStr_dprefix(a[3], S2834())), 4u, F_Bool_dpick(F_Bool_dand(F_U32_dis__zero(a[1]), F_Chk_dStr_dprefix(a[3], S2835())), 5u, F_Bool_dpick(F_Bool_dand(F_U32_dis__le(a[1], 5u), F_Chk_dStr_dprefix(a[3], S2836())), 6u, 7u))))))));
}
static V L2826(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dprev(), mk_clo(L2827, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L2825(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek__rest(), mk_clo(L2826, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L2824(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dnl(), mk_clo(L2825, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dops(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2824, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dops(V *a) { (void)a; return F_Chk_dP_dops(a[0], a[1]); }
static V S2838(void) { static V c; return STRC(c, "<"); }
static V S2839(void) { static V c; return STRC(c, "<&>"); }
static V F_Chk_dops_dlt(V a0, V a1, V a2) {
top:;
V v2837 = F_Chk_dStr_dsecond(a0);
return F_Bool_dand(F_Bool_dand(F_Chk_dStr_dprefix(a0, S2838()), F_Bool_dnot(F_Bool_dor(F_Bool_dor(F_U32_dis__eq(v2837, 45u), F_U32_dis__eq(v2837, 61u)), F_Bool_dor(F_U32_dis__eq(v2837, 60u), F_U32_dis__eq(v2837, 62u))))), F_Bool_dand(F_Bool_dnot(F_Chk_dStr_dprefix(a0, S2839())), F_Bool_dor(F_U32_dis__le(a1, 4u), F_Bool_dnot(F_Bool_dor(F_Chk_dis__space(a2), F_U32_dis__zero(a2))))));
}
static V W_Chk_dops_dlt(V *a) { (void)a; return F_Chk_dops_dlt(a[0], a[1], a[2]); }
static V F_Chk_dStr_dsecond(V a0) {
top:;
V s2840 = a0;
if (TAG(s2840) == 1 && TAG(FLD(s2840, 1)) == 1) {
return FLD(FLD(s2840, 1), 0);
} else {
return 0u;
}
}
static V W_Chk_dStr_dsecond(V *a) { (void)a; return F_Chk_dStr_dsecond(a[0]); }
static V S2842(void) { static V c; return STRC(c, "<-"); }
static V F_Chk_dP_dops_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2841 = a4;
if ((s2841) == 0) {
return F_Chk_dP_dpure(a0);
} else if ((s2841) == 1) {
return F_Chk_dP_dcall(a0, a1);
} else if ((s2841) == 2) {
return F_Chk_dP_dindex(a0, a1);
} else if ((s2841) == 3) {
return F_Chk_dP_dlt(a0, a1);
} else if ((s2841) == 4) {
return F_Chk_dP_dlam(a0, a1);
} else if ((s2841) == 5) {
return F_Chk_dP_darrow(a0, a1);
} else if ((s2841) == 6) {
return F_Chk_dP_dminq(a0, a1);
} else if (nat_ge(s2841, 7)) {
return F_Chk_dP_dinfix(a0, a1, F_Chk_dop_dfind(F_Chk_dOPS(), a2, a3), F_Chk_dStr_dprefix(a2, S2842()));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dops_dgo(V *a) { (void)a; return F_Chk_dP_dops_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V S2843(void) { static V c; return STRC(c, ".|."); }
static V S2844(void) { static V c; return STRC(c, ".or"); }
static V S2845(void) { static V c; return STRC(c, ".^."); }
static V S2846(void) { static V c; return STRC(c, ".xor"); }
static V S2847(void) { static V c; return STRC(c, ".&."); }
static V S2848(void) { static V c; return STRC(c, ".and"); }
static V S2849(void) { static V c; return STRC(c, "||"); }
static V S2850(void) { static V c; return STRC(c, "Bool.or"); }
static V S2851(void) { static V c; return STRC(c, "&&"); }
static V S2852(void) { static V c; return STRC(c, "Bool.and"); }
static V S2853(void) { static V c; return STRC(c, "<="); }
static V S2854(void) { static V c; return STRC(c, ".is_le"); }
static V S2855(void) { static V c; return STRC(c, ">="); }
static V S2856(void) { static V c; return STRC(c, ".is_ge"); }
static V S2857(void) { static V c; return STRC(c, "<>"); }
static V S2858(void) { static V c; return STRC(c, ""); }
static V S2859(void) { static V c; return STRC(c, "++"); }
static V S2860(void) { static V c; return STRC(c, "String.append"); }
static V S2861(void) { static V c; return STRC(c, "<<"); }
static V S2862(void) { static V c; return STRC(c, ".shln"); }
static V S2863(void) { static V c; return STRC(c, ">>"); }
static V S2864(void) { static V c; return STRC(c, ".shrn"); }
static V S2865(void) { static V c; return STRC(c, "&"); }
static V S2866(void) { static V c; return STRC(c, ""); }
static V S2867(void) { static V c; return STRC(c, "|"); }
static V S2868(void) { static V c; return STRC(c, ""); }
static V S2869(void) { static V c; return STRC(c, ">"); }
static V S2870(void) { static V c; return STRC(c, ".is_gt"); }
static V S2871(void) { static V c; return STRC(c, "+"); }
static V S2872(void) { static V c; return STRC(c, ".add"); }
static V S2873(void) { static V c; return STRC(c, "-"); }
static V S2874(void) { static V c; return STRC(c, ".sub"); }
static V S2875(void) { static V c; return STRC(c, "*"); }
static V S2876(void) { static V c; return STRC(c, ".mul"); }
static V S2877(void) { static V c; return STRC(c, "/"); }
static V S2878(void) { static V c; return STRC(c, ".div"); }
static V S2879(void) { static V c; return STRC(c, "%"); }
static V S2880(void) { static V c; return STRC(c, ".mod"); }
static V F_Chk_dOPS(void) {
top:;
return C2(1, C4(0, S2843(), 6u, IMM(0), S2844()), C2(1, C4(0, S2845(), 7u, IMM(0), S2846()), C2(1, C4(0, S2847(), 8u, IMM(0), S2848()), C2(1, C4(0, S2849(), 2u, IMM(0), S2850()), C2(1, C4(0, S2851(), 3u, IMM(0), S2852()), C2(1, C4(0, S2853(), 4u, IMM(0), S2854()), C2(1, C4(0, S2855(), 4u, IMM(0), S2856()), C2(1, C4(0, S2857(), 5u, IMM(1), S2858()), C2(1, C4(0, S2859(), 5u, IMM(1), S2860()), C2(1, C4(0, S2861(), 9u, IMM(0), S2862()), C2(1, C4(0, S2863(), 9u, IMM(0), S2864()), C2(1, C4(0, S2865(), 1u, IMM(1), S2866()), C2(1, C4(0, S2867(), 1u, IMM(1), S2868()), C2(1, C4(0, S2869(), 4u, IMM(0), S2870()), C2(1, C4(0, S2871(), 10u, IMM(0), S2872()), C2(1, C4(0, S2873(), 10u, IMM(0), S2874()), C2(1, C4(0, S2875(), 11u, IMM(0), S2876()), C2(1, C4(0, S2877(), 11u, IMM(0), S2878()), C2(1, C4(0, S2879(), 11u, IMM(0), S2880()), IMM(0))))))))))))))))))));
}
static V W_Chk_dOPS(V *a) { (void)a; return F_Chk_dOPS(); }
static V F_Chk_dop_dfind(V a0, V a1, V a2) {
top:;
V s2881 = a0;
if ((s2881) == IMM(0)) {
return IMM(0);
} else if (TAG(s2881) == 1) {
return F_Chk_dop_dfind_dif(FLD(s2881, 1), a1, a2, C4(0, FLD(FLD(s2881, 0), 0), FLD(FLD(s2881, 0), 1), FLD(FLD(s2881, 0), 2), FLD(FLD(s2881, 0), 3)), F_Chk_dop_dok(FLD(FLD(s2881, 0), 0), a1, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dop_dfind(V *a) { (void)a; return F_Chk_dop_dfind(a[0], a[1], a[2]); }
static V S2884(void) { static V c; return STRC(c, "-"); }
static V S2885(void) { static V c; return STRC(c, "+"); }
static V S2886(void) { static V c; return STRC(c, "%"); }
static V F_Chk_dop_dok(V a0, V a1, V a2) {
top:;
V v2882 = F_Chk_dStr_dfirst(F_String_ddrop(a1, F_String_dlength(a0)));
V v2883 = F_Chk_dStr_dfirst(a0);
return F_Bool_dand(F_Chk_dStr_dprefix(a1, a0), F_Bool_dand(F_Bool_dnot(F_Bool_dand(F_Bool_dor(F_String_deq(a0, S2884()), F_String_deq(a0, S2885())), F_Bool_dor(F_U32_dis__eq(v2882, 62u), F_Chk_dis__head(v2882)))), F_Bool_dand(F_Bool_dnot(F_Bool_dand(F_U32_dis__eq(v2883, 62u), F_Bool_dnot(F_Bool_dor(F_Chk_dis__space(a2), F_U32_dis__zero(a2))))), F_Bool_dnot(F_Bool_dand(F_String_deq(a0, S2886()), F_Bool_dnot(F_Chk_dis__space(v2882)))))));
}
static V W_Chk_dop_dok(V *a) { (void)a; return F_Chk_dop_dok(a[0], a[1], a[2]); }
static V F_Chk_dop_dfind_dif(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2887 = a4;
if ((s2887) == IMM(1)) {
return C1(1, a3);
} else if ((s2887) == IMM(0)) {
return F_Chk_dop_dfind(a0, a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dop_dfind_dif(V *a) { (void)a; return F_Chk_dop_dfind_dif(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dP_dinfix(V a0, V a1, V a2, V a3) {
top:;
V s2888 = a2;
if ((s2888) == IMM(0)) {
return F_Chk_dP_dpure(a0);
} else if (TAG(s2888) == 1) {
return F_Chk_dP_dif(F_Bool_dor(F_U32_dis__lt(FLD(FLD(s2888, 0), 1), a1), a3), F_Chk_dP_dpure(a0), F_Chk_dP_dinfix_dgo(a0, a1, FLD(FLD(s2888, 0), 0), FLD(FLD(s2888, 0), 1), FLD(FLD(s2888, 0), 2), FLD(FLD(s2888, 0), 3)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dinfix(V *a) { (void)a; return F_Chk_dP_dinfix(a[0], a[1], a[2], a[3]); }
static V L2893(V *a) {
return F_Chk_dP_dops(F_Chk_dinfix_dbuild(a[5], a[4], a[3], a[2], a[6], a[1]), a[0]);
}
static V L2892(V *a) {
return F_Chk_dP_dbind(F_Chk_dspan_dgrow(a[4]), mk_clo(L2893, 7, 6, (V[]){a[0], a[1], a[5], a[4], a[2], a[3]}));
}
static V L2891(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm(F_Bool_dpick(a[5], a[4], F_U32_dinc(a[4]))), mk_clo(L2892, 6, 5, (V[]){a[0], a[6], a[1], a[2], a[3]}));
}
static V L2890(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(F_U32_dsub(a[6], F_U32_dfrom__nat(F_String_dlength(a[5])))), mk_clo(L2891, 7, 6, (V[]){a[0], a[1], a[5], a[2], a[3], a[4]}));
}
static V L2889(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L2890, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V F_Chk_dP_dinfix_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(a2), mk_clo(L2889, 7, 6, (V[]){a1, a5, a0, a3, a4, a2}));
}
static V W_Chk_dP_dinfix_dgo(V *a) { (void)a; return F_Chk_dP_dinfix_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S2894(void) { static V c; return STRC(c, "<>"); }
static V S2895(void) { static V c; return STRC(c, "Con"); }
static V S2896(void) { static V c; return STRC(c, "&"); }
static V S2897(void) { static V c; return STRC(c, "Pair"); }
static V S2898(void) { static V c; return STRC(c, "|"); }
static V S2899(void) { static V c; return STRC(c, "Or"); }
static V F_Chk_dinfix_dbuild(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Bool_dpick(F_String_deq(a0, S2894()), C3(15, S2895(), C2(1, a2, C2(1, a3, IMM(0))), a4), F_Bool_dpick(F_String_deq(a0, S2896()), C3(13, C3(13, C3(4, S2897(), a4, IMM(0)), a2, a4), a3, a4), F_Bool_dpick(F_String_deq(a0, S2898()), C3(13, C3(13, C3(4, S2899(), a4, IMM(0)), a2, a4), a3, a4), C3(13, C3(13, C3(4, a1, a5, IMM(0)), a2, a4), a3, a4))));
}
static V W_Chk_dinfix_dbuild(V *a) { (void)a; return F_Chk_dinfix_dbuild(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dspan_dgrow(V a0) {
top:;
return F_Chk_dP_dspan_dfrom(F_Chk_dTm_dspan(a0));
}
static V W_Chk_dspan_dgrow(V *a) { (void)a; return F_Chk_dspan_dgrow(a[0]); }
static V F_Chk_dP_dspan_dfrom(V a0) {
top:;
V s2900 = a0;
if ((s2900) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s2900) == 1) {
return F_Chk_dP_dspan(FLD(s2900, 1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dspan_dfrom(V *a) { (void)a; return F_Chk_dP_dspan_dfrom(a[0]); }
static V L2901(V *a) {
return C1(1, C2(0, C3(1, F_Chk_dPS_dsrc(a[1]), a[0], F_Chk_dCur_dpos(F_Chk_dPS_dcur(a[1]))), a[1]));
}
static V F_Chk_dP_dspan(V a0) {
top:;
return mk_clo(L2901, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dspan(V *a) { (void)a; return F_Chk_dP_dspan(a[0]); }
static V L2902(V *a) {
return C1(1, C2(0, F_Chk_dCur_dpos(F_Chk_dPS_dcur(a[0])), a[0]));
}
static V F_Chk_dP_dpos(void) {
top:;
return mk_clo(L2902, 1, 0, 0);
}
static V W_Chk_dP_dpos(V *a) { (void)a; return F_Chk_dP_dpos(); }
static V S2903(void) { static V c; return STRC(c, "<&>"); }
static V L2906(V *a) {
return F_Chk_dP_dops(C3(10, a[2], a[1], a[3]), a[0]);
}
static V L2905(V *a) {
return F_Chk_dP_dbind(F_Chk_dspan_dgrow(a[1]), mk_clo(L2906, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L2904(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm(5u), mk_clo(L2905, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dminq(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2903()), mk_clo(L2904, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dminq(V *a) { (void)a; return F_Chk_dP_dminq(a[0], a[1]); }
static V S2907(void) { static V c; return STRC(c, "->"); }
static V S2911(void) { static V c; return STRC(c, "_"); }
static V S2913(void) { static V c; return STRC(c, "_"); }
static V L2912(V *a) {
return F_Chk_dP_dops(CN(11, 6, (V[]){IMM(1), S2913(), a[4], a[3], C3(24, IMM(0), a[4], a[2]), a[1]}), a[0]);
}
static V L2910(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dopen(S2911()), mk_clo(L2912, 5, 4, (V[]){a[0], a[3], a[1], a[2]}));
}
static V L2909(V *a) {
return F_Chk_dP_dbind(F_Chk_dspan_dgrow(a[1]), mk_clo(L2910, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L2908(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L2909, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_darrow(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2907()), mk_clo(L2908, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_darrow(V *a) { (void)a; return F_Chk_dP_darrow(a[0], a[1]); }
static V S2914(void) { static V c; return STRC(c, "=>"); }
static V L2919(V *a) {
return F_Chk_dP_dops(F_Chk_dlam_dbuild(a[2], a[1]), a[0]);
}
static V L2918(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[2]), mk_clo(L2919, 4, 3, (V[]){a[0], a[3], a[1]}));
}
static V L2917(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dblock(), mk_clo(L2918, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L2916(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbinder(a[1]), mk_clo(L2917, 3, 2, (V[]){a[0], a[2]}));
}
static V L2915(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L2916, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dlam(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2914()), mk_clo(L2915, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dlam(V *a) { (void)a; return F_Chk_dP_dlam(a[0], a[1]); }
static V F_Chk_dlam_dbuild(V a0, V a1) {
top:;
V s2920 = a0;
if (TAG(s2920) == 0) {
return CN(12, 5, (V[]){FLD(s2920, 0), FLD(s2920, 1), C3(24, IMM(0), FLD(s2920, 1), a1), FLD(s2920, 3), FLD(s2920, 2)});
} else {
return a1;
}
}
static V W_Chk_dlam_dbuild(V *a) { (void)a; return F_Chk_dlam_dbuild(a[0], a[1]); }
static V S2927(void) { static V c; return STRC(c, ">"); }
static V S2929(void) { static V c; return STRC(c, ","); }
static V S2931(void) { static V c; return STRC(c, ".is_lt"); }
static V L2930(V *a) {
return F_Chk_dP_dif(F_Bool_dor(a[5], a[6]), F_Chk_dP_dlt_dadt(a[4], a[3], a[2], a[1]), F_Chk_dP_dops(C3(13, C3(13, C3(4, S2931(), a[0], IMM(0)), a[4], a[2]), a[3], a[2]), a[1]));
}
static V L2928(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S2929()), mk_clo(L2930, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L2926(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S2927()), mk_clo(L2928, 6, 5, (V[]){a[0], a[1], a[4], a[2], a[3]}));
}
static V L2925(V *a) {
return F_Chk_dP_dbind(F_Chk_dspan_dgrow(a[3]), mk_clo(L2926, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L2924(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2925, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V L2923(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm(5u), mk_clo(L2924, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L2922(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(F_U32_dsub(a[2], 1u)), mk_clo(L2923, 3, 2, (V[]){a[0], a[1]}));
}
static V L2921(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L2922, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dlt(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L2921, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dlt(V *a) { (void)a; return F_Chk_dP_dlt(a[0], a[1]); }
static V S2932(void) { static V c; return STRC(c, "a family name before <..> (a comparison here needs parens)"); }
static V F_Chk_dP_dlt_dadt(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dP_dif(F_Bool_dor(F_Chk_dTm_dis__var(a0), F_Chk_dTm_dis__ref(a0)), F_Chk_dP_dlt_dadt_dgo(a0, a1, a2, a3), F_Chk_dP_dfail(S2932()));
}
static V W_Chk_dP_dlt_dadt(V *a) { (void)a; return F_Chk_dP_dlt_dadt(a[0], a[1], a[2], a[3]); }
static V S2933(void) { static V c; return STRC(c, ","); }
static V S2936(void) { static V c; return STRC(c, ">"); }
static V L2938(V *a) {
return F_Chk_dP_dops(C4(14, a[2], a[3], a[1], IMM(0)), a[0]);
}
static V L2937(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dfill(a[3], C2(1, a[2], a[4]), a[1]), mk_clo(L2938, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V L2935(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dargs(S2936()), mk_clo(L2937, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L2934(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(F_Chk_dTm_dname(a[3])), mk_clo(L2935, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dlt_dadt_dgo(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2933()), mk_clo(L2934, 5, 4, (V[]){a3, a2, a1, a0}));
}
static V W_Chk_dP_dlt_dadt_dgo(V *a) { (void)a; return F_Chk_dP_dlt_dadt_dgo(a[0], a[1], a[2], a[3]); }
static V L2939(V *a) {
return F_Chk_dP_dpure(F_Chk_dfill_dgo(F_Chk_dTld_dadt__fill(F_Chk_dbook__tld(a[3], a[2]), F_List_dlength(a[1])), a[1], a[0]));
}
static V F_Chk_dP_dfill(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L2939, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dP_dfill(V *a) { (void)a; return F_Chk_dP_dfill(a[0], a[1], a[2]); }
static V F_Chk_dTld_dadt__fill(V a0, V a1) {
top:;
V s2940 = a0;
if (TAG(s2940) == 1 && TAG(FLD(s2940, 0)) == 1) {
return F_Bool_dpick(F_Nat_dis__eq(F_Nat_dadd(a1, FLD(FLD(s2940, 0), 1)), FLD(FLD(s2940, 0), 0)), C1(1, FLD(FLD(s2940, 0), 1)), IMM(0));
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dadt__fill(V *a) { (void)a; return F_Chk_dTld_dadt__fill(a[0], a[1]); }
static V F_Chk_dfill_dgo(V a0, V a1, V a2) {
top:;
V s2941 = a0;
if ((s2941) == IMM(0)) {
return a1;
} else if (TAG(s2941) == 1) {
return F_List_dappend(F_Chk_dList_drepeat__tm(C2(9, IMM(1), a2), FLD(s2941, 0)), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dfill_dgo(V *a) { (void)a; return F_Chk_dfill_dgo(a[0], a[1], a[2]); }
static V F_Chk_dList_drepeat__tm(V a0, V a1) {
top:;
V s2942 = a1;
if ((s2942) == 0) {
return IMM(0);
} else if (nat_ge(s2942, 1)) {
return C2(1, a0, F_Chk_dList_drepeat__tm(a0, nat_subk(s2942, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dList_drepeat__tm(V *a) { (void)a; return F_Chk_dList_drepeat__tm(a[0], a[1]); }
static V L2944(V *a) {
return F_Chk_dP_dif(a[1], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dargs_done(a[0]));
}
static V L2943(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(a[0]), mk_clo(L2944, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dargs(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2943, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dargs(V *a) { (void)a; return F_Chk_dP_dargs(a[0]); }
static V S2947(void) { static V c; return STRC(c, ","); }
static V L2949(V *a) {
return F_Chk_dP_dpure(C2(1, a[0], a[1]));
}
static V L2948(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dargs(a[1]), mk_clo(L2949, 2, 1, (V[]){a[0]}));
}
static V L2946(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2947()), mk_clo(L2948, 3, 2, (V[]){a[0], a[1]}));
}
static V L2945(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2946, 3, 2, (V[]){a[1], a[0]}));
}
static V F_Chk_dP_dargs_done(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L2945, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dargs_done(V *a) { (void)a; return F_Chk_dP_dargs_done(a[0]); }
static V F_Chk_dTm_dis__ref(V a0) {
top:;
V s2950 = a0;
if (TAG(s2950) == 4) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__ref(V *a) { (void)a; return F_Chk_dTm_dis__ref(a[0]); }
static V L2951(V *a) {
return C1(1, C2(0, IMM(0), F_Chk_dPS_dset__cur(a[0], F_Chk_dCur_dstep(F_Chk_dPS_dcur(a[0])))));
}
static V F_Chk_dP_dbump(void) {
top:;
return mk_clo(L2951, 1, 0, 0);
}
static V W_Chk_dP_dbump(V *a) { (void)a; return F_Chk_dP_dbump(); }
static V S2954(void) { static V c; return STRC(c, "]"); }
static V S2957(void) { static V c; return STRC(c, "U32"); }
static V S2961(void) { static V c; return STRC(c, "<-"); }
static V S2963(void) { static V c; return STRC(c, "Array.get"); }
static V S2964(void) { static V c; return STRC(c, "U32"); }
static V L2962(V *a) {
return F_Chk_dP_dif(a[4], F_Chk_dP_dindex_dset(a[3], a[2], a[1], a[0]), F_Chk_dP_dops(C3(13, C3(13, C3(13, C3(4, S2963(), a[1], IMM(0)), C3(4, S2964(), a[1], IMM(0)), a[1]), a[3], a[1]), a[2], a[1]), a[0]));
}
static V L2960(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[4], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dtake(S2961())), mk_clo(L2962, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L2959(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dnl(), mk_clo(L2960, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L2958(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2959, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V L2956(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dns(a[2], C3(4, S2957(), a[3], IMM(0))), mk_clo(L2958, 4, 3, (V[]){a[0], a[3], a[1]}));
}
static V L2955(V *a) {
return F_Chk_dP_dbind(F_Chk_dspan_dgrow(a[2]), mk_clo(L2956, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L2953(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S2954()), mk_clo(L2955, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L2952(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L2953, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dindex(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L2952, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dindex(V *a) { (void)a; return F_Chk_dP_dindex(a[0], a[1]); }
static V S2966(void) { static V c; return STRC(c, "Array.set"); }
static V S2967(void) { static V c; return STRC(c, "U32"); }
static V L2965(V *a) {
return F_Chk_dP_dops(F_Chk_dapps(C3(4, S2966(), a[3], IMM(0)), C2(1, C3(4, S2967(), a[3], IMM(0)), C2(1, a[2], C2(1, a[1], C2(1, a[4], IMM(0))))), a[3]), a[0]);
}
static V F_Chk_dP_dindex_dset(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm(2u), mk_clo(L2965, 5, 4, (V[]){a3, a1, a0, a2}));
}
static V W_Chk_dP_dindex_dset(V *a) { (void)a; return F_Chk_dP_dindex_dset(a[0], a[1], a[2], a[3]); }
static V F_Chk_dapps(V a0, V a1, V a2) {
top:;
V s2968 = a1;
if ((s2968) == IMM(0)) {
return a0;
} else if (TAG(s2968) == 1) {
{ V t0 = C3(13, a0, FLD(s2968, 0), a2); V t1 = FLD(s2968, 1); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dapps(V *a) { (void)a; return F_Chk_dapps(a[0], a[1], a[2]); }
static V L2969(V *a) {
return C1(1, C2(0, F_Chk_dCur_dnl(F_Chk_dPS_dcur(a[0])), a[0]));
}
static V F_Chk_dP_dnl(void) {
top:;
return mk_clo(L2969, 1, 0, 0);
}
static V W_Chk_dP_dnl(V *a) { (void)a; return F_Chk_dP_dnl(); }
static V F_Chk_dCur_dnl(V a0) {
top:;
V v2970 = a0;
return FLD(v2970, 3);
}
static V W_Chk_dCur_dnl(V *a) { (void)a; return F_Chk_dCur_dnl(a[0]); }
static V L2972(V *a) {
return F_Chk_dP_dpure(CN(6, 6, (V[]){a[4], a[3], a[2], C3(25, IMM(0), a[3], a[5]), a[1], a[0]}));
}
static V F_Chk_dP_dns(V a0, V a1) {
top:;
V s2971 = a0;
if (TAG(s2971) == 6) {
return F_Chk_dP_dbind(F_Chk_dP_dns(F_Chk_dsyn__body(FLD(s2971, 3)), a1), mk_clo(L2972, 6, 5, (V[]){FLD(s2971, 5), FLD(s2971, 4), FLD(s2971, 2), FLD(s2971, 1), FLD(s2971, 0)}));
} else {
return F_Chk_dP_dns_dapp(F_Chk_dterm__unapply(s2971), a1);
}
}
static V W_Chk_dP_dns(V *a) { (void)a; return F_Chk_dP_dns(a[0], a[1]); }
static V S2975(void) { static V c; return STRC(c, "Bool.and"); }
static V S2976(void) { static V c; return STRC(c, "Bool.or"); }
static V S2977(void) { static V c; return STRC(c, "String.append"); }
static V F_Chk_dP_dns_dapp(V a0, V a1) {
top:;
V v2973 = a0;
V s2974 = FLD(v2973, 0);
if (TAG(s2974) == 4) {
return F_Chk_dP_dns_dref(FLD(s2974, 0), FLD(s2974, 1), FLD(s2974, 2), FLD(v2973, 1), a1, F_Nat_dis__eq(F_Chk_dStr_dlast__dot(FLD(s2974, 0)), 0u), F_Chk_dStr_dhas(C2(1, S2975(), C2(1, S2976(), C2(1, S2977(), IMM(0)))), FLD(s2974, 0)));
} else {
return F_Chk_dP_dpure(F_Chk_dapps(s2974, FLD(v2973, 1), IMM(0)));
}
}
static V W_Chk_dP_dns_dapp(V *a) { (void)a; return F_Chk_dP_dns_dapp(a[0], a[1]); }
static V F_Chk_dStr_dlast__dot(V a0) {
top:;
return F_Chk_dStr_dlast__dot_dgo(a0, 0u, 999999u);
}
static V W_Chk_dStr_dlast__dot(V *a) { (void)a; return F_Chk_dStr_dlast__dot(a[0]); }
static V F_Chk_dStr_dlast__dot_dgo(V a0, V a1, V a2) {
top:;
V s2978 = a0;
if ((s2978) == IMM(0)) {
return a2;
} else if (TAG(s2978) == 1) {
{ V t0 = FLD(s2978, 1); V t1 = nat_addk(a1, 1); V t2 = F_Bool_dpick(F_U32_dis__eq(FLD(s2978, 0), 46u), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dlast__dot_dgo(V *a) { (void)a; return F_Chk_dStr_dlast__dot_dgo(a[0], a[1], a[2]); }
static V L2981(V *a) {
return F_Chk_dP_dpure(F_Chk_dapps_dspan(C3(4, a[3], a[2], a[1]), a[4], a[0]));
}
static V F_Chk_dP_dns_dref(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2979 = a5;
V s2980 = a6;
if ((s2979) == IMM(1)) {
return F_Chk_dP_dns_dop(a0, a1, a2, a3, a4, F_Chk_dterm__head(a4));
} else if ((s2979) == IMM(0) && (s2980) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dns_dargs(a3, a4), mk_clo(L2981, 5, 4, (V[]){a3, a2, a1, a0}));
} else if ((s2979) == IMM(0) && (s2980) == IMM(0)) {
return F_Chk_dP_dpure(F_Chk_dapps(C3(4, a0, a1, a2), a3, IMM(0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dns_dref(V *a) { (void)a; return F_Chk_dP_dns_dref(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dapps_dspan(V a0, V a1, V a2) {
top:;
return F_Chk_dapps(a0, a1, IMM(0));
}
static V W_Chk_dapps_dspan(V *a) { (void)a; return F_Chk_dapps_dspan(a[0], a[1], a[2]); }
static V L2984(V *a) {
return F_Chk_dP_dpure(C2(1, a[0], a[1]));
}
static V L2983(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dns_dargs(a[1], a[0]), mk_clo(L2984, 2, 1, (V[]){a[2]}));
}
static V F_Chk_dP_dns_dargs(V a0, V a1) {
top:;
V s2982 = a0;
if ((s2982) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s2982) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dns(FLD(s2982, 0), a1), mk_clo(L2983, 3, 2, (V[]){a1, FLD(s2982, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dns_dargs(V *a) { (void)a; return F_Chk_dP_dns_dargs(a[0], a[1]); }
static V S2986(void) { static V c; return STRC(c, ""); }
static V S2987(void) { static V c; return STRC(c, "a type name after : (the operators' namespace)"); }
static V F_Chk_dP_dns_dop(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2985 = a5;
if (TAG(s2985) == 0) {
return F_Chk_dP_dns_dop_dgo(F_String_dappend(a0, S2986()), FLD(s2985, 0), a1, a2, a3, a4);
} else if (TAG(s2985) == 3) {
return F_Chk_dP_dns_dop_dgo(a0, FLD(s2985, 0), a1, a2, a3, a4);
} else if (TAG(s2985) == 4) {
return F_Chk_dP_dns_dop_dgo(a0, FLD(s2985, 0), a1, a2, a3, a4);
} else if (TAG(s2985) == 14) {
return F_Chk_dP_dns_dop_dgo(a0, FLD(s2985, 0), a1, a2, a3, a4);
} else {
return F_Chk_dP_dthrow(F_Chk_derr0(S2987(), IMM(0), F_Chk_dTm_dspan(s2985)));
}
}
static V W_Chk_dP_dns_dop(V *a) { (void)a; return F_Chk_dP_dns_dop(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L2989(V *a) {
return F_Chk_dP_dpure(F_Chk_dapps_dspan(C3(4, a[3], a[2], a[1]), a[4], a[0]));
}
static V L2988(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dns_dargs(a[3], a[2]), mk_clo(L2989, 5, 4, (V[]){a[3], a[0], a[1], a[4]}));
}
static V F_Chk_dP_dns_dop_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dreso(F_String_dappend(a1, a0)), mk_clo(L2988, 5, 4, (V[]){a3, a2, a5, a4}));
}
static V W_Chk_dP_dns_dop_dgo(V *a) { (void)a; return F_Chk_dP_dns_dop_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L2991(V *a) {
return F_Chk_dP_deat_dif(a[0], a[1]);
}
static V L2990(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(a[0]), mk_clo(L2991, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_deat(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2990, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_deat(V *a) { (void)a; return F_Chk_dP_deat(a[0]); }
static V S2993(void) { static V c; return STRC(c, "'"); }
static V S2994(void) { static V c; return STRC(c, "'"); }
static V F_Chk_dP_deat_dif(V a0, V a1) {
top:;
V s2992 = a1;
if ((s2992) == IMM(1)) {
return F_Chk_dP_dpure(IMM(0));
} else if ((s2992) == IMM(0)) {
return F_Chk_dP_dfail(F_String_dappend(S2993(), F_String_dappend(a0, S2994())));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_deat_dif(V *a) { (void)a; return F_Chk_dP_deat_dif(a[0], a[1]); }
static V S2996(void) { static V c; return STRC(c, "!"); }
static V L2997(V *a) {
return F_Chk_dP_dif(a[2], F_Chk_dP_dcall_dbang(a[1], a[0]), F_Chk_dP_dcall_dargs(a[1], a[0]));
}
static V L2995(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S2996()), mk_clo(L2997, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dcall(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dcall_dhead(a0), mk_clo(L2995, 2, 1, (V[]){a1}));
}
static V W_Chk_dP_dcall(V *a) { (void)a; return F_Chk_dP_dcall(a[0], a[1]); }
static V S3000(void) { static V c; return STRC(c, ""); }
static V S3004(void) { static V c; return STRC(c, ")"); }
static V L3006(V *a) {
return F_Chk_dP_dops(F_Chk_dapps(a[3], F_List_dappend(a[2], a[1]), a[4]), a[0]);
}
static V L3005(V *a) {
return F_Chk_dP_dbind(F_Chk_dspan_dgrow(a[2]), mk_clo(L3006, 5, 4, (V[]){a[0], a[3], a[1], a[2]}));
}
static V L3003(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dargs(S3004()), mk_clo(L3005, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L3002(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcall_dtmpl(a[2], a[1], IMM(0)), mk_clo(L3003, 3, 2, (V[]){a[0], a[2]}));
}
static V L3001(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3002, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L2999(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_dTld_dx(F_Chk_dbook__tld(a[2], F_Bool_dpick(F_Chk_dTm_dis__ref(a[1]), F_Chk_dTm_dname(a[1]), S3000())))), mk_clo(L3001, 3, 2, (V[]){a[0], a[1]}));
}
static V L2998(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L2999, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dcall_dargs(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L2998, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dcall_dargs(V *a) { (void)a; return F_Chk_dP_dcall_dargs(a[0], a[1]); }
static V S3007(void) { static V c; return STRC(c, "~"); }
static V L3008(V *a) {
return F_Chk_dP_dif(F_Bool_dand(F_Nat_dis__gt(a[2], 0u), a[3]), F_Chk_dP_dcall_dtmpl_done(a[1], a[2], a[0]), F_Chk_dP_dpure(a[0]));
}
static V F_Chk_dP_dcall_dtmpl(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dat(S3007()), mk_clo(L3008, 4, 3, (V[]){a2, a0, a1}));
}
static V W_Chk_dP_dcall_dtmpl(V *a) { (void)a; return F_Chk_dP_dcall_dtmpl(a[0], a[1], a[2]); }
static V S3009(void) { static V c; return STRC(c, "a term ("); }
static V S3010(void) { static V c; return STRC(c, " takes "); }
static V S3011(void) { static V c; return STRC(c, " ~)"); }
static V F_Chk_dP_dcall_dtmpl_done(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dif(F_Nat_dis__eq(F_List_dlength(a2), a1), F_Chk_dP_dfail(F_String_dappend(S3009(), F_String_dappend(F_Chk_dTm_dname(a0), F_String_dappend(S3010(), F_String_dappend(F_Nat_dshow(a1), S3011()))))), F_Chk_dP_dcall_dtmpl_dgo(a0, a1, a2));
}
static V W_Chk_dP_dcall_dtmpl_done(V *a) { (void)a; return F_Chk_dP_dcall_dtmpl_done(a[0], a[1], a[2]); }
static V S3015(void) { static V c; return STRC(c, ","); }
static V L3017(V *a) {
return F_Chk_dP_dcall_dtmpl(a[3], a[2], F_List_dappend(a[1], C2(1, a[0], IMM(0))));
}
static V L3016(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3017, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3014(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3015()), mk_clo(L3016, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3013(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3014, 5, 4, (V[]){a[3], a[0], a[1], a[2]}));
}
static V L3012(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3013, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dcall_dtmpl_dgo(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3012, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dP_dcall_dtmpl_dgo(V *a) { (void)a; return F_Chk_dP_dcall_dtmpl_dgo(a[0], a[1], a[2]); }
static V S3018(void) { static V c; return STRC(c, "a named def before ! (only f!(..) offloads)"); }
static V F_Chk_dP_dcall_dbang(V a0, V a1) {
top:;
return F_Chk_dP_dif(F_Chk_dTm_dis__ref(a0), F_Chk_dP_dcall_dbang_dgo(a0, a1), F_Chk_dP_dfail(S3018()));
}
static V W_Chk_dP_dcall_dbang(V *a) { (void)a; return F_Chk_dP_dcall_dbang(a[0], a[1]); }
static V L3019(V *a) {
return F_Chk_dP_dops(F_Chk_dTm_dbang(a[1]), a[0]);
}
static V F_Chk_dP_dcall_dbang_dgo(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3019, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dcall_dbang_dgo(V *a) { (void)a; return F_Chk_dP_dcall_dbang_dgo(a[0], a[1]); }
static V F_Chk_dTm_dbang(V a0) {
top:;
V s3020 = a0;
if (TAG(s3020) == 4) {
return C3(4, FLD(s3020, 0), FLD(s3020, 1), IMM(1));
} else {
return s3020;
}
}
static V W_Chk_dTm_dbang(V *a) { (void)a; return F_Chk_dTm_dbang(a[0]); }
static V F_Chk_dP_dcall_dhead(V a0) {
top:;
V s3021 = a0;
if (TAG(s3021) == 0) {
return F_Chk_dP_dcall_dhead_dvar(FLD(s3021, 0), FLD(s3021, 2), C3(0, FLD(s3021, 0), FLD(s3021, 1), FLD(s3021, 2)));
} else if (TAG(s3021) == 3) {
return F_Chk_dP_dcall_dhead_dvar(FLD(s3021, 0), FLD(s3021, 2), C4(3, FLD(s3021, 0), FLD(s3021, 1), FLD(s3021, 2), FLD(s3021, 3)));
} else {
return F_Chk_dP_dpure(s3021);
}
}
static V W_Chk_dP_dcall_dhead(V *a) { (void)a; return F_Chk_dP_dcall_dhead(a[0]); }
static V L3023(V *a) {
return F_Chk_dP_dpure(F_Bool_dpick(F_Maybe_dis__some(a[2]), a[1], C3(4, a[3], a[0], IMM(0))));
}
static V L3022(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(a[2]), mk_clo(L3023, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V F_Chk_dP_dcall_dhead_dvar(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dlookup(a0), mk_clo(L3022, 4, 3, (V[]){a1, a2, a0}));
}
static V W_Chk_dP_dcall_dhead_dvar(V *a) { (void)a; return F_Chk_dP_dcall_dhead_dvar(a[0], a[1], a[2]); }
static V L3024(V *a) {
return C1(1, C2(0, F_Chk_dSB_dfind(F_Chk_dPS_dstk(a[1]), a[0]), a[1]));
}
static V F_Chk_dP_dlookup(V a0) {
top:;
return mk_clo(L3024, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dlookup(V *a) { (void)a; return F_Chk_dP_dlookup(a[0]); }
static V F_Chk_dPS_dstk(V a0) {
top:;
V v3025 = a0;
return FLD(v3025, 1);
}
static V W_Chk_dPS_dstk(V *a) { (void)a; return F_Chk_dPS_dstk(a[0]); }
static V F_Chk_dSB_dfind(V a0, V a1) {
top:;
V s3026 = a0;
if ((s3026) == IMM(0)) {
return IMM(0);
} else if (TAG(s3026) == 1) {
return F_Chk_dSB_dfind_dif(FLD(s3026, 1), a1, FLD(FLD(s3026, 0), 1), F_String_deq(a1, FLD(FLD(s3026, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dSB_dfind(V *a) { (void)a; return F_Chk_dSB_dfind(a[0], a[1]); }
static V F_Chk_dSB_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s3027 = a3;
if ((s3027) == IMM(1)) {
return C1(1, a2);
} else if ((s3027) == IMM(0)) {
return F_Chk_dSB_dfind(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dSB_dfind_dif(V *a) { (void)a; return F_Chk_dSB_dfind_dif(a[0], a[1], a[2], a[3]); }
static V L3028(V *a) {
return C1(1, C2(0, F_Chk_dCur_dprev(F_Chk_dPS_dcur(a[0])), a[0]));
}
static V F_Chk_dP_dprev(void) {
top:;
return mk_clo(L3028, 1, 0, 0);
}
static V W_Chk_dP_dprev(V *a) { (void)a; return F_Chk_dP_dprev(); }
static V F_Chk_dCur_dprev(V a0) {
top:;
V v3029 = a0;
return FLD(v3029, 4);
}
static V W_Chk_dCur_dprev(V *a) { (void)a; return F_Chk_dCur_dprev(a[0]); }
static V L3030(V *a) {
return C1(1, C2(0, F_Chk_dCur_drest(F_Chk_dPS_dcur(a[0])), a[0]));
}
static V F_Chk_dP_dpeek__rest(void) {
top:;
return mk_clo(L3030, 1, 0, 0);
}
static V W_Chk_dP_dpeek__rest(V *a) { (void)a; return F_Chk_dP_dpeek__rest(); }
static V L3031(V *a) {
return F_Chk_dP_dbase_dgo(a[1], a[0], F_Bool_dpick(F_Chk_dis__head(a[1]), 0u, F_Bool_dpick(F_Chk_dis__digit(a[1]), 1u, 2u)));
}
static V F_Chk_dP_dbase(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3031, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbase(V *a) { (void)a; return F_Chk_dP_dbase(a[0]); }
static V L3033(V *a) {
return F_Chk_dP_dbase_dword(a[1], a[0]);
}
static V F_Chk_dP_dbase_dgo(V a0, V a1, V a2) {
top:;
V s3032 = a2;
if ((s3032) == 0) {
return F_Chk_dP_dbind(F_Chk_dP_dlexeme(), mk_clo(L3033, 2, 1, (V[]){a1}));
} else if ((s3032) == 1) {
return F_Chk_dP_dnum();
} else if (nat_ge(s3032, 2)) {
return F_Chk_dP_dbase_dsym(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dbase_dgo(V *a) { (void)a; return F_Chk_dP_dbase_dgo(a[0], a[1], a[2]); }
static V S3034(void) { static V c; return STRC(c, "@"); }
static V S3035(void) { static V c; return STRC(c, "&"); }
static V S3036(void) { static V c; return STRC(c, "+"); }
static V S3037(void) { static V c; return STRC(c, "\134"); }
static V S3038(void) { static V c; return STRC(c, "%"); }
static V S3039(void) { static V c; return STRC(c, "{"); }
static V S3040(void) { static V c; return STRC(c, "("); }
static V S3041(void) { static V c; return STRC(c, "["); }
static V S3042(void) { static V c; return STRC(c, "'"); }
static V S3043(void) { static V c; return STRC(c, "\042"); }
static V S3044(void) { static V c; return STRC(c, "\077"); }
static V F_Chk_dP_dbase_dsym(V a0, V a1) {
top:;
return F_Chk_dP_dbase_dsym_dgo(a0, a1, F_Chk_dStr_dindex(C2(1, S3034(), C2(1, S3035(), C2(1, S3036(), C2(1, S3037(), C2(1, S3038(), C2(1, S3039(), C2(1, S3040(), C2(1, S3041(), C2(1, S3042(), C2(1, S3043(), C2(1, S3044(), IMM(0)))))))))))), F_Chk_dStr_dchr(a0), 0u));
}
static V W_Chk_dP_dbase_dsym(V *a) { (void)a; return F_Chk_dP_dbase_dsym(a[0], a[1]); }
static V L3046(V *a) {
return F_Chk_dP_damp(F_Chk_dStr_dsecond(a[1]), a[0]);
}
static V L3047(V *a) {
return F_Chk_dP_dtup(a[0]);
}
static V S3048(void) { static V c; return STRC(c, "a term"); }
static V F_Chk_dP_dbase_dsym_dgo(V a0, V a1, V a2) {
top:;
V s3045 = a2;
if (TAG(s3045) == 1 && (FLD(s3045, 0)) == 0) {
return F_Chk_dP_dall(IMM(0));
} else if (TAG(s3045) == 1 && (FLD(s3045, 0)) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek__rest(), mk_clo(L3046, 2, 1, (V[]){a1}));
} else if (TAG(s3045) == 1 && (FLD(s3045, 0)) == 2) {
return F_Chk_dP_dplus(a1);
} else if (TAG(s3045) == 1 && (FLD(s3045, 0)) == 3) {
return F_Chk_dP_darms(a1);
} else if (TAG(s3045) == 1 && (FLD(s3045, 0)) == 4) {
return F_Chk_dP_drwt(a1);
} else if (TAG(s3045) == 1 && (FLD(s3045, 0)) == 5) {
return F_Chk_dP_dbrace(a1);
} else if (TAG(s3045) == 1 && (FLD(s3045, 0)) == 6) {
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3047, 2, 1, (V[]){a1}));
} else if (TAG(s3045) == 1 && (FLD(s3045, 0)) == 7) {
return F_Chk_dP_dbrack(a1);
} else if (TAG(s3045) == 1 && (FLD(s3045, 0)) == 8) {
return F_Chk_dP_dchr__lit(a1);
} else if (TAG(s3045) == 1 && (FLD(s3045, 0)) == 9) {
return F_Chk_dP_dstr__lit(a1);
} else if (TAG(s3045) == 1 && (FLD(s3045, 0)) == 10) {
return F_Chk_dP_dhole(a1);
} else {
return F_Chk_dP_dfail(S3048());
}
}
static V W_Chk_dP_dbase_dsym_dgo(V *a) { (void)a; return F_Chk_dP_dbase_dsym_dgo(a[0], a[1], a[2]); }
static V S3051(void) { static V c; return STRC(c, "TODO"); }
static V L3053(V *a) {
return F_Chk_dP_dpure(C2(22, a[0], a[1]));
}
static V L3052(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3053, 2, 1, (V[]){a[0]}));
}
static V L3050(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_String_deq(a[1], S3051()), F_Chk_dP_dcount__hole(), F_Chk_dP_dpure(IMM(0))), mk_clo(L3052, 3, 2, (V[]){a[1], a[0]}));
}
static V L3049(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3050, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dhole(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3049, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dhole(V *a) { (void)a; return F_Chk_dP_dhole(a[0]); }
static V L3054(V *a) {
return F_Chk_dP_dset__book(F_Chk_dbook__hole(a[0]));
}
static V F_Chk_dP_dcount__hole(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3054, 1, 0, 0));
}
static V W_Chk_dP_dcount__hole(V *a) { (void)a; return F_Chk_dP_dcount__hole(); }
static V F_Chk_dbook__hole(V a0) {
top:;
V v3055 = a0;
return CN(0, 7, (V[]){FLD(v3055, 0), FLD(v3055, 1), FLD(v3055, 2), nat_addk(FLD(v3055, 3), 1), FLD(v3055, 4), FLD(v3055, 5), FLD(v3055, 6)});
}
static V W_Chk_dbook__hole(V *a) { (void)a; return F_Chk_dbook__hole(a[0]); }
static V L3056(V *a) {
return F_Chk_dP_dname_dcheck(a[0]);
}
static V F_Chk_dP_dname(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dlexeme(), mk_clo(L3056, 1, 0, 0));
}
static V W_Chk_dP_dname(V *a) { (void)a; return F_Chk_dP_dname(); }
static V F_Chk_dP_dname_dcheck(V a0) {
top:;
return F_Chk_dP_dname_dcheck_dc(a0, F_Chk_dStr_dhas(F_Chk_dKEYWORDS(), a0));
}
static V W_Chk_dP_dname_dcheck(V *a) { (void)a; return F_Chk_dP_dname_dcheck(a[0]); }
static V S3057(void) { static V c; return STRC(c, "def"); }
static V S3058(void) { static V c; return STRC(c, "type"); }
static V S3059(void) { static V c; return STRC(c, "law"); }
static V S3060(void) { static V c; return STRC(c, "match"); }
static V S3061(void) { static V c; return STRC(c, "case"); }
static V S3062(void) { static V c; return STRC(c, "do"); }
static V S3063(void) { static V c; return STRC(c, "return"); }
static V S3064(void) { static V c; return STRC(c, "for"); }
static V S3065(void) { static V c; return STRC(c, "exs"); }
static V S3066(void) { static V c; return STRC(c, "where"); }
static V S3067(void) { static V c; return STRC(c, "is"); }
static V S3068(void) { static V c; return STRC(c, "import"); }
static V S3069(void) { static V c; return STRC(c, "Type"); }
static V S3070(void) { static V c; return STRC(c, "Data"); }
static V S3071(void) { static V c; return STRC(c, "Kind"); }
static V S3072(void) { static V c; return STRC(c, "Quant"); }
static V F_Chk_dKEYWORDS(void) {
top:;
return C2(1, S3057(), C2(1, S3058(), C2(1, S3059(), C2(1, S3060(), C2(1, S3061(), C2(1, S3062(), C2(1, S3063(), C2(1, S3064(), C2(1, S3065(), C2(1, S3066(), C2(1, S3067(), C2(1, S3068(), C2(1, S3069(), C2(1, S3070(), C2(1, S3071(), C2(1, S3072(), IMM(0)))))))))))))))));
}
static V W_Chk_dKEYWORDS(V *a) { (void)a; return F_Chk_dKEYWORDS(); }
static V S3074(void) { static V c; return STRC(c, "a name (got the keyword '"); }
static V S3075(void) { static V c; return STRC(c, "')"); }
static V F_Chk_dP_dname_dcheck_dc(V a0, V a1) {
top:;
V s3073 = a1;
if ((s3073) == IMM(1)) {
return F_Chk_dP_dfail(F_String_dappend(S3074(), F_String_dappend(a0, S3075())));
} else if ((s3073) == IMM(0)) {
return F_Chk_dP_dpure(a0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dname_dcheck_dc(V *a) { (void)a; return F_Chk_dP_dname_dcheck_dc(a[0], a[1]); }
static V L3077(V *a) {
return F_Chk_dP_dlexeme_dif(a[0], F_Chk_dis__head(F_Chk_dCur_dpeek(a[0])));
}
static V L3076(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcur(), mk_clo(L3077, 1, 0, 0));
}
static V F_Chk_dP_dlexeme(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3076, 1, 0, 0));
}
static V W_Chk_dP_dlexeme(V *a) { (void)a; return F_Chk_dP_dlexeme(); }
static V S3079(void) { static V c; return STRC(c, "a name"); }
static V F_Chk_dP_dlexeme_dif(V a0, V a1) {
top:;
V s3078 = a1;
if ((s3078) == IMM(1)) {
return F_Chk_dP_dlexeme_dgo(a0);
} else if ((s3078) == IMM(0)) {
return F_Chk_dP_dfail(S3079());
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dlexeme_dif(V *a) { (void)a; return F_Chk_dP_dlexeme_dif(a[0], a[1]); }
static V S3080(void) { static V c; return STRC(c, ""); }
static V F_Chk_dP_dlexeme_dgo(V a0) {
top:;
return F_Chk_dP_dlexeme_dfin(F_Chk_dCur_dname(a0, S3080()));
}
static V W_Chk_dP_dlexeme_dgo(V *a) { (void)a; return F_Chk_dP_dlexeme_dgo(a[0]); }
static V F_Chk_dCur_dname(V a0, V a1) {
top:;
return F_Chk_dCur_dname_dgo(F_Chk_dCur_dpeek(a0), a0, a1);
}
static V W_Chk_dCur_dname(V *a) { (void)a; return F_Chk_dCur_dname(a[0], a[1]); }
static V F_Chk_dCur_dname_dgo(V a0, V a1, V a2) {
top:;
return F_Chk_dCur_dname_dc(a0, a1, a2, F_Chk_dis__name(a0));
}
static V W_Chk_dCur_dname_dgo(V *a) { (void)a; return F_Chk_dCur_dname_dgo(a[0], a[1], a[2]); }
static V F_Chk_dis__name(V a0) {
top:;
return F_Bool_dor(F_Bool_dor(F_Chk_dis__head(a0), F_Chk_dis__digit(a0)), F_U32_dis__eq(a0, 46u));
}
static V W_Chk_dis__name(V *a) { (void)a; return F_Chk_dis__name(a[0]); }
static V F_Chk_dCur_dname_dc(V a0, V a1, V a2, V a3) {
top:;
V s3081 = a3;
if ((s3081) == IMM(1)) {
return F_Chk_dCur_dname(F_Chk_dCur_dstep(a1), C2(1, a0, a2));
} else if ((s3081) == IMM(0)) {
return C2(0, F_String_dreverse(a2), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCur_dname_dc(V *a) { (void)a; return F_Chk_dCur_dname_dc(a[0], a[1], a[2], a[3]); }
static V L3083(V *a) {
return F_Chk_dP_dlexeme_ddot(a[0]);
}
static V F_Chk_dP_dlexeme_dfin(V a0) {
top:;
V v3082 = a0;
return F_Chk_dP_dbind(F_Chk_dP_dset__cur(FLD(v3082, 1)), mk_clo(L3083, 2, 1, (V[]){FLD(v3082, 0)}));
}
static V W_Chk_dP_dlexeme_dfin(V *a) { (void)a; return F_Chk_dP_dlexeme_dfin(a[0]); }
static V S3084(void) { static V c; return STRC(c, "."); }
static V F_Chk_dP_dlexeme_ddot(V a0) {
top:;
return F_Chk_dP_dlexeme_ddot_dc(a0, F_String_dends__with(a0, S3084()));
}
static V W_Chk_dP_dlexeme_ddot(V *a) { (void)a; return F_Chk_dP_dlexeme_ddot(a[0]); }
static V S3086(void) { static V c; return STRC(c, "a name (a name cannot end in '.')"); }
static V F_Chk_dP_dlexeme_ddot_dc(V a0, V a1) {
top:;
V s3085 = a1;
if ((s3085) == IMM(1)) {
return F_Chk_dP_dfail(S3086());
} else if ((s3085) == IMM(0)) {
return F_Chk_dP_dpure(a0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dlexeme_ddot_dc(V *a) { (void)a; return F_Chk_dP_dlexeme_ddot_dc(a[0], a[1]); }
static V L3087(V *a) {
return C1(1, C2(0, IMM(0), F_Chk_dPS_dset__cur(a[1], a[0])));
}
static V F_Chk_dP_dset__cur(V a0) {
top:;
return mk_clo(L3087, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dset__cur(V *a) { (void)a; return F_Chk_dP_dset__cur(a[0]); }
static V L3088(V *a) {
return C1(1, C2(0, F_Chk_dPS_dcur(a[0]), a[0]));
}
static V F_Chk_dP_dcur(void) {
top:;
return mk_clo(L3088, 1, 0, 0);
}
static V W_Chk_dP_dcur(V *a) { (void)a; return F_Chk_dP_dcur(); }
static V L3091(V *a) {
return F_Chk_dP_dpure(F_Chk_dlit__of(a[0], a[1]));
}
static V L3090(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[0]), mk_clo(L3091, 2, 1, (V[]){a[1]}));
}
static V L3089(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstr_dgo(IMM(0)), mk_clo(L3090, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dstr__lit(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3089, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dstr__lit(V *a) { (void)a; return F_Chk_dP_dstr__lit(a[0]); }
static V F_Chk_dlit__of(V a0, V a1) {
top:;
return F_Bool_dpick(F_Chk_dcodes_dplain(a0), C2(16, C1(1, F_Chk_dStr_dfrom__codes(a0)), a1), F_Chk_dlit__chain(a0, a1));
}
static V W_Chk_dlit__of(V *a) { (void)a; return F_Chk_dlit__of(a[0], a[1]); }
static V F_Chk_dStr_dfrom__codes(V a0) {
top:;
V s3092 = a0;
if ((s3092) == IMM(0)) {
return IMM(0);
} else if (TAG(s3092) == 1) {
return C2(1, FLD(s3092, 0), F_Chk_dStr_dfrom__codes(FLD(s3092, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dfrom__codes(V *a) { (void)a; return F_Chk_dStr_dfrom__codes(a[0]); }
static V F_Chk_dcodes_dplain(V a0) {
top:;
V s3093 = a0;
if ((s3093) == IMM(0)) {
return IMM(1);
} else if (TAG(s3093) == 1) {
return F_Bool_dand(F_Bool_dand(F_U32_dis__le(FLD(s3093, 0), 1114111u), F_Bool_dor(F_U32_dis__lt(FLD(s3093, 0), 55296u), F_U32_dis__gt(FLD(s3093, 0), 57343u))), F_Chk_dcodes_dplain(FLD(s3093, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcodes_dplain(V *a) { (void)a; return F_Chk_dcodes_dplain(a[0]); }
static V S3094(void) { static V c; return STRC(c, "\042"); }
static V S3097(void) { static V c; return STRC(c, "a closing \042"); }
static V L3096(V *a) {
return F_Chk_dP_dif(a[1], F_Chk_dP_dpure(F_List_dreverse(a[0])), F_Chk_dP_dif(F_U32_dis__zero(a[2]), F_Chk_dP_dfail(S3097()), F_Chk_dP_dstr_dmore(a[0])));
}
static V L3095(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3096, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dstr_dgo(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3094()), mk_clo(L3095, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dstr_dgo(V *a) { (void)a; return F_Chk_dP_dstr_dgo(a[0]); }
static V L3098(V *a) {
return F_Chk_dP_dstr_dgo(C2(1, a[1], a[0]));
}
static V F_Chk_dP_dstr_dmore(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dchar(), mk_clo(L3098, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dstr_dmore(V *a) { (void)a; return F_Chk_dP_dstr_dmore(a[0]); }
static V S3099(void) { static V c; return STRC(c, "\134"); }
static V L3100(V *a) {
return F_Chk_dP_dif(a[0], F_Chk_dP_descape(), F_Chk_dP_dchar_dplain());
}
static V F_Chk_dP_dchar(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3099()), mk_clo(L3100, 1, 0, 0));
}
static V W_Chk_dP_dchar(V *a) { (void)a; return F_Chk_dP_dchar(); }
static V S3102(void) { static V c; return STRC(c, "a character"); }
static V L3101(V *a) {
return F_Chk_dP_dif(F_U32_dis__zero(a[0]), F_Chk_dP_dfail(S3102()), F_Chk_dP_dchar_dtake(a[0]));
}
static V F_Chk_dP_dchar_dplain(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3101, 1, 0, 0));
}
static V W_Chk_dP_dchar_dplain(V *a) { (void)a; return F_Chk_dP_dchar_dplain(); }
static V L3103(V *a) {
return F_Chk_dP_dpure(a[0]);
}
static V F_Chk_dP_dchar_dtake(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3103, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dchar_dtake(V *a) { (void)a; return F_Chk_dP_dchar_dtake(a[0]); }
static V L3104(V *a) {
return C1(1, C2(0, F_Chk_dCur_dpeek(F_Chk_dPS_dcur(a[0])), a[0]));
}
static V F_Chk_dP_dpeek(void) {
top:;
return mk_clo(L3104, 1, 0, 0);
}
static V W_Chk_dP_dpeek(V *a) { (void)a; return F_Chk_dP_dpeek(); }
static V L3105(V *a) {
return F_Chk_dP_descape_du(F_Chk_duesc(a[0]));
}
static V F_Chk_dP_descape(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpeek__rest(), mk_clo(L3105, 1, 0, 0));
}
static V W_Chk_dP_descape(V *a) { (void)a; return F_Chk_dP_descape(); }
static V F_Chk_duesc(V a0) {
top:;
V s3106 = a0;
if (TAG(s3106) == 1 && TAG(FLD(s3106, 1)) == 1 && (FLD(FLD(s3106, 1), 0)) == 123) {
return F_Chk_duesc_dif(FLD(FLD(s3106, 1), 1), F_Bool_dor(F_U32_dis__eq(FLD(s3106, 0), 117u), F_U32_dis__eq(FLD(s3106, 0), 85u)));
} else {
return IMM(0);
}
}
static V W_Chk_duesc(V *a) { (void)a; return F_Chk_duesc(a[0]); }
static V F_Chk_duesc_dif(V a0, V a1) {
top:;
V s3107 = a1;
if ((s3107) == IMM(1)) {
return F_Chk_duesc_dhex(a0, 0u, 0u);
} else if ((s3107) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duesc_dif(V *a) { (void)a; return F_Chk_duesc_dif(a[0], a[1]); }
static V F_Chk_duesc_dhex(V a0, V a1, V a2) {
top:;
V s3108 = a0;
if (TAG(s3108) == 1) {
return F_Chk_duesc_dhex_dif(FLD(s3108, 1), FLD(s3108, 0), a1, a2, F_Chk_dis__hex(FLD(s3108, 0)), F_U32_dis__eq(FLD(s3108, 0), 125u));
} else if ((s3108) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duesc_dhex(V *a) { (void)a; return F_Chk_duesc_dhex(a[0], a[1], a[2]); }
static V F_Chk_dis__hex(V a0) {
top:;
return F_Bool_dor(F_Chk_dis__digit(a0), F_Bool_dor(F_Bool_dand(F_U32_dis__ge(a0, 97u), F_U32_dis__le(a0, 102u)), F_Bool_dand(F_U32_dis__ge(a0, 65u), F_U32_dis__le(a0, 70u))));
}
static V W_Chk_dis__hex(V *a) { (void)a; return F_Chk_dis__hex(a[0]); }
static V F_Chk_duesc_dhex_dif(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s3109 = a4;
V s3110 = a5;
if ((s3109) == IMM(1)) {
return F_Bool_dpick(F_Nat_dis__ge(a3, 8u), IMM(0), F_Chk_duesc_dhex(a0, F_U32_dadd(F_U32_dmul(a2, 16u), F_Chk_dhex__val(a1)), nat_addk(a3, 1)));
} else if ((s3109) == IMM(0) && (s3110) == IMM(1)) {
return F_Bool_dpick(F_Nat_dis__eq(a3, 0u), IMM(0), C1(1, C2(0, a2, F_Nat_dadd(a3, 3u))));
} else if ((s3109) == IMM(0) && (s3110) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duesc_dhex_dif(V *a) { (void)a; return F_Chk_duesc_dhex_dif(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dhex__val(V a0) {
top:;
return F_Bool_dpick(F_Chk_dis__digit(a0), F_U32_dsub(a0, 48u), F_Bool_dpick(F_U32_dis__ge(a0, 97u), F_U32_dsub(a0, 87u), F_U32_dsub(a0, 55u)));
}
static V W_Chk_dhex__val(V *a) { (void)a; return F_Chk_dhex__val(a[0]); }
static V L3113(V *a) {
return F_Chk_dP_descape_dnamed(F_Chk_descape_dfind(F_Chk_dESCAPES(), a[0]));
}
static V L3112(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3113, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_descape_du(V a0) {
top:;
V s3111 = a0;
if (TAG(s3111) == 1) {
return F_Chk_dP_descape_du_dgo(FLD(s3111, 0));
} else if ((s3111) == IMM(0)) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3112, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_descape_du(V *a) { (void)a; return F_Chk_dP_descape_du(a[0]); }
static V F_Chk_dESCAPES(void) {
top:;
return C2(1, 110u, C2(1, 10u, C2(1, 116u, C2(1, 9u, C2(1, 114u, C2(1, 13u, C2(1, 48u, C2(1, 0u, C2(1, 92u, C2(1, 92u, C2(1, 39u, C2(1, 39u, C2(1, 34u, C2(1, 34u, IMM(0)))))))))))))));
}
static V W_Chk_dESCAPES(V *a) { (void)a; return F_Chk_dESCAPES(); }
static V F_Chk_descape_dfind(V a0, V a1) {
top:;
V s3114 = a0;
if (TAG(s3114) == 1 && TAG(FLD(s3114, 1)) == 1) {
return F_Chk_descape_dfind_dif(FLD(FLD(s3114, 1), 1), a1, FLD(FLD(s3114, 1), 0), F_U32_dis__eq(FLD(s3114, 0), a1));
} else {
return IMM(0);
}
}
static V W_Chk_descape_dfind(V *a) { (void)a; return F_Chk_descape_dfind(a[0], a[1]); }
static V F_Chk_descape_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s3115 = a3;
if ((s3115) == IMM(1)) {
return C1(1, a2);
} else if ((s3115) == IMM(0)) {
return F_Chk_descape_dfind(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_descape_dfind_dif(V *a) { (void)a; return F_Chk_descape_dfind_dif(a[0], a[1], a[2], a[3]); }
static V S3117(void) { static V c; return STRC(c, "an escape (\134n \134t \134r \1340 \134\134 \134' \134\042 \134u{1F600})"); }
static V F_Chk_dP_descape_dnamed(V a0) {
top:;
V s3116 = a0;
if (TAG(s3116) == 1) {
return F_Chk_dP_dpure(FLD(s3116, 0));
} else if ((s3116) == IMM(0)) {
return F_Chk_dP_dfail(S3117());
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_descape_dnamed(V *a) { (void)a; return F_Chk_dP_descape_dnamed(a[0]); }
static V L3120(V *a) {
return C1(1, C2(0, a[1], F_Chk_dPS_dset__cur(a[2], F_Chk_dCur_dsteps(F_Chk_dPS_dcur(a[2]), a[0]))));
}
static V F_Chk_dP_descape_du_dgo(V a0) {
top:;
V v3118 = a0;
V v3119 = FLD(v3118, 0);
return mk_clo(L3120, 3, 2, (V[]){FLD(v3118, 1), v3119});
}
static V W_Chk_dP_descape_du_dgo(V *a) { (void)a; return F_Chk_dP_descape_du_dgo(a[0]); }
static V S3123(void) { static V c; return STRC(c, "'"); }
static V L3124(V *a) {
return F_Chk_dP_dchr__lit_dfin(a[1], a[0], a[2]);
}
static V L3122(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3123()), mk_clo(L3124, 3, 2, (V[]){a[1], a[0]}));
}
static V L3121(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dchar(), mk_clo(L3122, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dchr__lit(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3121, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dchr__lit(V *a) { (void)a; return F_Chk_dP_dchr__lit(a[0]); }
static V S3127(void) { static V c; return STRC(c, "Chr"); }
static V L3126(V *a) {
return F_Chk_dP_dpure(C3(15, S3127(), C2(1, F_Chk_du32__to__term(a[0], a[1]), IMM(0)), a[1]));
}
static V S3128(void) { static V c; return STRC(c, "a closing '"); }
static V F_Chk_dP_dchr__lit_dfin(V a0, V a1, V a2) {
top:;
V s3125 = a2;
if ((s3125) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a0), mk_clo(L3126, 2, 1, (V[]){a1}));
} else if ((s3125) == IMM(0)) {
return F_Chk_dP_dfail(S3128());
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dchr__lit_dfin(V *a) { (void)a; return F_Chk_dP_dchr__lit_dfin(a[0], a[1], a[2]); }
static V S3131(void) { static V c; return STRC(c, "]"); }
static V L3132(V *a) {
return F_Chk_dP_dif(a[1], F_Chk_dP_dbrack_dlist(a[0], IMM(0)), F_Chk_dP_dbrack_dfirst(a[0]));
}
static V L3130(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S3131()), mk_clo(L3132, 2, 1, (V[]){a[0]}));
}
static V L3129(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3130, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dbrack(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3129, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbrack(V *a) { (void)a; return F_Chk_dP_dbrack(a[0]); }
static V S3135(void) { static V c; return STRC(c, ":"); }
static V L3136(V *a) {
return F_Chk_dP_dif(a[2], F_Chk_dP_dbrack_darr(a[1], a[0]), F_Chk_dP_dbrack_dlist(a[1], C2(1, a[0], IMM(0))));
}
static V L3134(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3135()), mk_clo(L3136, 3, 2, (V[]){a[0], a[1]}));
}
static V L3133(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3134, 3, 2, (V[]){a[1], a[0]}));
}
static V F_Chk_dP_dbrack_dfirst(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3133, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbrack_dfirst(V *a) { (void)a; return F_Chk_dP_dbrack_dfirst(a[0]); }
static V S3137(void) { static V c; return STRC(c, ","); }
static V S3139(void) { static V c; return STRC(c, "]"); }
static V L3141(V *a) {
return F_Chk_dP_dpure(F_Chk_dlist_dbuild(F_List_dappend(a[1], a[0]), a[2]));
}
static V L3140(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3141, 3, 2, (V[]){a[2], a[0]}));
}
static V L3138(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dargs(S3139()), mk_clo(L3140, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dbrack_dlist(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3137()), mk_clo(L3138, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dbrack_dlist(V *a) { (void)a; return F_Chk_dP_dbrack_dlist(a[0], a[1]); }
static V S3143(void) { static V c; return STRC(c, "Nil"); }
static V S3144(void) { static V c; return STRC(c, "Con"); }
static V F_Chk_dlist_dbuild(V a0, V a1) {
top:;
V s3142 = a0;
if ((s3142) == IMM(0)) {
return C3(15, S3143(), IMM(0), a1);
} else if (TAG(s3142) == 1) {
return C3(15, S3144(), C2(1, FLD(s3142, 0), C2(1, F_Chk_dlist_dbuild(FLD(s3142, 1), a1), IMM(0))), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlist_dbuild(V *a) { (void)a; return F_Chk_dlist_dbuild(a[0], a[1]); }
static V S3147(void) { static V c; return STRC(c, "*"); }
static V S3149(void) { static V c; return STRC(c, "^"); }
static V S3152(void) { static V c; return STRC(c, "]"); }
static V S3157(void) { static V c; return STRC(c, "Array.new"); }
static V L3156(V *a) {
return F_Chk_dP_dpure(C3(13, C3(13, C3(13, C3(4, S3157(), a[2], IMM(0)), a[1], a[2]), a[3], a[2]), a[0], a[2]));
}
static V L3155(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbrack_ddepth(a[3], a[2]), mk_clo(L3156, 4, 3, (V[]){a[4], a[0], a[1]}));
}
static V L3154(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dns(a[3], a[2]), mk_clo(L3155, 5, 4, (V[]){a[2], a[4], a[0], a[1]}));
}
static V L3153(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[4]), mk_clo(L3154, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3151(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3152()), mk_clo(L3153, 6, 5, (V[]){a[4], a[0], a[1], a[2], a[3]}));
}
static V L3150(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3151, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3148(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[3], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_deat(S3149())), mk_clo(L3150, 5, 4, (V[]){a[3], a[0], a[1], a[2]}));
}
static V L3146(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3147()), mk_clo(L3148, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3145(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3146, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V F_Chk_dP_dbrack_darr(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm(12u), mk_clo(L3145, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dbrack_darr(V *a) { (void)a; return F_Chk_dP_dbrack_darr(a[0], a[1]); }
static V F_Chk_dP_dbrack_ddepth(V a0, V a1) {
top:;
V s3158 = a0;
if ((s3158) == IMM(1)) {
return F_Chk_dP_dbrack_dlog2(F_Chk_dTm_dspan(a1), F_Chk_dnat__from__term(a1));
} else if ((s3158) == IMM(0)) {
return F_Chk_dP_dpure(a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dbrack_ddepth(V *a) { (void)a; return F_Chk_dP_dbrack_ddepth(a[0], a[1]); }
static V S3160(void) { static V c; return STRC(c, "a power of two count (^d takes a depth)"); }
static V F_Chk_dP_dbrack_dlog2(V a0, V a1) {
top:;
V s3159 = a1;
if ((s3159) == IMM(0)) {
return F_Chk_dP_dthrow(F_Chk_derr0(S3160(), IMM(0), a0));
} else if (TAG(s3159) == 1) {
return F_Chk_dP_dbrack_dlog2_dgo(a0, FLD(s3159, 0), F_Chk_dNat_dlog2__exact(FLD(s3159, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dbrack_dlog2(V *a) { (void)a; return F_Chk_dP_dbrack_dlog2(a[0], a[1]); }
static V F_Chk_dNat_dlog2__exact(V a0) {
top:;
return F_Chk_dNat_dlog2__exact_dgo(a0, 0u, 1u);
}
static V W_Chk_dNat_dlog2__exact(V *a) { (void)a; return F_Chk_dNat_dlog2__exact(a[0]); }
static V F_Chk_dNat_dlog2__exact_dgo(V a0, V a1, V a2) {
top:;
return F_Chk_dNat_dlog2__exact_dcmp(a0, a1, a2, F_Nat_dcmp(a2, a0));
}
static V W_Chk_dNat_dlog2__exact_dgo(V *a) { (void)a; return F_Chk_dNat_dlog2__exact_dgo(a[0], a[1], a[2]); }
static V W_Nat_dcmp(V *a) { (void)a; return F_Nat_dcmp(a[0], a[1]); }
static V F_Chk_dNat_dlog2__exact_dcmp(V a0, V a1, V a2, V a3) {
top:;
V s3161 = a3;
if ((s3161) == IMM(0)) {
return F_Chk_dNat_dlog2__exact_dgo(a0, nat_addk(a1, 1), F_Nat_ddouble(a2));
} else if ((s3161) == IMM(1)) {
return C1(1, a1);
} else if ((s3161) == IMM(2)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dNat_dlog2__exact_dcmp(V *a) { (void)a; return F_Chk_dNat_dlog2__exact_dcmp(a[0], a[1], a[2], a[3]); }
static V W_Nat_ddouble(V *a) { (void)a; return F_Nat_ddouble(a[0]); }
static V S3163(void) { static V c; return STRC(c, "a power of two count (^d takes a depth)"); }
static V F_Chk_dP_dbrack_dlog2_dgo(V a0, V a1, V a2) {
top:;
V s3162 = a2;
if ((s3162) == IMM(0)) {
return F_Chk_dP_dthrow(F_Chk_derr0(S3163(), IMM(0), a0));
} else if (TAG(s3162) == 1) {
return F_Chk_dP_dpure(C2(16, C1(0, FLD(s3162, 0)), a0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dbrack_dlog2_dgo(V *a) { (void)a; return F_Chk_dP_dbrack_dlog2_dgo(a[0], a[1], a[2]); }
static V S3169(void) { static V c; return STRC(c, ","); }
static V L3170(V *a) {
return F_Chk_dP_dif(a[2], F_Chk_dP_dtup_dmore(a[1], a[0]), F_Chk_dP_dtup_dend(a[0]));
}
static V L3168(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[2], F_Chk_dP_dtake(S3169()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3170, 3, 2, (V[]){a[0], a[1]}));
}
static V L3167(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_dBody_dis__reply(a[1])), mk_clo(L3168, 3, 2, (V[]){a[1], a[0]}));
}
static V L3166(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3167, 3, 2, (V[]){a[0], a[1]}));
}
static V L3165(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody(F_U32_dsub(a[1], 1u)), mk_clo(L3166, 2, 1, (V[]){a[0]}));
}
static V L3164(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcol(), mk_clo(L3165, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dtup(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3164, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dtup(V *a) { (void)a; return F_Chk_dP_dtup(a[0]); }
static V S3172(void) { static V c; return STRC(c, ":"); }
static V S3175(void) { static V c; return STRC(c, ")"); }
static V L3176(V *a) {
return F_Chk_dP_dpure(a[0]);
}
static V L3174(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3175()), mk_clo(L3176, 2, 1, (V[]){a[0]}));
}
static V L3173(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[1], F_Chk_dP_dtup_dann(a[0]), F_Chk_dP_dpure(a[0])), mk_clo(L3174, 1, 0, 0));
}
static V L3171(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3172()), mk_clo(L3173, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dtup_dend(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dflatten(a0, IMM(0)), mk_clo(L3171, 1, 0, 0));
}
static V W_Chk_dP_dtup_dend(V *a) { (void)a; return F_Chk_dP_dtup_dend(a[0]); }
static V L3177(V *a) {
return F_Chk_dP_dns(a[0], a[1]);
}
static V F_Chk_dP_dtup_dann(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3177, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dtup_dann(V *a) { (void)a; return F_Chk_dP_dtup_dann(a[0]); }
static V S3180(void) { static V c; return STRC(c, "Tuple"); }
static V L3179(V *a) {
return F_Chk_dP_dpure(C3(15, S3180(), C2(1, F_Chk_dBody_dreply__x(a[1]), C2(1, a[0], IMM(0))), a[2]));
}
static V L3178(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3179, 3, 2, (V[]){a[2], a[0]}));
}
static V F_Chk_dP_dtup_dmore(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtup(a0), mk_clo(L3178, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dtup_dmore(V *a) { (void)a; return F_Chk_dP_dtup_dmore(a[0], a[1]); }
static V F_Chk_dBody_dreply__x(V a0) {
top:;
V s3181 = a0;
if (TAG(s3181) == 2) {
return FLD(s3181, 0);
} else {
return C1(18, IMM(0));
}
}
static V W_Chk_dBody_dreply__x(V *a) { (void)a; return F_Chk_dBody_dreply__x(a[0]); }
static V F_Chk_dBody_dis__reply(V a0) {
top:;
V s3182 = a0;
if (TAG(s3182) == 2) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dBody_dis__reply(V *a) { (void)a; return F_Chk_dBody_dis__reply(a[0]); }
static V L3183(V *a) {
return C1(1, C2(0, F_Chk_dCur_dcol(F_Chk_dPS_dcur(a[0])), a[0]));
}
static V F_Chk_dP_dcol(void) {
top:;
return mk_clo(L3183, 1, 0, 0);
}
static V W_Chk_dP_dcol(V *a) { (void)a; return F_Chk_dP_dcol(); }
static V F_Chk_dCur_dcol(V a0) {
top:;
V v3184 = a0;
return FLD(v3184, 2);
}
static V W_Chk_dCur_dcol(V *a) { (void)a; return F_Chk_dCur_dcol(a[0]); }
static V S3187(void) { static V c; return STRC(c, "=="); }
static V L3188(V *a) {
return F_Chk_dP_dif(a[1], F_Chk_dP_dbrace_drfl(), F_Chk_dP_dbrace_dterm(a[0]));
}
static V L3186(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3187()), mk_clo(L3188, 2, 1, (V[]){a[0]}));
}
static V L3185(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3186, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dbrace(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3185, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbrace(V *a) { (void)a; return F_Chk_dP_dbrace(a[0]); }
static V S3191(void) { static V c; return STRC(c, "=="); }
static V S3193(void) { static V c; return STRC(c, "!="); }
static V L3194(V *a) {
return F_Chk_dP_dbrace_dgo(a[2], a[1], a[0], a[3]);
}
static V L3192(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[2], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dtake(S3193())), mk_clo(L3194, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L3190(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3191()), mk_clo(L3192, 3, 2, (V[]){a[0], a[1]}));
}
static V L3189(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3190, 3, 2, (V[]){a[1], a[0]}));
}
static V F_Chk_dP_dbrace_dterm(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3189, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbrace_dterm(V *a) { (void)a; return F_Chk_dP_dbrace_dterm(a[0]); }
static V S3198(void) { static V c; return STRC(c, ":"); }
static V S3201(void) { static V c; return STRC(c, "}"); }
static V L3202(V *a) {
return F_Chk_dP_dpure(C4(19, a[2], a[1], a[0], IMM(0)));
}
static V L3200(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3201()), mk_clo(L3202, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L3199(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3200, 3, 2, (V[]){a[0], a[1]}));
}
static V L3197(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3198()), mk_clo(L3199, 3, 2, (V[]){a[1], a[0]}));
}
static V S3206(void) { static V c; return STRC(c, ":"); }
static V S3209(void) { static V c; return STRC(c, "}"); }
static V S3212(void) { static V c; return STRC(c, "_"); }
static V S3214(void) { static V c; return STRC(c, "_"); }
static V S3215(void) { static V c; return STRC(c, "Empty"); }
static V L3213(V *a) {
return F_Chk_dP_dpure(CN(11, 6, (V[]){IMM(1), S3214(), a[5], C4(19, a[4], a[3], a[2], a[1]), C3(24, IMM(0), a[5], C3(4, S3215(), a[0], IMM(0))), a[1]}));
}
static V L3211(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dopen(S3212()), mk_clo(L3213, 6, 5, (V[]){a[0], a[4], a[1], a[2], a[3]}));
}
static V L3210(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[4]), mk_clo(L3211, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3208(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3209()), mk_clo(L3210, 6, 5, (V[]){a[0], a[4], a[1], a[2], a[3]}));
}
static V L3207(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3208, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3205(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3206()), mk_clo(L3207, 5, 4, (V[]){a[0], a[3], a[1], a[2]}));
}
static V L3204(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3205, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L3203(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(F_U32_dsub(a[2], 2u)), mk_clo(L3204, 3, 2, (V[]){a[0], a[1]}));
}
static V S3216(void) { static V c; return STRC(c, ":"); }
static V S3219(void) { static V c; return STRC(c, "}"); }
static V L3220(V *a) {
return F_Chk_dP_dpure(C3(23, a[1], a[0], IMM(0)));
}
static V L3218(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3219()), mk_clo(L3220, 3, 2, (V[]){a[1], a[0]}));
}
static V L3217(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3218, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dbrace_dgo(V a0, V a1, V a2, V a3) {
top:;
V s3195 = a2;
V s3196 = a3;
if ((s3195) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3197, 2, 1, (V[]){a1}));
} else if ((s3195) == IMM(0) && (s3196) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L3203, 3, 2, (V[]){a1, a0}));
} else if ((s3195) == IMM(0) && (s3196) == IMM(0)) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3216()), mk_clo(L3217, 2, 1, (V[]){a1}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dbrace_dgo(V *a) { (void)a; return F_Chk_dP_dbrace_dgo(a[0], a[1], a[2], a[3]); }
static V S3221(void) { static V c; return STRC(c, "}"); }
static V L3222(V *a) {
return F_Chk_dP_dpure(C1(20, IMM(0)));
}
static V F_Chk_dP_dbrace_drfl(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_deat(S3221()), mk_clo(L3222, 1, 0, 0));
}
static V W_Chk_dP_dbrace_drfl(V *a) { (void)a; return F_Chk_dP_dbrace_drfl(); }
static V S3226(void) { static V c; return STRC(c, "@"); }
static V L3228(V *a) {
return F_Chk_dP_drwt_dgo(a[1], a[0], a[2]);
}
static V L3227(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_drwt_dname(a[1], a[2]), mk_clo(L3228, 3, 2, (V[]){a[1], a[0]}));
}
static V L3225(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3226()), mk_clo(L3227, 3, 2, (V[]){a[0], a[1]}));
}
static V L3224(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3225, 3, 2, (V[]){a[0], a[1]}));
}
static V L3223(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3224, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_drwt(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3223, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_drwt(V *a) { (void)a; return F_Chk_dP_drwt(a[0]); }
static V S3231(void) { static V c; return STRC(c, ":"); }
static V S3235(void) { static V c; return STRC(c, "_"); }
static V S3241(void) { static V c; return STRC(c, ";"); }
static V S3245(void) { static V c; return STRC(c, "_"); }
static V L3244(V *a) {
return F_Chk_dP_dpure(C4(21, a[6], CN(12, 5, (V[]){S3245(), a[5], C3(24, IMM(0), a[5], CN(12, 5, (V[]){a[4], a[3], C3(24, IMM(0), a[3], a[2]), F_Chk_dTm_dspan(a[1]), IMM(3)})), a[7], IMM(3)}), a[0], a[7]));
}
static V L3243(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[6]), mk_clo(L3244, 8, 7, (V[]){a[7], a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3242(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dblock(), mk_clo(L3243, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3240(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3241()), mk_clo(L3242, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3239(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3240, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3238(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[6]), mk_clo(L3239, 8, 7, (V[]){a[0], a[7], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3237(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3238, 8, 7, (V[]){a[0], a[6], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3236(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dopen(a[5]), mk_clo(L3237, 7, 6, (V[]){a[0], a[5], a[1], a[2], a[3], a[4]}));
}
static V L3234(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpush__scope(C2(0, S3235(), a[5])), mk_clo(L3236, 7, 6, (V[]){a[0], a[5], a[1], a[2], a[3], a[4]}));
}
static V L3233(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dfresh__id(), mk_clo(L3234, 6, 5, (V[]){a[0], a[1], a[2], a[4], a[3]}));
}
static V L3232(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3233, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Chk_dP_drwt_dgo(V a0, V a1, V a2) {
top:;
V v3229 = a2;
V v3230 = FLD(v3229, 0);
return F_Chk_dP_dbind(F_Chk_dP_deat(S3231()), mk_clo(L3232, 5, 4, (V[]){a1, FLD(v3229, 1), a0, v3230}));
}
static V W_Chk_dP_drwt_dgo(V *a) { (void)a; return F_Chk_dP_drwt_dgo(a[0], a[1], a[2]); }
static V L3246(V *a) {
return C1(1, C2(0, IMM(0), F_Chk_dPS_dpush(a[1], a[0])));
}
static V F_Chk_dP_dpush__scope(V a0) {
top:;
return mk_clo(L3246, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dpush__scope(V *a) { (void)a; return F_Chk_dP_dpush__scope(a[0]); }
static V S3248(void) { static V c; return STRC(c, "a name before @ (a rewrite binder is one name: %e@E : P)"); }
static V S3249(void) { static V c; return STRC(c, ""); }
static V F_Chk_dP_drwt_dname(V a0, V a1) {
top:;
V s3247 = a1;
if ((s3247) == IMM(1)) {
return F_Chk_dP_dif(F_Chk_dTm_dis__var(a0), F_Chk_dP_drwt_dnamed(a0), F_Chk_dP_dfail(S3248()));
} else if ((s3247) == IMM(0)) {
return F_Chk_dP_dpure(C2(0, S3249(), a0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_drwt_dname(V *a) { (void)a; return F_Chk_dP_drwt_dname(a[0], a[1]); }
static V L3250(V *a) {
return F_Chk_dP_dpure(C2(0, F_Chk_dTm_dname(a[0]), a[1]));
}
static V F_Chk_dP_drwt_dnamed(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3250, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_drwt_dnamed(V *a) { (void)a; return F_Chk_dP_drwt_dnamed(a[0]); }
static V S3252(void) { static V c; return STRC(c, "{"); }
static V L3255(V *a) {
return F_Chk_dP_dpure(F_Chk_dP_darms_dfin(a[0], a[1]));
}
static V L3254(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[0]), mk_clo(L3255, 2, 1, (V[]){a[1]}));
}
static V L3253(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_darms_dgo(IMM(0)), mk_clo(L3254, 2, 1, (V[]){a[0]}));
}
static V L3251(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3252()), mk_clo(L3253, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_darms(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3251, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_darms(V *a) { (void)a; return F_Chk_dP_darms(a[0]); }
static V F_Chk_dP_darms_dfin(V a0, V a1) {
top:;
V v3256 = a0;
return F_Chk_darms_dbuild(FLD(v3256, 0), F_Chk_dTm_dspanned(FLD(v3256, 1), a1), a1);
}
static V W_Chk_dP_darms_dfin(V *a) { (void)a; return F_Chk_dP_darms_dfin(a[0], a[1]); }
static V F_Chk_darms_dbuild(V a0, V a1, V a2) {
top:;
V s3257 = a0;
if ((s3257) == IMM(0)) {
return a1;
} else if (TAG(s3257) == 1 && TAG(FLD(s3257, 0)) == 15 && TAG(FLD(FLD(s3257, 0), 1)) == 1 && (FLD(FLD(FLD(s3257, 0), 1), 1)) == IMM(0)) {
return C4(17, FLD(FLD(s3257, 0), 0), FLD(FLD(FLD(s3257, 0), 1), 0), F_Chk_darms_dbuild(FLD(s3257, 1), a1, a2), a2);
} else if (TAG(s3257) == 1) {
{ V t0 = FLD(s3257, 1); V t1 = a1; V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_darms_dbuild(V *a) { (void)a; return F_Chk_darms_dbuild(a[0], a[1], a[2]); }
static V S3259(void) { static V c; return STRC(c, "}"); }
static V L3260(V *a) {
return F_Chk_dP_dif(a[1], F_Chk_dP_dpure(C2(0, a[0], C1(18, IMM(0)))), F_Chk_dP_darms_ditem(a[0]));
}
static V L3258(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3259()), mk_clo(L3260, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_darms_dgo(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3258, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_darms_dgo(V *a) { (void)a; return F_Chk_dP_darms_dgo(a[0]); }
static V S3264(void) { static V c; return STRC(c, ":"); }
static V L3265(V *a) {
return F_Chk_dP_darms_dmore(a[1], a[0], a[2]);
}
static V L3263(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[2], F_Chk_dP_dtake(S3264()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3265, 3, 2, (V[]){a[0], a[1]}));
}
static V L3262(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Bool_dor(F_Chk_dTm_dis__var(a[1]), F_Chk_dTm_dis__ref(a[1]))), mk_clo(L3263, 3, 2, (V[]){a[1], a[0]}));
}
static V L3261(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3262, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_darms_ditem(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3261, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_darms_ditem(V *a) { (void)a; return F_Chk_dP_darms_ditem(a[0]); }
static V S3270(void) { static V c; return STRC(c, ";"); }
static V L3271(V *a) {
return F_Chk_dP_darms_dgo(F_List_dappend(a[3], C2(1, C3(15, a[2], C2(1, a[1], IMM(0)), F_Chk_dTm_dspan(a[0])), IMM(0))));
}
static V L3269(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3270()), mk_clo(L3271, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3268(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3269, 5, 4, (V[]){a[0], a[3], a[1], a[2]}));
}
static V L3267(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3268, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V S3273(void) { static V c; return STRC(c, ";"); }
static V S3275(void) { static V c; return STRC(c, "}"); }
static V L3276(V *a) {
return F_Chk_dP_dpure(C2(0, a[1], a[0]));
}
static V L3274(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3275()), mk_clo(L3276, 3, 2, (V[]){a[0], a[1]}));
}
static V L3272(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3273()), mk_clo(L3274, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_darms_dmore(V a0, V a1, V a2) {
top:;
V s3266 = a2;
if ((s3266) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(F_Chk_dTm_dname(a1)), mk_clo(L3267, 3, 2, (V[]){a1, a0}));
} else if ((s3266) == IMM(0)) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3272, 3, 2, (V[]){a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_darms_dmore(V *a) { (void)a; return F_Chk_dP_darms_dmore(a[0], a[1], a[2]); }
static V L3281(V *a) {
return F_Chk_dP_dplus_dgo(a[2], a[1], a[0], F_Chk_dTld_dadt__ng(F_Chk_dbook__tld(a[3], a[1])));
}
static V L3280(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3281, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L3279(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dplus_dkey(a[0]), mk_clo(L3280, 3, 2, (V[]){a[1], a[0]}));
}
static V L3278(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[0]), mk_clo(L3279, 2, 1, (V[]){a[1]}));
}
static V L3277(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm(12u), mk_clo(L3278, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dplus(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3277, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dplus(V *a) { (void)a; return F_Chk_dP_dplus(a[0]); }
static V F_Chk_dTld_dadt__ng(V a0) {
top:;
V s3282 = a0;
if (TAG(s3282) == 1 && TAG(FLD(s3282, 0)) == 1) {
return C1(1, C2(0, FLD(FLD(s3282, 0), 0), FLD(FLD(s3282, 0), 1)));
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dadt__ng(V *a) { (void)a; return F_Chk_dTld_dadt__ng(a[0]); }
static V S3284(void) { static V c; return STRC(c, "a quantified datatype after + (+D<..> sets D's leading quantities to &2)"); }
static V F_Chk_dP_dplus_dgo(V a0, V a1, V a2, V a3) {
top:;
V s3283 = a3;
if ((s3283) == IMM(0)) {
return F_Chk_dP_dif(F_Chk_dTm_dis__var(a0), F_Chk_dP_dpure(C2(2, F_Chk_dTm_dname(a0), a2)), F_Chk_dP_dfail(S3284()));
} else if (TAG(s3283) == 1) {
return F_Chk_dP_dplus_dadt(a0, a1, a2, FLD(s3283, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dplus_dgo(V *a) { (void)a; return F_Chk_dP_dplus_dgo(a[0], a[1], a[2], a[3]); }
static V S3288(void) { static V c; return STRC(c, "a quantified datatype after + (+D<..> sets D's leading quantities to &2)"); }
static V F_Chk_dP_dplus_dadt(V a0, V a1, V a2, V a3) {
top:;
V v3285 = a3;
V v3286 = FLD(v3285, 1);
V v3287 = FLD(v3285, 0);
return F_Chk_dP_dif(F_Bool_dor(F_Nat_dis__eq(v3286, 0u), F_Bool_dand(F_Nat_dis__lt(v3286, v3287), F_Bool_dnot(F_Chk_dTm_dis__adt(a0)))), F_Chk_dP_dfail(S3288()), F_Chk_dP_dpure(C4(14, a1, F_Chk_dplus_dargs(F_Chk_dP_dplus_dxs(a0, v3287, a2), v3286), a2, IMM(0))));
}
static V W_Chk_dP_dplus_dadt(V *a) { (void)a; return F_Chk_dP_dplus_dadt(a[0], a[1], a[2], a[3]); }
static V F_Chk_dP_dplus_dxs(V a0, V a1, V a2) {
top:;
V s3289 = a0;
if (TAG(s3289) == 14) {
return FLD(s3289, 1);
} else {
return F_Chk_dList_drepeat__tm(C2(9, IMM(1), a2), a1);
}
}
static V W_Chk_dP_dplus_dxs(V *a) { (void)a; return F_Chk_dP_dplus_dxs(a[0], a[1], a[2]); }
static V F_Chk_dplus_dargs(V a0, V a1) {
top:;
V s3290 = a0;
V s3291 = a1;
if (TAG(s3290) == 1 && nat_ge(s3291, 1)) {
return C2(1, C2(9, IMM(2), F_Chk_dTm_dspan(FLD(s3290, 0))), F_Chk_dplus_dargs(FLD(s3290, 1), nat_subk(s3291, 1)));
} else {
return s3290;
}
}
static V W_Chk_dplus_dargs(V *a) { (void)a; return F_Chk_dplus_dargs(a[0], a[1]); }
static V F_Chk_dTm_dis__adt(V a0) {
top:;
V s3292 = a0;
if (TAG(s3292) == 14) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__adt(V *a) { (void)a; return F_Chk_dTm_dis__adt(a[0]); }
static V S3294(void) { static V c; return STRC(c, ""); }
static V F_Chk_dP_dplus_dkey(V a0) {
top:;
V s3293 = a0;
if (TAG(s3293) == 14) {
return F_Chk_dP_dpure(FLD(s3293, 0));
} else {
return F_Chk_dP_dif(F_Bool_dor(F_Chk_dTm_dis__var(s3293), F_Chk_dTm_dis__ref(s3293)), F_Chk_dP_dreso(F_Chk_dTm_dname(s3293)), F_Chk_dP_dpure(S3294()));
}
}
static V W_Chk_dP_dplus_dkey(V *a) { (void)a; return F_Chk_dP_dplus_dkey(a[0]); }
static V F_Chk_dP_damp(V a0, V a1) {
top:;
return F_Chk_dP_damp_dgo(a1, F_Chk_damp_dcode(a0));
}
static V W_Chk_dP_damp(V *a) { (void)a; return F_Chk_dP_damp(a[0], a[1]); }
static V F_Chk_damp_dcode(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__eq(a0, 48u), 1u, F_Bool_dpick(F_U32_dis__eq(a0, 49u), 2u, F_Bool_dpick(F_U32_dis__eq(a0, 50u), 3u, 0u)));
}
static V W_Chk_damp_dcode(V *a) { (void)a; return F_Chk_damp_dcode(a[0]); }
static V L3298(V *a) {
return F_Chk_dP_dpure(C2(9, F_Chk_damp_dq(a[0]), a[1]));
}
static V L3297(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3298, 2, 1, (V[]){a[0]}));
}
static V L3296(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3297, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_damp_dgo(V a0, V a1) {
top:;
V s3295 = a1;
if ((s3295) == 0) {
return F_Chk_dP_dall(IMM(1));
} else if (nat_ge(s3295, 1)) {
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3296, 3, 2, (V[]){nat_subk(s3295, 1), a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_damp_dgo(V *a) { (void)a; return F_Chk_dP_damp_dgo(a[0], a[1]); }
static V F_Chk_damp_dq(V a0) {
top:;
V s3299 = a0;
if ((s3299) == 0) {
return IMM(0);
} else if ((s3299) == 1) {
return IMM(1);
} else if (nat_ge(s3299, 2)) {
return IMM(2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_damp_dq(V *a) { (void)a; return F_Chk_damp_dq(a[0]); }
static V S3304(void) { static V c; return STRC(c, ":"); }
static V S3307(void) { static V c; return STRC(c, "->"); }
static V L3313(V *a) {
return F_Chk_dP_dpure(F_Chk_dall_dbuild(a[5], a[4], a[3], a[2], a[1], a[0], a[6]));
}
static V L3312(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[6]), mk_clo(L3313, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3311(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[6]), mk_clo(L3312, 8, 7, (V[]){a[7], a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3310(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3311, 8, 7, (V[]){a[0], a[6], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3309(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dopen(a[4]), mk_clo(L3310, 7, 6, (V[]){a[0], a[4], a[1], a[2], a[3], a[5]}));
}
static V L3308(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3309, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L3306(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3307()), mk_clo(L3308, 6, 5, (V[]){a[4], a[0], a[1], a[2], a[3]}));
}
static V L3305(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm(1u), mk_clo(L3306, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3303(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3304()), mk_clo(L3305, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3302(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3303, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L3301(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[1], F_Chk_dP_dpure(IMM(1)), F_Chk_dP_dquant()), mk_clo(L3302, 3, 2, (V[]){a[1], a[0]}));
}
static V L3300(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3301, 3, 2, (V[]){a[1], a[0]}));
}
static V F_Chk_dP_dall(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L3300, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dall(V *a) { (void)a; return F_Chk_dP_dall(a[0]); }
static V S3315(void) { static V c; return STRC(c, "Exists"); }
static V F_Chk_dall_dbuild(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s3314 = a0;
if ((s3314) == IMM(1)) {
return C3(13, C3(13, C3(4, S3315(), a6, IMM(0)), a4, a6), CN(12, 5, (V[]){a2, a3, C3(24, IMM(0), a3, a5), a6, IMM(3)}), a6);
} else if ((s3314) == IMM(0)) {
return CN(11, 6, (V[]){a1, a2, a3, a4, C3(24, IMM(0), a3, a5), IMM(0)});
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dall_dbuild(V *a) { (void)a; return F_Chk_dall_dbuild(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S3317(void) { static V c; return STRC(c, "-"); }
static V S3319(void) { static V c; return STRC(c, "+"); }
static V L3320(V *a) {
return F_Chk_dP_dpure(F_Bool_dpick(a[0], IMM(0), F_Bool_dpick(a[1], IMM(2), IMM(1))));
}
static V L3318(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[0], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dtake(S3319())), mk_clo(L3320, 2, 1, (V[]){a[0]}));
}
static V L3316(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3317()), mk_clo(L3318, 1, 0, 0));
}
static V F_Chk_dP_dquant(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3316, 1, 0, 0));
}
static V W_Chk_dP_dquant(V *a) { (void)a; return F_Chk_dP_dquant(); }
static V L3326(V *a) {
return F_Chk_dP_dnum_dgo(a[1], a[0], a[2], F_Chk_dnum_dkind(a[2]));
}
static V L3325(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek__rest(), mk_clo(L3326, 3, 2, (V[]){a[0], a[1]}));
}
static V L3324(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dsteps(a[1]), mk_clo(L3325, 3, 2, (V[]){a[2], a[0]}));
}
static V L3323(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_String_dtake(a[1], a[2])), mk_clo(L3324, 3, 2, (V[]){a[0], a[2]}));
}
static V L3322(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_ddigits_dspan(a[1])), mk_clo(L3323, 3, 2, (V[]){a[0], a[1]}));
}
static V L3321(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek__rest(), mk_clo(L3322, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dnum(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L3321, 1, 0, 0));
}
static V W_Chk_dP_dnum(V *a) { (void)a; return F_Chk_dP_dnum(); }
static V F_Chk_dnum_dkind(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__eq(F_Chk_dStr_dfirst(a0), 110u), 1u, F_Bool_dpick(F_Bool_dand(F_U32_dis__eq(F_Chk_dStr_dfirst(a0), 46u), F_Chk_dis__digit(F_Chk_dStr_dsecond(a0))), 2u, 0u));
}
static V W_Chk_dnum_dkind(V *a) { (void)a; return F_Chk_dnum_dkind(a[0]); }
static V S3331(void) { static V c; return STRC(c, "a numeric literal (NUMBER is U32, NUMBER n is Nat)"); }
static V S3332(void) { static V c; return STRC(c, "a u32 literal up to 4294967295 (got "); }
static V S3333(void) { static V c; return STRC(c, ")"); }
static V L3330(V *a) {
return F_Chk_dP_dif(F_Chk_dis__name(a[2]), F_Chk_dP_dfail(S3331()), F_Chk_dP_dif(F_Nat_dis__gt(a[1], 4294967295u), F_Chk_dP_dfail(F_String_dappend(S3332(), F_String_dappend(a[0], S3333()))), F_Chk_dP_dpure(F_Chk_du32__to__term(F_U32_dfrom__nat(a[1]), a[3]))));
}
static V L3329(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[2]), mk_clo(L3330, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V L3334(V *a) {
return F_Chk_dP_dnat(a[1], a[0], F_Chk_ddigits_dval(a[0], F_String_dlength(a[0]), 0u));
}
static V F_Chk_dP_dnum_dgo(V a0, V a1, V a2, V a3) {
top:;
V s3327 = a3;
if ((s3327) == 0) {
V v3328 = F_Chk_ddigits_dval(a1, F_String_dlength(a1), 0u);
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3329, 4, 3, (V[]){a1, v3328, a0}));
} else if ((s3327) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3334, 3, 2, (V[]){a1, a0}));
} else if (nat_ge(s3327, 2)) {
return F_Chk_dP_dflt(a0, a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dnum_dgo(V *a) { (void)a; return F_Chk_dP_dnum_dgo(a[0], a[1], a[2], a[3]); }
static V L3337(V *a) {
return F_Chk_dP_dflt_dgo(F_String_dappend(a[1], a[0]), F_F32_dread(F_String_dappend(a[1], a[0])), a[2]);
}
static V L3336(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[2]), mk_clo(L3337, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dflt(V a0, V a1, V a2) {
top:;
V v3335 = F_Chk_dflt_dtext(a2);
return F_Chk_dP_dbind(F_Chk_dP_dsteps(F_String_dlength(v3335)), mk_clo(L3336, 4, 3, (V[]){v3335, a1, a0}));
}
static V W_Chk_dP_dflt(V *a) { (void)a; return F_Chk_dP_dflt(a[0], a[1], a[2]); }
static V W_F32_dread(V *a) { (void)a; return F_F32_dread(a[0]); }
static V S3339(void) { static V c; return STRC(c, "F32"); }
static V S3340(void) { static V c; return STRC(c, "a float literal with a finite f32 value (got "); }
static V S3341(void) { static V c; return STRC(c, ")"); }
static V S3342(void) { static V c; return STRC(c, "a float literal with a finite f32 value (got "); }
static V S3343(void) { static V c; return STRC(c, ")"); }
static V F_Chk_dP_dflt_dgo(V a0, V a1, V a2) {
top:;
V s3338 = a1;
if (TAG(s3338) == 1) {
return F_Chk_dP_dif(F_Chk_dF32_dis__finite(FLD(s3338, 0)), F_Chk_dP_dpure(C3(15, S3339(), C2(1, F_Chk_dword__to__term(F_F32_dbits(FLD(s3338, 0)), a2), IMM(0)), a2)), F_Chk_dP_dfail(F_String_dappend(S3340(), F_String_dappend(a0, S3341()))));
} else if ((s3338) == IMM(0)) {
return F_Chk_dP_dfail(F_String_dappend(S3342(), F_String_dappend(a0, S3343())));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dflt_dgo(V *a) { (void)a; return F_Chk_dP_dflt_dgo(a[0], a[1], a[2]); }
static V W_F32_dbits(V *a) { (void)a; return F_F32_dbits(a[0]); }
static V F_Chk_dF32_dis__finite(V a0) {
top:;
V v3344 = F_F32_dbits(a0);
return F_Bool_dnot(F_U32_dis__eq(F_U32_dand(v3344, 2139095040u), 2139095040u));
}
static V W_Chk_dF32_dis__finite(V *a) { (void)a; return F_Chk_dF32_dis__finite(a[0]); }
static V L3345(V *a) {
return C1(1, C2(0, IMM(0), F_Chk_dPS_dset__cur(a[1], F_Chk_dCur_dsteps(F_Chk_dPS_dcur(a[1]), a[0]))));
}
static V F_Chk_dP_dsteps(V a0) {
top:;
return mk_clo(L3345, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dsteps(V *a) { (void)a; return F_Chk_dP_dsteps(a[0]); }
static V F_Chk_dflt_dtext(V a0) {
top:;
V v3346 = F_Chk_ddigits_dspan(F_String_ddrop(a0, 1u));
V v3347 = F_String_ddrop(a0, nat_addk(v3346, 1));
return F_String_dappend(F_String_dtake(a0, nat_addk(v3346, 1)), F_Chk_dflt_dexp(v3347));
}
static V W_Chk_dflt_dtext(V *a) { (void)a; return F_Chk_dflt_dtext(a[0]); }
static V S3351(void) { static V c; return STRC(c, ""); }
static V F_Chk_dflt_dexp(V a0) {
top:;
V v3348 = F_Chk_dStr_dfirst(a0);
V v3349 = F_Bool_dor(F_U32_dis__eq(F_Chk_dStr_dsecond(a0), 43u), F_U32_dis__eq(F_Chk_dStr_dsecond(a0), 45u));
V v3350 = F_Chk_ddigits_dspan(F_String_ddrop(a0, F_Bool_dpick(v3349, 2u, 1u)));
return F_Bool_dpick(F_Bool_dand(F_Bool_dor(F_U32_dis__eq(v3348, 101u), F_U32_dis__eq(v3348, 69u)), F_Nat_dis__gt(v3350, 0u)), F_String_dtake(a0, F_Nat_dadd(v3350, F_Bool_dpick(v3349, 2u, 1u))), S3351());
}
static V W_Chk_dflt_dexp(V *a) { (void)a; return F_Chk_dflt_dexp(a[0]); }
static V F_Chk_ddigits_dspan(V a0) {
top:;
V s3352 = a0;
if ((s3352) == IMM(0)) {
return 0u;
} else if (TAG(s3352) == 1) {
return F_Bool_dpick(F_Chk_dis__digit(FLD(s3352, 0)), nat_addk(F_Chk_ddigits_dspan(FLD(s3352, 1)), 1), 0u);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_ddigits_dspan(V *a) { (void)a; return F_Chk_ddigits_dspan(a[0]); }
static V F_Chk_ddigits_dval(V a0, V a1, V a2) {
top:;
V s3353 = a0;
V s3354 = a1;
if (TAG(s3353) == 1 && nat_ge(s3354, 1)) {
{ V t0 = FLD(s3353, 1); V t1 = nat_subk(s3354, 1); V t2 = F_Nat_dadd(F_Nat_dmul(a2, 10u), F_U32_dto__nat(F_U32_dsub(FLD(s3353, 0), 48u))); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else {
return a2;
}
}
static V W_Chk_ddigits_dval(V *a) { (void)a; return F_Chk_ddigits_dval(a[0], a[1], a[2]); }
static V W_Nat_dmul(V *a) { (void)a; return F_Nat_dmul(a[0], a[1]); }
static V S3355(void) { static V c; return STRC(c, "a nat literal up to 4294967295n (got "); }
static V S3356(void) { static V c; return STRC(c, "n)"); }
static V F_Chk_dP_dnat(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dif(F_Nat_dis__gt(a2, 4294967295u), F_Chk_dP_dfail(F_String_dappend(S3355(), F_String_dappend(a1, S3356()))), F_Chk_dP_dnat_dgo(a0, a2));
}
static V W_Chk_dP_dnat(V *a) { (void)a; return F_Chk_dP_dnat(a[0], a[1], a[2]); }
static V S3357(void) { static V c; return STRC(c, "+"); }
static V L3358(V *a) {
return F_Chk_dP_dif(a[2], F_Chk_dP_dnat_dplus(a[1], a[0]), F_Chk_dP_dnat_dlit(a[1], a[0]));
}
static V F_Chk_dP_dnat_dgo(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3357()), mk_clo(L3358, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dnat_dgo(V *a) { (void)a; return F_Chk_dP_dnat_dgo(a[0], a[1]); }
static V S3361(void) { static V c; return STRC(c, "a nat literal (NUMBER n)"); }
static V L3360(V *a) {
return F_Chk_dP_dif(F_Chk_dis__name(a[1]), F_Chk_dP_dfail(S3361()), F_Chk_dP_dpure(C2(16, C1(0, a[0]), a[2])));
}
static V L3359(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3360, 3, 2, (V[]){a[0], a[2]}));
}
static V F_Chk_dP_dnat_dlit(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3359, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dnat_dlit(V *a) { (void)a; return F_Chk_dP_dnat_dlit(a[0], a[1]); }
static V L3363(V *a) {
return F_Chk_dP_dpure(F_Chk_dnat_dplus(a[1], a[0], a[2]));
}
static V L3362(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3363, 3, 2, (V[]){a[2], a[0]}));
}
static V F_Chk_dP_dnat_dplus(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3362, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dnat_dplus(V *a) { (void)a; return F_Chk_dP_dnat_dplus(a[0], a[1]); }
static V F_Chk_dnat_dplus(V a0, V a1, V a2) {
top:;
V s3364 = a1;
if (TAG(s3364) == 16 && TAG(FLD(s3364, 0)) == 0) {
return F_Bool_dpick(F_Nat_dis__le(F_Nat_dadd(a0, FLD(FLD(s3364, 0), 0)), 4294967295u), C2(16, C1(0, F_Nat_dadd(a0, FLD(FLD(s3364, 0), 0))), a2), F_Chk_dnat_dplus_dbig(a0, C2(16, C1(0, FLD(FLD(s3364, 0), 0)), FLD(s3364, 1)), a2));
} else {
return F_Chk_dnat_dplus_dbig(a0, s3364, a2);
}
}
static V W_Chk_dnat_dplus(V *a) { (void)a; return F_Chk_dnat_dplus(a[0], a[1], a[2]); }
static V S3365(void) { static V c; return STRC(c, "Nat.add"); }
static V F_Chk_dnat_dplus_dbig(V a0, V a1, V a2) {
top:;
return F_Bool_dpick(F_Nat_dis__gt(a0, 256u), C3(13, C3(13, C3(4, S3365(), a2, IMM(0)), C2(16, C1(0, a0), a2), a2), a1, a2), F_Chk_dnat_dsuccs(a0, a1, a2));
}
static V W_Chk_dnat_dplus_dbig(V *a) { (void)a; return F_Chk_dnat_dplus_dbig(a[0], a[1], a[2]); }
static V S3367(void) { static V c; return STRC(c, "Succ"); }
static V F_Chk_dnat_dsuccs(V a0, V a1, V a2) {
top:;
V s3366 = a0;
if ((s3366) == 0) {
return a1;
} else if (nat_ge(s3366, 1)) {
{ V t0 = nat_subk(s3366, 1); V t1 = C3(15, S3367(), C2(1, a1, IMM(0)), a2); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dnat_dsuccs(V *a) { (void)a; return F_Chk_dnat_dsuccs(a[0], a[1], a[2]); }
static V S3368(void) { static V c; return STRC(c, "Type"); }
static V S3369(void) { static V c; return STRC(c, "Data"); }
static V S3370(void) { static V c; return STRC(c, "Quant"); }
static V S3371(void) { static V c; return STRC(c, "Kind"); }
static V S3372(void) { static V c; return STRC(c, "do"); }
static V S3373(void) { static V c; return STRC(c, "match"); }
static V S3374(void) { static V c; return STRC(c, "case"); }
static V S3375(void) { static V c; return STRC(c, "return"); }
static V F_Chk_dP_dbase_dword(V a0, V a1) {
top:;
return F_Chk_dP_dbase_dword_dgo(a0, a1, F_Chk_dStr_dindex(C2(1, S3368(), C2(1, S3369(), C2(1, S3370(), C2(1, S3371(), C2(1, S3372(), C2(1, S3373(), C2(1, S3374(), C2(1, S3375(), IMM(0))))))))), a0, 0u));
}
static V W_Chk_dP_dbase_dword(V *a) { (void)a; return F_Chk_dP_dbase_dword(a[0], a[1]); }
static V L3377(V *a) {
return F_Chk_dP_dpure(C2(7, C2(9, IMM(1), a[0]), a[0]));
}
static V L3378(V *a) {
return F_Chk_dP_dpure(C2(7, C2(9, IMM(2), a[0]), a[0]));
}
static V L3379(V *a) {
return F_Chk_dP_dpure(C1(8, a[0]));
}
static V S3380(void) { static V c; return STRC(c, "("); }
static V S3383(void) { static V c; return STRC(c, ")"); }
static V L3385(V *a) {
return F_Chk_dP_dpure(C2(7, a[0], a[1]));
}
static V L3384(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3385, 2, 1, (V[]){a[0]}));
}
static V L3382(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3383()), mk_clo(L3384, 3, 2, (V[]){a[1], a[0]}));
}
static V L3381(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3382, 2, 1, (V[]){a[0]}));
}
static V S3386(void) { static V c; return STRC(c, "a term (a match heads a def body, not a term)"); }
static V S3387(void) { static V c; return STRC(c, "a match heading this case (this case is orphaned)"); }
static V S3388(void) { static V c; return STRC(c, "a do-block heading this return"); }
static V S3389(void) { static V c; return STRC(c, "a term (the keyword '"); }
static V S3390(void) { static V c; return STRC(c, "' cannot head one)"); }
static V F_Chk_dP_dbase_dword_dgo(V a0, V a1, V a2) {
top:;
V s3376 = a2;
if (TAG(s3376) == 1 && (FLD(s3376, 0)) == 0) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a1), mk_clo(L3377, 1, 0, 0));
} else if (TAG(s3376) == 1 && (FLD(s3376, 0)) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a1), mk_clo(L3378, 1, 0, 0));
} else if (TAG(s3376) == 1 && (FLD(s3376, 0)) == 2) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a1), mk_clo(L3379, 1, 0, 0));
} else if (TAG(s3376) == 1 && (FLD(s3376, 0)) == 3) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3380()), mk_clo(L3381, 2, 1, (V[]){a1}));
} else if (TAG(s3376) == 1 && (FLD(s3376, 0)) == 4) {
return F_Chk_dP_ddo(a1);
} else if (TAG(s3376) == 1 && (FLD(s3376, 0)) == 5) {
return F_Chk_dP_dfail(S3386());
} else if (TAG(s3376) == 1 && (FLD(s3376, 0)) == 6) {
return F_Chk_dP_dfail(S3387());
} else if (TAG(s3376) == 1 && (FLD(s3376, 0)) == 7) {
return F_Chk_dP_dfail(S3388());
} else {
return F_Chk_dP_dif(F_Chk_dStr_dhas(F_Chk_dKEYWORDS(), a0), F_Chk_dP_dfail(F_String_dappend(S3389(), F_String_dappend(a0, S3390()))), F_Chk_dP_dbase_dname(a0, a1));
}
}
static V W_Chk_dP_dbase_dword_dgo(V *a) { (void)a; return F_Chk_dP_dbase_dword_dgo(a[0], a[1], a[2]); }
static V S3391(void) { static V c; return STRC(c, "{"); }
static V L3392(V *a) {
return F_Chk_dP_dif(a[2], F_Chk_dP_dbase_dctor(a[1], a[0]), F_Chk_dP_dbase_dvar(a[1], a[0]));
}
static V F_Chk_dP_dbase_dname(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dat(S3391()), mk_clo(L3392, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dbase_dname(V *a) { (void)a; return F_Chk_dP_dbase_dname(a[0], a[1]); }
static V L3393(V *a) {
return F_Chk_dP_dvar(a[0], a[1]);
}
static V F_Chk_dP_dbase_dvar(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dspan(a1), mk_clo(L3393, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbase_dvar(V *a) { (void)a; return F_Chk_dP_dbase_dvar(a[0], a[1]); }
static V L3394(V *a) {
return F_Chk_dP_dvar_dfound(a[1], a[2], a[0]);
}
static V F_Chk_dP_dvar(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dlookup(a0), mk_clo(L3394, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dvar(V *a) { (void)a; return F_Chk_dP_dvar(a[0], a[1]); }
static V L3396(V *a) {
return F_Chk_dP_dvar_dfree(a[1], a[2], a[0], F_Chk_dStr_dhas__dot(a[1]));
}
static V F_Chk_dP_dvar_dfound(V a0, V a1, V a2) {
top:;
V s3395 = a1;
if (TAG(s3395) == 1) {
return F_Chk_dP_dpure(C3(0, a0, FLD(s3395, 0), a2));
} else if ((s3395) == IMM(0)) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(a0), mk_clo(L3396, 3, 2, (V[]){a2, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dvar_dfound(V *a) { (void)a; return F_Chk_dP_dvar_dfound(a[0], a[1], a[2]); }
static V F_Chk_dStr_dhas__dot(V a0) {
top:;
V s3397 = a0;
if ((s3397) == IMM(0)) {
return IMM(0);
} else if (TAG(s3397) == 1) {
return F_Bool_dor(F_U32_dis__eq(FLD(s3397, 0), 46u), F_Chk_dStr_dhas__dot(FLD(s3397, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dhas__dot(V *a) { (void)a; return F_Chk_dStr_dhas__dot(a[0]); }
static V L3399(V *a) {
return F_Chk_dP_dpure(C4(3, a[2], a[3], a[1], C3(4, a[0], a[1], IMM(0))));
}
static V F_Chk_dP_dvar_dfree(V a0, V a1, V a2, V a3) {
top:;
V s3398 = a3;
if ((s3398) == IMM(1)) {
return F_Chk_dP_dpure(C3(4, a1, a2, IMM(0)));
} else if ((s3398) == IMM(0)) {
return F_Chk_dP_dbind(F_Chk_dP_dfresh__id(), mk_clo(L3399, 4, 3, (V[]){a1, a2, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dvar_dfree(V *a) { (void)a; return F_Chk_dP_dvar_dfree(a[0], a[1], a[2], a[3]); }
static V S3401(void) { static V c; return STRC(c, "}"); }
static V L3404(V *a) {
return F_Chk_dP_dpure(C3(15, a[1], a[0], a[2]));
}
static V L3403(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3404, 3, 2, (V[]){a[0], a[2]}));
}
static V L3402(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(a[1]), mk_clo(L3403, 3, 2, (V[]){a[2], a[0]}));
}
static V L3400(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dargs(S3401()), mk_clo(L3402, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dbase_dctor(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3400, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dbase_dctor(V *a) { (void)a; return F_Chk_dP_dbase_dctor(a[0], a[1]); }
static V S3406(void) { static V c; return STRC(c, "<"); }
static V S3408(void) { static V c; return STRC(c, ">"); }
static V S3413(void) { static V c; return STRC(c, ":"); }
static V L3416(V *a) {
return F_Chk_dP_ddo__stmt(a[1], a[0], a[2]);
}
static V L3415(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcol(), mk_clo(L3416, 3, 2, (V[]){a[0], a[1]}));
}
static V L3414(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3415, 3, 2, (V[]){a[0], a[1]}));
}
static V L3412(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3413()), mk_clo(L3414, 3, 2, (V[]){a[1], a[0]}));
}
static V L3411(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dfill(a[2], a[1], a[3]), mk_clo(L3412, 2, 1, (V[]){a[0]}));
}
static V L3410(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[2]), mk_clo(L3411, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V L3409(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(a[1]), mk_clo(L3410, 4, 3, (V[]){a[1], a[2], a[0]}));
}
static V L3407(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dargs(S3408()), mk_clo(L3409, 3, 2, (V[]){a[0], a[1]}));
}
static V L3405(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3406()), mk_clo(L3407, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_ddo(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3405, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_ddo(V *a) { (void)a; return F_Chk_dP_ddo(a[0]); }
static V S3419(void) { static V c; return STRC(c, "return"); }
static V L3420(V *a) {
return F_Chk_dP_dif(a[4], F_Chk_dP_ddo__ret(a[3], a[2], a[1]), F_Chk_dP_ddo__step(a[3], a[2], a[0], a[1]));
}
static V L3418(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dword(S3419()), mk_clo(L3420, 5, 4, (V[]){a[0], a[3], a[1], a[2]}));
}
static V L3417(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L3418, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_ddo__stmt(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3417, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dP_ddo__stmt(V *a) { (void)a; return F_Chk_dP_ddo__stmt(a[0], a[1], a[2]); }
static V S3423(void) { static V c; return STRC(c, ":"); }
static V S3426(void) { static V c; return STRC(c, "Unit"); }
static V S3429(void) { static V c; return STRC(c, "=="); }
static V S3431(void) { static V c; return STRC(c, "="); }
static V L3432(V *a) {
return F_Chk_dP_ddo__step_dgo(a[7], a[6], a[5], a[4], a[3], a[2], a[1], a[0], a[8]);
}
static V L3430(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Bool_dand(a[7], F_Bool_dnot(a[8])), F_Chk_dP_dtake(S3431()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3432, 9, 8, (V[]){a[0], a[7], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3428(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S3429()), mk_clo(L3430, 9, 8, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]}));
}
static V L3427(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3428, 9, 8, (V[]){a[0], a[7], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3425(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[5], F_Chk_dP_dterm(1u), F_Chk_dP_dif(a[6], F_Chk_dP_dvar(S3426(), F_Chk_dTm_dspan(a[4])), F_Chk_dP_dpure(a[4]))), mk_clo(L3427, 8, 7, (V[]){a[6], a[4], a[0], a[1], a[2], a[3], a[5]}));
}
static V L3424(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[5], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dmore(a[4])), mk_clo(L3425, 7, 6, (V[]){a[0], a[4], a[1], a[2], a[3], a[5]}));
}
static V L3422(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Chk_dTm_dis__var(a[4]), F_Chk_dP_dtake(S3423()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3424, 6, 5, (V[]){a[0], a[1], a[2], a[4], a[3]}));
}
static V L3421(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3422, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V F_Chk_dP_ddo__step(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3421, 5, 4, (V[]){a3, a1, a0, a2}));
}
static V W_Chk_dP_ddo__step(V *a) { (void)a; return F_Chk_dP_ddo__step(a[0], a[1], a[2], a[3]); }
static V S3434(void) { static V c; return STRC(c, "<-"); }
static V L3435(V *a) {
return F_Chk_dP_ddo__bind(a[6], a[5], a[4], a[3], a[2], a[1], IMM(1), a[0], IMM(0));
}
static V F_Chk_dP_ddo__step_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s3433 = a6;
if ((s3433) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a8, F_Chk_dP_dpure(IMM(0)), F_Chk_dP_deat(S3434())), mk_clo(L3435, 8, 7, (V[]){a8, a5, a4, a3, a2, a1, a0}));
} else if ((s3433) == IMM(0)) {
return F_Chk_dP_dif(a7, F_Chk_dP_ddo__bind(a0, a1, a2, a3, a4, a5, IMM(0), IMM(0), IMM(1)), F_Chk_dP_ddo__arrow(a0, a1, a2, a3, a4, a5));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_ddo__step_dgo(V *a) { (void)a; return F_Chk_dP_ddo__step_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V S3436(void) { static V c; return STRC(c, "<-"); }
static V L3437(V *a) {
return F_Chk_dP_dif(a[6], F_Chk_dP_ddo__bind(a[5], a[4], a[3], a[2], a[1], a[0], IMM(0), IMM(0), IMM(0)), F_Chk_dP_ddo__last(a[5], a[4], a[1]));
}
static V F_Chk_dP_ddo__arrow(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3436()), mk_clo(L3437, 7, 6, (V[]){a5, a4, a3, a2, a1, a0}));
}
static V W_Chk_dP_ddo__arrow(V *a) { (void)a; return F_Chk_dP_ddo__arrow(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S3440(void) { static V c; return STRC(c, ""); }
static V L3441(V *a) {
return F_Chk_dP_dpure(C3(23, a[3], F_Bool_dpick(F_Chk_dTld_dis__adt(F_Chk_dbook__tld(a[2], a[1])), C4(14, a[1], a[0], F_Chk_dTm_dspan(a[3]), IMM(0)), a[4]), F_Chk_dTm_dspan(a[3])));
}
static V L3439(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_ddocall(a[3], S3440(), a[2], IMM(0), IMM(0), F_Chk_dTm_dspan(a[1])), mk_clo(L3441, 5, 4, (V[]){a[2], a[0], a[4], a[1]}));
}
static V L3438(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3439, 5, 4, (V[]){a[3], a[0], a[1], a[2]}));
}
static V F_Chk_dP_ddo__last(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dreso(a0), mk_clo(L3438, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dP_ddo__last(V *a) { (void)a; return F_Chk_dP_ddo__last(a[0], a[1], a[2]); }
static V L3442(V *a) {
return C1(1, C2(0, F_Chk_ddo_dcall(F_Chk_dPS_dbook(a[6]), a[6], a[5], a[4], a[3], a[2], a[1], a[0]), a[6]));
}
static V F_Chk_dP_ddocall(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return mk_clo(L3442, 7, 6, (V[]){a5, a4, a3, a2, a1, a0});
}
static V W_Chk_dP_ddocall(V *a) { (void)a; return F_Chk_dP_ddocall(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_ddo_dcall(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
return F_Chk_dapps(C3(4, F_Chk_dPS_dreso(a1, F_String_dappend(a2, a3)), a7, IMM(0)), F_List_dappend(F_List_dappend(F_List_dappend(F_Chk_dList_dinit__tm(a4), a5), F_Chk_dList_dlast__tm(a4)), a6), a7);
}
static V W_Chk_ddo_dcall(V *a) { (void)a; return F_Chk_ddo_dcall(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V F_Chk_dList_dlast__tm(V a0) {
top:;
V s3443 = a0;
if ((s3443) == IMM(0)) {
return IMM(0);
} else if (TAG(s3443) == 1 && (FLD(s3443, 1)) == IMM(0)) {
return C2(1, FLD(s3443, 0), IMM(0));
} else if (TAG(s3443) == 1) {
{ V t0 = FLD(s3443, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dList_dlast__tm(V *a) { (void)a; return F_Chk_dList_dlast__tm(a[0]); }
static V F_Chk_dList_dinit__tm(V a0) {
top:;
V s3444 = a0;
if ((s3444) == IMM(0)) {
return IMM(0);
} else if (TAG(s3444) == 1 && (FLD(s3444, 1)) == IMM(0)) {
return IMM(0);
} else if (TAG(s3444) == 1) {
return C2(1, FLD(s3444, 0), F_Chk_dList_dinit__tm(FLD(s3444, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dList_dinit__tm(V *a) { (void)a; return F_Chk_dList_dinit__tm(a[0]); }
static V S3447(void) { static V c; return STRC(c, ";"); }
static V S3451(void) { static V c; return STRC(c, "_"); }
static V S3455(void) { static V c; return STRC(c, ".bind"); }
static V L3454(V *a) {
return F_Chk_dP_dif(a[7], F_Chk_dP_dpure(F_Chk_ddo_dlet(a[6], C3(23, a[5], a[4], a[3]), a[2], a[3])), F_Chk_dP_ddocall(a[1], S3455(), a[0], C2(1, a[4], IMM(0)), C2(1, a[5], C2(1, F_Chk_ddo_dlam(a[6], a[2], a[3]), IMM(0))), a[3]));
}
static V L3453(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[7]), mk_clo(L3454, 9, 8, (V[]){a[0], a[1], a[8], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3452(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_ddo__stmt(a[7], a[6], a[5]), mk_clo(L3453, 9, 8, (V[]){a[6], a[7], a[0], a[1], a[2], a[8], a[3], a[4]}));
}
static V L3450(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbinder(F_Bool_dpick(a[8], a[7], C3(0, S3451(), 0u, IMM(0)))), mk_clo(L3452, 9, 8, (V[]){a[0], a[1], a[2], a[3], a[9], a[4], a[5], a[6]}));
}
static V L3449(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3450, 10, 9, (V[]){a[8], a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]}));
}
static V L3448(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[8]), mk_clo(L3449, 9, 8, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]}));
}
static V L3446(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3447()), mk_clo(L3448, 10, 9, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]}));
}
static V L3445(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3446, 10, 9, (V[]){a[0], a[8], a[1], a[2], a[3], a[4], a[5], a[6], a[7]}));
}
static V F_Chk_dP_ddo__bind(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dif(a8, F_Chk_dP_dpure(a4), F_Chk_dP_dterm0()), mk_clo(L3445, 9, 8, (V[]){a5, a7, a2, a1, a0, a4, a6, a3}));
}
static V W_Chk_dP_ddo__bind(V *a) { (void)a; return F_Chk_dP_ddo__bind(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Chk_ddo_dlam(V a0, V a1, V a2) {
top:;
return CN(12, 5, (V[]){F_Chk_dPt_dk(a0), F_Chk_dPt_di(a0), C3(24, IMM(0), F_Chk_dPt_di(a0), a1), a2, F_Chk_dPt_dq(a0)});
}
static V W_Chk_ddo_dlam(V *a) { (void)a; return F_Chk_ddo_dlam(a[0], a[1], a[2]); }
static V F_Chk_ddo_dlet(V a0, V a1, V a2, V a3) {
top:;
return CN(6, 6, (V[]){C2(1, F_Chk_dPt_dk(a0), IMM(0)), C2(1, F_Chk_dPt_di(a0), IMM(0)), C2(1, a1, IMM(0)), C3(25, IMM(0), C2(1, F_Chk_dPt_di(a0), IMM(0)), a2), a3, C2(1, F_Chk_dPt_dq(a0), IMM(0))});
}
static V W_Chk_ddo_dlet(V *a) { (void)a; return F_Chk_ddo_dlet(a[0], a[1], a[2], a[3]); }
static V S3456(void) { static V c; return STRC(c, ";"); }
static V L3459(V *a) {
return F_Chk_dP_dpure(F_Bool_dor(a[2], F_Bool_dand(F_Bool_dnot(F_U32_dis__zero(a[1])), F_U32_dis__eq(a[3], a[0]))));
}
static V L3458(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcol(), mk_clo(L3459, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L3457(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3458, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dmore(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dat(S3456()), mk_clo(L3457, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dmore(V *a) { (void)a; return F_Chk_dP_dmore(a[0]); }
static V S3462(void) { static V c; return STRC(c, ".pure"); }
static V L3461(V *a) {
return F_Chk_dP_ddocall(a[2], S3462(), a[1], IMM(0), C2(1, a[0], IMM(0)), a[3]);
}
static V L3460(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[2]), mk_clo(L3461, 4, 3, (V[]){a[3], a[0], a[1]}));
}
static V F_Chk_dP_ddo__ret(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3460, 4, 3, (V[]){a1, a0, a2}));
}
static V W_Chk_dP_ddo__ret(V *a) { (void)a; return F_Chk_dP_ddo__ret(a[0], a[1], a[2]); }
static V L3463(V *a) {
return F_Chk_dP_dword_dif(a[0], a[1]);
}
static V F_Chk_dP_dword(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dat__word(a0), mk_clo(L3463, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dword(V *a) { (void)a; return F_Chk_dP_dword(a[0]); }
static V F_Chk_dP_dword_dif(V a0, V a1) {
top:;
V s3464 = a1;
if ((s3464) == IMM(1)) {
return F_Chk_dP_dtake(a0);
} else if ((s3464) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dword_dif(V *a) { (void)a; return F_Chk_dP_dword_dif(a[0], a[1]); }
static V L3466(V *a) {
return F_Chk_dP_dpure(F_Bool_dand(F_Chk_dStr_dprefix(a[1], a[0]), F_Bool_dnot(F_Chk_dis__name(F_Chk_dStr_dfirst(F_String_ddrop(a[1], F_String_dlength(a[0])))))));
}
static V L3465(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek__rest(), mk_clo(L3466, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dat__word(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3465, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dat__word(V *a) { (void)a; return F_Chk_dP_dat__word(a[0]); }
static V S3467(void) { static V c; return STRC(c, "="); }
static V L3468(V *a) {
return F_Chk_dP_dbody_dlet_dann(a[1], a[0]);
}
static V F_Chk_dP_dbody_dlet_deq(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_deat(S3467()), mk_clo(L3468, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dbody_dlet_deq(V *a) { (void)a; return F_Chk_dP_dbody_dlet_deq(a[0], a[1]); }
static V L3471(V *a) {
return F_Chk_dP_dpure(C2(1, C3(23, a[1], a[0], a[2]), IMM(0)));
}
static V L3470(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3471, 3, 2, (V[]){a[0], a[2]}));
}
static V F_Chk_dP_dbody_dlet_dann(V a0, V a1) {
top:;
V s3469 = a1;
if ((s3469) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s3469) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3470, 3, 2, (V[]){FLD(s3469, 0), a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dbody_dlet_dann(V *a) { (void)a; return F_Chk_dP_dbody_dlet_dann(a[0], a[1]); }
static V F_Chk_dP_dbody_dreply(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dP_dbody_dreply_dgo(a0, a1, a2, a3, F_Chk_dterm__write(a3));
}
static V W_Chk_dP_dbody_dreply(V *a) { (void)a; return F_Chk_dP_dbody_dreply(a[0], a[1], a[2], a[3]); }
static V F_Chk_dterm__write(V a0) {
top:;
return F_Chk_dterm__write_dgo(F_Chk_dterm__unapply(a0));
}
static V W_Chk_dterm__write(V *a) { (void)a; return F_Chk_dterm__write(a[0]); }
static V F_Chk_dterm__write_dgo(V a0) {
top:;
V v3472 = a0;
V s3473 = FLD(v3472, 0);
V s3474 = FLD(v3472, 1);
if (TAG(s3473) == 4 && TAG(FLD(s3473, 0)) == 1 && (FLD(FLD(s3473, 0), 0)) == 65 && TAG(FLD(FLD(s3473, 0), 1)) == 1 && (FLD(FLD(FLD(s3473, 0), 1), 0)) == 114 && TAG(FLD(FLD(FLD(s3473, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s3473, 0), 1), 1), 0)) == 114 && TAG(FLD(FLD(FLD(FLD(s3473, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s3473, 0), 1), 1), 1), 0)) == 97 && TAG(FLD(FLD(FLD(FLD(FLD(s3473, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s3473, 0), 1), 1), 1), 1), 0)) == 121 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(s3473, 0), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3473, 0), 1), 1), 1), 1), 1), 0)) == 46 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3473, 0), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3473, 0), 1), 1), 1), 1), 1), 1), 0)) == 115 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3473, 0), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3473, 0), 1), 1), 1), 1), 1), 1), 1), 0)) == 101 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3473, 0), 1), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3473, 0), 1), 1), 1), 1), 1), 1), 1), 1), 0)) == 116 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3473, 0), 1), 1), 1), 1), 1), 1), 1), 1), 1)) == IMM(0) && TAG(s3474) == 1 && TAG(FLD(s3474, 1)) == 1 && TAG(FLD(FLD(s3474, 1), 1)) == 1 && TAG(FLD(FLD(FLD(s3474, 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s3474, 1), 1), 1), 1)) == IMM(0)) {
return F_Bool_dpick(F_Chk_dTm_dis__var(FLD(FLD(s3474, 1), 0)), C1(1, FLD(FLD(s3474, 1), 0)), IMM(0));
} else {
return IMM(0);
}
}
static V W_Chk_dterm__write_dgo(V *a) { (void)a; return F_Chk_dterm__write_dgo(a[0]); }
static V L3476(V *a) {
return F_Chk_dP_dpure(C2(2, a[0], a[1]));
}
static V L3478(V *a) {
return F_Chk_dP_dif(a[4], F_Chk_dP_dbody_dlet(a[3], a[2], IMM(1), C2(1, a[1], IMM(0)), IMM(0), C2(1, a[0], IMM(0))), F_Chk_dP_dpure(C2(2, a[0], a[5])));
}
static V L3477(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[3]), mk_clo(L3478, 6, 5, (V[]){a[0], a[1], a[3], a[2], a[4]}));
}
static V F_Chk_dP_dbody_dreply_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s3475 = a4;
if ((s3475) == IMM(0)) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a1), mk_clo(L3476, 2, 1, (V[]){a3}));
} else if (TAG(s3475) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dmore(a2), mk_clo(L3477, 5, 4, (V[]){a3, FLD(s3475, 0), a0, a1}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dbody_dreply_dgo(V *a) { (void)a; return F_Chk_dP_dbody_dreply_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V F_Maybe_dis__none(V a2) {
top:;
return F_Bool_dnot(F_Maybe_dis__some(a2));
}
static V W_Maybe_dis__none(V *a) { (void)a; return F_Maybe_dis__none(a[2]); }
static V L3481(V *a) {
return F_Chk_dP_dpure(IMM(0));
}
static V F_Chk_dP_dbody_dty__ok(V a0, V a1, V a2) {
top:;
V s3479 = a1;
V s3480 = a2;
if (TAG(s3479) == 1 && (s3480) == IMM(0)) {
return F_Chk_dP_dbind(F_Chk_dP_dset__cur(a0), mk_clo(L3481, 1, 0, 0));
} else {
return F_Chk_dP_dpure(s3479);
}
}
static V W_Chk_dP_dbody_dty__ok(V *a) { (void)a; return F_Chk_dP_dbody_dty__ok(a[0], a[1], a[2]); }
static V L3482(V *a) {
return F_Chk_dP_dpure(C1(1, a[0]));
}
static V F_Chk_dP_dbody_dty(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3482, 1, 0, 0));
}
static V W_Chk_dP_dbody_dty(V *a) { (void)a; return F_Chk_dP_dbody_dty(); }
static V L3486(V *a) {
return F_Chk_dP_dif(a[2], F_Chk_dP_dlocal_dnames_dmore(a[1], a[0]), F_Chk_dP_dpure(a[0]));
}
static V L3485(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Bool_dand(F_Bool_dand(F_Bool_dnot(a[3]), F_Bool_dor(F_Chk_dis__head(a[2]), F_Bool_dand(F_Chk_dQ_dis__lone(a[1]), F_U32_dis__eq(a[2], 43u)))), F_Bool_dnot(F_Chk_dStr_dhas(F_Chk_dKEYWORDS(), F_Chk_dStr_dword__at(a[4]))))), mk_clo(L3486, 3, 2, (V[]){a[0], a[1]}));
}
static V L3484(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek__rest(), mk_clo(L3485, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V L3483(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3484, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dlocal_dnames(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dnl(), mk_clo(L3483, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dlocal_dnames(V *a) { (void)a; return F_Chk_dP_dlocal_dnames(a[0], a[1]); }
static V L3488(V *a) {
return F_Chk_dP_dlocal_dnames(a[2], F_List_dappend(a[1], C2(1, a[0], IMM(0))));
}
static V L3487(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3488, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V F_Chk_dP_dlocal_dnames_dmore(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3487, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dlocal_dnames_dmore(V *a) { (void)a; return F_Chk_dP_dlocal_dnames_dmore(a[0], a[1]); }
static V S3490(void) { static V c; return STRC(c, ""); }
static V F_Chk_dStr_dword__at(V a0) {
top:;
V s3489 = a0;
if (TAG(s3489) == 1) {
return F_Chk_dStr_dword__at_dif(FLD(s3489, 0), FLD(s3489, 1), F_Bool_dor(F_Chk_dis__name(FLD(s3489, 0)), F_U32_dis__eq(FLD(s3489, 0), 46u)));
} else if ((s3489) == IMM(0)) {
return S3490();
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dword__at(V *a) { (void)a; return F_Chk_dStr_dword__at(a[0]); }
static V S3492(void) { static V c; return STRC(c, ""); }
static V F_Chk_dStr_dword__at_dif(V a0, V a1, V a2) {
top:;
V s3491 = a2;
if ((s3491) == IMM(1)) {
return C2(1, a0, F_Chk_dStr_dword__at(a1));
} else if ((s3491) == IMM(0)) {
return S3492();
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dword__at_dif(V *a) { (void)a; return F_Chk_dStr_dword__at_dif(a[0], a[1], a[2]); }
static V L3494(V *a) {
return F_Chk_dP_dpure(C3(0, a[0], 0u, a[1]));
}
static V L3493(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[0]), mk_clo(L3494, 2, 1, (V[]){a[1]}));
}
static V F_Chk_dP_dbody_derased__name(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3493, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbody_derased__name(V *a) { (void)a; return F_Chk_dP_dbody_derased__name(a[0]); }
static V L3499(V *a) {
return F_Chk_dP_dpure(C3(0, a[1], a[0], a[2]));
}
static V L3498(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3499, 3, 2, (V[]){a[2], a[0]}));
}
static V L3497(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_drows(a[2], a[3], F_List_dlength(a[1])), mk_clo(L3498, 3, 2, (V[]){a[1], a[0]}));
}
static V L3496(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcol(), mk_clo(L3497, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3495(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3496, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V F_Chk_dP_dbody_dmatch(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterms(), mk_clo(L3495, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dbody_dmatch(V *a) { (void)a; return F_Chk_dP_dbody_dmatch(a[0], a[1]); }
static V S3500(void) { static V c; return STRC(c, "case"); }
static V L3502(V *a) {
return F_Chk_dP_dif(F_Bool_dand(F_U32_dis__gt(a[3], a[2]), F_Bool_dand(a[1], F_U32_dis__ge(a[4], a[3]))), F_Chk_dP_drow(a[2], a[3], a[0], a[4]), F_Chk_dP_dpure(IMM(0)));
}
static V L3501(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcol(), mk_clo(L3502, 5, 4, (V[]){a[0], a[3], a[1], a[2]}));
}
static V F_Chk_dP_drows(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3500()), mk_clo(L3501, 4, 3, (V[]){a2, a0, a1}));
}
static V W_Chk_dP_drows(V *a) { (void)a; return F_Chk_dP_drows(a[0], a[1], a[2]); }
static V S3503(void) { static V c; return STRC(c, "case"); }
static V S3506(void) { static V c; return STRC(c, " patterns (one per scrutinee)"); }
static V L3512(V *a) {
return F_Chk_dP_dpure(C2(1, C2(3, a[1], a[0]), a[2]));
}
static V L3511(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_drows(a[4], a[3], a[2]), mk_clo(L3512, 3, 2, (V[]){a[0], a[1]}));
}
static V L3510(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[4]), mk_clo(L3511, 6, 5, (V[]){a[5], a[0], a[1], a[2], a[3]}));
}
static V L3509(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody(a[4]), mk_clo(L3510, 6, 5, (V[]){a[5], a[0], a[1], a[2], a[3]}));
}
static V L3508(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpatts(a[4]), mk_clo(L3509, 6, 5, (V[]){a[0], a[1], a[2], a[5], a[3]}));
}
static V L3507(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3508, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L3505(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Nat_dis__eq(F_List_dlength(a[4]), a[3]), F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dfail(F_String_dappend(F_Nat_dshow(a[3]), S3506()))), mk_clo(L3507, 6, 5, (V[]){a[3], a[0], a[1], a[2], a[4]}));
}
static V L3504(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterms(), mk_clo(L3505, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Chk_dP_drow(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(S3503()), mk_clo(L3504, 5, 4, (V[]){a1, a0, a3, a2}));
}
static V W_Chk_dP_drow(V *a) { (void)a; return F_Chk_dP_drow(a[0], a[1], a[2], a[3]); }
static V S3515(void) { static V c; return STRC(c, ":"); }
static V L3516(V *a) {
return F_Chk_dP_dif(a[1], F_Chk_dP_dpure(C2(1, a[0], IMM(0))), F_Chk_dP_dterms_dmore(a[0]));
}
static V L3514(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3515()), mk_clo(L3516, 2, 1, (V[]){a[0]}));
}
static V L3513(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3514, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dterms(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3513, 1, 0, 0));
}
static V W_Chk_dP_dterms(V *a) { (void)a; return F_Chk_dP_dterms(); }
static V S3517(void) { static V c; return STRC(c, ","); }
static V L3519(V *a) {
return F_Chk_dP_dpure(C2(1, a[0], a[1]));
}
static V L3518(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterms(), mk_clo(L3519, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dterms_dmore(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3517()), mk_clo(L3518, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dterms_dmore(V *a) { (void)a; return F_Chk_dP_dterms_dmore(a[0]); }
static V S3520(void) { static V c; return STRC(c, "for"); }
static V S3522(void) { static V c; return STRC(c, "exs"); }
static V L3523(V *a) {
return F_Chk_dP_dif(F_Bool_dor(a[2], a[3]), F_Chk_dP_dclause(a[1], a[0], a[2]), F_Chk_dP_dpure(C2(0, a[1], a[0])));
}
static V L3521(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3522()), mk_clo(L3523, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dclauses(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3520()), mk_clo(L3521, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dclauses(V *a) { (void)a; return F_Chk_dP_dclauses(a[0], a[1]); }
static V S3524(void) { static V c; return STRC(c, "for"); }
static V S3525(void) { static V c; return STRC(c, "exs"); }
static V S3528(void) { static V c; return STRC(c, "~"); }
static V S3530(void) { static V c; return STRC(c, "a plain clause (only leading clauses take ~)"); }
static V S3532(void) { static V c; return STRC(c, "~"); }
static V S3538(void) { static V c; return STRC(c, ":"); }
static V S3541(void) { static V c; return STRC(c, "where"); }
static V L3544(V *a) {
return F_Chk_dP_dclauses(F_List_dappend(a[7], C2(1, CN(0, 6, (V[]){a[6], a[5], a[4], a[8], a[3], a[2]}), IMM(0))), F_Bool_dpick(a[1], nat_addk(a[0], 1), a[0]));
}
static V L3543(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dopen(a[6]), mk_clo(L3544, 9, 8, (V[]){a[0], a[1], a[2], a[7], a[6], a[3], a[4], a[5]}));
}
static V L3542(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[8], F_Chk_dP_dclause_dwhere(a[7], a[6], a[5]), F_Chk_dP_dpure(a[6])), mk_clo(L3543, 8, 7, (V[]){a[0], a[1], a[5], a[2], a[3], a[4], a[7]}));
}
static V L3540(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3541()), mk_clo(L3542, 9, 8, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[7], a[6]}));
}
static V L3539(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3540, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3537(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3538()), mk_clo(L3539, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[6], a[5]}));
}
static V L3536(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[5]), mk_clo(L3537, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[6]}));
}
static V L3535(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3536, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3534(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L3535, 6, 5, (V[]){a[0], a[1], a[4], a[2], a[3]}));
}
static V L3533(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[3], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dif(a[2], F_Chk_dP_dquant(), F_Chk_dP_dpure(IMM(1)))), mk_clo(L3534, 5, 4, (V[]){a[0], a[3], a[2], a[1]}));
}
static V L3531(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[2], F_Chk_dP_dtake(S3532()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3533, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3529(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Bool_dand(F_Bool_dand(a[2], a[3]), F_Nat_dis__lt(a[1], F_List_dlength(a[0]))), F_Chk_dP_dfail(S3530()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3531, 4, 3, (V[]){a[1], a[0], a[2]}));
}
static V L3527(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S3528()), mk_clo(L3529, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3526(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3527, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dclause(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(F_Bool_dpick(a2, S3524(), S3525())), mk_clo(L3526, 4, 3, (V[]){a0, a1, a2}));
}
static V W_Chk_dP_dclause(V *a) { (void)a; return F_Chk_dP_dclause(a[0], a[1], a[2]); }
static V S3546(void) { static V c; return STRC(c, "where"); }
static V S3553(void) { static V c; return STRC(c, "Exists"); }
static V L3552(V *a) {
return F_Chk_dP_dpure(C3(13, C3(13, C3(4, S3553(), a[5], IMM(0)), a[4], a[3]), CN(12, 5, (V[]){a[2], a[1], C3(24, IMM(0), a[1], a[0]), a[3], IMM(3)}), a[3]));
}
static V L3551(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[5]), mk_clo(L3552, 7, 6, (V[]){a[6], a[0], a[1], a[2], a[3], a[4]}));
}
static V L3550(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3551, 7, 6, (V[]){a[5], a[0], a[1], a[2], a[3], a[4]}));
}
static V L3549(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dopen(a[3]), mk_clo(L3550, 6, 5, (V[]){a[3], a[0], a[1], a[2], a[4]}));
}
static V L3548(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3549, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V L3547(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[3]), mk_clo(L3548, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3545(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dword(S3546()), mk_clo(L3547, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Chk_dP_dclause_dwhere(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L3545, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dP_dclause_dwhere(V *a) { (void)a; return F_Chk_dP_dclause_dwhere(a[0], a[1], a[2]); }
static V S3555(void) { static V c; return STRC(c, "a fresh name (duplicate declaration: "); }
static V S3556(void) { static V c; return STRC(c, ")"); }
static V L3554(V *a) {
return F_Chk_dP_dif(F_Chk_dbook__has(a[1], a[0]), F_Chk_dP_dfail(F_String_dappend(S3555(), F_String_dappend(a[0], S3556()))), F_Chk_dP_dpure(IMM(0)));
}
static V F_Chk_dP_dfresh(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3554, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dfresh(V *a) { (void)a; return F_Chk_dP_dfresh(a[0]); }
static V L3557(V *a) {
return C1(1, C2(0, F_Chk_dPS_dqual(a[1], a[0]), a[1]));
}
static V F_Chk_dP_dqual(V a0) {
top:;
return mk_clo(L3557, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dqual(V *a) { (void)a; return F_Chk_dP_dqual(a[0]); }
static V S3558(void) { static V c; return STRC(c, "type"); }
static V S3565(void) { static V c; return STRC(c, "<"); }
static V S3567(void) { static V c; return STRC(c, ">"); }
static V L3568(V *a) {
return F_Chk_dP_dtype_dgo(a[1], a[0], F_Pair_dfst(a[2]));
}
static V L3566(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[2], F_Chk_dP_dtele(S3567(), IMM(0), 0u), F_Chk_dP_dpure(C2(0, IMM(0), 0u))), mk_clo(L3568, 3, 2, (V[]){a[0], a[1]}));
}
static V L3564(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3565()), mk_clo(L3566, 3, 2, (V[]){a[0], a[1]}));
}
static V L3563(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3564, 3, 2, (V[]){a[1], a[0]}));
}
static V L3562(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3563, 2, 1, (V[]){a[0]}));
}
static V L3561(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dfresh(a[0]), mk_clo(L3562, 2, 1, (V[]){a[0]}));
}
static V L3560(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dqual(a[0]), mk_clo(L3561, 1, 0, 0));
}
static V L3559(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3560, 1, 0, 0));
}
static V F_Chk_dP_dtype(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(S3558()), mk_clo(L3559, 1, 0, 0));
}
static V W_Chk_dP_dtype(V *a) { (void)a; return F_Chk_dP_dtype(); }
static V S3569(void) { static V c; return STRC(c, "is"); }
static V S3571(void) { static V c; return STRC(c, "'is'"); }
static V S3574(void) { static V c; return STRC(c, ":"); }
static V L3583(V *a) {
return F_Chk_dP_dclose(a[0]);
}
static V L3582(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dset__book(F_Chk_dbook__push(F_Chk_dbook__set(a[6], a[5], CN(1, 5, (V[]){a[4], a[3], a[2], a[1], IMM(0)})), a[5])), mk_clo(L3583, 2, 1, (V[]){a[0]}));
}
static V L3581(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3582, 7, 6, (V[]){a[0], a[5], a[1], a[2], a[3], a[4]}));
}
static V L3580(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dctors(a[5], a[4], IMM(0)), mk_clo(L3581, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[5]}));
}
static V L3579(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dset__book(F_Chk_dbook__set(a[5], a[4], CN(1, 5, (V[]){a[3], a[6], a[2], IMM(0), IMM(0)}))), mk_clo(L3580, 7, 6, (V[]){a[0], a[2], a[6], a[3], a[1], a[4]}));
}
static V L3578(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_dTC_dfirst__typed(a[4])), mk_clo(L3579, 7, 6, (V[]){a[0], a[4], a[1], a[5], a[2], a[3]}));
}
static V L3577(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_List_dlength(a[3])), mk_clo(L3578, 6, 5, (V[]){a[0], a[4], a[1], a[2], a[3]}));
}
static V L3576(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_dhigher0(a[4], F_Chk_dtele__bind(a[3], a[2]))), mk_clo(L3577, 5, 4, (V[]){a[0], a[1], a[4], a[3]}));
}
static V L3575(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3576, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3573(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3574()), mk_clo(L3575, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V L3572(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3573, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3570(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[3], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dfail(S3571())), mk_clo(L3572, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dtype_dgo(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(S3569()), mk_clo(L3570, 4, 3, (V[]){a1, a0, a2}));
}
static V W_Chk_dP_dtype_dgo(V *a) { (void)a; return F_Chk_dP_dtype_dgo(a[0], a[1], a[2]); }
static V S3586(void) { static V c; return STRC(c, "def"); }
static V S3588(void) { static V c; return STRC(c, "type"); }
static V S3590(void) { static V c; return STRC(c, "law"); }
static V L3591(V *a) {
return F_Chk_dP_dif(F_Bool_dor(F_Bool_dnot(F_Chk_dis__head(a[5])), F_Bool_dor(a[4], F_Bool_dor(a[3], a[6]))), F_Chk_dP_dpure(a[2]), F_Chk_dP_dctor(a[1], a[0], a[2]));
}
static V L3589(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3590()), mk_clo(L3591, 7, 6, (V[]){a[0], a[1], a[2], a[5], a[3], a[4]}));
}
static V L3587(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3588()), mk_clo(L3589, 6, 5, (V[]){a[0], a[1], a[2], a[4], a[3]}));
}
static V L3585(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3586()), mk_clo(L3587, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3584(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3585, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dctors(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3584, 4, 3, (V[]){a1, a0, a2}));
}
static V W_Chk_dP_dctors(V *a) { (void)a; return F_Chk_dP_dctors(a[0], a[1], a[2]); }
static V S3595(void) { static V c; return STRC(c, "a fresh constructor name (duplicate declaration: "); }
static V S3596(void) { static V c; return STRC(c, ")"); }
static V S3598(void) { static V c; return STRC(c, "{"); }
static V S3601(void) { static V c; return STRC(c, "}"); }
static V L3607(V *a) {
return F_Chk_dP_dctors(a[3], a[2], F_List_dappend(a[1], C2(1, a[0], IMM(0))));
}
static V L3606(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dset__book(F_Chk_dbook__set__ctr(a[5], a[4], a[3])), mk_clo(L3607, 5, 4, (V[]){a[3], a[0], a[1], a[2]}));
}
static V L3605(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[5]), mk_clo(L3606, 7, 6, (V[]){a[0], a[1], a[2], a[6], a[3], a[4]}));
}
static V L3604(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(C3(0, a[5], F_List_dlength(a[4]), F_Chk_dhigher0(a[6], F_Chk_dtele__bind(F_List_dappend(a[3], a[4]), C4(14, a[2], F_Chk_dTC_dparams(a[3]), IMM(0), IMM(0)))))), mk_clo(L3605, 7, 6, (V[]){a[0], a[3], a[2], a[5], a[6], a[1]}));
}
static V L3603(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3604, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[5], a[4]}));
}
static V L3602(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Pair_dfst(a[5])), mk_clo(L3603, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L3600(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtele(S3601(), IMM(0), 0u), mk_clo(L3602, 6, 5, (V[]){a[0], a[4], a[1], a[2], a[3]}));
}
static V L3599(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3600, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3597(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3598()), mk_clo(L3599, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3594(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Maybe_dis__some(F_Chk_dbook__ctr(a[4], a[3])), F_Chk_dP_dfail(F_String_dappend(S3595(), F_String_dappend(a[3], S3596()))), F_Chk_dP_dpure(IMM(0))), mk_clo(L3597, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3593(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3594, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3592(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dqual(a[3]), mk_clo(L3593, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dctor(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3592, 4, 3, (V[]){a2, a0, a1}));
}
static V W_Chk_dP_dctor(V *a) { (void)a; return F_Chk_dP_dctor(a[0], a[1], a[2]); }
static V F_Chk_dTC_dparams(V a0) {
top:;
V s3608 = a0;
if ((s3608) == IMM(0)) {
return IMM(0);
} else if (TAG(s3608) == 1) {
return C2(1, C3(0, FLD(FLD(s3608, 0), 1), FLD(FLD(s3608, 0), 2), IMM(0)), F_Chk_dTC_dparams(FLD(s3608, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dTC_dparams(V *a) { (void)a; return F_Chk_dTC_dparams(a[0]); }
static V F_Chk_dtele__bind(V a0, V a1) {
top:;
V s3609 = a0;
if ((s3609) == IMM(0)) {
return a1;
} else if (TAG(s3609) == 1) {
return CN(11, 6, (V[]){FLD(FLD(s3609, 0), 0), FLD(FLD(s3609, 0), 1), FLD(FLD(s3609, 0), 2), FLD(FLD(s3609, 0), 3), C3(24, IMM(0), FLD(FLD(s3609, 0), 2), F_Chk_dtele__bind(FLD(s3609, 1), a1)), FLD(FLD(s3609, 0), 4)});
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dtele__bind(V *a) { (void)a; return F_Chk_dtele__bind(a[0], a[1]); }
static V L3611(V *a) {
return F_Chk_dP_dif(a[3], F_Chk_dP_dpure(C2(0, a[2], a[1])), F_Chk_dP_dtele_done(a[0], a[2], a[1]));
}
static V L3610(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(a[2]), mk_clo(L3611, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V F_Chk_dP_dtele(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3610, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dP_dtele(V *a) { (void)a; return F_Chk_dP_dtele(a[0], a[1], a[2]); }
static V S3613(void) { static V c; return STRC(c, ")"); }
static V S3615(void) { static V c; return STRC(c, "~"); }
static V S3617(void) { static V c; return STRC(c, "a plain binder (only leading binders take ~)"); }
static V S3619(void) { static V c; return STRC(c, "~"); }
static V S3624(void) { static V c; return STRC(c, "a fresh field name (duplicate declaration: "); }
static V S3625(void) { static V c; return STRC(c, ")"); }
static V S3629(void) { static V c; return STRC(c, ":"); }
static V S3632(void) { static V c; return STRC(c, ":"); }
static V S3637(void) { static V c; return STRC(c, ","); }
static V L3638(V *a) {
return F_Chk_dP_dtele(a[9], F_List_dappend(a[8], C2(1, CN(0, 5, (V[]){F_Bool_dpick(a[7], IMM(0), a[6]), a[5], a[4], a[3], a[2]}), IMM(0))), F_Bool_dpick(a[1], nat_addk(a[0], 1), a[0]));
}
static V L3636(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3637()), mk_clo(L3638, 11, 10, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]}));
}
static V L3635(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3636, 11, 10, (V[]){a[0], a[1], a[2], a[3], a[9], a[4], a[5], a[6], a[7], a[8]}));
}
static V L3634(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dopen(a[7]), mk_clo(L3635, 10, 9, (V[]){a[0], a[1], a[2], a[8], a[7], a[3], a[4], a[5], a[6]}));
}
static V L3633(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[7], F_Chk_dP_dpure(C1(8, a[6])), F_Chk_dP_dterm0()), mk_clo(L3634, 9, 8, (V[]){a[0], a[1], a[6], a[2], a[7], a[3], a[4], a[5]}));
}
static V L3631(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[7], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_deat(S3632())), mk_clo(L3633, 9, 8, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]}));
}
static V L3630(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Bool_dand(F_Chk_dQ_dis__lone(a[6]), F_Bool_dnot(a[7]))), mk_clo(L3631, 8, 7, (V[]){a[0], a[1], a[6], a[2], a[3], a[4], a[5]}));
}
static V L3628(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S3629()), mk_clo(L3630, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3627(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3628, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[6], a[5]}));
}
static V L3626(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[6]), mk_clo(L3627, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3623(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Bool_dand(F_Bool_dnot(a[6]), F_Chk_dStr_dhas(F_Chk_dTC_dnames(a[5]), a[7])), F_Chk_dP_dfail(F_String_dappend(S3624(), F_String_dappend(a[7], S3625()))), F_Chk_dP_dpure(IMM(0))), mk_clo(L3626, 8, 7, (V[]){a[0], a[1], a[5], a[2], a[7], a[3], a[4]}));
}
static V L3622(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3623, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[6], a[4], a[5]}));
}
static V L3621(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L3622, 7, 6, (V[]){a[0], a[1], a[2], a[5], a[3], a[4]}));
}
static V L3620(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[4], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dquant()), mk_clo(L3621, 6, 5, (V[]){a[0], a[4], a[1], a[2], a[3]}));
}
static V L3618(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[3], F_Chk_dP_dtake(S3619()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3620, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3616(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Bool_dand(F_Bool_dand(a[4], a[5]), F_Nat_dis__lt(a[3], a[2])), F_Chk_dP_dfail(S3617()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3618, 5, 4, (V[]){a[3], a[0], a[1], a[4]}));
}
static V F_Chk_dP_dtele_done(V a0, V a1, V a2) {
top:;
V v3612 = F_String_deq(a0, S3613());
V v3614 = F_List_dlength(a1);
return F_Chk_dP_dbind(F_Chk_dP_dat(S3615()), mk_clo(L3616, 6, 5, (V[]){a0, a1, v3614, a2, v3612}));
}
static V W_Chk_dP_dtele_done(V *a) { (void)a; return F_Chk_dP_dtele_done(a[0], a[1], a[2]); }
static V F_Chk_dTC_dnames(V a0) {
top:;
V s3639 = a0;
if ((s3639) == IMM(0)) {
return IMM(0);
} else if (TAG(s3639) == 1) {
return C2(1, F_Chk_dTC_dk(FLD(s3639, 0)), F_Chk_dTC_dnames(FLD(s3639, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dTC_dnames(V *a) { (void)a; return F_Chk_dTC_dnames(a[0]); }
static V F_Chk_dTC_dk(V a0) {
top:;
V v3640 = a0;
return FLD(v3640, 1);
}
static V W_Chk_dTC_dk(V *a) { (void)a; return F_Chk_dTC_dk(a[0]); }
static V F_Chk_dTC_dfirst__typed(V a0) {
top:;
V s3641 = a0;
if ((s3641) == IMM(0)) {
return 0u;
} else if (TAG(s3641) == 1 && TAG(FLD(FLD(s3641, 0), 3)) == 8) {
return nat_addk(F_Chk_dTC_dfirst__typed(FLD(s3641, 1)), 1);
} else if (TAG(s3641) == 1) {
return 0u;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dTC_dfirst__typed(V *a) { (void)a; return F_Chk_dTC_dfirst__typed(a[0]); }
static V S3642(void) { static V c; return STRC(c, "def"); }
static V S3651(void) { static V c; return STRC(c, "("); }
static V S3654(void) { static V c; return STRC(c, "~"); }
static V S3656(void) { static V c; return STRC(c, "a name"); }
static V S3658(void) { static V c; return STRC(c, ")"); }
static V L3660(V *a) {
return F_Chk_dP_ddef_dgo(a[4], a[3], a[2], a[1], a[0]);
}
static V L3659(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3660, 6, 5, (V[]){a[4], a[0], a[1], a[2], a[3]}));
}
static V L3657(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtele(S3658(), IMM(0), 0u), mk_clo(L3659, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3655(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Bool_dand(a[3], a[4]), F_Chk_dP_dfail(S3656()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3657, 5, 4, (V[]){a[0], a[3], a[1], a[2]}));
}
static V L3653(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S3654()), mk_clo(L3655, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3652(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3653, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3650(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3651()), mk_clo(L3652, 5, 4, (V[]){a[3], a[0], a[1], a[2]}));
}
static V L3649(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3650, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3648(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[1], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dfresh(a[2])), mk_clo(L3649, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L3647(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[3], F_Chk_dP_dpure(a[2]), F_Chk_dP_dqual(a[1])), mk_clo(L3648, 3, 2, (V[]){a[0], a[3]}));
}
static V L3646(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_dTld_dopen__law(F_Chk_dbook__tld(a[3], a[2]))), mk_clo(L3647, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3645(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3646, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3644(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(a[1]), mk_clo(L3645, 3, 2, (V[]){a[0], a[1]}));
}
static V L3643(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3644, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_ddef(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(S3642()), mk_clo(L3643, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_ddef(V *a) { (void)a; return F_Chk_dP_ddef(a[0]); }
static V F_Chk_dP_ddef_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V v3661 = a4;
V v3662 = FLD(v3661, 0);
return F_Chk_dP_dif(a2, F_Chk_dP_ddef_dfill(a0, a1, a3, v3662), F_Chk_dP_ddef_dnew(a0, a1, a3, v3662, FLD(v3661, 1)));
}
static V W_Chk_dP_ddef_dgo(V *a) { (void)a; return F_Chk_dP_ddef_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V S3663(void) { static V c; return STRC(c, "->"); }
static V S3665(void) { static V c; return STRC(c, "'->' (a def with no return type fills a law; no law named "); }
static V S3666(void) { static V c; return STRC(c, " is in scope)"); }
static V L3670(V *a) {
return F_Chk_dP_ddef_dbody(a[2], a[1], a[0]);
}
static V L3669(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dset__book(F_Chk_dbook__set(a[6], a[5], CN(0, 7, (V[]){F_List_dlength(a[4]), a[3], F_Chk_dhigher0(a[6], F_Chk_dtele__bind(a[4], a[2])), IMM(0), a[1], IMM(0), IMM(0)}))), mk_clo(L3670, 4, 3, (V[]){a[4], a[0], a[5]}));
}
static V L3668(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3669, 7, 6, (V[]){a[0], a[1], a[5], a[2], a[3], a[4]}));
}
static V L3667(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3668, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L3664(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[5], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dfail(F_String_dappend(S3665(), F_String_dappend(a[4], S3666())))), mk_clo(L3667, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V F_Chk_dP_ddef_dnew(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3663()), mk_clo(L3664, 6, 5, (V[]){a2, a0, a4, a3, a1}));
}
static V W_Chk_dP_ddef_dnew(V *a) { (void)a; return F_Chk_dP_ddef_dnew(a[0], a[1], a[2], a[3], a[4]); }
static V S3671(void) { static V c; return STRC(c, ":"); }
static V S3673(void) { static V c; return STRC(c, "import"); }
static V L3677(V *a) {
return F_Chk_dP_dset__book(F_Chk_dbook__push(a[1], a[0]));
}
static V L3676(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3677, 2, 1, (V[]){a[0]}));
}
static V L3675(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[1]), mk_clo(L3676, 2, 1, (V[]){a[0]}));
}
static V L3674(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[3], F_Chk_dP_ddef_dforeign(a[2]), F_Chk_dP_ddef_dvalue(a[2], a[1])), mk_clo(L3675, 3, 2, (V[]){a[2], a[0]}));
}
static V L3672(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3673()), mk_clo(L3674, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_ddef_dbody(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_deat(S3671()), mk_clo(L3672, 4, 3, (V[]){a1, a2, a0}));
}
static V W_Chk_dP_ddef_dbody(V *a) { (void)a; return F_Chk_dP_ddef_dbody(a[0], a[1], a[2]); }
static V L3681(V *a) {
return F_Chk_dP_dset__book(F_Chk_dbook__set(a[2], a[1], F_Chk_dTld_dwith__v(F_Chk_dbook__tld(a[2], a[1]), F_Chk_dhigher0(a[2], F_Chk_dterm__lower(a[2], F_Chk_dhigher0(a[2], a[0]), 0u)))));
}
static V L3680(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcheck__ops(a[1]), mk_clo(L3681, 4, 3, (V[]){a[1], a[0], a[2]}));
}
static V L3679(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3680, 3, 2, (V[]){a[0], a[1]}));
}
static V L3678(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dflatten(a[2], F_Chk_dTC_dvars(a[1])), mk_clo(L3679, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_ddef_dvalue(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbody(0u), mk_clo(L3678, 3, 2, (V[]){a0, a1}));
}
static V W_Chk_dP_ddef_dvalue(V *a) { (void)a; return F_Chk_dP_ddef_dvalue(a[0], a[1]); }
static V F_Chk_dTld_dwith__v(V a0, V a1) {
top:;
V s3682 = a0;
if (TAG(s3682) == 1 && TAG(FLD(s3682, 0)) == 0) {
return CN(0, 7, (V[]){FLD(FLD(s3682, 0), 0), FLD(FLD(s3682, 0), 1), FLD(FLD(s3682, 0), 2), C1(1, a1), FLD(FLD(s3682, 0), 4), FLD(FLD(s3682, 0), 5), FLD(FLD(s3682, 0), 6)});
} else {
return CN(0, 7, (V[]){0u, 0u, C1(8, IMM(0)), C1(1, a1), IMM(0), IMM(0), IMM(0)});
}
}
static V W_Chk_dTld_dwith__v(V *a) { (void)a; return F_Chk_dTld_dwith__v(a[0], a[1]); }
static V F_Chk_dP_dcheck__ops(V a0) {
top:;
return F_Chk_dP_dcheck__ops_dc(F_Chk_dops_dbare(a0));
}
static V W_Chk_dP_dcheck__ops(V *a) { (void)a; return F_Chk_dP_dcheck__ops(a[0]); }
static V F_Chk_dops_dbare(V a0) {
top:;
V s3683 = a0;
if (TAG(s3683) == 4) {
return F_Bool_dpick(F_Nat_dis__eq(F_Chk_dStr_dlast__dot(FLD(s3683, 0)), 0u), C1(1, C3(4, FLD(s3683, 0), FLD(s3683, 1), FLD(s3683, 2))), IMM(0));
} else if (TAG(s3683) == 5) {
{ V t0 = FLD(s3683, 2); a0 = t0; goto top; }
} else if (TAG(s3683) == 6) {
return F_Chk_dops_dfirst(F_Chk_dops_dbares(FLD(s3683, 2)), F_Chk_dops_dbare(F_Chk_dsyn__body(FLD(s3683, 3))));
} else if (TAG(s3683) == 7) {
{ V t0 = FLD(s3683, 0); a0 = t0; goto top; }
} else if (TAG(s3683) == 10) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3683, 0)), F_Chk_dops_dbare(FLD(s3683, 1)));
} else if (TAG(s3683) == 11) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3683, 3)), F_Chk_dops_dbare(F_Chk_dsyn__body(FLD(s3683, 4))));
} else if (TAG(s3683) == 12) {
{ V t0 = F_Chk_dsyn__body(FLD(s3683, 2)); a0 = t0; goto top; }
} else if (TAG(s3683) == 13) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3683, 0)), F_Chk_dops_dbare(FLD(s3683, 1)));
} else if (TAG(s3683) == 14) {
return F_Chk_dops_dbares(FLD(s3683, 1));
} else if (TAG(s3683) == 15) {
return F_Chk_dops_dbares(FLD(s3683, 1));
} else if (TAG(s3683) == 17) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3683, 1)), F_Chk_dops_dbare(FLD(s3683, 2)));
} else if (TAG(s3683) == 19) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3683, 0)), F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3683, 1)), F_Chk_dops_dbare(FLD(s3683, 2))));
} else if (TAG(s3683) == 21) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3683, 0)), F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3683, 1)), F_Chk_dops_dbare(FLD(s3683, 2))));
} else if (TAG(s3683) == 23) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3683, 0)), F_Chk_dops_dbare(FLD(s3683, 1)));
} else if (TAG(s3683) == 3) {
{ V t0 = FLD(s3683, 3); a0 = t0; goto top; }
} else {
return IMM(0);
}
}
static V W_Chk_dops_dbare(V *a) { (void)a; return F_Chk_dops_dbare(a[0]); }
static V F_Chk_dops_dfirst(V a0, V a1) {
top:;
V s3684 = a0;
if (TAG(s3684) == 1) {
return C1(1, FLD(s3684, 0));
} else if ((s3684) == IMM(0)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dops_dfirst(V *a) { (void)a; return F_Chk_dops_dfirst(a[0], a[1]); }
static V F_Chk_dops_dbares(V a0) {
top:;
V s3685 = a0;
if ((s3685) == IMM(0)) {
return IMM(0);
} else if (TAG(s3685) == 1) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3685, 0)), F_Chk_dops_dbares(FLD(s3685, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dops_dbares(V *a) { (void)a; return F_Chk_dops_dbares(a[0]); }
static V F_Chk_dP_dcheck__ops_dc(V a0) {
top:;
V s3686 = a0;
if ((s3686) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s3686) == 1) {
return F_Chk_dP_dthrow(F_Chk_dops_derr(FLD(s3686, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dcheck__ops_dc(V *a) { (void)a; return F_Chk_dP_dcheck__ops_dc(a[0]); }
static V S3688(void) { static V c; return STRC(c, "a type for this operator (write (a "); }
static V S3689(void) { static V c; return STRC(c, " b : Nat))"); }
static V S3690(void) { static V c; return STRC(c, ""); }
static V S3691(void) { static V c; return STRC(c, "Note: we broke this after launch, sorry. Until 2.0.16 a bare operator meant Nat.\012"); }
static V S3692(void) { static V c; return STRC(c, "That was a bug: operators demand annotation. Wrap the expression and it'll work again."); }
static V S3693(void) { static V c; return STRC(c, "a type for this operator"); }
static V F_Chk_dops_derr(V a0) {
top:;
V s3687 = a0;
if (TAG(s3687) == 4) {
return CN(0, 7, (V[]){F_Chk_dbook__nil(), IMM(0), C1(1, F_String_dappend(S3688(), F_String_dappend(F_Chk_dops_dtext(FLD(s3687, 1), FLD(s3687, 0)), S3689()))), IMM(0), FLD(s3687, 1), S3690(), F_String_dappend(S3691(), S3692())});
} else {
return F_Chk_derr0(S3693(), IMM(0), IMM(0));
}
}
static V W_Chk_dops_derr(V *a) { (void)a; return F_Chk_dops_derr(a[0]); }
static V F_Chk_dops_dtext(V a0, V a1) {
top:;
V s3694 = a0;
if (TAG(s3694) == 1) {
return F_String_dtake(F_String_ddrop(FLD(s3694, 0), F_U32_dto__nat(FLD(s3694, 1))), F_Nat_dsub(F_U32_dto__nat(FLD(s3694, 2)), F_U32_dto__nat(FLD(s3694, 1))));
} else if ((s3694) == IMM(0)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dops_dtext(V *a) { (void)a; return F_Chk_dops_dtext(a[0], a[1]); }
static V F_Chk_dTC_dvars(V a0) {
top:;
V s3695 = a0;
if ((s3695) == IMM(0)) {
return IMM(0);
} else if (TAG(s3695) == 1) {
return C2(1, C4(0, FLD(FLD(s3695, 0), 1), FLD(FLD(s3695, 0), 2), IMM(1), FLD(FLD(s3695, 0), 4)), F_Chk_dTC_dvars(FLD(s3695, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dTC_dvars(V *a) { (void)a; return F_Chk_dTC_dvars(a[0]); }
static V S3697(void) { static V c; return STRC(c, "a body (a template is not foreign)"); }
static V L3700(V *a) {
return F_Chk_dP_dset__book(F_Chk_dbook__set(a[2], a[1], F_Chk_dTld_dwith__imps(F_Chk_dbook__tld(a[2], a[1]), a[0])));
}
static V L3699(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3700, 3, 2, (V[]){a[1], a[0]}));
}
static V L3698(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dimports(IMM(0)), mk_clo(L3699, 2, 1, (V[]){a[0]}));
}
static V L3696(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Nat_dis__gt(F_Chk_dTld_dlaw__x(F_Chk_dbook__tld(a[1], a[0])), 0u), F_Chk_dP_dfail(S3697()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3698, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_ddef_dforeign(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3696, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_ddef_dforeign(V *a) { (void)a; return F_Chk_dP_ddef_dforeign(a[0]); }
static V F_Chk_dTld_dwith__imps(V a0, V a1) {
top:;
V s3701 = a0;
if (TAG(s3701) == 1 && TAG(FLD(s3701, 0)) == 0) {
return CN(0, 7, (V[]){FLD(FLD(s3701, 0), 0), FLD(FLD(s3701, 0), 1), FLD(FLD(s3701, 0), 2), FLD(FLD(s3701, 0), 3), FLD(FLD(s3701, 0), 4), FLD(FLD(s3701, 0), 5), C1(1, a1)});
} else {
return CN(0, 7, (V[]){0u, 0u, C1(8, IMM(0)), IMM(0), IMM(0), IMM(0), C1(1, a1)});
}
}
static V W_Chk_dTld_dwith__imps(V *a) { (void)a; return F_Chk_dTld_dwith__imps(a[0], a[1]); }
static V S3702(void) { static V c; return STRC(c, "import"); }
static V L3703(V *a) {
return F_Chk_dP_dif(a[1], F_Chk_dP_dimport1(a[0]), F_Chk_dP_dpure(a[0]));
}
static V F_Chk_dP_dimports(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(S3702()), mk_clo(L3703, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dimports(V *a) { (void)a; return F_Chk_dP_dimports(a[0]); }
static V S3704(void) { static V c; return STRC(c, "\042"); }
static V S3706(void) { static V c; return STRC(c, ""); }
static V S3708(void) { static V c; return STRC(c, "\042"); }
static V S3710(void) { static V c; return STRC(c, ".c"); }
static V S3711(void) { static V c; return STRC(c, ".js"); }
static V S3712(void) { static V c; return STRC(c, "a .c or .js path"); }
static V L3714(V *a) {
return F_Chk_dP_dimports(F_List_dappend(a[1], C2(1, F_String_dappend(a[2], a[0]), IMM(0))));
}
static V L3713(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_ddir(), mk_clo(L3714, 3, 2, (V[]){a[0], a[1]}));
}
static V L3709(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Bool_dor(F_String_dends__with(a[1], S3710()), F_String_dends__with(a[1], S3711())), F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dfail(S3712())), mk_clo(L3713, 3, 2, (V[]){a[1], a[0]}));
}
static V L3707(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3708()), mk_clo(L3709, 3, 2, (V[]){a[0], a[1]}));
}
static V L3705(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_duntil__quote(S3706()), mk_clo(L3707, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dimport1(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_deat(S3704()), mk_clo(L3705, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dimport1(V *a) { (void)a; return F_Chk_dP_dimport1(a[0]); }
static V L3715(V *a) {
return C1(1, C2(0, F_Chk_dPS_ddir(a[0]), a[0]));
}
static V F_Chk_dP_ddir(void) {
top:;
return mk_clo(L3715, 1, 0, 0);
}
static V W_Chk_dP_ddir(V *a) { (void)a; return F_Chk_dP_ddir(); }
static V F_Chk_dPS_ddir(V a0) {
top:;
V v3716 = a0;
return FLD(v3716, 7);
}
static V W_Chk_dPS_ddir(V *a) { (void)a; return F_Chk_dPS_ddir(a[0]); }
static V L3717(V *a) {
return F_Chk_dP_dif(F_Bool_dor(F_U32_dis__eq(a[1], 34u), F_U32_dis__zero(a[1])), F_Chk_dP_dpure(F_String_dreverse(a[0])), F_Chk_dP_duntil__quote_dmore(a[1], a[0]));
}
static V F_Chk_dP_duntil__quote(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3717, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_duntil__quote(V *a) { (void)a; return F_Chk_dP_duntil__quote(a[0]); }
static V L3718(V *a) {
return F_Chk_dP_duntil__quote(C2(1, a[1], a[0]));
}
static V F_Chk_dP_duntil__quote_dmore(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3718, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_duntil__quote_dmore(V *a) { (void)a; return F_Chk_dP_duntil__quote_dmore(a[0], a[1]); }
static V F_Chk_dTld_dlaw__x(V a0) {
top:;
V s3719 = a0;
if (TAG(s3719) == 1 && TAG(FLD(s3719, 0)) == 0) {
return FLD(FLD(s3719, 0), 1);
} else {
return 0u;
}
}
static V W_Chk_dTld_dlaw__x(V *a) { (void)a; return F_Chk_dTld_dlaw__x(a[0]); }
static V S3722(void) { static V c; return STRC(c, "a name"); }
static V S3724(void) { static V c; return STRC(c, "a name for each ~ clause of the law ("); }
static V S3725(void) { static V c; return STRC(c, ")"); }
static V L3728(V *a) {
return F_Chk_dP_ddef_dbody(a[2], a[1], a[0]);
}
static V L3727(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dset__book(F_Chk_dbook__set(a[4], a[3], F_Chk_dTld_dlaw__fill(F_Chk_dbook__tld(a[4], a[3]), F_List_dlength(a[2]), a[1]))), mk_clo(L3728, 4, 3, (V[]){a[2], a[0], a[3]}));
}
static V L3726(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3727, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3723(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Nat_dis__lt(F_List_dlength(a[4]), a[3]), F_Chk_dP_dfail(F_String_dappend(S3724(), F_String_dappend(F_Nat_dshow(a[3]), S3725()))), F_Chk_dP_dpure(IMM(0))), mk_clo(L3726, 5, 4, (V[]){a[0], a[1], a[4], a[2]}));
}
static V L3721(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Chk_dTC_dall__qnt(a[3]), F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dfail(S3722())), mk_clo(L3723, 6, 5, (V[]){a[0], a[1], a[2], a[4], a[3]}));
}
static V L3720(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_dTld_dlaw__x(F_Chk_dbook__tld(a[4], a[3]))), mk_clo(L3721, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V F_Chk_dP_ddef_dfill(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3720, 5, 4, (V[]){a2, a0, a3, a1}));
}
static V W_Chk_dP_ddef_dfill(V *a) { (void)a; return F_Chk_dP_ddef_dfill(a[0], a[1], a[2], a[3]); }
static V F_Chk_dTld_dlaw__fill(V a0, V a1, V a2) {
top:;
V s3729 = a0;
if (TAG(s3729) == 1 && TAG(FLD(s3729, 0)) == 0) {
return CN(0, 7, (V[]){a1, FLD(FLD(s3729, 0), 1), FLD(FLD(s3729, 0), 2), FLD(FLD(s3729, 0), 3), F_Bool_dor(FLD(FLD(s3729, 0), 4), a2), FLD(FLD(s3729, 0), 5), FLD(FLD(s3729, 0), 6)});
} else {
return CN(0, 7, (V[]){a1, 0u, C1(8, IMM(0)), IMM(0), a2, IMM(0), IMM(0)});
}
}
static V W_Chk_dTld_dlaw__fill(V *a) { (void)a; return F_Chk_dTld_dlaw__fill(a[0], a[1], a[2]); }
static V F_Chk_dTC_dall__qnt(V a0) {
top:;
V s3730 = a0;
if ((s3730) == IMM(0)) {
return IMM(1);
} else if (TAG(s3730) == 1 && TAG(FLD(FLD(s3730, 0), 3)) == 8) {
{ V t0 = FLD(s3730, 1); a0 = t0; goto top; }
} else if (TAG(s3730) == 1) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dTC_dall__qnt(V *a) { (void)a; return F_Chk_dTC_dall__qnt(a[0]); }
static V F_Chk_dTld_dopen__law(V a0) {
top:;
V s3731 = a0;
if (TAG(s3731) == 1 && TAG(FLD(s3731, 0)) == 0 && (FLD(FLD(s3731, 0), 3)) == IMM(0) && (FLD(FLD(s3731, 0), 5)) == IMM(0) && (FLD(FLD(s3731, 0), 6)) == IMM(0)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dopen__law(V *a) { (void)a; return F_Chk_dTld_dopen__law(a[0]); }
static V S3732(void) { static V c; return STRC(c, "unsafe"); }
static V S3734(void) { static V c; return STRC(c, "'unsafe' (the one decorator)"); }
static V S3737(void) { static V c; return STRC(c, "def"); }
static V S3739(void) { static V c; return STRC(c, "'def' (@unsafe marks the def below it)"); }
static V L3738(V *a) {
return F_Chk_dP_dif(a[0], F_Chk_dP_ddef(IMM(1)), F_Chk_dP_dfail(S3739()));
}
static V L3736(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3737()), mk_clo(L3738, 1, 0, 0));
}
static V L3735(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3736, 1, 0, 0));
}
static V L3733(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[0], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dfail(S3734())), mk_clo(L3735, 1, 0, 0));
}
static V F_Chk_dP_dunsafe(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(S3732()), mk_clo(L3733, 1, 0, 0));
}
static V W_Chk_dP_dunsafe(V *a) { (void)a; return F_Chk_dP_dunsafe(); }
static V L3740(V *a) {
return C1(1, C2(0, IMM(0), F_Chk_dPS_dset__scope(a[0], IMM(0), 0u, 0u)));
}
static V F_Chk_dP_dreset__scope(void) {
top:;
return mk_clo(L3740, 1, 0, 0);
}
static V W_Chk_dP_dreset__scope(V *a) { (void)a; return F_Chk_dP_dreset__scope(); }
static V F_Chk_dPS_dset__scope(V a0, V a1, V a2, V a3) {
top:;
V v3741 = a0;
return CN(0, 9, (V[]){FLD(v3741, 0), a1, a2, a3, FLD(v3741, 4), FLD(v3741, 5), FLD(v3741, 6), FLD(v3741, 7), FLD(v3741, 8)});
}
static V W_Chk_dPS_dset__scope(V *a) { (void)a; return F_Chk_dPS_dset__scope(a[0], a[1], a[2], a[3]); }
static V F_Chk_dparse__file_dfin(V a0) {
top:;
V s3742 = a0;
if (TAG(s3742) == 0) {
return C1(0, FLD(s3742, 0));
} else if (TAG(s3742) == 1) {
return C1(1, F_Chk_dPS_dbook(F_Pair_dsnd(FLD(s3742, 0))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dparse__file_dfin(V *a) { (void)a; return F_Chk_dparse__file_dfin(a[0]); }
static V F_Main_dchk_dparsed(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s3743 = a5;
if (TAG(s3743) == 0) {
return F_Main_dchk_dfail(FLD(s3743, 0));
} else if (TAG(s3743) == 1) {
return F_IO_dpure(C3(0, F_Bool_dpick(F_String_deq(F_Path_dnorm(a1), F_Path_dnorm(a0)), F_Chk_dmark__base(FLD(s3743, 0), a4), FLD(s3743, 0)), C2(1, C2(0, F_Path_dnorm(a1), a2), a3), a4));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dparsed(V *a) { (void)a; return F_Main_dchk_dparsed(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dmark__base(V a0, V a1) {
top:;
return F_Chk_dmark__base_dgo(F_Chk_dbook__order(a0), 0u, a1, a0);
}
static V W_Chk_dmark__base(V *a) { (void)a; return F_Chk_dmark__base(a[0], a[1]); }
static V F_Chk_dmark__base_dgo(V a0, V a1, V a2, V a3) {
top:;
V s3744 = a0;
if ((s3744) == IMM(0)) {
return a3;
} else if (TAG(s3744) == 1) {
{ V t0 = FLD(s3744, 1); V t1 = nat_addk(a1, 1); V t2 = a2; V t3 = F_Bool_dpick(F_Nat_dis__ge(a1, a2), F_Chk_dmark__base_done(a3, FLD(s3744, 0)), a3); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dmark__base_dgo(V *a) { (void)a; return F_Chk_dmark__base_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dmark__base_done(V a0, V a1) {
top:;
return F_Chk_dmark__base_dtld(a0, a1, F_Chk_dbook__tld(a0, a1));
}
static V W_Chk_dmark__base_done(V *a) { (void)a; return F_Chk_dmark__base_done(a[0], a[1]); }
static V F_Chk_dmark__base_dtld(V a0, V a1, V a2) {
top:;
V s3745 = a2;
if (TAG(s3745) == 1 && TAG(FLD(s3745, 0)) == 0) {
return F_Chk_dbook__set(a0, a1, CN(0, 7, (V[]){FLD(FLD(s3745, 0), 0), FLD(FLD(s3745, 0), 1), FLD(FLD(s3745, 0), 2), FLD(FLD(s3745, 0), 3), FLD(FLD(s3745, 0), 4), IMM(1), FLD(FLD(s3745, 0), 6)}));
} else if (TAG(s3745) == 1 && TAG(FLD(s3745, 0)) == 1) {
return F_Chk_dbook__set(a0, a1, CN(1, 5, (V[]){FLD(FLD(s3745, 0), 0), FLD(FLD(s3745, 0), 1), FLD(FLD(s3745, 0), 2), FLD(FLD(s3745, 0), 3), IMM(1)}));
} else if ((s3745) == IMM(0)) {
return a0;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dmark__base_dtld(V *a) { (void)a; return F_Chk_dmark__base_dtld(a[0], a[1], a[2]); }
static V F_Chk_dbook__len(V a0) {
top:;
return F_List_dlength(F_Chk_dbook__order(a0));
}
static V W_Chk_dbook__len(V *a) { (void)a; return F_Chk_dbook__len(a[0]); }
static V F_CS_dmark(V a0, V a1) {
top:;
V v3746 = a0;
return C3(0, FLD(v3746, 0), C2(1, C2(0, a1, F_Main_dchk_dloading()), FLD(v3746, 1)), FLD(v3746, 2));
}
static V W_CS_dmark(V *a) { (void)a; return F_CS_dmark(a[0], a[1]); }
static V S3747(void) { static V c; return STRC(c, "u{0}"); }
static V F_Main_dchk_dloading(void) {
top:;
return S3747();
}
static V W_Main_dchk_dloading(V *a) { (void)a; return F_Main_dchk_dloading(); }
static V L3749(V *a) {
return F_Main_dchk_dimps_dnext(a[5], a[4], a[3], a[2], a[1], a[0], a[6]);
}
static V F_Main_dchk_dimps(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s3748 = a5;
if ((s3748) == IMM(0)) {
return F_IO_dpure(C2(0, a6, a7));
} else if (TAG(s3748) == 1) {
return F_IO_dbind(F_Main_dchk_dimp(a0, a1, a2, a3, a4, FLD(s3748, 0), a6, a7), mk_clo(L3749, 7, 6, (V[]){FLD(s3748, 1), a4, a3, a2, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dimps(V *a) { (void)a; return F_Main_dchk_dimps(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V F_Main_dchk_dimps_dnext(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v3750 = a6;
return F_Main_dchk_dimps(a0, a1, a2, a3, a4, a5, FLD(v3750, 0), FLD(v3750, 1));
}
static V W_Main_dchk_dimps_dnext(V *a) { (void)a; return F_Main_dchk_dimps_dnext(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Main_dchk_dimp(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V v3751 = a5;
V v3752 = C3(1, a4, FLD(v3751, 2), FLD(v3751, 2));
V v3753 = F_Path_dnorm(FLD(v3751, 0));
return F_Main_dchk_dimp_dgo(a0, a1, a2, a3, v3752, v3753, FLD(v3751, 1), FLD(v3751, 0), a6, a7, F_String_dis__empty(FLD(v3751, 1)));
}
static V W_Main_dchk_dimp(V *a) { (void)a; return F_Main_dchk_dimp(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S3755(void) { static V c; return STRC(c, ""); }
static V L3756(V *a) {
return F_IO_dpure(C2(0, a[1], a[0]));
}
static V S3757(void) { static V c; return STRC(c, ".bend"); }
static V F_Main_dchk_dimp_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10) {
top:;
V s3754 = a10;
if ((s3754) == IMM(1)) {
return F_IO_dbind(F_Main_dchk_dload(a0, a1, a1, S3755(), a4, a8), mk_clo(L3756, 2, 1, (V[]){a9}));
} else if ((s3754) == IMM(0)) {
return F_Main_dchk_dimp_drel(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, F_String_dends__with(a5, S3757()));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dimp_dgo(V *a) { (void)a; return F_Main_dchk_dimp_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10]); }
static V S3759(void) { static V c; return STRC(c, "an import of a .bend file"); }
static V S3760(void) { static V c; return STRC(c, "'"); }
static V S3761(void) { static V c; return STRC(c, "'"); }
static V S3763(void) { static V c; return STRC(c, "/"); }
static V L3768(V *a) {
return F_IO_dpure(C2(0, a[3], F_List_dappend(a[2], C2(1, C2(0, a[1], a[0]), IMM(0)))));
}
static V L3767(V *a) {
return F_IO_dbind(F_Main_dchk_dload(a[6], a[5], a[7], a[4], a[3], a[2]), mk_clo(L3768, 4, 3, (V[]){a[4], a[0], a[1]}));
}
static V F_Main_dchk_dimp_drel(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10) {
top:;
V s3758 = a10;
if ((s3758) == IMM(0)) {
return F_Main_dchk_dfail(F_Chk_derr0(S3759(), C1(1, F_String_dappend(S3760(), F_String_dappend(a7, S3761()))), a4));
} else if ((s3758) == IMM(1)) {
V v3762 = F_String_dstarts__with(a5, S3763());
V v3764 = F_Main_dchk_dis__hub(a5);
V v3765 = F_Bool_dpick(F_Bool_dor(v3762, v3764), a5, F_Path_djoin(F_Path_ddirname(a3), a5));
V v3766 = F_String_dtake(v3765, F_Nat_dsub(F_String_dlength(v3765), 5u));
return F_IO_dbind(F_Bool_dpick(v3764, F_Main_dchk_dhub(a5), F_IO_dpure(F_Bool_dpick(v3762, a5, F_String_dappend(a2, a5)))), mk_clo(L3767, 8, 7, (V[]){a6, a9, a8, a4, v3766, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dimp_drel(V *a) { (void)a; return F_Main_dchk_dimp_drel(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10]); }
static V S3770(void) { static V c; return STRC(c, "BEND_HUB"); }
static V S3773(void) { static V c; return STRC(c, "/"); }
static V L3772(V *a) {
return F_IO_dpure(F_String_dappend(a[1], F_String_dappend(S3773(), a[0])));
}
static V L3771(V *a) {
return F_IO_dbind(F_IO_dtry(F_Hub_densure(a[1], F_Main_dhub_durl(a[2]), a[0])), mk_clo(L3772, 3, 2, (V[]){a[0], a[1]}));
}
static V L3769(V *a) {
return F_IO_dbind(F_IO_dget__env(S3770()), mk_clo(L3771, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Main_dchk_dhub(V a0) {
top:;
return F_IO_dbind(F_Main_dlib(), mk_clo(L3769, 2, 1, (V[]){a0}));
}
static V W_Main_dchk_dhub(V *a) { (void)a; return F_Main_dchk_dhub(a[0]); }
static V S3775(void) { static V c; return STRC(c, "."); }
static V S3776(void) { static V c; return STRC(c, "/"); }
static V S3777(void) { static V c; return STRC(c, "/"); }
static V F_Path_ddirname(V a0) {
top:;
V v3774 = F_Mod_ddir(a0);
return F_Bool_dpick(F_String_dis__empty(v3774), S3775(), F_Bool_dpick(F_String_deq(v3774, S3776()), S3777(), F_String_dtake(v3774, F_Nat_dsub(F_String_dlength(v3774), 1u))));
}
static V W_Path_ddirname(V *a) { (void)a; return F_Path_ddirname(a[0]); }
static V S3778(void) { static V c; return STRC(c, "/"); }
static V F_Path_djoin(V a0, V a1) {
top:;
return F_Path_dnorm(F_String_dappend(a0, F_String_dappend(S3778(), a1)));
}
static V W_Path_djoin(V *a) { (void)a; return F_Path_djoin(a[0], a[1]); }
static V S3779(void) { static V c; return STRC(c, "0x"); }
static V F_Main_dchk_dis__hub(V a0) {
top:;
return F_Bool_dand(F_String_dstarts__with(a0, S3779()), F_Main_dchk_dis__hub_dhex(F_String_ddrop(a0, 2u)));
}
static V W_Main_dchk_dis__hub(V *a) { (void)a; return F_Main_dchk_dis__hub(a[0]); }
static V F_Main_dchk_dis__hub_dhex(V a0) {
top:;
V s3780 = a0;
if (TAG(s3780) == 1) {
return F_Bool_dor(F_U32_dis__eq(FLD(s3780, 0), 47u), F_Bool_dand(F_Bool_dor(F_Char_dis__digit(FLD(s3780, 0)), F_Bool_dand(F_U32_dis__ge(FLD(s3780, 0), 97u), F_U32_dis__le(FLD(s3780, 0), 102u))), F_Main_dchk_dis__hub_dhex(FLD(s3780, 1))));
} else if ((s3780) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dis__hub_dhex(V *a) { (void)a; return F_Main_dchk_dis__hub_dhex(a[0]); }
static V S3781(void) { static V c; return STRC(c, "r"); }
static V L3782(V *a) {
return F_Main_dread__opt_dopen(a[0]);
}
static V F_Main_dread__opt(V a0) {
top:;
return F_IO_dbind(F_File_dopen(a0, S3781()), mk_clo(L3782, 1, 0, 0));
}
static V W_Main_dread__opt(V *a) { (void)a; return F_Main_dread__opt(a[0]); }
static V L3784(V *a) {
return F_Main_dread__opt_dfin(a[0]);
}
static V F_Main_dread__opt_dopen(V a0) {
top:;
V s3783 = a0;
if (TAG(s3783) == 1) {
return F_IO_dbind(F_IO_dread__all(FLD(s3783, 0)), mk_clo(L3784, 1, 0, 0));
} else if (TAG(s3783) == 0) {
return F_IO_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dread__opt_dopen(V *a) { (void)a; return F_Main_dread__opt_dopen(a[0]); }
static V L3786(V *a) {
return F_IO_dpure(F_Main_dread__opt_dres(a[0]));
}
static V F_Main_dread__opt_dfin(V a0) {
top:;
V v3785 = a0;
return F_IO_dbind(F_File_dclose(FLD(v3785, 0)), mk_clo(L3786, 2, 1, (V[]){FLD(v3785, 1)}));
}
static V W_Main_dread__opt_dfin(V *a) { (void)a; return F_Main_dread__opt_dfin(a[0]); }
static V F_Main_dread__opt_dres(V a0) {
top:;
V s3787 = a0;
if (TAG(s3787) == 1) {
return C1(1, FLD(s3787, 0));
} else if (TAG(s3787) == 0) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Main_dread__opt_dres(V *a) { (void)a; return F_Main_dread__opt_dres(a[0]); }
static V F_CS_dat__end(V a0) {
top:;
V v3788 = a0;
return C3(0, FLD(v3788, 0), FLD(v3788, 1), F_Chk_dbook__len(FLD(v3788, 0)));
}
static V W_CS_dat__end(V *a) { (void)a; return F_CS_dat__end(a[0]); }
static V S3791(void) { static V c; return STRC(c, "All terms check.\012"); }
static V F_Main_dcheck__only_dfin(V a0) {
top:;
V v3789 = a0;
V v3790 = F_Chk_dreport(FLD(v3789, 0), FLD(v3789, 1));
return F_Bool_dpick(F_List_dis__empty(v3790), F_IO_dwrite(S3791()), F_IO_dwrite(F_Chk_dreport__text(v3790)));
}
static V W_Main_dcheck__only_dfin(V *a) { (void)a; return F_Main_dcheck__only_dfin(a[0]); }
static V S3793(void) { static V c; return STRC(c, "bendc: parse error: "); }
static V F_Main_dast(V a0) {
top:;
V s3792 = a0;
if (TAG(s3792) == 0) {
return F_IO_ddie(1u, F_String_dappend(S3793(), FLD(s3792, 0)));
} else if (TAG(s3792) == 1) {
return F_IO_dwrite(F_Decls_dshow(FLD(s3792, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dast(V *a) { (void)a; return F_Main_dast(a[0]); }
static V F_Decls_dshow(V a0) {
top:;
return F_Decls_dshow_dgo(a0);
}
static V W_Decls_dshow(V *a) { (void)a; return F_Decls_dshow(a[0]); }
static V S3795(void) { static V c; return STRC(c, ""); }
static V S3796(void) { static V c; return STRC(c, "\012"); }
static V F_Decls_dshow_dgo(V a0) {
top:;
V s3794 = a0;
if ((s3794) == IMM(0)) {
return S3795();
} else if (TAG(s3794) == 1) {
return F_String_dappend(F_Decl_dshow(FLD(s3794, 0)), F_String_dappend(S3796(), F_Decls_dshow_dgo(FLD(s3794, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Decls_dshow_dgo(V *a) { (void)a; return F_Decls_dshow_dgo(a[0]); }
static V S3798(void) { static V c; return STRC(c, "def "); }
static V S3799(void) { static V c; return STRC(c, "("); }
static V S3800(void) { static V c; return STRC(c, ") = "); }
static V S3801(void) { static V c; return STRC(c, "eff "); }
static V S3802(void) { static V c; return STRC(c, "("); }
static V S3803(void) { static V c; return STRC(c, ")"); }
static V S3804(void) { static V c; return STRC(c, "law "); }
static V S3805(void) { static V c; return STRC(c, "("); }
static V S3806(void) { static V c; return STRC(c, ")"); }
static V S3807(void) { static V c; return STRC(c, "type "); }
static V S3808(void) { static V c; return STRC(c, " "); }
static V S3809(void) { static V c; return STRC(c, "import "); }
static V S3810(void) { static V c; return STRC(c, " as "); }
static V F_Decl_dshow(V a0) {
top:;
V s3797 = a0;
if (TAG(s3797) == 0) {
return F_String_dappend(S3798(), F_String_dappend(FLD(s3797, 0), F_String_dappend(S3799(), F_String_dappend(F_Params_dshow(FLD(s3797, 1)), F_String_dappend(S3800(), F_Expr_dshow(FLD(s3797, 2)))))));
} else if (TAG(s3797) == 1) {
return F_String_dappend(S3801(), F_String_dappend(FLD(s3797, 0), F_String_dappend(S3802(), F_String_dappend(F_Params_dshow(FLD(s3797, 1)), S3803()))));
} else if (TAG(s3797) == 2) {
return F_String_dappend(S3804(), F_String_dappend(FLD(s3797, 0), F_String_dappend(S3805(), F_String_dappend(F_Params_dshow(FLD(s3797, 1)), S3806()))));
} else if (TAG(s3797) == 3) {
return F_String_dappend(S3807(), F_String_dappend(FLD(s3797, 0), F_String_dappend(S3808(), F_Ctors_dshow(FLD(s3797, 2)))));
} else if (TAG(s3797) == 4) {
return F_String_dappend(S3809(), F_String_dappend(FLD(s3797, 0), F_String_dappend(S3810(), FLD(s3797, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Decl_dshow(V *a) { (void)a; return F_Decl_dshow(a[0]); }
static V S3812(void) { static V c; return STRC(c, ""); }
static V S3813(void) { static V c; return STRC(c, " "); }
static V F_Ctors_dshow(V a0) {
top:;
V s3811 = a0;
if ((s3811) == IMM(0)) {
return S3812();
} else if (TAG(s3811) == 1) {
return F_String_dappend(F_Ctor_dshow(FLD(s3811, 0)), F_String_dappend(S3813(), F_Ctors_dshow(FLD(s3811, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Ctors_dshow(V *a) { (void)a; return F_Ctors_dshow(a[0]); }
static V S3815(void) { static V c; return STRC(c, "{"); }
static V S3816(void) { static V c; return STRC(c, "}"); }
static V F_Ctor_dshow(V a0) {
top:;
V v3814 = a0;
return F_String_dappend(FLD(v3814, 0), F_String_dappend(S3815(), F_String_dappend(F_Fields_dshow(FLD(v3814, 1)), S3816())));
}
static V W_Ctor_dshow(V *a) { (void)a; return F_Ctor_dshow(a[0]); }
static V S3818(void) { static V c; return STRC(c, ""); }
static V S3819(void) { static V c; return STRC(c, ":"); }
static V S3820(void) { static V c; return STRC(c, " "); }
static V F_Fields_dshow(V a0) {
top:;
V s3817 = a0;
if ((s3817) == IMM(0)) {
return S3818();
} else if (TAG(s3817) == 1) {
return F_String_dappend(FLD(FLD(s3817, 0), 0), F_String_dappend(S3819(), F_String_dappend(F_Expr_dshow(FLD(FLD(s3817, 0), 1)), F_String_dappend(S3820(), F_Fields_dshow(FLD(s3817, 1))))));
} else { bend_fail("incomplete match"); }
}
static V W_Fields_dshow(V *a) { (void)a; return F_Fields_dshow(a[0]); }
static V S3822(void) { static V c; return STRC(c, ""); }
static V S3823(void) { static V c; return STRC(c, " "); }
static V F_Params_dshow(V a0) {
top:;
V s3821 = a0;
if ((s3821) == IMM(0)) {
return S3822();
} else if (TAG(s3821) == 1) {
return F_String_dappend(F_Param_dshow(FLD(s3821, 0)), F_String_dappend(S3823(), F_Params_dshow(FLD(s3821, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Params_dshow(V *a) { (void)a; return F_Params_dshow(a[0]); }
static V S3825(void) { static V c; return STRC(c, ":"); }
static V F_Param_dshow(V a0) {
top:;
V v3824 = a0;
return F_String_dappend(F_U32_dshow(FLD(v3824, 1)), F_String_dappend(FLD(v3824, 0), F_String_dappend(S3825(), FLD(v3824, 2))));
}
static V W_Param_dshow(V *a) { (void)a; return F_Param_dshow(a[0]); }
static V S3827(void) { static V c; return STRC(c, ""); }
static V F_Toks_dshow(V a0) {
top:;
V s3826 = a0;
if ((s3826) == IMM(0)) {
return S3827();
} else if (TAG(s3826) == 1) {
return F_String_dappend(F_Tok_dshow(FLD(s3826, 0)), F_Toks_dshow(FLD(s3826, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Toks_dshow(V *a) { (void)a; return F_Toks_dshow(a[0]); }
static V S3829(void) { static V c; return STRC(c, " "); }
static V S3830(void) { static V c; return STRC(c, ""); }
static V F_Tok_dshow(V a0) {
top:;
V v3828 = a0;
return F_String_dappend(F_Bool_dpick(FLD(v3828, 1), S3829(), S3830()), F_TK_dshow(FLD(v3828, 0)));
}
static V W_Tok_dshow(V *a) { (void)a; return F_Tok_dshow(a[0]); }
static V E_IO_dprint(V *a) { return io_req(CID_IO_PRINT, 2, (V[]){a[0], a[2]}); }
static V F_IO_dprint(V a0) { return mk_clo(E_IO_dprint, 3, 1, (V[]){a0}); }
static V W_IO_dprint(V *a) { (void)a; return F_IO_dprint(a[0]); }
static V E_IO_dargs(V *a) { return io_req(CID_IO_ARGS, 1, (V[]){a[1]}); }
static V F_IO_dargs(void) { return mk_clo(E_IO_dargs, 2, 0, 0); }
static V W_IO_dargs(V *a) { (void)a; return F_IO_dargs(); }

int main(int argc, char **argv) { return bend_run(argc, argv, F_main); }

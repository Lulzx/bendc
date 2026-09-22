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
static V F_Chk_denv__get_dif(V a0, V a1, V a2, V a3);
static V W_Chk_denv__get_dif(V *a);
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
static V S94(void);
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
static V S105(void);
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
static V S114(void);
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
static V S173(void);
static V W_Chk_dterm__key(V *a);
static V F_String_dappend(V a0, V a1);
static V W_String_dappend(V *a);
static V F_Chk_dshow_dtext(V a0);
static V S176(void);
static V W_Chk_dshow_dtext(V *a);
static V F_Chk_dshow_dchr(V a0, V a1);
static V S177(void);
static V S178(void);
static V S179(void);
static V S180(void);
static V S181(void);
static V S182(void);
static V S183(void);
static V W_Chk_dshow_dchr(V *a);
static V F_Chk_dStr_dchr(V a0);
static V W_Chk_dStr_dchr(V *a);
static V F_Chk_dU32_dshow__hex(V a0);
static V S184(void);
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
static V S191(void);
static V S192(void);
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
static V S200(void);
static V S201(void);
static V S202(void);
static V W_Chk_dquant__show(V *a);
static V F_Chk_dshow_dqua(V a0);
static V S204(void);
static V S205(void);
static V S206(void);
static V W_Chk_dshow_dqua(V *a);
static V F_Chk_dhas__fun_dadt(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dhas__fun_dadt(V *a);
static V F_Chk_dStr_dhas(V a0, V a1);
static V W_Chk_dStr_dhas(V *a);
static V F_Chk_dStr_dhas_dif(V a0, V a1, V a2);
static V W_Chk_dStr_dhas_dif(V *a);
static V F_Chk_dhas__fun_dadt_dc(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Chk_dhas__fun_dadt_dc(V *a);
static V F_Chk_dhas__fun_dcs(V a0);
static V W_Chk_dhas__fun_dcs(V *a);
static V F_Chk_dhas__fun_dctrs(V a0, V a1, V a2, V a3);
static V L212(V *a);
static V W_Chk_dhas__fun_dctrs(V *a);
static V F_Chk_dhas__fun_dfill(V a0, V a1, V a2);
static V W_Chk_dhas__fun_dfill(V *a);
static V F_Chk_dAll_db(V a0);
static V W_Chk_dAll_db(V *a);
static V F_Chk_dhas__fun_dfields(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dhas__fun_dfields(V *a);
static V F_Chk_dhas__fun_dfield(V a0, V a1, V a2, V a3, V a4);
static V L217(V *a);
static V W_Chk_dhas__fun_dfield(V *a);
static V F_Chk_dLazy_dor(V a0, V a1);
static V W_Chk_dLazy_dor(V *a);
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
static V S223(void);
static V W_Chk_dvalid_dio(V *a);
static V F_Chk_dvalid_dio_dbase(V a0);
static V W_Chk_dvalid_dio_dbase(V *a);
static V F_Bool_dnot(V a0);
static V W_Bool_dnot(V *a);
static V F_Main_dchecked_dgo(V a0, V a1, V a2, V a3);
static V W_Main_dchecked_dgo(V *a);
static V F_Main_dbuild(V a0, V a1);
static V L227(V *a);
static V L228(V *a);
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
static V S242(void);
static V S243(void);
static V S244(void);
static V S245(void);
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
static V S252(void);
static V S253(void);
static V S254(void);
static V S255(void);
static V S256(void);
static V S257(void);
static V S258(void);
static V S259(void);
static V S260(void);
static V S261(void);
static V S262(void);
static V S263(void);
static V S264(void);
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
static V S290(void);
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
static V S308(void);
static V W_Lay_dtoks(V *a);
static V F_Lay_dis__op(V a0);
static V S310(void);
static V S311(void);
static V S312(void);
static V S313(void);
static V S314(void);
static V S315(void);
static V S316(void);
static V S317(void);
static V S318(void);
static V S319(void);
static V S320(void);
static V S321(void);
static V S322(void);
static V W_Lay_dis__op(V *a);
static V F_List_dcontains(V a1, V a2, V a3);
static V W_List_dcontains(V *a);
static V F_Lay_dis__sym(V a0, V a1);
static V W_Lay_dis__sym(V *a);
static V F_Str_deq(V a0, V a1);
static V W_Str_deq(V *a);
static V F_Lay_ddelta(V a0);
static V S325(void);
static V S326(void);
static V S327(void);
static V S328(void);
static V S329(void);
static V S330(void);
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
static V L342(V *a);
static V L343(V *a);
static V W_P_ddecls(V *a);
static V F_P_dtok__kind(V a0);
static V W_P_dtok__kind(V *a);
static V F_P_dstuck(V a0);
static V W_P_dstuck(V *a);
static V F_P_ddecls_dgo(V a0);
static V L347(V *a);
static V L348(V *a);
static V W_P_ddecls_dgo(V *a);
static V F_Parser_dpure(V a1);
static V L349(V *a);
static V W_Parser_dpure(V *a);
static V F_Parser_dbind(V a2, V a3);
static V L350(V *a);
static V W_Parser_dbind(V *a);
static V F_Parser_dgo(V a2, V a3);
static V W_Parser_dgo(V *a);
static V F_P_ddecl(void);
static V L352(V *a);
static V S353(void);
static V W_P_ddecl(V *a);
static V F_P_dtok__is(V a0, V a1);
static V W_P_dtok__is(V *a);
static V F_P_ddecl_dat(V a0, V a1);
static V L356(V *a);
static V L357(V *a);
static V L358(V *a);
static V S359(void);
static V S360(void);
static V S361(void);
static V S362(void);
static V W_P_ddecl_dat(V *a);
static V F_P_dtok__which__id(V a0, V a1);
static V W_P_dtok__which__id(V *a);
static V F_P_dwhich(V a0, V a1);
static V W_P_dwhich(V *a);
static V F_P_dwhich_dif(V a0, V a1, V a2);
static V W_P_dwhich_dif(V *a);
static V F_P_ddecl_dgo(V a0);
static V S367(void);
static V L368(V *a);
static V S369(void);
static V S370(void);
static V W_P_ddecl_dgo(V *a);
static V F_P_derr(V a0);
static V L371(V *a);
static V W_P_derr(V *a);
static V F_P_derr_dgo(V a0, V a1);
static V S373(void);
static V S374(void);
static V S375(void);
static V S376(void);
static V S377(void);
static V W_P_derr_dgo(V *a);
static V F_TK_dshow(V a0);
static V S379(void);
static V S380(void);
static V S381(void);
static V S382(void);
static V S383(void);
static V S384(void);
static V S385(void);
static V S386(void);
static V S387(void);
static V S388(void);
static V S389(void);
static V S390(void);
static V W_TK_dshow(V *a);
static V F_P_dimport(void);
static V L391(V *a);
static V L392(V *a);
static V L393(V *a);
static V S394(void);
static V L395(V *a);
static V L396(V *a);
static V W_P_dimport(V *a);
static V F_P_dskip__line(void);
static V L397(V *a);
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
static V L403(V *a);
static V S404(void);
static V W_P_dimport_dalias(V *a);
static V F_P_dident(void);
static V L405(V *a);
static V W_P_dident(V *a);
static V F_P_dident_dk(V a0);
static V L407(V *a);
static V S408(void);
static V L409(V *a);
static V S410(void);
static V W_P_dident_dk(V *a);
static V F_P_dskip(void);
static V L411(V *a);
static V W_P_dskip(V *a);
static V F_P_dskip_dgo(V a0);
static V W_P_dskip_dgo(V *a);
static V F_P_dskip_dif(V a0, V a1, V a2);
static V W_P_dskip_dif(V *a);
static V F_P_dpeek(void);
static V L414(V *a);
static V W_P_dpeek(V *a);
static V F_P_dpeek_dgo(V a0);
static V W_P_dpeek_dgo(V *a);
static V F_P_deof__tok(void);
static V W_P_deof__tok(V *a);
static V F_P_dimport_dpath(void);
static V L416(V *a);
static V W_P_dimport_dpath(V *a);
static V F_P_dimport_dpath_dgo(V a0);
static V S418(void);
static V S419(void);
static V W_P_dimport_dpath_dgo(V *a);
static V F_P_dimport_dpath_dcat(V a0, V a1);
static V W_P_dimport_dpath_dcat(V *a);
static V F_P_dimport_dpath_did(V a0, V a1, V a2, V a3, V a4);
static V S422(void);
static V W_P_dimport_dpath_did(V *a);
static V F_P_dlaw(void);
static V L423(V *a);
static V L424(V *a);
static V S425(void);
static V L426(V *a);
static V L427(V *a);
static V L428(V *a);
static V W_P_dlaw(V *a);
static V F_P_dlaw_dlines(void);
static V L429(V *a);
static V L430(V *a);
static V W_P_dlaw_dlines(V *a);
static V F_P_dis__de(V a0);
static V W_P_dis__de(V *a);
static V F_P_dlaw_dgo(V a0, V a1);
static V L433(V *a);
static V S434(void);
static V W_P_dlaw_dgo(V *a);
static V F_P_dlaw_dline(V a0);
static V L436(V *a);
static V L437(V *a);
static V L438(V *a);
static V L439(V *a);
static V L440(V *a);
static V W_P_dlaw_dline(V *a);
static V F_P_dparam(void);
static V L441(V *a);
static V L442(V *a);
static V L443(V *a);
static V L444(V *a);
static V L445(V *a);
static V S446(void);
static V W_P_dparam(V *a);
static V F_P_dparam_dty(V a0, V a1, V a2);
static V L448(V *a);
static V L449(V *a);
static V S450(void);
static V W_P_dparam_dty(V *a);
static V F_P_dhead(V a0);
static V S452(void);
static V W_P_dhead(V *a);
static V F_P_dexpr(void);
static V W_P_dexpr(V *a);
static V F_P_dbin(V a0);
static V L453(V *a);
static V W_P_dbin(V *a);
static V F_P_dbin_dloop(V a0, V a1);
static V L454(V *a);
static V W_P_dbin_dloop(V *a);
static V F_P_dtok__op(V a0);
static V S456(void);
static V W_P_dtok__op(V *a);
static V F_P_dops(void);
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
static V S474(void);
static V S475(void);
static V S476(void);
static V S477(void);
static V S478(void);
static V W_P_dops(V *a);
static V F_P_dop__find(V a0, V a1);
static V S480(void);
static V W_P_dop__find(V *a);
static V F_P_dop__find_dif(V a0, V a1, V a2, V a3);
static V W_P_dop__find_dif(V *a);
static V F_P_dbin_dloop_dop(V a0, V a1, V a2);
static V W_P_dbin_dloop_dop(V *a);
static V F_P_dbin_dloop_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V L484(V *a);
static V L485(V *a);
static V W_P_dbin_dloop_dgo(V *a);
static V F_P_dmk__bin(V a0, V a1, V a2);
static V S486(void);
static V S487(void);
static V S488(void);
static V S489(void);
static V S490(void);
static V S491(void);
static V S492(void);
static V S493(void);
static V W_P_dmk__bin(V *a);
static V F_P_dmk__bin_dgo(V a0, V a1, V a2, V a3);
static V S495(void);
static V S496(void);
static V S497(void);
static V S498(void);
static V S499(void);
static V S500(void);
static V S501(void);
static V S502(void);
static V W_P_dmk__bin_dgo(V *a);
static V F_P_dterm(void);
static V L503(V *a);
static V W_P_dterm(V *a);
static V F_P_dpostfix(V a0);
static V L504(V *a);
static V W_P_dpostfix(V *a);
static V F_P_dpostfix_dt(V a0, V a1);
static V S505(void);
static V S506(void);
static V S507(void);
static V W_P_dpostfix_dt(V *a);
static V F_P_dtok__which(V a0, V a1);
static V W_P_dtok__which(V *a);
static V F_P_dtok__sp(V a0);
static V W_P_dtok__sp(V *a);
static V F_P_dpostfix_dk(V a0, V a1);
static V L511(V *a);
static V S512(void);
static V L513(V *a);
static V L514(V *a);
static V L515(V *a);
static V L516(V *a);
static V S517(void);
static V L518(V *a);
static V S519(void);
static V S520(void);
static V W_P_dpostfix_dk(V *a);
static V F_P_dexpect(V a0);
static V L521(V *a);
static V W_P_dexpect(V *a);
static V F_P_dexpect_dif(V a0, V a1);
static V S523(void);
static V S524(void);
static V W_P_dexpect_dif(V *a);
static V F_P_dlist(V a0);
static V L525(V *a);
static V W_P_dlist(V *a);
static V F_P_dlist_dstuck(V a0, V a1, V a2);
static V S527(void);
static V L528(V *a);
static V W_P_dlist_dstuck(V *a);
static V F_P_dlist_dgo(V a0, V a1);
static V L530(V *a);
static V W_P_dlist_dgo(V *a);
static V F_P_dlist_ditem(V a0);
static V L531(V *a);
static V S532(void);
static V L533(V *a);
static V L534(V *a);
static V W_P_dlist_ditem(V *a);
static V F_P_dlist_dmore(V a0, V a1);
static V L536(V *a);
static V W_P_dlist_dmore(V *a);
static V F_P_deat(V a0);
static V L537(V *a);
static V W_P_deat(V *a);
static V F_P_deat_dif(V a0);
static V L539(V *a);
static V W_P_deat_dif(V *a);
static V F_P_dprimary(void);
static V L540(V *a);
static V W_P_dprimary(V *a);
static V F_P_dprimary_dk(V a0);
static V L542(V *a);
static V L543(V *a);
static V L544(V *a);
static V L545(V *a);
static V L546(V *a);
static V L547(V *a);
static V L548(V *a);
static V L549(V *a);
static V L550(V *a);
static V S551(void);
static V S552(void);
static V S553(void);
static V S554(void);
static V S555(void);
static V S556(void);
static V S557(void);
static V S558(void);
static V S559(void);
static V S560(void);
static V L561(V *a);
static V S562(void);
static V W_P_dprimary_dk(V *a);
static V F_P_dprimary_dsym(V a0);
static V L564(V *a);
static V L565(V *a);
static V L566(V *a);
static V L567(V *a);
static V L568(V *a);
static V L569(V *a);
static V L570(V *a);
static V L571(V *a);
static V L572(V *a);
static V S573(void);
static V S574(void);
static V L575(V *a);
static V S576(void);
static V W_P_dprimary_dsym(V *a);
static V F_P_damp_dgo(V a0);
static V L578(V *a);
static V S579(void);
static V W_P_damp_dgo(V *a);
static V F_P_ddep(void);
static V S580(void);
static V L581(V *a);
static V S582(void);
static V L583(V *a);
static V L584(V *a);
static V S585(void);
static V L586(V *a);
static V L587(V *a);
static V S588(void);
static V W_P_ddep(V *a);
static V F_P_dneg(V a0);
static V S590(void);
static V W_P_dneg(V *a);
static V F_P_dbrace(void);
static V L591(V *a);
static V L592(V *a);
static V S593(void);
static V W_P_dbrace(V *a);
static V F_P_dbrace_dgo(V a0);
static V L595(V *a);
static V S596(void);
static V L597(V *a);
static V S598(void);
static V W_P_dbrace_dgo(V *a);
static V F_P_dbrace_dbody(void);
static V L599(V *a);
static V L600(V *a);
static V S601(void);
static V S602(void);
static V S603(void);
static V W_P_dbrace_dbody(V *a);
static V F_P_dbrace_dtail(V a0, V a1);
static V L605(V *a);
static V L606(V *a);
static V S607(void);
static V L608(V *a);
static V L609(V *a);
static V S610(void);
static V L611(V *a);
static V S612(void);
static V L613(V *a);
static V L614(V *a);
static V S615(void);
static V L616(V *a);
static V L617(V *a);
static V S618(void);
static V L619(V *a);
static V S620(void);
static V L621(V *a);
static V L622(V *a);
static V S623(void);
static V L624(V *a);
static V S625(void);
static V L626(V *a);
static V W_P_dbrace_dtail(V *a);
static V F_P_dbrack(void);
static V L627(V *a);
static V L628(V *a);
static V S629(void);
static V W_P_dbrack(V *a);
static V F_P_dbrack_dgo(V a0);
static V L631(V *a);
static V S632(void);
static V W_P_dbrack_dgo(V *a);
static V F_P_dbrack_dbody(void);
static V L633(V *a);
static V L634(V *a);
static V S635(void);
static V W_P_dbrack_dbody(V *a);
static V F_P_dbrack_dtail(V a0, V a1);
static V S637(void);
static V L638(V *a);
static V S639(void);
static V L640(V *a);
static V W_P_dbrack_dtail(V *a);
static V F_P_delist(V a0);
static V S642(void);
static V S643(void);
static V W_P_delist(V *a);
static V F_P_darr(V a0);
static V L644(V *a);
static V L645(V *a);
static V L646(V *a);
static V L647(V *a);
static V L648(V *a);
static V S649(void);
static V L650(V *a);
static V S651(void);
static V L652(V *a);
static V S653(void);
static V S654(void);
static V W_P_darr(V *a);
static V F_P_darr_dsize(V a0, V a1);
static V W_P_darr_dsize(V *a);
static V F_P_darr_dsize_dlit(V a0);
static V L657(V *a);
static V S658(void);
static V L659(V *a);
static V W_P_darr_dsize_dlit(V *a);
static V F_P_dlog2(V a0);
static V W_P_dlog2(V *a);
static V W_U32_dlog2(V *a);
static V F_P_dparen(void);
static V L660(V *a);
static V L661(V *a);
static V S662(void);
static V W_P_dparen(V *a);
static V F_P_dparen_dgo(V a0);
static V L664(V *a);
static V S665(void);
static V W_P_dparen_dgo(V *a);
static V F_P_dparen_dbody(void);
static V L666(V *a);
static V L667(V *a);
static V S668(void);
static V S669(void);
static V W_P_dparen_dbody(V *a);
static V F_P_dparen_dtail(V a0, V a1);
static V L671(V *a);
static V S672(void);
static V L673(V *a);
static V L674(V *a);
static V L675(V *a);
static V S676(void);
static V L677(V *a);
static V S678(void);
static V L679(V *a);
static V W_P_dparen_dtail(V *a);
static V F_P_dtuple(V a0);
static V S681(void);
static V S682(void);
static V W_P_dtuple(V *a);
static V F_P_dafter__id(V a0, V a1);
static V S683(void);
static V S684(void);
static V S685(void);
static V W_P_dafter__id(V *a);
static V F_P_dafter__id_dgo(V a0, V a1, V a2);
static V L687(V *a);
static V L688(V *a);
static V W_P_dafter__id_dgo(V *a);
static V F_P_dafter__id_dk(V a0, V a1);
static V L690(V *a);
static V S691(void);
static V L692(V *a);
static V L693(V *a);
static V L694(V *a);
static V W_P_dafter__id_dk(V *a);
static V F_P_dtyargs(void);
static V L695(V *a);
static V W_P_dtyargs(V *a);
static V F_P_dtyargs_dgo(V a0, V a1);
static V W_P_dtyargs_dgo(V *a);
static V F_P_dis__gt(V a0);
static V S697(void);
static V S698(void);
static V S699(void);
static V W_P_dis__gt(V *a);
static V F_P_dtyargs_dclose(V a0);
static V L701(V *a);
static V W_P_dtyargs_dclose(V *a);
static V F_P_dtyargs_ditem(void);
static V L702(V *a);
static V S703(void);
static V L704(V *a);
static V L705(V *a);
static V W_P_dtyargs_ditem(V *a);
static V F_P_dtyargs_dmore(V a0);
static V L707(V *a);
static V W_P_dtyargs_dmore(V *a);
static V F_P_dgt(void);
static V L708(V *a);
static V W_P_dgt(V *a);
static V F_P_dgt_dgo(V a0);
static V S710(void);
static V S711(void);
static V S712(void);
static V S713(void);
static V W_P_dgt_dgo(V *a);
static V F_P_dgt_dif(V a0, V a1, V a2, V a3, V a4);
static V S715(void);
static V S716(void);
static V S717(void);
static V W_P_dgt_dif(V *a);
static V F_P_dparam_dskip__mode(V a0);
static V W_P_dparam_dskip__mode(V *a);
static V F_P_dparam_dskip__mode_dgo(V a0);
static V W_P_dparam_dskip__mode_dgo(V *a);
static V F_P_dparam_dmode(V a0);
static V S719(void);
static V S720(void);
static V S721(void);
static V W_P_dparam_dmode(V *a);
static V F_P_dnls(void);
static V L722(V *a);
static V W_P_dnls(V *a);
static V F_P_dis__nl(V a0);
static V W_P_dis__nl(V *a);
static V F_P_dnls_dif(V a0);
static V L725(V *a);
static V W_P_dnls_dif(V *a);
static V F_P_dexpect__in(void);
static V L726(V *a);
static V W_P_dexpect__in(V *a);
static V F_P_dis__in(V a0);
static V W_P_dis__in(V *a);
static V F_P_dexpect__in_dgo(V a0);
static V S729(void);
static V W_P_dexpect__in_dgo(V *a);
static V F_P_dtype(void);
static V L730(V *a);
static V L731(V *a);
static V L732(V *a);
static V S733(void);
static V S734(void);
static V L735(V *a);
static V L736(V *a);
static V L737(V *a);
static V S738(void);
static V L739(V *a);
static V L740(V *a);
static V L741(V *a);
static V W_P_dtype(V *a);
static V F_P_dtype_dbody(V a0);
static V L743(V *a);
static V W_P_dtype_dbody(V *a);
static V F_P_dctors(void);
static V L744(V *a);
static V L745(V *a);
static V W_P_dctors(V *a);
static V F_P_dctors_dgo(V a0, V a1);
static V L747(V *a);
static V L748(V *a);
static V S749(void);
static V L750(V *a);
static V L751(V *a);
static V L752(V *a);
static V W_P_dctors_dgo(V *a);
static V F_P_dfields(void);
static V L753(V *a);
static V S754(void);
static V W_P_dfields(V *a);
static V F_P_dfields_dgo(V a0);
static V L756(V *a);
static V S757(void);
static V L758(V *a);
static V S759(void);
static V L760(V *a);
static V L761(V *a);
static V S762(void);
static V L763(V *a);
static V L764(V *a);
static V S765(void);
static V L766(V *a);
static V L767(V *a);
static V W_P_dfields_dgo(V *a);
static V F_P_duntil__is(void);
static V L768(V *a);
static V W_P_duntil__is(V *a);
static V F_P_duntil__is_dgo(V a0);
static V S770(void);
static V W_P_duntil__is_dgo(V *a);
static V F_P_duntil__is_dif(V a0, V a1, V a2);
static V W_P_duntil__is_dif(V *a);
static V F_P_dtparams_dopt(V a0);
static V L773(V *a);
static V L774(V *a);
static V W_P_dtparams_dopt(V *a);
static V F_P_dtparams(void);
static V S775(void);
static V L776(V *a);
static V L777(V *a);
static V L778(V *a);
static V S779(void);
static V L780(V *a);
static V L781(V *a);
static V W_P_dtparams(V *a);
static V F_P_dtparams_dmore(V a0);
static V L783(V *a);
static V W_P_dtparams_dmore(V *a);
static V F_P_dskip__ann(void);
static V L784(V *a);
static V S785(void);
static V W_P_dskip__ann(V *a);
static V F_P_dskip__ann_dgo(V a0);
static V L787(V *a);
static V L788(V *a);
static V W_P_dskip__ann_dgo(V *a);
static V F_P_ddef(void);
static V L789(V *a);
static V L790(V *a);
static V S791(void);
static V L792(V *a);
static V L793(V *a);
static V L794(V *a);
static V S795(void);
static V L796(V *a);
static V S797(void);
static V L798(V *a);
static V L799(V *a);
static V L800(V *a);
static V S801(void);
static V W_P_ddef(V *a);
static V F_P_ddef_dbody(V a0, V a1, V a2, V a3);
static V L803(V *a);
static V L804(V *a);
static V W_P_ddef_dbody(V *a);
static V F_Fold_dplain(V a0);
static V S806(void);
static V S807(void);
static V S808(void);
static V W_Fold_dplain(V *a);
static V F_P_dstmts(void);
static V L809(V *a);
static V L810(V *a);
static V W_P_dstmts(V *a);
static V F_P_dstmts_dgo(V a0, V a1);
static V L812(V *a);
static V L813(V *a);
static V L814(V *a);
static V W_P_dstmts_dgo(V *a);
static V F_P_dstmt(void);
static V L815(V *a);
static V S816(void);
static V W_P_dstmt(V *a);
static V F_P_dstmt_dgo(V a0, V a1);
static V L818(V *a);
static V S819(void);
static V S820(void);
static V S821(void);
static V W_P_dstmt_dgo(V *a);
static V F_P_dstmt_did(V a0);
static V L823(V *a);
static V L824(V *a);
static V L825(V *a);
static V L826(V *a);
static V L827(V *a);
static V W_P_dstmt_did(V *a);
static V F_P_dstmt_dscan(V a0);
static V W_P_dstmt_dscan(V *a);
static V W_U32_dto__nat(V *a);
static V F_P_dstmt_dscan_dgo(V a0);
static V L829(V *a);
static V W_P_dstmt_dscan_dgo(V *a);
static V F_P_dbind__stmt(void);
static V S830(void);
static V L831(V *a);
static V L832(V *a);
static V L833(V *a);
static V S834(void);
static V W_P_dbind__stmt(V *a);
static V F_P_dbind_darr(V a0, V a1);
static V L836(V *a);
static V L837(V *a);
static V S838(void);
static V L839(V *a);
static V S840(void);
static V L841(V *a);
static V L842(V *a);
static V S843(void);
static V S844(void);
static V L845(V *a);
static V S846(void);
static V L847(V *a);
static V L848(V *a);
static V W_P_dbind_darr(V *a);
static V F_P_dlet__stmt(void);
static V S849(void);
static V S850(void);
static V L851(V *a);
static V L852(V *a);
static V S853(void);
static V L854(V *a);
static V L855(V *a);
static V W_P_dlet__stmt(V *a);
static V F_P_dlets_dpar(V a0, V a1);
static V S856(void);
static V S857(void);
static V W_P_dlets_dpar(V *a);
static V F_P_dlets(V a0, V a1);
static V W_P_dlets(V *a);
static V W_Nat_dis__gt(V *a);
static V F_P_dexprs__n(V a0);
static V L861(V *a);
static V L862(V *a);
static V W_P_dexprs__n(V *a);
static V F_P_dpat__seq(V a0);
static V L863(V *a);
static V W_P_dpat__seq(V *a);
static V F_P_dpat__seq_dstop(V a0, V a1);
static V W_P_dpat__seq_dstop(V *a);
static V F_P_dpat__seq_dgo(V a0, V a1, V a2);
static V L865(V *a);
static V L866(V *a);
static V W_P_dpat__seq_dgo(V *a);
static V F_P_dpat(void);
static V L867(V *a);
static V L868(V *a);
static V S869(void);
static V W_P_dpat(V *a);
static V F_P_dpat_dcons(V a0, V a1);
static V L871(V *a);
static V L872(V *a);
static V S873(void);
static V W_P_dpat_dcons(V *a);
static V F_P_dpat1(void);
static V L874(V *a);
static V W_P_dpat1(V *a);
static V F_P_dpat1_dk(V a0);
static V L876(V *a);
static V L877(V *a);
static V S878(void);
static V L879(V *a);
static V L880(V *a);
static V L881(V *a);
static V L882(V *a);
static V L883(V *a);
static V L884(V *a);
static V S885(void);
static V S886(void);
static V S887(void);
static V S888(void);
static V S889(void);
static V L890(V *a);
static V S891(void);
static V W_P_dpat1_dk(V *a);
static V F_P_dpat_dsym(V a0);
static V L893(V *a);
static V L894(V *a);
static V L895(V *a);
static V S896(void);
static V L897(V *a);
static V L898(V *a);
static V S899(void);
static V L900(V *a);
static V S901(void);
static V L902(V *a);
static V S903(void);
static V W_P_dpat_dsym(V *a);
static V F_P_dplist(V a0);
static V S905(void);
static V S906(void);
static V W_P_dplist(V *a);
static V F_P_dpats(V a0);
static V L907(V *a);
static V W_P_dpats(V *a);
static V F_P_dpats_dgo(V a0, V a1, V a2);
static V W_P_dpats_dgo(V *a);
static V F_P_dpats_dclose(V a0, V a1);
static V L910(V *a);
static V W_P_dpats_dclose(V *a);
static V F_P_dpats_ditem(V a0);
static V L911(V *a);
static V S912(void);
static V L913(V *a);
static V L914(V *a);
static V W_P_dpats_ditem(V *a);
static V F_P_dpats_dmore(V a0, V a1);
static V L916(V *a);
static V W_P_dpats_dmore(V *a);
static V F_P_dptuple(V a0);
static V S918(void);
static V S919(void);
static V W_P_dptuple(V *a);
static V F_P_dpstr(V a0);
static V S921(void);
static V S922(void);
static V W_P_dpstr(V *a);
static V F_P_dpat_did(V a0, V a1);
static V L924(V *a);
static V S925(void);
static V L926(V *a);
static V W_P_dpat_did(V *a);
static V F_P_dscan(void);
static V L927(V *a);
static V W_P_dscan(V *a);
static V F_P_dscan_dret(V a0);
static V W_P_dscan_dret(V *a);
static V F_P_dscan_dgo(V a0, V a1);
static V S929(void);
static V S930(void);
static V S931(void);
static V S932(void);
static V S933(void);
static V S934(void);
static V S935(void);
static V S936(void);
static V W_P_dscan_dgo(V *a);
static V F_P_dscan_dend(V a0, V a1, V a2);
static V W_P_dscan_dend(V *a);
static V F_P_dscan_dsym(V a0, V a1, V a2);
static V W_P_dscan_dsym(V *a);
static V F_P_dscan_dtop(V a0, V a1, V a2, V a3);
static V W_P_dscan_dtop(V *a);
static V F_P_ddo(void);
static V L940(V *a);
static V L941(V *a);
static V S942(void);
static V L943(V *a);
static V L944(V *a);
static V S945(void);
static V L946(V *a);
static V L947(V *a);
static V L948(V *a);
static V W_P_ddo(V *a);
static V F_P_dlast(V a0);
static V S950(void);
static V W_P_dlast(V *a);
static V F_P_dinit(V a0);
static V W_P_dinit(V *a);
static V F_Fold_ddo(V a0, V a1, V a2, V a3);
static V S953(void);
static V S954(void);
static V S955(void);
static V S956(void);
static V S957(void);
static V S958(void);
static V S959(void);
static V S960(void);
static V S961(void);
static V W_Fold_ddo(V *a);
static V F_Fold_dapp(V a0, V a1, V a2, V a3);
static V S962(void);
static V W_Fold_dapp(V *a);
static V F_P_dmatch(void);
static V L963(V *a);
static V L964(V *a);
static V S965(void);
static V L966(V *a);
static V L967(V *a);
static V L968(V *a);
static V W_P_dmatch(V *a);
static V F_P_dmatch_dbody(V a0);
static V L970(V *a);
static V W_P_dmatch_dbody(V *a);
static V F_P_dcases(void);
static V L971(V *a);
static V L972(V *a);
static V W_P_dcases(V *a);
static V F_P_dcases_dde(V a0);
static V L974(V *a);
static V L975(V *a);
static V S976(void);
static V W_P_dcases_dde(V *a);
static V F_P_dcases_dgo(V a0);
static V L978(V *a);
static V S979(void);
static V L980(V *a);
static V S981(void);
static V L982(V *a);
static V L983(V *a);
static V L984(V *a);
static V W_P_dcases_dgo(V *a);
static V F_P_dbody(void);
static V L985(V *a);
static V L986(V *a);
static V W_P_dbody(V *a);
static V F_P_dscrs(void);
static V L987(V *a);
static V S988(void);
static V W_P_dscrs(V *a);
static V F_P_dscrs_dgo(V a0, V a1);
static V L990(V *a);
static V L991(V *a);
static V W_P_dscrs_dgo(V *a);
static V F_P_deff_dimports(void);
static V L992(V *a);
static V W_P_deff_dimports(V *a);
static V F_P_deff_dgo(V a0, V a1);
static V W_P_deff_dgo(V *a);
static V F_P_dret_dgo(V a0);
static V L995(V *a);
static V S996(void);
static V W_P_dret_dgo(V *a);
static V F_P_dparams(void);
static V L997(V *a);
static V S998(void);
static V W_P_dparams(V *a);
static V F_P_dparams_dgo(V a0);
static V L1000(V *a);
static V L1001(V *a);
static V S1002(void);
static V L1003(V *a);
static V L1004(V *a);
static V W_P_dparams_dgo(V *a);
static V F_P_dparams_dmore(V a0);
static V S1006(void);
static V L1007(V *a);
static V W_P_dparams_dmore(V *a);
static V F_P_dfile_dfin(V a0);
static V W_P_dfile_dfin(V *a);
static V F_P_dfile_derr(V a0);
static V S1010(void);
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
static V S1019(void);
static V W_Eff_dpath(V *a);
static V F_Main_dcompile(V a0, V a1);
static V S1022(void);
static V S1023(void);
static V W_Main_dcompile(V *a);
static V F_Gen_dprogram(V a0);
static V W_Gen_dprogram(V *a);
static V F_Gen_dprogram_dm(V a0);
static V S1025(void);
static V L1026(V *a);
static V S1027(void);
static V W_Gen_dprogram_dm(V *a);
static V F_G_dbody(V a0, V a1);
static V S1029(void);
static V S1030(void);
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
static V S1039(void);
static V S1040(void);
static V L1041(V *a);
static V S1042(void);
static V W_Gen_dentry(V *a);
static V F_Gen_dpure(V a1);
static V L1043(V *a);
static V W_Gen_dpure(V *a);
static V F_Gen_derror(V a0);
static V L1044(V *a);
static V W_Gen_derror(V *a);
static V F_Gen_derror_dgo(V a0, V a1);
static V W_Gen_derror_dgo(V *a);
static V F_Gen_dbind(V a2, V a3);
static V L1046(V *a);
static V W_Gen_dbind(V *a);
static V F_Gen_dgo(V a2, V a3);
static V W_Gen_dgo(V *a);
static V F_Ty_dhead(V a0);
static V S1049(void);
static V W_Ty_dhead(V *a);
static V F_Gen_dentry_dty(V a0, V a1, V a2);
static V S1051(void);
static V L1052(V *a);
static V S1053(void);
static V S1054(void);
static V W_Gen_dentry_dty(V *a);
static V F_Gen_dprinter(V a0, V a1);
static V L1056(V *a);
static V W_Gen_dprinter(V *a);
static V F_Gen_dprinter_dmemo(V a0, V a1, V a2, V a3);
static V L1058(V *a);
static V S1059(void);
static V L1060(V *a);
static V L1061(V *a);
static V S1062(void);
static V S1063(void);
static V L1064(V *a);
static V L1065(V *a);
static V S1066(void);
static V S1067(void);
static V S1068(void);
static V L1069(V *a);
static V W_Gen_dprinter_dmemo(V *a);
static V F_Doc_dlist(V a0);
static V W_Doc_dlist(V *a);
static V F_Gen_dcode(V a0);
static V L1071(V *a);
static V W_Gen_dcode(V *a);
static V F_Gen_dcode_dgo(V a0, V a1);
static V W_Gen_dcode_dgo(V *a);
static V F_Gen_dprinter_dbody(V a0, V a1, V a2);
static V S1073(void);
static V S1074(void);
static V S1075(void);
static V S1076(void);
static V S1077(void);
static V S1078(void);
static V S1079(void);
static V S1080(void);
static V W_Gen_dprinter_dbody(V *a);
static V F_Gen_dprinter_dhead(V a0, V a1, V a2);
static V S1082(void);
static V S1083(void);
static V S1084(void);
static V S1085(void);
static V S1086(void);
static V L1087(V *a);
static V S1088(void);
static V S1089(void);
static V S1090(void);
static V L1091(V *a);
static V S1092(void);
static V S1093(void);
static V S1094(void);
static V S1095(void);
static V W_Gen_dprinter_dhead(V *a);
static V F_Gen_dprinter_dadt(V a0, V a1, V a2);
static V L1097(V *a);
static V S1098(void);
static V S1099(void);
static V W_Gen_dprinter_dadt(V *a);
static V F_Ty_dargs(V a0);
static V W_Ty_dargs(V *a);
static V F_Ty_dbind(V a0, V a1);
static V W_Ty_dbind(V *a);
static V F_Ty_dbind_dgo(V a0, V a1);
static V W_Ty_dbind_dgo(V *a);
static V F_Gen_dprinter_dctors(V a0, V a1, V a2);
static V L1104(V *a);
static V L1105(V *a);
static V W_Gen_dprinter_dctors(V *a);
static V F_G_dctor(V a0, V a1);
static V W_G_dctor(V *a);
static V F_G_dopt__ctors(V a0);
static V W_G_dopt__ctors(V *a);
static V F_Gen_dprinter_dctor(V a0, V a1, V a2, V a3, V a4);
static V S1109(void);
static V S1110(void);
static V L1111(V *a);
static V S1112(void);
static V S1113(void);
static V S1114(void);
static V W_Gen_dprinter_dctor(V *a);
static V F_Gen_dprinter_dtest(V a0, V a1, V a2);
static V S1115(void);
static V S1116(void);
static V S1117(void);
static V S1118(void);
static V S1119(void);
static V W_Gen_dprinter_dtest(V *a);
static V F_Gen_dprinter_dfields(V a0, V a1, V a2, V a3, V a4);
static V L1121(V *a);
static V L1122(V *a);
static V S1123(void);
static V S1124(void);
static V S1125(void);
static V S1126(void);
static V S1127(void);
static V S1128(void);
static V S1129(void);
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
static V S1136(void);
static V W_Ty_dtuple(V *a);
static V F_Ty_dtuple_dgo(V a0, V a1, V a2);
static V W_Ty_dtuple_dgo(V *a);
static V F_Ty_dtuple_dargs(V a0, V a1);
static V W_Ty_dtuple_dargs(V *a);
static V F_Gen_dprinter_dtuple(V a0, V a1, V a2);
static V L1140(V *a);
static V S1141(void);
static V S1142(void);
static V L1143(V *a);
static V S1144(void);
static V S1145(void);
static V L1146(V *a);
static V S1147(void);
static V S1148(void);
static V W_Gen_dprinter_dtuple(V *a);
static V F_Gen_dproto(V a0);
static V L1149(V *a);
static V W_Gen_dproto(V *a);
static V F_Gen_dproto_dgo(V a0, V a1);
static V W_Gen_dproto_dgo(V *a);
static V F_Gen_dmemo_dadd(V a0);
static V L1151(V *a);
static V W_Gen_dmemo_dadd(V *a);
static V F_Gen_dmemo_dadd_dgo(V a0, V a1);
static V W_Gen_dmemo_dadd_dgo(V *a);
static V F_Gen_dfresh(void);
static V L1153(V *a);
static V W_Gen_dfresh(V *a);
static V F_Gen_dfresh_dgo(V a0);
static V W_Gen_dfresh_dgo(V *a);
static V F_Gen_dmemo_dfind(V a0);
static V L1155(V *a);
static V W_Gen_dmemo_dfind(V *a);
static V F_Gen_dmemo_dfind_dgo(V a0, V a1);
static V W_Gen_dmemo_dfind_dgo(V *a);
static V F_Env_dfind(V a0, V a1);
static V W_Env_dfind(V *a);
static V F_Env_dfind_dif(V a0, V a1, V a2, V a3);
static V W_Env_dfind_dif(V *a);
static V F_Expr_dshow(V a0);
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
static V S1189(void);
static V S1190(void);
static V S1191(void);
static V S1192(void);
static V S1193(void);
static V W_Expr_dshow(V *a);
static V F_Pats_dshow(V a0);
static V S1195(void);
static V S1196(void);
static V W_Pats_dshow(V *a);
static V F_Pat_dshow(V a0);
static V S1198(void);
static V S1199(void);
static V S1200(void);
static V S1201(void);
static V W_Pat_dshow(V *a);
static V F_Exprs_dshow(V a0);
static V S1203(void);
static V S1204(void);
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
static V L1212(V *a);
static V L1213(V *a);
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
static V L1239(V *a);
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
static V S1246(void);
static V S1247(void);
static V W_Gen_ddummy__params(V *a);
static V F_Gen_dsig(V a0, V a1, V a2, V a3);
static V S1252(void);
static V S1253(void);
static V S1254(void);
static V S1256(void);
static V W_Gen_dsig(V *a);
static V F_Sig_dwargs(V a0);
static V W_Sig_dwargs(V *a);
static V F_Gen_dwrapper(V a0, V a1);
static V S1259(void);
static V S1260(void);
static V L1261(V *a);
static V S1262(void);
static V S1263(void);
static V S1264(void);
static V S1265(void);
static V S1266(void);
static V W_Gen_dwrapper(V *a);
static V F_Gen_df(V a0);
static V S1267(void);
static V W_Gen_df(V *a);
static V F_Gen_dmangle(V a0);
static V S1269(void);
static V W_Gen_dmangle(V *a);
static V F_Gen_dmangle_dchr(V a0);
static V S1270(void);
static V S1271(void);
static V S1272(void);
static V W_Gen_dmangle_dchr(V *a);
static V F_Str_dchr(V a0);
static V W_Str_dchr(V *a);
static V F_Gen_dw(V a0);
static V S1273(void);
static V W_Gen_dw(V *a);
static V F_Gen_ddef_deff(V a0, V a1, V a2);
static V S1277(void);
static V S1279(void);
static V S1280(void);
static V S1281(void);
static V L1282(V *a);
static V S1283(void);
static V S1284(void);
static V L1285(V *a);
static V S1286(void);
static V S1287(void);
static V S1288(void);
static V S1289(void);
static V S1290(void);
static V S1291(void);
static V S1292(void);
static V S1293(void);
static V L1294(V *a);
static V S1295(void);
static V S1296(void);
static V S1297(void);
static V S1298(void);
static V S1299(void);
static V S1300(void);
static V S1301(void);
static V S1302(void);
static V S1303(void);
static V L1304(V *a);
static V W_Gen_ddef_deff(V *a);
static V F_Gen_deff_dargs(V a0, V a1);
static V S1306(void);
static V S1307(void);
static V W_Gen_deff_dargs(V *a);
static V F_Gen_dcid(V a0);
static V S1308(void);
static V W_Gen_dcid(V *a);
static V F_String_dto__upper(V a0);
static V W_String_dto__upper(V *a);
static V F_Char_dto__upper(V a0);
static V W_Char_dto__upper(V *a);
static V F_Bool_dto__u32(V a0);
static V W_Bool_dto__u32(V *a);
static V F_Gen_dhost(V a0);
static V S1312(void);
static V W_Gen_dhost(V *a);
static V F_Gen_dhost_dchr(V a0);
static V S1313(void);
static V W_Gen_dhost_dchr(V *a);
static V F_Gen_deffs(V a0);
static V L1314(V *a);
static V W_Gen_deffs(V *a);
static V F_Gen_deffs_dgo(V a0, V a1);
static V W_Gen_deffs_dgo(V *a);
static V F_Gen_deffs_dc(V a0);
static V S1317(void);
static V W_Gen_deffs_dc(V *a);
static V F_String_dends__with(V a0, V a1);
static V W_String_dends__with(V *a);
static V F_Gen_deffs_dc_dif(V a0, V a1, V a2);
static V W_Gen_deffs_dc_dif(V *a);
static V F_Gen_dcparams(V a0);
static V S1320(void);
static V S1321(void);
static V W_Gen_dcparams(V *a);
static V F_Gen_dcparams_dgo(V a0);
static V S1323(void);
static V W_Gen_dcparams_dgo(V *a);
static V F_Gen_ddef_dnative(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Gen_ddef_dnative(V *a);
static V F_Gen_ddef_dbody(V a0, V a1, V a2, V a3, V a4);
static V S1327(void);
static V S1328(void);
static V S1329(void);
static V S1330(void);
static V L1331(V *a);
static V S1332(void);
static V L1333(V *a);
static V S1334(void);
static V S1335(void);
static V L1336(V *a);
static V W_Gen_ddef_dbody(V *a);
static V F_R_dops(V a0, V a1);
static V S1338(void);
static V W_R_dops(V *a);
static V F_R_dopss(V a0, V a1);
static V W_R_dopss(V *a);
static V F_R_dopname(V a0);
static V S1340(void);
static V S1341(void);
static V S1342(void);
static V S1343(void);
static V S1344(void);
static V S1345(void);
static V S1346(void);
static V S1347(void);
static V S1348(void);
static V S1349(void);
static V S1350(void);
static V S1351(void);
static V S1352(void);
static V S1353(void);
static V W_R_dopname(V *a);
static V F_R_dopname_dgo(V a0);
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
static V S1365(void);
static V S1366(void);
static V S1367(void);
static V S1368(void);
static V S1369(void);
static V W_R_dopname_dgo(V *a);
static V F_Gen_dstmt(V a0, V a1, V a2, V a3, V a4);
static V L1371(V *a);
static V W_Gen_dstmt(V *a);
static V F_Gen_dret(V a0, V a1);
static V S1373(void);
static V S1374(void);
static V S1375(void);
static V S1376(void);
static V W_Gen_dret(V *a);
static V F_Gen_dexpr(V a0, V a1, V a2);
static V S1378(void);
static V S1379(void);
static V S1380(void);
static V S1381(void);
static V L1382(V *a);
static V S1383(void);
static V S1384(void);
static V S1385(void);
static V S1386(void);
static V S1387(void);
static V L1388(V *a);
static V S1389(void);
static V S1390(void);
static V L1391(V *a);
static V S1392(void);
static V W_Gen_dexpr(V *a);
static V F_Gen_dblock(V a0, V a1, V a2);
static V L1393(V *a);
static V S1394(void);
static V L1395(V *a);
static V L1396(V *a);
static V S1397(void);
static V S1398(void);
static V S1399(void);
static V W_Gen_dblock(V *a);
static V F_Self_dnone(void);
static V S1400(void);
static V W_Self_dnone(V *a);
static V F_Gen_dlam(V a0, V a1, V a2, V a3);
static V L1403(V *a);
static V S1404(void);
static V L1405(V *a);
static V S1406(void);
static V S1407(void);
static V L1408(V *a);
static V S1409(void);
static V S1410(void);
static V L1411(V *a);
static V L1412(V *a);
static V S1413(void);
static V S1414(void);
static V S1415(void);
static V L1416(V *a);
static V S1417(void);
static V S1418(void);
static V S1419(void);
static V S1420(void);
static V S1421(void);
static V W_Gen_dlam(V *a);
static V F_Gen_dcaps_douter(V a0);
static V W_Gen_dcaps_douter(V *a);
static V F_Gen_darr(V a0);
static V S1424(void);
static V S1425(void);
static V S1426(void);
static V W_Gen_darr(V *a);
static V F_Gen_dcommas(V a0);
static V S1427(void);
static V W_Gen_dcommas(V *a);
static V F_Doc_dsep(V a0, V a1);
static V W_Doc_dsep(V *a);
static V F_Doc_dsep_dgo(V a0, V a1);
static V W_Doc_dsep_dgo(V *a);
static V F_Gen_dcaps_dinner(V a0, V a1);
static V S1431(void);
static V S1432(void);
static V W_Gen_dcaps_dinner(V *a);
static V F_Gen_dpat(V a0, V a1, V a2, V a3);
static V S1434(void);
static V S1435(void);
static V S1436(void);
static V S1437(void);
static V S1438(void);
static V S1439(void);
static V S1440(void);
static V S1441(void);
static V S1442(void);
static V S1443(void);
static V W_Gen_dpat(V *a);
static V F_Gen_dpat_dcond(V a0, V a1);
static V W_Gen_dpat_dcond(V *a);
static V F_Gen_dpat_dctor(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1446(void);
static V S1447(void);
static V W_Gen_dpat_dctor(V *a);
static V F_Gen_dpat_dkind(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S1449(void);
static V S1450(void);
static V S1451(void);
static V S1452(void);
static V S1453(void);
static V S1454(void);
static V S1455(void);
static V S1456(void);
static V S1457(void);
static V S1458(void);
static V S1459(void);
static V W_Gen_dpat_dkind(V *a);
static V F_Gen_dpat_dfields(V a0, V a1, V a2, V a3, V a4);
static V S1461(void);
static V S1462(void);
static V S1463(void);
static V W_Gen_dpat_dfields(V *a);
static V F_Gen_dpat_dtag(V a0, V a1, V a2);
static V W_Gen_dpat_dtag(V *a);
static V F_Gen_dpat_dvar(V a0, V a1, V a2);
static V S1466(void);
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
static V S1475(void);
static V L1476(V *a);
static V S1477(void);
static V L1478(V *a);
static V W_Gen_dctor_dinfo(V *a);
static V F_Gen_dctor_dkind(V a0, V a1, V a2);
static V S1480(void);
static V S1481(void);
static V S1482(void);
static V S1483(void);
static V S1484(void);
static V W_Gen_dctor_dkind(V *a);
static V F_Gen_dctor_dnode(V a0, V a1);
static V S1486(void);
static V S1487(void);
static V S1488(void);
static V S1489(void);
static V S1490(void);
static V S1491(void);
static V S1492(void);
static V S1493(void);
static V W_Gen_dctor_dnode(V *a);
static V F_Gen_dlen(V a0);
static V W_Gen_dlen(V *a);
static V F_Gen_dexprs(V a0, V a1, V a2);
static V L1495(V *a);
static V L1496(V *a);
static V W_Gen_dexprs(V *a);
static V F_Gen_dcall(V a0, V a1, V a2, V a3);
static V W_Gen_dcall(V *a);
static V F_Gen_dcall_dlocal(V a0, V a1, V a2, V a3);
static V L1498(V *a);
static V L1499(V *a);
static V W_Gen_dcall_dlocal(V *a);
static V F_Gen_dapply(V a0, V a1);
static V S1501(void);
static V S1502(void);
static V S1503(void);
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
static V S1513(void);
static V W_Gen_dsplit(V *a);
static V F_Gen_dcall_dkind(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1515(void);
static V S1516(void);
static V L1517(V *a);
static V S1518(void);
static V L1519(V *a);
static V W_Gen_dcall_dkind(V *a);
static V F_Gen_dcall_dsplit(V a0, V a1, V a2, V a3, V a4);
static V W_Gen_dcall_dsplit(V *a);
static V F_Gen_dcall_dfull(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L1522(V *a);
static V L1523(V *a);
static V S1524(void);
static V S1525(void);
static V L1526(V *a);
static V S1527(void);
static V S1528(void);
static V S1529(void);
static V S1530(void);
static V S1531(void);
static V W_Gen_dcall_dfull(V *a);
static V F_Gen_dref(V a0);
static V L1532(V *a);
static V W_Gen_dref(V *a);
static V F_Gen_dref_dgo(V a0, V a1);
static V W_Gen_dref_dgo(V *a);
static V F_Gen_dstr(V a0);
static V L1534(V *a);
static V S1535(void);
static V L1536(V *a);
static V S1537(void);
static V S1538(void);
static V L1539(V *a);
static V S1540(void);
static V S1541(void);
static V S1542(void);
static V L1543(V *a);
static V S1544(void);
static V W_Gen_dstr(V *a);
static V F_Gen_dlit(V a0);
static V S1546(void);
static V W_Gen_dlit(V *a);
static V F_Gen_dlit__chr(V a0);
static V S1547(void);
static V S1548(void);
static V S1549(void);
static V W_Gen_dlit__chr(V *a);
static V F_Gen_dutf8(V a0);
static V W_Gen_dutf8(V *a);
static V W_U32_dor(V *a);
static V F_Gen_doct(V a0);
static V S1550(void);
static V W_Gen_doct(V *a);
static V F_Gen_dvar(V a0, V a1, V a2);
static V W_Gen_dvar(V *a);
static V F_Gen_dvar_dfound(V a0, V a1, V a2);
static V S1552(void);
static V W_Gen_dvar_dfound(V *a);
static V F_Gen_dvar_dglobal(V a0, V a1, V a2);
static V S1554(void);
static V W_Gen_dvar_dglobal(V *a);
static V F_Gen_dvar_ddef(V a0, V a1);
static V W_Gen_dvar_ddef(V *a);
static V F_Gen_dvar_dkind(V a0, V a1, V a2);
static V S1557(void);
static V S1558(void);
static V L1559(V *a);
static V S1560(void);
static V L1561(V *a);
static V S1562(void);
static V S1563(void);
static V S1564(void);
static V S1565(void);
static V W_Gen_dvar_dkind(V *a);
static V F_Gen_dis__tail(V a0, V a1, V a2, V a3, V a4);
static V W_Gen_dis__tail(V *a);
static V W_Nat_dis__eq(V *a);
static V F_Gen_dis__ret(V a0);
static V W_Gen_dis__ret(V *a);
static V F_Gen_dstmt_dcall(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L1569(V *a);
static V W_Gen_dstmt_dcall(V *a);
static V F_Gen_dtail_dself(V a0, V a1, V a2, V a3);
static V W_Gen_dtail_dself(V *a);
static V F_Gen_dtail(V a0, V a1, V a2, V a3);
static V L1572(V *a);
static V S1573(void);
static V S1574(void);
static V W_Gen_dtail(V *a);
static V F_Gen_dtail_dassign(V a0, V a1);
static V S1576(void);
static V S1577(void);
static V W_Gen_dtail_dassign(V *a);
static V F_Gen_dtail_dtemps(V a0, V a1);
static V S1579(void);
static V S1580(void);
static V S1581(void);
static V W_Gen_dtail_dtemps(V *a);
static V F_Gen_dmatch(V a0, V a1, V a2, V a3, V a4, V a5);
static V L1582(V *a);
static V W_Gen_dmatch(V *a);
static V F_Gen_dmatch_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V L1584(V *a);
static V W_Gen_dmatch_dgo(V *a);
static V F_Gen_dcases(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1586(void);
static V L1590(V *a);
static V W_Gen_dcases(V *a);
static V F_Gen_dcases_dnext(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V S1592(void);
static V S1593(void);
static V L1594(V *a);
static V S1595(void);
static V S1596(void);
static V S1597(void);
static V W_Gen_dcases_dnext(V *a);
static V F_Gen_dand(V a0);
static V S1599(void);
static V S1600(void);
static V W_Gen_dand(V *a);
static V F_PatR_dconds(V a0);
static V W_PatR_dconds(V *a);
static V F_Gen_dpats(V a0, V a1, V a2, V a3);
static V W_Gen_dpats(V *a);
static V F_Gen_dscrs(V a0, V a1, V a2);
static V L1605(V *a);
static V S1606(void);
static V L1607(V *a);
static V L1608(V *a);
static V L1609(V *a);
static V W_Gen_dscrs(V *a);
static V F_Gen_dscrs_dput(V a0, V a1, V a2);
static V S1611(void);
static V S1612(void);
static V S1613(void);
static V W_Gen_dscrs_dput(V *a);
static V F_Gen_dlet(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S1615(void);
static V S1616(void);
static V W_Gen_dlet(V *a);
static V F_Gen_dlet_dpat(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L1617(V *a);
static V S1618(void);
static V L1619(V *a);
static V L1620(V *a);
static V L1621(V *a);
static V L1622(V *a);
static V S1623(void);
static V S1624(void);
static V S1625(void);
static V W_Gen_dlet_dpat(V *a);
static V F_Gen_dlet_dctor(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V W_Gen_dlet_dctor(V *a);
static V F_Gen_dlet_dpar(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Gen_dlet_dpar(V *a);
static V F_Gen_dpar(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L1628(V *a);
static V L1629(V *a);
static V L1630(V *a);
static V W_Gen_dpar(V *a);
static V F_Gen_dpar_denv(V a0, V a1, V a2, V a3);
static V S1632(void);
static V W_Gen_dpar_denv(V *a);
static V F_Gen_dpar_dname(V a0, V a1);
static V S1633(void);
static V S1634(void);
static V W_Gen_dpar_dname(V *a);
static V F_Gen_dpar_dvals(V a0, V a1, V a2, V a3, V a4);
static V L1636(V *a);
static V S1637(void);
static V S1638(void);
static V S1639(void);
static V S1640(void);
static V L1641(V *a);
static V L1642(V *a);
static V S1643(void);
static V S1644(void);
static V S1645(void);
static V S1646(void);
static V S1647(void);
static V S1648(void);
static V W_Gen_dpar_dvals(V *a);
static V F_Gen_dlet_dvar(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L1650(V *a);
static V L1651(V *a);
static V S1652(void);
static V S1653(void);
static V L1654(V *a);
static V S1655(void);
static V L1656(V *a);
static V L1657(V *a);
static V L1658(V *a);
static V S1659(void);
static V S1660(void);
static V S1661(void);
static V W_Gen_dlet_dvar(V *a);
static V F_Gen_dcids(V a0, V a1, V a2);
static V S1663(void);
static V S1664(void);
static V S1665(void);
static V S1666(void);
static V W_Gen_dcids(V *a);
static V F_Gen_dcids_dctors(V a0, V a1);
static V S1668(void);
static V W_Gen_dcids_dctors(V *a);
static V F_Gen_dcids_dkind(V a0, V a1);
static V S1670(void);
static V W_Gen_dcids_dkind(V *a);
static V F_Gen_dcids_dline(V a0, V a1, V a2);
static V S1672(void);
static V S1673(void);
static V S1674(void);
static V S1675(void);
static V S1676(void);
static V S1677(void);
static V S1678(void);
static V S1679(void);
static V S1680(void);
static V S1681(void);
static V W_Gen_dcids_dline(V *a);
static V F_Gen_dprogram_dfin(V a0, V a1);
static V S1684(void);
static V S1685(void);
static V S1686(void);
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
static V S1695(void);
static V S1696(void);
static V S1697(void);
static V S1698(void);
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
static V S1780(void);
static V S1781(void);
static V S1782(void);
static V S1783(void);
static V S1784(void);
static V W_Natives(V *a);
static V F_G_dadd_dlaw(V a0, V a1, V a2);
static V W_G_dadd_dlaw(V *a);
static V F_G_dadd_dtype(V a0, V a1, V a2, V a3);
static V S1788(void);
static V W_G_dadd_dtype(V *a);
static V F_G_dctors(V a0, V a1, V a2, V a3, V a4);
static V W_G_dctors(V *a);
static V F_G_dctor__kind(V a0, V a1, V a2, V a3);
static V S1791(void);
static V S1792(void);
static V W_G_dctor__kind(V *a);
static V F_Main_demit(V a0);
static V S1795(void);
static V L1796(V *a);
static V S1797(void);
static V W_Main_demit(V *a);
static V F_IO_dprint__err(V a0);
static V E_IO_dprint__err(V *a);
static V W_IO_dprint__err(V *a);
static V F_IO_dbind(V a2, V a3);
static V L1798(V *a);
static V L1799(V *a);
static V L1800(V *a);
static V W_IO_dbind(V *a);
static V F_Main_demit_dok(V a0, V a1, V a2);
static V S1801(void);
static V L1802(V *a);
static V W_Main_demit_dok(V *a);
static V F_IO_dwrite(V a0);
static V E_IO_dwrite(V *a);
static V W_IO_dwrite(V *a);
static V F_Main_deffs(V a0, V a1);
static V L1804(V *a);
static V S1805(void);
static V W_Main_deffs(V *a);
static V F_IO_dread__file(V a0);
static V S1806(void);
static V L1807(V *a);
static V L1808(V *a);
static V W_IO_dread__file(V *a);
static V F_IO_dread__fin(V a0);
static V L1810(V *a);
static V W_IO_dread__fin(V *a);
static V F_IO_dpass(V a1);
static V W_IO_dpass(V *a);
static V F_IO_dpure(V a1);
static V L1812(V *a);
static V L1813(V *a);
static V W_IO_dpure(V *a);
static V F_File_dclose(V a0);
static V E_File_dclose(V *a);
static V W_File_dclose(V *a);
static V F_IO_dread__all(V a0);
static V L1814(V *a);
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
static V S1818(void);
static V L1819(V *a);
static V W_Main_dload(V *a);
static V F_Main_dload_dparsed(V a0, V a1, V a2, V a3);
static V S1821(void);
static V S1822(void);
static V L1823(V *a);
static V W_Main_dload_dparsed(V *a);
static V F_Main_dimports(V a0, V a1, V a2);
static V S1825(void);
static V W_Main_dimports(V *a);
static V F_Main_dimports_done(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1827(void);
static V L1828(V *a);
static V L1829(V *a);
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
static V S1839(void);
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
static V L1844(V *a);
static V S1845(void);
static V L1846(V *a);
static V L1847(V *a);
static V S1848(void);
static V W_Main_dload_dhub(V *a);
static V F_Main_dhub_durl(V a0);
static V S1850(void);
static V W_Main_dhub_durl(V *a);
static V F_Hub_densure(V a0, V a1, V a2);
static V E_Hub_densure(V *a);
static V W_Hub_densure(V *a);
static V F_IO_dget__env(V a0);
static V E_IO_dget__env(V *a);
static V W_IO_dget__env(V *a);
static V F_Main_dlib(void);
static V S1851(void);
static V L1852(V *a);
static V W_Main_dlib(V *a);
static V F_Main_dlib_dor(V a0);
static V S1854(void);
static V L1855(V *a);
static V S1856(void);
static V W_Main_dlib_dor(V *a);
static V F_Chk_dshow__main(V a0);
static V W_Chk_dshow__main(V *a);
static V F_Chk_dshow__main_dgo(V a0, V a1);
static V S1858(void);
static V W_Chk_dshow__main_dgo(V *a);
static V F_Chk_dterm__show(V a0, V a1, V a2);
static V W_Chk_dterm__show(V *a);
static V F_Chk_dterm__show_dgo(V a0, V a1, V a2, V a3);
static V S1860(void);
static V S1861(void);
static V S1862(void);
static V S1863(void);
static V S1867(void);
static V S1868(void);
static V S1869(void);
static V S1870(void);
static V S1871(void);
static V S1872(void);
static V S1873(void);
static V S1874(void);
static V S1875(void);
static V S1876(void);
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
static V S1895(void);
static V S1896(void);
static V S1897(void);
static V S1898(void);
static V S1899(void);
static V W_Chk_dterm__show_dgo(V *a);
static V F_Chk_dshow_drwt(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dshow_drwt(V *a);
static V F_Chk_dshow_drwt_dgo(V a0, V a1, V a2, V a3, V a4);
static V S1901(void);
static V S1902(void);
static V S1903(void);
static V W_Chk_dshow_drwt_dgo(V *a);
static V F_Chk_dshow_drwt_dinner(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S1905(void);
static V S1906(void);
static V S1907(void);
static V S1908(void);
static V S1909(void);
static V S1910(void);
static V S1911(void);
static V S1912(void);
static V W_Chk_dshow_drwt_dinner(V *a);
static V F_Chk_dshow_dparen(V a0, V a1);
static V S1914(void);
static V S1915(void);
static V W_Chk_dshow_dparen(V *a);
static V F_Chk_dshow_darms(V a0, V a1, V a2);
static V S1917(void);
static V W_Chk_dshow_darms(V *a);
static V F_Chk_dshow_djoin(V a0, V a1);
static V W_Chk_dshow_djoin(V *a);
static V F_Chk_dshow_dctr(V a0, V a1, V a2, V a3);
static V S1918(void);
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
static V S1924(void);
static V W_Chk_dshow_dctr_du32(V *a);
static V F_Chk_dshow_dctr_df32(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dshow_dctr_df32(V *a);
static V F_Chk_dnat__from__term(V a0);
static V W_Chk_dnat__from__term(V *a);
static V F_Chk_dMaybe_dmap__nat(V a0);
static V W_Chk_dMaybe_dmap__nat(V *a);
static V W_Nat_dis__le(V *a);
static V F_Chk_dshow_dctr_dnat(V a0, V a1, V a2, V a3, V a4);
static V S1929(void);
static V S1930(void);
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
static V S1937(void);
static V W_Chk_dshow_dctr_dsucc(V *a);
static V F_Chk_dshow_dchr__term(V a0, V a1);
static V S1939(void);
static V W_Chk_dshow_dchr__term(V *a);
static V F_Chk_dshow_dchr__term_du(V a0, V a1);
static V W_Chk_dshow_dchr__term_du(V *a);
static V F_Chk_dshow_dctr_dchr(V a0, V a1, V a2, V a3, V a4);
static V S1942(void);
static V S1943(void);
static V W_Chk_dshow_dctr_dchr(V *a);
static V F_Chk_dshow_dstr(V a0);
static V S1944(void);
static V W_Chk_dshow_dstr(V *a);
static V F_Chk_dshow_dstr_dgo(V a0);
static V W_Chk_dshow_dstr_dgo(V *a);
static V F_Chk_dshow_dstr__tail(V a0);
static V S1947(void);
static V W_Chk_dshow_dstr__tail(V *a);
static V F_Chk_dshow_dchrs(V a0);
static V S1949(void);
static V W_Chk_dshow_dchrs(V *a);
static V F_Chk_dshow_dchrs_dcat(V a0, V a1);
static V W_Chk_dshow_dchrs_dcat(V *a);
static V F_Chk_dshow_dstr_dc(V a0);
static V S1953(void);
static V S1954(void);
static V W_Chk_dshow_dstr_dc(V *a);
static V F_Chk_dshow_dctr_dstr(V a0, V a1, V a2, V a3, V a4);
static V S1956(void);
static V W_Chk_dshow_dctr_dstr(V *a);
static V F_Chk_dshow_dctr_dlst(V a0, V a1, V a2, V a3, V a4);
static V S1960(void);
static V S1961(void);
static V S1962(void);
static V S1963(void);
static V S1964(void);
static V S1965(void);
static V W_Chk_dshow_dctr_dlst(V *a);
static V F_Chk_dshow_dargs(V a0, V a1, V a2, V a3);
static V W_Chk_dshow_dargs(V *a);
static V F_Chk_dshow_dctr_dtup(V a0, V a1, V a2, V a3, V a4);
static V S1969(void);
static V S1970(void);
static V S1971(void);
static V W_Chk_dshow_dctr_dtup(V *a);
static V F_Chk_dshow_darr(V a0, V a1, V a2);
static V W_Chk_dshow_darr(V *a);
static V F_Chk_dshow_darr_dcat(V a0, V a1);
static V W_Chk_dshow_darr_dcat(V *a);
static V F_Chk_dshow_dctr_darr(V a0, V a1, V a2, V a3);
static V S1976(void);
static V S1977(void);
static V S1978(void);
static V W_Chk_dshow_dctr_darr(V *a);
static V F_Chk_dshow_dctr_dplain(V a0, V a1, V a2);
static V S1980(void);
static V S1981(void);
static V S1982(void);
static V S1983(void);
static V W_Chk_dshow_dctr_dplain(V *a);
static V F_Chk_df32__show(V a0);
static V S1985(void);
static V S1986(void);
static V S1987(void);
static V S1988(void);
static V S1989(void);
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
static V S1995(void);
static V S1996(void);
static V S1997(void);
static V W_Chk_dshow_drems(V *a);
static V F_Chk_dshow_dapp(V a0, V a1, V a2, V a3);
static V W_Chk_dshow_dapp(V *a);
static V F_Chk_dshow_dapp_dgo(V a0, V a1, V a2, V a3);
static V S2001(void);
static V S2002(void);
static V S2003(void);
static V S2004(void);
static V S2005(void);
static V S2006(void);
static V W_Chk_dshow_dapp_dgo(V *a);
static V F_Chk_dQ_ddef(V a0);
static V W_Chk_dQ_ddef(V *a);
static V F_Chk_dshow_dtyp(V a0, V a1, V a2);
static V S2009(void);
static V S2010(void);
static V S2011(void);
static V S2012(void);
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
static V S2018(void);
static V S2019(void);
static V W_Main_demit__value(V *a);
static V F_Chk_dreport__text(V a0);
static V S2021(void);
static V S2023(void);
static V S2024(void);
static V S2025(void);
static V S2026(void);
static V S2027(void);
static V W_Chk_dreport__text(V *a);
static V F_Chk_dreport__lines(V a0);
static V S2029(void);
static V S2030(void);
static V S2031(void);
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
static V S2062(void);
static V L2063(V *a);
static V W_Main_dcheck(V *a);
static V F_Main_dcheck_dfin(V a0);
static V W_Main_dcheck_dfin(V *a);
static V F_Chk_dcheck__book(V a0);
static V W_Chk_dcheck__book(V *a);
static V F_Chk_dbook__reset(V a0);
static V W_Chk_dbook__reset(V *a);
static V F_Chk_dbook__valid(V a0, V a1);
static V L2068(V *a);
static V W_Chk_dbook__valid(V *a);
static V F_Chk_dbook__valid_done(V a0, V a1, V a2);
static V L2070(V *a);
static V L2071(V *a);
static V W_Chk_dbook__valid_done(V *a);
static V F_Chk_dvalid_ddef(V a0, V a1, V a2);
static V L2072(V *a);
static V L2073(V *a);
static V L2074(V *a);
static V L2075(V *a);
static V L2076(V *a);
static V L2077(V *a);
static V L2078(V *a);
static V L2079(V *a);
static V L2080(V *a);
static V W_Chk_dvalid_ddef(V *a);
static V F_Chk_dbook__set(V a0, V a1, V a2);
static V W_Chk_dbook__set(V *a);
static V F_Chk_dK_dset__book(V a0);
static V L2082(V *a);
static V W_Chk_dK_dset__book(V *a);
static V F_Chk_dK_dbook(void);
static V L2083(V *a);
static V W_Chk_dK_dbook(V *a);
static V F_Chk_dK_dbind(V a2, V a3);
static V L2084(V *a);
static V W_Chk_dK_dbind(V *a);
static V F_Chk_dK_dgo(V a2, V a3);
static V W_Chk_dK_dgo(V *a);
static V F_Chk_dK_dgo_ddone(V a2, V a3);
static V W_Chk_dK_dgo_ddone(V *a);
static V F_Chk_dK_dpure(V a1);
static V L2087(V *a);
static V W_Chk_dK_dpure(V *a);
static V F_Chk_ddef__check(V a0, V a1, V a2);
static V L2088(V *a);
static V L2089(V *a);
static V L2090(V *a);
static V W_Chk_ddef__check(V *a);
static V F_Chk_dTld_dx__of(V a0);
static V W_Chk_dTld_dx__of(V *a);
static V F_Chk_ddef__check_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2094(V *a);
static V L2095(V *a);
static V W_Chk_ddef__check_dgo(V *a);
static V F_Chk_dTld_ddu(V a0);
static V W_Chk_dTld_ddu(V *a);
static V F_Chk_dTld_ddn(V a0);
static V W_Chk_dTld_ddn(V *a);
static V F_Chk_dterm__check(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2099(V *a);
static V L2100(V *a);
static V L2101(V *a);
static V L2102(V *a);
static V L2103(V *a);
static V L2104(V *a);
static V L2105(V *a);
static V S2106(void);
static V L2107(V *a);
static V L2108(V *a);
static V W_Chk_dterm__check(V *a);
static V F_Chk_dcheck_dinfer(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2109(V *a);
static V L2110(V *a);
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
static V L2119(V *a);
static V L2121(V *a);
static V L2122(V *a);
static V L2123(V *a);
static V L2124(V *a);
static V L2125(V *a);
static V L2126(V *a);
static V L2127(V *a);
static V L2128(V *a);
static V L2129(V *a);
static V L2130(V *a);
static V L2131(V *a);
static V L2132(V *a);
static V L2133(V *a);
static V W_Chk_dcmp_dgo(V *a);
static V F_Chk_dLazy_dand(V a0, V a1);
static V W_Chk_dLazy_dand(V *a);
static V F_Chk_dcmps(V a0, V a1, V a2, V a3);
static V L2137(V *a);
static V W_Chk_dcmps(V *a);
static V F_Chk_dStr_dsubset(V a0, V a1);
static V L2139(V *a);
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
static V L2147(V *a);
static V W_Chk_dcmp_dkind_dmin(V *a);
static V F_Chk_dcmp_dkind_drmin(V a0, V a1, V a2, V a3);
static V L2149(V *a);
static V W_Chk_dcmp_dkind_drmin(V *a);
static V F_Chk_dterm__apply1(V a0, V a1, V a2);
static V W_Chk_dterm__apply1(V *a);
static V F_Chk_dTm_dlam__k(V a0, V a1);
static V S2152(void);
static V W_Chk_dTm_dlam__k(V *a);
static V F_Chk_dcheck_dinfer_dcmp(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Chk_dcheck_dinfer_dcmp(V *a);
static V F_Chk_dCL_ddn(V a0);
static V W_Chk_dCL_ddn(V *a);
static V F_Chk_dK_derr(V a1, V a2, V a3, V a4, V a5);
static V L2156(V *a);
static V W_Chk_dK_derr(V *a);
static V F_Chk_derr(V a0, V a1, V a2, V a3, V a4, V a5);
static V S2157(void);
static V W_Chk_derr(V *a);
static V F_Chk_dterm__infer(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2159(V *a);
static V L2160(V *a);
static V L2161(V *a);
static V L2162(V *a);
static V L2163(V *a);
static V L2164(V *a);
static V L2165(V *a);
static V L2166(V *a);
static V L2167(V *a);
static V L2168(V *a);
static V L2169(V *a);
static V L2170(V *a);
static V L2171(V *a);
static V L2172(V *a);
static V W_Chk_dterm__infer(V *a);
static V F_Chk_dinfer_dfail(V a0, V a1, V a2);
static V L2173(V *a);
static V L2174(V *a);
static V L2175(V *a);
static V S2176(void);
static V S2177(void);
static V W_Chk_dinfer_dfail(V *a);
static V F_Chk_dTm_dname(V a0);
static V S2179(void);
static V W_Chk_dTm_dname(V *a);
static V F_Chk_dbook__ctr(V a0, V a1);
static V W_Chk_dbook__ctr(V *a);
static V F_Chk_dtyp(V a0);
static V W_Chk_dtyp(V *a);
static V F_Chk_dinfer_dadt(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V S2181(void);
static V S2182(void);
static V S2183(void);
static V W_Chk_dinfer_dadt(V *a);
static V F_Chk_dAD_dn(V a0);
static V W_Chk_dAD_dn(V *a);
static V F_Chk_dinfer_dadt_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2185(V *a);
static V W_Chk_dinfer_dadt_dgo(V *a);
static V F_Chk_dinfer_dadt_dfin(V a0);
static V W_Chk_dinfer_dadt_dfin(V *a);
static V F_Chk_dAD_dt(V a0);
static V W_Chk_dAD_dt(V *a);
static V F_Chk_dtele__check(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L2189(V *a);
static V L2190(V *a);
static V L2191(V *a);
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
static V L2202(V *a);
static V W_Chk_dtele__head(V *a);
static V F_Chk_dtele__head_dgo(V a0, V a1, V a2, V a3);
static V S2204(void);
static V W_Chk_dtele__head_dgo(V *a);
static V F_Chk_dK_dif(V a1, V a2, V a3);
static V W_Chk_dK_dif(V *a);
static V F_Chk_dbook__adt(V a0, V a1, V a2);
static V L2206(V *a);
static V W_Chk_dbook__adt(V *a);
static V F_Chk_dbook__adt_dgo(V a0, V a1, V a2, V a3);
static V S2208(void);
static V S2209(void);
static V W_Chk_dbook__adt_dgo(V *a);
static V F_Chk_dADT_dr(V a0);
static V W_Chk_dADT_dr(V *a);
static V F_Chk_dctrs__drop(V a0, V a1);
static V W_Chk_dctrs__drop(V *a);
static V F_Chk_dctrs__drop_dif(V a0, V a1, V a2);
static V W_Chk_dctrs__drop_dif(V *a);
static V F_Chk_dinfer_dapp(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2215(V *a);
static V W_Chk_dinfer_dapp(V *a);
static V F_Chk_dinfer_dapp_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V L2217(V *a);
static V L2218(V *a);
static V S2219(void);
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
static V S2223(void);
static V W_Chk_dinfer_dref(V *a);
static V F_Chk_dinfer_dref_dlive(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V L2224(V *a);
static V L2225(V *a);
static V L2226(V *a);
static V L2227(V *a);
static V S2228(void);
static V L2229(V *a);
static V W_Chk_dinfer_dref_dlive(V *a);
static V F_Chk_dinfer_dref_dself(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L2230(V *a);
static V S2231(void);
static V L2232(V *a);
static V W_Chk_dinfer_dref_dself(V *a);
static V F_Chk_dinfer_dref_dfin(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2234(void);
static V S2235(void);
static V W_Chk_dinfer_dref_dfin(V *a);
static V F_Chk_dinfer_dref_dbad__self(V a0, V a1, V a2, V a3);
static V W_Chk_dinfer_dref_dbad__self(V *a);
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
static V F_Chk_ddescend_dsub_dif(V a0, V a1, V a2, V a3);
static V W_Chk_ddescend_dsub_dif(V *a);
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
static V F_Chk_ddescend_dargs_dif(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Chk_ddescend_dargs_dif(V *a);
static V F_Chk_dinfer_dref_dinst(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V L2253(V *a);
static V L2254(V *a);
static V L2255(V *a);
static V W_Chk_dinfer_dref_dinst(V *a);
static V F_Chk_dList_ddrop__tm(V a0, V a1);
static V W_Chk_dList_ddrop__tm(V *a);
static V F_Chk_ddef__inst(V a0, V a1, V a2, V a3, V a4, V a5);
static V S2260(void);
static V W_Chk_ddef__inst(V *a);
static V F_Chk_ddef__inst_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2261(V *a);
static V L2262(V *a);
static V L2263(V *a);
static V S2264(void);
static V L2265(V *a);
static V S2266(void);
static V S2267(void);
static V W_Chk_ddef__inst_dgo(V *a);
static V F_Chk_dBook_dtmp(V a0, V a1);
static V W_Chk_dBook_dtmp(V *a);
static V F_Chk_ddef__inst_dfind(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L2270(V *a);
static V S2271(void);
static V W_Chk_ddef__inst_dfind(V *a);
static V F_Chk_ddef__inst_dnew(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2273(void);
static V W_Chk_ddef__inst_dnew(V *a);
static V F_Chk_ddef__inst_dmake(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2275(V *a);
static V S2276(void);
static V L2277(V *a);
static V L2278(V *a);
static V L2279(V *a);
static V L2280(V *a);
static V L2281(V *a);
static V L2282(V *a);
static V L2283(V *a);
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
static V L2292(V *a);
static V L2293(V *a);
static V L2294(V *a);
static V W_Chk_dinst_dargs(V *a);
static V F_Chk_dinst_dclosed(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2295(V *a);
static V W_Chk_dinst_dclosed(V *a);
static V F_Chk_dinst_dclosed_dgo(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dinst_dclosed_dgo(V *a);
static V F_Chk_dinst_dclosed_derr(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dinst_dclosed_derr(V *a);
static V F_Chk_dinst_dclosed_derr_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2299(void);
static V S2300(void);
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
static V F_Chk_dctx__get_dif(V a0, V a1, V a2, V a3);
static V W_Chk_dctx__get_dif(V *a);
static V F_Chk_dinfer_dvar_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2310(void);
static V W_Chk_dinfer_dvar_dgo(V *a);
static V F_Chk_duses__one(V a0, V a1);
static V W_Chk_duses__one(V *a);
static V F_Chk_dcheck_drwt(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10);
static V S2312(void);
static V L2313(V *a);
static V L2314(V *a);
static V L2315(V *a);
static V L2316(V *a);
static V L2317(V *a);
static V S2318(void);
static V W_Chk_dcheck_drwt(V *a);
static V F_Chk_dIR_dus(V a0);
static V W_Chk_dIR_dus(V *a);
static V F_Chk_dcheck_drfl(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2321(V *a);
static V W_Chk_dcheck_drfl(V *a);
static V F_Chk_dcheck_dtypeless(V a1, V a2, V a3, V a4, V a5);
static V L2322(V *a);
static V W_Chk_dcheck_dtypeless(V *a);
static V F_Chk_dtypeless__show(V a0, V a1, V a2);
static V S2323(void);
static V S2324(void);
static V W_Chk_dtypeless__show(V *a);
static V F_Chk_dtypeless_dnote(V a0, V a1);
static V S2326(void);
static V S2327(void);
static V S2328(void);
static V S2329(void);
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
static V S2334(void);
static V W_Chk_dctx__name(V *a);
static V F_Chk_dctx__name_dif(V a0, V a1, V a2, V a3);
static V W_Chk_dctx__name_dif(V *a);
static V F_Chk_dexpr__show(V a0, V a1, V a2);
static V S2337(void);
static V W_Chk_dexpr__show(V *a);
static V F_Chk_dcheck_delim(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V S2339(void);
static V L2340(V *a);
static V L2341(V *a);
static V W_Chk_dcheck_delim(V *a);
static V F_Chk_dcheck_delim_dadt(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V L2343(V *a);
static V S2344(void);
static V W_Chk_dcheck_delim_dadt(V *a);
static V F_Chk_dAD_dcs(V a0);
static V W_Chk_dAD_dcs(V *a);
static V F_Chk_dcheck_delim_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11);
static V L2347(V *a);
static V L2348(V *a);
static V S2349(void);
static V S2350(void);
static V W_Chk_dcheck_delim_dgo(V *a);
static V F_Chk_dctrs__find(V a0, V a1);
static V W_Chk_dctrs__find(V *a);
static V F_Chk_dctrs__find_dif(V a0, V a1, V a2, V a3);
static V W_Chk_dctrs__find_dif(V *a);
static V F_Chk_dcheck_dmat(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11, V a12, V a13);
static V S2354(void);
static V S2355(void);
static V L2356(V *a);
static V L2357(V *a);
static V L2358(V *a);
static V L2359(V *a);
static V L2360(V *a);
static V W_Chk_dcheck_dmat(V *a);
static V F_Chk_duses__join(V a0, V a1);
static V W_Chk_duses__join(V *a);
static V F_Chk_dAll_dk(V a0);
static V S2362(void);
static V W_Chk_dAll_dk(V *a);
static V F_Chk_dCL_dext(V a0, V a1, V a2);
static V L2365(V *a);
static V W_Chk_dCL_dext(V *a);
static V F_Chk_dtele__fill(V a0, V a1, V a2, V a3, V a4);
static V L2367(V *a);
static V L2368(V *a);
static V W_Chk_dtele__fill(V *a);
static V F_Chk_dCtrD_dnames(V a0);
static V W_Chk_dCtrD_dnames(V *a);
static V F_Chk_dctx__dead(V a0, V a1);
static V L2371(V *a);
static V L2372(V *a);
static V W_Chk_dctx__dead(V *a);
static V F_Chk_dctx__dead_dty(V a0, V a1);
static V W_Chk_dctx__dead_dty(V *a);
static V F_Chk_dctx__dead_dtld(V a0, V a1);
static V W_Chk_dctx__dead_dtld(V *a);
static V F_Chk_dcheck_dlit(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2376(V *a);
static V W_Chk_dcheck_dlit(V *a);
static V F_Chk_dLit_dv(V a0);
static V W_Chk_dLit_dv(V *a);
static V F_Chk_dlit_dctr(V a0);
static V S2379(void);
static V S2380(void);
static V S2381(void);
static V S2382(void);
static V W_Chk_dlit_dctr(V *a);
static V F_Chk_dcheck_dlit_dbase(V a0, V a1, V a2);
static V W_Chk_dcheck_dlit_dbase(V *a);
static V F_Chk_dcheck_dlit_dbase__adt(V a0);
static V W_Chk_dcheck_dlit_dbase__adt(V *a);
static V F_Chk_dcheck_dctr(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V L2385(V *a);
static V L2386(V *a);
static V L2387(V *a);
static V W_Chk_dcheck_dctr(V *a);
static V F_Chk_dbook__fam(V a0, V a1);
static V W_Chk_dbook__fam(V *a);
static V F_Chk_dbook__fam_dctr(V a0, V a1, V a2);
static V W_Chk_dbook__fam_dctr(V *a);
static V F_Chk_dbook__fam_dgo(V a0, V a1, V a2, V a3);
static V W_Chk_dbook__fam_dgo(V *a);
static V F_Chk_dcheck_dctr_dfind(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11);
static V L2391(V *a);
static V S2392(void);
static V S2393(void);
static V S2394(void);
static V S2395(void);
static V S2396(void);
static V S2397(void);
static V S2398(void);
static V W_Chk_dcheck_dctr_dfind(V *a);
static V F_Chk_dcheck_dctr_dfields(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L2399(V *a);
static V L2400(V *a);
static V W_Chk_dcheck_dctr_dfields(V *a);
static V F_Chk_dcheck_dlet_dbody(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10);
static V L2403(V *a);
static V L2404(V *a);
static V L2405(V *a);
static V W_Chk_dcheck_dlet_dbody(V *a);
static V F_Chk_dcheck_dlet_dused(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2408(V *a);
static V W_Chk_dcheck_dlet_dused(V *a);
static V F_Chk_duses__del(V a0, V a1);
static V W_Chk_duses__del(V *a);
static V F_Chk_duses__del_dif(V a0, V a1, V a2);
static V W_Chk_duses__del_dif(V *a);
static V F_Chk_duses__get(V a0, V a1);
static V W_Chk_duses__get(V *a);
static V F_Chk_duses__get_dif(V a0, V a1, V a2, V a3);
static V W_Chk_duses__get_dif(V *a);
static V F_Chk_dquant__used(V a0, V a1, V a2, V a3, V a4, V a5);
static V S2413(void);
static V W_Chk_dquant__used(V *a);
static V F_Chk_dlet_dvars(V a0, V a1, V a2);
static V W_Chk_dlet_dvars(V *a);
static V F_Chk_dcheck_dlets(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9);
static V L2419(V *a);
static V L2420(V *a);
static V W_Chk_dcheck_dlets(V *a);
static V F_Chk_dcheck__kind(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2422(V *a);
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
static V L2433(V *a);
static V L2434(V *a);
static V L2435(V *a);
static V L2436(V *a);
static V L2437(V *a);
static V W_Chk_dcheck_dlam(V *a);
static V F_Chk_dCL_dunder(V a0, V a1);
static V L2440(V *a);
static V W_Chk_dCL_dunder(V *a);
static V F_Chk_dQ_dis__lone(V a0);
static V W_Chk_dQ_dis__lone(V *a);
static V F_Chk_ddef__check_dtmpl(V a0, V a1, V a2, V a3, V a4);
static V L2443(V *a);
static V S2444(void);
static V L2445(V *a);
static V L2446(V *a);
static V S2447(void);
static V S2448(void);
static V L2449(V *a);
static V L2450(V *a);
static V L2451(V *a);
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
static V L2456(V *a);
static V L2457(V *a);
static V S2458(void);
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
static V L2463(V *a);
static V L2464(V *a);
static V L2465(V *a);
static V L2466(V *a);
static V W_Chk_dvalid_dadt(V *a);
static V F_Chk_dvalid_dctrs(V a0, V a1, V a2, V a3);
static V L2468(V *a);
static V W_Chk_dvalid_dctrs(V *a);
static V F_Chk_dvalid_dfields(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L2470(V *a);
static V L2471(V *a);
static V L2472(V *a);
static V L2473(V *a);
static V L2474(V *a);
static V W_Chk_dvalid_dfields(V *a);
static V F_Chk_dvalid_dtip(V a0, V a1, V a2, V a3, V a4);
static V L2475(V *a);
static V S2476(void);
static V S2477(void);
static V W_Chk_dvalid_dtip(V *a);
static V F_Chk_dvalid_dtip_dok(V a0, V a1, V a2, V a3);
static V L2479(V *a);
static V L2480(V *a);
static V W_Chk_dvalid_dtip_dok(V *a);
static V F_Chk_dvalid_dtip_dparams(V a0, V a1, V a2);
static V L2482(V *a);
static V W_Chk_dvalid_dtip_dparams(V *a);
static V F_Chk_dvalid_dtip_dvar(V a0, V a1);
static V W_Chk_dvalid_dtip_dvar(V *a);
static V W_Nat_dis__ge(V *a);
static V F_Chk_dvalid_dkind(V a0, V a1, V a2);
static V S2486(void);
static V S2487(void);
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
static V S2493(void);
static V S2494(void);
static V S2495(void);
static V S2496(void);
static V S2497(void);
static V S2498(void);
static V W_Chk_dcheck__book_dholes(V *a);
static V F_Chk_dbook__nil(void);
static V W_Chk_dbook__nil(V *a);
static V F_Chk_dcheck__book_downed(V a0);
static V S2499(void);
static V S2500(void);
static V S2501(void);
static V S2502(void);
static V S2503(void);
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
static V S2508(void);
static V S2509(void);
static V W_Chk_dshow__err(V *a);
static V F_Chk_derr__show(V a0);
static V S2516(void);
static V S2517(void);
static V S2518(void);
static V S2519(void);
static V S2520(void);
static V S2521(void);
static V S2522(void);
static V S2523(void);
static V S2524(void);
static V W_Chk_derr__show(V *a);
static V F_Chk_derr_dlines(V a0);
static V S2526(void);
static V W_Chk_derr_dlines(V *a);
static V F_Chk_dStr_dcount__nl(V a0);
static V W_Chk_dStr_dcount__nl(V *a);
static V F_Chk_derr_dlines_dgo(V a0, V a1);
static V W_Chk_derr_dlines_dgo(V *a);
static V F_Chk_dList_ddrop__str(V a0, V a1);
static V W_Chk_dList_ddrop__str(V *a);
static V F_Chk_derr_dlines_deach(V a0, V a1, V a2, V a3, V a4);
static V S2534(void);
static V W_Chk_derr_dlines_deach(V *a);
static V F_Chk_derr_dlines_done(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2536(void);
static V S2537(void);
static V S2538(void);
static V S2539(void);
static V W_Chk_derr_dlines_done(V *a);
static V F_Chk_dStr_dpadl(V a0, V a1);
static V S2541(void);
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
static V S2545(void);
static V S2546(void);
static V S2547(void);
static V W_Chk_derr_dctx__lines(V *a);
static V F_Chk_dList_dtake__str(V a0, V a1);
static V W_Chk_dList_dtake__str(V *a);
static V F_Chk_dList_dtake__strn(V a0, V a1);
static V W_Chk_dList_dtake__strn(V *a);
static V F_Chk_dStr_dpad(V a0, V a1);
static V S2551(void);
static V W_Chk_dStr_dpad(V *a);
static V F_Chk_derr_dmsg(V a0, V a1, V a2, V a3);
static V S2553(void);
static V S2554(void);
static V S2555(void);
static V W_Chk_derr_dmsg(V *a);
static V F_Chk_dshow__err_draw(V a0);
static V S2557(void);
static V W_Chk_dshow__err_draw(V *a);
static V F_Main_dchk_dload(V a0, V a1, V a2, V a3, V a4, V a5);
static V S2559(void);
static V W_Main_dchk_dload(V *a);
static V F_Path_dnorm(V a0);
static V S2561(void);
static V S2563(void);
static V S2564(void);
static V S2565(void);
static V W_Path_dnorm(V *a);
static V F_Path_dfold(V a0, V a1, V a2);
static V S2567(void);
static V W_Path_dfold(V *a);
static V F_Path_dpush(V a0, V a1, V a2);
static V S2569(void);
static V S2570(void);
static V S2571(void);
static V S2572(void);
static V S2573(void);
static V W_Path_dpush(V *a);
static V F_CS_dseen(V a0);
static V W_CS_dseen(V *a);
static V F_Chk_dSB2_dfind(V a0, V a1);
static V W_Chk_dSB2_dfind(V *a);
static V F_Chk_dSB2_dfind_dif(V a0, V a1, V a2, V a3);
static V W_Chk_dSB2_dfind_dif(V *a);
static V F_Main_dchk_dseen(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2578(void);
static V S2579(void);
static V S2580(void);
static V S2581(void);
static V S2582(void);
static V L2583(V *a);
static V W_Main_dchk_dseen(V *a);
static V F_Main_dchk_dread(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2585(void);
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
static V S2591(void);
static V S2592(void);
static V S2593(void);
static V W_Chk_dheader_dline(V *a);
static V F_Chk_dheader_dline_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V W_Chk_dheader_dline_dgo(V *a);
static V F_Chk_dheader_drest(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Chk_dheader_drest(V *a);
static V F_Chk_dheader_dgo_dnext(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dheader_dgo_dnext(V *a);
static V F_Chk_dStr_dwords(V a0);
static V S2596(void);
static V W_Chk_dStr_dwords(V *a);
static V F_Chk_dStr_dwords_dgo(V a0, V a1, V a2);
static V W_Chk_dStr_dwords_dgo(V *a);
static V F_Chk_dis__space(V a0);
static V W_Chk_dis__space(V *a);
static V F_Chk_dStr_dwords_dchr(V a0, V a1, V a2, V a3, V a4);
static V S2599(void);
static V W_Chk_dStr_dwords_dchr(V *a);
static V F_Chk_dStr_dwords_dpush(V a0, V a1);
static V W_Chk_dStr_dwords_dpush(V *a);
static V F_Chk_dStr_duntil__hash(V a0);
static V S2601(void);
static V W_Chk_dStr_duntil__hash(V *a);
static V F_Chk_dimport_dparse(V a0);
static V S2603(void);
static V S2604(void);
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
static V S2609(void);
static V S2610(void);
static V S2611(void);
static V W_Chk_dheader_dimp(V *a);
static V F_Chk_dheader_dimp_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2615(void);
static V W_Chk_dheader_dimp_dgo(V *a);
static V F_Chk_dStr_dindex__of(V a0, V a1, V a2);
static V W_Chk_dStr_dindex__of(V *a);
static V F_Chk_dStr_dindex__of_dif(V a0, V a1, V a2, V a3);
static V W_Chk_dStr_dindex__of_dif(V *a);
static V F_Chk_derr0(V a0, V a1, V a2);
static V S2618(void);
static V S2619(void);
static V W_Chk_derr0(V *a);
static V F_Chk_dStr_dfirst(V a0);
static V W_Chk_dStr_dfirst(V *a);
static V F_Main_dchk_dhdr(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2623(V *a);
static V W_Main_dchk_dhdr(V *a);
static V F_Main_dchk_dparse(V a0, V a1, V a2, V a3, V a4, V a5);
static V S2627(void);
static V W_Main_dchk_dparse(V *a);
static V F_Chk_dparse__file(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Chk_dparse__file(V *a);
static V F_Chk_dP_ddecls(void);
static V L2628(V *a);
static V L2629(V *a);
static V W_Chk_dP_ddecls(V *a);
static V F_Chk_dP_ddecl(void);
static V L2630(V *a);
static V S2631(void);
static V L2632(V *a);
static V S2633(void);
static V L2634(V *a);
static V S2635(void);
static V L2636(V *a);
static V S2637(void);
static V L2638(V *a);
static V L2639(V *a);
static V W_Chk_dP_ddecl(V *a);
static V F_Chk_dP_ddecl_dgo(V a0, V a1, V a2, V a3);
static V S2641(void);
static V W_Chk_dP_ddecl_dgo(V *a);
static V F_Chk_dP_dfail(V a1);
static V L2642(V *a);
static V L2643(V *a);
static V S2644(void);
static V W_Chk_dP_dfail(V *a);
static V F_Chk_dP_dthrow(V a1);
static V L2645(V *a);
static V W_Chk_dP_dthrow(V *a);
static V F_Chk_dP_dfail_dgo(V a0, V a1);
static V S2648(void);
static V S2649(void);
static V S2650(void);
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
static V S2657(void);
static V L2658(V *a);
static V L2659(V *a);
static V L2660(V *a);
static V L2661(V *a);
static V S2662(void);
static V L2663(V *a);
static V L2664(V *a);
static V L2665(V *a);
static V L2666(V *a);
static V L2667(V *a);
static V L2668(V *a);
static V W_Chk_dP_dlaw(V *a);
static V F_Chk_dP_dlaw_dfin(V a0, V a1, V a2, V a3);
static V W_Chk_dP_dlaw_dfin(V *a);
static V F_Chk_dLC_dbind(V a0, V a1);
static V W_Chk_dLC_dbind(V *a);
static V F_Chk_dLC_dbind_done(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S2673(void);
static V W_Chk_dLC_dbind_done(V *a);
static V F_Chk_dhigher0(V a0, V a1);
static V W_Chk_dhigher0(V *a);
static V F_Chk_dLC_dfirst__exs(V a0);
static V W_Chk_dLC_dfirst__exs(V *a);
static V F_Chk_dbook__push(V a0, V a1);
static V W_Chk_dbook__push(V *a);
static V F_Chk_dP_dset__book(V a0);
static V L2676(V *a);
static V W_Chk_dP_dset__book(V *a);
static V F_Chk_dPS_dset__book(V a0, V a1);
static V W_Chk_dPS_dset__book(V *a);
static V F_Chk_dP_dbook(void);
static V L2678(V *a);
static V W_Chk_dP_dbook(V *a);
static V F_Chk_dPS_dbook(V a0);
static V W_Chk_dPS_dbook(V *a);
static V F_Chk_dP_dbind(V a2, V a3);
static V L2680(V *a);
static V W_Chk_dP_dbind(V *a);
static V F_Chk_dP_dclose(V a0);
static V L2681(V *a);
static V W_Chk_dP_dclose(V *a);
static V F_Chk_dP_dclose_dgo(V a0, V a1);
static V W_Chk_dP_dclose_dgo(V *a);
static V F_Chk_dSB_ddrop(V a0, V a1);
static V W_Chk_dSB_ddrop(V *a);
static V F_Chk_dP_dblock(void);
static V L2685(V *a);
static V L2686(V *a);
static V L2687(V *a);
static V W_Chk_dP_dblock(V *a);
static V F_Chk_dP_dflatten(V a0, V a1);
static V W_Chk_dP_dflatten(V *a);
static V F_Chk_dP_dmatch__flatten(V a0, V a1, V a2, V a3);
static V S2691(void);
static V W_Chk_dP_dmatch__flatten(V *a);
static V F_Chk_dP_dmf_dvars(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dP_dmf_dvars(V *a);
static V F_Chk_dTm_dvar__i(V a0);
static V W_Chk_dTm_dvar__i(V *a);
static V F_Chk_dvars_dfind(V a0, V a1);
static V W_Chk_dvars_dfind(V *a);
static V F_Chk_dvars_dfind_dif(V a0, V a1, V a2, V a3);
static V W_Chk_dvars_dfind_dif(V *a);
static V F_Chk_dP_dmf_dcol(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Chk_dP_dmf_dcol(V *a);
static V F_Chk_dP_dmf_dskip(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2697(V *a);
static V W_Chk_dP_dmf_dskip(V *a);
static V F_Chk_dflatten_dlams(V a0, V a1);
static V W_Chk_dflatten_dlams(V *a);
static V F_Chk_dP_dpure(V a1);
static V L2699(V *a);
static V W_Chk_dP_dpure(V *a);
static V F_Chk_drows_dctr(V a0);
static V W_Chk_drows_dctr(V *a);
static V F_Chk_dP_dmf_dcol_dvar(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V W_Chk_dP_dmf_dcol_dvar(V *a);
static V F_Chk_dP_dmf_dctr(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L2705(V *a);
static V L2706(V *a);
static V L2707(V *a);
static V L2708(V *a);
static V L2709(V *a);
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
static V L2721(V *a);
static V L2722(V *a);
static V L2723(V *a);
static V S2724(void);
static V W_Chk_dP_dmf_dfields(V *a);
static V F_Chk_dP_dfresh__id(void);
static V L2725(V *a);
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
static V L2731(V *a);
static V W_Chk_dP_dmf_dvarcol(V *a);
static V F_Chk_dvars_dreplace(V a0, V a1);
static V W_Chk_dvars_dreplace(V *a);
static V F_Chk_dP_dmf_dvarrows(V a0, V a1);
static V L2734(V *a);
static V S2735(void);
static V W_Chk_dP_dmf_dvarrows(V *a);
static V F_Chk_dPt_dwith__q(V a0, V a1);
static V W_Chk_dPt_dwith__q(V *a);
static V F_Chk_dTm_dstrip__subs(V a0);
static V W_Chk_dTm_dstrip__subs(V *a);
static V F_Chk_dP_dmf_dbad(V a0, V a1);
static V S2739(void);
static V S2740(void);
static V S2741(void);
static V S2742(void);
static V S2743(void);
static V W_Chk_dP_dmf_dbad(V *a);
static V F_Chk_dP_dflatten_dlocal(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dP_dflatten_dlocal(V *a);
static V F_Chk_dP_dflatten_dlet(V a0, V a1, V a2, V a3, V a4);
static V L2745(V *a);
static V L2746(V *a);
static V S2747(void);
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
static V S2755(void);
static V W_Chk_dP_dflatten_dstrip(V *a);
static V F_Chk_dP_dbody(V a0);
static V L2756(V *a);
static V L2757(V *a);
static V L2758(V *a);
static V S2759(void);
static V L2760(V *a);
static V W_Chk_dP_dbody(V *a);
static V F_Chk_dP_dbody_dlocal(V a0, V a1, V a2);
static V S2761(void);
static V L2762(V *a);
static V L2763(V *a);
static V L2764(V *a);
static V L2765(V *a);
static V L2766(V *a);
static V L2767(V *a);
static V S2768(void);
static V L2769(V *a);
static V L2770(V *a);
static V L2771(V *a);
static V S2772(void);
static V L2773(V *a);
static V L2774(V *a);
static V S2775(void);
static V L2776(V *a);
static V W_Chk_dP_dbody_dlocal(V *a);
static V F_Chk_dP_dbody_dlocal_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Chk_dP_dbody_dlocal_dgo(V *a);
static V F_Chk_dP_dbody_dlet(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2779(V *a);
static V L2780(V *a);
static V L2781(V *a);
static V S2782(void);
static V L2783(V *a);
static V L2784(V *a);
static V L2785(V *a);
static V L2786(V *a);
static V L2787(V *a);
static V W_Chk_dP_dbody_dlet(V *a);
static V F_Chk_dP_dbody_dbinders(V a0, V a1);
static V S2789(void);
static V L2790(V *a);
static V L2791(V *a);
static V L2792(V *a);
static V W_Chk_dP_dbody_dbinders(V *a);
static V F_Chk_dP_dpatt(V a0);
static V L2794(V *a);
static V W_Chk_dP_dpatt(V *a);
static V F_Chk_dTm_dis__var(V a0);
static V W_Chk_dTm_dis__var(V *a);
static V F_Chk_dP_dpatt_dvar(V a0, V a1);
static V L2797(V *a);
static V L2798(V *a);
static V W_Chk_dP_dpatt_dvar(V *a);
static V F_Chk_dP_dpatt_dother(V a0);
static V L2799(V *a);
static V S2800(void);
static V W_Chk_dP_dpatt_dother(V *a);
static V F_Chk_dP_dpatt_dvar_dgo(V a0, V a1);
static V S2802(void);
static V S2803(void);
static V S2804(void);
static V W_Chk_dP_dpatt_dvar_dgo(V *a);
static V F_Chk_dP_dbinder(V a0);
static V S2806(void);
static V W_Chk_dP_dbinder(V *a);
static V F_Chk_dP_dbinder_dgo(V a0, V a1, V a2);
static V L2807(V *a);
static V W_Chk_dP_dbinder_dgo(V *a);
static V F_Chk_dP_dopen(V a0);
static V L2808(V *a);
static V W_Chk_dP_dopen(V *a);
static V F_Chk_dP_dopen_dgo(V a0, V a1);
static V S2810(void);
static V W_Chk_dP_dopen_dgo(V *a);
static V F_Chk_dPS_dopened(V a0, V a1, V a2, V a3);
static V W_Chk_dPS_dopened(V *a);
static V F_Chk_dPS_dpush(V a0, V a1);
static V W_Chk_dPS_dpush(V *a);
static V F_Chk_dP_dreso(V a0);
static V L2813(V *a);
static V W_Chk_dP_dreso(V *a);
static V F_Chk_dPS_dreso(V a0, V a1);
static V W_Chk_dPS_dreso(V *a);
static V F_Chk_dPS_dal(V a0);
static V W_Chk_dPS_dal(V *a);
static V F_Chk_dPS_dqual(V a0, V a1);
static V S2817(void);
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
static V S2824(void);
static V S2825(void);
static V W_Chk_dnat__full(V *a);
static V F_Chk_dStr_dcodes(V a0);
static V W_Chk_dStr_dcodes(V *a);
static V F_Chk_dlit__chain(V a0, V a1);
static V S2828(void);
static V S2829(void);
static V W_Chk_dlit__chain(V *a);
static V F_Chk_dP_dpatt_dctr(V a0, V a1, V a2, V a3);
static V S2831(void);
static V S2832(void);
static V W_Chk_dP_dpatt_dctr(V *a);
static V F_Chk_dP_dpatt_dctr_dn(V a0, V a1, V a2, V a3, V a4);
static V S2834(void);
static V S2835(void);
static V S2836(void);
static V S2837(void);
static V L2838(V *a);
static V W_Chk_dP_dpatt_dctr_dn(V *a);
static V F_Chk_dP_dpatts(V a0);
static V L2840(V *a);
static V L2841(V *a);
static V W_Chk_dP_dpatts(V *a);
static V F_Chk_dP_dstn(void);
static V L2842(V *a);
static V W_Chk_dP_dstn(V *a);
static V F_Chk_dPS_dstn(V a0);
static V W_Chk_dPS_dstn(V *a);
static V F_Chk_dP_dtake(V a0);
static V L2844(V *a);
static V W_Chk_dP_dtake(V *a);
static V F_Chk_dP_dtake_dif(V a0, V a1);
static V L2846(V *a);
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
static V L2851(V *a);
static V W_Chk_dP_dat(V *a);
static V F_Chk_dCur_drest(V a0);
static V W_Chk_dCur_drest(V *a);
static V F_Chk_dStr_dprefix(V a0, V a1);
static V W_Chk_dStr_dprefix(V *a);
static V F_Chk_dP_dskip(void);
static V L2853(V *a);
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
static V L2856(V *a);
static V W_Chk_dP_dbody_dvals_dmore(V *a);
static V F_Chk_dP_dterm0(void);
static V W_Chk_dP_dterm0(V *a);
static V F_Chk_dP_dterm(V a0);
static V L2857(V *a);
static V L2858(V *a);
static V L2859(V *a);
static V L2860(V *a);
static V W_Chk_dP_dterm(V *a);
static V F_Chk_dTm_dspanned(V a0, V a1);
static V W_Chk_dTm_dspanned(V *a);
static V F_Chk_dP_dops(V a0, V a1);
static V L2862(V *a);
static V L2863(V *a);
static V L2864(V *a);
static V L2865(V *a);
static V S2867(void);
static V S2868(void);
static V S2870(void);
static V S2871(void);
static V S2872(void);
static V S2873(void);
static V S2874(void);
static V W_Chk_dP_dops(V *a);
static V F_Chk_dops_dlt(V a0, V a1, V a2);
static V S2876(void);
static V S2877(void);
static V W_Chk_dops_dlt(V *a);
static V F_Chk_dStr_dsecond(V a0);
static V W_Chk_dStr_dsecond(V *a);
static V F_Chk_dP_dops_dgo(V a0, V a1, V a2, V a3, V a4);
static V S2880(void);
static V W_Chk_dP_dops_dgo(V *a);
static V F_Chk_dOPS(void);
static V S2881(void);
static V S2882(void);
static V S2883(void);
static V S2884(void);
static V S2885(void);
static V S2886(void);
static V S2887(void);
static V S2888(void);
static V S2889(void);
static V S2890(void);
static V S2891(void);
static V S2892(void);
static V S2893(void);
static V S2894(void);
static V S2895(void);
static V S2896(void);
static V S2897(void);
static V S2898(void);
static V S2899(void);
static V S2900(void);
static V S2901(void);
static V S2902(void);
static V S2903(void);
static V S2904(void);
static V S2905(void);
static V S2906(void);
static V S2907(void);
static V S2908(void);
static V S2909(void);
static V S2910(void);
static V S2911(void);
static V S2912(void);
static V S2913(void);
static V S2914(void);
static V S2915(void);
static V S2916(void);
static V S2917(void);
static V S2918(void);
static V W_Chk_dOPS(V *a);
static V F_Chk_dop_dfind(V a0, V a1, V a2);
static V W_Chk_dop_dfind(V *a);
static V F_Chk_dop_dok(V a0, V a1, V a2);
static V S2922(void);
static V S2923(void);
static V S2924(void);
static V W_Chk_dop_dok(V *a);
static V F_Chk_dop_dfind_dif(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dop_dfind_dif(V *a);
static V F_Chk_dP_dinfix(V a0, V a1, V a2, V a3);
static V W_Chk_dP_dinfix(V *a);
static V F_Chk_dP_dinfix_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V L2927(V *a);
static V L2928(V *a);
static V L2929(V *a);
static V L2930(V *a);
static V L2931(V *a);
static V W_Chk_dP_dinfix_dgo(V *a);
static V F_Chk_dinfix_dbuild(V a0, V a1, V a2, V a3, V a4, V a5);
static V S2932(void);
static V S2933(void);
static V S2934(void);
static V S2935(void);
static V S2936(void);
static V S2937(void);
static V W_Chk_dinfix_dbuild(V *a);
static V F_Chk_dspan_dgrow(V a0);
static V W_Chk_dspan_dgrow(V *a);
static V F_Chk_dP_dspan_dfrom(V a0);
static V W_Chk_dP_dspan_dfrom(V *a);
static V F_Chk_dP_dspan(V a0);
static V L2939(V *a);
static V W_Chk_dP_dspan(V *a);
static V F_Chk_dP_dpos(void);
static V L2940(V *a);
static V W_Chk_dP_dpos(V *a);
static V F_Chk_dP_dminq(V a0, V a1);
static V S2941(void);
static V L2942(V *a);
static V L2943(V *a);
static V L2944(V *a);
static V W_Chk_dP_dminq(V *a);
static V F_Chk_dP_darrow(V a0, V a1);
static V S2945(void);
static V L2946(V *a);
static V L2947(V *a);
static V L2948(V *a);
static V S2949(void);
static V L2950(V *a);
static V S2951(void);
static V W_Chk_dP_darrow(V *a);
static V F_Chk_dP_dlam(V a0, V a1);
static V S2952(void);
static V L2953(V *a);
static V L2954(V *a);
static V L2955(V *a);
static V L2956(V *a);
static V L2957(V *a);
static V W_Chk_dP_dlam(V *a);
static V F_Chk_dlam_dbuild(V a0, V a1);
static V W_Chk_dlam_dbuild(V *a);
static V F_Chk_dP_dlt(V a0, V a1);
static V L2959(V *a);
static V L2960(V *a);
static V L2961(V *a);
static V L2962(V *a);
static V L2963(V *a);
static V L2964(V *a);
static V S2965(void);
static V L2966(V *a);
static V S2967(void);
static V L2968(V *a);
static V S2969(void);
static V W_Chk_dP_dlt(V *a);
static V F_Chk_dP_dlt_dadt(V a0, V a1, V a2, V a3);
static V S2970(void);
static V W_Chk_dP_dlt_dadt(V *a);
static V F_Chk_dP_dlt_dadt_dgo(V a0, V a1, V a2, V a3);
static V S2971(void);
static V L2972(V *a);
static V L2973(V *a);
static V S2974(void);
static V L2975(V *a);
static V L2976(V *a);
static V W_Chk_dP_dlt_dadt_dgo(V *a);
static V F_Chk_dP_dfill(V a0, V a1, V a2);
static V L2977(V *a);
static V W_Chk_dP_dfill(V *a);
static V F_Chk_dTld_dadt__fill(V a0, V a1);
static V W_Chk_dTld_dadt__fill(V *a);
static V F_Chk_dfill_dgo(V a0, V a1, V a2);
static V W_Chk_dfill_dgo(V *a);
static V F_Chk_dList_drepeat__tm(V a0, V a1);
static V W_Chk_dList_drepeat__tm(V *a);
static V F_Chk_dP_dargs(V a0);
static V L2981(V *a);
static V L2982(V *a);
static V W_Chk_dP_dargs(V *a);
static V F_Chk_dP_dargs_done(V a0);
static V L2983(V *a);
static V L2984(V *a);
static V S2985(void);
static V L2986(V *a);
static V L2987(V *a);
static V W_Chk_dP_dargs_done(V *a);
static V F_Chk_dTm_dis__ref(V a0);
static V W_Chk_dTm_dis__ref(V *a);
static V F_Chk_dP_dbump(void);
static V L2989(V *a);
static V W_Chk_dP_dbump(V *a);
static V F_Chk_dP_dindex(V a0, V a1);
static V L2990(V *a);
static V L2991(V *a);
static V S2992(void);
static V L2993(V *a);
static V L2994(V *a);
static V S2995(void);
static V L2996(V *a);
static V L2997(V *a);
static V L2998(V *a);
static V S2999(void);
static V L3000(V *a);
static V S3001(void);
static V S3002(void);
static V W_Chk_dP_dindex(V *a);
static V F_Chk_dP_dindex_dset(V a0, V a1, V a2, V a3);
static V L3003(V *a);
static V S3004(void);
static V S3005(void);
static V W_Chk_dP_dindex_dset(V *a);
static V F_Chk_dapps(V a0, V a1, V a2);
static V W_Chk_dapps(V *a);
static V F_Chk_dP_dnl(void);
static V L3007(V *a);
static V W_Chk_dP_dnl(V *a);
static V F_Chk_dCur_dnl(V a0);
static V W_Chk_dCur_dnl(V *a);
static V F_Chk_dP_dns(V a0, V a1);
static V L3010(V *a);
static V W_Chk_dP_dns(V *a);
static V F_Chk_dP_dns_dapp(V a0, V a1);
static V S3013(void);
static V S3014(void);
static V S3015(void);
static V W_Chk_dP_dns_dapp(V *a);
static V F_Chk_dStr_dlast__dot(V a0);
static V W_Chk_dStr_dlast__dot(V *a);
static V F_Chk_dStr_dlast__dot_dgo(V a0, V a1, V a2);
static V W_Chk_dStr_dlast__dot_dgo(V *a);
static V F_Chk_dP_dns_dref(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L3019(V *a);
static V W_Chk_dP_dns_dref(V *a);
static V F_Chk_dapps_dspan(V a0, V a1, V a2);
static V W_Chk_dapps_dspan(V *a);
static V F_Chk_dP_dns_dargs(V a0, V a1);
static V L3021(V *a);
static V L3022(V *a);
static V W_Chk_dP_dns_dargs(V *a);
static V F_Chk_dP_dns_dop(V a0, V a1, V a2, V a3, V a4, V a5);
static V S3024(void);
static V S3025(void);
static V W_Chk_dP_dns_dop(V *a);
static V F_Chk_dP_dns_dop_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V L3026(V *a);
static V L3027(V *a);
static V W_Chk_dP_dns_dop_dgo(V *a);
static V F_Chk_dP_deat(V a0);
static V L3028(V *a);
static V L3029(V *a);
static V W_Chk_dP_deat(V *a);
static V F_Chk_dP_deat_dif(V a0, V a1);
static V S3031(void);
static V S3032(void);
static V W_Chk_dP_deat_dif(V *a);
static V F_Chk_dP_dcall(V a0, V a1);
static V L3033(V *a);
static V S3034(void);
static V L3035(V *a);
static V W_Chk_dP_dcall(V *a);
static V F_Chk_dP_dcall_dargs(V a0, V a1);
static V L3036(V *a);
static V L3037(V *a);
static V S3038(void);
static V L3039(V *a);
static V L3040(V *a);
static V L3041(V *a);
static V S3042(void);
static V L3043(V *a);
static V L3044(V *a);
static V W_Chk_dP_dcall_dargs(V *a);
static V F_Chk_dP_dcall_dtmpl(V a0, V a1, V a2);
static V S3045(void);
static V L3046(V *a);
static V W_Chk_dP_dcall_dtmpl(V *a);
static V F_Chk_dP_dcall_dtmpl_done(V a0, V a1, V a2);
static V S3047(void);
static V S3048(void);
static V S3049(void);
static V W_Chk_dP_dcall_dtmpl_done(V *a);
static V F_Chk_dP_dcall_dtmpl_dgo(V a0, V a1, V a2);
static V L3050(V *a);
static V L3051(V *a);
static V L3052(V *a);
static V S3053(void);
static V L3054(V *a);
static V L3055(V *a);
static V W_Chk_dP_dcall_dtmpl_dgo(V *a);
static V F_Chk_dP_dcall_dbang(V a0, V a1);
static V S3056(void);
static V W_Chk_dP_dcall_dbang(V *a);
static V F_Chk_dP_dcall_dbang_dgo(V a0, V a1);
static V L3057(V *a);
static V W_Chk_dP_dcall_dbang_dgo(V *a);
static V F_Chk_dTm_dbang(V a0);
static V W_Chk_dTm_dbang(V *a);
static V F_Chk_dP_dcall_dhead(V a0);
static V W_Chk_dP_dcall_dhead(V *a);
static V F_Chk_dP_dcall_dhead_dvar(V a0, V a1, V a2);
static V L3060(V *a);
static V L3061(V *a);
static V W_Chk_dP_dcall_dhead_dvar(V *a);
static V F_Chk_dP_dlookup(V a0);
static V L3062(V *a);
static V W_Chk_dP_dlookup(V *a);
static V F_Chk_dPS_dstk(V a0);
static V W_Chk_dPS_dstk(V *a);
static V F_Chk_dSB_dfind(V a0, V a1);
static V W_Chk_dSB_dfind(V *a);
static V F_Chk_dSB_dfind_dif(V a0, V a1, V a2, V a3);
static V W_Chk_dSB_dfind_dif(V *a);
static V F_Chk_dP_dprev(void);
static V L3066(V *a);
static V W_Chk_dP_dprev(V *a);
static V F_Chk_dCur_dprev(V a0);
static V W_Chk_dCur_dprev(V *a);
static V F_Chk_dP_dpeek__rest(void);
static V L3068(V *a);
static V W_Chk_dP_dpeek__rest(V *a);
static V F_Chk_dP_dbase(V a0);
static V L3069(V *a);
static V W_Chk_dP_dbase(V *a);
static V F_Chk_dP_dbase_dgo(V a0, V a1, V a2);
static V L3071(V *a);
static V W_Chk_dP_dbase_dgo(V *a);
static V F_Chk_dP_dbase_dsym(V a0, V a1);
static V S3072(void);
static V S3073(void);
static V S3074(void);
static V S3075(void);
static V S3076(void);
static V S3077(void);
static V S3078(void);
static V S3079(void);
static V S3080(void);
static V S3081(void);
static V S3082(void);
static V W_Chk_dP_dbase_dsym(V *a);
static V F_Chk_dP_dbase_dsym_dgo(V a0, V a1, V a2);
static V L3084(V *a);
static V L3085(V *a);
static V S3086(void);
static V W_Chk_dP_dbase_dsym_dgo(V *a);
static V F_Chk_dP_dhole(V a0);
static V L3087(V *a);
static V L3088(V *a);
static V S3089(void);
static V L3090(V *a);
static V L3091(V *a);
static V W_Chk_dP_dhole(V *a);
static V F_Chk_dP_dcount__hole(void);
static V L3092(V *a);
static V W_Chk_dP_dcount__hole(V *a);
static V F_Chk_dbook__hole(V a0);
static V W_Chk_dbook__hole(V *a);
static V F_Chk_dP_dname(void);
static V L3094(V *a);
static V W_Chk_dP_dname(V *a);
static V F_Chk_dP_dname_dcheck(V a0);
static V W_Chk_dP_dname_dcheck(V *a);
static V F_Chk_dKEYWORDS(void);
static V S3095(void);
static V S3096(void);
static V S3097(void);
static V S3098(void);
static V S3099(void);
static V S3100(void);
static V S3101(void);
static V S3102(void);
static V S3103(void);
static V S3104(void);
static V S3105(void);
static V S3106(void);
static V S3107(void);
static V S3108(void);
static V S3109(void);
static V S3110(void);
static V W_Chk_dKEYWORDS(V *a);
static V F_Chk_dP_dname_dcheck_dc(V a0, V a1);
static V S3112(void);
static V S3113(void);
static V W_Chk_dP_dname_dcheck_dc(V *a);
static V F_Chk_dP_dlexeme(void);
static V L3114(V *a);
static V L3115(V *a);
static V W_Chk_dP_dlexeme(V *a);
static V F_Chk_dP_dlexeme_dif(V a0, V a1);
static V S3117(void);
static V W_Chk_dP_dlexeme_dif(V *a);
static V F_Chk_dP_dlexeme_dgo(V a0);
static V S3118(void);
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
static V L3121(V *a);
static V W_Chk_dP_dlexeme_dfin(V *a);
static V F_Chk_dP_dlexeme_ddot(V a0);
static V S3122(void);
static V W_Chk_dP_dlexeme_ddot(V *a);
static V F_Chk_dP_dlexeme_ddot_dc(V a0, V a1);
static V S3124(void);
static V W_Chk_dP_dlexeme_ddot_dc(V *a);
static V F_Chk_dP_dset__cur(V a0);
static V L3125(V *a);
static V W_Chk_dP_dset__cur(V *a);
static V F_Chk_dP_dcur(void);
static V L3126(V *a);
static V W_Chk_dP_dcur(V *a);
static V F_Chk_dP_dstr__lit(V a0);
static V L3127(V *a);
static V L3128(V *a);
static V L3129(V *a);
static V W_Chk_dP_dstr__lit(V *a);
static V F_Chk_dlit__of(V a0, V a1);
static V W_Chk_dlit__of(V *a);
static V F_Chk_dStr_dfrom__codes(V a0);
static V W_Chk_dStr_dfrom__codes(V *a);
static V F_Chk_dcodes_dplain(V a0);
static V W_Chk_dcodes_dplain(V *a);
static V F_Chk_dP_dstr_dgo(V a0);
static V S3132(void);
static V L3133(V *a);
static V L3134(V *a);
static V S3135(void);
static V W_Chk_dP_dstr_dgo(V *a);
static V F_Chk_dP_dstr_dmore(V a0);
static V L3136(V *a);
static V W_Chk_dP_dstr_dmore(V *a);
static V F_Chk_dP_dchar(void);
static V S3137(void);
static V L3138(V *a);
static V W_Chk_dP_dchar(V *a);
static V F_Chk_dP_dchar_dplain(void);
static V L3139(V *a);
static V S3140(void);
static V W_Chk_dP_dchar_dplain(V *a);
static V F_Chk_dP_dchar_dtake(V a0);
static V L3141(V *a);
static V W_Chk_dP_dchar_dtake(V *a);
static V F_Chk_dP_dpeek(void);
static V L3142(V *a);
static V W_Chk_dP_dpeek(V *a);
static V F_Chk_dP_descape(void);
static V L3143(V *a);
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
static V L3150(V *a);
static V L3151(V *a);
static V W_Chk_dP_descape_du(V *a);
static V F_Chk_dESCAPES(void);
static V W_Chk_dESCAPES(V *a);
static V F_Chk_descape_dfind(V a0, V a1);
static V W_Chk_descape_dfind(V *a);
static V F_Chk_descape_dfind_dif(V a0, V a1, V a2, V a3);
static V W_Chk_descape_dfind_dif(V *a);
static V F_Chk_dP_descape_dnamed(V a0);
static V S3155(void);
static V W_Chk_dP_descape_dnamed(V *a);
static V F_Chk_dP_descape_du_dgo(V a0);
static V L3158(V *a);
static V W_Chk_dP_descape_du_dgo(V *a);
static V F_Chk_dP_dchr__lit(V a0);
static V L3159(V *a);
static V L3160(V *a);
static V S3161(void);
static V L3162(V *a);
static V W_Chk_dP_dchr__lit(V *a);
static V F_Chk_dP_dchr__lit_dfin(V a0, V a1, V a2);
static V L3164(V *a);
static V S3165(void);
static V S3166(void);
static V W_Chk_dP_dchr__lit_dfin(V *a);
static V F_Chk_dP_dbrack(V a0);
static V L3167(V *a);
static V L3168(V *a);
static V S3169(void);
static V L3170(V *a);
static V W_Chk_dP_dbrack(V *a);
static V F_Chk_dP_dbrack_dfirst(V a0);
static V L3171(V *a);
static V L3172(V *a);
static V S3173(void);
static V L3174(V *a);
static V W_Chk_dP_dbrack_dfirst(V *a);
static V F_Chk_dP_dbrack_dlist(V a0, V a1);
static V S3175(void);
static V L3176(V *a);
static V S3177(void);
static V L3178(V *a);
static V L3179(V *a);
static V W_Chk_dP_dbrack_dlist(V *a);
static V F_Chk_dlist_dbuild(V a0, V a1);
static V S3181(void);
static V S3182(void);
static V W_Chk_dlist_dbuild(V *a);
static V F_Chk_dP_dbrack_darr(V a0, V a1);
static V L3183(V *a);
static V L3184(V *a);
static V S3185(void);
static V L3186(V *a);
static V S3187(void);
static V L3188(V *a);
static V L3189(V *a);
static V S3190(void);
static V L3191(V *a);
static V L3192(V *a);
static V L3193(V *a);
static V L3194(V *a);
static V S3195(void);
static V W_Chk_dP_dbrack_darr(V *a);
static V F_Chk_dP_dbrack_ddepth(V a0, V a1);
static V W_Chk_dP_dbrack_ddepth(V *a);
static V F_Chk_dP_dbrack_dlog2(V a0, V a1);
static V S3198(void);
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
static V S3201(void);
static V W_Chk_dP_dbrack_dlog2_dgo(V *a);
static V F_Chk_dP_dtup(V a0);
static V L3202(V *a);
static V L3203(V *a);
static V L3204(V *a);
static V L3205(V *a);
static V L3206(V *a);
static V S3207(void);
static V L3208(V *a);
static V W_Chk_dP_dtup(V *a);
static V F_Chk_dP_dtup_dend(V a0);
static V L3209(V *a);
static V S3210(void);
static V L3211(V *a);
static V L3212(V *a);
static V S3213(void);
static V L3214(V *a);
static V W_Chk_dP_dtup_dend(V *a);
static V F_Chk_dP_dtup_dann(V a0);
static V L3215(V *a);
static V W_Chk_dP_dtup_dann(V *a);
static V F_Chk_dP_dtup_dmore(V a0, V a1);
static V L3216(V *a);
static V L3217(V *a);
static V S3218(void);
static V W_Chk_dP_dtup_dmore(V *a);
static V F_Chk_dBody_dreply__x(V a0);
static V W_Chk_dBody_dreply__x(V *a);
static V F_Chk_dBody_dis__reply(V a0);
static V W_Chk_dBody_dis__reply(V *a);
static V F_Chk_dP_dcol(void);
static V L3221(V *a);
static V W_Chk_dP_dcol(V *a);
static V F_Chk_dCur_dcol(V a0);
static V W_Chk_dCur_dcol(V *a);
static V F_Chk_dP_dbrace(V a0);
static V L3223(V *a);
static V L3224(V *a);
static V S3225(void);
static V L3226(V *a);
static V W_Chk_dP_dbrace(V *a);
static V F_Chk_dP_dbrace_dterm(V a0);
static V L3227(V *a);
static V L3228(V *a);
static V S3229(void);
static V L3230(V *a);
static V S3231(void);
static V L3232(V *a);
static V W_Chk_dP_dbrace_dterm(V *a);
static V F_Chk_dP_dbrace_dgo(V a0, V a1, V a2, V a3);
static V L3235(V *a);
static V S3236(void);
static V L3237(V *a);
static V L3238(V *a);
static V S3239(void);
static V L3240(V *a);
static V L3241(V *a);
static V L3242(V *a);
static V L3243(V *a);
static V S3244(void);
static V L3245(V *a);
static V L3246(V *a);
static V S3247(void);
static V L3248(V *a);
static V L3249(V *a);
static V S3250(void);
static V L3251(V *a);
static V S3252(void);
static V S3253(void);
static V S3254(void);
static V L3255(V *a);
static V L3256(V *a);
static V S3257(void);
static V L3258(V *a);
static V W_Chk_dP_dbrace_dgo(V *a);
static V F_Chk_dP_dbrace_drfl(void);
static V S3259(void);
static V L3260(V *a);
static V W_Chk_dP_dbrace_drfl(V *a);
static V F_Chk_dP_drwt(V a0);
static V L3261(V *a);
static V L3262(V *a);
static V L3263(V *a);
static V S3264(void);
static V L3265(V *a);
static V L3266(V *a);
static V W_Chk_dP_drwt(V *a);
static V F_Chk_dP_drwt_dgo(V a0, V a1, V a2);
static V S3269(void);
static V L3270(V *a);
static V L3271(V *a);
static V L3272(V *a);
static V S3273(void);
static V L3274(V *a);
static V L3275(V *a);
static V L3276(V *a);
static V L3277(V *a);
static V L3278(V *a);
static V S3279(void);
static V L3280(V *a);
static V L3281(V *a);
static V L3282(V *a);
static V S3283(void);
static V W_Chk_dP_drwt_dgo(V *a);
static V F_Chk_dP_dpush__scope(V a0);
static V L3284(V *a);
static V W_Chk_dP_dpush__scope(V *a);
static V F_Chk_dP_drwt_dname(V a0, V a1);
static V S3286(void);
static V S3287(void);
static V W_Chk_dP_drwt_dname(V *a);
static V F_Chk_dP_drwt_dnamed(V a0);
static V L3288(V *a);
static V W_Chk_dP_drwt_dnamed(V *a);
static V F_Chk_dP_darms(V a0);
static V L3289(V *a);
static V S3290(void);
static V L3291(V *a);
static V L3292(V *a);
static V L3293(V *a);
static V W_Chk_dP_darms(V *a);
static V F_Chk_dP_darms_dfin(V a0, V a1);
static V W_Chk_dP_darms_dfin(V *a);
static V F_Chk_darms_dbuild(V a0, V a1, V a2);
static V W_Chk_darms_dbuild(V *a);
static V F_Chk_dP_darms_dgo(V a0);
static V L3296(V *a);
static V S3297(void);
static V L3298(V *a);
static V W_Chk_dP_darms_dgo(V *a);
static V F_Chk_dP_darms_ditem(V a0);
static V L3299(V *a);
static V L3300(V *a);
static V L3301(V *a);
static V S3302(void);
static V L3303(V *a);
static V W_Chk_dP_darms_ditem(V *a);
static V F_Chk_dP_darms_dmore(V a0, V a1, V a2);
static V L3305(V *a);
static V L3306(V *a);
static V L3307(V *a);
static V S3308(void);
static V L3309(V *a);
static V L3310(V *a);
static V S3311(void);
static V L3312(V *a);
static V S3313(void);
static V L3314(V *a);
static V W_Chk_dP_darms_dmore(V *a);
static V F_Chk_dP_dplus(V a0);
static V L3315(V *a);
static V L3316(V *a);
static V L3317(V *a);
static V L3318(V *a);
static V L3319(V *a);
static V W_Chk_dP_dplus(V *a);
static V F_Chk_dTld_dadt__ng(V a0);
static V W_Chk_dTld_dadt__ng(V *a);
static V F_Chk_dP_dplus_dgo(V a0, V a1, V a2, V a3);
static V S3322(void);
static V W_Chk_dP_dplus_dgo(V *a);
static V F_Chk_dP_dplus_dadt(V a0, V a1, V a2, V a3);
static V S3326(void);
static V W_Chk_dP_dplus_dadt(V *a);
static V F_Chk_dP_dplus_dxs(V a0, V a1, V a2);
static V W_Chk_dP_dplus_dxs(V *a);
static V F_Chk_dplus_dargs(V a0, V a1);
static V W_Chk_dplus_dargs(V *a);
static V F_Chk_dTm_dis__adt(V a0);
static V W_Chk_dTm_dis__adt(V *a);
static V F_Chk_dP_dplus_dkey(V a0);
static V S3332(void);
static V W_Chk_dP_dplus_dkey(V *a);
static V F_Chk_dP_damp(V a0, V a1);
static V W_Chk_dP_damp(V *a);
static V F_Chk_damp_dcode(V a0);
static V W_Chk_damp_dcode(V *a);
static V F_Chk_dP_damp_dgo(V a0, V a1);
static V L3334(V *a);
static V L3335(V *a);
static V L3336(V *a);
static V W_Chk_dP_damp_dgo(V *a);
static V F_Chk_damp_dq(V a0);
static V W_Chk_damp_dq(V *a);
static V F_Chk_dP_dall(V a0);
static V L3338(V *a);
static V L3339(V *a);
static V L3340(V *a);
static V L3341(V *a);
static V S3342(void);
static V L3343(V *a);
static V L3344(V *a);
static V S3345(void);
static V L3346(V *a);
static V L3347(V *a);
static V L3348(V *a);
static V L3349(V *a);
static V L3350(V *a);
static V L3351(V *a);
static V W_Chk_dP_dall(V *a);
static V F_Chk_dall_dbuild(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S3353(void);
static V W_Chk_dall_dbuild(V *a);
static V F_Chk_dP_dquant(void);
static V L3354(V *a);
static V S3355(void);
static V L3356(V *a);
static V S3357(void);
static V L3358(V *a);
static V W_Chk_dP_dquant(V *a);
static V F_Chk_dP_dnum(void);
static V L3359(V *a);
static V L3360(V *a);
static V L3361(V *a);
static V L3362(V *a);
static V L3363(V *a);
static V L3364(V *a);
static V W_Chk_dP_dnum(V *a);
static V F_Chk_dnum_dkind(V a0);
static V W_Chk_dnum_dkind(V *a);
static V F_Chk_dP_dnum_dgo(V a0, V a1, V a2, V a3);
static V L3367(V *a);
static V L3368(V *a);
static V S3369(void);
static V S3370(void);
static V S3371(void);
static V L3372(V *a);
static V W_Chk_dP_dnum_dgo(V *a);
static V F_Chk_dP_dflt(V a0, V a1, V a2);
static V L3374(V *a);
static V L3375(V *a);
static V W_Chk_dP_dflt(V *a);
static V W_F32_dread(V *a);
static V F_Chk_dP_dflt_dgo(V a0, V a1, V a2);
static V S3377(void);
static V S3378(void);
static V S3379(void);
static V S3380(void);
static V S3381(void);
static V W_Chk_dP_dflt_dgo(V *a);
static V W_F32_dbits(V *a);
static V F_Chk_dF32_dis__finite(V a0);
static V W_Chk_dF32_dis__finite(V *a);
static V F_Chk_dP_dsteps(V a0);
static V L3383(V *a);
static V W_Chk_dP_dsteps(V *a);
static V F_Chk_dflt_dtext(V a0);
static V W_Chk_dflt_dtext(V *a);
static V F_Chk_dflt_dexp(V a0);
static V S3389(void);
static V W_Chk_dflt_dexp(V *a);
static V F_Chk_ddigits_dspan(V a0);
static V W_Chk_ddigits_dspan(V *a);
static V F_Chk_ddigits_dval(V a0, V a1, V a2);
static V W_Chk_ddigits_dval(V *a);
static V W_Nat_dmul(V *a);
static V F_Chk_dP_dnat(V a0, V a1, V a2);
static V S3393(void);
static V S3394(void);
static V W_Chk_dP_dnat(V *a);
static V F_Chk_dP_dnat_dgo(V a0, V a1);
static V S3395(void);
static V L3396(V *a);
static V W_Chk_dP_dnat_dgo(V *a);
static V F_Chk_dP_dnat_dlit(V a0, V a1);
static V L3397(V *a);
static V L3398(V *a);
static V S3399(void);
static V W_Chk_dP_dnat_dlit(V *a);
static V F_Chk_dP_dnat_dplus(V a0, V a1);
static V L3400(V *a);
static V L3401(V *a);
static V W_Chk_dP_dnat_dplus(V *a);
static V F_Chk_dnat_dplus(V a0, V a1, V a2);
static V W_Chk_dnat_dplus(V *a);
static V F_Chk_dnat_dplus_dbig(V a0, V a1, V a2);
static V S3403(void);
static V W_Chk_dnat_dplus_dbig(V *a);
static V F_Chk_dnat_dsuccs(V a0, V a1, V a2);
static V S3405(void);
static V W_Chk_dnat_dsuccs(V *a);
static V F_Chk_dP_dbase_dword(V a0, V a1);
static V S3406(void);
static V S3407(void);
static V S3408(void);
static V S3409(void);
static V S3410(void);
static V S3411(void);
static V S3412(void);
static V S3413(void);
static V W_Chk_dP_dbase_dword(V *a);
static V F_Chk_dP_dbase_dword_dgo(V a0, V a1, V a2);
static V L3415(V *a);
static V L3416(V *a);
static V L3417(V *a);
static V S3418(void);
static V L3419(V *a);
static V L3420(V *a);
static V S3421(void);
static V L3422(V *a);
static V L3423(V *a);
static V S3424(void);
static V S3425(void);
static V S3426(void);
static V S3427(void);
static V S3428(void);
static V W_Chk_dP_dbase_dword_dgo(V *a);
static V F_Chk_dP_dbase_dname(V a0, V a1);
static V S3429(void);
static V L3430(V *a);
static V W_Chk_dP_dbase_dname(V *a);
static V F_Chk_dP_dbase_dvar(V a0, V a1);
static V L3431(V *a);
static V W_Chk_dP_dbase_dvar(V *a);
static V F_Chk_dP_dvar(V a0, V a1);
static V L3432(V *a);
static V W_Chk_dP_dvar(V *a);
static V F_Chk_dP_dvar_dfound(V a0, V a1, V a2);
static V L3434(V *a);
static V W_Chk_dP_dvar_dfound(V *a);
static V F_Chk_dStr_dhas__dot(V a0);
static V W_Chk_dStr_dhas__dot(V *a);
static V F_Chk_dP_dvar_dfree(V a0, V a1, V a2, V a3);
static V L3437(V *a);
static V W_Chk_dP_dvar_dfree(V *a);
static V F_Chk_dP_dbase_dctor(V a0, V a1);
static V L3438(V *a);
static V S3439(void);
static V L3440(V *a);
static V L3441(V *a);
static V L3442(V *a);
static V W_Chk_dP_dbase_dctor(V *a);
static V F_Chk_dP_ddo(V a0);
static V L3443(V *a);
static V S3444(void);
static V L3445(V *a);
static V S3446(void);
static V L3447(V *a);
static V L3448(V *a);
static V L3449(V *a);
static V L3450(V *a);
static V S3451(void);
static V L3452(V *a);
static V L3453(V *a);
static V L3454(V *a);
static V W_Chk_dP_ddo(V *a);
static V F_Chk_dP_ddo__stmt(V a0, V a1, V a2);
static V L3455(V *a);
static V L3456(V *a);
static V S3457(void);
static V L3458(V *a);
static V W_Chk_dP_ddo__stmt(V *a);
static V F_Chk_dP_ddo__step(V a0, V a1, V a2, V a3);
static V L3459(V *a);
static V L3460(V *a);
static V S3461(void);
static V L3462(V *a);
static V L3463(V *a);
static V S3464(void);
static V L3465(V *a);
static V L3466(V *a);
static V S3467(void);
static V L3468(V *a);
static V S3469(void);
static V L3470(V *a);
static V W_Chk_dP_ddo__step(V *a);
static V F_Chk_dP_ddo__step_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V S3472(void);
static V L3473(V *a);
static V W_Chk_dP_ddo__step_dgo(V *a);
static V F_Chk_dP_ddo__arrow(V a0, V a1, V a2, V a3, V a4, V a5);
static V S3474(void);
static V L3475(V *a);
static V W_Chk_dP_ddo__arrow(V *a);
static V F_Chk_dP_ddo__last(V a0, V a1, V a2);
static V L3476(V *a);
static V L3477(V *a);
static V S3478(void);
static V L3479(V *a);
static V W_Chk_dP_ddo__last(V *a);
static V F_Chk_dP_ddocall(V a0, V a1, V a2, V a3, V a4, V a5);
static V L3480(V *a);
static V W_Chk_dP_ddocall(V *a);
static V F_Chk_ddo_dcall(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V W_Chk_ddo_dcall(V *a);
static V F_Chk_dList_dlast__tm(V a0);
static V W_Chk_dList_dlast__tm(V *a);
static V F_Chk_dList_dinit__tm(V a0);
static V W_Chk_dList_dinit__tm(V *a);
static V F_Chk_dP_ddo__bind(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V L3483(V *a);
static V L3484(V *a);
static V S3485(void);
static V L3486(V *a);
static V L3487(V *a);
static V L3488(V *a);
static V S3489(void);
static V L3490(V *a);
static V L3491(V *a);
static V L3492(V *a);
static V S3493(void);
static V W_Chk_dP_ddo__bind(V *a);
static V F_Chk_ddo_dlam(V a0, V a1, V a2);
static V W_Chk_ddo_dlam(V *a);
static V F_Chk_ddo_dlet(V a0, V a1, V a2, V a3);
static V W_Chk_ddo_dlet(V *a);
static V F_Chk_dP_dmore(V a0);
static V S3494(void);
static V L3495(V *a);
static V L3496(V *a);
static V L3497(V *a);
static V W_Chk_dP_dmore(V *a);
static V F_Chk_dP_ddo__ret(V a0, V a1, V a2);
static V L3498(V *a);
static V L3499(V *a);
static V S3500(void);
static V W_Chk_dP_ddo__ret(V *a);
static V F_Chk_dP_dword(V a0);
static V L3501(V *a);
static V W_Chk_dP_dword(V *a);
static V F_Chk_dP_dword_dif(V a0, V a1);
static V W_Chk_dP_dword_dif(V *a);
static V F_Chk_dP_dat__word(V a0);
static V L3503(V *a);
static V L3504(V *a);
static V W_Chk_dP_dat__word(V *a);
static V F_Chk_dP_dbody_dlet_deq(V a0, V a1);
static V S3505(void);
static V L3506(V *a);
static V W_Chk_dP_dbody_dlet_deq(V *a);
static V F_Chk_dP_dbody_dlet_dann(V a0, V a1);
static V L3508(V *a);
static V L3509(V *a);
static V W_Chk_dP_dbody_dlet_dann(V *a);
static V F_Chk_dP_dbody_dreply(V a0, V a1, V a2, V a3);
static V W_Chk_dP_dbody_dreply(V *a);
static V F_Chk_dterm__write(V a0);
static V W_Chk_dterm__write(V *a);
static V F_Chk_dterm__write_dgo(V a0);
static V W_Chk_dterm__write_dgo(V *a);
static V F_Chk_dP_dbody_dreply_dgo(V a0, V a1, V a2, V a3, V a4);
static V L3514(V *a);
static V L3515(V *a);
static V L3516(V *a);
static V W_Chk_dP_dbody_dreply_dgo(V *a);
static V F_Maybe_dis__none(V a2);
static V W_Maybe_dis__none(V *a);
static V F_Chk_dP_dbody_dty__ok(V a0, V a1, V a2);
static V L3519(V *a);
static V W_Chk_dP_dbody_dty__ok(V *a);
static V F_Chk_dP_dbody_dty(void);
static V L3520(V *a);
static V W_Chk_dP_dbody_dty(V *a);
static V F_Chk_dP_dlocal_dnames(V a0, V a1);
static V L3521(V *a);
static V L3522(V *a);
static V L3523(V *a);
static V L3524(V *a);
static V W_Chk_dP_dlocal_dnames(V *a);
static V F_Chk_dP_dlocal_dnames_dmore(V a0, V a1);
static V L3525(V *a);
static V L3526(V *a);
static V W_Chk_dP_dlocal_dnames_dmore(V *a);
static V F_Chk_dStr_dword__at(V a0);
static V S3528(void);
static V W_Chk_dStr_dword__at(V *a);
static V F_Chk_dStr_dword__at_dif(V a0, V a1, V a2);
static V S3530(void);
static V W_Chk_dStr_dword__at_dif(V *a);
static V F_Chk_dP_dbody_derased__name(V a0);
static V L3531(V *a);
static V L3532(V *a);
static V W_Chk_dP_dbody_derased__name(V *a);
static V F_Chk_dP_dbody_dmatch(V a0, V a1);
static V L3533(V *a);
static V L3534(V *a);
static V L3535(V *a);
static V L3536(V *a);
static V L3537(V *a);
static V W_Chk_dP_dbody_dmatch(V *a);
static V F_Chk_dP_drows(V a0, V a1, V a2);
static V S3538(void);
static V L3539(V *a);
static V L3540(V *a);
static V W_Chk_dP_drows(V *a);
static V F_Chk_dP_drow(V a0, V a1, V a2, V a3);
static V S3541(void);
static V L3542(V *a);
static V L3543(V *a);
static V S3544(void);
static V L3545(V *a);
static V L3546(V *a);
static V L3547(V *a);
static V L3548(V *a);
static V L3549(V *a);
static V L3550(V *a);
static V W_Chk_dP_drow(V *a);
static V F_Chk_dP_dterms(void);
static V L3551(V *a);
static V L3552(V *a);
static V S3553(void);
static V L3554(V *a);
static V W_Chk_dP_dterms(V *a);
static V F_Chk_dP_dterms_dmore(V a0);
static V S3555(void);
static V L3556(V *a);
static V L3557(V *a);
static V W_Chk_dP_dterms_dmore(V *a);
static V F_Chk_dP_dclauses(V a0, V a1);
static V S3558(void);
static V L3559(V *a);
static V S3560(void);
static V L3561(V *a);
static V W_Chk_dP_dclauses(V *a);
static V F_Chk_dP_dclause(V a0, V a1, V a2);
static V S3562(void);
static V S3563(void);
static V L3564(V *a);
static V L3565(V *a);
static V S3566(void);
static V L3567(V *a);
static V S3568(void);
static V L3569(V *a);
static V S3570(void);
static V L3571(V *a);
static V L3572(V *a);
static V L3573(V *a);
static V L3574(V *a);
static V L3575(V *a);
static V S3576(void);
static V L3577(V *a);
static V L3578(V *a);
static V S3579(void);
static V L3580(V *a);
static V L3581(V *a);
static V L3582(V *a);
static V W_Chk_dP_dclause(V *a);
static V F_Chk_dP_dclause_dwhere(V a0, V a1, V a2);
static V L3583(V *a);
static V S3584(void);
static V L3585(V *a);
static V L3586(V *a);
static V L3587(V *a);
static V L3588(V *a);
static V L3589(V *a);
static V L3590(V *a);
static V S3591(void);
static V W_Chk_dP_dclause_dwhere(V *a);
static V F_Chk_dP_dfresh(V a0);
static V L3592(V *a);
static V S3593(void);
static V S3594(void);
static V W_Chk_dP_dfresh(V *a);
static V F_Chk_dP_dqual(V a0);
static V L3595(V *a);
static V W_Chk_dP_dqual(V *a);
static V F_Chk_dP_dtype(void);
static V S3596(void);
static V L3597(V *a);
static V L3598(V *a);
static V L3599(V *a);
static V L3600(V *a);
static V L3601(V *a);
static V L3602(V *a);
static V S3603(void);
static V L3604(V *a);
static V S3605(void);
static V L3606(V *a);
static V W_Chk_dP_dtype(V *a);
static V F_Chk_dP_dtype_dgo(V a0, V a1, V a2);
static V S3607(void);
static V L3608(V *a);
static V S3609(void);
static V L3610(V *a);
static V L3611(V *a);
static V S3612(void);
static V L3613(V *a);
static V L3614(V *a);
static V L3615(V *a);
static V L3616(V *a);
static V L3617(V *a);
static V L3618(V *a);
static V L3619(V *a);
static V L3620(V *a);
static V L3621(V *a);
static V W_Chk_dP_dtype_dgo(V *a);
static V F_Chk_dP_dctors(V a0, V a1, V a2);
static V L3622(V *a);
static V L3623(V *a);
static V S3624(void);
static V L3625(V *a);
static V S3626(void);
static V L3627(V *a);
static V S3628(void);
static V L3629(V *a);
static V W_Chk_dP_dctors(V *a);
static V F_Chk_dP_dctor(V a0, V a1, V a2);
static V L3630(V *a);
static V L3631(V *a);
static V L3632(V *a);
static V S3633(void);
static V S3634(void);
static V L3635(V *a);
static V S3636(void);
static V L3637(V *a);
static V L3638(V *a);
static V S3639(void);
static V L3640(V *a);
static V L3641(V *a);
static V L3642(V *a);
static V L3643(V *a);
static V L3644(V *a);
static V L3645(V *a);
static V W_Chk_dP_dctor(V *a);
static V F_Chk_dTC_dparams(V a0);
static V W_Chk_dTC_dparams(V *a);
static V F_Chk_dtele__bind(V a0, V a1);
static V W_Chk_dtele__bind(V *a);
static V F_Chk_dP_dtele(V a0, V a1, V a2);
static V L3648(V *a);
static V L3649(V *a);
static V W_Chk_dP_dtele(V *a);
static V F_Chk_dP_dtele_done(V a0, V a1, V a2);
static V S3651(void);
static V S3653(void);
static V L3654(V *a);
static V S3655(void);
static V L3656(V *a);
static V S3657(void);
static V L3658(V *a);
static V L3659(V *a);
static V L3660(V *a);
static V L3661(V *a);
static V S3662(void);
static V S3663(void);
static V L3664(V *a);
static V L3665(V *a);
static V L3666(V *a);
static V S3667(void);
static V L3668(V *a);
static V L3669(V *a);
static V S3670(void);
static V L3671(V *a);
static V L3672(V *a);
static V L3673(V *a);
static V L3674(V *a);
static V S3675(void);
static V L3676(V *a);
static V W_Chk_dP_dtele_done(V *a);
static V F_Chk_dTC_dnames(V a0);
static V W_Chk_dTC_dnames(V *a);
static V F_Chk_dTC_dk(V a0);
static V W_Chk_dTC_dk(V *a);
static V F_Chk_dTC_dfirst__typed(V a0);
static V W_Chk_dTC_dfirst__typed(V *a);
static V F_Chk_dP_ddef(V a0);
static V S3680(void);
static V L3681(V *a);
static V L3682(V *a);
static V L3683(V *a);
static V L3684(V *a);
static V L3685(V *a);
static V L3686(V *a);
static V L3687(V *a);
static V L3688(V *a);
static V S3689(void);
static V L3690(V *a);
static V L3691(V *a);
static V S3692(void);
static V L3693(V *a);
static V S3694(void);
static V L3695(V *a);
static V S3696(void);
static V L3697(V *a);
static V L3698(V *a);
static V W_Chk_dP_ddef(V *a);
static V F_Chk_dP_ddef_dgo(V a0, V a1, V a2, V a3, V a4);
static V W_Chk_dP_ddef_dgo(V *a);
static V F_Chk_dP_ddef_dnew(V a0, V a1, V a2, V a3, V a4);
static V S3701(void);
static V L3702(V *a);
static V S3703(void);
static V S3704(void);
static V L3705(V *a);
static V L3706(V *a);
static V L3707(V *a);
static V L3708(V *a);
static V W_Chk_dP_ddef_dnew(V *a);
static V F_Chk_dP_ddef_dbody(V a0, V a1, V a2);
static V S3709(void);
static V L3710(V *a);
static V S3711(void);
static V L3712(V *a);
static V L3713(V *a);
static V L3714(V *a);
static V L3715(V *a);
static V W_Chk_dP_ddef_dbody(V *a);
static V F_Chk_dP_ddef_dvalue(V a0, V a1);
static V L3716(V *a);
static V L3717(V *a);
static V L3718(V *a);
static V L3719(V *a);
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
static V S3726(void);
static V S3727(void);
static V S3728(void);
static V S3729(void);
static V S3730(void);
static V S3731(void);
static V W_Chk_dops_derr(V *a);
static V F_Chk_dops_dtext(V a0, V a1);
static V W_Chk_dops_dtext(V *a);
static V F_Chk_dTC_dvars(V a0);
static V W_Chk_dTC_dvars(V *a);
static V F_Chk_dP_ddef_dforeign(V a0);
static V L3734(V *a);
static V S3735(void);
static V L3736(V *a);
static V L3737(V *a);
static V L3738(V *a);
static V W_Chk_dP_ddef_dforeign(V *a);
static V F_Chk_dTld_dwith__imps(V a0, V a1);
static V W_Chk_dTld_dwith__imps(V *a);
static V F_Chk_dP_dimports(V a0);
static V S3740(void);
static V L3741(V *a);
static V W_Chk_dP_dimports(V *a);
static V F_Chk_dP_dimport1(V a0);
static V S3742(void);
static V L3743(V *a);
static V S3744(void);
static V L3745(V *a);
static V S3746(void);
static V L3747(V *a);
static V S3748(void);
static V S3749(void);
static V S3750(void);
static V L3751(V *a);
static V L3752(V *a);
static V W_Chk_dP_dimport1(V *a);
static V F_Chk_dP_ddir(void);
static V L3753(V *a);
static V W_Chk_dP_ddir(V *a);
static V F_Chk_dPS_ddir(V a0);
static V W_Chk_dPS_ddir(V *a);
static V F_Chk_dP_duntil__quote(V a0);
static V L3755(V *a);
static V W_Chk_dP_duntil__quote(V *a);
static V F_Chk_dP_duntil__quote_dmore(V a0, V a1);
static V L3756(V *a);
static V W_Chk_dP_duntil__quote_dmore(V *a);
static V F_Chk_dTld_dlaw__x(V a0);
static V W_Chk_dTld_dlaw__x(V *a);
static V F_Chk_dP_ddef_dfill(V a0, V a1, V a2, V a3);
static V L3758(V *a);
static V L3759(V *a);
static V S3760(void);
static V L3761(V *a);
static V S3762(void);
static V S3763(void);
static V L3764(V *a);
static V L3765(V *a);
static V L3766(V *a);
static V W_Chk_dP_ddef_dfill(V *a);
static V F_Chk_dTld_dlaw__fill(V a0, V a1, V a2);
static V W_Chk_dTld_dlaw__fill(V *a);
static V F_Chk_dTC_dall__qnt(V a0);
static V W_Chk_dTC_dall__qnt(V *a);
static V F_Chk_dTld_dopen__law(V a0);
static V W_Chk_dTld_dopen__law(V *a);
static V F_Chk_dP_dunsafe(void);
static V S3770(void);
static V L3771(V *a);
static V S3772(void);
static V L3773(V *a);
static V L3774(V *a);
static V S3775(void);
static V L3776(V *a);
static V S3777(void);
static V W_Chk_dP_dunsafe(V *a);
static V F_Chk_dP_dreset__scope(void);
static V L3778(V *a);
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
static V S3785(void);
static V W_Main_dchk_dloading(V *a);
static V F_Main_dchk_dimps(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L3787(V *a);
static V W_Main_dchk_dimps(V *a);
static V F_Main_dchk_dimps_dnext(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Main_dchk_dimps_dnext(V *a);
static V F_Main_dchk_dimp(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V W_Main_dchk_dimp(V *a);
static V F_Main_dchk_dimp_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10);
static V S3793(void);
static V L3794(V *a);
static V S3795(void);
static V W_Main_dchk_dimp_dgo(V *a);
static V F_Main_dchk_dimp_drel(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10);
static V S3797(void);
static V S3798(void);
static V S3799(void);
static V S3801(void);
static V L3805(V *a);
static V L3806(V *a);
static V W_Main_dchk_dimp_drel(V *a);
static V F_Main_dchk_dhub(V a0);
static V L3807(V *a);
static V S3808(void);
static V L3809(V *a);
static V L3810(V *a);
static V S3811(void);
static V W_Main_dchk_dhub(V *a);
static V F_Path_ddirname(V a0);
static V S3813(void);
static V S3814(void);
static V S3815(void);
static V W_Path_ddirname(V *a);
static V F_Path_djoin(V a0, V a1);
static V S3816(void);
static V W_Path_djoin(V *a);
static V F_Main_dchk_dis__hub(V a0);
static V S3817(void);
static V W_Main_dchk_dis__hub(V *a);
static V F_Main_dchk_dis__hub_dhex(V a0);
static V W_Main_dchk_dis__hub_dhex(V *a);
static V F_Main_dread__opt(V a0);
static V S3819(void);
static V L3820(V *a);
static V W_Main_dread__opt(V *a);
static V F_Main_dread__opt_dopen(V a0);
static V L3822(V *a);
static V W_Main_dread__opt_dopen(V *a);
static V F_Main_dread__opt_dfin(V a0);
static V L3824(V *a);
static V W_Main_dread__opt_dfin(V *a);
static V F_Main_dread__opt_dres(V a0);
static V W_Main_dread__opt_dres(V *a);
static V F_CS_dat__end(V a0);
static V W_CS_dat__end(V *a);
static V F_Main_dcheck__only_dfin(V a0);
static V S3829(void);
static V W_Main_dcheck__only_dfin(V *a);
static V F_Main_dast(V a0);
static V S3831(void);
static V W_Main_dast(V *a);
static V F_Decls_dshow(V a0);
static V W_Decls_dshow(V *a);
static V F_Decls_dshow_dgo(V a0);
static V S3833(void);
static V S3834(void);
static V W_Decls_dshow_dgo(V *a);
static V F_Decl_dshow(V a0);
static V S3836(void);
static V S3837(void);
static V S3838(void);
static V S3839(void);
static V S3840(void);
static V S3841(void);
static V S3842(void);
static V S3843(void);
static V S3844(void);
static V S3845(void);
static V S3846(void);
static V S3847(void);
static V S3848(void);
static V W_Decl_dshow(V *a);
static V F_Ctors_dshow(V a0);
static V S3850(void);
static V S3851(void);
static V W_Ctors_dshow(V *a);
static V F_Ctor_dshow(V a0);
static V S3853(void);
static V S3854(void);
static V W_Ctor_dshow(V *a);
static V F_Fields_dshow(V a0);
static V S3856(void);
static V S3857(void);
static V S3858(void);
static V W_Fields_dshow(V *a);
static V F_Params_dshow(V a0);
static V S3860(void);
static V S3861(void);
static V W_Params_dshow(V *a);
static V F_Param_dshow(V a0);
static V S3863(void);
static V W_Param_dshow(V *a);
static V F_Toks_dshow(V a0);
static V S3865(void);
static V W_Toks_dshow(V *a);
static V F_Tok_dshow(V a0);
static V S3867(void);
static V S3868(void);
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
return F_Chk_denv__get_dif(FLD(FLD(s81, 0), 1), FLD(s81, 1), a1, F_U32_dis__eq(a1, FLD(FLD(s81, 0), 0)));
} else if (TAG(s81) == 1) {
{ V t0 = FLD(s81, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_denv__get(V *a) { (void)a; return F_Chk_denv__get(a[0], a[1]); }
static V W_U32_dis__eq(V *a) { (void)a; return F_U32_dis__eq(a[0], a[1]); }
static V F_Chk_denv__get_dif(V a0, V a1, V a2, V a3) {
top:;
V s82 = a3;
if ((s82) == IMM(1)) {
return C1(1, a0);
} else if ((s82) == IMM(0)) {
return F_Chk_denv__get(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_denv__get_dif(V *a) { (void)a; return F_Chk_denv__get_dif(a[0], a[1], a[2], a[3]); }
static V F_Chk_dhigher_dvar(V a0, V a1, V a2, V a3) {
top:;
V s83 = a1;
if ((s83) == IMM(0)) {
return a2;
} else if (TAG(s83) == 1) {
return F_Chk_dhigher_dval(a0, FLD(s83, 0), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dhigher_dvar(V *a) { (void)a; return F_Chk_dhigher_dvar(a[0], a[1], a[2], a[3]); }
static V F_Chk_dhigher_dval(V a0, V a1, V a2) {
top:;
V s84 = a1;
if (TAG(s84) == 32) {
return F_Chk_dhigher(a0, F_Chk_dpatt__term(FLD(s84, 0), a2), FLD(s84, 1));
} else if (TAG(s84) == 1) {
return C3(1, FLD(s84, 0), FLD(s84, 1), FLD(s84, 2));
} else {
return F_Chk_dTm_drespan(s84, a2);
}
}
static V W_Chk_dhigher_dval(V *a) { (void)a; return F_Chk_dhigher_dval(a[0], a[1], a[2]); }
static V F_Chk_dTm_drespan(V a0, V a1) {
top:;
V s85 = a0;
if (TAG(s85) == 0 && (FLD(s85, 2)) == IMM(0)) {
return C3(0, FLD(s85, 0), FLD(s85, 1), a1);
} else if (TAG(s85) == 4 && (FLD(s85, 1)) == IMM(0)) {
return C3(4, FLD(s85, 0), a1, FLD(s85, 2));
} else if (TAG(s85) == 7 && (FLD(s85, 1)) == IMM(0)) {
return C2(7, FLD(s85, 0), a1);
} else if (TAG(s85) == 8 && (FLD(s85, 0)) == IMM(0)) {
return C1(8, a1);
} else if (TAG(s85) == 9 && (FLD(s85, 1)) == IMM(0)) {
return C2(9, FLD(s85, 0), a1);
} else if (TAG(s85) == 13 && (FLD(s85, 2)) == IMM(0)) {
return C3(13, FLD(s85, 0), FLD(s85, 1), a1);
} else if (TAG(s85) == 14 && (FLD(s85, 2)) == IMM(0)) {
return C4(14, FLD(s85, 0), FLD(s85, 1), a1, FLD(s85, 3));
} else if (TAG(s85) == 15 && (FLD(s85, 2)) == IMM(0)) {
return C3(15, FLD(s85, 0), FLD(s85, 1), a1);
} else if (TAG(s85) == 16 && (FLD(s85, 1)) == IMM(0)) {
return C2(16, FLD(s85, 0), a1);
} else if (TAG(s85) == 20 && (FLD(s85, 0)) == IMM(0)) {
return C1(20, a1);
} else if (TAG(s85) == 22 && (FLD(s85, 1)) == IMM(0)) {
return C2(22, FLD(s85, 0), a1);
} else {
return s85;
}
}
static V W_Chk_dTm_drespan(V *a) { (void)a; return F_Chk_dTm_drespan(a[0], a[1]); }
static V F_Chk_dpatt__term(V a0, V a1) {
top:;
V s86 = a0;
if (TAG(s86) == 0) {
return C3(0, FLD(s86, 0), FLD(s86, 1), F_Chk_dSp_dor(a1, FLD(s86, 3)));
} else if (TAG(s86) == 1) {
return C3(15, FLD(s86, 0), F_Chk_dpatt__terms(FLD(s86, 1), a1), F_Chk_dSp_dor(a1, FLD(s86, 2)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dpatt__term(V *a) { (void)a; return F_Chk_dpatt__term(a[0], a[1]); }
static V F_Chk_dSp_dor(V a0, V a1) {
top:;
V s87 = a0;
if ((s87) == IMM(0)) {
return a1;
} else {
return s87;
}
}
static V W_Chk_dSp_dor(V *a) { (void)a; return F_Chk_dSp_dor(a[0], a[1]); }
static V F_Chk_dpatt__terms(V a0, V a1) {
top:;
V s88 = a0;
if ((s88) == IMM(0)) {
return IMM(0);
} else if (TAG(s88) == 1) {
return C2(1, F_Chk_dpatt__term(FLD(s88, 0), a1), F_Chk_dpatt__terms(FLD(s88, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dpatt__terms(V *a) { (void)a; return F_Chk_dpatt__terms(a[0], a[1]); }
static V F_Chk_dwnf_dwalk(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9) {
top:;
V s89 = a4;
if (TAG(s89) == 23) {
{ V t0 = a0; V t1 = a1; V t2 = a2; V t3 = a3; V t4 = FLD(s89, 0); V t5 = a5; V t6 = a6; V t7 = a7; V t8 = a8; V t9 = a9; a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; a5 = t5; a6 = t6; a7 = t7; a8 = t8; a9 = t9; goto top; }
} else if (TAG(s89) == 17) {
return F_Chk_dwnf_dwalk_dmat(a0, a1, a2, a3, C4(17, FLD(s89, 0), FLD(s89, 1), FLD(s89, 2), FLD(s89, 3)), FLD(s89, 1), FLD(s89, 2), a5, a6, a7, a8, a9, F_String_deq(a1, FLD(s89, 0)));
} else if (TAG(s89) == 18) {
return F_Chk_dwnf_dback(a0, F_Chk_dterm__apply(a0, F_Chk_dlhs__or(a7, a5), a6, a8), a9);
} else {
return F_Chk_dwnf_dgo(a0, s89, C2(1, C2(0, a3, IMM(0)), a9), a7);
}
}
static V W_Chk_dwnf_dwalk(V *a) { (void)a; return F_Chk_dwnf_dwalk(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]); }
static V F_Chk_dwnf_dwalk_dmat(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11, V a12) {
top:;
V s90 = a12;
if ((s90) == IMM(1)) {
return F_Chk_dwnf_dgo(a0, a5, F_Chk_dapp__frames(a2, a11), F_Chk_dlhs__mat(a0, a9, a1, F_List_dlength(a2)));
} else if ((s90) == IMM(0)) {
return F_Chk_dwnf_dwalk(a0, a1, a2, a3, a6, a7, a8, a9, a10, a11);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dwnf_dwalk_dmat(V *a) { (void)a; return F_Chk_dwnf_dwalk_dmat(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12]); }
static V F_List_dlength(V a2) {
top:;
V s91 = a2;
if ((s91) == IMM(0)) {
return 0u;
} else if (TAG(s91) == 1) {
return nat_addk(F_List_dlength(FLD(s91, 1)), 1);
} else { bend_fail("incomplete match"); }
}
static V W_List_dlength(V *a) { (void)a; return F_List_dlength(a[2]); }
static V F_Chk_dlhs__mat(V a0, V a1, V a2, V a3) {
top:;
V s92 = a1;
if ((s92) == IMM(0)) {
return IMM(0);
} else if (TAG(s92) == 1) {
return C2(1, F_Chk_dlhs__ext(a0, FLD(s92, 0), a2, a3, IMM(0)), F_Nat_dadd(F_Nat_dsub(FLD(s92, 1), 1u), a3));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlhs__mat(V *a) { (void)a; return F_Chk_dlhs__mat(a[0], a[1], a[2], a[3]); }
static V W_Nat_dadd(V *a) { (void)a; return F_Nat_dadd(a[0], a[1]); }
static V S94(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dapp__frames(V a0, V a1) {
top:;
V s93 = a0;
if ((s93) == IMM(0)) {
return a1;
} else if (TAG(s93) == 1) {
return C2(1, C2(0, F_Chk_dterm__cell(FLD(s93, 0), S94()), IMM(0)), F_Chk_dapp__frames(FLD(s93, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dapp__frames(V *a) { (void)a; return F_Chk_dapp__frames(a[0], a[1]); }
static V F_Chk_dterm__cell(V a0, V a1) {
top:;
V s95 = a0;
if (TAG(s95) == 1) {
return C3(1, FLD(s95, 0), FLD(s95, 1), FLD(s95, 2));
} else {
return C3(1, a1, F_Chk_dTm_dspan(s95), s95);
}
}
static V W_Chk_dterm__cell(V *a) { (void)a; return F_Chk_dterm__cell(a[0], a[1]); }
static V F_Chk_dTm_dspan(V a0) {
top:;
V s96 = a0;
if (TAG(s96) == 0) {
return FLD(s96, 2);
} else if (TAG(s96) == 1) {
return FLD(s96, 1);
} else if (TAG(s96) == 2) {
return FLD(s96, 1);
} else if (TAG(s96) == 3) {
return FLD(s96, 2);
} else if (TAG(s96) == 4) {
return FLD(s96, 1);
} else if (TAG(s96) == 5) {
return FLD(s96, 3);
} else if (TAG(s96) == 6) {
return FLD(s96, 4);
} else if (TAG(s96) == 7) {
return FLD(s96, 1);
} else if (TAG(s96) == 8) {
return FLD(s96, 0);
} else if (TAG(s96) == 9) {
return FLD(s96, 1);
} else if (TAG(s96) == 10) {
return FLD(s96, 2);
} else if (TAG(s96) == 11) {
return FLD(s96, 5);
} else if (TAG(s96) == 12) {
return FLD(s96, 3);
} else if (TAG(s96) == 13) {
return FLD(s96, 2);
} else if (TAG(s96) == 14) {
return FLD(s96, 2);
} else if (TAG(s96) == 15) {
return FLD(s96, 2);
} else if (TAG(s96) == 16) {
return FLD(s96, 1);
} else if (TAG(s96) == 17) {
return FLD(s96, 3);
} else if (TAG(s96) == 18) {
return FLD(s96, 0);
} else if (TAG(s96) == 19) {
return FLD(s96, 3);
} else if (TAG(s96) == 20) {
return FLD(s96, 0);
} else if (TAG(s96) == 21) {
return FLD(s96, 3);
} else if (TAG(s96) == 22) {
return FLD(s96, 1);
} else if (TAG(s96) == 23) {
return FLD(s96, 2);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dspan(V *a) { (void)a; return F_Chk_dTm_dspan(a[0]); }
static V F_Chk_dwnf_dmnb(V a0, V a1, V a2) {
top:;
V s97 = a0;
if (TAG(s97) == 9 && (FLD(s97, 0)) == IMM(2)) {
return a1;
} else if (TAG(s97) == 9 && (FLD(s97, 0)) == IMM(1)) {
return F_Bool_dpick(F_Chk_dTm_dis__qua(a1), C2(9, IMM(1), FLD(s97, 1)), C3(10, a1, C2(9, IMM(1), FLD(s97, 1)), a2));
} else if (TAG(s97) == 9) {
return C2(9, FLD(s97, 0), FLD(s97, 1));
} else {
return C3(10, a1, s97, a2);
}
}
static V W_Chk_dwnf_dmnb(V *a) { (void)a; return F_Chk_dwnf_dmnb(a[0], a[1], a[2]); }
static V F_Chk_dTm_dis__qua(V a0) {
top:;
V s98 = a0;
if (TAG(s98) == 9) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__qua(V *a) { (void)a; return F_Chk_dTm_dis__qua(a[0]); }
static V F_Chk_dwnf_dmna(V a0, V a1, V a2, V a3, V a4) {
top:;
V s99 = a1;
if (TAG(s99) == 9 && (FLD(s99, 0)) == IMM(2)) {
return F_Chk_dwnf_dgo(a0, a2, a4, IMM(0));
} else if (TAG(s99) == 9 && (FLD(s99, 0)) == IMM(0)) {
return F_Chk_dwnf_dback(a0, C2(9, IMM(0), FLD(s99, 1)), a4);
} else {
return F_Chk_dwnf_dgo(a0, a2, C2(1, C2(3, s99, a3), a4), IMM(0));
}
}
static V W_Chk_dwnf_dmna(V *a) { (void)a; return F_Chk_dwnf_dmna(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dwnf_dref(V a0, V a1, V a2, V a3, V a4) {
top:;
V s100 = a1;
if (TAG(s100) == 1 && TAG(FLD(s100, 0)) == 1 && (FLD(FLD(s100, 0), 0)) == 0) {
return F_Chk_dwnf_dback(a0, C4(14, F_Chk_dTm_dref__k(a2), IMM(0), F_Chk_dTm_dspan(a2), IMM(0)), a3);
} else if (TAG(s100) == 1 && TAG(FLD(s100, 0)) == 0 && TAG(FLD(FLD(s100, 0), 3)) == 1) {
return F_Chk_dwnf_dref_ddef(a0, a2, FLD(FLD(FLD(s100, 0), 3), 0), FLD(FLD(s100, 0), 0), a3, F_Nat_dis__lt(F_Chk_dfrs__apps(a3, FLD(FLD(s100, 0), 0)), FLD(FLD(s100, 0), 0)));
} else {
return F_Chk_dwnf_dback(a0, a2, a3);
}
}
static V W_Chk_dwnf_dref(V *a) { (void)a; return F_Chk_dwnf_dref(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dfrs__apps(V a0, V a1) {
top:;
V s101 = a0;
V s102 = a1;
if ((s102) == 0) {
return 0u;
} else if (TAG(s101) == 1 && TAG(FLD(s101, 0)) == 0 && nat_ge(s102, 1)) {
return nat_addk(F_Chk_dfrs__apps(FLD(s101, 1), nat_subk(s102, 1)), 1);
} else {
return 0u;
}
}
static V W_Chk_dfrs__apps(V *a) { (void)a; return F_Chk_dfrs__apps(a[0], a[1]); }
static V W_Nat_dis__lt(V *a) { (void)a; return F_Nat_dis__lt(a[0], a[1]); }
static V F_Chk_dwnf_dref_ddef(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s103 = a5;
if ((s103) == IMM(1)) {
return F_Chk_dwnf_dback(a0, a1, a4);
} else if ((s103) == IMM(0)) {
return F_Chk_dwnf_dgo(a0, a2, a4, C2(1, a1, a3));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dwnf_dref_ddef(V *a) { (void)a; return F_Chk_dwnf_dref_ddef(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S105(void) { static V c; return STRC(c, ""); }
static V F_Chk_dTm_dref__k(V a0) {
top:;
V s104 = a0;
if (TAG(s104) == 4) {
return FLD(s104, 0);
} else {
return S105();
}
}
static V W_Chk_dTm_dref__k(V *a) { (void)a; return F_Chk_dTm_dref__k(a[0]); }
static V F_Chk_dwnf_drwt(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s106 = a1;
if (TAG(s106) == 20) {
return F_Chk_dwnf_dgo(a0, a3, a4, a5);
} else {
return F_Chk_dwnf_dback(a0, a2, a4);
}
}
static V W_Chk_dwnf_drwt(V *a) { (void)a; return F_Chk_dwnf_drwt(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dwnf_defq(V a0, V a1, V a2, V a3) {
top:;
V s107 = a2;
V s108 = a3;
if (TAG(s107) == 1 && TAG(FLD(s107, 0)) == 0 && TAG(s108) == 1 && nat_ge(FLD(s108, 1), 1)) {
return F_Chk_dwnf_dback(a0, FLD(s108, 0), C2(1, C2(0, FLD(FLD(s107, 0), 0), FLD(FLD(s107, 0), 1)), FLD(s107, 1)));
} else {
return F_Chk_dwnf_dback(a0, a1, s107);
}
}
static V W_Chk_dwnf_defq(V *a) { (void)a; return F_Chk_dwnf_defq(a[0], a[1], a[2], a[3]); }
static V F_Chk_dwnf_dmat(V a0, V a1, V a2, V a3) {
top:;
V s109 = a2;
if (TAG(s109) == 1 && TAG(FLD(s109, 0)) == 0) {
return F_Chk_dwnf_dgo(a0, FLD(FLD(s109, 0), 0), C2(1, C4(1, a1, FLD(FLD(s109, 0), 0), a3, FLD(FLD(s109, 0), 1)), FLD(s109, 1)), IMM(0));
} else {
return F_Chk_dwnf_dback(a0, a1, s109);
}
}
static V W_Chk_dwnf_dmat(V *a) { (void)a; return F_Chk_dwnf_dmat(a[0], a[1], a[2], a[3]); }
static V F_Chk_dwnf_dlam(V a0, V a1, V a2, V a3) {
top:;
V s110 = a2;
if (TAG(s110) == 1 && TAG(FLD(s110, 0)) == 0) {
return F_Chk_dwnf_dgo(a0, F_Chk_dterm__apply(a0, a1, FLD(FLD(s110, 0), 0), FLD(FLD(s110, 0), 1)), FLD(s110, 1), F_Chk_dlhs__step(a0, a3, FLD(FLD(s110, 0), 0), FLD(FLD(s110, 0), 1)));
} else {
return F_Chk_dwnf_dback(a0, a1, s110);
}
}
static V W_Chk_dwnf_dlam(V *a) { (void)a; return F_Chk_dwnf_dlam(a[0], a[1], a[2], a[3]); }
static V F_Chk_dlhs__step(V a0, V a1, V a2, V a3) {
top:;
V s111 = a1;
if ((s111) == IMM(0)) {
return IMM(0);
} else if (TAG(s111) == 1 && (FLD(s111, 1)) == 0) {
return IMM(0);
} else if (TAG(s111) == 1 && nat_ge(FLD(s111, 1), 1)) {
return C2(1, F_Chk_dterm__apply(a0, FLD(s111, 0), a2, a3), nat_subk(FLD(s111, 1), 1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlhs__step(V *a) { (void)a; return F_Chk_dlhs__step(a[0], a[1], a[2], a[3]); }
static V S114(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dterm__cells(V a0, V a1) {
top:;
V s112 = a0;
V s113 = a1;
if (TAG(s112) == 1 && TAG(s113) == 1) {
return C2(1, F_Chk_dterm__cell(FLD(s112, 0), FLD(s113, 0)), F_Chk_dterm__cells(FLD(s112, 1), FLD(s113, 1)));
} else if (TAG(s112) == 1 && (s113) == IMM(0)) {
return C2(1, F_Chk_dterm__cell(FLD(s112, 0), S114()), F_Chk_dterm__cells(FLD(s112, 1), IMM(0)));
} else {
return IMM(0);
}
}
static V W_Chk_dterm__cells(V *a) { (void)a; return F_Chk_dterm__cells(a[0], a[1]); }
static V F_Chk_dhas__fun_dgo(V a0, V a1, V a2) {
top:;
V s115 = a1;
if (TAG(s115) == 11) {
return IMM(1);
} else if (TAG(s115) == 14) {
return F_Chk_dhas__fun_dadt(a0, FLD(s115, 0), FLD(s115, 1), F_Chk_dterm__key(F_Chk_dterm__lower(a0, C4(14, FLD(s115, 0), FLD(s115, 1), FLD(s115, 2), FLD(s115, 3)), 0u)), a2);
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
V s116 = a1;
if (TAG(s116) == 0) {
return C3(0, FLD(s116, 0), FLD(s116, 1), FLD(s116, 2));
} else if (TAG(s116) == 5) {
return C4(5, FLD(s116, 0), FLD(s116, 1), F_Chk_dterm__lower(a0, FLD(s116, 2), a2), FLD(s116, 3));
} else if (TAG(s116) == 6) {
V v117 = F_U32_dfrom__nat(F_List_dlength(FLD(s116, 0)));
return CN(6, 6, (V[]){FLD(s116, 0), F_Chk_dlet__ids(FLD(s116, 0), a2), F_Chk_dlowers(a0, FLD(s116, 2), a2), C3(25, IMM(0), IMM(0), F_Chk_dterm__lower(a0, F_Chk_dclo__apply(a0, FLD(s116, 3), F_Chk_dlet__vars(FLD(s116, 0), a2)), F_U32_dadd(a2, v117))), FLD(s116, 4), FLD(s116, 5)});
} else if (TAG(s116) == 7) {
return C2(7, F_Chk_dterm__lower(a0, FLD(s116, 0), a2), FLD(s116, 1));
} else if (TAG(s116) == 10) {
return C3(10, F_Chk_dterm__lower(a0, FLD(s116, 0), a2), F_Chk_dterm__lower(a0, FLD(s116, 1), a2), FLD(s116, 2));
} else if (TAG(s116) == 11) {
return CN(11, 6, (V[]){FLD(s116, 0), FLD(s116, 1), a2, F_Chk_dterm__lower(a0, FLD(s116, 3), a2), C3(24, IMM(0), a2, F_Chk_dterm__lower(a0, F_Chk_dclo__apply(a0, FLD(s116, 4), C2(1, C3(0, FLD(s116, 1), a2, IMM(0)), IMM(0))), F_U32_dinc(a2))), FLD(s116, 5)});
} else if (TAG(s116) == 12) {
return CN(12, 5, (V[]){FLD(s116, 0), a2, C3(24, IMM(0), a2, F_Chk_dterm__lower(a0, F_Chk_dclo__apply(a0, FLD(s116, 2), C2(1, C3(0, FLD(s116, 0), a2, IMM(0)), IMM(0))), F_U32_dinc(a2))), FLD(s116, 3), FLD(s116, 4)});
} else if (TAG(s116) == 13) {
return C3(13, F_Chk_dterm__lower(a0, FLD(s116, 0), a2), F_Chk_dterm__lower(a0, FLD(s116, 1), a2), FLD(s116, 2));
} else if (TAG(s116) == 14) {
return C4(14, FLD(s116, 0), F_Chk_dlowers(a0, FLD(s116, 1), a2), FLD(s116, 2), FLD(s116, 3));
} else if (TAG(s116) == 15) {
return C3(15, FLD(s116, 0), F_Chk_dlowers(a0, FLD(s116, 1), a2), FLD(s116, 2));
} else if (TAG(s116) == 17) {
return C4(17, FLD(s116, 0), F_Chk_dterm__lower(a0, FLD(s116, 1), a2), F_Chk_dterm__lower(a0, FLD(s116, 2), a2), FLD(s116, 3));
} else if (TAG(s116) == 19) {
return C4(19, F_Chk_dterm__lower(a0, FLD(s116, 0), a2), F_Chk_dterm__lower(a0, FLD(s116, 1), a2), F_Chk_dterm__lower(a0, FLD(s116, 2), a2), FLD(s116, 3));
} else if (TAG(s116) == 21) {
return C4(21, F_Chk_dterm__lower(a0, FLD(s116, 0), a2), F_Chk_dterm__lower(a0, FLD(s116, 1), a2), F_Chk_dterm__lower(a0, FLD(s116, 2), a2), FLD(s116, 3));
} else if (TAG(s116) == 23) {
return C3(23, F_Chk_dterm__lower(a0, FLD(s116, 0), a2), F_Chk_dterm__lower(a0, FLD(s116, 1), a2), FLD(s116, 2));
} else {
return s116;
}
}
static V W_Chk_dterm__lower_dgo(V *a) { (void)a; return F_Chk_dterm__lower_dgo(a[0], a[1], a[2]); }
static V F_Chk_dlowers(V a0, V a1, V a2) {
top:;
V s118 = a1;
if ((s118) == IMM(0)) {
return IMM(0);
} else if (TAG(s118) == 1) {
return C2(1, F_Chk_dterm__lower(a0, FLD(s118, 0), a2), F_Chk_dlowers(a0, FLD(s118, 1), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlowers(V *a) { (void)a; return F_Chk_dlowers(a[0], a[1], a[2]); }
static V W_U32_dinc(V *a) { (void)a; return F_U32_dinc(a[0]); }
static V W_U32_dadd(V *a) { (void)a; return F_U32_dadd(a[0], a[1]); }
static V F_Chk_dlet__vars(V a0, V a1) {
top:;
V s119 = a0;
if ((s119) == IMM(0)) {
return IMM(0);
} else if (TAG(s119) == 1) {
return C2(1, C3(0, FLD(s119, 0), a1, IMM(0)), F_Chk_dlet__vars(FLD(s119, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlet__vars(V *a) { (void)a; return F_Chk_dlet__vars(a[0], a[1]); }
static V F_Chk_dlet__ids(V a0, V a1) {
top:;
V s120 = a0;
if ((s120) == IMM(0)) {
return IMM(0);
} else if (TAG(s120) == 1) {
return C2(1, a1, F_Chk_dlet__ids(FLD(s120, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlet__ids(V *a) { (void)a; return F_Chk_dlet__ids(a[0], a[1]); }
static V W_U32_dfrom__nat(V *a) { (void)a; return F_U32_dfrom__nat(a[0]); }
static V S122(void) { static V c; return STRC(c, "V"); }
static V S123(void) { static V c; return STRC(c, "R"); }
static V S124(void) { static V c; return STRC(c, "!"); }
static V S125(void) { static V c; return STRC(c, ""); }
static V S126(void) { static V c; return STRC(c, "L("); }
static V S127(void) { static V c; return STRC(c, ")"); }
static V S128(void) { static V c; return STRC(c, "T("); }
static V S129(void) { static V c; return STRC(c, ")"); }
static V S130(void) { static V c; return STRC(c, "Q"); }
static V S131(void) { static V c; return STRC(c, "&"); }
static V S132(void) { static V c; return STRC(c, "M("); }
static V S133(void) { static V c; return STRC(c, ","); }
static V S134(void) { static V c; return STRC(c, ")"); }
static V S135(void) { static V c; return STRC(c, "A"); }
static V S136(void) { static V c; return STRC(c, "("); }
static V S137(void) { static V c; return STRC(c, ","); }
static V S138(void) { static V c; return STRC(c, ")"); }
static V S139(void) { static V c; return STRC(c, "F"); }
static V S140(void) { static V c; return STRC(c, "("); }
static V S141(void) { static V c; return STRC(c, ")"); }
static V S142(void) { static V c; return STRC(c, "@("); }
static V S143(void) { static V c; return STRC(c, ","); }
static V S144(void) { static V c; return STRC(c, ")"); }
static V S145(void) { static V c; return STRC(c, "D"); }
static V S146(void) { static V c; return STRC(c, "("); }
static V S147(void) { static V c; return STRC(c, ","); }
static V S148(void) { static V c; return STRC(c, ")"); }
static V S149(void) { static V c; return STRC(c, "C"); }
static V S150(void) { static V c; return STRC(c, "("); }
static V S151(void) { static V c; return STRC(c, ")"); }
static V S152(void) { static V c; return STRC(c, "N"); }
static V S153(void) { static V c; return STRC(c, "S\042"); }
static V S154(void) { static V c; return STRC(c, "\042"); }
static V S155(void) { static V c; return STRC(c, "X"); }
static V S156(void) { static V c; return STRC(c, "("); }
static V S157(void) { static V c; return STRC(c, ","); }
static V S158(void) { static V c; return STRC(c, ")"); }
static V S159(void) { static V c; return STRC(c, "E"); }
static V S160(void) { static V c; return STRC(c, "=("); }
static V S161(void) { static V c; return STRC(c, ","); }
static V S162(void) { static V c; return STRC(c, ","); }
static V S163(void) { static V c; return STRC(c, ")"); }
static V S164(void) { static V c; return STRC(c, "r"); }
static V S165(void) { static V c; return STRC(c, "%("); }
static V S166(void) { static V c; return STRC(c, ","); }
static V S167(void) { static V c; return STRC(c, ","); }
static V S168(void) { static V c; return STRC(c, ")"); }
static V S169(void) { static V c; return STRC(c, "\077"); }
static V S170(void) { static V c; return STRC(c, ":("); }
static V S171(void) { static V c; return STRC(c, ","); }
static V S172(void) { static V c; return STRC(c, ")"); }
static V S173(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dterm__key(V a0) {
top:;
V s121 = a0;
if (TAG(s121) == 0) {
return F_String_dappend(S122(), F_U32_dshow(FLD(s121, 1)));
} else if (TAG(s121) == 4) {
return F_String_dappend(S123(), F_String_dappend(FLD(s121, 0), F_Bool_dpick(FLD(s121, 2), S124(), S125())));
} else if (TAG(s121) == 5) {
{ V t0 = FLD(s121, 2); a0 = t0; goto top; }
} else if (TAG(s121) == 6) {
return F_String_dappend(S126(), F_String_dappend(F_Chk_dterm__key_dlist(FLD(s121, 2)), F_String_dappend(F_Chk_dterm__key(F_Chk_dsyn__body(FLD(s121, 3))), S127())));
} else if (TAG(s121) == 7) {
return F_String_dappend(S128(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 0)), S129()));
} else if (TAG(s121) == 8) {
return S130();
} else if (TAG(s121) == 9) {
return F_String_dappend(S131(), F_Chk_dshow_dqua(FLD(s121, 0)));
} else if (TAG(s121) == 10) {
return F_String_dappend(S132(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 0)), F_String_dappend(S133(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 1)), S134()))));
} else if (TAG(s121) == 11) {
return F_String_dappend(S135(), F_String_dappend(F_Chk_dquant__show(FLD(s121, 0)), F_String_dappend(F_U32_dshow(FLD(s121, 2)), F_String_dappend(S136(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 3)), F_String_dappend(S137(), F_String_dappend(F_Chk_dterm__key(F_Chk_dsyn__body(FLD(s121, 4))), S138())))))));
} else if (TAG(s121) == 12) {
return F_String_dappend(S139(), F_String_dappend(F_Chk_dquant__show(FLD(s121, 4)), F_String_dappend(F_U32_dshow(FLD(s121, 1)), F_String_dappend(S140(), F_String_dappend(F_Chk_dterm__key(F_Chk_dsyn__body(FLD(s121, 2))), S141())))));
} else if (TAG(s121) == 13) {
return F_String_dappend(S142(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 0)), F_String_dappend(S143(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 1)), S144()))));
} else if (TAG(s121) == 14) {
return F_String_dappend(S145(), F_String_dappend(FLD(s121, 0), F_String_dappend(S146(), F_String_dappend(F_Chk_dterm__key_dlist(FLD(s121, 1)), F_String_dappend(F_String_djoin(FLD(s121, 3), S147()), S148())))));
} else if (TAG(s121) == 15) {
return F_String_dappend(S149(), F_String_dappend(FLD(s121, 0), F_String_dappend(S150(), F_String_dappend(F_Chk_dterm__key_dlist(FLD(s121, 1)), S151()))));
} else if (TAG(s121) == 16 && TAG(FLD(s121, 0)) == 0) {
return F_String_dappend(S152(), F_Nat_dshow(FLD(FLD(s121, 0), 0)));
} else if (TAG(s121) == 16 && TAG(FLD(s121, 0)) == 1) {
return F_String_dappend(S153(), F_String_dappend(F_Chk_dshow_dtext(FLD(FLD(s121, 0), 0)), S154()));
} else if (TAG(s121) == 17) {
return F_String_dappend(S155(), F_String_dappend(FLD(s121, 0), F_String_dappend(S156(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 1)), F_String_dappend(S157(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 2)), S158()))))));
} else if (TAG(s121) == 18) {
return S159();
} else if (TAG(s121) == 19) {
return F_String_dappend(S160(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 0)), F_String_dappend(S161(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 1)), F_String_dappend(S162(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 2)), S163()))))));
} else if (TAG(s121) == 20) {
return S164();
} else if (TAG(s121) == 21) {
return F_String_dappend(S165(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 0)), F_String_dappend(S166(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 1)), F_String_dappend(S167(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 2)), S168()))))));
} else if (TAG(s121) == 22) {
return F_String_dappend(S169(), FLD(s121, 0));
} else if (TAG(s121) == 23) {
return F_String_dappend(S170(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 0)), F_String_dappend(S171(), F_String_dappend(F_Chk_dterm__key(FLD(s121, 1)), S172()))));
} else {
return S173();
}
}
static V W_Chk_dterm__key(V *a) { (void)a; return F_Chk_dterm__key(a[0]); }
static V F_String_dappend(V a0, V a1) {
top:;
V s174 = a0;
if ((s174) == IMM(0)) {
return a1;
} else if (TAG(s174) == 1) {
return C2(1, FLD(s174, 0), F_String_dappend(FLD(s174, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_String_dappend(V *a) { (void)a; return F_String_dappend(a[0], a[1]); }
static V S176(void) { static V c; return STRC(c, ""); }
static V F_Chk_dshow_dtext(V a0) {
top:;
V s175 = a0;
if ((s175) == IMM(0)) {
return S176();
} else if (TAG(s175) == 1) {
return F_String_dappend(F_Chk_dshow_dchr(FLD(s175, 0), 34u), F_Chk_dshow_dtext(FLD(s175, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dtext(V *a) { (void)a; return F_Chk_dshow_dtext(a[0]); }
static V S177(void) { static V c; return STRC(c, "\134n"); }
static V S178(void) { static V c; return STRC(c, "\134t"); }
static V S179(void) { static V c; return STRC(c, "\134r"); }
static V S180(void) { static V c; return STRC(c, "\1340"); }
static V S181(void) { static V c; return STRC(c, "\134"); }
static V S182(void) { static V c; return STRC(c, "\134u{"); }
static V S183(void) { static V c; return STRC(c, "}"); }
static V F_Chk_dshow_dchr(V a0, V a1) {
top:;
return F_Bool_dpick(F_U32_dis__eq(a0, 10u), S177(), F_Bool_dpick(F_U32_dis__eq(a0, 9u), S178(), F_Bool_dpick(F_U32_dis__eq(a0, 13u), S179(), F_Bool_dpick(F_U32_dis__eq(a0, 0u), S180(), F_Bool_dpick(F_Bool_dor(F_U32_dis__eq(a0, 92u), F_U32_dis__eq(a0, a1)), F_String_dappend(S181(), F_Chk_dStr_dchr(a0)), F_Bool_dpick(F_Bool_dor(F_Bool_dor(F_U32_dis__lt(a0, 32u), F_U32_dis__eq(a0, 127u)), F_Bool_dor(F_Bool_dand(F_U32_dis__ge(a0, 55296u), F_U32_dis__le(a0, 57343u)), F_U32_dis__gt(a0, 1114111u))), F_String_dappend(S182(), F_String_dappend(F_Chk_dU32_dshow__hex(a0), S183())), F_Chk_dStr_dchr(a0)))))));
}
static V W_Chk_dshow_dchr(V *a) { (void)a; return F_Chk_dshow_dchr(a[0], a[1]); }
static V F_Chk_dStr_dchr(V a0) {
top:;
return C2(1, a0, IMM(0));
}
static V W_Chk_dStr_dchr(V *a) { (void)a; return F_Chk_dStr_dchr(a[0]); }
static V S184(void) { static V c; return STRC(c, ""); }
static V F_Chk_dU32_dshow__hex(V a0) {
top:;
return F_Chk_dU32_dshow__hex_dgo(a0, S184());
}
static V W_Chk_dU32_dshow__hex(V *a) { (void)a; return F_Chk_dU32_dshow__hex(a[0]); }
static V F_Chk_dU32_dshow__hex_dgo(V a0, V a1) {
top:;
V v185 = F_U32_dand(a0, 15u);
V v186 = F_Chk_dStr_dchr(F_Bool_dpick(F_U32_dis__lt(v185, 10u), F_U32_dadd(48u, v185), F_U32_dadd(87u, v185)));
return F_Chk_dshow__hex_dmore(a0, F_String_dappend(v186, a1), F_U32_dis__lt(a0, 16u));
}
static V W_Chk_dU32_dshow__hex_dgo(V *a) { (void)a; return F_Chk_dU32_dshow__hex_dgo(a[0], a[1]); }
static V W_U32_dis__lt(V *a) { (void)a; return F_U32_dis__lt(a[0], a[1]); }
static V F_Chk_dshow__hex_dmore(V a0, V a1, V a2) {
top:;
V s187 = a2;
if ((s187) == IMM(1)) {
return a1;
} else if ((s187) == IMM(0)) {
return F_Chk_dU32_dshow__hex_dgo(F_U32_dshrn(a0, 4u), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow__hex_dmore(V *a) { (void)a; return F_Chk_dshow__hex_dmore(a[0], a[1], a[2]); }
static V W_U32_dis__gt(V *a) { (void)a; return F_U32_dis__gt(a[0], a[1]); }
static V W_U32_dis__le(V *a) { (void)a; return F_U32_dis__le(a[0], a[1]); }
static V W_U32_dis__ge(V *a) { (void)a; return F_U32_dis__ge(a[0], a[1]); }
static V F_Bool_dand(V a0, V a1) {
top:;
V s188 = a0;
if ((s188) == IMM(0)) {
return IMM(0);
} else if ((s188) == IMM(1)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dand(V *a) { (void)a; return F_Bool_dand(a[0], a[1]); }
static V F_Bool_dor(V a0, V a1) {
top:;
V s189 = a0;
if ((s189) == IMM(0)) {
return a1;
} else if ((s189) == IMM(1)) {
return IMM(1);
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dor(V *a) { (void)a; return F_Bool_dor(a[0], a[1]); }
static V W_Nat_dshow(V *a) { (void)a; return F_Nat_dshow(a[0]); }
static V S191(void) { static V c; return STRC(c, ""); }
static V S192(void) { static V c; return STRC(c, ","); }
static V F_Chk_dterm__key_dlist(V a0) {
top:;
V s190 = a0;
if ((s190) == IMM(0)) {
return S191();
} else if (TAG(s190) == 1) {
return F_String_dappend(F_Chk_dterm__key(FLD(s190, 0)), F_String_dappend(S192(), F_Chk_dterm__key_dlist(FLD(s190, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dterm__key_dlist(V *a) { (void)a; return F_Chk_dterm__key_dlist(a[0]); }
static V F_String_djoin(V a0, V a1) {
top:;
V s193 = a0;
if ((s193) == IMM(0)) {
return IMM(0);
} else if (TAG(s193) == 1) {
return F_String_djoin_dgo(FLD(s193, 1), FLD(s193, 0), a1);
} else { bend_fail("incomplete match"); }
}
static V W_String_djoin(V *a) { (void)a; return F_String_djoin(a[0], a[1]); }
static V F_String_djoin_dgo(V a0, V a1, V a2) {
top:;
V s194 = a0;
if ((s194) == IMM(0)) {
return a1;
} else if (TAG(s194) == 1) {
return F_String_dappend(a1, F_String_dappend(a2, F_String_djoin_dgo(FLD(s194, 1), FLD(s194, 0), a2)));
} else { bend_fail("incomplete match"); }
}
static V W_String_djoin_dgo(V *a) { (void)a; return F_String_djoin_dgo(a[0], a[1], a[2]); }
static V F_U32_dshow(V a0) {
top:;
V v195 = a0;
return F_U32_dshow_dif(v195, F_U32_dis__zero(v195));
}
static V W_U32_dshow(V *a) { (void)a; return F_U32_dshow(a[0]); }
static V F_U32_dshow_dif(V a0, V a1) {
top:;
V s196 = a1;
if ((s196) == IMM(1)) {
return C2(1, 48u, IMM(0));
} else if ((s196) == IMM(0)) {
return F_U32_dshow_dgo(10u, a0, IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_U32_dshow_dif(V *a) { (void)a; return F_U32_dshow_dif(a[0], a[1]); }
static V F_U32_dshow_dgo(V a0, V a1, V a2) {
top:;
V s197 = a0;
if ((s197) == 0) {
return a2;
} else if (nat_ge(s197, 1)) {
return F_U32_dshow_dfin(nat_subk(s197, 1), a2, a1, F_U32_dis__zero(a1));
} else { bend_fail("incomplete match"); }
}
static V W_U32_dshow_dgo(V *a) { (void)a; return F_U32_dshow_dgo(a[0], a[1], a[2]); }
static V F_U32_dshow_dfin(V a0, V a1, V a2, V a3) {
top:;
V s198 = a3;
if ((s198) == IMM(1)) {
return a1;
} else if ((s198) == IMM(0)) {
return F_U32_dshow_dgo(a0, F_U32_ddiv(a2, 10u), C2(1, F_U32_dadd(48u, F_U32_dmod(a2, 10u)), a1));
} else { bend_fail("incomplete match"); }
}
static V W_U32_dshow_dfin(V *a) { (void)a; return F_U32_dshow_dfin(a[0], a[1], a[2], a[3]); }
static V W_U32_dmod(V *a) { (void)a; return F_U32_dmod(a[0], a[1]); }
static V W_U32_ddiv(V *a) { (void)a; return F_U32_ddiv(a[0], a[1]); }
static V S200(void) { static V c; return STRC(c, "-"); }
static V S201(void) { static V c; return STRC(c, "+"); }
static V S202(void) { static V c; return STRC(c, ""); }
static V F_Chk_dquant__show(V a0) {
top:;
V s199 = a0;
if ((s199) == IMM(0)) {
return S200();
} else if ((s199) == IMM(2)) {
return S201();
} else {
return S202();
}
}
static V W_Chk_dquant__show(V *a) { (void)a; return F_Chk_dquant__show(a[0]); }
static V S204(void) { static V c; return STRC(c, "&0"); }
static V S205(void) { static V c; return STRC(c, "&2"); }
static V S206(void) { static V c; return STRC(c, "&1"); }
static V F_Chk_dshow_dqua(V a0) {
top:;
V s203 = a0;
if ((s203) == IMM(0)) {
return S204();
} else if ((s203) == IMM(2)) {
return S205();
} else {
return S206();
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
V s207 = a0;
if ((s207) == IMM(0)) {
return IMM(0);
} else if (TAG(s207) == 1) {
return F_Chk_dStr_dhas_dif(FLD(s207, 1), a1, F_String_deq(FLD(s207, 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dhas(V *a) { (void)a; return F_Chk_dStr_dhas(a[0], a[1]); }
static V F_Chk_dStr_dhas_dif(V a0, V a1, V a2) {
top:;
V s208 = a2;
if ((s208) == IMM(1)) {
return IMM(1);
} else if ((s208) == IMM(0)) {
return F_Chk_dStr_dhas(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dhas_dif(V *a) { (void)a; return F_Chk_dStr_dhas_dif(a[0], a[1], a[2]); }
static V F_Chk_dhas__fun_dadt_dc(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s209 = a5;
if ((s209) == IMM(1)) {
return IMM(0);
} else if ((s209) == IMM(0)) {
return F_Chk_dhas__fun_dctrs(a0, a2, F_Chk_dhas__fun_dcs(F_Chk_dbook__tld(a0, a1)), C2(1, a3, a4));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dhas__fun_dadt_dc(V *a) { (void)a; return F_Chk_dhas__fun_dadt_dc(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dhas__fun_dcs(V a0) {
top:;
V s210 = a0;
if (TAG(s210) == 1 && TAG(FLD(s210, 0)) == 1) {
return FLD(FLD(s210, 0), 3);
} else {
return IMM(0);
}
}
static V W_Chk_dhas__fun_dcs(V *a) { (void)a; return F_Chk_dhas__fun_dcs(a[0]); }
static V L212(V *a) {
return F_Chk_dhas__fun_dctrs(a[3], a[2], a[1], a[0]);
}
static V F_Chk_dhas__fun_dctrs(V a0, V a1, V a2, V a3) {
top:;
V s211 = a2;
if ((s211) == IMM(0)) {
return IMM(0);
} else if (TAG(s211) == 1) {
return F_Chk_dLazy_dor(F_Chk_dhas__fun_dfields(a0, F_Chk_dhas__fun_dfill(a0, FLD(FLD(s211, 0), 2), a1), FLD(FLD(s211, 0), 1), 0u, a3), mk_clo(L212, 5, 4, (V[]){a3, FLD(s211, 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dhas__fun_dctrs(V *a) { (void)a; return F_Chk_dhas__fun_dctrs(a[0], a[1], a[2], a[3]); }
static V F_Chk_dhas__fun_dfill(V a0, V a1, V a2) {
top:;
V s213 = a2;
if ((s213) == IMM(0)) {
return a1;
} else if (TAG(s213) == 1) {
{ V t0 = a0; V t1 = F_Chk_dclo__apply(a0, F_Chk_dAll_db(F_Chk_dterm__wnf(a0, a1)), C2(1, FLD(s213, 0), IMM(0))); V t2 = FLD(s213, 1); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dhas__fun_dfill(V *a) { (void)a; return F_Chk_dhas__fun_dfill(a[0], a[1], a[2]); }
static V F_Chk_dAll_db(V a0) {
top:;
V s214 = a0;
if (TAG(s214) == 11) {
return FLD(s214, 4);
} else {
return C1(30, s214);
}
}
static V W_Chk_dAll_db(V *a) { (void)a; return F_Chk_dAll_db(a[0]); }
static V F_Chk_dhas__fun_dfields(V a0, V a1, V a2, V a3, V a4) {
top:;
V s215 = a2;
if ((s215) == 0) {
return IMM(0);
} else if (nat_ge(s215, 1)) {
return F_Chk_dhas__fun_dfield(a0, F_Chk_dterm__wnf(a0, a1), nat_subk(s215, 1), a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dhas__fun_dfields(V *a) { (void)a; return F_Chk_dhas__fun_dfields(a[0], a[1], a[2], a[3], a[4]); }
static V L217(V *a) {
return F_Chk_dhas__fun_dfields(a[5], F_Chk_dclo__apply(a[5], a[4], C2(1, C3(0, a[3], a[2], IMM(0)), IMM(0))), a[1], F_U32_dinc(a[2]), a[0]);
}
static V F_Chk_dhas__fun_dfield(V a0, V a1, V a2, V a3, V a4) {
top:;
V s216 = a1;
if (TAG(s216) == 11) {
return F_Chk_dLazy_dor(F_Chk_dhas__fun(a0, FLD(s216, 3), a4), mk_clo(L217, 7, 6, (V[]){a4, a2, a3, FLD(s216, 1), FLD(s216, 4), a0}));
} else {
return IMM(0);
}
}
static V W_Chk_dhas__fun_dfield(V *a) { (void)a; return F_Chk_dhas__fun_dfield(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dLazy_dor(V a0, V a1) {
top:;
V s218 = a0;
if ((s218) == IMM(1)) {
return IMM(1);
} else if ((s218) == IMM(0)) {
return apply(a1, IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dLazy_dor(V *a) { (void)a; return F_Chk_dLazy_dor(a[0], a[1]); }
static V F_Chk_dmain__is__io(V a0) {
top:;
return F_Chk_dmain__is__io_dgo(a0, F_Chk_dmain__tld(a0));
}
static V W_Chk_dmain__is__io(V *a) { (void)a; return F_Chk_dmain__is__io(a[0]); }
static V F_Chk_dmain__is__io_dgo(V a0, V a1) {
top:;
V s219 = a1;
if (TAG(s219) == 1 && TAG(FLD(s219, 0)) == 0) {
return F_Chk_dvalid_dio(a0, F_Chk_dterm__head(F_Chk_dterm__strip(FLD(FLD(s219, 0), 2))));
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
V s220 = a0;
if (TAG(s220) == 13) {
{ V t0 = FLD(s220, 0); V t1 = C2(1, FLD(s220, 1), a1); a0 = t0; a1 = t1; goto top; }
} else {
return C2(0, s220, a1);
}
}
static V W_Chk_dterm__unapply_dgo(V *a) { (void)a; return F_Chk_dterm__unapply_dgo(a[0], a[1]); }
static V F_Pair_dfst(V a2) {
top:;
V v221 = a2;
return FLD(v221, 0);
}
static V W_Pair_dfst(V *a) { (void)a; return F_Pair_dfst(a[2]); }
static V S223(void) { static V c; return STRC(c, "IO"); }
static V F_Chk_dvalid_dio(V a0, V a1) {
top:;
V s222 = a1;
if (TAG(s222) == 4 && TAG(FLD(s222, 0)) == 1 && (FLD(FLD(s222, 0), 0)) == 73 && TAG(FLD(FLD(s222, 0), 1)) == 1 && (FLD(FLD(FLD(s222, 0), 1), 0)) == 79 && (FLD(FLD(FLD(s222, 0), 1), 1)) == IMM(0)) {
return F_Chk_dvalid_dio_dbase(F_Chk_dbook__tld(a0, S223()));
} else {
return IMM(0);
}
}
static V W_Chk_dvalid_dio(V *a) { (void)a; return F_Chk_dvalid_dio(a[0], a[1]); }
static V F_Chk_dvalid_dio_dbase(V a0) {
top:;
V s224 = a0;
if (TAG(s224) == 1 && TAG(FLD(s224, 0)) == 0 && (FLD(FLD(s224, 0), 5)) == IMM(1)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dvalid_dio_dbase(V *a) { (void)a; return F_Chk_dvalid_dio_dbase(a[0]); }
static V F_Bool_dnot(V a0) {
top:;
V s225 = a0;
if ((s225) == IMM(0)) {
return IMM(1);
} else if ((s225) == IMM(1)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dnot(V *a) { (void)a; return F_Bool_dnot(a[0]); }
static V F_Main_dchecked_dgo(V a0, V a1, V a2, V a3) {
top:;
V s226 = a3;
if ((s226) == IMM(1)) {
return F_Main_demit__value(F_Chk_dshow__main(a2));
} else if ((s226) == IMM(0)) {
return F_Main_dbuild(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchecked_dgo(V *a) { (void)a; return F_Main_dchecked_dgo(a[0], a[1], a[2], a[3]); }
static V L228(V *a) {
return F_Main_dcompile(F_Main_dresolve(F_Mod_ddir(a[1]), F_Main_dparse(a[0])), C1(1, a[2]));
}
static V L227(V *a) {
return F_IO_dbind(F_Main_dload(64u, a[1]), mk_clo(L228, 3, 2, (V[]){a[2], a[0]}));
}
static V F_Main_dbuild(V a0, V a1) {
top:;
return F_IO_dbind(F_IO_dread__file(a0), mk_clo(L227, 3, 2, (V[]){a0, a1}));
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
V s229 = a0;
if ((s229) == IMM(0)) {
return C2(1, IMM(0), IMM(0));
} else if (TAG(s229) == 1) {
return F_String_dsplit_dfin(FLD(s229, 0), F_String_dsplit(FLD(s229, 1), a1), F_Char_dis__eq(FLD(s229, 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_String_dsplit(V *a) { (void)a; return F_String_dsplit(a[0], a[1]); }
static V F_Char_dis__eq(V a0, V a1) {
top:;
V s230 = a0;
V s231 = a1;
{
return F_U32_dis__eq(s230, s231);
}
}
static V W_Char_dis__eq(V *a) { (void)a; return F_Char_dis__eq(a[0], a[1]); }
static V F_String_dsplit_dfin(V a0, V a1, V a2) {
top:;
V s232 = a2;
if ((s232) == IMM(0)) {
return F_String_dsplit_dpush(a0, a1);
} else if ((s232) == IMM(1)) {
return C2(1, IMM(0), a1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dsplit_dfin(V *a) { (void)a; return F_String_dsplit_dfin(a[0], a[1], a[2]); }
static V F_String_dsplit_dpush(V a0, V a1) {
top:;
V s233 = a1;
if ((s233) == IMM(0)) {
return C2(1, C2(1, a0, IMM(0)), IMM(0));
} else if (TAG(s233) == 1) {
return C2(1, C2(1, a0, FLD(s233, 0)), FLD(s233, 1));
} else { bend_fail("incomplete match"); }
}
static V W_String_dsplit_dpush(V *a) { (void)a; return F_String_dsplit_dpush(a[0], a[1]); }
static V F_Lex_dlines_dgo(V a0, V a1) {
top:;
V s234 = a0;
if ((s234) == IMM(0)) {
return IMM(0);
} else if (TAG(s234) == 1) {
return F_Lex_dlines_dput(C3(0, F_Lex_dindent(FLD(s234, 0)), a1, F_List_dreverse(F_Lex_dline(FLD(s234, 0), IMM(1), a1, IMM(0)))), F_Lex_dlines_dgo(FLD(s234, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlines_dgo(V *a) { (void)a; return F_Lex_dlines_dgo(a[0], a[1]); }
static V F_Lex_dline(V a0, V a1, V a2, V a3) {
top:;
V s235 = a0;
if ((s235) == IMM(0)) {
return a3;
} else if (TAG(s235) == 1) {
return F_Lex_dline_dgo(FLD(s235, 0), FLD(s235, 1), a1, a2, a3, F_Lex_dclass(FLD(s235, 0)));
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
V s236 = a0;
{
return F_Bool_dand(F_U32_dis__ge(s236, 48u), F_U32_dis__le(s236, 57u));
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
V s237 = a0;
{
return s237;
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
V s238 = a0;
{
return F_Bool_dand(F_U32_dis__ge(s238, 97u), F_U32_dis__le(s238, 122u));
}
}
static V W_Char_dis__lower(V *a) { (void)a; return F_Char_dis__lower(a[0]); }
static V F_Char_dis__upper(V a0) {
top:;
V s239 = a0;
{
return F_Bool_dand(F_U32_dis__ge(s239, 65u), F_U32_dis__le(s239, 90u));
}
}
static V W_Char_dis__upper(V *a) { (void)a; return F_Char_dis__upper(a[0]); }
static V F_Lex_dline_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s240 = a5;
if ((s240) == 0) {
return F_Lex_dline(a1, IMM(1), a3, a4);
} else if ((s240) == 1) {
return a4;
} else if ((s240) == 2) {
return F_Lex_dline_did(a2, a3, a4, F_Lex_did(C2(1, a0, a1), IMM(0)));
} else if ((s240) == 3) {
return F_Lex_dline_dnum(a2, a3, a4, F_Lex_ddigits(C2(1, a0, a1), 0u));
} else if ((s240) == 4) {
return F_Lex_dline_dchr(a2, a3, a4, F_Lex_dlit__char(a1));
} else if ((s240) == 5) {
return F_Lex_dline_dstr(a2, a3, a4, F_Lex_dstr(a1, IMM(0)));
} else if (nat_ge(s240, 6)) {
V v241 = C2(1, a0, a1);
return F_Lex_dline_dop(v241, a2, a3, a4, F_Lex_dop__of(v241));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dgo(V *a) { (void)a; return F_Lex_dline_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Lex_dop__of(V a0) {
top:;
return F_Lex_dop__of_dgo(F_Lex_dfind__op(F_Lex_dops3(), a0), a0);
}
static V W_Lex_dop__of(V *a) { (void)a; return F_Lex_dop__of(a[0]); }
static V S242(void) { static V c; return STRC(c, ".&."); }
static V S243(void) { static V c; return STRC(c, ".|."); }
static V S244(void) { static V c; return STRC(c, ".^."); }
static V S245(void) { static V c; return STRC(c, "<&>"); }
static V F_Lex_dops3(void) {
top:;
return C2(1, S242(), C2(1, S243(), C2(1, S244(), C2(1, S245(), IMM(0)))));
}
static V W_Lex_dops3(V *a) { (void)a; return F_Lex_dops3(); }
static V F_Lex_dfind__op(V a0, V a1) {
top:;
V s246 = a0;
if ((s246) == IMM(0)) {
return IMM(0);
} else if (TAG(s246) == 1) {
return F_Lex_dfind__op_dif(FLD(s246, 0), FLD(s246, 1), a1, F_String_dstarts__with(a1, FLD(s246, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dfind__op(V *a) { (void)a; return F_Lex_dfind__op(a[0], a[1]); }
static V F_String_dstarts__with(V a0, V a1) {
top:;
V s247 = a0;
V s248 = a1;
if ((s247) == IMM(0) && (s248) == IMM(0)) {
return IMM(1);
} else if ((s247) == IMM(0) && TAG(s248) == 1) {
return IMM(0);
} else if (TAG(s247) == 1 && (s248) == IMM(0)) {
return IMM(1);
} else if (TAG(s247) == 1 && TAG(s248) == 1) {
return F_String_dstarts__with_dif(FLD(s247, 1), FLD(s248, 1), F_Char_dis__eq(FLD(s247, 0), FLD(s248, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_String_dstarts__with(V *a) { (void)a; return F_String_dstarts__with(a[0], a[1]); }
static V F_String_dstarts__with_dif(V a0, V a1, V a2) {
top:;
V s249 = a2;
if ((s249) == IMM(0)) {
return IMM(0);
} else if ((s249) == IMM(1)) {
return F_String_dstarts__with(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dstarts__with_dif(V *a) { (void)a; return F_String_dstarts__with_dif(a[0], a[1], a[2]); }
static V F_Lex_dfind__op_dif(V a0, V a1, V a2, V a3) {
top:;
V s250 = a3;
if ((s250) == IMM(1)) {
return C1(1, a0);
} else if ((s250) == IMM(0)) {
return F_Lex_dfind__op(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dfind__op_dif(V *a) { (void)a; return F_Lex_dfind__op_dif(a[0], a[1], a[2], a[3]); }
static V F_Lex_dop__of_dgo(V a0, V a1) {
top:;
V s251 = a0;
if (TAG(s251) == 1) {
return FLD(s251, 0);
} else if ((s251) == IMM(0)) {
return F_Lex_dop__of_dtwo(F_Lex_dfind__op(F_Lex_dops2(), a1), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dop__of_dgo(V *a) { (void)a; return F_Lex_dop__of_dgo(a[0], a[1]); }
static V S252(void) { static V c; return STRC(c, "=>"); }
static V S253(void) { static V c; return STRC(c, "->"); }
static V S254(void) { static V c; return STRC(c, "<-"); }
static V S255(void) { static V c; return STRC(c, "<>"); }
static V S256(void) { static V c; return STRC(c, "<="); }
static V S257(void) { static V c; return STRC(c, ">="); }
static V S258(void) { static V c; return STRC(c, "=="); }
static V S259(void) { static V c; return STRC(c, "!="); }
static V S260(void) { static V c; return STRC(c, "++"); }
static V S261(void) { static V c; return STRC(c, "&&"); }
static V S262(void) { static V c; return STRC(c, "||"); }
static V S263(void) { static V c; return STRC(c, ">>"); }
static V S264(void) { static V c; return STRC(c, "<<"); }
static V F_Lex_dops2(void) {
top:;
return C2(1, S252(), C2(1, S253(), C2(1, S254(), C2(1, S255(), C2(1, S256(), C2(1, S257(), C2(1, S258(), C2(1, S259(), C2(1, S260(), C2(1, S261(), C2(1, S262(), C2(1, S263(), C2(1, S264(), IMM(0))))))))))))));
}
static V W_Lex_dops2(V *a) { (void)a; return F_Lex_dops2(); }
static V F_Lex_dop__of_dtwo(V a0, V a1) {
top:;
V s265 = a0;
if (TAG(s265) == 1) {
return FLD(s265, 0);
} else if ((s265) == IMM(0)) {
return F_String_dtake(a1, 1u);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dop__of_dtwo(V *a) { (void)a; return F_Lex_dop__of_dtwo(a[0], a[1]); }
static V F_String_dtake(V a0, V a1) {
top:;
V s266 = a0;
V s267 = a1;
if ((s266) == IMM(0)) {
return IMM(0);
} else if (TAG(s266) == 1 && (s267) == 0) {
return IMM(0);
} else if (TAG(s266) == 1 && nat_ge(s267, 1)) {
return C2(1, FLD(s266, 0), F_String_dtake(FLD(s266, 1), nat_subk(s267, 1)));
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
V s268 = a0;
if ((s268) == IMM(0)) {
return 0u;
} else if (TAG(s268) == 1) {
return nat_addk(F_String_dlength(FLD(s268, 1)), 1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dlength(V *a) { (void)a; return F_String_dlength(a[0]); }
static V F_String_ddrop(V a0, V a1) {
top:;
V s269 = a0;
V s270 = a1;
if ((s269) == IMM(0)) {
return IMM(0);
} else if (TAG(s269) == 1 && (s270) == 0) {
return C2(1, FLD(s269, 0), FLD(s269, 1));
} else if (TAG(s269) == 1 && nat_ge(s270, 1)) {
{ V t0 = FLD(s269, 1); V t1 = nat_subk(s270, 1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_String_ddrop(V *a) { (void)a; return F_String_ddrop(a[0], a[1]); }
static V F_Lex_dstr(V a0, V a1) {
top:;
V s271 = a0;
if ((s271) == IMM(0)) {
return C2(0, F_Str_drev(a1), IMM(0));
} else if (TAG(s271) == 1) {
return F_Lex_dstr_dif(FLD(s271, 0), FLD(s271, 1), a1, F_U32_dis__eq(FLD(s271, 0), 34u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dstr(V *a) { (void)a; return F_Lex_dstr(a[0], a[1]); }
static V F_Lex_dstr_dif(V a0, V a1, V a2, V a3) {
top:;
V s272 = a3;
if ((s272) == IMM(1)) {
return C2(0, F_Str_drev(a2), a1);
} else if ((s272) == IMM(0)) {
return F_Lex_dstr_dnext(a2, F_Lex_dlit__char(C2(1, a0, a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dstr_dif(V *a) { (void)a; return F_Lex_dstr_dif(a[0], a[1], a[2], a[3]); }
static V F_Lex_dlit__char(V a0) {
top:;
V s273 = a0;
if ((s273) == IMM(0)) {
return C2(0, 0u, IMM(0));
} else if (TAG(s273) == 1) {
return F_Lex_dlit__char_dif(FLD(s273, 0), FLD(s273, 1), F_U32_dis__eq(FLD(s273, 0), 92u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlit__char(V *a) { (void)a; return F_Lex_dlit__char(a[0]); }
static V F_Lex_dlit__char_dif(V a0, V a1, V a2) {
top:;
V s274 = a2;
if ((s274) == IMM(0)) {
return C2(0, a0, a1);
} else if ((s274) == IMM(1)) {
return F_Lex_dlit__char_desc(a1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlit__char_dif(V *a) { (void)a; return F_Lex_dlit__char_dif(a[0], a[1], a[2]); }
static V F_Lex_dlit__char_desc(V a0) {
top:;
V s275 = a0;
if ((s275) == IMM(0)) {
return C2(0, 92u, IMM(0));
} else if (TAG(s275) == 1) {
return C2(0, F_Lex_desc(FLD(s275, 0)), FLD(s275, 1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlit__char_desc(V *a) { (void)a; return F_Lex_dlit__char_desc(a[0]); }
static V F_Lex_desc(V a0) {
top:;
V v276 = a0;
return F_Bool_dpick(F_U32_dis__eq(v276, 110u), 10u, F_Bool_dpick(F_U32_dis__eq(v276, 116u), 9u, F_Bool_dpick(F_U32_dis__eq(v276, 114u), 13u, F_Bool_dpick(F_U32_dis__eq(v276, 48u), 0u, v276))));
}
static V W_Lex_desc(V *a) { (void)a; return F_Lex_desc(a[0]); }
static V F_Lex_dstr_dnext(V a0, V a1) {
top:;
V v277 = a1;
return F_Lex_dstr(FLD(v277, 1), C2(1, FLD(v277, 0), a0));
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
V s278 = a0;
if ((s278) == IMM(0)) {
return a1;
} else if (TAG(s278) == 1) {
{ V t0 = FLD(s278, 1); V t1 = C2(1, FLD(s278, 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_String_dreverse_dgo(V *a) { (void)a; return F_String_dreverse_dgo(a[0], a[1]); }
static V F_Lex_dline_dstr(V a0, V a1, V a2, V a3) {
top:;
V v279 = a3;
return F_Lex_dline(FLD(v279, 1), IMM(0), a1, C2(1, C3(0, C1(6, FLD(v279, 0)), a0, a1), a2));
}
static V W_Lex_dline_dstr(V *a) { (void)a; return F_Lex_dline_dstr(a[0], a[1], a[2], a[3]); }
static V F_Lex_dline_dchr(V a0, V a1, V a2, V a3) {
top:;
V v280 = a3;
return F_Lex_dline(F_Lex_ddrop1(FLD(v280, 1)), IMM(0), a1, C2(1, C3(0, C1(5, FLD(v280, 0)), a0, a1), a2));
}
static V W_Lex_dline_dchr(V *a) { (void)a; return F_Lex_dline_dchr(a[0], a[1], a[2], a[3]); }
static V F_Lex_ddrop1(V a0) {
top:;
V s281 = a0;
if ((s281) == IMM(0)) {
return IMM(0);
} else if (TAG(s281) == 1) {
return FLD(s281, 1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddrop1(V *a) { (void)a; return F_Lex_ddrop1(a[0]); }
static V F_Lex_ddigits(V a0, V a1) {
top:;
V s282 = a0;
if ((s282) == IMM(0)) {
return C2(0, a1, IMM(0));
} else if (TAG(s282) == 1) {
return F_Lex_ddigits_dif(FLD(s282, 0), FLD(s282, 1), a1, F_Char_dis__digit(FLD(s282, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddigits(V *a) { (void)a; return F_Lex_ddigits(a[0], a[1]); }
static V F_Lex_ddigits_dif(V a0, V a1, V a2, V a3) {
top:;
V s283 = a3;
if ((s283) == IMM(1)) {
return F_Lex_ddigits(a1, F_U32_dadd(F_U32_dmul(a2, 10u), F_U32_dsub(F_Char_dto__u32(a0), 48u)));
} else if ((s283) == IMM(0)) {
return C2(0, a2, C2(1, a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddigits_dif(V *a) { (void)a; return F_Lex_ddigits_dif(a[0], a[1], a[2], a[3]); }
static V W_U32_dsub(V *a) { (void)a; return F_U32_dsub(a[0], a[1]); }
static V W_U32_dmul(V *a) { (void)a; return F_U32_dmul(a[0], a[1]); }
static V F_Lex_dline_dnum(V a0, V a1, V a2, V a3) {
top:;
V v284 = a3;
return F_Lex_dline_dnum_dgo(a0, a1, a2, FLD(v284, 0), FLD(v284, 1));
}
static V W_Lex_dline_dnum(V *a) { (void)a; return F_Lex_dline_dnum(a[0], a[1], a[2], a[3]); }
static V F_Lex_dline_dnum_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s285 = a4;
if ((s285) == IMM(0)) {
return F_Lex_dline(IMM(0), IMM(0), a1, C2(1, C3(0, C1(3, a3), a0, a1), a2));
} else if (TAG(s285) == 1) {
return F_Lex_dline_dnum_dif(a0, a1, a2, a3, FLD(s285, 0), FLD(s285, 1), F_Bool_dpick(F_U32_dis__eq(FLD(s285, 0), 110u), 1u, F_Bool_dpick(F_U32_dis__eq(FLD(s285, 0), 46u), 2u, 0u)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnum_dgo(V *a) { (void)a; return F_Lex_dline_dnum_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V F_Lex_dline_dnum_dif(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s286 = a6;
if ((s286) == 0) {
return F_Lex_dline(C2(1, a4, a5), IMM(0), a1, C2(1, C3(0, C1(3, a3), a0, a1), a2));
} else if ((s286) == 1) {
return F_Lex_dline_dnat(a0, a1, a2, a3, a5);
} else if (nat_ge(s286, 2)) {
return F_Lex_dline_dflt(a0, a1, a2, a3, F_Lex_ddtext(a5, IMM(0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnum_dif(V *a) { (void)a; return F_Lex_dline_dnum_dif(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Lex_ddtext(V a0, V a1) {
top:;
V s287 = a0;
if ((s287) == IMM(0)) {
return C2(0, F_Str_drev(a1), IMM(0));
} else if (TAG(s287) == 1) {
return F_Lex_ddtext_dif(FLD(s287, 0), FLD(s287, 1), a1, F_Char_dis__digit(FLD(s287, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddtext(V *a) { (void)a; return F_Lex_ddtext(a[0], a[1]); }
static V F_Lex_ddtext_dif(V a0, V a1, V a2, V a3) {
top:;
V s288 = a3;
if ((s288) == IMM(1)) {
return F_Lex_ddtext(a1, C2(1, a0, a2));
} else if ((s288) == IMM(0)) {
return C2(0, F_Str_drev(a2), C2(1, a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddtext_dif(V *a) { (void)a; return F_Lex_ddtext_dif(a[0], a[1], a[2], a[3]); }
static V S290(void) { static V c; return STRC(c, "."); }
static V F_Lex_dline_dflt(V a0, V a1, V a2, V a3, V a4) {
top:;
V v289 = a4;
return F_Lex_dline(FLD(v289, 1), IMM(0), a1, C2(1, C3(0, C1(4, F_String_dappend(F_U32_dshow(a3), F_String_dappend(S290(), FLD(v289, 0)))), a0, a1), a2));
}
static V W_Lex_dline_dflt(V *a) { (void)a; return F_Lex_dline_dflt(a[0], a[1], a[2], a[3], a[4]); }
static V F_Lex_dline_dnat(V a0, V a1, V a2, V a3, V a4) {
top:;
V s291 = a4;
if ((s291) == IMM(0)) {
return F_Lex_dline(IMM(0), IMM(0), a1, C2(1, C3(0, C1(1, a3), a0, a1), a2));
} else if (TAG(s291) == 1) {
return F_Lex_dline_dnat_dif(a0, a1, a2, a3, FLD(s291, 0), FLD(s291, 1), F_U32_dis__eq(FLD(s291, 0), 43u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnat(V *a) { (void)a; return F_Lex_dline_dnat(a[0], a[1], a[2], a[3], a[4]); }
static V F_Lex_dline_dnat_dif(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s292 = a6;
if ((s292) == IMM(1)) {
return F_Lex_dline(a5, IMM(0), a1, C2(1, C3(0, C1(2, a3), a0, a1), a2));
} else if ((s292) == IMM(0)) {
return F_Lex_dline(C2(1, a4, a5), IMM(0), a1, C2(1, C3(0, C1(1, a3), a0, a1), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnat_dif(V *a) { (void)a; return F_Lex_dline_dnat_dif(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Lex_did(V a0, V a1) {
top:;
V s293 = a0;
if ((s293) == IMM(0)) {
return C2(0, F_Str_drev(a1), IMM(0));
} else if (TAG(s293) == 1) {
return F_Lex_did_dif(FLD(s293, 0), FLD(s293, 1), a1, F_Lex_dis__idc(FLD(s293, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_did(V *a) { (void)a; return F_Lex_did(a[0], a[1]); }
static V F_Lex_dis__idc(V a0) {
top:;
V v294 = F_Char_dto__u32(a0);
return F_Bool_dor(F_Char_dis__alpha(a0), F_Bool_dor(F_Char_dis__digit(a0), F_Bool_dor(F_U32_dis__eq(v294, 95u), F_U32_dis__eq(v294, 46u))));
}
static V W_Lex_dis__idc(V *a) { (void)a; return F_Lex_dis__idc(a[0]); }
static V F_Lex_did_dif(V a0, V a1, V a2, V a3) {
top:;
V s295 = a3;
if ((s295) == IMM(1)) {
return F_Lex_did(a1, C2(1, a0, a2));
} else if ((s295) == IMM(0)) {
return C2(0, F_Str_drev(a2), C2(1, a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_did_dif(V *a) { (void)a; return F_Lex_did_dif(a[0], a[1], a[2], a[3]); }
static V F_Lex_dline_did(V a0, V a1, V a2, V a3) {
top:;
V v296 = a3;
return F_Lex_dline(FLD(v296, 1), IMM(0), a1, C2(1, C3(0, C1(0, FLD(v296, 0)), a0, a1), a2));
}
static V W_Lex_dline_did(V *a) { (void)a; return F_Lex_dline_did(a[0], a[1], a[2], a[3]); }
static V F_List_dreverse(V a2) {
top:;
return F_List_dreverse_dgo(a2, IMM(0));
}
static V W_List_dreverse(V *a) { (void)a; return F_List_dreverse(a[2]); }
static V F_List_dreverse_dgo(V a2, V a3) {
top:;
V s297 = a2;
if ((s297) == IMM(0)) {
return a3;
} else if (TAG(s297) == 1) {
{ V t0 = FLD(s297, 1); V t1 = C2(1, FLD(s297, 0), a3); a2 = t0; a3 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_List_dreverse_dgo(V *a) { (void)a; return F_List_dreverse_dgo(a[2], a[3]); }
static V F_Lex_dindent(V a0) {
top:;
V s298 = a0;
if ((s298) == IMM(0)) {
return 0u;
} else if (TAG(s298) == 1) {
return F_Lex_dindent_dif(FLD(s298, 1), F_U32_dis__eq(FLD(s298, 0), 32u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dindent(V *a) { (void)a; return F_Lex_dindent(a[0]); }
static V F_Lex_dindent_dif(V a0, V a1) {
top:;
V s299 = a1;
if ((s299) == IMM(1)) {
return F_U32_dinc(F_Lex_dindent(a0));
} else if ((s299) == IMM(0)) {
return 0u;
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dindent_dif(V *a) { (void)a; return F_Lex_dindent_dif(a[0], a[1]); }
static V F_Lex_dlines_dput(V a0, V a1) {
top:;
V s300 = a0;
if ((FLD(s300, 2)) == IMM(0)) {
return a1;
} else if (TAG(FLD(s300, 2)) == 1) {
return C2(1, C3(0, FLD(s300, 0), FLD(s300, 1), C2(1, FLD(FLD(s300, 2), 0), FLD(FLD(s300, 2), 1))), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlines_dput(V *a) { (void)a; return F_Lex_dlines_dput(a[0], a[1]); }
static V F_Lay_dlines(V a0, V a1) {
top:;
V s301 = a0;
if ((s301) == IMM(0)) {
return a1;
} else if (TAG(s301) == 1) {
{ V t0 = FLD(s301, 1); V t1 = F_Lay_dline(FLD(s301, 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dlines(V *a) { (void)a; return F_Lay_dlines(a[0], a[1]); }
static V F_Lay_dline(V a0, V a1) {
top:;
V v302 = a0;
V v303 = a1;
return F_Lay_dline_dgo(FLD(v302, 0), FLD(v302, 1), FLD(v302, 2), CN(0, 5, (V[]){FLD(v303, 0), FLD(v303, 1), FLD(v303, 2), FLD(v303, 3), FLD(v303, 4)}), F_U32_dis__zero(FLD(v303, 1)));
}
static V W_Lay_dline(V *a) { (void)a; return F_Lay_dline(a[0], a[1]); }
static V F_Lay_dline_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s304 = a4;
if ((s304) == IMM(1)) {
return F_Lay_dtoks(a2, F_Lay_dstart(a3, a0, a1));
} else if ((s304) == IMM(0)) {
return F_Lay_dtoks(a2, a3);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dline_dgo(V *a) { (void)a; return F_Lay_dline_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V S308(void) { static V c; return STRC(c, ":"); }
static V F_Lay_dtoks(V a0, V a1) {
top:;
V s305 = a0;
if ((s305) == IMM(0)) {
return a1;
} else if (TAG(s305) == 1) {
V v306 = a1;
V v307 = F_U32_dadd(FLD(v306, 1), F_Lay_ddelta(FLD(FLD(s305, 0), 0)));
{ V t0 = FLD(s305, 1); V t1 = CN(0, 5, (V[]){C2(1, C3(0, FLD(FLD(s305, 0), 0), FLD(FLD(s305, 0), 1), FLD(FLD(s305, 0), 2)), FLD(v306, 0)), v307, F_Bool_dand(F_Lay_dis__sym(FLD(FLD(s305, 0), 0), S308()), F_U32_dis__zero(v307)), FLD(v306, 3), F_Lay_dis__op(FLD(FLD(s305, 0), 0))}); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dtoks(V *a) { (void)a; return F_Lay_dtoks(a[0], a[1]); }
static V S310(void) { static V c; return STRC(c, "->"); }
static V S311(void) { static V c; return STRC(c, "=>"); }
static V S312(void) { static V c; return STRC(c, "&"); }
static V S313(void) { static V c; return STRC(c, "|"); }
static V S314(void) { static V c; return STRC(c, "++"); }
static V S315(void) { static V c; return STRC(c, "<>"); }
static V S316(void) { static V c; return STRC(c, "&&"); }
static V S317(void) { static V c; return STRC(c, "||"); }
static V S318(void) { static V c; return STRC(c, "+"); }
static V S319(void) { static V c; return STRC(c, "*"); }
static V S320(void) { static V c; return STRC(c, ","); }
static V S321(void) { static V c; return STRC(c, "="); }
static V S322(void) { static V c; return STRC(c, "<-"); }
static V F_Lay_dis__op(V a0) {
top:;
V s309 = a0;
if (TAG(s309) == 7) {
return F_List_dcontains(mk_clo(W_String_deq, 2, 0, 0), C2(1, S310(), C2(1, S311(), C2(1, S312(), C2(1, S313(), C2(1, S314(), C2(1, S315(), C2(1, S316(), C2(1, S317(), C2(1, S318(), C2(1, S319(), C2(1, S320(), C2(1, S321(), C2(1, S322(), IMM(0)))))))))))))), FLD(s309, 0));
} else {
return IMM(0);
}
}
static V W_Lay_dis__op(V *a) { (void)a; return F_Lay_dis__op(a[0]); }
static V F_List_dcontains(V a1, V a2, V a3) {
top:;
V s323 = a2;
if ((s323) == IMM(0)) {
return IMM(0);
} else if (TAG(s323) == 1) {
return F_Bool_dor(apply(apply(a1, FLD(s323, 0)), a3), F_List_dcontains(a1, FLD(s323, 1), a3));
} else { bend_fail("incomplete match"); }
}
static V W_List_dcontains(V *a) { (void)a; return F_List_dcontains(a[1], a[2], a[3]); }
static V F_Lay_dis__sym(V a0, V a1) {
top:;
V s324 = a0;
if (TAG(s324) == 7) {
return F_Str_deq(FLD(s324, 0), a1);
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
static V S325(void) { static V c; return STRC(c, "("); }
static V S326(void) { static V c; return STRC(c, "["); }
static V S327(void) { static V c; return STRC(c, "{"); }
static V S328(void) { static V c; return STRC(c, ")"); }
static V S329(void) { static V c; return STRC(c, "]"); }
static V S330(void) { static V c; return STRC(c, "}"); }
static V F_Lay_ddelta(V a0) {
top:;
return F_Bool_dpick(F_Bool_dor(F_Lay_dis__sym(a0, S325()), F_Bool_dor(F_Lay_dis__sym(a0, S326()), F_Lay_dis__sym(a0, S327()))), 1u, F_Bool_dpick(F_Bool_dor(F_Lay_dis__sym(a0, S328()), F_Bool_dor(F_Lay_dis__sym(a0, S329()), F_Lay_dis__sym(a0, S330()))), 4294967295u, 0u));
}
static V W_Lay_ddelta(V *a) { (void)a; return F_Lay_ddelta(a[0]); }
static V F_Lay_dstart(V a0, V a1, V a2) {
top:;
V v331 = a0;
V v332 = F_Lay_dtop(FLD(v331, 3));
return F_Lay_dstart_dop(FLD(v331, 0), FLD(v331, 1), FLD(v331, 2), FLD(v331, 3), a1, a2, F_U32_dcmp(a1, v332), FLD(v331, 4));
}
static V W_Lay_dstart(V *a) { (void)a; return F_Lay_dstart(a[0], a[1], a[2]); }
static V F_Lay_dstart_dop(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s333 = a7;
if ((s333) == IMM(1)) {
return CN(0, 5, (V[]){a0, a1, a2, a3, IMM(0)});
} else if ((s333) == IMM(0)) {
return F_Lay_dstart_dgo(a0, a1, a2, a3, a4, a5, a6);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dstart_dop(V *a) { (void)a; return F_Lay_dstart_dop(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V F_Lay_dstart_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s334 = a6;
if ((s334) == IMM(2)) {
return F_Lay_dstart_dgt(a0, a1, a2, a3, a4, a5, a2);
} else if ((s334) == IMM(1)) {
return CN(0, 5, (V[]){C2(1, F_Lay_dtok(IMM(8), a5), a0), a1, a2, a3, IMM(0)});
} else if ((s334) == IMM(0)) {
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
V s335 = a0;
if ((s335) == IMM(0)) {
return C2(0, IMM(0), a2);
} else if (TAG(s335) == 1) {
return F_Lay_dpop_dif(FLD(s335, 0), FLD(s335, 1), a1, a2, a3, F_U32_dis__gt(FLD(s335, 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dpop(V *a) { (void)a; return F_Lay_dpop(a[0], a[1], a[2], a[3]); }
static V F_Lay_dpop_dif(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s336 = a5;
if ((s336) == IMM(1)) {
return F_Lay_dpop(a1, a2, C2(1, F_Lay_dtok(IMM(10), a4), a3), a4);
} else if ((s336) == IMM(0)) {
return C2(0, C2(1, a0, a1), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dpop_dif(V *a) { (void)a; return F_Lay_dpop_dif(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Lay_ddedent(V a0, V a1, V a2, V a3) {
top:;
V v337 = a3;
return CN(0, 5, (V[]){FLD(v337, 1), a0, a1, FLD(v337, 0), IMM(0)});
}
static V W_Lay_ddedent(V *a) { (void)a; return F_Lay_ddedent(a[0], a[1], a[2], a[3]); }
static V F_Lay_dstart_dgt(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s338 = a6;
if ((s338) == IMM(1)) {
return CN(0, 5, (V[]){C2(1, F_Lay_dtok(IMM(9), a5), a0), a1, a2, C2(1, a4, a3), IMM(0)});
} else if ((s338) == IMM(0)) {
return CN(0, 5, (V[]){a0, a1, a2, a3, IMM(0)});
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dstart_dgt(V *a) { (void)a; return F_Lay_dstart_dgt(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Lay_dtop(V a0) {
top:;
V s339 = a0;
if ((s339) == IMM(0)) {
return 0u;
} else if (TAG(s339) == 1) {
return FLD(s339, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dtop(V *a) { (void)a; return F_Lay_dtop(a[0]); }
static V F_Lay_dfinish(V a0) {
top:;
V v340 = a0;
return F_Lay_dfinish_dgo(F_Lay_dpop(FLD(v340, 3), 0u, C2(1, F_Lay_dtok(IMM(8), 0u), FLD(v340, 0)), 0u));
}
static V W_Lay_dfinish(V *a) { (void)a; return F_Lay_dfinish(a[0]); }
static V F_Lay_dfinish_dgo(V a0) {
top:;
V v341 = a0;
return F_List_dreverse(C2(1, F_Lay_dtok(IMM(11), 0u), FLD(v341, 1)));
}
static V W_Lay_dfinish_dgo(V *a) { (void)a; return F_Lay_dfinish_dgo(a[0]); }
static V L343(V *a) {
return F_P_ddecls_dgo(F_P_dstuck(F_P_dtok__kind(a[0])));
}
static V L342(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L343, 1, 0, 0));
}
static V F_P_ddecls(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L342, 1, 0, 0));
}
static V W_P_ddecls(V *a) { (void)a; return F_P_ddecls(); }
static V F_P_dtok__kind(V a0) {
top:;
V v344 = a0;
return FLD(v344, 0);
}
static V W_P_dtok__kind(V *a) { (void)a; return F_P_dtok__kind(a[0]); }
static V F_P_dstuck(V a0) {
top:;
V s345 = a0;
if (TAG(s345) == 12) {
return IMM(1);
} else if ((s345) == IMM(11)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dstuck(V *a) { (void)a; return F_P_dstuck(a[0]); }
static V L348(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L347(V *a) {
return F_Parser_dbind(F_P_ddecls(), mk_clo(L348, 2, 1, (V[]){a[0]}));
}
static V F_P_ddecls_dgo(V a0) {
top:;
V s346 = a0;
if ((s346) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s346) == IMM(0)) {
return F_Parser_dbind(F_P_ddecl(), mk_clo(L347, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddecls_dgo(V *a) { (void)a; return F_P_ddecls_dgo(a[0]); }
static V L349(V *a) {
return C2(0, a[0], a[1]);
}
static V F_Parser_dpure(V a1) {
top:;
return mk_clo(L349, 2, 1, (V[]){a1});
}
static V W_Parser_dpure(V *a) { (void)a; return F_Parser_dpure(a[1]); }
static V L350(V *a) {
return F_Parser_dgo(apply(a[1], a[4]), a[0]);
}
static V F_Parser_dbind(V a2, V a3) {
top:;
return mk_clo(L350, 5, 4, (V[]){a3, a2, 0, 0});
}
static V W_Parser_dbind(V *a) { (void)a; return F_Parser_dbind(a[2], a[3]); }
static V F_Parser_dgo(V a2, V a3) {
top:;
V v351 = a2;
return apply(apply(a3, FLD(v351, 0)), FLD(v351, 1));
}
static V W_Parser_dgo(V *a) { (void)a; return F_Parser_dgo(a[2], a[3]); }
static V S353(void) { static V c; return STRC(c, "@"); }
static V L352(V *a) {
return F_P_ddecl_dat(F_P_dtok__is(a[0], S353()), a[0]);
}
static V F_P_ddecl(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L352, 1, 0, 0));
}
static V W_P_ddecl(V *a) { (void)a; return F_P_ddecl(); }
static V F_P_dtok__is(V a0, V a1) {
top:;
V s354 = a0;
if (TAG(FLD(s354, 0)) == 7) {
return F_Str_deq(FLD(FLD(s354, 0), 0), a1);
} else {
return IMM(0);
}
}
static V W_P_dtok__is(V *a) { (void)a; return F_P_dtok__is(a[0], a[1]); }
static V L358(V *a) {
return F_P_ddecl();
}
static V L357(V *a) {
return F_Parser_dbind(F_P_dnls(), mk_clo(L358, 1, 0, 0));
}
static V L356(V *a) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L357, 1, 0, 0));
}
static V S359(void) { static V c; return STRC(c, "def"); }
static V S360(void) { static V c; return STRC(c, "type"); }
static V S361(void) { static V c; return STRC(c, "law"); }
static V S362(void) { static V c; return STRC(c, "import"); }
static V F_P_ddecl_dat(V a0, V a1) {
top:;
V s355 = a0;
if ((s355) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L356, 1, 0, 0));
} else if ((s355) == IMM(0)) {
return F_P_ddecl_dgo(F_P_dtok__which__id(a1, C2(1, S359(), C2(1, S360(), C2(1, S361(), C2(1, S362(), IMM(0)))))));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddecl_dat(V *a) { (void)a; return F_P_ddecl_dat(a[0], a[1]); }
static V F_P_dtok__which__id(V a0, V a1) {
top:;
V s363 = a0;
if (TAG(FLD(s363, 0)) == 0) {
return F_P_dwhich(FLD(FLD(s363, 0), 0), a1);
} else {
return 99u;
}
}
static V W_P_dtok__which__id(V *a) { (void)a; return F_P_dtok__which__id(a[0], a[1]); }
static V F_P_dwhich(V a0, V a1) {
top:;
V s364 = a1;
if ((s364) == IMM(0)) {
return 0u;
} else if (TAG(s364) == 1) {
return F_P_dwhich_dif(a0, FLD(s364, 1), F_String_deq(a0, FLD(s364, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dwhich(V *a) { (void)a; return F_P_dwhich(a[0], a[1]); }
static V F_P_dwhich_dif(V a0, V a1, V a2) {
top:;
V s365 = a2;
if ((s365) == IMM(1)) {
return 0u;
} else if ((s365) == IMM(0)) {
return nat_addk(F_P_dwhich(a0, a1), 1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dwhich_dif(V *a) { (void)a; return F_P_dwhich_dif(a[0], a[1], a[2]); }
static V S367(void) { static V c; return STRC(c, "expected a declaration"); }
static V S369(void) { static V c; return STRC(c, ""); }
static V S370(void) { static V c; return STRC(c, ""); }
static V L368(V *a) {
return F_Parser_dpure(C2(4, S369(), S370()));
}
static V F_P_ddecl_dgo(V a0) {
top:;
V s366 = a0;
if ((s366) == 0) {
return F_P_ddef();
} else if ((s366) == 1) {
return F_P_dtype();
} else if ((s366) == 2) {
return F_P_dlaw();
} else if ((s366) == 3) {
return F_P_dimport();
} else if (nat_ge(s366, 4)) {
return F_Parser_dbind(F_P_derr(S367()), mk_clo(L368, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddecl_dgo(V *a) { (void)a; return F_P_ddecl_dgo(a[0]); }
static V L371(V *a) {
return F_P_derr_dgo(a[0], a[1]);
}
static V F_P_derr(V a0) {
top:;
return mk_clo(L371, 2, 1, (V[]){a0});
}
static V W_P_derr(V *a) { (void)a; return F_P_derr(a[0]); }
static V S373(void) { static V c; return STRC(c, "line "); }
static V S374(void) { static V c; return STRC(c, ": "); }
static V S375(void) { static V c; return STRC(c, " (got '"); }
static V S376(void) { static V c; return STRC(c, "')"); }
static V S377(void) { static V c; return STRC(c, " (at end)"); }
static V F_P_derr_dgo(V a0, V a1) {
top:;
V s372 = a1;
if (TAG(s372) == 1 && TAG(FLD(FLD(s372, 0), 0)) == 12) {
return C2(0, IMM(0), C2(1, C3(0, C1(12, FLD(FLD(FLD(s372, 0), 0), 0)), FLD(FLD(s372, 0), 1), FLD(FLD(s372, 0), 2)), IMM(0)));
} else if (TAG(s372) == 1) {
return C2(0, IMM(0), C2(1, C3(0, C1(12, F_String_dappend(S373(), F_String_dappend(F_U32_dshow(FLD(FLD(s372, 0), 2)), F_String_dappend(S374(), F_String_dappend(a0, F_String_dappend(S375(), F_String_dappend(F_TK_dshow(FLD(FLD(s372, 0), 0)), S376()))))))), FLD(FLD(s372, 0), 1), FLD(FLD(s372, 0), 2)), IMM(0)));
} else if ((s372) == IMM(0)) {
return C2(0, IMM(0), C2(1, C3(0, C1(12, F_String_dappend(a0, S377())), IMM(1), 0u), IMM(0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_derr_dgo(V *a) { (void)a; return F_P_derr_dgo(a[0], a[1]); }
static V S379(void) { static V c; return STRC(c, "n"); }
static V S380(void) { static V c; return STRC(c, "n+"); }
static V S381(void) { static V c; return STRC(c, "'"); }
static V S382(void) { static V c; return STRC(c, "'"); }
static V S383(void) { static V c; return STRC(c, "\042"); }
static V S384(void) { static V c; return STRC(c, "\042"); }
static V S385(void) { static V c; return STRC(c, "<NL>\012"); }
static V S386(void) { static V c; return STRC(c, "<IN>"); }
static V S387(void) { static V c; return STRC(c, "<DE>"); }
static V S388(void) { static V c; return STRC(c, "<EOF>"); }
static V S389(void) { static V c; return STRC(c, "<ERR "); }
static V S390(void) { static V c; return STRC(c, ">"); }
static V F_TK_dshow(V a0) {
top:;
V s378 = a0;
if (TAG(s378) == 0) {
return FLD(s378, 0);
} else if (TAG(s378) == 1) {
return F_String_dappend(F_U32_dshow(FLD(s378, 0)), S379());
} else if (TAG(s378) == 2) {
return F_String_dappend(F_U32_dshow(FLD(s378, 0)), S380());
} else if (TAG(s378) == 3) {
return F_U32_dshow(FLD(s378, 0));
} else if (TAG(s378) == 4) {
return FLD(s378, 0);
} else if (TAG(s378) == 5) {
return F_String_dappend(S381(), F_String_dappend(F_U32_dshow(FLD(s378, 0)), S382()));
} else if (TAG(s378) == 6) {
return F_String_dappend(S383(), F_String_dappend(FLD(s378, 0), S384()));
} else if (TAG(s378) == 7) {
return FLD(s378, 0);
} else if ((s378) == IMM(8)) {
return S385();
} else if ((s378) == IMM(9)) {
return S386();
} else if ((s378) == IMM(10)) {
return S387();
} else if ((s378) == IMM(11)) {
return S388();
} else if (TAG(s378) == 12) {
return F_String_dappend(S389(), F_String_dappend(FLD(s378, 0), S390()));
} else { bend_fail("incomplete match"); }
}
static V W_TK_dshow(V *a) { (void)a; return F_TK_dshow(a[0]); }
static V S394(void) { static V c; return STRC(c, "as"); }
static V L396(V *a) {
return F_Parser_dpure(C2(4, a[1], a[0]));
}
static V L395(V *a) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L396, 3, 2, (V[]){a[1], a[0]}));
}
static V L393(V *a) {
return F_Parser_dbind(F_P_dimport_dalias(F_P_dtok__is__id(a[1], S394())), mk_clo(L395, 2, 1, (V[]){a[0]}));
}
static V L392(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L393, 2, 1, (V[]){a[0]}));
}
static V L391(V *a) {
return F_Parser_dbind(F_P_dimport_dpath(), mk_clo(L392, 1, 0, 0));
}
static V F_P_dimport(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L391, 1, 0, 0));
}
static V W_P_dimport(V *a) { (void)a; return F_P_dimport(); }
static V L397(V *a) {
return C2(0, IMM(0), F_P_dskip__line_dgo(a[0]));
}
static V F_P_dskip__line(void) {
top:;
return mk_clo(L397, 1, 0, 0);
}
static V W_P_dskip__line(V *a) { (void)a; return F_P_dskip__line(); }
static V F_P_dskip__line_dgo(V a0) {
top:;
V s398 = a0;
if ((s398) == IMM(0)) {
return IMM(0);
} else if (TAG(s398) == 1 && (FLD(FLD(s398, 0), 0)) == IMM(8)) {
return C2(1, C3(0, IMM(8), FLD(FLD(s398, 0), 1), FLD(FLD(s398, 0), 2)), FLD(s398, 1));
} else if (TAG(s398) == 1 && (FLD(FLD(s398, 0), 0)) == IMM(10)) {
return C2(1, C3(0, IMM(10), FLD(FLD(s398, 0), 1), FLD(FLD(s398, 0), 2)), FLD(s398, 1));
} else if (TAG(s398) == 1 && (FLD(FLD(s398, 0), 0)) == IMM(11)) {
return C2(1, C3(0, IMM(11), FLD(FLD(s398, 0), 1), FLD(FLD(s398, 0), 2)), FLD(s398, 1));
} else if (TAG(s398) == 1 && TAG(FLD(FLD(s398, 0), 0)) == 12) {
return C2(1, C3(0, C1(12, FLD(FLD(FLD(s398, 0), 0), 0)), FLD(FLD(s398, 0), 1), FLD(FLD(s398, 0), 2)), FLD(s398, 1));
} else if (TAG(s398) == 1 && (FLD(FLD(s398, 0), 0)) == IMM(9)) {
return F_P_dskip__block_dgo(FLD(s398, 1), 1u);
} else if (TAG(s398) == 1) {
{ V t0 = FLD(s398, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__line_dgo(V *a) { (void)a; return F_P_dskip__line_dgo(a[0]); }
static V F_P_dskip__block_dgo(V a0, V a1) {
top:;
V s399 = a0;
if ((s399) == IMM(0)) {
return IMM(0);
} else if (TAG(s399) == 1 && (FLD(FLD(s399, 0), 0)) == IMM(9)) {
{ V t0 = FLD(s399, 1); V t1 = F_U32_dinc(a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s399) == 1 && (FLD(FLD(s399, 0), 0)) == IMM(10)) {
return F_P_dskip__block_dde(FLD(s399, 1), a1, F_U32_dis__eq(a1, 1u));
} else if (TAG(s399) == 1 && (FLD(FLD(s399, 0), 0)) == IMM(11)) {
return C2(1, C3(0, IMM(11), FLD(FLD(s399, 0), 1), FLD(FLD(s399, 0), 2)), FLD(s399, 1));
} else if (TAG(s399) == 1) {
{ V t0 = FLD(s399, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__block_dgo(V *a) { (void)a; return F_P_dskip__block_dgo(a[0], a[1]); }
static V F_P_dskip__block_dde(V a0, V a1, V a2) {
top:;
V s400 = a2;
if ((s400) == IMM(1)) {
return a0;
} else if ((s400) == IMM(0)) {
return F_P_dskip__block_dgo(a0, F_U32_dsub(a1, 1u));
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__block_dde(V *a) { (void)a; return F_P_dskip__block_dde(a[0], a[1], a[2]); }
static V F_P_dtok__is__id(V a0, V a1) {
top:;
V s401 = a0;
if (TAG(FLD(s401, 0)) == 0) {
return F_Str_deq(FLD(FLD(s401, 0), 0), a1);
} else {
return IMM(0);
}
}
static V W_P_dtok__is__id(V *a) { (void)a; return F_P_dtok__is__id(a[0], a[1]); }
static V L403(V *a) {
return F_P_dident();
}
static V S404(void) { static V c; return STRC(c, ""); }
static V F_P_dimport_dalias(V a0) {
top:;
V s402 = a0;
if ((s402) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L403, 1, 0, 0));
} else if ((s402) == IMM(0)) {
return F_Parser_dpure(S404());
} else { bend_fail("incomplete match"); }
}
static V W_P_dimport_dalias(V *a) { (void)a; return F_P_dimport_dalias(a[0]); }
static V L405(V *a) {
return F_P_dident_dk(F_P_dtok__kind(a[0]));
}
static V F_P_dident(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L405, 1, 0, 0));
}
static V W_P_dident(V *a) { (void)a; return F_P_dident(); }
static V L407(V *a) {
return F_Parser_dpure(a[0]);
}
static V S408(void) { static V c; return STRC(c, "expected an identifier"); }
static V S410(void) { static V c; return STRC(c, ""); }
static V L409(V *a) {
return F_Parser_dpure(S410());
}
static V F_P_dident_dk(V a0) {
top:;
V s406 = a0;
if (TAG(s406) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L407, 2, 1, (V[]){FLD(s406, 0)}));
} else {
return F_Parser_dbind(F_P_derr(S408()), mk_clo(L409, 1, 0, 0));
}
}
static V W_P_dident_dk(V *a) { (void)a; return F_P_dident_dk(a[0]); }
static V L411(V *a) {
return F_P_dskip_dgo(a[0]);
}
static V F_P_dskip(void) {
top:;
return mk_clo(L411, 1, 0, 0);
}
static V W_P_dskip(V *a) { (void)a; return F_P_dskip(); }
static V F_P_dskip_dgo(V a0) {
top:;
V s412 = a0;
if ((s412) == IMM(0)) {
return C2(0, IMM(0), IMM(0));
} else if (TAG(s412) == 1) {
return F_P_dskip_dif(C3(0, FLD(FLD(s412, 0), 0), FLD(FLD(s412, 0), 1), FLD(FLD(s412, 0), 2)), FLD(s412, 1), F_P_dstuck(FLD(FLD(s412, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip_dgo(V *a) { (void)a; return F_P_dskip_dgo(a[0]); }
static V F_P_dskip_dif(V a0, V a1, V a2) {
top:;
V s413 = a2;
if ((s413) == IMM(1)) {
return C2(0, IMM(0), C2(1, a0, a1));
} else if ((s413) == IMM(0)) {
return C2(0, IMM(0), a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip_dif(V *a) { (void)a; return F_P_dskip_dif(a[0], a[1], a[2]); }
static V L414(V *a) {
return F_P_dpeek_dgo(a[0]);
}
static V F_P_dpeek(void) {
top:;
return mk_clo(L414, 1, 0, 0);
}
static V W_P_dpeek(V *a) { (void)a; return F_P_dpeek(); }
static V F_P_dpeek_dgo(V a0) {
top:;
V s415 = a0;
if ((s415) == IMM(0)) {
return C2(0, F_P_deof__tok(), IMM(0));
} else if (TAG(s415) == 1) {
return C2(0, FLD(s415, 0), C2(1, FLD(s415, 0), FLD(s415, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpeek_dgo(V *a) { (void)a; return F_P_dpeek_dgo(a[0]); }
static V F_P_deof__tok(void) {
top:;
return C3(0, IMM(11), IMM(1), 0u);
}
static V W_P_deof__tok(V *a) { (void)a; return F_P_deof__tok(); }
static V L416(V *a) {
return F_P_dimport_dpath_dgo(a[0]);
}
static V F_P_dimport_dpath(void) {
top:;
return mk_clo(L416, 1, 0, 0);
}
static V W_P_dimport_dpath(V *a) { (void)a; return F_P_dimport_dpath(); }
static V S418(void) { static V c; return STRC(c, "as"); }
static V S419(void) { static V c; return STRC(c, ""); }
static V F_P_dimport_dpath_dgo(V a0) {
top:;
V s417 = a0;
if (TAG(s417) == 1 && TAG(FLD(FLD(s417, 0), 0)) == 0) {
return F_P_dimport_dpath_did(FLD(FLD(FLD(s417, 0), 0), 0), FLD(FLD(s417, 0), 1), FLD(FLD(s417, 0), 2), FLD(s417, 1), F_Str_deq(FLD(FLD(FLD(s417, 0), 0), 0), S418()));
} else if (TAG(s417) == 1 && TAG(FLD(FLD(s417, 0), 0)) == 7) {
return F_P_dimport_dpath_dcat(FLD(FLD(FLD(s417, 0), 0), 0), F_P_dimport_dpath_dgo(FLD(s417, 1)));
} else if (TAG(s417) == 1 && TAG(FLD(FLD(s417, 0), 0)) == 3) {
return F_P_dimport_dpath_dcat(F_U32_dshow(FLD(FLD(FLD(s417, 0), 0), 0)), F_P_dimport_dpath_dgo(FLD(s417, 1)));
} else {
return C2(0, S419(), s417);
}
}
static V W_P_dimport_dpath_dgo(V *a) { (void)a; return F_P_dimport_dpath_dgo(a[0]); }
static V F_P_dimport_dpath_dcat(V a0, V a1) {
top:;
V v420 = a1;
return C2(0, F_String_dappend(a0, FLD(v420, 0)), FLD(v420, 1));
}
static V W_P_dimport_dpath_dcat(V *a) { (void)a; return F_P_dimport_dpath_dcat(a[0], a[1]); }
static V S422(void) { static V c; return STRC(c, ""); }
static V F_P_dimport_dpath_did(V a0, V a1, V a2, V a3, V a4) {
top:;
V s421 = a4;
if ((s421) == IMM(1)) {
return C2(0, S422(), C2(1, C3(0, C1(0, a0), a1, a2), a3));
} else if ((s421) == IMM(0)) {
return F_P_dimport_dpath_dcat(a0, F_P_dimport_dpath_dgo(a3));
} else { bend_fail("incomplete match"); }
}
static V W_P_dimport_dpath_did(V *a) { (void)a; return F_P_dimport_dpath_did(a[0], a[1], a[2], a[3], a[4]); }
static V S425(void) { static V c; return STRC(c, ":"); }
static V L428(V *a) {
return F_Parser_dpure(C2(2, a[0], a[1]));
}
static V L427(V *a) {
return F_Parser_dbind(F_P_dlaw_dlines(), mk_clo(L428, 2, 1, (V[]){a[0]}));
}
static V L426(V *a) {
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L427, 2, 1, (V[]){a[0]}));
}
static V L424(V *a) {
return F_Parser_dbind(F_P_dexpect(S425()), mk_clo(L426, 2, 1, (V[]){a[0]}));
}
static V L423(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L424, 1, 0, 0));
}
static V F_P_dlaw(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L423, 1, 0, 0));
}
static V W_P_dlaw(V *a) { (void)a; return F_P_dlaw(); }
static V L430(V *a) {
return F_P_dlaw_dgo(a[0], F_Bool_dpick(F_P_dis__de(a[0]), 0u, F_Bool_dpick(F_P_dstuck(F_P_dtok__kind(a[0])), 1u, 2u)));
}
static V L429(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L430, 1, 0, 0));
}
static V F_P_dlaw_dlines(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L429, 1, 0, 0));
}
static V W_P_dlaw_dlines(V *a) { (void)a; return F_P_dlaw_dlines(); }
static V F_P_dis__de(V a0) {
top:;
V s431 = a0;
if ((FLD(s431, 0)) == IMM(10)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dis__de(V *a) { (void)a; return F_P_dis__de(a[0]); }
static V L433(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S434(void) { static V c; return STRC(c, "for"); }
static V F_P_dlaw_dgo(V a0, V a1) {
top:;
V s432 = a1;
if ((s432) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L433, 1, 0, 0));
} else if ((s432) == 1) {
return F_Parser_dpure(IMM(0));
} else if (nat_ge(s432, 2)) {
return F_P_dlaw_dline(F_P_dtok__which__id(a0, C2(1, S434(), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlaw_dgo(V *a) { (void)a; return F_P_dlaw_dgo(a[0], a[1]); }
static V L439(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L438(V *a) {
return F_Parser_dbind(F_P_dlaw_dlines(), mk_clo(L439, 2, 1, (V[]){a[0]}));
}
static V L437(V *a) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L438, 2, 1, (V[]){a[0]}));
}
static V L436(V *a) {
return F_Parser_dbind(F_P_dparam(), mk_clo(L437, 1, 0, 0));
}
static V L440(V *a) {
return F_P_dlaw_dlines();
}
static V F_P_dlaw_dline(V a0) {
top:;
V s435 = a0;
if ((s435) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L436, 1, 0, 0));
} else if (nat_ge(s435, 1)) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L440, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlaw_dline(V *a) { (void)a; return F_P_dlaw_dline(a[0]); }
static V S446(void) { static V c; return STRC(c, ":"); }
static V L445(V *a) {
return F_P_dparam_dty(a[1], a[0], F_P_dtok__is(a[2], S446()));
}
static V L444(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L445, 3, 2, (V[]){a[0], a[1]}));
}
static V L443(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L444, 2, 1, (V[]){a[0]}));
}
static V L442(V *a) {
return F_Parser_dbind(F_P_dparam_dskip__mode(a[0]), mk_clo(L443, 2, 1, (V[]){a[0]}));
}
static V L441(V *a) {
return F_Parser_dbind(F_Parser_dpure(F_P_dparam_dmode(a[0])), mk_clo(L442, 1, 0, 0));
}
static V F_P_dparam(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L441, 1, 0, 0));
}
static V W_P_dparam(V *a) { (void)a; return F_P_dparam(); }
static V L449(V *a) {
return F_Parser_dpure(C3(0, a[1], a[0], F_P_dhead(a[2])));
}
static V L448(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L449, 3, 2, (V[]){a[0], a[1]}));
}
static V S450(void) { static V c; return STRC(c, ""); }
static V F_P_dparam_dty(V a0, V a1, V a2) {
top:;
V s447 = a2;
if ((s447) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L448, 3, 2, (V[]){a1, a0}));
} else if ((s447) == IMM(0)) {
return F_Parser_dpure(C3(0, a0, F_Bool_dpick(F_U32_dis__zero(a1), 4u, a1), S450()));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparam_dty(V *a) { (void)a; return F_P_dparam_dty(a[0], a[1], a[2]); }
static V S452(void) { static V c; return STRC(c, ""); }
static V F_P_dhead(V a0) {
top:;
V s451 = a0;
if (TAG(s451) == 0) {
return FLD(s451, 0);
} else if (TAG(s451) == 5 && TAG(FLD(s451, 0)) == 0) {
return FLD(FLD(s451, 0), 0);
} else if (TAG(s451) == 14) {
return FLD(s451, 0);
} else {
return S452();
}
}
static V W_P_dhead(V *a) { (void)a; return F_P_dhead(a[0]); }
static V F_P_dexpr(void) {
top:;
return F_P_dbin(1u);
}
static V W_P_dexpr(V *a) { (void)a; return F_P_dexpr(); }
static V L453(V *a) {
return F_P_dbin_dloop(a[0], a[1]);
}
static V F_P_dbin(V a0) {
top:;
return F_Parser_dbind(F_P_dterm(), mk_clo(L453, 2, 1, (V[]){a0}));
}
static V W_P_dbin(V *a) { (void)a; return F_P_dbin(a[0]); }
static V L454(V *a) {
return F_P_dbin_dloop_dop(a[1], a[0], F_P_dtok__op(a[2]));
}
static V F_P_dbin_dloop(V a0, V a1) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L454, 3, 2, (V[]){a1, a0}));
}
static V W_P_dbin_dloop(V *a) { (void)a; return F_P_dbin_dloop(a[0], a[1]); }
static V S456(void) { static V c; return STRC(c, ""); }
static V F_P_dtok__op(V a0) {
top:;
V s455 = a0;
if (TAG(FLD(s455, 0)) == 7 && (FLD(s455, 1)) == IMM(1)) {
return F_P_dop__find(FLD(FLD(s455, 0), 0), F_P_dops());
} else {
return C3(0, S456(), 0u, IMM(0));
}
}
static V W_P_dtok__op(V *a) { (void)a; return F_P_dtok__op(a[0]); }
static V S457(void) { static V c; return STRC(c, "->"); }
static V S458(void) { static V c; return STRC(c, "|"); }
static V S459(void) { static V c; return STRC(c, "&"); }
static V S460(void) { static V c; return STRC(c, "<&>"); }
static V S461(void) { static V c; return STRC(c, "||"); }
static V S462(void) { static V c; return STRC(c, "&&"); }
static V S463(void) { static V c; return STRC(c, "<>"); }
static V S464(void) { static V c; return STRC(c, "++"); }
static V S465(void) { static V c; return STRC(c, "<"); }
static V S466(void) { static V c; return STRC(c, "<="); }
static V S467(void) { static V c; return STRC(c, ">"); }
static V S468(void) { static V c; return STRC(c, ">="); }
static V S469(void) { static V c; return STRC(c, ".|."); }
static V S470(void) { static V c; return STRC(c, ".^."); }
static V S471(void) { static V c; return STRC(c, ".&."); }
static V S472(void) { static V c; return STRC(c, "<<"); }
static V S473(void) { static V c; return STRC(c, ">>"); }
static V S474(void) { static V c; return STRC(c, "+"); }
static V S475(void) { static V c; return STRC(c, "-"); }
static V S476(void) { static V c; return STRC(c, "*"); }
static V S477(void) { static V c; return STRC(c, "/"); }
static V S478(void) { static V c; return STRC(c, "%"); }
static V F_P_dops(void) {
top:;
return C2(1, C3(0, S457(), 1u, IMM(1)), C2(1, C3(0, S458(), 2u, IMM(1)), C2(1, C3(0, S459(), 3u, IMM(1)), C2(1, C3(0, S460(), 3u, IMM(1)), C2(1, C3(0, S461(), 4u, IMM(0)), C2(1, C3(0, S462(), 5u, IMM(0)), C2(1, C3(0, S463(), 6u, IMM(1)), C2(1, C3(0, S464(), 6u, IMM(1)), C2(1, C3(0, S465(), 7u, IMM(0)), C2(1, C3(0, S466(), 7u, IMM(0)), C2(1, C3(0, S467(), 7u, IMM(0)), C2(1, C3(0, S468(), 7u, IMM(0)), C2(1, C3(0, S469(), 8u, IMM(0)), C2(1, C3(0, S470(), 9u, IMM(0)), C2(1, C3(0, S471(), 10u, IMM(0)), C2(1, C3(0, S472(), 11u, IMM(0)), C2(1, C3(0, S473(), 11u, IMM(0)), C2(1, C3(0, S474(), 12u, IMM(0)), C2(1, C3(0, S475(), 12u, IMM(0)), C2(1, C3(0, S476(), 13u, IMM(0)), C2(1, C3(0, S477(), 13u, IMM(0)), C2(1, C3(0, S478(), 13u, IMM(0)), IMM(0)))))))))))))))))))))));
}
static V W_P_dops(V *a) { (void)a; return F_P_dops(); }
static V S480(void) { static V c; return STRC(c, ""); }
static V F_P_dop__find(V a0, V a1) {
top:;
V s479 = a1;
if ((s479) == IMM(0)) {
return C3(0, S480(), 0u, IMM(0));
} else if (TAG(s479) == 1) {
return F_P_dop__find_dif(a0, FLD(s479, 1), C3(0, FLD(FLD(s479, 0), 0), FLD(FLD(s479, 0), 1), FLD(FLD(s479, 0), 2)), F_String_deq(a0, FLD(FLD(s479, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dop__find(V *a) { (void)a; return F_P_dop__find(a[0], a[1]); }
static V F_P_dop__find_dif(V a0, V a1, V a2, V a3) {
top:;
V s481 = a3;
if ((s481) == IMM(1)) {
return a2;
} else if ((s481) == IMM(0)) {
return F_P_dop__find(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dop__find_dif(V *a) { (void)a; return F_P_dop__find_dif(a[0], a[1], a[2], a[3]); }
static V F_P_dbin_dloop_dop(V a0, V a1, V a2) {
top:;
V v482 = a2;
return F_P_dbin_dloop_dgo(a0, a1, FLD(v482, 0), FLD(v482, 1), FLD(v482, 2), F_Bool_dand(F_U32_dis__ne(FLD(v482, 1), 0u), F_U32_dis__ge(FLD(v482, 1), a0)));
}
static V W_P_dbin_dloop_dop(V *a) { (void)a; return F_P_dbin_dloop_dop(a[0], a[1], a[2]); }
static V L485(V *a) {
return F_P_dbin_dloop(a[2], F_P_dmk__bin(a[1], a[0], a[3]));
}
static V L484(V *a) {
return F_Parser_dbind(F_P_dbin(F_Bool_dpick(a[4], a[3], F_U32_dinc(a[3]))), mk_clo(L485, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_P_dbin_dloop_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s483 = a5;
if ((s483) == IMM(0)) {
return F_Parser_dpure(a1);
} else if ((s483) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L484, 6, 5, (V[]){a1, a2, a0, a3, a4}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbin_dloop_dgo(V *a) { (void)a; return F_P_dbin_dloop_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S486(void) { static V c; return STRC(c, "->"); }
static V S487(void) { static V c; return STRC(c, "|"); }
static V S488(void) { static V c; return STRC(c, "&"); }
static V S489(void) { static V c; return STRC(c, "<&>"); }
static V S490(void) { static V c; return STRC(c, "||"); }
static V S491(void) { static V c; return STRC(c, "&&"); }
static V S492(void) { static V c; return STRC(c, "<>"); }
static V S493(void) { static V c; return STRC(c, "++"); }
static V F_P_dmk__bin(V a0, V a1, V a2) {
top:;
return F_P_dmk__bin_dgo(a0, a1, a2, F_P_dwhich(a0, C2(1, S486(), C2(1, S487(), C2(1, S488(), C2(1, S489(), C2(1, S490(), C2(1, S491(), C2(1, S492(), C2(1, S493(), IMM(0)))))))))));
}
static V W_P_dmk__bin(V *a) { (void)a; return F_P_dmk__bin(a[0], a[1], a[2]); }
static V S495(void) { static V c; return STRC(c, "->"); }
static V S496(void) { static V c; return STRC(c, "|"); }
static V S497(void) { static V c; return STRC(c, "&"); }
static V S498(void) { static V c; return STRC(c, "#q"); }
static V S499(void) { static V c; return STRC(c, "Bool.or"); }
static V S500(void) { static V c; return STRC(c, "Bool.and"); }
static V S501(void) { static V c; return STRC(c, "Con"); }
static V S502(void) { static V c; return STRC(c, "String.append"); }
static V F_P_dmk__bin_dgo(V a0, V a1, V a2, V a3) {
top:;
V s494 = a3;
if ((s494) == 0) {
return C2(14, S495(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s494) == 1) {
return C2(14, S496(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s494) == 2) {
return C2(14, S497(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s494) == 3) {
return C2(14, S498(), IMM(0));
} else if ((s494) == 4) {
return C2(5, C1(0, S499()), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s494) == 5) {
return C2(5, C1(0, S500()), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s494) == 6) {
return C2(6, S501(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s494) == 7) {
return C2(5, C1(0, S502()), C2(1, a1, C2(1, a2, IMM(0))));
} else if (nat_ge(s494, 8)) {
return C3(12, a0, a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_P_dmk__bin_dgo(V *a) { (void)a; return F_P_dmk__bin_dgo(a[0], a[1], a[2], a[3]); }
static V L503(V *a) {
return F_P_dpostfix(a[0]);
}
static V F_P_dterm(void) {
top:;
return F_Parser_dbind(F_P_dprimary(), mk_clo(L503, 1, 0, 0));
}
static V W_P_dterm(V *a) { (void)a; return F_P_dterm(); }
static V L504(V *a) {
return F_P_dpostfix_dt(a[0], a[1]);
}
static V F_P_dpostfix(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L504, 2, 1, (V[]){a0}));
}
static V W_P_dpostfix(V *a) { (void)a; return F_P_dpostfix(a[0]); }
static V S505(void) { static V c; return STRC(c, "("); }
static V S506(void) { static V c; return STRC(c, "!"); }
static V S507(void) { static V c; return STRC(c, "["); }
static V F_P_dpostfix_dt(V a0, V a1) {
top:;
return F_P_dpostfix_dk(a0, F_Bool_dpick(F_P_dtok__sp(a1), 9u, F_P_dtok__which(a1, C2(1, S505(), C2(1, S506(), C2(1, S507(), IMM(0)))))));
}
static V W_P_dpostfix_dt(V *a) { (void)a; return F_P_dpostfix_dt(a[0], a[1]); }
static V F_P_dtok__which(V a0, V a1) {
top:;
V s508 = a0;
if (TAG(FLD(s508, 0)) == 7) {
return F_P_dwhich(FLD(FLD(s508, 0), 0), a1);
} else {
return 99u;
}
}
static V W_P_dtok__which(V *a) { (void)a; return F_P_dtok__which(a[0], a[1]); }
static V F_P_dtok__sp(V a0) {
top:;
V v509 = a0;
return FLD(v509, 1);
}
static V W_P_dtok__sp(V *a) { (void)a; return F_P_dtok__sp(a[0]); }
static V S512(void) { static V c; return STRC(c, ")"); }
static V L513(V *a) {
return F_P_dpostfix(C2(5, a[0], a[1]));
}
static V L511(V *a) {
return F_Parser_dbind(F_P_dlist(S512()), mk_clo(L513, 2, 1, (V[]){a[0]}));
}
static V L514(V *a) {
return F_P_dpostfix(a[0]);
}
static V S517(void) { static V c; return STRC(c, "]"); }
static V S519(void) { static V c; return STRC(c, "Array.get"); }
static V S520(void) { static V c; return STRC(c, "U32"); }
static V L518(V *a) {
return F_P_dpostfix(C2(5, C1(0, S519()), C2(1, C2(14, S520(), IMM(0)), C2(1, a[1], C2(1, a[0], IMM(0))))));
}
static V L516(V *a) {
return F_Parser_dbind(F_P_dexpect(S517()), mk_clo(L518, 3, 2, (V[]){a[1], a[0]}));
}
static V L515(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L516, 2, 1, (V[]){a[0]}));
}
static V F_P_dpostfix_dk(V a0, V a1) {
top:;
V s510 = a1;
if ((s510) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L511, 2, 1, (V[]){a0}));
} else if ((s510) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L514, 2, 1, (V[]){a0}));
} else if ((s510) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L515, 2, 1, (V[]){a0}));
} else if (nat_ge(s510, 3)) {
return F_Parser_dpure(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dpostfix_dk(V *a) { (void)a; return F_P_dpostfix_dk(a[0], a[1]); }
static V L521(V *a) {
return F_P_dexpect_dif(a[0], F_P_dtok__is(a[1], a[0]));
}
static V F_P_dexpect(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L521, 2, 1, (V[]){a0}));
}
static V W_P_dexpect(V *a) { (void)a; return F_P_dexpect(a[0]); }
static V S523(void) { static V c; return STRC(c, "expected '"); }
static V S524(void) { static V c; return STRC(c, "'"); }
static V F_P_dexpect_dif(V a0, V a1) {
top:;
V s522 = a1;
if ((s522) == IMM(1)) {
return F_P_dskip();
} else if ((s522) == IMM(0)) {
return F_P_derr(F_String_dappend(S523(), F_String_dappend(a0, S524())));
} else { bend_fail("incomplete match"); }
}
static V W_P_dexpect_dif(V *a) { (void)a; return F_P_dexpect_dif(a[0], a[1]); }
static V L525(V *a) {
return F_P_dlist_dstuck(a[0], a[1], F_P_dstuck(F_P_dtok__kind(a[1])));
}
static V F_P_dlist(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L525, 2, 1, (V[]){a0}));
}
static V W_P_dlist(V *a) { (void)a; return F_P_dlist(a[0]); }
static V S527(void) { static V c; return STRC(c, "unterminated list"); }
static V L528(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dlist_dstuck(V a0, V a1, V a2) {
top:;
V s526 = a2;
if ((s526) == IMM(1)) {
return F_Parser_dbind(F_P_derr(S527()), mk_clo(L528, 1, 0, 0));
} else if ((s526) == IMM(0)) {
return F_P_dlist_dgo(a0, F_P_dtok__is(a1, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlist_dstuck(V *a) { (void)a; return F_P_dlist_dstuck(a[0], a[1], a[2]); }
static V L530(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dlist_dgo(V a0, V a1) {
top:;
V s529 = a1;
if ((s529) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L530, 1, 0, 0));
} else if ((s529) == IMM(0)) {
return F_P_dlist_ditem(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dlist_dgo(V *a) { (void)a; return F_P_dlist_dgo(a[0], a[1]); }
static V S532(void) { static V c; return STRC(c, ","); }
static V L534(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L533(V *a) {
return F_Parser_dbind(F_P_dlist_dmore(a[1], a[2]), mk_clo(L534, 2, 1, (V[]){a[0]}));
}
static V L531(V *a) {
return F_Parser_dbind(F_P_deat(S532()), mk_clo(L533, 3, 2, (V[]){a[1], a[0]}));
}
static V F_P_dlist_ditem(V a0) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L531, 2, 1, (V[]){a0}));
}
static V W_P_dlist_ditem(V *a) { (void)a; return F_P_dlist_ditem(a[0]); }
static V L536(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dlist_dmore(V a0, V a1) {
top:;
V s535 = a1;
if ((s535) == IMM(1)) {
return F_P_dlist(a0);
} else if ((s535) == IMM(0)) {
return F_Parser_dbind(F_P_dexpect(a0), mk_clo(L536, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlist_dmore(V *a) { (void)a; return F_P_dlist_dmore(a[0], a[1]); }
static V L537(V *a) {
return F_P_deat_dif(F_P_dtok__is(a[1], a[0]));
}
static V F_P_deat(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L537, 2, 1, (V[]){a0}));
}
static V W_P_deat(V *a) { (void)a; return F_P_deat(a[0]); }
static V L539(V *a) {
return F_Parser_dpure(IMM(1));
}
static V F_P_deat_dif(V a0) {
top:;
V s538 = a0;
if ((s538) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L539, 1, 0, 0));
} else if ((s538) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_deat_dif(V *a) { (void)a; return F_P_deat_dif(a[0]); }
static V L540(V *a) {
return F_P_dprimary_dk(F_P_dtok__kind(a[0]));
}
static V F_P_dprimary(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L540, 1, 0, 0));
}
static V W_P_dprimary(V *a) { (void)a; return F_P_dprimary(); }
static V L543(V *a) {
return F_P_dafter__id(a[0], a[1]);
}
static V L542(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L543, 2, 1, (V[]){a[0]}));
}
static V L544(V *a) {
return F_Parser_dpure(C1(1, a[0]));
}
static V L545(V *a) {
return F_Parser_dpure(C1(2, a[0]));
}
static V L547(V *a) {
return F_Parser_dpure(C2(11, a[0], a[1]));
}
static V L546(V *a) {
return F_Parser_dbind(F_P_dterm(), mk_clo(L547, 2, 1, (V[]){a[0]}));
}
static V L548(V *a) {
return F_Parser_dpure(C1(3, a[0]));
}
static V L549(V *a) {
return F_Parser_dpure(C1(1, a[0]));
}
static V L550(V *a) {
return F_Parser_dpure(C1(4, a[0]));
}
static V S551(void) { static V c; return STRC(c, "("); }
static V S552(void) { static V c; return STRC(c, "["); }
static V S553(void) { static V c; return STRC(c, "{"); }
static V S554(void) { static V c; return STRC(c, "~"); }
static V S555(void) { static V c; return STRC(c, "+"); }
static V S556(void) { static V c; return STRC(c, "-"); }
static V S557(void) { static V c; return STRC(c, "@"); }
static V S558(void) { static V c; return STRC(c, "&"); }
static V S559(void) { static V c; return STRC(c, "\077"); }
static V S560(void) { static V c; return STRC(c, "expected an expression"); }
static V S562(void) { static V c; return STRC(c, ""); }
static V L561(V *a) {
return F_Parser_dpure(C1(15, S562()));
}
static V F_P_dprimary_dk(V a0) {
top:;
V s541 = a0;
if (TAG(s541) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L542, 2, 1, (V[]){FLD(s541, 0)}));
} else if (TAG(s541) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L544, 2, 1, (V[]){FLD(s541, 0)}));
} else if (TAG(s541) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L545, 2, 1, (V[]){FLD(s541, 0)}));
} else if (TAG(s541) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L546, 2, 1, (V[]){FLD(s541, 0)}));
} else if (TAG(s541) == 4) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L548, 2, 1, (V[]){FLD(s541, 0)}));
} else if (TAG(s541) == 5) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L549, 2, 1, (V[]){FLD(s541, 0)}));
} else if (TAG(s541) == 6) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L550, 2, 1, (V[]){FLD(s541, 0)}));
} else if (TAG(s541) == 7) {
return F_P_dprimary_dsym(F_P_dwhich(FLD(s541, 0), C2(1, S551(), C2(1, S552(), C2(1, S553(), C2(1, S554(), C2(1, S555(), C2(1, S556(), C2(1, S557(), C2(1, S558(), C2(1, S559(), IMM(0))))))))))));
} else {
return F_Parser_dbind(F_P_derr(S560()), mk_clo(L561, 1, 0, 0));
}
}
static V W_P_dprimary_dk(V *a) { (void)a; return F_P_dprimary_dk(a[0]); }
static V L564(V *a) {
return F_P_dterm();
}
static V L565(V *a) {
return F_P_dterm();
}
static V L567(V *a) {
return F_Parser_dpure(F_P_dneg(a[0]));
}
static V L566(V *a) {
return F_Parser_dbind(F_P_dterm(), mk_clo(L567, 1, 0, 0));
}
static V L568(V *a) {
return F_P_ddep();
}
static V L570(V *a) {
return F_P_damp_dgo(a[0]);
}
static V L569(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L570, 1, 0, 0));
}
static V S573(void) { static V c; return STRC(c, ""); }
static V L572(V *a) {
return F_Parser_dpure(C2(14, S573(), IMM(0)));
}
static V L571(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L572, 1, 0, 0));
}
static V S574(void) { static V c; return STRC(c, "unexpected symbol"); }
static V S576(void) { static V c; return STRC(c, ""); }
static V L575(V *a) {
return F_Parser_dpure(C1(15, S576()));
}
static V F_P_dprimary_dsym(V a0) {
top:;
V s563 = a0;
if ((s563) == 0) {
return F_P_dparen();
} else if ((s563) == 1) {
return F_P_dbrack();
} else if ((s563) == 2) {
return F_P_dbrace();
} else if ((s563) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L564, 1, 0, 0));
} else if ((s563) == 4) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L565, 1, 0, 0));
} else if ((s563) == 5) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L566, 1, 0, 0));
} else if ((s563) == 6) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L568, 1, 0, 0));
} else if ((s563) == 7) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L569, 1, 0, 0));
} else if ((s563) == 8) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L571, 1, 0, 0));
} else if (nat_ge(s563, 9)) {
return F_Parser_dbind(F_P_derr(S574()), mk_clo(L575, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dprimary_dsym(V *a) { (void)a; return F_P_dprimary_dsym(a[0]); }
static V S579(void) { static V c; return STRC(c, "#q"); }
static V L578(V *a) {
return F_Parser_dpure(C2(14, S579(), IMM(0)));
}
static V F_P_damp_dgo(V a0) {
top:;
V s577 = a0;
if (TAG(FLD(s577, 0)) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L578, 1, 0, 0));
} else {
return F_P_ddep();
}
}
static V W_P_damp_dgo(V *a) { (void)a; return F_P_damp_dgo(a[0]); }
static V S580(void) { static V c; return STRC(c, "-"); }
static V S582(void) { static V c; return STRC(c, "+"); }
static V S585(void) { static V c; return STRC(c, ":"); }
static V S588(void) { static V c; return STRC(c, ""); }
static V L587(V *a) {
return F_Parser_dpure(C2(14, S588(), IMM(0)));
}
static V L586(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L587, 1, 0, 0));
}
static V L584(V *a) {
return F_Parser_dbind(F_P_dexpect(S585()), mk_clo(L586, 1, 0, 0));
}
static V L583(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L584, 1, 0, 0));
}
static V L581(V *a) {
return F_Parser_dbind(F_P_deat(S582()), mk_clo(L583, 1, 0, 0));
}
static V F_P_ddep(void) {
top:;
return F_Parser_dbind(F_P_deat(S580()), mk_clo(L581, 1, 0, 0));
}
static V W_P_ddep(V *a) { (void)a; return F_P_ddep(); }
static V S590(void) { static V c; return STRC(c, "-"); }
static V F_P_dneg(V a0) {
top:;
V s589 = a0;
if (TAG(s589) == 1) {
return C1(1, F_U32_dsub(0u, FLD(s589, 0)));
} else if (TAG(s589) == 3) {
return C1(3, F_String_dappend(S590(), FLD(s589, 0)));
} else {
return s589;
}
}
static V W_P_dneg(V *a) { (void)a; return F_P_dneg(a[0]); }
static V S593(void) { static V c; return STRC(c, "=="); }
static V L592(V *a) {
return F_P_dbrace_dgo(F_P_dtok__is(a[0], S593()));
}
static V L591(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L592, 1, 0, 0));
}
static V F_P_dbrace(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L591, 1, 0, 0));
}
static V W_P_dbrace(V *a) { (void)a; return F_P_dbrace(); }
static V S596(void) { static V c; return STRC(c, "}"); }
static V S598(void) { static V c; return STRC(c, ""); }
static V L597(V *a) {
return F_Parser_dpure(C2(14, S598(), IMM(0)));
}
static V L595(V *a) {
return F_Parser_dbind(F_P_dexpect(S596()), mk_clo(L597, 1, 0, 0));
}
static V F_P_dbrace_dgo(V a0) {
top:;
V s594 = a0;
if ((s594) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L595, 1, 0, 0));
} else if ((s594) == IMM(0)) {
return F_P_dbrace_dbody();
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrace_dgo(V *a) { (void)a; return F_P_dbrace_dgo(a[0]); }
static V S601(void) { static V c; return STRC(c, "=="); }
static V S602(void) { static V c; return STRC(c, "!="); }
static V S603(void) { static V c; return STRC(c, ":"); }
static V L600(V *a) {
return F_P_dbrace_dtail(a[0], F_P_dtok__which(a[1], C2(1, S601(), C2(1, S602(), C2(1, S603(), IMM(0))))));
}
static V L599(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L600, 2, 1, (V[]){a[0]}));
}
static V F_P_dbrace_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L599, 1, 0, 0));
}
static V W_P_dbrace_dbody(V *a) { (void)a; return F_P_dbrace_dbody(); }
static V S607(void) { static V c; return STRC(c, ":"); }
static V S610(void) { static V c; return STRC(c, "}"); }
static V S612(void) { static V c; return STRC(c, ""); }
static V L611(V *a) {
return F_Parser_dpure(C2(14, S612(), IMM(0)));
}
static V L609(V *a) {
return F_Parser_dbind(F_P_dexpect(S610()), mk_clo(L611, 1, 0, 0));
}
static V L608(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L609, 1, 0, 0));
}
static V L606(V *a) {
return F_Parser_dbind(F_P_dexpect(S607()), mk_clo(L608, 1, 0, 0));
}
static V L605(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L606, 1, 0, 0));
}
static V S615(void) { static V c; return STRC(c, ":"); }
static V S618(void) { static V c; return STRC(c, "}"); }
static V S620(void) { static V c; return STRC(c, ""); }
static V L619(V *a) {
return F_Parser_dpure(C2(14, S620(), IMM(0)));
}
static V L617(V *a) {
return F_Parser_dbind(F_P_dexpect(S618()), mk_clo(L619, 1, 0, 0));
}
static V L616(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L617, 1, 0, 0));
}
static V L614(V *a) {
return F_Parser_dbind(F_P_dexpect(S615()), mk_clo(L616, 1, 0, 0));
}
static V L613(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L614, 1, 0, 0));
}
static V S623(void) { static V c; return STRC(c, "}"); }
static V L624(V *a) {
return F_Parser_dpure(C2(13, a[1], F_P_dhead(a[0])));
}
static V L622(V *a) {
return F_Parser_dbind(F_P_dexpect(S623()), mk_clo(L624, 3, 2, (V[]){a[1], a[0]}));
}
static V L621(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L622, 2, 1, (V[]){a[0]}));
}
static V S625(void) { static V c; return STRC(c, "}"); }
static V L626(V *a) {
return F_Parser_dpure(a[0]);
}
static V F_P_dbrace_dtail(V a0, V a1) {
top:;
V s604 = a1;
if ((s604) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L605, 1, 0, 0));
} else if ((s604) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L613, 1, 0, 0));
} else if ((s604) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L621, 2, 1, (V[]){a0}));
} else if (nat_ge(s604, 3)) {
return F_Parser_dbind(F_P_dexpect(S625()), mk_clo(L626, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrace_dtail(V *a) { (void)a; return F_P_dbrace_dtail(a[0], a[1]); }
static V S629(void) { static V c; return STRC(c, "]"); }
static V L628(V *a) {
return F_P_dbrack_dgo(F_P_dtok__is(a[0], S629()));
}
static V L627(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L628, 1, 0, 0));
}
static V F_P_dbrack(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L627, 1, 0, 0));
}
static V W_P_dbrack(V *a) { (void)a; return F_P_dbrack(); }
static V S632(void) { static V c; return STRC(c, "Nil"); }
static V L631(V *a) {
return F_Parser_dpure(C2(6, S632(), IMM(0)));
}
static V F_P_dbrack_dgo(V a0) {
top:;
V s630 = a0;
if ((s630) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L631, 1, 0, 0));
} else if ((s630) == IMM(0)) {
return F_P_dbrack_dbody();
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrack_dgo(V *a) { (void)a; return F_P_dbrack_dgo(a[0]); }
static V S635(void) { static V c; return STRC(c, ":"); }
static V L634(V *a) {
return F_P_dbrack_dtail(a[0], F_P_dtok__is(a[1], S635()));
}
static V L633(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L634, 2, 1, (V[]){a[0]}));
}
static V F_P_dbrack_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L633, 1, 0, 0));
}
static V W_P_dbrack_dbody(V *a) { (void)a; return F_P_dbrack_dbody(); }
static V S637(void) { static V c; return STRC(c, ","); }
static V S639(void) { static V c; return STRC(c, "]"); }
static V L640(V *a) {
return F_Parser_dpure(F_P_delist(C2(1, a[0], a[1])));
}
static V L638(V *a) {
return F_Parser_dbind(F_P_dlist(S639()), mk_clo(L640, 2, 1, (V[]){a[0]}));
}
static V F_P_dbrack_dtail(V a0, V a1) {
top:;
V s636 = a1;
if ((s636) == IMM(1)) {
return F_P_darr(a0);
} else if ((s636) == IMM(0)) {
return F_Parser_dbind(F_P_deat(S637()), mk_clo(L638, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrack_dtail(V *a) { (void)a; return F_P_dbrack_dtail(a[0], a[1]); }
static V S642(void) { static V c; return STRC(c, "Nil"); }
static V S643(void) { static V c; return STRC(c, "Con"); }
static V F_P_delist(V a0) {
top:;
V s641 = a0;
if ((s641) == IMM(0)) {
return C2(6, S642(), IMM(0));
} else if (TAG(s641) == 1) {
return C2(6, S643(), C2(1, FLD(s641, 0), C2(1, F_P_delist(FLD(s641, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_delist(V *a) { (void)a; return F_P_delist(a[0]); }
static V S649(void) { static V c; return STRC(c, "^"); }
static V S651(void) { static V c; return STRC(c, "]"); }
static V S653(void) { static V c; return STRC(c, "Array.new"); }
static V S654(void) { static V c; return STRC(c, ""); }
static V L652(V *a) {
return F_Parser_dpure(C2(5, C1(0, S653()), C2(1, C2(14, S654(), IMM(0)), C2(1, a[1], C2(1, a[0], IMM(0))))));
}
static V L650(V *a) {
return F_Parser_dbind(F_P_dexpect(S651()), mk_clo(L652, 3, 2, (V[]){a[0], a[1]}));
}
static V L648(V *a) {
return F_Parser_dbind(F_P_darr_dsize(F_P_dtok__is(a[1], S649()), a[2]), mk_clo(L650, 2, 1, (V[]){a[0]}));
}
static V L647(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L648, 3, 2, (V[]){a[0], a[1]}));
}
static V L646(V *a) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L647, 3, 2, (V[]){a[0], a[1]}));
}
static V L645(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L646, 2, 1, (V[]){a[0]}));
}
static V L644(V *a) {
return F_Parser_dbind(F_P_dterm(), mk_clo(L645, 2, 1, (V[]){a[0]}));
}
static V F_P_darr(V a0) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L644, 2, 1, (V[]){a0}));
}
static V W_P_darr(V *a) { (void)a; return F_P_darr(a[0]); }
static V F_P_darr_dsize(V a0, V a1) {
top:;
V s655 = a0;
if ((s655) == IMM(1)) {
return F_P_dterm();
} else if ((s655) == IMM(0)) {
return F_P_darr_dsize_dlit(a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_darr_dsize(V *a) { (void)a; return F_P_darr_dsize(a[0], a[1]); }
static V L657(V *a) {
return F_Parser_dpure(C1(2, F_P_dlog2(a[0])));
}
static V S658(void) { static V c; return STRC(c, "expected an array size"); }
static V L659(V *a) {
return F_Parser_dpure(C1(2, 0u));
}
static V F_P_darr_dsize_dlit(V a0) {
top:;
V s656 = a0;
if (TAG(FLD(s656, 0)) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L657, 2, 1, (V[]){FLD(FLD(s656, 0), 0)}));
} else {
return F_Parser_dbind(F_P_derr(S658()), mk_clo(L659, 1, 0, 0));
}
}
static V W_P_darr_dsize_dlit(V *a) { (void)a; return F_P_darr_dsize_dlit(a[0]); }
static V F_P_dlog2(V a0) {
top:;
return F_U32_dfrom__nat(F_U32_dlog2(a0));
}
static V W_P_dlog2(V *a) { (void)a; return F_P_dlog2(a[0]); }
static V W_U32_dlog2(V *a) { (void)a; return F_U32_dlog2(a[0]); }
static V S662(void) { static V c; return STRC(c, ")"); }
static V L661(V *a) {
return F_P_dparen_dgo(F_P_dtok__is(a[0], S662()));
}
static V L660(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L661, 1, 0, 0));
}
static V F_P_dparen(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L660, 1, 0, 0));
}
static V W_P_dparen(V *a) { (void)a; return F_P_dparen(); }
static V S665(void) { static V c; return STRC(c, "Unit"); }
static V L664(V *a) {
return F_Parser_dpure(C2(6, S665(), IMM(0)));
}
static V F_P_dparen_dgo(V a0) {
top:;
V s663 = a0;
if ((s663) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L664, 1, 0, 0));
} else if ((s663) == IMM(0)) {
return F_P_dparen_dbody();
} else { bend_fail("incomplete match"); }
}
static V W_P_dparen_dgo(V *a) { (void)a; return F_P_dparen_dgo(a[0]); }
static V S668(void) { static V c; return STRC(c, ","); }
static V S669(void) { static V c; return STRC(c, ":"); }
static V L667(V *a) {
return F_P_dparen_dtail(a[0], F_P_dtok__which(a[1], C2(1, S668(), C2(1, S669(), IMM(0)))));
}
static V L666(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L667, 2, 1, (V[]){a[0]}));
}
static V F_P_dparen_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L666, 1, 0, 0));
}
static V W_P_dparen_dbody(V *a) { (void)a; return F_P_dparen_dbody(); }
static V S672(void) { static V c; return STRC(c, ")"); }
static V L673(V *a) {
return F_Parser_dpure(F_P_dtuple(C2(1, a[0], a[1])));
}
static V L671(V *a) {
return F_Parser_dbind(F_P_dlist(S672()), mk_clo(L673, 2, 1, (V[]){a[0]}));
}
static V S676(void) { static V c; return STRC(c, ")"); }
static V L677(V *a) {
return F_Parser_dpure(C2(13, a[1], F_P_dhead(a[0])));
}
static V L675(V *a) {
return F_Parser_dbind(F_P_dexpect(S676()), mk_clo(L677, 3, 2, (V[]){a[1], a[0]}));
}
static V L674(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L675, 2, 1, (V[]){a[0]}));
}
static V S678(void) { static V c; return STRC(c, ")"); }
static V L679(V *a) {
return F_Parser_dpure(a[0]);
}
static V F_P_dparen_dtail(V a0, V a1) {
top:;
V s670 = a1;
if ((s670) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L671, 2, 1, (V[]){a0}));
} else if ((s670) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L674, 2, 1, (V[]){a0}));
} else if (nat_ge(s670, 2)) {
return F_Parser_dbind(F_P_dexpect(S678()), mk_clo(L679, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparen_dtail(V *a) { (void)a; return F_P_dparen_dtail(a[0], a[1]); }
static V S681(void) { static V c; return STRC(c, "Unit"); }
static V S682(void) { static V c; return STRC(c, "Tuple"); }
static V F_P_dtuple(V a0) {
top:;
V s680 = a0;
if ((s680) == IMM(0)) {
return C2(6, S681(), IMM(0));
} else if (TAG(s680) == 1 && (FLD(s680, 1)) == IMM(0)) {
return FLD(s680, 0);
} else if (TAG(s680) == 1) {
return C2(6, S682(), C2(1, FLD(s680, 0), C2(1, F_P_dtuple(FLD(s680, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtuple(V *a) { (void)a; return F_P_dtuple(a[0]); }
static V S683(void) { static V c; return STRC(c, "{"); }
static V S684(void) { static V c; return STRC(c, "<"); }
static V S685(void) { static V c; return STRC(c, "=>"); }
static V F_P_dafter__id(V a0, V a1) {
top:;
return F_P_dafter__id_dgo(a0, F_Bool_dpick(F_P_dtok__sp(a1), 3u, F_P_dtok__which(a1, C2(1, S683(), C2(1, S684(), IMM(0))))), F_P_dtok__is(a1, S685()));
}
static V W_P_dafter__id(V *a) { (void)a; return F_P_dafter__id(a[0], a[1]); }
static V L688(V *a) {
return F_Parser_dpure(C2(7, C1(0, a[0]), a[1]));
}
static V L687(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L688, 2, 1, (V[]){a[0]}));
}
static V F_P_dafter__id_dgo(V a0, V a1, V a2) {
top:;
V s686 = a2;
if ((s686) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L687, 2, 1, (V[]){a0}));
} else if ((s686) == IMM(0)) {
return F_P_dafter__id_dk(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dafter__id_dgo(V *a) { (void)a; return F_P_dafter__id_dgo(a[0], a[1], a[2]); }
static V S691(void) { static V c; return STRC(c, "}"); }
static V L692(V *a) {
return F_Parser_dpure(C2(6, a[0], a[1]));
}
static V L690(V *a) {
return F_Parser_dbind(F_P_dlist(S691()), mk_clo(L692, 2, 1, (V[]){a[0]}));
}
static V L694(V *a) {
return F_Parser_dpure(C2(14, a[0], a[1]));
}
static V L693(V *a) {
return F_Parser_dbind(F_P_dtyargs(), mk_clo(L694, 2, 1, (V[]){a[0]}));
}
static V F_P_dafter__id_dk(V a0, V a1) {
top:;
V s689 = a1;
if ((s689) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L690, 2, 1, (V[]){a0}));
} else if ((s689) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L693, 2, 1, (V[]){a0}));
} else if (nat_ge(s689, 2)) {
return F_Parser_dpure(C1(0, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dafter__id_dk(V *a) { (void)a; return F_P_dafter__id_dk(a[0], a[1]); }
static V L695(V *a) {
return F_P_dtyargs_dgo(a[0], F_P_dstuck(F_P_dtok__kind(a[0])));
}
static V F_P_dtyargs(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L695, 1, 0, 0));
}
static V W_P_dtyargs(V *a) { (void)a; return F_P_dtyargs(); }
static V F_P_dtyargs_dgo(V a0, V a1) {
top:;
V s696 = a1;
if ((s696) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s696) == IMM(0)) {
return F_P_dtyargs_dclose(F_P_dis__gt(a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtyargs_dgo(V *a) { (void)a; return F_P_dtyargs_dgo(a[0], a[1]); }
static V S697(void) { static V c; return STRC(c, ">"); }
static V S698(void) { static V c; return STRC(c, ">>"); }
static V S699(void) { static V c; return STRC(c, ">="); }
static V F_P_dis__gt(V a0) {
top:;
return F_Bool_dor(F_P_dtok__is(a0, S697()), F_Bool_dor(F_P_dtok__is(a0, S698()), F_P_dtok__is(a0, S699())));
}
static V W_P_dis__gt(V *a) { (void)a; return F_P_dis__gt(a[0]); }
static V L701(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dtyargs_dclose(V a0) {
top:;
V s700 = a0;
if ((s700) == IMM(1)) {
return F_Parser_dbind(F_P_dgt(), mk_clo(L701, 1, 0, 0));
} else if ((s700) == IMM(0)) {
return F_P_dtyargs_ditem();
} else { bend_fail("incomplete match"); }
}
static V W_P_dtyargs_dclose(V *a) { (void)a; return F_P_dtyargs_dclose(a[0]); }
static V S703(void) { static V c; return STRC(c, ","); }
static V L705(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L704(V *a) {
return F_Parser_dbind(F_P_dtyargs_dmore(a[1]), mk_clo(L705, 2, 1, (V[]){a[0]}));
}
static V L702(V *a) {
return F_Parser_dbind(F_P_deat(S703()), mk_clo(L704, 2, 1, (V[]){a[0]}));
}
static V F_P_dtyargs_ditem(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L702, 1, 0, 0));
}
static V W_P_dtyargs_ditem(V *a) { (void)a; return F_P_dtyargs_ditem(); }
static V L707(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dtyargs_dmore(V a0) {
top:;
V s706 = a0;
if ((s706) == IMM(1)) {
return F_P_dtyargs();
} else if ((s706) == IMM(0)) {
return F_Parser_dbind(F_P_dgt(), mk_clo(L707, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtyargs_dmore(V *a) { (void)a; return F_P_dtyargs_dmore(a[0]); }
static V L708(V *a) {
return F_P_dgt_dgo(a[0]);
}
static V F_P_dgt(void) {
top:;
return mk_clo(L708, 1, 0, 0);
}
static V W_P_dgt(V *a) { (void)a; return F_P_dgt(); }
static V S710(void) { static V c; return STRC(c, ">"); }
static V S711(void) { static V c; return STRC(c, ">>"); }
static V S712(void) { static V c; return STRC(c, ">="); }
static V S713(void) { static V c; return STRC(c, "expected '>'"); }
static V F_P_dgt_dgo(V a0) {
top:;
V s709 = a0;
if (TAG(s709) == 1 && TAG(FLD(FLD(s709, 0), 0)) == 7) {
return F_P_dgt_dif(FLD(FLD(FLD(s709, 0), 0), 0), FLD(FLD(s709, 0), 1), FLD(FLD(s709, 0), 2), FLD(s709, 1), F_P_dwhich(FLD(FLD(FLD(s709, 0), 0), 0), C2(1, S710(), C2(1, S711(), C2(1, S712(), IMM(0))))));
} else {
return F_P_derr_dgo(S713(), s709);
}
}
static V W_P_dgt_dgo(V *a) { (void)a; return F_P_dgt_dgo(a[0]); }
static V S715(void) { static V c; return STRC(c, ">"); }
static V S716(void) { static V c; return STRC(c, "="); }
static V S717(void) { static V c; return STRC(c, "expected '>'"); }
static V F_P_dgt_dif(V a0, V a1, V a2, V a3, V a4) {
top:;
V s714 = a4;
if ((s714) == 0) {
return C2(0, IMM(0), a3);
} else if ((s714) == 1) {
return C2(0, IMM(0), C2(1, C3(0, C1(7, S715()), IMM(0), a2), a3));
} else if ((s714) == 2) {
return C2(0, IMM(0), C2(1, C3(0, C1(7, S716()), IMM(0), a2), a3));
} else if (nat_ge(s714, 3)) {
return F_P_derr_dgo(S717(), C2(1, C3(0, C1(7, a0), a1, a2), a3));
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
V s718 = a0;
if ((s718) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s718) == IMM(0)) {
return F_P_dskip();
} else { bend_fail("incomplete match"); }
}
static V W_P_dparam_dskip__mode_dgo(V *a) { (void)a; return F_P_dparam_dskip__mode_dgo(a[0]); }
static V S719(void) { static V c; return STRC(c, "-"); }
static V S720(void) { static V c; return STRC(c, "+"); }
static V S721(void) { static V c; return STRC(c, "~"); }
static V F_P_dparam_dmode(V a0) {
top:;
return F_Bool_dpick(F_P_dtok__is(a0, S719()), 1u, F_Bool_dpick(F_P_dtok__is(a0, S720()), 2u, F_Bool_dpick(F_P_dtok__is(a0, S721()), 3u, 0u)));
}
static V W_P_dparam_dmode(V *a) { (void)a; return F_P_dparam_dmode(a[0]); }
static V L722(V *a) {
return F_P_dnls_dif(F_P_dis__nl(a[0]));
}
static V F_P_dnls(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L722, 1, 0, 0));
}
static V W_P_dnls(V *a) { (void)a; return F_P_dnls(); }
static V F_P_dis__nl(V a0) {
top:;
V s723 = a0;
if ((FLD(s723, 0)) == IMM(8)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dis__nl(V *a) { (void)a; return F_P_dis__nl(a[0]); }
static V L725(V *a) {
return F_P_dnls();
}
static V F_P_dnls_dif(V a0) {
top:;
V s724 = a0;
if ((s724) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L725, 1, 0, 0));
} else if ((s724) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dnls_dif(V *a) { (void)a; return F_P_dnls_dif(a[0]); }
static V L726(V *a) {
return F_P_dexpect__in_dgo(F_P_dis__in(a[0]));
}
static V F_P_dexpect__in(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L726, 1, 0, 0));
}
static V W_P_dexpect__in(V *a) { (void)a; return F_P_dexpect__in(); }
static V F_P_dis__in(V a0) {
top:;
V s727 = a0;
if ((FLD(s727, 0)) == IMM(9)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dis__in(V *a) { (void)a; return F_P_dis__in(a[0]); }
static V S729(void) { static V c; return STRC(c, "expected an indented block"); }
static V F_P_dexpect__in_dgo(V a0) {
top:;
V s728 = a0;
if ((s728) == IMM(1)) {
return F_P_dskip();
} else if ((s728) == IMM(0)) {
return F_P_derr(S729());
} else { bend_fail("incomplete match"); }
}
static V W_P_dexpect__in_dgo(V *a) { (void)a; return F_P_dexpect__in_dgo(a[0]); }
static V S733(void) { static V c; return STRC(c, "<"); }
static V S734(void) { static V c; return STRC(c, "<-"); }
static V S738(void) { static V c; return STRC(c, ":"); }
static V L741(V *a) {
return F_Parser_dpure(C3(3, a[1], a[0], a[2]));
}
static V L740(V *a) {
return F_Parser_dbind(F_P_dtype_dbody(F_P_dis__in(a[2])), mk_clo(L741, 3, 2, (V[]){a[0], a[1]}));
}
static V L739(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L740, 3, 2, (V[]){a[0], a[1]}));
}
static V L737(V *a) {
return F_Parser_dbind(F_P_dexpect(S738()), mk_clo(L739, 3, 2, (V[]){a[0], a[1]}));
}
static V L736(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L737, 3, 2, (V[]){a[0], a[1]}));
}
static V L735(V *a) {
return F_Parser_dbind(F_P_duntil__is(), mk_clo(L736, 3, 2, (V[]){a[1], a[0]}));
}
static V L732(V *a) {
return F_Parser_dbind(F_P_dtparams_dopt(F_P_dtok__which(a[1], C2(1, S733(), C2(1, S734(), IMM(0))))), mk_clo(L735, 2, 1, (V[]){a[0]}));
}
static V L731(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L732, 2, 1, (V[]){a[0]}));
}
static V L730(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L731, 1, 0, 0));
}
static V F_P_dtype(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L730, 1, 0, 0));
}
static V W_P_dtype(V *a) { (void)a; return F_P_dtype(); }
static V L743(V *a) {
return F_P_dctors();
}
static V F_P_dtype_dbody(V a0) {
top:;
V s742 = a0;
if ((s742) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L743, 1, 0, 0));
} else if ((s742) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtype_dbody(V *a) { (void)a; return F_P_dtype_dbody(a[0]); }
static V L745(V *a) {
return F_P_dctors_dgo(a[0], F_Bool_dpick(F_P_dis__de(a[0]), 0u, F_Bool_dpick(F_P_dstuck(F_P_dtok__kind(a[0])), 1u, 2u)));
}
static V L744(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L745, 1, 0, 0));
}
static V F_P_dctors(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L744, 1, 0, 0));
}
static V W_P_dctors(V *a) { (void)a; return F_P_dctors(); }
static V L747(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S749(void) { static V c; return STRC(c, "{"); }
static V L752(V *a) {
return F_Parser_dpure(C2(1, C2(0, a[1], a[0]), a[2]));
}
static V L751(V *a) {
return F_Parser_dbind(F_P_dctors(), mk_clo(L752, 3, 2, (V[]){a[1], a[0]}));
}
static V L750(V *a) {
return F_Parser_dbind(F_P_dfields(), mk_clo(L751, 2, 1, (V[]){a[0]}));
}
static V L748(V *a) {
return F_Parser_dbind(F_P_dexpect(S749()), mk_clo(L750, 2, 1, (V[]){a[0]}));
}
static V F_P_dctors_dgo(V a0, V a1) {
top:;
V s746 = a1;
if ((s746) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L747, 1, 0, 0));
} else if ((s746) == 1) {
return F_Parser_dpure(IMM(0));
} else if (nat_ge(s746, 2)) {
return F_Parser_dbind(F_P_dident(), mk_clo(L748, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dctors_dgo(V *a) { (void)a; return F_P_dctors_dgo(a[0], a[1]); }
static V S754(void) { static V c; return STRC(c, "}"); }
static V L753(V *a) {
return F_P_dfields_dgo(F_Bool_dor(F_P_dtok__is(a[0], S754()), F_P_dstuck(F_P_dtok__kind(a[0]))));
}
static V F_P_dfields(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L753, 1, 0, 0));
}
static V W_P_dfields(V *a) { (void)a; return F_P_dfields(); }
static V L756(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S757(void) { static V c; return STRC(c, "+"); }
static V S759(void) { static V c; return STRC(c, "-"); }
static V S762(void) { static V c; return STRC(c, ":"); }
static V S765(void) { static V c; return STRC(c, ","); }
static V L767(V *a) {
return F_Parser_dpure(C2(1, C2(0, a[1], a[0]), a[2]));
}
static V L766(V *a) {
return F_Parser_dbind(F_P_dfields(), mk_clo(L767, 3, 2, (V[]){a[0], a[1]}));
}
static V L764(V *a) {
return F_Parser_dbind(F_P_deat(S765()), mk_clo(L766, 3, 2, (V[]){a[1], a[0]}));
}
static V L763(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L764, 2, 1, (V[]){a[0]}));
}
static V L761(V *a) {
return F_Parser_dbind(F_P_dexpect(S762()), mk_clo(L763, 2, 1, (V[]){a[0]}));
}
static V L760(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L761, 1, 0, 0));
}
static V L758(V *a) {
return F_Parser_dbind(F_P_deat(S759()), mk_clo(L760, 1, 0, 0));
}
static V F_P_dfields_dgo(V a0) {
top:;
V s755 = a0;
if ((s755) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L756, 1, 0, 0));
} else if ((s755) == IMM(0)) {
return F_Parser_dbind(F_P_deat(S757()), mk_clo(L758, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dfields_dgo(V *a) { (void)a; return F_P_dfields_dgo(a[0]); }
static V L768(V *a) {
return C2(0, IMM(0), F_P_duntil__is_dgo(a[0]));
}
static V F_P_duntil__is(void) {
top:;
return mk_clo(L768, 1, 0, 0);
}
static V W_P_duntil__is(V *a) { (void)a; return F_P_duntil__is(); }
static V S770(void) { static V c; return STRC(c, "is"); }
static V F_P_duntil__is_dgo(V a0) {
top:;
V s769 = a0;
if ((s769) == IMM(0)) {
return IMM(0);
} else if (TAG(s769) == 1 && TAG(FLD(FLD(s769, 0), 0)) == 0) {
return F_P_duntil__is_dif(C3(0, C1(0, FLD(FLD(FLD(s769, 0), 0), 0)), FLD(FLD(s769, 0), 1), FLD(FLD(s769, 0), 2)), FLD(s769, 1), F_Str_deq(FLD(FLD(FLD(s769, 0), 0), 0), S770()));
} else if (TAG(s769) == 1 && (FLD(FLD(s769, 0), 0)) == IMM(11)) {
return C2(1, C3(0, IMM(11), FLD(FLD(s769, 0), 1), FLD(FLD(s769, 0), 2)), FLD(s769, 1));
} else if (TAG(s769) == 1 && TAG(FLD(FLD(s769, 0), 0)) == 12) {
return C2(1, C3(0, C1(12, FLD(FLD(FLD(s769, 0), 0), 0)), FLD(FLD(s769, 0), 1), FLD(FLD(s769, 0), 2)), FLD(s769, 1));
} else if (TAG(s769) == 1) {
{ V t0 = FLD(s769, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_duntil__is_dgo(V *a) { (void)a; return F_P_duntil__is_dgo(a[0]); }
static V F_P_duntil__is_dif(V a0, V a1, V a2) {
top:;
V s771 = a2;
if ((s771) == IMM(1)) {
return a1;
} else if ((s771) == IMM(0)) {
return F_P_duntil__is_dgo(a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_duntil__is_dif(V *a) { (void)a; return F_P_duntil__is_dif(a[0], a[1], a[2]); }
static V L773(V *a) {
return F_P_dtparams();
}
static V L774(V *a) {
return F_P_dtparams();
}
static V F_P_dtparams_dopt(V a0) {
top:;
V s772 = a0;
if ((s772) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L773, 1, 0, 0));
} else if ((s772) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L774, 1, 0, 0));
} else if (nat_ge(s772, 2)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtparams_dopt(V *a) { (void)a; return F_P_dtparams_dopt(a[0]); }
static V S775(void) { static V c; return STRC(c, "-"); }
static V S779(void) { static V c; return STRC(c, ","); }
static V L781(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L780(V *a) {
return F_Parser_dbind(F_P_dtparams_dmore(a[1]), mk_clo(L781, 2, 1, (V[]){a[0]}));
}
static V L778(V *a) {
return F_Parser_dbind(F_P_deat(S779()), mk_clo(L780, 2, 1, (V[]){a[0]}));
}
static V L777(V *a) {
return F_Parser_dbind(F_P_dskip__ann(), mk_clo(L778, 2, 1, (V[]){a[0]}));
}
static V L776(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L777, 1, 0, 0));
}
static V F_P_dtparams(void) {
top:;
return F_Parser_dbind(F_P_deat(S775()), mk_clo(L776, 1, 0, 0));
}
static V W_P_dtparams(V *a) { (void)a; return F_P_dtparams(); }
static V L783(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dtparams_dmore(V a0) {
top:;
V s782 = a0;
if ((s782) == IMM(1)) {
return F_P_dtparams();
} else if ((s782) == IMM(0)) {
return F_Parser_dbind(F_P_dgt(), mk_clo(L783, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtparams_dmore(V *a) { (void)a; return F_P_dtparams_dmore(a[0]); }
static V S785(void) { static V c; return STRC(c, ":"); }
static V L784(V *a) {
return F_P_dskip__ann_dgo(F_P_dtok__is(a[0], S785()));
}
static V F_P_dskip__ann(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L784, 1, 0, 0));
}
static V W_P_dskip__ann(V *a) { (void)a; return F_P_dskip__ann(); }
static V L788(V *a) {
return F_Parser_dpure(IMM(0));
}
static V L787(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L788, 1, 0, 0));
}
static V F_P_dskip__ann_dgo(V a0) {
top:;
V s786 = a0;
if ((s786) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L787, 1, 0, 0));
} else if ((s786) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__ann_dgo(V *a) { (void)a; return F_P_dskip__ann_dgo(a[0]); }
static V S791(void) { static V c; return STRC(c, "("); }
static V S795(void) { static V c; return STRC(c, "->"); }
static V S797(void) { static V c; return STRC(c, ":"); }
static V S801(void) { static V c; return STRC(c, "import"); }
static V L800(V *a) {
return F_P_ddef_dbody(a[2], a[1], a[0], F_P_dtok__is__id(a[3], S801()));
}
static V L799(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L800, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L798(V *a) {
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L799, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L796(V *a) {
return F_Parser_dbind(F_P_dexpect(S797()), mk_clo(L798, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L794(V *a) {
return F_Parser_dbind(F_P_dret_dgo(F_P_dtok__is(a[2], S795())), mk_clo(L796, 3, 2, (V[]){a[0], a[1]}));
}
static V L793(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L794, 3, 2, (V[]){a[1], a[0]}));
}
static V L792(V *a) {
return F_Parser_dbind(F_P_dparams(), mk_clo(L793, 2, 1, (V[]){a[0]}));
}
static V L790(V *a) {
return F_Parser_dbind(F_P_dexpect(S791()), mk_clo(L792, 2, 1, (V[]){a[0]}));
}
static V L789(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L790, 1, 0, 0));
}
static V F_P_ddef(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L789, 1, 0, 0));
}
static V W_P_ddef(V *a) { (void)a; return F_P_ddef(); }
static V L803(V *a) {
return F_Parser_dpure(C3(1, a[1], a[0], a[2]));
}
static V L804(V *a) {
return F_Parser_dpure(C4(0, a[2], a[1], F_Fold_dplain(a[3]), a[0]));
}
static V F_P_ddef_dbody(V a0, V a1, V a2, V a3) {
top:;
V s802 = a3;
if ((s802) == IMM(1)) {
return F_Parser_dbind(F_P_deff_dimports(), mk_clo(L803, 3, 2, (V[]){a1, a0}));
} else if ((s802) == IMM(0)) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L804, 4, 3, (V[]){a2, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddef_dbody(V *a) { (void)a; return F_P_ddef_dbody(a[0], a[1], a[2], a[3]); }
static V S806(void) { static V c; return STRC(c, "empty block"); }
static V S807(void) { static V c; return STRC(c, ""); }
static V S808(void) { static V c; return STRC(c, "_"); }
static V F_Fold_dplain(V a0) {
top:;
V s805 = a0;
if ((s805) == IMM(0)) {
return C1(15, S806());
} else if (TAG(s805) == 1 && TAG(FLD(s805, 0)) == 0 && (FLD(s805, 1)) == IMM(0)) {
return FLD(FLD(s805, 0), 1);
} else if (TAG(s805) == 1 && TAG(FLD(s805, 0)) == 1 && (FLD(s805, 1)) == IMM(0)) {
return FLD(FLD(s805, 0), 1);
} else if (TAG(s805) == 1 && TAG(FLD(s805, 0)) == 2 && (FLD(s805, 1)) == IMM(0)) {
return FLD(FLD(s805, 0), 0);
} else if (TAG(s805) == 1 && TAG(FLD(s805, 0)) == 3 && (FLD(s805, 1)) == IMM(0)) {
return FLD(FLD(s805, 0), 0);
} else if (TAG(s805) == 1 && (FLD(s805, 0)) == IMM(4) && (FLD(s805, 1)) == IMM(0)) {
return C2(14, S807(), IMM(0));
} else if (TAG(s805) == 1 && TAG(FLD(s805, 0)) == 0) {
return C3(8, FLD(FLD(s805, 0), 0), FLD(FLD(s805, 0), 1), F_Fold_dplain(FLD(s805, 1)));
} else if (TAG(s805) == 1 && TAG(FLD(s805, 0)) == 1) {
return C3(8, C1(0, FLD(FLD(s805, 0), 0)), FLD(FLD(s805, 0), 1), F_Fold_dplain(FLD(s805, 1)));
} else if (TAG(s805) == 1 && TAG(FLD(s805, 0)) == 2) {
return FLD(FLD(s805, 0), 0);
} else if (TAG(s805) == 1 && TAG(FLD(s805, 0)) == 3) {
return C3(8, C1(0, S808()), FLD(FLD(s805, 0), 0), F_Fold_dplain(FLD(s805, 1)));
} else if (TAG(s805) == 1 && (FLD(s805, 0)) == IMM(4)) {
{ V t0 = FLD(s805, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Fold_dplain(V *a) { (void)a; return F_Fold_dplain(a[0]); }
static V L810(V *a) {
return F_P_dstmts_dgo(a[0], F_Bool_dpick(F_P_dis__de(a[0]), 0u, F_Bool_dpick(F_P_dstuck(F_P_dtok__kind(a[0])), 1u, 2u)));
}
static V L809(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L810, 1, 0, 0));
}
static V F_P_dstmts(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L809, 1, 0, 0));
}
static V W_P_dstmts(V *a) { (void)a; return F_P_dstmts(); }
static V L812(V *a) {
return F_Parser_dpure(IMM(0));
}
static V L814(V *a) {
return F_Parser_dpure(F_List_dappend(a[0], a[1]));
}
static V L813(V *a) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L814, 2, 1, (V[]){a[0]}));
}
static V F_P_dstmts_dgo(V a0, V a1) {
top:;
V s811 = a1;
if ((s811) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L812, 1, 0, 0));
} else if ((s811) == 1) {
return F_Parser_dpure(IMM(0));
} else if (nat_ge(s811, 2)) {
return F_Parser_dbind(F_P_dstmt(), mk_clo(L813, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmts_dgo(V *a) { (void)a; return F_P_dstmts_dgo(a[0], a[1]); }
static V S816(void) { static V c; return STRC(c, "%"); }
static V L815(V *a) {
return F_P_dstmt_dgo(a[0], F_P_dtok__is(a[0], S816()));
}
static V F_P_dstmt(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L815, 1, 0, 0));
}
static V W_P_dstmt(V *a) { (void)a; return F_P_dstmt(); }
static V L818(V *a) {
return F_Parser_dpure(C2(1, IMM(4), IMM(0)));
}
static V S819(void) { static V c; return STRC(c, "match"); }
static V S820(void) { static V c; return STRC(c, "return"); }
static V S821(void) { static V c; return STRC(c, "do"); }
static V F_P_dstmt_dgo(V a0, V a1) {
top:;
V s817 = a1;
if ((s817) == IMM(1)) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L818, 1, 0, 0));
} else if ((s817) == IMM(0)) {
return F_P_dstmt_did(F_P_dtok__which__id(a0, C2(1, S819(), C2(1, S820(), C2(1, S821(), IMM(0))))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmt_dgo(V *a) { (void)a; return F_P_dstmt_dgo(a[0], a[1]); }
static V L823(V *a) {
return F_Parser_dpure(C2(1, C1(3, a[0]), IMM(0)));
}
static V L825(V *a) {
return F_Parser_dpure(C2(1, C1(2, a[0]), IMM(0)));
}
static V L824(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L825, 1, 0, 0));
}
static V L826(V *a) {
return F_Parser_dpure(C2(1, C1(3, a[0]), IMM(0)));
}
static V L827(V *a) {
return F_P_dstmt_dscan(a[0]);
}
static V F_P_dstmt_did(V a0) {
top:;
V s822 = a0;
if ((s822) == 0) {
return F_Parser_dbind(F_P_dmatch(), mk_clo(L823, 1, 0, 0));
} else if ((s822) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L824, 1, 0, 0));
} else if ((s822) == 2) {
return F_Parser_dbind(F_P_ddo(), mk_clo(L826, 1, 0, 0));
} else if (nat_ge(s822, 3)) {
return F_Parser_dbind(F_P_dscan(), mk_clo(L827, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmt_did(V *a) { (void)a; return F_P_dstmt_did(a[0]); }
static V F_P_dstmt_dscan(V a0) {
top:;
return F_P_dstmt_dscan_dgo(F_U32_dto__nat(a0));
}
static V W_P_dstmt_dscan(V *a) { (void)a; return F_P_dstmt_dscan(a[0]); }
static V W_U32_dto__nat(V *a) { (void)a; return F_U32_dto__nat(a[0]); }
static V L829(V *a) {
return F_Parser_dpure(C2(1, C1(3, a[0]), IMM(0)));
}
static V F_P_dstmt_dscan_dgo(V a0) {
top:;
V s828 = a0;
if ((s828) == 0) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L829, 1, 0, 0));
} else if ((s828) == 1) {
return F_P_dlet__stmt();
} else if (nat_ge(s828, 2)) {
return F_P_dbind__stmt();
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmt_dscan_dgo(V *a) { (void)a; return F_P_dstmt_dscan_dgo(a[0]); }
static V S830(void) { static V c; return STRC(c, "+"); }
static V S834(void) { static V c; return STRC(c, "["); }
static V L833(V *a) {
return F_P_dbind_darr(a[0], F_Bool_dand(F_P_dtok__is(a[1], S834()), F_Bool_dnot(F_P_dtok__sp(a[1]))));
}
static V L832(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L833, 2, 1, (V[]){a[0]}));
}
static V L831(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L832, 1, 0, 0));
}
static V F_P_dbind__stmt(void) {
top:;
return F_Parser_dbind(F_P_deat(S830()), mk_clo(L831, 1, 0, 0));
}
static V W_P_dbind__stmt(V *a) { (void)a; return F_P_dbind__stmt(); }
static V S838(void) { static V c; return STRC(c, "]"); }
static V S840(void) { static V c; return STRC(c, "<-"); }
static V S843(void) { static V c; return STRC(c, "Array.set"); }
static V S844(void) { static V c; return STRC(c, "U32"); }
static V L842(V *a) {
return F_Parser_dpure(C2(1, C2(0, C1(0, a[1]), C2(5, C1(0, S843()), C2(1, C2(14, S844(), IMM(0)), C2(1, C1(0, a[1]), C2(1, a[0], C2(1, a[2], IMM(0))))))), IMM(0)));
}
static V L841(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L842, 3, 2, (V[]){a[0], a[1]}));
}
static V L839(V *a) {
return F_Parser_dbind(F_P_dexpect(S840()), mk_clo(L841, 3, 2, (V[]){a[0], a[1]}));
}
static V L837(V *a) {
return F_Parser_dbind(F_P_dexpect(S838()), mk_clo(L839, 3, 2, (V[]){a[1], a[0]}));
}
static V L836(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L837, 2, 1, (V[]){a[0]}));
}
static V S846(void) { static V c; return STRC(c, "<-"); }
static V L848(V *a) {
return F_Parser_dpure(C2(1, C2(1, a[0], a[1]), IMM(0)));
}
static V L847(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L848, 2, 1, (V[]){a[0]}));
}
static V L845(V *a) {
return F_Parser_dbind(F_P_dexpect(S846()), mk_clo(L847, 2, 1, (V[]){a[0]}));
}
static V F_P_dbind_darr(V a0, V a1) {
top:;
V s835 = a1;
if ((s835) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L836, 2, 1, (V[]){a0}));
} else if ((s835) == IMM(0)) {
return F_Parser_dbind(F_P_dskip__ann(), mk_clo(L845, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbind_darr(V *a) { (void)a; return F_P_dbind_darr(a[0], a[1]); }
static V S849(void) { static V c; return STRC(c, "="); }
static V S850(void) { static V c; return STRC(c, ":"); }
static V S853(void) { static V c; return STRC(c, "="); }
static V L855(V *a) {
return F_Parser_dpure(F_P_dlets_dpar(a[0], a[1]));
}
static V L854(V *a) {
return F_Parser_dbind(F_P_dexprs__n(F_List_dlength(a[0])), mk_clo(L855, 2, 1, (V[]){a[0]}));
}
static V L852(V *a) {
return F_Parser_dbind(F_P_dexpect(S853()), mk_clo(L854, 2, 1, (V[]){a[0]}));
}
static V L851(V *a) {
return F_Parser_dbind(F_P_dskip__ann(), mk_clo(L852, 2, 1, (V[]){a[0]}));
}
static V F_P_dlet__stmt(void) {
top:;
return F_Parser_dbind(F_P_dpat__seq(C2(1, S849(), C2(1, S850(), IMM(0)))), mk_clo(L851, 1, 0, 0));
}
static V W_P_dlet__stmt(V *a) { (void)a; return F_P_dlet__stmt(); }
static V S856(void) { static V c; return STRC(c, "%par"); }
static V S857(void) { static V c; return STRC(c, "%par"); }
static V F_P_dlets_dpar(V a0, V a1) {
top:;
return F_Bool_dpick(F_Nat_dis__gt(F_List_dlength(a0), 1u), C2(1, C2(0, C2(1, S856(), a0), C2(6, S857(), a1)), IMM(0)), F_P_dlets(a0, a1));
}
static V W_P_dlets_dpar(V *a) { (void)a; return F_P_dlets_dpar(a[0], a[1]); }
static V F_P_dlets(V a0, V a1) {
top:;
V s858 = a0;
V s859 = a1;
if (TAG(s858) == 1 && TAG(s859) == 1) {
return C2(1, C2(0, FLD(s858, 0), FLD(s859, 0)), F_P_dlets(FLD(s858, 1), FLD(s859, 1)));
} else {
return IMM(0);
}
}
static V W_P_dlets(V *a) { (void)a; return F_P_dlets(a[0], a[1]); }
static V W_Nat_dis__gt(V *a) { (void)a; return F_Nat_dis__gt(a[0], a[1]); }
static V L862(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L861(V *a) {
return F_Parser_dbind(F_P_dexprs__n(a[0]), mk_clo(L862, 2, 1, (V[]){a[1]}));
}
static V F_P_dexprs__n(V a0) {
top:;
V s860 = a0;
if ((s860) == 0) {
return F_Parser_dpure(IMM(0));
} else if (nat_ge(s860, 1)) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L861, 2, 1, (V[]){nat_subk(s860, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dexprs__n(V *a) { (void)a; return F_P_dexprs__n(a[0]); }
static V L863(V *a) {
return F_P_dpat__seq_dgo(a[0], a[1], F_P_dpat__seq_dstop(a[0], a[1]));
}
static V F_P_dpat__seq(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L863, 2, 1, (V[]){a0}));
}
static V W_P_dpat__seq(V *a) { (void)a; return F_P_dpat__seq(a[0]); }
static V F_P_dpat__seq_dstop(V a0, V a1) {
top:;
return F_Bool_dor(F_P_dstuck(F_P_dtok__kind(a1)), F_Bool_dor(F_P_dis__nl(a1), F_Nat_dis__lt(F_P_dtok__which(a1, a0), F_List_dlength(a0))));
}
static V W_P_dpat__seq_dstop(V *a) { (void)a; return F_P_dpat__seq_dstop(a[0], a[1]); }
static V L866(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L865(V *a) {
return F_Parser_dbind(F_P_dpat__seq(a[0]), mk_clo(L866, 2, 1, (V[]){a[1]}));
}
static V F_P_dpat__seq_dgo(V a0, V a1, V a2) {
top:;
V s864 = a2;
if ((s864) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s864) == IMM(0)) {
return F_Parser_dbind(F_P_dpat(), mk_clo(L865, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat__seq_dgo(V *a) { (void)a; return F_P_dpat__seq_dgo(a[0], a[1], a[2]); }
static V S869(void) { static V c; return STRC(c, "<>"); }
static V L868(V *a) {
return F_P_dpat_dcons(a[0], F_P_dtok__is(a[1], S869()));
}
static V L867(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L868, 2, 1, (V[]){a[0]}));
}
static V F_P_dpat(void) {
top:;
return F_Parser_dbind(F_P_dpat1(), mk_clo(L867, 1, 0, 0));
}
static V W_P_dpat(V *a) { (void)a; return F_P_dpat(); }
static V S873(void) { static V c; return STRC(c, "Con"); }
static V L872(V *a) {
return F_Parser_dpure(C2(1, S873(), C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V L871(V *a) {
return F_Parser_dbind(F_P_dpat(), mk_clo(L872, 2, 1, (V[]){a[0]}));
}
static V F_P_dpat_dcons(V a0, V a1) {
top:;
V s870 = a1;
if ((s870) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L871, 2, 1, (V[]){a0}));
} else if ((s870) == IMM(0)) {
return F_Parser_dpure(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat_dcons(V *a) { (void)a; return F_P_dpat_dcons(a[0], a[1]); }
static V L874(V *a) {
return F_P_dpat1_dk(F_P_dtok__kind(a[0]));
}
static V F_P_dpat1(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L874, 1, 0, 0));
}
static V W_P_dpat1(V *a) { (void)a; return F_P_dpat1(); }
static V S878(void) { static V c; return STRC(c, "{"); }
static V L877(V *a) {
return F_P_dpat_did(a[0], F_Bool_dand(F_P_dtok__is(a[1], S878()), F_Bool_dnot(F_P_dtok__sp(a[1]))));
}
static V L876(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L877, 2, 1, (V[]){a[0]}));
}
static V L879(V *a) {
return F_Parser_dpure(C1(2, a[0]));
}
static V L881(V *a) {
return F_Parser_dpure(C2(3, a[0], a[1]));
}
static V L880(V *a) {
return F_Parser_dbind(F_P_dpat1(), mk_clo(L881, 2, 1, (V[]){a[0]}));
}
static V L882(V *a) {
return F_Parser_dpure(C1(4, a[0]));
}
static V L883(V *a) {
return F_Parser_dpure(C1(4, a[0]));
}
static V L884(V *a) {
return F_Parser_dpure(F_P_dpstr(a[0]));
}
static V S885(void) { static V c; return STRC(c, "+"); }
static V S886(void) { static V c; return STRC(c, "-"); }
static V S887(void) { static V c; return STRC(c, "("); }
static V S888(void) { static V c; return STRC(c, "["); }
static V S889(void) { static V c; return STRC(c, "expected a pattern"); }
static V S891(void) { static V c; return STRC(c, "_"); }
static V L890(V *a) {
return F_Parser_dpure(C1(0, S891()));
}
static V F_P_dpat1_dk(V a0) {
top:;
V s875 = a0;
if (TAG(s875) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L876, 2, 1, (V[]){FLD(s875, 0)}));
} else if (TAG(s875) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L879, 2, 1, (V[]){FLD(s875, 0)}));
} else if (TAG(s875) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L880, 2, 1, (V[]){FLD(s875, 0)}));
} else if (TAG(s875) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L882, 2, 1, (V[]){FLD(s875, 0)}));
} else if (TAG(s875) == 5) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L883, 2, 1, (V[]){FLD(s875, 0)}));
} else if (TAG(s875) == 6) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L884, 2, 1, (V[]){FLD(s875, 0)}));
} else if (TAG(s875) == 7) {
return F_P_dpat_dsym(F_P_dwhich(FLD(s875, 0), C2(1, S885(), C2(1, S886(), C2(1, S887(), C2(1, S888(), IMM(0)))))));
} else {
return F_Parser_dbind(F_P_derr(S889()), mk_clo(L890, 1, 0, 0));
}
}
static V W_P_dpat1_dk(V *a) { (void)a; return F_P_dpat1_dk(a[0]); }
static V L893(V *a) {
return F_P_dpat1();
}
static V L894(V *a) {
return F_P_dpat1();
}
static V S896(void) { static V c; return STRC(c, ")"); }
static V L897(V *a) {
return F_Parser_dpure(F_P_dptuple(a[0]));
}
static V L895(V *a) {
return F_Parser_dbind(F_P_dpats(S896()), mk_clo(L897, 1, 0, 0));
}
static V S899(void) { static V c; return STRC(c, "]"); }
static V L900(V *a) {
return F_Parser_dpure(F_P_dplist(a[0]));
}
static V L898(V *a) {
return F_Parser_dbind(F_P_dpats(S899()), mk_clo(L900, 1, 0, 0));
}
static V S901(void) { static V c; return STRC(c, "expected a pattern"); }
static V S903(void) { static V c; return STRC(c, "_"); }
static V L902(V *a) {
return F_Parser_dpure(C1(0, S903()));
}
static V F_P_dpat_dsym(V a0) {
top:;
V s892 = a0;
if ((s892) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L893, 1, 0, 0));
} else if ((s892) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L894, 1, 0, 0));
} else if ((s892) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L895, 1, 0, 0));
} else if ((s892) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L898, 1, 0, 0));
} else if (nat_ge(s892, 4)) {
return F_Parser_dbind(F_P_derr(S901()), mk_clo(L902, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat_dsym(V *a) { (void)a; return F_P_dpat_dsym(a[0]); }
static V S905(void) { static V c; return STRC(c, "Nil"); }
static V S906(void) { static V c; return STRC(c, "Con"); }
static V F_P_dplist(V a0) {
top:;
V s904 = a0;
if ((s904) == IMM(0)) {
return C2(1, S905(), IMM(0));
} else if (TAG(s904) == 1) {
return C2(1, S906(), C2(1, FLD(s904, 0), C2(1, F_P_dplist(FLD(s904, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dplist(V *a) { (void)a; return F_P_dplist(a[0]); }
static V L907(V *a) {
return F_P_dpats_dgo(a[0], a[1], F_P_dstuck(F_P_dtok__kind(a[1])));
}
static V F_P_dpats(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L907, 2, 1, (V[]){a0}));
}
static V W_P_dpats(V *a) { (void)a; return F_P_dpats(a[0]); }
static V F_P_dpats_dgo(V a0, V a1, V a2) {
top:;
V s908 = a2;
if ((s908) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s908) == IMM(0)) {
return F_P_dpats_dclose(a0, F_P_dtok__is(a1, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpats_dgo(V *a) { (void)a; return F_P_dpats_dgo(a[0], a[1], a[2]); }
static V L910(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dpats_dclose(V a0, V a1) {
top:;
V s909 = a1;
if ((s909) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L910, 1, 0, 0));
} else if ((s909) == IMM(0)) {
return F_P_dpats_ditem(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dpats_dclose(V *a) { (void)a; return F_P_dpats_dclose(a[0], a[1]); }
static V S912(void) { static V c; return STRC(c, ","); }
static V L914(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L913(V *a) {
return F_Parser_dbind(F_P_dpats_dmore(a[1], a[2]), mk_clo(L914, 2, 1, (V[]){a[0]}));
}
static V L911(V *a) {
return F_Parser_dbind(F_P_deat(S912()), mk_clo(L913, 3, 2, (V[]){a[1], a[0]}));
}
static V F_P_dpats_ditem(V a0) {
top:;
return F_Parser_dbind(F_P_dpat(), mk_clo(L911, 2, 1, (V[]){a0}));
}
static V W_P_dpats_ditem(V *a) { (void)a; return F_P_dpats_ditem(a[0]); }
static V L916(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dpats_dmore(V a0, V a1) {
top:;
V s915 = a1;
if ((s915) == IMM(1)) {
return F_P_dpats(a0);
} else if ((s915) == IMM(0)) {
return F_Parser_dbind(F_P_dexpect(a0), mk_clo(L916, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpats_dmore(V *a) { (void)a; return F_P_dpats_dmore(a[0], a[1]); }
static V S918(void) { static V c; return STRC(c, "Unit"); }
static V S919(void) { static V c; return STRC(c, "Tuple"); }
static V F_P_dptuple(V a0) {
top:;
V s917 = a0;
if ((s917) == IMM(0)) {
return C2(1, S918(), IMM(0));
} else if (TAG(s917) == 1 && (FLD(s917, 1)) == IMM(0)) {
return FLD(s917, 0);
} else if (TAG(s917) == 1) {
return C2(1, S919(), C2(1, FLD(s917, 0), C2(1, F_P_dptuple(FLD(s917, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dptuple(V *a) { (void)a; return F_P_dptuple(a[0]); }
static V S921(void) { static V c; return STRC(c, "SNil"); }
static V S922(void) { static V c; return STRC(c, "SCon"); }
static V F_P_dpstr(V a0) {
top:;
V s920 = a0;
if ((s920) == IMM(0)) {
return C2(1, S921(), IMM(0));
} else if (TAG(s920) == 1) {
return C2(1, S922(), C2(1, C1(4, FLD(s920, 0)), C2(1, F_P_dpstr(FLD(s920, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpstr(V *a) { (void)a; return F_P_dpstr(a[0]); }
static V S925(void) { static V c; return STRC(c, "}"); }
static V L926(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L924(V *a) {
return F_Parser_dbind(F_P_dpats(S925()), mk_clo(L926, 2, 1, (V[]){a[0]}));
}
static V F_P_dpat_did(V a0, V a1) {
top:;
V s923 = a1;
if ((s923) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L924, 2, 1, (V[]){a0}));
} else if ((s923) == IMM(0)) {
return F_Parser_dpure(C1(0, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat_did(V *a) { (void)a; return F_P_dpat_did(a[0], a[1]); }
static V L927(V *a) {
return F_P_dscan_dret(a[0]);
}
static V F_P_dscan(void) {
top:;
return mk_clo(L927, 1, 0, 0);
}
static V W_P_dscan(V *a) { (void)a; return F_P_dscan(); }
static V F_P_dscan_dret(V a0) {
top:;
return C2(0, F_P_dscan_dgo(a0, 0u), a0);
}
static V W_P_dscan_dret(V *a) { (void)a; return F_P_dscan_dret(a[0]); }
static V S929(void) { static V c; return STRC(c, "="); }
static V S930(void) { static V c; return STRC(c, "<-"); }
static V S931(void) { static V c; return STRC(c, "("); }
static V S932(void) { static V c; return STRC(c, "["); }
static V S933(void) { static V c; return STRC(c, "{"); }
static V S934(void) { static V c; return STRC(c, ")"); }
static V S935(void) { static V c; return STRC(c, "]"); }
static V S936(void) { static V c; return STRC(c, "}"); }
static V F_P_dscan_dgo(V a0, V a1) {
top:;
V s928 = a0;
if ((s928) == IMM(0)) {
return 0u;
} else if (TAG(s928) == 1 && TAG(FLD(FLD(s928, 0), 0)) == 7) {
return F_P_dscan_dsym(FLD(s928, 1), a1, F_P_dwhich(FLD(FLD(FLD(s928, 0), 0), 0), C2(1, S929(), C2(1, S930(), C2(1, S931(), C2(1, S932(), C2(1, S933(), C2(1, S934(), C2(1, S935(), C2(1, S936(), IMM(0)))))))))));
} else if (TAG(s928) == 1 && TAG(FLD(FLD(s928, 0), 0)) == 0) {
{ V t0 = FLD(s928, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else if (TAG(s928) == 1 && (FLD(FLD(s928, 0), 0)) == IMM(8)) {
return F_P_dscan_dend(FLD(s928, 1), a1, F_U32_dis__zero(a1));
} else if (TAG(s928) == 1 && (FLD(FLD(s928, 0), 0)) == IMM(9)) {
return 0u;
} else if (TAG(s928) == 1 && (FLD(FLD(s928, 0), 0)) == IMM(10)) {
return 0u;
} else if (TAG(s928) == 1 && (FLD(FLD(s928, 0), 0)) == IMM(11)) {
return 0u;
} else if (TAG(s928) == 1 && TAG(FLD(FLD(s928, 0), 0)) == 12) {
return 0u;
} else if (TAG(s928) == 1) {
{ V t0 = FLD(s928, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dgo(V *a) { (void)a; return F_P_dscan_dgo(a[0], a[1]); }
static V F_P_dscan_dend(V a0, V a1, V a2) {
top:;
V s937 = a2;
if ((s937) == IMM(1)) {
return 0u;
} else if ((s937) == IMM(0)) {
return F_P_dscan_dgo(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dend(V *a) { (void)a; return F_P_dscan_dend(a[0], a[1], a[2]); }
static V F_P_dscan_dsym(V a0, V a1, V a2) {
top:;
V s938 = a2;
if ((s938) == 0) {
return F_P_dscan_dtop(a0, a1, 1u, F_U32_dis__zero(a1));
} else if ((s938) == 1) {
return F_P_dscan_dtop(a0, a1, 2u, F_U32_dis__zero(a1));
} else if ((s938) == 2) {
return F_P_dscan_dgo(a0, F_U32_dinc(a1));
} else if ((s938) == 3) {
return F_P_dscan_dgo(a0, F_U32_dinc(a1));
} else if ((s938) == 4) {
return F_P_dscan_dgo(a0, F_U32_dinc(a1));
} else if ((s938) == 5) {
return F_P_dscan_dgo(a0, F_U32_dsub(a1, 1u));
} else if ((s938) == 6) {
return F_P_dscan_dgo(a0, F_U32_dsub(a1, 1u));
} else if ((s938) == 7) {
return F_P_dscan_dgo(a0, F_U32_dsub(a1, 1u));
} else if (nat_ge(s938, 8)) {
return F_P_dscan_dgo(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dsym(V *a) { (void)a; return F_P_dscan_dsym(a[0], a[1], a[2]); }
static V F_P_dscan_dtop(V a0, V a1, V a2, V a3) {
top:;
V s939 = a3;
if ((s939) == IMM(1)) {
return a2;
} else if ((s939) == IMM(0)) {
return F_P_dscan_dgo(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dtop(V *a) { (void)a; return F_P_dscan_dtop(a[0], a[1], a[2], a[3]); }
static V S942(void) { static V c; return STRC(c, "<"); }
static V S945(void) { static V c; return STRC(c, ":"); }
static V L948(V *a) {
return F_Parser_dpure(F_Fold_ddo(a[1], F_P_dinit(a[0]), F_P_dlast(a[0]), a[2]));
}
static V L947(V *a) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L948, 3, 2, (V[]){a[0], a[1]}));
}
static V L946(V *a) {
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L947, 3, 2, (V[]){a[0], a[1]}));
}
static V L944(V *a) {
return F_Parser_dbind(F_P_dexpect(S945()), mk_clo(L946, 3, 2, (V[]){a[1], a[0]}));
}
static V L943(V *a) {
return F_Parser_dbind(F_P_dtyargs(), mk_clo(L944, 2, 1, (V[]){a[0]}));
}
static V L941(V *a) {
return F_Parser_dbind(F_P_dexpect(S942()), mk_clo(L943, 2, 1, (V[]){a[0]}));
}
static V L940(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L941, 1, 0, 0));
}
static V F_P_ddo(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L940, 1, 0, 0));
}
static V W_P_ddo(V *a) { (void)a; return F_P_ddo(); }
static V S950(void) { static V c; return STRC(c, ""); }
static V F_P_dlast(V a0) {
top:;
V s949 = a0;
if ((s949) == IMM(0)) {
return C2(14, S950(), IMM(0));
} else if (TAG(s949) == 1 && (FLD(s949, 1)) == IMM(0)) {
return FLD(s949, 0);
} else if (TAG(s949) == 1) {
{ V t0 = FLD(s949, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dlast(V *a) { (void)a; return F_P_dlast(a[0]); }
static V F_P_dinit(V a0) {
top:;
V s951 = a0;
if ((s951) == IMM(0)) {
return IMM(0);
} else if (TAG(s951) == 1 && (FLD(s951, 1)) == IMM(0)) {
return IMM(0);
} else if (TAG(s951) == 1) {
return C2(1, FLD(s951, 0), F_P_dinit(FLD(s951, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dinit(V *a) { (void)a; return F_P_dinit(a[0]); }
static V S953(void) { static V c; return STRC(c, "empty do block"); }
static V S954(void) { static V c; return STRC(c, "pure"); }
static V S955(void) { static V c; return STRC(c, ""); }
static V S956(void) { static V c; return STRC(c, "bind"); }
static V S957(void) { static V c; return STRC(c, ""); }
static V S958(void) { static V c; return STRC(c, "pure"); }
static V S959(void) { static V c; return STRC(c, "bind"); }
static V S960(void) { static V c; return STRC(c, ""); }
static V S961(void) { static V c; return STRC(c, "_"); }
static V F_Fold_ddo(V a0, V a1, V a2, V a3) {
top:;
V s952 = a3;
if ((s952) == IMM(0)) {
return C1(15, S953());
} else if (TAG(s952) == 1 && TAG(FLD(s952, 0)) == 0 && (FLD(s952, 1)) == IMM(0)) {
return FLD(FLD(s952, 0), 1);
} else if (TAG(s952) == 1 && TAG(FLD(s952, 0)) == 1 && (FLD(s952, 1)) == IMM(0)) {
return FLD(FLD(s952, 0), 1);
} else if (TAG(s952) == 1 && TAG(FLD(s952, 0)) == 2 && (FLD(s952, 1)) == IMM(0)) {
return F_Fold_dapp(a0, S954(), a1, C2(1, a2, C2(1, FLD(FLD(s952, 0), 0), IMM(0))));
} else if (TAG(s952) == 1 && TAG(FLD(s952, 0)) == 3 && (FLD(s952, 1)) == IMM(0)) {
return FLD(FLD(s952, 0), 0);
} else if (TAG(s952) == 1 && (FLD(s952, 0)) == IMM(4) && (FLD(s952, 1)) == IMM(0)) {
return C2(14, S955(), IMM(0));
} else if (TAG(s952) == 1 && TAG(FLD(s952, 0)) == 0) {
return C3(8, FLD(FLD(s952, 0), 0), FLD(FLD(s952, 0), 1), F_Fold_ddo(a0, a1, a2, FLD(s952, 1)));
} else if (TAG(s952) == 1 && TAG(FLD(s952, 0)) == 1) {
return F_Fold_dapp(a0, S956(), a1, C2(1, C2(14, S957(), IMM(0)), C2(1, a2, C2(1, FLD(FLD(s952, 0), 1), C2(1, C2(7, C1(0, FLD(FLD(s952, 0), 0)), F_Fold_ddo(a0, a1, a2, FLD(s952, 1))), IMM(0))))));
} else if (TAG(s952) == 1 && TAG(FLD(s952, 0)) == 2) {
return F_Fold_dapp(a0, S958(), a1, C2(1, a2, C2(1, FLD(FLD(s952, 0), 0), IMM(0))));
} else if (TAG(s952) == 1 && TAG(FLD(s952, 0)) == 3) {
return F_Fold_dapp(a0, S959(), a1, C2(1, C2(14, S960(), IMM(0)), C2(1, a2, C2(1, FLD(FLD(s952, 0), 0), C2(1, C2(7, C1(0, S961()), F_Fold_ddo(a0, a1, a2, FLD(s952, 1))), IMM(0))))));
} else if (TAG(s952) == 1 && (FLD(s952, 0)) == IMM(4)) {
{ V t0 = a0; V t1 = a1; V t2 = a2; V t3 = FLD(s952, 1); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Fold_ddo(V *a) { (void)a; return F_Fold_ddo(a[0], a[1], a[2], a[3]); }
static V S962(void) { static V c; return STRC(c, "."); }
static V F_Fold_dapp(V a0, V a1, V a2, V a3) {
top:;
return C2(5, C1(0, F_String_dappend(a0, F_String_dappend(S962(), a1))), F_List_dappend(a2, a3));
}
static V W_Fold_dapp(V *a) { (void)a; return F_Fold_dapp(a[0], a[1], a[2], a[3]); }
static V S965(void) { static V c; return STRC(c, ":"); }
static V L968(V *a) {
return F_Parser_dpure(C2(9, a[0], a[1]));
}
static V L967(V *a) {
return F_Parser_dbind(F_P_dmatch_dbody(F_P_dis__in(a[1])), mk_clo(L968, 2, 1, (V[]){a[0]}));
}
static V L966(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L967, 2, 1, (V[]){a[0]}));
}
static V L964(V *a) {
return F_Parser_dbind(F_P_dexpect(S965()), mk_clo(L966, 2, 1, (V[]){a[0]}));
}
static V L963(V *a) {
return F_Parser_dbind(F_P_dscrs(), mk_clo(L964, 1, 0, 0));
}
static V F_P_dmatch(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L963, 1, 0, 0));
}
static V W_P_dmatch(V *a) { (void)a; return F_P_dmatch(); }
static V L970(V *a) {
return F_P_dcases();
}
static V F_P_dmatch_dbody(V a0) {
top:;
V s969 = a0;
if ((s969) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L970, 1, 0, 0));
} else if ((s969) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dmatch_dbody(V *a) { (void)a; return F_P_dmatch_dbody(a[0]); }
static V L972(V *a) {
return F_P_dcases_dde(F_P_dis__de(a[0]));
}
static V L971(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L972, 1, 0, 0));
}
static V F_P_dcases(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L971, 1, 0, 0));
}
static V W_P_dcases(V *a) { (void)a; return F_P_dcases(); }
static V L974(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S976(void) { static V c; return STRC(c, "case"); }
static V L975(V *a) {
return F_P_dcases_dgo(F_P_dtok__which__id(a[0], C2(1, S976(), IMM(0))));
}
static V F_P_dcases_dde(V a0) {
top:;
V s973 = a0;
if ((s973) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L974, 1, 0, 0));
} else if ((s973) == IMM(0)) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L975, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dcases_dde(V *a) { (void)a; return F_P_dcases_dde(a[0]); }
static V S979(void) { static V c; return STRC(c, ":"); }
static V S981(void) { static V c; return STRC(c, ":"); }
static V L984(V *a) {
return F_Parser_dpure(C2(1, C2(10, a[1], a[0]), a[2]));
}
static V L983(V *a) {
return F_Parser_dbind(F_P_dcases(), mk_clo(L984, 3, 2, (V[]){a[1], a[0]}));
}
static V L982(V *a) {
return F_Parser_dbind(F_P_dbody(), mk_clo(L983, 2, 1, (V[]){a[0]}));
}
static V L980(V *a) {
return F_Parser_dbind(F_P_dexpect(S981()), mk_clo(L982, 2, 1, (V[]){a[0]}));
}
static V L978(V *a) {
return F_Parser_dbind(F_P_dpat__seq(C2(1, S979(), IMM(0))), mk_clo(L980, 1, 0, 0));
}
static V F_P_dcases_dgo(V a0) {
top:;
V s977 = a0;
if ((s977) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L978, 1, 0, 0));
} else if (nat_ge(s977, 1)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dcases_dgo(V *a) { (void)a; return F_P_dcases_dgo(a[0]); }
static V L986(V *a) {
return F_Parser_dpure(F_Fold_dplain(a[0]));
}
static V L985(V *a) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L986, 1, 0, 0));
}
static V F_P_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L985, 1, 0, 0));
}
static V W_P_dbody(V *a) { (void)a; return F_P_dbody(); }
static V S988(void) { static V c; return STRC(c, ":"); }
static V L987(V *a) {
return F_P_dscrs_dgo(a[0], F_Bool_dor(F_P_dtok__is(a[0], S988()), F_P_dstuck(F_P_dtok__kind(a[0]))));
}
static V F_P_dscrs(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L987, 1, 0, 0));
}
static V W_P_dscrs(V *a) { (void)a; return F_P_dscrs(); }
static V L991(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L990(V *a) {
return F_Parser_dbind(F_P_dscrs(), mk_clo(L991, 2, 1, (V[]){a[0]}));
}
static V F_P_dscrs_dgo(V a0, V a1) {
top:;
V s989 = a1;
if ((s989) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s989) == IMM(0)) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L990, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dscrs_dgo(V *a) { (void)a; return F_P_dscrs_dgo(a[0], a[1]); }
static V L992(V *a) {
return F_P_deff_dgo(a[0], IMM(0));
}
static V F_P_deff_dimports(void) {
top:;
return mk_clo(L992, 1, 0, 0);
}
static V W_P_deff_dimports(V *a) { (void)a; return F_P_deff_dimports(); }
static V F_P_deff_dgo(V a0, V a1) {
top:;
V s993 = a0;
if ((s993) == IMM(0)) {
return C2(0, a1, IMM(0));
} else if (TAG(s993) == 1 && TAG(FLD(FLD(s993, 0), 0)) == 6) {
{ V t0 = FLD(s993, 1); V t1 = F_List_dappend(a1, C2(1, FLD(FLD(FLD(s993, 0), 0), 0), IMM(0))); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s993) == 1 && (FLD(FLD(s993, 0), 0)) == IMM(10)) {
return C2(0, a1, FLD(s993, 1));
} else if (TAG(s993) == 1 && (FLD(FLD(s993, 0), 0)) == IMM(11)) {
return C2(0, a1, C2(1, C3(0, IMM(11), FLD(FLD(s993, 0), 1), FLD(FLD(s993, 0), 2)), FLD(s993, 1)));
} else if (TAG(s993) == 1 && TAG(FLD(FLD(s993, 0), 0)) == 12) {
return C2(0, a1, C2(1, C3(0, C1(12, FLD(FLD(FLD(s993, 0), 0), 0)), FLD(FLD(s993, 0), 1), FLD(FLD(s993, 0), 2)), FLD(s993, 1)));
} else if (TAG(s993) == 1) {
{ V t0 = FLD(s993, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_deff_dgo(V *a) { (void)a; return F_P_deff_dgo(a[0], a[1]); }
static V L995(V *a) {
return F_P_dexpr();
}
static V S996(void) { static V c; return STRC(c, ""); }
static V F_P_dret_dgo(V a0) {
top:;
V s994 = a0;
if ((s994) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L995, 1, 0, 0));
} else if ((s994) == IMM(0)) {
return F_Parser_dpure(C2(14, S996(), IMM(0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dret_dgo(V *a) { (void)a; return F_P_dret_dgo(a[0]); }
static V S998(void) { static V c; return STRC(c, ")"); }
static V L997(V *a) {
return F_P_dparams_dgo(F_Bool_dor(F_P_dtok__is(a[0], S998()), F_P_dstuck(F_P_dtok__kind(a[0]))));
}
static V F_P_dparams(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L997, 1, 0, 0));
}
static V W_P_dparams(V *a) { (void)a; return F_P_dparams(); }
static V L1000(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S1002(void) { static V c; return STRC(c, ","); }
static V L1004(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L1003(V *a) {
return F_Parser_dbind(F_P_dparams_dmore(a[1]), mk_clo(L1004, 2, 1, (V[]){a[0]}));
}
static V L1001(V *a) {
return F_Parser_dbind(F_P_deat(S1002()), mk_clo(L1003, 2, 1, (V[]){a[0]}));
}
static V F_P_dparams_dgo(V a0) {
top:;
V s999 = a0;
if ((s999) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L1000, 1, 0, 0));
} else if ((s999) == IMM(0)) {
return F_Parser_dbind(F_P_dparam(), mk_clo(L1001, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparams_dgo(V *a) { (void)a; return F_P_dparams_dgo(a[0]); }
static V S1006(void) { static V c; return STRC(c, ")"); }
static V L1007(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dparams_dmore(V a0) {
top:;
V s1005 = a0;
if ((s1005) == IMM(1)) {
return F_P_dparams();
} else if ((s1005) == IMM(0)) {
return F_Parser_dbind(F_P_dexpect(S1006()), mk_clo(L1007, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparams_dmore(V *a) { (void)a; return F_P_dparams_dmore(a[0]); }
static V F_P_dfile_dfin(V a0) {
top:;
V v1008 = a0;
return C2(0, FLD(v1008, 0), F_P_dfile_derr(FLD(v1008, 1)));
}
static V W_P_dfile_dfin(V *a) { (void)a; return F_P_dfile_dfin(a[0]); }
static V S1010(void) { static V c; return STRC(c, ""); }
static V F_P_dfile_derr(V a0) {
top:;
V s1009 = a0;
if (TAG(s1009) == 1 && TAG(FLD(FLD(s1009, 0), 0)) == 12) {
return FLD(FLD(FLD(s1009, 0), 0), 0);
} else {
return S1010();
}
}
static V W_P_dfile_derr(V *a) { (void)a; return F_P_dfile_derr(a[0]); }
static V F_Main_dparse_dfin(V a0) {
top:;
V v1011 = a0;
return F_Bool_dpick(F_String_dis__empty(FLD(v1011, 1)), C1(1, FLD(v1011, 0)), C1(0, FLD(v1011, 1)));
}
static V W_Main_dparse_dfin(V *a) { (void)a; return F_Main_dparse_dfin(a[0]); }
static V F_String_dis__empty(V a0) {
top:;
V s1012 = a0;
if ((s1012) == IMM(0)) {
return IMM(1);
} else if (TAG(s1012) == 1) {
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
V s1013 = a0;
if ((s1013) == IMM(0)) {
return IMM(0);
} else if (TAG(s1013) == 1) {
return F_Mod_ddir_dif(FLD(s1013, 0), FLD(s1013, 1), F_U32_dis__eq(FLD(s1013, 0), 47u));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddir_dgo(V *a) { (void)a; return F_Mod_ddir_dgo(a[0]); }
static V F_Mod_ddir_dif(V a0, V a1, V a2) {
top:;
V s1014 = a2;
if ((s1014) == IMM(1)) {
return C2(1, a0, a1);
} else if ((s1014) == IMM(0)) {
return F_Mod_ddir_dgo(a1);
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddir_dif(V *a) { (void)a; return F_Mod_ddir_dif(a[0], a[1], a[2]); }
static V F_Main_dresolve(V a0, V a1) {
top:;
V s1015 = a1;
if (TAG(s1015) == 0) {
return C1(0, FLD(s1015, 0));
} else if (TAG(s1015) == 1) {
return C1(1, F_Eff_ddecls(a0, FLD(s1015, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dresolve(V *a) { (void)a; return F_Main_dresolve(a[0], a[1]); }
static V F_Eff_ddecls(V a0, V a1) {
top:;
V s1016 = a1;
if ((s1016) == IMM(0)) {
return IMM(0);
} else if (TAG(s1016) == 1) {
return C2(1, F_Eff_ddecl(a0, FLD(s1016, 0)), F_Eff_ddecls(a0, FLD(s1016, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Eff_ddecls(V *a) { (void)a; return F_Eff_ddecls(a[0], a[1]); }
static V F_Eff_ddecl(V a0, V a1) {
top:;
V s1017 = a1;
if (TAG(s1017) == 1) {
return C3(1, FLD(s1017, 0), FLD(s1017, 1), F_Eff_dpaths(a0, FLD(s1017, 2)));
} else {
return s1017;
}
}
static V W_Eff_ddecl(V *a) { (void)a; return F_Eff_ddecl(a[0], a[1]); }
static V F_Eff_dpaths(V a0, V a1) {
top:;
V s1018 = a1;
if ((s1018) == IMM(0)) {
return IMM(0);
} else if (TAG(s1018) == 1) {
return C2(1, F_Eff_dpath(a0, FLD(s1018, 0)), F_Eff_dpaths(a0, FLD(s1018, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Eff_dpaths(V *a) { (void)a; return F_Eff_dpaths(a[0], a[1]); }
static V S1019(void) { static V c; return STRC(c, "/"); }
static V F_Eff_dpath(V a0, V a1) {
top:;
return F_Bool_dpick(F_String_dstarts__with(a1, S1019()), a1, F_String_dappend(a0, a1));
}
static V W_Eff_dpath(V *a) { (void)a; return F_Eff_dpath(a[0], a[1]); }
static V S1022(void) { static V c; return STRC(c, "bendc: parse error in base: "); }
static V S1023(void) { static V c; return STRC(c, "bendc: parse error: "); }
static V F_Main_dcompile(V a0, V a1) {
top:;
V s1020 = a0;
V s1021 = a1;
if (TAG(s1020) == 0) {
return F_IO_ddie(1u, F_String_dappend(S1022(), FLD(s1020, 0)));
} else if (TAG(s1020) == 1 && TAG(s1021) == 0) {
return F_IO_ddie(1u, F_String_dappend(S1023(), FLD(s1021, 0)));
} else if (TAG(s1020) == 1 && TAG(s1021) == 1) {
return F_Main_demit(F_Gen_dprogram(F_List_dappend(FLD(s1020, 0), FLD(s1021, 0))));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dcompile(V *a) { (void)a; return F_Main_dcompile(a[0], a[1]); }
static V F_Gen_dprogram(V a0) {
top:;
V v1024 = F_G_dnew(a0);
return F_Gen_dprogram_dfin(F_Gen_dcids(v1024, a0, 0u), apply(F_Gen_dprogram_dm(v1024), CN(0, 7, (V[]){0u, IMM(0), IMM(0), IMM(0), IMM(0), IMM(0), IMM(0)})));
}
static V W_Gen_dprogram(V *a) { (void)a; return F_Gen_dprogram(a[0]); }
static V S1025(void) { static V c; return STRC(c, "main"); }
static V S1027(void) { static V c; return STRC(c, "main"); }
static V L1026(V *a) {
return F_Gen_dentry(a[0], F_G_dbody(a[0], S1027()));
}
static V F_Gen_dprogram_dm(V a0) {
top:;
return F_Gen_dbind(F_Gen_dall(a0, C2(1, S1025(), IMM(0)), F_Set_dnew()), mk_clo(L1026, 2, 1, (V[]){a0}));
}
static V W_Gen_dprogram_dm(V *a) { (void)a; return F_Gen_dprogram_dm(a[0]); }
static V S1029(void) { static V c; return STRC(c, ""); }
static V S1030(void) { static V c; return STRC(c, ""); }
static V F_G_dbody(V a0, V a1) {
top:;
V v1028 = a0;
return F_G_dget(C2(4, S1029(), S1030()), FLD(v1028, 2), a1);
}
static V W_G_dbody(V *a) { (void)a; return F_G_dbody(a[0], a[1]); }
static V F_G_dget(V a1, V a2, V a3) {
top:;
return F_Pair_dsnd(F_Map_dget(a1, a2, a3));
}
static V W_G_dget(V *a) { (void)a; return F_G_dget(a[1], a[2], a[3]); }
static V F_Map_dget(V a1, V a2, V a3) {
top:;
V s1031 = a2;
if ((s1031) == IMM(0)) {
return C2(0, IMM(0), a1);
} else if (TAG(s1031) == 1) {
return F_Map_dget_dleaf(a1, FLD(s1031, 1), F_String_dcmp(a3, FLD(s1031, 0)));
} else if (TAG(s1031) == 2) {
return F_Map_dget_dbit(a1, FLD(s1031, 1), FLD(s1031, 2), FLD(s1031, 0), F_Map_dbit(a3, FLD(s1031, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dget(V *a) { (void)a; return F_Map_dget(a[1], a[2], a[3]); }
static V F_Map_dget_dbit(V a1, V a2, V a3, V a4, V a5) {
top:;
V v1032 = a5;
V s1033 = FLD(v1032, 1);
if ((s1033) == IMM(0)) {
return F_Map_dlo(a4, a3, F_Map_dget(a1, a2, FLD(v1032, 0)));
} else if ((s1033) == IMM(1)) {
return F_Map_dhi(a4, a2, F_Map_dget(a1, a3, FLD(v1032, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dget_dbit(V *a) { (void)a; return F_Map_dget_dbit(a[1], a[2], a[3], a[4], a[5]); }
static V F_Map_dhi(V a3, V a4, V a5) {
top:;
V v1034 = a5;
return C2(0, C3(2, a3, a4, FLD(v1034, 0)), FLD(v1034, 1));
}
static V W_Map_dhi(V *a) { (void)a; return F_Map_dhi(a[3], a[4], a[5]); }
static V F_Map_dlo(V a3, V a4, V a5) {
top:;
V v1035 = a5;
return C2(0, C3(2, a3, FLD(v1035, 0), a4), FLD(v1035, 1));
}
static V W_Map_dlo(V *a) { (void)a; return F_Map_dlo(a[3], a[4], a[5]); }
static V F_Map_dget_dleaf(V a1, V a2, V a3) {
top:;
V v1036 = a3;
V s1037 = FLD(v1036, 1);
if ((s1037) == IMM(0)) {
return C2(0, C2(1, FLD(FLD(v1036, 0), 1), a2), a1);
} else if ((s1037) == IMM(1)) {
return C2(0, C2(1, FLD(FLD(v1036, 0), 1), a2), a2);
} else if ((s1037) == IMM(2)) {
return C2(0, C2(1, FLD(FLD(v1036, 0), 1), a2), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Map_dget_dleaf(V *a) { (void)a; return F_Map_dget_dleaf(a[1], a[2], a[3]); }
static V S1039(void) { static V c; return STRC(c, "IO"); }
static V S1040(void) { static V c; return STRC(c, "no main definition"); }
static V S1042(void) { static V c; return STRC(c, ""); }
static V L1041(V *a) {
return F_Gen_dpure(S1042());
}
static V F_Gen_dentry(V a0, V a1) {
top:;
V s1038 = a1;
if (TAG(s1038) == 0) {
return F_Gen_dentry_dty(a0, FLD(s1038, 3), F_Str_deq(F_Ty_dhead(FLD(s1038, 3)), S1039()));
} else {
return F_Gen_dbind(F_Gen_derror(S1040()), mk_clo(L1041, 1, 0, 0));
}
}
static V W_Gen_dentry(V *a) { (void)a; return F_Gen_dentry(a[0], a[1]); }
static V L1043(V *a) {
return C2(0, a[0], a[1]);
}
static V F_Gen_dpure(V a1) {
top:;
return mk_clo(L1043, 2, 1, (V[]){a1});
}
static V W_Gen_dpure(V *a) { (void)a; return F_Gen_dpure(a[1]); }
static V L1044(V *a) {
return F_Gen_derror_dgo(a[0], a[1]);
}
static V F_Gen_derror(V a0) {
top:;
return mk_clo(L1044, 2, 1, (V[]){a0});
}
static V W_Gen_derror(V *a) { (void)a; return F_Gen_derror(a[0]); }
static V F_Gen_derror_dgo(V a0, V a1) {
top:;
V v1045 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v1045, 0), FLD(v1045, 1), FLD(v1045, 2), FLD(v1045, 3), C2(1, a0, FLD(v1045, 4)), FLD(v1045, 5), FLD(v1045, 6)}));
}
static V W_Gen_derror_dgo(V *a) { (void)a; return F_Gen_derror_dgo(a[0], a[1]); }
static V L1046(V *a) {
return F_Gen_dgo(apply(a[1], a[4]), a[0]);
}
static V F_Gen_dbind(V a2, V a3) {
top:;
return mk_clo(L1046, 5, 4, (V[]){a3, a2, 0, 0});
}
static V W_Gen_dbind(V *a) { (void)a; return F_Gen_dbind(a[2], a[3]); }
static V F_Gen_dgo(V a2, V a3) {
top:;
V v1047 = a2;
return apply(apply(a3, FLD(v1047, 0)), FLD(v1047, 1));
}
static V W_Gen_dgo(V *a) { (void)a; return F_Gen_dgo(a[2], a[3]); }
static V S1049(void) { static V c; return STRC(c, "\077"); }
static V F_Ty_dhead(V a0) {
top:;
V s1048 = a0;
if (TAG(s1048) == 0) {
return FLD(s1048, 0);
} else if (TAG(s1048) == 14) {
return FLD(s1048, 0);
} else if (TAG(s1048) == 5 && TAG(FLD(s1048, 0)) == 0) {
return FLD(FLD(s1048, 0), 0);
} else {
return S1049();
}
}
static V W_Ty_dhead(V *a) { (void)a; return F_Ty_dhead(a[0]); }
static V S1051(void) { static V c; return STRC(c, "int main(int argc, char **argv) { return bend_run(argc, argv, F_main); }\012"); }
static V S1053(void) { static V c; return STRC(c, "int main(int argc, char **argv) { return bend_run_value(argc, argv, F_main, "); }
static V S1054(void) { static V c; return STRC(c, "); }\012"); }
static V L1052(V *a) {
return F_Gen_dpure(F_String_dappend(S1053(), F_String_dappend(a[0], S1054())));
}
static V F_Gen_dentry_dty(V a0, V a1, V a2) {
top:;
V s1050 = a2;
if ((s1050) == IMM(1)) {
return F_Gen_dpure(S1051());
} else if ((s1050) == IMM(0)) {
return F_Gen_dbind(F_Gen_dprinter(a0, a1), mk_clo(L1052, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dentry_dty(V *a) { (void)a; return F_Gen_dentry_dty(a[0], a[1], a[2]); }
static V L1056(V *a) {
return F_Gen_dprinter_dmemo(a[2], a[1], a[0], a[3]);
}
static V F_Gen_dprinter(V a0, V a1) {
top:;
V v1055 = F_Expr_dshow(a1);
return F_Gen_dbind(F_Gen_dmemo_dfind(v1055), mk_clo(L1056, 4, 3, (V[]){v1055, a1, a0}));
}
static V W_Gen_dprinter(V *a) { (void)a; return F_Gen_dprinter(a[0], a[1]); }
static V S1059(void) { static V c; return STRC(c, "P"); }
static V S1062(void) { static V c; return STRC(c, "static void "); }
static V S1063(void) { static V c; return STRC(c, "(V v);\012"); }
static V S1066(void) { static V c; return STRC(c, "static void "); }
static V S1067(void) { static V c; return STRC(c, "(V v) {\012"); }
static V S1068(void) { static V c; return STRC(c, "}\012"); }
static V L1069(V *a) {
return F_Gen_dpure(a[0]);
}
static V L1065(V *a) {
return F_Gen_dbind(F_Gen_dcode(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1066(), F_String_dappend(a[0], S1067()))), C2(1, a[1], C2(1, C1(1, S1068()), IMM(0)))))), mk_clo(L1069, 2, 1, (V[]){a[0]}));
}
static V L1064(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dbody(a[2], a[1], F_Ty_dhead(a[1])), mk_clo(L1065, 2, 1, (V[]){a[0]}));
}
static V L1061(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S1062(), F_String_dappend(a[2], S1063())))), mk_clo(L1064, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L1060(V *a) {
return F_Gen_dbind(F_Gen_dmemo_dadd(C2(0, a[2], a[3])), mk_clo(L1061, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V L1058(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1059(), F_U32_dshow(a[3]))), mk_clo(L1060, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Gen_dprinter_dmemo(V a0, V a1, V a2, V a3) {
top:;
V s1057 = a3;
if (TAG(s1057) == 1) {
return F_Gen_dpure(FLD(s1057, 0));
} else if ((s1057) == IMM(0)) {
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1058, 4, 3, (V[]){a1, a0, a2}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dmemo(V *a) { (void)a; return F_Gen_dprinter_dmemo(a[0], a[1], a[2], a[3]); }
static V F_Doc_dlist(V a0) {
top:;
V s1070 = a0;
if ((s1070) == IMM(0)) {
return IMM(0);
} else if (TAG(s1070) == 1) {
return C2(2, FLD(s1070, 0), F_Doc_dlist(FLD(s1070, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dlist(V *a) { (void)a; return F_Doc_dlist(a[0]); }
static V L1071(V *a) {
return F_Gen_dcode_dgo(a[0], a[1]);
}
static V F_Gen_dcode(V a0) {
top:;
return mk_clo(L1071, 2, 1, (V[]){a0});
}
static V W_Gen_dcode(V *a) { (void)a; return F_Gen_dcode(a[0]); }
static V F_Gen_dcode_dgo(V a0, V a1) {
top:;
V v1072 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v1072, 0), FLD(v1072, 1), C2(2, FLD(v1072, 2), a0), FLD(v1072, 3), FLD(v1072, 4), FLD(v1072, 5), FLD(v1072, 6)}));
}
static V W_Gen_dcode_dgo(V *a) { (void)a; return F_Gen_dcode_dgo(a[0], a[1]); }
static V S1073(void) { static V c; return STRC(c, "U32"); }
static V S1074(void) { static V c; return STRC(c, "Nat"); }
static V S1075(void) { static V c; return STRC(c, "F32"); }
static V S1076(void) { static V c; return STRC(c, "Char"); }
static V S1077(void) { static V c; return STRC(c, "String"); }
static V S1078(void) { static V c; return STRC(c, "List"); }
static V S1079(void) { static V c; return STRC(c, "&"); }
static V S1080(void) { static V c; return STRC(c, "->"); }
static V F_Gen_dprinter_dbody(V a0, V a1, V a2) {
top:;
return F_Gen_dprinter_dhead(a0, a1, F_P_dwhich(a2, C2(1, S1073(), C2(1, S1074(), C2(1, S1075(), C2(1, S1076(), C2(1, S1077(), C2(1, S1078(), C2(1, S1079(), C2(1, S1080(), IMM(0)))))))))));
}
static V W_Gen_dprinter_dbody(V *a) { (void)a; return F_Gen_dprinter_dbody(a[0], a[1], a[2]); }
static V S1082(void) { static V c; return STRC(c, "pr_u32(v);\012"); }
static V S1083(void) { static V c; return STRC(c, "pr_nat(v);\012"); }
static V S1084(void) { static V c; return STRC(c, "pr_f32(v);\012"); }
static V S1085(void) { static V c; return STRC(c, "pr_char(v);\012"); }
static V S1086(void) { static V c; return STRC(c, "pr_str(v);\012"); }
static V S1088(void) { static V c; return STRC(c, "pr_s(\042[\042);\012for (int i = 0; TAG(v) == 1; i++) { if (i) pr_s(\042, \042); "); }
static V S1089(void) { static V c; return STRC(c, "(FLD(v, 0)); v = FLD(v, 1); }\012pr_s(\042]\042);\012"); }
static V L1087(V *a) {
return F_Gen_dpure(C1(1, F_String_dappend(S1088(), F_String_dappend(a[0], S1089()))));
}
static V S1090(void) { static V c; return STRC(c, "v"); }
static V S1092(void) { static V c; return STRC(c, "pr_s(\042(\042);\012"); }
static V S1093(void) { static V c; return STRC(c, "pr_s(\042)\042);\012"); }
static V L1091(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1092()), C2(1, a[0], C2(1, C1(1, S1093()), IMM(0))))));
}
static V S1094(void) { static V c; return STRC(c, "(void)v; pr_s(\042<function>\042);\012"); }
static V S1095(void) { static V c; return STRC(c, "%"); }
static V F_Gen_dprinter_dhead(V a0, V a1, V a2) {
top:;
V s1081 = a2;
if ((s1081) == 0) {
return F_Gen_dpure(C1(1, S1082()));
} else if ((s1081) == 1) {
return F_Gen_dpure(C1(1, S1083()));
} else if ((s1081) == 2) {
return F_Gen_dpure(C1(1, S1084()));
} else if ((s1081) == 3) {
return F_Gen_dpure(C1(1, S1085()));
} else if ((s1081) == 4) {
return F_Gen_dpure(C1(1, S1086()));
} else if ((s1081) == 5) {
return F_Gen_dbind(F_Gen_dprinter(a0, F_P_dlast(F_Ty_dargs(a1))), mk_clo(L1087, 1, 0, 0));
} else if ((s1081) == 6) {
return F_Gen_dbind(F_Gen_dprinter_dtuple(a0, F_Ty_dtuple(a1), S1090()), mk_clo(L1091, 1, 0, 0));
} else if ((s1081) == 7) {
return F_Gen_dpure(C1(1, S1094()));
} else if (nat_ge(s1081, 8)) {
return F_Gen_dprinter_dadt(a0, a1, F_G_dbody(a0, F_String_dappend(S1095(), F_Ty_dhead(a1))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dhead(V *a) { (void)a; return F_Gen_dprinter_dhead(a[0], a[1], a[2]); }
static V S1098(void) { static V c; return STRC(c, "pr_s(\042\077\042);\012"); }
static V L1097(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, C1(1, S1098()), IMM(0)))));
}
static V S1099(void) { static V c; return STRC(c, "(void)v; pr_s(\042\077\042);\012"); }
static V F_Gen_dprinter_dadt(V a0, V a1, V a2) {
top:;
V s1096 = a2;
if (TAG(s1096) == 3) {
return F_Gen_dbind(F_Gen_dprinter_dctors(a0, F_Ty_dbind(FLD(s1096, 1), F_Ty_dargs(a1)), FLD(s1096, 2)), mk_clo(L1097, 1, 0, 0));
} else {
return F_Gen_dpure(C1(1, S1099()));
}
}
static V W_Gen_dprinter_dadt(V *a) { (void)a; return F_Gen_dprinter_dadt(a[0], a[1], a[2]); }
static V F_Ty_dargs(V a0) {
top:;
V s1100 = a0;
if (TAG(s1100) == 14) {
return FLD(s1100, 1);
} else if (TAG(s1100) == 5) {
return FLD(s1100, 1);
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
V s1101 = a0;
V s1102 = a1;
if (TAG(s1101) == 1 && TAG(s1102) == 1) {
return C2(1, C2(0, FLD(s1101, 0), FLD(s1102, 0)), F_Ty_dbind_dgo(FLD(s1101, 1), FLD(s1102, 1)));
} else {
return IMM(0);
}
}
static V W_Ty_dbind_dgo(V *a) { (void)a; return F_Ty_dbind_dgo(a[0], a[1]); }
static V L1105(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V L1104(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dctors(a[2], a[1], a[0]), mk_clo(L1105, 2, 1, (V[]){a[3]}));
}
static V F_Gen_dprinter_dctors(V a0, V a1, V a2) {
top:;
V s1103 = a2;
if ((s1103) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1103) == 1) {
return F_Gen_dbind(F_Gen_dprinter_dctor(a0, a1, FLD(FLD(s1103, 0), 0), FLD(FLD(s1103, 0), 1), F_G_dctor(a0, FLD(FLD(s1103, 0), 0))), mk_clo(L1104, 4, 3, (V[]){FLD(s1103, 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dctors(V *a) { (void)a; return F_Gen_dprinter_dctors(a[0], a[1], a[2]); }
static V F_G_dctor(V a0, V a1) {
top:;
V v1106 = a0;
return F_Pair_dsnd(F_Map_dget(IMM(0), F_G_dopt__ctors(FLD(v1106, 0)), a1));
}
static V W_G_dctor(V *a) { (void)a; return F_G_dctor(a[0], a[1]); }
static V F_G_dopt__ctors(V a0) {
top:;
V s1107 = a0;
if ((s1107) == IMM(0)) {
return IMM(0);
} else if (TAG(s1107) == 1) {
return C2(1, FLD(s1107, 0), C1(1, FLD(s1107, 1)));
} else if (TAG(s1107) == 2) {
return C3(2, FLD(s1107, 0), F_G_dopt__ctors(FLD(s1107, 1)), F_G_dopt__ctors(FLD(s1107, 2)));
} else { bend_fail("incomplete match"); }
}
static V W_G_dopt__ctors(V *a) { (void)a; return F_G_dopt__ctors(a[0]); }
static V S1109(void) { static V c; return STRC(c, "v"); }
static V S1110(void) { static V c; return STRC(c, "FLD(v, "); }
static V S1112(void) { static V c; return STRC(c, " { pr_s(\042"); }
static V S1113(void) { static V c; return STRC(c, "{\042);\012"); }
static V S1114(void) { static V c; return STRC(c, "pr_s(\042}\042); return; }\012"); }
static V L1111(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(F_Gen_dprinter_dtest(a[3], a[2], a[1]), F_String_dappend(S1112(), F_String_dappend(a[0], S1113())))), C2(1, a[4], C2(1, C1(1, S1114()), IMM(0))))));
}
static V F_Gen_dprinter_dctor(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1108 = a4;
if ((s1108) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1108) == 1) {
return F_Gen_dbind(F_Gen_dprinter_dfields(a0, a1, a3, F_Bool_dpick(F_U32_dis__eq(FLD(FLD(s1108, 0), 2), 2u), S1109(), S1110()), 0u), mk_clo(L1111, 5, 4, (V[]){a2, FLD(FLD(s1108, 0), 3), FLD(FLD(s1108, 0), 0), FLD(FLD(s1108, 0), 2)}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dctor(V *a) { (void)a; return F_Gen_dprinter_dctor(a[0], a[1], a[2], a[3], a[4]); }
static V S1115(void) { static V c; return STRC(c, "if (1)"); }
static V S1116(void) { static V c; return STRC(c, "if (v == IMM("); }
static V S1117(void) { static V c; return STRC(c, "))"); }
static V S1118(void) { static V c; return STRC(c, "if (!(v & 1) && TAG(v) == "); }
static V S1119(void) { static V c; return STRC(c, ")"); }
static V F_Gen_dprinter_dtest(V a0, V a1, V a2) {
top:;
return F_Bool_dpick(a2, S1115(), F_Bool_dpick(F_U32_dis__eq(a0, 1u), F_String_dappend(S1116(), F_String_dappend(F_U32_dshow(a1), S1117())), F_String_dappend(S1118(), F_String_dappend(F_U32_dshow(a1), S1119()))));
}
static V W_Gen_dprinter_dtest(V *a) { (void)a; return F_Gen_dprinter_dtest(a[0], a[1], a[2]); }
static V S1123(void) { static V c; return STRC(c, ""); }
static V S1124(void) { static V c; return STRC(c, "pr_s(\042, \042);\012"); }
static V S1125(void) { static V c; return STRC(c, "("); }
static V S1126(void) { static V c; return STRC(c, "v"); }
static V S1127(void) { static V c; return STRC(c, "v"); }
static V S1128(void) { static V c; return STRC(c, ")"); }
static V S1129(void) { static V c; return STRC(c, ");\012"); }
static V L1122(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(F_Bool_dpick(F_U32_dis__zero(a[2]), S1123(), S1124()), F_String_dappend(a[1], F_String_dappend(S1125(), F_String_dappend(F_Bool_dpick(F_Str_deq(a[0], S1126()), S1127(), F_String_dappend(a[0], F_String_dappend(F_U32_dshow(a[2]), S1128()))), S1129()))))), C2(1, a[3], IMM(0)))));
}
static V L1121(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dfields(a[4], a[3], a[2], a[1], F_U32_dinc(a[0])), mk_clo(L1122, 4, 3, (V[]){a[1], a[5], a[0]}));
}
static V F_Gen_dprinter_dfields(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1120 = a2;
if ((s1120) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1120) == 1) {
return F_Gen_dbind(F_Gen_dprinter(a0, F_Ty_dsubst(FLD(FLD(s1120, 0), 1), a1)), mk_clo(L1121, 6, 5, (V[]){a4, a3, FLD(s1120, 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dfields(V *a) { (void)a; return F_Gen_dprinter_dfields(a[0], a[1], a[2], a[3], a[4]); }
static V F_Ty_dsubst(V a0, V a1) {
top:;
V s1130 = a0;
if (TAG(s1130) == 0) {
return F_Maybe_ddefault(F_Ty_dfind(a1, FLD(s1130, 0)), C1(0, FLD(s1130, 0)));
} else if (TAG(s1130) == 14) {
return C2(14, FLD(s1130, 0), F_Ty_dsubsts(FLD(s1130, 1), a1));
} else if (TAG(s1130) == 5) {
return C2(5, FLD(s1130, 0), F_Ty_dsubsts(FLD(s1130, 1), a1));
} else {
return s1130;
}
}
static V W_Ty_dsubst(V *a) { (void)a; return F_Ty_dsubst(a[0], a[1]); }
static V F_Ty_dsubsts(V a0, V a1) {
top:;
V s1131 = a0;
if ((s1131) == IMM(0)) {
return IMM(0);
} else if (TAG(s1131) == 1) {
return C2(1, F_Ty_dsubst(FLD(s1131, 0), a1), F_Ty_dsubsts(FLD(s1131, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dsubsts(V *a) { (void)a; return F_Ty_dsubsts(a[0], a[1]); }
static V F_Ty_dfind(V a0, V a1) {
top:;
V s1132 = a0;
if ((s1132) == IMM(0)) {
return IMM(0);
} else if (TAG(s1132) == 1) {
return F_Ty_dfind_dif(FLD(FLD(s1132, 0), 1), FLD(s1132, 1), a1, F_String_deq(FLD(FLD(s1132, 0), 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dfind(V *a) { (void)a; return F_Ty_dfind(a[0], a[1]); }
static V F_Ty_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s1133 = a3;
if ((s1133) == IMM(1)) {
return C1(1, a0);
} else if ((s1133) == IMM(0)) {
return F_Ty_dfind(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dfind_dif(V *a) { (void)a; return F_Ty_dfind_dif(a[0], a[1], a[2], a[3]); }
static V F_Maybe_ddefault(V a2, V a3) {
top:;
V s1134 = a2;
if ((s1134) == IMM(0)) {
return a3;
} else if (TAG(s1134) == 1) {
return FLD(s1134, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Maybe_ddefault(V *a) { (void)a; return F_Maybe_ddefault(a[2], a[3]); }
static V S1136(void) { static V c; return STRC(c, "&"); }
static V F_Ty_dtuple(V a0) {
top:;
V s1135 = a0;
if (TAG(s1135) == 14) {
return F_Ty_dtuple_dgo(C2(14, FLD(s1135, 0), FLD(s1135, 1)), FLD(s1135, 1), F_Str_deq(FLD(s1135, 0), S1136()));
} else {
return C2(1, s1135, IMM(0));
}
}
static V W_Ty_dtuple(V *a) { (void)a; return F_Ty_dtuple(a[0]); }
static V F_Ty_dtuple_dgo(V a0, V a1, V a2) {
top:;
V s1137 = a2;
if ((s1137) == IMM(1)) {
return F_Ty_dtuple_dargs(a0, a1);
} else if ((s1137) == IMM(0)) {
return C2(1, a0, IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dtuple_dgo(V *a) { (void)a; return F_Ty_dtuple_dgo(a[0], a[1], a[2]); }
static V F_Ty_dtuple_dargs(V a0, V a1) {
top:;
V s1138 = a1;
if (TAG(s1138) == 1 && TAG(FLD(s1138, 1)) == 1 && (FLD(FLD(s1138, 1), 1)) == IMM(0)) {
return C2(1, FLD(s1138, 0), F_Ty_dtuple(FLD(FLD(s1138, 1), 0)));
} else {
return C2(1, a0, IMM(0));
}
}
static V W_Ty_dtuple_dargs(V *a) { (void)a; return F_Ty_dtuple_dargs(a[0], a[1]); }
static V S1141(void) { static V c; return STRC(c, "("); }
static V S1142(void) { static V c; return STRC(c, ");\012"); }
static V L1140(V *a) {
return F_Gen_dpure(C1(1, F_String_dappend(a[1], F_String_dappend(S1141(), F_String_dappend(a[0], S1142())))));
}
static V S1144(void) { static V c; return STRC(c, "FLD("); }
static V S1145(void) { static V c; return STRC(c, ", 1)"); }
static V S1147(void) { static V c; return STRC(c, "(FLD("); }
static V S1148(void) { static V c; return STRC(c, ", 0));\012pr_s(\042, \042);\012"); }
static V L1146(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(a[1], F_String_dappend(S1147(), F_String_dappend(a[0], S1148())))), C2(1, a[2], IMM(0)))));
}
static V L1143(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dtuple(a[2], a[1], F_String_dappend(S1144(), F_String_dappend(a[0], S1145()))), mk_clo(L1146, 3, 2, (V[]){a[0], a[3]}));
}
static V F_Gen_dprinter_dtuple(V a0, V a1, V a2) {
top:;
V s1139 = a1;
if ((s1139) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1139) == 1 && (FLD(s1139, 1)) == IMM(0)) {
return F_Gen_dbind(F_Gen_dprinter(a0, FLD(s1139, 0)), mk_clo(L1140, 2, 1, (V[]){a2}));
} else if (TAG(s1139) == 1) {
return F_Gen_dbind(F_Gen_dprinter(a0, FLD(s1139, 0)), mk_clo(L1143, 4, 3, (V[]){a2, FLD(s1139, 1), a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dtuple(V *a) { (void)a; return F_Gen_dprinter_dtuple(a[0], a[1], a[2]); }
static V L1149(V *a) {
return F_Gen_dproto_dgo(a[0], a[1]);
}
static V F_Gen_dproto(V a0) {
top:;
return mk_clo(L1149, 2, 1, (V[]){a0});
}
static V W_Gen_dproto(V *a) { (void)a; return F_Gen_dproto(a[0]); }
static V F_Gen_dproto_dgo(V a0, V a1) {
top:;
V v1150 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v1150, 0), C2(2, FLD(v1150, 1), a0), FLD(v1150, 2), FLD(v1150, 3), FLD(v1150, 4), FLD(v1150, 5), FLD(v1150, 6)}));
}
static V W_Gen_dproto_dgo(V *a) { (void)a; return F_Gen_dproto_dgo(a[0], a[1]); }
static V L1151(V *a) {
return F_Gen_dmemo_dadd_dgo(a[1], a[0]);
}
static V F_Gen_dmemo_dadd(V a0) {
top:;
return mk_clo(L1151, 2, 1, (V[]){a0});
}
static V W_Gen_dmemo_dadd(V *a) { (void)a; return F_Gen_dmemo_dadd(a[0]); }
static V F_Gen_dmemo_dadd_dgo(V a0, V a1) {
top:;
V v1152 = a0;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v1152, 0), FLD(v1152, 1), FLD(v1152, 2), FLD(v1152, 3), FLD(v1152, 4), C2(1, a1, FLD(v1152, 5)), FLD(v1152, 6)}));
}
static V W_Gen_dmemo_dadd_dgo(V *a) { (void)a; return F_Gen_dmemo_dadd_dgo(a[0], a[1]); }
static V L1153(V *a) {
return F_Gen_dfresh_dgo(a[0]);
}
static V F_Gen_dfresh(void) {
top:;
return mk_clo(L1153, 1, 0, 0);
}
static V W_Gen_dfresh(V *a) { (void)a; return F_Gen_dfresh(); }
static V F_Gen_dfresh_dgo(V a0) {
top:;
V v1154 = a0;
return C2(0, FLD(v1154, 0), CN(0, 7, (V[]){F_U32_dinc(FLD(v1154, 0)), FLD(v1154, 1), FLD(v1154, 2), FLD(v1154, 3), FLD(v1154, 4), FLD(v1154, 5), FLD(v1154, 6)}));
}
static V W_Gen_dfresh_dgo(V *a) { (void)a; return F_Gen_dfresh_dgo(a[0]); }
static V L1155(V *a) {
return F_Gen_dmemo_dfind_dgo(a[1], a[0]);
}
static V F_Gen_dmemo_dfind(V a0) {
top:;
return mk_clo(L1155, 2, 1, (V[]){a0});
}
static V W_Gen_dmemo_dfind(V *a) { (void)a; return F_Gen_dmemo_dfind(a[0]); }
static V F_Gen_dmemo_dfind_dgo(V a0, V a1) {
top:;
V v1156 = a0;
return C2(0, F_Env_dfind(FLD(v1156, 5), a1), CN(0, 7, (V[]){FLD(v1156, 0), FLD(v1156, 1), FLD(v1156, 2), FLD(v1156, 3), FLD(v1156, 4), FLD(v1156, 5), FLD(v1156, 6)}));
}
static V W_Gen_dmemo_dfind_dgo(V *a) { (void)a; return F_Gen_dmemo_dfind_dgo(a[0], a[1]); }
static V F_Env_dfind(V a0, V a1) {
top:;
V s1157 = a0;
if ((s1157) == IMM(0)) {
return IMM(0);
} else if (TAG(s1157) == 1) {
return F_Env_dfind_dif(FLD(FLD(s1157, 0), 1), FLD(s1157, 1), a1, F_String_deq(FLD(FLD(s1157, 0), 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Env_dfind(V *a) { (void)a; return F_Env_dfind(a[0], a[1]); }
static V F_Env_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s1158 = a3;
if ((s1158) == IMM(1)) {
return C1(1, a0);
} else if ((s1158) == IMM(0)) {
return F_Env_dfind(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Env_dfind_dif(V *a) { (void)a; return F_Env_dfind_dif(a[0], a[1], a[2], a[3]); }
static V S1160(void) { static V c; return STRC(c, "n"); }
static V S1161(void) { static V c; return STRC(c, "\042"); }
static V S1162(void) { static V c; return STRC(c, "\042"); }
static V S1163(void) { static V c; return STRC(c, "("); }
static V S1164(void) { static V c; return STRC(c, " "); }
static V S1165(void) { static V c; return STRC(c, ")"); }
static V S1166(void) { static V c; return STRC(c, "{"); }
static V S1167(void) { static V c; return STRC(c, "}"); }
static V S1168(void) { static V c; return STRC(c, "(\134"); }
static V S1169(void) { static V c; return STRC(c, " "); }
static V S1170(void) { static V c; return STRC(c, ")"); }
static V S1171(void) { static V c; return STRC(c, "(let "); }
static V S1172(void) { static V c; return STRC(c, " "); }
static V S1173(void) { static V c; return STRC(c, " "); }
static V S1174(void) { static V c; return STRC(c, ")"); }
static V S1175(void) { static V c; return STRC(c, "(match ["); }
static V S1176(void) { static V c; return STRC(c, "] "); }
static V S1177(void) { static V c; return STRC(c, ")"); }
static V S1178(void) { static V c; return STRC(c, "(case "); }
static V S1179(void) { static V c; return STRC(c, " => "); }
static V S1180(void) { static V c; return STRC(c, ")"); }
static V S1181(void) { static V c; return STRC(c, "("); }
static V S1182(void) { static V c; return STRC(c, "n+ "); }
static V S1183(void) { static V c; return STRC(c, ")"); }
static V S1184(void) { static V c; return STRC(c, "("); }
static V S1185(void) { static V c; return STRC(c, " "); }
static V S1186(void) { static V c; return STRC(c, " "); }
static V S1187(void) { static V c; return STRC(c, ")"); }
static V S1188(void) { static V c; return STRC(c, "(: "); }
static V S1189(void) { static V c; return STRC(c, " "); }
static V S1190(void) { static V c; return STRC(c, ")"); }
static V S1191(void) { static V c; return STRC(c, "#"); }
static V S1192(void) { static V c; return STRC(c, "(ERR "); }
static V S1193(void) { static V c; return STRC(c, ")"); }
static V F_Expr_dshow(V a0) {
top:;
V s1159 = a0;
if (TAG(s1159) == 0) {
return FLD(s1159, 0);
} else if (TAG(s1159) == 1) {
return F_U32_dshow(FLD(s1159, 0));
} else if (TAG(s1159) == 2) {
return F_String_dappend(F_U32_dshow(FLD(s1159, 0)), S1160());
} else if (TAG(s1159) == 3) {
return FLD(s1159, 0);
} else if (TAG(s1159) == 4) {
return F_String_dappend(S1161(), F_String_dappend(FLD(s1159, 0), S1162()));
} else if (TAG(s1159) == 5) {
return F_String_dappend(S1163(), F_String_dappend(F_Expr_dshow(FLD(s1159, 0)), F_String_dappend(S1164(), F_String_dappend(F_Exprs_dshow(FLD(s1159, 1)), S1165()))));
} else if (TAG(s1159) == 6) {
return F_String_dappend(FLD(s1159, 0), F_String_dappend(S1166(), F_String_dappend(F_Exprs_dshow(FLD(s1159, 1)), S1167())));
} else if (TAG(s1159) == 7) {
return F_String_dappend(S1168(), F_String_dappend(F_Pat_dshow(FLD(s1159, 0)), F_String_dappend(S1169(), F_String_dappend(F_Expr_dshow(FLD(s1159, 1)), S1170()))));
} else if (TAG(s1159) == 8) {
return F_String_dappend(S1171(), F_String_dappend(F_Pat_dshow(FLD(s1159, 0)), F_String_dappend(S1172(), F_String_dappend(F_Expr_dshow(FLD(s1159, 1)), F_String_dappend(S1173(), F_String_dappend(F_Expr_dshow(FLD(s1159, 2)), S1174()))))));
} else if (TAG(s1159) == 9) {
return F_String_dappend(S1175(), F_String_dappend(F_Exprs_dshow(FLD(s1159, 0)), F_String_dappend(S1176(), F_String_dappend(F_Exprs_dshow(FLD(s1159, 1)), S1177()))));
} else if (TAG(s1159) == 10) {
return F_String_dappend(S1178(), F_String_dappend(F_Pats_dshow(FLD(s1159, 0)), F_String_dappend(S1179(), F_String_dappend(F_Expr_dshow(FLD(s1159, 1)), S1180()))));
} else if (TAG(s1159) == 11) {
return F_String_dappend(S1181(), F_String_dappend(F_U32_dshow(FLD(s1159, 0)), F_String_dappend(S1182(), F_String_dappend(F_Expr_dshow(FLD(s1159, 1)), S1183()))));
} else if (TAG(s1159) == 12) {
return F_String_dappend(S1184(), F_String_dappend(FLD(s1159, 0), F_String_dappend(S1185(), F_String_dappend(F_Expr_dshow(FLD(s1159, 1)), F_String_dappend(S1186(), F_String_dappend(F_Expr_dshow(FLD(s1159, 2)), S1187()))))));
} else if (TAG(s1159) == 13) {
return F_String_dappend(S1188(), F_String_dappend(F_Expr_dshow(FLD(s1159, 0)), F_String_dappend(S1189(), F_String_dappend(FLD(s1159, 1), S1190()))));
} else if (TAG(s1159) == 14) {
return F_String_dappend(S1191(), FLD(s1159, 0));
} else if (TAG(s1159) == 15) {
return F_String_dappend(S1192(), F_String_dappend(FLD(s1159, 0), S1193()));
} else { bend_fail("incomplete match"); }
}
static V W_Expr_dshow(V *a) { (void)a; return F_Expr_dshow(a[0]); }
static V S1195(void) { static V c; return STRC(c, ""); }
static V S1196(void) { static V c; return STRC(c, " "); }
static V F_Pats_dshow(V a0) {
top:;
V s1194 = a0;
if ((s1194) == IMM(0)) {
return S1195();
} else if (TAG(s1194) == 1 && (FLD(s1194, 1)) == IMM(0)) {
return F_Pat_dshow(FLD(s1194, 0));
} else if (TAG(s1194) == 1) {
return F_String_dappend(F_Pat_dshow(FLD(s1194, 0)), F_String_dappend(S1196(), F_Pats_dshow(FLD(s1194, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Pats_dshow(V *a) { (void)a; return F_Pats_dshow(a[0]); }
static V S1198(void) { static V c; return STRC(c, "{"); }
static V S1199(void) { static V c; return STRC(c, "}"); }
static V S1200(void) { static V c; return STRC(c, "n"); }
static V S1201(void) { static V c; return STRC(c, "n+"); }
static V F_Pat_dshow(V a0) {
top:;
V s1197 = a0;
if (TAG(s1197) == 0) {
return FLD(s1197, 0);
} else if (TAG(s1197) == 1) {
return F_String_dappend(FLD(s1197, 0), F_String_dappend(S1198(), F_String_dappend(F_Pats_dshow(FLD(s1197, 1)), S1199())));
} else if (TAG(s1197) == 2) {
return F_String_dappend(F_U32_dshow(FLD(s1197, 0)), S1200());
} else if (TAG(s1197) == 3) {
return F_String_dappend(F_U32_dshow(FLD(s1197, 0)), F_String_dappend(S1201(), F_Pat_dshow(FLD(s1197, 1))));
} else if (TAG(s1197) == 4) {
return F_U32_dshow(FLD(s1197, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Pat_dshow(V *a) { (void)a; return F_Pat_dshow(a[0]); }
static V S1203(void) { static V c; return STRC(c, ""); }
static V S1204(void) { static V c; return STRC(c, " "); }
static V F_Exprs_dshow(V a0) {
top:;
V s1202 = a0;
if ((s1202) == IMM(0)) {
return S1203();
} else if (TAG(s1202) == 1 && (FLD(s1202, 1)) == IMM(0)) {
return F_Expr_dshow(FLD(s1202, 0));
} else if (TAG(s1202) == 1) {
return F_String_dappend(F_Expr_dshow(FLD(s1202, 0)), F_String_dappend(S1204(), F_Exprs_dshow(FLD(s1202, 1))));
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
V s1205 = a1;
if ((s1205) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1205) == 1) {
return F_Gen_dall_dseen(a0, FLD(s1205, 0), FLD(s1205, 1), F_Set_dhas(a2, FLD(s1205, 0)));
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
V s1206 = a2;
if ((s1206) == IMM(0)) {
return C2(0, IMM(0), IMM(0));
} else if (TAG(s1206) == 1) {
return F_Map_dhas_dleaf(FLD(s1206, 1), F_String_dcmp(a3, FLD(s1206, 0)));
} else if (TAG(s1206) == 2) {
return F_Map_dhas_dbit(FLD(s1206, 1), FLD(s1206, 2), FLD(s1206, 0), F_Map_dbit(a3, FLD(s1206, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dhas(V *a) { (void)a; return F_Map_dhas(a[2], a[3]); }
static V F_Map_dhas_dbit(V a2, V a3, V a4, V a5) {
top:;
V v1207 = a5;
V s1208 = FLD(v1207, 1);
if ((s1208) == IMM(0)) {
return F_Map_dlo(a4, a3, F_Map_dhas(a2, FLD(v1207, 0)));
} else if ((s1208) == IMM(1)) {
return F_Map_dhi(a4, a2, F_Map_dhas(a3, FLD(v1207, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dhas_dbit(V *a) { (void)a; return F_Map_dhas_dbit(a[2], a[3], a[4], a[5]); }
static V F_Map_dhas_dleaf(V a2, V a3) {
top:;
V v1209 = a3;
return C2(0, C2(1, FLD(FLD(v1209, 0), 1), a2), F_Cmp_dis__eq(FLD(v1209, 1)));
}
static V W_Map_dhas_dleaf(V *a) { (void)a; return F_Map_dhas_dleaf(a[2], a[3]); }
static V F_Gen_dall_dseen(V a0, V a1, V a2, V a3) {
top:;
V v1210 = a3;
return F_Gen_dall_dgo(a0, a1, a2, FLD(v1210, 0), FLD(v1210, 1));
}
static V W_Gen_dall_dseen(V *a) { (void)a; return F_Gen_dall_dseen(a[0], a[1], a[2], a[3]); }
static V L1213(V *a) {
return F_Gen_dall(a[3], F_List_dappend(a[4], a[2]), F_Set_dadd(a[1], a[0]));
}
static V L1212(V *a) {
return F_Gen_dbind(F_Gen_dtake__refs(), mk_clo(L1213, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Gen_dall_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1211 = a4;
if ((s1211) == IMM(1)) {
return F_Gen_dall(a0, a2, a3);
} else if ((s1211) == IMM(0)) {
return F_Gen_dbind(F_Gen_ddef(a0, a1), mk_clo(L1212, 5, 4, (V[]){a1, a3, a2, a0}));
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
V s1214 = a2;
if ((s1214) == IMM(0)) {
return C2(0, IMM(0), C2(0, a3, IMM(0)));
} else if (TAG(s1214) == 1) {
return C2(0, C2(1, FLD(s1214, 0), FLD(s1214, 1)), C2(0, a3, C1(1, FLD(s1214, 0))));
} else if (TAG(s1214) == 2) {
return F_Map_dseek_dbit(FLD(s1214, 1), FLD(s1214, 2), FLD(s1214, 0), F_Map_dbit(a3, FLD(s1214, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dseek(V *a) { (void)a; return F_Map_dseek(a[2], a[3]); }
static V F_Map_dseek_dbit(V a2, V a3, V a4, V a5) {
top:;
V v1215 = a5;
V s1216 = FLD(v1215, 1);
if ((s1216) == IMM(0)) {
return F_Map_dlo(a4, a3, F_Map_dseek(a2, FLD(v1215, 0)));
} else if ((s1216) == IMM(1)) {
return F_Map_dhi(a4, a2, F_Map_dseek(a3, FLD(v1215, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dseek_dbit(V *a) { (void)a; return F_Map_dseek_dbit(a[2], a[3], a[4], a[5]); }
static V F_Map_dset_dgo(V a2, V a3) {
top:;
V v1217 = a3;
V s1218 = FLD(FLD(v1217, 1), 1);
if ((s1218) == IMM(0)) {
return C2(1, FLD(FLD(v1217, 1), 0), a2);
} else if (TAG(s1218) == 1) {
V v1219 = FLD(FLD(v1217, 1), 0);
return F_Map_dset_dfin(FLD(v1217, 0), v1219, a2, v1219, FLD(s1218, 0));
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
V v1220 = a5;
V s1221 = FLD(v1220, 1);
if ((s1221) == IMM(0)) {
return F_Map_dins(a2, a3, a4, F_Map_ddiff(FLD(FLD(v1220, 0), 0), FLD(FLD(v1220, 0), 1)));
} else if ((s1221) == IMM(1)) {
return F_Map_dput(a2, a3, a4);
} else if ((s1221) == IMM(2)) {
return F_Map_dins(a2, a3, a4, F_Map_ddiff(FLD(FLD(v1220, 0), 0), FLD(FLD(v1220, 0), 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dset_dfin_dgo(V *a) { (void)a; return F_Map_dset_dfin_dgo(a[2], a[3], a[4], a[5]); }
static V F_Map_ddiff(V a0, V a1) {
top:;
V s1222 = a0;
V s1223 = a1;
if ((s1222) == IMM(0) && (s1223) == IMM(0)) {
return 0u;
} else if ((s1222) == IMM(0) && TAG(s1223) == 1) {
return 0u;
} else if (TAG(s1222) == 1 && (s1223) == IMM(0)) {
return 0u;
} else if (TAG(s1222) == 1 && TAG(s1223) == 1) {
return F_Map_ddiff_dfin(FLD(s1222, 1), FLD(s1223, 1), F_Map_ddiff_dstep(FLD(s1222, 0), FLD(s1223, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_ddiff(V *a) { (void)a; return F_Map_ddiff(a[0], a[1]); }
static V F_Map_ddiff_dstep(V a0, V a1) {
top:;
V s1224 = a0;
V s1225 = a1;
{
return C2(0, F_Map_ddiff_dchr(F_U32_dxor(s1224, s1225)), F_U32_dis__eq(s1224, s1225));
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
V s1226 = a0;
if ((s1226) == 0) {
return 0u;
} else if (nat_ge(s1226, 1)) {
return F_Map_dmsb_du_dif(nat_subk(s1226, 1), a1, F_U32_dis__zero(a1));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dmsb_du(V *a) { (void)a; return F_Map_dmsb_du(a[0], a[1]); }
static V F_Map_dmsb_du_dif(V a0, V a1, V a2) {
top:;
V s1227 = a2;
if ((s1227) == IMM(1)) {
return 0u;
} else if ((s1227) == IMM(0)) {
return F_Nat_dadd(1u, F_Map_dmsb_du(a0, F_U32_dshr(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dmsb_du_dif(V *a) { (void)a; return F_Map_dmsb_du_dif(a[0], a[1], a[2]); }
static V W_U32_dshr(V *a) { (void)a; return F_U32_dshr(a[0]); }
static V F_Map_ddiff_dfin(V a0, V a1, V a2) {
top:;
V v1228 = a2;
V s1229 = FLD(v1228, 1);
if ((s1229) == IMM(1)) {
return F_Nat_dadd(33u, F_Map_ddiff(a0, a1));
} else if ((s1229) == IMM(0)) {
return FLD(v1228, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Map_ddiff_dfin(V *a) { (void)a; return F_Map_ddiff_dfin(a[0], a[1], a[2]); }
static V F_Map_dins(V a2, V a3, V a4, V a5) {
top:;
V s1230 = a2;
if ((s1230) == IMM(0)) {
return C2(1, a3, a4);
} else if (TAG(s1230) == 1) {
return F_Map_dins_dsplice(a5, a3, a4, C2(1, FLD(s1230, 0), FLD(s1230, 1)));
} else if (TAG(s1230) == 2) {
return F_Map_dins_dif(a3, a4, FLD(s1230, 1), FLD(s1230, 2), FLD(s1230, 0), a5, F_Nat_dis__lt(FLD(s1230, 0), a5));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dins(V *a) { (void)a; return F_Map_dins(a[2], a[3], a[4], a[5]); }
static V F_Map_dins_dif(V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s1231 = a8;
if ((s1231) == IMM(0)) {
return F_Map_dins_dsplice(a7, a2, a3, C3(2, a6, a4, a5));
} else if ((s1231) == IMM(1)) {
return F_Map_dins_ddeep(a3, a4, a5, a7, a6, F_Map_dbit(a2, a6));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dins_dif(V *a) { (void)a; return F_Map_dins_dif(a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Map_dins_ddeep(V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V v1232 = a7;
V s1233 = FLD(v1232, 1);
if ((s1233) == IMM(0)) {
return C3(2, a6, F_Map_dins(a3, FLD(v1232, 0), a2, a5), a4);
} else if ((s1233) == IMM(1)) {
return C3(2, a6, a3, F_Map_dins(a4, FLD(v1232, 0), a2, a5));
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
V v1234 = a5;
V s1235 = FLD(v1234, 1);
if ((s1235) == IMM(0)) {
return C3(2, a4, C2(1, FLD(v1234, 0), a2), a3);
} else if ((s1235) == IMM(1)) {
return C3(2, a4, a3, C2(1, FLD(v1234, 0), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dins_dsplice_dbit(V *a) { (void)a; return F_Map_dins_dsplice_dbit(a[2], a[3], a[4], a[5]); }
static V F_Map_dput(V a2, V a3, V a4) {
top:;
V s1236 = a2;
if ((s1236) == IMM(0)) {
return C2(1, a3, a4);
} else if (TAG(s1236) == 1) {
return C2(1, FLD(s1236, 0), a4);
} else if (TAG(s1236) == 2) {
return F_Map_dput_dbit(a4, FLD(s1236, 0), FLD(s1236, 1), FLD(s1236, 2), F_Map_dbit(a3, FLD(s1236, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dput(V *a) { (void)a; return F_Map_dput(a[2], a[3], a[4]); }
static V F_Map_dput_dbit(V a2, V a3, V a4, V a5, V a6) {
top:;
V v1237 = a6;
V s1238 = FLD(v1237, 1);
if ((s1238) == IMM(0)) {
return C3(2, a3, F_Map_dput(a4, FLD(v1237, 0), a2), a5);
} else if ((s1238) == IMM(1)) {
return C3(2, a3, a4, F_Map_dput(a5, FLD(v1237, 0), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dput_dbit(V *a) { (void)a; return F_Map_dput_dbit(a[2], a[3], a[4], a[5], a[6]); }
static V L1239(V *a) {
return F_Gen_dtake__refs_dgo(a[0]);
}
static V F_Gen_dtake__refs(void) {
top:;
return mk_clo(L1239, 1, 0, 0);
}
static V W_Gen_dtake__refs(V *a) { (void)a; return F_Gen_dtake__refs(); }
static V F_Gen_dtake__refs_dgo(V a0) {
top:;
V v1240 = a0;
return C2(0, FLD(v1240, 3), CN(0, 7, (V[]){FLD(v1240, 0), FLD(v1240, 1), FLD(v1240, 2), IMM(0), FLD(v1240, 4), FLD(v1240, 5), FLD(v1240, 6)}));
}
static V W_Gen_dtake__refs_dgo(V *a) { (void)a; return F_Gen_dtake__refs_dgo(a[0]); }
static V F_Gen_ddef(V a0, V a1) {
top:;
return F_Gen_ddef_ddecl(a0, a1, F_G_ddef(a0, a1), F_G_dbody(a0, a1));
}
static V W_Gen_ddef(V *a) { (void)a; return F_Gen_ddef(a[0], a[1]); }
static V F_G_ddef(V a0, V a1) {
top:;
V v1241 = a0;
return F_G_dget(C2(0, 99u, IMM(0)), FLD(v1241, 1), a1);
}
static V W_G_ddef(V *a) { (void)a; return F_G_ddef(a[0], a[1]); }
static V F_Gen_ddef_ddecl(V a0, V a1, V a2, V a3) {
top:;
V v1242 = a2;
V s1243 = a3;
if (TAG(s1243) == 0) {
return F_Gen_ddef_dnative(a0, a1, FLD(v1242, 1), FLD(s1243, 2), F_Gen_dsig(FLD(s1243, 1), FLD(v1242, 1), 0u, C3(0, IMM(0), IMM(0), IMM(0))), F_U32_dis__eq(FLD(v1242, 0), 2u));
} else if (TAG(s1243) == 1) {
return F_Gen_ddef_deff(a1, F_Gen_dsig(FLD(s1243, 1), FLD(v1242, 1), 0u, C3(0, IMM(0), IMM(0), IMM(0))), FLD(s1243, 2));
} else {
return F_Gen_ddef_dlaw(a1, FLD(v1242, 1), F_U32_dis__eq(FLD(v1242, 0), 2u));
}
}
static V W_Gen_ddef_ddecl(V *a) { (void)a; return F_Gen_ddef_ddecl(a[0], a[1], a[2], a[3]); }
static V F_Gen_ddef_dlaw(V a0, V a1, V a2) {
top:;
V s1244 = a2;
if ((s1244) == IMM(1)) {
return F_Gen_dwrapper(a0, F_Sig_dwargs(F_Gen_dsig(F_Gen_ddummy__params(a1), a1, 0u, C3(0, IMM(0), IMM(0), IMM(0)))));
} else if ((s1244) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_ddef_dlaw(V *a) { (void)a; return F_Gen_ddef_dlaw(a[0], a[1], a[2]); }
static V S1246(void) { static V c; return STRC(c, "_"); }
static V S1247(void) { static V c; return STRC(c, ""); }
static V F_Gen_ddummy__params(V a0) {
top:;
V s1245 = a0;
if ((s1245) == IMM(0)) {
return IMM(0);
} else if (TAG(s1245) == 1) {
return C2(1, C3(0, S1246(), 0u, S1247()), F_Gen_ddummy__params(FLD(s1245, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_ddummy__params(V *a) { (void)a; return F_Gen_ddummy__params(a[0]); }
static V S1252(void) { static V c; return STRC(c, "a"); }
static V S1253(void) { static V c; return STRC(c, "a["); }
static V S1254(void) { static V c; return STRC(c, "]"); }
static V S1256(void) { static V c; return STRC(c, "0"); }
static V F_Gen_dsig(V a0, V a1, V a2, V a3) {
top:;
V s1248 = a0;
V s1249 = a1;
if (TAG(s1248) == 1 && TAG(s1249) == 1 && (FLD(s1249, 0)) == IMM(1)) {
V v1250 = a3;
V v1251 = F_String_dappend(S1252(), F_U32_dshow(a2));
{ V t0 = FLD(s1248, 1); V t1 = FLD(s1249, 1); V t2 = F_U32_dinc(a2); V t3 = C3(0, F_List_dappend(FLD(v1250, 0), C2(1, v1251, IMM(0))), C2(1, C2(0, FLD(FLD(s1248, 0), 0), v1251), FLD(v1250, 1)), F_List_dappend(FLD(v1250, 2), C2(1, F_String_dappend(S1253(), F_String_dappend(F_U32_dshow(a2), S1254())), IMM(0)))); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1248) == 1 && TAG(s1249) == 1 && (FLD(s1249, 0)) == IMM(0)) {
V v1255 = a3;
{ V t0 = FLD(s1248, 1); V t1 = FLD(s1249, 1); V t2 = F_U32_dinc(a2); V t3 = C3(0, FLD(v1255, 0), C2(1, C2(0, FLD(FLD(s1248, 0), 0), S1256()), FLD(v1255, 1)), FLD(v1255, 2)); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else {
return a3;
}
}
static V W_Gen_dsig(V *a) { (void)a; return F_Gen_dsig(a[0], a[1], a[2], a[3]); }
static V F_Sig_dwargs(V a0) {
top:;
V v1257 = a0;
return FLD(v1257, 2);
}
static V W_Sig_dwargs(V *a) { (void)a; return F_Sig_dwargs(a[0]); }
static V S1259(void) { static V c; return STRC(c, "static V "); }
static V S1260(void) { static V c; return STRC(c, "(V *a);\012"); }
static V S1262(void) { static V c; return STRC(c, "static V "); }
static V S1263(void) { static V c; return STRC(c, "(V *a) { (void)a; return "); }
static V S1264(void) { static V c; return STRC(c, "("); }
static V S1265(void) { static V c; return STRC(c, ", "); }
static V S1266(void) { static V c; return STRC(c, "); }\012"); }
static V L1261(V *a) {
return F_Gen_dcode(C1(1, F_String_dappend(S1262(), F_String_dappend(a[2], F_String_dappend(S1263(), F_String_dappend(F_Gen_df(a[1]), F_String_dappend(S1264(), F_String_dappend(F_String_djoin(a[0], S1265()), S1266()))))))));
}
static V F_Gen_dwrapper(V a0, V a1) {
top:;
V v1258 = F_Gen_dw(a0);
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S1259(), F_String_dappend(v1258, S1260())))), mk_clo(L1261, 4, 3, (V[]){a1, a0, v1258}));
}
static V W_Gen_dwrapper(V *a) { (void)a; return F_Gen_dwrapper(a[0], a[1]); }
static V S1267(void) { static V c; return STRC(c, "F_"); }
static V F_Gen_df(V a0) {
top:;
return F_String_dappend(S1267(), F_Gen_dmangle(a0));
}
static V W_Gen_df(V *a) { (void)a; return F_Gen_df(a[0]); }
static V S1269(void) { static V c; return STRC(c, ""); }
static V F_Gen_dmangle(V a0) {
top:;
V s1268 = a0;
if ((s1268) == IMM(0)) {
return S1269();
} else if (TAG(s1268) == 1) {
return F_String_dappend(F_Gen_dmangle_dchr(FLD(s1268, 0)), F_Gen_dmangle(FLD(s1268, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dmangle(V *a) { (void)a; return F_Gen_dmangle(a[0]); }
static V S1270(void) { static V c; return STRC(c, "_d"); }
static V S1271(void) { static V c; return STRC(c, "__"); }
static V S1272(void) { static V c; return STRC(c, "_x"); }
static V F_Gen_dmangle_dchr(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__eq(a0, 46u), S1270(), F_Bool_dpick(F_U32_dis__eq(a0, 95u), S1271(), F_Bool_dpick(F_Bool_dor(F_Char_dis__alpha(a0), F_Char_dis__digit(a0)), F_Str_dchr(a0), F_String_dappend(S1272(), F_U32_dshow(a0)))));
}
static V W_Gen_dmangle_dchr(V *a) { (void)a; return F_Gen_dmangle_dchr(a[0]); }
static V F_Str_dchr(V a0) {
top:;
return C2(1, a0, IMM(0));
}
static V W_Str_dchr(V *a) { (void)a; return F_Str_dchr(a[0]); }
static V S1273(void) { static V c; return STRC(c, "W_"); }
static V F_Gen_dw(V a0) {
top:;
return F_String_dappend(S1273(), F_Gen_dmangle(a0));
}
static V W_Gen_dw(V *a) { (void)a; return F_Gen_dw(a[0]); }
static V S1277(void) { static V c; return STRC(c, "E_"); }
static V S1279(void) { static V c; return STRC(c, "static V "); }
static V S1280(void) { static V c; return STRC(c, "("); }
static V S1281(void) { static V c; return STRC(c, ")"); }
static V S1283(void) { static V c; return STRC(c, ";\012static V "); }
static V S1284(void) { static V c; return STRC(c, "(V *a);\012"); }
static V S1286(void) { static V c; return STRC(c, "static V "); }
static V S1287(void) { static V c; return STRC(c, "(V *a) { return io_req("); }
static V S1288(void) { static V c; return STRC(c, ", "); }
static V S1289(void) { static V c; return STRC(c, ", (V[]){"); }
static V S1290(void) { static V c; return STRC(c, "a["); }
static V S1291(void) { static V c; return STRC(c, "]"); }
static V S1292(void) { static V c; return STRC(c, ", "); }
static V S1293(void) { static V c; return STRC(c, "}); }\012"); }
static V S1295(void) { static V c; return STRC(c, " { return mk_clo("); }
static V S1296(void) { static V c; return STRC(c, ", "); }
static V S1297(void) { static V c; return STRC(c, ", "); }
static V S1298(void) { static V c; return STRC(c, ", "); }
static V S1299(void) { static V c; return STRC(c, "0"); }
static V S1300(void) { static V c; return STRC(c, "(V[]){"); }
static V S1301(void) { static V c; return STRC(c, ", "); }
static V S1302(void) { static V c; return STRC(c, "}"); }
static V S1303(void) { static V c; return STRC(c, "); }\012"); }
static V L1304(V *a) {
return F_Gen_dwrapper(a[1], a[0]);
}
static V L1294(V *a) {
return F_Gen_dbind(F_Gen_dcode(C1(1, F_String_dappend(a[5], F_String_dappend(S1295(), F_String_dappend(a[4], F_String_dappend(S1296(), F_String_dappend(F_U32_dshow(F_U32_dadd(a[3], 2u)), F_String_dappend(S1297(), F_String_dappend(F_U32_dshow(a[3]), F_String_dappend(S1298(), F_String_dappend(F_Bool_dpick(F_U32_dis__zero(a[3]), S1299(), F_String_dappend(S1300(), F_String_dappend(F_String_djoin(a[2], S1301()), S1302()))), S1303()))))))))))), mk_clo(L1304, 3, 2, (V[]){a[0], a[1]}));
}
static V L1285(V *a) {
return F_Gen_dbind(F_Gen_dcode(C1(1, F_String_dappend(S1286(), F_String_dappend(a[5], F_String_dappend(S1287(), F_String_dappend(F_Gen_dcid(a[4]), F_String_dappend(S1288(), F_String_dappend(F_U32_dshow(F_U32_dinc(a[3])), F_String_dappend(S1289(), F_String_dappend(F_String_djoin(F_List_dappend(F_Gen_deff_dargs(F_U32_dto__nat(a[3]), 0u), C2(1, F_String_dappend(S1290(), F_String_dappend(F_U32_dshow(F_U32_dinc(a[3])), S1291())), IMM(0))), S1292()), S1293())))))))))), mk_clo(L1294, 7, 6, (V[]){a[0], a[4], a[1], a[3], a[5], a[2]}));
}
static V L1282(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(a[5], F_String_dappend(S1283(), F_String_dappend(a[4], S1284()))))), mk_clo(L1285, 7, 6, (V[]){a[0], a[1], a[5], a[2], a[3], a[4]}));
}
static V F_Gen_ddef_deff(V a0, V a1, V a2) {
top:;
V v1274 = a1;
V v1275 = F_U32_dfrom__nat(F_List_dlength(FLD(v1274, 0)));
V v1276 = F_String_dappend(S1277(), F_Gen_dmangle(a0));
V v1278 = F_String_dappend(S1279(), F_String_dappend(F_Gen_df(a0), F_String_dappend(S1280(), F_String_dappend(F_Gen_dcparams(FLD(v1274, 0)), S1281()))));
return F_Gen_dbind(F_Gen_deffs(a2), mk_clo(L1282, 7, 6, (V[]){FLD(v1274, 2), FLD(v1274, 0), v1275, a0, v1276, v1278}));
}
static V W_Gen_ddef_deff(V *a) { (void)a; return F_Gen_ddef_deff(a[0], a[1], a[2]); }
static V S1306(void) { static V c; return STRC(c, "a["); }
static V S1307(void) { static V c; return STRC(c, "]"); }
static V F_Gen_deff_dargs(V a0, V a1) {
top:;
V s1305 = a0;
if ((s1305) == 0) {
return IMM(0);
} else if (nat_ge(s1305, 1)) {
return C2(1, F_String_dappend(S1306(), F_String_dappend(F_U32_dshow(a1), S1307())), F_Gen_deff_dargs(nat_subk(s1305, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_deff_dargs(V *a) { (void)a; return F_Gen_deff_dargs(a[0], a[1]); }
static V S1308(void) { static V c; return STRC(c, "CID_"); }
static V F_Gen_dcid(V a0) {
top:;
return F_String_dappend(S1308(), F_Gen_dhost(F_String_dto__upper(a0)));
}
static V W_Gen_dcid(V *a) { (void)a; return F_Gen_dcid(a[0]); }
static V F_String_dto__upper(V a0) {
top:;
V s1309 = a0;
if ((s1309) == IMM(0)) {
return IMM(0);
} else if (TAG(s1309) == 1) {
return C2(1, F_Char_dto__upper(FLD(s1309, 0)), F_String_dto__upper(FLD(s1309, 1)));
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
V s1310 = a0;
if ((s1310) == IMM(0)) {
return 0u;
} else if ((s1310) == IMM(1)) {
return 1u;
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dto__u32(V *a) { (void)a; return F_Bool_dto__u32(a[0]); }
static V S1312(void) { static V c; return STRC(c, ""); }
static V F_Gen_dhost(V a0) {
top:;
V s1311 = a0;
if ((s1311) == IMM(0)) {
return S1312();
} else if (TAG(s1311) == 1) {
return F_String_dappend(F_Gen_dhost_dchr(FLD(s1311, 0)), F_Gen_dhost(FLD(s1311, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dhost(V *a) { (void)a; return F_Gen_dhost(a[0]); }
static V S1313(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dhost_dchr(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__eq(a0, 46u), S1313(), F_Str_dchr(a0));
}
static V W_Gen_dhost_dchr(V *a) { (void)a; return F_Gen_dhost_dchr(a[0]); }
static V L1314(V *a) {
return F_Gen_deffs_dgo(a[0], a[1]);
}
static V F_Gen_deffs(V a0) {
top:;
return mk_clo(L1314, 2, 1, (V[]){a0});
}
static V W_Gen_deffs(V *a) { (void)a; return F_Gen_deffs(a[0]); }
static V F_Gen_deffs_dgo(V a0, V a1) {
top:;
V v1315 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v1315, 0), FLD(v1315, 1), FLD(v1315, 2), FLD(v1315, 3), FLD(v1315, 4), FLD(v1315, 5), F_List_dappend(F_Gen_deffs_dc(a0), FLD(v1315, 6))}));
}
static V W_Gen_deffs_dgo(V *a) { (void)a; return F_Gen_deffs_dgo(a[0], a[1]); }
static V S1317(void) { static V c; return STRC(c, ".c"); }
static V F_Gen_deffs_dc(V a0) {
top:;
V s1316 = a0;
if ((s1316) == IMM(0)) {
return IMM(0);
} else if (TAG(s1316) == 1) {
return F_Gen_deffs_dc_dif(FLD(s1316, 0), F_Gen_deffs_dc(FLD(s1316, 1)), F_String_dends__with(FLD(s1316, 0), S1317()));
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
V s1318 = a2;
if ((s1318) == IMM(1)) {
return C2(1, a0, a1);
} else if ((s1318) == IMM(0)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Gen_deffs_dc_dif(V *a) { (void)a; return F_Gen_deffs_dc_dif(a[0], a[1], a[2]); }
static V S1320(void) { static V c; return STRC(c, "void"); }
static V S1321(void) { static V c; return STRC(c, ", "); }
static V F_Gen_dcparams(V a0) {
top:;
V s1319 = a0;
if ((s1319) == IMM(0)) {
return S1320();
} else if (TAG(s1319) == 1) {
return F_String_djoin(F_Gen_dcparams_dgo(C2(1, FLD(s1319, 0), FLD(s1319, 1))), S1321());
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcparams(V *a) { (void)a; return F_Gen_dcparams(a[0]); }
static V S1323(void) { static V c; return STRC(c, "V "); }
static V F_Gen_dcparams_dgo(V a0) {
top:;
V s1322 = a0;
if ((s1322) == IMM(0)) {
return IMM(0);
} else if (TAG(s1322) == 1) {
return C2(1, F_String_dappend(S1323(), FLD(s1322, 0)), F_Gen_dcparams_dgo(FLD(s1322, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcparams_dgo(V *a) { (void)a; return F_Gen_dcparams_dgo(a[0]); }
static V F_Gen_ddef_dnative(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1324 = a5;
if ((s1324) == IMM(1)) {
return F_Gen_dwrapper(a1, F_Sig_dwargs(a4));
} else if ((s1324) == IMM(0)) {
return F_Gen_ddef_dbody(a0, a1, a2, a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_ddef_dnative(V *a) { (void)a; return F_Gen_ddef_dnative(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1327(void) { static V c; return STRC(c, "static V "); }
static V S1328(void) { static V c; return STRC(c, "("); }
static V S1329(void) { static V c; return STRC(c, ")"); }
static V S1330(void) { static V c; return STRC(c, ";\012"); }
static V S1332(void) { static V c; return STRC(c, "Nat"); }
static V S1334(void) { static V c; return STRC(c, " {\012top:;\012"); }
static V S1335(void) { static V c; return STRC(c, "}\012"); }
static V L1336(V *a) {
return F_Gen_dwrapper(a[1], a[0]);
}
static V L1333(V *a) {
return F_Gen_dbind(F_Gen_dcode(F_Doc_dlist(C2(1, C1(1, F_String_dappend(a[2], S1334())), C2(1, a[3], C2(1, C1(1, S1335()), IMM(0)))))), mk_clo(L1336, 3, 2, (V[]){a[0], a[1]}));
}
static V L1331(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[7], a[6], C3(0, a[5], a[4], a[3]), IMM(0), F_R_dops(a[2], S1332())), mk_clo(L1333, 4, 3, (V[]){a[0], a[5], a[1]}));
}
static V F_Gen_ddef_dbody(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1325 = a4;
V v1326 = F_String_dappend(S1327(), F_String_dappend(F_Gen_df(a1), F_String_dappend(S1328(), F_String_dappend(F_Gen_dcparams(FLD(v1325, 0)), S1329()))));
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(v1326, S1330()))), mk_clo(L1331, 9, 8, (V[]){FLD(v1325, 2), v1326, a3, FLD(v1325, 0), a2, a1, FLD(v1325, 1), a0}));
}
static V W_Gen_ddef_dbody(V *a) { (void)a; return F_Gen_ddef_dbody(a[0], a[1], a[2], a[3], a[4]); }
static V S1338(void) { static V c; return STRC(c, "."); }
static V F_R_dops(V a0, V a1) {
top:;
V s1337 = a0;
if (TAG(s1337) == 12) {
return C2(5, C1(0, F_String_dappend(a1, F_String_dappend(S1338(), F_R_dopname(FLD(s1337, 0))))), C2(1, F_R_dops(FLD(s1337, 1), a1), C2(1, F_R_dops(FLD(s1337, 2), a1), IMM(0))));
} else if (TAG(s1337) == 13) {
{ V t0 = FLD(s1337, 0); V t1 = F_Bool_dpick(F_String_dis__empty(FLD(s1337, 1)), a1, FLD(s1337, 1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1337) == 5) {
return C2(5, F_R_dops(FLD(s1337, 0), a1), F_R_dopss(FLD(s1337, 1), a1));
} else if (TAG(s1337) == 6) {
return C2(6, FLD(s1337, 0), F_R_dopss(FLD(s1337, 1), a1));
} else if (TAG(s1337) == 7) {
return C2(7, FLD(s1337, 0), F_R_dops(FLD(s1337, 1), a1));
} else if (TAG(s1337) == 8) {
return C3(8, FLD(s1337, 0), F_R_dops(FLD(s1337, 1), a1), F_R_dops(FLD(s1337, 2), a1));
} else if (TAG(s1337) == 9) {
return C2(9, F_R_dopss(FLD(s1337, 0), a1), F_R_dopss(FLD(s1337, 1), a1));
} else if (TAG(s1337) == 10) {
return C2(10, FLD(s1337, 0), F_R_dops(FLD(s1337, 1), a1));
} else if (TAG(s1337) == 11) {
return C2(11, FLD(s1337, 0), F_R_dops(FLD(s1337, 1), a1));
} else {
return s1337;
}
}
static V W_R_dops(V *a) { (void)a; return F_R_dops(a[0], a[1]); }
static V F_R_dopss(V a0, V a1) {
top:;
V s1339 = a0;
if ((s1339) == IMM(0)) {
return IMM(0);
} else if (TAG(s1339) == 1) {
return C2(1, F_R_dops(FLD(s1339, 0), a1), F_R_dopss(FLD(s1339, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_R_dopss(V *a) { (void)a; return F_R_dopss(a[0], a[1]); }
static V S1340(void) { static V c; return STRC(c, "+"); }
static V S1341(void) { static V c; return STRC(c, "-"); }
static V S1342(void) { static V c; return STRC(c, "*"); }
static V S1343(void) { static V c; return STRC(c, "/"); }
static V S1344(void) { static V c; return STRC(c, "%"); }
static V S1345(void) { static V c; return STRC(c, "<"); }
static V S1346(void) { static V c; return STRC(c, "<="); }
static V S1347(void) { static V c; return STRC(c, ">"); }
static V S1348(void) { static V c; return STRC(c, ">="); }
static V S1349(void) { static V c; return STRC(c, ".&."); }
static V S1350(void) { static V c; return STRC(c, ".|."); }
static V S1351(void) { static V c; return STRC(c, ".^."); }
static V S1352(void) { static V c; return STRC(c, "<<"); }
static V S1353(void) { static V c; return STRC(c, ">>"); }
static V F_R_dopname(V a0) {
top:;
return F_R_dopname_dgo(F_P_dwhich(a0, C2(1, S1340(), C2(1, S1341(), C2(1, S1342(), C2(1, S1343(), C2(1, S1344(), C2(1, S1345(), C2(1, S1346(), C2(1, S1347(), C2(1, S1348(), C2(1, S1349(), C2(1, S1350(), C2(1, S1351(), C2(1, S1352(), C2(1, S1353(), IMM(0)))))))))))))))));
}
static V W_R_dopname(V *a) { (void)a; return F_R_dopname(a[0]); }
static V S1355(void) { static V c; return STRC(c, "add"); }
static V S1356(void) { static V c; return STRC(c, "sub"); }
static V S1357(void) { static V c; return STRC(c, "mul"); }
static V S1358(void) { static V c; return STRC(c, "div"); }
static V S1359(void) { static V c; return STRC(c, "mod"); }
static V S1360(void) { static V c; return STRC(c, "is_lt"); }
static V S1361(void) { static V c; return STRC(c, "is_le"); }
static V S1362(void) { static V c; return STRC(c, "is_gt"); }
static V S1363(void) { static V c; return STRC(c, "is_ge"); }
static V S1364(void) { static V c; return STRC(c, "and"); }
static V S1365(void) { static V c; return STRC(c, "or"); }
static V S1366(void) { static V c; return STRC(c, "xor"); }
static V S1367(void) { static V c; return STRC(c, "shln"); }
static V S1368(void) { static V c; return STRC(c, "shrn"); }
static V S1369(void) { static V c; return STRC(c, "\077"); }
static V F_R_dopname_dgo(V a0) {
top:;
V s1354 = a0;
if ((s1354) == 0) {
return S1355();
} else if ((s1354) == 1) {
return S1356();
} else if ((s1354) == 2) {
return S1357();
} else if ((s1354) == 3) {
return S1358();
} else if ((s1354) == 4) {
return S1359();
} else if ((s1354) == 5) {
return S1360();
} else if ((s1354) == 6) {
return S1361();
} else if ((s1354) == 7) {
return S1362();
} else if ((s1354) == 8) {
return S1363();
} else if ((s1354) == 9) {
return S1364();
} else if ((s1354) == 10) {
return S1365();
} else if ((s1354) == 11) {
return S1366();
} else if ((s1354) == 12) {
return S1367();
} else if ((s1354) == 13) {
return S1368();
} else if (nat_ge(s1354, 14)) {
return S1369();
} else { bend_fail("incomplete match"); }
}
static V W_R_dopname_dgo(V *a) { (void)a; return F_R_dopname_dgo(a[0]); }
static V L1371(V *a) {
return F_Gen_dpure(F_Gen_dret(a[0], a[1]));
}
static V F_Gen_dstmt(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1370 = a4;
if (TAG(s1370) == 8) {
return F_Gen_dlet(a0, a1, a2, a3, FLD(s1370, 0), FLD(s1370, 1), FLD(s1370, 2));
} else if (TAG(s1370) == 9) {
return F_Gen_dmatch(a0, a1, a2, a3, FLD(s1370, 0), FLD(s1370, 1));
} else if (TAG(s1370) == 5 && TAG(FLD(s1370, 0)) == 0) {
return F_Gen_dstmt_dcall(a0, a1, a2, a3, FLD(FLD(s1370, 0), 0), FLD(s1370, 1), F_Gen_dis__tail(a1, a2, a3, FLD(FLD(s1370, 0), 0), FLD(s1370, 1)));
} else {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, s1370), mk_clo(L1371, 2, 1, (V[]){a3}));
}
}
static V W_Gen_dstmt(V *a) { (void)a; return F_Gen_dstmt(a[0], a[1], a[2], a[3], a[4]); }
static V S1373(void) { static V c; return STRC(c, "return "); }
static V S1374(void) { static V c; return STRC(c, ";\012"); }
static V S1375(void) { static V c; return STRC(c, " = "); }
static V S1376(void) { static V c; return STRC(c, ";\012"); }
static V F_Gen_dret(V a0, V a1) {
top:;
V s1372 = a0;
if ((s1372) == IMM(0)) {
return F_Doc_dlist(C2(1, C1(1, S1373()), C2(1, a1, C2(1, C1(1, S1374()), IMM(0)))));
} else if (TAG(s1372) == 1) {
return F_Doc_dlist(C2(1, C1(1, FLD(s1372, 0)), C2(1, C1(1, S1375()), C2(1, a1, C2(1, C1(1, S1376()), IMM(0))))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dret(V *a) { (void)a; return F_Gen_dret(a[0], a[1]); }
static V S1378(void) { static V c; return STRC(c, "u"); }
static V S1379(void) { static V c; return STRC(c, "u"); }
static V S1380(void) { static V c; return STRC(c, "VF("); }
static V S1381(void) { static V c; return STRC(c, "f)"); }
static V S1383(void) { static V c; return STRC(c, "nat_addk("); }
static V S1384(void) { static V c; return STRC(c, ", "); }
static V S1385(void) { static V c; return STRC(c, ")"); }
static V L1382(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1383()), C2(1, a[1], C2(1, C1(1, F_String_dappend(S1384(), F_String_dappend(F_U32_dshow(a[0]), S1385()))), IMM(0))))));
}
static V S1386(void) { static V c; return STRC(c, "0"); }
static V S1387(void) { static V c; return STRC(c, "parse error: "); }
static V S1389(void) { static V c; return STRC(c, "0"); }
static V L1388(V *a) {
return F_Gen_dpure(C1(1, S1389()));
}
static V S1390(void) { static V c; return STRC(c, "unexpected expression: "); }
static V S1392(void) { static V c; return STRC(c, "0"); }
static V L1391(V *a) {
return F_Gen_dpure(C1(1, S1392()));
}
static V F_Gen_dexpr(V a0, V a1, V a2) {
top:;
V s1377 = a2;
if (TAG(s1377) == 0) {
return F_Gen_dvar(a0, a1, FLD(s1377, 0));
} else if (TAG(s1377) == 1) {
return F_Gen_dpure(C1(1, F_String_dappend(F_U32_dshow(FLD(s1377, 0)), S1378())));
} else if (TAG(s1377) == 2) {
return F_Gen_dpure(C1(1, F_String_dappend(F_U32_dshow(FLD(s1377, 0)), S1379())));
} else if (TAG(s1377) == 3) {
return F_Gen_dpure(C1(1, F_String_dappend(S1380(), F_String_dappend(FLD(s1377, 0), S1381()))));
} else if (TAG(s1377) == 4) {
return F_Gen_dstr(FLD(s1377, 0));
} else if (TAG(s1377) == 5) {
return F_Gen_dcall(a0, a1, FLD(s1377, 0), FLD(s1377, 1));
} else if (TAG(s1377) == 6) {
return F_Gen_dctor(a0, a1, FLD(s1377, 0), FLD(s1377, 1));
} else if (TAG(s1377) == 7) {
return F_Gen_dlam(a0, a1, FLD(s1377, 0), FLD(s1377, 1));
} else if (TAG(s1377) == 8) {
return F_Gen_dblock(a0, a1, C3(8, FLD(s1377, 0), FLD(s1377, 1), FLD(s1377, 2)));
} else if (TAG(s1377) == 9) {
return F_Gen_dblock(a0, a1, C2(9, FLD(s1377, 0), FLD(s1377, 1)));
} else if (TAG(s1377) == 11) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, FLD(s1377, 1)), mk_clo(L1382, 2, 1, (V[]){FLD(s1377, 0)}));
} else if (TAG(s1377) == 14) {
return F_Gen_dpure(C1(1, S1386()));
} else if (TAG(s1377) == 15) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1387(), FLD(s1377, 0))), mk_clo(L1388, 1, 0, 0));
} else {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1390(), F_Expr_dshow(s1377))), mk_clo(L1391, 1, 0, 0));
}
}
static V W_Gen_dexpr(V *a) { (void)a; return F_Gen_dexpr(a[0], a[1], a[2]); }
static V S1394(void) { static V c; return STRC(c, "r"); }
static V S1397(void) { static V c; return STRC(c, "({ V "); }
static V S1398(void) { static V c; return STRC(c, ";\012"); }
static V S1399(void) { static V c; return STRC(c, "; })"); }
static V L1396(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1397(), F_String_dappend(a[0], S1398()))), C2(1, a[1], C2(1, C1(1, F_String_dappend(a[0], S1399())), IMM(0))))));
}
static V L1395(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[2], a[1], F_Self_dnone(), C1(1, a[3]), a[0]), mk_clo(L1396, 2, 1, (V[]){a[3]}));
}
static V L1393(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1394(), F_U32_dshow(a[3]))), mk_clo(L1395, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Gen_dblock(V a0, V a1, V a2) {
top:;
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1393, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Gen_dblock(V *a) { (void)a; return F_Gen_dblock(a[0], a[1], a[2]); }
static V S1400(void) { static V c; return STRC(c, ""); }
static V F_Self_dnone(void) {
top:;
return C3(0, S1400(), IMM(0), IMM(0));
}
static V W_Self_dnone(V *a) { (void)a; return F_Self_dnone(); }
static V S1404(void) { static V c; return STRC(c, "L"); }
static V S1406(void) { static V c; return STRC(c, "static V "); }
static V S1407(void) { static V c; return STRC(c, "(V *a);\012"); }
static V S1409(void) { static V c; return STRC(c, "a["); }
static V S1410(void) { static V c; return STRC(c, "]"); }
static V S1413(void) { static V c; return STRC(c, "static V "); }
static V S1414(void) { static V c; return STRC(c, "(V *a) {\012"); }
static V S1415(void) { static V c; return STRC(c, "}\012"); }
static V S1417(void) { static V c; return STRC(c, "mk_clo("); }
static V S1418(void) { static V c; return STRC(c, ", "); }
static V S1419(void) { static V c; return STRC(c, ", "); }
static V S1420(void) { static V c; return STRC(c, ", "); }
static V S1421(void) { static V c; return STRC(c, ")"); }
static V L1416(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1417(), F_String_dappend(a[2], F_String_dappend(S1418(), F_String_dappend(F_U32_dshow(F_U32_dinc(a[1])), F_String_dappend(S1419(), F_String_dappend(F_U32_dshow(a[1]), S1420()))))))), C2(1, F_Gen_darr(F_Gen_dcaps_douter(a[0])), C2(1, C1(1, S1421()), IMM(0))))));
}
static V L1412(V *a) {
return F_Gen_dbind(F_Gen_dcode(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1413(), F_String_dappend(a[2], S1414()))), C2(1, a[3], C2(1, C1(1, S1415()), IMM(0)))))), mk_clo(L1416, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L1411(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[4], F_List_dappend(a[5], F_Gen_dcaps_dinner(a[3], 0u)), F_Self_dnone(), IMM(0), a[2]), mk_clo(L1412, 4, 3, (V[]){a[3], a[0], a[1]}));
}
static V L1408(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_PatR_dbinds(F_Gen_dpat(a[5], a[4], F_String_dappend(S1409(), F_String_dappend(F_U32_dshow(a[3]), S1410())), C2(0, IMM(0), IMM(0))))), mk_clo(L1411, 6, 5, (V[]){a[3], a[0], a[1], a[2], a[5]}));
}
static V L1405(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S1406(), F_String_dappend(a[5], S1407())))), mk_clo(L1408, 7, 6, (V[]){a[5], a[0], a[1], a[2], a[3], a[4]}));
}
static V L1403(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1404(), F_U32_dshow(a[5]))), mk_clo(L1405, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V F_Gen_dlam(V a0, V a1, V a2, V a3) {
top:;
V v1401 = F_Gen_dcaps(F_FV_dexpr(a3, F_Pat_dvars(a2, IMM(0)), IMM(0)), a1);
V v1402 = F_U32_dfrom__nat(F_List_dlength(v1401));
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1403, 6, 5, (V[]){a3, v1401, v1402, a2, a0}));
}
static V W_Gen_dlam(V *a) { (void)a; return F_Gen_dlam(a[0], a[1], a[2], a[3]); }
static V F_Gen_dcaps_douter(V a0) {
top:;
V s1422 = a0;
if ((s1422) == IMM(0)) {
return IMM(0);
} else if (TAG(s1422) == 1) {
return C2(1, C1(1, FLD(FLD(s1422, 0), 1)), F_Gen_dcaps_douter(FLD(s1422, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps_douter(V *a) { (void)a; return F_Gen_dcaps_douter(a[0]); }
static V S1424(void) { static V c; return STRC(c, "0"); }
static V S1425(void) { static V c; return STRC(c, "(V[]){"); }
static V S1426(void) { static V c; return STRC(c, "}"); }
static V F_Gen_darr(V a0) {
top:;
V s1423 = a0;
if ((s1423) == IMM(0)) {
return C1(1, S1424());
} else if (TAG(s1423) == 1) {
return F_Doc_dlist(C2(1, C1(1, S1425()), C2(1, F_Gen_dcommas(C2(1, FLD(s1423, 0), FLD(s1423, 1))), C2(1, C1(1, S1426()), IMM(0)))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_darr(V *a) { (void)a; return F_Gen_darr(a[0]); }
static V S1427(void) { static V c; return STRC(c, ", "); }
static V F_Gen_dcommas(V a0) {
top:;
return F_Doc_dsep(a0, S1427());
}
static V W_Gen_dcommas(V *a) { (void)a; return F_Gen_dcommas(a[0]); }
static V F_Doc_dsep(V a0, V a1) {
top:;
V s1428 = a0;
if ((s1428) == IMM(0)) {
return IMM(0);
} else if (TAG(s1428) == 1) {
return C2(2, FLD(s1428, 0), F_Doc_dsep_dgo(FLD(s1428, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dsep(V *a) { (void)a; return F_Doc_dsep(a[0], a[1]); }
static V F_Doc_dsep_dgo(V a0, V a1) {
top:;
V s1429 = a0;
if ((s1429) == IMM(0)) {
return IMM(0);
} else if (TAG(s1429) == 1) {
return C2(2, C1(1, a1), C2(2, FLD(s1429, 0), F_Doc_dsep_dgo(FLD(s1429, 1), a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dsep_dgo(V *a) { (void)a; return F_Doc_dsep_dgo(a[0], a[1]); }
static V S1431(void) { static V c; return STRC(c, "a["); }
static V S1432(void) { static V c; return STRC(c, "]"); }
static V F_Gen_dcaps_dinner(V a0, V a1) {
top:;
V s1430 = a0;
if ((s1430) == IMM(0)) {
return IMM(0);
} else if (TAG(s1430) == 1) {
return C2(1, C2(0, FLD(FLD(s1430, 0), 0), F_String_dappend(S1431(), F_String_dappend(F_U32_dshow(a1), S1432()))), F_Gen_dcaps_dinner(FLD(s1430, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps_dinner(V *a) { (void)a; return F_Gen_dcaps_dinner(a[0], a[1]); }
static V S1434(void) { static V c; return STRC(c, "("); }
static V S1435(void) { static V c; return STRC(c, ") == "); }
static V S1436(void) { static V c; return STRC(c, "nat_subk("); }
static V S1437(void) { static V c; return STRC(c, ", "); }
static V S1438(void) { static V c; return STRC(c, ")"); }
static V S1439(void) { static V c; return STRC(c, "nat_ge("); }
static V S1440(void) { static V c; return STRC(c, ", "); }
static V S1441(void) { static V c; return STRC(c, ")"); }
static V S1442(void) { static V c; return STRC(c, "("); }
static V S1443(void) { static V c; return STRC(c, ") == "); }
static V F_Gen_dpat(V a0, V a1, V a2, V a3) {
top:;
V s1433 = a1;
if (TAG(s1433) == 0) {
return F_Gen_dpat_dvar(FLD(s1433, 0), a2, a3);
} else if (TAG(s1433) == 1) {
return F_Gen_dpat_dctor(a0, F_G_dctor(a0, FLD(s1433, 0)), FLD(s1433, 0), FLD(s1433, 1), a2, a3);
} else if (TAG(s1433) == 2) {
return F_Gen_dpat_dcond(F_String_dappend(S1434(), F_String_dappend(a2, F_String_dappend(S1435(), F_U32_dshow(FLD(s1433, 0))))), a3);
} else if (TAG(s1433) == 3) {
{ V t0 = a0; V t1 = FLD(s1433, 1); V t2 = F_String_dappend(S1436(), F_String_dappend(a2, F_String_dappend(S1437(), F_String_dappend(F_U32_dshow(FLD(s1433, 0)), S1438())))); V t3 = F_Gen_dpat_dcond(F_String_dappend(S1439(), F_String_dappend(a2, F_String_dappend(S1440(), F_String_dappend(F_U32_dshow(FLD(s1433, 0)), S1441())))), a3); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1433) == 4) {
return F_Gen_dpat_dcond(F_String_dappend(S1442(), F_String_dappend(a2, F_String_dappend(S1443(), F_U32_dshow(FLD(s1433, 0))))), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat(V *a) { (void)a; return F_Gen_dpat(a[0], a[1], a[2], a[3]); }
static V F_Gen_dpat_dcond(V a0, V a1) {
top:;
V v1444 = a1;
return C2(0, C2(1, a0, FLD(v1444, 0)), FLD(v1444, 1));
}
static V W_Gen_dpat_dcond(V *a) { (void)a; return F_Gen_dpat_dcond(a[0], a[1]); }
static V S1446(void) { static V c; return STRC(c, "0 /* unknown constructor "); }
static V S1447(void) { static V c; return STRC(c, " */"); }
static V F_Gen_dpat_dctor(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1445 = a1;
if ((s1445) == IMM(0)) {
return F_Gen_dpat_dcond(F_String_dappend(S1446(), F_String_dappend(a2, S1447())), a5);
} else if (TAG(s1445) == 1) {
return F_Gen_dpat_dkind(a0, F_U32_dto__nat(FLD(FLD(s1445, 0), 2)), FLD(FLD(s1445, 0), 0), FLD(FLD(s1445, 0), 3), a3, a4, a5);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dctor(V *a) { (void)a; return F_Gen_dpat_dctor(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1449(void) { static V c; return STRC(c, "TAG("); }
static V S1450(void) { static V c; return STRC(c, ") == "); }
static V S1451(void) { static V c; return STRC(c, "("); }
static V S1452(void) { static V c; return STRC(c, ") == IMM("); }
static V S1453(void) { static V c; return STRC(c, ")"); }
static V S1454(void) { static V c; return STRC(c, "("); }
static V S1455(void) { static V c; return STRC(c, ") == 0"); }
static V S1456(void) { static V c; return STRC(c, "nat_subk("); }
static V S1457(void) { static V c; return STRC(c, ", 1)"); }
static V S1458(void) { static V c; return STRC(c, "("); }
static V S1459(void) { static V c; return STRC(c, ") != 0"); }
static V F_Gen_dpat_dkind(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1448 = a1;
if ((s1448) == 0) {
return F_Gen_dpat_dfields(a0, a4, a5, 0u, F_Gen_dpat_dtag(a3, F_String_dappend(S1449(), F_String_dappend(a5, F_String_dappend(S1450(), F_U32_dshow(a2)))), a6));
} else if ((s1448) == 1) {
return F_Gen_dpat_dtag(a3, F_String_dappend(S1451(), F_String_dappend(a5, F_String_dappend(S1452(), F_String_dappend(F_U32_dshow(a2), S1453())))), a6);
} else if ((s1448) == 2) {
return F_Gen_dpat_dfields(a0, a4, a5, 99u, a6);
} else if ((s1448) == 3) {
return F_Gen_dpat_dcond(F_String_dappend(S1454(), F_String_dappend(a5, S1455())), a6);
} else if (nat_ge(s1448, 4)) {
return F_Gen_dpat_dfields(a0, a4, F_String_dappend(S1456(), F_String_dappend(a5, S1457())), 99u, F_Gen_dpat_dcond(F_String_dappend(S1458(), F_String_dappend(a5, S1459())), a6));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dkind(V *a) { (void)a; return F_Gen_dpat_dkind(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S1461(void) { static V c; return STRC(c, "FLD("); }
static V S1462(void) { static V c; return STRC(c, ", "); }
static V S1463(void) { static V c; return STRC(c, ")"); }
static V F_Gen_dpat_dfields(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1460 = a1;
if ((s1460) == IMM(0)) {
return a4;
} else if (TAG(s1460) == 1) {
{ V t0 = a0; V t1 = FLD(s1460, 1); V t2 = a2; V t3 = F_U32_dinc(a3); V t4 = F_Gen_dpat(a0, FLD(s1460, 0), F_Bool_dpick(F_U32_dis__eq(a3, 99u), a2, F_String_dappend(S1461(), F_String_dappend(a2, F_String_dappend(S1462(), F_String_dappend(F_U32_dshow(a3), S1463()))))), a4); a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dfields(V *a) { (void)a; return F_Gen_dpat_dfields(a[0], a[1], a[2], a[3], a[4]); }
static V F_Gen_dpat_dtag(V a0, V a1, V a2) {
top:;
V s1464 = a0;
if ((s1464) == IMM(1)) {
return a2;
} else if ((s1464) == IMM(0)) {
return F_Gen_dpat_dcond(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dtag(V *a) { (void)a; return F_Gen_dpat_dtag(a[0], a[1], a[2]); }
static V S1466(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dpat_dvar(V a0, V a1, V a2) {
top:;
V v1465 = a2;
return C2(0, FLD(v1465, 0), F_Bool_dpick(F_Str_deq(a0, S1466()), FLD(v1465, 1), C2(1, C2(0, a0, a1), FLD(v1465, 1))));
}
static V W_Gen_dpat_dvar(V *a) { (void)a; return F_Gen_dpat_dvar(a[0], a[1], a[2]); }
static V F_PatR_dbinds(V a0) {
top:;
V v1467 = a0;
return FLD(v1467, 1);
}
static V W_PatR_dbinds(V *a) { (void)a; return F_PatR_dbinds(a[0]); }
static V F_Pat_dvars(V a0, V a1) {
top:;
V s1468 = a0;
if (TAG(s1468) == 0) {
return C2(1, FLD(s1468, 0), a1);
} else if (TAG(s1468) == 1) {
return F_Pats_dvars(FLD(s1468, 1), a1);
} else if (TAG(s1468) == 3) {
{ V t0 = FLD(s1468, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else {
return a1;
}
}
static V W_Pat_dvars(V *a) { (void)a; return F_Pat_dvars(a[0], a[1]); }
static V F_Pats_dvars(V a0, V a1) {
top:;
V s1469 = a0;
if ((s1469) == IMM(0)) {
return a1;
} else if (TAG(s1469) == 1) {
{ V t0 = FLD(s1469, 1); V t1 = F_Pat_dvars(FLD(s1469, 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Pats_dvars(V *a) { (void)a; return F_Pats_dvars(a[0], a[1]); }
static V F_FV_dexpr(V a0, V a1, V a2) {
top:;
V s1470 = a0;
if (TAG(s1470) == 0) {
return F_FV_dvar(FLD(s1470, 0), a1, a2);
} else if (TAG(s1470) == 5) {
return F_FV_dexprs(FLD(s1470, 1), a1, F_FV_dexpr(FLD(s1470, 0), a1, a2));
} else if (TAG(s1470) == 6) {
return F_FV_dexprs(FLD(s1470, 1), a1, a2);
} else if (TAG(s1470) == 7) {
{ V t0 = FLD(s1470, 1); V t1 = F_Pat_dvars(FLD(s1470, 0), a1); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1470) == 8) {
{ V t0 = FLD(s1470, 2); V t1 = F_Pat_dvars(FLD(s1470, 0), a1); V t2 = F_FV_dexpr(FLD(s1470, 1), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1470) == 9) {
return F_FV_dexprs(FLD(s1470, 1), a1, F_FV_dexprs(FLD(s1470, 0), a1, a2));
} else if (TAG(s1470) == 10) {
{ V t0 = FLD(s1470, 1); V t1 = F_Pats_dvars(FLD(s1470, 0), a1); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1470) == 11) {
{ V t0 = FLD(s1470, 1); V t1 = a1; V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1470) == 12) {
{ V t0 = FLD(s1470, 2); V t1 = a1; V t2 = F_FV_dexpr(FLD(s1470, 1), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1470) == 13) {
{ V t0 = FLD(s1470, 0); V t1 = a1; V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else {
return a2;
}
}
static V W_FV_dexpr(V *a) { (void)a; return F_FV_dexpr(a[0], a[1], a[2]); }
static V F_FV_dexprs(V a0, V a1, V a2) {
top:;
V s1471 = a0;
if ((s1471) == IMM(0)) {
return a2;
} else if (TAG(s1471) == 1) {
{ V t0 = FLD(s1471, 1); V t1 = a1; V t2 = F_FV_dexpr(FLD(s1471, 0), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
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
V s1472 = a0;
if ((s1472) == IMM(0)) {
return IMM(0);
} else if (TAG(s1472) == 1) {
return F_Gen_dcaps_dput(FLD(s1472, 0), F_Env_dfind(a1, FLD(s1472, 0)), F_Gen_dcaps(FLD(s1472, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps(V *a) { (void)a; return F_Gen_dcaps(a[0], a[1]); }
static V F_Gen_dcaps_dput(V a0, V a1, V a2) {
top:;
V s1473 = a1;
if ((s1473) == IMM(0)) {
return a2;
} else if (TAG(s1473) == 1) {
return C2(1, C2(0, a0, FLD(s1473, 0)), a2);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps_dput(V *a) { (void)a; return F_Gen_dcaps_dput(a[0], a[1], a[2]); }
static V F_Gen_dctor(V a0, V a1, V a2, V a3) {
top:;
return F_Gen_dctor_dinfo(a0, a1, a2, F_G_dctor(a0, a2), a3);
}
static V W_Gen_dctor(V *a) { (void)a; return F_Gen_dctor(a[0], a[1], a[2], a[3]); }
static V S1475(void) { static V c; return STRC(c, "unknown constructor: "); }
static V S1477(void) { static V c; return STRC(c, "0"); }
static V L1476(V *a) {
return F_Gen_dpure(C1(1, S1477()));
}
static V L1478(V *a) {
return F_Gen_dpure(F_Gen_dctor_dkind(a[1], F_U32_dto__nat(a[0]), a[2]));
}
static V F_Gen_dctor_dinfo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1474 = a3;
if ((s1474) == IMM(0)) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1475(), a2)), mk_clo(L1476, 1, 0, 0));
} else if (TAG(s1474) == 1) {
return F_Gen_dbind(F_Gen_dexprs(a0, a1, a4), mk_clo(L1478, 3, 2, (V[]){FLD(FLD(s1474, 0), 2), FLD(FLD(s1474, 0), 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dctor_dinfo(V *a) { (void)a; return F_Gen_dctor_dinfo(a[0], a[1], a[2], a[3], a[4]); }
static V S1480(void) { static V c; return STRC(c, "IMM("); }
static V S1481(void) { static V c; return STRC(c, ")"); }
static V S1482(void) { static V c; return STRC(c, "0"); }
static V S1483(void) { static V c; return STRC(c, "nat_addk("); }
static V S1484(void) { static V c; return STRC(c, ", 1)"); }
static V F_Gen_dctor_dkind(V a0, V a1, V a2) {
top:;
V s1479 = a1;
if ((s1479) == 0) {
return F_Gen_dctor_dnode(a0, a2);
} else if ((s1479) == 1) {
return C1(1, F_String_dappend(S1480(), F_String_dappend(F_U32_dshow(a0), S1481())));
} else if ((s1479) == 2) {
return F_Doc_dlist(a2);
} else if ((s1479) == 3) {
return C1(1, S1482());
} else if (nat_ge(s1479, 4)) {
return F_Doc_dlist(C2(1, C1(1, S1483()), C2(1, F_Doc_dlist(a2), C2(1, C1(1, S1484()), IMM(0)))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dctor_dkind(V *a) { (void)a; return F_Gen_dctor_dkind(a[0], a[1], a[2]); }
static V S1486(void) { static V c; return STRC(c, "C"); }
static V S1487(void) { static V c; return STRC(c, "("); }
static V S1488(void) { static V c; return STRC(c, ", "); }
static V S1489(void) { static V c; return STRC(c, ")"); }
static V S1490(void) { static V c; return STRC(c, "CN("); }
static V S1491(void) { static V c; return STRC(c, ", "); }
static V S1492(void) { static V c; return STRC(c, ", "); }
static V S1493(void) { static V c; return STRC(c, ")"); }
static V F_Gen_dctor_dnode(V a0, V a1) {
top:;
V v1485 = F_Gen_dlen(a1);
return F_Bool_dpick(F_U32_dis__le(v1485, 4u), F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1486(), F_String_dappend(F_U32_dshow(v1485), F_String_dappend(S1487(), F_String_dappend(F_U32_dshow(a0), S1488()))))), C2(1, F_Gen_dcommas(a1), C2(1, C1(1, S1489()), IMM(0))))), F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1490(), F_String_dappend(F_U32_dshow(a0), F_String_dappend(S1491(), F_String_dappend(F_U32_dshow(v1485), S1492()))))), C2(1, F_Gen_darr(a1), C2(1, C1(1, S1493()), IMM(0))))));
}
static V W_Gen_dctor_dnode(V *a) { (void)a; return F_Gen_dctor_dnode(a[0], a[1]); }
static V F_Gen_dlen(V a0) {
top:;
return F_U32_dfrom__nat(F_List_dlength(a0));
}
static V W_Gen_dlen(V *a) { (void)a; return F_Gen_dlen(a[0]); }
static V L1496(V *a) {
return F_Gen_dpure(C2(1, a[0], a[1]));
}
static V L1495(V *a) {
return F_Gen_dbind(F_Gen_dexprs(a[2], a[1], a[0]), mk_clo(L1496, 2, 1, (V[]){a[3]}));
}
static V F_Gen_dexprs(V a0, V a1, V a2) {
top:;
V s1494 = a2;
if ((s1494) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1494) == 1) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, FLD(s1494, 0)), mk_clo(L1495, 4, 3, (V[]){FLD(s1494, 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dexprs(V *a) { (void)a; return F_Gen_dexprs(a[0], a[1], a[2]); }
static V F_Gen_dcall(V a0, V a1, V a2, V a3) {
top:;
V s1497 = a2;
if (TAG(s1497) == 0) {
return F_Gen_dcall_dvar(a0, a1, FLD(s1497, 0), a3, F_Env_dhas(a1, FLD(s1497, 0)));
} else {
return F_Gen_dcall_dlocal(a0, a1, s1497, a3);
}
}
static V W_Gen_dcall(V *a) { (void)a; return F_Gen_dcall(a[0], a[1], a[2], a[3]); }
static V L1499(V *a) {
return F_Gen_dpure(F_Gen_dapply(a[1], a[0]));
}
static V L1498(V *a) {
return F_Gen_dbind(F_Gen_dexprs(a[2], a[1], a[0]), mk_clo(L1499, 2, 1, (V[]){a[3]}));
}
static V F_Gen_dcall_dlocal(V a0, V a1, V a2, V a3) {
top:;
return F_Gen_dbind(F_Gen_dexpr(a0, a1, a2), mk_clo(L1498, 4, 3, (V[]){a3, a1, a0}));
}
static V W_Gen_dcall_dlocal(V *a) { (void)a; return F_Gen_dcall_dlocal(a[0], a[1], a[2], a[3]); }
static V S1501(void) { static V c; return STRC(c, "apply("); }
static V S1502(void) { static V c; return STRC(c, ", "); }
static V S1503(void) { static V c; return STRC(c, ")"); }
static V F_Gen_dapply(V a0, V a1) {
top:;
V s1500 = a0;
if ((s1500) == IMM(0)) {
return a1;
} else if (TAG(s1500) == 1) {
{ V t0 = FLD(s1500, 1); V t1 = F_Doc_dlist(C2(1, C1(1, S1501()), C2(1, a1, C2(1, C1(1, S1502()), C2(1, FLD(s1500, 0), C2(1, C1(1, S1503()), IMM(0))))))); a0 = t0; a1 = t1; goto top; }
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
V s1504 = a2;
if ((s1504) == IMM(0)) {
return IMM(0);
} else if (TAG(s1504) == 1) {
return IMM(1);
} else { bend_fail("incomplete match"); }
}
static V W_Maybe_dis__some(V *a) { (void)a; return F_Maybe_dis__some(a[2]); }
static V F_Gen_dcall_dvar(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1505 = a4;
if ((s1505) == IMM(1)) {
return F_Gen_dcall_dlocal(a0, a1, C1(0, a2), a3);
} else if ((s1505) == IMM(0)) {
return F_Gen_dcall_ddef(a0, a1, a2, F_G_ddef(a0, a2), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcall_dvar(V *a) { (void)a; return F_Gen_dcall_dvar(a[0], a[1], a[2], a[3], a[4]); }
static V F_Gen_dcall_ddef(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1506 = a3;
return F_Gen_dcall_dkind(a0, a1, a2, F_U32_dto__nat(FLD(v1506, 0)), FLD(v1506, 1), F_Gen_dsplit(FLD(v1506, 1), a4, C4(0, IMM(0), IMM(0), IMM(0), IMM(0))));
}
static V W_Gen_dcall_ddef(V *a) { (void)a; return F_Gen_dcall_ddef(a[0], a[1], a[2], a[3], a[4]); }
static V S1513(void) { static V c; return STRC(c, ""); }
static V F_Gen_dsplit(V a0, V a1, V a2) {
top:;
V s1507 = a0;
V s1508 = a1;
if ((s1507) == IMM(0)) {
V v1509 = a2;
return C4(0, FLD(v1509, 0), FLD(v1509, 1), s1508, IMM(1));
} else if (TAG(s1507) == 1 && (s1508) == IMM(0)) {
V v1510 = a2;
return C4(0, FLD(v1510, 0), FLD(v1510, 1), IMM(0), IMM(0));
} else if (TAG(s1507) == 1 && (FLD(s1507, 0)) == IMM(1) && TAG(s1508) == 1) {
V v1511 = a2;
{ V t0 = FLD(s1507, 1); V t1 = FLD(s1508, 1); V t2 = C4(0, F_List_dappend(FLD(v1511, 0), C2(1, FLD(s1508, 0), IMM(0))), F_List_dappend(FLD(v1511, 1), C2(1, FLD(s1508, 0), IMM(0))), FLD(v1511, 2), FLD(v1511, 3)); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1507) == 1 && (FLD(s1507, 0)) == IMM(0) && TAG(s1508) == 1) {
V v1512 = a2;
{ V t0 = FLD(s1507, 1); V t1 = FLD(s1508, 1); V t2 = C4(0, FLD(v1512, 0), F_List_dappend(FLD(v1512, 1), C2(1, C2(14, S1513(), IMM(0)), IMM(0))), FLD(v1512, 2), FLD(v1512, 3)); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dsplit(V *a) { (void)a; return F_Gen_dsplit(a[0], a[1], a[2]); }
static V S1515(void) { static V c; return STRC(c, "0"); }
static V S1516(void) { static V c; return STRC(c, "unknown function: "); }
static V S1518(void) { static V c; return STRC(c, "0"); }
static V L1517(V *a) {
return F_Gen_dpure(C1(1, S1518()));
}
static V L1519(V *a) {
return F_Gen_dcall_dsplit(a[4], a[3], a[2], a[1], a[0]);
}
static V F_Gen_dcall_dkind(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1514 = a3;
if ((s1514) == 3) {
return F_Gen_dpure(C1(1, S1515()));
} else if ((s1514) == 99) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1516(), a2)), mk_clo(L1517, 1, 0, 0));
} else {
return F_Gen_dbind(F_Gen_dref(a2), mk_clo(L1519, 6, 5, (V[]){a5, a4, a2, a1, a0}));
}
}
static V W_Gen_dcall_dkind(V *a) { (void)a; return F_Gen_dcall_dkind(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Gen_dcall_dsplit(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1520 = a4;
return F_Gen_dcall_dfull(a0, a1, a2, a3, FLD(v1520, 0), FLD(v1520, 1), FLD(v1520, 2), FLD(v1520, 3));
}
static V W_Gen_dcall_dsplit(V *a) { (void)a; return F_Gen_dcall_dsplit(a[0], a[1], a[2], a[3], a[4]); }
static V S1524(void) { static V c; return STRC(c, "("); }
static V S1525(void) { static V c; return STRC(c, ")"); }
static V L1523(V *a) {
return F_Gen_dpure(F_Gen_dapply(a[2], F_Doc_dlist(C2(1, C1(1, F_String_dappend(F_Gen_df(a[1]), S1524())), C2(1, F_Gen_dcommas(a[0]), C2(1, C1(1, S1525()), IMM(0)))))));
}
static V L1522(V *a) {
return F_Gen_dbind(F_Gen_dexprs(a[3], a[2], a[1]), mk_clo(L1523, 3, 2, (V[]){a[4], a[0]}));
}
static V S1527(void) { static V c; return STRC(c, "mk_clo("); }
static V S1528(void) { static V c; return STRC(c, ", "); }
static V S1529(void) { static V c; return STRC(c, ", "); }
static V S1530(void) { static V c; return STRC(c, ", "); }
static V S1531(void) { static V c; return STRC(c, ")"); }
static V L1526(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1527(), F_String_dappend(F_Gen_dw(a[1]), F_String_dappend(S1528(), F_String_dappend(F_U32_dshow(F_U32_dfrom__nat(F_List_dlength(a[0]))), F_String_dappend(S1529(), F_String_dappend(F_U32_dshow(F_Gen_dlen(a[2])), S1530()))))))), C2(1, F_Gen_darr(a[2]), C2(1, C1(1, S1531()), IMM(0))))));
}
static V F_Gen_dcall_dfull(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s1521 = a7;
if ((s1521) == IMM(1)) {
return F_Gen_dbind(F_Gen_dexprs(a0, a1, a4), mk_clo(L1522, 5, 4, (V[]){a2, a6, a1, a0}));
} else if ((s1521) == IMM(0)) {
return F_Gen_dbind(F_Gen_dexprs(a0, a1, a5), mk_clo(L1526, 3, 2, (V[]){a3, a2}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcall_dfull(V *a) { (void)a; return F_Gen_dcall_dfull(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V L1532(V *a) {
return F_Gen_dref_dgo(a[0], a[1]);
}
static V F_Gen_dref(V a0) {
top:;
return mk_clo(L1532, 2, 1, (V[]){a0});
}
static V W_Gen_dref(V *a) { (void)a; return F_Gen_dref(a[0]); }
static V F_Gen_dref_dgo(V a0, V a1) {
top:;
V v1533 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v1533, 0), FLD(v1533, 1), FLD(v1533, 2), C2(1, a0, FLD(v1533, 3)), FLD(v1533, 4), FLD(v1533, 5), FLD(v1533, 6)}));
}
static V W_Gen_dref_dgo(V *a) { (void)a; return F_Gen_dref_dgo(a[0], a[1]); }
static V S1535(void) { static V c; return STRC(c, "S"); }
static V S1537(void) { static V c; return STRC(c, "static V "); }
static V S1538(void) { static V c; return STRC(c, "(void);\012"); }
static V S1540(void) { static V c; return STRC(c, "static V "); }
static V S1541(void) { static V c; return STRC(c, "(void) { static V c; return STRC(c, \042"); }
static V S1542(void) { static V c; return STRC(c, "\042); }\012"); }
static V S1544(void) { static V c; return STRC(c, "()"); }
static V L1543(V *a) {
return F_Gen_dpure(C1(1, F_String_dappend(a[0], S1544())));
}
static V L1539(V *a) {
return F_Gen_dbind(F_Gen_dcode(C1(1, F_String_dappend(S1540(), F_String_dappend(a[1], F_String_dappend(S1541(), F_String_dappend(F_Gen_dlit(a[0]), S1542())))))), mk_clo(L1543, 2, 1, (V[]){a[1]}));
}
static V L1536(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S1537(), F_String_dappend(a[1], S1538())))), mk_clo(L1539, 3, 2, (V[]){a[0], a[1]}));
}
static V L1534(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1535(), F_U32_dshow(a[1]))), mk_clo(L1536, 2, 1, (V[]){a[0]}));
}
static V F_Gen_dstr(V a0) {
top:;
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1534, 2, 1, (V[]){a0}));
}
static V W_Gen_dstr(V *a) { (void)a; return F_Gen_dstr(a[0]); }
static V S1546(void) { static V c; return STRC(c, ""); }
static V F_Gen_dlit(V a0) {
top:;
V s1545 = a0;
if ((s1545) == IMM(0)) {
return S1546();
} else if (TAG(s1545) == 1) {
return F_String_dappend(F_Gen_dlit__chr(FLD(s1545, 0)), F_Gen_dlit(FLD(s1545, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dlit(V *a) { (void)a; return F_Gen_dlit(a[0]); }
static V S1547(void) { static V c; return STRC(c, "\042"); }
static V S1548(void) { static V c; return STRC(c, "\134"); }
static V S1549(void) { static V c; return STRC(c, "\077"); }
static V F_Gen_dlit__chr(V a0) {
top:;
return F_Bool_dpick(F_Bool_dand(F_Bool_dand(F_U32_dis__ge(a0, 32u), F_U32_dis__lt(a0, 127u)), F_Bool_dnot(F_Str_dhas(C2(1, S1547(), C2(1, S1548(), C2(1, S1549(), IMM(0)))), F_Str_dchr(a0)))), F_Str_dchr(a0), F_Gen_dutf8(a0));
}
static V W_Gen_dlit__chr(V *a) { (void)a; return F_Gen_dlit__chr(a[0]); }
static V F_Gen_dutf8(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__lt(a0, 128u), F_Gen_doct(a0), F_Bool_dpick(F_U32_dis__lt(a0, 2048u), F_String_dappend(F_Gen_doct(F_U32_dor(192u, F_U32_dshrn(a0, 6u))), F_Gen_doct(F_U32_dor(128u, F_U32_dand(a0, 63u)))), F_Bool_dpick(F_U32_dis__lt(a0, 65536u), F_String_dappend(F_Gen_doct(F_U32_dor(224u, F_U32_dshrn(a0, 12u))), F_String_dappend(F_Gen_doct(F_U32_dor(128u, F_U32_dand(F_U32_dshrn(a0, 6u), 63u))), F_Gen_doct(F_U32_dor(128u, F_U32_dand(a0, 63u))))), F_String_dappend(F_Gen_doct(F_U32_dor(240u, F_U32_dshrn(a0, 18u))), F_String_dappend(F_Gen_doct(F_U32_dor(128u, F_U32_dand(F_U32_dshrn(a0, 12u), 63u))), F_String_dappend(F_Gen_doct(F_U32_dor(128u, F_U32_dand(F_U32_dshrn(a0, 6u), 63u))), F_Gen_doct(F_U32_dor(128u, F_U32_dand(a0, 63u)))))))));
}
static V W_Gen_dutf8(V *a) { (void)a; return F_Gen_dutf8(a[0]); }
static V W_U32_dor(V *a) { (void)a; return F_U32_dor(a[0], a[1]); }
static V S1550(void) { static V c; return STRC(c, "\134"); }
static V F_Gen_doct(V a0) {
top:;
return F_String_dappend(S1550(), F_String_dappend(F_Str_dchr(F_U32_dadd(48u, F_U32_dand(F_U32_dshrn(a0, 6u), 7u))), F_String_dappend(F_Str_dchr(F_U32_dadd(48u, F_U32_dand(F_U32_dshrn(a0, 3u), 7u))), F_Str_dchr(F_U32_dadd(48u, F_U32_dand(a0, 7u))))));
}
static V W_Gen_doct(V *a) { (void)a; return F_Gen_doct(a[0]); }
static V F_Gen_dvar(V a0, V a1, V a2) {
top:;
return F_Gen_dvar_dfound(a0, a2, F_Env_dfind(a1, a2));
}
static V W_Gen_dvar(V *a) { (void)a; return F_Gen_dvar(a[0], a[1], a[2]); }
static V S1552(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dvar_dfound(V a0, V a1, V a2) {
top:;
V s1551 = a2;
if (TAG(s1551) == 1) {
return F_Gen_dpure(C1(1, FLD(s1551, 0)));
} else if ((s1551) == IMM(0)) {
return F_Gen_dvar_dglobal(a0, a1, F_Str_deq(a1, S1552()));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dvar_dfound(V *a) { (void)a; return F_Gen_dvar_dfound(a[0], a[1], a[2]); }
static V S1554(void) { static V c; return STRC(c, "0"); }
static V F_Gen_dvar_dglobal(V a0, V a1, V a2) {
top:;
V s1553 = a2;
if ((s1553) == IMM(1)) {
return F_Gen_dpure(C1(1, S1554()));
} else if ((s1553) == IMM(0)) {
return F_Gen_dvar_ddef(a1, F_G_ddef(a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dvar_dglobal(V *a) { (void)a; return F_Gen_dvar_dglobal(a[0], a[1], a[2]); }
static V F_Gen_dvar_ddef(V a0, V a1) {
top:;
V v1555 = a1;
return F_Gen_dvar_dkind(a0, F_U32_dto__nat(FLD(v1555, 0)), F_U32_dfrom__nat(F_List_dlength(FLD(v1555, 1))));
}
static V W_Gen_dvar_ddef(V *a) { (void)a; return F_Gen_dvar_ddef(a[0], a[1]); }
static V S1557(void) { static V c; return STRC(c, "0"); }
static V S1558(void) { static V c; return STRC(c, "unknown name: "); }
static V S1560(void) { static V c; return STRC(c, "0"); }
static V L1559(V *a) {
return F_Gen_dpure(C1(1, S1560()));
}
static V S1562(void) { static V c; return STRC(c, "()"); }
static V S1563(void) { static V c; return STRC(c, "mk_clo("); }
static V S1564(void) { static V c; return STRC(c, ", "); }
static V S1565(void) { static V c; return STRC(c, ", 0, 0)"); }
static V L1561(V *a) {
return F_Gen_dpure(F_Bool_dpick(F_U32_dis__zero(a[1]), C1(1, F_String_dappend(F_Gen_df(a[0]), S1562())), C1(1, F_String_dappend(S1563(), F_String_dappend(F_Gen_dw(a[0]), F_String_dappend(S1564(), F_String_dappend(F_U32_dshow(a[1]), S1565())))))));
}
static V F_Gen_dvar_dkind(V a0, V a1, V a2) {
top:;
V s1556 = a1;
if ((s1556) == 3) {
return F_Gen_dpure(C1(1, S1557()));
} else if ((s1556) == 99) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1558(), a0)), mk_clo(L1559, 1, 0, 0));
} else {
return F_Gen_dbind(F_Gen_dref(a0), mk_clo(L1561, 3, 2, (V[]){a0, a2}));
}
}
static V W_Gen_dvar_dkind(V *a) { (void)a; return F_Gen_dvar_dkind(a[0], a[1], a[2]); }
static V F_Gen_dis__tail(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1566 = a1;
return F_Bool_dand(F_Bool_dand(F_Gen_dis__ret(a2), F_Str_deq(FLD(v1566, 0), a3)), F_Bool_dand(F_Bool_dnot(F_Env_dhas(a0, a3)), F_Nat_dis__eq(F_List_dlength(FLD(v1566, 1)), F_List_dlength(a4))));
}
static V W_Gen_dis__tail(V *a) { (void)a; return F_Gen_dis__tail(a[0], a[1], a[2], a[3], a[4]); }
static V W_Nat_dis__eq(V *a) { (void)a; return F_Nat_dis__eq(a[0], a[1]); }
static V F_Gen_dis__ret(V a0) {
top:;
V s1567 = a0;
if ((s1567) == IMM(0)) {
return IMM(1);
} else if (TAG(s1567) == 1) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dis__ret(V *a) { (void)a; return F_Gen_dis__ret(a[0]); }
static V L1569(V *a) {
return F_Gen_dpure(F_Gen_dret(a[0], a[1]));
}
static V F_Gen_dstmt_dcall(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1568 = a6;
if ((s1568) == IMM(1)) {
return F_Gen_dtail_dself(a0, a1, a2, a5);
} else if ((s1568) == IMM(0)) {
return F_Gen_dbind(F_Gen_dcall(a0, a1, C1(0, a4), a5), mk_clo(L1569, 2, 1, (V[]){a3}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dstmt_dcall(V *a) { (void)a; return F_Gen_dstmt_dcall(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Gen_dtail_dself(V a0, V a1, V a2, V a3) {
top:;
V v1570 = a2;
return F_Gen_dtail(a0, a1, FLD(v1570, 2), F_Gen_dsplit(FLD(v1570, 1), a3, C4(0, IMM(0), IMM(0), IMM(0), IMM(0))));
}
static V W_Gen_dtail_dself(V *a) { (void)a; return F_Gen_dtail_dself(a[0], a[1], a[2], a[3]); }
static V S1573(void) { static V c; return STRC(c, "{ "); }
static V S1574(void) { static V c; return STRC(c, "goto top; }\012"); }
static V L1572(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1573()), C2(1, F_Gen_dtail_dtemps(a[1], 0u), C2(1, F_Gen_dtail_dassign(a[0], 0u), C2(1, C1(1, S1574()), IMM(0)))))));
}
static V F_Gen_dtail(V a0, V a1, V a2, V a3) {
top:;
V v1571 = a3;
return F_Gen_dbind(F_Gen_dexprs(a0, a1, FLD(v1571, 0)), mk_clo(L1572, 2, 1, (V[]){a2}));
}
static V W_Gen_dtail(V *a) { (void)a; return F_Gen_dtail(a[0], a[1], a[2], a[3]); }
static V S1576(void) { static V c; return STRC(c, " = t"); }
static V S1577(void) { static V c; return STRC(c, "; "); }
static V F_Gen_dtail_dassign(V a0, V a1) {
top:;
V s1575 = a0;
if ((s1575) == IMM(0)) {
return IMM(0);
} else if (TAG(s1575) == 1) {
return F_Doc_dlist(C2(1, C1(1, F_String_dappend(FLD(s1575, 0), F_String_dappend(S1576(), F_String_dappend(F_U32_dshow(a1), S1577())))), C2(1, F_Gen_dtail_dassign(FLD(s1575, 1), F_U32_dinc(a1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dtail_dassign(V *a) { (void)a; return F_Gen_dtail_dassign(a[0], a[1]); }
static V S1579(void) { static V c; return STRC(c, "V t"); }
static V S1580(void) { static V c; return STRC(c, " = "); }
static V S1581(void) { static V c; return STRC(c, "; "); }
static V F_Gen_dtail_dtemps(V a0, V a1) {
top:;
V s1578 = a0;
if ((s1578) == IMM(0)) {
return IMM(0);
} else if (TAG(s1578) == 1) {
return F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1579(), F_String_dappend(F_U32_dshow(a1), S1580()))), C2(1, FLD(s1578, 0), C2(1, C1(1, S1581()), C2(1, F_Gen_dtail_dtemps(FLD(s1578, 1), F_U32_dinc(a1)), IMM(0))))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dtail_dtemps(V *a) { (void)a; return F_Gen_dtail_dtemps(a[0], a[1]); }
static V L1582(V *a) {
return F_Gen_dmatch_dgo(a[4], a[3], a[2], a[1], a[0], a[5]);
}
static V F_Gen_dmatch(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Gen_dbind(F_Gen_dscrs(a0, a1, a4), mk_clo(L1582, 6, 5, (V[]){a5, a3, a2, a1, a0}));
}
static V W_Gen_dmatch(V *a) { (void)a; return F_Gen_dmatch(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L1584(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V F_Gen_dmatch_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v1583 = a5;
return F_Gen_dbind(F_Gen_dcases(a0, a1, a2, a3, FLD(v1583, 0), a4), mk_clo(L1584, 2, 1, (V[]){FLD(v1583, 1)}));
}
static V W_Gen_dmatch_dgo(V *a) { (void)a; return F_Gen_dmatch_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1586(void) { static V c; return STRC(c, "{ bend_fail(\042incomplete match\042); }\012"); }
static V L1590(V *a) {
return F_Gen_dcases_dnext(a[6], a[5], a[4], a[3], a[2], a[1], F_List_dreverse(a[0]), a[7]);
}
static V F_Gen_dcases(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1585 = a5;
if ((s1585) == IMM(0)) {
return F_Gen_dpure(C1(1, S1586()));
} else if (TAG(s1585) == 1 && TAG(FLD(s1585, 0)) == 10) {
V v1587 = F_Gen_dpats(a0, FLD(FLD(s1585, 0), 0), a4, C2(0, IMM(0), IMM(0)));
V v1588 = F_PatR_dconds(v1587);
V v1589 = F_PatR_dbinds(v1587);
return F_Gen_dbind(F_Gen_dstmt(a0, F_List_dappend(v1589, a1), a2, a3, FLD(FLD(s1585, 0), 1)), mk_clo(L1590, 8, 7, (V[]){v1588, FLD(s1585, 1), a4, a3, a2, a1, a0}));
} else if (TAG(s1585) == 1) {
{ V t0 = a0; V t1 = a1; V t2 = a2; V t3 = a3; V t4 = a4; V t5 = FLD(s1585, 1); a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; a5 = t5; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcases(V *a) { (void)a; return F_Gen_dcases(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1592(void) { static V c; return STRC(c, "{\012"); }
static V S1593(void) { static V c; return STRC(c, "}\012"); }
static V S1595(void) { static V c; return STRC(c, "if ("); }
static V S1596(void) { static V c; return STRC(c, ") {\012"); }
static V S1597(void) { static V c; return STRC(c, "} else "); }
static V L1594(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1595(), F_String_dappend(F_Gen_dand(C2(1, a[2], a[1])), S1596()))), C2(1, a[0], C2(1, C1(1, S1597()), C2(1, a[3], IMM(0)))))));
}
static V F_Gen_dcases_dnext(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s1591 = a6;
if ((s1591) == IMM(0)) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1592()), C2(1, a7, C2(1, C1(1, S1593()), IMM(0))))));
} else if (TAG(s1591) == 1) {
return F_Gen_dbind(F_Gen_dcases(a0, a1, a2, a3, a4, a5), mk_clo(L1594, 4, 3, (V[]){a7, FLD(s1591, 1), FLD(s1591, 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcases_dnext(V *a) { (void)a; return F_Gen_dcases_dnext(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S1599(void) { static V c; return STRC(c, "1"); }
static V S1600(void) { static V c; return STRC(c, " && "); }
static V F_Gen_dand(V a0) {
top:;
V s1598 = a0;
if ((s1598) == IMM(0)) {
return S1599();
} else if (TAG(s1598) == 1 && (FLD(s1598, 1)) == IMM(0)) {
return FLD(s1598, 0);
} else if (TAG(s1598) == 1) {
return F_String_dappend(FLD(s1598, 0), F_String_dappend(S1600(), F_Gen_dand(FLD(s1598, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dand(V *a) { (void)a; return F_Gen_dand(a[0]); }
static V F_PatR_dconds(V a0) {
top:;
V v1601 = a0;
return FLD(v1601, 0);
}
static V W_PatR_dconds(V *a) { (void)a; return F_PatR_dconds(a[0]); }
static V F_Gen_dpats(V a0, V a1, V a2, V a3) {
top:;
V s1602 = a1;
V s1603 = a2;
if (TAG(s1602) == 1 && TAG(s1603) == 1) {
{ V t0 = a0; V t1 = FLD(s1602, 1); V t2 = FLD(s1603, 1); V t3 = F_Gen_dpat(a0, FLD(s1602, 0), FLD(s1603, 0), a3); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else {
return a3;
}
}
static V W_Gen_dpats(V *a) { (void)a; return F_Gen_dpats(a[0], a[1], a[2], a[3]); }
static V S1606(void) { static V c; return STRC(c, "s"); }
static V L1609(V *a) {
return F_Gen_dpure(F_Gen_dscrs_dput(a[1], a[0], a[2]));
}
static V L1608(V *a) {
return F_Gen_dbind(F_Gen_dscrs(a[3], a[2], a[1]), mk_clo(L1609, 3, 2, (V[]){a[4], a[0]}));
}
static V L1607(V *a) {
return F_Gen_dbind(F_Gen_dexpr(a[3], a[2], a[1]), mk_clo(L1608, 5, 4, (V[]){a[4], a[0], a[2], a[3]}));
}
static V L1605(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1606(), F_U32_dshow(a[4]))), mk_clo(L1607, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Gen_dscrs(V a0, V a1, V a2) {
top:;
V s1604 = a2;
if ((s1604) == IMM(0)) {
return F_Gen_dpure(C2(0, IMM(0), IMM(0)));
} else if (TAG(s1604) == 1) {
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1605, 5, 4, (V[]){FLD(s1604, 1), FLD(s1604, 0), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dscrs(V *a) { (void)a; return F_Gen_dscrs(a[0], a[1], a[2]); }
static V S1611(void) { static V c; return STRC(c, "V "); }
static V S1612(void) { static V c; return STRC(c, " = "); }
static V S1613(void) { static V c; return STRC(c, ";\012"); }
static V F_Gen_dscrs_dput(V a0, V a1, V a2) {
top:;
V v1610 = a2;
return C2(0, C2(1, a0, FLD(v1610, 0)), F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1611(), F_String_dappend(a0, S1612()))), C2(1, a1, C2(1, C1(1, S1613()), C2(1, FLD(v1610, 1), IMM(0)))))));
}
static V W_Gen_dscrs_dput(V *a) { (void)a; return F_Gen_dscrs_dput(a[0], a[1], a[2]); }
static V S1615(void) { static V c; return STRC(c, "_"); }
static V S1616(void) { static V c; return STRC(c, "%par"); }
static V F_Gen_dlet(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1614 = a4;
if (TAG(s1614) == 0) {
return F_Gen_dlet_dvar(a0, a1, a2, a3, FLD(s1614, 0), a5, a6, F_Str_deq(FLD(s1614, 0), S1615()));
} else if (TAG(s1614) == 1) {
return F_Gen_dlet_dctor(a0, a1, a2, a3, FLD(s1614, 0), FLD(s1614, 1), a5, a6, F_Str_deq(FLD(s1614, 0), S1616()));
} else {
return F_Gen_dlet_dpat(a0, a1, a2, a3, s1614, a5, a6);
}
}
static V W_Gen_dlet(V *a) { (void)a; return F_Gen_dlet(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S1618(void) { static V c; return STRC(c, "v"); }
static V S1623(void) { static V c; return STRC(c, "V "); }
static V S1624(void) { static V c; return STRC(c, " = "); }
static V S1625(void) { static V c; return STRC(c, ";\012"); }
static V L1622(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1623(), F_String_dappend(a[1], S1624()))), C2(1, a[0], C2(1, C1(1, S1625()), C2(1, a[2], IMM(0)))))));
}
static V L1621(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[6], F_List_dappend(a[7], a[5]), a[4], a[3], a[2]), mk_clo(L1622, 3, 2, (V[]){a[0], a[1]}));
}
static V L1620(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_PatR_dbinds(F_Gen_dpat(a[6], a[5], a[4], C2(0, IMM(0), IMM(0))))), mk_clo(L1621, 8, 7, (V[]){a[7], a[4], a[0], a[1], a[2], a[3], a[6]}));
}
static V L1619(V *a) {
return F_Gen_dbind(F_Gen_dexpr(a[6], a[5], a[4]), mk_clo(L1620, 8, 7, (V[]){a[0], a[1], a[2], a[5], a[7], a[3], a[6]}));
}
static V L1617(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1618(), F_U32_dshow(a[7]))), mk_clo(L1619, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V F_Gen_dlet_dpat(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1617, 8, 7, (V[]){a6, a3, a2, a4, a5, a1, a0}));
}
static V W_Gen_dlet_dpat(V *a) { (void)a; return F_Gen_dlet_dpat(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Gen_dlet_dctor(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s1626 = a8;
if ((s1626) == IMM(1)) {
return F_Gen_dlet_dpar(a0, a1, a2, a3, a5, a6, a7);
} else if ((s1626) == IMM(0)) {
return F_Gen_dlet_dpat(a0, a1, a2, a3, C2(1, a4, a5), a6, a7);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dlet_dctor(V *a) { (void)a; return F_Gen_dlet_dctor(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Gen_dlet_dpar(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1627 = a5;
if (TAG(s1627) == 6) {
return F_Gen_dpar(a0, a1, a2, a3, a4, FLD(s1627, 1), a6);
} else {
return F_Gen_dpar(a0, a1, a2, a3, a4, C2(1, s1627, IMM(0)), a6);
}
}
static V W_Gen_dlet_dpar(V *a) { (void)a; return F_Gen_dlet_dpar(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V L1630(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V L1629(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[6], F_Gen_dpar_denv(a[5], a[4], 0u, a[3]), a[2], a[1], a[0]), mk_clo(L1630, 2, 1, (V[]){a[7]}));
}
static V L1628(V *a) {
return F_Gen_dbind(F_Gen_dpar_dvals(a[6], a[5], a[7], 0u, a[4]), mk_clo(L1629, 8, 7, (V[]){a[0], a[1], a[2], a[5], a[7], a[3], a[6]}));
}
static V F_Gen_dpar(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1628, 8, 7, (V[]){a6, a3, a2, a4, a5, a1, a0}));
}
static V W_Gen_dpar(V *a) { (void)a; return F_Gen_dpar(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S1632(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dpar_denv(V a0, V a1, V a2, V a3) {
top:;
V s1631 = a0;
if ((s1631) == IMM(0)) {
return a3;
} else if (TAG(s1631) == 1 && TAG(FLD(s1631, 0)) == 0) {
{ V t0 = FLD(s1631, 1); V t1 = a1; V t2 = F_U32_dinc(a2); V t3 = F_Bool_dpick(F_Str_deq(FLD(FLD(s1631, 0), 0), S1632()), a3, C2(1, C2(0, FLD(FLD(s1631, 0), 0), F_Gen_dpar_dname(a1, a2)), a3)); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1631) == 1) {
{ V t0 = FLD(s1631, 1); V t1 = a1; V t2 = F_U32_dinc(a2); V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpar_denv(V *a) { (void)a; return F_Gen_dpar_denv(a[0], a[1], a[2], a[3]); }
static V S1633(void) { static V c; return STRC(c, "p"); }
static V S1634(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dpar_dname(V a0, V a1) {
top:;
return F_String_dappend(S1633(), F_String_dappend(F_U32_dshow(a0), F_String_dappend(S1634(), F_U32_dshow(a1))));
}
static V W_Gen_dpar_dname(V *a) { (void)a; return F_Gen_dpar_dname(a[0], a[1]); }
static V S1637(void) { static V c; return STRC(c, "V "); }
static V S1638(void) { static V c; return STRC(c, " = "); }
static V S1639(void) { static V c; return STRC(c, ";\012"); }
static V L1636(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1637(), F_String_dappend(F_Gen_dpar_dname(a[1], a[0]), S1638()))), C2(1, a[2], C2(1, C1(1, S1639()), IMM(0))))));
}
static V S1640(void) { static V c; return STRC(c, "_"); }
static V S1643(void) { static V c; return STRC(c, "V "); }
static V S1644(void) { static V c; return STRC(c, "t = par_fork("); }
static V S1645(void) { static V c; return STRC(c, ");\012"); }
static V S1646(void) { static V c; return STRC(c, "V "); }
static V S1647(void) { static V c; return STRC(c, " = par_join("); }
static V S1648(void) { static V c; return STRC(c, "t);\012"); }
static V L1642(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1643(), F_String_dappend(F_Gen_dpar_dname(a[2], a[1]), S1644()))), C2(1, a[0], C2(1, C1(1, S1645()), C2(1, a[3], C2(1, C1(1, F_String_dappend(S1646(), F_String_dappend(F_Gen_dpar_dname(a[2], a[1]), F_String_dappend(S1647(), F_String_dappend(F_Gen_dpar_dname(a[2], a[1]), S1648()))))), IMM(0))))))));
}
static V L1641(V *a) {
return F_Gen_dbind(F_Gen_dpar_dvals(a[4], a[3], a[2], F_U32_dinc(a[1]), a[0]), mk_clo(L1642, 4, 3, (V[]){a[5], a[1], a[2]}));
}
static V F_Gen_dpar_dvals(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1635 = a4;
if ((s1635) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1635) == 1 && (FLD(s1635, 1)) == IMM(0)) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, FLD(s1635, 0)), mk_clo(L1636, 3, 2, (V[]){a3, a2}));
} else if (TAG(s1635) == 1) {
return F_Gen_dbind(F_Gen_dlam(a0, a1, C1(0, S1640()), FLD(s1635, 0)), mk_clo(L1641, 6, 5, (V[]){FLD(s1635, 1), a3, a2, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpar_dvals(V *a) { (void)a; return F_Gen_dpar_dvals(a[0], a[1], a[2], a[3], a[4]); }
static V S1652(void) { static V c; return STRC(c, "(void)("); }
static V S1653(void) { static V c; return STRC(c, ");\012"); }
static V L1651(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1652()), C2(1, a[0], C2(1, C1(1, S1653()), C2(1, a[1], IMM(0)))))));
}
static V L1650(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[4], a[3], a[2], a[1], a[0]), mk_clo(L1651, 2, 1, (V[]){a[5]}));
}
static V S1655(void) { static V c; return STRC(c, "v"); }
static V S1659(void) { static V c; return STRC(c, "V "); }
static V S1660(void) { static V c; return STRC(c, " = "); }
static V S1661(void) { static V c; return STRC(c, ";\012"); }
static V L1658(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1659(), F_String_dappend(a[1], S1660()))), C2(1, a[0], C2(1, C1(1, S1661()), C2(1, a[2], IMM(0)))))));
}
static V L1657(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[6], C2(1, C2(0, a[5], a[4]), a[3]), a[2], a[1], a[0]), mk_clo(L1658, 3, 2, (V[]){a[7], a[4]}));
}
static V L1656(V *a) {
return F_Gen_dbind(F_Gen_dexpr(a[6], a[5], a[4]), mk_clo(L1657, 8, 7, (V[]){a[0], a[1], a[2], a[5], a[7], a[3], a[6]}));
}
static V L1654(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1655(), F_U32_dshow(a[7]))), mk_clo(L1656, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V F_Gen_dlet_dvar(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s1649 = a7;
if ((s1649) == IMM(1)) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, a5), mk_clo(L1650, 6, 5, (V[]){a6, a3, a2, a1, a0}));
} else if ((s1649) == IMM(0)) {
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1654, 8, 7, (V[]){a6, a3, a2, a4, a5, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dlet_dvar(V *a) { (void)a; return F_Gen_dlet_dvar(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S1663(void) { static V c; return STRC(c, ""); }
static V S1664(void) { static V c; return STRC(c, "#define "); }
static V S1665(void) { static V c; return STRC(c, " ((3u << 16) | "); }
static V S1666(void) { static V c; return STRC(c, "u)\012"); }
static V F_Gen_dcids(V a0, V a1, V a2) {
top:;
V s1662 = a1;
if ((s1662) == IMM(0)) {
return S1663();
} else if (TAG(s1662) == 1 && TAG(FLD(s1662, 0)) == 3) {
return F_String_dappend(F_Gen_dcids_dctors(a0, FLD(FLD(s1662, 0), 2)), F_Gen_dcids(a0, FLD(s1662, 1), a2));
} else if (TAG(s1662) == 1 && TAG(FLD(s1662, 0)) == 1) {
return F_String_dappend(S1664(), F_String_dappend(F_Gen_dcid(FLD(FLD(s1662, 0), 0)), F_String_dappend(S1665(), F_String_dappend(F_U32_dshow(a2), F_String_dappend(S1666(), F_Gen_dcids(a0, FLD(s1662, 1), F_U32_dinc(a2)))))));
} else if (TAG(s1662) == 1) {
{ V t0 = a0; V t1 = FLD(s1662, 1); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcids(V *a) { (void)a; return F_Gen_dcids(a[0], a[1], a[2]); }
static V S1668(void) { static V c; return STRC(c, ""); }
static V F_Gen_dcids_dctors(V a0, V a1) {
top:;
V s1667 = a1;
if ((s1667) == IMM(0)) {
return S1668();
} else if (TAG(s1667) == 1) {
return F_String_dappend(F_Gen_dcids_dkind(FLD(FLD(s1667, 0), 0), F_G_dctor(a0, FLD(FLD(s1667, 0), 0))), F_Gen_dcids_dctors(a0, FLD(s1667, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcids_dctors(V *a) { (void)a; return F_Gen_dcids_dctors(a[0], a[1]); }
static V S1670(void) { static V c; return STRC(c, ""); }
static V F_Gen_dcids_dkind(V a0, V a1) {
top:;
V s1669 = a1;
if ((s1669) == IMM(0)) {
return S1670();
} else if (TAG(s1669) == 1) {
return F_Gen_dcids_dline(a0, F_U32_dto__nat(FLD(FLD(s1669, 0), 2)), FLD(FLD(s1669, 0), 0));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcids_dkind(V *a) { (void)a; return F_Gen_dcids_dkind(a[0], a[1]); }
static V S1672(void) { static V c; return STRC(c, "#define "); }
static V S1673(void) { static V c; return STRC(c, " "); }
static V S1674(void) { static V c; return STRC(c, "u\012"); }
static V S1675(void) { static V c; return STRC(c, "#define "); }
static V S1676(void) { static V c; return STRC(c, " ((1u << 16) | "); }
static V S1677(void) { static V c; return STRC(c, "u)\012"); }
static V S1678(void) { static V c; return STRC(c, "#define "); }
static V S1679(void) { static V c; return STRC(c, " ((2u << 16) | "); }
static V S1680(void) { static V c; return STRC(c, "u)\012"); }
static V S1681(void) { static V c; return STRC(c, ""); }
static V F_Gen_dcids_dline(V a0, V a1, V a2) {
top:;
V s1671 = a1;
if ((s1671) == 0) {
return F_String_dappend(S1672(), F_String_dappend(F_Gen_dcid(a0), F_String_dappend(S1673(), F_String_dappend(F_U32_dshow(a2), S1674()))));
} else if ((s1671) == 1) {
return F_String_dappend(S1675(), F_String_dappend(F_Gen_dcid(a0), F_String_dappend(S1676(), F_String_dappend(F_U32_dshow(a2), S1677()))));
} else if ((s1671) == 2) {
return F_String_dappend(S1678(), F_String_dappend(F_Gen_dcid(a0), F_String_dappend(S1679(), F_String_dappend(F_U32_dshow(a2), S1680()))));
} else {
return S1681();
}
}
static V W_Gen_dcids_dline(V *a) { (void)a; return F_Gen_dcids_dline(a[0], a[1], a[2]); }
static V S1684(void) { static V c; return STRC(c, "#include \042bendrt.h\042\012\012"); }
static V S1685(void) { static V c; return STRC(c, "\012"); }
static V S1686(void) { static V c; return STRC(c, "\012"); }
static V F_Gen_dprogram_dfin(V a0, V a1) {
top:;
V v1682 = a1;
V v1683 = FLD(v1682, 1);
return C4(0, F_String_dappend(a0, S1684()), F_Gen_ddedup(F_List_dreverse(FLD(v1683, 6)), IMM(0)), F_Doc_dflat(F_Doc_dlist(C2(1, FLD(v1683, 1), C2(1, C1(1, S1685()), C2(1, FLD(v1683, 2), C2(1, C1(1, F_String_dappend(S1686(), FLD(v1682, 0))), IMM(0))))))), FLD(v1683, 4));
}
static V W_Gen_dprogram_dfin(V *a) { (void)a; return F_Gen_dprogram_dfin(a[0], a[1]); }
static V F_Doc_dflat(V a0) {
top:;
return F_Doc_dgo(a0, IMM(0));
}
static V W_Doc_dflat(V *a) { (void)a; return F_Doc_dflat(a[0]); }
static V F_Doc_dgo(V a0, V a1) {
top:;
V s1687 = a0;
if ((s1687) == IMM(0)) {
return a1;
} else if (TAG(s1687) == 1) {
return F_String_dappend(FLD(s1687, 0), a1);
} else if (TAG(s1687) == 2) {
{ V t0 = FLD(s1687, 0); V t1 = F_Doc_dgo(FLD(s1687, 1), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dgo(V *a) { (void)a; return F_Doc_dgo(a[0], a[1]); }
static V F_Gen_ddedup(V a0, V a1) {
top:;
V s1688 = a0;
if ((s1688) == IMM(0)) {
return F_List_dreverse(a1);
} else if (TAG(s1688) == 1) {
{ V t0 = FLD(s1688, 1); V t1 = F_Bool_dpick(F_Str_dhas(a1, FLD(s1688, 0)), a1, C2(1, FLD(s1688, 0), a1)); a0 = t0; a1 = t1; goto top; }
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
V s1689 = a0;
if ((s1689) == IMM(0)) {
return a1;
} else if (TAG(s1689) == 1 && TAG(FLD(s1689, 0)) == 2) {
{ V t0 = FLD(s1689, 1); V t1 = F_Map_dset(a1, FLD(FLD(s1689, 0), 0), FLD(FLD(s1689, 0), 1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1689) == 1) {
{ V t0 = FLD(s1689, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_G_dlaws(V *a) { (void)a; return F_G_dlaws(a[0], a[1]); }
static V F_G_dbuild(V a0, V a1, V a2) {
top:;
V s1690 = a0;
if ((s1690) == IMM(0)) {
return a2;
} else if (TAG(s1690) == 1) {
{ V t0 = FLD(s1690, 1); V t1 = a1; V t2 = F_G_dadd(FLD(s1690, 0), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_G_dbuild(V *a) { (void)a; return F_G_dbuild(a[0], a[1], a[2]); }
static V F_G_dadd(V a0, V a1, V a2) {
top:;
V s1691 = a0;
if (TAG(s1691) == 3) {
return F_G_dadd_dtype(FLD(s1691, 0), FLD(s1691, 1), FLD(s1691, 2), a2);
} else if (TAG(s1691) == 2) {
return F_G_dadd_dlaw(FLD(s1691, 0), FLD(s1691, 1), a2);
} else if (TAG(s1691) == 0) {
return F_G_dadd_ddef(FLD(s1691, 0), FLD(s1691, 1), FLD(s1691, 2), FLD(s1691, 3), a1, a2);
} else if (TAG(s1691) == 1) {
return F_G_dadd_deff(FLD(s1691, 0), FLD(s1691, 1), FLD(s1691, 2), a2);
} else if (TAG(s1691) == 4) {
return a2;
} else { bend_fail("incomplete match"); }
}
static V W_G_dadd(V *a) { (void)a; return F_G_dadd(a[0], a[1], a[2]); }
static V F_G_dadd_deff(V a0, V a1, V a2, V a3) {
top:;
V v1692 = a3;
return C3(0, FLD(v1692, 0), F_Map_dset(FLD(v1692, 1), a0, C2(0, 1u, F_G_dmask(a1))), F_Map_dset(FLD(v1692, 2), a0, C3(1, a0, a1, a2)));
}
static V W_G_dadd_deff(V *a) { (void)a; return F_G_dadd_deff(a[0], a[1], a[2], a[3]); }
static V F_G_dmask(V a0) {
top:;
V s1693 = a0;
if ((s1693) == IMM(0)) {
return IMM(0);
} else if (TAG(s1693) == 1) {
return C2(1, F_G_dkeep(FLD(s1693, 0)), F_G_dmask(FLD(s1693, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_G_dmask(V *a) { (void)a; return F_G_dmask(a[0]); }
static V F_G_dkeep(V a0) {
top:;
V v1694 = a0;
return F_Bool_dnot(F_Bool_dor(F_Bool_dor(F_U32_dis__eq(FLD(v1694, 1), 1u), F_U32_dis__eq(FLD(v1694, 1), 4u)), F_G_derased__ty(FLD(v1694, 2))));
}
static V W_G_dkeep(V *a) { (void)a; return F_G_dkeep(a[0]); }
static V S1695(void) { static V c; return STRC(c, "Type"); }
static V S1696(void) { static V c; return STRC(c, "Data"); }
static V S1697(void) { static V c; return STRC(c, "Quant"); }
static V S1698(void) { static V c; return STRC(c, "Kind"); }
static V F_G_derased__ty(V a0) {
top:;
return F_Str_dhas(C2(1, S1695(), C2(1, S1696(), C2(1, S1697(), C2(1, S1698(), IMM(0))))), a0);
}
static V W_G_derased__ty(V *a) { (void)a; return F_G_derased__ty(a[0]); }
static V F_G_dadd_ddef(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v1699 = a5;
return C3(0, FLD(v1699, 0), F_Map_dset(FLD(v1699, 1), a0, C2(0, F_Bool_dpick(F_G_dis__native(a0), 2u, 0u), F_G_dmask(F_G_dparams(a4, a0, a1)))), F_Map_dset(FLD(v1699, 2), a0, C4(0, a0, a1, a2, a3)));
}
static V W_G_dadd_ddef(V *a) { (void)a; return F_G_dadd_ddef(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_G_dparams(V a0, V a1, V a2) {
top:;
return F_G_dparams_dgo(F_G_dget(IMM(0), a0, a1), a2);
}
static V W_G_dparams(V *a) { (void)a; return F_G_dparams(a[0], a[1], a[2]); }
static V F_G_dparams_dgo(V a0, V a1) {
top:;
V s1700 = a0;
if ((s1700) == IMM(0)) {
return a1;
} else if (TAG(s1700) == 1) {
return C2(1, FLD(s1700, 0), FLD(s1700, 1));
} else { bend_fail("incomplete match"); }
}
static V W_G_dparams_dgo(V *a) { (void)a; return F_G_dparams_dgo(a[0], a[1]); }
static V F_G_dis__native(V a0) {
top:;
return F_Str_dhas(F_Natives(), a0);
}
static V W_G_dis__native(V *a) { (void)a; return F_G_dis__native(a[0]); }
static V S1701(void) { static V c; return STRC(c, "U32.inc"); }
static V S1702(void) { static V c; return STRC(c, "U32.add"); }
static V S1703(void) { static V c; return STRC(c, "U32.sub"); }
static V S1704(void) { static V c; return STRC(c, "U32.mul"); }
static V S1705(void) { static V c; return STRC(c, "U32.div"); }
static V S1706(void) { static V c; return STRC(c, "U32.mod"); }
static V S1707(void) { static V c; return STRC(c, "U32.not"); }
static V S1708(void) { static V c; return STRC(c, "U32.and"); }
static V S1709(void) { static V c; return STRC(c, "U32.or"); }
static V S1710(void) { static V c; return STRC(c, "U32.xor"); }
static V S1711(void) { static V c; return STRC(c, "U32.shl"); }
static V S1712(void) { static V c; return STRC(c, "U32.shr"); }
static V S1713(void) { static V c; return STRC(c, "U32.shln"); }
static V S1714(void) { static V c; return STRC(c, "U32.shrn"); }
static V S1715(void) { static V c; return STRC(c, "U32.cmp"); }
static V S1716(void) { static V c; return STRC(c, "U32.is_eq"); }
static V S1717(void) { static V c; return STRC(c, "U32.is_ne"); }
static V S1718(void) { static V c; return STRC(c, "U32.is_lt"); }
static V S1719(void) { static V c; return STRC(c, "U32.is_le"); }
static V S1720(void) { static V c; return STRC(c, "U32.is_gt"); }
static V S1721(void) { static V c; return STRC(c, "U32.is_ge"); }
static V S1722(void) { static V c; return STRC(c, "U32.is_zero"); }
static V S1723(void) { static V c; return STRC(c, "U32.is_even"); }
static V S1724(void) { static V c; return STRC(c, "U32.to_nat"); }
static V S1725(void) { static V c; return STRC(c, "U32.from_nat"); }
static V S1726(void) { static V c; return STRC(c, "U32.min"); }
static V S1727(void) { static V c; return STRC(c, "U32.max"); }
static V S1728(void) { static V c; return STRC(c, "U32.pow"); }
static V S1729(void) { static V c; return STRC(c, "U32.log2"); }
static V S1730(void) { static V c; return STRC(c, "U32.to_f32"); }
static V S1731(void) { static V c; return STRC(c, "Nat.double"); }
static V S1732(void) { static V c; return STRC(c, "Nat.add"); }
static V S1733(void) { static V c; return STRC(c, "Nat.sub"); }
static V S1734(void) { static V c; return STRC(c, "Nat.mul"); }
static V S1735(void) { static V c; return STRC(c, "Nat.divmod"); }
static V S1736(void) { static V c; return STRC(c, "Nat.div"); }
static V S1737(void) { static V c; return STRC(c, "Nat.mod"); }
static V S1738(void) { static V c; return STRC(c, "Nat.cmp"); }
static V S1739(void) { static V c; return STRC(c, "Nat.is_eq"); }
static V S1740(void) { static V c; return STRC(c, "Nat.is_ne"); }
static V S1741(void) { static V c; return STRC(c, "Nat.is_lt"); }
static V S1742(void) { static V c; return STRC(c, "Nat.is_le"); }
static V S1743(void) { static V c; return STRC(c, "Nat.is_gt"); }
static V S1744(void) { static V c; return STRC(c, "Nat.is_ge"); }
static V S1745(void) { static V c; return STRC(c, "Nat.min"); }
static V S1746(void) { static V c; return STRC(c, "Nat.max"); }
static V S1747(void) { static V c; return STRC(c, "Nat.pow"); }
static V S1748(void) { static V c; return STRC(c, "Nat.show"); }
static V S1749(void) { static V c; return STRC(c, "F32.add"); }
static V S1750(void) { static V c; return STRC(c, "F32.sub"); }
static V S1751(void) { static V c; return STRC(c, "F32.mul"); }
static V S1752(void) { static V c; return STRC(c, "F32.div"); }
static V S1753(void) { static V c; return STRC(c, "F32.mod"); }
static V S1754(void) { static V c; return STRC(c, "F32.pow"); }
static V S1755(void) { static V c; return STRC(c, "F32.atan2"); }
static V S1756(void) { static V c; return STRC(c, "F32.is_eq"); }
static V S1757(void) { static V c; return STRC(c, "F32.is_ne"); }
static V S1758(void) { static V c; return STRC(c, "F32.is_lt"); }
static V S1759(void) { static V c; return STRC(c, "F32.is_le"); }
static V S1760(void) { static V c; return STRC(c, "F32.is_gt"); }
static V S1761(void) { static V c; return STRC(c, "F32.is_ge"); }
static V S1762(void) { static V c; return STRC(c, "F32.neg"); }
static V S1763(void) { static V c; return STRC(c, "F32.abs"); }
static V S1764(void) { static V c; return STRC(c, "F32.sqrt"); }
static V S1765(void) { static V c; return STRC(c, "F32.exp"); }
static V S1766(void) { static V c; return STRC(c, "F32.log"); }
static V S1767(void) { static V c; return STRC(c, "F32.log2"); }
static V S1768(void) { static V c; return STRC(c, "F32.log10"); }
static V S1769(void) { static V c; return STRC(c, "F32.sin"); }
static V S1770(void) { static V c; return STRC(c, "F32.cos"); }
static V S1771(void) { static V c; return STRC(c, "F32.tan"); }
static V S1772(void) { static V c; return STRC(c, "F32.asin"); }
static V S1773(void) { static V c; return STRC(c, "F32.acos"); }
static V S1774(void) { static V c; return STRC(c, "F32.atan"); }
static V S1775(void) { static V c; return STRC(c, "F32.sinh"); }
static V S1776(void) { static V c; return STRC(c, "F32.cosh"); }
static V S1777(void) { static V c; return STRC(c, "F32.tanh"); }
static V S1778(void) { static V c; return STRC(c, "F32.floor"); }
static V S1779(void) { static V c; return STRC(c, "F32.ceil"); }
static V S1780(void) { static V c; return STRC(c, "F32.trunc"); }
static V S1781(void) { static V c; return STRC(c, "F32.bits"); }
static V S1782(void) { static V c; return STRC(c, "F32.to_u32"); }
static V S1783(void) { static V c; return STRC(c, "F32.show"); }
static V S1784(void) { static V c; return STRC(c, "F32.read"); }
static V F_Natives(void) {
top:;
return C2(1, S1701(), C2(1, S1702(), C2(1, S1703(), C2(1, S1704(), C2(1, S1705(), C2(1, S1706(), C2(1, S1707(), C2(1, S1708(), C2(1, S1709(), C2(1, S1710(), C2(1, S1711(), C2(1, S1712(), C2(1, S1713(), C2(1, S1714(), C2(1, S1715(), C2(1, S1716(), C2(1, S1717(), C2(1, S1718(), C2(1, S1719(), C2(1, S1720(), C2(1, S1721(), C2(1, S1722(), C2(1, S1723(), C2(1, S1724(), C2(1, S1725(), C2(1, S1726(), C2(1, S1727(), C2(1, S1728(), C2(1, S1729(), C2(1, S1730(), C2(1, S1731(), C2(1, S1732(), C2(1, S1733(), C2(1, S1734(), C2(1, S1735(), C2(1, S1736(), C2(1, S1737(), C2(1, S1738(), C2(1, S1739(), C2(1, S1740(), C2(1, S1741(), C2(1, S1742(), C2(1, S1743(), C2(1, S1744(), C2(1, S1745(), C2(1, S1746(), C2(1, S1747(), C2(1, S1748(), C2(1, S1749(), C2(1, S1750(), C2(1, S1751(), C2(1, S1752(), C2(1, S1753(), C2(1, S1754(), C2(1, S1755(), C2(1, S1756(), C2(1, S1757(), C2(1, S1758(), C2(1, S1759(), C2(1, S1760(), C2(1, S1761(), C2(1, S1762(), C2(1, S1763(), C2(1, S1764(), C2(1, S1765(), C2(1, S1766(), C2(1, S1767(), C2(1, S1768(), C2(1, S1769(), C2(1, S1770(), C2(1, S1771(), C2(1, S1772(), C2(1, S1773(), C2(1, S1774(), C2(1, S1775(), C2(1, S1776(), C2(1, S1777(), C2(1, S1778(), C2(1, S1779(), C2(1, S1780(), C2(1, S1781(), C2(1, S1782(), C2(1, S1783(), C2(1, S1784(), IMM(0)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
}
static V W_Natives(V *a) { (void)a; return F_Natives(); }
static V F_G_dadd_dlaw(V a0, V a1, V a2) {
top:;
V v1785 = a2;
return C3(0, FLD(v1785, 0), F_Map_dset(FLD(v1785, 1), a0, C2(0, F_Bool_dpick(F_G_dis__native(a0), 2u, 3u), F_G_dmask(a1))), FLD(v1785, 2));
}
static V W_G_dadd_dlaw(V *a) { (void)a; return F_G_dadd_dlaw(a[0], a[1], a[2]); }
static V S1788(void) { static V c; return STRC(c, "%"); }
static V F_G_dadd_dtype(V a0, V a1, V a2, V a3) {
top:;
V v1786 = a3;
V v1787 = F_U32_dfrom__nat(F_List_dlength(a2));
return C3(0, F_G_dctors(a0, a2, 0u, v1787, FLD(v1786, 0)), F_Map_dset(FLD(v1786, 1), a0, C2(0, 3u, IMM(0))), F_Map_dset(FLD(v1786, 2), F_String_dappend(S1788(), a0), C3(3, a0, a1, a2)));
}
static V W_G_dadd_dtype(V *a) { (void)a; return F_G_dadd_dtype(a[0], a[1], a[2], a[3]); }
static V F_G_dctors(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1789 = a1;
if ((s1789) == IMM(0)) {
return a4;
} else if (TAG(s1789) == 1) {
V v1790 = F_U32_dfrom__nat(F_List_dlength(FLD(FLD(s1789, 0), 1)));
{ V t0 = a0; V t1 = FLD(s1789, 1); V t2 = F_U32_dinc(a2); V t3 = a3; V t4 = F_Map_dset(a4, FLD(FLD(s1789, 0), 0), C4(0, a2, v1790, F_G_dctor__kind(a0, FLD(FLD(s1789, 0), 0), a3, v1790), F_U32_dis__eq(a3, 1u))); a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_G_dctors(V *a) { (void)a; return F_G_dctors(a[0], a[1], a[2], a[3], a[4]); }
static V S1791(void) { static V c; return STRC(c, "Nat"); }
static V S1792(void) { static V c; return STRC(c, "Zero"); }
static V F_G_dctor__kind(V a0, V a1, V a2, V a3) {
top:;
return F_Bool_dpick(F_Str_deq(a0, S1791()), F_Bool_dpick(F_Str_deq(a1, S1792()), 3u, 4u), F_Bool_dpick(F_Bool_dand(F_U32_dis__eq(a2, 1u), F_U32_dis__eq(a3, 1u)), 2u, F_Bool_dpick(F_U32_dis__zero(a3), 1u, 0u)));
}
static V W_G_dctor__kind(V *a) { (void)a; return F_G_dctor__kind(a[0], a[1], a[2], a[3]); }
static V S1795(void) { static V c; return STRC(c, "\012"); }
static V S1797(void) { static V c; return STRC(c, "bendc: compilation failed"); }
static V L1796(V *a) {
return F_IO_ddie(1u, S1797());
}
static V F_Main_demit(V a0) {
top:;
V v1793 = a0;
V s1794 = FLD(v1793, 3);
if ((s1794) == IMM(0)) {
return F_Main_demit_dok(FLD(v1793, 0), FLD(v1793, 1), FLD(v1793, 2));
} else if (TAG(s1794) == 1) {
return F_IO_dbind(F_IO_dprint__err(F_String_djoin(F_List_dreverse(C2(1, FLD(s1794, 0), FLD(s1794, 1))), S1795())), mk_clo(L1796, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Main_demit(V *a) { (void)a; return F_Main_demit(a[0]); }
static V E_IO_dprint__err(V *a) { return io_req(CID_IO_PRINT_ERR, 2, (V[]){a[0], a[2]}); }
static V F_IO_dprint__err(V a0) { return mk_clo(E_IO_dprint__err, 3, 1, (V[]){a0}); }
static V W_IO_dprint__err(V *a) { (void)a; return F_IO_dprint__err(a[0]); }
static V L1800(V *a) {
return apply(apply(apply(a[2], a[3]), a[1]), a[0]);
}
static V L1799(V *a) {
return apply(apply(a[2], a[1]), mk_clo(L1800, 4, 3, (V[]){a[3], a[1], a[0]}));
}
static V L1798(V *a) {
return mk_clo(L1799, 4, 3, (V[]){a[0], a[2], a[1]});
}
static V F_IO_dbind(V a2, V a3) {
top:;
return mk_clo(L1798, 3, 2, (V[]){a3, a2});
}
static V W_IO_dbind(V *a) { (void)a; return F_IO_dbind(a[2], a[3]); }
static V S1801(void) { static V c; return STRC(c, ""); }
static V L1802(V *a) {
return F_IO_dwrite(F_String_dappend(a[1], F_String_dappend(a[2], a[0])));
}
static V F_Main_demit_dok(V a0, V a1, V a2) {
top:;
return F_IO_dbind(F_Main_deffs(a1, S1801()), mk_clo(L1802, 3, 2, (V[]){a2, a0}));
}
static V W_Main_demit_dok(V *a) { (void)a; return F_Main_demit_dok(a[0], a[1], a[2]); }
static V E_IO_dwrite(V *a) { return io_req(CID_IO_WRITE, 2, (V[]){a[0], a[2]}); }
static V F_IO_dwrite(V a0) { return mk_clo(E_IO_dwrite, 3, 1, (V[]){a0}); }
static V W_IO_dwrite(V *a) { (void)a; return F_IO_dwrite(a[0]); }
static V S1805(void) { static V c; return STRC(c, "\012"); }
static V L1804(V *a) {
return F_Main_deffs(a[1], F_String_dappend(a[0], F_String_dappend(a[2], S1805())));
}
static V F_Main_deffs(V a0, V a1) {
top:;
V s1803 = a0;
if ((s1803) == IMM(0)) {
return F_IO_dpure(a1);
} else if (TAG(s1803) == 1) {
return F_IO_dbind(F_IO_dread__file(FLD(s1803, 0)), mk_clo(L1804, 3, 2, (V[]){a1, FLD(s1803, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_deffs(V *a) { (void)a; return F_Main_deffs(a[0], a[1]); }
static V S1806(void) { static V c; return STRC(c, "r"); }
static V L1808(V *a) {
return F_IO_dread__fin(a[0]);
}
static V L1807(V *a) {
return F_IO_dbind(F_IO_dread__all(a[0]), mk_clo(L1808, 1, 0, 0));
}
static V F_IO_dread__file(V a0) {
top:;
return F_IO_dbind(F_IO_dtry(F_File_dopen(a0, S1806())), mk_clo(L1807, 1, 0, 0));
}
static V W_IO_dread__file(V *a) { (void)a; return F_IO_dread__file(a[0]); }
static V L1810(V *a) {
return F_IO_dpass(a[0]);
}
static V F_IO_dread__fin(V a0) {
top:;
V v1809 = a0;
return F_IO_dbind(F_File_dclose(FLD(v1809, 0)), mk_clo(L1810, 2, 1, (V[]){FLD(v1809, 1)}));
}
static V W_IO_dread__fin(V *a) { (void)a; return F_IO_dread__fin(a[0]); }
static V F_IO_dpass(V a1) {
top:;
V s1811 = a1;
if (TAG(s1811) == 1) {
return F_IO_dpure(FLD(s1811, 0));
} else if (TAG(s1811) == 0) {
return F_IO_ddie(FLD(FLD(s1811, 0), 0), FLD(FLD(s1811, 0), 1));
} else { bend_fail("incomplete match"); }
}
static V W_IO_dpass(V *a) { (void)a; return F_IO_dpass(a[1]); }
static V L1813(V *a) {
return apply(a[1], a[0]);
}
static V L1812(V *a) {
return mk_clo(L1813, 2, 1, (V[]){a[0]});
}
static V F_IO_dpure(V a1) {
top:;
return mk_clo(L1812, 2, 1, (V[]){a1});
}
static V W_IO_dpure(V *a) { (void)a; return F_IO_dpure(a[1]); }
static V E_File_dclose(V *a) { return io_req(CID_FILE_CLOSE, 2, (V[]){a[0], a[2]}); }
static V F_File_dclose(V a0) { return mk_clo(E_File_dclose, 3, 1, (V[]){a0}); }
static V W_File_dclose(V *a) { (void)a; return F_File_dclose(a[0]); }
static V L1814(V *a) {
return F_IO_dread__sized(a[0]);
}
static V F_IO_dread__all(V a0) {
top:;
return F_IO_dbind(F_File_dsize(a0), mk_clo(L1814, 1, 0, 0));
}
static V W_IO_dread__all(V *a) { (void)a; return F_IO_dread__all(a[0]); }
static V F_IO_dread__sized(V a0) {
top:;
V v1815 = a0;
V s1816 = FLD(v1815, 1);
if (TAG(s1816) == 1) {
return F_File_dread(FLD(v1815, 0), F_U32_dinc(FLD(s1816, 0)));
} else if (TAG(s1816) == 0) {
return F_File_dread(FLD(v1815, 0), 2000000000u);
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
static V S1818(void) { static V c; return STRC(c, "bendc: imports nested too deeply at "); }
static V L1819(V *a) {
return F_Main_dload_dparsed(a[1], F_Mod_ddir(a[0]), a[0], F_Main_dparse(a[2]));
}
static V F_Main_dload(V a0, V a1) {
top:;
V s1817 = a0;
if ((s1817) == 0) {
return F_IO_ddie(1u, F_String_dappend(S1818(), a1));
} else if (nat_ge(s1817, 1)) {
return F_IO_dbind(F_IO_dread__file(a1), mk_clo(L1819, 3, 2, (V[]){a1, nat_subk(s1817, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dload(V *a) { (void)a; return F_Main_dload(a[0], a[1]); }
static V S1821(void) { static V c; return STRC(c, "bendc: parse error in "); }
static V S1822(void) { static V c; return STRC(c, ": "); }
static V L1823(V *a) {
return F_IO_dpure(F_List_dappend(a[2], F_Eff_ddecls(a[1], a[0])));
}
static V F_Main_dload_dparsed(V a0, V a1, V a2, V a3) {
top:;
V s1820 = a3;
if (TAG(s1820) == 0) {
return F_IO_ddie(1u, F_String_dappend(S1821(), F_String_dappend(a2, F_String_dappend(S1822(), FLD(s1820, 0)))));
} else if (TAG(s1820) == 1) {
return F_IO_dbind(F_Main_dimports(a0, a1, FLD(s1820, 0)), mk_clo(L1823, 3, 2, (V[]){FLD(s1820, 0), a1}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dload_dparsed(V *a) { (void)a; return F_Main_dload_dparsed(a[0], a[1], a[2], a[3]); }
static V S1825(void) { static V c; return STRC(c, "Base"); }
static V F_Main_dimports(V a0, V a1, V a2) {
top:;
V s1824 = a2;
if ((s1824) == IMM(0)) {
return F_IO_dpure(IMM(0));
} else if (TAG(s1824) == 1 && TAG(FLD(s1824, 0)) == 4) {
return F_Main_dimports_done(a0, a1, FLD(FLD(s1824, 0), 0), FLD(FLD(s1824, 0), 1), FLD(s1824, 1), F_Str_deq(FLD(FLD(s1824, 0), 0), S1825()));
} else if (TAG(s1824) == 1) {
{ V t0 = a0; V t1 = a1; V t2 = FLD(s1824, 1); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Main_dimports(V *a) { (void)a; return F_Main_dimports(a[0], a[1], a[2]); }
static V S1827(void) { static V c; return STRC(c, "0x"); }
static V L1829(V *a) {
return F_IO_dpure(F_List_dappend(F_Mod_dqualify(a[1], a[0]), a[2]));
}
static V L1828(V *a) {
return F_IO_dbind(F_Main_dimports(a[3], a[2], a[1]), mk_clo(L1829, 3, 2, (V[]){a[4], a[0]}));
}
static V F_Main_dimports_done(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1826 = a5;
if ((s1826) == IMM(1)) {
return F_Main_dimports(a0, a1, a4);
} else if ((s1826) == IMM(0)) {
return F_IO_dbind(F_Main_dload_dimport(a0, a1, a2, F_String_dstarts__with(a2, S1827())), mk_clo(L1828, 5, 4, (V[]){a3, a4, a1, a0}));
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
V s1830 = a0;
if ((s1830) == IMM(0)) {
return a1;
} else if (TAG(s1830) == 1 && TAG(FLD(s1830, 0)) == 0) {
{ V t0 = FLD(s1830, 1); V t1 = C2(1, FLD(FLD(s1830, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1830) == 1 && TAG(FLD(s1830, 0)) == 1) {
{ V t0 = FLD(s1830, 1); V t1 = C2(1, FLD(FLD(s1830, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1830) == 1 && TAG(FLD(s1830, 0)) == 2) {
{ V t0 = FLD(s1830, 1); V t1 = C2(1, FLD(FLD(s1830, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1830) == 1 && TAG(FLD(s1830, 0)) == 3) {
{ V t0 = FLD(s1830, 1); V t1 = C2(1, FLD(FLD(s1830, 0), 0), F_Mod_dctor__names(FLD(FLD(s1830, 0), 2), a1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1830) == 1 && TAG(FLD(s1830, 0)) == 4) {
{ V t0 = FLD(s1830, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dnames(V *a) { (void)a; return F_Mod_dnames(a[0], a[1]); }
static V F_Mod_dctor__names(V a0, V a1) {
top:;
V s1831 = a0;
if ((s1831) == IMM(0)) {
return a1;
} else if (TAG(s1831) == 1) {
{ V t0 = FLD(s1831, 1); V t1 = C2(1, FLD(FLD(s1831, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dctor__names(V *a) { (void)a; return F_Mod_dctor__names(a[0], a[1]); }
static V F_Mod_ddecls(V a0, V a1) {
top:;
V s1832 = a1;
if ((s1832) == IMM(0)) {
return IMM(0);
} else if (TAG(s1832) == 1) {
return C2(1, F_Mod_ddecl(a0, FLD(s1832, 0)), F_Mod_ddecls(a0, FLD(s1832, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddecls(V *a) { (void)a; return F_Mod_ddecls(a[0], a[1]); }
static V F_Mod_ddecl(V a0, V a1) {
top:;
V s1833 = a1;
if (TAG(s1833) == 0) {
return C4(0, F_Mod_dq(a0, FLD(s1833, 0)), FLD(s1833, 1), F_Mod_dexpr(a0, F_Mod_dparam__names(FLD(s1833, 1)), FLD(s1833, 2)), F_Mod_dexpr(a0, IMM(0), FLD(s1833, 3)));
} else if (TAG(s1833) == 1) {
return C3(1, F_Mod_dq(a0, FLD(s1833, 0)), FLD(s1833, 1), FLD(s1833, 2));
} else if (TAG(s1833) == 2) {
return C2(2, F_Mod_dq(a0, FLD(s1833, 0)), FLD(s1833, 1));
} else if (TAG(s1833) == 3) {
return C3(3, F_Mod_dq(a0, FLD(s1833, 0)), FLD(s1833, 1), F_Mod_dctors(a0, FLD(s1833, 2)));
} else if (TAG(s1833) == 4) {
return C2(4, FLD(s1833, 0), FLD(s1833, 1));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddecl(V *a) { (void)a; return F_Mod_ddecl(a[0], a[1]); }
static V F_Mod_dctors(V a0, V a1) {
top:;
V s1834 = a1;
if ((s1834) == IMM(0)) {
return IMM(0);
} else if (TAG(s1834) == 1) {
return C2(1, C2(0, F_Mod_dq(a0, FLD(FLD(s1834, 0), 0)), F_Mod_dfields(a0, FLD(FLD(s1834, 0), 1))), F_Mod_dctors(a0, FLD(s1834, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dctors(V *a) { (void)a; return F_Mod_dctors(a[0], a[1]); }
static V F_Mod_dfields(V a0, V a1) {
top:;
V s1835 = a1;
if ((s1835) == IMM(0)) {
return IMM(0);
} else if (TAG(s1835) == 1) {
return C2(1, C2(0, FLD(FLD(s1835, 0), 0), F_Mod_dexpr(a0, IMM(0), FLD(FLD(s1835, 0), 1))), F_Mod_dfields(a0, FLD(s1835, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dfields(V *a) { (void)a; return F_Mod_dfields(a[0], a[1]); }
static V F_Mod_dexpr(V a0, V a1, V a2) {
top:;
V s1836 = a2;
if (TAG(s1836) == 0) {
return C1(0, F_Mod_dvar(a0, a1, FLD(s1836, 0)));
} else if (TAG(s1836) == 5) {
return C2(5, F_Mod_dexpr(a0, a1, FLD(s1836, 0)), F_Mod_dexprs(a0, a1, FLD(s1836, 1)));
} else if (TAG(s1836) == 6) {
return C2(6, F_Mod_dq(a0, FLD(s1836, 0)), F_Mod_dexprs(a0, a1, FLD(s1836, 1)));
} else if (TAG(s1836) == 7) {
return C2(7, F_Mod_dpat(a0, FLD(s1836, 0)), F_Mod_dexpr(a0, F_Pat_dvars(FLD(s1836, 0), a1), FLD(s1836, 1)));
} else if (TAG(s1836) == 8) {
return C3(8, F_Mod_dpat(a0, FLD(s1836, 0)), F_Mod_dexpr(a0, a1, FLD(s1836, 1)), F_Mod_dexpr(a0, F_Pat_dvars(FLD(s1836, 0), a1), FLD(s1836, 2)));
} else if (TAG(s1836) == 9) {
return C2(9, F_Mod_dexprs(a0, a1, FLD(s1836, 0)), F_Mod_dexprs(a0, a1, FLD(s1836, 1)));
} else if (TAG(s1836) == 10) {
return C2(10, F_Mod_dpats(a0, FLD(s1836, 0)), F_Mod_dexpr(a0, F_Pats_dvars(FLD(s1836, 0), a1), FLD(s1836, 1)));
} else if (TAG(s1836) == 11) {
return C2(11, FLD(s1836, 0), F_Mod_dexpr(a0, a1, FLD(s1836, 1)));
} else if (TAG(s1836) == 12) {
return C3(12, FLD(s1836, 0), F_Mod_dexpr(a0, a1, FLD(s1836, 1)), F_Mod_dexpr(a0, a1, FLD(s1836, 2)));
} else if (TAG(s1836) == 13) {
return C2(13, F_Mod_dexpr(a0, a1, FLD(s1836, 0)), F_Mod_dvar(a0, a1, FLD(s1836, 1)));
} else if (TAG(s1836) == 14) {
return C2(14, F_Mod_dvar(a0, a1, FLD(s1836, 0)), F_Mod_dexprs(a0, a1, FLD(s1836, 1)));
} else {
return s1836;
}
}
static V W_Mod_dexpr(V *a) { (void)a; return F_Mod_dexpr(a[0], a[1], a[2]); }
static V F_Mod_dexprs(V a0, V a1, V a2) {
top:;
V s1837 = a2;
if ((s1837) == IMM(0)) {
return IMM(0);
} else if (TAG(s1837) == 1) {
return C2(1, F_Mod_dexpr(a0, a1, FLD(s1837, 0)), F_Mod_dexprs(a0, a1, FLD(s1837, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dexprs(V *a) { (void)a; return F_Mod_dexprs(a[0], a[1], a[2]); }
static V F_Mod_dvar(V a0, V a1, V a2) {
top:;
return F_Bool_dpick(F_Str_dhas(a1, a2), a2, F_Mod_dq(a0, a2));
}
static V W_Mod_dvar(V *a) { (void)a; return F_Mod_dvar(a[0], a[1], a[2]); }
static V S1839(void) { static V c; return STRC(c, "."); }
static V F_Mod_dq(V a0, V a1) {
top:;
V v1838 = a0;
return F_Bool_dpick(F_Str_dhas(FLD(v1838, 1), a1), F_String_dappend(FLD(v1838, 0), F_String_dappend(S1839(), a1)), a1);
}
static V W_Mod_dq(V *a) { (void)a; return F_Mod_dq(a[0], a[1]); }
static V F_Mod_dpats(V a0, V a1) {
top:;
V s1840 = a1;
if ((s1840) == IMM(0)) {
return IMM(0);
} else if (TAG(s1840) == 1) {
return C2(1, F_Mod_dpat(a0, FLD(s1840, 0)), F_Mod_dpats(a0, FLD(s1840, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dpats(V *a) { (void)a; return F_Mod_dpats(a[0], a[1]); }
static V F_Mod_dpat(V a0, V a1) {
top:;
V s1841 = a1;
if (TAG(s1841) == 1) {
return C2(1, F_Mod_dq(a0, FLD(s1841, 0)), F_Mod_dpats(a0, FLD(s1841, 1)));
} else if (TAG(s1841) == 3) {
return C2(3, FLD(s1841, 0), F_Mod_dpat(a0, FLD(s1841, 1)));
} else {
return s1841;
}
}
static V W_Mod_dpat(V *a) { (void)a; return F_Mod_dpat(a[0], a[1]); }
static V F_Mod_dparam__names(V a0) {
top:;
V s1842 = a0;
if ((s1842) == IMM(0)) {
return IMM(0);
} else if (TAG(s1842) == 1) {
return C2(1, FLD(FLD(s1842, 0), 0), F_Mod_dparam__names(FLD(s1842, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dparam__names(V *a) { (void)a; return F_Mod_dparam__names(a[0]); }
static V F_Main_dload_dimport(V a0, V a1, V a2, V a3) {
top:;
V s1843 = a3;
if ((s1843) == IMM(1)) {
return F_Main_dload_dhub(a0, a2);
} else if ((s1843) == IMM(0)) {
return F_Main_dload(a0, F_Eff_dpath(a1, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dload_dimport(V *a) { (void)a; return F_Main_dload_dimport(a[0], a[1], a[2], a[3]); }
static V S1845(void) { static V c; return STRC(c, "BEND_HUB"); }
static V S1848(void) { static V c; return STRC(c, "/"); }
static V L1847(V *a) {
return F_Main_dload(a[2], F_String_dappend(a[1], F_String_dappend(S1848(), a[0])));
}
static V L1846(V *a) {
return F_IO_dbind(F_IO_dtry(F_Hub_densure(a[2], F_Main_dhub_durl(a[3]), a[1])), mk_clo(L1847, 4, 3, (V[]){a[1], a[2], a[0]}));
}
static V L1844(V *a) {
return F_IO_dbind(F_IO_dget__env(S1845()), mk_clo(L1846, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Main_dload_dhub(V a0, V a1) {
top:;
return F_IO_dbind(F_Main_dlib(), mk_clo(L1844, 3, 2, (V[]){a0, a1}));
}
static V W_Main_dload_dhub(V *a) { (void)a; return F_Main_dload_dhub(a[0], a[1]); }
static V S1850(void) { static V c; return STRC(c, "https://hub.bend-lang.com"); }
static V F_Main_dhub_durl(V a0) {
top:;
V s1849 = a0;
if (TAG(s1849) == 1) {
return FLD(s1849, 0);
} else if (TAG(s1849) == 0) {
return S1850();
} else { bend_fail("incomplete match"); }
}
static V W_Main_dhub_durl(V *a) { (void)a; return F_Main_dhub_durl(a[0]); }
static V E_Hub_densure(V *a) { return io_req(CID_HUB_ENSURE, 4, (V[]){a[0], a[1], a[2], a[4]}); }
static V F_Hub_densure(V a0, V a1, V a2) { return mk_clo(E_Hub_densure, 5, 3, (V[]){a0, a1, a2}); }
static V W_Hub_densure(V *a) { (void)a; return F_Hub_densure(a[0], a[1], a[2]); }
static V E_IO_dget__env(V *a) { return io_req(CID_IO_GET_ENV, 2, (V[]){a[0], a[2]}); }
static V F_IO_dget__env(V a0) { return mk_clo(E_IO_dget__env, 3, 1, (V[]){a0}); }
static V W_IO_dget__env(V *a) { (void)a; return F_IO_dget__env(a[0]); }
static V S1851(void) { static V c; return STRC(c, "BEND_LIB"); }
static V L1852(V *a) {
return F_Main_dlib_dor(a[0]);
}
static V F_Main_dlib(void) {
top:;
return F_IO_dbind(F_IO_dget__env(S1851()), mk_clo(L1852, 1, 0, 0));
}
static V W_Main_dlib(V *a) { (void)a; return F_Main_dlib(); }
static V S1854(void) { static V c; return STRC(c, "HOME"); }
static V S1856(void) { static V c; return STRC(c, "/.bend/lib"); }
static V L1855(V *a) {
return F_IO_dpure(F_String_dappend(a[0], S1856()));
}
static V F_Main_dlib_dor(V a0) {
top:;
V s1853 = a0;
if (TAG(s1853) == 1) {
return F_IO_dpure(FLD(s1853, 0));
} else if (TAG(s1853) == 0) {
return F_IO_dbind(F_IO_dtry(F_IO_dget__env(S1854())), mk_clo(L1855, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dlib_dor(V *a) { (void)a; return F_Main_dlib_dor(a[0]); }
static V F_Chk_dshow__main(V a0) {
top:;
return F_Chk_dshow__main_dgo(a0, F_Chk_dmain__tld(a0));
}
static V W_Chk_dshow__main(V *a) { (void)a; return F_Chk_dshow__main(a[0]); }
static V S1858(void) { static V c; return STRC(c, ""); }
static V F_Chk_dshow__main_dgo(V a0, V a1) {
top:;
V s1857 = a1;
if (TAG(s1857) == 1 && TAG(FLD(s1857, 0)) == 0 && TAG(FLD(FLD(s1857, 0), 3)) == 1) {
return F_Chk_dterm__show(F_Chk_dterm__lower(a0, F_Chk_dterm__snf(a0, FLD(FLD(FLD(s1857, 0), 3), 0)), 0u), 0u, IMM(0));
} else {
return S1858();
}
}
static V W_Chk_dshow__main_dgo(V *a) { (void)a; return F_Chk_dshow__main_dgo(a[0], a[1]); }
static V F_Chk_dterm__show(V a0, V a1, V a2) {
top:;
return F_Chk_dterm__show_dgo(a0, a1, a2, F_List_dlength(a2));
}
static V W_Chk_dterm__show(V *a) { (void)a; return F_Chk_dterm__show(a[0], a[1], a[2]); }
static V S1860(void) { static V c; return STRC(c, "^"); }
static V S1861(void) { static V c; return STRC(c, "^"); }
static V S1862(void) { static V c; return STRC(c, "!"); }
static V S1863(void) { static V c; return STRC(c, ""); }
static V S1867(void) { static V c; return STRC(c, " "); }
static V S1868(void) { static V c; return STRC(c, " = "); }
static V S1869(void) { static V c; return STRC(c, " "); }
static V S1870(void) { static V c; return STRC(c, "; "); }
static V S1871(void) { static V c; return STRC(c, "Quant"); }
static V S1872(void) { static V c; return STRC(c, " <&> "); }
static V S1873(void) { static V c; return STRC(c, "@"); }
static V S1874(void) { static V c; return STRC(c, ":"); }
static V S1875(void) { static V c; return STRC(c, " -> "); }
static V S1876(void) { static V c; return STRC(c, " => "); }
static V S1879(void) { static V c; return STRC(c, ""); }
static V S1880(void) { static V c; return STRC(c, "<"); }
static V S1881(void) { static V c; return STRC(c, ", "); }
static V S1882(void) { static V c; return STRC(c, ">"); }
static V S1883(void) { static V c; return STRC(c, "n"); }
static V S1884(void) { static V c; return STRC(c, "\042"); }
static V S1885(void) { static V c; return STRC(c, "\042"); }
static V S1886(void) { static V c; return STRC(c, "\134{"); }
static V S1887(void) { static V c; return STRC(c, "; "); }
static V S1888(void) { static V c; return STRC(c, "}"); }
static V S1889(void) { static V c; return STRC(c, "\134{}"); }
static V S1890(void) { static V c; return STRC(c, "{"); }
static V S1891(void) { static V c; return STRC(c, " == "); }
static V S1892(void) { static V c; return STRC(c, " : "); }
static V S1893(void) { static V c; return STRC(c, "}"); }
static V S1894(void) { static V c; return STRC(c, "{==}"); }
static V S1895(void) { static V c; return STRC(c, "\077"); }
static V S1896(void) { static V c; return STRC(c, "{"); }
static V S1897(void) { static V c; return STRC(c, " : "); }
static V S1898(void) { static V c; return STRC(c, "}"); }
static V S1899(void) { static V c; return STRC(c, "\077"); }
static V F_Chk_dterm__show_dgo(V a0, V a1, V a2, V a3) {
top:;
V s1859 = a0;
if (TAG(s1859) == 0) {
return F_Bool_dpick(F_Chk_dshow_dbound__at(a2, a3, FLD(s1859, 0), FLD(s1859, 1)), FLD(s1859, 0), F_String_dappend(FLD(s1859, 0), F_String_dappend(S1860(), F_U32_dshow(FLD(s1859, 1)))));
} else if (TAG(s1859) == 4) {
return F_String_dappend(F_Bool_dpick(F_Chk_dStr_dhas(a2, FLD(s1859, 0)), F_String_dappend(FLD(s1859, 0), S1861()), FLD(s1859, 0)), F_Bool_dpick(FLD(s1859, 2), S1862(), S1863()));
} else if (TAG(s1859) == 5) {
{ V t0 = FLD(s1859, 2); V t1 = a1; V t2 = a2; V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1859) == 6) {
V v1864 = F_Chk_dshow_dargs(a2, a3, FLD(s1859, 2), 2u);
V v1865 = F_List_dlength(FLD(s1859, 0));
V v1866 = F_Chk_dterm__show_dgo(F_Chk_dsyn__body(FLD(s1859, 3)), 0u, F_List_dappend(F_List_dreverse(FLD(s1859, 0)), a2), F_Nat_dadd(a3, v1865));
return F_Chk_dshow_dparen(F_U32_dis__ge(a1, 1u), F_String_dappend(F_Chk_dshow_djoin(F_Chk_dshow_dlet__ks(FLD(s1859, 0), FLD(s1859, 5)), S1867()), F_String_dappend(S1868(), F_String_dappend(F_Chk_dshow_djoin(v1864, S1869()), F_String_dappend(S1870(), v1866)))));
} else if (TAG(s1859) == 7) {
return F_Chk_dshow_dtyp(FLD(s1859, 0), a2, a3);
} else if (TAG(s1859) == 8) {
return S1871();
} else if (TAG(s1859) == 9) {
return F_Chk_dshow_dqua(FLD(s1859, 0));
} else if (TAG(s1859) == 10) {
return F_Chk_dshow_dparen(F_U32_dis__gt(a1, 2u), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1859, 0), 3u, a2, a3), F_String_dappend(S1872(), F_Chk_dterm__show_dgo(FLD(s1859, 1), 3u, a2, a3))));
} else if (TAG(s1859) == 11) {
return F_Chk_dshow_dparen(F_U32_dis__gt(a1, 2u), F_String_dappend(S1873(), F_String_dappend(F_Chk_dquant__show(FLD(s1859, 0)), F_String_dappend(FLD(s1859, 1), F_String_dappend(S1874(), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1859, 3), 3u, a2, a3), F_String_dappend(S1875(), F_Chk_dterm__show_dgo(F_Chk_dsyn__body(FLD(s1859, 4)), 2u, C2(1, FLD(s1859, 1), a2), nat_addk(a3, 1)))))))));
} else if (TAG(s1859) == 12) {
return F_Chk_dshow_dparen(F_U32_dis__gt(a1, 1u), F_String_dappend(F_Chk_dquant__show(F_Chk_dQ_ddef(FLD(s1859, 4))), F_String_dappend(FLD(s1859, 0), F_String_dappend(S1876(), F_Chk_dterm__show_dgo(F_Chk_dsyn__body(FLD(s1859, 2)), 0u, C2(1, FLD(s1859, 0), a2), nat_addk(a3, 1))))));
} else if (TAG(s1859) == 13) {
return F_Chk_dshow_dapp(C3(13, FLD(s1859, 0), FLD(s1859, 1), FLD(s1859, 2)), a1, a2, a3);
} else if (TAG(s1859) == 14) {
V v1877 = F_Chk_dshow_drems(FLD(s1859, 3));
V v1878 = F_Chk_dshow_dargs(a2, a3, FLD(s1859, 1), 1u);
return F_Chk_dshow_dparen(F_Bool_dand(F_Bool_dnot(F_String_dis__empty(v1877)), F_U32_dis__gt(a1, 2u)), F_String_dappend(FLD(s1859, 0), F_String_dappend(F_Bool_dpick(F_Bool_dand(F_Chk_dLst_dempty(v1878), F_String_dis__empty(v1877)), S1879(), F_String_dappend(S1880(), F_String_dappend(F_Chk_dshow_djoin(v1878, S1881()), S1882()))), v1877)));
} else if (TAG(s1859) == 15) {
return F_Chk_dshow_dctr(C3(15, FLD(s1859, 0), FLD(s1859, 1), FLD(s1859, 2)), a1, a2, a3);
} else if (TAG(s1859) == 16 && TAG(FLD(s1859, 0)) == 0) {
return F_String_dappend(F_Nat_dshow(FLD(FLD(s1859, 0), 0)), S1883());
} else if (TAG(s1859) == 16 && TAG(FLD(s1859, 0)) == 1) {
return F_String_dappend(S1884(), F_String_dappend(F_Chk_dshow_dtext(FLD(FLD(s1859, 0), 0)), S1885()));
} else if (TAG(s1859) == 17) {
return F_String_dappend(S1886(), F_String_dappend(F_Chk_dshow_djoin(F_Chk_dshow_darms(C4(17, FLD(s1859, 0), FLD(s1859, 1), FLD(s1859, 2), FLD(s1859, 3)), a2, a3), S1887()), S1888()));
} else if (TAG(s1859) == 18) {
return S1889();
} else if (TAG(s1859) == 19) {
return F_String_dappend(S1890(), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1859, 0), 2u, a2, a3), F_String_dappend(S1891(), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1859, 1), 2u, a2, a3), F_String_dappend(S1892(), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1859, 2), 2u, a2, a3), S1893()))))));
} else if (TAG(s1859) == 20) {
return S1894();
} else if (TAG(s1859) == 22) {
return F_String_dappend(S1895(), FLD(s1859, 0));
} else if (TAG(s1859) == 21) {
return F_Chk_dshow_dparen(F_U32_dis__gt(a1, 1u), F_Chk_dshow_drwt(FLD(s1859, 0), FLD(s1859, 1), FLD(s1859, 2), a2, a3));
} else if (TAG(s1859) == 23) {
return F_String_dappend(S1896(), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1859, 0), 2u, a2, a3), F_String_dappend(S1897(), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s1859, 1), 2u, a2, a3), S1898()))));
} else if (TAG(s1859) == 1) {
{ V t0 = FLD(s1859, 2); V t1 = a1; V t2 = a2; V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1859) == 3) {
{ V t0 = FLD(s1859, 3); V t1 = a1; V t2 = a2; V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1859) == 2) {
return FLD(s1859, 0);
} else {
return S1899();
}
}
static V W_Chk_dterm__show_dgo(V *a) { (void)a; return F_Chk_dterm__show_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dshow_drwt(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Chk_dshow_drwt_dgo(F_Chk_dterm__show_dgo(a0, 2u, a3, a4), F_Chk_dterm__strip(a1), a2, a3, a4);
}
static V W_Chk_dshow_drwt(V *a) { (void)a; return F_Chk_dshow_drwt(a[0], a[1], a[2], a[3], a[4]); }
static V S1901(void) { static V c; return STRC(c, "%"); }
static V S1902(void) { static V c; return STRC(c, " : "); }
static V S1903(void) { static V c; return STRC(c, "; "); }
static V F_Chk_dshow_drwt_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1900 = a1;
if (TAG(s1900) == 12) {
return F_Chk_dshow_drwt_dinner(a0, CN(12, 5, (V[]){FLD(s1900, 0), FLD(s1900, 1), FLD(s1900, 2), FLD(s1900, 3), FLD(s1900, 4)}), FLD(s1900, 0), F_Chk_dterm__strip(F_Chk_dsyn__body(FLD(s1900, 2))), a2, a3, a4);
} else {
return F_String_dappend(S1901(), F_String_dappend(a0, F_String_dappend(S1902(), F_String_dappend(F_Chk_dterm__show_dgo(s1900, 2u, a3, a4), F_String_dappend(S1903(), F_Chk_dterm__show_dgo(a2, 0u, a3, a4))))));
}
}
static V W_Chk_dshow_drwt_dgo(V *a) { (void)a; return F_Chk_dshow_drwt_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V S1905(void) { static V c; return STRC(c, "%"); }
static V S1906(void) { static V c; return STRC(c, ""); }
static V S1907(void) { static V c; return STRC(c, "@"); }
static V S1908(void) { static V c; return STRC(c, " : "); }
static V S1909(void) { static V c; return STRC(c, "; "); }
static V S1910(void) { static V c; return STRC(c, "%"); }
static V S1911(void) { static V c; return STRC(c, " : "); }
static V S1912(void) { static V c; return STRC(c, "; "); }
static V F_Chk_dshow_drwt_dinner(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1904 = a3;
if (TAG(s1904) == 12) {
return F_String_dappend(S1905(), F_String_dappend(F_Bool_dpick(F_String_dis__empty(FLD(s1904, 0)), S1906(), F_String_dappend(FLD(s1904, 0), S1907())), F_String_dappend(a0, F_String_dappend(S1908(), F_String_dappend(F_Chk_dterm__show_dgo(F_Chk_dsyn__body(FLD(s1904, 2)), 2u, C2(1, FLD(s1904, 0), C2(1, a2, a5)), nat_addk(a6, 2)), F_String_dappend(S1909(), F_Chk_dterm__show_dgo(a4, 0u, a5, a6)))))));
} else {
return F_String_dappend(S1910(), F_String_dappend(a0, F_String_dappend(S1911(), F_String_dappend(F_Chk_dterm__show_dgo(a1, 2u, a5, a6), F_String_dappend(S1912(), F_Chk_dterm__show_dgo(a4, 0u, a5, a6))))));
}
}
static V W_Chk_dshow_drwt_dinner(V *a) { (void)a; return F_Chk_dshow_drwt_dinner(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S1914(void) { static V c; return STRC(c, "("); }
static V S1915(void) { static V c; return STRC(c, ")"); }
static V F_Chk_dshow_dparen(V a0, V a1) {
top:;
V s1913 = a0;
if ((s1913) == IMM(1)) {
return F_String_dappend(S1914(), F_String_dappend(a1, S1915()));
} else if ((s1913) == IMM(0)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dparen(V *a) { (void)a; return F_Chk_dshow_dparen(a[0], a[1]); }
static V S1917(void) { static V c; return STRC(c, ": "); }
static V F_Chk_dshow_darms(V a0, V a1, V a2) {
top:;
V s1916 = a0;
if (TAG(s1916) == 17) {
return C2(1, F_String_dappend(FLD(s1916, 0), F_String_dappend(S1917(), F_Chk_dterm__show_dgo(FLD(s1916, 1), 2u, a1, a2))), F_Chk_dshow_darms(FLD(s1916, 2), a1, a2));
} else if (TAG(s1916) == 18) {
return IMM(0);
} else {
return C2(1, F_Chk_dterm__show_dgo(s1916, 2u, a1, a2), IMM(0));
}
}
static V W_Chk_dshow_darms(V *a) { (void)a; return F_Chk_dshow_darms(a[0], a[1], a[2]); }
static V F_Chk_dshow_djoin(V a0, V a1) {
top:;
return F_String_djoin(a0, a1);
}
static V W_Chk_dshow_djoin(V *a) { (void)a; return F_Chk_dshow_djoin(a[0], a[1]); }
static V S1918(void) { static V c; return STRC(c, "U32"); }
static V F_Chk_dshow_dctr(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dshow_dctr_du32(a0, F_Chk_du32__from__term(a0, S1918()), a1, a2, a3);
}
static V W_Chk_dshow_dctr(V *a) { (void)a; return F_Chk_dshow_dctr(a[0], a[1], a[2], a[3]); }
static V F_Chk_du32__from__term(V a0, V a1) {
top:;
return F_Chk_du32__from__term_dgo(F_Chk_dterm__strip(a0), a1);
}
static V W_Chk_du32__from__term(V *a) { (void)a; return F_Chk_du32__from__term(a[0], a[1]); }
static V F_Chk_du32__from__term_dgo(V a0, V a1) {
top:;
V s1919 = a0;
if (TAG(s1919) == 15 && TAG(FLD(s1919, 1)) == 1 && (FLD(FLD(s1919, 1), 1)) == IMM(0)) {
return F_Chk_du32__from__term_dif(FLD(FLD(s1919, 1), 0), F_String_deq(a1, FLD(s1919, 0)));
} else {
return IMM(0);
}
}
static V W_Chk_du32__from__term_dgo(V *a) { (void)a; return F_Chk_du32__from__term_dgo(a[0], a[1]); }
static V F_Chk_du32__from__term_dif(V a0, V a1) {
top:;
V s1920 = a1;
if ((s1920) == IMM(1)) {
return F_Chk_du32__bits(F_Chk_dterm__strip(a0), 0u, 0u);
} else if ((s1920) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_du32__from__term_dif(V *a) { (void)a; return F_Chk_du32__from__term_dif(a[0], a[1]); }
static V F_Chk_du32__bits(V a0, V a1, V a2) {
top:;
V s1921 = a0;
if (TAG(s1921) == 15 && TAG(FLD(s1921, 0)) == 1 && (FLD(FLD(s1921, 0), 0)) == 87 && TAG(FLD(FLD(s1921, 0), 1)) == 1 && (FLD(FLD(FLD(s1921, 0), 1), 0)) == 67 && TAG(FLD(FLD(FLD(s1921, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 0)) == 111 && TAG(FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 1), 0)) == 110 && (FLD(FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s1921, 1)) == 1 && TAG(FLD(FLD(s1921, 1), 1)) == 1 && (FLD(FLD(FLD(s1921, 1), 1), 1)) == IMM(0)) {
return F_Chk_du32__bits_dbit(F_Chk_dterm__strip(FLD(FLD(s1921, 1), 0)), FLD(FLD(FLD(s1921, 1), 1), 0), a1, a2);
} else if (TAG(s1921) == 15 && TAG(FLD(s1921, 0)) == 1 && (FLD(FLD(s1921, 0), 0)) == 87 && TAG(FLD(FLD(s1921, 0), 1)) == 1 && (FLD(FLD(FLD(s1921, 0), 1), 0)) == 78 && TAG(FLD(FLD(FLD(s1921, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 0)) == 105 && TAG(FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 1), 0)) == 108 && (FLD(FLD(FLD(FLD(FLD(s1921, 0), 1), 1), 1), 1)) == IMM(0) && (FLD(s1921, 1)) == IMM(0)) {
return F_Bool_dpick(F_U32_dis__eq(a1, 32u), C1(1, a2), IMM(0));
} else {
return IMM(0);
}
}
static V W_Chk_du32__bits(V *a) { (void)a; return F_Chk_du32__bits(a[0], a[1], a[2]); }
static V F_Chk_du32__bits_dbit(V a0, V a1, V a2, V a3) {
top:;
V s1922 = a0;
if (TAG(s1922) == 15 && TAG(FLD(s1922, 0)) == 1 && (FLD(FLD(s1922, 0), 0)) == 84 && TAG(FLD(FLD(s1922, 0), 1)) == 1 && (FLD(FLD(FLD(s1922, 0), 1), 0)) == 114 && TAG(FLD(FLD(FLD(s1922, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1922, 0), 1), 1), 0)) == 117 && TAG(FLD(FLD(FLD(FLD(s1922, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1922, 0), 1), 1), 1), 0)) == 101 && (FLD(FLD(FLD(FLD(FLD(s1922, 0), 1), 1), 1), 1)) == IMM(0) && (FLD(s1922, 1)) == IMM(0)) {
return F_Chk_du32__bits_dnext(a1, a2, F_U32_dor(a3, F_U32_dshln(1u, F_U32_dto__nat(a2))));
} else if (TAG(s1922) == 15 && TAG(FLD(s1922, 0)) == 1 && (FLD(FLD(s1922, 0), 0)) == 70 && TAG(FLD(FLD(s1922, 0), 1)) == 1 && (FLD(FLD(FLD(s1922, 0), 1), 0)) == 97 && TAG(FLD(FLD(FLD(s1922, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1922, 0), 1), 1), 0)) == 108 && TAG(FLD(FLD(FLD(FLD(s1922, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1922, 0), 1), 1), 1), 0)) == 115 && TAG(FLD(FLD(FLD(FLD(FLD(s1922, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s1922, 0), 1), 1), 1), 1), 0)) == 101 && (FLD(FLD(FLD(FLD(FLD(FLD(s1922, 0), 1), 1), 1), 1), 1)) == IMM(0) && (FLD(s1922, 1)) == IMM(0)) {
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
static V S1924(void) { static V c; return STRC(c, "F32"); }
static V F_Chk_dshow_dctr_du32(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1923 = a1;
if (TAG(s1923) == 1) {
return F_U32_dshow(FLD(s1923, 0));
} else if ((s1923) == IMM(0)) {
return F_Chk_dshow_dctr_df32(a0, F_Chk_du32__from__term(a0, S1924()), a2, a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_du32(V *a) { (void)a; return F_Chk_dshow_dctr_du32(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dshow_dctr_df32(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1925 = a1;
if (TAG(s1925) == 1) {
return F_Chk_df32__show(FLD(s1925, 0));
} else if ((s1925) == IMM(0)) {
return F_Chk_dshow_dctr_dnat(a0, F_Chk_dnat__from__term(a0), a2, a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_df32(V *a) { (void)a; return F_Chk_dshow_dctr_df32(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dnat__from__term(V a0) {
top:;
V s1926 = a0;
if (TAG(s1926) == 15 && TAG(FLD(s1926, 0)) == 1 && (FLD(FLD(s1926, 0), 0)) == 83 && TAG(FLD(FLD(s1926, 0), 1)) == 1 && (FLD(FLD(FLD(s1926, 0), 1), 0)) == 117 && TAG(FLD(FLD(FLD(s1926, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1926, 0), 1), 1), 0)) == 99 && TAG(FLD(FLD(FLD(FLD(s1926, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1926, 0), 1), 1), 1), 0)) == 99 && (FLD(FLD(FLD(FLD(FLD(s1926, 0), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s1926, 1)) == 1 && (FLD(FLD(s1926, 1), 1)) == IMM(0)) {
return F_Chk_dMaybe_dmap__nat(F_Chk_dnat__from__term(FLD(FLD(s1926, 1), 0)));
} else if (TAG(s1926) == 15 && TAG(FLD(s1926, 0)) == 1 && (FLD(FLD(s1926, 0), 0)) == 90 && TAG(FLD(FLD(s1926, 0), 1)) == 1 && (FLD(FLD(FLD(s1926, 0), 1), 0)) == 101 && TAG(FLD(FLD(FLD(s1926, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1926, 0), 1), 1), 0)) == 114 && TAG(FLD(FLD(FLD(FLD(s1926, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1926, 0), 1), 1), 1), 0)) == 111 && (FLD(FLD(FLD(FLD(FLD(s1926, 0), 1), 1), 1), 1)) == IMM(0) && (FLD(s1926, 1)) == IMM(0)) {
return C1(1, 0u);
} else if (TAG(s1926) == 16 && TAG(FLD(s1926, 0)) == 0) {
return C1(1, FLD(FLD(s1926, 0), 0));
} else {
return IMM(0);
}
}
static V W_Chk_dnat__from__term(V *a) { (void)a; return F_Chk_dnat__from__term(a[0]); }
static V F_Chk_dMaybe_dmap__nat(V a0) {
top:;
V s1927 = a0;
if ((s1927) == IMM(0)) {
return IMM(0);
} else if (TAG(s1927) == 1) {
return F_Bool_dpick(F_Nat_dis__le(nat_addk(FLD(s1927, 0), 1), 4294967295u), C1(1, nat_addk(FLD(s1927, 0), 1)), IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dMaybe_dmap__nat(V *a) { (void)a; return F_Chk_dMaybe_dmap__nat(a[0]); }
static V W_Nat_dis__le(V *a) { (void)a; return F_Nat_dis__le(a[0], a[1]); }
static V S1929(void) { static V c; return STRC(c, "n"); }
static V S1930(void) { static V c; return STRC(c, "Succ"); }
static V F_Chk_dshow_dctr_dnat(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1928 = a1;
if (TAG(s1928) == 1) {
return F_String_dappend(F_Nat_dshow(FLD(s1928, 0)), S1929());
} else if ((s1928) == IMM(0)) {
return F_Chk_dshow_dctr_dsucc(a0, F_Chk_dshow_dchain(a0, S1930(), 1u), a2, a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_dnat(V *a) { (void)a; return F_Chk_dshow_dctr_dnat(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dshow_dchain(V a0, V a1, V a2) {
top:;
V s1931 = a0;
if (TAG(s1931) == 15) {
return F_Chk_dshow_dchain_dif(C3(15, FLD(s1931, 0), FLD(s1931, 1), FLD(s1931, 2)), FLD(s1931, 1), a1, a2, F_Bool_dand(F_String_deq(a1, FLD(s1931, 0)), F_Nat_dis__eq(F_List_dlength(FLD(s1931, 1)), a2)));
} else {
return C2(0, IMM(0), s1931);
}
}
static V W_Chk_dshow_dchain(V *a) { (void)a; return F_Chk_dshow_dchain(a[0], a[1], a[2]); }
static V F_Chk_dshow_dchain_dif(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1932 = a4;
if ((s1932) == IMM(1)) {
return F_Chk_dshow_dchain_dcons(F_Chk_dLst_dhead(a0, a1), F_Chk_dshow_dchain(F_Chk_dLst_dlast(a0, a1), a2, a3));
} else if ((s1932) == IMM(0)) {
return C2(0, IMM(0), a0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dchain_dif(V *a) { (void)a; return F_Chk_dshow_dchain_dif(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dLst_dlast(V a1, V a2) {
top:;
V s1933 = a2;
if ((s1933) == IMM(0)) {
return a1;
} else if (TAG(s1933) == 1 && (FLD(s1933, 1)) == IMM(0)) {
return FLD(s1933, 0);
} else if (TAG(s1933) == 1) {
{ V t0 = a1; V t1 = FLD(s1933, 1); a1 = t0; a2 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dLst_dlast(V *a) { (void)a; return F_Chk_dLst_dlast(a[1], a[2]); }
static V F_Chk_dshow_dchain_dcons(V a0, V a1) {
top:;
V v1934 = a1;
return C2(0, C2(1, a0, FLD(v1934, 0)), FLD(v1934, 1));
}
static V W_Chk_dshow_dchain_dcons(V *a) { (void)a; return F_Chk_dshow_dchain_dcons(a[0], a[1]); }
static V S1937(void) { static V c; return STRC(c, "n+"); }
static V F_Chk_dshow_dctr_dsucc(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1935 = a1;
V s1936 = FLD(v1935, 0);
if ((s1936) == IMM(0)) {
return F_Chk_dshow_dctr_dchr(a0, F_Chk_dshow_dchr__term(a0, 39u), a2, a3, a4);
} else if (TAG(s1936) == 1) {
return F_Chk_dshow_dparen(F_U32_dis__gt(a2, 2u), F_String_dappend(F_Nat_dshow(F_List_dlength(C2(1, FLD(s1936, 0), FLD(s1936, 1)))), F_String_dappend(S1937(), F_Chk_dterm__show_dgo(FLD(v1935, 1), 2u, a3, a4))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_dsucc(V *a) { (void)a; return F_Chk_dshow_dctr_dsucc(a[0], a[1], a[2], a[3], a[4]); }
static V S1939(void) { static V c; return STRC(c, "U32"); }
static V F_Chk_dshow_dchr__term(V a0, V a1) {
top:;
V s1938 = a0;
if (TAG(s1938) == 15 && TAG(FLD(s1938, 0)) == 1 && (FLD(FLD(s1938, 0), 0)) == 67 && TAG(FLD(FLD(s1938, 0), 1)) == 1 && (FLD(FLD(FLD(s1938, 0), 1), 0)) == 104 && TAG(FLD(FLD(FLD(s1938, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1938, 0), 1), 1), 0)) == 114 && (FLD(FLD(FLD(FLD(s1938, 0), 1), 1), 1)) == IMM(0) && TAG(FLD(s1938, 1)) == 1 && (FLD(FLD(s1938, 1), 1)) == IMM(0)) {
return F_Chk_dshow_dchr__term_du(F_Chk_du32__from__term(FLD(FLD(s1938, 1), 0), S1939()), a1);
} else {
return IMM(0);
}
}
static V W_Chk_dshow_dchr__term(V *a) { (void)a; return F_Chk_dshow_dchr__term(a[0], a[1]); }
static V F_Chk_dshow_dchr__term_du(V a0, V a1) {
top:;
V s1940 = a0;
if ((s1940) == IMM(0)) {
return IMM(0);
} else if (TAG(s1940) == 1) {
return C1(1, F_Chk_dshow_dchr(FLD(s1940, 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dchr__term_du(V *a) { (void)a; return F_Chk_dshow_dchr__term_du(a[0], a[1]); }
static V S1942(void) { static V c; return STRC(c, "'"); }
static V S1943(void) { static V c; return STRC(c, "'"); }
static V F_Chk_dshow_dctr_dchr(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1941 = a1;
if (TAG(s1941) == 1) {
return F_String_dappend(S1942(), F_String_dappend(FLD(s1941, 0), S1943()));
} else if ((s1941) == IMM(0)) {
return F_Chk_dshow_dctr_dstr(a0, F_Chk_dshow_dstr(a0), a2, a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_dchr(V *a) { (void)a; return F_Chk_dshow_dctr_dchr(a[0], a[1], a[2], a[3], a[4]); }
static V S1944(void) { static V c; return STRC(c, "SCon"); }
static V F_Chk_dshow_dstr(V a0) {
top:;
return F_Chk_dshow_dstr_dgo(F_Chk_dshow_dchain(a0, S1944(), 2u));
}
static V W_Chk_dshow_dstr(V *a) { (void)a; return F_Chk_dshow_dstr(a[0]); }
static V F_Chk_dshow_dstr_dgo(V a0) {
top:;
V v1945 = a0;
return F_Chk_dshow_dstr_dc(F_Chk_dshow_dchrs_dcat(F_Chk_dshow_dchrs(FLD(v1945, 0)), F_Chk_dshow_dstr__tail(FLD(v1945, 1))));
}
static V W_Chk_dshow_dstr_dgo(V *a) { (void)a; return F_Chk_dshow_dstr_dgo(a[0]); }
static V S1947(void) { static V c; return STRC(c, ""); }
static V F_Chk_dshow_dstr__tail(V a0) {
top:;
V s1946 = a0;
if (TAG(s1946) == 16 && TAG(FLD(s1946, 0)) == 1) {
return C1(1, F_Chk_dshow_dtext(FLD(FLD(s1946, 0), 0)));
} else if (TAG(s1946) == 15 && TAG(FLD(s1946, 0)) == 1 && (FLD(FLD(s1946, 0), 0)) == 83 && TAG(FLD(FLD(s1946, 0), 1)) == 1 && (FLD(FLD(FLD(s1946, 0), 1), 0)) == 78 && TAG(FLD(FLD(FLD(s1946, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1946, 0), 1), 1), 0)) == 105 && TAG(FLD(FLD(FLD(FLD(s1946, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1946, 0), 1), 1), 1), 0)) == 108 && (FLD(FLD(FLD(FLD(FLD(s1946, 0), 1), 1), 1), 1)) == IMM(0) && (FLD(s1946, 1)) == IMM(0)) {
return C1(1, S1947());
} else {
return IMM(0);
}
}
static V W_Chk_dshow_dstr__tail(V *a) { (void)a; return F_Chk_dshow_dstr__tail(a[0]); }
static V S1949(void) { static V c; return STRC(c, ""); }
static V F_Chk_dshow_dchrs(V a0) {
top:;
V s1948 = a0;
if ((s1948) == IMM(0)) {
return C1(1, S1949());
} else if (TAG(s1948) == 1) {
return F_Chk_dshow_dchrs_dcat(F_Chk_dshow_dchr__term(FLD(s1948, 0), 34u), F_Chk_dshow_dchrs(FLD(s1948, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dchrs(V *a) { (void)a; return F_Chk_dshow_dchrs(a[0]); }
static V F_Chk_dshow_dchrs_dcat(V a0, V a1) {
top:;
V s1950 = a0;
V s1951 = a1;
if (TAG(s1950) == 1 && TAG(s1951) == 1) {
return C1(1, F_String_dappend(FLD(s1950, 0), FLD(s1951, 0)));
} else {
return IMM(0);
}
}
static V W_Chk_dshow_dchrs_dcat(V *a) { (void)a; return F_Chk_dshow_dchrs_dcat(a[0], a[1]); }
static V S1953(void) { static V c; return STRC(c, "\042"); }
static V S1954(void) { static V c; return STRC(c, "\042"); }
static V F_Chk_dshow_dstr_dc(V a0) {
top:;
V s1952 = a0;
if ((s1952) == IMM(0)) {
return IMM(0);
} else if (TAG(s1952) == 1) {
return C1(1, F_String_dappend(S1953(), F_String_dappend(FLD(s1952, 0), S1954())));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dstr_dc(V *a) { (void)a; return F_Chk_dshow_dstr_dc(a[0]); }
static V S1956(void) { static V c; return STRC(c, "Con"); }
static V F_Chk_dshow_dctr_dstr(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1955 = a1;
if (TAG(s1955) == 1) {
return FLD(s1955, 0);
} else if ((s1955) == IMM(0)) {
return F_Chk_dshow_dctr_dlst(a0, F_Chk_dshow_dchain(a0, S1956(), 2u), a2, a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_dstr(V *a) { (void)a; return F_Chk_dshow_dctr_dstr(a[0], a[1], a[2], a[3], a[4]); }
static V S1960(void) { static V c; return STRC(c, "["); }
static V S1961(void) { static V c; return STRC(c, ", "); }
static V S1962(void) { static V c; return STRC(c, "]"); }
static V S1963(void) { static V c; return STRC(c, "Tuple"); }
static V S1964(void) { static V c; return STRC(c, " <> "); }
static V S1965(void) { static V c; return STRC(c, " <> "); }
static V F_Chk_dshow_dctr_dlst(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1957 = a1;
V s1958 = FLD(v1957, 0);
V s1959 = FLD(v1957, 1);
if (TAG(s1959) == 15 && TAG(FLD(s1959, 0)) == 1 && (FLD(FLD(s1959, 0), 0)) == 78 && TAG(FLD(FLD(s1959, 0), 1)) == 1 && (FLD(FLD(FLD(s1959, 0), 1), 0)) == 105 && TAG(FLD(FLD(FLD(s1959, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1959, 0), 1), 1), 0)) == 108 && (FLD(FLD(FLD(FLD(s1959, 0), 1), 1), 1)) == IMM(0) && (FLD(s1959, 1)) == IMM(0)) {
return F_String_dappend(S1960(), F_String_dappend(F_Chk_dshow_djoin(F_Chk_dshow_dargs(a3, a4, s1958, 1u), S1961()), S1962()));
} else if ((s1958) == IMM(0)) {
return F_Chk_dshow_dctr_dtup(a0, F_Chk_dshow_dchain(a0, S1963(), 2u), a2, a3, a4);
} else {
return F_Chk_dshow_dparen(F_U32_dis__gt(a2, 2u), F_String_dappend(F_Chk_dshow_djoin(F_Chk_dshow_dargs(a3, a4, s1958, 3u), S1964()), F_String_dappend(S1965(), F_Chk_dterm__show_dgo(s1959, 2u, a3, a4))));
}
}
static V W_Chk_dshow_dctr_dlst(V *a) { (void)a; return F_Chk_dshow_dctr_dlst(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dshow_dargs(V a0, V a1, V a2, V a3) {
top:;
V s1966 = a2;
if ((s1966) == IMM(0)) {
return IMM(0);
} else if (TAG(s1966) == 1) {
return C2(1, F_Chk_dterm__show_dgo(FLD(s1966, 0), a3, a0, a1), F_Chk_dshow_dargs(a0, a1, FLD(s1966, 1), a3));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dargs(V *a) { (void)a; return F_Chk_dshow_dargs(a[0], a[1], a[2], a[3]); }
static V S1969(void) { static V c; return STRC(c, "("); }
static V S1970(void) { static V c; return STRC(c, ", "); }
static V S1971(void) { static V c; return STRC(c, ")"); }
static V F_Chk_dshow_dctr_dtup(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1967 = a1;
V s1968 = FLD(v1967, 0);
if ((s1968) == IMM(0)) {
return F_Chk_dshow_dctr_darr(a0, F_Chk_dshow_darr(a0, a3, a4), a3, a4);
} else if (TAG(s1968) == 1) {
return F_String_dappend(S1969(), F_String_dappend(F_Chk_dshow_djoin(F_Chk_dshow_dargs(a3, a4, F_List_dappend(C2(1, FLD(s1968, 0), FLD(s1968, 1)), C2(1, FLD(v1967, 1), IMM(0))), 1u), S1970()), S1971()));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_dtup(V *a) { (void)a; return F_Chk_dshow_dctr_dtup(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dshow_darr(V a0, V a1, V a2) {
top:;
V s1972 = a0;
if (TAG(s1972) == 15 && TAG(FLD(s1972, 0)) == 1 && (FLD(FLD(s1972, 0), 0)) == 65 && TAG(FLD(FLD(s1972, 0), 1)) == 1 && (FLD(FLD(FLD(s1972, 0), 1), 0)) == 76 && TAG(FLD(FLD(FLD(s1972, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1972, 0), 1), 1), 0)) == 101 && TAG(FLD(FLD(FLD(FLD(s1972, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1972, 0), 1), 1), 1), 0)) == 97 && TAG(FLD(FLD(FLD(FLD(FLD(s1972, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s1972, 0), 1), 1), 1), 1), 0)) == 102 && (FLD(FLD(FLD(FLD(FLD(FLD(s1972, 0), 1), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s1972, 1)) == 1 && (FLD(FLD(s1972, 1), 1)) == IMM(0)) {
return C1(1, C2(1, F_Chk_dterm__show_dgo(FLD(FLD(s1972, 1), 0), 1u, a1, a2), IMM(0)));
} else if (TAG(s1972) == 15 && TAG(FLD(s1972, 0)) == 1 && (FLD(FLD(s1972, 0), 0)) == 65 && TAG(FLD(FLD(s1972, 0), 1)) == 1 && (FLD(FLD(FLD(s1972, 0), 1), 0)) == 78 && TAG(FLD(FLD(FLD(s1972, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1972, 0), 1), 1), 0)) == 111 && TAG(FLD(FLD(FLD(FLD(s1972, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1972, 0), 1), 1), 1), 0)) == 100 && TAG(FLD(FLD(FLD(FLD(FLD(s1972, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s1972, 0), 1), 1), 1), 1), 0)) == 101 && (FLD(FLD(FLD(FLD(FLD(FLD(s1972, 0), 1), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s1972, 1)) == 1 && TAG(FLD(FLD(s1972, 1), 1)) == 1 && (FLD(FLD(FLD(s1972, 1), 1), 1)) == IMM(0)) {
return F_Chk_dshow_darr_dcat(F_Chk_dshow_darr(FLD(FLD(s1972, 1), 0), a1, a2), F_Chk_dshow_darr(FLD(FLD(FLD(s1972, 1), 1), 0), a1, a2));
} else {
return IMM(0);
}
}
static V W_Chk_dshow_darr(V *a) { (void)a; return F_Chk_dshow_darr(a[0], a[1], a[2]); }
static V F_Chk_dshow_darr_dcat(V a0, V a1) {
top:;
V s1973 = a0;
V s1974 = a1;
if (TAG(s1973) == 1 && TAG(s1974) == 1) {
return C1(1, F_List_dappend(FLD(s1973, 0), FLD(s1974, 0)));
} else {
return IMM(0);
}
}
static V W_Chk_dshow_darr_dcat(V *a) { (void)a; return F_Chk_dshow_darr_dcat(a[0], a[1]); }
static V S1976(void) { static V c; return STRC(c, "["); }
static V S1977(void) { static V c; return STRC(c, ", "); }
static V S1978(void) { static V c; return STRC(c, "]"); }
static V F_Chk_dshow_dctr_darr(V a0, V a1, V a2, V a3) {
top:;
V s1975 = a1;
if (TAG(s1975) == 1) {
return F_String_dappend(S1976(), F_String_dappend(F_Chk_dshow_djoin(FLD(s1975, 0), S1977()), S1978()));
} else if ((s1975) == IMM(0)) {
return F_Chk_dshow_dctr_dplain(a0, a2, a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dctr_darr(V *a) { (void)a; return F_Chk_dshow_dctr_darr(a[0], a[1], a[2], a[3]); }
static V S1980(void) { static V c; return STRC(c, "{"); }
static V S1981(void) { static V c; return STRC(c, ", "); }
static V S1982(void) { static V c; return STRC(c, "}"); }
static V S1983(void) { static V c; return STRC(c, "\077"); }
static V F_Chk_dshow_dctr_dplain(V a0, V a1, V a2) {
top:;
V s1979 = a0;
if (TAG(s1979) == 15) {
return F_String_dappend(FLD(s1979, 0), F_String_dappend(S1980(), F_String_dappend(F_Chk_dshow_djoin(F_Chk_dshow_dargs(a1, a2, FLD(s1979, 1), 1u), S1981()), S1982())));
} else {
return S1983();
}
}
static V W_Chk_dshow_dctr_dplain(V *a) { (void)a; return F_Chk_dshow_dctr_dplain(a[0], a[1], a[2]); }
static V S1985(void) { static V c; return STRC(c, "."); }
static V S1986(void) { static V c; return STRC(c, "e"); }
static V S1987(void) { static V c; return STRC(c, "n"); }
static V S1988(void) { static V c; return STRC(c, "i"); }
static V S1989(void) { static V c; return STRC(c, ".0"); }
static V F_Chk_df32__show(V a0) {
top:;
V v1984 = F_F32_dshow(F_Chk_dF32_dfrom__bits(a0));
return F_Bool_dpick(F_Bool_dor(F_String_dcontains(v1984, S1985()), F_Bool_dor(F_String_dcontains(v1984, S1986()), F_Bool_dor(F_String_dcontains(v1984, S1987()), F_String_dcontains(v1984, S1988())))), v1984, F_String_dappend(v1984, S1989()));
}
static V W_Chk_df32__show(V *a) { (void)a; return F_Chk_df32__show(a[0]); }
static V F_String_dcontains(V a0, V a1) {
top:;
V s1990 = a0;
if ((s1990) == IMM(0)) {
return F_String_dis__empty(a1);
} else if (TAG(s1990) == 1) {
return F_String_dcontains_dif(FLD(s1990, 1), a1, F_String_dstarts__with(C2(1, FLD(s1990, 0), FLD(s1990, 1)), a1));
} else { bend_fail("incomplete match"); }
}
static V W_String_dcontains(V *a) { (void)a; return F_String_dcontains(a[0], a[1]); }
static V F_String_dcontains_dif(V a0, V a1, V a2) {
top:;
V s1991 = a2;
if ((s1991) == IMM(0)) {
return F_String_dcontains(a0, a1);
} else if ((s1991) == IMM(1)) {
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
V s1992 = a0;
{
return s1992;
}
}
static V W_Chk_dWord_dfrom__u32(V *a) { (void)a; return F_Chk_dWord_dfrom__u32(a[0]); }
static V W_F32_dshow(V *a) { (void)a; return F_F32_dshow(a[0]); }
static V F_Chk_dLst_dempty(V a2) {
top:;
V s1993 = a2;
if ((s1993) == IMM(0)) {
return IMM(1);
} else if (TAG(s1993) == 1) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dLst_dempty(V *a) { (void)a; return F_Chk_dLst_dempty(a[2]); }
static V S1995(void) { static V c; return STRC(c, ""); }
static V S1996(void) { static V c; return STRC(c, " - "); }
static V S1997(void) { static V c; return STRC(c, "{}"); }
static V F_Chk_dshow_drems(V a0) {
top:;
V s1994 = a0;
if ((s1994) == IMM(0)) {
return S1995();
} else if (TAG(s1994) == 1) {
return F_String_dappend(S1996(), F_String_dappend(FLD(s1994, 0), F_String_dappend(S1997(), F_Chk_dshow_drems(FLD(s1994, 1)))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_drems(V *a) { (void)a; return F_Chk_dshow_drems(a[0]); }
static V F_Chk_dshow_dapp(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dshow_dapp_dgo(F_Chk_dterm__unapply(a0), a1, a2, a3);
}
static V W_Chk_dshow_dapp(V *a) { (void)a; return F_Chk_dshow_dapp(a[0], a[1], a[2], a[3]); }
static V S2001(void) { static V c; return STRC(c, "&"); }
static V S2002(void) { static V c; return STRC(c, ":"); }
static V S2003(void) { static V c; return STRC(c, " -> "); }
static V S2004(void) { static V c; return STRC(c, "("); }
static V S2005(void) { static V c; return STRC(c, ", "); }
static V S2006(void) { static V c; return STRC(c, ")"); }
static V F_Chk_dshow_dapp_dgo(V a0, V a1, V a2, V a3) {
top:;
V v1998 = a0;
V s1999 = FLD(v1998, 0);
V s2000 = FLD(v1998, 1);
if (TAG(s1999) == 4 && TAG(FLD(s1999, 0)) == 1 && (FLD(FLD(s1999, 0), 0)) == 69 && TAG(FLD(FLD(s1999, 0), 1)) == 1 && (FLD(FLD(FLD(s1999, 0), 1), 0)) == 120 && TAG(FLD(FLD(FLD(s1999, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s1999, 0), 1), 1), 0)) == 105 && TAG(FLD(FLD(FLD(FLD(s1999, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s1999, 0), 1), 1), 1), 0)) == 115 && TAG(FLD(FLD(FLD(FLD(FLD(s1999, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s1999, 0), 1), 1), 1), 1), 0)) == 116 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(s1999, 0), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(s1999, 0), 1), 1), 1), 1), 1), 0)) == 115 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(s1999, 0), 1), 1), 1), 1), 1), 1)) == IMM(0) && TAG(s2000) == 1 && TAG(FLD(s2000, 1)) == 1 && TAG(FLD(FLD(s2000, 1), 0)) == 12 && (FLD(FLD(s2000, 1), 1)) == IMM(0)) {
return F_Chk_dshow_dparen(F_U32_dis__gt(a1, 2u), F_String_dappend(S2001(), F_String_dappend(FLD(FLD(FLD(s2000, 1), 0), 0), F_String_dappend(S2002(), F_String_dappend(F_Chk_dterm__show_dgo(FLD(s2000, 0), 3u, a2, a3), F_String_dappend(S2003(), F_Chk_dterm__show_dgo(F_Chk_dsyn__body(FLD(FLD(FLD(s2000, 1), 0), 2)), 2u, C2(1, FLD(FLD(FLD(s2000, 1), 0), 0), a2), nat_addk(a3, 1))))))));
} else {
return F_String_dappend(F_Chk_dterm__show_dgo(s1999, 3u, a2, a3), F_String_dappend(S2004(), F_String_dappend(F_Chk_dshow_djoin(F_Chk_dshow_dargs(a2, a3, s2000, 1u), S2005()), S2006())));
}
}
static V W_Chk_dshow_dapp_dgo(V *a) { (void)a; return F_Chk_dshow_dapp_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dQ_ddef(V a0) {
top:;
V s2007 = a0;
if ((s2007) == IMM(3)) {
return IMM(1);
} else {
return s2007;
}
}
static V W_Chk_dQ_ddef(V *a) { (void)a; return F_Chk_dQ_ddef(a[0]); }
static V S2009(void) { static V c; return STRC(c, "Type"); }
static V S2010(void) { static V c; return STRC(c, "Data"); }
static V S2011(void) { static V c; return STRC(c, "Kind("); }
static V S2012(void) { static V c; return STRC(c, ")"); }
static V F_Chk_dshow_dtyp(V a0, V a1, V a2) {
top:;
V s2008 = a0;
if (TAG(s2008) == 9 && (FLD(s2008, 0)) == IMM(1)) {
return S2009();
} else if (TAG(s2008) == 9 && (FLD(s2008, 0)) == IMM(2)) {
return S2010();
} else {
return F_String_dappend(S2011(), F_String_dappend(F_Chk_dterm__show_dgo(s2008, 1u, a1, a2), S2012()));
}
}
static V W_Chk_dshow_dtyp(V *a) { (void)a; return F_Chk_dshow_dtyp(a[0], a[1], a[2]); }
static V F_Chk_dshow_dlet__ks(V a0, V a1) {
top:;
V s2013 = a0;
V s2014 = a1;
if (TAG(s2013) == 1 && TAG(s2014) == 1) {
return C2(1, F_String_dappend(F_Chk_dquant__show(FLD(s2014, 0)), FLD(s2013, 0)), F_Chk_dshow_dlet__ks(FLD(s2013, 1), FLD(s2014, 1)));
} else if (TAG(s2013) == 1 && (s2014) == IMM(0)) {
return C2(1, FLD(s2013, 0), F_Chk_dshow_dlet__ks(FLD(s2013, 1), IMM(0)));
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
V s2015 = a0;
if ((s2015) == IMM(0)) {
return IMM(0);
} else if (TAG(s2015) == 1) {
return F_Chk_dStr_dindex_dif(FLD(s2015, 1), a1, a2, F_String_deq(FLD(s2015, 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dindex(V *a) { (void)a; return F_Chk_dStr_dindex(a[0], a[1], a[2]); }
static V F_Chk_dStr_dindex_dif(V a0, V a1, V a2, V a3) {
top:;
V s2016 = a3;
if ((s2016) == IMM(1)) {
return C1(1, a2);
} else if ((s2016) == IMM(0)) {
return F_Chk_dStr_dindex(a0, a1, nat_addk(a2, 1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dindex_dif(V *a) { (void)a; return F_Chk_dStr_dindex_dif(a[0], a[1], a[2], a[3]); }
static V F_Chk_dshow_dbound__at_dc(V a0, V a1, V a2) {
top:;
V s2017 = a2;
if ((s2017) == IMM(0)) {
return IMM(0);
} else if (TAG(s2017) == 1) {
return F_Nat_dis__eq(F_Nat_dsub(F_Nat_dsub(a0, 1u), FLD(s2017, 0)), F_U32_dto__nat(a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dshow_dbound__at_dc(V *a) { (void)a; return F_Chk_dshow_dbound__at_dc(a[0], a[1], a[2]); }
static V S2018(void) { static V c; return STRC(c, "#include <stdio.h>\012\012int main(void) {\012  fputs(\042"); }
static V S2019(void) { static V c; return STRC(c, "\134n\042, stdout);\012  return 0;\012}\012"); }
static V F_Main_demit__value(V a0) {
top:;
return F_IO_dwrite(F_String_dappend(S2018(), F_String_dappend(F_Gen_dlit(a0), S2019())));
}
static V W_Main_demit__value(V *a) { (void)a; return F_Main_demit__value(a[0]); }
static V S2021(void) { static V c; return STRC(c, ""); }
static V S2023(void) { static V c; return STRC(c, "All terms check, but "); }
static V S2024(void) { static V c; return STRC(c, " def"); }
static V S2025(void) { static V c; return STRC(c, " relies"); }
static V S2026(void) { static V c; return STRC(c, "s rely"); }
static V S2027(void) { static V c; return STRC(c, " on unsafe or foreign code:\012"); }
static V F_Chk_dreport__text(V a0) {
top:;
V s2020 = a0;
if ((s2020) == IMM(0)) {
return S2021();
} else if (TAG(s2020) == 1) {
V v2022 = F_List_dlength(C2(1, FLD(s2020, 0), FLD(s2020, 1)));
return F_String_dappend(S2023(), F_String_dappend(F_Nat_dshow(v2022), F_String_dappend(S2024(), F_String_dappend(F_Bool_dpick(F_Nat_dis__eq(v2022, 1u), S2025(), S2026()), F_String_dappend(S2027(), F_Chk_dreport__lines(C2(1, FLD(s2020, 0), FLD(s2020, 1))))))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport__text(V *a) { (void)a; return F_Chk_dreport__text(a[0]); }
static V S2029(void) { static V c; return STRC(c, ""); }
static V S2030(void) { static V c; return STRC(c, "- "); }
static V S2031(void) { static V c; return STRC(c, "\012"); }
static V F_Chk_dreport__lines(V a0) {
top:;
V s2028 = a0;
if ((s2028) == IMM(0)) {
return S2029();
} else if (TAG(s2028) == 1) {
return F_String_dappend(S2030(), F_String_dappend(FLD(s2028, 0), F_String_dappend(S2031(), F_Chk_dreport__lines(FLD(s2028, 1)))));
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
V s2032 = a2;
if ((s2032) == IMM(0)) {
return IMM(1);
} else if (TAG(s2032) == 1) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_List_dis__empty(V *a) { (void)a; return F_List_dis__empty(a[2]); }
static V F_Chk_dreport(V a0, V a1) {
top:;
V v2033 = F_Chk_dStr_dunique(F_Chk_dList_ddrop__str2(F_Chk_dbook__order(a0), a1), IMM(0));
V v2034 = F_Chk_dreport_dbad__all(a0, F_Map_dkeys(F_Chk_dBook_dtlds(a0)));
return F_Chk_dreport_dgo(a0, v2033, v2034, F_Chk_dLst_dempty(v2034));
}
static V W_Chk_dreport(V *a) { (void)a; return F_Chk_dreport(a[0], a[1]); }
static V F_Chk_dreport_dgo(V a0, V a1, V a2, V a3) {
top:;
V s2035 = a3;
if ((s2035) == IMM(1)) {
return IMM(0);
} else if ((s2035) == IMM(0)) {
return F_Chk_dStr_dfilter__in(a1, F_Chk_dreport_dclose(F_Chk_dreport_dwalk(a0, a1, F_Set_dnew(), IMM(0)), a2, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dgo(V *a) { (void)a; return F_Chk_dreport_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dreport_dwalk(V a0, V a1, V a2, V a3) {
top:;
V s2036 = a1;
if ((s2036) == IMM(0)) {
return a3;
} else if (TAG(s2036) == 1) {
return F_Chk_dreport_dwalk_done(a0, FLD(s2036, 0), FLD(s2036, 1), F_Set_dhas(a2, FLD(s2036, 0)), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dwalk(V *a) { (void)a; return F_Chk_dreport_dwalk(a[0], a[1], a[2], a[3]); }
static V F_Chk_dreport_dwalk_done(V a0, V a1, V a2, V a3, V a4) {
top:;
V v2037 = a3;
V s2038 = FLD(v2037, 1);
if ((s2038) == IMM(1)) {
return F_Chk_dreport_dwalk(a0, a2, FLD(v2037, 0), a4);
} else if ((s2038) == IMM(0)) {
V v2039 = F_Chk_dtld__refs(F_Chk_dbook__tld(a0, a1));
return F_Chk_dreport_dwalk(a0, F_List_dappend(v2039, a2), F_Set_dadd(FLD(v2037, 0), a1), F_Chk_dreport_duses(v2039, a1, a4));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dwalk_done(V *a) { (void)a; return F_Chk_dreport_dwalk_done(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dreport_duses(V a0, V a1, V a2) {
top:;
V s2040 = a0;
if ((s2040) == IMM(0)) {
return a2;
} else if (TAG(s2040) == 1) {
{ V t0 = FLD(s2040, 1); V t1 = a1; V t2 = C2(1, C2(0, FLD(s2040, 0), a1), a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_duses(V *a) { (void)a; return F_Chk_dreport_duses(a[0], a[1], a[2]); }
static V F_Chk_dtld__refs(V a0) {
top:;
V s2041 = a0;
if (TAG(s2041) == 1 && TAG(FLD(s2041, 0)) == 0) {
return F_Chk_dterm__refs(FLD(FLD(s2041, 0), 2), F_Chk_dtld__refs_dv(FLD(FLD(s2041, 0), 3)));
} else if (TAG(s2041) == 1 && TAG(FLD(s2041, 0)) == 1) {
return F_Chk_drefs_dlist(F_Chk_dCtrD_dts(FLD(FLD(s2041, 0), 3)), IMM(0));
} else if ((s2041) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dtld__refs(V *a) { (void)a; return F_Chk_dtld__refs(a[0]); }
static V F_Chk_dCtrD_dts(V a0) {
top:;
V s2042 = a0;
if ((s2042) == IMM(0)) {
return IMM(0);
} else if (TAG(s2042) == 1) {
return C2(1, FLD(FLD(s2042, 0), 2), F_Chk_dCtrD_dts(FLD(s2042, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCtrD_dts(V *a) { (void)a; return F_Chk_dCtrD_dts(a[0]); }
static V F_Chk_drefs_dlist(V a0, V a1) {
top:;
V s2043 = a0;
if ((s2043) == IMM(0)) {
return a1;
} else if (TAG(s2043) == 1) {
{ V t0 = FLD(s2043, 1); V t1 = F_Chk_dterm__refs(FLD(s2043, 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_drefs_dlist(V *a) { (void)a; return F_Chk_drefs_dlist(a[0], a[1]); }
static V F_Chk_dterm__refs(V a0, V a1) {
top:;
V s2044 = a0;
if (TAG(s2044) == 4) {
return C2(1, FLD(s2044, 0), a1);
} else if (TAG(s2044) == 14) {
return F_Chk_drefs_dlist(FLD(s2044, 1), C2(1, FLD(s2044, 0), a1));
} else if (TAG(s2044) == 1) {
{ V t0 = FLD(s2044, 2); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 3) {
{ V t0 = FLD(s2044, 3); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 5) {
{ V t0 = FLD(s2044, 2); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 6) {
{ V t0 = FLD(s2044, 3); V t1 = F_Chk_drefs_dlist(FLD(s2044, 2), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 7) {
{ V t0 = FLD(s2044, 0); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 10) {
{ V t0 = FLD(s2044, 1); V t1 = F_Chk_dterm__refs(FLD(s2044, 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 11) {
{ V t0 = FLD(s2044, 4); V t1 = F_Chk_dterm__refs(FLD(s2044, 3), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 12) {
{ V t0 = FLD(s2044, 2); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 13) {
{ V t0 = FLD(s2044, 1); V t1 = F_Chk_dterm__refs(FLD(s2044, 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 15) {
return F_Chk_drefs_dlist(FLD(s2044, 1), a1);
} else if (TAG(s2044) == 17) {
{ V t0 = FLD(s2044, 2); V t1 = F_Chk_dterm__refs(FLD(s2044, 1), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 19) {
{ V t0 = FLD(s2044, 2); V t1 = F_Chk_dterm__refs(FLD(s2044, 1), F_Chk_dterm__refs(FLD(s2044, 0), a1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 21) {
{ V t0 = FLD(s2044, 2); V t1 = F_Chk_dterm__refs(FLD(s2044, 1), F_Chk_dterm__refs(FLD(s2044, 0), a1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 23) {
{ V t0 = FLD(s2044, 1); V t1 = F_Chk_dterm__refs(FLD(s2044, 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 24) {
{ V t0 = FLD(s2044, 2); V t1 = F_Chk_drefs_dlist(FLD(s2044, 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 25) {
{ V t0 = FLD(s2044, 2); V t1 = F_Chk_drefs_dlist(FLD(s2044, 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2044) == 31) {
{ V t0 = FLD(s2044, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else {
return a1;
}
}
static V W_Chk_dterm__refs(V *a) { (void)a; return F_Chk_dterm__refs(a[0], a[1]); }
static V F_Chk_dtld__refs_dv(V a0) {
top:;
V s2045 = a0;
if (TAG(s2045) == 1) {
return F_Chk_dterm__refs(FLD(s2045, 0), IMM(0));
} else if ((s2045) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dtld__refs_dv(V *a) { (void)a; return F_Chk_dtld__refs_dv(a[0]); }
static V F_Chk_dreport_dclose(V a0, V a1, V a2) {
top:;
V s2046 = a1;
if ((s2046) == IMM(0)) {
return a2;
} else if (TAG(s2046) == 1) {
return F_Chk_dreport_dclose_dadd(a0, FLD(s2046, 1), a2, F_Chk_dreport_dusers(a0, FLD(s2046, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dclose(V *a) { (void)a; return F_Chk_dreport_dclose(a[0], a[1], a[2]); }
static V F_Chk_dreport_dusers(V a0, V a1) {
top:;
V s2047 = a0;
if ((s2047) == IMM(0)) {
return IMM(0);
} else if (TAG(s2047) == 1) {
return F_Chk_dreport_dusers_dif(FLD(FLD(s2047, 0), 1), F_Chk_dreport_dusers(FLD(s2047, 1), a1), F_String_deq(FLD(FLD(s2047, 0), 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dusers(V *a) { (void)a; return F_Chk_dreport_dusers(a[0], a[1]); }
static V F_Chk_dreport_dusers_dif(V a0, V a1, V a2) {
top:;
V s2048 = a2;
if ((s2048) == IMM(1)) {
return C2(1, a0, a1);
} else if ((s2048) == IMM(0)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dusers_dif(V *a) { (void)a; return F_Chk_dreport_dusers_dif(a[0], a[1], a[2]); }
static V F_Chk_dreport_dclose_dadd(V a0, V a1, V a2, V a3) {
top:;
V s2049 = a3;
if ((s2049) == IMM(0)) {
return F_Chk_dreport_dclose(a0, a1, a2);
} else if (TAG(s2049) == 1) {
return F_Chk_dreport_dclose_dadd_dif(a0, a1, a2, FLD(s2049, 0), FLD(s2049, 1), F_Chk_dStr_dhas(a2, FLD(s2049, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dclose_dadd(V *a) { (void)a; return F_Chk_dreport_dclose_dadd(a[0], a[1], a[2], a[3]); }
static V F_Chk_dreport_dclose_dadd_dif(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2050 = a5;
if ((s2050) == IMM(1)) {
return F_Chk_dreport_dclose_dadd(a0, a1, a2, a4);
} else if ((s2050) == IMM(0)) {
return F_Chk_dreport_dclose_dadd(a0, F_List_dappend(a1, C2(1, a3, IMM(0))), C2(1, a3, a2), a4);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dclose_dadd_dif(V *a) { (void)a; return F_Chk_dreport_dclose_dadd_dif(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dStr_dfilter__in(V a0, V a1) {
top:;
V s2051 = a0;
if ((s2051) == IMM(0)) {
return IMM(0);
} else if (TAG(s2051) == 1) {
return F_Chk_dStr_dfilter__in_dif(FLD(s2051, 0), F_Chk_dStr_dfilter__in(FLD(s2051, 1), a1), F_Chk_dStr_dhas(a1, FLD(s2051, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dfilter__in(V *a) { (void)a; return F_Chk_dStr_dfilter__in(a[0], a[1]); }
static V F_Chk_dStr_dfilter__in_dif(V a0, V a1, V a2) {
top:;
V s2052 = a2;
if ((s2052) == IMM(1)) {
return C2(1, a0, a1);
} else if ((s2052) == IMM(0)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dfilter__in_dif(V *a) { (void)a; return F_Chk_dStr_dfilter__in_dif(a[0], a[1], a[2]); }
static V F_Chk_dBook_dtlds(V a0) {
top:;
V v2053 = a0;
return FLD(v2053, 0);
}
static V W_Chk_dBook_dtlds(V *a) { (void)a; return F_Chk_dBook_dtlds(a[0]); }
static V F_Map_dkeys(V a2) {
top:;
return F_Map_dkeys_dgo(a2, IMM(0));
}
static V W_Map_dkeys(V *a) { (void)a; return F_Map_dkeys(a[2]); }
static V F_Map_dkeys_dgo(V a2, V a3) {
top:;
V s2054 = a2;
if ((s2054) == IMM(0)) {
return a3;
} else if (TAG(s2054) == 1) {
return C2(1, FLD(s2054, 0), a3);
} else if (TAG(s2054) == 2) {
{ V t0 = FLD(s2054, 1); V t1 = F_Map_dkeys_dgo(FLD(s2054, 2), a3); a2 = t0; a3 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Map_dkeys_dgo(V *a) { (void)a; return F_Map_dkeys_dgo(a[2], a[3]); }
static V F_Chk_dreport_dbad__all(V a0, V a1) {
top:;
V s2055 = a1;
if ((s2055) == IMM(0)) {
return IMM(0);
} else if (TAG(s2055) == 1) {
return F_Chk_dStr_dfilter__in_dif(FLD(s2055, 0), F_Chk_dreport_dbad__all(a0, FLD(s2055, 1)), F_Chk_dTld_dbad(F_Chk_dbook__tld(a0, FLD(s2055, 0))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dreport_dbad__all(V *a) { (void)a; return F_Chk_dreport_dbad__all(a[0], a[1]); }
static V F_Chk_dTld_dbad(V a0) {
top:;
V s2056 = a0;
if (TAG(s2056) == 1 && TAG(FLD(s2056, 0)) == 0) {
return F_Bool_dor(FLD(FLD(s2056, 0), 4), F_Bool_dand(F_Maybe_dis__some(FLD(FLD(s2056, 0), 6)), F_Bool_dnot(FLD(FLD(s2056, 0), 5))));
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dbad(V *a) { (void)a; return F_Chk_dTld_dbad(a[0]); }
static V F_Chk_dbook__order(V a0) {
top:;
V v2057 = a0;
return F_List_dreverse(FLD(v2057, 2));
}
static V W_Chk_dbook__order(V *a) { (void)a; return F_Chk_dbook__order(a[0]); }
static V F_Chk_dList_ddrop__str2(V a0, V a1) {
top:;
V s2058 = a0;
V s2059 = a1;
if ((s2059) == 0) {
return s2058;
} else if (TAG(s2058) == 1 && nat_ge(s2059, 1)) {
{ V t0 = FLD(s2058, 1); V t1 = nat_subk(s2059, 1); a0 = t0; a1 = t1; goto top; }
} else if ((s2058) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dList_ddrop__str2(V *a) { (void)a; return F_Chk_dList_ddrop__str2(a[0], a[1]); }
static V F_Chk_dStr_dunique(V a0, V a1) {
top:;
V s2060 = a0;
if ((s2060) == IMM(0)) {
return IMM(0);
} else if (TAG(s2060) == 1) {
return F_Chk_dStr_dunique_dif(FLD(s2060, 0), FLD(s2060, 1), a1, F_Chk_dStr_dhas(a1, FLD(s2060, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dunique(V *a) { (void)a; return F_Chk_dStr_dunique(a[0], a[1]); }
static V F_Chk_dStr_dunique_dif(V a0, V a1, V a2, V a3) {
top:;
V s2061 = a3;
if ((s2061) == IMM(1)) {
return F_Chk_dStr_dunique(a1, a2);
} else if ((s2061) == IMM(0)) {
return C2(1, a0, F_Chk_dStr_dunique(a1, C2(1, a0, a2)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dunique_dif(V *a) { (void)a; return F_Chk_dStr_dunique_dif(a[0], a[1], a[2], a[3]); }
static V S2062(void) { static V c; return STRC(c, ""); }
static V L2063(V *a) {
return F_Main_dcheck_dfin(a[0]);
}
static V F_Main_dcheck(V a0, V a1) {
top:;
return F_IO_dbind(F_Main_dchk_dload(64u, a0, a1, S2062(), IMM(0), C3(0, F_Chk_dbook__nil(), IMM(0), 0u)), mk_clo(L2063, 1, 0, 0));
}
static V W_Main_dcheck(V *a) { (void)a; return F_Main_dcheck(a[0], a[1]); }
static V F_Main_dcheck_dfin(V a0) {
top:;
V v2064 = a0;
return F_Main_dcheck_dres(FLD(v2064, 2), F_Chk_dcheck__book(FLD(v2064, 0)));
}
static V W_Main_dcheck_dfin(V *a) { (void)a; return F_Main_dcheck_dfin(a[0]); }
static V F_Chk_dcheck__book(V a0) {
top:;
V v2065 = a0;
return F_Chk_dcheck__book_dfin(apply(F_Chk_dbook__valid(F_Chk_dbook__order(v2065), v2065), F_Chk_dbook__reset(v2065)));
}
static V W_Chk_dcheck__book(V *a) { (void)a; return F_Chk_dcheck__book(a[0]); }
static V F_Chk_dbook__reset(V a0) {
top:;
V v2066 = a0;
return CN(0, 7, (V[]){IMM(0), IMM(0), FLD(v2066, 2), FLD(v2066, 3), FLD(v2066, 4), FLD(v2066, 5), FLD(v2066, 6)});
}
static V W_Chk_dbook__reset(V *a) { (void)a; return F_Chk_dbook__reset(a[0]); }
static V L2068(V *a) {
return F_Chk_dbook__valid(a[1], a[0]);
}
static V F_Chk_dbook__valid(V a0, V a1) {
top:;
V s2067 = a0;
if ((s2067) == IMM(0)) {
return F_Chk_dK_dpure(IMM(0));
} else if (TAG(s2067) == 1) {
return F_Chk_dK_dbind(F_Chk_dbook__valid_done(FLD(s2067, 0), F_Maybe_ddefault(F_Chk_dbook__tld(a1, FLD(s2067, 0)), CN(1, 5, (V[]){0u, 0u, C1(8, IMM(0)), IMM(0), IMM(0)})), F_Bool_dnot(F_Chk_dStr_dhas(FLD(s2067, 1), FLD(s2067, 0)))), mk_clo(L2068, 3, 2, (V[]){a1, FLD(s2067, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dbook__valid(V *a) { (void)a; return F_Chk_dbook__valid(a[0], a[1]); }
static V L2071(V *a) {
return F_Chk_dvalid_dadt(a[3], a[2], a[1], a[0]);
}
static V L2070(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dset__book(F_Chk_dbook__set__ctrs(F_Chk_dbook__set(a[5], a[4], a[3]), a[2])), mk_clo(L2071, 5, 4, (V[]){a[2], a[0], a[1], a[4]}));
}
static V F_Chk_dbook__valid_done(V a0, V a1, V a2) {
top:;
V s2069 = a1;
if (TAG(s2069) == 1) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2070, 6, 5, (V[]){FLD(s2069, 2), FLD(s2069, 0), FLD(s2069, 3), a1, a0}));
} else if (TAG(s2069) == 0) {
return F_Chk_dvalid_ddef(a0, a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dbook__valid_done(V *a) { (void)a; return F_Chk_dbook__valid_done(a[0], a[1], a[2]); }
static V L2080(V *a) {
return F_Chk_dK_dset__book(F_Chk_dbook__set(a[2], a[1], a[0]));
}
static V L2079(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2080, 3, 2, (V[]){a[0], a[1]}));
}
static V L2078(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dif(F_Maybe_dis__some(F_Chk_dTld_ddval(a[1])), F_Chk_ddef__check(a[0], a[1], 0u), F_Chk_dK_dpure(IMM(0))), mk_clo(L2079, 3, 2, (V[]){a[1], a[0]}));
}
static V L2077(V *a) {
return F_Chk_dK_dbind(F_Chk_dvalid_dforeign(a[1], a[0], F_Chk_dTld_dimps(a[0])), mk_clo(L2078, 3, 2, (V[]){a[1], a[0]}));
}
static V L2076(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(F_Chk_dCL_dof(a[0], F_Chk_dTld_ddu(a[1])), F_Chk_dTld_dt(a[1]), IMM(0), F_Chk_dtyp(IMM(1)), IMM(0), 0u), mk_clo(L2077, 3, 2, (V[]){a[1], a[0]}));
}
static V L2075(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Bool_dpick(a[2], a[1], F_Chk_dTld_ddec(a[1]))), mk_clo(L2076, 2, 1, (V[]){a[0]}));
}
static V L2074(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dset__book(F_Chk_dbook__set(a[3], a[2], F_Chk_dTld_ddec(a[1]))), mk_clo(L2075, 4, 3, (V[]){a[2], a[1], a[0]}));
}
static V L2073(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Bool_dpick(a[4], F_Chk_dbook__opened(a[3]), a[3])), mk_clo(L2074, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L2072(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Bool_dand(a[2], F_Chk_dTld_dis__law__open(a[1]))), mk_clo(L2073, 5, 4, (V[]){a[2], a[1], a[0], a[3]}));
}
static V F_Chk_dvalid_ddef(V a0, V a1, V a2) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2072, 4, 3, (V[]){a0, a1, a2}));
}
static V W_Chk_dvalid_ddef(V *a) { (void)a; return F_Chk_dvalid_ddef(a[0], a[1], a[2]); }
static V F_Chk_dbook__set(V a0, V a1, V a2) {
top:;
V v2081 = a0;
return CN(0, 7, (V[]){F_Map_dset(FLD(v2081, 0), a1, a2), FLD(v2081, 1), FLD(v2081, 2), FLD(v2081, 3), FLD(v2081, 4), FLD(v2081, 5), FLD(v2081, 6)});
}
static V W_Chk_dbook__set(V *a) { (void)a; return F_Chk_dbook__set(a[0], a[1], a[2]); }
static V L2082(V *a) {
return C1(1, C2(0, IMM(0), a[0]));
}
static V F_Chk_dK_dset__book(V a0) {
top:;
return mk_clo(L2082, 2, 1, (V[]){a0});
}
static V W_Chk_dK_dset__book(V *a) { (void)a; return F_Chk_dK_dset__book(a[0]); }
static V L2083(V *a) {
return C1(1, C2(0, a[0], a[0]));
}
static V F_Chk_dK_dbook(void) {
top:;
return mk_clo(L2083, 1, 0, 0);
}
static V W_Chk_dK_dbook(V *a) { (void)a; return F_Chk_dK_dbook(); }
static V L2084(V *a) {
return F_Chk_dK_dgo(apply(a[1], a[4]), a[0]);
}
static V F_Chk_dK_dbind(V a2, V a3) {
top:;
return mk_clo(L2084, 5, 4, (V[]){a3, a2, 0, 0});
}
static V W_Chk_dK_dbind(V *a) { (void)a; return F_Chk_dK_dbind(a[2], a[3]); }
static V F_Chk_dK_dgo(V a2, V a3) {
top:;
V s2085 = a2;
if (TAG(s2085) == 0) {
return C1(0, FLD(s2085, 0));
} else if (TAG(s2085) == 1) {
return F_Chk_dK_dgo_ddone(FLD(s2085, 0), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dK_dgo(V *a) { (void)a; return F_Chk_dK_dgo(a[2], a[3]); }
static V F_Chk_dK_dgo_ddone(V a2, V a3) {
top:;
V v2086 = a2;
return apply(apply(a3, FLD(v2086, 0)), FLD(v2086, 1));
}
static V W_Chk_dK_dgo_ddone(V *a) { (void)a; return F_Chk_dK_dgo_ddone(a[2], a[3]); }
static V L2087(V *a) {
return C1(1, C2(0, a[0], a[1]));
}
static V F_Chk_dK_dpure(V a1) {
top:;
return mk_clo(L2087, 2, 1, (V[]){a1});
}
static V W_Chk_dK_dpure(V *a) { (void)a; return F_Chk_dK_dpure(a[1]); }
static V L2090(V *a) {
return F_Chk_ddef__check_dgo(a[4], a[3], a[2], a[1], a[5], a[0], F_Nat_dis__gt(F_Chk_dTld_dx__of(a[3]), 0u));
}
static V L2089(V *a) {
return F_Chk_dK_dbind(F_Chk_ddef__check_dtmpl(a[3], F_Chk_dTld_dx__of(a[2]), C3(4, a[3], IMM(0), IMM(0)), F_Maybe_ddefault(F_Chk_dTld_ddval(a[2]), C1(18, IMM(0))), F_Chk_dTld_dt(a[2])), mk_clo(L2090, 6, 5, (V[]){a[0], a[4], a[1], a[2], a[3]}));
}
static V L2088(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dDom_dqs(F_Pair_dfst(F_Chk_dtele__unbind(a[3], F_Chk_dTld_dt(a[2]))))), mk_clo(L2089, 5, 4, (V[]){a[3], a[0], a[2], a[1]}));
}
static V F_Chk_ddef__check(V a0, V a1, V a2) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2088, 4, 3, (V[]){a2, a0, a1}));
}
static V W_Chk_ddef__check(V *a) { (void)a; return F_Chk_ddef__check(a[0], a[1], a[2]); }
static V F_Chk_dTld_dx__of(V a0) {
top:;
V s2091 = a0;
if (TAG(s2091) == 0) {
return FLD(s2091, 1);
} else {
return 0u;
}
}
static V W_Chk_dTld_dx__of(V *a) { (void)a; return F_Chk_dTld_dx__of(a[0]); }
static V L2095(V *a) {
return F_Chk_dK_dset__book(F_Bool_dpick(a[1], a[0], a[2]));
}
static V L2094(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2095, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_ddef__check_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2092 = a4;
V v2093 = FLD(v2092, 1);
return F_Chk_dK_dbind(F_Chk_dterm__check(CN(0, 6, (V[]){FLD(v2092, 0), F_Nat_dsub(F_Chk_dTld_ddn(a1), F_Chk_dTld_dx__of(a1)), a0, a3, F_Chk_dTld_ddu(a1), a2}), FLD(v2093, 0), IMM(1), FLD(v2093, 1), IMM(0), 0u), mk_clo(L2094, 3, 2, (V[]){a5, a6}));
}
static V W_Chk_ddef__check_dgo(V *a) { (void)a; return F_Chk_ddef__check_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dTld_ddu(V a0) {
top:;
V s2096 = a0;
if (TAG(s2096) == 0) {
return FLD(s2096, 4);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_ddu(V *a) { (void)a; return F_Chk_dTld_ddu(a[0]); }
static V F_Chk_dTld_ddn(V a0) {
top:;
V s2097 = a0;
if (TAG(s2097) == 0) {
return FLD(s2097, 0);
} else {
return 0u;
}
}
static V W_Chk_dTld_ddn(V *a) { (void)a; return F_Chk_dTld_ddn(a[0]); }
static V L2099(V *a) {
return F_Chk_dcheck_dlam(a[8], a[7], a[6], a[5], a[4], F_Chk_dterm__wnf(a[9], a[3]), a[2], a[3], a[1], a[0]);
}
static V L2100(V *a) {
return F_Chk_dcheck_dlet_dbody(a[9], a[8], a[7], a[6], a[5], a[4], a[3], a[2], a[1], a[0], a[10]);
}
static V L2101(V *a) {
return F_Chk_dcheck_dctr(a[7], a[6], a[5], a[4], F_Chk_dterm__wnf(a[8], a[3]), a[2], a[3], a[1], a[0]);
}
static V L2102(V *a) {
return F_Chk_dcheck_dlit(a[6], C2(16, a[5], a[4]), F_Chk_dterm__wnf(a[7], a[3]), a[2], a[3], a[1], a[0]);
}
static V L2103(V *a) {
return F_Chk_dcheck_delim(a[8], C4(17, a[7], a[6], a[5], a[4]), a[4], F_Chk_dterm__wnf(a[9], a[3]), a[2], a[3], a[1], a[0]);
}
static V L2104(V *a) {
return F_Chk_dcheck_delim(a[5], C1(18, a[4]), a[4], F_Chk_dterm__wnf(a[6], a[3]), a[2], a[3], a[1], a[0]);
}
static V L2105(V *a) {
return F_Chk_dcheck_drfl(a[4], a[3], F_Chk_dterm__wnf(a[5], a[2]), a[2], a[1], a[0]);
}
static V S2106(void) { static V c; return STRC(c, "TODO"); }
static V L2108(V *a) {
return F_Chk_dcheck_drwt(a[9], a[8], a[7], a[6], a[5], a[4], F_Chk_dterm__wnf(a[10], F_Chk_dIR_dty(a[4])), a[3], a[2], a[1], a[0]);
}
static V L2107(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2108, 11, 10, (V[]){a[0], a[1], a[2], a[3], a[9], a[4], a[5], a[6], a[7], a[8]}));
}
static V F_Chk_dterm__check(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2098 = a1;
if (TAG(s2098) == 1) {
{ V t0 = a0; V t1 = FLD(s2098, 2); V t2 = a2; V t3 = a3; V t4 = a4; V t5 = a5; a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; a5 = t5; goto top; }
} else if (TAG(s2098) == 12) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2099, 10, 9, (V[]){a5, a4, a2, a3, FLD(s2098, 4), FLD(s2098, 3), FLD(s2098, 2), FLD(s2098, 0), a0}));
} else if (TAG(s2098) == 6) {
return F_Chk_dK_dbind(F_Chk_dcheck_dlets(a0, FLD(s2098, 0), FLD(s2098, 2), FLD(s2098, 5), a2, a4, a4, a5, 0u, IMM(0)), mk_clo(L2100, 11, 10, (V[]){a5, a4, a3, a2, FLD(s2098, 5), FLD(s2098, 4), FLD(s2098, 3), FLD(s2098, 2), FLD(s2098, 0), a0}));
} else if (TAG(s2098) == 15) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2101, 9, 8, (V[]){a5, a4, a2, a3, FLD(s2098, 2), FLD(s2098, 1), FLD(s2098, 0), a0}));
} else if (TAG(s2098) == 16) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2102, 8, 7, (V[]){a5, a4, a2, a3, FLD(s2098, 1), FLD(s2098, 0), a0}));
} else if (TAG(s2098) == 17) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2103, 10, 9, (V[]){a5, a4, a2, a3, FLD(s2098, 3), FLD(s2098, 2), FLD(s2098, 1), FLD(s2098, 0), a0}));
} else if (TAG(s2098) == 18) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2104, 7, 6, (V[]){a5, a4, a2, a3, FLD(s2098, 0), a0}));
} else if (TAG(s2098) == 20) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2105, 6, 5, (V[]){a5, a4, a3, FLD(s2098, 0), a0}));
} else if (TAG(s2098) == 22) {
return F_Chk_dK_dif(F_String_deq(FLD(s2098, 0), S2106()), F_Chk_dK_dpure(IMM(0)), F_Chk_dK_derr(a4, C1(2, a3), C1(2, C2(22, FLD(s2098, 0), FLD(s2098, 1))), FLD(s2098, 1), F_Chk_dCL_ddn(a0)));
} else if (TAG(s2098) == 21) {
return F_Chk_dK_dbind(F_Chk_dterm__infer(a0, FLD(s2098, 0), a2, a4, a5, IMM(0)), mk_clo(L2107, 10, 9, (V[]){a5, a4, a3, a2, FLD(s2098, 3), FLD(s2098, 2), FLD(s2098, 1), FLD(s2098, 0), a0}));
} else {
return F_Chk_dcheck_dinfer(a0, s2098, a2, a3, a4, a5);
}
}
static V W_Chk_dterm__check(V *a) { (void)a; return F_Chk_dterm__check(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L2110(V *a) {
return F_Chk_dcheck_dinfer_dcmp(a[5], a[4], a[3], a[2], a[1], a[0], F_Chk_dterm__compare(IMM(1), a[6], F_Chk_dIR_dty(a[3]), a[2], a[0]));
}
static V L2109(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2110, 7, 6, (V[]){a[0], a[1], a[2], a[5], a[3], a[4]}));
}
static V F_Chk_dcheck_dinfer(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dK_dbind(F_Chk_dterm__infer(a0, a1, a2, a4, a5, IMM(0)), mk_clo(L2109, 6, 5, (V[]){a5, a4, a3, a1, a0}));
}
static V W_Chk_dcheck_dinfer(V *a) { (void)a; return F_Chk_dcheck_dinfer(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dIR_dty(V a0) {
top:;
V v2111 = a0;
return FLD(v2111, 0);
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
V s2112 = a0;
if (TAG(s2112) == 12) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__lam(V *a) { (void)a; return F_Chk_dTm_dis__lam(a[0]); }
static V F_Chk_dcmp_dlam(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2113 = a5;
if ((s2113) == IMM(1)) {
V v2114 = C3(0, F_Chk_dTm_dlam__k(a2, a3), a4, IMM(0));
return F_Chk_dterm__compare(a0, a1, F_Chk_dterm__apply1(a1, a2, v2114), F_Chk_dterm__apply1(a1, a3, v2114), F_U32_dinc(a4));
} else if ((s2113) == IMM(0)) {
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
V s2115 = a0;
if (TAG(s2115) == 15) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__ctr(V *a) { (void)a; return F_Chk_dTm_dis__ctr(a[0]); }
static V F_Chk_dTm_dis__lit(V a0) {
top:;
V s2116 = a0;
if (TAG(s2116) == 16) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__lit(V *a) { (void)a; return F_Chk_dTm_dis__lit(a[0]); }
static V L2119(V *a) {
return F_Chk_dterm__compare(IMM(0), a[3], a[2], a[1], a[0]);
}
static V L2122(V *a) {
return F_Chk_dterm__compare(a[5], a[4], F_Chk_dclo__apply(a[4], a[3], C2(1, a[2], IMM(0))), F_Chk_dclo__apply(a[4], a[1], C2(1, a[2], IMM(0))), F_U32_dinc(a[0]));
}
static V L2121(V *a) {
return F_Chk_dLazy_dand(F_Chk_dterm__compare(a[7], a[6], a[5], a[4], a[3]), mk_clo(L2122, 7, 6, (V[]){a[3], a[0], a[1], a[2], a[6], a[7]}));
}
static V L2123(V *a) {
return F_Chk_dterm__compare(IMM(0), a[3], a[2], a[1], a[0]);
}
static V L2126(V *a) {
return F_Chk_dcmps(a[3], a[2], a[1], a[0]);
}
static V L2125(V *a) {
return F_Chk_dLazy_dand(F_Chk_dStr_dsubset(a[5], a[4]), mk_clo(L2126, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L2124(V *a) {
return F_Chk_dLazy_dand(F_Bool_dor(a[6], F_Nat_dis__eq(F_List_dlength(a[5]), F_List_dlength(a[4]))), mk_clo(L2125, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[5], a[4]}));
}
static V L2127(V *a) {
return F_Chk_dcmps(a[3], a[2], a[1], a[0]);
}
static V L2129(V *a) {
return F_Chk_dterm__compare(IMM(0), a[3], a[2], a[1], a[0]);
}
static V L2128(V *a) {
return F_Chk_dLazy_dand(F_Chk_dterm__compare(IMM(0), a[5], a[4], a[3], a[2]), mk_clo(L2129, 5, 4, (V[]){a[2], a[0], a[1], a[5]}));
}
static V L2131(V *a) {
return F_Chk_dterm__compare(IMM(0), a[3], a[2], a[1], a[0]);
}
static V L2130(V *a) {
return F_Chk_dLazy_dand(F_Chk_dterm__compare(IMM(0), a[5], a[4], a[3], a[2]), mk_clo(L2131, 5, 4, (V[]){a[2], a[0], a[1], a[5]}));
}
static V L2133(V *a) {
return F_Chk_dterm__compare(IMM(0), a[3], a[2], a[1], a[0]);
}
static V L2132(V *a) {
return F_Chk_dLazy_dand(F_Chk_dterm__compare(IMM(0), a[5], a[4], a[3], a[2]), mk_clo(L2133, 5, 4, (V[]){a[2], a[0], a[1], a[5]}));
}
static V F_Chk_dcmp_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2117 = a2;
V s2118 = a3;
if (TAG(s2117) == 0 && TAG(s2118) == 0) {
return F_U32_dis__eq(FLD(s2117, 1), FLD(s2118, 1));
} else if (TAG(s2117) == 4 && TAG(s2118) == 4) {
return F_String_deq(FLD(s2117, 0), FLD(s2118, 0));
} else if (TAG(s2117) == 7 && TAG(s2118) == 7) {
return F_Chk_dcmp_dtyp(a0, a1, FLD(s2117, 0), FLD(s2118, 0), a4);
} else if (TAG(s2117) == 8 && TAG(s2118) == 8) {
return IMM(1);
} else if (TAG(s2117) == 9 && TAG(s2118) == 9) {
return F_Chk_dQ_deq(FLD(s2117, 0), FLD(s2118, 0));
} else if (TAG(s2117) == 10 && TAG(s2118) == 10) {
return F_Chk_dLazy_dand(F_Chk_dterm__compare(IMM(0), a1, FLD(s2117, 0), FLD(s2118, 0), a4), mk_clo(L2119, 5, 4, (V[]){a4, FLD(s2118, 1), FLD(s2117, 1), a1}));
} else if (TAG(s2117) == 11 && TAG(s2118) == 11) {
V v2120 = C3(0, FLD(s2117, 1), a4, IMM(0));
return F_Chk_dLazy_dand(F_Chk_dQ_deq(FLD(s2117, 0), FLD(s2118, 0)), mk_clo(L2121, 9, 8, (V[]){FLD(s2118, 4), v2120, FLD(s2117, 4), a4, FLD(s2117, 3), FLD(s2118, 3), a1, a0}));
} else if (TAG(s2117) == 13 && TAG(s2118) == 13) {
return F_Chk_dLazy_dand(F_Chk_dterm__compare(IMM(0), a1, FLD(s2117, 0), FLD(s2118, 0), a4), mk_clo(L2123, 5, 4, (V[]){a4, FLD(s2118, 1), FLD(s2117, 1), a1}));
} else if (TAG(s2117) == 14 && TAG(s2118) == 14) {
return F_Chk_dLazy_dand(F_Bool_dand(F_String_deq(FLD(s2117, 0), FLD(s2118, 0)), F_Nat_dis__eq(F_List_dlength(FLD(s2117, 1)), F_List_dlength(FLD(s2118, 1)))), mk_clo(L2124, 8, 7, (V[]){a4, a1, FLD(s2118, 1), FLD(s2117, 1), FLD(s2118, 3), FLD(s2117, 3), a0}));
} else if (TAG(s2117) == 15 && TAG(s2118) == 15) {
return F_Chk_dLazy_dand(F_Bool_dand(F_String_deq(FLD(s2117, 0), FLD(s2118, 0)), F_Nat_dis__eq(F_List_dlength(FLD(s2117, 1)), F_List_dlength(FLD(s2118, 1)))), mk_clo(L2127, 5, 4, (V[]){a4, a1, FLD(s2118, 1), FLD(s2117, 1)}));
} else if (TAG(s2117) == 16 && TAG(FLD(s2117, 0)) == 0 && TAG(s2118) == 16 && TAG(FLD(s2118, 0)) == 0) {
return F_Nat_dis__eq(FLD(FLD(s2117, 0), 0), FLD(FLD(s2118, 0), 0));
} else if (TAG(s2117) == 16 && TAG(FLD(s2117, 0)) == 1 && TAG(s2118) == 16 && TAG(FLD(s2118, 0)) == 1) {
return F_String_deq(FLD(FLD(s2117, 0), 0), FLD(FLD(s2118, 0), 0));
} else if (TAG(s2117) == 17 && TAG(s2118) == 17) {
return F_Chk_dLazy_dand(F_String_deq(FLD(s2117, 0), FLD(s2118, 0)), mk_clo(L2128, 7, 6, (V[]){FLD(s2118, 2), FLD(s2117, 2), a4, FLD(s2118, 1), FLD(s2117, 1), a1}));
} else if (TAG(s2117) == 18 && TAG(s2118) == 18) {
return IMM(1);
} else if (TAG(s2117) == 19 && TAG(s2118) == 19) {
return F_Chk_dLazy_dand(F_Chk_dterm__compare(IMM(0), a1, FLD(s2117, 0), FLD(s2118, 0), a4), mk_clo(L2130, 7, 6, (V[]){FLD(s2118, 2), FLD(s2117, 2), a4, FLD(s2118, 1), FLD(s2117, 1), a1}));
} else if (TAG(s2117) == 20 && TAG(s2118) == 20) {
return IMM(1);
} else if (TAG(s2117) == 22 && TAG(s2118) == 22) {
return F_String_deq(FLD(s2117, 0), FLD(s2118, 0));
} else if (TAG(s2117) == 21 && TAG(s2118) == 21) {
return F_Chk_dLazy_dand(F_Chk_dterm__compare(IMM(0), a1, FLD(s2117, 0), FLD(s2118, 0), a4), mk_clo(L2132, 7, 6, (V[]){FLD(s2118, 2), FLD(s2117, 2), a4, FLD(s2118, 1), FLD(s2117, 1), a1}));
} else {
return IMM(0);
}
}
static V W_Chk_dcmp_dgo(V *a) { (void)a; return F_Chk_dcmp_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dLazy_dand(V a0, V a1) {
top:;
V s2134 = a0;
if ((s2134) == IMM(1)) {
return apply(a1, IMM(0));
} else if ((s2134) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dLazy_dand(V *a) { (void)a; return F_Chk_dLazy_dand(a[0], a[1]); }
static V L2137(V *a) {
return F_Chk_dcmps(a[3], a[2], a[1], a[0]);
}
static V F_Chk_dcmps(V a0, V a1, V a2, V a3) {
top:;
V s2135 = a0;
V s2136 = a1;
if (TAG(s2135) == 1 && TAG(s2136) == 1) {
return F_Chk_dLazy_dand(F_Chk_dterm__compare(IMM(0), a2, FLD(s2135, 0), FLD(s2136, 0), a3), mk_clo(L2137, 5, 4, (V[]){a3, a2, FLD(s2136, 1), FLD(s2135, 1)}));
} else if ((s2135) == IMM(0) && (s2136) == IMM(0)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dcmps(V *a) { (void)a; return F_Chk_dcmps(a[0], a[1], a[2], a[3]); }
static V L2139(V *a) {
return F_Chk_dStr_dsubset(a[1], a[0]);
}
static V F_Chk_dStr_dsubset(V a0, V a1) {
top:;
V s2138 = a0;
if ((s2138) == IMM(0)) {
return IMM(1);
} else if (TAG(s2138) == 1) {
return F_Chk_dLazy_dand(F_Chk_dStr_dhas(a1, FLD(s2138, 0)), mk_clo(L2139, 3, 2, (V[]){a1, FLD(s2138, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dsubset(V *a) { (void)a; return F_Chk_dStr_dsubset(a[0], a[1]); }
static V F_Chk_dQ_deq(V a0, V a1) {
top:;
V s2140 = a0;
V s2141 = a1;
if ((s2140) == IMM(0) && (s2141) == IMM(0)) {
return IMM(1);
} else if ((s2140) == IMM(1) && (s2141) == IMM(1)) {
return IMM(1);
} else if ((s2140) == IMM(2) && (s2141) == IMM(2)) {
return IMM(1);
} else if ((s2140) == IMM(3) && (s2141) == IMM(3)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dQ_deq(V *a) { (void)a; return F_Chk_dQ_deq(a[0], a[1]); }
static V F_Chk_dcmp_dtyp(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2142 = a0;
if ((s2142) == IMM(0)) {
return F_Chk_dterm__compare(IMM(0), a1, a2, a3, a4);
} else if ((s2142) == IMM(1)) {
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
V s2143 = a0;
if (TAG(s2143) == 9 && (FLD(s2143, 0)) == IMM(2)) {
return IMM(0);
} else if (TAG(s2143) == 9) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__qua__not__many(V *a) { (void)a; return F_Chk_dTm_dis__qua__not__many(a[0]); }
static V F_Chk_dTm_dis__many(V a0) {
top:;
V s2144 = a0;
if (TAG(s2144) == 9 && (FLD(s2144, 0)) == IMM(2)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__many(V *a) { (void)a; return F_Chk_dTm_dis__many(a[0]); }
static V F_Chk_dcmp_dkind_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2145 = a4;
if ((s2145) == IMM(1)) {
return IMM(1);
} else if ((s2145) == IMM(0)) {
return F_Chk_dcmp_dkind_dmin(a0, a1, a2, a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcmp_dkind_dgo(V *a) { (void)a; return F_Chk_dcmp_dkind_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V L2147(V *a) {
return F_Chk_dterm__compare(IMM(1), a[3], C2(7, a[2], IMM(0)), C2(7, a[1], IMM(0)), a[0]);
}
static V F_Chk_dcmp_dkind_dmin(V a0, V a1, V a2, V a3) {
top:;
V s2146 = a1;
if (TAG(s2146) == 10) {
return F_Chk_dLazy_dand(F_Chk_dterm__compare(IMM(1), a0, C2(7, FLD(s2146, 0), IMM(0)), C2(7, a2, IMM(0)), a3), mk_clo(L2147, 5, 4, (V[]){a3, a2, FLD(s2146, 1), a0}));
} else {
return F_Chk_dcmp_dkind_drmin(a0, s2146, a2, a3);
}
}
static V W_Chk_dcmp_dkind_dmin(V *a) { (void)a; return F_Chk_dcmp_dkind_dmin(a[0], a[1], a[2], a[3]); }
static V L2149(V *a) {
return F_Chk_dterm__compare(IMM(1), a[3], C2(7, a[2], IMM(0)), C2(7, a[1], IMM(0)), a[0]);
}
static V F_Chk_dcmp_dkind_drmin(V a0, V a1, V a2, V a3) {
top:;
V s2148 = a2;
if (TAG(s2148) == 10) {
return F_Chk_dLazy_dor(F_Chk_dterm__compare(IMM(1), a0, C2(7, a1, IMM(0)), C2(7, FLD(s2148, 0), IMM(0)), a3), mk_clo(L2149, 5, 4, (V[]){a3, FLD(s2148, 1), a1, a0}));
} else {
return F_Chk_dterm__compare(IMM(1), a0, a1, s2148, a3);
}
}
static V W_Chk_dcmp_dkind_drmin(V *a) { (void)a; return F_Chk_dcmp_dkind_drmin(a[0], a[1], a[2], a[3]); }
static V F_Chk_dterm__apply1(V a0, V a1, V a2) {
top:;
return F_Chk_dterm__apply(a0, a1, a2, IMM(0));
}
static V W_Chk_dterm__apply1(V *a) { (void)a; return F_Chk_dterm__apply1(a[0], a[1], a[2]); }
static V S2152(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dTm_dlam__k(V a0, V a1) {
top:;
V s2150 = a0;
V s2151 = a1;
if (TAG(s2150) == 12) {
return FLD(s2150, 0);
} else if (TAG(s2151) == 12) {
return FLD(s2151, 0);
} else {
return S2152();
}
}
static V W_Chk_dTm_dlam__k(V *a) { (void)a; return F_Chk_dTm_dlam__k(a[0], a[1]); }
static V F_Chk_dcheck_dinfer_dcmp(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2153 = a2;
V s2154 = a6;
if ((s2154) == IMM(1)) {
return F_Chk_dK_dpure(FLD(v2153, 1));
} else if ((s2154) == IMM(0)) {
return F_Chk_dK_derr(a4, C1(2, a3), C1(2, FLD(v2153, 0)), F_Chk_dTm_dspan(a1), F_Chk_dCL_ddn(a0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcheck_dinfer_dcmp(V *a) { (void)a; return F_Chk_dcheck_dinfer_dcmp(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dCL_ddn(V a0) {
top:;
V v2155 = a0;
return FLD(v2155, 2);
}
static V W_Chk_dCL_ddn(V *a) { (void)a; return F_Chk_dCL_ddn(a[0]); }
static V L2156(V *a) {
return C1(0, F_Chk_derr(a[5], a[4], a[3], a[2], a[1], a[0]));
}
static V F_Chk_dK_derr(V a1, V a2, V a3, V a4, V a5) {
top:;
return mk_clo(L2156, 6, 5, (V[]){a5, a4, a3, a2, a1});
}
static V W_Chk_dK_derr(V *a) { (void)a; return F_Chk_dK_derr(a[1], a[2], a[3], a[4], a[5]); }
static V S2157(void) { static V c; return STRC(c, ""); }
static V F_Chk_derr(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return CN(0, 7, (V[]){a0, a1, a2, a3, a4, a5, S2157()});
}
static V W_Chk_derr(V *a) { (void)a; return F_Chk_derr(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L2159(V *a) {
return F_Chk_dinfer_dref(a[7], a[6], a[5], a[4], F_Chk_dbook__tld(a[8], a[6]), a[3], a[2], a[1], a[0]);
}
static V L2160(V *a) {
return F_Chk_dK_dpure(C3(0, F_Chk_dtyp(IMM(1)), IMM(0), 0u));
}
static V L2162(V *a) {
return F_Chk_dK_dpure(C3(0, C1(8, a[1]), F_Chk_duses__add(a[0], a[2]), 0u));
}
static V L2161(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[5], a[4], a[3], C1(8, a[2]), a[1], a[0]), mk_clo(L2162, 3, 2, (V[]){a[6], a[2]}));
}
static V L2165(V *a) {
return F_Chk_dK_dpure(C3(0, F_Chk_dtyp(IMM(1)), IMM(0), 0u));
}
static V L2164(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[6], F_Chk_dclo__apply(a[7], a[5], C2(1, C3(0, a[4], a[3], IMM(0)), IMM(0))), IMM(0), F_Chk_dtyp(IMM(1)), F_Chk_dctx__bind(a[2], a[3], a[1], a[4], a[0]), F_U32_dinc(a[3])), mk_clo(L2165, 1, 0, 0));
}
static V L2163(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2164, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L2166(V *a) {
return F_Chk_dinfer_dapp(a[5], a[6], a[4], a[3], a[2], a[1], a[0]);
}
static V L2167(V *a) {
return F_Chk_dinfer_dadt(a[6], a[7], a[5], a[4], a[3], a[2], a[1], a[0]);
}
static V L2170(V *a) {
return F_Chk_dK_dpure(C3(0, F_Chk_dtyp(IMM(2)), IMM(0), 0u));
}
static V L2169(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[4], a[3], IMM(0), a[2], a[1], a[0]), mk_clo(L2170, 1, 0, 0));
}
static V L2168(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[5], a[4], IMM(0), a[3], a[2], a[1]), mk_clo(L2169, 6, 5, (V[]){a[1], a[2], a[3], a[0], a[5]}));
}
static V L2172(V *a) {
return F_Chk_dK_dpure(C3(0, a[0], a[1], 0u));
}
static V L2171(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[5], a[4], a[3], a[2], a[1], a[0]), mk_clo(L2172, 2, 1, (V[]){a[2]}));
}
static V F_Chk_dterm__infer(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2158 = a1;
if (TAG(s2158) == 1) {
{ V t0 = a0; V t1 = FLD(s2158, 2); V t2 = a2; V t3 = a3; V t4 = a4; V t5 = a5; a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; a5 = t5; goto top; }
} else if (TAG(s2158) == 0) {
return F_Chk_dinfer_dvar(C3(0, FLD(s2158, 0), FLD(s2158, 1), FLD(s2158, 2)), FLD(s2158, 1), a2, a3, FLD(s2158, 2), a0);
} else if (TAG(s2158) == 3) {
return F_Chk_dinfer_dvar(C3(0, FLD(s2158, 0), FLD(s2158, 1), FLD(s2158, 2)), FLD(s2158, 1), a2, a3, FLD(s2158, 2), a0);
} else if (TAG(s2158) == 4) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2159, 9, 8, (V[]){a5, a4, a3, a2, FLD(s2158, 2), FLD(s2158, 1), FLD(s2158, 0), a0}));
} else if (TAG(s2158) == 7) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a0, FLD(s2158, 0), IMM(0), C1(8, FLD(s2158, 1)), a3, a4), mk_clo(L2160, 1, 0, 0));
} else if (TAG(s2158) == 8) {
return F_Chk_dK_dpure(C3(0, F_Chk_dtyp(IMM(1)), IMM(0), 0u));
} else if (TAG(s2158) == 9) {
return F_Chk_dK_dpure(C3(0, C1(8, FLD(s2158, 1)), IMM(0), 0u));
} else if (TAG(s2158) == 10) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a0, FLD(s2158, 0), a2, C1(8, FLD(s2158, 2)), a3, a4), mk_clo(L2161, 7, 6, (V[]){a4, a3, FLD(s2158, 2), a2, FLD(s2158, 1), a0}));
} else if (TAG(s2158) == 11) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a0, FLD(s2158, 3), IMM(0), F_Chk_dtyp(F_Chk_dlhs__kind(a0, FLD(s2158, 0))), a3, a4), mk_clo(L2163, 8, 7, (V[]){FLD(s2158, 3), FLD(s2158, 0), a3, a4, FLD(s2158, 1), FLD(s2158, 4), a0}));
} else if (TAG(s2158) == 13) {
return F_Chk_dK_dbind(F_Chk_dterm__infer(a0, FLD(s2158, 0), a2, a3, a4, C2(1, FLD(s2158, 1), a5)), mk_clo(L2166, 7, 6, (V[]){FLD(s2158, 2), a4, a3, a2, FLD(s2158, 1), a0}));
} else if (TAG(s2158) == 14) {
return F_Chk_dK_dbind(F_Chk_dbook__adt(C4(14, FLD(s2158, 0), FLD(s2158, 1), FLD(s2158, 2), FLD(s2158, 3)), a3, F_Chk_dCL_ddn(a0)), mk_clo(L2167, 8, 7, (V[]){a4, a3, a2, FLD(s2158, 2), FLD(s2158, 1), FLD(s2158, 0), a0}));
} else if (TAG(s2158) == 19) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a0, FLD(s2158, 2), IMM(0), F_Chk_dtyp(IMM(1)), a3, a4), mk_clo(L2168, 7, 6, (V[]){FLD(s2158, 1), a4, a3, FLD(s2158, 2), FLD(s2158, 0), a0}));
} else if (TAG(s2158) == 23) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a0, FLD(s2158, 1), IMM(0), F_Chk_dtyp(IMM(1)), a3, a4), mk_clo(L2171, 7, 6, (V[]){a4, a3, FLD(s2158, 1), a2, FLD(s2158, 0), a0}));
} else {
return F_Chk_dinfer_dfail(a0, s2158, a3);
}
}
static V W_Chk_dterm__infer(V *a) { (void)a; return F_Chk_dterm__infer(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S2176(void) { static V c; return STRC(c, "a declared constructor"); }
static V S2177(void) { static V c; return STRC(c, "an annotated term (cannot infer)"); }
static V L2175(V *a) {
return F_Chk_dK_derr(a[2], C1(1, F_Bool_dpick(a[3], S2176(), S2177())), C1(2, a[1]), F_Chk_dTm_dspan(a[1]), F_Chk_dCL_ddn(a[0]));
}
static V L2174(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Bool_dand(F_Chk_dTm_dis__ctr(a[4]), F_Bool_dnot(F_Maybe_dis__some(F_Chk_dbook__ctr(a[3], F_Chk_dTm_dname(a[4])))))), mk_clo(L2175, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L2173(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dlit__ctr(a[2])), mk_clo(L2174, 5, 4, (V[]){a[0], a[2], a[1], a[3]}));
}
static V F_Chk_dinfer_dfail(V a0, V a1, V a2) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2173, 4, 3, (V[]){a0, a2, a1}));
}
static V W_Chk_dinfer_dfail(V *a) { (void)a; return F_Chk_dinfer_dfail(a[0], a[1], a[2]); }
static V S2179(void) { static V c; return STRC(c, ""); }
static V F_Chk_dTm_dname(V a0) {
top:;
V s2178 = a0;
if (TAG(s2178) == 0) {
return FLD(s2178, 0);
} else if (TAG(s2178) == 3) {
return FLD(s2178, 0);
} else if (TAG(s2178) == 2) {
return FLD(s2178, 0);
} else if (TAG(s2178) == 4) {
return FLD(s2178, 0);
} else if (TAG(s2178) == 14) {
return FLD(s2178, 0);
} else if (TAG(s2178) == 15) {
return FLD(s2178, 0);
} else {
return S2179();
}
}
static V W_Chk_dTm_dname(V *a) { (void)a; return F_Chk_dTm_dname(a[0]); }
static V F_Chk_dbook__ctr(V a0, V a1) {
top:;
V v2180 = a0;
return F_Chk_dMap_dfind(FLD(v2180, 1), a1);
}
static V W_Chk_dbook__ctr(V *a) { (void)a; return F_Chk_dbook__ctr(a[0], a[1]); }
static V F_Chk_dtyp(V a0) {
top:;
return C2(7, C2(9, a0, IMM(0)), IMM(0));
}
static V W_Chk_dtyp(V *a) { (void)a; return F_Chk_dtyp(a[0]); }
static V S2181(void) { static V c; return STRC(c, " with "); }
static V S2182(void) { static V c; return STRC(c, " parameter"); }
static V S2183(void) { static V c; return STRC(c, " parameters"); }
static V F_Chk_dinfer_dadt(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
return F_Chk_dK_dif(F_Nat_dis__eq(F_List_dlength(a3), F_Chk_dAD_dn(a1)), F_Chk_dinfer_dadt_dgo(a0, a1, a3, a4, a5, a6, a7), F_Chk_dK_derr(a6, C1(1, F_String_dappend(a2, F_String_dappend(S2181(), F_String_dappend(F_Nat_dshow(F_Chk_dAD_dn(a1)), F_Bool_dpick(F_Nat_dis__eq(F_Chk_dAD_dn(a1), 1u), S2182(), S2183()))))), C1(2, C4(14, a2, a3, a4, IMM(0))), a4, F_Chk_dCL_ddn(a0)));
}
static V W_Chk_dinfer_dadt(V *a) { (void)a; return F_Chk_dinfer_dadt(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V F_Chk_dAD_dn(V a0) {
top:;
V v2184 = a0;
return FLD(v2184, 0);
}
static V W_Chk_dAD_dn(V *a) { (void)a; return F_Chk_dAD_dn(a[0]); }
static V L2185(V *a) {
return F_Chk_dK_dpure(F_Chk_dinfer_dadt_dfin(a[0]));
}
static V F_Chk_dinfer_dadt_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
return F_Chk_dK_dbind(F_Chk_dtele__check(a0, F_Chk_dAD_dt(a1), a2, a4, a5, a6, a3, IMM(0)), mk_clo(L2185, 1, 0, 0));
}
static V W_Chk_dinfer_dadt_dgo(V *a) { (void)a; return F_Chk_dinfer_dadt_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dinfer_dadt_dfin(V a0) {
top:;
V v2186 = a0;
return C3(0, FLD(v2186, 1), FLD(v2186, 0), 0u);
}
static V W_Chk_dinfer_dadt_dfin(V *a) { (void)a; return F_Chk_dinfer_dadt_dfin(a[0]); }
static V F_Chk_dAD_dt(V a0) {
top:;
V v2187 = a0;
return FLD(v2187, 2);
}
static V W_Chk_dAD_dt(V *a) { (void)a; return F_Chk_dAD_dt(a[0]); }
static V L2191(V *a) {
return F_Chk_dtele__check(a[9], F_Chk_dclo__apply(a[10], F_Chk_dAll_db(a[8]), C2(1, a[7], IMM(0))), a[6], a[5], a[4], a[3], a[2], F_Chk_duses__add(a[1], a[0]));
}
static V L2190(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2191, 11, 10, (V[]){a[9], a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]}));
}
static V L2189(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[7], a[6], F_Chk_dquant__dem(F_Chk_dAll_dq(a[8]), a[5]), F_Chk_dAll_da(a[8]), a[4], a[3]), mk_clo(L2190, 10, 9, (V[]){a[0], a[1], a[3], a[4], a[5], a[2], a[6], a[8], a[7]}));
}
static V F_Chk_dtele__check(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s2188 = a2;
if ((s2188) == IMM(0)) {
return F_Chk_dK_dpure(C2(0, a7, a1));
} else if (TAG(s2188) == 1) {
return F_Chk_dK_dbind(F_Chk_dtele__head(a1, a4, F_Chk_dCL_ddn(a0), a6), mk_clo(L2189, 9, 8, (V[]){a7, a6, FLD(s2188, 1), a5, a4, a3, FLD(s2188, 0), a0}));
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
V s2192 = a2;
if ((s2192) == IMM(0)) {
return a1;
} else if (TAG(s2192) == 1) {
{ V t0 = a0; V t1 = F_Chk_duses__put(a0, FLD(s2192, 0), a1); V t2 = FLD(s2192, 1); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duses__merge(V *a) { (void)a; return F_Chk_duses__merge(a[0], a[1], a[2]); }
static V F_Chk_duses__put(V a0, V a1, V a2) {
top:;
V s2193 = a2;
if ((s2193) == IMM(0)) {
return C2(1, a1, IMM(0));
} else if (TAG(s2193) == 1) {
return F_Chk_duses__put_dif(a0, a1, FLD(FLD(s2193, 0), 0), FLD(FLD(s2193, 0), 1), FLD(s2193, 1), F_U32_dis__eq(F_Chk_dUs_di(a1), FLD(FLD(s2193, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duses__put(V *a) { (void)a; return F_Chk_duses__put(a[0], a[1], a[2]); }
static V F_Chk_dUs_di(V a0) {
top:;
V v2194 = a0;
return FLD(v2194, 0);
}
static V W_Chk_dUs_di(V *a) { (void)a; return F_Chk_dUs_di(a[0]); }
static V F_Chk_duses__put_dif(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2195 = a5;
if ((s2195) == IMM(1)) {
return C2(1, C2(0, a2, F_Bool_dpick(F_U32_dis__zero(a0), F_Chk_dquant__add(a3, F_Chk_dUs_dq(a1)), F_Chk_dquant__join(a3, F_Chk_dUs_dq(a1)))), a4);
} else if ((s2195) == IMM(0)) {
return C2(1, C2(0, a2, a3), F_Chk_duses__put(a0, a1, a4));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duses__put_dif(V *a) { (void)a; return F_Chk_duses__put_dif(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dUs_dq(V a0) {
top:;
V v2196 = a0;
return FLD(v2196, 1);
}
static V W_Chk_dUs_dq(V *a) { (void)a; return F_Chk_dUs_dq(a[0]); }
static V F_Chk_dquant__join(V a0, V a1) {
top:;
V s2197 = a0;
V s2198 = a1;
if ((s2197) == IMM(2)) {
return IMM(2);
} else if ((s2198) == IMM(2)) {
return IMM(2);
} else if ((s2197) == IMM(0)) {
return s2198;
} else {
return s2197;
}
}
static V W_Chk_dquant__join(V *a) { (void)a; return F_Chk_dquant__join(a[0], a[1]); }
static V F_Chk_dAll_da(V a0) {
top:;
V s2199 = a0;
if (TAG(s2199) == 11) {
return FLD(s2199, 3);
} else {
return s2199;
}
}
static V W_Chk_dAll_da(V *a) { (void)a; return F_Chk_dAll_da(a[0]); }
static V F_Chk_dAll_dq(V a0) {
top:;
V s2200 = a0;
if (TAG(s2200) == 11) {
return FLD(s2200, 0);
} else {
return IMM(1);
}
}
static V W_Chk_dAll_dq(V *a) { (void)a; return F_Chk_dAll_dq(a[0]); }
static V F_Chk_dquant__dem(V a0, V a1) {
top:;
V s2201 = a0;
if ((s2201) == IMM(0)) {
return IMM(0);
} else {
return a1;
}
}
static V W_Chk_dquant__dem(V *a) { (void)a; return F_Chk_dquant__dem(a[0], a[1]); }
static V L2202(V *a) {
return F_Chk_dtele__head_dgo(F_Chk_dterm__wnf(a[4], a[3]), a[2], a[1], a[0]);
}
static V F_Chk_dtele__head(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2202, 5, 4, (V[]){a3, a2, a1, a0}));
}
static V W_Chk_dtele__head(V *a) { (void)a; return F_Chk_dtele__head(a[0], a[1], a[2], a[3]); }
static V S2204(void) { static V c; return STRC(c, "unreachable (a telescope binds its parameters and fields)"); }
static V F_Chk_dtele__head_dgo(V a0, V a1, V a2, V a3) {
top:;
V s2203 = a0;
if (TAG(s2203) == 11) {
return F_Chk_dK_dpure(CN(11, 6, (V[]){FLD(s2203, 0), FLD(s2203, 1), FLD(s2203, 2), FLD(s2203, 3), FLD(s2203, 4), FLD(s2203, 5)}));
} else {
return F_Chk_dK_derr(a1, C1(1, S2204()), IMM(0), a3, a2);
}
}
static V W_Chk_dtele__head_dgo(V *a) { (void)a; return F_Chk_dtele__head_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dK_dif(V a1, V a2, V a3) {
top:;
V s2205 = a1;
if ((s2205) == IMM(1)) {
return a2;
} else if ((s2205) == IMM(0)) {
return a3;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dK_dif(V *a) { (void)a; return F_Chk_dK_dif(a[1], a[2], a[3]); }
static V L2206(V *a) {
return F_Chk_dbook__adt_dgo(a[2], F_Chk_dbook__tld(a[3], F_Chk_dTm_dname(a[2])), a[1], a[0]);
}
static V F_Chk_dbook__adt(V a0, V a1, V a2) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2206, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dbook__adt(V *a) { (void)a; return F_Chk_dbook__adt(a[0], a[1], a[2]); }
static V S2208(void) { static V c; return STRC(c, "a declared datatype (unknown: "); }
static V S2209(void) { static V c; return STRC(c, ")"); }
static V F_Chk_dbook__adt_dgo(V a0, V a1, V a2, V a3) {
top:;
V s2207 = a1;
if (TAG(s2207) == 1 && TAG(FLD(s2207, 0)) == 1) {
return F_Chk_dK_dpure(C4(0, FLD(FLD(s2207, 0), 0), FLD(FLD(s2207, 0), 1), FLD(FLD(s2207, 0), 2), F_Chk_dctrs__drop(FLD(FLD(s2207, 0), 3), F_Chk_dADT_dr(a0))));
} else {
return F_Chk_dK_derr(a2, C1(1, F_String_dappend(S2208(), F_String_dappend(F_Chk_dTm_dname(a0), S2209()))), IMM(0), F_Chk_dTm_dspan(a0), a3);
}
}
static V W_Chk_dbook__adt_dgo(V *a) { (void)a; return F_Chk_dbook__adt_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dADT_dr(V a0) {
top:;
V s2210 = a0;
if (TAG(s2210) == 14) {
return FLD(s2210, 3);
} else {
return IMM(0);
}
}
static V W_Chk_dADT_dr(V *a) { (void)a; return F_Chk_dADT_dr(a[0]); }
static V F_Chk_dctrs__drop(V a0, V a1) {
top:;
V s2211 = a0;
if ((s2211) == IMM(0)) {
return IMM(0);
} else if (TAG(s2211) == 1) {
return F_Chk_dctrs__drop_dif(C3(0, FLD(FLD(s2211, 0), 0), FLD(FLD(s2211, 0), 1), FLD(FLD(s2211, 0), 2)), F_Chk_dctrs__drop(FLD(s2211, 1), a1), F_Chk_dStr_dhas(a1, FLD(FLD(s2211, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctrs__drop(V *a) { (void)a; return F_Chk_dctrs__drop(a[0], a[1]); }
static V F_Chk_dctrs__drop_dif(V a0, V a1, V a2) {
top:;
V s2212 = a2;
if ((s2212) == IMM(1)) {
return a1;
} else if ((s2212) == IMM(0)) {
return C2(1, a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctrs__drop_dif(V *a) { (void)a; return F_Chk_dctrs__drop_dif(a[0], a[1], a[2]); }
static V L2215(V *a) {
return F_Chk_dinfer_dapp_dgo(a[7], F_Chk_dterm__wnf(a[8], a[6]), a[6], a[5], a[4], a[3], a[2], a[1], a[0]);
}
static V F_Chk_dinfer_dapp(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2213 = a1;
V s2214 = FLD(v2213, 2);
if (nat_ge(s2214, 1)) {
return F_Chk_dK_dpure(C3(0, FLD(v2213, 0), FLD(v2213, 1), nat_subk(s2214, 1)));
} else if ((s2214) == 0) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2215, 9, 8, (V[]){a6, a5, a4, a3, a2, FLD(v2213, 1), FLD(v2213, 0), a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dinfer_dapp(V *a) { (void)a; return F_Chk_dinfer_dapp(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V L2218(V *a) {
return F_Chk_dK_dpure(C3(0, F_Chk_dclo__apply(a[4], a[3], C2(1, a[2], IMM(0))), F_Chk_duses__add(a[1], a[0]), 0u));
}
static V L2217(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2218, 5, 4, (V[]){a[3], a[0], a[1], a[2]}));
}
static V S2219(void) { static V c; return STRC(c, "a function type"); }
static V F_Chk_dinfer_dapp_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s2216 = a1;
if (TAG(s2216) == 11) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a0, a4, F_Chk_dquant__dem(FLD(s2216, 0), a5), FLD(s2216, 3), a6, a7), mk_clo(L2217, 4, 3, (V[]){a3, a4, FLD(s2216, 4)}));
} else {
return F_Chk_dK_derr(a6, C1(1, S2219()), C1(2, a2), a8, F_Chk_dCL_ddn(a0));
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
V s2220 = a0;
if ((s2220) == IMM(2)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dQ_dis__many(V *a) { (void)a; return F_Chk_dQ_dis__many(a[0]); }
static V F_Chk_dCL_du(V a0) {
top:;
V v2221 = a0;
return FLD(v2221, 4);
}
static V W_Chk_dCL_du(V *a) { (void)a; return F_Chk_dCL_du(a[0]); }
static V S2223(void) { static V c; return STRC(c, "a defined name"); }
static V F_Chk_dinfer_dref(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s2222 = a4;
if ((s2222) == IMM(0)) {
return F_Chk_dK_derr(a6, C1(1, S2223()), C1(2, C3(4, a1, a2, a3)), a2, F_Chk_dCL_ddn(a0));
} else if (TAG(s2222) == 1) {
return F_Chk_dK_dif(F_Chk_dQ_dis__none(a5), F_Chk_dinfer_dref_dfin(a0, a1, a2, a3, FLD(s2222, 0), a6, 0u), F_Chk_dinfer_dref_dlive(a0, a1, a2, a3, FLD(s2222, 0), a5, a6, a7, a8));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dinfer_dref(V *a) { (void)a; return F_Chk_dinfer_dref(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V S2228(void) { static V c; return STRC(c, "a filled definition (an unfilled law is a dead claim: live code cannot use it)"); }
static V L2229(V *a) {
return F_Chk_dK_dif(a[9], F_Chk_dinfer_dref_dinst(a[8], a[7], a[6], a[5], a[4], a[3], a[2], a[1], a[0]), F_Chk_dinfer_dref_dself(a[8], a[7], a[6], a[5], a[4], a[2], a[0], 0u));
}
static V L2227(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dif(F_Bool_dand(F_Bool_dand(F_Chk_dTld_dis__open(a[9]), F_Bool_dnot(a[10])), F_Bool_dor(F_Bool_dand(F_Bool_dnot(F_Chk_dTld_dis__base(a[9])), F_Bool_dnot(F_Chk_dCL_du(a[8]))), a[7])), F_Chk_dK_derr(a[6], C1(1, S2228()), C1(2, C3(4, a[5], a[4], a[3])), a[4], F_Chk_dCL_ddn(a[8])), F_Chk_dK_dpure(IMM(0))), mk_clo(L2229, 11, 10, (V[]){a[0], a[1], a[6], a[2], a[9], a[3], a[4], a[5], a[8], a[7]}));
}
static V L2226(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_String_deq(a[8], F_Chk_dCL_ddn(a[7]))), mk_clo(L2227, 11, 10, (V[]){a[0], a[1], a[2], a[3], a[4], a[8], a[5], a[9], a[7], a[6]}));
}
static V L2225(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Bool_dand(F_Nat_dis__gt(F_Chk_dTld_dx__of(a[8]), 0u), F_Nat_dis__eq(0u, a[9]))), mk_clo(L2226, 10, 9, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[8], a[6], a[7]}));
}
static V L2224(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dTld_dx(F_Chk_dbook__tld(a[9], F_Chk_dCL_ddn(a[8])))), mk_clo(L2225, 10, 9, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[8], a[6], a[7]}));
}
static V F_Chk_dinfer_dref_dlive(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2224, 10, 9, (V[]){a8, a7, a5, a3, a2, a6, a1, a4, a0}));
}
static V W_Chk_dinfer_dref_dlive(V *a) { (void)a; return F_Chk_dinfer_dref_dlive(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V S2231(void) { static V c; return STRC(c, "a decreasing self-call (arguments are read left to right: each passed unchanged until one shrinks)"); }
static V L2232(V *a) {
return F_Chk_dinfer_dref_dfin(a[6], a[5], a[4], a[3], a[2], a[1], a[0]);
}
static V L2230(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dif(F_Chk_dinfer_dref_dbad__self(a[8], a[7], a[6], F_Bool_dand(F_String_deq(a[5], F_Chk_dCL_ddn(a[7])), F_Bool_dnot(F_Chk_dCL_du(a[7])))), F_Chk_dK_derr(a[4], C1(1, S2231()), C1(2, C3(4, a[5], a[3], a[2])), a[3], F_Chk_dCL_ddn(a[7])), F_Chk_dK_dpure(IMM(0))), mk_clo(L2232, 8, 7, (V[]){a[0], a[4], a[1], a[2], a[3], a[5], a[7]}));
}
static V F_Chk_dinfer_dref_dself(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2230, 9, 8, (V[]){a7, a4, a3, a2, a5, a1, a6, a0}));
}
static V W_Chk_dinfer_dref_dself(V *a) { (void)a; return F_Chk_dinfer_dref_dself(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S2234(void) { static V c; return STRC(c, "a family instance (write "); }
static V S2235(void) { static V c; return STRC(c, "<..>)"); }
static V F_Chk_dinfer_dref_dfin(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2233 = a4;
if (TAG(s2233) == 1) {
return F_Chk_dK_dif(F_Nat_dis__gt(FLD(s2233, 0), 0u), F_Chk_dK_derr(a5, C1(1, F_String_dappend(S2234(), F_String_dappend(a1, S2235()))), C1(2, C3(4, a1, a2, a3)), a2, F_Chk_dCL_ddn(a0)), F_Chk_dK_dpure(C3(0, FLD(s2233, 2), IMM(0), a6)));
} else if (TAG(s2233) == 0) {
return F_Chk_dK_dpure(C3(0, FLD(s2233, 2), IMM(0), a6));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dinfer_dref_dfin(V *a) { (void)a; return F_Chk_dinfer_dref_dfin(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dinfer_dref_dbad__self(V a0, V a1, V a2, V a3) {
top:;
V s2236 = a3;
if ((s2236) == IMM(1)) {
return F_Bool_dnot(F_Chk_dCL_ddecreases(a0, a1, a2));
} else if ((s2236) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dinfer_dref_dbad__self(V *a) { (void)a; return F_Chk_dinfer_dref_dbad__self(a[0], a[1], a[2], a[3]); }
static V F_Chk_dCL_ddecreases(V a0, V a1, V a2) {
top:;
V v2237 = a1;
return F_U32_dis__eq(F_Chk_ddescend_dargs(a0, FLD(v2237, 3), a2, F_Chk_dcl_dcols(FLD(v2237, 0)), 0u), 1u);
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
V s2238 = a1;
V s2239 = a2;
V s2240 = a3;
if (TAG(s2238) == 1 && TAG(s2239) == 1 && TAG(s2240) == 1) {
return F_Chk_ddescend_dargs_dstep(a0, FLD(s2238, 1), FLD(s2239, 1), FLD(s2240, 1), a4, F_Chk_dterm__descend(a0, FLD(s2238, 0), FLD(s2239, 0), FLD(s2240, 0)));
} else {
return a4;
}
}
static V W_Chk_ddescend_dargs(V *a) { (void)a; return F_Chk_ddescend_dargs(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dterm__descend(V a0, V a1, V a2, V a3) {
top:;
V s2241 = a1;
if ((s2241) == IMM(0)) {
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
V s2242 = a2;
if (TAG(s2242) == 0) {
return F_Chk_ddescend_dvar(a1, FLD(s2242, 1));
} else if (TAG(s2242) == 15) {
return F_Chk_ddescend_dctr(a0, a1, FLD(s2242, 0), FLD(s2242, 1), F_Chk_ddescend_dsame(a1, FLD(s2242, 0), FLD(s2242, 1)));
} else {
return 2u;
}
}
static V W_Chk_ddescend_dgo(V *a) { (void)a; return F_Chk_ddescend_dgo(a[0], a[1], a[2]); }
static V F_Chk_ddescend_dsame(V a0, V a1, V a2) {
top:;
V s2243 = a0;
if (TAG(s2243) == 15) {
return F_Bool_dand(F_String_deq(a1, FLD(s2243, 0)), F_Nat_dis__eq(F_List_dlength(a2), F_List_dlength(FLD(s2243, 1))));
} else {
return IMM(0);
}
}
static V W_Chk_ddescend_dsame(V *a) { (void)a; return F_Chk_ddescend_dsame(a[0], a[1], a[2]); }
static V F_Chk_ddescend_dctr(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2244 = a4;
if ((s2244) == IMM(1)) {
return F_Chk_ddescend_dctr_dfields(a0, a1, a3, F_Chk_ddescend_dfields(a0, F_Chk_dCtr_dxs(a1), a3, 0u));
} else if ((s2244) == IMM(0)) {
return F_Chk_ddescend_dsub(a0, a1, a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_ddescend_dctr(V *a) { (void)a; return F_Chk_ddescend_dctr(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_ddescend_dsub(V a0, V a1, V a2) {
top:;
V s2245 = a2;
if ((s2245) == IMM(0)) {
return 2u;
} else if (TAG(s2245) == 1) {
return F_Chk_ddescend_dsub_dif(a0, a1, FLD(s2245, 1), F_U32_dis__eq(F_Chk_dterm__descend(a0, IMM(1), a1, FLD(s2245, 0)), 2u));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_ddescend_dsub(V *a) { (void)a; return F_Chk_ddescend_dsub(a[0], a[1], a[2]); }
static V F_Chk_ddescend_dsub_dif(V a0, V a1, V a2, V a3) {
top:;
V s2246 = a3;
if ((s2246) == IMM(1)) {
return F_Chk_ddescend_dsub(a0, a1, a2);
} else if ((s2246) == IMM(0)) {
return 1u;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_ddescend_dsub_dif(V *a) { (void)a; return F_Chk_ddescend_dsub_dif(a[0], a[1], a[2], a[3]); }
static V F_Chk_dCtr_dxs(V a0) {
top:;
V s2247 = a0;
if (TAG(s2247) == 15) {
return FLD(s2247, 1);
} else {
return IMM(0);
}
}
static V W_Chk_dCtr_dxs(V *a) { (void)a; return F_Chk_dCtr_dxs(a[0]); }
static V F_Chk_ddescend_dfields(V a0, V a1, V a2, V a3) {
top:;
V s2248 = a1;
V s2249 = a2;
if (TAG(s2248) == 1 && TAG(s2249) == 1) {
return F_Chk_ddescend_dfields_dstep(a0, FLD(s2248, 1), FLD(s2249, 1), a3, F_Chk_dterm__descend(a0, IMM(1), FLD(s2248, 0), FLD(s2249, 0)));
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
V s2250 = a4;
if ((s2250) == IMM(1)) {
return 2u;
} else if ((s2250) == IMM(0)) {
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
V s2251 = a0;
if (TAG(s2251) == 0) {
return F_Bool_dpick(F_U32_dis__eq(a1, FLD(s2251, 1)), 0u, 2u);
} else {
return 2u;
}
}
static V W_Chk_ddescend_dvar(V *a) { (void)a; return F_Chk_ddescend_dvar(a[0], a[1]); }
static V F_Chk_ddescend_dargs_dstep(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_ddescend_dargs_dif(a0, a1, a2, a3, a4, a5, F_U32_dis__eq(a5, 0u));
}
static V W_Chk_ddescend_dargs_dstep(V *a) { (void)a; return F_Chk_ddescend_dargs_dstep(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_ddescend_dargs_dif(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2252 = a6;
if ((s2252) == IMM(1)) {
return F_Chk_ddescend_dargs(a0, a1, a2, a3, a4);
} else if ((s2252) == IMM(0)) {
return a5;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_ddescend_dargs_dif(V *a) { (void)a; return F_Chk_ddescend_dargs_dif(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V L2255(V *a) {
return F_Chk_dinfer_dref_dself(a[7], a[6], a[5], a[4], F_Maybe_ddefault(F_Chk_dbook__tld(a[3], a[6]), a[2]), a[1], F_Chk_dList_ddrop__tm(a[0], a[8]), a[8]);
}
static V L2254(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dTld_dx__of(a[6])), mk_clo(L2255, 9, 8, (V[]){a[0], a[1], a[6], a[7], a[2], a[3], a[4], a[5]}));
}
static V L2253(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2254, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[6], a[4], a[5]}));
}
static V F_Chk_dinfer_dref_dinst(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
return F_Chk_dK_dbind(F_Chk_ddef__inst(a0, C3(4, a1, a2, a3), a4, a8, a6, a7), mk_clo(L2253, 7, 6, (V[]){a8, a6, a3, a2, a0, a4}));
}
static V W_Chk_dinfer_dref_dinst(V *a) { (void)a; return F_Chk_dinfer_dref_dinst(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Chk_dList_ddrop__tm(V a0, V a1) {
top:;
V s2256 = a0;
V s2257 = a1;
if ((s2257) == 0) {
return s2256;
} else if (TAG(s2256) == 1 && nat_ge(s2257, 1)) {
{ V t0 = FLD(s2256, 1); V t1 = nat_subk(s2257, 1); a0 = t0; a1 = t1; goto top; }
} else if ((s2256) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dList_ddrop__tm(V *a) { (void)a; return F_Chk_dList_ddrop__tm(a[0], a[1]); }
static V S2260(void) { static V c; return STRC(c, "a template applied to closed ~ arguments (a def parameter is not comptime)"); }
static V F_Chk_ddef__inst(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v2258 = F_Chk_dTld_dx__of(a2);
V v2259 = F_Chk_dList_dtake__tm(a3, v2258);
return F_Chk_dK_dif(F_Nat_dis__lt(F_List_dlength(v2259), v2258), F_Chk_dK_derr(a4, C1(1, S2260()), C1(2, a1), F_Chk_dTm_dspan(a1), F_Chk_dCL_ddn(a0)), F_Chk_ddef__inst_dgo(a0, a1, a2, v2259, a4, a5));
}
static V W_Chk_ddef__inst(V *a) { (void)a; return F_Chk_ddef__inst(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S2264(void) { static V c; return STRC(c, "a ~ argument that stops growing"); }
static V S2266(void) { static V c; return STRC(c, "\012"); }
static V S2267(void) { static V c; return STRC(c, "\012"); }
static V L2265(V *a) {
return F_Chk_ddef__inst_dfind(a[7], a[6], a[5], a[4], a[3], F_String_dappend(F_Chk_dTm_dname(a[6]), F_String_dappend(S2266(), a[2])), a[1], F_Chk_dBook_dtmp(a[0], F_String_dappend(F_Chk_dTm_dname(a[6]), F_String_dappend(S2267(), a[2]))));
}
static V L2263(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dif(F_Nat_dis__gt(F_String_dlength(a[7]), 32768u), F_Chk_dK_derr(a[6], C1(1, S2264()), C1(2, a[5]), F_Chk_dTm_dspan(a[5]), F_Chk_dCL_ddn(a[4])), F_Chk_dK_dpure(IMM(0))), mk_clo(L2265, 9, 8, (V[]){a[0], a[6], a[7], a[1], a[2], a[3], a[5], a[4]}));
}
static V L2262(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dterm__key_dlist(F_Chk_dlowers(a[6], a[5], 0u))), mk_clo(L2263, 8, 7, (V[]){a[6], a[0], a[5], a[1], a[2], a[3], a[4]}));
}
static V L2261(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2262, 7, 6, (V[]){a[5], a[0], a[1], a[2], a[3], a[4]}));
}
static V F_Chk_ddef__inst_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dK_dbind(F_Chk_dinst_dargs(a0, a1, F_Chk_dTld_dt(a2), a3, a4, a5), mk_clo(L2261, 6, 5, (V[]){a2, a0, a1, a4, a3}));
}
static V W_Chk_ddef__inst_dgo(V *a) { (void)a; return F_Chk_ddef__inst_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dBook_dtmp(V a0, V a1) {
top:;
V v2268 = a0;
return F_Chk_dMap_dfind(FLD(v2268, 5), a1);
}
static V W_Chk_dBook_dtmp(V *a) { (void)a; return F_Chk_dBook_dtmp(a[0], a[1]); }
static V S2271(void) { static V c; return STRC(c, "a decreasing self-call (arguments are read left to right: each passed unchanged until one shrinks)"); }
static V L2270(V *a) {
return F_Chk_dK_dif(F_Bool_dand(F_Bool_dnot(F_Maybe_dis__some(F_Chk_dTld_ddval(F_Maybe_ddefault(F_Chk_dbook__tld(a[5], a[4]), a[3])))), F_Bool_dnot(F_String_deq(a[4], F_Chk_dCL_ddn(a[2])))), F_Chk_dK_derr(a[1], C1(1, S2271()), C1(2, a[0]), F_Chk_dTm_dspan(a[0]), F_Chk_dCL_ddn(a[2])), F_Chk_dK_dpure(a[4]));
}
static V F_Chk_ddef__inst_dfind(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s2269 = a7;
if (TAG(s2269) == 1) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2270, 6, 5, (V[]){a1, a6, a0, a2, FLD(s2269, 0)}));
} else if ((s2269) == IMM(0)) {
return F_Chk_ddef__inst_dnew(a0, a1, a2, a3, a4, a5, a6);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_ddef__inst_dfind(V *a) { (void)a; return F_Chk_ddef__inst_dfind(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S2273(void) { static V c; return STRC(c, "a template that stops instantiating itself (64 levels at most)"); }
static V F_Chk_ddef__inst_dnew(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2272 = nat_addk(F_Chk_dCL_dz(a0), 1);
return F_Chk_dK_dif(F_Nat_dis__gt(v2272, 64u), F_Chk_dK_derr(a6, C1(1, S2273()), C1(2, a1), F_Chk_dTm_dspan(a1), F_Chk_dCL_ddn(a0)), F_Chk_ddef__inst_dmake(a1, a2, a3, a4, a5, v2272));
}
static V W_Chk_ddef__inst_dnew(V *a) { (void)a; return F_Chk_ddef__inst_dnew(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S2276(void) { static V c; return STRC(c, "~"); }
static V L2283(V *a) {
return F_Chk_dK_dpure(a[0]);
}
static V L2282(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dset__book(F_Chk_dbook__set(a[5], a[4], CN(0, 7, (V[]){a[3], 0u, a[2], C1(1, a[1]), F_Chk_dTld_ddu(a[0]), IMM(0), IMM(0)}))), mk_clo(L2283, 2, 1, (V[]){a[4]}));
}
static V L2281(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2282, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L2280(V *a) {
return F_Chk_dK_dbind(F_Chk_ddef__check(a[5], CN(0, 7, (V[]){a[4], 0u, a[3], C1(1, a[2]), F_Chk_dTld_ddu(a[1]), IMM(0), IMM(0)}), a[0]), mk_clo(L2281, 6, 5, (V[]){a[1], a[2], a[3], a[4], a[5]}));
}
static V L2279(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dset__book(F_Chk_dbook__set(F_Chk_dBook_dadd__tmp(a[7], a[6], a[5], a[4]), a[4], CN(0, 7, (V[]){a[3], 0u, a[2], IMM(0), F_Chk_dTld_ddu(a[1]), IMM(0), IMM(0)}))), mk_clo(L2280, 7, 6, (V[]){a[0], a[1], a[8], a[2], a[3], a[4]}));
}
static V L2278(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dapplys(a[7], F_Maybe_ddefault(F_Chk_dTld_ddval(a[6]), C1(18, IMM(0))), a[5])), mk_clo(L2279, 9, 8, (V[]){a[0], a[6], a[1], a[8], a[2], a[3], a[4], a[7]}));
}
static V L2277(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Nat_dsub(F_Chk_dTld_ddn(a[6]), F_Chk_dTld_dx__of(a[6]))), mk_clo(L2278, 9, 8, (V[]){a[0], a[1], a[7], a[2], a[3], a[4], a[6], a[5]}));
}
static V L2275(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_String_dappend(a[5], F_String_dappend(S2276(), F_Nat_dshow(F_Chk_dBook_dtcnt(a[6], a[5]))))), mk_clo(L2277, 8, 7, (V[]){a[0], a[1], a[2], a[5], a[3], a[6], a[4]}));
}
static V F_Chk_ddef__inst_dmake(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v2274 = F_Chk_dTm_dname(a0);
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2275, 7, 6, (V[]){a5, a3, a4, a2, a1, v2274}));
}
static V W_Chk_ddef__inst_dmake(V *a) { (void)a; return F_Chk_ddef__inst_dmake(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dBook_dadd__tmp(V a0, V a1, V a2, V a3) {
top:;
V v2284 = a0;
V v2285 = F_Maybe_ddefault(F_Chk_dMap_dfind(FLD(v2284, 6), a1), 0u);
return CN(0, 7, (V[]){FLD(v2284, 0), FLD(v2284, 1), FLD(v2284, 2), FLD(v2284, 3), FLD(v2284, 4), F_Map_dset(FLD(v2284, 5), a2, a3), F_Map_dset(FLD(v2284, 6), a1, nat_addk(v2285, 1))});
}
static V W_Chk_dBook_dadd__tmp(V *a) { (void)a; return F_Chk_dBook_dadd__tmp(a[0], a[1], a[2], a[3]); }
static V F_Chk_dTld_ddval(V a0) {
top:;
V s2286 = a0;
if (TAG(s2286) == 0) {
return FLD(s2286, 3);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_ddval(V *a) { (void)a; return F_Chk_dTld_ddval(a[0]); }
static V F_Chk_dapplys(V a0, V a1, V a2) {
top:;
V s2287 = a2;
if ((s2287) == IMM(0)) {
return a1;
} else if (TAG(s2287) == 1) {
{ V t0 = a0; V t1 = F_Chk_dterm__apply1(a0, a1, FLD(s2287, 0)); V t2 = FLD(s2287, 1); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dapplys(V *a) { (void)a; return F_Chk_dapplys(a[0], a[1], a[2]); }
static V F_Chk_dBook_dtcnt(V a0, V a1) {
top:;
V v2288 = a0;
return F_Maybe_ddefault(F_Chk_dMap_dfind(FLD(v2288, 6), a1), 0u);
}
static V W_Chk_dBook_dtcnt(V *a) { (void)a; return F_Chk_dBook_dtcnt(a[0], a[1]); }
static V F_Chk_dCL_dz(V a0) {
top:;
V v2289 = a0;
return FLD(v2289, 5);
}
static V W_Chk_dCL_dz(V *a) { (void)a; return F_Chk_dCL_dz(a[0]); }
static V F_Chk_dTld_dt(V a0) {
top:;
V s2290 = a0;
if (TAG(s2290) == 0) {
return FLD(s2290, 2);
} else if (TAG(s2290) == 1) {
return FLD(s2290, 2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dTld_dt(V *a) { (void)a; return F_Chk_dTld_dt(a[0]); }
static V L2294(V *a) {
return F_Chk_dinst_dargs(a[6], a[5], F_Chk_dclo__apply(a[7], F_Chk_dAll_db(a[4]), C2(1, a[3], IMM(0))), a[2], a[1], a[0]);
}
static V L2293(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2294, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L2292(V *a) {
return F_Chk_dK_dbind(F_Chk_dinst_dclosed(a[5], a[4], a[3], F_Chk_dAll_da(a[6]), a[2], a[1]), mk_clo(L2293, 8, 7, (V[]){a[1], a[2], a[0], a[3], a[6], a[4], a[5]}));
}
static V F_Chk_dinst_dargs(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2291 = a3;
if ((s2291) == IMM(0)) {
return F_Chk_dK_dpure(a2);
} else if (TAG(s2291) == 1) {
return F_Chk_dK_dbind(F_Chk_dtele__head(a2, a4, F_Chk_dCL_ddn(a0), F_Chk_dTm_dspan(a1)), mk_clo(L2292, 7, 6, (V[]){FLD(s2291, 1), a5, a4, FLD(s2291, 0), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dinst_dargs(V *a) { (void)a; return F_Chk_dinst_dargs(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L2295(V *a) {
return F_Chk_dinst_dclosed_dgo(apply(F_Chk_dterm__check(a[5], a[4], IMM(0), a[3], IMM(0), a[2]), a[6]), a[5], a[1], a[0], a[2]);
}
static V F_Chk_dinst_dclosed(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return mk_clo(L2295, 7, 6, (V[]){a4, a1, a5, a3, a2, a0});
}
static V W_Chk_dinst_dclosed(V *a) { (void)a; return F_Chk_dinst_dclosed(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dinst_dclosed_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2296 = a0;
if (TAG(s2296) == 1) {
return C1(1, FLD(s2296, 0));
} else if (TAG(s2296) == 0) {
return C1(0, F_Chk_dinst_dclosed_derr(FLD(s2296, 0), a1, a2, a3, a4));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dinst_dclosed_dgo(V *a) { (void)a; return F_Chk_dinst_dclosed_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dinst_dclosed_derr(V a0, V a1, V a2, V a3, V a4) {
top:;
V v2297 = a0;
return F_Chk_dinst_dclosed_derr_dgo(CN(0, 7, (V[]){FLD(v2297, 0), FLD(v2297, 1), FLD(v2297, 2), FLD(v2297, 3), FLD(v2297, 4), FLD(v2297, 5), FLD(v2297, 6)}), FLD(v2297, 3), FLD(v2297, 0), a1, a2, a3, a4);
}
static V W_Chk_dinst_dclosed_derr(V *a) { (void)a; return F_Chk_dinst_dclosed_derr(a[0], a[1], a[2], a[3], a[4]); }
static V S2299(void) { static V c; return STRC(c, "a template applied to closed ~ arguments ("); }
static V S2300(void) { static V c; return STRC(c, " is a variable here, not comptime: pass it at run time)"); }
static V F_Chk_dinst_dclosed_derr_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2298 = a1;
if (TAG(s2298) == 2 && TAG(FLD(s2298, 0)) == 0) {
return F_Bool_dpick(F_U32_dis__lt(FLD(FLD(s2298, 0), 1), a6), F_Chk_derr(a2, a5, C1(1, F_String_dappend(S2299(), F_String_dappend(FLD(FLD(s2298, 0), 0), S2300()))), C1(2, a4), F_Chk_dTm_dspan(a4), F_Chk_dCL_ddn(a3)), a0);
} else {
return a0;
}
}
static V W_Chk_dinst_dclosed_derr_dgo(V *a) { (void)a; return F_Chk_dinst_dclosed_derr_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dList_dtake__tm(V a0, V a1) {
top:;
V s2301 = a0;
V s2302 = a1;
if (TAG(s2301) == 1 && nat_ge(s2302, 1)) {
return C2(1, FLD(s2301, 0), F_Chk_dList_dtake__tm(FLD(s2301, 1), nat_subk(s2302, 1)));
} else {
return IMM(0);
}
}
static V W_Chk_dList_dtake__tm(V *a) { (void)a; return F_Chk_dList_dtake__tm(a[0], a[1]); }
static V F_Chk_dTld_dis__base(V a0) {
top:;
V s2303 = a0;
if (TAG(s2303) == 0) {
return FLD(s2303, 5);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dis__base(V *a) { (void)a; return F_Chk_dTld_dis__base(a[0]); }
static V F_Chk_dTld_dis__open(V a0) {
top:;
V s2304 = a0;
if (TAG(s2304) == 0 && (FLD(s2304, 3)) == IMM(0) && (FLD(s2304, 6)) == IMM(0)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dis__open(V *a) { (void)a; return F_Chk_dTld_dis__open(a[0]); }
static V F_Chk_dTld_dx(V a0) {
top:;
V s2305 = a0;
if (TAG(s2305) == 1 && TAG(FLD(s2305, 0)) == 0) {
return FLD(FLD(s2305, 0), 1);
} else {
return 0u;
}
}
static V W_Chk_dTld_dx(V *a) { (void)a; return F_Chk_dTld_dx(a[0]); }
static V F_Chk_dQ_dis__none(V a0) {
top:;
V s2306 = a0;
if ((s2306) == IMM(0)) {
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
V s2307 = a0;
if ((s2307) == IMM(0)) {
return IMM(0);
} else if (TAG(s2307) == 1 && TAG(FLD(s2307, 0)) == 33) {
return F_Chk_dctx__get_dif(FLD(FLD(s2307, 0), 3), FLD(s2307, 1), a1, F_U32_dis__eq(a1, FLD(FLD(s2307, 0), 0)));
} else if (TAG(s2307) == 1) {
{ V t0 = FLD(s2307, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctx__get(V *a) { (void)a; return F_Chk_dctx__get(a[0], a[1]); }
static V F_Chk_dctx__get_dif(V a0, V a1, V a2, V a3) {
top:;
V s2308 = a3;
if ((s2308) == IMM(1)) {
return C1(1, a0);
} else if ((s2308) == IMM(0)) {
return F_Chk_dctx__get(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctx__get_dif(V *a) { (void)a; return F_Chk_dctx__get_dif(a[0], a[1], a[2], a[3]); }
static V S2310(void) { static V c; return STRC(c, "a bound variable"); }
static V F_Chk_dinfer_dvar_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2309 = a6;
if ((s2309) == IMM(0)) {
return F_Chk_dK_derr(a3, C1(1, S2310()), C1(2, a0), a4, F_Chk_dCL_ddn(a5));
} else if (TAG(s2309) == 1) {
return F_Chk_dK_dpure(C3(0, FLD(s2309, 0), F_Chk_duses__one(a1, a2), 0u));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dinfer_dvar_dgo(V *a) { (void)a; return F_Chk_dinfer_dvar_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_duses__one(V a0, V a1) {
top:;
return C2(1, C2(0, a0, a1), IMM(0));
}
static V W_Chk_duses__one(V *a) { (void)a; return F_Chk_duses__one(a[0], a[1]); }
static V S2312(void) { static V c; return STRC(c, "_"); }
static V L2317(V *a) {
return F_Chk_dK_dpure(F_Chk_duses__add(F_Chk_dIR_dus(a[0]), a[1]));
}
static V L2316(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[9], a[8], a[7], F_Chk_dterm__apply1(a[6], F_Chk_dterm__apply1(a[6], a[5], a[4]), C1(20, a[3])), a[2], a[1]), mk_clo(L2317, 2, 1, (V[]){a[0]}));
}
static V L2315(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dif(F_Chk_dterm__compare(IMM(1), a[10], a[11], a[9], a[8]), F_Chk_dK_dpure(IMM(0)), F_Chk_dK_derr(a[7], C1(2, a[9]), C1(2, a[11]), a[6], F_Chk_dCL_ddn(a[5]))), mk_clo(L2316, 11, 10, (V[]){a[0], a[8], a[7], a[6], a[1], a[2], a[10], a[3], a[4], a[5]}));
}
static V L2314(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dterm__apply1(a[12], F_Chk_dterm__apply1(a[12], a[11], a[10]), a[9])), mk_clo(L2315, 12, 11, (V[]){a[0], a[1], a[11], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[12]}));
}
static V L2313(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2314, 13, 12, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11]}));
}
static V S2318(void) { static V c; return STRC(c, "an equation {a == b : T}"); }
static V F_Chk_dcheck_drwt(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10) {
top:;
V s2311 = a6;
if (TAG(s2311) == 19) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a0, a2, IMM(0), CN(11, 6, (V[]){IMM(1), S2312(), 0u, FLD(s2311, 2), C3(29, FLD(s2311, 0), FLD(s2311, 2), a4), a4}), a9, a10), mk_clo(L2313, 13, 12, (V[]){a5, FLD(s2311, 0), a7, a3, a0, a4, a9, a10, a8, a1, FLD(s2311, 1), a2}));
} else {
return F_Chk_dK_derr(a9, C1(1, S2318()), C1(2, F_Chk_dIR_dty(a5)), F_Chk_dSp_dor(F_Chk_dTm_dspan(a1), a4), F_Chk_dCL_ddn(a0));
}
}
static V W_Chk_dcheck_drwt(V *a) { (void)a; return F_Chk_dcheck_drwt(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10]); }
static V F_Chk_dIR_dus(V a0) {
top:;
V v2319 = a0;
return FLD(v2319, 1);
}
static V W_Chk_dIR_dus(V *a) { (void)a; return F_Chk_dIR_dus(a[0]); }
static V L2321(V *a) {
return F_Chk_dK_dif(F_Chk_dterm__compare(IMM(0), a[6], a[5], a[4], a[3]), F_Chk_dK_dpure(IMM(0)), F_Chk_dK_derr(a[2], C1(2, a[5]), C1(2, a[4]), a[1], F_Chk_dCL_ddn(a[0])));
}
static V F_Chk_dcheck_drfl(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2320 = a2;
if (TAG(s2320) == 19) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2321, 7, 6, (V[]){a0, a1, a4, a5, FLD(s2320, 1), FLD(s2320, 0)}));
} else {
return F_Chk_dcheck_dtypeless(a0, C1(20, a1), a3, a4, a1);
}
}
static V W_Chk_dcheck_drfl(V *a) { (void)a; return F_Chk_dcheck_drfl(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L2322(V *a) {
return F_Chk_dK_derr(a[4], C1(2, a[3]), C1(1, F_Chk_dtypeless__show(a[6], a[4], a[2])), a[1], F_Chk_dCL_ddn(a[0]));
}
static V F_Chk_dcheck_dtypeless(V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2322, 7, 6, (V[]){a1, a5, a2, a3, a4, 0}));
}
static V W_Chk_dcheck_dtypeless(V *a) { (void)a; return F_Chk_dcheck_dtypeless(a[1], a[2], a[3], a[4], a[5]); }
static V S2323(void) { static V c; return STRC(c, "non-inferrable term '"); }
static V S2324(void) { static V c; return STRC(c, "'"); }
static V F_Chk_dtypeless__show(V a0, V a1, V a2) {
top:;
return F_String_dappend(S2323(), F_String_dappend(F_Chk_dexpr__show(a0, C1(2, a2), F_Chk_dctx__scope(a1)), F_String_dappend(S2324(), F_Chk_dtypeless_dnote(a0, a2))));
}
static V W_Chk_dtypeless__show(V *a) { (void)a; return F_Chk_dtypeless__show(a[0], a[1], a[2]); }
static V S2326(void) { static V c; return STRC(c, " ("); }
static V S2327(void) { static V c; return STRC(c, " is a datatype: write its arguments as <>)"); }
static V S2328(void) { static V c; return STRC(c, ""); }
static V S2329(void) { static V c; return STRC(c, ""); }
static V F_Chk_dtypeless_dnote(V a0, V a1) {
top:;
V s2325 = a1;
if (TAG(s2325) == 15) {
return F_Bool_dpick(F_Chk_dTld_dis__adt(F_Chk_dbook__tld(a0, FLD(s2325, 0))), F_String_dappend(S2326(), F_String_dappend(FLD(s2325, 0), S2327())), S2328());
} else {
return S2329();
}
}
static V W_Chk_dtypeless_dnote(V *a) { (void)a; return F_Chk_dtypeless_dnote(a[0], a[1]); }
static V F_Chk_dTld_dis__adt(V a0) {
top:;
V s2330 = a0;
if (TAG(s2330) == 1 && TAG(FLD(s2330, 0)) == 1) {
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
V s2331 = a0;
if ((s2331) == IMM(0)) {
return 0u;
} else if (TAG(s2331) == 1 && TAG(FLD(s2331, 0)) == 33) {
return F_U32_dmax(F_U32_dinc(FLD(FLD(s2331, 0), 0)), F_Chk_dctx__len(FLD(s2331, 1)));
} else if (TAG(s2331) == 1) {
{ V t0 = FLD(s2331, 1); a0 = t0; goto top; }
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
V s2332 = a3;
if ((s2332) == IMM(1)) {
return IMM(0);
} else if ((s2332) == IMM(0)) {
return C2(1, F_Chk_dctx__name(a0, a1), F_Chk_dctx__scope_dgo(a0, F_U32_dinc(a1), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctx__scope_dc(V *a) { (void)a; return F_Chk_dctx__scope_dc(a[0], a[1], a[2], a[3]); }
static V S2334(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dctx__name(V a0, V a1) {
top:;
V s2333 = a0;
if ((s2333) == IMM(0)) {
return S2334();
} else if (TAG(s2333) == 1 && TAG(FLD(s2333, 0)) == 33) {
return F_Chk_dctx__name_dif(FLD(FLD(s2333, 0), 2), FLD(s2333, 1), a1, F_U32_dis__eq(a1, FLD(FLD(s2333, 0), 0)));
} else if (TAG(s2333) == 1) {
{ V t0 = FLD(s2333, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctx__name(V *a) { (void)a; return F_Chk_dctx__name(a[0], a[1]); }
static V F_Chk_dctx__name_dif(V a0, V a1, V a2, V a3) {
top:;
V s2335 = a3;
if ((s2335) == IMM(1)) {
return a0;
} else if ((s2335) == IMM(0)) {
return F_Chk_dctx__name(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctx__name_dif(V *a) { (void)a; return F_Chk_dctx__name_dif(a[0], a[1], a[2], a[3]); }
static V S2337(void) { static V c; return STRC(c, ""); }
static V F_Chk_dexpr__show(V a0, V a1, V a2) {
top:;
V s2336 = a1;
if ((s2336) == IMM(0)) {
return S2337();
} else if (TAG(s2336) == 1) {
return FLD(s2336, 0);
} else if (TAG(s2336) == 2) {
return F_Chk_dterm__show(F_Chk_dterm__lower(a0, F_Chk_dterm__snf(a0, FLD(s2336, 0)), F_U32_dfrom__nat(F_List_dlength(a2))), 0u, F_List_dreverse(a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dexpr__show(V *a) { (void)a; return F_Chk_dexpr__show(a[0], a[1], a[2]); }
static V S2339(void) { static V c; return STRC(c, "a live scrutinee (a - scrutinee matches only in a dead region)"); }
static V L2341(V *a) {
return F_Chk_dcheck_delim_dadt(a[12], a[11], a[10], CN(11, 6, (V[]){a[9], a[8], a[7], a[6], a[5], a[4]}), F_Chk_dterm__wnf(a[13], a[6]), a[3], a[2], a[1], a[0]);
}
static V L2340(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2341, 14, 13, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12]}));
}
static V F_Chk_dcheck_delim(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s2338 = a3;
if (TAG(s2338) == 11) {
return F_Chk_dK_dbind(F_Chk_dK_dif(F_Bool_dand(F_Bool_dnot(F_Chk_dQ_dis__none(a4)), F_Chk_dQ_dis__none(FLD(s2338, 0))), F_Chk_dK_derr(a6, C1(1, S2339()), IMM(0), a2, F_Chk_dCL_ddn(a0)), F_Chk_dK_dpure(IMM(0))), mk_clo(L2340, 14, 13, (V[]){a7, a6, a5, a4, FLD(s2338, 5), FLD(s2338, 4), FLD(s2338, 3), FLD(s2338, 2), FLD(s2338, 1), FLD(s2338, 0), a2, a1, a0}));
} else {
return F_Chk_dcheck_dtypeless(a0, a1, a5, a6, a2);
}
}
static V W_Chk_dcheck_delim(V *a) { (void)a; return F_Chk_dcheck_delim(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V L2343(V *a) {
return F_Chk_dcheck_delim_dgo(a[10], a[9], a[8], a[7], a[6], a[5], a[4], F_Chk_dAD_dcs(a[11]), a[3], a[2], a[1], a[0]);
}
static V S2344(void) { static V c; return STRC(c, "a datatype"); }
static V F_Chk_dcheck_delim_dadt(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s2342 = a4;
if (TAG(s2342) == 14) {
return F_Chk_dK_dbind(F_Chk_dbook__adt(C4(14, FLD(s2342, 0), FLD(s2342, 1), FLD(s2342, 2), FLD(s2342, 3)), a7, F_Chk_dCL_ddn(a0)), mk_clo(L2343, 12, 11, (V[]){a8, a7, a6, a5, FLD(s2342, 3), FLD(s2342, 1), FLD(s2342, 0), a3, a2, a1, a0}));
} else {
return F_Chk_dK_derr(a7, C1(1, S2344()), C1(2, F_Chk_dAll_da(a3)), a2, F_Chk_dCL_ddn(a0));
}
}
static V W_Chk_dcheck_delim_dadt(V *a) { (void)a; return F_Chk_dcheck_delim_dadt(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Chk_dAD_dcs(V a0) {
top:;
V v2345 = a0;
return FLD(v2345, 3);
}
static V W_Chk_dAD_dcs(V *a) { (void)a; return F_Chk_dAD_dcs(a[0]); }
static V L2348(V *a) {
return F_Bool_dnot(F_Chk_dctx__dead(a[1], a[0]));
}
static V S2349(void) { static V c; return STRC(c, "cases for "); }
static V S2350(void) { static V c; return STRC(c, ", "); }
static V L2347(V *a) {
return F_Chk_dK_dif(F_Chk_dLazy_dand(F_Bool_dnot(F_Chk_dLst_dempty(a[4])), mk_clo(L2348, 3, 2, (V[]){a[3], a[5]})), F_Chk_dK_derr(a[3], C1(1, F_String_dappend(S2349(), F_String_djoin(F_Chk_dCtrD_dnames(a[4]), S2350()))), C1(2, C1(18, a[2])), a[1], F_Chk_dCL_ddn(a[0])), F_Chk_dK_dpure(IMM(0)));
}
static V F_Chk_dcheck_delim_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11) {
top:;
V s2346 = a1;
if (TAG(s2346) == 18) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2347, 6, 5, (V[]){a0, a2, FLD(s2346, 0), a10, a7}));
} else if (TAG(s2346) == 17) {
return F_Chk_dcheck_dmat(a0, FLD(s2346, 0), FLD(s2346, 1), FLD(s2346, 2), a2, a3, a4, a5, a6, F_Chk_dctrs__find(a7, FLD(s2346, 0)), a8, a9, a10, a11);
} else {
return F_Chk_dK_dpure(IMM(0));
}
}
static V W_Chk_dcheck_delim_dgo(V *a) { (void)a; return F_Chk_dcheck_delim_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11]); }
static V F_Chk_dctrs__find(V a0, V a1) {
top:;
V s2351 = a0;
if ((s2351) == IMM(0)) {
return IMM(0);
} else if (TAG(s2351) == 1) {
return F_Chk_dctrs__find_dif(C3(0, FLD(FLD(s2351, 0), 0), FLD(FLD(s2351, 0), 1), FLD(FLD(s2351, 0), 2)), FLD(s2351, 1), a1, F_String_deq(a1, FLD(FLD(s2351, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctrs__find(V *a) { (void)a; return F_Chk_dctrs__find(a[0], a[1]); }
static V F_Chk_dctrs__find_dif(V a0, V a1, V a2, V a3) {
top:;
V s2352 = a3;
if ((s2352) == IMM(1)) {
return C1(1, a0);
} else if ((s2352) == IMM(0)) {
return F_Chk_dctrs__find(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctrs__find_dif(V *a) { (void)a; return F_Chk_dctrs__find_dif(a[0], a[1], a[2], a[3]); }
static V S2354(void) { static V c; return STRC(c, "a constructor of "); }
static V S2355(void) { static V c; return STRC(c, " (missing, or already matched)"); }
static V L2360(V *a) {
return F_Chk_dK_dpure(F_Chk_duses__join(a[0], a[1]));
}
static V L2359(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[10], a[9], a[8], CN(11, 6, (V[]){F_Chk_dAll_dq(a[7]), F_Chk_dAll_dk(a[7]), 0u, C4(14, a[6], a[5], a[4], F_List_dappend(a[3], C2(1, a[2], IMM(0)))), F_Chk_dAll_db(a[7]), a[4]}), a[1], a[0]), mk_clo(L2360, 2, 1, (V[]){a[11]}));
}
static V L2358(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[14], a[13], a[12], F_Chk_dmat__goal(a[15], a[11], a[10], IMM(0), F_Chk_dAll_db(a[9]), a[8], a[7], F_Chk_dAll_dq(a[9]), a[6], F_Chk_dCL_ddn(a[5])), a[6], a[4]), mk_clo(L2359, 12, 11, (V[]){a[4], a[6], a[8], a[0], a[7], a[1], a[2], a[9], a[12], a[3], a[5]}));
}
static V L2357(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2358, 16, 15, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14]}));
}
static V L2356(V *a) {
return F_Chk_dK_dbind(F_Chk_dCL_dext(a[12], a[11], a[10]), mk_clo(L2357, 15, 14, (V[]){a[0], a[1], a[2], a[3], a[4], a[12], a[5], a[6], a[11], a[7], a[10], a[13], a[8], a[9]}));
}
static V F_Chk_dcheck_dmat(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11, V a12, V a13) {
top:;
V s2353 = a9;
if ((s2353) == IMM(0)) {
return F_Chk_dK_derr(a12, C1(1, F_String_dappend(S2354(), F_String_dappend(a6, S2355()))), C1(2, C4(17, a1, a2, a3, a4)), a4, F_Chk_dCL_ddn(a0));
} else if (TAG(s2353) == 1) {
return F_Chk_dK_dbind(F_Chk_dtele__fill(FLD(FLD(s2353, 0), 2), a7, a12, F_Chk_dCL_ddn(a0), a4), mk_clo(L2356, 14, 13, (V[]){a8, a7, a6, a3, a13, a12, a4, a5, a10, a2, FLD(FLD(s2353, 0), 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcheck_dmat(V *a) { (void)a; return F_Chk_dcheck_dmat(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13]); }
static V F_Chk_duses__join(V a0, V a1) {
top:;
return F_Chk_duses__merge(1u, a0, a1);
}
static V W_Chk_duses__join(V *a) { (void)a; return F_Chk_duses__join(a[0], a[1]); }
static V S2362(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dAll_dk(V a0) {
top:;
V s2361 = a0;
if (TAG(s2361) == 11) {
return FLD(s2361, 1);
} else {
return S2362();
}
}
static V W_Chk_dAll_dk(V *a) { (void)a; return F_Chk_dAll_dk(a[0]); }
static V L2365(V *a) {
return F_Chk_dK_dpure(CN(0, 6, (V[]){F_Chk_dlhs__ext(a[8], a[7], a[6], a[5], IMM(0)), F_Nat_dadd(a[4], a[5]), a[3], a[2], a[1], a[0]}));
}
static V F_Chk_dCL_dext(V a0, V a1, V a2) {
top:;
V v2363 = a0;
V s2364 = FLD(v2363, 1);
if ((s2364) == 0) {
return F_Chk_dK_dpure(CN(0, 6, (V[]){FLD(v2363, 0), FLD(v2363, 1), FLD(v2363, 2), FLD(v2363, 3), FLD(v2363, 4), FLD(v2363, 5)}));
} else if (nat_ge(s2364, 1)) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2365, 9, 8, (V[]){FLD(v2363, 5), FLD(v2363, 4), FLD(v2363, 3), FLD(v2363, 2), nat_subk(s2364, 1), a2, a1, FLD(v2363, 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCL_dext(V *a) { (void)a; return F_Chk_dCL_dext(a[0], a[1], a[2]); }
static V L2368(V *a) {
return F_Chk_dtele__fill(F_Chk_dclo__apply(a[6], F_Chk_dAll_db(a[5]), C2(1, a[4], IMM(0))), a[3], a[2], a[1], a[0]);
}
static V L2367(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2368, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V F_Chk_dtele__fill(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2366 = a1;
if ((s2366) == IMM(0)) {
return F_Chk_dK_dpure(a0);
} else if (TAG(s2366) == 1) {
return F_Chk_dK_dbind(F_Chk_dtele__head(a0, a2, a3, a4), mk_clo(L2367, 6, 5, (V[]){a4, a3, a2, FLD(s2366, 1), FLD(s2366, 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dtele__fill(V *a) { (void)a; return F_Chk_dtele__fill(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dCtrD_dnames(V a0) {
top:;
V s2369 = a0;
if ((s2369) == IMM(0)) {
return IMM(0);
} else if (TAG(s2369) == 1) {
return C2(1, FLD(FLD(s2369, 0), 0), F_Chk_dCtrD_dnames(FLD(s2369, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCtrD_dnames(V *a) { (void)a; return F_Chk_dCtrD_dnames(a[0]); }
static V L2371(V *a) {
return F_Chk_dctx__dead_dty(a[1], F_Chk_dterm__wnf(a[1], a[0]));
}
static V L2372(V *a) {
return F_Chk_dctx__dead(a[1], a[0]);
}
static V F_Chk_dctx__dead(V a0, V a1) {
top:;
V s2370 = a1;
if ((s2370) == IMM(0)) {
return IMM(0);
} else if (TAG(s2370) == 1 && TAG(FLD(s2370, 0)) == 33) {
return F_Chk_dLazy_dor(F_Chk_dLazy_dand(F_Bool_dnot(F_Chk_dQ_dis__none(FLD(FLD(s2370, 0), 1))), mk_clo(L2371, 3, 2, (V[]){FLD(FLD(s2370, 0), 3), a0})), mk_clo(L2372, 3, 2, (V[]){FLD(s2370, 1), a0}));
} else if (TAG(s2370) == 1) {
{ V t0 = a0; V t1 = FLD(s2370, 1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctx__dead(V *a) { (void)a; return F_Chk_dctx__dead(a[0], a[1]); }
static V F_Chk_dctx__dead_dty(V a0, V a1) {
top:;
V s2373 = a1;
if (TAG(s2373) == 14) {
return F_Chk_dctx__dead_dtld(F_Chk_dbook__tld(a0, FLD(s2373, 0)), FLD(s2373, 3));
} else {
return IMM(0);
}
}
static V W_Chk_dctx__dead_dty(V *a) { (void)a; return F_Chk_dctx__dead_dty(a[0], a[1]); }
static V F_Chk_dctx__dead_dtld(V a0, V a1) {
top:;
V s2374 = a0;
if (TAG(s2374) == 1 && TAG(FLD(s2374, 0)) == 1) {
return F_Chk_dLst_dempty(F_Chk_dctrs__drop(FLD(FLD(s2374, 0), 3), a1));
} else {
return IMM(0);
}
}
static V W_Chk_dctx__dead_dtld(V *a) { (void)a; return F_Chk_dctx__dead_dtld(a[0], a[1]); }
static V L2376(V *a) {
return F_Chk_dK_dif(F_Chk_dcheck_dlit_dbase(F_Chk_dbook__tld(a[8], a[7]), a[6], F_Chk_dlit_dctr(F_Chk_dLit_dv(a[5]))), F_Chk_dK_dpure(IMM(0)), F_Chk_dterm__check(a[4], F_Chk_dlit__step(a[5]), a[3], a[2], a[1], a[0]));
}
static V F_Chk_dcheck_dlit(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2375 = a2;
if (TAG(s2375) == 14) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2376, 9, 8, (V[]){a6, a5, a4, a3, a0, a1, FLD(s2375, 3), FLD(s2375, 0)}));
} else {
return F_Chk_dterm__check(a0, F_Chk_dlit__step(a1), a3, a4, a5, a6);
}
}
static V W_Chk_dcheck_dlit(V *a) { (void)a; return F_Chk_dcheck_dlit(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dLit_dv(V a0) {
top:;
V s2377 = a0;
if (TAG(s2377) == 16) {
return FLD(s2377, 0);
} else {
return C1(0, 0u);
}
}
static V W_Chk_dLit_dv(V *a) { (void)a; return F_Chk_dLit_dv(a[0]); }
static V S2379(void) { static V c; return STRC(c, "Zero"); }
static V S2380(void) { static V c; return STRC(c, "Succ"); }
static V S2381(void) { static V c; return STRC(c, "SNil"); }
static V S2382(void) { static V c; return STRC(c, "SCon"); }
static V F_Chk_dlit_dctr(V a0) {
top:;
V s2378 = a0;
if (TAG(s2378) == 0 && (FLD(s2378, 0)) == 0) {
return S2379();
} else if (TAG(s2378) == 0) {
return S2380();
} else if (TAG(s2378) == 1 && (FLD(s2378, 0)) == IMM(0)) {
return S2381();
} else if (TAG(s2378) == 1) {
return S2382();
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlit_dctr(V *a) { (void)a; return F_Chk_dlit_dctr(a[0]); }
static V F_Chk_dcheck_dlit_dbase(V a0, V a1, V a2) {
top:;
V s2383 = a0;
if (TAG(s2383) == 1 && TAG(FLD(s2383, 0)) == 1) {
return F_Bool_dand(F_Chk_dcheck_dlit_dbase__adt(FLD(FLD(s2383, 0), 3)), F_Maybe_dis__some(F_Chk_dctrs__find(F_Chk_dctrs__drop(FLD(FLD(s2383, 0), 3), a1), a2)));
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
static V L2386(V *a) {
return F_Chk_dcheck_dctr_dfind(a[10], a[9], a[8], a[7], a[6], a[5], F_Chk_dAD_dcs(a[4]), F_Chk_dctrs__find(F_Chk_dAD_dcs(a[4]), a[9]), a[3], a[2], a[1], a[0]);
}
static V L2385(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2386, 12, 11, (V[]){a[0], a[1], a[2], a[3], a[10], a[4], a[5], a[6], a[7], a[8], a[9]}));
}
static V L2387(V *a) {
return F_Chk_dK_dif(F_Maybe_dis__some(F_Chk_dbook__ctr(a[6], a[5])), F_Chk_dK_derr(a[4], C1(2, a[3]), C1(2, C3(4, F_Chk_dbook__fam(a[6], a[5]), a[2], IMM(0))), a[2], F_Chk_dCL_ddn(a[1])), F_Chk_dcheck_dtypeless(a[1], C3(15, a[5], a[0], a[2]), a[3], a[4], a[2]));
}
static V F_Chk_dcheck_dctr(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s2384 = a4;
if (TAG(s2384) == 14) {
return F_Chk_dK_dbind(F_Chk_dbook__adt(C4(14, FLD(s2384, 0), FLD(s2384, 1), FLD(s2384, 2), FLD(s2384, 3)), a7, F_Chk_dCL_ddn(a0)), mk_clo(L2385, 11, 10, (V[]){a8, a7, a6, a5, FLD(s2384, 1), FLD(s2384, 0), a3, a2, a1, a0}));
} else {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2387, 7, 6, (V[]){a2, a0, a3, a6, a7, a1}));
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
V s2388 = a1;
if (TAG(s2388) == 1) {
return F_Chk_dbook__fam_dgo(a0, F_Chk_dterm__strip(FLD(FLD(s2388, 0), 2)), 0u, a2);
} else if ((s2388) == IMM(0)) {
return a2;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dbook__fam_dctr(V *a) { (void)a; return F_Chk_dbook__fam_dctr(a[0], a[1], a[2]); }
static V F_Chk_dbook__fam_dgo(V a0, V a1, V a2, V a3) {
top:;
V s2389 = a1;
if (TAG(s2389) == 11) {
{ V t0 = a0; V t1 = F_Chk_dterm__strip(F_Chk_dclo__apply(a0, FLD(s2389, 4), C2(1, C3(0, FLD(s2389, 1), a2, IMM(0)), IMM(0)))); V t2 = F_U32_dinc(a2); V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s2389) == 14) {
return FLD(s2389, 0);
} else {
return a3;
}
}
static V W_Chk_dbook__fam_dgo(V *a) { (void)a; return F_Chk_dbook__fam_dgo(a[0], a[1], a[2], a[3]); }
static V S2392(void) { static V c; return STRC(c, "a declared constructor ("); }
static V S2393(void) { static V c; return STRC(c, " declares "); }
static V S2394(void) { static V c; return STRC(c, ", "); }
static V S2395(void) { static V c; return STRC(c, ")"); }
static V L2391(V *a) {
return F_Chk_dK_dif(F_Maybe_dis__some(F_Chk_dbook__ctr(a[8], a[7])), F_Chk_dK_derr(a[6], C1(2, a[5]), C1(2, C3(4, F_Chk_dbook__fam(a[8], a[7]), a[4], IMM(0))), a[4], F_Chk_dCL_ddn(a[3])), F_Chk_dK_derr(a[6], C1(1, F_String_dappend(S2392(), F_String_dappend(a[2], F_String_dappend(S2393(), F_String_dappend(F_String_djoin(F_Chk_dCtrD_dnames(a[1]), S2394()), S2395()))))), C1(2, C3(15, a[7], a[0], a[4])), a[4], F_Chk_dCL_ddn(a[3])));
}
static V S2396(void) { static V c; return STRC(c, " with "); }
static V S2397(void) { static V c; return STRC(c, " field"); }
static V S2398(void) { static V c; return STRC(c, " fields"); }
static V F_Chk_dcheck_dctr_dfind(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10, V a11) {
top:;
V s2390 = a7;
if ((s2390) == IMM(0)) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2391, 9, 8, (V[]){a2, a6, a4, a0, a3, a9, a10, a1}));
} else if (TAG(s2390) == 1) {
return F_Chk_dK_dif(F_Nat_dis__eq(FLD(FLD(s2390, 0), 1), F_List_dlength(a2)), F_Chk_dcheck_dctr_dfields(a0, FLD(FLD(s2390, 0), 2), a2, a3, a5, a8, a10, a11), F_Chk_dK_derr(a10, C1(1, F_String_dappend(a1, F_String_dappend(S2396(), F_String_dappend(F_Nat_dshow(FLD(FLD(s2390, 0), 1)), F_Bool_dpick(F_Nat_dis__eq(FLD(FLD(s2390, 0), 1), 1u), S2397(), S2398()))))), C1(2, C3(15, a1, a2, a3)), a3, F_Chk_dCL_ddn(a0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcheck_dctr_dfind(V *a) { (void)a; return F_Chk_dcheck_dctr_dfind(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11]); }
static V L2400(V *a) {
return F_Chk_dK_dpure(F_Pair_dfst(a[0]));
}
static V L2399(V *a) {
return F_Chk_dK_dbind(F_Chk_dtele__check(a[5], a[6], a[4], a[3], a[2], a[1], a[0], IMM(0)), mk_clo(L2400, 1, 0, 0));
}
static V F_Chk_dcheck_dctr_dfields(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
return F_Chk_dK_dbind(F_Chk_dtele__fill(a1, a4, a6, F_Chk_dCL_ddn(a0), a3), mk_clo(L2399, 7, 6, (V[]){a3, a7, a6, a5, a2, a0}));
}
static V W_Chk_dcheck_dctr_dfields(V *a) { (void)a; return F_Chk_dcheck_dctr_dfields(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V L2405(V *a) {
return F_Chk_dK_dpure(F_Chk_duses__add(a[0], a[1]));
}
static V L2404(V *a) {
return F_Chk_dK_dbind(F_Chk_dcheck_dlet_dused(a[6], a[5], a[4], a[3], a[2], a[1], a[7]), mk_clo(L2405, 2, 1, (V[]){a[0]}));
}
static V L2403(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[12], F_Chk_dclo__apply(a[13], a[11], F_Chk_dlet_dvars(a[10], a[9], a[8])), a[7], a[6], a[5], F_U32_dadd(a[8], a[4])), mk_clo(L2404, 8, 7, (V[]){a[0], a[1], a[8], a[2], a[3], a[10], a[12]}));
}
static V F_Chk_dcheck_dlet_dbody(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10) {
top:;
V v2401 = a10;
V v2402 = F_U32_dfrom__nat(F_List_dlength(a1));
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2403, 14, 13, (V[]){FLD(v2401, 1), a4, a8, a5, v2402, FLD(v2401, 0), a7, a6, a9, a2, a1, a3, a0}));
}
static V W_Chk_dcheck_dlet_dbody(V *a) { (void)a; return F_Chk_dcheck_dlet_dbody(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10]); }
static V L2408(V *a) {
return F_Chk_dcheck_dlet_dused(a[6], a[5], a[4], a[3], F_U32_dinc(a[2]), a[1], F_Chk_duses__del(a[0], a[2]));
}
static V F_Chk_dcheck_dlet_dused(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2406 = a1;
V s2407 = a2;
if (TAG(s2406) == 1 && TAG(s2407) == 1) {
return F_Chk_dK_dbind(F_Chk_dquant__used(a3, FLD(s2406, 0), FLD(s2407, 0), F_Chk_duses__get(a6, a4), a5, F_Chk_dCL_ddn(a0)), mk_clo(L2408, 8, 7, (V[]){a6, a5, a4, a3, FLD(s2407, 1), FLD(s2406, 1), a0}));
} else {
return F_Chk_dK_dpure(a6);
}
}
static V W_Chk_dcheck_dlet_dused(V *a) { (void)a; return F_Chk_dcheck_dlet_dused(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_duses__del(V a0, V a1) {
top:;
V s2409 = a0;
if ((s2409) == IMM(0)) {
return IMM(0);
} else if (TAG(s2409) == 1) {
return F_Chk_duses__del_dif(C2(0, FLD(FLD(s2409, 0), 0), FLD(FLD(s2409, 0), 1)), F_Chk_duses__del(FLD(s2409, 1), a1), F_U32_dis__eq(a1, FLD(FLD(s2409, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duses__del(V *a) { (void)a; return F_Chk_duses__del(a[0], a[1]); }
static V F_Chk_duses__del_dif(V a0, V a1, V a2) {
top:;
V s2410 = a2;
if ((s2410) == IMM(1)) {
return a1;
} else if ((s2410) == IMM(0)) {
return C2(1, a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duses__del_dif(V *a) { (void)a; return F_Chk_duses__del_dif(a[0], a[1], a[2]); }
static V F_Chk_duses__get(V a0, V a1) {
top:;
V s2411 = a0;
if ((s2411) == IMM(0)) {
return IMM(0);
} else if (TAG(s2411) == 1) {
return F_Chk_duses__get_dif(FLD(FLD(s2411, 0), 1), FLD(s2411, 1), a1, F_U32_dis__eq(a1, FLD(FLD(s2411, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duses__get(V *a) { (void)a; return F_Chk_duses__get(a[0], a[1]); }
static V F_Chk_duses__get_dif(V a0, V a1, V a2, V a3) {
top:;
V s2412 = a3;
if ((s2412) == IMM(1)) {
return a0;
} else if ((s2412) == IMM(0)) {
return F_Chk_duses__get(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duses__get_dif(V *a) { (void)a; return F_Chk_duses__get_dif(a[0], a[1], a[2], a[3]); }
static V S2413(void) { static V c; return STRC(c, " (consumed more than once)"); }
static V F_Chk_dquant__used(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dK_dif(F_Chk_dQ_deq(F_Chk_dquant__join(a3, a2), a2), F_Chk_dK_dpure(IMM(0)), F_Chk_dK_derr(a0, C1(1, F_String_dappend(F_Chk_dquant__show(a2), a1)), C1(1, F_Bool_dpick(F_Chk_dQ_dis__many(a3), F_String_dappend(a1, S2413()), F_String_dappend(F_Chk_dquant__show(a3), a1))), a4, a5));
}
static V W_Chk_dquant__used(V *a) { (void)a; return F_Chk_dquant__used(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dlet_dvars(V a0, V a1, V a2) {
top:;
V s2414 = a0;
V s2415 = a1;
if (TAG(s2414) == 1 && TAG(s2415) == 1) {
return C2(1, C4(3, FLD(s2414, 0), a2, IMM(0), FLD(s2415, 0)), F_Chk_dlet_dvars(FLD(s2414, 1), FLD(s2415, 1), F_U32_dinc(a2)));
} else {
return IMM(0);
}
}
static V W_Chk_dlet_dvars(V *a) { (void)a; return F_Chk_dlet_dvars(a[0], a[1], a[2]); }
static V L2420(V *a) {
return F_Chk_dcheck_dlets(a[12], a[11], a[10], a[9], a[8], a[7], F_Chk_dctx__bind(a[6], F_U32_dadd(a[5], a[4]), a[3], a[2], F_Chk_dIR_dty(a[1])), a[5], F_U32_dinc(a[4]), F_Chk_duses__add(a[0], F_Chk_dIR_dus(a[1])));
}
static V L2419(V *a) {
return F_Chk_dK_dbind(F_Chk_dcheck__kind(a[11], F_Chk_dIR_dty(a[12]), a[10], a[9], a[8], IMM(0)), mk_clo(L2420, 14, 13, (V[]){a[0], a[12], a[1], a[10], a[2], a[8], a[3], a[9], a[4], a[5], a[6], a[7], a[11]}));
}
static V F_Chk_dcheck_dlets(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9) {
top:;
V s2416 = a1;
V s2417 = a2;
V s2418 = a3;
if (TAG(s2416) == 1 && TAG(s2417) == 1 && TAG(s2418) == 1) {
return F_Chk_dK_dbind(F_Chk_dterm__infer(a0, FLD(s2417, 0), F_Chk_dquant__dem(FLD(s2418, 0), a4), a5, a7, IMM(0)), mk_clo(L2419, 13, 12, (V[]){a9, FLD(s2416, 0), a8, a6, a4, FLD(s2418, 1), FLD(s2417, 1), FLD(s2416, 1), a7, a5, FLD(s2418, 0), a0}));
} else {
return F_Chk_dK_dpure(C2(0, a6, a9));
}
}
static V W_Chk_dcheck_dlets(V *a) { (void)a; return F_Chk_dcheck_dlets(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]); }
static V L2422(V *a) {
return F_Chk_dcheck__kind_dgo(apply(F_Chk_dterm__check(a[5], a[4], IMM(0), a[3], a[2], a[1]), a[6]), a[3], a[0]);
}
static V F_Chk_dcheck__kind(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v2421 = C2(7, C2(9, F_Chk_dlhs__kind(a0, a2), a5), a5);
return mk_clo(L2422, 7, 6, (V[]){a5, a4, a3, v2421, a1, a0});
}
static V W_Chk_dcheck__kind(V *a) { (void)a; return F_Chk_dcheck__kind(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dcheck__kind_dgo(V a0, V a1, V a2) {
top:;
V s2423 = a0;
if (TAG(s2423) == 1) {
return C1(1, C2(0, IMM(0), F_Pair_dsnd(FLD(s2423, 0))));
} else if (TAG(s2423) == 0) {
return C1(0, F_Chk_dcheck__kind_derr(FLD(s2423, 0), a1, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcheck__kind_dgo(V *a) { (void)a; return F_Chk_dcheck__kind_dgo(a[0], a[1], a[2]); }
static V F_Chk_dcheck__kind_derr(V a0, V a1, V a2) {
top:;
V v2424 = a0;
return CN(0, 7, (V[]){FLD(v2424, 0), FLD(v2424, 1), FLD(v2424, 2), FLD(v2424, 3), F_Bool_dpick(F_Chk_dMsg_dis__kind(FLD(v2424, 2), a1), a2, FLD(v2424, 4)), FLD(v2424, 5), FLD(v2424, 6)});
}
static V W_Chk_dcheck__kind_derr(V *a) { (void)a; return F_Chk_dcheck__kind_derr(a[0], a[1], a[2]); }
static V F_Chk_dMsg_dis__kind(V a0, V a1) {
top:;
V s2425 = a0;
V s2426 = a1;
if (TAG(s2425) == 2 && TAG(FLD(s2425, 0)) == 7 && TAG(FLD(FLD(s2425, 0), 0)) == 9 && TAG(s2426) == 7 && TAG(FLD(s2426, 0)) == 9) {
return F_Bool_dand(F_Chk_dQ_deq(FLD(FLD(FLD(s2425, 0), 0), 0), FLD(FLD(s2426, 0), 0)), F_Chk_dSp_deq(FLD(FLD(FLD(s2425, 0), 0), 1), FLD(FLD(s2426, 0), 1)));
} else {
return IMM(0);
}
}
static V W_Chk_dMsg_dis__kind(V *a) { (void)a; return F_Chk_dMsg_dis__kind(a[0], a[1]); }
static V F_Chk_dSp_deq(V a0, V a1) {
top:;
V s2427 = a0;
V s2428 = a1;
if ((s2427) == IMM(0) && (s2428) == IMM(0)) {
return IMM(1);
} else if (TAG(s2427) == 1 && TAG(s2428) == 1) {
return F_Bool_dand(F_U32_dis__eq(FLD(s2427, 1), FLD(s2428, 1)), F_U32_dis__eq(FLD(s2427, 2), FLD(s2428, 2)));
} else {
return IMM(0);
}
}
static V W_Chk_dSp_deq(V *a) { (void)a; return F_Chk_dSp_deq(a[0], a[1]); }
static V L2437(V *a) {
return F_Chk_dK_dpure(F_Chk_duses__del(a[1], a[0]));
}
static V L2436(V *a) {
return F_Chk_dK_dbind(F_Chk_dquant__used(a[5], a[4], a[3], F_Chk_duses__get(a[6], a[2]), a[1], F_Chk_dCL_ddn(a[0])), mk_clo(L2437, 3, 2, (V[]){a[2], a[6]}));
}
static V L2435(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(a[11], F_Chk_dclo__apply(a[12], a[10], C2(1, a[9], IMM(0))), a[8], F_Chk_dclo__apply(a[12], a[7], C2(1, a[9], IMM(0))), F_Chk_dctx__bind(a[6], a[5], a[4], a[3], a[2]), F_U32_dinc(a[5])), mk_clo(L2436, 7, 6, (V[]){a[0], a[1], a[5], a[4], a[3], a[6]}));
}
static V L2434(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2435, 13, 12, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11]}));
}
static V L2433(V *a) {
return F_Chk_dK_dbind(F_Chk_dCL_dunder(a[10], a[9]), mk_clo(L2434, 12, 11, (V[]){a[10], a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[9], a[8]}));
}
static V F_Chk_dcheck_dlam(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9) {
top:;
V s2429 = a5;
if (TAG(s2429) == 11) {
V v2430 = C3(0, a1, a9, IMM(0));
V v2431 = F_Bool_dand(F_Chk_dQ_dis__many(a4), F_Chk_dQ_dis__lone(FLD(s2429, 0)));
V v2432 = F_Bool_dpick(v2431, IMM(2), FLD(s2429, 0));
return F_Chk_dK_dbind(F_Chk_dK_dif(v2431, F_Chk_dcheck__kind(a0, FLD(s2429, 3), v2432, a8, a9, a3), F_Chk_dK_dpure(IMM(0))), mk_clo(L2433, 12, 11, (V[]){a3, FLD(s2429, 3), a1, v2432, a9, a8, FLD(s2429, 4), a6, a2, v2430, a0}));
} else {
return F_Chk_dcheck_dtypeless(a0, CN(12, 5, (V[]){a1, 0u, a2, a3, a4}), a7, a8, a3);
}
}
static V W_Chk_dcheck_dlam(V *a) { (void)a; return F_Chk_dcheck_dlam(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]); }
static V L2440(V *a) {
return F_Chk_dK_dpure(CN(0, 6, (V[]){F_Chk_dterm__apply1(a[7], a[6], a[5]), a[4], a[3], a[2], a[1], a[0]}));
}
static V F_Chk_dCL_dunder(V a0, V a1) {
top:;
V v2438 = a0;
V s2439 = FLD(v2438, 1);
if ((s2439) == 0) {
return F_Chk_dK_dpure(CN(0, 6, (V[]){FLD(v2438, 0), FLD(v2438, 1), FLD(v2438, 2), FLD(v2438, 3), FLD(v2438, 4), FLD(v2438, 5)}));
} else if (nat_ge(s2439, 1)) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2440, 8, 7, (V[]){FLD(v2438, 5), FLD(v2438, 4), FLD(v2438, 3), FLD(v2438, 2), nat_subk(s2439, 1), a1, FLD(v2438, 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCL_dunder(V *a) { (void)a; return F_Chk_dCL_dunder(a[0], a[1]); }
static V F_Chk_dQ_dis__lone(V a0) {
top:;
V s2441 = a0;
if ((s2441) == IMM(1)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dQ_dis__lone(V *a) { (void)a; return F_Chk_dQ_dis__lone(a[0]); }
static V S2444(void) { static V c; return STRC(c, "~"); }
static V S2447(void) { static V c; return STRC(c, "a fresh ~ binder name"); }
static V S2448(void) { static V c; return STRC(c, ""); }
static V L2451(V *a) {
return F_Chk_ddef__check_dtmpl(a[5], a[4], C3(13, a[3], C3(4, a[2], IMM(0), IMM(0)), IMM(0)), F_Chk_dterm__apply1(a[6], a[1], C3(4, a[2], IMM(0), IMM(0))), F_Chk_dclo__apply(a[6], F_Chk_dAll_db(a[0]), C2(1, C3(4, a[2], IMM(0), IMM(0)), IMM(0))));
}
static V L2450(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2451, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L2449(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dset__book(F_Chk_dbook__set(a[6], a[5], CN(0, 7, (V[]){0u, 0u, F_Chk_dAll_da(a[4]), IMM(0), IMM(0), IMM(1), IMM(0)}))), mk_clo(L2450, 7, 6, (V[]){a[4], a[0], a[5], a[1], a[2], a[3]}));
}
static V L2446(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dif(F_Chk_dbook__has(a[6], a[5]), F_Chk_dK_derr(IMM(0), C1(1, S2447()), C1(1, F_Chk_dAll_dk(a[4])), IMM(0), S2448()), F_Chk_dK_dpure(IMM(0))), mk_clo(L2449, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L2445(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2446, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L2443(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_String_dappend(a[3], F_String_dappend(S2444(), F_Chk_dAll_dk(a[4])))), mk_clo(L2445, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V F_Chk_ddef__check_dtmpl(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2442 = a1;
if ((s2442) == 0) {
return F_Chk_dK_dpure(C2(0, a2, C2(0, a3, a4)));
} else if (nat_ge(s2442, 1)) {
return F_Chk_dK_dbind(F_Chk_dtele__head(a4, IMM(0), a0, IMM(0)), mk_clo(L2443, 5, 4, (V[]){a3, a2, nat_subk(s2442, 1), a0}));
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
V s2452 = a1;
if (TAG(s2452) == 11) {
{ V t0 = a0; V t1 = F_Chk_dterm__wnf(a0, F_Chk_dclo__apply(a0, FLD(s2452, 4), C2(1, C3(0, FLD(s2452, 1), a2, IMM(0)), IMM(0)))); V t2 = F_U32_dinc(a2); V t3 = F_List_dappend(a3, C2(1, C3(0, FLD(s2452, 0), FLD(s2452, 1), FLD(s2452, 3)), IMM(0))); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else {
return C2(0, a3, s2452);
}
}
static V W_Chk_dtele__unbind_dgo(V *a) { (void)a; return F_Chk_dtele__unbind_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dDom_dqs(V a0) {
top:;
V s2453 = a0;
if ((s2453) == IMM(0)) {
return IMM(0);
} else if (TAG(s2453) == 1) {
return C2(1, FLD(FLD(s2453, 0), 0), F_Chk_dDom_dqs(FLD(s2453, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dDom_dqs(V *a) { (void)a; return F_Chk_dDom_dqs(a[0]); }
static V F_Chk_dTld_dimps(V a0) {
top:;
V s2454 = a0;
if (TAG(s2454) == 0) {
return FLD(s2454, 6);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dimps(V *a) { (void)a; return F_Chk_dTld_dimps(a[0]); }
static V S2458(void) { static V c; return STRC(c, "a foreign definition returning base IO(...) directly (return type aliases are not unfolded)"); }
static V L2457(V *a) {
return F_Chk_dK_dif(F_Chk_dvalid_dio(a[1], F_Chk_dterm__head(a[2])), F_Chk_dK_dpure(IMM(0)), F_Chk_dK_derr(IMM(0), C1(1, S2458()), C1(1, a[0]), F_Chk_dTm_dspan(a[2]), a[0]));
}
static V L2456(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dvalid_dret(a[2], F_Chk_dterm__strip(F_Chk_dTld_dt(a[1])), 0u)), mk_clo(L2457, 3, 2, (V[]){a[0], a[2]}));
}
static V F_Chk_dvalid_dforeign(V a0, V a1, V a2) {
top:;
V s2455 = a2;
if ((s2455) == IMM(0)) {
return F_Chk_dK_dpure(IMM(0));
} else if (TAG(s2455) == 1) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2456, 3, 2, (V[]){a0, a1}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dvalid_dforeign(V *a) { (void)a; return F_Chk_dvalid_dforeign(a[0], a[1], a[2]); }
static V F_Chk_dvalid_dret(V a0, V a1, V a2) {
top:;
V s2459 = a1;
if (TAG(s2459) == 11) {
{ V t0 = a0; V t1 = F_Chk_dterm__strip(F_Chk_dclo__apply(a0, FLD(s2459, 4), C2(1, C3(0, FLD(s2459, 1), a2, IMM(0)), IMM(0)))); V t2 = F_U32_dinc(a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else {
return s2459;
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
V s2460 = a0;
if (TAG(s2460) == 0) {
return CN(0, 7, (V[]){FLD(s2460, 0), FLD(s2460, 1), FLD(s2460, 2), IMM(0), FLD(s2460, 4), FLD(s2460, 5), FLD(s2460, 6)});
} else {
return s2460;
}
}
static V W_Chk_dTld_ddec(V *a) { (void)a; return F_Chk_dTld_ddec(a[0]); }
static V F_Chk_dbook__opened(V a0) {
top:;
V v2461 = a0;
return CN(0, 7, (V[]){FLD(v2461, 0), FLD(v2461, 1), FLD(v2461, 2), FLD(v2461, 3), nat_addk(FLD(v2461, 4), 1), FLD(v2461, 5), FLD(v2461, 6)});
}
static V W_Chk_dbook__opened(V *a) { (void)a; return F_Chk_dbook__opened(a[0]); }
static V F_Chk_dTld_dis__law__open(V a0) {
top:;
V s2462 = a0;
if (TAG(s2462) == 0 && (FLD(s2462, 3)) == IMM(0) && (FLD(s2462, 5)) == IMM(0) && (FLD(s2462, 6)) == IMM(0)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dis__law__open(V *a) { (void)a; return F_Chk_dTld_dis__law__open(a[0]); }
static V L2466(V *a) {
return F_Chk_dvalid_dctrs(a[2], a[1], a[3], a[0]);
}
static V L2465(V *a) {
return F_Chk_dK_dbind(F_Chk_dvalid_dkind(a[3], a[2], a[4]), mk_clo(L2466, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V L2464(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dtele__unbind(a[4], a[3])), mk_clo(L2465, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V L2463(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2464, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Chk_dvalid_dadt(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dK_dbind(F_Chk_dterm__check(F_Chk_dCL_dof(a0, IMM(0)), a2, IMM(0), F_Chk_dtyp(IMM(1)), IMM(0), 0u), mk_clo(L2463, 5, 4, (V[]){a3, a1, a0, a2}));
}
static V W_Chk_dvalid_dadt(V *a) { (void)a; return F_Chk_dvalid_dadt(a[0], a[1], a[2], a[3]); }
static V L2468(V *a) {
return F_Chk_dvalid_dctrs(a[3], a[2], a[1], a[0]);
}
static V F_Chk_dvalid_dctrs(V a0, V a1, V a2, V a3) {
top:;
V s2467 = a3;
if ((s2467) == IMM(0)) {
return F_Chk_dK_dpure(IMM(0));
} else if (TAG(s2467) == 1) {
return F_Chk_dK_dbind(F_Chk_dvalid_dfields(a0, a1, a2, FLD(FLD(s2467, 0), 0), FLD(FLD(s2467, 0), 2), F_Nat_dadd(a1, FLD(FLD(s2467, 0), 1)), 0u, IMM(0)), mk_clo(L2468, 5, 4, (V[]){FLD(s2467, 1), a2, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dvalid_dctrs(V *a) { (void)a; return F_Chk_dvalid_dctrs(a[0], a[1], a[2], a[3]); }
static V L2473(V *a) {
return F_Chk_dvalid_dfields(a[8], a[7], a[6], a[5], F_Chk_dclo__apply(a[9], F_Chk_dAll_db(a[4]), C2(1, C3(0, F_Chk_dAll_dk(a[4]), a[3], IMM(0)), IMM(0))), a[2], F_U32_dinc(a[3]), F_Chk_dctx__bind(a[1], a[3], a[0], F_Chk_dAll_dk(a[4]), F_Chk_dAll_da(a[4])));
}
static V L2472(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2473, 10, 9, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]}));
}
static V L2471(V *a) {
return F_Chk_dK_dbind(F_Chk_dterm__check(F_Chk_dCL_dof(a[7], IMM(0)), F_Chk_dAll_da(a[6]), IMM(0), F_Bool_dpick(F_Bool_dand(F_Nat_dis__ge(F_U32_dto__nat(a[5]), a[4]), F_Chk_dQ_dis__lone(a[8])), a[3], F_Chk_dtyp(a[8])), a[2], a[5]), mk_clo(L2472, 10, 9, (V[]){a[8], a[2], a[0], a[5], a[6], a[7], a[3], a[4], a[1]}));
}
static V L2470(V *a) {
return F_Chk_dK_dbind(F_Chk_dK_dpure(F_Chk_dAll_dq(a[7])), mk_clo(L2471, 9, 8, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[7], a[6]}));
}
static V L2474(V *a) {
return F_Chk_dvalid_dtip(a[4], a[3], a[2], F_Chk_dterm__wnf(a[5], a[1]), a[0]);
}
static V F_Chk_dvalid_dfields(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s2469 = a5;
if (nat_ge(s2469, 1)) {
return F_Chk_dK_dbind(F_Chk_dtele__head(a4, a7, a3, IMM(0)), mk_clo(L2470, 8, 7, (V[]){nat_subk(s2469, 1), a0, a7, a2, a1, a6, a3}));
} else if ((s2469) == 0) {
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2474, 6, 5, (V[]){a7, a4, a3, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dvalid_dfields(V *a) { (void)a; return F_Chk_dvalid_dfields(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S2476(void) { static V c; return STRC(c, "a telescope tipped at "); }
static V S2477(void) { static V c; return STRC(c, " applied to its own parameters"); }
static V L2475(V *a) {
return F_Chk_dK_dif(F_Chk_dvalid_dtip_dok(a[5], a[4], a[3], a[2]), F_Chk_dK_dpure(IMM(0)), F_Chk_dK_derr(a[1], C1(1, F_String_dappend(S2476(), F_String_dappend(a[4], S2477()))), C1(2, a[2]), IMM(0), a[0]));
}
static V F_Chk_dvalid_dtip(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Chk_dK_dbind(F_Chk_dK_dbook(), mk_clo(L2475, 6, 5, (V[]){a2, a4, a3, a1, a0}));
}
static V W_Chk_dvalid_dtip(V *a) { (void)a; return F_Chk_dvalid_dtip(a[0], a[1], a[2], a[3], a[4]); }
static V L2480(V *a) {
return F_Chk_dvalid_dtip_dparams(a[1], a[0], 0u);
}
static V L2479(V *a) {
return F_Chk_dLazy_dand(F_Chk_dLst_dempty(a[2]), mk_clo(L2480, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dvalid_dtip_dok(V a0, V a1, V a2, V a3) {
top:;
V s2478 = a3;
if (TAG(s2478) == 14) {
return F_Chk_dLazy_dand(F_Bool_dand(F_String_deq(a1, FLD(s2478, 0)), F_Nat_dis__eq(F_List_dlength(FLD(s2478, 1)), a2)), mk_clo(L2479, 4, 3, (V[]){FLD(s2478, 1), a0, FLD(s2478, 3)}));
} else {
return IMM(0);
}
}
static V W_Chk_dvalid_dtip_dok(V *a) { (void)a; return F_Chk_dvalid_dtip_dok(a[0], a[1], a[2], a[3]); }
static V L2482(V *a) {
return F_Chk_dvalid_dtip_dparams(a[2], a[1], F_U32_dinc(a[0]));
}
static V F_Chk_dvalid_dtip_dparams(V a0, V a1, V a2) {
top:;
V s2481 = a1;
if ((s2481) == IMM(0)) {
return IMM(1);
} else if (TAG(s2481) == 1) {
return F_Chk_dLazy_dand(F_Chk_dvalid_dtip_dvar(F_Chk_dterm__wnf(a0, FLD(s2481, 0)), a2), mk_clo(L2482, 4, 3, (V[]){a2, FLD(s2481, 1), a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dvalid_dtip_dparams(V *a) { (void)a; return F_Chk_dvalid_dtip_dparams(a[0], a[1], a[2]); }
static V F_Chk_dvalid_dtip_dvar(V a0, V a1) {
top:;
V s2483 = a0;
if (TAG(s2483) == 0) {
return F_U32_dis__eq(FLD(s2483, 1), a1);
} else {
return IMM(0);
}
}
static V W_Chk_dvalid_dtip_dvar(V *a) { (void)a; return F_Chk_dvalid_dtip_dvar(a[0], a[1]); }
static V W_Nat_dis__ge(V *a) { (void)a; return F_Nat_dis__ge(a[0], a[1]); }
static V S2486(void) { static V c; return STRC(c, "a kind (type "); }
static V S2487(void) { static V c; return STRC(c, "<..> is Kind(g))"); }
static V F_Chk_dvalid_dkind(V a0, V a1, V a2) {
top:;
V v2484 = a2;
V s2485 = FLD(v2484, 1);
if (TAG(s2485) == 7) {
return F_Chk_dK_dpure(C2(7, FLD(s2485, 0), FLD(s2485, 1)));
} else {
return F_Chk_dK_derr(F_Chk_dDom_dctx(FLD(v2484, 0), 0u, IMM(0)), C1(1, F_String_dappend(S2486(), F_String_dappend(a0, S2487()))), C1(2, s2485), F_Chk_dSp_dor(F_Chk_dTm_dspan(s2485), F_Chk_dTm_dspan(a1)), a0);
}
}
static V W_Chk_dvalid_dkind(V *a) { (void)a; return F_Chk_dvalid_dkind(a[0], a[1], a[2]); }
static V F_Chk_dDom_dctx(V a0, V a1, V a2) {
top:;
V s2488 = a0;
if ((s2488) == IMM(0)) {
return a2;
} else if (TAG(s2488) == 1) {
{ V t0 = FLD(s2488, 1); V t1 = F_U32_dinc(a1); V t2 = F_Chk_dctx__bind(a2, a1, FLD(FLD(s2488, 0), 0), FLD(FLD(s2488, 0), 1), FLD(FLD(s2488, 0), 2)); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dDom_dctx(V *a) { (void)a; return F_Chk_dDom_dctx(a[0], a[1], a[2]); }
static V F_Chk_dbook__set__ctrs(V a0, V a1) {
top:;
V s2489 = a1;
if ((s2489) == IMM(0)) {
return a0;
} else if (TAG(s2489) == 1) {
{ V t0 = F_Chk_dbook__set__ctr(a0, FLD(FLD(s2489, 0), 0), C3(0, FLD(FLD(s2489, 0), 0), FLD(FLD(s2489, 0), 1), FLD(FLD(s2489, 0), 2))); V t1 = FLD(s2489, 1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dbook__set__ctrs(V *a) { (void)a; return F_Chk_dbook__set__ctrs(a[0], a[1]); }
static V F_Chk_dbook__set__ctr(V a0, V a1, V a2) {
top:;
V v2490 = a0;
return CN(0, 7, (V[]){FLD(v2490, 0), F_Map_dset(FLD(v2490, 1), a1, a2), FLD(v2490, 2), FLD(v2490, 3), FLD(v2490, 4), FLD(v2490, 5), FLD(v2490, 6)});
}
static V W_Chk_dbook__set__ctr(V *a) { (void)a; return F_Chk_dbook__set__ctr(a[0], a[1], a[2]); }
static V F_Chk_dcheck__book_dfin(V a0) {
top:;
V s2491 = a0;
if (TAG(s2491) == 0) {
return C1(0, FLD(s2491, 0));
} else if (TAG(s2491) == 1) {
return F_Chk_dcheck__book_dholes(F_Pair_dsnd(FLD(s2491, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcheck__book_dfin(V *a) { (void)a; return F_Chk_dcheck__book_dfin(a[0]); }
static V S2493(void) { static V c; return STRC(c, " TODO"); }
static V S2494(void) { static V c; return STRC(c, ""); }
static V S2495(void) { static V c; return STRC(c, "s"); }
static V S2496(void) { static V c; return STRC(c, " found.\012The code is incomplete, and not a valid proof yet."); }
static V S2497(void) { static V c; return STRC(c, ""); }
static V S2498(void) { static V c; return STRC(c, "!raw"); }
static V F_Chk_dcheck__book_dholes(V a0) {
top:;
V v2492 = F_Chk_dBook_dholes(a0);
return F_Bool_dpick(F_Nat_dis__eq(v2492, 0u), F_Chk_dcheck__book_downed(a0), C1(0, CN(0, 7, (V[]){F_Chk_dbook__nil(), IMM(0), C1(1, F_String_dappend(F_Nat_dshow(v2492), F_String_dappend(S2493(), F_String_dappend(F_Bool_dpick(F_Nat_dis__eq(v2492, 1u), S2494(), S2495()), S2496())))), IMM(0), IMM(0), S2497(), S2498()})));
}
static V W_Chk_dcheck__book_dholes(V *a) { (void)a; return F_Chk_dcheck__book_dholes(a[0]); }
static V F_Chk_dbook__nil(void) {
top:;
return CN(0, 7, (V[]){IMM(0), IMM(0), IMM(0), 0u, 0u, IMM(0), IMM(0)});
}
static V W_Chk_dbook__nil(V *a) { (void)a; return F_Chk_dbook__nil(); }
static V S2499(void) { static V c; return STRC(c, "Clo.apply"); }
static V S2500(void) { static V c; return STRC(c, "Clo.apply"); }
static V S2501(void) { static V c; return STRC(c, "Clo.apply is a name the compiler encodes itself: name yours apart"); }
static V S2502(void) { static V c; return STRC(c, ""); }
static V S2503(void) { static V c; return STRC(c, "!raw"); }
static V F_Chk_dcheck__book_downed(V a0) {
top:;
return F_Bool_dpick(F_Bool_dand(F_Chk_dbook__has(a0, S2499()), F_Bool_dnot(F_Chk_dTld_dbase__of(F_Chk_dbook__tld(a0, S2500())))), C1(0, CN(0, 7, (V[]){F_Chk_dbook__nil(), IMM(0), C1(1, S2501()), IMM(0), IMM(0), S2502(), S2503()})), C1(1, a0));
}
static V W_Chk_dcheck__book_downed(V *a) { (void)a; return F_Chk_dcheck__book_downed(a[0]); }
static V F_Chk_dTld_dbase__of(V a0) {
top:;
V s2504 = a0;
if (TAG(s2504) == 1 && TAG(FLD(s2504, 0)) == 0) {
return FLD(FLD(s2504, 0), 5);
} else if (TAG(s2504) == 1 && TAG(FLD(s2504, 0)) == 1) {
return FLD(FLD(s2504, 0), 4);
} else if ((s2504) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dTld_dbase__of(V *a) { (void)a; return F_Chk_dTld_dbase__of(a[0]); }
static V F_Chk_dBook_dholes(V a0) {
top:;
V v2505 = a0;
return F_Nat_dadd(FLD(v2505, 3), FLD(v2505, 4));
}
static V W_Chk_dBook_dholes(V *a) { (void)a; return F_Chk_dBook_dholes(a[0]); }
static V F_Main_dcheck_dres(V a0, V a1) {
top:;
V s2506 = a1;
if (TAG(s2506) == 0) {
return F_Main_dchk_dfail(FLD(s2506, 0));
} else if (TAG(s2506) == 1) {
return F_IO_dpure(C2(0, FLD(s2506, 0), a0));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dcheck_dres(V *a) { (void)a; return F_Main_dcheck_dres(a[0], a[1]); }
static V F_Main_dchk_dfail(V a1) {
top:;
return F_IO_ddie(1u, F_Chk_dshow__err(a1));
}
static V W_Main_dchk_dfail(V *a) { (void)a; return F_Main_dchk_dfail(a[1]); }
static V S2508(void) { static V c; return STRC(c, "!raw"); }
static V S2509(void) { static V c; return STRC(c, "Error: "); }
static V F_Chk_dshow__err(V a0) {
top:;
V v2507 = a0;
return F_Bool_dpick(F_String_deq(FLD(v2507, 6), S2508()), F_String_dappend(S2509(), F_Chk_dshow__err_draw(FLD(v2507, 2))), F_Chk_derr__show(CN(0, 7, (V[]){FLD(v2507, 0), FLD(v2507, 1), FLD(v2507, 2), FLD(v2507, 3), FLD(v2507, 4), FLD(v2507, 5), FLD(v2507, 6)})));
}
static V W_Chk_dshow__err(V *a) { (void)a; return F_Chk_dshow__err(a[0]); }
static V S2516(void) { static V c; return STRC(c, ""); }
static V S2517(void) { static V c; return STRC(c, " "); }
static V S2518(void) { static V c; return STRC(c, "Error:"); }
static V S2519(void) { static V c; return STRC(c, ""); }
static V S2520(void) { static V c; return STRC(c, "\012Context:"); }
static V S2521(void) { static V c; return STRC(c, ""); }
static V S2522(void) { static V c; return STRC(c, "\012Location:"); }
static V S2523(void) { static V c; return STRC(c, ""); }
static V S2524(void) { static V c; return STRC(c, "\012"); }
static V F_Chk_derr__show(V a0) {
top:;
V v2510 = a0;
V v2511 = F_Chk_dctx__scope(FLD(v2510, 1));
V v2512 = F_Chk_derr_dmsg(FLD(v2510, 0), FLD(v2510, 2), FLD(v2510, 3), v2511);
V v2513 = F_Chk_derr_dctx__lines(FLD(v2510, 0), F_Chk_dctx__sorted(FLD(v2510, 1)), v2511, F_Chk_dctx__width(FLD(v2510, 1)));
V v2514 = F_Chk_derr_dlines(FLD(v2510, 4));
V v2515 = F_Bool_dpick(F_String_dis__empty(FLD(v2510, 5)), S2516(), F_String_dappend(S2517(), FLD(v2510, 5)));
return F_String_dappend(S2518(), F_String_dappend(v2512, F_String_dappend(F_Bool_dpick(F_Chk_dLst_dempty(FLD(v2510, 1)), S2519(), S2520()), F_String_dappend(v2513, F_String_dappend(F_Bool_dpick(F_Bool_dand(F_String_dis__empty(v2515), F_String_dis__empty(v2514)), S2521(), F_String_dappend(S2522(), F_String_dappend(v2515, v2514))), F_Bool_dpick(F_String_dis__empty(FLD(v2510, 6)), S2523(), F_String_dappend(S2524(), FLD(v2510, 6))))))));
}
static V W_Chk_derr__show(V *a) { (void)a; return F_Chk_derr__show(a[0]); }
static V S2526(void) { static V c; return STRC(c, ""); }
static V F_Chk_derr_dlines(V a0) {
top:;
V s2525 = a0;
if ((s2525) == IMM(0)) {
return S2526();
} else if (TAG(s2525) == 1) {
return F_Chk_derr_dlines_dgo(F_String_dsplit(FLD(s2525, 0), 10u), F_Nat_dadd(1u, F_Chk_dStr_dcount__nl(F_String_dtake(FLD(s2525, 0), F_U32_dto__nat(FLD(s2525, 1))))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_derr_dlines(V *a) { (void)a; return F_Chk_derr_dlines(a[0]); }
static V F_Chk_dStr_dcount__nl(V a0) {
top:;
V s2527 = a0;
if ((s2527) == IMM(0)) {
return 0u;
} else if (TAG(s2527) == 1) {
return F_Nat_dadd(F_Bool_dpick(F_U32_dis__eq(FLD(s2527, 0), 10u), 1u, 0u), F_Chk_dStr_dcount__nl(FLD(s2527, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dcount__nl(V *a) { (void)a; return F_Chk_dStr_dcount__nl(a[0]); }
static V F_Chk_derr_dlines_dgo(V a0, V a1) {
top:;
V v2528 = F_Nat_dmax(1u, F_Nat_dsub(a1, 1u));
V v2529 = F_Nat_dmin(F_List_dlength(a0), F_Nat_dadd(a1, 1u));
V v2530 = F_String_dlength(F_Nat_dshow(v2529));
return F_Chk_derr_dlines_deach(F_Chk_dList_ddrop__str(a0, F_Nat_dsub(v2528, 1u)), v2528, v2529, a1, v2530);
}
static V W_Chk_derr_dlines_dgo(V *a) { (void)a; return F_Chk_derr_dlines_dgo(a[0], a[1]); }
static V F_Chk_dList_ddrop__str(V a0, V a1) {
top:;
V s2531 = a0;
V s2532 = a1;
if ((s2532) == 0) {
return s2531;
} else if (TAG(s2531) == 1 && nat_ge(s2532, 1)) {
{ V t0 = FLD(s2531, 1); V t1 = nat_subk(s2532, 1); a0 = t0; a1 = t1; goto top; }
} else if ((s2531) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dList_ddrop__str(V *a) { (void)a; return F_Chk_dList_ddrop__str(a[0], a[1]); }
static V S2534(void) { static V c; return STRC(c, ""); }
static V F_Chk_derr_dlines_deach(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2533 = a0;
if ((s2533) == IMM(0)) {
return S2534();
} else if (TAG(s2533) == 1) {
return F_Chk_derr_dlines_done(FLD(s2533, 0), FLD(s2533, 1), a1, a2, a3, a4, F_Nat_dis__gt(a1, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_derr_dlines_deach(V *a) { (void)a; return F_Chk_derr_dlines_deach(a[0], a[1], a[2], a[3], a[4]); }
static V S2536(void) { static V c; return STRC(c, ""); }
static V S2537(void) { static V c; return STRC(c, "\012"); }
static V S2538(void) { static V c; return STRC(c, ">| "); }
static V S2539(void) { static V c; return STRC(c, " | "); }
static V F_Chk_derr_dlines_done(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2535 = a6;
if ((s2535) == IMM(1)) {
return S2536();
} else if ((s2535) == IMM(0)) {
return F_String_dappend(S2537(), F_String_dappend(F_Chk_dStr_dpadl(F_Nat_dshow(a2), a5), F_String_dappend(F_Bool_dpick(F_Nat_dis__eq(a2, a4), S2538(), S2539()), F_String_dappend(a0, F_Chk_derr_dlines_deach(a1, nat_addk(a2, 1), a3, a4, a5)))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_derr_dlines_done(V *a) { (void)a; return F_Chk_derr_dlines_done(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S2541(void) { static V c; return STRC(c, " "); }
static V F_Chk_dStr_dpadl(V a0, V a1) {
top:;
V v2540 = F_String_dlength(a0);
return F_String_dappend(F_String_drepeat(S2541(), F_Nat_dsub(a1, v2540)), a0);
}
static V W_Chk_dStr_dpadl(V *a) { (void)a; return F_Chk_dStr_dpadl(a[0], a[1]); }
static V F_String_drepeat(V a0, V a1) {
top:;
V s2542 = a1;
if ((s2542) == 0) {
return IMM(0);
} else if (nat_ge(s2542, 1)) {
return F_String_dappend(a0, F_String_drepeat(a0, nat_subk(s2542, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_String_drepeat(V *a) { (void)a; return F_String_drepeat(a[0], a[1]); }
static V W_Nat_dmin(V *a) { (void)a; return F_Nat_dmin(a[0], a[1]); }
static V W_Nat_dmax(V *a) { (void)a; return F_Nat_dmax(a[0], a[1]); }
static V F_Chk_dctx__width(V a0) {
top:;
V s2543 = a0;
if ((s2543) == IMM(0)) {
return 0u;
} else if (TAG(s2543) == 1 && TAG(FLD(s2543, 0)) == 33) {
return F_Nat_dmax(F_String_dlength(FLD(FLD(s2543, 0), 2)), F_Chk_dctx__width(FLD(s2543, 1)));
} else if (TAG(s2543) == 1) {
{ V t0 = FLD(s2543, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dctx__width(V *a) { (void)a; return F_Chk_dctx__width(a[0]); }
static V F_Chk_dctx__sorted(V a0) {
top:;
return F_List_dreverse(a0);
}
static V W_Chk_dctx__sorted(V *a) { (void)a; return F_Chk_dctx__sorted(a[0]); }
static V S2545(void) { static V c; return STRC(c, ""); }
static V S2546(void) { static V c; return STRC(c, "\012- "); }
static V S2547(void) { static V c; return STRC(c, " : "); }
static V F_Chk_derr_dctx__lines(V a0, V a1, V a2, V a3) {
top:;
V s2544 = a1;
if ((s2544) == IMM(0)) {
return S2545();
} else if (TAG(s2544) == 1 && TAG(FLD(s2544, 0)) == 33) {
return F_String_dappend(S2546(), F_String_dappend(F_Chk_dStr_dpad(FLD(FLD(s2544, 0), 2), a3), F_String_dappend(S2547(), F_String_dappend(F_Chk_dterm__show(F_Chk_dterm__lower(a0, F_Chk_dterm__snf(a0, FLD(FLD(s2544, 0), 3)), FLD(FLD(s2544, 0), 0)), 0u, F_List_dreverse(F_Chk_dList_dtake__str(a2, FLD(FLD(s2544, 0), 0)))), F_Chk_derr_dctx__lines(a0, FLD(s2544, 1), a2, a3)))));
} else if (TAG(s2544) == 1) {
{ V t0 = a0; V t1 = FLD(s2544, 1); V t2 = a2; V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
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
V s2548 = a0;
V s2549 = a1;
if ((s2548) == 0) {
return IMM(0);
} else if (nat_ge(s2548, 1) && TAG(s2549) == 1) {
return C2(1, FLD(s2549, 0), F_Chk_dList_dtake__strn(nat_subk(s2548, 1), FLD(s2549, 1)));
} else if ((s2549) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dList_dtake__strn(V *a) { (void)a; return F_Chk_dList_dtake__strn(a[0], a[1]); }
static V S2551(void) { static V c; return STRC(c, " "); }
static V F_Chk_dStr_dpad(V a0, V a1) {
top:;
V v2550 = F_String_dlength(a0);
return F_String_dappend(a0, F_String_drepeat(S2551(), F_Nat_dsub(a1, v2550)));
}
static V W_Chk_dStr_dpad(V *a) { (void)a; return F_Chk_dStr_dpad(a[0], a[1]); }
static V S2553(void) { static V c; return STRC(c, "\012- message  : "); }
static V S2554(void) { static V c; return STRC(c, "\012- expected : "); }
static V S2555(void) { static V c; return STRC(c, "\012- observed : "); }
static V F_Chk_derr_dmsg(V a0, V a1, V a2, V a3) {
top:;
V s2552 = a2;
if ((s2552) == IMM(0)) {
return F_String_dappend(S2553(), F_Chk_dexpr__show(a0, a1, a3));
} else {
return F_String_dappend(S2554(), F_String_dappend(F_Chk_dexpr__show(a0, a1, a3), F_String_dappend(S2555(), F_Chk_dexpr__show(a0, s2552, a3))));
}
}
static V W_Chk_derr_dmsg(V *a) { (void)a; return F_Chk_derr_dmsg(a[0], a[1], a[2], a[3]); }
static V S2557(void) { static V c; return STRC(c, ""); }
static V F_Chk_dshow__err_draw(V a0) {
top:;
V s2556 = a0;
if (TAG(s2556) == 1) {
return FLD(s2556, 0);
} else {
return S2557();
}
}
static V W_Chk_dshow__err_draw(V *a) { (void)a; return F_Chk_dshow__err_draw(a[0]); }
static V S2559(void) { static V c; return STRC(c, "bendc: imports nested too deeply at "); }
static V F_Main_dchk_dload(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s2558 = a0;
if ((s2558) == 0) {
return F_IO_ddie(1u, F_String_dappend(S2559(), a2));
} else if (nat_ge(s2558, 1)) {
return F_Main_dchk_dseen(nat_subk(s2558, 1), a1, a2, a3, a4, a5, F_Chk_dSB2_dfind(F_CS_dseen(a5), F_Path_dnorm(a2)));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dload(V *a) { (void)a; return F_Main_dchk_dload(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S2561(void) { static V c; return STRC(c, "/"); }
static V S2563(void) { static V c; return STRC(c, "/"); }
static V S2564(void) { static V c; return STRC(c, "/"); }
static V S2565(void) { static V c; return STRC(c, "."); }
static V F_Path_dnorm(V a0) {
top:;
V v2560 = F_String_dstarts__with(a0, S2561());
V v2562 = F_String_djoin(F_List_dreverse(F_Path_dfold(F_String_dsplit(a0, 47u), IMM(0), v2560)), S2563());
return F_Bool_dpick(v2560, F_String_dappend(S2564(), v2562), F_Bool_dpick(F_String_dis__empty(v2562), S2565(), v2562));
}
static V W_Path_dnorm(V *a) { (void)a; return F_Path_dnorm(a[0]); }
static V S2567(void) { static V c; return STRC(c, "."); }
static V F_Path_dfold(V a0, V a1, V a2) {
top:;
V s2566 = a0;
if ((s2566) == IMM(0)) {
return a1;
} else if (TAG(s2566) == 1) {
{ V t0 = FLD(s2566, 1); V t1 = F_Bool_dpick(F_Bool_dor(F_String_dis__empty(FLD(s2566, 0)), F_String_deq(FLD(s2566, 0), S2567())), a1, F_Path_dpush(FLD(s2566, 0), a1, a2)); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Path_dfold(V *a) { (void)a; return F_Path_dfold(a[0], a[1], a[2]); }
static V S2569(void) { static V c; return STRC(c, ".."); }
static V S2570(void) { static V c; return STRC(c, ".."); }
static V S2571(void) { static V c; return STRC(c, ".."); }
static V S2572(void) { static V c; return STRC(c, ".."); }
static V S2573(void) { static V c; return STRC(c, ".."); }
static V F_Path_dpush(V a0, V a1, V a2) {
top:;
V s2568 = a1;
if ((s2568) == IMM(0)) {
return F_Bool_dpick(F_String_deq(a0, S2569()), F_Bool_dpick(a2, IMM(0), C2(1, S2570(), IMM(0))), C2(1, a0, IMM(0)));
} else if (TAG(s2568) == 1) {
return F_Bool_dpick(F_String_deq(a0, S2571()), F_Bool_dpick(F_String_deq(FLD(s2568, 0), S2572()), C2(1, S2573(), C2(1, FLD(s2568, 0), FLD(s2568, 1))), FLD(s2568, 1)), C2(1, a0, C2(1, FLD(s2568, 0), FLD(s2568, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Path_dpush(V *a) { (void)a; return F_Path_dpush(a[0], a[1], a[2]); }
static V F_CS_dseen(V a0) {
top:;
V v2574 = a0;
return FLD(v2574, 1);
}
static V W_CS_dseen(V *a) { (void)a; return F_CS_dseen(a[0]); }
static V F_Chk_dSB2_dfind(V a0, V a1) {
top:;
V s2575 = a0;
if ((s2575) == IMM(0)) {
return IMM(0);
} else if (TAG(s2575) == 1) {
return F_Chk_dSB2_dfind_dif(FLD(s2575, 1), a1, FLD(FLD(s2575, 0), 1), F_String_deq(a1, FLD(FLD(s2575, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dSB2_dfind(V *a) { (void)a; return F_Chk_dSB2_dfind(a[0], a[1]); }
static V F_Chk_dSB2_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s2576 = a3;
if ((s2576) == IMM(1)) {
return C1(1, a2);
} else if ((s2576) == IMM(0)) {
return F_Chk_dSB2_dfind(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dSB2_dfind_dif(V *a) { (void)a; return F_Chk_dSB2_dfind_dif(a[0], a[1], a[2], a[3]); }
static V S2578(void) { static V c; return STRC(c, "an import cycle through "); }
static V S2579(void) { static V c; return STRC(c, "one namespace per file ("); }
static V S2580(void) { static V c; return STRC(c, " is both '"); }
static V S2581(void) { static V c; return STRC(c, "' and '"); }
static V S2582(void) { static V c; return STRC(c, "')"); }
static V L2583(V *a) {
return F_Main_dchk_dread(a[5], a[4], a[3], a[2], a[1], a[0], a[6]);
}
static V F_Main_dchk_dseen(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2577 = a6;
if (TAG(s2577) == 1) {
return F_Bool_dpick(F_String_deq(FLD(s2577, 0), F_Main_dchk_dloading()), F_Main_dchk_dfail(F_Chk_derr0(F_String_dappend(S2578(), a2), IMM(0), a4)), F_Bool_dpick(F_String_deq(FLD(s2577, 0), a3), F_IO_dpure(F_CS_dat__end(a5)), F_Main_dchk_dfail(F_Chk_derr0(F_String_dappend(S2579(), F_String_dappend(a2, F_String_dappend(S2580(), F_String_dappend(FLD(s2577, 0), F_String_dappend(S2581(), F_String_dappend(a3, S2582())))))), IMM(0), a4))));
} else if ((s2577) == IMM(0)) {
return F_IO_dbind(F_Main_dread__opt(a2), mk_clo(L2583, 7, 6, (V[]){a5, a4, a3, a2, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dseen(V *a) { (void)a; return F_Main_dchk_dseen(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S2585(void) { static V c; return STRC(c, "no such file: "); }
static V F_Main_dchk_dread(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2584 = a6;
if ((s2584) == IMM(0)) {
return F_Main_dchk_dfail(F_Chk_derr0(F_String_dappend(S2585(), a2), IMM(0), a4));
} else if (TAG(s2584) == 1) {
return F_Main_dchk_dsrc(a0, a1, a2, a3, FLD(s2584, 0), a5);
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
V s2586 = a1;
if ((s2586) == IMM(0)) {
return C3(0, F_List_dreverse(a3), a4, IMM(0));
} else if (TAG(s2586) == 1) {
return F_Chk_dheader_dline(a0, FLD(s2586, 0), FLD(s2586, 1), a2, a3, a4, F_Chk_dStr_dtrim(FLD(s2586, 0)));
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
V s2587 = a0;
if ((s2587) == IMM(0)) {
return IMM(0);
} else if (TAG(s2587) == 1) {
return F_String_dtrim__start_dif(FLD(s2587, 0), FLD(s2587, 1), F_Char_dis__space(FLD(s2587, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_String_dtrim__start(V *a) { (void)a; return F_String_dtrim__start(a[0]); }
static V F_Char_dis__space(V a0) {
top:;
V s2588 = a0;
{
return F_Bool_dor(F_U32_dis__eq(s2588, 32u), F_Bool_dand(F_U32_dis__ge(s2588, 9u), F_U32_dis__le(s2588, 13u)));
}
}
static V W_Char_dis__space(V *a) { (void)a; return F_Char_dis__space(a[0]); }
static V F_String_dtrim__start_dif(V a0, V a1, V a2) {
top:;
V s2589 = a2;
if ((s2589) == IMM(0)) {
return C2(1, a0, a1);
} else if ((s2589) == IMM(1)) {
return F_String_dtrim__start(a1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dtrim__start_dif(V *a) { (void)a; return F_String_dtrim__start_dif(a[0], a[1], a[2]); }
static V F_String_dtrim__end(V a0) {
top:;
return F_String_dreverse(F_String_dtrim__start(F_String_dreverse(a0)));
}
static V W_String_dtrim__end(V *a) { (void)a; return F_String_dtrim__end(a[0]); }
static V S2591(void) { static V c; return STRC(c, "import"); }
static V S2592(void) { static V c; return STRC(c, "import"); }
static V S2593(void) { static V c; return STRC(c, "#"); }
static V F_Chk_dheader_dline(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2590 = F_Bool_dor(F_String_deq(a6, S2591()), F_Bool_dand(F_String_dstarts__with(a6, S2592()), F_Chk_dis__space(F_Chk_dStr_dfirst(F_String_ddrop(a6, 6u)))));
return F_Chk_dheader_dline_dgo(a0, a1, a2, a3, a4, a5, a6, v2590, F_Bool_dor(F_String_dis__empty(a6), F_String_dstarts__with(a6, S2593())));
}
static V W_Chk_dheader_dline(V *a) { (void)a; return F_Chk_dheader_dline(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dheader_dline_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s2594 = a7;
if ((s2594) == IMM(1)) {
return F_Chk_dheader_dimp(a0, a1, a2, a3, a4, a5, a6, F_Chk_dimport_dparse(F_Chk_dStr_duntil__hash(F_Chk_dStr_dwords(F_String_ddrop(a6, 6u)))));
} else if ((s2594) == IMM(0)) {
return F_Chk_dheader_drest(a0, a1, a2, a3, a4, a5, a8);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dheader_dline_dgo(V *a) { (void)a; return F_Chk_dheader_dline_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Chk_dheader_drest(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2595 = a6;
if ((s2595) == IMM(1)) {
return F_Chk_dheader_dgo_dnext(a0, a2, F_Nat_dadd(a3, nat_addk(F_String_dlength(a1), 1)), C2(1, a1, a4), a5);
} else if ((s2595) == IMM(0)) {
return C3(0, F_List_dappend(F_List_dreverse(C2(1, a1, a4)), a2), a5, IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dheader_drest(V *a) { (void)a; return F_Chk_dheader_drest(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dheader_dgo_dnext(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Chk_dheader_dgo(a0, a1, a2, a3, a4);
}
static V W_Chk_dheader_dgo_dnext(V *a) { (void)a; return F_Chk_dheader_dgo_dnext(a[0], a[1], a[2], a[3], a[4]); }
static V S2596(void) { static V c; return STRC(c, ""); }
static V F_Chk_dStr_dwords(V a0) {
top:;
return F_Chk_dStr_dwords_dgo(a0, S2596(), IMM(0));
}
static V W_Chk_dStr_dwords(V *a) { (void)a; return F_Chk_dStr_dwords(a[0]); }
static V F_Chk_dStr_dwords_dgo(V a0, V a1, V a2) {
top:;
V s2597 = a0;
if ((s2597) == IMM(0)) {
return F_List_dreverse(F_Chk_dStr_dwords_dpush(a1, a2));
} else if (TAG(s2597) == 1) {
return F_Chk_dStr_dwords_dchr(FLD(s2597, 1), FLD(s2597, 0), a1, a2, F_Chk_dis__space(FLD(s2597, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dwords_dgo(V *a) { (void)a; return F_Chk_dStr_dwords_dgo(a[0], a[1], a[2]); }
static V F_Chk_dis__space(V a0) {
top:;
return F_Bool_dor(F_Bool_dor(F_U32_dis__eq(a0, 32u), F_U32_dis__eq(a0, 10u)), F_Bool_dor(F_U32_dis__eq(a0, 13u), F_U32_dis__eq(a0, 9u)));
}
static V W_Chk_dis__space(V *a) { (void)a; return F_Chk_dis__space(a[0]); }
static V S2599(void) { static V c; return STRC(c, ""); }
static V F_Chk_dStr_dwords_dchr(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2598 = a4;
if ((s2598) == IMM(1)) {
return F_Chk_dStr_dwords_dgo(a0, S2599(), F_Chk_dStr_dwords_dpush(a2, a3));
} else if ((s2598) == IMM(0)) {
return F_Chk_dStr_dwords_dgo(a0, F_String_dappend(a2, F_Chk_dStr_dchr(a1)), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dwords_dchr(V *a) { (void)a; return F_Chk_dStr_dwords_dchr(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dStr_dwords_dpush(V a0, V a1) {
top:;
return F_Bool_dpick(F_String_dis__empty(a0), a1, C2(1, a0, a1));
}
static V W_Chk_dStr_dwords_dpush(V *a) { (void)a; return F_Chk_dStr_dwords_dpush(a[0], a[1]); }
static V S2601(void) { static V c; return STRC(c, "#"); }
static V F_Chk_dStr_duntil__hash(V a0) {
top:;
V s2600 = a0;
if ((s2600) == IMM(0)) {
return IMM(0);
} else if (TAG(s2600) == 1) {
return F_Bool_dpick(F_String_dstarts__with(FLD(s2600, 0), S2601()), IMM(0), C2(1, FLD(s2600, 0), F_Chk_dStr_duntil__hash(FLD(s2600, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_duntil__hash(V *a) { (void)a; return F_Chk_dStr_duntil__hash(a[0]); }
static V S2603(void) { static V c; return STRC(c, "Base"); }
static V S2604(void) { static V c; return STRC(c, ""); }
static V F_Chk_dimport_dparse(V a0) {
top:;
V s2602 = a0;
if (TAG(s2602) == 1 && TAG(FLD(s2602, 0)) == 1 && (FLD(FLD(s2602, 0), 0)) == 66 && TAG(FLD(FLD(s2602, 0), 1)) == 1 && (FLD(FLD(FLD(s2602, 0), 1), 0)) == 97 && TAG(FLD(FLD(FLD(s2602, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s2602, 0), 1), 1), 0)) == 115 && TAG(FLD(FLD(FLD(FLD(s2602, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s2602, 0), 1), 1), 1), 0)) == 101 && (FLD(FLD(FLD(FLD(FLD(s2602, 0), 1), 1), 1), 1)) == IMM(0) && (FLD(s2602, 1)) == IMM(0)) {
return C1(1, C2(0, S2603(), S2604()));
} else if (TAG(s2602) == 1 && TAG(FLD(s2602, 1)) == 1 && TAG(FLD(FLD(s2602, 1), 0)) == 1 && (FLD(FLD(FLD(s2602, 1), 0), 0)) == 97 && TAG(FLD(FLD(FLD(s2602, 1), 0), 1)) == 1 && (FLD(FLD(FLD(FLD(s2602, 1), 0), 1), 0)) == 115 && (FLD(FLD(FLD(FLD(s2602, 1), 0), 1), 1)) == IMM(0) && TAG(FLD(FLD(s2602, 1), 1)) == 1 && (FLD(FLD(FLD(s2602, 1), 1), 1)) == IMM(0)) {
return F_Bool_dpick(F_Chk_dis__ident(FLD(FLD(FLD(s2602, 1), 1), 0)), C1(1, C2(0, FLD(s2602, 0), FLD(FLD(FLD(s2602, 1), 1), 0))), IMM(0));
} else {
return IMM(0);
}
}
static V W_Chk_dimport_dparse(V *a) { (void)a; return F_Chk_dimport_dparse(a[0]); }
static V F_Chk_dis__ident(V a0) {
top:;
V s2605 = a0;
if ((s2605) == IMM(0)) {
return IMM(0);
} else if (TAG(s2605) == 1) {
return F_Bool_dand(F_Chk_dis__head(FLD(s2605, 0)), F_Chk_dis__ident_drest(FLD(s2605, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dis__ident(V *a) { (void)a; return F_Chk_dis__ident(a[0]); }
static V F_Chk_dis__ident_drest(V a0) {
top:;
V s2606 = a0;
if ((s2606) == IMM(0)) {
return IMM(1);
} else if (TAG(s2606) == 1) {
return F_Bool_dand(F_Bool_dor(F_Chk_dis__head(FLD(s2606, 0)), F_Chk_dis__digit(FLD(s2606, 0))), F_Chk_dis__ident_drest(FLD(s2606, 1)));
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
static V S2609(void) { static V c; return STRC(c, "an import ('import Base', or 'import <path> as <Name>')"); }
static V S2610(void) { static V c; return STRC(c, "'"); }
static V S2611(void) { static V c; return STRC(c, "'"); }
static V F_Chk_dheader_dimp(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s2607 = a7;
if ((s2607) == IMM(0)) {
V v2608 = F_U32_dfrom__nat(F_Nat_dadd(a3, F_Chk_dStr_dindex__of(a1, a6, 0u)));
return C3(0, IMM(0), IMM(0), C1(1, F_Chk_derr0(S2609(), C1(1, F_String_dappend(S2610(), F_String_dappend(a6, S2611()))), C3(1, a0, v2608, v2608))));
} else if (TAG(s2607) == 1) {
return F_Chk_dheader_dimp_dgo(a0, a1, a2, a3, a4, a5, FLD(s2607, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dheader_dimp(V *a) { (void)a; return F_Chk_dheader_dimp(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S2615(void) { static V c; return STRC(c, ""); }
static V F_Chk_dheader_dimp_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2612 = a6;
V v2613 = FLD(v2612, 0);
V v2614 = F_U32_dfrom__nat(F_Nat_dadd(a3, F_Chk_dStr_dindex__of(a1, v2613, 0u)));
return F_Chk_dheader_dgo_dnext(a0, a2, F_Nat_dadd(a3, nat_addk(F_String_dlength(a1), 1)), C2(1, S2615(), a4), F_List_dappend(a5, C2(1, C3(0, v2613, FLD(v2612, 1), v2614), IMM(0))));
}
static V W_Chk_dheader_dimp_dgo(V *a) { (void)a; return F_Chk_dheader_dimp_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dStr_dindex__of(V a0, V a1, V a2) {
top:;
V s2616 = a0;
if ((s2616) == IMM(0)) {
return 0u;
} else if (TAG(s2616) == 1) {
return F_Chk_dStr_dindex__of_dif(FLD(s2616, 1), a1, a2, F_String_dstarts__with(C2(1, FLD(s2616, 0), FLD(s2616, 1)), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dindex__of(V *a) { (void)a; return F_Chk_dStr_dindex__of(a[0], a[1], a[2]); }
static V F_Chk_dStr_dindex__of_dif(V a0, V a1, V a2, V a3) {
top:;
V s2617 = a3;
if ((s2617) == IMM(1)) {
return a2;
} else if ((s2617) == IMM(0)) {
return F_Chk_dStr_dindex__of(a0, a1, nat_addk(a2, 1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dindex__of_dif(V *a) { (void)a; return F_Chk_dStr_dindex__of_dif(a[0], a[1], a[2], a[3]); }
static V S2618(void) { static V c; return STRC(c, ""); }
static V S2619(void) { static V c; return STRC(c, ""); }
static V F_Chk_derr0(V a0, V a1, V a2) {
top:;
return CN(0, 7, (V[]){F_Chk_dbook__nil(), IMM(0), C1(1, a0), a1, a2, S2618(), S2619()});
}
static V W_Chk_derr0(V *a) { (void)a; return F_Chk_derr0(a[0], a[1], a[2]); }
static V F_Chk_dStr_dfirst(V a0) {
top:;
V s2620 = a0;
if ((s2620) == IMM(0)) {
return 0u;
} else if (TAG(s2620) == 1) {
return FLD(s2620, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dfirst(V *a) { (void)a; return F_Chk_dStr_dfirst(a[0]); }
static V L2623(V *a) {
return F_Main_dchk_dparse(a[4], a[3], a[2], a[1], a[0], a[5]);
}
static V F_Main_dchk_dhdr(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2621 = a6;
V s2622 = FLD(v2621, 2);
if (TAG(s2622) == 1) {
return F_Main_dchk_dfail(FLD(s2622, 0));
} else if ((s2622) == IMM(0)) {
return F_IO_dbind(F_Main_dchk_dimps(a0, a1, F_Mod_ddir(a2), a3, a4, FLD(v2621, 1), F_CS_dmark(a5, F_Path_dnorm(a2)), IMM(0)), mk_clo(L2623, 6, 5, (V[]){FLD(v2621, 0), a4, a3, a2, a1}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dhdr(V *a) { (void)a; return F_Main_dchk_dhdr(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S2627(void) { static V c; return STRC(c, "\012"); }
static V F_Main_dchk_dparse(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v2624 = a5;
V v2625 = FLD(v2624, 0);
V v2626 = F_Chk_dbook__len(FLD(v2625, 0));
return F_Main_dchk_dparsed(a0, a1, a2, FLD(v2625, 1), v2626, F_Chk_dparse__file(FLD(v2625, 0), a3, F_String_djoin(a4, S2627()), a2, F_Mod_ddir(a1), FLD(v2624, 1)));
}
static V W_Main_dchk_dparse(V *a) { (void)a; return F_Main_dchk_dparse(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dparse__file(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dparse__file_dfin(apply(F_Chk_dP_ddecls(), CN(0, 9, (V[]){CN(0, 5, (V[]){a2, 0u, 1u, IMM(1), 0u}), IMM(0), 0u, 0u, a0, a1, a3, a4, a5})));
}
static V W_Chk_dparse__file(V *a) { (void)a; return F_Chk_dparse__file(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L2629(V *a) {
return F_Chk_dP_dif(F_U32_dis__zero(a[0]), F_Chk_dP_dpure(IMM(0)), F_Chk_dP_ddecl());
}
static V L2628(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L2629, 1, 0, 0));
}
static V F_Chk_dP_ddecls(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2628, 1, 0, 0));
}
static V W_Chk_dP_ddecls(V *a) { (void)a; return F_Chk_dP_ddecls(); }
static V S2631(void) { static V c; return STRC(c, "@"); }
static V S2633(void) { static V c; return STRC(c, "def"); }
static V S2635(void) { static V c; return STRC(c, "type"); }
static V S2637(void) { static V c; return STRC(c, "law"); }
static V L2639(V *a) {
return F_Chk_dP_ddecls();
}
static V L2638(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_ddecl_dgo(a[2], a[1], a[0], a[3]), mk_clo(L2639, 1, 0, 0));
}
static V L2636(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S2637()), mk_clo(L2638, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L2634(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S2635()), mk_clo(L2636, 3, 2, (V[]){a[1], a[0]}));
}
static V L2632(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S2633()), mk_clo(L2634, 2, 1, (V[]){a[0]}));
}
static V L2630(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2631()), mk_clo(L2632, 1, 0, 0));
}
static V F_Chk_dP_ddecl(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dreset__scope(), mk_clo(L2630, 1, 0, 0));
}
static V W_Chk_dP_ddecl(V *a) { (void)a; return F_Chk_dP_ddecl(); }
static V S2641(void) { static V c; return STRC(c, "'def', 'type' or 'law'"); }
static V F_Chk_dP_ddecl_dgo(V a0, V a1, V a2, V a3) {
top:;
V s2640 = a0;
if ((s2640) == IMM(1)) {
return F_Chk_dP_dunsafe();
} else if ((s2640) == IMM(0)) {
return F_Chk_dP_dif(a1, F_Chk_dP_ddef(IMM(0)), F_Chk_dP_dif(a2, F_Chk_dP_dtype(), F_Chk_dP_dif(a3, F_Chk_dP_dlaw(), F_Chk_dP_dfail(S2641()))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_ddecl_dgo(V *a) { (void)a; return F_Chk_dP_ddecl_dgo(a[0], a[1], a[2], a[3]); }
static V S2644(void) { static V c; return STRC(c, ""); }
static V L2643(V *a) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2644(), IMM(0), IMM(0)));
}
static V L2642(V *a) {
return F_Chk_dP_dgo(F_Chk_dP_dfail_dgo(a[0], a[2]), mk_clo(L2643, 2, 1, (V[]){a[1]}));
}
static V F_Chk_dP_dfail(V a1) {
top:;
return mk_clo(L2642, 3, 2, (V[]){a1, 0});
}
static V W_Chk_dP_dfail(V *a) { (void)a; return F_Chk_dP_dfail(a[1]); }
static V L2645(V *a) {
return C1(0, a[0]);
}
static V F_Chk_dP_dthrow(V a1) {
top:;
return mk_clo(L2645, 2, 1, (V[]){a1});
}
static V W_Chk_dP_dthrow(V *a) { (void)a; return F_Chk_dP_dthrow(a[1]); }
static V S2648(void) { static V c; return STRC(c, "end of input"); }
static V S2649(void) { static V c; return STRC(c, "'"); }
static V S2650(void) { static V c; return STRC(c, "'"); }
static V F_Chk_dP_dfail_dgo(V a0, V a1) {
top:;
V v2646 = F_Chk_dCur_dpeek(F_Chk_dPS_dcur(a1));
V v2647 = F_Chk_dCur_dpos(F_Chk_dPS_dcur(a1));
return C1(0, F_Chk_derr0(a0, C1(1, F_Bool_dpick(F_U32_dis__zero(v2646), S2648(), F_String_dappend(S2649(), F_String_dappend(F_Chk_dStr_dchr(v2646), S2650())))), C3(1, F_Chk_dPS_dsrc(a1), v2647, v2647)));
}
static V W_Chk_dP_dfail_dgo(V *a) { (void)a; return F_Chk_dP_dfail_dgo(a[0], a[1]); }
static V F_Chk_dPS_dsrc(V a0) {
top:;
V v2651 = a0;
return FLD(v2651, 5);
}
static V W_Chk_dPS_dsrc(V *a) { (void)a; return F_Chk_dPS_dsrc(a[0]); }
static V F_Chk_dPS_dcur(V a0) {
top:;
V v2652 = a0;
return FLD(v2652, 0);
}
static V W_Chk_dPS_dcur(V *a) { (void)a; return F_Chk_dPS_dcur(a[0]); }
static V F_Chk_dCur_dpos(V a0) {
top:;
V v2653 = a0;
return FLD(v2653, 1);
}
static V W_Chk_dCur_dpos(V *a) { (void)a; return F_Chk_dCur_dpos(a[0]); }
static V F_Chk_dCur_dpeek(V a0) {
top:;
V v2654 = a0;
return F_Chk_dStr_dfirst(FLD(v2654, 0));
}
static V W_Chk_dCur_dpeek(V *a) { (void)a; return F_Chk_dCur_dpeek(a[0]); }
static V F_Chk_dP_dgo(V a2, V a3) {
top:;
V s2655 = a2;
if (TAG(s2655) == 0) {
return C1(0, FLD(s2655, 0));
} else if (TAG(s2655) == 1) {
return F_Chk_dP_dgo_ddone(FLD(s2655, 0), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dgo(V *a) { (void)a; return F_Chk_dP_dgo(a[2], a[3]); }
static V F_Chk_dP_dgo_ddone(V a2, V a3) {
top:;
V v2656 = a2;
return apply(apply(a3, FLD(v2656, 0)), FLD(v2656, 1));
}
static V W_Chk_dP_dgo_ddone(V *a) { (void)a; return F_Chk_dP_dgo_ddone(a[2], a[3]); }
static V S2657(void) { static V c; return STRC(c, "law"); }
static V S2662(void) { static V c; return STRC(c, ":"); }
static V L2668(V *a) {
return F_Chk_dP_dlaw_dfin(a[2], a[1], a[0], a[3]);
}
static V L2667(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L2668, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L2666(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[2]), mk_clo(L2667, 4, 3, (V[]){a[3], a[0], a[1]}));
}
static V L2665(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dblock(), mk_clo(L2666, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L2664(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclauses(IMM(0), 0u), mk_clo(L2665, 3, 2, (V[]){a[0], a[1]}));
}
static V L2663(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L2664, 2, 1, (V[]){a[0]}));
}
static V L2661(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S2662()), mk_clo(L2663, 2, 1, (V[]){a[0]}));
}
static V L2660(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dfresh(a[0]), mk_clo(L2661, 2, 1, (V[]){a[0]}));
}
static V L2659(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dqual(a[0]), mk_clo(L2660, 1, 0, 0));
}
static V L2658(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L2659, 1, 0, 0));
}
static V F_Chk_dP_dlaw(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(S2657()), mk_clo(L2658, 1, 0, 0));
}
static V W_Chk_dP_dlaw(V *a) { (void)a; return F_Chk_dP_dlaw(); }
static V F_Chk_dP_dlaw_dfin(V a0, V a1, V a2, V a3) {
top:;
V v2669 = a1;
V v2670 = FLD(v2669, 0);
return F_Chk_dP_dset__book(F_Chk_dbook__push(F_Chk_dbook__set(a3, a0, CN(0, 7, (V[]){F_Chk_dLC_dfirst__exs(v2670), FLD(v2669, 1), F_Chk_dhigher0(a3, F_Chk_dLC_dbind(v2670, a2)), IMM(0), IMM(0), IMM(0), IMM(0)})), a0));
}
static V W_Chk_dP_dlaw_dfin(V *a) { (void)a; return F_Chk_dP_dlaw_dfin(a[0], a[1], a[2], a[3]); }
static V F_Chk_dLC_dbind(V a0, V a1) {
top:;
V s2671 = a0;
if ((s2671) == IMM(0)) {
return a1;
} else if (TAG(s2671) == 1) {
return F_Chk_dLC_dbind_done(FLD(FLD(s2671, 0), 0), FLD(FLD(s2671, 0), 1), FLD(FLD(s2671, 0), 2), FLD(FLD(s2671, 0), 3), FLD(FLD(s2671, 0), 4), FLD(FLD(s2671, 0), 5), F_Chk_dLC_dbind(FLD(s2671, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dLC_dbind(V *a) { (void)a; return F_Chk_dLC_dbind(a[0], a[1]); }
static V S2673(void) { static V c; return STRC(c, "Exists"); }
static V F_Chk_dLC_dbind_done(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2672 = a0;
if ((s2672) == IMM(1)) {
return CN(11, 6, (V[]){a1, a2, a3, a4, C3(24, IMM(0), a3, a6), a5});
} else if ((s2672) == IMM(0)) {
return C3(13, C3(13, C3(4, S2673(), a5, IMM(0)), a4, a5), CN(12, 5, (V[]){a2, a3, C3(24, IMM(0), a3, a6), a5, IMM(3)}), a5);
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
V s2674 = a0;
if ((s2674) == IMM(0)) {
return 0u;
} else if (TAG(s2674) == 1 && (FLD(FLD(s2674, 0), 0)) == IMM(1)) {
return nat_addk(F_Chk_dLC_dfirst__exs(FLD(s2674, 1)), 1);
} else if (TAG(s2674) == 1) {
return 0u;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dLC_dfirst__exs(V *a) { (void)a; return F_Chk_dLC_dfirst__exs(a[0]); }
static V F_Chk_dbook__push(V a0, V a1) {
top:;
V v2675 = a0;
return CN(0, 7, (V[]){FLD(v2675, 0), FLD(v2675, 1), C2(1, a1, FLD(v2675, 2)), FLD(v2675, 3), FLD(v2675, 4), FLD(v2675, 5), FLD(v2675, 6)});
}
static V W_Chk_dbook__push(V *a) { (void)a; return F_Chk_dbook__push(a[0], a[1]); }
static V L2676(V *a) {
return C1(1, C2(0, IMM(0), F_Chk_dPS_dset__book(a[1], a[0])));
}
static V F_Chk_dP_dset__book(V a0) {
top:;
return mk_clo(L2676, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dset__book(V *a) { (void)a; return F_Chk_dP_dset__book(a[0]); }
static V F_Chk_dPS_dset__book(V a0, V a1) {
top:;
V v2677 = a0;
return CN(0, 9, (V[]){FLD(v2677, 0), FLD(v2677, 1), FLD(v2677, 2), FLD(v2677, 3), a1, FLD(v2677, 5), FLD(v2677, 6), FLD(v2677, 7), FLD(v2677, 8)});
}
static V W_Chk_dPS_dset__book(V *a) { (void)a; return F_Chk_dPS_dset__book(a[0], a[1]); }
static V L2678(V *a) {
return C1(1, C2(0, F_Chk_dPS_dbook(a[0]), a[0]));
}
static V F_Chk_dP_dbook(void) {
top:;
return mk_clo(L2678, 1, 0, 0);
}
static V W_Chk_dP_dbook(V *a) { (void)a; return F_Chk_dP_dbook(); }
static V F_Chk_dPS_dbook(V a0) {
top:;
V v2679 = a0;
return FLD(v2679, 4);
}
static V W_Chk_dPS_dbook(V *a) { (void)a; return F_Chk_dPS_dbook(a[0]); }
static V L2680(V *a) {
return F_Chk_dP_dgo(apply(a[1], a[4]), a[0]);
}
static V F_Chk_dP_dbind(V a2, V a3) {
top:;
return mk_clo(L2680, 5, 4, (V[]){a3, a2, 0, 0});
}
static V W_Chk_dP_dbind(V *a) { (void)a; return F_Chk_dP_dbind(a[2], a[3]); }
static V L2681(V *a) {
return F_Chk_dP_dclose_dgo(a[0], a[1]);
}
static V F_Chk_dP_dclose(V a0) {
top:;
return mk_clo(L2681, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dclose(V *a) { (void)a; return F_Chk_dP_dclose(a[0]); }
static V F_Chk_dP_dclose_dgo(V a0, V a1) {
top:;
V v2682 = a1;
return C1(1, C2(0, IMM(0), CN(0, 9, (V[]){FLD(v2682, 0), F_Chk_dSB_ddrop(FLD(v2682, 1), F_Nat_dsub(FLD(v2682, 2), a0)), F_Nat_dmin(FLD(v2682, 2), a0), FLD(v2682, 3), FLD(v2682, 4), FLD(v2682, 5), FLD(v2682, 6), FLD(v2682, 7), FLD(v2682, 8)})));
}
static V W_Chk_dP_dclose_dgo(V *a) { (void)a; return F_Chk_dP_dclose_dgo(a[0], a[1]); }
static V F_Chk_dSB_ddrop(V a0, V a1) {
top:;
V s2683 = a0;
V s2684 = a1;
if ((s2684) == 0) {
return s2683;
} else if (TAG(s2683) == 1 && nat_ge(s2684, 1)) {
{ V t0 = FLD(s2683, 1); V t1 = nat_subk(s2684, 1); a0 = t0; a1 = t1; goto top; }
} else if ((s2683) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dSB_ddrop(V *a) { (void)a; return F_Chk_dSB_ddrop(a[0], a[1]); }
static V L2687(V *a) {
return F_Chk_dP_dflatten(a[0], IMM(0));
}
static V L2686(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody(F_U32_dsub(a[0], 1u)), mk_clo(L2687, 1, 0, 0));
}
static V L2685(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcol(), mk_clo(L2686, 1, 0, 0));
}
static V F_Chk_dP_dblock(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2685, 1, 0, 0));
}
static V W_Chk_dP_dblock(V *a) { (void)a; return F_Chk_dP_dblock(); }
static V F_Chk_dP_dflatten(V a0, V a1) {
top:;
V s2688 = a0;
if (TAG(s2688) == 2) {
return F_Chk_dP_dpure(F_Chk_dflatten_dlams(a1, FLD(s2688, 0)));
} else if (TAG(s2688) == 1) {
return F_Chk_dP_dflatten_dlocal(FLD(s2688, 0), FLD(s2688, 1), FLD(s2688, 2), FLD(s2688, 3), a1);
} else if (TAG(s2688) == 0) {
return F_Chk_dP_dmatch__flatten(FLD(s2688, 0), FLD(s2688, 1), FLD(s2688, 2), a1);
} else if (TAG(s2688) == 3) {
{ V t0 = FLD(s2688, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dflatten(V *a) { (void)a; return F_Chk_dP_dflatten(a[0], a[1]); }
static V S2691(void) { static V c; return STRC(c, "a case (this match has no row to return)"); }
static V F_Chk_dP_dmatch__flatten(V a0, V a1, V a2, V a3) {
top:;
V s2689 = a0;
V s2690 = a1;
if ((s2689) == IMM(0) && TAG(s2690) == 1 && TAG(FLD(s2690, 0)) == 3) {
return F_Chk_dP_dflatten(FLD(FLD(s2690, 0), 1), a3);
} else if ((s2689) == IMM(0) && TAG(s2690) == 1) {
return F_Chk_dP_dflatten(FLD(s2690, 0), a3);
} else if ((s2689) == IMM(0) && (s2690) == IMM(0)) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2691(), IMM(0), a2));
} else if (TAG(s2689) == 1) {
return F_Chk_dP_dmf_dvars(FLD(s2689, 0), FLD(s2689, 1), s2690, a2, a3);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dmatch__flatten(V *a) { (void)a; return F_Chk_dP_dmatch__flatten(a[0], a[1], a[2], a[3]); }
static V F_Chk_dP_dmf_dvars(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2692 = a4;
if ((s2692) == IMM(0)) {
return F_Chk_dP_dmf_dbad(F_Chk_dTm_dstrip__subs(a0), a3);
} else if (TAG(s2692) == 1) {
return F_Chk_dP_dmf_dcol(a0, a1, a2, a3, FLD(s2692, 0), FLD(s2692, 1), F_Chk_dvars_dfind(C2(1, FLD(s2692, 0), FLD(s2692, 1)), F_Maybe_ddefault(F_Chk_dTm_dvar__i(a0), 4294967295u)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dmf_dvars(V *a) { (void)a; return F_Chk_dP_dmf_dvars(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dTm_dvar__i(V a0) {
top:;
V s2693 = a0;
if (TAG(s2693) == 0) {
return C1(1, FLD(s2693, 1));
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dvar__i(V *a) { (void)a; return F_Chk_dTm_dvar__i(a[0]); }
static V F_Chk_dvars_dfind(V a0, V a1) {
top:;
V s2694 = a0;
if ((s2694) == IMM(0)) {
return IMM(0);
} else if (TAG(s2694) == 1 && TAG(FLD(s2694, 0)) == 0) {
return F_Chk_dvars_dfind_dif(C4(0, FLD(FLD(s2694, 0), 0), FLD(FLD(s2694, 0), 1), FLD(FLD(s2694, 0), 2), FLD(FLD(s2694, 0), 3)), FLD(s2694, 1), a1, F_U32_dis__eq(a1, FLD(FLD(s2694, 0), 1)));
} else if (TAG(s2694) == 1) {
{ V t0 = FLD(s2694, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dvars_dfind(V *a) { (void)a; return F_Chk_dvars_dfind(a[0], a[1]); }
static V F_Chk_dvars_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s2695 = a3;
if ((s2695) == IMM(1)) {
return C1(1, a0);
} else if ((s2695) == IMM(0)) {
return F_Chk_dvars_dfind(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dvars_dfind_dif(V *a) { (void)a; return F_Chk_dvars_dfind_dif(a[0], a[1], a[2], a[3]); }
static V F_Chk_dP_dmf_dcol(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2696 = a6;
if (TAG(s2696) == 1) {
return F_Chk_dP_dmf_dcol_dvar(a0, a1, a2, a3, a4, a5, FLD(s2696, 0), F_Chk_drows_dctr(a2), F_Nat_dis__eq(F_List_dlength(a2), 0u));
} else if ((s2696) == IMM(0)) {
return F_Chk_dP_dmf_dskip(a0, a1, a2, a3, a4, a5);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dmf_dcol(V *a) { (void)a; return F_Chk_dP_dmf_dcol(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V L2697(V *a) {
return F_Chk_dP_dpure(F_Chk_dflatten_dlams(C2(1, a[0], IMM(0)), a[1]));
}
static V F_Chk_dP_dmf_dskip(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dmatch__flatten(C2(1, a0, a1), a2, a3, a5), mk_clo(L2697, 2, 1, (V[]){a4}));
}
static V W_Chk_dP_dmf_dskip(V *a) { (void)a; return F_Chk_dP_dmf_dskip(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dflatten_dlams(V a0, V a1) {
top:;
V s2698 = a0;
if ((s2698) == IMM(0)) {
return a1;
} else if (TAG(s2698) == 1 && TAG(FLD(s2698, 0)) == 0) {
return CN(12, 5, (V[]){FLD(FLD(s2698, 0), 0), FLD(FLD(s2698, 0), 1), C3(24, IMM(0), FLD(FLD(s2698, 0), 1), F_Chk_dflatten_dlams(FLD(s2698, 1), a1)), FLD(FLD(s2698, 0), 3), FLD(FLD(s2698, 0), 2)});
} else if (TAG(s2698) == 1) {
{ V t0 = FLD(s2698, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dflatten_dlams(V *a) { (void)a; return F_Chk_dflatten_dlams(a[0], a[1]); }
static V L2699(V *a) {
return C1(1, C2(0, a[0], a[1]));
}
static V F_Chk_dP_dpure(V a1) {
top:;
return mk_clo(L2699, 2, 1, (V[]){a1});
}
static V W_Chk_dP_dpure(V *a) { (void)a; return F_Chk_dP_dpure(a[1]); }
static V F_Chk_drows_dctr(V a0) {
top:;
V s2700 = a0;
if ((s2700) == IMM(0)) {
return IMM(0);
} else if (TAG(s2700) == 1 && TAG(FLD(s2700, 0)) == 3 && TAG(FLD(FLD(s2700, 0), 0)) == 1 && TAG(FLD(FLD(FLD(s2700, 0), 0), 0)) == 1) {
return C1(1, C3(1, FLD(FLD(FLD(FLD(s2700, 0), 0), 0), 0), FLD(FLD(FLD(FLD(s2700, 0), 0), 0), 1), FLD(FLD(FLD(FLD(s2700, 0), 0), 0), 2)));
} else if (TAG(s2700) == 1) {
{ V t0 = FLD(s2700, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_drows_dctr(V *a) { (void)a; return F_Chk_drows_dctr(a[0]); }
static V F_Chk_dP_dmf_dcol_dvar(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s2701 = a7;
V s2702 = a8;
if ((s2701) == IMM(0) && (s2702) == IMM(0)) {
return F_Chk_dP_dmf_dvarcol(a0, a1, a2, a3, a4, a5, a6);
} else {
return F_Chk_dP_dif(F_Chk_dPt_dsame(a6, a4), F_Chk_dP_dmf_dctr(a0, a1, a2, a3, a4, a5, s2701), F_Chk_dP_dmf_dskip(a0, a1, a2, a3, a4, a5));
}
}
static V W_Chk_dP_dmf_dcol_dvar(V *a) { (void)a; return F_Chk_dP_dmf_dcol_dvar(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V L2709(V *a) {
return F_Chk_dP_dpure(C4(17, a[2], a[1], a[3], a[0]));
}
static V L2708(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dmatch__flatten(C2(1, a[7], a[6]), F_Chk_dmf_dothers(a[5], a[4]), a[3], C2(1, a[2], a[1])), mk_clo(L2709, 4, 3, (V[]){a[0], a[8], a[4]}));
}
static V L2707(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dmatch__flatten(F_List_dappend(F_Chk_dpatt__terms(a[8], IMM(0)), a[7]), a[9], a[6], F_List_dappend(a[8], a[5])), mk_clo(L2708, 9, 8, (V[]){a[0], a[5], a[1], a[6], a[2], a[3], a[7], a[4]}));
}
static V L2706(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_dmf_drows(a[8], a[7], a[6], a[9], a[5])), mk_clo(L2707, 10, 9, (V[]){a[0], a[6], a[7], a[8], a[1], a[2], a[3], a[4], a[5]}));
}
static V L2705(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(C3(1, a[7], a[8], F_Chk_dPt_ds(a[6]))), mk_clo(L2706, 10, 9, (V[]){a[0], a[1], a[2], a[3], a[4], a[8], a[6], a[7], a[5]}));
}
static V F_Chk_dP_dmf_dctr(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s2703 = a6;
if ((s2703) == IMM(0)) {
return F_Chk_dP_dpure(C1(18, a3));
} else if (TAG(s2703) == 1 && TAG(FLD(s2703, 0)) == 1) {
V v2704 = F_Chk_dpatt__mark(F_Chk_dPt_dvar__q(a4), a2);
return F_Chk_dP_dbind(F_Chk_dP_dmf_dfields(FLD(FLD(s2703, 0), 1), v2704), mk_clo(L2705, 9, 8, (V[]){FLD(FLD(s2703, 0), 2), a0, a5, a3, a1, a2, a4, FLD(FLD(s2703, 0), 0)}));
} else if (TAG(s2703) == 1) {
return F_Chk_dP_dpure(C1(18, a3));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dmf_dctr(V *a) { (void)a; return F_Chk_dP_dmf_dctr(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dmf_dothers(V a0, V a1) {
top:;
V s2710 = a0;
if ((s2710) == IMM(0)) {
return IMM(0);
} else if (TAG(s2710) == 1 && TAG(FLD(s2710, 0)) == 3 && TAG(FLD(FLD(s2710, 0), 0)) == 1 && TAG(FLD(FLD(FLD(s2710, 0), 0), 0)) == 1) {
return F_Chk_dmf_dothers_dif(C2(3, C2(1, C3(1, FLD(FLD(FLD(FLD(s2710, 0), 0), 0), 0), FLD(FLD(FLD(FLD(s2710, 0), 0), 0), 1), FLD(FLD(FLD(FLD(s2710, 0), 0), 0), 2)), FLD(FLD(FLD(s2710, 0), 0), 1)), FLD(FLD(s2710, 0), 1)), F_Chk_dmf_dothers(FLD(s2710, 1), a1), F_String_deq(FLD(FLD(FLD(FLD(s2710, 0), 0), 0), 0), a1));
} else if (TAG(s2710) == 1) {
return C2(1, FLD(s2710, 0), F_Chk_dmf_dothers(FLD(s2710, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dmf_dothers(V *a) { (void)a; return F_Chk_dmf_dothers(a[0], a[1]); }
static V F_Chk_dmf_dothers_dif(V a0, V a1, V a2) {
top:;
V s2711 = a2;
if ((s2711) == IMM(1)) {
return a1;
} else if ((s2711) == IMM(0)) {
return C2(1, a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dmf_dothers_dif(V *a) { (void)a; return F_Chk_dmf_dothers_dif(a[0], a[1], a[2]); }
static V F_Chk_dmf_drows(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2712 = a0;
if ((s2712) == IMM(0)) {
return IMM(0);
} else if (TAG(s2712) == 1 && TAG(FLD(s2712, 0)) == 3 && TAG(FLD(FLD(s2712, 0), 0)) == 1 && TAG(FLD(FLD(FLD(s2712, 0), 0), 0)) == 1) {
return F_Chk_dmf_drows_dctr(FLD(FLD(FLD(FLD(s2712, 0), 0), 0), 0), FLD(FLD(FLD(FLD(s2712, 0), 0), 0), 1), FLD(FLD(FLD(s2712, 0), 0), 1), FLD(FLD(s2712, 0), 1), a1, a2, a3, a4, F_String_deq(FLD(FLD(FLD(FLD(s2712, 0), 0), 0), 0), a1), F_Chk_dmf_drows(FLD(s2712, 1), a1, a2, a3, a4));
} else if (TAG(s2712) == 1 && TAG(FLD(s2712, 0)) == 3 && TAG(FLD(FLD(s2712, 0), 0)) == 1 && TAG(FLD(FLD(FLD(s2712, 0), 0), 0)) == 0) {
return C2(1, C2(3, F_List_dappend(a4, FLD(FLD(FLD(s2712, 0), 0), 1)), F_Chk_dbody__sub(F_Chk_dbody__sub(FLD(FLD(s2712, 0), 1), FLD(FLD(FLD(FLD(s2712, 0), 0), 0), 1), a2), F_Chk_dPt_di(a2), a3)), F_Chk_dmf_drows(FLD(s2712, 1), a1, a2, a3, a4));
} else if (TAG(s2712) == 1) {
{ V t0 = FLD(s2712, 1); V t1 = a1; V t2 = a2; V t3 = a3; V t4 = a4; a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dmf_drows(V *a) { (void)a; return F_Chk_dmf_drows(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dPt_di(V a0) {
top:;
V s2713 = a0;
if (TAG(s2713) == 0) {
return FLD(s2713, 1);
} else if (TAG(s2713) == 1) {
return 0u;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPt_di(V *a) { (void)a; return F_Chk_dPt_di(a[0]); }
static V F_Chk_dbody__sub(V a0, V a1, V a2) {
top:;
V s2714 = a0;
if (TAG(s2714) == 0) {
return C3(0, F_Chk_dbody__sub_dscruts(a1, a2, FLD(s2714, 0)), F_Chk_dbody__sub_drows(FLD(s2714, 1), a1, a2), FLD(s2714, 2));
} else if (TAG(s2714) == 1) {
return C4(1, FLD(s2714, 0), FLD(s2714, 1), F_Chk_dbody__sub_dscruts(a1, a2, FLD(s2714, 2)), F_Chk_dbody__sub(FLD(s2714, 3), a1, a2));
} else if (TAG(s2714) == 2) {
return C2(2, C4(5, a1, a2, FLD(s2714, 0), IMM(0)), FLD(s2714, 1));
} else if (TAG(s2714) == 3) {
return C2(3, FLD(s2714, 0), F_Chk_dbody__sub(FLD(s2714, 1), a1, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dbody__sub(V *a) { (void)a; return F_Chk_dbody__sub(a[0], a[1], a[2]); }
static V F_Chk_dbody__sub_dscruts(V a0, V a1, V a2) {
top:;
V s2715 = a2;
if ((s2715) == IMM(0)) {
return IMM(0);
} else if (TAG(s2715) == 1) {
return C2(1, F_Chk_dbody__sub_dscrut(a0, a1, FLD(s2715, 0)), F_Chk_dbody__sub_dscruts(a0, a1, FLD(s2715, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dbody__sub_dscruts(V *a) { (void)a; return F_Chk_dbody__sub_dscruts(a[0], a[1], a[2]); }
static V F_Chk_dbody__sub_dscrut(V a0, V a1, V a2) {
top:;
V s2716 = a2;
if (TAG(s2716) == 0) {
return F_Bool_dpick(F_U32_dis__eq(a0, FLD(s2716, 1)), F_Chk_dpatt__term(a1, FLD(s2716, 2)), C3(0, FLD(s2716, 0), FLD(s2716, 1), FLD(s2716, 2)));
} else {
return C4(5, a0, a1, s2716, IMM(0));
}
}
static V W_Chk_dbody__sub_dscrut(V *a) { (void)a; return F_Chk_dbody__sub_dscrut(a[0], a[1], a[2]); }
static V F_Chk_dbody__sub_drows(V a0, V a1, V a2) {
top:;
V s2717 = a0;
if ((s2717) == IMM(0)) {
return IMM(0);
} else if (TAG(s2717) == 1) {
return C2(1, F_Chk_dbody__sub(FLD(s2717, 0), a1, a2), F_Chk_dbody__sub_drows(FLD(s2717, 1), a1, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dbody__sub_drows(V *a) { (void)a; return F_Chk_dbody__sub_drows(a[0], a[1], a[2]); }
static V F_Chk_dmf_drows_dctr(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9) {
top:;
V s2718 = a8;
if ((s2718) == IMM(1)) {
return C2(1, C2(3, F_List_dappend(a1, a2), F_Chk_dbody__sub(a3, F_Chk_dPt_di(a5), a6)), a9);
} else if ((s2718) == IMM(0)) {
return a9;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dmf_drows_dctr(V *a) { (void)a; return F_Chk_dmf_drows_dctr(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]); }
static V F_Chk_dPt_ds(V a0) {
top:;
V s2719 = a0;
if (TAG(s2719) == 0) {
return FLD(s2719, 3);
} else if (TAG(s2719) == 1) {
return FLD(s2719, 2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPt_ds(V *a) { (void)a; return F_Chk_dPt_ds(a[0]); }
static V L2721(V *a) {
return F_Chk_dP_dpure(C2(1, C4(0, a[4], a[3], F_Chk_dquant__join(a[2], a[1]), a[0]), a[5]));
}
static V S2724(void) { static V c; return STRC(c, "_"); }
static V L2723(V *a) {
return F_Chk_dP_dpure(C2(1, C4(0, F_String_dappend(S2724(), F_U32_dshow(a[2])), a[2], a[1], F_Chk_dPt_ds(a[0])), a[3]));
}
static V L2722(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dmf_dfields(a[2], a[1]), mk_clo(L2723, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V F_Chk_dP_dmf_dfields(V a0, V a1) {
top:;
V s2720 = a0;
if ((s2720) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s2720) == 1 && TAG(FLD(s2720, 0)) == 0) {
return F_Chk_dP_dbind(F_Chk_dP_dmf_dfields(FLD(s2720, 1), a1), mk_clo(L2721, 6, 5, (V[]){FLD(FLD(s2720, 0), 3), a1, FLD(FLD(s2720, 0), 2), FLD(FLD(s2720, 0), 1), FLD(FLD(s2720, 0), 0)}));
} else if (TAG(s2720) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dfresh__id(), mk_clo(L2722, 4, 3, (V[]){FLD(s2720, 0), a1, FLD(s2720, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dmf_dfields(V *a) { (void)a; return F_Chk_dP_dmf_dfields(a[0], a[1]); }
static V L2725(V *a) {
return F_Chk_dP_dfresh__id_dgo(a[0]);
}
static V F_Chk_dP_dfresh__id(void) {
top:;
return mk_clo(L2725, 1, 0, 0);
}
static V W_Chk_dP_dfresh__id(V *a) { (void)a; return F_Chk_dP_dfresh__id(); }
static V F_Chk_dP_dfresh__id_dgo(V a0) {
top:;
V v2726 = a0;
return C1(1, C2(0, FLD(v2726, 3), CN(0, 9, (V[]){FLD(v2726, 0), FLD(v2726, 1), FLD(v2726, 2), F_U32_dinc(FLD(v2726, 3)), FLD(v2726, 4), FLD(v2726, 5), FLD(v2726, 6), FLD(v2726, 7), FLD(v2726, 8)})));
}
static V W_Chk_dP_dfresh__id_dgo(V *a) { (void)a; return F_Chk_dP_dfresh__id_dgo(a[0]); }
static V F_Chk_dPt_dvar__q(V a0) {
top:;
V s2727 = a0;
if (TAG(s2727) == 0) {
return FLD(s2727, 2);
} else {
return IMM(1);
}
}
static V W_Chk_dPt_dvar__q(V *a) { (void)a; return F_Chk_dPt_dvar__q(a[0]); }
static V F_Chk_dpatt__mark(V a0, V a1) {
top:;
V s2728 = a1;
if ((s2728) == IMM(0)) {
return a0;
} else if (TAG(s2728) == 1 && TAG(FLD(s2728, 0)) == 3 && TAG(FLD(FLD(s2728, 0), 0)) == 1 && TAG(FLD(FLD(FLD(s2728, 0), 0), 0)) == 0) {
{ V t0 = F_Chk_dquant__join(a0, FLD(FLD(FLD(FLD(s2728, 0), 0), 0), 2)); V t1 = FLD(s2728, 1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2728) == 1) {
{ V t0 = a0; V t1 = FLD(s2728, 1); a0 = t0; a1 = t1; goto top; }
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
V s2729 = a1;
if ((s2729) == IMM(1)) {
return a2;
} else if ((s2729) == IMM(0)) {
return a3;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dif(V *a) { (void)a; return F_Chk_dP_dif(a[1], a[2], a[3]); }
static V L2731(V *a) {
return F_Chk_dP_dmatch__flatten(a[4], a[5], a[3], F_Chk_dvars_dreplace(C2(1, a[2], a[1]), a[0]));
}
static V F_Chk_dP_dmf_dvarcol(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2730 = F_Chk_dPt_dwith__q(a6, F_Chk_dpatt__mark(F_Chk_dPt_dvar__q(a6), a2));
return F_Chk_dP_dbind(F_Chk_dP_dmf_dvarrows(a2, v2730), mk_clo(L2731, 6, 5, (V[]){v2730, a5, a4, a3, a1}));
}
static V W_Chk_dP_dmf_dvarcol(V *a) { (void)a; return F_Chk_dP_dmf_dvarcol(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dvars_dreplace(V a0, V a1) {
top:;
V s2732 = a0;
if ((s2732) == IMM(0)) {
return IMM(0);
} else if (TAG(s2732) == 1) {
return C2(1, F_Bool_dpick(F_Chk_dPt_dsame(FLD(s2732, 0), a1), a1, FLD(s2732, 0)), F_Chk_dvars_dreplace(FLD(s2732, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dvars_dreplace(V *a) { (void)a; return F_Chk_dvars_dreplace(a[0], a[1]); }
static V L2734(V *a) {
return F_Chk_dP_dpure(C2(1, C2(3, a[3], F_Chk_dbody__sub(a[2], a[1], a[0])), a[4]));
}
static V S2735(void) { static V c; return STRC(c, "a variable pattern (this column has no constructor row)"); }
static V F_Chk_dP_dmf_dvarrows(V a0, V a1) {
top:;
V s2733 = a0;
if ((s2733) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s2733) == 1 && TAG(FLD(s2733, 0)) == 3 && TAG(FLD(FLD(s2733, 0), 0)) == 1 && TAG(FLD(FLD(FLD(s2733, 0), 0), 0)) == 0) {
return F_Chk_dP_dbind(F_Chk_dP_dmf_dvarrows(FLD(s2733, 1), a1), mk_clo(L2734, 5, 4, (V[]){a1, FLD(FLD(FLD(FLD(s2733, 0), 0), 0), 1), FLD(FLD(s2733, 0), 1), FLD(FLD(FLD(s2733, 0), 0), 1)}));
} else if (TAG(s2733) == 1 && TAG(FLD(s2733, 0)) == 3 && TAG(FLD(FLD(s2733, 0), 0)) == 1) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2735(), IMM(0), F_Chk_dPt_ds(FLD(FLD(FLD(s2733, 0), 0), 0))));
} else if (TAG(s2733) == 1) {
{ V t0 = FLD(s2733, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dmf_dvarrows(V *a) { (void)a; return F_Chk_dP_dmf_dvarrows(a[0], a[1]); }
static V F_Chk_dPt_dwith__q(V a0, V a1) {
top:;
V s2736 = a0;
if (TAG(s2736) == 0) {
return C4(0, FLD(s2736, 0), FLD(s2736, 1), a1, FLD(s2736, 3));
} else {
return s2736;
}
}
static V W_Chk_dPt_dwith__q(V *a) { (void)a; return F_Chk_dPt_dwith__q(a[0], a[1]); }
static V F_Chk_dTm_dstrip__subs(V a0) {
top:;
V s2737 = a0;
if (TAG(s2737) == 5) {
{ V t0 = FLD(s2737, 2); a0 = t0; goto top; }
} else {
return s2737;
}
}
static V W_Chk_dTm_dstrip__subs(V *a) { (void)a; return F_Chk_dTm_dstrip__subs(a[0]); }
static V S2739(void) { static V c; return STRC(c, "a match on a parameter or field (this name is a def or a consumed binder: give the value its own def)"); }
static V S2740(void) { static V c; return STRC(c, "a match on a parameter or field (this name is a def or a consumed binder: give the value its own def)"); }
static V S2741(void) { static V c; return STRC(c, "an undestructed scrutinee (this value is already a constructor: bind its fields directly; if an outer match destructed it, fold the pattern into the outer case)"); }
static V S2742(void) { static V c; return STRC(c, "an undestructed scrutinee (this value is already a constructor: bind its fields directly; if an outer match destructed it, fold the pattern into the outer case)"); }
static V S2743(void) { static V c; return STRC(c, "a parameter or field scrutinee (a match cannot scrutinize a computed value: give it its own def)"); }
static V F_Chk_dP_dmf_dbad(V a0, V a1) {
top:;
V s2738 = a0;
if (TAG(s2738) == 0) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2739(), IMM(0), FLD(s2738, 2)));
} else if (TAG(s2738) == 3) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2740(), IMM(0), FLD(s2738, 2)));
} else if (TAG(s2738) == 15) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2741(), IMM(0), a1));
} else if (TAG(s2738) == 16) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2742(), IMM(0), a1));
} else {
return F_Chk_dP_dthrow(F_Chk_derr0(S2743(), IMM(0), F_Chk_dSp_dor(F_Chk_dTm_dspan(s2738), a1)));
}
}
static V W_Chk_dP_dmf_dbad(V *a) { (void)a; return F_Chk_dP_dmf_dbad(a[0], a[1]); }
static V F_Chk_dP_dflatten_dlocal(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2744 = a0;
if (TAG(s2744) == 1 && TAG(FLD(s2744, 0)) == 1 && (FLD(s2744, 1)) == IMM(0)) {
return F_Chk_dP_dmatch__flatten(a2, C2(1, C2(3, C2(1, C3(1, FLD(FLD(s2744, 0), 0), FLD(FLD(s2744, 0), 1), FLD(FLD(s2744, 0), 2)), IMM(0)), a3), IMM(0)), F_Chk_dTm_dspan(F_Chk_dLst_dhead(C1(18, IMM(0)), a2)), a4);
} else {
return F_Chk_dP_dflatten_dlet(s2744, a1, a2, a3, a4);
}
}
static V W_Chk_dP_dflatten_dlocal(V *a) { (void)a; return F_Chk_dP_dflatten_dlocal(a[0], a[1], a[2], a[3], a[4]); }
static V S2747(void) { static V c; return STRC(c, "_"); }
static V L2746(V *a) {
return F_Chk_dP_dpure(F_Chk_dflatten_dlams(a[3], CN(6, 6, (V[]){F_Chk_dPt_dks(a[2]), F_Chk_dPt_dis(a[2]), a[1], C3(25, IMM(0), F_Chk_dPt_dis(a[2]), a[4]), F_Chk_dPt_ds(F_Chk_dLst_dhead(C4(0, S2747(), 0u, IMM(1), IMM(0)), a[2])), F_Chk_dPt_dqs(a[2], a[0])})));
}
static V L2745(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dflatten_dstrip(a[3], a[4]), mk_clo(L2746, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V F_Chk_dP_dflatten_dlet(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dflatten(a3, a0), mk_clo(L2745, 5, 4, (V[]){a1, a2, a4, a0}));
}
static V W_Chk_dP_dflatten_dlet(V *a) { (void)a; return F_Chk_dP_dflatten_dlet(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dPt_dqs(V a0, V a1) {
top:;
V s2748 = a0;
if ((s2748) == IMM(0)) {
return IMM(0);
} else if (TAG(s2748) == 1) {
return C2(1, F_Chk_dquant__dem(a1, F_Chk_dPt_dq(FLD(s2748, 0))), F_Chk_dPt_dqs(FLD(s2748, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPt_dqs(V *a) { (void)a; return F_Chk_dPt_dqs(a[0], a[1]); }
static V F_Chk_dPt_dq(V a0) {
top:;
V s2749 = a0;
if (TAG(s2749) == 0) {
return FLD(s2749, 2);
} else if (TAG(s2749) == 1) {
return IMM(1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPt_dq(V *a) { (void)a; return F_Chk_dPt_dq(a[0]); }
static V F_Chk_dPt_dis(V a0) {
top:;
V s2750 = a0;
if ((s2750) == IMM(0)) {
return IMM(0);
} else if (TAG(s2750) == 1) {
return C2(1, F_Chk_dPt_di(FLD(s2750, 0)), F_Chk_dPt_dis(FLD(s2750, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPt_dis(V *a) { (void)a; return F_Chk_dPt_dis(a[0]); }
static V F_Chk_dPt_dks(V a0) {
top:;
V s2751 = a0;
if ((s2751) == IMM(0)) {
return IMM(0);
} else if (TAG(s2751) == 1) {
return C2(1, F_Chk_dPt_dk(FLD(s2751, 0)), F_Chk_dPt_dks(FLD(s2751, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPt_dks(V *a) { (void)a; return F_Chk_dPt_dks(a[0]); }
static V F_Chk_dPt_dk(V a0) {
top:;
V s2752 = a0;
if (TAG(s2752) == 0) {
return FLD(s2752, 0);
} else if (TAG(s2752) == 1) {
return FLD(s2752, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPt_dk(V *a) { (void)a; return F_Chk_dPt_dk(a[0]); }
static V S2755(void) { static V c; return STRC(c, "a parameter or field scrutinee (a match cannot scrutinize a local binder: give it its own def)"); }
static V F_Chk_dP_dflatten_dstrip(V a0, V a1) {
top:;
V s2753 = a0;
V s2754 = a1;
if ((s2753) == IMM(0)) {
return F_Chk_dP_dpure(s2754);
} else if (TAG(s2753) == 1 && TAG(s2754) == 12) {
{ V t0 = FLD(s2753, 1); V t1 = F_Chk_dsyn__body(FLD(s2754, 2)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s2753) == 1) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2755(), IMM(0), F_Chk_dPt_ds(FLD(s2753, 0))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dflatten_dstrip(V *a) { (void)a; return F_Chk_dP_dflatten_dstrip(a[0], a[1]); }
static V S2759(void) { static V c; return STRC(c, "match"); }
static V L2760(V *a) {
return F_Chk_dP_dif(a[3], F_Chk_dP_dbody_dmatch(a[2], a[1]), F_Chk_dP_dbody_dlocal(a[2], a[1], a[0]));
}
static V L2758(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dword(S2759()), mk_clo(L2760, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L2757(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcol(), mk_clo(L2758, 3, 2, (V[]){a[1], a[0]}));
}
static V L2756(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L2757, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dbody(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2756, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbody(V *a) { (void)a; return F_Chk_dP_dbody(a[0]); }
static V S2761(void) { static V c; return STRC(c, "-"); }
static V S2768(void) { static V c; return STRC(c, ":"); }
static V S2772(void) { static V c; return STRC(c, "="); }
static V S2775(void) { static V c; return STRC(c, "=="); }
static V L2776(V *a) {
return F_Chk_dP_dbody_dlocal_dgo(a[6], a[5], a[4], a[3], a[2], a[1], F_Bool_dand(a[0], F_Bool_dnot(a[7])));
}
static V L2774(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S2775()), mk_clo(L2776, 8, 7, (V[]){a[0], a[6], a[1], a[2], a[3], a[4], a[5]}));
}
static V L2773(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody_dty__ok(a[6], a[5], a[7]), mk_clo(L2774, 7, 6, (V[]){a[7], a[0], a[1], a[2], a[3], a[4]}));
}
static V L2771(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S2772()), mk_clo(L2773, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L2770(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2771, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[6], a[5]}));
}
static V L2769(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[6], F_Chk_dP_dbody_dty(), F_Chk_dP_dpure(IMM(0))), mk_clo(L2770, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L2767(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Nat_dis__eq(F_List_dlength(a[4]), 1u), F_Chk_dP_dtake(S2768()), F_Chk_dP_dpure(IMM(0))), mk_clo(L2769, 7, 6, (V[]){a[4], a[0], a[1], a[2], a[3], a[5]}));
}
static V L2766(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcur(), mk_clo(L2767, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L2765(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dlocal_dnames(a[4], C2(1, a[3], IMM(0))), mk_clo(L2766, 5, 4, (V[]){a[4], a[0], a[1], a[2]}));
}
static V L2764(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2765, 6, 5, (V[]){a[0], a[1], a[2], a[4], a[3]}));
}
static V L2763(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[3], F_Chk_dP_dbody_derased__name(a[2]), F_Chk_dP_dterm0()), mk_clo(L2764, 5, 4, (V[]){a[0], a[2], a[1], a[4]}));
}
static V L2762(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Bool_dpick(a[3], IMM(0), IMM(1))), mk_clo(L2763, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Chk_dP_dbody_dlocal(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2761()), mk_clo(L2762, 4, 3, (V[]){a2, a0, a1}));
}
static V W_Chk_dP_dbody_dlocal(V *a) { (void)a; return F_Chk_dP_dbody_dlocal(a[0], a[1], a[2]); }
static V F_Chk_dP_dbody_dlocal_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v2777 = F_Nat_dis__eq(F_List_dlength(a4), 1u);
V v2778 = F_Bool_dand(F_Bool_dand(F_Maybe_dis__none(a5), F_Chk_dQ_dis__lone(a3)), F_Bool_dand(v2777, F_Bool_dnot(a6)));
return F_Chk_dP_dif(v2778, F_Chk_dP_dbody_dreply(a0, a1, a2, F_Chk_dLst_dhead(C1(18, IMM(0)), a4)), F_Chk_dP_dbody_dlet(a0, a1, a3, a4, a5, IMM(0)));
}
static V W_Chk_dP_dbody_dlocal_dgo(V *a) { (void)a; return F_Chk_dP_dbody_dlocal_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S2782(void) { static V c; return STRC(c, ";"); }
static V L2787(V *a) {
return F_Chk_dP_dpure(C4(1, a[3], a[2], a[1], a[0]));
}
static V L2786(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[3]), mk_clo(L2787, 5, 4, (V[]){a[4], a[0], a[1], a[2]}));
}
static V L2785(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody(a[3]), mk_clo(L2786, 5, 4, (V[]){a[0], a[1], a[4], a[2]}));
}
static V L2784(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody_dbinders(a[4], F_Bool_dor(F_Nat_dis__gt(F_List_dlength(a[4]), 1u), F_Maybe_dis__some(a[3]))), mk_clo(L2785, 5, 4, (V[]){a[0], a[1], a[5], a[2]}));
}
static V L2783(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L2784, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L2781(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2782()), mk_clo(L2783, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L2780(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2781, 6, 5, (V[]){a[4], a[0], a[1], a[2], a[3]}));
}
static V L2779(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody_dvals(a[4], F_List_dlength(a[3])), mk_clo(L2780, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Chk_dP_dbody_dlet(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Chk_dLst_dempty(a5), F_Chk_dP_dbody_dlet_deq(a1, a4), F_Chk_dP_dpure(a5)), mk_clo(L2779, 5, 4, (V[]){a2, a0, a4, a3}));
}
static V W_Chk_dP_dbody_dlet(V *a) { (void)a; return F_Chk_dP_dbody_dlet(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S2789(void) { static V c; return STRC(c, "a name (a parallel or typed let binds names; destructure in its body)"); }
static V L2792(V *a) {
return F_Chk_dP_dpure(C2(1, a[0], a[1]));
}
static V L2791(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody_dbinders(a[1], a[0]), mk_clo(L2792, 2, 1, (V[]){a[2]}));
}
static V L2790(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpatt(a[2]), mk_clo(L2791, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dbody_dbinders(V a0, V a1) {
top:;
V s2788 = a0;
if ((s2788) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s2788) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Bool_dand(a1, F_Bool_dnot(F_Chk_dTm_dis__var(FLD(s2788, 0)))), F_Chk_dP_dthrow(F_Chk_derr0(S2789(), IMM(0), F_Chk_dTm_dspan(FLD(s2788, 0)))), F_Chk_dP_dpure(IMM(0))), mk_clo(L2790, 4, 3, (V[]){a1, FLD(s2788, 1), FLD(s2788, 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dbody_dbinders(V *a) { (void)a; return F_Chk_dP_dbody_dbinders(a[0], a[1]); }
static V L2794(V *a) {
return F_Chk_dP_dpatt_dctr(a[2], a[1], a[0], F_Chk_dbook__ctr(a[3], a[2]));
}
static V F_Chk_dP_dpatt(V a0) {
top:;
V s2793 = a0;
if (TAG(s2793) == 15) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L2794, 4, 3, (V[]){FLD(s2793, 2), FLD(s2793, 1), FLD(s2793, 0)}));
} else if (TAG(s2793) == 16) {
{ V t0 = F_Chk_dlit__full(C2(16, FLD(s2793, 0), FLD(s2793, 1))); a0 = t0; goto top; }
} else {
return F_Chk_dP_dpatt_dvar(s2793, F_Chk_dTm_dis__var(s2793));
}
}
static V W_Chk_dP_dpatt(V *a) { (void)a; return F_Chk_dP_dpatt(a[0]); }
static V F_Chk_dTm_dis__var(V a0) {
top:;
V s2795 = a0;
if (TAG(s2795) == 0) {
return IMM(1);
} else if (TAG(s2795) == 3) {
return IMM(1);
} else if (TAG(s2795) == 2) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__var(V *a) { (void)a; return F_Chk_dTm_dis__var(a[0]); }
static V L2798(V *a) {
return F_Chk_dP_dpatt_dvar_dgo(a[1], F_Maybe_dis__some(F_Chk_dbook__ctr(a[2], a[0])));
}
static V L2797(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L2798, 3, 2, (V[]){a[1], a[0]}));
}
static V F_Chk_dP_dpatt_dvar(V a0, V a1) {
top:;
V s2796 = a1;
if ((s2796) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(F_Chk_dTm_dname(a0)), mk_clo(L2797, 2, 1, (V[]){a0}));
} else if ((s2796) == IMM(0)) {
return F_Chk_dP_dpatt_dother(a0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dpatt_dvar(V *a) { (void)a; return F_Chk_dP_dpatt_dvar(a[0], a[1]); }
static V S2800(void) { static V c; return STRC(c, "a pattern (a binder or a constructor)"); }
static V L2799(V *a) {
return F_Chk_dP_dthrow(F_Chk_derr0(S2800(), C1(1, F_Chk_dterm__show(F_Chk_dterm__lower(a[1], F_Chk_dhigher0(a[1], a[0]), 0u), 0u, IMM(0))), F_Chk_dTm_dspan(a[0])));
}
static V F_Chk_dP_dpatt_dother(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L2799, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dpatt_dother(V *a) { (void)a; return F_Chk_dP_dpatt_dother(a[0]); }
static V S2802(void) { static V c; return STRC(c, "a braced constructor pattern ("); }
static V S2803(void) { static V c; return STRC(c, " is a constructor: write "); }
static V S2804(void) { static V c; return STRC(c, "{}, or rename the binder)"); }
static V F_Chk_dP_dpatt_dvar_dgo(V a0, V a1) {
top:;
V s2801 = a1;
if ((s2801) == IMM(1)) {
return F_Chk_dP_dthrow(F_Chk_derr0(F_String_dappend(S2802(), F_String_dappend(F_Chk_dTm_dname(a0), F_String_dappend(S2803(), F_String_dappend(F_Chk_dTm_dname(a0), S2804())))), IMM(0), F_Chk_dTm_dspan(a0)));
} else if ((s2801) == IMM(0)) {
return F_Chk_dP_dbinder(a0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dpatt_dvar_dgo(V *a) { (void)a; return F_Chk_dP_dpatt_dvar_dgo(a[0], a[1]); }
static V S2806(void) { static V c; return STRC(c, "a lambda binder (one name: k => body)"); }
static V F_Chk_dP_dbinder(V a0) {
top:;
V s2805 = a0;
if (TAG(s2805) == 0) {
return F_Chk_dP_dbinder_dgo(FLD(s2805, 0), IMM(1), FLD(s2805, 2));
} else if (TAG(s2805) == 3) {
return F_Chk_dP_dbinder_dgo(FLD(s2805, 0), IMM(1), FLD(s2805, 2));
} else if (TAG(s2805) == 2) {
return F_Chk_dP_dbinder_dgo(FLD(s2805, 0), IMM(2), FLD(s2805, 1));
} else {
return F_Chk_dP_dfail(S2806());
}
}
static V W_Chk_dP_dbinder(V *a) { (void)a; return F_Chk_dP_dbinder(a[0]); }
static V L2807(V *a) {
return F_Chk_dP_dpure(C4(0, a[2], a[3], a[1], a[0]));
}
static V F_Chk_dP_dbinder_dgo(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dopen(a0), mk_clo(L2807, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dP_dbinder_dgo(V *a) { (void)a; return F_Chk_dP_dbinder_dgo(a[0], a[1], a[2]); }
static V L2808(V *a) {
return F_Chk_dP_dopen_dgo(a[0], a[1]);
}
static V F_Chk_dP_dopen(V a0) {
top:;
return mk_clo(L2808, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dopen(V *a) { (void)a; return F_Chk_dP_dopen(a[0]); }
static V S2810(void) { static V c; return STRC(c, "_"); }
static V F_Chk_dP_dopen_dgo(V a0, V a1) {
top:;
V v2809 = a1;
return C1(1, C2(0, FLD(v2809, 3), F_Chk_dPS_dopened(CN(0, 9, (V[]){FLD(v2809, 0), FLD(v2809, 1), FLD(v2809, 2), F_U32_dinc(FLD(v2809, 3)), FLD(v2809, 4), FLD(v2809, 5), FLD(v2809, 6), FLD(v2809, 7), FLD(v2809, 8)}), a0, FLD(v2809, 3), F_Bool_dnot(F_String_deq(a0, S2810())))));
}
static V W_Chk_dP_dopen_dgo(V *a) { (void)a; return F_Chk_dP_dopen_dgo(a[0], a[1]); }
static V F_Chk_dPS_dopened(V a0, V a1, V a2, V a3) {
top:;
V s2811 = a3;
if ((s2811) == IMM(1)) {
return F_Chk_dPS_dpush(a0, C2(0, a1, a2));
} else if ((s2811) == IMM(0)) {
return a0;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dPS_dopened(V *a) { (void)a; return F_Chk_dPS_dopened(a[0], a[1], a[2], a[3]); }
static V F_Chk_dPS_dpush(V a0, V a1) {
top:;
V v2812 = a0;
return CN(0, 9, (V[]){FLD(v2812, 0), C2(1, a1, FLD(v2812, 1)), nat_addk(FLD(v2812, 2), 1), FLD(v2812, 3), FLD(v2812, 4), FLD(v2812, 5), FLD(v2812, 6), FLD(v2812, 7), FLD(v2812, 8)});
}
static V W_Chk_dPS_dpush(V *a) { (void)a; return F_Chk_dPS_dpush(a[0], a[1]); }
static V L2813(V *a) {
return C1(1, C2(0, F_Chk_dPS_dreso(a[1], a[0]), a[1]));
}
static V F_Chk_dP_dreso(V a0) {
top:;
return mk_clo(L2813, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dreso(V *a) { (void)a; return F_Chk_dP_dreso(a[0]); }
static V F_Chk_dPS_dreso(V a0, V a1) {
top:;
V v2814 = F_Chk_dStr_dfirst__dot(a1);
V v2815 = F_Chk_dPS_dreso_dalias(F_Chk_dPS_dqual(a0, a1), F_Chk_dSB2_dfind(F_Chk_dPS_dal(a0), F_String_dtake(a1, v2814)), F_String_ddrop(a1, v2814), F_Nat_dis__lt(v2814, F_String_dlength(a1)));
return F_Bool_dpick(F_Bool_dor(F_Chk_dbook__has(F_Chk_dPS_dbook(a0), v2815), F_Maybe_dis__some(F_Chk_dbook__ctr(F_Chk_dPS_dbook(a0), v2815))), v2815, a1);
}
static V W_Chk_dPS_dreso(V *a) { (void)a; return F_Chk_dPS_dreso(a[0], a[1]); }
static V F_Chk_dPS_dal(V a0) {
top:;
V v2816 = a0;
return FLD(v2816, 8);
}
static V W_Chk_dPS_dal(V *a) { (void)a; return F_Chk_dPS_dal(a[0]); }
static V S2817(void) { static V c; return STRC(c, "."); }
static V F_Chk_dPS_dqual(V a0, V a1) {
top:;
return F_Bool_dpick(F_String_dis__empty(F_Chk_dPS_dns(a0)), a1, F_String_dappend(F_Chk_dPS_dns(a0), F_String_dappend(S2817(), a1)));
}
static V W_Chk_dPS_dqual(V *a) { (void)a; return F_Chk_dPS_dqual(a[0], a[1]); }
static V F_Chk_dPS_dns(V a0) {
top:;
V v2818 = a0;
return FLD(v2818, 6);
}
static V W_Chk_dPS_dns(V *a) { (void)a; return F_Chk_dPS_dns(a[0]); }
static V F_Chk_dPS_dreso_dalias(V a0, V a1, V a2, V a3) {
top:;
V s2819 = a1;
V s2820 = a3;
if (TAG(s2819) == 1 && (s2820) == IMM(1)) {
return F_String_dappend(FLD(s2819, 0), a2);
} else {
return a0;
}
}
static V W_Chk_dPS_dreso_dalias(V *a) { (void)a; return F_Chk_dPS_dreso_dalias(a[0], a[1], a[2], a[3]); }
static V F_Chk_dStr_dfirst__dot(V a0) {
top:;
V s2821 = a0;
if ((s2821) == IMM(0)) {
return 0u;
} else if (TAG(s2821) == 1) {
return F_Bool_dpick(F_U32_dis__eq(FLD(s2821, 0), 46u), 0u, nat_addk(F_Chk_dStr_dfirst__dot(FLD(s2821, 1)), 1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dfirst__dot(V *a) { (void)a; return F_Chk_dStr_dfirst__dot(a[0]); }
static V F_Chk_dlit__full(V a0) {
top:;
V s2822 = a0;
if (TAG(s2822) == 16 && TAG(FLD(s2822, 0)) == 1) {
return F_Chk_dlit__chain(F_Chk_dStr_dcodes(FLD(FLD(s2822, 0), 0)), FLD(s2822, 1));
} else if (TAG(s2822) == 16 && TAG(FLD(s2822, 0)) == 0) {
return F_Chk_dnat__full(FLD(FLD(s2822, 0), 0), FLD(s2822, 1));
} else {
return s2822;
}
}
static V W_Chk_dlit__full(V *a) { (void)a; return F_Chk_dlit__full(a[0]); }
static V S2824(void) { static V c; return STRC(c, "Zero"); }
static V S2825(void) { static V c; return STRC(c, "Succ"); }
static V F_Chk_dnat__full(V a0, V a1) {
top:;
V s2823 = a0;
if ((s2823) == 0) {
return C3(15, S2824(), IMM(0), a1);
} else if (nat_ge(s2823, 1)) {
return C3(15, S2825(), C2(1, F_Chk_dnat__full(nat_subk(s2823, 1), a1), IMM(0)), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dnat__full(V *a) { (void)a; return F_Chk_dnat__full(a[0], a[1]); }
static V F_Chk_dStr_dcodes(V a0) {
top:;
V s2826 = a0;
if ((s2826) == IMM(0)) {
return IMM(0);
} else if (TAG(s2826) == 1) {
return C2(1, FLD(s2826, 0), F_Chk_dStr_dcodes(FLD(s2826, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dcodes(V *a) { (void)a; return F_Chk_dStr_dcodes(a[0]); }
static V S2828(void) { static V c; return STRC(c, "SNil"); }
static V S2829(void) { static V c; return STRC(c, "SCon"); }
static V F_Chk_dlit__chain(V a0, V a1) {
top:;
V s2827 = a0;
if ((s2827) == IMM(0)) {
return C3(15, S2828(), IMM(0), a1);
} else if (TAG(s2827) == 1) {
return C3(15, S2829(), C2(1, F_Chk_dchr__term(FLD(s2827, 0), a1), C2(1, F_Chk_dlit__chain(FLD(s2827, 1), a1), IMM(0))), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlit__chain(V *a) { (void)a; return F_Chk_dlit__chain(a[0], a[1]); }
static V S2831(void) { static V c; return STRC(c, "a declared constructor (unknown: "); }
static V S2832(void) { static V c; return STRC(c, ")"); }
static V F_Chk_dP_dpatt_dctr(V a0, V a1, V a2, V a3) {
top:;
V s2830 = a3;
if ((s2830) == IMM(0)) {
return F_Chk_dP_dthrow(F_Chk_derr0(F_String_dappend(S2831(), F_String_dappend(a0, S2832())), IMM(0), a2));
} else if (TAG(s2830) == 1) {
return F_Chk_dP_dpatt_dctr_dn(a0, a1, a2, FLD(FLD(s2830, 0), 1), F_Nat_dis__eq(FLD(FLD(s2830, 0), 1), F_List_dlength(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dpatt_dctr(V *a) { (void)a; return F_Chk_dP_dpatt_dctr(a[0], a[1], a[2], a[3]); }
static V S2834(void) { static V c; return STRC(c, "a "); }
static V S2835(void) { static V c; return STRC(c, " pattern with "); }
static V S2836(void) { static V c; return STRC(c, " field"); }
static V S2837(void) { static V c; return STRC(c, " fields"); }
static V L2838(V *a) {
return F_Chk_dP_dpure(C3(1, a[1], a[2], a[0]));
}
static V F_Chk_dP_dpatt_dctr_dn(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2833 = a4;
if ((s2833) == IMM(0)) {
return F_Chk_dP_dthrow(F_Chk_derr0(F_String_dappend(S2834(), F_String_dappend(a0, F_String_dappend(S2835(), F_String_dappend(F_Nat_dshow(a3), F_Bool_dpick(F_Nat_dis__eq(a3, 1u), S2836(), S2837()))))), IMM(0), a2));
} else if ((s2833) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dpatts(a1), mk_clo(L2838, 3, 2, (V[]){a2, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dpatt_dctr_dn(V *a) { (void)a; return F_Chk_dP_dpatt_dctr_dn(a[0], a[1], a[2], a[3], a[4]); }
static V L2841(V *a) {
return F_Chk_dP_dpure(C2(1, a[0], a[1]));
}
static V L2840(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpatts(a[0]), mk_clo(L2841, 2, 1, (V[]){a[1]}));
}
static V F_Chk_dP_dpatts(V a0) {
top:;
V s2839 = a0;
if ((s2839) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s2839) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dpatt(FLD(s2839, 0)), mk_clo(L2840, 2, 1, (V[]){FLD(s2839, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dpatts(V *a) { (void)a; return F_Chk_dP_dpatts(a[0]); }
static V L2842(V *a) {
return C1(1, C2(0, F_Chk_dPS_dstn(a[0]), a[0]));
}
static V F_Chk_dP_dstn(void) {
top:;
return mk_clo(L2842, 1, 0, 0);
}
static V W_Chk_dP_dstn(V *a) { (void)a; return F_Chk_dP_dstn(); }
static V F_Chk_dPS_dstn(V a0) {
top:;
V v2843 = a0;
return FLD(v2843, 2);
}
static V W_Chk_dPS_dstn(V *a) { (void)a; return F_Chk_dPS_dstn(a[0]); }
static V L2844(V *a) {
return F_Chk_dP_dtake_dif(a[0], a[1]);
}
static V F_Chk_dP_dtake(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dat(a0), mk_clo(L2844, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dtake(V *a) { (void)a; return F_Chk_dP_dtake(a[0]); }
static V L2846(V *a) {
return C1(1, C2(0, IMM(1), F_Chk_dPS_dset__cur(a[1], F_Chk_dCur_dsteps(F_Chk_dPS_dcur(a[1]), F_String_dlength(a[0])))));
}
static V F_Chk_dP_dtake_dif(V a0, V a1) {
top:;
V s2845 = a1;
if ((s2845) == IMM(1)) {
return mk_clo(L2846, 2, 1, (V[]){a0});
} else if ((s2845) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dtake_dif(V *a) { (void)a; return F_Chk_dP_dtake_dif(a[0], a[1]); }
static V F_Chk_dCur_dsteps(V a0, V a1) {
top:;
V s2847 = a1;
if ((s2847) == 0) {
return a0;
} else if (nat_ge(s2847, 1)) {
{ V t0 = F_Chk_dCur_dstep(a0); V t1 = nat_subk(s2847, 1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCur_dsteps(V *a) { (void)a; return F_Chk_dCur_dsteps(a[0], a[1]); }
static V F_Chk_dCur_dstep(V a0) {
top:;
V v2848 = a0;
return F_Chk_dCur_dstep_dgo(FLD(v2848, 0), FLD(v2848, 1), FLD(v2848, 2), FLD(v2848, 3));
}
static V W_Chk_dCur_dstep(V *a) { (void)a; return F_Chk_dCur_dstep(a[0]); }
static V F_Chk_dCur_dstep_dgo(V a0, V a1, V a2, V a3) {
top:;
V s2849 = a0;
if ((s2849) == IMM(0)) {
return CN(0, 5, (V[]){IMM(0), a1, a2, a3, 0u});
} else if (TAG(s2849) == 1) {
return CN(0, 5, (V[]){FLD(s2849, 1), F_U32_dinc(a1), F_Bool_dpick(F_U32_dis__eq(FLD(s2849, 0), 10u), 1u, F_U32_dinc(a2)), F_Bool_dpick(F_U32_dis__eq(FLD(s2849, 0), 10u), IMM(1), F_Bool_dpick(F_Bool_dor(F_U32_dis__eq(FLD(s2849, 0), 32u), F_Bool_dor(F_U32_dis__eq(FLD(s2849, 0), 13u), F_U32_dis__eq(FLD(s2849, 0), 9u))), a3, IMM(0))), FLD(s2849, 0)});
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCur_dstep_dgo(V *a) { (void)a; return F_Chk_dCur_dstep_dgo(a[0], a[1], a[2], a[3]); }
static V F_Chk_dPS_dset__cur(V a0, V a1) {
top:;
V v2850 = a0;
return CN(0, 9, (V[]){a1, FLD(v2850, 1), FLD(v2850, 2), FLD(v2850, 3), FLD(v2850, 4), FLD(v2850, 5), FLD(v2850, 6), FLD(v2850, 7), FLD(v2850, 8)});
}
static V W_Chk_dPS_dset__cur(V *a) { (void)a; return F_Chk_dPS_dset__cur(a[0], a[1]); }
static V L2851(V *a) {
return C1(1, C2(0, F_Chk_dStr_dprefix(F_Chk_dCur_drest(F_Chk_dPS_dcur(a[1])), a[0]), a[1]));
}
static V F_Chk_dP_dat(V a0) {
top:;
return mk_clo(L2851, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dat(V *a) { (void)a; return F_Chk_dP_dat(a[0]); }
static V F_Chk_dCur_drest(V a0) {
top:;
V v2852 = a0;
return FLD(v2852, 0);
}
static V W_Chk_dCur_drest(V *a) { (void)a; return F_Chk_dCur_drest(a[0]); }
static V F_Chk_dStr_dprefix(V a0, V a1) {
top:;
return F_String_dstarts__with(a0, a1);
}
static V W_Chk_dStr_dprefix(V *a) { (void)a; return F_Chk_dStr_dprefix(a[0], a[1]); }
static V L2853(V *a) {
return C1(1, C2(0, IMM(0), F_Chk_dPS_dset__cur(a[0], F_Chk_dCur_dskip(F_Chk_dPS_dcur(a[0])))));
}
static V F_Chk_dP_dskip(void) {
top:;
return mk_clo(L2853, 1, 0, 0);
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
V s2854 = a1;
if ((s2854) == 0) {
return a0;
} else if ((s2854) == 1) {
return F_Chk_dCur_dskip(F_Chk_dCur_dstep(a0));
} else if (nat_ge(s2854, 2)) {
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
V s2855 = a1;
if ((s2855) == IMM(1)) {
return a0;
} else if ((s2855) == IMM(0)) {
return F_Chk_dCur_dline(F_Chk_dCur_dstep(a0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCur_dline_dc(V *a) { (void)a; return F_Chk_dCur_dline_dc(a[0], a[1]); }
static V F_Chk_dP_dbody_dvals(V a0, V a1) {
top:;
return F_Chk_dP_dif(F_Nat_dis__ge(F_List_dlength(a0), a1), F_Chk_dP_dpure(a0), F_Chk_dP_dbody_dvals_dmore(a0, a1));
}
static V W_Chk_dP_dbody_dvals(V *a) { (void)a; return F_Chk_dP_dbody_dvals(a[0], a[1]); }
static V L2856(V *a) {
return F_Chk_dP_dbody_dvals(F_List_dappend(a[1], C2(1, a[2], IMM(0))), a[0]);
}
static V F_Chk_dP_dbody_dvals_dmore(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L2856, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dbody_dvals_dmore(V *a) { (void)a; return F_Chk_dP_dbody_dvals_dmore(a[0], a[1]); }
static V F_Chk_dP_dterm0(void) {
top:;
return F_Chk_dP_dterm(0u);
}
static V W_Chk_dP_dterm0(V *a) { (void)a; return F_Chk_dP_dterm0(); }
static V L2860(V *a) {
return F_Chk_dP_dops(F_Chk_dTm_dspanned(a[1], a[2]), a[0]);
}
static V L2859(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L2860, 3, 2, (V[]){a[0], a[2]}));
}
static V L2858(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbase(a[1]), mk_clo(L2859, 3, 2, (V[]){a[0], a[1]}));
}
static V L2857(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L2858, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dterm(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2857, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dterm(V *a) { (void)a; return F_Chk_dP_dterm(a[0]); }
static V F_Chk_dTm_dspanned(V a0, V a1) {
top:;
V s2861 = a0;
if (TAG(s2861) == 6 && (FLD(s2861, 4)) == IMM(0)) {
return CN(6, 6, (V[]){FLD(s2861, 0), FLD(s2861, 1), FLD(s2861, 2), FLD(s2861, 3), a1, FLD(s2861, 5)});
} else if (TAG(s2861) == 10 && (FLD(s2861, 2)) == IMM(0)) {
return C3(10, FLD(s2861, 0), FLD(s2861, 1), a1);
} else if (TAG(s2861) == 11 && (FLD(s2861, 5)) == IMM(0)) {
return CN(11, 6, (V[]){FLD(s2861, 0), FLD(s2861, 1), FLD(s2861, 2), FLD(s2861, 3), FLD(s2861, 4), a1});
} else if (TAG(s2861) == 12 && (FLD(s2861, 3)) == IMM(0)) {
return CN(12, 5, (V[]){FLD(s2861, 0), FLD(s2861, 1), FLD(s2861, 2), a1, FLD(s2861, 4)});
} else if (TAG(s2861) == 17 && (FLD(s2861, 3)) == IMM(0)) {
return C4(17, FLD(s2861, 0), FLD(s2861, 1), FLD(s2861, 2), a1);
} else if (TAG(s2861) == 18 && (FLD(s2861, 0)) == IMM(0)) {
return C1(18, a1);
} else if (TAG(s2861) == 19 && (FLD(s2861, 3)) == IMM(0)) {
return C4(19, FLD(s2861, 0), FLD(s2861, 1), FLD(s2861, 2), a1);
} else if (TAG(s2861) == 21 && (FLD(s2861, 3)) == IMM(0)) {
return C4(21, FLD(s2861, 0), FLD(s2861, 1), FLD(s2861, 2), a1);
} else if (TAG(s2861) == 23 && (FLD(s2861, 2)) == IMM(0)) {
return C3(23, FLD(s2861, 0), FLD(s2861, 1), a1);
} else if (TAG(s2861) == 2 && (FLD(s2861, 1)) == IMM(0)) {
return C2(2, FLD(s2861, 0), a1);
} else if (TAG(s2861) == 3 && (FLD(s2861, 2)) == IMM(0)) {
return C4(3, FLD(s2861, 0), FLD(s2861, 1), a1, FLD(s2861, 3));
} else if (TAG(s2861) == 5 && (FLD(s2861, 3)) == IMM(0)) {
return C4(5, FLD(s2861, 0), FLD(s2861, 1), FLD(s2861, 2), a1);
} else {
return F_Chk_dTm_drespan(s2861, a1);
}
}
static V W_Chk_dTm_dspanned(V *a) { (void)a; return F_Chk_dTm_dspanned(a[0], a[1]); }
static V S2867(void) { static V c; return STRC(c, "("); }
static V S2868(void) { static V c; return STRC(c, "!("); }
static V S2870(void) { static V c; return STRC(c, "["); }
static V S2871(void) { static V c; return STRC(c, "("); }
static V S2872(void) { static V c; return STRC(c, "=>"); }
static V S2873(void) { static V c; return STRC(c, "->"); }
static V S2874(void) { static V c; return STRC(c, "<&>"); }
static V L2865(V *a) {
V v2866 = F_Bool_dor(F_Chk_dStr_dprefix(a[3], S2867()), F_Chk_dStr_dprefix(a[3], S2868()));
V v2869 = F_Chk_dStr_dprefix(a[3], S2870());
return F_Chk_dP_dops_dgo(a[2], a[1], a[3], a[4], F_Bool_dpick(F_Bool_dand(a[0], F_Bool_dor(F_Chk_dStr_dprefix(a[3], S2871()), v2869)), 0u, F_Bool_dpick(v2866, 1u, F_Bool_dpick(v2869, 2u, F_Bool_dpick(F_Chk_dops_dlt(a[3], a[1], a[4]), 3u, F_Bool_dpick(F_Bool_dand(F_U32_dis__zero(a[1]), F_Chk_dStr_dprefix(a[3], S2872())), 4u, F_Bool_dpick(F_Bool_dand(F_U32_dis__zero(a[1]), F_Chk_dStr_dprefix(a[3], S2873())), 5u, F_Bool_dpick(F_Bool_dand(F_U32_dis__le(a[1], 5u), F_Chk_dStr_dprefix(a[3], S2874())), 6u, 7u))))))));
}
static V L2864(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dprev(), mk_clo(L2865, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L2863(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek__rest(), mk_clo(L2864, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L2862(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dnl(), mk_clo(L2863, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dops(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2862, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dops(V *a) { (void)a; return F_Chk_dP_dops(a[0], a[1]); }
static V S2876(void) { static V c; return STRC(c, "<"); }
static V S2877(void) { static V c; return STRC(c, "<&>"); }
static V F_Chk_dops_dlt(V a0, V a1, V a2) {
top:;
V v2875 = F_Chk_dStr_dsecond(a0);
return F_Bool_dand(F_Bool_dand(F_Chk_dStr_dprefix(a0, S2876()), F_Bool_dnot(F_Bool_dor(F_Bool_dor(F_U32_dis__eq(v2875, 45u), F_U32_dis__eq(v2875, 61u)), F_Bool_dor(F_U32_dis__eq(v2875, 60u), F_U32_dis__eq(v2875, 62u))))), F_Bool_dand(F_Bool_dnot(F_Chk_dStr_dprefix(a0, S2877())), F_Bool_dor(F_U32_dis__le(a1, 4u), F_Bool_dnot(F_Bool_dor(F_Chk_dis__space(a2), F_U32_dis__zero(a2))))));
}
static V W_Chk_dops_dlt(V *a) { (void)a; return F_Chk_dops_dlt(a[0], a[1], a[2]); }
static V F_Chk_dStr_dsecond(V a0) {
top:;
V s2878 = a0;
if (TAG(s2878) == 1 && TAG(FLD(s2878, 1)) == 1) {
return FLD(FLD(s2878, 1), 0);
} else {
return 0u;
}
}
static V W_Chk_dStr_dsecond(V *a) { (void)a; return F_Chk_dStr_dsecond(a[0]); }
static V S2880(void) { static V c; return STRC(c, "<-"); }
static V F_Chk_dP_dops_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2879 = a4;
if ((s2879) == 0) {
return F_Chk_dP_dpure(a0);
} else if ((s2879) == 1) {
return F_Chk_dP_dcall(a0, a1);
} else if ((s2879) == 2) {
return F_Chk_dP_dindex(a0, a1);
} else if ((s2879) == 3) {
return F_Chk_dP_dlt(a0, a1);
} else if ((s2879) == 4) {
return F_Chk_dP_dlam(a0, a1);
} else if ((s2879) == 5) {
return F_Chk_dP_darrow(a0, a1);
} else if ((s2879) == 6) {
return F_Chk_dP_dminq(a0, a1);
} else if (nat_ge(s2879, 7)) {
return F_Chk_dP_dinfix(a0, a1, F_Chk_dop_dfind(F_Chk_dOPS(), a2, a3), F_Chk_dStr_dprefix(a2, S2880()));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dops_dgo(V *a) { (void)a; return F_Chk_dP_dops_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V S2881(void) { static V c; return STRC(c, ".|."); }
static V S2882(void) { static V c; return STRC(c, ".or"); }
static V S2883(void) { static V c; return STRC(c, ".^."); }
static V S2884(void) { static V c; return STRC(c, ".xor"); }
static V S2885(void) { static V c; return STRC(c, ".&."); }
static V S2886(void) { static V c; return STRC(c, ".and"); }
static V S2887(void) { static V c; return STRC(c, "||"); }
static V S2888(void) { static V c; return STRC(c, "Bool.or"); }
static V S2889(void) { static V c; return STRC(c, "&&"); }
static V S2890(void) { static V c; return STRC(c, "Bool.and"); }
static V S2891(void) { static V c; return STRC(c, "<="); }
static V S2892(void) { static V c; return STRC(c, ".is_le"); }
static V S2893(void) { static V c; return STRC(c, ">="); }
static V S2894(void) { static V c; return STRC(c, ".is_ge"); }
static V S2895(void) { static V c; return STRC(c, "<>"); }
static V S2896(void) { static V c; return STRC(c, ""); }
static V S2897(void) { static V c; return STRC(c, "++"); }
static V S2898(void) { static V c; return STRC(c, "String.append"); }
static V S2899(void) { static V c; return STRC(c, "<<"); }
static V S2900(void) { static V c; return STRC(c, ".shln"); }
static V S2901(void) { static V c; return STRC(c, ">>"); }
static V S2902(void) { static V c; return STRC(c, ".shrn"); }
static V S2903(void) { static V c; return STRC(c, "&"); }
static V S2904(void) { static V c; return STRC(c, ""); }
static V S2905(void) { static V c; return STRC(c, "|"); }
static V S2906(void) { static V c; return STRC(c, ""); }
static V S2907(void) { static V c; return STRC(c, ">"); }
static V S2908(void) { static V c; return STRC(c, ".is_gt"); }
static V S2909(void) { static V c; return STRC(c, "+"); }
static V S2910(void) { static V c; return STRC(c, ".add"); }
static V S2911(void) { static V c; return STRC(c, "-"); }
static V S2912(void) { static V c; return STRC(c, ".sub"); }
static V S2913(void) { static V c; return STRC(c, "*"); }
static V S2914(void) { static V c; return STRC(c, ".mul"); }
static V S2915(void) { static V c; return STRC(c, "/"); }
static V S2916(void) { static V c; return STRC(c, ".div"); }
static V S2917(void) { static V c; return STRC(c, "%"); }
static V S2918(void) { static V c; return STRC(c, ".mod"); }
static V F_Chk_dOPS(void) {
top:;
return C2(1, C4(0, S2881(), 6u, IMM(0), S2882()), C2(1, C4(0, S2883(), 7u, IMM(0), S2884()), C2(1, C4(0, S2885(), 8u, IMM(0), S2886()), C2(1, C4(0, S2887(), 2u, IMM(0), S2888()), C2(1, C4(0, S2889(), 3u, IMM(0), S2890()), C2(1, C4(0, S2891(), 4u, IMM(0), S2892()), C2(1, C4(0, S2893(), 4u, IMM(0), S2894()), C2(1, C4(0, S2895(), 5u, IMM(1), S2896()), C2(1, C4(0, S2897(), 5u, IMM(1), S2898()), C2(1, C4(0, S2899(), 9u, IMM(0), S2900()), C2(1, C4(0, S2901(), 9u, IMM(0), S2902()), C2(1, C4(0, S2903(), 1u, IMM(1), S2904()), C2(1, C4(0, S2905(), 1u, IMM(1), S2906()), C2(1, C4(0, S2907(), 4u, IMM(0), S2908()), C2(1, C4(0, S2909(), 10u, IMM(0), S2910()), C2(1, C4(0, S2911(), 10u, IMM(0), S2912()), C2(1, C4(0, S2913(), 11u, IMM(0), S2914()), C2(1, C4(0, S2915(), 11u, IMM(0), S2916()), C2(1, C4(0, S2917(), 11u, IMM(0), S2918()), IMM(0))))))))))))))))))));
}
static V W_Chk_dOPS(V *a) { (void)a; return F_Chk_dOPS(); }
static V F_Chk_dop_dfind(V a0, V a1, V a2) {
top:;
V s2919 = a0;
if ((s2919) == IMM(0)) {
return IMM(0);
} else if (TAG(s2919) == 1) {
return F_Chk_dop_dfind_dif(FLD(s2919, 1), a1, a2, C4(0, FLD(FLD(s2919, 0), 0), FLD(FLD(s2919, 0), 1), FLD(FLD(s2919, 0), 2), FLD(FLD(s2919, 0), 3)), F_Chk_dop_dok(FLD(FLD(s2919, 0), 0), a1, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dop_dfind(V *a) { (void)a; return F_Chk_dop_dfind(a[0], a[1], a[2]); }
static V S2922(void) { static V c; return STRC(c, "-"); }
static V S2923(void) { static V c; return STRC(c, "+"); }
static V S2924(void) { static V c; return STRC(c, "%"); }
static V F_Chk_dop_dok(V a0, V a1, V a2) {
top:;
V v2920 = F_Chk_dStr_dfirst(F_String_ddrop(a1, F_String_dlength(a0)));
V v2921 = F_Chk_dStr_dfirst(a0);
return F_Bool_dand(F_Chk_dStr_dprefix(a1, a0), F_Bool_dand(F_Bool_dnot(F_Bool_dand(F_Bool_dor(F_String_deq(a0, S2922()), F_String_deq(a0, S2923())), F_Bool_dor(F_U32_dis__eq(v2920, 62u), F_Chk_dis__head(v2920)))), F_Bool_dand(F_Bool_dnot(F_Bool_dand(F_U32_dis__eq(v2921, 62u), F_Bool_dnot(F_Bool_dor(F_Chk_dis__space(a2), F_U32_dis__zero(a2))))), F_Bool_dnot(F_Bool_dand(F_String_deq(a0, S2924()), F_Bool_dnot(F_Chk_dis__space(v2920)))))));
}
static V W_Chk_dop_dok(V *a) { (void)a; return F_Chk_dop_dok(a[0], a[1], a[2]); }
static V F_Chk_dop_dfind_dif(V a0, V a1, V a2, V a3, V a4) {
top:;
V s2925 = a4;
if ((s2925) == IMM(1)) {
return C1(1, a3);
} else if ((s2925) == IMM(0)) {
return F_Chk_dop_dfind(a0, a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dop_dfind_dif(V *a) { (void)a; return F_Chk_dop_dfind_dif(a[0], a[1], a[2], a[3], a[4]); }
static V F_Chk_dP_dinfix(V a0, V a1, V a2, V a3) {
top:;
V s2926 = a2;
if ((s2926) == IMM(0)) {
return F_Chk_dP_dpure(a0);
} else if (TAG(s2926) == 1) {
return F_Chk_dP_dif(F_Bool_dor(F_U32_dis__lt(FLD(FLD(s2926, 0), 1), a1), a3), F_Chk_dP_dpure(a0), F_Chk_dP_dinfix_dgo(a0, a1, FLD(FLD(s2926, 0), 0), FLD(FLD(s2926, 0), 1), FLD(FLD(s2926, 0), 2), FLD(FLD(s2926, 0), 3)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dinfix(V *a) { (void)a; return F_Chk_dP_dinfix(a[0], a[1], a[2], a[3]); }
static V L2931(V *a) {
return F_Chk_dP_dops(F_Chk_dinfix_dbuild(a[5], a[4], a[3], a[2], a[6], a[1]), a[0]);
}
static V L2930(V *a) {
return F_Chk_dP_dbind(F_Chk_dspan_dgrow(a[4]), mk_clo(L2931, 7, 6, (V[]){a[0], a[1], a[5], a[4], a[2], a[3]}));
}
static V L2929(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm(F_Bool_dpick(a[5], a[4], F_U32_dinc(a[4]))), mk_clo(L2930, 6, 5, (V[]){a[0], a[6], a[1], a[2], a[3]}));
}
static V L2928(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(F_U32_dsub(a[6], F_U32_dfrom__nat(F_String_dlength(a[5])))), mk_clo(L2929, 7, 6, (V[]){a[0], a[1], a[5], a[2], a[3], a[4]}));
}
static V L2927(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L2928, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V F_Chk_dP_dinfix_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(a2), mk_clo(L2927, 7, 6, (V[]){a1, a5, a0, a3, a4, a2}));
}
static V W_Chk_dP_dinfix_dgo(V *a) { (void)a; return F_Chk_dP_dinfix_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S2932(void) { static V c; return STRC(c, "<>"); }
static V S2933(void) { static V c; return STRC(c, "Con"); }
static V S2934(void) { static V c; return STRC(c, "&"); }
static V S2935(void) { static V c; return STRC(c, "Pair"); }
static V S2936(void) { static V c; return STRC(c, "|"); }
static V S2937(void) { static V c; return STRC(c, "Or"); }
static V F_Chk_dinfix_dbuild(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Bool_dpick(F_String_deq(a0, S2932()), C3(15, S2933(), C2(1, a2, C2(1, a3, IMM(0))), a4), F_Bool_dpick(F_String_deq(a0, S2934()), C3(13, C3(13, C3(4, S2935(), a4, IMM(0)), a2, a4), a3, a4), F_Bool_dpick(F_String_deq(a0, S2936()), C3(13, C3(13, C3(4, S2937(), a4, IMM(0)), a2, a4), a3, a4), C3(13, C3(13, C3(4, a1, a5, IMM(0)), a2, a4), a3, a4))));
}
static V W_Chk_dinfix_dbuild(V *a) { (void)a; return F_Chk_dinfix_dbuild(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dspan_dgrow(V a0) {
top:;
return F_Chk_dP_dspan_dfrom(F_Chk_dTm_dspan(a0));
}
static V W_Chk_dspan_dgrow(V *a) { (void)a; return F_Chk_dspan_dgrow(a[0]); }
static V F_Chk_dP_dspan_dfrom(V a0) {
top:;
V s2938 = a0;
if ((s2938) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s2938) == 1) {
return F_Chk_dP_dspan(FLD(s2938, 1));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dspan_dfrom(V *a) { (void)a; return F_Chk_dP_dspan_dfrom(a[0]); }
static V L2939(V *a) {
return C1(1, C2(0, C3(1, F_Chk_dPS_dsrc(a[1]), a[0], F_Chk_dCur_dpos(F_Chk_dPS_dcur(a[1]))), a[1]));
}
static V F_Chk_dP_dspan(V a0) {
top:;
return mk_clo(L2939, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dspan(V *a) { (void)a; return F_Chk_dP_dspan(a[0]); }
static V L2940(V *a) {
return C1(1, C2(0, F_Chk_dCur_dpos(F_Chk_dPS_dcur(a[0])), a[0]));
}
static V F_Chk_dP_dpos(void) {
top:;
return mk_clo(L2940, 1, 0, 0);
}
static V W_Chk_dP_dpos(V *a) { (void)a; return F_Chk_dP_dpos(); }
static V S2941(void) { static V c; return STRC(c, "<&>"); }
static V L2944(V *a) {
return F_Chk_dP_dops(C3(10, a[2], a[1], a[3]), a[0]);
}
static V L2943(V *a) {
return F_Chk_dP_dbind(F_Chk_dspan_dgrow(a[1]), mk_clo(L2944, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L2942(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm(5u), mk_clo(L2943, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dminq(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2941()), mk_clo(L2942, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dminq(V *a) { (void)a; return F_Chk_dP_dminq(a[0], a[1]); }
static V S2945(void) { static V c; return STRC(c, "->"); }
static V S2949(void) { static V c; return STRC(c, "_"); }
static V S2951(void) { static V c; return STRC(c, "_"); }
static V L2950(V *a) {
return F_Chk_dP_dops(CN(11, 6, (V[]){IMM(1), S2951(), a[4], a[3], C3(24, IMM(0), a[4], a[2]), a[1]}), a[0]);
}
static V L2948(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dopen(S2949()), mk_clo(L2950, 5, 4, (V[]){a[0], a[3], a[1], a[2]}));
}
static V L2947(V *a) {
return F_Chk_dP_dbind(F_Chk_dspan_dgrow(a[1]), mk_clo(L2948, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L2946(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L2947, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_darrow(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2945()), mk_clo(L2946, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_darrow(V *a) { (void)a; return F_Chk_dP_darrow(a[0], a[1]); }
static V S2952(void) { static V c; return STRC(c, "=>"); }
static V L2957(V *a) {
return F_Chk_dP_dops(F_Chk_dlam_dbuild(a[2], a[1]), a[0]);
}
static V L2956(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[2]), mk_clo(L2957, 4, 3, (V[]){a[0], a[3], a[1]}));
}
static V L2955(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dblock(), mk_clo(L2956, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L2954(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbinder(a[1]), mk_clo(L2955, 3, 2, (V[]){a[0], a[2]}));
}
static V L2953(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L2954, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dlam(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2952()), mk_clo(L2953, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dlam(V *a) { (void)a; return F_Chk_dP_dlam(a[0], a[1]); }
static V F_Chk_dlam_dbuild(V a0, V a1) {
top:;
V s2958 = a0;
if (TAG(s2958) == 0) {
return CN(12, 5, (V[]){FLD(s2958, 0), FLD(s2958, 1), C3(24, IMM(0), FLD(s2958, 1), a1), FLD(s2958, 3), FLD(s2958, 2)});
} else {
return a1;
}
}
static V W_Chk_dlam_dbuild(V *a) { (void)a; return F_Chk_dlam_dbuild(a[0], a[1]); }
static V S2965(void) { static V c; return STRC(c, ">"); }
static V S2967(void) { static V c; return STRC(c, ","); }
static V S2969(void) { static V c; return STRC(c, ".is_lt"); }
static V L2968(V *a) {
return F_Chk_dP_dif(F_Bool_dor(a[5], a[6]), F_Chk_dP_dlt_dadt(a[4], a[3], a[2], a[1]), F_Chk_dP_dops(C3(13, C3(13, C3(4, S2969(), a[0], IMM(0)), a[4], a[2]), a[3], a[2]), a[1]));
}
static V L2966(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S2967()), mk_clo(L2968, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L2964(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S2965()), mk_clo(L2966, 6, 5, (V[]){a[0], a[1], a[4], a[2], a[3]}));
}
static V L2963(V *a) {
return F_Chk_dP_dbind(F_Chk_dspan_dgrow(a[3]), mk_clo(L2964, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L2962(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2963, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V L2961(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm(5u), mk_clo(L2962, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L2960(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(F_U32_dsub(a[2], 1u)), mk_clo(L2961, 3, 2, (V[]){a[0], a[1]}));
}
static V L2959(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L2960, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dlt(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L2959, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dlt(V *a) { (void)a; return F_Chk_dP_dlt(a[0], a[1]); }
static V S2970(void) { static V c; return STRC(c, "a family name before <..> (a comparison here needs parens)"); }
static V F_Chk_dP_dlt_dadt(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dP_dif(F_Bool_dor(F_Chk_dTm_dis__var(a0), F_Chk_dTm_dis__ref(a0)), F_Chk_dP_dlt_dadt_dgo(a0, a1, a2, a3), F_Chk_dP_dfail(S2970()));
}
static V W_Chk_dP_dlt_dadt(V *a) { (void)a; return F_Chk_dP_dlt_dadt(a[0], a[1], a[2], a[3]); }
static V S2971(void) { static V c; return STRC(c, ","); }
static V S2974(void) { static V c; return STRC(c, ">"); }
static V L2976(V *a) {
return F_Chk_dP_dops(C4(14, a[2], a[3], a[1], IMM(0)), a[0]);
}
static V L2975(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dfill(a[3], C2(1, a[2], a[4]), a[1]), mk_clo(L2976, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V L2973(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dargs(S2974()), mk_clo(L2975, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L2972(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(F_Chk_dTm_dname(a[3])), mk_clo(L2973, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dlt_dadt_dgo(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2971()), mk_clo(L2972, 5, 4, (V[]){a3, a2, a1, a0}));
}
static V W_Chk_dP_dlt_dadt_dgo(V *a) { (void)a; return F_Chk_dP_dlt_dadt_dgo(a[0], a[1], a[2], a[3]); }
static V L2977(V *a) {
return F_Chk_dP_dpure(F_Chk_dfill_dgo(F_Chk_dTld_dadt__fill(F_Chk_dbook__tld(a[3], a[2]), F_List_dlength(a[1])), a[1], a[0]));
}
static V F_Chk_dP_dfill(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L2977, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dP_dfill(V *a) { (void)a; return F_Chk_dP_dfill(a[0], a[1], a[2]); }
static V F_Chk_dTld_dadt__fill(V a0, V a1) {
top:;
V s2978 = a0;
if (TAG(s2978) == 1 && TAG(FLD(s2978, 0)) == 1) {
return F_Bool_dpick(F_Nat_dis__eq(F_Nat_dadd(a1, FLD(FLD(s2978, 0), 1)), FLD(FLD(s2978, 0), 0)), C1(1, FLD(FLD(s2978, 0), 1)), IMM(0));
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dadt__fill(V *a) { (void)a; return F_Chk_dTld_dadt__fill(a[0], a[1]); }
static V F_Chk_dfill_dgo(V a0, V a1, V a2) {
top:;
V s2979 = a0;
if ((s2979) == IMM(0)) {
return a1;
} else if (TAG(s2979) == 1) {
return F_List_dappend(F_Chk_dList_drepeat__tm(C2(9, IMM(1), a2), FLD(s2979, 0)), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dfill_dgo(V *a) { (void)a; return F_Chk_dfill_dgo(a[0], a[1], a[2]); }
static V F_Chk_dList_drepeat__tm(V a0, V a1) {
top:;
V s2980 = a1;
if ((s2980) == 0) {
return IMM(0);
} else if (nat_ge(s2980, 1)) {
return C2(1, a0, F_Chk_dList_drepeat__tm(a0, nat_subk(s2980, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dList_drepeat__tm(V *a) { (void)a; return F_Chk_dList_drepeat__tm(a[0], a[1]); }
static V L2982(V *a) {
return F_Chk_dP_dif(a[1], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dargs_done(a[0]));
}
static V L2981(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(a[0]), mk_clo(L2982, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dargs(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2981, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dargs(V *a) { (void)a; return F_Chk_dP_dargs(a[0]); }
static V S2985(void) { static V c; return STRC(c, ","); }
static V L2987(V *a) {
return F_Chk_dP_dpure(C2(1, a[0], a[1]));
}
static V L2986(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dargs(a[1]), mk_clo(L2987, 2, 1, (V[]){a[0]}));
}
static V L2984(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S2985()), mk_clo(L2986, 3, 2, (V[]){a[0], a[1]}));
}
static V L2983(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2984, 3, 2, (V[]){a[1], a[0]}));
}
static V F_Chk_dP_dargs_done(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L2983, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dargs_done(V *a) { (void)a; return F_Chk_dP_dargs_done(a[0]); }
static V F_Chk_dTm_dis__ref(V a0) {
top:;
V s2988 = a0;
if (TAG(s2988) == 4) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__ref(V *a) { (void)a; return F_Chk_dTm_dis__ref(a[0]); }
static V L2989(V *a) {
return C1(1, C2(0, IMM(0), F_Chk_dPS_dset__cur(a[0], F_Chk_dCur_dstep(F_Chk_dPS_dcur(a[0])))));
}
static V F_Chk_dP_dbump(void) {
top:;
return mk_clo(L2989, 1, 0, 0);
}
static V W_Chk_dP_dbump(V *a) { (void)a; return F_Chk_dP_dbump(); }
static V S2992(void) { static V c; return STRC(c, "]"); }
static V S2995(void) { static V c; return STRC(c, "U32"); }
static V S2999(void) { static V c; return STRC(c, "<-"); }
static V S3001(void) { static V c; return STRC(c, "Array.get"); }
static V S3002(void) { static V c; return STRC(c, "U32"); }
static V L3000(V *a) {
return F_Chk_dP_dif(a[4], F_Chk_dP_dindex_dset(a[3], a[2], a[1], a[0]), F_Chk_dP_dops(C3(13, C3(13, C3(13, C3(4, S3001(), a[1], IMM(0)), C3(4, S3002(), a[1], IMM(0)), a[1]), a[3], a[1]), a[2], a[1]), a[0]));
}
static V L2998(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[4], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dtake(S2999())), mk_clo(L3000, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L2997(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dnl(), mk_clo(L2998, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L2996(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L2997, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V L2994(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dns(a[2], C3(4, S2995(), a[3], IMM(0))), mk_clo(L2996, 4, 3, (V[]){a[0], a[3], a[1]}));
}
static V L2993(V *a) {
return F_Chk_dP_dbind(F_Chk_dspan_dgrow(a[2]), mk_clo(L2994, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L2991(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S2992()), mk_clo(L2993, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L2990(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L2991, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dindex(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L2990, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dindex(V *a) { (void)a; return F_Chk_dP_dindex(a[0], a[1]); }
static V S3004(void) { static V c; return STRC(c, "Array.set"); }
static V S3005(void) { static V c; return STRC(c, "U32"); }
static V L3003(V *a) {
return F_Chk_dP_dops(F_Chk_dapps(C3(4, S3004(), a[3], IMM(0)), C2(1, C3(4, S3005(), a[3], IMM(0)), C2(1, a[2], C2(1, a[1], C2(1, a[4], IMM(0))))), a[3]), a[0]);
}
static V F_Chk_dP_dindex_dset(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm(2u), mk_clo(L3003, 5, 4, (V[]){a3, a1, a0, a2}));
}
static V W_Chk_dP_dindex_dset(V *a) { (void)a; return F_Chk_dP_dindex_dset(a[0], a[1], a[2], a[3]); }
static V F_Chk_dapps(V a0, V a1, V a2) {
top:;
V s3006 = a1;
if ((s3006) == IMM(0)) {
return a0;
} else if (TAG(s3006) == 1) {
{ V t0 = C3(13, a0, FLD(s3006, 0), a2); V t1 = FLD(s3006, 1); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dapps(V *a) { (void)a; return F_Chk_dapps(a[0], a[1], a[2]); }
static V L3007(V *a) {
return C1(1, C2(0, F_Chk_dCur_dnl(F_Chk_dPS_dcur(a[0])), a[0]));
}
static V F_Chk_dP_dnl(void) {
top:;
return mk_clo(L3007, 1, 0, 0);
}
static V W_Chk_dP_dnl(V *a) { (void)a; return F_Chk_dP_dnl(); }
static V F_Chk_dCur_dnl(V a0) {
top:;
V v3008 = a0;
return FLD(v3008, 3);
}
static V W_Chk_dCur_dnl(V *a) { (void)a; return F_Chk_dCur_dnl(a[0]); }
static V L3010(V *a) {
return F_Chk_dP_dpure(CN(6, 6, (V[]){a[4], a[3], a[2], C3(25, IMM(0), a[3], a[5]), a[1], a[0]}));
}
static V F_Chk_dP_dns(V a0, V a1) {
top:;
V s3009 = a0;
if (TAG(s3009) == 6) {
return F_Chk_dP_dbind(F_Chk_dP_dns(F_Chk_dsyn__body(FLD(s3009, 3)), a1), mk_clo(L3010, 6, 5, (V[]){FLD(s3009, 5), FLD(s3009, 4), FLD(s3009, 2), FLD(s3009, 1), FLD(s3009, 0)}));
} else {
return F_Chk_dP_dns_dapp(F_Chk_dterm__unapply(s3009), a1);
}
}
static V W_Chk_dP_dns(V *a) { (void)a; return F_Chk_dP_dns(a[0], a[1]); }
static V S3013(void) { static V c; return STRC(c, "Bool.and"); }
static V S3014(void) { static V c; return STRC(c, "Bool.or"); }
static V S3015(void) { static V c; return STRC(c, "String.append"); }
static V F_Chk_dP_dns_dapp(V a0, V a1) {
top:;
V v3011 = a0;
V s3012 = FLD(v3011, 0);
if (TAG(s3012) == 4) {
return F_Chk_dP_dns_dref(FLD(s3012, 0), FLD(s3012, 1), FLD(s3012, 2), FLD(v3011, 1), a1, F_Nat_dis__eq(F_Chk_dStr_dlast__dot(FLD(s3012, 0)), 0u), F_Chk_dStr_dhas(C2(1, S3013(), C2(1, S3014(), C2(1, S3015(), IMM(0)))), FLD(s3012, 0)));
} else {
return F_Chk_dP_dpure(F_Chk_dapps(s3012, FLD(v3011, 1), IMM(0)));
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
V s3016 = a0;
if ((s3016) == IMM(0)) {
return a2;
} else if (TAG(s3016) == 1) {
{ V t0 = FLD(s3016, 1); V t1 = nat_addk(a1, 1); V t2 = F_Bool_dpick(F_U32_dis__eq(FLD(s3016, 0), 46u), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dlast__dot_dgo(V *a) { (void)a; return F_Chk_dStr_dlast__dot_dgo(a[0], a[1], a[2]); }
static V L3019(V *a) {
return F_Chk_dP_dpure(F_Chk_dapps_dspan(C3(4, a[3], a[2], a[1]), a[4], a[0]));
}
static V F_Chk_dP_dns_dref(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s3017 = a5;
V s3018 = a6;
if ((s3017) == IMM(1)) {
return F_Chk_dP_dns_dop(a0, a1, a2, a3, a4, F_Chk_dterm__head(a4));
} else if ((s3017) == IMM(0) && (s3018) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dns_dargs(a3, a4), mk_clo(L3019, 5, 4, (V[]){a3, a2, a1, a0}));
} else if ((s3017) == IMM(0) && (s3018) == IMM(0)) {
return F_Chk_dP_dpure(F_Chk_dapps(C3(4, a0, a1, a2), a3, IMM(0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dns_dref(V *a) { (void)a; return F_Chk_dP_dns_dref(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Chk_dapps_dspan(V a0, V a1, V a2) {
top:;
return F_Chk_dapps(a0, a1, IMM(0));
}
static V W_Chk_dapps_dspan(V *a) { (void)a; return F_Chk_dapps_dspan(a[0], a[1], a[2]); }
static V L3022(V *a) {
return F_Chk_dP_dpure(C2(1, a[0], a[1]));
}
static V L3021(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dns_dargs(a[1], a[0]), mk_clo(L3022, 2, 1, (V[]){a[2]}));
}
static V F_Chk_dP_dns_dargs(V a0, V a1) {
top:;
V s3020 = a0;
if ((s3020) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s3020) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dns(FLD(s3020, 0), a1), mk_clo(L3021, 3, 2, (V[]){a1, FLD(s3020, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dns_dargs(V *a) { (void)a; return F_Chk_dP_dns_dargs(a[0], a[1]); }
static V S3024(void) { static V c; return STRC(c, ""); }
static V S3025(void) { static V c; return STRC(c, "a type name after : (the operators' namespace)"); }
static V F_Chk_dP_dns_dop(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s3023 = a5;
if (TAG(s3023) == 0) {
return F_Chk_dP_dns_dop_dgo(F_String_dappend(a0, S3024()), FLD(s3023, 0), a1, a2, a3, a4);
} else if (TAG(s3023) == 3) {
return F_Chk_dP_dns_dop_dgo(a0, FLD(s3023, 0), a1, a2, a3, a4);
} else if (TAG(s3023) == 4) {
return F_Chk_dP_dns_dop_dgo(a0, FLD(s3023, 0), a1, a2, a3, a4);
} else if (TAG(s3023) == 14) {
return F_Chk_dP_dns_dop_dgo(a0, FLD(s3023, 0), a1, a2, a3, a4);
} else {
return F_Chk_dP_dthrow(F_Chk_derr0(S3025(), IMM(0), F_Chk_dTm_dspan(s3023)));
}
}
static V W_Chk_dP_dns_dop(V *a) { (void)a; return F_Chk_dP_dns_dop(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L3027(V *a) {
return F_Chk_dP_dpure(F_Chk_dapps_dspan(C3(4, a[3], a[2], a[1]), a[4], a[0]));
}
static V L3026(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dns_dargs(a[3], a[2]), mk_clo(L3027, 5, 4, (V[]){a[3], a[0], a[1], a[4]}));
}
static V F_Chk_dP_dns_dop_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dreso(F_String_dappend(a1, a0)), mk_clo(L3026, 5, 4, (V[]){a3, a2, a5, a4}));
}
static V W_Chk_dP_dns_dop_dgo(V *a) { (void)a; return F_Chk_dP_dns_dop_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L3029(V *a) {
return F_Chk_dP_deat_dif(a[0], a[1]);
}
static V L3028(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(a[0]), mk_clo(L3029, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_deat(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3028, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_deat(V *a) { (void)a; return F_Chk_dP_deat(a[0]); }
static V S3031(void) { static V c; return STRC(c, "'"); }
static V S3032(void) { static V c; return STRC(c, "'"); }
static V F_Chk_dP_deat_dif(V a0, V a1) {
top:;
V s3030 = a1;
if ((s3030) == IMM(1)) {
return F_Chk_dP_dpure(IMM(0));
} else if ((s3030) == IMM(0)) {
return F_Chk_dP_dfail(F_String_dappend(S3031(), F_String_dappend(a0, S3032())));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_deat_dif(V *a) { (void)a; return F_Chk_dP_deat_dif(a[0], a[1]); }
static V S3034(void) { static V c; return STRC(c, "!"); }
static V L3035(V *a) {
return F_Chk_dP_dif(a[2], F_Chk_dP_dcall_dbang(a[1], a[0]), F_Chk_dP_dcall_dargs(a[1], a[0]));
}
static V L3033(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S3034()), mk_clo(L3035, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dcall(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dcall_dhead(a0), mk_clo(L3033, 2, 1, (V[]){a1}));
}
static V W_Chk_dP_dcall(V *a) { (void)a; return F_Chk_dP_dcall(a[0], a[1]); }
static V S3038(void) { static V c; return STRC(c, ""); }
static V S3042(void) { static V c; return STRC(c, ")"); }
static V L3044(V *a) {
return F_Chk_dP_dops(F_Chk_dapps(a[3], F_List_dappend(a[2], a[1]), a[4]), a[0]);
}
static V L3043(V *a) {
return F_Chk_dP_dbind(F_Chk_dspan_dgrow(a[2]), mk_clo(L3044, 5, 4, (V[]){a[0], a[3], a[1], a[2]}));
}
static V L3041(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dargs(S3042()), mk_clo(L3043, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L3040(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcall_dtmpl(a[2], a[1], IMM(0)), mk_clo(L3041, 3, 2, (V[]){a[0], a[2]}));
}
static V L3039(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3040, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L3037(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_dTld_dx(F_Chk_dbook__tld(a[2], F_Bool_dpick(F_Chk_dTm_dis__ref(a[1]), F_Chk_dTm_dname(a[1]), S3038())))), mk_clo(L3039, 3, 2, (V[]){a[0], a[1]}));
}
static V L3036(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3037, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dcall_dargs(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3036, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dcall_dargs(V *a) { (void)a; return F_Chk_dP_dcall_dargs(a[0], a[1]); }
static V S3045(void) { static V c; return STRC(c, "~"); }
static V L3046(V *a) {
return F_Chk_dP_dif(F_Bool_dand(F_Nat_dis__gt(a[2], 0u), a[3]), F_Chk_dP_dcall_dtmpl_done(a[1], a[2], a[0]), F_Chk_dP_dpure(a[0]));
}
static V F_Chk_dP_dcall_dtmpl(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dat(S3045()), mk_clo(L3046, 4, 3, (V[]){a2, a0, a1}));
}
static V W_Chk_dP_dcall_dtmpl(V *a) { (void)a; return F_Chk_dP_dcall_dtmpl(a[0], a[1], a[2]); }
static V S3047(void) { static V c; return STRC(c, "a term ("); }
static V S3048(void) { static V c; return STRC(c, " takes "); }
static V S3049(void) { static V c; return STRC(c, " ~)"); }
static V F_Chk_dP_dcall_dtmpl_done(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dif(F_Nat_dis__eq(F_List_dlength(a2), a1), F_Chk_dP_dfail(F_String_dappend(S3047(), F_String_dappend(F_Chk_dTm_dname(a0), F_String_dappend(S3048(), F_String_dappend(F_Nat_dshow(a1), S3049()))))), F_Chk_dP_dcall_dtmpl_dgo(a0, a1, a2));
}
static V W_Chk_dP_dcall_dtmpl_done(V *a) { (void)a; return F_Chk_dP_dcall_dtmpl_done(a[0], a[1], a[2]); }
static V S3053(void) { static V c; return STRC(c, ","); }
static V L3055(V *a) {
return F_Chk_dP_dcall_dtmpl(a[3], a[2], F_List_dappend(a[1], C2(1, a[0], IMM(0))));
}
static V L3054(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3055, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3052(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3053()), mk_clo(L3054, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3051(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3052, 5, 4, (V[]){a[3], a[0], a[1], a[2]}));
}
static V L3050(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3051, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dcall_dtmpl_dgo(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3050, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dP_dcall_dtmpl_dgo(V *a) { (void)a; return F_Chk_dP_dcall_dtmpl_dgo(a[0], a[1], a[2]); }
static V S3056(void) { static V c; return STRC(c, "a named def before ! (only f!(..) offloads)"); }
static V F_Chk_dP_dcall_dbang(V a0, V a1) {
top:;
return F_Chk_dP_dif(F_Chk_dTm_dis__ref(a0), F_Chk_dP_dcall_dbang_dgo(a0, a1), F_Chk_dP_dfail(S3056()));
}
static V W_Chk_dP_dcall_dbang(V *a) { (void)a; return F_Chk_dP_dcall_dbang(a[0], a[1]); }
static V L3057(V *a) {
return F_Chk_dP_dops(F_Chk_dTm_dbang(a[1]), a[0]);
}
static V F_Chk_dP_dcall_dbang_dgo(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3057, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dcall_dbang_dgo(V *a) { (void)a; return F_Chk_dP_dcall_dbang_dgo(a[0], a[1]); }
static V F_Chk_dTm_dbang(V a0) {
top:;
V s3058 = a0;
if (TAG(s3058) == 4) {
return C3(4, FLD(s3058, 0), FLD(s3058, 1), IMM(1));
} else {
return s3058;
}
}
static V W_Chk_dTm_dbang(V *a) { (void)a; return F_Chk_dTm_dbang(a[0]); }
static V F_Chk_dP_dcall_dhead(V a0) {
top:;
V s3059 = a0;
if (TAG(s3059) == 0) {
return F_Chk_dP_dcall_dhead_dvar(FLD(s3059, 0), FLD(s3059, 2), C3(0, FLD(s3059, 0), FLD(s3059, 1), FLD(s3059, 2)));
} else if (TAG(s3059) == 3) {
return F_Chk_dP_dcall_dhead_dvar(FLD(s3059, 0), FLD(s3059, 2), C4(3, FLD(s3059, 0), FLD(s3059, 1), FLD(s3059, 2), FLD(s3059, 3)));
} else {
return F_Chk_dP_dpure(s3059);
}
}
static V W_Chk_dP_dcall_dhead(V *a) { (void)a; return F_Chk_dP_dcall_dhead(a[0]); }
static V L3061(V *a) {
return F_Chk_dP_dpure(F_Bool_dpick(F_Maybe_dis__some(a[2]), a[1], C3(4, a[3], a[0], IMM(0))));
}
static V L3060(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(a[2]), mk_clo(L3061, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V F_Chk_dP_dcall_dhead_dvar(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dlookup(a0), mk_clo(L3060, 4, 3, (V[]){a1, a2, a0}));
}
static V W_Chk_dP_dcall_dhead_dvar(V *a) { (void)a; return F_Chk_dP_dcall_dhead_dvar(a[0], a[1], a[2]); }
static V L3062(V *a) {
return C1(1, C2(0, F_Chk_dSB_dfind(F_Chk_dPS_dstk(a[1]), a[0]), a[1]));
}
static V F_Chk_dP_dlookup(V a0) {
top:;
return mk_clo(L3062, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dlookup(V *a) { (void)a; return F_Chk_dP_dlookup(a[0]); }
static V F_Chk_dPS_dstk(V a0) {
top:;
V v3063 = a0;
return FLD(v3063, 1);
}
static V W_Chk_dPS_dstk(V *a) { (void)a; return F_Chk_dPS_dstk(a[0]); }
static V F_Chk_dSB_dfind(V a0, V a1) {
top:;
V s3064 = a0;
if ((s3064) == IMM(0)) {
return IMM(0);
} else if (TAG(s3064) == 1) {
return F_Chk_dSB_dfind_dif(FLD(s3064, 1), a1, FLD(FLD(s3064, 0), 1), F_String_deq(a1, FLD(FLD(s3064, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dSB_dfind(V *a) { (void)a; return F_Chk_dSB_dfind(a[0], a[1]); }
static V F_Chk_dSB_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s3065 = a3;
if ((s3065) == IMM(1)) {
return C1(1, a2);
} else if ((s3065) == IMM(0)) {
return F_Chk_dSB_dfind(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dSB_dfind_dif(V *a) { (void)a; return F_Chk_dSB_dfind_dif(a[0], a[1], a[2], a[3]); }
static V L3066(V *a) {
return C1(1, C2(0, F_Chk_dCur_dprev(F_Chk_dPS_dcur(a[0])), a[0]));
}
static V F_Chk_dP_dprev(void) {
top:;
return mk_clo(L3066, 1, 0, 0);
}
static V W_Chk_dP_dprev(V *a) { (void)a; return F_Chk_dP_dprev(); }
static V F_Chk_dCur_dprev(V a0) {
top:;
V v3067 = a0;
return FLD(v3067, 4);
}
static V W_Chk_dCur_dprev(V *a) { (void)a; return F_Chk_dCur_dprev(a[0]); }
static V L3068(V *a) {
return C1(1, C2(0, F_Chk_dCur_drest(F_Chk_dPS_dcur(a[0])), a[0]));
}
static V F_Chk_dP_dpeek__rest(void) {
top:;
return mk_clo(L3068, 1, 0, 0);
}
static V W_Chk_dP_dpeek__rest(V *a) { (void)a; return F_Chk_dP_dpeek__rest(); }
static V L3069(V *a) {
return F_Chk_dP_dbase_dgo(a[1], a[0], F_Bool_dpick(F_Chk_dis__head(a[1]), 0u, F_Bool_dpick(F_Chk_dis__digit(a[1]), 1u, 2u)));
}
static V F_Chk_dP_dbase(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3069, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbase(V *a) { (void)a; return F_Chk_dP_dbase(a[0]); }
static V L3071(V *a) {
return F_Chk_dP_dbase_dword(a[1], a[0]);
}
static V F_Chk_dP_dbase_dgo(V a0, V a1, V a2) {
top:;
V s3070 = a2;
if ((s3070) == 0) {
return F_Chk_dP_dbind(F_Chk_dP_dlexeme(), mk_clo(L3071, 2, 1, (V[]){a1}));
} else if ((s3070) == 1) {
return F_Chk_dP_dnum();
} else if (nat_ge(s3070, 2)) {
return F_Chk_dP_dbase_dsym(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dbase_dgo(V *a) { (void)a; return F_Chk_dP_dbase_dgo(a[0], a[1], a[2]); }
static V S3072(void) { static V c; return STRC(c, "@"); }
static V S3073(void) { static V c; return STRC(c, "&"); }
static V S3074(void) { static V c; return STRC(c, "+"); }
static V S3075(void) { static V c; return STRC(c, "\134"); }
static V S3076(void) { static V c; return STRC(c, "%"); }
static V S3077(void) { static V c; return STRC(c, "{"); }
static V S3078(void) { static V c; return STRC(c, "("); }
static V S3079(void) { static V c; return STRC(c, "["); }
static V S3080(void) { static V c; return STRC(c, "'"); }
static V S3081(void) { static V c; return STRC(c, "\042"); }
static V S3082(void) { static V c; return STRC(c, "\077"); }
static V F_Chk_dP_dbase_dsym(V a0, V a1) {
top:;
return F_Chk_dP_dbase_dsym_dgo(a0, a1, F_Chk_dStr_dindex(C2(1, S3072(), C2(1, S3073(), C2(1, S3074(), C2(1, S3075(), C2(1, S3076(), C2(1, S3077(), C2(1, S3078(), C2(1, S3079(), C2(1, S3080(), C2(1, S3081(), C2(1, S3082(), IMM(0)))))))))))), F_Chk_dStr_dchr(a0), 0u));
}
static V W_Chk_dP_dbase_dsym(V *a) { (void)a; return F_Chk_dP_dbase_dsym(a[0], a[1]); }
static V L3084(V *a) {
return F_Chk_dP_damp(F_Chk_dStr_dsecond(a[1]), a[0]);
}
static V L3085(V *a) {
return F_Chk_dP_dtup(a[0]);
}
static V S3086(void) { static V c; return STRC(c, "a term"); }
static V F_Chk_dP_dbase_dsym_dgo(V a0, V a1, V a2) {
top:;
V s3083 = a2;
if (TAG(s3083) == 1 && (FLD(s3083, 0)) == 0) {
return F_Chk_dP_dall(IMM(0));
} else if (TAG(s3083) == 1 && (FLD(s3083, 0)) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek__rest(), mk_clo(L3084, 2, 1, (V[]){a1}));
} else if (TAG(s3083) == 1 && (FLD(s3083, 0)) == 2) {
return F_Chk_dP_dplus(a1);
} else if (TAG(s3083) == 1 && (FLD(s3083, 0)) == 3) {
return F_Chk_dP_darms(a1);
} else if (TAG(s3083) == 1 && (FLD(s3083, 0)) == 4) {
return F_Chk_dP_drwt(a1);
} else if (TAG(s3083) == 1 && (FLD(s3083, 0)) == 5) {
return F_Chk_dP_dbrace(a1);
} else if (TAG(s3083) == 1 && (FLD(s3083, 0)) == 6) {
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3085, 2, 1, (V[]){a1}));
} else if (TAG(s3083) == 1 && (FLD(s3083, 0)) == 7) {
return F_Chk_dP_dbrack(a1);
} else if (TAG(s3083) == 1 && (FLD(s3083, 0)) == 8) {
return F_Chk_dP_dchr__lit(a1);
} else if (TAG(s3083) == 1 && (FLD(s3083, 0)) == 9) {
return F_Chk_dP_dstr__lit(a1);
} else if (TAG(s3083) == 1 && (FLD(s3083, 0)) == 10) {
return F_Chk_dP_dhole(a1);
} else {
return F_Chk_dP_dfail(S3086());
}
}
static V W_Chk_dP_dbase_dsym_dgo(V *a) { (void)a; return F_Chk_dP_dbase_dsym_dgo(a[0], a[1], a[2]); }
static V S3089(void) { static V c; return STRC(c, "TODO"); }
static V L3091(V *a) {
return F_Chk_dP_dpure(C2(22, a[0], a[1]));
}
static V L3090(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3091, 2, 1, (V[]){a[0]}));
}
static V L3088(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_String_deq(a[1], S3089()), F_Chk_dP_dcount__hole(), F_Chk_dP_dpure(IMM(0))), mk_clo(L3090, 3, 2, (V[]){a[1], a[0]}));
}
static V L3087(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3088, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dhole(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3087, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dhole(V *a) { (void)a; return F_Chk_dP_dhole(a[0]); }
static V L3092(V *a) {
return F_Chk_dP_dset__book(F_Chk_dbook__hole(a[0]));
}
static V F_Chk_dP_dcount__hole(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3092, 1, 0, 0));
}
static V W_Chk_dP_dcount__hole(V *a) { (void)a; return F_Chk_dP_dcount__hole(); }
static V F_Chk_dbook__hole(V a0) {
top:;
V v3093 = a0;
return CN(0, 7, (V[]){FLD(v3093, 0), FLD(v3093, 1), FLD(v3093, 2), nat_addk(FLD(v3093, 3), 1), FLD(v3093, 4), FLD(v3093, 5), FLD(v3093, 6)});
}
static V W_Chk_dbook__hole(V *a) { (void)a; return F_Chk_dbook__hole(a[0]); }
static V L3094(V *a) {
return F_Chk_dP_dname_dcheck(a[0]);
}
static V F_Chk_dP_dname(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dlexeme(), mk_clo(L3094, 1, 0, 0));
}
static V W_Chk_dP_dname(V *a) { (void)a; return F_Chk_dP_dname(); }
static V F_Chk_dP_dname_dcheck(V a0) {
top:;
return F_Chk_dP_dname_dcheck_dc(a0, F_Chk_dStr_dhas(F_Chk_dKEYWORDS(), a0));
}
static V W_Chk_dP_dname_dcheck(V *a) { (void)a; return F_Chk_dP_dname_dcheck(a[0]); }
static V S3095(void) { static V c; return STRC(c, "def"); }
static V S3096(void) { static V c; return STRC(c, "type"); }
static V S3097(void) { static V c; return STRC(c, "law"); }
static V S3098(void) { static V c; return STRC(c, "match"); }
static V S3099(void) { static V c; return STRC(c, "case"); }
static V S3100(void) { static V c; return STRC(c, "do"); }
static V S3101(void) { static V c; return STRC(c, "return"); }
static V S3102(void) { static V c; return STRC(c, "for"); }
static V S3103(void) { static V c; return STRC(c, "exs"); }
static V S3104(void) { static V c; return STRC(c, "where"); }
static V S3105(void) { static V c; return STRC(c, "is"); }
static V S3106(void) { static V c; return STRC(c, "import"); }
static V S3107(void) { static V c; return STRC(c, "Type"); }
static V S3108(void) { static V c; return STRC(c, "Data"); }
static V S3109(void) { static V c; return STRC(c, "Kind"); }
static V S3110(void) { static V c; return STRC(c, "Quant"); }
static V F_Chk_dKEYWORDS(void) {
top:;
return C2(1, S3095(), C2(1, S3096(), C2(1, S3097(), C2(1, S3098(), C2(1, S3099(), C2(1, S3100(), C2(1, S3101(), C2(1, S3102(), C2(1, S3103(), C2(1, S3104(), C2(1, S3105(), C2(1, S3106(), C2(1, S3107(), C2(1, S3108(), C2(1, S3109(), C2(1, S3110(), IMM(0)))))))))))))))));
}
static V W_Chk_dKEYWORDS(V *a) { (void)a; return F_Chk_dKEYWORDS(); }
static V S3112(void) { static V c; return STRC(c, "a name (got the keyword '"); }
static V S3113(void) { static V c; return STRC(c, "')"); }
static V F_Chk_dP_dname_dcheck_dc(V a0, V a1) {
top:;
V s3111 = a1;
if ((s3111) == IMM(1)) {
return F_Chk_dP_dfail(F_String_dappend(S3112(), F_String_dappend(a0, S3113())));
} else if ((s3111) == IMM(0)) {
return F_Chk_dP_dpure(a0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dname_dcheck_dc(V *a) { (void)a; return F_Chk_dP_dname_dcheck_dc(a[0], a[1]); }
static V L3115(V *a) {
return F_Chk_dP_dlexeme_dif(a[0], F_Chk_dis__head(F_Chk_dCur_dpeek(a[0])));
}
static V L3114(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcur(), mk_clo(L3115, 1, 0, 0));
}
static V F_Chk_dP_dlexeme(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3114, 1, 0, 0));
}
static V W_Chk_dP_dlexeme(V *a) { (void)a; return F_Chk_dP_dlexeme(); }
static V S3117(void) { static V c; return STRC(c, "a name"); }
static V F_Chk_dP_dlexeme_dif(V a0, V a1) {
top:;
V s3116 = a1;
if ((s3116) == IMM(1)) {
return F_Chk_dP_dlexeme_dgo(a0);
} else if ((s3116) == IMM(0)) {
return F_Chk_dP_dfail(S3117());
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dlexeme_dif(V *a) { (void)a; return F_Chk_dP_dlexeme_dif(a[0], a[1]); }
static V S3118(void) { static V c; return STRC(c, ""); }
static V F_Chk_dP_dlexeme_dgo(V a0) {
top:;
return F_Chk_dP_dlexeme_dfin(F_Chk_dCur_dname(a0, S3118()));
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
V s3119 = a3;
if ((s3119) == IMM(1)) {
return F_Chk_dCur_dname(F_Chk_dCur_dstep(a1), C2(1, a0, a2));
} else if ((s3119) == IMM(0)) {
return C2(0, F_String_dreverse(a2), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dCur_dname_dc(V *a) { (void)a; return F_Chk_dCur_dname_dc(a[0], a[1], a[2], a[3]); }
static V L3121(V *a) {
return F_Chk_dP_dlexeme_ddot(a[0]);
}
static V F_Chk_dP_dlexeme_dfin(V a0) {
top:;
V v3120 = a0;
return F_Chk_dP_dbind(F_Chk_dP_dset__cur(FLD(v3120, 1)), mk_clo(L3121, 2, 1, (V[]){FLD(v3120, 0)}));
}
static V W_Chk_dP_dlexeme_dfin(V *a) { (void)a; return F_Chk_dP_dlexeme_dfin(a[0]); }
static V S3122(void) { static V c; return STRC(c, "."); }
static V F_Chk_dP_dlexeme_ddot(V a0) {
top:;
return F_Chk_dP_dlexeme_ddot_dc(a0, F_String_dends__with(a0, S3122()));
}
static V W_Chk_dP_dlexeme_ddot(V *a) { (void)a; return F_Chk_dP_dlexeme_ddot(a[0]); }
static V S3124(void) { static V c; return STRC(c, "a name (a name cannot end in '.')"); }
static V F_Chk_dP_dlexeme_ddot_dc(V a0, V a1) {
top:;
V s3123 = a1;
if ((s3123) == IMM(1)) {
return F_Chk_dP_dfail(S3124());
} else if ((s3123) == IMM(0)) {
return F_Chk_dP_dpure(a0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dlexeme_ddot_dc(V *a) { (void)a; return F_Chk_dP_dlexeme_ddot_dc(a[0], a[1]); }
static V L3125(V *a) {
return C1(1, C2(0, IMM(0), F_Chk_dPS_dset__cur(a[1], a[0])));
}
static V F_Chk_dP_dset__cur(V a0) {
top:;
return mk_clo(L3125, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dset__cur(V *a) { (void)a; return F_Chk_dP_dset__cur(a[0]); }
static V L3126(V *a) {
return C1(1, C2(0, F_Chk_dPS_dcur(a[0]), a[0]));
}
static V F_Chk_dP_dcur(void) {
top:;
return mk_clo(L3126, 1, 0, 0);
}
static V W_Chk_dP_dcur(V *a) { (void)a; return F_Chk_dP_dcur(); }
static V L3129(V *a) {
return F_Chk_dP_dpure(F_Chk_dlit__of(a[0], a[1]));
}
static V L3128(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[0]), mk_clo(L3129, 2, 1, (V[]){a[1]}));
}
static V L3127(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstr_dgo(IMM(0)), mk_clo(L3128, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dstr__lit(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3127, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dstr__lit(V *a) { (void)a; return F_Chk_dP_dstr__lit(a[0]); }
static V F_Chk_dlit__of(V a0, V a1) {
top:;
return F_Bool_dpick(F_Chk_dcodes_dplain(a0), C2(16, C1(1, F_Chk_dStr_dfrom__codes(a0)), a1), F_Chk_dlit__chain(a0, a1));
}
static V W_Chk_dlit__of(V *a) { (void)a; return F_Chk_dlit__of(a[0], a[1]); }
static V F_Chk_dStr_dfrom__codes(V a0) {
top:;
V s3130 = a0;
if ((s3130) == IMM(0)) {
return IMM(0);
} else if (TAG(s3130) == 1) {
return C2(1, FLD(s3130, 0), F_Chk_dStr_dfrom__codes(FLD(s3130, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dfrom__codes(V *a) { (void)a; return F_Chk_dStr_dfrom__codes(a[0]); }
static V F_Chk_dcodes_dplain(V a0) {
top:;
V s3131 = a0;
if ((s3131) == IMM(0)) {
return IMM(1);
} else if (TAG(s3131) == 1) {
return F_Bool_dand(F_Bool_dand(F_U32_dis__le(FLD(s3131, 0), 1114111u), F_Bool_dor(F_U32_dis__lt(FLD(s3131, 0), 55296u), F_U32_dis__gt(FLD(s3131, 0), 57343u))), F_Chk_dcodes_dplain(FLD(s3131, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dcodes_dplain(V *a) { (void)a; return F_Chk_dcodes_dplain(a[0]); }
static V S3132(void) { static V c; return STRC(c, "\042"); }
static V S3135(void) { static V c; return STRC(c, "a closing \042"); }
static V L3134(V *a) {
return F_Chk_dP_dif(a[1], F_Chk_dP_dpure(F_List_dreverse(a[0])), F_Chk_dP_dif(F_U32_dis__zero(a[2]), F_Chk_dP_dfail(S3135()), F_Chk_dP_dstr_dmore(a[0])));
}
static V L3133(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3134, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dstr_dgo(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3132()), mk_clo(L3133, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dstr_dgo(V *a) { (void)a; return F_Chk_dP_dstr_dgo(a[0]); }
static V L3136(V *a) {
return F_Chk_dP_dstr_dgo(C2(1, a[1], a[0]));
}
static V F_Chk_dP_dstr_dmore(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dchar(), mk_clo(L3136, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dstr_dmore(V *a) { (void)a; return F_Chk_dP_dstr_dmore(a[0]); }
static V S3137(void) { static V c; return STRC(c, "\134"); }
static V L3138(V *a) {
return F_Chk_dP_dif(a[0], F_Chk_dP_descape(), F_Chk_dP_dchar_dplain());
}
static V F_Chk_dP_dchar(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3137()), mk_clo(L3138, 1, 0, 0));
}
static V W_Chk_dP_dchar(V *a) { (void)a; return F_Chk_dP_dchar(); }
static V S3140(void) { static V c; return STRC(c, "a character"); }
static V L3139(V *a) {
return F_Chk_dP_dif(F_U32_dis__zero(a[0]), F_Chk_dP_dfail(S3140()), F_Chk_dP_dchar_dtake(a[0]));
}
static V F_Chk_dP_dchar_dplain(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3139, 1, 0, 0));
}
static V W_Chk_dP_dchar_dplain(V *a) { (void)a; return F_Chk_dP_dchar_dplain(); }
static V L3141(V *a) {
return F_Chk_dP_dpure(a[0]);
}
static V F_Chk_dP_dchar_dtake(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3141, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dchar_dtake(V *a) { (void)a; return F_Chk_dP_dchar_dtake(a[0]); }
static V L3142(V *a) {
return C1(1, C2(0, F_Chk_dCur_dpeek(F_Chk_dPS_dcur(a[0])), a[0]));
}
static V F_Chk_dP_dpeek(void) {
top:;
return mk_clo(L3142, 1, 0, 0);
}
static V W_Chk_dP_dpeek(V *a) { (void)a; return F_Chk_dP_dpeek(); }
static V L3143(V *a) {
return F_Chk_dP_descape_du(F_Chk_duesc(a[0]));
}
static V F_Chk_dP_descape(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpeek__rest(), mk_clo(L3143, 1, 0, 0));
}
static V W_Chk_dP_descape(V *a) { (void)a; return F_Chk_dP_descape(); }
static V F_Chk_duesc(V a0) {
top:;
V s3144 = a0;
if (TAG(s3144) == 1 && TAG(FLD(s3144, 1)) == 1 && (FLD(FLD(s3144, 1), 0)) == 123) {
return F_Chk_duesc_dif(FLD(FLD(s3144, 1), 1), F_Bool_dor(F_U32_dis__eq(FLD(s3144, 0), 117u), F_U32_dis__eq(FLD(s3144, 0), 85u)));
} else {
return IMM(0);
}
}
static V W_Chk_duesc(V *a) { (void)a; return F_Chk_duesc(a[0]); }
static V F_Chk_duesc_dif(V a0, V a1) {
top:;
V s3145 = a1;
if ((s3145) == IMM(1)) {
return F_Chk_duesc_dhex(a0, 0u, 0u);
} else if ((s3145) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duesc_dif(V *a) { (void)a; return F_Chk_duesc_dif(a[0], a[1]); }
static V F_Chk_duesc_dhex(V a0, V a1, V a2) {
top:;
V s3146 = a0;
if (TAG(s3146) == 1) {
return F_Chk_duesc_dhex_dif(FLD(s3146, 1), FLD(s3146, 0), a1, a2, F_Chk_dis__hex(FLD(s3146, 0)), F_U32_dis__eq(FLD(s3146, 0), 125u));
} else if ((s3146) == IMM(0)) {
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
V s3147 = a4;
V s3148 = a5;
if ((s3147) == IMM(1)) {
return F_Bool_dpick(F_Nat_dis__ge(a3, 8u), IMM(0), F_Chk_duesc_dhex(a0, F_U32_dadd(F_U32_dmul(a2, 16u), F_Chk_dhex__val(a1)), nat_addk(a3, 1)));
} else if ((s3147) == IMM(0) && (s3148) == IMM(1)) {
return F_Bool_dpick(F_Nat_dis__eq(a3, 0u), IMM(0), C1(1, C2(0, a2, F_Nat_dadd(a3, 3u))));
} else if ((s3147) == IMM(0) && (s3148) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_duesc_dhex_dif(V *a) { (void)a; return F_Chk_duesc_dhex_dif(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_dhex__val(V a0) {
top:;
return F_Bool_dpick(F_Chk_dis__digit(a0), F_U32_dsub(a0, 48u), F_Bool_dpick(F_U32_dis__ge(a0, 97u), F_U32_dsub(a0, 87u), F_U32_dsub(a0, 55u)));
}
static V W_Chk_dhex__val(V *a) { (void)a; return F_Chk_dhex__val(a[0]); }
static V L3151(V *a) {
return F_Chk_dP_descape_dnamed(F_Chk_descape_dfind(F_Chk_dESCAPES(), a[0]));
}
static V L3150(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3151, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_descape_du(V a0) {
top:;
V s3149 = a0;
if (TAG(s3149) == 1) {
return F_Chk_dP_descape_du_dgo(FLD(s3149, 0));
} else if ((s3149) == IMM(0)) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3150, 1, 0, 0));
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
V s3152 = a0;
if (TAG(s3152) == 1 && TAG(FLD(s3152, 1)) == 1) {
return F_Chk_descape_dfind_dif(FLD(FLD(s3152, 1), 1), a1, FLD(FLD(s3152, 1), 0), F_U32_dis__eq(FLD(s3152, 0), a1));
} else {
return IMM(0);
}
}
static V W_Chk_descape_dfind(V *a) { (void)a; return F_Chk_descape_dfind(a[0], a[1]); }
static V F_Chk_descape_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s3153 = a3;
if ((s3153) == IMM(1)) {
return C1(1, a2);
} else if ((s3153) == IMM(0)) {
return F_Chk_descape_dfind(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_descape_dfind_dif(V *a) { (void)a; return F_Chk_descape_dfind_dif(a[0], a[1], a[2], a[3]); }
static V S3155(void) { static V c; return STRC(c, "an escape (\134n \134t \134r \1340 \134\134 \134' \134\042 \134u{1F600})"); }
static V F_Chk_dP_descape_dnamed(V a0) {
top:;
V s3154 = a0;
if (TAG(s3154) == 1) {
return F_Chk_dP_dpure(FLD(s3154, 0));
} else if ((s3154) == IMM(0)) {
return F_Chk_dP_dfail(S3155());
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_descape_dnamed(V *a) { (void)a; return F_Chk_dP_descape_dnamed(a[0]); }
static V L3158(V *a) {
return C1(1, C2(0, a[1], F_Chk_dPS_dset__cur(a[2], F_Chk_dCur_dsteps(F_Chk_dPS_dcur(a[2]), a[0]))));
}
static V F_Chk_dP_descape_du_dgo(V a0) {
top:;
V v3156 = a0;
V v3157 = FLD(v3156, 0);
return mk_clo(L3158, 3, 2, (V[]){FLD(v3156, 1), v3157});
}
static V W_Chk_dP_descape_du_dgo(V *a) { (void)a; return F_Chk_dP_descape_du_dgo(a[0]); }
static V S3161(void) { static V c; return STRC(c, "'"); }
static V L3162(V *a) {
return F_Chk_dP_dchr__lit_dfin(a[1], a[0], a[2]);
}
static V L3160(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3161()), mk_clo(L3162, 3, 2, (V[]){a[1], a[0]}));
}
static V L3159(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dchar(), mk_clo(L3160, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dchr__lit(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3159, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dchr__lit(V *a) { (void)a; return F_Chk_dP_dchr__lit(a[0]); }
static V S3165(void) { static V c; return STRC(c, "Chr"); }
static V L3164(V *a) {
return F_Chk_dP_dpure(C3(15, S3165(), C2(1, F_Chk_du32__to__term(a[0], a[1]), IMM(0)), a[1]));
}
static V S3166(void) { static V c; return STRC(c, "a closing '"); }
static V F_Chk_dP_dchr__lit_dfin(V a0, V a1, V a2) {
top:;
V s3163 = a2;
if ((s3163) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a0), mk_clo(L3164, 2, 1, (V[]){a1}));
} else if ((s3163) == IMM(0)) {
return F_Chk_dP_dfail(S3166());
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dchr__lit_dfin(V *a) { (void)a; return F_Chk_dP_dchr__lit_dfin(a[0], a[1], a[2]); }
static V S3169(void) { static V c; return STRC(c, "]"); }
static V L3170(V *a) {
return F_Chk_dP_dif(a[1], F_Chk_dP_dbrack_dlist(a[0], IMM(0)), F_Chk_dP_dbrack_dfirst(a[0]));
}
static V L3168(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S3169()), mk_clo(L3170, 2, 1, (V[]){a[0]}));
}
static V L3167(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3168, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dbrack(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3167, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbrack(V *a) { (void)a; return F_Chk_dP_dbrack(a[0]); }
static V S3173(void) { static V c; return STRC(c, ":"); }
static V L3174(V *a) {
return F_Chk_dP_dif(a[2], F_Chk_dP_dbrack_darr(a[1], a[0]), F_Chk_dP_dbrack_dlist(a[1], C2(1, a[0], IMM(0))));
}
static V L3172(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3173()), mk_clo(L3174, 3, 2, (V[]){a[0], a[1]}));
}
static V L3171(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3172, 3, 2, (V[]){a[1], a[0]}));
}
static V F_Chk_dP_dbrack_dfirst(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3171, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbrack_dfirst(V *a) { (void)a; return F_Chk_dP_dbrack_dfirst(a[0]); }
static V S3175(void) { static V c; return STRC(c, ","); }
static V S3177(void) { static V c; return STRC(c, "]"); }
static V L3179(V *a) {
return F_Chk_dP_dpure(F_Chk_dlist_dbuild(F_List_dappend(a[1], a[0]), a[2]));
}
static V L3178(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3179, 3, 2, (V[]){a[2], a[0]}));
}
static V L3176(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dargs(S3177()), mk_clo(L3178, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dbrack_dlist(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3175()), mk_clo(L3176, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dbrack_dlist(V *a) { (void)a; return F_Chk_dP_dbrack_dlist(a[0], a[1]); }
static V S3181(void) { static V c; return STRC(c, "Nil"); }
static V S3182(void) { static V c; return STRC(c, "Con"); }
static V F_Chk_dlist_dbuild(V a0, V a1) {
top:;
V s3180 = a0;
if ((s3180) == IMM(0)) {
return C3(15, S3181(), IMM(0), a1);
} else if (TAG(s3180) == 1) {
return C3(15, S3182(), C2(1, FLD(s3180, 0), C2(1, F_Chk_dlist_dbuild(FLD(s3180, 1), a1), IMM(0))), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dlist_dbuild(V *a) { (void)a; return F_Chk_dlist_dbuild(a[0], a[1]); }
static V S3185(void) { static V c; return STRC(c, "*"); }
static V S3187(void) { static V c; return STRC(c, "^"); }
static V S3190(void) { static V c; return STRC(c, "]"); }
static V S3195(void) { static V c; return STRC(c, "Array.new"); }
static V L3194(V *a) {
return F_Chk_dP_dpure(C3(13, C3(13, C3(13, C3(4, S3195(), a[2], IMM(0)), a[1], a[2]), a[3], a[2]), a[0], a[2]));
}
static V L3193(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbrack_ddepth(a[3], a[2]), mk_clo(L3194, 4, 3, (V[]){a[4], a[0], a[1]}));
}
static V L3192(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dns(a[3], a[2]), mk_clo(L3193, 5, 4, (V[]){a[2], a[4], a[0], a[1]}));
}
static V L3191(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[4]), mk_clo(L3192, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3189(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3190()), mk_clo(L3191, 6, 5, (V[]){a[4], a[0], a[1], a[2], a[3]}));
}
static V L3188(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3189, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3186(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[3], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_deat(S3187())), mk_clo(L3188, 5, 4, (V[]){a[3], a[0], a[1], a[2]}));
}
static V L3184(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3185()), mk_clo(L3186, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3183(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3184, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V F_Chk_dP_dbrack_darr(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm(12u), mk_clo(L3183, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dbrack_darr(V *a) { (void)a; return F_Chk_dP_dbrack_darr(a[0], a[1]); }
static V F_Chk_dP_dbrack_ddepth(V a0, V a1) {
top:;
V s3196 = a0;
if ((s3196) == IMM(1)) {
return F_Chk_dP_dbrack_dlog2(F_Chk_dTm_dspan(a1), F_Chk_dnat__from__term(a1));
} else if ((s3196) == IMM(0)) {
return F_Chk_dP_dpure(a1);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dbrack_ddepth(V *a) { (void)a; return F_Chk_dP_dbrack_ddepth(a[0], a[1]); }
static V S3198(void) { static V c; return STRC(c, "a power of two count (^d takes a depth)"); }
static V F_Chk_dP_dbrack_dlog2(V a0, V a1) {
top:;
V s3197 = a1;
if ((s3197) == IMM(0)) {
return F_Chk_dP_dthrow(F_Chk_derr0(S3198(), IMM(0), a0));
} else if (TAG(s3197) == 1) {
return F_Chk_dP_dbrack_dlog2_dgo(a0, FLD(s3197, 0), F_Chk_dNat_dlog2__exact(FLD(s3197, 0)));
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
V s3199 = a3;
if ((s3199) == IMM(0)) {
return F_Chk_dNat_dlog2__exact_dgo(a0, nat_addk(a1, 1), F_Nat_ddouble(a2));
} else if ((s3199) == IMM(1)) {
return C1(1, a1);
} else if ((s3199) == IMM(2)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dNat_dlog2__exact_dcmp(V *a) { (void)a; return F_Chk_dNat_dlog2__exact_dcmp(a[0], a[1], a[2], a[3]); }
static V W_Nat_ddouble(V *a) { (void)a; return F_Nat_ddouble(a[0]); }
static V S3201(void) { static V c; return STRC(c, "a power of two count (^d takes a depth)"); }
static V F_Chk_dP_dbrack_dlog2_dgo(V a0, V a1, V a2) {
top:;
V s3200 = a2;
if ((s3200) == IMM(0)) {
return F_Chk_dP_dthrow(F_Chk_derr0(S3201(), IMM(0), a0));
} else if (TAG(s3200) == 1) {
return F_Chk_dP_dpure(C2(16, C1(0, FLD(s3200, 0)), a0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dbrack_dlog2_dgo(V *a) { (void)a; return F_Chk_dP_dbrack_dlog2_dgo(a[0], a[1], a[2]); }
static V S3207(void) { static V c; return STRC(c, ","); }
static V L3208(V *a) {
return F_Chk_dP_dif(a[2], F_Chk_dP_dtup_dmore(a[1], a[0]), F_Chk_dP_dtup_dend(a[0]));
}
static V L3206(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[2], F_Chk_dP_dtake(S3207()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3208, 3, 2, (V[]){a[0], a[1]}));
}
static V L3205(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_dBody_dis__reply(a[1])), mk_clo(L3206, 3, 2, (V[]){a[1], a[0]}));
}
static V L3204(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3205, 3, 2, (V[]){a[0], a[1]}));
}
static V L3203(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody(F_U32_dsub(a[1], 1u)), mk_clo(L3204, 2, 1, (V[]){a[0]}));
}
static V L3202(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcol(), mk_clo(L3203, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dtup(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3202, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dtup(V *a) { (void)a; return F_Chk_dP_dtup(a[0]); }
static V S3210(void) { static V c; return STRC(c, ":"); }
static V S3213(void) { static V c; return STRC(c, ")"); }
static V L3214(V *a) {
return F_Chk_dP_dpure(a[0]);
}
static V L3212(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3213()), mk_clo(L3214, 2, 1, (V[]){a[0]}));
}
static V L3211(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[1], F_Chk_dP_dtup_dann(a[0]), F_Chk_dP_dpure(a[0])), mk_clo(L3212, 1, 0, 0));
}
static V L3209(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3210()), mk_clo(L3211, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dtup_dend(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dflatten(a0, IMM(0)), mk_clo(L3209, 1, 0, 0));
}
static V W_Chk_dP_dtup_dend(V *a) { (void)a; return F_Chk_dP_dtup_dend(a[0]); }
static V L3215(V *a) {
return F_Chk_dP_dns(a[0], a[1]);
}
static V F_Chk_dP_dtup_dann(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3215, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dtup_dann(V *a) { (void)a; return F_Chk_dP_dtup_dann(a[0]); }
static V S3218(void) { static V c; return STRC(c, "Tuple"); }
static V L3217(V *a) {
return F_Chk_dP_dpure(C3(15, S3218(), C2(1, F_Chk_dBody_dreply__x(a[1]), C2(1, a[0], IMM(0))), a[2]));
}
static V L3216(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3217, 3, 2, (V[]){a[2], a[0]}));
}
static V F_Chk_dP_dtup_dmore(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtup(a0), mk_clo(L3216, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dtup_dmore(V *a) { (void)a; return F_Chk_dP_dtup_dmore(a[0], a[1]); }
static V F_Chk_dBody_dreply__x(V a0) {
top:;
V s3219 = a0;
if (TAG(s3219) == 2) {
return FLD(s3219, 0);
} else {
return C1(18, IMM(0));
}
}
static V W_Chk_dBody_dreply__x(V *a) { (void)a; return F_Chk_dBody_dreply__x(a[0]); }
static V F_Chk_dBody_dis__reply(V a0) {
top:;
V s3220 = a0;
if (TAG(s3220) == 2) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dBody_dis__reply(V *a) { (void)a; return F_Chk_dBody_dis__reply(a[0]); }
static V L3221(V *a) {
return C1(1, C2(0, F_Chk_dCur_dcol(F_Chk_dPS_dcur(a[0])), a[0]));
}
static V F_Chk_dP_dcol(void) {
top:;
return mk_clo(L3221, 1, 0, 0);
}
static V W_Chk_dP_dcol(V *a) { (void)a; return F_Chk_dP_dcol(); }
static V F_Chk_dCur_dcol(V a0) {
top:;
V v3222 = a0;
return FLD(v3222, 2);
}
static V W_Chk_dCur_dcol(V *a) { (void)a; return F_Chk_dCur_dcol(a[0]); }
static V S3225(void) { static V c; return STRC(c, "=="); }
static V L3226(V *a) {
return F_Chk_dP_dif(a[1], F_Chk_dP_dbrace_drfl(), F_Chk_dP_dbrace_dterm(a[0]));
}
static V L3224(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3225()), mk_clo(L3226, 2, 1, (V[]){a[0]}));
}
static V L3223(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3224, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dbrace(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3223, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbrace(V *a) { (void)a; return F_Chk_dP_dbrace(a[0]); }
static V S3229(void) { static V c; return STRC(c, "=="); }
static V S3231(void) { static V c; return STRC(c, "!="); }
static V L3232(V *a) {
return F_Chk_dP_dbrace_dgo(a[2], a[1], a[0], a[3]);
}
static V L3230(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[2], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dtake(S3231())), mk_clo(L3232, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L3228(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3229()), mk_clo(L3230, 3, 2, (V[]){a[0], a[1]}));
}
static V L3227(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3228, 3, 2, (V[]){a[1], a[0]}));
}
static V F_Chk_dP_dbrace_dterm(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3227, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbrace_dterm(V *a) { (void)a; return F_Chk_dP_dbrace_dterm(a[0]); }
static V S3236(void) { static V c; return STRC(c, ":"); }
static V S3239(void) { static V c; return STRC(c, "}"); }
static V L3240(V *a) {
return F_Chk_dP_dpure(C4(19, a[2], a[1], a[0], IMM(0)));
}
static V L3238(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3239()), mk_clo(L3240, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L3237(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3238, 3, 2, (V[]){a[0], a[1]}));
}
static V L3235(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3236()), mk_clo(L3237, 3, 2, (V[]){a[1], a[0]}));
}
static V S3244(void) { static V c; return STRC(c, ":"); }
static V S3247(void) { static V c; return STRC(c, "}"); }
static V S3250(void) { static V c; return STRC(c, "_"); }
static V S3252(void) { static V c; return STRC(c, "_"); }
static V S3253(void) { static V c; return STRC(c, "Empty"); }
static V L3251(V *a) {
return F_Chk_dP_dpure(CN(11, 6, (V[]){IMM(1), S3252(), a[5], C4(19, a[4], a[3], a[2], a[1]), C3(24, IMM(0), a[5], C3(4, S3253(), a[0], IMM(0))), a[1]}));
}
static V L3249(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dopen(S3250()), mk_clo(L3251, 6, 5, (V[]){a[0], a[4], a[1], a[2], a[3]}));
}
static V L3248(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[4]), mk_clo(L3249, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3246(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3247()), mk_clo(L3248, 6, 5, (V[]){a[0], a[4], a[1], a[2], a[3]}));
}
static V L3245(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3246, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3243(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3244()), mk_clo(L3245, 5, 4, (V[]){a[0], a[3], a[1], a[2]}));
}
static V L3242(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3243, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L3241(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(F_U32_dsub(a[2], 2u)), mk_clo(L3242, 3, 2, (V[]){a[0], a[1]}));
}
static V S3254(void) { static V c; return STRC(c, ":"); }
static V S3257(void) { static V c; return STRC(c, "}"); }
static V L3258(V *a) {
return F_Chk_dP_dpure(C3(23, a[1], a[0], IMM(0)));
}
static V L3256(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3257()), mk_clo(L3258, 3, 2, (V[]){a[1], a[0]}));
}
static V L3255(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3256, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dbrace_dgo(V a0, V a1, V a2, V a3) {
top:;
V s3233 = a2;
V s3234 = a3;
if ((s3233) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3235, 2, 1, (V[]){a1}));
} else if ((s3233) == IMM(0) && (s3234) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L3241, 3, 2, (V[]){a1, a0}));
} else if ((s3233) == IMM(0) && (s3234) == IMM(0)) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3254()), mk_clo(L3255, 2, 1, (V[]){a1}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dbrace_dgo(V *a) { (void)a; return F_Chk_dP_dbrace_dgo(a[0], a[1], a[2], a[3]); }
static V S3259(void) { static V c; return STRC(c, "}"); }
static V L3260(V *a) {
return F_Chk_dP_dpure(C1(20, IMM(0)));
}
static V F_Chk_dP_dbrace_drfl(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_deat(S3259()), mk_clo(L3260, 1, 0, 0));
}
static V W_Chk_dP_dbrace_drfl(V *a) { (void)a; return F_Chk_dP_dbrace_drfl(); }
static V S3264(void) { static V c; return STRC(c, "@"); }
static V L3266(V *a) {
return F_Chk_dP_drwt_dgo(a[1], a[0], a[2]);
}
static V L3265(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_drwt_dname(a[1], a[2]), mk_clo(L3266, 3, 2, (V[]){a[1], a[0]}));
}
static V L3263(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3264()), mk_clo(L3265, 3, 2, (V[]){a[0], a[1]}));
}
static V L3262(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3263, 3, 2, (V[]){a[0], a[1]}));
}
static V L3261(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3262, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_drwt(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3261, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_drwt(V *a) { (void)a; return F_Chk_dP_drwt(a[0]); }
static V S3269(void) { static V c; return STRC(c, ":"); }
static V S3273(void) { static V c; return STRC(c, "_"); }
static V S3279(void) { static V c; return STRC(c, ";"); }
static V S3283(void) { static V c; return STRC(c, "_"); }
static V L3282(V *a) {
return F_Chk_dP_dpure(C4(21, a[6], CN(12, 5, (V[]){S3283(), a[5], C3(24, IMM(0), a[5], CN(12, 5, (V[]){a[4], a[3], C3(24, IMM(0), a[3], a[2]), F_Chk_dTm_dspan(a[1]), IMM(3)})), a[7], IMM(3)}), a[0], a[7]));
}
static V L3281(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[6]), mk_clo(L3282, 8, 7, (V[]){a[7], a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3280(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dblock(), mk_clo(L3281, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3278(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3279()), mk_clo(L3280, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3277(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3278, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3276(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[6]), mk_clo(L3277, 8, 7, (V[]){a[0], a[7], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3275(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3276, 8, 7, (V[]){a[0], a[6], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3274(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dopen(a[5]), mk_clo(L3275, 7, 6, (V[]){a[0], a[5], a[1], a[2], a[3], a[4]}));
}
static V L3272(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpush__scope(C2(0, S3273(), a[5])), mk_clo(L3274, 7, 6, (V[]){a[0], a[5], a[1], a[2], a[3], a[4]}));
}
static V L3271(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dfresh__id(), mk_clo(L3272, 6, 5, (V[]){a[0], a[1], a[2], a[4], a[3]}));
}
static V L3270(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3271, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Chk_dP_drwt_dgo(V a0, V a1, V a2) {
top:;
V v3267 = a2;
V v3268 = FLD(v3267, 0);
return F_Chk_dP_dbind(F_Chk_dP_deat(S3269()), mk_clo(L3270, 5, 4, (V[]){a1, FLD(v3267, 1), a0, v3268}));
}
static V W_Chk_dP_drwt_dgo(V *a) { (void)a; return F_Chk_dP_drwt_dgo(a[0], a[1], a[2]); }
static V L3284(V *a) {
return C1(1, C2(0, IMM(0), F_Chk_dPS_dpush(a[1], a[0])));
}
static V F_Chk_dP_dpush__scope(V a0) {
top:;
return mk_clo(L3284, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dpush__scope(V *a) { (void)a; return F_Chk_dP_dpush__scope(a[0]); }
static V S3286(void) { static V c; return STRC(c, "a name before @ (a rewrite binder is one name: %e@E : P)"); }
static V S3287(void) { static V c; return STRC(c, ""); }
static V F_Chk_dP_drwt_dname(V a0, V a1) {
top:;
V s3285 = a1;
if ((s3285) == IMM(1)) {
return F_Chk_dP_dif(F_Chk_dTm_dis__var(a0), F_Chk_dP_drwt_dnamed(a0), F_Chk_dP_dfail(S3286()));
} else if ((s3285) == IMM(0)) {
return F_Chk_dP_dpure(C2(0, S3287(), a0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_drwt_dname(V *a) { (void)a; return F_Chk_dP_drwt_dname(a[0], a[1]); }
static V L3288(V *a) {
return F_Chk_dP_dpure(C2(0, F_Chk_dTm_dname(a[0]), a[1]));
}
static V F_Chk_dP_drwt_dnamed(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3288, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_drwt_dnamed(V *a) { (void)a; return F_Chk_dP_drwt_dnamed(a[0]); }
static V S3290(void) { static V c; return STRC(c, "{"); }
static V L3293(V *a) {
return F_Chk_dP_dpure(F_Chk_dP_darms_dfin(a[0], a[1]));
}
static V L3292(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[0]), mk_clo(L3293, 2, 1, (V[]){a[1]}));
}
static V L3291(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_darms_dgo(IMM(0)), mk_clo(L3292, 2, 1, (V[]){a[0]}));
}
static V L3289(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3290()), mk_clo(L3291, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_darms(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3289, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_darms(V *a) { (void)a; return F_Chk_dP_darms(a[0]); }
static V F_Chk_dP_darms_dfin(V a0, V a1) {
top:;
V v3294 = a0;
return F_Chk_darms_dbuild(FLD(v3294, 0), F_Chk_dTm_dspanned(FLD(v3294, 1), a1), a1);
}
static V W_Chk_dP_darms_dfin(V *a) { (void)a; return F_Chk_dP_darms_dfin(a[0], a[1]); }
static V F_Chk_darms_dbuild(V a0, V a1, V a2) {
top:;
V s3295 = a0;
if ((s3295) == IMM(0)) {
return a1;
} else if (TAG(s3295) == 1 && TAG(FLD(s3295, 0)) == 15 && TAG(FLD(FLD(s3295, 0), 1)) == 1 && (FLD(FLD(FLD(s3295, 0), 1), 1)) == IMM(0)) {
return C4(17, FLD(FLD(s3295, 0), 0), FLD(FLD(FLD(s3295, 0), 1), 0), F_Chk_darms_dbuild(FLD(s3295, 1), a1, a2), a2);
} else if (TAG(s3295) == 1) {
{ V t0 = FLD(s3295, 1); V t1 = a1; V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_darms_dbuild(V *a) { (void)a; return F_Chk_darms_dbuild(a[0], a[1], a[2]); }
static V S3297(void) { static V c; return STRC(c, "}"); }
static V L3298(V *a) {
return F_Chk_dP_dif(a[1], F_Chk_dP_dpure(C2(0, a[0], C1(18, IMM(0)))), F_Chk_dP_darms_ditem(a[0]));
}
static V L3296(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3297()), mk_clo(L3298, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_darms_dgo(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3296, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_darms_dgo(V *a) { (void)a; return F_Chk_dP_darms_dgo(a[0]); }
static V S3302(void) { static V c; return STRC(c, ":"); }
static V L3303(V *a) {
return F_Chk_dP_darms_dmore(a[1], a[0], a[2]);
}
static V L3301(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[2], F_Chk_dP_dtake(S3302()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3303, 3, 2, (V[]){a[0], a[1]}));
}
static V L3300(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Bool_dor(F_Chk_dTm_dis__var(a[1]), F_Chk_dTm_dis__ref(a[1]))), mk_clo(L3301, 3, 2, (V[]){a[1], a[0]}));
}
static V L3299(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3300, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_darms_ditem(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3299, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_darms_ditem(V *a) { (void)a; return F_Chk_dP_darms_ditem(a[0]); }
static V S3308(void) { static V c; return STRC(c, ";"); }
static V L3309(V *a) {
return F_Chk_dP_darms_dgo(F_List_dappend(a[3], C2(1, C3(15, a[2], C2(1, a[1], IMM(0)), F_Chk_dTm_dspan(a[0])), IMM(0))));
}
static V L3307(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3308()), mk_clo(L3309, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3306(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3307, 5, 4, (V[]){a[0], a[3], a[1], a[2]}));
}
static V L3305(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3306, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V S3311(void) { static V c; return STRC(c, ";"); }
static V S3313(void) { static V c; return STRC(c, "}"); }
static V L3314(V *a) {
return F_Chk_dP_dpure(C2(0, a[1], a[0]));
}
static V L3312(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3313()), mk_clo(L3314, 3, 2, (V[]){a[0], a[1]}));
}
static V L3310(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3311()), mk_clo(L3312, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_darms_dmore(V a0, V a1, V a2) {
top:;
V s3304 = a2;
if ((s3304) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(F_Chk_dTm_dname(a1)), mk_clo(L3305, 3, 2, (V[]){a1, a0}));
} else if ((s3304) == IMM(0)) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3310, 3, 2, (V[]){a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_darms_dmore(V *a) { (void)a; return F_Chk_dP_darms_dmore(a[0], a[1], a[2]); }
static V L3319(V *a) {
return F_Chk_dP_dplus_dgo(a[2], a[1], a[0], F_Chk_dTld_dadt__ng(F_Chk_dbook__tld(a[3], a[1])));
}
static V L3318(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3319, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L3317(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dplus_dkey(a[0]), mk_clo(L3318, 3, 2, (V[]){a[1], a[0]}));
}
static V L3316(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[0]), mk_clo(L3317, 2, 1, (V[]){a[1]}));
}
static V L3315(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm(12u), mk_clo(L3316, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dplus(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3315, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dplus(V *a) { (void)a; return F_Chk_dP_dplus(a[0]); }
static V F_Chk_dTld_dadt__ng(V a0) {
top:;
V s3320 = a0;
if (TAG(s3320) == 1 && TAG(FLD(s3320, 0)) == 1) {
return C1(1, C2(0, FLD(FLD(s3320, 0), 0), FLD(FLD(s3320, 0), 1)));
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dadt__ng(V *a) { (void)a; return F_Chk_dTld_dadt__ng(a[0]); }
static V S3322(void) { static V c; return STRC(c, "a quantified datatype after + (+D<..> sets D's leading quantities to &2)"); }
static V F_Chk_dP_dplus_dgo(V a0, V a1, V a2, V a3) {
top:;
V s3321 = a3;
if ((s3321) == IMM(0)) {
return F_Chk_dP_dif(F_Chk_dTm_dis__var(a0), F_Chk_dP_dpure(C2(2, F_Chk_dTm_dname(a0), a2)), F_Chk_dP_dfail(S3322()));
} else if (TAG(s3321) == 1) {
return F_Chk_dP_dplus_dadt(a0, a1, a2, FLD(s3321, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dplus_dgo(V *a) { (void)a; return F_Chk_dP_dplus_dgo(a[0], a[1], a[2], a[3]); }
static V S3326(void) { static V c; return STRC(c, "a quantified datatype after + (+D<..> sets D's leading quantities to &2)"); }
static V F_Chk_dP_dplus_dadt(V a0, V a1, V a2, V a3) {
top:;
V v3323 = a3;
V v3324 = FLD(v3323, 1);
V v3325 = FLD(v3323, 0);
return F_Chk_dP_dif(F_Bool_dor(F_Nat_dis__eq(v3324, 0u), F_Bool_dand(F_Nat_dis__lt(v3324, v3325), F_Bool_dnot(F_Chk_dTm_dis__adt(a0)))), F_Chk_dP_dfail(S3326()), F_Chk_dP_dpure(C4(14, a1, F_Chk_dplus_dargs(F_Chk_dP_dplus_dxs(a0, v3325, a2), v3324), a2, IMM(0))));
}
static V W_Chk_dP_dplus_dadt(V *a) { (void)a; return F_Chk_dP_dplus_dadt(a[0], a[1], a[2], a[3]); }
static V F_Chk_dP_dplus_dxs(V a0, V a1, V a2) {
top:;
V s3327 = a0;
if (TAG(s3327) == 14) {
return FLD(s3327, 1);
} else {
return F_Chk_dList_drepeat__tm(C2(9, IMM(1), a2), a1);
}
}
static V W_Chk_dP_dplus_dxs(V *a) { (void)a; return F_Chk_dP_dplus_dxs(a[0], a[1], a[2]); }
static V F_Chk_dplus_dargs(V a0, V a1) {
top:;
V s3328 = a0;
V s3329 = a1;
if (TAG(s3328) == 1 && nat_ge(s3329, 1)) {
return C2(1, C2(9, IMM(2), F_Chk_dTm_dspan(FLD(s3328, 0))), F_Chk_dplus_dargs(FLD(s3328, 1), nat_subk(s3329, 1)));
} else {
return s3328;
}
}
static V W_Chk_dplus_dargs(V *a) { (void)a; return F_Chk_dplus_dargs(a[0], a[1]); }
static V F_Chk_dTm_dis__adt(V a0) {
top:;
V s3330 = a0;
if (TAG(s3330) == 14) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTm_dis__adt(V *a) { (void)a; return F_Chk_dTm_dis__adt(a[0]); }
static V S3332(void) { static V c; return STRC(c, ""); }
static V F_Chk_dP_dplus_dkey(V a0) {
top:;
V s3331 = a0;
if (TAG(s3331) == 14) {
return F_Chk_dP_dpure(FLD(s3331, 0));
} else {
return F_Chk_dP_dif(F_Bool_dor(F_Chk_dTm_dis__var(s3331), F_Chk_dTm_dis__ref(s3331)), F_Chk_dP_dreso(F_Chk_dTm_dname(s3331)), F_Chk_dP_dpure(S3332()));
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
static V L3336(V *a) {
return F_Chk_dP_dpure(C2(9, F_Chk_damp_dq(a[0]), a[1]));
}
static V L3335(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3336, 2, 1, (V[]){a[0]}));
}
static V L3334(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3335, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_damp_dgo(V a0, V a1) {
top:;
V s3333 = a1;
if ((s3333) == 0) {
return F_Chk_dP_dall(IMM(1));
} else if (nat_ge(s3333, 1)) {
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3334, 3, 2, (V[]){nat_subk(s3333, 1), a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_damp_dgo(V *a) { (void)a; return F_Chk_dP_damp_dgo(a[0], a[1]); }
static V F_Chk_damp_dq(V a0) {
top:;
V s3337 = a0;
if ((s3337) == 0) {
return IMM(0);
} else if ((s3337) == 1) {
return IMM(1);
} else if (nat_ge(s3337, 2)) {
return IMM(2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_damp_dq(V *a) { (void)a; return F_Chk_damp_dq(a[0]); }
static V S3342(void) { static V c; return STRC(c, ":"); }
static V S3345(void) { static V c; return STRC(c, "->"); }
static V L3351(V *a) {
return F_Chk_dP_dpure(F_Chk_dall_dbuild(a[5], a[4], a[3], a[2], a[1], a[0], a[6]));
}
static V L3350(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[6]), mk_clo(L3351, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3349(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[6]), mk_clo(L3350, 8, 7, (V[]){a[7], a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3348(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3349, 8, 7, (V[]){a[0], a[6], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3347(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dopen(a[4]), mk_clo(L3348, 7, 6, (V[]){a[0], a[4], a[1], a[2], a[3], a[5]}));
}
static V L3346(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3347, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L3344(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3345()), mk_clo(L3346, 6, 5, (V[]){a[4], a[0], a[1], a[2], a[3]}));
}
static V L3343(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm(1u), mk_clo(L3344, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3341(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3342()), mk_clo(L3343, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3340(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3341, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L3339(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[1], F_Chk_dP_dpure(IMM(1)), F_Chk_dP_dquant()), mk_clo(L3340, 3, 2, (V[]){a[1], a[0]}));
}
static V L3338(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3339, 3, 2, (V[]){a[1], a[0]}));
}
static V F_Chk_dP_dall(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L3338, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dall(V *a) { (void)a; return F_Chk_dP_dall(a[0]); }
static V S3353(void) { static V c; return STRC(c, "Exists"); }
static V F_Chk_dall_dbuild(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s3352 = a0;
if ((s3352) == IMM(1)) {
return C3(13, C3(13, C3(4, S3353(), a6, IMM(0)), a4, a6), CN(12, 5, (V[]){a2, a3, C3(24, IMM(0), a3, a5), a6, IMM(3)}), a6);
} else if ((s3352) == IMM(0)) {
return CN(11, 6, (V[]){a1, a2, a3, a4, C3(24, IMM(0), a3, a5), IMM(0)});
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dall_dbuild(V *a) { (void)a; return F_Chk_dall_dbuild(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S3355(void) { static V c; return STRC(c, "-"); }
static V S3357(void) { static V c; return STRC(c, "+"); }
static V L3358(V *a) {
return F_Chk_dP_dpure(F_Bool_dpick(a[0], IMM(0), F_Bool_dpick(a[1], IMM(2), IMM(1))));
}
static V L3356(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[0], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dtake(S3357())), mk_clo(L3358, 2, 1, (V[]){a[0]}));
}
static V L3354(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3355()), mk_clo(L3356, 1, 0, 0));
}
static V F_Chk_dP_dquant(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3354, 1, 0, 0));
}
static V W_Chk_dP_dquant(V *a) { (void)a; return F_Chk_dP_dquant(); }
static V L3364(V *a) {
return F_Chk_dP_dnum_dgo(a[1], a[0], a[2], F_Chk_dnum_dkind(a[2]));
}
static V L3363(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek__rest(), mk_clo(L3364, 3, 2, (V[]){a[0], a[1]}));
}
static V L3362(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dsteps(a[1]), mk_clo(L3363, 3, 2, (V[]){a[2], a[0]}));
}
static V L3361(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_String_dtake(a[1], a[2])), mk_clo(L3362, 3, 2, (V[]){a[0], a[2]}));
}
static V L3360(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_ddigits_dspan(a[1])), mk_clo(L3361, 3, 2, (V[]){a[0], a[1]}));
}
static V L3359(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek__rest(), mk_clo(L3360, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dnum(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L3359, 1, 0, 0));
}
static V W_Chk_dP_dnum(V *a) { (void)a; return F_Chk_dP_dnum(); }
static V F_Chk_dnum_dkind(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__eq(F_Chk_dStr_dfirst(a0), 110u), 1u, F_Bool_dpick(F_Bool_dand(F_U32_dis__eq(F_Chk_dStr_dfirst(a0), 46u), F_Chk_dis__digit(F_Chk_dStr_dsecond(a0))), 2u, 0u));
}
static V W_Chk_dnum_dkind(V *a) { (void)a; return F_Chk_dnum_dkind(a[0]); }
static V S3369(void) { static V c; return STRC(c, "a numeric literal (NUMBER is U32, NUMBER n is Nat)"); }
static V S3370(void) { static V c; return STRC(c, "a u32 literal up to 4294967295 (got "); }
static V S3371(void) { static V c; return STRC(c, ")"); }
static V L3368(V *a) {
return F_Chk_dP_dif(F_Chk_dis__name(a[2]), F_Chk_dP_dfail(S3369()), F_Chk_dP_dif(F_Nat_dis__gt(a[1], 4294967295u), F_Chk_dP_dfail(F_String_dappend(S3370(), F_String_dappend(a[0], S3371()))), F_Chk_dP_dpure(F_Chk_du32__to__term(F_U32_dfrom__nat(a[1]), a[3]))));
}
static V L3367(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[2]), mk_clo(L3368, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V L3372(V *a) {
return F_Chk_dP_dnat(a[1], a[0], F_Chk_ddigits_dval(a[0], F_String_dlength(a[0]), 0u));
}
static V F_Chk_dP_dnum_dgo(V a0, V a1, V a2, V a3) {
top:;
V s3365 = a3;
if ((s3365) == 0) {
V v3366 = F_Chk_ddigits_dval(a1, F_String_dlength(a1), 0u);
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3367, 4, 3, (V[]){a1, v3366, a0}));
} else if ((s3365) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3372, 3, 2, (V[]){a1, a0}));
} else if (nat_ge(s3365, 2)) {
return F_Chk_dP_dflt(a0, a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dnum_dgo(V *a) { (void)a; return F_Chk_dP_dnum_dgo(a[0], a[1], a[2], a[3]); }
static V L3375(V *a) {
return F_Chk_dP_dflt_dgo(F_String_dappend(a[1], a[0]), F_F32_dread(F_String_dappend(a[1], a[0])), a[2]);
}
static V L3374(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[2]), mk_clo(L3375, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dflt(V a0, V a1, V a2) {
top:;
V v3373 = F_Chk_dflt_dtext(a2);
return F_Chk_dP_dbind(F_Chk_dP_dsteps(F_String_dlength(v3373)), mk_clo(L3374, 4, 3, (V[]){v3373, a1, a0}));
}
static V W_Chk_dP_dflt(V *a) { (void)a; return F_Chk_dP_dflt(a[0], a[1], a[2]); }
static V W_F32_dread(V *a) { (void)a; return F_F32_dread(a[0]); }
static V S3377(void) { static V c; return STRC(c, "F32"); }
static V S3378(void) { static V c; return STRC(c, "a float literal with a finite f32 value (got "); }
static V S3379(void) { static V c; return STRC(c, ")"); }
static V S3380(void) { static V c; return STRC(c, "a float literal with a finite f32 value (got "); }
static V S3381(void) { static V c; return STRC(c, ")"); }
static V F_Chk_dP_dflt_dgo(V a0, V a1, V a2) {
top:;
V s3376 = a1;
if (TAG(s3376) == 1) {
return F_Chk_dP_dif(F_Chk_dF32_dis__finite(FLD(s3376, 0)), F_Chk_dP_dpure(C3(15, S3377(), C2(1, F_Chk_dword__to__term(F_F32_dbits(FLD(s3376, 0)), a2), IMM(0)), a2)), F_Chk_dP_dfail(F_String_dappend(S3378(), F_String_dappend(a0, S3379()))));
} else if ((s3376) == IMM(0)) {
return F_Chk_dP_dfail(F_String_dappend(S3380(), F_String_dappend(a0, S3381())));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dflt_dgo(V *a) { (void)a; return F_Chk_dP_dflt_dgo(a[0], a[1], a[2]); }
static V W_F32_dbits(V *a) { (void)a; return F_F32_dbits(a[0]); }
static V F_Chk_dF32_dis__finite(V a0) {
top:;
V v3382 = F_F32_dbits(a0);
return F_Bool_dnot(F_U32_dis__eq(F_U32_dand(v3382, 2139095040u), 2139095040u));
}
static V W_Chk_dF32_dis__finite(V *a) { (void)a; return F_Chk_dF32_dis__finite(a[0]); }
static V L3383(V *a) {
return C1(1, C2(0, IMM(0), F_Chk_dPS_dset__cur(a[1], F_Chk_dCur_dsteps(F_Chk_dPS_dcur(a[1]), a[0]))));
}
static V F_Chk_dP_dsteps(V a0) {
top:;
return mk_clo(L3383, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dsteps(V *a) { (void)a; return F_Chk_dP_dsteps(a[0]); }
static V F_Chk_dflt_dtext(V a0) {
top:;
V v3384 = F_Chk_ddigits_dspan(F_String_ddrop(a0, 1u));
V v3385 = F_String_ddrop(a0, nat_addk(v3384, 1));
return F_String_dappend(F_String_dtake(a0, nat_addk(v3384, 1)), F_Chk_dflt_dexp(v3385));
}
static V W_Chk_dflt_dtext(V *a) { (void)a; return F_Chk_dflt_dtext(a[0]); }
static V S3389(void) { static V c; return STRC(c, ""); }
static V F_Chk_dflt_dexp(V a0) {
top:;
V v3386 = F_Chk_dStr_dfirst(a0);
V v3387 = F_Bool_dor(F_U32_dis__eq(F_Chk_dStr_dsecond(a0), 43u), F_U32_dis__eq(F_Chk_dStr_dsecond(a0), 45u));
V v3388 = F_Chk_ddigits_dspan(F_String_ddrop(a0, F_Bool_dpick(v3387, 2u, 1u)));
return F_Bool_dpick(F_Bool_dand(F_Bool_dor(F_U32_dis__eq(v3386, 101u), F_U32_dis__eq(v3386, 69u)), F_Nat_dis__gt(v3388, 0u)), F_String_dtake(a0, F_Nat_dadd(v3388, F_Bool_dpick(v3387, 2u, 1u))), S3389());
}
static V W_Chk_dflt_dexp(V *a) { (void)a; return F_Chk_dflt_dexp(a[0]); }
static V F_Chk_ddigits_dspan(V a0) {
top:;
V s3390 = a0;
if ((s3390) == IMM(0)) {
return 0u;
} else if (TAG(s3390) == 1) {
return F_Bool_dpick(F_Chk_dis__digit(FLD(s3390, 0)), nat_addk(F_Chk_ddigits_dspan(FLD(s3390, 1)), 1), 0u);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_ddigits_dspan(V *a) { (void)a; return F_Chk_ddigits_dspan(a[0]); }
static V F_Chk_ddigits_dval(V a0, V a1, V a2) {
top:;
V s3391 = a0;
V s3392 = a1;
if (TAG(s3391) == 1 && nat_ge(s3392, 1)) {
{ V t0 = FLD(s3391, 1); V t1 = nat_subk(s3392, 1); V t2 = F_Nat_dadd(F_Nat_dmul(a2, 10u), F_U32_dto__nat(F_U32_dsub(FLD(s3391, 0), 48u))); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else {
return a2;
}
}
static V W_Chk_ddigits_dval(V *a) { (void)a; return F_Chk_ddigits_dval(a[0], a[1], a[2]); }
static V W_Nat_dmul(V *a) { (void)a; return F_Nat_dmul(a[0], a[1]); }
static V S3393(void) { static V c; return STRC(c, "a nat literal up to 4294967295n (got "); }
static V S3394(void) { static V c; return STRC(c, "n)"); }
static V F_Chk_dP_dnat(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dif(F_Nat_dis__gt(a2, 4294967295u), F_Chk_dP_dfail(F_String_dappend(S3393(), F_String_dappend(a1, S3394()))), F_Chk_dP_dnat_dgo(a0, a2));
}
static V W_Chk_dP_dnat(V *a) { (void)a; return F_Chk_dP_dnat(a[0], a[1], a[2]); }
static V S3395(void) { static V c; return STRC(c, "+"); }
static V L3396(V *a) {
return F_Chk_dP_dif(a[2], F_Chk_dP_dnat_dplus(a[1], a[0]), F_Chk_dP_dnat_dlit(a[1], a[0]));
}
static V F_Chk_dP_dnat_dgo(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3395()), mk_clo(L3396, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dnat_dgo(V *a) { (void)a; return F_Chk_dP_dnat_dgo(a[0], a[1]); }
static V S3399(void) { static V c; return STRC(c, "a nat literal (NUMBER n)"); }
static V L3398(V *a) {
return F_Chk_dP_dif(F_Chk_dis__name(a[1]), F_Chk_dP_dfail(S3399()), F_Chk_dP_dpure(C2(16, C1(0, a[0]), a[2])));
}
static V L3397(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3398, 3, 2, (V[]){a[0], a[2]}));
}
static V F_Chk_dP_dnat_dlit(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3397, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dnat_dlit(V *a) { (void)a; return F_Chk_dP_dnat_dlit(a[0], a[1]); }
static V L3401(V *a) {
return F_Chk_dP_dpure(F_Chk_dnat_dplus(a[1], a[0], a[2]));
}
static V L3400(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3401, 3, 2, (V[]){a[2], a[0]}));
}
static V F_Chk_dP_dnat_dplus(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3400, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dnat_dplus(V *a) { (void)a; return F_Chk_dP_dnat_dplus(a[0], a[1]); }
static V F_Chk_dnat_dplus(V a0, V a1, V a2) {
top:;
V s3402 = a1;
if (TAG(s3402) == 16 && TAG(FLD(s3402, 0)) == 0) {
return F_Bool_dpick(F_Nat_dis__le(F_Nat_dadd(a0, FLD(FLD(s3402, 0), 0)), 4294967295u), C2(16, C1(0, F_Nat_dadd(a0, FLD(FLD(s3402, 0), 0))), a2), F_Chk_dnat_dplus_dbig(a0, C2(16, C1(0, FLD(FLD(s3402, 0), 0)), FLD(s3402, 1)), a2));
} else {
return F_Chk_dnat_dplus_dbig(a0, s3402, a2);
}
}
static V W_Chk_dnat_dplus(V *a) { (void)a; return F_Chk_dnat_dplus(a[0], a[1], a[2]); }
static V S3403(void) { static V c; return STRC(c, "Nat.add"); }
static V F_Chk_dnat_dplus_dbig(V a0, V a1, V a2) {
top:;
return F_Bool_dpick(F_Nat_dis__gt(a0, 256u), C3(13, C3(13, C3(4, S3403(), a2, IMM(0)), C2(16, C1(0, a0), a2), a2), a1, a2), F_Chk_dnat_dsuccs(a0, a1, a2));
}
static V W_Chk_dnat_dplus_dbig(V *a) { (void)a; return F_Chk_dnat_dplus_dbig(a[0], a[1], a[2]); }
static V S3405(void) { static V c; return STRC(c, "Succ"); }
static V F_Chk_dnat_dsuccs(V a0, V a1, V a2) {
top:;
V s3404 = a0;
if ((s3404) == 0) {
return a1;
} else if (nat_ge(s3404, 1)) {
{ V t0 = nat_subk(s3404, 1); V t1 = C3(15, S3405(), C2(1, a1, IMM(0)), a2); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dnat_dsuccs(V *a) { (void)a; return F_Chk_dnat_dsuccs(a[0], a[1], a[2]); }
static V S3406(void) { static V c; return STRC(c, "Type"); }
static V S3407(void) { static V c; return STRC(c, "Data"); }
static V S3408(void) { static V c; return STRC(c, "Quant"); }
static V S3409(void) { static V c; return STRC(c, "Kind"); }
static V S3410(void) { static V c; return STRC(c, "do"); }
static V S3411(void) { static V c; return STRC(c, "match"); }
static V S3412(void) { static V c; return STRC(c, "case"); }
static V S3413(void) { static V c; return STRC(c, "return"); }
static V F_Chk_dP_dbase_dword(V a0, V a1) {
top:;
return F_Chk_dP_dbase_dword_dgo(a0, a1, F_Chk_dStr_dindex(C2(1, S3406(), C2(1, S3407(), C2(1, S3408(), C2(1, S3409(), C2(1, S3410(), C2(1, S3411(), C2(1, S3412(), C2(1, S3413(), IMM(0))))))))), a0, 0u));
}
static V W_Chk_dP_dbase_dword(V *a) { (void)a; return F_Chk_dP_dbase_dword(a[0], a[1]); }
static V L3415(V *a) {
return F_Chk_dP_dpure(C2(7, C2(9, IMM(1), a[0]), a[0]));
}
static V L3416(V *a) {
return F_Chk_dP_dpure(C2(7, C2(9, IMM(2), a[0]), a[0]));
}
static V L3417(V *a) {
return F_Chk_dP_dpure(C1(8, a[0]));
}
static V S3418(void) { static V c; return STRC(c, "("); }
static V S3421(void) { static V c; return STRC(c, ")"); }
static V L3423(V *a) {
return F_Chk_dP_dpure(C2(7, a[0], a[1]));
}
static V L3422(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3423, 2, 1, (V[]){a[0]}));
}
static V L3420(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3421()), mk_clo(L3422, 3, 2, (V[]){a[1], a[0]}));
}
static V L3419(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3420, 2, 1, (V[]){a[0]}));
}
static V S3424(void) { static V c; return STRC(c, "a term (a match heads a def body, not a term)"); }
static V S3425(void) { static V c; return STRC(c, "a match heading this case (this case is orphaned)"); }
static V S3426(void) { static V c; return STRC(c, "a do-block heading this return"); }
static V S3427(void) { static V c; return STRC(c, "a term (the keyword '"); }
static V S3428(void) { static V c; return STRC(c, "' cannot head one)"); }
static V F_Chk_dP_dbase_dword_dgo(V a0, V a1, V a2) {
top:;
V s3414 = a2;
if (TAG(s3414) == 1 && (FLD(s3414, 0)) == 0) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a1), mk_clo(L3415, 1, 0, 0));
} else if (TAG(s3414) == 1 && (FLD(s3414, 0)) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a1), mk_clo(L3416, 1, 0, 0));
} else if (TAG(s3414) == 1 && (FLD(s3414, 0)) == 2) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a1), mk_clo(L3417, 1, 0, 0));
} else if (TAG(s3414) == 1 && (FLD(s3414, 0)) == 3) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3418()), mk_clo(L3419, 2, 1, (V[]){a1}));
} else if (TAG(s3414) == 1 && (FLD(s3414, 0)) == 4) {
return F_Chk_dP_ddo(a1);
} else if (TAG(s3414) == 1 && (FLD(s3414, 0)) == 5) {
return F_Chk_dP_dfail(S3424());
} else if (TAG(s3414) == 1 && (FLD(s3414, 0)) == 6) {
return F_Chk_dP_dfail(S3425());
} else if (TAG(s3414) == 1 && (FLD(s3414, 0)) == 7) {
return F_Chk_dP_dfail(S3426());
} else {
return F_Chk_dP_dif(F_Chk_dStr_dhas(F_Chk_dKEYWORDS(), a0), F_Chk_dP_dfail(F_String_dappend(S3427(), F_String_dappend(a0, S3428()))), F_Chk_dP_dbase_dname(a0, a1));
}
}
static V W_Chk_dP_dbase_dword_dgo(V *a) { (void)a; return F_Chk_dP_dbase_dword_dgo(a[0], a[1], a[2]); }
static V S3429(void) { static V c; return STRC(c, "{"); }
static V L3430(V *a) {
return F_Chk_dP_dif(a[2], F_Chk_dP_dbase_dctor(a[1], a[0]), F_Chk_dP_dbase_dvar(a[1], a[0]));
}
static V F_Chk_dP_dbase_dname(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dat(S3429()), mk_clo(L3430, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dbase_dname(V *a) { (void)a; return F_Chk_dP_dbase_dname(a[0], a[1]); }
static V L3431(V *a) {
return F_Chk_dP_dvar(a[0], a[1]);
}
static V F_Chk_dP_dbase_dvar(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dspan(a1), mk_clo(L3431, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbase_dvar(V *a) { (void)a; return F_Chk_dP_dbase_dvar(a[0], a[1]); }
static V L3432(V *a) {
return F_Chk_dP_dvar_dfound(a[1], a[2], a[0]);
}
static V F_Chk_dP_dvar(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dlookup(a0), mk_clo(L3432, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dvar(V *a) { (void)a; return F_Chk_dP_dvar(a[0], a[1]); }
static V L3434(V *a) {
return F_Chk_dP_dvar_dfree(a[1], a[2], a[0], F_Chk_dStr_dhas__dot(a[1]));
}
static V F_Chk_dP_dvar_dfound(V a0, V a1, V a2) {
top:;
V s3433 = a1;
if (TAG(s3433) == 1) {
return F_Chk_dP_dpure(C3(0, a0, FLD(s3433, 0), a2));
} else if ((s3433) == IMM(0)) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(a0), mk_clo(L3434, 3, 2, (V[]){a2, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dvar_dfound(V *a) { (void)a; return F_Chk_dP_dvar_dfound(a[0], a[1], a[2]); }
static V F_Chk_dStr_dhas__dot(V a0) {
top:;
V s3435 = a0;
if ((s3435) == IMM(0)) {
return IMM(0);
} else if (TAG(s3435) == 1) {
return F_Bool_dor(F_U32_dis__eq(FLD(s3435, 0), 46u), F_Chk_dStr_dhas__dot(FLD(s3435, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dhas__dot(V *a) { (void)a; return F_Chk_dStr_dhas__dot(a[0]); }
static V L3437(V *a) {
return F_Chk_dP_dpure(C4(3, a[2], a[3], a[1], C3(4, a[0], a[1], IMM(0))));
}
static V F_Chk_dP_dvar_dfree(V a0, V a1, V a2, V a3) {
top:;
V s3436 = a3;
if ((s3436) == IMM(1)) {
return F_Chk_dP_dpure(C3(4, a1, a2, IMM(0)));
} else if ((s3436) == IMM(0)) {
return F_Chk_dP_dbind(F_Chk_dP_dfresh__id(), mk_clo(L3437, 4, 3, (V[]){a1, a2, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dvar_dfree(V *a) { (void)a; return F_Chk_dP_dvar_dfree(a[0], a[1], a[2], a[3]); }
static V S3439(void) { static V c; return STRC(c, "}"); }
static V L3442(V *a) {
return F_Chk_dP_dpure(C3(15, a[1], a[0], a[2]));
}
static V L3441(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3442, 3, 2, (V[]){a[0], a[2]}));
}
static V L3440(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(a[1]), mk_clo(L3441, 3, 2, (V[]){a[2], a[0]}));
}
static V L3438(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dargs(S3439()), mk_clo(L3440, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dbase_dctor(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3438, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dbase_dctor(V *a) { (void)a; return F_Chk_dP_dbase_dctor(a[0], a[1]); }
static V S3444(void) { static V c; return STRC(c, "<"); }
static V S3446(void) { static V c; return STRC(c, ">"); }
static V S3451(void) { static V c; return STRC(c, ":"); }
static V L3454(V *a) {
return F_Chk_dP_ddo__stmt(a[1], a[0], a[2]);
}
static V L3453(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcol(), mk_clo(L3454, 3, 2, (V[]){a[0], a[1]}));
}
static V L3452(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3453, 3, 2, (V[]){a[0], a[1]}));
}
static V L3450(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3451()), mk_clo(L3452, 3, 2, (V[]){a[1], a[0]}));
}
static V L3449(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dfill(a[2], a[1], a[3]), mk_clo(L3450, 2, 1, (V[]){a[0]}));
}
static V L3448(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[2]), mk_clo(L3449, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V L3447(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(a[1]), mk_clo(L3448, 4, 3, (V[]){a[1], a[2], a[0]}));
}
static V L3445(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dargs(S3446()), mk_clo(L3447, 3, 2, (V[]){a[0], a[1]}));
}
static V L3443(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3444()), mk_clo(L3445, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_ddo(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3443, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_ddo(V *a) { (void)a; return F_Chk_dP_ddo(a[0]); }
static V S3457(void) { static V c; return STRC(c, "return"); }
static V L3458(V *a) {
return F_Chk_dP_dif(a[4], F_Chk_dP_ddo__ret(a[3], a[2], a[1]), F_Chk_dP_ddo__step(a[3], a[2], a[0], a[1]));
}
static V L3456(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dword(S3457()), mk_clo(L3458, 5, 4, (V[]){a[0], a[3], a[1], a[2]}));
}
static V L3455(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L3456, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_ddo__stmt(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3455, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dP_ddo__stmt(V *a) { (void)a; return F_Chk_dP_ddo__stmt(a[0], a[1], a[2]); }
static V S3461(void) { static V c; return STRC(c, ":"); }
static V S3464(void) { static V c; return STRC(c, "Unit"); }
static V S3467(void) { static V c; return STRC(c, "=="); }
static V S3469(void) { static V c; return STRC(c, "="); }
static V L3470(V *a) {
return F_Chk_dP_ddo__step_dgo(a[7], a[6], a[5], a[4], a[3], a[2], a[1], a[0], a[8]);
}
static V L3468(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Bool_dand(a[7], F_Bool_dnot(a[8])), F_Chk_dP_dtake(S3469()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3470, 9, 8, (V[]){a[0], a[7], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3466(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S3467()), mk_clo(L3468, 9, 8, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]}));
}
static V L3465(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3466, 9, 8, (V[]){a[0], a[7], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3463(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[5], F_Chk_dP_dterm(1u), F_Chk_dP_dif(a[6], F_Chk_dP_dvar(S3464(), F_Chk_dTm_dspan(a[4])), F_Chk_dP_dpure(a[4]))), mk_clo(L3465, 8, 7, (V[]){a[6], a[4], a[0], a[1], a[2], a[3], a[5]}));
}
static V L3462(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[5], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dmore(a[4])), mk_clo(L3463, 7, 6, (V[]){a[0], a[4], a[1], a[2], a[3], a[5]}));
}
static V L3460(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Chk_dTm_dis__var(a[4]), F_Chk_dP_dtake(S3461()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3462, 6, 5, (V[]){a[0], a[1], a[2], a[4], a[3]}));
}
static V L3459(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3460, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V F_Chk_dP_ddo__step(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3459, 5, 4, (V[]){a3, a1, a0, a2}));
}
static V W_Chk_dP_ddo__step(V *a) { (void)a; return F_Chk_dP_ddo__step(a[0], a[1], a[2], a[3]); }
static V S3472(void) { static V c; return STRC(c, "<-"); }
static V L3473(V *a) {
return F_Chk_dP_ddo__bind(a[6], a[5], a[4], a[3], a[2], a[1], IMM(1), a[0], IMM(0));
}
static V F_Chk_dP_ddo__step_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s3471 = a6;
if ((s3471) == IMM(1)) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a8, F_Chk_dP_dpure(IMM(0)), F_Chk_dP_deat(S3472())), mk_clo(L3473, 8, 7, (V[]){a8, a5, a4, a3, a2, a1, a0}));
} else if ((s3471) == IMM(0)) {
return F_Chk_dP_dif(a7, F_Chk_dP_ddo__bind(a0, a1, a2, a3, a4, a5, IMM(0), IMM(0), IMM(1)), F_Chk_dP_ddo__arrow(a0, a1, a2, a3, a4, a5));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_ddo__step_dgo(V *a) { (void)a; return F_Chk_dP_ddo__step_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V S3474(void) { static V c; return STRC(c, "<-"); }
static V L3475(V *a) {
return F_Chk_dP_dif(a[6], F_Chk_dP_ddo__bind(a[5], a[4], a[3], a[2], a[1], a[0], IMM(0), IMM(0), IMM(0)), F_Chk_dP_ddo__last(a[5], a[4], a[1]));
}
static V F_Chk_dP_ddo__arrow(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3474()), mk_clo(L3475, 7, 6, (V[]){a5, a4, a3, a2, a1, a0}));
}
static V W_Chk_dP_ddo__arrow(V *a) { (void)a; return F_Chk_dP_ddo__arrow(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S3478(void) { static V c; return STRC(c, ""); }
static V L3479(V *a) {
return F_Chk_dP_dpure(C3(23, a[3], F_Bool_dpick(F_Chk_dTld_dis__adt(F_Chk_dbook__tld(a[2], a[1])), C4(14, a[1], a[0], F_Chk_dTm_dspan(a[3]), IMM(0)), a[4]), F_Chk_dTm_dspan(a[3])));
}
static V L3477(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_ddocall(a[3], S3478(), a[2], IMM(0), IMM(0), F_Chk_dTm_dspan(a[1])), mk_clo(L3479, 5, 4, (V[]){a[2], a[0], a[4], a[1]}));
}
static V L3476(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3477, 5, 4, (V[]){a[3], a[0], a[1], a[2]}));
}
static V F_Chk_dP_ddo__last(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dreso(a0), mk_clo(L3476, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dP_ddo__last(V *a) { (void)a; return F_Chk_dP_ddo__last(a[0], a[1], a[2]); }
static V L3480(V *a) {
return C1(1, C2(0, F_Chk_ddo_dcall(F_Chk_dPS_dbook(a[6]), a[6], a[5], a[4], a[3], a[2], a[1], a[0]), a[6]));
}
static V F_Chk_dP_ddocall(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return mk_clo(L3480, 7, 6, (V[]){a5, a4, a3, a2, a1, a0});
}
static V W_Chk_dP_ddocall(V *a) { (void)a; return F_Chk_dP_ddocall(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Chk_ddo_dcall(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
return F_Chk_dapps(C3(4, F_Chk_dPS_dreso(a1, F_String_dappend(a2, a3)), a7, IMM(0)), F_List_dappend(F_List_dappend(F_List_dappend(F_Chk_dList_dinit__tm(a4), a5), F_Chk_dList_dlast__tm(a4)), a6), a7);
}
static V W_Chk_ddo_dcall(V *a) { (void)a; return F_Chk_ddo_dcall(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V F_Chk_dList_dlast__tm(V a0) {
top:;
V s3481 = a0;
if ((s3481) == IMM(0)) {
return IMM(0);
} else if (TAG(s3481) == 1 && (FLD(s3481, 1)) == IMM(0)) {
return C2(1, FLD(s3481, 0), IMM(0));
} else if (TAG(s3481) == 1) {
{ V t0 = FLD(s3481, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dList_dlast__tm(V *a) { (void)a; return F_Chk_dList_dlast__tm(a[0]); }
static V F_Chk_dList_dinit__tm(V a0) {
top:;
V s3482 = a0;
if ((s3482) == IMM(0)) {
return IMM(0);
} else if (TAG(s3482) == 1 && (FLD(s3482, 1)) == IMM(0)) {
return IMM(0);
} else if (TAG(s3482) == 1) {
return C2(1, FLD(s3482, 0), F_Chk_dList_dinit__tm(FLD(s3482, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dList_dinit__tm(V *a) { (void)a; return F_Chk_dList_dinit__tm(a[0]); }
static V S3485(void) { static V c; return STRC(c, ";"); }
static V S3489(void) { static V c; return STRC(c, "_"); }
static V S3493(void) { static V c; return STRC(c, ".bind"); }
static V L3492(V *a) {
return F_Chk_dP_dif(a[7], F_Chk_dP_dpure(F_Chk_ddo_dlet(a[6], C3(23, a[5], a[4], a[3]), a[2], a[3])), F_Chk_dP_ddocall(a[1], S3493(), a[0], C2(1, a[4], IMM(0)), C2(1, a[5], C2(1, F_Chk_ddo_dlam(a[6], a[2], a[3]), IMM(0))), a[3]));
}
static V L3491(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[7]), mk_clo(L3492, 9, 8, (V[]){a[0], a[1], a[8], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3490(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_ddo__stmt(a[7], a[6], a[5]), mk_clo(L3491, 9, 8, (V[]){a[6], a[7], a[0], a[1], a[2], a[8], a[3], a[4]}));
}
static V L3488(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbinder(F_Bool_dpick(a[8], a[7], C3(0, S3489(), 0u, IMM(0)))), mk_clo(L3490, 9, 8, (V[]){a[0], a[1], a[2], a[3], a[9], a[4], a[5], a[6]}));
}
static V L3487(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3488, 10, 9, (V[]){a[8], a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]}));
}
static V L3486(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[8]), mk_clo(L3487, 9, 8, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]}));
}
static V L3484(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3485()), mk_clo(L3486, 10, 9, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]}));
}
static V L3483(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3484, 10, 9, (V[]){a[0], a[8], a[1], a[2], a[3], a[4], a[5], a[6], a[7]}));
}
static V F_Chk_dP_ddo__bind(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dif(a8, F_Chk_dP_dpure(a4), F_Chk_dP_dterm0()), mk_clo(L3483, 9, 8, (V[]){a5, a7, a2, a1, a0, a4, a6, a3}));
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
static V S3494(void) { static V c; return STRC(c, ";"); }
static V L3497(V *a) {
return F_Chk_dP_dpure(F_Bool_dor(a[2], F_Bool_dand(F_Bool_dnot(F_U32_dis__zero(a[1])), F_U32_dis__eq(a[3], a[0]))));
}
static V L3496(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcol(), mk_clo(L3497, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V L3495(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3496, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Chk_dP_dmore(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dat(S3494()), mk_clo(L3495, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dmore(V *a) { (void)a; return F_Chk_dP_dmore(a[0]); }
static V S3500(void) { static V c; return STRC(c, ".pure"); }
static V L3499(V *a) {
return F_Chk_dP_ddocall(a[2], S3500(), a[1], IMM(0), C2(1, a[0], IMM(0)), a[3]);
}
static V L3498(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[2]), mk_clo(L3499, 4, 3, (V[]){a[3], a[0], a[1]}));
}
static V F_Chk_dP_ddo__ret(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3498, 4, 3, (V[]){a1, a0, a2}));
}
static V W_Chk_dP_ddo__ret(V *a) { (void)a; return F_Chk_dP_ddo__ret(a[0], a[1], a[2]); }
static V L3501(V *a) {
return F_Chk_dP_dword_dif(a[0], a[1]);
}
static V F_Chk_dP_dword(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dat__word(a0), mk_clo(L3501, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dword(V *a) { (void)a; return F_Chk_dP_dword(a[0]); }
static V F_Chk_dP_dword_dif(V a0, V a1) {
top:;
V s3502 = a1;
if ((s3502) == IMM(1)) {
return F_Chk_dP_dtake(a0);
} else if ((s3502) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dword_dif(V *a) { (void)a; return F_Chk_dP_dword_dif(a[0], a[1]); }
static V L3504(V *a) {
return F_Chk_dP_dpure(F_Bool_dand(F_Chk_dStr_dprefix(a[1], a[0]), F_Bool_dnot(F_Chk_dis__name(F_Chk_dStr_dfirst(F_String_ddrop(a[1], F_String_dlength(a[0])))))));
}
static V L3503(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek__rest(), mk_clo(L3504, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dat__word(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3503, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dat__word(V *a) { (void)a; return F_Chk_dP_dat__word(a[0]); }
static V S3505(void) { static V c; return STRC(c, "="); }
static V L3506(V *a) {
return F_Chk_dP_dbody_dlet_dann(a[1], a[0]);
}
static V F_Chk_dP_dbody_dlet_deq(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_deat(S3505()), mk_clo(L3506, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dbody_dlet_deq(V *a) { (void)a; return F_Chk_dP_dbody_dlet_deq(a[0], a[1]); }
static V L3509(V *a) {
return F_Chk_dP_dpure(C2(1, C3(23, a[1], a[0], a[2]), IMM(0)));
}
static V L3508(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3509, 3, 2, (V[]){a[0], a[2]}));
}
static V F_Chk_dP_dbody_dlet_dann(V a0, V a1) {
top:;
V s3507 = a1;
if ((s3507) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s3507) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3508, 3, 2, (V[]){FLD(s3507, 0), a0}));
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
V v3510 = a0;
V s3511 = FLD(v3510, 0);
V s3512 = FLD(v3510, 1);
if (TAG(s3511) == 4 && TAG(FLD(s3511, 0)) == 1 && (FLD(FLD(s3511, 0), 0)) == 65 && TAG(FLD(FLD(s3511, 0), 1)) == 1 && (FLD(FLD(FLD(s3511, 0), 1), 0)) == 114 && TAG(FLD(FLD(FLD(s3511, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s3511, 0), 1), 1), 0)) == 114 && TAG(FLD(FLD(FLD(FLD(s3511, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s3511, 0), 1), 1), 1), 0)) == 97 && TAG(FLD(FLD(FLD(FLD(FLD(s3511, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s3511, 0), 1), 1), 1), 1), 0)) == 121 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(s3511, 0), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3511, 0), 1), 1), 1), 1), 1), 0)) == 46 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3511, 0), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3511, 0), 1), 1), 1), 1), 1), 1), 0)) == 115 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3511, 0), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3511, 0), 1), 1), 1), 1), 1), 1), 1), 0)) == 101 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3511, 0), 1), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3511, 0), 1), 1), 1), 1), 1), 1), 1), 1), 0)) == 116 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s3511, 0), 1), 1), 1), 1), 1), 1), 1), 1), 1)) == IMM(0) && TAG(s3512) == 1 && TAG(FLD(s3512, 1)) == 1 && TAG(FLD(FLD(s3512, 1), 1)) == 1 && TAG(FLD(FLD(FLD(s3512, 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s3512, 1), 1), 1), 1)) == IMM(0)) {
return F_Bool_dpick(F_Chk_dTm_dis__var(FLD(FLD(s3512, 1), 0)), C1(1, FLD(FLD(s3512, 1), 0)), IMM(0));
} else {
return IMM(0);
}
}
static V W_Chk_dterm__write_dgo(V *a) { (void)a; return F_Chk_dterm__write_dgo(a[0]); }
static V L3514(V *a) {
return F_Chk_dP_dpure(C2(2, a[0], a[1]));
}
static V L3516(V *a) {
return F_Chk_dP_dif(a[4], F_Chk_dP_dbody_dlet(a[3], a[2], IMM(1), C2(1, a[1], IMM(0)), IMM(0), C2(1, a[0], IMM(0))), F_Chk_dP_dpure(C2(2, a[0], a[5])));
}
static V L3515(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[3]), mk_clo(L3516, 6, 5, (V[]){a[0], a[1], a[3], a[2], a[4]}));
}
static V F_Chk_dP_dbody_dreply_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s3513 = a4;
if ((s3513) == IMM(0)) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a1), mk_clo(L3514, 2, 1, (V[]){a3}));
} else if (TAG(s3513) == 1) {
return F_Chk_dP_dbind(F_Chk_dP_dmore(a2), mk_clo(L3515, 5, 4, (V[]){a3, FLD(s3513, 0), a0, a1}));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dbody_dreply_dgo(V *a) { (void)a; return F_Chk_dP_dbody_dreply_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V F_Maybe_dis__none(V a2) {
top:;
return F_Bool_dnot(F_Maybe_dis__some(a2));
}
static V W_Maybe_dis__none(V *a) { (void)a; return F_Maybe_dis__none(a[2]); }
static V L3519(V *a) {
return F_Chk_dP_dpure(IMM(0));
}
static V F_Chk_dP_dbody_dty__ok(V a0, V a1, V a2) {
top:;
V s3517 = a1;
V s3518 = a2;
if (TAG(s3517) == 1 && (s3518) == IMM(0)) {
return F_Chk_dP_dbind(F_Chk_dP_dset__cur(a0), mk_clo(L3519, 1, 0, 0));
} else {
return F_Chk_dP_dpure(s3517);
}
}
static V W_Chk_dP_dbody_dty__ok(V *a) { (void)a; return F_Chk_dP_dbody_dty__ok(a[0], a[1], a[2]); }
static V L3520(V *a) {
return F_Chk_dP_dpure(C1(1, a[0]));
}
static V F_Chk_dP_dbody_dty(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3520, 1, 0, 0));
}
static V W_Chk_dP_dbody_dty(V *a) { (void)a; return F_Chk_dP_dbody_dty(); }
static V L3524(V *a) {
return F_Chk_dP_dif(a[2], F_Chk_dP_dlocal_dnames_dmore(a[1], a[0]), F_Chk_dP_dpure(a[0]));
}
static V L3523(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Bool_dand(F_Bool_dand(F_Bool_dnot(a[3]), F_Bool_dor(F_Chk_dis__head(a[2]), F_Bool_dand(F_Chk_dQ_dis__lone(a[1]), F_U32_dis__eq(a[2], 43u)))), F_Bool_dnot(F_Chk_dStr_dhas(F_Chk_dKEYWORDS(), F_Chk_dStr_dword__at(a[4]))))), mk_clo(L3524, 3, 2, (V[]){a[0], a[1]}));
}
static V L3522(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek__rest(), mk_clo(L3523, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V L3521(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3522, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dlocal_dnames(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dnl(), mk_clo(L3521, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dlocal_dnames(V *a) { (void)a; return F_Chk_dP_dlocal_dnames(a[0], a[1]); }
static V L3526(V *a) {
return F_Chk_dP_dlocal_dnames(a[2], F_List_dappend(a[1], C2(1, a[0], IMM(0))));
}
static V L3525(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3526, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V F_Chk_dP_dlocal_dnames_dmore(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3525, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dlocal_dnames_dmore(V *a) { (void)a; return F_Chk_dP_dlocal_dnames_dmore(a[0], a[1]); }
static V S3528(void) { static V c; return STRC(c, ""); }
static V F_Chk_dStr_dword__at(V a0) {
top:;
V s3527 = a0;
if (TAG(s3527) == 1) {
return F_Chk_dStr_dword__at_dif(FLD(s3527, 0), FLD(s3527, 1), F_Bool_dor(F_Chk_dis__name(FLD(s3527, 0)), F_U32_dis__eq(FLD(s3527, 0), 46u)));
} else if ((s3527) == IMM(0)) {
return S3528();
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dword__at(V *a) { (void)a; return F_Chk_dStr_dword__at(a[0]); }
static V S3530(void) { static V c; return STRC(c, ""); }
static V F_Chk_dStr_dword__at_dif(V a0, V a1, V a2) {
top:;
V s3529 = a2;
if ((s3529) == IMM(1)) {
return C2(1, a0, F_Chk_dStr_dword__at(a1));
} else if ((s3529) == IMM(0)) {
return S3530();
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dStr_dword__at_dif(V *a) { (void)a; return F_Chk_dStr_dword__at_dif(a[0], a[1], a[2]); }
static V L3532(V *a) {
return F_Chk_dP_dpure(C3(0, a[0], 0u, a[1]));
}
static V L3531(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[0]), mk_clo(L3532, 2, 1, (V[]){a[1]}));
}
static V F_Chk_dP_dbody_derased__name(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3531, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dbody_derased__name(V *a) { (void)a; return F_Chk_dP_dbody_derased__name(a[0]); }
static V L3537(V *a) {
return F_Chk_dP_dpure(C3(0, a[1], a[0], a[2]));
}
static V L3536(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[1]), mk_clo(L3537, 3, 2, (V[]){a[2], a[0]}));
}
static V L3535(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_drows(a[2], a[3], F_List_dlength(a[1])), mk_clo(L3536, 3, 2, (V[]){a[1], a[0]}));
}
static V L3534(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcol(), mk_clo(L3535, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3533(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3534, 4, 3, (V[]){a[0], a[2], a[1]}));
}
static V F_Chk_dP_dbody_dmatch(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterms(), mk_clo(L3533, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dbody_dmatch(V *a) { (void)a; return F_Chk_dP_dbody_dmatch(a[0], a[1]); }
static V S3538(void) { static V c; return STRC(c, "case"); }
static V L3540(V *a) {
return F_Chk_dP_dif(F_Bool_dand(F_U32_dis__gt(a[3], a[2]), F_Bool_dand(a[1], F_U32_dis__ge(a[4], a[3]))), F_Chk_dP_drow(a[2], a[3], a[0], a[4]), F_Chk_dP_dpure(IMM(0)));
}
static V L3539(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcol(), mk_clo(L3540, 5, 4, (V[]){a[0], a[3], a[1], a[2]}));
}
static V F_Chk_dP_drows(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3538()), mk_clo(L3539, 4, 3, (V[]){a2, a0, a1}));
}
static V W_Chk_dP_drows(V *a) { (void)a; return F_Chk_dP_drows(a[0], a[1], a[2]); }
static V S3541(void) { static V c; return STRC(c, "case"); }
static V S3544(void) { static V c; return STRC(c, " patterns (one per scrutinee)"); }
static V L3550(V *a) {
return F_Chk_dP_dpure(C2(1, C2(3, a[1], a[0]), a[2]));
}
static V L3549(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_drows(a[4], a[3], a[2]), mk_clo(L3550, 3, 2, (V[]){a[0], a[1]}));
}
static V L3548(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[4]), mk_clo(L3549, 6, 5, (V[]){a[5], a[0], a[1], a[2], a[3]}));
}
static V L3547(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbody(a[4]), mk_clo(L3548, 6, 5, (V[]){a[5], a[0], a[1], a[2], a[3]}));
}
static V L3546(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpatts(a[4]), mk_clo(L3547, 6, 5, (V[]){a[0], a[1], a[2], a[5], a[3]}));
}
static V L3545(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3546, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L3543(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Nat_dis__eq(F_List_dlength(a[4]), a[3]), F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dfail(F_String_dappend(F_Nat_dshow(a[3]), S3544()))), mk_clo(L3545, 6, 5, (V[]){a[3], a[0], a[1], a[2], a[4]}));
}
static V L3542(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterms(), mk_clo(L3543, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Chk_dP_drow(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(S3541()), mk_clo(L3542, 5, 4, (V[]){a1, a0, a3, a2}));
}
static V W_Chk_dP_drow(V *a) { (void)a; return F_Chk_dP_drow(a[0], a[1], a[2], a[3]); }
static V S3553(void) { static V c; return STRC(c, ":"); }
static V L3554(V *a) {
return F_Chk_dP_dif(a[1], F_Chk_dP_dpure(C2(1, a[0], IMM(0))), F_Chk_dP_dterms_dmore(a[0]));
}
static V L3552(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3553()), mk_clo(L3554, 2, 1, (V[]){a[0]}));
}
static V L3551(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3552, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dterms(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3551, 1, 0, 0));
}
static V W_Chk_dP_dterms(V *a) { (void)a; return F_Chk_dP_dterms(); }
static V S3555(void) { static V c; return STRC(c, ","); }
static V L3557(V *a) {
return F_Chk_dP_dpure(C2(1, a[0], a[1]));
}
static V L3556(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterms(), mk_clo(L3557, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dterms_dmore(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3555()), mk_clo(L3556, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dterms_dmore(V *a) { (void)a; return F_Chk_dP_dterms_dmore(a[0]); }
static V S3558(void) { static V c; return STRC(c, "for"); }
static V S3560(void) { static V c; return STRC(c, "exs"); }
static V L3561(V *a) {
return F_Chk_dP_dif(F_Bool_dor(a[2], a[3]), F_Chk_dP_dclause(a[1], a[0], a[2]), F_Chk_dP_dpure(C2(0, a[1], a[0])));
}
static V L3559(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3560()), mk_clo(L3561, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dclauses(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3558()), mk_clo(L3559, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_dclauses(V *a) { (void)a; return F_Chk_dP_dclauses(a[0], a[1]); }
static V S3562(void) { static V c; return STRC(c, "for"); }
static V S3563(void) { static V c; return STRC(c, "exs"); }
static V S3566(void) { static V c; return STRC(c, "~"); }
static V S3568(void) { static V c; return STRC(c, "a plain clause (only leading clauses take ~)"); }
static V S3570(void) { static V c; return STRC(c, "~"); }
static V S3576(void) { static V c; return STRC(c, ":"); }
static V S3579(void) { static V c; return STRC(c, "where"); }
static V L3582(V *a) {
return F_Chk_dP_dclauses(F_List_dappend(a[7], C2(1, CN(0, 6, (V[]){a[6], a[5], a[4], a[8], a[3], a[2]}), IMM(0))), F_Bool_dpick(a[1], nat_addk(a[0], 1), a[0]));
}
static V L3581(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dopen(a[6]), mk_clo(L3582, 9, 8, (V[]){a[0], a[1], a[2], a[7], a[6], a[3], a[4], a[5]}));
}
static V L3580(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[8], F_Chk_dP_dclause_dwhere(a[7], a[6], a[5]), F_Chk_dP_dpure(a[6])), mk_clo(L3581, 8, 7, (V[]){a[0], a[1], a[5], a[2], a[3], a[4], a[7]}));
}
static V L3578(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3579()), mk_clo(L3580, 9, 8, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[7], a[6]}));
}
static V L3577(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3578, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3575(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3576()), mk_clo(L3577, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[6], a[5]}));
}
static V L3574(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[5]), mk_clo(L3575, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[6]}));
}
static V L3573(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3574, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3572(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L3573, 6, 5, (V[]){a[0], a[1], a[4], a[2], a[3]}));
}
static V L3571(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[3], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dif(a[2], F_Chk_dP_dquant(), F_Chk_dP_dpure(IMM(1)))), mk_clo(L3572, 5, 4, (V[]){a[0], a[3], a[2], a[1]}));
}
static V L3569(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[2], F_Chk_dP_dtake(S3570()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3571, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3567(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Bool_dand(F_Bool_dand(a[2], a[3]), F_Nat_dis__lt(a[1], F_List_dlength(a[0]))), F_Chk_dP_dfail(S3568()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3569, 4, 3, (V[]){a[1], a[0], a[2]}));
}
static V L3565(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S3566()), mk_clo(L3567, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3564(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3565, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dclause(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(F_Bool_dpick(a2, S3562(), S3563())), mk_clo(L3564, 4, 3, (V[]){a0, a1, a2}));
}
static V W_Chk_dP_dclause(V *a) { (void)a; return F_Chk_dP_dclause(a[0], a[1], a[2]); }
static V S3584(void) { static V c; return STRC(c, "where"); }
static V S3591(void) { static V c; return STRC(c, "Exists"); }
static V L3590(V *a) {
return F_Chk_dP_dpure(C3(13, C3(13, C3(4, S3591(), a[5], IMM(0)), a[4], a[3]), CN(12, 5, (V[]){a[2], a[1], C3(24, IMM(0), a[1], a[0]), a[3], IMM(3)}), a[3]));
}
static V L3589(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[5]), mk_clo(L3590, 7, 6, (V[]){a[6], a[0], a[1], a[2], a[3], a[4]}));
}
static V L3588(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3589, 7, 6, (V[]){a[5], a[0], a[1], a[2], a[3], a[4]}));
}
static V L3587(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dopen(a[3]), mk_clo(L3588, 6, 5, (V[]){a[3], a[0], a[1], a[2], a[4]}));
}
static V L3586(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3587, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V L3585(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[3]), mk_clo(L3586, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3583(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dword(S3584()), mk_clo(L3585, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Chk_dP_dclause_dwhere(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L3583, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dP_dclause_dwhere(V *a) { (void)a; return F_Chk_dP_dclause_dwhere(a[0], a[1], a[2]); }
static V S3593(void) { static V c; return STRC(c, "a fresh name (duplicate declaration: "); }
static V S3594(void) { static V c; return STRC(c, ")"); }
static V L3592(V *a) {
return F_Chk_dP_dif(F_Chk_dbook__has(a[1], a[0]), F_Chk_dP_dfail(F_String_dappend(S3593(), F_String_dappend(a[0], S3594()))), F_Chk_dP_dpure(IMM(0)));
}
static V F_Chk_dP_dfresh(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3592, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dfresh(V *a) { (void)a; return F_Chk_dP_dfresh(a[0]); }
static V L3595(V *a) {
return C1(1, C2(0, F_Chk_dPS_dqual(a[1], a[0]), a[1]));
}
static V F_Chk_dP_dqual(V a0) {
top:;
return mk_clo(L3595, 2, 1, (V[]){a0});
}
static V W_Chk_dP_dqual(V *a) { (void)a; return F_Chk_dP_dqual(a[0]); }
static V S3596(void) { static V c; return STRC(c, "type"); }
static V S3603(void) { static V c; return STRC(c, "<"); }
static V S3605(void) { static V c; return STRC(c, ">"); }
static V L3606(V *a) {
return F_Chk_dP_dtype_dgo(a[1], a[0], F_Pair_dfst(a[2]));
}
static V L3604(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[2], F_Chk_dP_dtele(S3605(), IMM(0), 0u), F_Chk_dP_dpure(C2(0, IMM(0), 0u))), mk_clo(L3606, 3, 2, (V[]){a[0], a[1]}));
}
static V L3602(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3603()), mk_clo(L3604, 3, 2, (V[]){a[0], a[1]}));
}
static V L3601(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3602, 3, 2, (V[]){a[1], a[0]}));
}
static V L3600(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3601, 2, 1, (V[]){a[0]}));
}
static V L3599(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dfresh(a[0]), mk_clo(L3600, 2, 1, (V[]){a[0]}));
}
static V L3598(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dqual(a[0]), mk_clo(L3599, 1, 0, 0));
}
static V L3597(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3598, 1, 0, 0));
}
static V F_Chk_dP_dtype(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(S3596()), mk_clo(L3597, 1, 0, 0));
}
static V W_Chk_dP_dtype(V *a) { (void)a; return F_Chk_dP_dtype(); }
static V S3607(void) { static V c; return STRC(c, "is"); }
static V S3609(void) { static V c; return STRC(c, "'is'"); }
static V S3612(void) { static V c; return STRC(c, ":"); }
static V L3621(V *a) {
return F_Chk_dP_dclose(a[0]);
}
static V L3620(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dset__book(F_Chk_dbook__push(F_Chk_dbook__set(a[6], a[5], CN(1, 5, (V[]){a[4], a[3], a[2], a[1], IMM(0)})), a[5])), mk_clo(L3621, 2, 1, (V[]){a[0]}));
}
static V L3619(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3620, 7, 6, (V[]){a[0], a[5], a[1], a[2], a[3], a[4]}));
}
static V L3618(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dctors(a[5], a[4], IMM(0)), mk_clo(L3619, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[5]}));
}
static V L3617(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dset__book(F_Chk_dbook__set(a[5], a[4], CN(1, 5, (V[]){a[3], a[6], a[2], IMM(0), IMM(0)}))), mk_clo(L3618, 7, 6, (V[]){a[0], a[2], a[6], a[3], a[1], a[4]}));
}
static V L3616(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_dTC_dfirst__typed(a[4])), mk_clo(L3617, 7, 6, (V[]){a[0], a[4], a[1], a[5], a[2], a[3]}));
}
static V L3615(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_List_dlength(a[3])), mk_clo(L3616, 6, 5, (V[]){a[0], a[4], a[1], a[2], a[3]}));
}
static V L3614(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_dhigher0(a[4], F_Chk_dtele__bind(a[3], a[2]))), mk_clo(L3615, 5, 4, (V[]){a[0], a[1], a[4], a[3]}));
}
static V L3613(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3614, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3611(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3612()), mk_clo(L3613, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V L3610(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3611, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3608(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[3], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dfail(S3609())), mk_clo(L3610, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dtype_dgo(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(S3607()), mk_clo(L3608, 4, 3, (V[]){a1, a0, a2}));
}
static V W_Chk_dP_dtype_dgo(V *a) { (void)a; return F_Chk_dP_dtype_dgo(a[0], a[1], a[2]); }
static V S3624(void) { static V c; return STRC(c, "def"); }
static V S3626(void) { static V c; return STRC(c, "type"); }
static V S3628(void) { static V c; return STRC(c, "law"); }
static V L3629(V *a) {
return F_Chk_dP_dif(F_Bool_dor(F_Bool_dnot(F_Chk_dis__head(a[5])), F_Bool_dor(a[4], F_Bool_dor(a[3], a[6]))), F_Chk_dP_dpure(a[2]), F_Chk_dP_dctor(a[1], a[0], a[2]));
}
static V L3627(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3628()), mk_clo(L3629, 7, 6, (V[]){a[0], a[1], a[2], a[5], a[3], a[4]}));
}
static V L3625(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3626()), mk_clo(L3627, 6, 5, (V[]){a[0], a[1], a[2], a[4], a[3]}));
}
static V L3623(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3624()), mk_clo(L3625, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3622(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3623, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dctors(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3622, 4, 3, (V[]){a1, a0, a2}));
}
static V W_Chk_dP_dctors(V *a) { (void)a; return F_Chk_dP_dctors(a[0], a[1], a[2]); }
static V S3633(void) { static V c; return STRC(c, "a fresh constructor name (duplicate declaration: "); }
static V S3634(void) { static V c; return STRC(c, ")"); }
static V S3636(void) { static V c; return STRC(c, "{"); }
static V S3639(void) { static V c; return STRC(c, "}"); }
static V L3645(V *a) {
return F_Chk_dP_dctors(a[3], a[2], F_List_dappend(a[1], C2(1, a[0], IMM(0))));
}
static V L3644(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dset__book(F_Chk_dbook__set__ctr(a[5], a[4], a[3])), mk_clo(L3645, 5, 4, (V[]){a[3], a[0], a[1], a[2]}));
}
static V L3643(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[5]), mk_clo(L3644, 7, 6, (V[]){a[0], a[1], a[2], a[6], a[3], a[4]}));
}
static V L3642(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(C3(0, a[5], F_List_dlength(a[4]), F_Chk_dhigher0(a[6], F_Chk_dtele__bind(F_List_dappend(a[3], a[4]), C4(14, a[2], F_Chk_dTC_dparams(a[3]), IMM(0), IMM(0)))))), mk_clo(L3643, 7, 6, (V[]){a[0], a[3], a[2], a[5], a[6], a[1]}));
}
static V L3641(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3642, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[5], a[4]}));
}
static V L3640(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Pair_dfst(a[5])), mk_clo(L3641, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L3638(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtele(S3639(), IMM(0), 0u), mk_clo(L3640, 6, 5, (V[]){a[0], a[4], a[1], a[2], a[3]}));
}
static V L3637(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3638, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3635(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3636()), mk_clo(L3637, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3632(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Maybe_dis__some(F_Chk_dbook__ctr(a[4], a[3])), F_Chk_dP_dfail(F_String_dappend(S3633(), F_String_dappend(a[3], S3634()))), F_Chk_dP_dpure(IMM(0))), mk_clo(L3635, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3631(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3632, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3630(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dqual(a[3]), mk_clo(L3631, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_dctor(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3630, 4, 3, (V[]){a2, a0, a1}));
}
static V W_Chk_dP_dctor(V *a) { (void)a; return F_Chk_dP_dctor(a[0], a[1], a[2]); }
static V F_Chk_dTC_dparams(V a0) {
top:;
V s3646 = a0;
if ((s3646) == IMM(0)) {
return IMM(0);
} else if (TAG(s3646) == 1) {
return C2(1, C3(0, FLD(FLD(s3646, 0), 1), FLD(FLD(s3646, 0), 2), IMM(0)), F_Chk_dTC_dparams(FLD(s3646, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dTC_dparams(V *a) { (void)a; return F_Chk_dTC_dparams(a[0]); }
static V F_Chk_dtele__bind(V a0, V a1) {
top:;
V s3647 = a0;
if ((s3647) == IMM(0)) {
return a1;
} else if (TAG(s3647) == 1) {
return CN(11, 6, (V[]){FLD(FLD(s3647, 0), 0), FLD(FLD(s3647, 0), 1), FLD(FLD(s3647, 0), 2), FLD(FLD(s3647, 0), 3), C3(24, IMM(0), FLD(FLD(s3647, 0), 2), F_Chk_dtele__bind(FLD(s3647, 1), a1)), FLD(FLD(s3647, 0), 4)});
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dtele__bind(V *a) { (void)a; return F_Chk_dtele__bind(a[0], a[1]); }
static V L3649(V *a) {
return F_Chk_dP_dif(a[3], F_Chk_dP_dpure(C2(0, a[2], a[1])), F_Chk_dP_dtele_done(a[0], a[2], a[1]));
}
static V L3648(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(a[2]), mk_clo(L3649, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V F_Chk_dP_dtele(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3648, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Chk_dP_dtele(V *a) { (void)a; return F_Chk_dP_dtele(a[0], a[1], a[2]); }
static V S3651(void) { static V c; return STRC(c, ")"); }
static V S3653(void) { static V c; return STRC(c, "~"); }
static V S3655(void) { static V c; return STRC(c, "a plain binder (only leading binders take ~)"); }
static V S3657(void) { static V c; return STRC(c, "~"); }
static V S3662(void) { static V c; return STRC(c, "a fresh field name (duplicate declaration: "); }
static V S3663(void) { static V c; return STRC(c, ")"); }
static V S3667(void) { static V c; return STRC(c, ":"); }
static V S3670(void) { static V c; return STRC(c, ":"); }
static V S3675(void) { static V c; return STRC(c, ","); }
static V L3676(V *a) {
return F_Chk_dP_dtele(a[9], F_List_dappend(a[8], C2(1, CN(0, 5, (V[]){F_Bool_dpick(a[7], IMM(0), a[6]), a[5], a[4], a[3], a[2]}), IMM(0))), F_Bool_dpick(a[1], nat_addk(a[0], 1), a[0]));
}
static V L3674(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3675()), mk_clo(L3676, 11, 10, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]}));
}
static V L3673(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3674, 11, 10, (V[]){a[0], a[1], a[2], a[3], a[9], a[4], a[5], a[6], a[7], a[8]}));
}
static V L3672(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dopen(a[7]), mk_clo(L3673, 10, 9, (V[]){a[0], a[1], a[2], a[8], a[7], a[3], a[4], a[5], a[6]}));
}
static V L3671(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[7], F_Chk_dP_dpure(C1(8, a[6])), F_Chk_dP_dterm0()), mk_clo(L3672, 9, 8, (V[]){a[0], a[1], a[6], a[2], a[7], a[3], a[4], a[5]}));
}
static V L3669(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[7], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_deat(S3670())), mk_clo(L3671, 9, 8, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]}));
}
static V L3668(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Bool_dand(F_Chk_dQ_dis__lone(a[6]), F_Bool_dnot(a[7]))), mk_clo(L3669, 8, 7, (V[]){a[0], a[1], a[6], a[2], a[3], a[4], a[5]}));
}
static V L3666(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S3667()), mk_clo(L3668, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V L3665(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3666, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[6], a[5]}));
}
static V L3664(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dspan(a[6]), mk_clo(L3665, 7, 6, (V[]){a[0], a[1], a[2], a[3], a[4], a[5]}));
}
static V L3661(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Bool_dand(F_Bool_dnot(a[6]), F_Chk_dStr_dhas(F_Chk_dTC_dnames(a[5]), a[7])), F_Chk_dP_dfail(F_String_dappend(S3662(), F_String_dappend(a[7], S3663()))), F_Chk_dP_dpure(IMM(0))), mk_clo(L3664, 8, 7, (V[]){a[0], a[1], a[5], a[2], a[7], a[3], a[4]}));
}
static V L3660(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3661, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[6], a[4], a[5]}));
}
static V L3659(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpos(), mk_clo(L3660, 7, 6, (V[]){a[0], a[1], a[2], a[5], a[3], a[4]}));
}
static V L3658(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[4], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dquant()), mk_clo(L3659, 6, 5, (V[]){a[0], a[4], a[1], a[2], a[3]}));
}
static V L3656(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[3], F_Chk_dP_dtake(S3657()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3658, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3654(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Bool_dand(F_Bool_dand(a[4], a[5]), F_Nat_dis__lt(a[3], a[2])), F_Chk_dP_dfail(S3655()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3656, 5, 4, (V[]){a[3], a[0], a[1], a[4]}));
}
static V F_Chk_dP_dtele_done(V a0, V a1, V a2) {
top:;
V v3650 = F_String_deq(a0, S3651());
V v3652 = F_List_dlength(a1);
return F_Chk_dP_dbind(F_Chk_dP_dat(S3653()), mk_clo(L3654, 6, 5, (V[]){a0, a1, v3652, a2, v3650}));
}
static V W_Chk_dP_dtele_done(V *a) { (void)a; return F_Chk_dP_dtele_done(a[0], a[1], a[2]); }
static V F_Chk_dTC_dnames(V a0) {
top:;
V s3677 = a0;
if ((s3677) == IMM(0)) {
return IMM(0);
} else if (TAG(s3677) == 1) {
return C2(1, F_Chk_dTC_dk(FLD(s3677, 0)), F_Chk_dTC_dnames(FLD(s3677, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dTC_dnames(V *a) { (void)a; return F_Chk_dTC_dnames(a[0]); }
static V F_Chk_dTC_dk(V a0) {
top:;
V v3678 = a0;
return FLD(v3678, 1);
}
static V W_Chk_dTC_dk(V *a) { (void)a; return F_Chk_dTC_dk(a[0]); }
static V F_Chk_dTC_dfirst__typed(V a0) {
top:;
V s3679 = a0;
if ((s3679) == IMM(0)) {
return 0u;
} else if (TAG(s3679) == 1 && TAG(FLD(FLD(s3679, 0), 3)) == 8) {
return nat_addk(F_Chk_dTC_dfirst__typed(FLD(s3679, 1)), 1);
} else if (TAG(s3679) == 1) {
return 0u;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dTC_dfirst__typed(V *a) { (void)a; return F_Chk_dTC_dfirst__typed(a[0]); }
static V S3680(void) { static V c; return STRC(c, "def"); }
static V S3689(void) { static V c; return STRC(c, "("); }
static V S3692(void) { static V c; return STRC(c, "~"); }
static V S3694(void) { static V c; return STRC(c, "a name"); }
static V S3696(void) { static V c; return STRC(c, ")"); }
static V L3698(V *a) {
return F_Chk_dP_ddef_dgo(a[4], a[3], a[2], a[1], a[0]);
}
static V L3697(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3698, 6, 5, (V[]){a[4], a[0], a[1], a[2], a[3]}));
}
static V L3695(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dtele(S3696(), IMM(0), 0u), mk_clo(L3697, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3693(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Bool_dand(a[3], a[4]), F_Chk_dP_dfail(S3694()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3695, 5, 4, (V[]){a[0], a[3], a[1], a[2]}));
}
static V L3691(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat(S3692()), mk_clo(L3693, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3690(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3691, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3688(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3689()), mk_clo(L3690, 5, 4, (V[]){a[3], a[0], a[1], a[2]}));
}
static V L3687(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dstn(), mk_clo(L3688, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3686(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[1], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dfresh(a[2])), mk_clo(L3687, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L3685(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[3], F_Chk_dP_dpure(a[2]), F_Chk_dP_dqual(a[1])), mk_clo(L3686, 3, 2, (V[]){a[0], a[3]}));
}
static V L3684(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_dTld_dopen__law(F_Chk_dbook__tld(a[3], a[2]))), mk_clo(L3685, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3683(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3684, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L3682(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dreso(a[1]), mk_clo(L3683, 3, 2, (V[]){a[0], a[1]}));
}
static V L3681(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dname(), mk_clo(L3682, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_ddef(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(S3680()), mk_clo(L3681, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_ddef(V *a) { (void)a; return F_Chk_dP_ddef(a[0]); }
static V F_Chk_dP_ddef_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V v3699 = a4;
V v3700 = FLD(v3699, 0);
return F_Chk_dP_dif(a2, F_Chk_dP_ddef_dfill(a0, a1, a3, v3700), F_Chk_dP_ddef_dnew(a0, a1, a3, v3700, FLD(v3699, 1)));
}
static V W_Chk_dP_ddef_dgo(V *a) { (void)a; return F_Chk_dP_ddef_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V S3701(void) { static V c; return STRC(c, "->"); }
static V S3703(void) { static V c; return STRC(c, "'->' (a def with no return type fills a law; no law named "); }
static V S3704(void) { static V c; return STRC(c, " is in scope)"); }
static V L3708(V *a) {
return F_Chk_dP_ddef_dbody(a[2], a[1], a[0]);
}
static V L3707(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dset__book(F_Chk_dbook__set(a[6], a[5], CN(0, 7, (V[]){F_List_dlength(a[4]), a[3], F_Chk_dhigher0(a[6], F_Chk_dtele__bind(a[4], a[2])), IMM(0), a[1], IMM(0), IMM(0)}))), mk_clo(L3708, 4, 3, (V[]){a[4], a[0], a[5]}));
}
static V L3706(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3707, 7, 6, (V[]){a[0], a[1], a[5], a[2], a[3], a[4]}));
}
static V L3705(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dterm0(), mk_clo(L3706, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V L3702(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[5], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dfail(F_String_dappend(S3703(), F_String_dappend(a[4], S3704())))), mk_clo(L3705, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V F_Chk_dP_ddef_dnew(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dtake(S3701()), mk_clo(L3702, 6, 5, (V[]){a2, a0, a4, a3, a1}));
}
static V W_Chk_dP_ddef_dnew(V *a) { (void)a; return F_Chk_dP_ddef_dnew(a[0], a[1], a[2], a[3], a[4]); }
static V S3709(void) { static V c; return STRC(c, ":"); }
static V S3711(void) { static V c; return STRC(c, "import"); }
static V L3715(V *a) {
return F_Chk_dP_dset__book(F_Chk_dbook__push(a[1], a[0]));
}
static V L3714(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3715, 2, 1, (V[]){a[0]}));
}
static V L3713(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dclose(a[1]), mk_clo(L3714, 2, 1, (V[]){a[0]}));
}
static V L3712(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[3], F_Chk_dP_ddef_dforeign(a[2]), F_Chk_dP_ddef_dvalue(a[2], a[1])), mk_clo(L3713, 3, 2, (V[]){a[2], a[0]}));
}
static V L3710(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3711()), mk_clo(L3712, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Chk_dP_ddef_dbody(V a0, V a1, V a2) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_deat(S3709()), mk_clo(L3710, 4, 3, (V[]){a1, a2, a0}));
}
static V W_Chk_dP_ddef_dbody(V *a) { (void)a; return F_Chk_dP_ddef_dbody(a[0], a[1], a[2]); }
static V L3719(V *a) {
return F_Chk_dP_dset__book(F_Chk_dbook__set(a[2], a[1], F_Chk_dTld_dwith__v(F_Chk_dbook__tld(a[2], a[1]), F_Chk_dhigher0(a[2], F_Chk_dterm__lower(a[2], F_Chk_dhigher0(a[2], a[0]), 0u)))));
}
static V L3718(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dcheck__ops(a[1]), mk_clo(L3719, 4, 3, (V[]){a[1], a[0], a[2]}));
}
static V L3717(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3718, 3, 2, (V[]){a[0], a[1]}));
}
static V L3716(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dflatten(a[2], F_Chk_dTC_dvars(a[1])), mk_clo(L3717, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_ddef_dvalue(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbody(0u), mk_clo(L3716, 3, 2, (V[]){a0, a1}));
}
static V W_Chk_dP_ddef_dvalue(V *a) { (void)a; return F_Chk_dP_ddef_dvalue(a[0], a[1]); }
static V F_Chk_dTld_dwith__v(V a0, V a1) {
top:;
V s3720 = a0;
if (TAG(s3720) == 1 && TAG(FLD(s3720, 0)) == 0) {
return CN(0, 7, (V[]){FLD(FLD(s3720, 0), 0), FLD(FLD(s3720, 0), 1), FLD(FLD(s3720, 0), 2), C1(1, a1), FLD(FLD(s3720, 0), 4), FLD(FLD(s3720, 0), 5), FLD(FLD(s3720, 0), 6)});
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
V s3721 = a0;
if (TAG(s3721) == 4) {
return F_Bool_dpick(F_Nat_dis__eq(F_Chk_dStr_dlast__dot(FLD(s3721, 0)), 0u), C1(1, C3(4, FLD(s3721, 0), FLD(s3721, 1), FLD(s3721, 2))), IMM(0));
} else if (TAG(s3721) == 5) {
{ V t0 = FLD(s3721, 2); a0 = t0; goto top; }
} else if (TAG(s3721) == 6) {
return F_Chk_dops_dfirst(F_Chk_dops_dbares(FLD(s3721, 2)), F_Chk_dops_dbare(F_Chk_dsyn__body(FLD(s3721, 3))));
} else if (TAG(s3721) == 7) {
{ V t0 = FLD(s3721, 0); a0 = t0; goto top; }
} else if (TAG(s3721) == 10) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3721, 0)), F_Chk_dops_dbare(FLD(s3721, 1)));
} else if (TAG(s3721) == 11) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3721, 3)), F_Chk_dops_dbare(F_Chk_dsyn__body(FLD(s3721, 4))));
} else if (TAG(s3721) == 12) {
{ V t0 = F_Chk_dsyn__body(FLD(s3721, 2)); a0 = t0; goto top; }
} else if (TAG(s3721) == 13) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3721, 0)), F_Chk_dops_dbare(FLD(s3721, 1)));
} else if (TAG(s3721) == 14) {
return F_Chk_dops_dbares(FLD(s3721, 1));
} else if (TAG(s3721) == 15) {
return F_Chk_dops_dbares(FLD(s3721, 1));
} else if (TAG(s3721) == 17) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3721, 1)), F_Chk_dops_dbare(FLD(s3721, 2)));
} else if (TAG(s3721) == 19) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3721, 0)), F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3721, 1)), F_Chk_dops_dbare(FLD(s3721, 2))));
} else if (TAG(s3721) == 21) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3721, 0)), F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3721, 1)), F_Chk_dops_dbare(FLD(s3721, 2))));
} else if (TAG(s3721) == 23) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3721, 0)), F_Chk_dops_dbare(FLD(s3721, 1)));
} else if (TAG(s3721) == 3) {
{ V t0 = FLD(s3721, 3); a0 = t0; goto top; }
} else {
return IMM(0);
}
}
static V W_Chk_dops_dbare(V *a) { (void)a; return F_Chk_dops_dbare(a[0]); }
static V F_Chk_dops_dfirst(V a0, V a1) {
top:;
V s3722 = a0;
if (TAG(s3722) == 1) {
return C1(1, FLD(s3722, 0));
} else if ((s3722) == IMM(0)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dops_dfirst(V *a) { (void)a; return F_Chk_dops_dfirst(a[0], a[1]); }
static V F_Chk_dops_dbares(V a0) {
top:;
V s3723 = a0;
if ((s3723) == IMM(0)) {
return IMM(0);
} else if (TAG(s3723) == 1) {
return F_Chk_dops_dfirst(F_Chk_dops_dbare(FLD(s3723, 0)), F_Chk_dops_dbares(FLD(s3723, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dops_dbares(V *a) { (void)a; return F_Chk_dops_dbares(a[0]); }
static V F_Chk_dP_dcheck__ops_dc(V a0) {
top:;
V s3724 = a0;
if ((s3724) == IMM(0)) {
return F_Chk_dP_dpure(IMM(0));
} else if (TAG(s3724) == 1) {
return F_Chk_dP_dthrow(F_Chk_dops_derr(FLD(s3724, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dP_dcheck__ops_dc(V *a) { (void)a; return F_Chk_dP_dcheck__ops_dc(a[0]); }
static V S3726(void) { static V c; return STRC(c, "a type for this operator (write (a "); }
static V S3727(void) { static V c; return STRC(c, " b : Nat))"); }
static V S3728(void) { static V c; return STRC(c, ""); }
static V S3729(void) { static V c; return STRC(c, "Note: we broke this after launch, sorry. Until 2.0.16 a bare operator meant Nat.\012"); }
static V S3730(void) { static V c; return STRC(c, "That was a bug: operators demand annotation. Wrap the expression and it'll work again."); }
static V S3731(void) { static V c; return STRC(c, "a type for this operator"); }
static V F_Chk_dops_derr(V a0) {
top:;
V s3725 = a0;
if (TAG(s3725) == 4) {
return CN(0, 7, (V[]){F_Chk_dbook__nil(), IMM(0), C1(1, F_String_dappend(S3726(), F_String_dappend(F_Chk_dops_dtext(FLD(s3725, 1), FLD(s3725, 0)), S3727()))), IMM(0), FLD(s3725, 1), S3728(), F_String_dappend(S3729(), S3730())});
} else {
return F_Chk_derr0(S3731(), IMM(0), IMM(0));
}
}
static V W_Chk_dops_derr(V *a) { (void)a; return F_Chk_dops_derr(a[0]); }
static V F_Chk_dops_dtext(V a0, V a1) {
top:;
V s3732 = a0;
if (TAG(s3732) == 1) {
return F_String_dtake(F_String_ddrop(FLD(s3732, 0), F_U32_dto__nat(FLD(s3732, 1))), F_Nat_dsub(F_U32_dto__nat(FLD(s3732, 2)), F_U32_dto__nat(FLD(s3732, 1))));
} else if ((s3732) == IMM(0)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dops_dtext(V *a) { (void)a; return F_Chk_dops_dtext(a[0], a[1]); }
static V F_Chk_dTC_dvars(V a0) {
top:;
V s3733 = a0;
if ((s3733) == IMM(0)) {
return IMM(0);
} else if (TAG(s3733) == 1) {
return C2(1, C4(0, FLD(FLD(s3733, 0), 1), FLD(FLD(s3733, 0), 2), IMM(1), FLD(FLD(s3733, 0), 4)), F_Chk_dTC_dvars(FLD(s3733, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dTC_dvars(V *a) { (void)a; return F_Chk_dTC_dvars(a[0]); }
static V S3735(void) { static V c; return STRC(c, "a body (a template is not foreign)"); }
static V L3738(V *a) {
return F_Chk_dP_dset__book(F_Chk_dbook__set(a[2], a[1], F_Chk_dTld_dwith__imps(F_Chk_dbook__tld(a[2], a[1]), a[0])));
}
static V L3737(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3738, 3, 2, (V[]){a[1], a[0]}));
}
static V L3736(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dimports(IMM(0)), mk_clo(L3737, 2, 1, (V[]){a[0]}));
}
static V L3734(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Nat_dis__gt(F_Chk_dTld_dlaw__x(F_Chk_dbook__tld(a[1], a[0])), 0u), F_Chk_dP_dfail(S3735()), F_Chk_dP_dpure(IMM(0))), mk_clo(L3736, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_ddef_dforeign(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3734, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_ddef_dforeign(V *a) { (void)a; return F_Chk_dP_ddef_dforeign(a[0]); }
static V F_Chk_dTld_dwith__imps(V a0, V a1) {
top:;
V s3739 = a0;
if (TAG(s3739) == 1 && TAG(FLD(s3739, 0)) == 0) {
return CN(0, 7, (V[]){FLD(FLD(s3739, 0), 0), FLD(FLD(s3739, 0), 1), FLD(FLD(s3739, 0), 2), FLD(FLD(s3739, 0), 3), FLD(FLD(s3739, 0), 4), FLD(FLD(s3739, 0), 5), C1(1, a1)});
} else {
return CN(0, 7, (V[]){0u, 0u, C1(8, IMM(0)), IMM(0), IMM(0), IMM(0), C1(1, a1)});
}
}
static V W_Chk_dTld_dwith__imps(V *a) { (void)a; return F_Chk_dTld_dwith__imps(a[0], a[1]); }
static V S3740(void) { static V c; return STRC(c, "import"); }
static V L3741(V *a) {
return F_Chk_dP_dif(a[1], F_Chk_dP_dimport1(a[0]), F_Chk_dP_dpure(a[0]));
}
static V F_Chk_dP_dimports(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(S3740()), mk_clo(L3741, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dimports(V *a) { (void)a; return F_Chk_dP_dimports(a[0]); }
static V S3742(void) { static V c; return STRC(c, "\042"); }
static V S3744(void) { static V c; return STRC(c, ""); }
static V S3746(void) { static V c; return STRC(c, "\042"); }
static V S3748(void) { static V c; return STRC(c, ".c"); }
static V S3749(void) { static V c; return STRC(c, ".js"); }
static V S3750(void) { static V c; return STRC(c, "a .c or .js path"); }
static V L3752(V *a) {
return F_Chk_dP_dimports(F_List_dappend(a[1], C2(1, F_String_dappend(a[2], a[0]), IMM(0))));
}
static V L3751(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_ddir(), mk_clo(L3752, 3, 2, (V[]){a[0], a[1]}));
}
static V L3747(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Bool_dor(F_String_dends__with(a[1], S3748()), F_String_dends__with(a[1], S3749())), F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dfail(S3750())), mk_clo(L3751, 3, 2, (V[]){a[1], a[0]}));
}
static V L3745(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_deat(S3746()), mk_clo(L3747, 3, 2, (V[]){a[0], a[1]}));
}
static V L3743(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_duntil__quote(S3744()), mk_clo(L3745, 2, 1, (V[]){a[0]}));
}
static V F_Chk_dP_dimport1(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_deat(S3742()), mk_clo(L3743, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_dimport1(V *a) { (void)a; return F_Chk_dP_dimport1(a[0]); }
static V L3753(V *a) {
return C1(1, C2(0, F_Chk_dPS_ddir(a[0]), a[0]));
}
static V F_Chk_dP_ddir(void) {
top:;
return mk_clo(L3753, 1, 0, 0);
}
static V W_Chk_dP_ddir(V *a) { (void)a; return F_Chk_dP_ddir(); }
static V F_Chk_dPS_ddir(V a0) {
top:;
V v3754 = a0;
return FLD(v3754, 7);
}
static V W_Chk_dPS_ddir(V *a) { (void)a; return F_Chk_dPS_ddir(a[0]); }
static V L3755(V *a) {
return F_Chk_dP_dif(F_Bool_dor(F_U32_dis__eq(a[1], 34u), F_U32_dis__zero(a[1])), F_Chk_dP_dpure(F_String_dreverse(a[0])), F_Chk_dP_duntil__quote_dmore(a[1], a[0]));
}
static V F_Chk_dP_duntil__quote(V a0) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dpeek(), mk_clo(L3755, 2, 1, (V[]){a0}));
}
static V W_Chk_dP_duntil__quote(V *a) { (void)a; return F_Chk_dP_duntil__quote(a[0]); }
static V L3756(V *a) {
return F_Chk_dP_duntil__quote(C2(1, a[1], a[0]));
}
static V F_Chk_dP_duntil__quote_dmore(V a0, V a1) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbump(), mk_clo(L3756, 3, 2, (V[]){a1, a0}));
}
static V W_Chk_dP_duntil__quote_dmore(V *a) { (void)a; return F_Chk_dP_duntil__quote_dmore(a[0], a[1]); }
static V F_Chk_dTld_dlaw__x(V a0) {
top:;
V s3757 = a0;
if (TAG(s3757) == 1 && TAG(FLD(s3757, 0)) == 0) {
return FLD(FLD(s3757, 0), 1);
} else {
return 0u;
}
}
static V W_Chk_dTld_dlaw__x(V *a) { (void)a; return F_Chk_dTld_dlaw__x(a[0]); }
static V S3760(void) { static V c; return STRC(c, "a name"); }
static V S3762(void) { static V c; return STRC(c, "a name for each ~ clause of the law ("); }
static V S3763(void) { static V c; return STRC(c, ")"); }
static V L3766(V *a) {
return F_Chk_dP_ddef_dbody(a[2], a[1], a[0]);
}
static V L3765(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dset__book(F_Chk_dbook__set(a[4], a[3], F_Chk_dTld_dlaw__fill(F_Chk_dbook__tld(a[4], a[3]), F_List_dlength(a[2]), a[1]))), mk_clo(L3766, 4, 3, (V[]){a[2], a[0], a[3]}));
}
static V L3764(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3765, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V L3761(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Nat_dis__lt(F_List_dlength(a[4]), a[3]), F_Chk_dP_dfail(F_String_dappend(S3762(), F_String_dappend(F_Nat_dshow(a[3]), S3763()))), F_Chk_dP_dpure(IMM(0))), mk_clo(L3764, 5, 4, (V[]){a[0], a[1], a[4], a[2]}));
}
static V L3759(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(F_Chk_dTC_dall__qnt(a[3]), F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dfail(S3760())), mk_clo(L3761, 6, 5, (V[]){a[0], a[1], a[2], a[4], a[3]}));
}
static V L3758(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dpure(F_Chk_dTld_dlaw__x(F_Chk_dbook__tld(a[4], a[3]))), mk_clo(L3759, 5, 4, (V[]){a[0], a[1], a[3], a[2]}));
}
static V F_Chk_dP_ddef_dfill(V a0, V a1, V a2, V a3) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dbook(), mk_clo(L3758, 5, 4, (V[]){a2, a0, a3, a1}));
}
static V W_Chk_dP_ddef_dfill(V *a) { (void)a; return F_Chk_dP_ddef_dfill(a[0], a[1], a[2], a[3]); }
static V F_Chk_dTld_dlaw__fill(V a0, V a1, V a2) {
top:;
V s3767 = a0;
if (TAG(s3767) == 1 && TAG(FLD(s3767, 0)) == 0) {
return CN(0, 7, (V[]){a1, FLD(FLD(s3767, 0), 1), FLD(FLD(s3767, 0), 2), FLD(FLD(s3767, 0), 3), F_Bool_dor(FLD(FLD(s3767, 0), 4), a2), FLD(FLD(s3767, 0), 5), FLD(FLD(s3767, 0), 6)});
} else {
return CN(0, 7, (V[]){a1, 0u, C1(8, IMM(0)), IMM(0), a2, IMM(0), IMM(0)});
}
}
static V W_Chk_dTld_dlaw__fill(V *a) { (void)a; return F_Chk_dTld_dlaw__fill(a[0], a[1], a[2]); }
static V F_Chk_dTC_dall__qnt(V a0) {
top:;
V s3768 = a0;
if ((s3768) == IMM(0)) {
return IMM(1);
} else if (TAG(s3768) == 1 && TAG(FLD(FLD(s3768, 0), 3)) == 8) {
{ V t0 = FLD(s3768, 1); a0 = t0; goto top; }
} else if (TAG(s3768) == 1) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dTC_dall__qnt(V *a) { (void)a; return F_Chk_dTC_dall__qnt(a[0]); }
static V F_Chk_dTld_dopen__law(V a0) {
top:;
V s3769 = a0;
if (TAG(s3769) == 1 && TAG(FLD(s3769, 0)) == 0 && (FLD(FLD(s3769, 0), 3)) == IMM(0) && (FLD(FLD(s3769, 0), 5)) == IMM(0) && (FLD(FLD(s3769, 0), 6)) == IMM(0)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_Chk_dTld_dopen__law(V *a) { (void)a; return F_Chk_dTld_dopen__law(a[0]); }
static V S3770(void) { static V c; return STRC(c, "unsafe"); }
static V S3772(void) { static V c; return STRC(c, "'unsafe' (the one decorator)"); }
static V S3775(void) { static V c; return STRC(c, "def"); }
static V S3777(void) { static V c; return STRC(c, "'def' (@unsafe marks the def below it)"); }
static V L3776(V *a) {
return F_Chk_dP_dif(a[0], F_Chk_dP_ddef(IMM(1)), F_Chk_dP_dfail(S3777()));
}
static V L3774(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dat__word(S3775()), mk_clo(L3776, 1, 0, 0));
}
static V L3773(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dskip(), mk_clo(L3774, 1, 0, 0));
}
static V L3771(V *a) {
return F_Chk_dP_dbind(F_Chk_dP_dif(a[0], F_Chk_dP_dpure(IMM(0)), F_Chk_dP_dfail(S3772())), mk_clo(L3773, 1, 0, 0));
}
static V F_Chk_dP_dunsafe(void) {
top:;
return F_Chk_dP_dbind(F_Chk_dP_dword(S3770()), mk_clo(L3771, 1, 0, 0));
}
static V W_Chk_dP_dunsafe(V *a) { (void)a; return F_Chk_dP_dunsafe(); }
static V L3778(V *a) {
return C1(1, C2(0, IMM(0), F_Chk_dPS_dset__scope(a[0], IMM(0), 0u, 0u)));
}
static V F_Chk_dP_dreset__scope(void) {
top:;
return mk_clo(L3778, 1, 0, 0);
}
static V W_Chk_dP_dreset__scope(V *a) { (void)a; return F_Chk_dP_dreset__scope(); }
static V F_Chk_dPS_dset__scope(V a0, V a1, V a2, V a3) {
top:;
V v3779 = a0;
return CN(0, 9, (V[]){FLD(v3779, 0), a1, a2, a3, FLD(v3779, 4), FLD(v3779, 5), FLD(v3779, 6), FLD(v3779, 7), FLD(v3779, 8)});
}
static V W_Chk_dPS_dset__scope(V *a) { (void)a; return F_Chk_dPS_dset__scope(a[0], a[1], a[2], a[3]); }
static V F_Chk_dparse__file_dfin(V a0) {
top:;
V s3780 = a0;
if (TAG(s3780) == 0) {
return C1(0, FLD(s3780, 0));
} else if (TAG(s3780) == 1) {
return C1(1, F_Chk_dPS_dbook(F_Pair_dsnd(FLD(s3780, 0))));
} else { bend_fail("incomplete match"); }
}
static V W_Chk_dparse__file_dfin(V *a) { (void)a; return F_Chk_dparse__file_dfin(a[0]); }
static V F_Main_dchk_dparsed(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s3781 = a5;
if (TAG(s3781) == 0) {
return F_Main_dchk_dfail(FLD(s3781, 0));
} else if (TAG(s3781) == 1) {
return F_IO_dpure(C3(0, F_Bool_dpick(F_String_deq(F_Path_dnorm(a1), F_Path_dnorm(a0)), F_Chk_dmark__base(FLD(s3781, 0), a4), FLD(s3781, 0)), C2(1, C2(0, F_Path_dnorm(a1), a2), a3), a4));
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
V s3782 = a0;
if ((s3782) == IMM(0)) {
return a3;
} else if (TAG(s3782) == 1) {
{ V t0 = FLD(s3782, 1); V t1 = nat_addk(a1, 1); V t2 = a2; V t3 = F_Bool_dpick(F_Nat_dis__ge(a1, a2), F_Chk_dmark__base_done(a3, FLD(s3782, 0)), a3); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
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
V s3783 = a2;
if (TAG(s3783) == 1 && TAG(FLD(s3783, 0)) == 0) {
return F_Chk_dbook__set(a0, a1, CN(0, 7, (V[]){FLD(FLD(s3783, 0), 0), FLD(FLD(s3783, 0), 1), FLD(FLD(s3783, 0), 2), FLD(FLD(s3783, 0), 3), FLD(FLD(s3783, 0), 4), IMM(1), FLD(FLD(s3783, 0), 6)}));
} else if (TAG(s3783) == 1 && TAG(FLD(s3783, 0)) == 1) {
return F_Chk_dbook__set(a0, a1, CN(1, 5, (V[]){FLD(FLD(s3783, 0), 0), FLD(FLD(s3783, 0), 1), FLD(FLD(s3783, 0), 2), FLD(FLD(s3783, 0), 3), IMM(1)}));
} else if ((s3783) == IMM(0)) {
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
V v3784 = a0;
return C3(0, FLD(v3784, 0), C2(1, C2(0, a1, F_Main_dchk_dloading()), FLD(v3784, 1)), FLD(v3784, 2));
}
static V W_CS_dmark(V *a) { (void)a; return F_CS_dmark(a[0], a[1]); }
static V S3785(void) { static V c; return STRC(c, "u{0}"); }
static V F_Main_dchk_dloading(void) {
top:;
return S3785();
}
static V W_Main_dchk_dloading(V *a) { (void)a; return F_Main_dchk_dloading(); }
static V L3787(V *a) {
return F_Main_dchk_dimps_dnext(a[5], a[4], a[3], a[2], a[1], a[0], a[6]);
}
static V F_Main_dchk_dimps(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s3786 = a5;
if ((s3786) == IMM(0)) {
return F_IO_dpure(C2(0, a6, a7));
} else if (TAG(s3786) == 1) {
return F_IO_dbind(F_Main_dchk_dimp(a0, a1, a2, a3, a4, FLD(s3786, 0), a6, a7), mk_clo(L3787, 7, 6, (V[]){FLD(s3786, 1), a4, a3, a2, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dimps(V *a) { (void)a; return F_Main_dchk_dimps(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V F_Main_dchk_dimps_dnext(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V v3788 = a6;
return F_Main_dchk_dimps(a0, a1, a2, a3, a4, a5, FLD(v3788, 0), FLD(v3788, 1));
}
static V W_Main_dchk_dimps_dnext(V *a) { (void)a; return F_Main_dchk_dimps_dnext(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Main_dchk_dimp(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V v3789 = a5;
V v3790 = C3(1, a4, FLD(v3789, 2), FLD(v3789, 2));
V v3791 = F_Path_dnorm(FLD(v3789, 0));
return F_Main_dchk_dimp_dgo(a0, a1, a2, a3, v3790, v3791, FLD(v3789, 1), FLD(v3789, 0), a6, a7, F_String_dis__empty(FLD(v3789, 1)));
}
static V W_Main_dchk_dimp(V *a) { (void)a; return F_Main_dchk_dimp(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S3793(void) { static V c; return STRC(c, ""); }
static V L3794(V *a) {
return F_IO_dpure(C2(0, a[1], a[0]));
}
static V S3795(void) { static V c; return STRC(c, ".bend"); }
static V F_Main_dchk_dimp_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10) {
top:;
V s3792 = a10;
if ((s3792) == IMM(1)) {
return F_IO_dbind(F_Main_dchk_dload(a0, a1, a1, S3793(), a4, a8), mk_clo(L3794, 2, 1, (V[]){a9}));
} else if ((s3792) == IMM(0)) {
return F_Main_dchk_dimp_drel(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, F_String_dends__with(a5, S3795()));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dimp_dgo(V *a) { (void)a; return F_Main_dchk_dimp_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10]); }
static V S3797(void) { static V c; return STRC(c, "an import of a .bend file"); }
static V S3798(void) { static V c; return STRC(c, "'"); }
static V S3799(void) { static V c; return STRC(c, "'"); }
static V S3801(void) { static V c; return STRC(c, "/"); }
static V L3806(V *a) {
return F_IO_dpure(C2(0, a[3], F_List_dappend(a[2], C2(1, C2(0, a[1], a[0]), IMM(0)))));
}
static V L3805(V *a) {
return F_IO_dbind(F_Main_dchk_dload(a[6], a[5], a[7], a[4], a[3], a[2]), mk_clo(L3806, 4, 3, (V[]){a[4], a[0], a[1]}));
}
static V F_Main_dchk_dimp_drel(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8, V a9, V a10) {
top:;
V s3796 = a10;
if ((s3796) == IMM(0)) {
return F_Main_dchk_dfail(F_Chk_derr0(S3797(), C1(1, F_String_dappend(S3798(), F_String_dappend(a7, S3799()))), a4));
} else if ((s3796) == IMM(1)) {
V v3800 = F_String_dstarts__with(a5, S3801());
V v3802 = F_Main_dchk_dis__hub(a5);
V v3803 = F_Bool_dpick(F_Bool_dor(v3800, v3802), a5, F_Path_djoin(F_Path_ddirname(a3), a5));
V v3804 = F_String_dtake(v3803, F_Nat_dsub(F_String_dlength(v3803), 5u));
return F_IO_dbind(F_Bool_dpick(v3802, F_Main_dchk_dhub(a5), F_IO_dpure(F_Bool_dpick(v3800, a5, F_String_dappend(a2, a5)))), mk_clo(L3805, 8, 7, (V[]){a6, a9, a8, a4, v3804, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dimp_drel(V *a) { (void)a; return F_Main_dchk_dimp_drel(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10]); }
static V S3808(void) { static V c; return STRC(c, "BEND_HUB"); }
static V S3811(void) { static V c; return STRC(c, "/"); }
static V L3810(V *a) {
return F_IO_dpure(F_String_dappend(a[1], F_String_dappend(S3811(), a[0])));
}
static V L3809(V *a) {
return F_IO_dbind(F_IO_dtry(F_Hub_densure(a[1], F_Main_dhub_durl(a[2]), a[0])), mk_clo(L3810, 3, 2, (V[]){a[0], a[1]}));
}
static V L3807(V *a) {
return F_IO_dbind(F_IO_dget__env(S3808()), mk_clo(L3809, 3, 2, (V[]){a[0], a[1]}));
}
static V F_Main_dchk_dhub(V a0) {
top:;
return F_IO_dbind(F_Main_dlib(), mk_clo(L3807, 2, 1, (V[]){a0}));
}
static V W_Main_dchk_dhub(V *a) { (void)a; return F_Main_dchk_dhub(a[0]); }
static V S3813(void) { static V c; return STRC(c, "."); }
static V S3814(void) { static V c; return STRC(c, "/"); }
static V S3815(void) { static V c; return STRC(c, "/"); }
static V F_Path_ddirname(V a0) {
top:;
V v3812 = F_Mod_ddir(a0);
return F_Bool_dpick(F_String_dis__empty(v3812), S3813(), F_Bool_dpick(F_String_deq(v3812, S3814()), S3815(), F_String_dtake(v3812, F_Nat_dsub(F_String_dlength(v3812), 1u))));
}
static V W_Path_ddirname(V *a) { (void)a; return F_Path_ddirname(a[0]); }
static V S3816(void) { static V c; return STRC(c, "/"); }
static V F_Path_djoin(V a0, V a1) {
top:;
return F_Path_dnorm(F_String_dappend(a0, F_String_dappend(S3816(), a1)));
}
static V W_Path_djoin(V *a) { (void)a; return F_Path_djoin(a[0], a[1]); }
static V S3817(void) { static V c; return STRC(c, "0x"); }
static V F_Main_dchk_dis__hub(V a0) {
top:;
return F_Bool_dand(F_String_dstarts__with(a0, S3817()), F_Main_dchk_dis__hub_dhex(F_String_ddrop(a0, 2u)));
}
static V W_Main_dchk_dis__hub(V *a) { (void)a; return F_Main_dchk_dis__hub(a[0]); }
static V F_Main_dchk_dis__hub_dhex(V a0) {
top:;
V s3818 = a0;
if (TAG(s3818) == 1) {
return F_Bool_dor(F_U32_dis__eq(FLD(s3818, 0), 47u), F_Bool_dand(F_Bool_dor(F_Char_dis__digit(FLD(s3818, 0)), F_Bool_dand(F_U32_dis__ge(FLD(s3818, 0), 97u), F_U32_dis__le(FLD(s3818, 0), 102u))), F_Main_dchk_dis__hub_dhex(FLD(s3818, 1))));
} else if ((s3818) == IMM(0)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Main_dchk_dis__hub_dhex(V *a) { (void)a; return F_Main_dchk_dis__hub_dhex(a[0]); }
static V S3819(void) { static V c; return STRC(c, "r"); }
static V L3820(V *a) {
return F_Main_dread__opt_dopen(a[0]);
}
static V F_Main_dread__opt(V a0) {
top:;
return F_IO_dbind(F_File_dopen(a0, S3819()), mk_clo(L3820, 1, 0, 0));
}
static V W_Main_dread__opt(V *a) { (void)a; return F_Main_dread__opt(a[0]); }
static V L3822(V *a) {
return F_Main_dread__opt_dfin(a[0]);
}
static V F_Main_dread__opt_dopen(V a0) {
top:;
V s3821 = a0;
if (TAG(s3821) == 1) {
return F_IO_dbind(F_IO_dread__all(FLD(s3821, 0)), mk_clo(L3822, 1, 0, 0));
} else if (TAG(s3821) == 0) {
return F_IO_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dread__opt_dopen(V *a) { (void)a; return F_Main_dread__opt_dopen(a[0]); }
static V L3824(V *a) {
return F_IO_dpure(F_Main_dread__opt_dres(a[0]));
}
static V F_Main_dread__opt_dfin(V a0) {
top:;
V v3823 = a0;
return F_IO_dbind(F_File_dclose(FLD(v3823, 0)), mk_clo(L3824, 2, 1, (V[]){FLD(v3823, 1)}));
}
static V W_Main_dread__opt_dfin(V *a) { (void)a; return F_Main_dread__opt_dfin(a[0]); }
static V F_Main_dread__opt_dres(V a0) {
top:;
V s3825 = a0;
if (TAG(s3825) == 1) {
return C1(1, FLD(s3825, 0));
} else if (TAG(s3825) == 0) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Main_dread__opt_dres(V *a) { (void)a; return F_Main_dread__opt_dres(a[0]); }
static V F_CS_dat__end(V a0) {
top:;
V v3826 = a0;
return C3(0, FLD(v3826, 0), FLD(v3826, 1), F_Chk_dbook__len(FLD(v3826, 0)));
}
static V W_CS_dat__end(V *a) { (void)a; return F_CS_dat__end(a[0]); }
static V S3829(void) { static V c; return STRC(c, "All terms check.\012"); }
static V F_Main_dcheck__only_dfin(V a0) {
top:;
V v3827 = a0;
V v3828 = F_Chk_dreport(FLD(v3827, 0), FLD(v3827, 1));
return F_Bool_dpick(F_List_dis__empty(v3828), F_IO_dwrite(S3829()), F_IO_dwrite(F_Chk_dreport__text(v3828)));
}
static V W_Main_dcheck__only_dfin(V *a) { (void)a; return F_Main_dcheck__only_dfin(a[0]); }
static V S3831(void) { static V c; return STRC(c, "bendc: parse error: "); }
static V F_Main_dast(V a0) {
top:;
V s3830 = a0;
if (TAG(s3830) == 0) {
return F_IO_ddie(1u, F_String_dappend(S3831(), FLD(s3830, 0)));
} else if (TAG(s3830) == 1) {
return F_IO_dwrite(F_Decls_dshow(FLD(s3830, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dast(V *a) { (void)a; return F_Main_dast(a[0]); }
static V F_Decls_dshow(V a0) {
top:;
return F_Decls_dshow_dgo(a0);
}
static V W_Decls_dshow(V *a) { (void)a; return F_Decls_dshow(a[0]); }
static V S3833(void) { static V c; return STRC(c, ""); }
static V S3834(void) { static V c; return STRC(c, "\012"); }
static V F_Decls_dshow_dgo(V a0) {
top:;
V s3832 = a0;
if ((s3832) == IMM(0)) {
return S3833();
} else if (TAG(s3832) == 1) {
return F_String_dappend(F_Decl_dshow(FLD(s3832, 0)), F_String_dappend(S3834(), F_Decls_dshow_dgo(FLD(s3832, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Decls_dshow_dgo(V *a) { (void)a; return F_Decls_dshow_dgo(a[0]); }
static V S3836(void) { static V c; return STRC(c, "def "); }
static V S3837(void) { static V c; return STRC(c, "("); }
static V S3838(void) { static V c; return STRC(c, ") = "); }
static V S3839(void) { static V c; return STRC(c, "eff "); }
static V S3840(void) { static V c; return STRC(c, "("); }
static V S3841(void) { static V c; return STRC(c, ")"); }
static V S3842(void) { static V c; return STRC(c, "law "); }
static V S3843(void) { static V c; return STRC(c, "("); }
static V S3844(void) { static V c; return STRC(c, ")"); }
static V S3845(void) { static V c; return STRC(c, "type "); }
static V S3846(void) { static V c; return STRC(c, " "); }
static V S3847(void) { static V c; return STRC(c, "import "); }
static V S3848(void) { static V c; return STRC(c, " as "); }
static V F_Decl_dshow(V a0) {
top:;
V s3835 = a0;
if (TAG(s3835) == 0) {
return F_String_dappend(S3836(), F_String_dappend(FLD(s3835, 0), F_String_dappend(S3837(), F_String_dappend(F_Params_dshow(FLD(s3835, 1)), F_String_dappend(S3838(), F_Expr_dshow(FLD(s3835, 2)))))));
} else if (TAG(s3835) == 1) {
return F_String_dappend(S3839(), F_String_dappend(FLD(s3835, 0), F_String_dappend(S3840(), F_String_dappend(F_Params_dshow(FLD(s3835, 1)), S3841()))));
} else if (TAG(s3835) == 2) {
return F_String_dappend(S3842(), F_String_dappend(FLD(s3835, 0), F_String_dappend(S3843(), F_String_dappend(F_Params_dshow(FLD(s3835, 1)), S3844()))));
} else if (TAG(s3835) == 3) {
return F_String_dappend(S3845(), F_String_dappend(FLD(s3835, 0), F_String_dappend(S3846(), F_Ctors_dshow(FLD(s3835, 2)))));
} else if (TAG(s3835) == 4) {
return F_String_dappend(S3847(), F_String_dappend(FLD(s3835, 0), F_String_dappend(S3848(), FLD(s3835, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Decl_dshow(V *a) { (void)a; return F_Decl_dshow(a[0]); }
static V S3850(void) { static V c; return STRC(c, ""); }
static V S3851(void) { static V c; return STRC(c, " "); }
static V F_Ctors_dshow(V a0) {
top:;
V s3849 = a0;
if ((s3849) == IMM(0)) {
return S3850();
} else if (TAG(s3849) == 1) {
return F_String_dappend(F_Ctor_dshow(FLD(s3849, 0)), F_String_dappend(S3851(), F_Ctors_dshow(FLD(s3849, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Ctors_dshow(V *a) { (void)a; return F_Ctors_dshow(a[0]); }
static V S3853(void) { static V c; return STRC(c, "{"); }
static V S3854(void) { static V c; return STRC(c, "}"); }
static V F_Ctor_dshow(V a0) {
top:;
V v3852 = a0;
return F_String_dappend(FLD(v3852, 0), F_String_dappend(S3853(), F_String_dappend(F_Fields_dshow(FLD(v3852, 1)), S3854())));
}
static V W_Ctor_dshow(V *a) { (void)a; return F_Ctor_dshow(a[0]); }
static V S3856(void) { static V c; return STRC(c, ""); }
static V S3857(void) { static V c; return STRC(c, ":"); }
static V S3858(void) { static V c; return STRC(c, " "); }
static V F_Fields_dshow(V a0) {
top:;
V s3855 = a0;
if ((s3855) == IMM(0)) {
return S3856();
} else if (TAG(s3855) == 1) {
return F_String_dappend(FLD(FLD(s3855, 0), 0), F_String_dappend(S3857(), F_String_dappend(F_Expr_dshow(FLD(FLD(s3855, 0), 1)), F_String_dappend(S3858(), F_Fields_dshow(FLD(s3855, 1))))));
} else { bend_fail("incomplete match"); }
}
static V W_Fields_dshow(V *a) { (void)a; return F_Fields_dshow(a[0]); }
static V S3860(void) { static V c; return STRC(c, ""); }
static V S3861(void) { static V c; return STRC(c, " "); }
static V F_Params_dshow(V a0) {
top:;
V s3859 = a0;
if ((s3859) == IMM(0)) {
return S3860();
} else if (TAG(s3859) == 1) {
return F_String_dappend(F_Param_dshow(FLD(s3859, 0)), F_String_dappend(S3861(), F_Params_dshow(FLD(s3859, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Params_dshow(V *a) { (void)a; return F_Params_dshow(a[0]); }
static V S3863(void) { static V c; return STRC(c, ":"); }
static V F_Param_dshow(V a0) {
top:;
V v3862 = a0;
return F_String_dappend(F_U32_dshow(FLD(v3862, 1)), F_String_dappend(FLD(v3862, 0), F_String_dappend(S3863(), FLD(v3862, 2))));
}
static V W_Param_dshow(V *a) { (void)a; return F_Param_dshow(a[0]); }
static V S3865(void) { static V c; return STRC(c, ""); }
static V F_Toks_dshow(V a0) {
top:;
V s3864 = a0;
if ((s3864) == IMM(0)) {
return S3865();
} else if (TAG(s3864) == 1) {
return F_String_dappend(F_Tok_dshow(FLD(s3864, 0)), F_Toks_dshow(FLD(s3864, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Toks_dshow(V *a) { (void)a; return F_Toks_dshow(a[0]); }
static V S3867(void) { static V c; return STRC(c, " "); }
static V S3868(void) { static V c; return STRC(c, ""); }
static V F_Tok_dshow(V a0) {
top:;
V v3866 = a0;
return F_String_dappend(F_Bool_dpick(FLD(v3866, 1), S3867(), S3868()), F_TK_dshow(FLD(v3866, 0)));
}
static V W_Tok_dshow(V *a) { (void)a; return F_Tok_dshow(a[0]); }
static V E_IO_dprint(V *a) { return io_req(CID_IO_PRINT, 2, (V[]){a[0], a[2]}); }
static V F_IO_dprint(V a0) { return mk_clo(E_IO_dprint, 3, 1, (V[]){a0}); }
static V W_IO_dprint(V *a) { (void)a; return F_IO_dprint(a[0]); }
static V E_IO_dargs(V *a) { return io_req(CID_IO_ARGS, 1, (V[]){a[1]}); }
static V F_IO_dargs(void) { return mk_clo(E_IO_dargs, 2, 0, 0); }
static V W_IO_dargs(V *a) { (void)a; return F_IO_dargs(); }

int main(int argc, char **argv) { return bend_run(argc, argv, F_main); }

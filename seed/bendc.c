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
static V W_U32_dis__eq(V *a);
static V F_String_dsplit_dfin(V a0, V a1, V a2);
static V W_String_dsplit_dfin(V *a);
static V F_String_dsplit_dpush(V a0, V a1);
static V W_String_dsplit_dpush(V *a);
static V F_Lex_dlines_dgo(V a0, V a1);
static V W_Lex_dlines_dgo(V *a);
static V W_U32_dinc(V *a);
static V F_Lex_dline(V a0, V a1, V a2, V a3);
static V W_Lex_dline(V *a);
static V F_Lex_dclass(V a0);
static V W_Lex_dclass(V *a);
static V F_Bool_dpick(V a1, V a2, V a3);
static V W_Bool_dpick(V *a);
static V F_Char_dis__digit(V a0);
static V W_Char_dis__digit(V *a);
static V W_U32_dis__le(V *a);
static V W_U32_dis__ge(V *a);
static V F_Bool_dand(V a0, V a1);
static V W_Bool_dand(V *a);
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
static V F_Bool_dor(V a0, V a1);
static V W_Bool_dor(V *a);
static V F_Lex_dline_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Lex_dline_dgo(V *a);
static V F_Lex_dop__of(V a0);
static V W_Lex_dop__of(V *a);
static V F_Lex_dops3(void);
static V S26(void);
static V S27(void);
static V S28(void);
static V S29(void);
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
static V S36(void);
static V S37(void);
static V S38(void);
static V S39(void);
static V S40(void);
static V S41(void);
static V S42(void);
static V S43(void);
static V S44(void);
static V S45(void);
static V S46(void);
static V S47(void);
static V S48(void);
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
static V W_U32_dadd(V *a);
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
static V S74(void);
static V W_Lex_dline_dflt(V *a);
static V F_String_dappend(V a0, V a1);
static V W_String_dappend(V *a);
static V F_U32_dshow(V a0);
static V W_U32_dshow(V *a);
static V W_U32_dis__zero(V *a);
static V F_U32_dshow_dif(V a0, V a1);
static V W_U32_dshow_dif(V *a);
static V F_U32_dshow_dgo(V a0, V a1, V a2);
static V W_U32_dshow_dgo(V *a);
static V F_U32_dshow_dfin(V a0, V a1, V a2, V a3);
static V W_U32_dshow_dfin(V *a);
static V W_U32_dmod(V *a);
static V W_U32_ddiv(V *a);
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
static V S97(void);
static V W_Lay_dtoks(V *a);
static V F_Lay_dis__op(V a0);
static V S99(void);
static V S100(void);
static V S101(void);
static V S102(void);
static V S103(void);
static V S104(void);
static V S105(void);
static V S106(void);
static V S107(void);
static V S108(void);
static V S109(void);
static V S110(void);
static V S111(void);
static V W_Lay_dis__op(V *a);
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
static V F_List_dcontains(V a1, V a2, V a3);
static V W_List_dcontains(V *a);
static V F_Lay_dis__sym(V a0, V a1);
static V W_Lay_dis__sym(V *a);
static V F_Str_deq(V a0, V a1);
static V W_Str_deq(V *a);
static V F_Lay_ddelta(V a0);
static V S123(void);
static V S124(void);
static V S125(void);
static V S126(void);
static V S127(void);
static V S128(void);
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
static V W_U32_dis__gt(V *a);
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
static V L140(V *a);
static V L141(V *a);
static V W_P_ddecls(V *a);
static V F_P_dtok__kind(V a0);
static V W_P_dtok__kind(V *a);
static V F_P_dstuck(V a0);
static V W_P_dstuck(V *a);
static V F_P_ddecls_dgo(V a0);
static V L145(V *a);
static V L146(V *a);
static V W_P_ddecls_dgo(V *a);
static V F_Parser_dpure(V a1);
static V L147(V *a);
static V W_Parser_dpure(V *a);
static V F_Parser_dbind(V a2, V a3);
static V L148(V *a);
static V W_Parser_dbind(V *a);
static V F_Parser_dgo(V a2, V a3);
static V W_Parser_dgo(V *a);
static V F_P_ddecl(void);
static V L150(V *a);
static V S151(void);
static V W_P_ddecl(V *a);
static V F_P_dtok__is(V a0, V a1);
static V W_P_dtok__is(V *a);
static V F_P_ddecl_dat(V a0, V a1);
static V L154(V *a);
static V L155(V *a);
static V L156(V *a);
static V S157(void);
static V S158(void);
static V S159(void);
static V S160(void);
static V W_P_ddecl_dat(V *a);
static V F_P_dtok__which__id(V a0, V a1);
static V W_P_dtok__which__id(V *a);
static V F_P_dwhich(V a0, V a1);
static V W_P_dwhich(V *a);
static V F_P_dwhich_dif(V a0, V a1, V a2);
static V W_P_dwhich_dif(V *a);
static V F_P_ddecl_dgo(V a0);
static V S165(void);
static V L166(V *a);
static V S167(void);
static V S168(void);
static V W_P_ddecl_dgo(V *a);
static V F_P_derr(V a0);
static V L169(V *a);
static V W_P_derr(V *a);
static V F_P_derr_dgo(V a0, V a1);
static V S171(void);
static V S172(void);
static V S173(void);
static V S174(void);
static V S175(void);
static V W_P_derr_dgo(V *a);
static V F_TK_dshow(V a0);
static V S177(void);
static V S178(void);
static V S179(void);
static V S180(void);
static V S181(void);
static V S182(void);
static V S183(void);
static V S184(void);
static V S185(void);
static V S186(void);
static V S187(void);
static V S188(void);
static V W_TK_dshow(V *a);
static V F_P_dimport(void);
static V L189(V *a);
static V L190(V *a);
static V L191(V *a);
static V S192(void);
static V L193(V *a);
static V L194(V *a);
static V W_P_dimport(V *a);
static V F_P_dskip__line(void);
static V L195(V *a);
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
static V L201(V *a);
static V S202(void);
static V W_P_dimport_dalias(V *a);
static V F_P_dident(void);
static V L203(V *a);
static V W_P_dident(V *a);
static V F_P_dident_dk(V a0);
static V L205(V *a);
static V S206(void);
static V L207(V *a);
static V S208(void);
static V W_P_dident_dk(V *a);
static V F_P_dskip(void);
static V L209(V *a);
static V W_P_dskip(V *a);
static V F_P_dskip_dgo(V a0);
static V W_P_dskip_dgo(V *a);
static V F_P_dskip_dif(V a0, V a1, V a2);
static V W_P_dskip_dif(V *a);
static V F_P_dpeek(void);
static V L212(V *a);
static V W_P_dpeek(V *a);
static V F_P_dpeek_dgo(V a0);
static V W_P_dpeek_dgo(V *a);
static V F_P_deof__tok(void);
static V W_P_deof__tok(V *a);
static V F_P_dimport_dpath(void);
static V L214(V *a);
static V W_P_dimport_dpath(V *a);
static V F_P_dimport_dpath_dgo(V a0);
static V S216(void);
static V S217(void);
static V W_P_dimport_dpath_dgo(V *a);
static V F_P_dimport_dpath_dcat(V a0, V a1);
static V W_P_dimport_dpath_dcat(V *a);
static V F_P_dimport_dpath_did(V a0, V a1, V a2, V a3, V a4);
static V S220(void);
static V W_P_dimport_dpath_did(V *a);
static V F_P_dlaw(void);
static V L221(V *a);
static V L222(V *a);
static V S223(void);
static V L224(V *a);
static V L225(V *a);
static V L226(V *a);
static V W_P_dlaw(V *a);
static V F_P_dlaw_dlines(void);
static V L227(V *a);
static V L228(V *a);
static V W_P_dlaw_dlines(V *a);
static V F_P_dis__de(V a0);
static V W_P_dis__de(V *a);
static V F_P_dlaw_dgo(V a0, V a1);
static V L231(V *a);
static V S232(void);
static V W_P_dlaw_dgo(V *a);
static V F_P_dlaw_dline(V a0);
static V L234(V *a);
static V L235(V *a);
static V L236(V *a);
static V L237(V *a);
static V L238(V *a);
static V W_P_dlaw_dline(V *a);
static V F_P_dparam(void);
static V L239(V *a);
static V L240(V *a);
static V L241(V *a);
static V L242(V *a);
static V L243(V *a);
static V S244(void);
static V W_P_dparam(V *a);
static V F_P_dparam_dty(V a0, V a1, V a2);
static V L246(V *a);
static V L247(V *a);
static V S248(void);
static V W_P_dparam_dty(V *a);
static V F_P_dhead(V a0);
static V S250(void);
static V W_P_dhead(V *a);
static V F_P_dexpr(void);
static V W_P_dexpr(V *a);
static V F_P_dbin(V a0);
static V L251(V *a);
static V W_P_dbin(V *a);
static V F_P_dbin_dloop(V a0, V a1);
static V L252(V *a);
static V W_P_dbin_dloop(V *a);
static V F_P_dtok__op(V a0);
static V S254(void);
static V W_P_dtok__op(V *a);
static V F_P_dops(void);
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
static V S265(void);
static V S266(void);
static V S267(void);
static V S268(void);
static V S269(void);
static V S270(void);
static V S271(void);
static V S272(void);
static V S273(void);
static V S274(void);
static V S275(void);
static V S276(void);
static V W_P_dops(V *a);
static V F_P_dop__find(V a0, V a1);
static V S278(void);
static V W_P_dop__find(V *a);
static V F_P_dop__find_dif(V a0, V a1, V a2, V a3);
static V W_P_dop__find_dif(V *a);
static V F_P_dbin_dloop_dop(V a0, V a1, V a2);
static V W_P_dbin_dloop_dop(V *a);
static V W_U32_dis__ne(V *a);
static V F_P_dbin_dloop_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V L282(V *a);
static V L283(V *a);
static V W_P_dbin_dloop_dgo(V *a);
static V F_P_dmk__bin(V a0, V a1, V a2);
static V S284(void);
static V S285(void);
static V S286(void);
static V S287(void);
static V S288(void);
static V S289(void);
static V S290(void);
static V S291(void);
static V W_P_dmk__bin(V *a);
static V F_P_dmk__bin_dgo(V a0, V a1, V a2, V a3);
static V S293(void);
static V S294(void);
static V S295(void);
static V S296(void);
static V S297(void);
static V S298(void);
static V S299(void);
static V S300(void);
static V W_P_dmk__bin_dgo(V *a);
static V F_P_dterm(void);
static V L301(V *a);
static V W_P_dterm(V *a);
static V F_P_dpostfix(V a0);
static V L302(V *a);
static V W_P_dpostfix(V *a);
static V F_P_dpostfix_dt(V a0, V a1);
static V S303(void);
static V S304(void);
static V S305(void);
static V W_P_dpostfix_dt(V *a);
static V F_P_dtok__which(V a0, V a1);
static V W_P_dtok__which(V *a);
static V F_P_dtok__sp(V a0);
static V W_P_dtok__sp(V *a);
static V F_P_dpostfix_dk(V a0, V a1);
static V L309(V *a);
static V S310(void);
static V L311(V *a);
static V L312(V *a);
static V L313(V *a);
static V L314(V *a);
static V S315(void);
static V L316(V *a);
static V S317(void);
static V S318(void);
static V W_P_dpostfix_dk(V *a);
static V F_P_dexpect(V a0);
static V L319(V *a);
static V W_P_dexpect(V *a);
static V F_P_dexpect_dif(V a0, V a1);
static V S321(void);
static V S322(void);
static V W_P_dexpect_dif(V *a);
static V F_P_dlist(V a0);
static V L323(V *a);
static V W_P_dlist(V *a);
static V F_P_dlist_dstuck(V a0, V a1, V a2);
static V S325(void);
static V L326(V *a);
static V W_P_dlist_dstuck(V *a);
static V F_P_dlist_dgo(V a0, V a1);
static V L328(V *a);
static V W_P_dlist_dgo(V *a);
static V F_P_dlist_ditem(V a0);
static V L329(V *a);
static V S330(void);
static V L331(V *a);
static V L332(V *a);
static V W_P_dlist_ditem(V *a);
static V F_P_dlist_dmore(V a0, V a1);
static V L334(V *a);
static V W_P_dlist_dmore(V *a);
static V F_P_deat(V a0);
static V L335(V *a);
static V W_P_deat(V *a);
static V F_P_deat_dif(V a0);
static V L337(V *a);
static V W_P_deat_dif(V *a);
static V F_P_dprimary(void);
static V L338(V *a);
static V W_P_dprimary(V *a);
static V F_P_dprimary_dk(V a0);
static V L340(V *a);
static V L341(V *a);
static V L342(V *a);
static V L343(V *a);
static V L344(V *a);
static V L345(V *a);
static V L346(V *a);
static V L347(V *a);
static V L348(V *a);
static V S349(void);
static V S350(void);
static V S351(void);
static V S352(void);
static V S353(void);
static V S354(void);
static V S355(void);
static V S356(void);
static V S357(void);
static V S358(void);
static V L359(V *a);
static V S360(void);
static V W_P_dprimary_dk(V *a);
static V F_P_dprimary_dsym(V a0);
static V L362(V *a);
static V L363(V *a);
static V L364(V *a);
static V L365(V *a);
static V L366(V *a);
static V L367(V *a);
static V L368(V *a);
static V L369(V *a);
static V L370(V *a);
static V S371(void);
static V S372(void);
static V L373(V *a);
static V S374(void);
static V W_P_dprimary_dsym(V *a);
static V F_P_damp_dgo(V a0);
static V L376(V *a);
static V S377(void);
static V W_P_damp_dgo(V *a);
static V F_P_ddep(void);
static V S378(void);
static V L379(V *a);
static V S380(void);
static V L381(V *a);
static V L382(V *a);
static V S383(void);
static V L384(V *a);
static V L385(V *a);
static V S386(void);
static V W_P_ddep(V *a);
static V F_P_dneg(V a0);
static V S388(void);
static V W_P_dneg(V *a);
static V F_P_dbrace(void);
static V L389(V *a);
static V L390(V *a);
static V S391(void);
static V W_P_dbrace(V *a);
static V F_P_dbrace_dgo(V a0);
static V L393(V *a);
static V S394(void);
static V L395(V *a);
static V S396(void);
static V W_P_dbrace_dgo(V *a);
static V F_P_dbrace_dbody(void);
static V L397(V *a);
static V L398(V *a);
static V S399(void);
static V S400(void);
static V S401(void);
static V W_P_dbrace_dbody(V *a);
static V F_P_dbrace_dtail(V a0, V a1);
static V L403(V *a);
static V L404(V *a);
static V S405(void);
static V L406(V *a);
static V L407(V *a);
static V S408(void);
static V L409(V *a);
static V S410(void);
static V L411(V *a);
static V L412(V *a);
static V S413(void);
static V L414(V *a);
static V L415(V *a);
static V S416(void);
static V L417(V *a);
static V S418(void);
static V L419(V *a);
static V L420(V *a);
static V S421(void);
static V L422(V *a);
static V S423(void);
static V L424(V *a);
static V W_P_dbrace_dtail(V *a);
static V F_P_dbrack(void);
static V L425(V *a);
static V L426(V *a);
static V S427(void);
static V W_P_dbrack(V *a);
static V F_P_dbrack_dgo(V a0);
static V L429(V *a);
static V S430(void);
static V W_P_dbrack_dgo(V *a);
static V F_P_dbrack_dbody(void);
static V L431(V *a);
static V L432(V *a);
static V S433(void);
static V W_P_dbrack_dbody(V *a);
static V F_P_dbrack_dtail(V a0, V a1);
static V S435(void);
static V L436(V *a);
static V S437(void);
static V L438(V *a);
static V W_P_dbrack_dtail(V *a);
static V F_P_delist(V a0);
static V S440(void);
static V S441(void);
static V W_P_delist(V *a);
static V F_P_darr(V a0);
static V L442(V *a);
static V L443(V *a);
static V L444(V *a);
static V L445(V *a);
static V L446(V *a);
static V S447(void);
static V L448(V *a);
static V S449(void);
static V L450(V *a);
static V S451(void);
static V S452(void);
static V W_P_darr(V *a);
static V F_P_darr_dsize(V a0, V a1);
static V W_P_darr_dsize(V *a);
static V F_P_darr_dsize_dlit(V a0);
static V L455(V *a);
static V S456(void);
static V L457(V *a);
static V W_P_darr_dsize_dlit(V *a);
static V F_P_dlog2(V a0);
static V W_P_dlog2(V *a);
static V W_U32_dlog2(V *a);
static V W_U32_dfrom__nat(V *a);
static V F_P_dparen(void);
static V L458(V *a);
static V L459(V *a);
static V S460(void);
static V W_P_dparen(V *a);
static V F_P_dparen_dgo(V a0);
static V L462(V *a);
static V S463(void);
static V W_P_dparen_dgo(V *a);
static V F_P_dparen_dbody(void);
static V L464(V *a);
static V L465(V *a);
static V S466(void);
static V S467(void);
static V W_P_dparen_dbody(V *a);
static V F_P_dparen_dtail(V a0, V a1);
static V L469(V *a);
static V S470(void);
static V L471(V *a);
static V L472(V *a);
static V L473(V *a);
static V S474(void);
static V L475(V *a);
static V S476(void);
static V L477(V *a);
static V W_P_dparen_dtail(V *a);
static V F_P_dtuple(V a0);
static V S479(void);
static V S480(void);
static V W_P_dtuple(V *a);
static V F_P_dafter__id(V a0, V a1);
static V S481(void);
static V S482(void);
static V S483(void);
static V W_P_dafter__id(V *a);
static V F_P_dafter__id_dgo(V a0, V a1, V a2);
static V L485(V *a);
static V L486(V *a);
static V W_P_dafter__id_dgo(V *a);
static V F_P_dafter__id_dk(V a0, V a1);
static V L488(V *a);
static V S489(void);
static V L490(V *a);
static V L491(V *a);
static V L492(V *a);
static V W_P_dafter__id_dk(V *a);
static V F_P_dtyargs(void);
static V L493(V *a);
static V W_P_dtyargs(V *a);
static V F_P_dtyargs_dgo(V a0, V a1);
static V W_P_dtyargs_dgo(V *a);
static V F_P_dis__gt(V a0);
static V S495(void);
static V S496(void);
static V S497(void);
static V W_P_dis__gt(V *a);
static V F_P_dtyargs_dclose(V a0);
static V L499(V *a);
static V W_P_dtyargs_dclose(V *a);
static V F_P_dtyargs_ditem(void);
static V L500(V *a);
static V S501(void);
static V L502(V *a);
static V L503(V *a);
static V W_P_dtyargs_ditem(V *a);
static V F_P_dtyargs_dmore(V a0);
static V L505(V *a);
static V W_P_dtyargs_dmore(V *a);
static V F_P_dgt(void);
static V L506(V *a);
static V W_P_dgt(V *a);
static V F_P_dgt_dgo(V a0);
static V S508(void);
static V S509(void);
static V S510(void);
static V S511(void);
static V W_P_dgt_dgo(V *a);
static V F_P_dgt_dif(V a0, V a1, V a2, V a3, V a4);
static V S513(void);
static V S514(void);
static V S515(void);
static V W_P_dgt_dif(V *a);
static V F_P_dparam_dskip__mode(V a0);
static V W_P_dparam_dskip__mode(V *a);
static V F_P_dparam_dskip__mode_dgo(V a0);
static V W_P_dparam_dskip__mode_dgo(V *a);
static V F_P_dparam_dmode(V a0);
static V S517(void);
static V S518(void);
static V S519(void);
static V W_P_dparam_dmode(V *a);
static V F_P_dnls(void);
static V L520(V *a);
static V W_P_dnls(V *a);
static V F_P_dis__nl(V a0);
static V W_P_dis__nl(V *a);
static V F_P_dnls_dif(V a0);
static V L523(V *a);
static V W_P_dnls_dif(V *a);
static V F_P_dexpect__in(void);
static V L524(V *a);
static V W_P_dexpect__in(V *a);
static V F_P_dis__in(V a0);
static V W_P_dis__in(V *a);
static V F_P_dexpect__in_dgo(V a0);
static V S527(void);
static V W_P_dexpect__in_dgo(V *a);
static V F_P_dtype(void);
static V L528(V *a);
static V L529(V *a);
static V L530(V *a);
static V S531(void);
static V S532(void);
static V L533(V *a);
static V L534(V *a);
static V L535(V *a);
static V S536(void);
static V L537(V *a);
static V L538(V *a);
static V L539(V *a);
static V W_P_dtype(V *a);
static V F_P_dtype_dbody(V a0);
static V L541(V *a);
static V W_P_dtype_dbody(V *a);
static V F_P_dctors(void);
static V L542(V *a);
static V L543(V *a);
static V W_P_dctors(V *a);
static V F_P_dctors_dgo(V a0, V a1);
static V L545(V *a);
static V L546(V *a);
static V S547(void);
static V L548(V *a);
static V L549(V *a);
static V L550(V *a);
static V W_P_dctors_dgo(V *a);
static V F_P_dfields(void);
static V L551(V *a);
static V S552(void);
static V W_P_dfields(V *a);
static V F_P_dfields_dgo(V a0);
static V L554(V *a);
static V S555(void);
static V L556(V *a);
static V S557(void);
static V L558(V *a);
static V L559(V *a);
static V S560(void);
static V L561(V *a);
static V L562(V *a);
static V S563(void);
static V L564(V *a);
static V L565(V *a);
static V W_P_dfields_dgo(V *a);
static V F_P_duntil__is(void);
static V L566(V *a);
static V W_P_duntil__is(V *a);
static V F_P_duntil__is_dgo(V a0);
static V S568(void);
static V W_P_duntil__is_dgo(V *a);
static V F_P_duntil__is_dif(V a0, V a1, V a2);
static V W_P_duntil__is_dif(V *a);
static V F_P_dtparams_dopt(V a0);
static V L571(V *a);
static V L572(V *a);
static V W_P_dtparams_dopt(V *a);
static V F_P_dtparams(void);
static V S573(void);
static V L574(V *a);
static V L575(V *a);
static V L576(V *a);
static V S577(void);
static V L578(V *a);
static V L579(V *a);
static V W_P_dtparams(V *a);
static V F_P_dtparams_dmore(V a0);
static V L581(V *a);
static V W_P_dtparams_dmore(V *a);
static V F_P_dskip__ann(void);
static V L582(V *a);
static V S583(void);
static V W_P_dskip__ann(V *a);
static V F_P_dskip__ann_dgo(V a0);
static V L585(V *a);
static V L586(V *a);
static V W_P_dskip__ann_dgo(V *a);
static V F_P_ddef(void);
static V L587(V *a);
static V L588(V *a);
static V S589(void);
static V L590(V *a);
static V L591(V *a);
static V L592(V *a);
static V S593(void);
static V L594(V *a);
static V S595(void);
static V L596(V *a);
static V L597(V *a);
static V L598(V *a);
static V S599(void);
static V W_P_ddef(V *a);
static V F_P_ddef_dbody(V a0, V a1, V a2, V a3);
static V L601(V *a);
static V L602(V *a);
static V W_P_ddef_dbody(V *a);
static V F_Fold_dplain(V a0);
static V S604(void);
static V S605(void);
static V S606(void);
static V W_Fold_dplain(V *a);
static V F_P_dstmts(void);
static V L607(V *a);
static V L608(V *a);
static V W_P_dstmts(V *a);
static V F_P_dstmts_dgo(V a0, V a1);
static V L610(V *a);
static V L611(V *a);
static V L612(V *a);
static V W_P_dstmts_dgo(V *a);
static V F_List_dappend(V a2, V a3);
static V W_List_dappend(V *a);
static V F_P_dstmt(void);
static V L614(V *a);
static V S615(void);
static V W_P_dstmt(V *a);
static V F_P_dstmt_dgo(V a0, V a1);
static V L617(V *a);
static V S618(void);
static V S619(void);
static V S620(void);
static V W_P_dstmt_dgo(V *a);
static V F_P_dstmt_did(V a0);
static V L622(V *a);
static V L623(V *a);
static V L624(V *a);
static V L625(V *a);
static V L626(V *a);
static V W_P_dstmt_did(V *a);
static V F_P_dstmt_dscan(V a0);
static V W_P_dstmt_dscan(V *a);
static V W_U32_dto__nat(V *a);
static V F_P_dstmt_dscan_dgo(V a0);
static V L628(V *a);
static V W_P_dstmt_dscan_dgo(V *a);
static V F_P_dbind__stmt(void);
static V S629(void);
static V L630(V *a);
static V L631(V *a);
static V L632(V *a);
static V S633(void);
static V W_P_dbind__stmt(V *a);
static V F_Bool_dnot(V a0);
static V W_Bool_dnot(V *a);
static V F_P_dbind_darr(V a0, V a1);
static V L636(V *a);
static V L637(V *a);
static V S638(void);
static V L639(V *a);
static V S640(void);
static V L641(V *a);
static V L642(V *a);
static V S643(void);
static V S644(void);
static V L645(V *a);
static V S646(void);
static V L647(V *a);
static V L648(V *a);
static V W_P_dbind_darr(V *a);
static V F_P_dlet__stmt(void);
static V S649(void);
static V S650(void);
static V L651(V *a);
static V L652(V *a);
static V S653(void);
static V L654(V *a);
static V L655(V *a);
static V W_P_dlet__stmt(V *a);
static V F_P_dlets_dpar(V a0, V a1);
static V S656(void);
static V S657(void);
static V W_P_dlets_dpar(V *a);
static V F_P_dlets(V a0, V a1);
static V W_P_dlets(V *a);
static V F_List_dlength(V a2);
static V W_List_dlength(V *a);
static V W_Nat_dis__gt(V *a);
static V F_P_dexprs__n(V a0);
static V L662(V *a);
static V L663(V *a);
static V W_P_dexprs__n(V *a);
static V F_P_dpat__seq(V a0);
static V L664(V *a);
static V W_P_dpat__seq(V *a);
static V F_P_dpat__seq_dstop(V a0, V a1);
static V W_P_dpat__seq_dstop(V *a);
static V W_Nat_dis__lt(V *a);
static V F_P_dpat__seq_dgo(V a0, V a1, V a2);
static V L666(V *a);
static V L667(V *a);
static V W_P_dpat__seq_dgo(V *a);
static V F_P_dpat(void);
static V L668(V *a);
static V L669(V *a);
static V S670(void);
static V W_P_dpat(V *a);
static V F_P_dpat_dcons(V a0, V a1);
static V L672(V *a);
static V L673(V *a);
static V S674(void);
static V W_P_dpat_dcons(V *a);
static V F_P_dpat1(void);
static V L675(V *a);
static V W_P_dpat1(V *a);
static V F_P_dpat1_dk(V a0);
static V L677(V *a);
static V L678(V *a);
static V S679(void);
static V L680(V *a);
static V L681(V *a);
static V L682(V *a);
static V L683(V *a);
static V L684(V *a);
static V L685(V *a);
static V S686(void);
static V S687(void);
static V S688(void);
static V S689(void);
static V S690(void);
static V L691(V *a);
static V S692(void);
static V W_P_dpat1_dk(V *a);
static V F_P_dpat_dsym(V a0);
static V L694(V *a);
static V L695(V *a);
static V L696(V *a);
static V S697(void);
static V L698(V *a);
static V L699(V *a);
static V S700(void);
static V L701(V *a);
static V S702(void);
static V L703(V *a);
static V S704(void);
static V W_P_dpat_dsym(V *a);
static V F_P_dplist(V a0);
static V S706(void);
static V S707(void);
static V W_P_dplist(V *a);
static V F_P_dpats(V a0);
static V L708(V *a);
static V W_P_dpats(V *a);
static V F_P_dpats_dgo(V a0, V a1, V a2);
static V W_P_dpats_dgo(V *a);
static V F_P_dpats_dclose(V a0, V a1);
static V L711(V *a);
static V W_P_dpats_dclose(V *a);
static V F_P_dpats_ditem(V a0);
static V L712(V *a);
static V S713(void);
static V L714(V *a);
static V L715(V *a);
static V W_P_dpats_ditem(V *a);
static V F_P_dpats_dmore(V a0, V a1);
static V L717(V *a);
static V W_P_dpats_dmore(V *a);
static V F_P_dptuple(V a0);
static V S719(void);
static V S720(void);
static V W_P_dptuple(V *a);
static V F_P_dpstr(V a0);
static V S722(void);
static V S723(void);
static V W_P_dpstr(V *a);
static V F_P_dpat_did(V a0, V a1);
static V L725(V *a);
static V S726(void);
static V L727(V *a);
static V W_P_dpat_did(V *a);
static V F_P_dscan(void);
static V L728(V *a);
static V W_P_dscan(V *a);
static V F_P_dscan_dret(V a0);
static V W_P_dscan_dret(V *a);
static V F_P_dscan_dgo(V a0, V a1);
static V S730(void);
static V S731(void);
static V S732(void);
static V S733(void);
static V S734(void);
static V S735(void);
static V S736(void);
static V S737(void);
static V W_P_dscan_dgo(V *a);
static V F_P_dscan_dend(V a0, V a1, V a2);
static V W_P_dscan_dend(V *a);
static V F_P_dscan_dsym(V a0, V a1, V a2);
static V W_P_dscan_dsym(V *a);
static V F_P_dscan_dtop(V a0, V a1, V a2, V a3);
static V W_P_dscan_dtop(V *a);
static V F_P_ddo(void);
static V L741(V *a);
static V L742(V *a);
static V S743(void);
static V L744(V *a);
static V L745(V *a);
static V S746(void);
static V L747(V *a);
static V L748(V *a);
static V L749(V *a);
static V W_P_ddo(V *a);
static V F_P_dlast(V a0);
static V S751(void);
static V W_P_dlast(V *a);
static V F_P_dinit(V a0);
static V W_P_dinit(V *a);
static V F_Fold_ddo(V a0, V a1, V a2, V a3);
static V S754(void);
static V S755(void);
static V S756(void);
static V S757(void);
static V S758(void);
static V S759(void);
static V S760(void);
static V S761(void);
static V S762(void);
static V W_Fold_ddo(V *a);
static V F_Fold_dapp(V a0, V a1, V a2, V a3);
static V S763(void);
static V W_Fold_dapp(V *a);
static V F_P_dmatch(void);
static V L764(V *a);
static V L765(V *a);
static V S766(void);
static V L767(V *a);
static V L768(V *a);
static V L769(V *a);
static V W_P_dmatch(V *a);
static V F_P_dmatch_dbody(V a0);
static V L771(V *a);
static V W_P_dmatch_dbody(V *a);
static V F_P_dcases(void);
static V L772(V *a);
static V L773(V *a);
static V W_P_dcases(V *a);
static V F_P_dcases_dde(V a0);
static V L775(V *a);
static V L776(V *a);
static V S777(void);
static V W_P_dcases_dde(V *a);
static V F_P_dcases_dgo(V a0);
static V L779(V *a);
static V S780(void);
static V L781(V *a);
static V S782(void);
static V L783(V *a);
static V L784(V *a);
static V L785(V *a);
static V W_P_dcases_dgo(V *a);
static V F_P_dbody(void);
static V L786(V *a);
static V L787(V *a);
static V W_P_dbody(V *a);
static V F_P_dscrs(void);
static V L788(V *a);
static V S789(void);
static V W_P_dscrs(V *a);
static V F_P_dscrs_dgo(V a0, V a1);
static V L791(V *a);
static V L792(V *a);
static V W_P_dscrs_dgo(V *a);
static V F_P_deff_dimports(void);
static V L793(V *a);
static V W_P_deff_dimports(V *a);
static V F_P_deff_dgo(V a0, V a1);
static V W_P_deff_dgo(V *a);
static V F_P_dret_dgo(V a0);
static V L796(V *a);
static V S797(void);
static V W_P_dret_dgo(V *a);
static V F_P_dparams(void);
static V L798(V *a);
static V S799(void);
static V W_P_dparams(V *a);
static V F_P_dparams_dgo(V a0);
static V L801(V *a);
static V L802(V *a);
static V S803(void);
static V L804(V *a);
static V L805(V *a);
static V W_P_dparams_dgo(V *a);
static V F_P_dparams_dmore(V a0);
static V S807(void);
static V L808(V *a);
static V W_P_dparams_dmore(V *a);
static V F_P_dfile_dfin(V a0);
static V W_P_dfile_dfin(V *a);
static V F_P_dfile_derr(V a0);
static V S811(void);
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
static V S820(void);
static V W_Eff_dpath(V *a);
static V F_Main_dcompile(V a0, V a1);
static V S823(void);
static V S824(void);
static V W_Main_dcompile(V *a);
static V F_Gen_dprogram(V a0);
static V W_Gen_dprogram(V *a);
static V F_Gen_dprogram_dm(V a0);
static V S826(void);
static V L827(V *a);
static V S828(void);
static V W_Gen_dprogram_dm(V *a);
static V F_G_dbody(V a0, V a1);
static V S830(void);
static V S831(void);
static V W_G_dbody(V *a);
static V F_G_dget(V a1, V a2, V a3);
static V W_G_dget(V *a);
static V F_Map_dget(V a1, V a2, V a3);
static V W_Map_dget(V *a);
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
static V F_Map_dbit_dgo_dchr(V a0, V a1);
static V W_Map_dbit_dgo_dchr(V *a);
static V F_Map_dget_dbit(V a1, V a2, V a3, V a4, V a5);
static V W_Map_dget_dbit(V *a);
static V F_Map_dhi(V a3, V a4, V a5);
static V W_Map_dhi(V *a);
static V F_Map_dlo(V a3, V a4, V a5);
static V W_Map_dlo(V *a);
static V F_Map_dget_dleaf(V a1, V a2, V a3);
static V W_Map_dget_dleaf(V *a);
static V F_Pair_dsnd(V a2);
static V W_Pair_dsnd(V *a);
static V F_Gen_dentry(V a0, V a1);
static V S848(void);
static V S849(void);
static V L850(V *a);
static V S851(void);
static V W_Gen_dentry(V *a);
static V F_Gen_dpure(V a1);
static V L852(V *a);
static V W_Gen_dpure(V *a);
static V F_Gen_derror(V a0);
static V L853(V *a);
static V W_Gen_derror(V *a);
static V F_Gen_derror_dgo(V a0, V a1);
static V W_Gen_derror_dgo(V *a);
static V F_Gen_dbind(V a2, V a3);
static V L855(V *a);
static V W_Gen_dbind(V *a);
static V F_Gen_dgo(V a2, V a3);
static V W_Gen_dgo(V *a);
static V F_Ty_dhead(V a0);
static V S858(void);
static V W_Ty_dhead(V *a);
static V F_Gen_dentry_dty(V a0, V a1, V a2);
static V S860(void);
static V L861(V *a);
static V S862(void);
static V S863(void);
static V W_Gen_dentry_dty(V *a);
static V F_Gen_dprinter(V a0, V a1);
static V L865(V *a);
static V W_Gen_dprinter(V *a);
static V F_Gen_dprinter_dmemo(V a0, V a1, V a2, V a3);
static V L867(V *a);
static V S868(void);
static V L869(V *a);
static V L870(V *a);
static V S871(void);
static V S872(void);
static V L873(V *a);
static V L874(V *a);
static V S875(void);
static V S876(void);
static V S877(void);
static V L878(V *a);
static V W_Gen_dprinter_dmemo(V *a);
static V F_Doc_dlist(V a0);
static V W_Doc_dlist(V *a);
static V F_Gen_dcode(V a0);
static V L880(V *a);
static V W_Gen_dcode(V *a);
static V F_Gen_dcode_dgo(V a0, V a1);
static V W_Gen_dcode_dgo(V *a);
static V F_Gen_dprinter_dbody(V a0, V a1, V a2);
static V S882(void);
static V S883(void);
static V S884(void);
static V S885(void);
static V S886(void);
static V S887(void);
static V S888(void);
static V S889(void);
static V W_Gen_dprinter_dbody(V *a);
static V F_Gen_dprinter_dhead(V a0, V a1, V a2);
static V S891(void);
static V S892(void);
static V S893(void);
static V S894(void);
static V S895(void);
static V L896(V *a);
static V S897(void);
static V S898(void);
static V S899(void);
static V L900(V *a);
static V S901(void);
static V S902(void);
static V S903(void);
static V S904(void);
static V W_Gen_dprinter_dhead(V *a);
static V F_Gen_dprinter_dadt(V a0, V a1, V a2);
static V L906(V *a);
static V S907(void);
static V S908(void);
static V W_Gen_dprinter_dadt(V *a);
static V F_Ty_dargs(V a0);
static V W_Ty_dargs(V *a);
static V F_Ty_dbind(V a0, V a1);
static V W_Ty_dbind(V *a);
static V F_Ty_dbind_dgo(V a0, V a1);
static V W_Ty_dbind_dgo(V *a);
static V F_Gen_dprinter_dctors(V a0, V a1, V a2);
static V L913(V *a);
static V L914(V *a);
static V W_Gen_dprinter_dctors(V *a);
static V F_G_dctor(V a0, V a1);
static V W_G_dctor(V *a);
static V F_G_dopt__ctors(V a0);
static V W_G_dopt__ctors(V *a);
static V F_Gen_dprinter_dctor(V a0, V a1, V a2, V a3, V a4);
static V S918(void);
static V S919(void);
static V L920(V *a);
static V S921(void);
static V S922(void);
static V S923(void);
static V W_Gen_dprinter_dctor(V *a);
static V F_Gen_dprinter_dtest(V a0, V a1, V a2);
static V S924(void);
static V S925(void);
static V S926(void);
static V S927(void);
static V S928(void);
static V W_Gen_dprinter_dtest(V *a);
static V F_Gen_dprinter_dfields(V a0, V a1, V a2, V a3, V a4);
static V L930(V *a);
static V L931(V *a);
static V S932(void);
static V S933(void);
static V S934(void);
static V S935(void);
static V S936(void);
static V S937(void);
static V S938(void);
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
static V S945(void);
static V W_Ty_dtuple(V *a);
static V F_Ty_dtuple_dgo(V a0, V a1, V a2);
static V W_Ty_dtuple_dgo(V *a);
static V F_Ty_dtuple_dargs(V a0, V a1);
static V W_Ty_dtuple_dargs(V *a);
static V F_Gen_dprinter_dtuple(V a0, V a1, V a2);
static V L949(V *a);
static V S950(void);
static V S951(void);
static V L952(V *a);
static V S953(void);
static V S954(void);
static V L955(V *a);
static V S956(void);
static V S957(void);
static V W_Gen_dprinter_dtuple(V *a);
static V F_Gen_dproto(V a0);
static V L958(V *a);
static V W_Gen_dproto(V *a);
static V F_Gen_dproto_dgo(V a0, V a1);
static V W_Gen_dproto_dgo(V *a);
static V F_Gen_dmemo_dadd(V a0);
static V L960(V *a);
static V W_Gen_dmemo_dadd(V *a);
static V F_Gen_dmemo_dadd_dgo(V a0, V a1);
static V W_Gen_dmemo_dadd_dgo(V *a);
static V F_Gen_dfresh(void);
static V L962(V *a);
static V W_Gen_dfresh(V *a);
static V F_Gen_dfresh_dgo(V a0);
static V W_Gen_dfresh_dgo(V *a);
static V F_Gen_dmemo_dfind(V a0);
static V L964(V *a);
static V W_Gen_dmemo_dfind(V *a);
static V F_Gen_dmemo_dfind_dgo(V a0, V a1);
static V W_Gen_dmemo_dfind_dgo(V *a);
static V F_Env_dfind(V a0, V a1);
static V W_Env_dfind(V *a);
static V F_Env_dfind_dif(V a0, V a1, V a2, V a3);
static V W_Env_dfind_dif(V *a);
static V F_Expr_dshow(V a0);
static V S969(void);
static V S970(void);
static V S971(void);
static V S972(void);
static V S973(void);
static V S974(void);
static V S975(void);
static V S976(void);
static V S977(void);
static V S978(void);
static V S979(void);
static V S980(void);
static V S981(void);
static V S982(void);
static V S983(void);
static V S984(void);
static V S985(void);
static V S986(void);
static V S987(void);
static V S988(void);
static V S989(void);
static V S990(void);
static V S991(void);
static V S992(void);
static V S993(void);
static V S994(void);
static V S995(void);
static V S996(void);
static V S997(void);
static V S998(void);
static V S999(void);
static V S1000(void);
static V S1001(void);
static V S1002(void);
static V W_Expr_dshow(V *a);
static V F_Pats_dshow(V a0);
static V S1004(void);
static V S1005(void);
static V W_Pats_dshow(V *a);
static V F_Pat_dshow(V a0);
static V S1007(void);
static V S1008(void);
static V S1009(void);
static V S1010(void);
static V W_Pat_dshow(V *a);
static V F_Exprs_dshow(V a0);
static V S1012(void);
static V S1013(void);
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
static V L1021(V *a);
static V L1022(V *a);
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
static V W_Nat_dadd(V *a);
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
static V L1048(V *a);
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
static V S1055(void);
static V S1056(void);
static V W_Gen_ddummy__params(V *a);
static V F_Gen_dsig(V a0, V a1, V a2, V a3);
static V S1061(void);
static V S1062(void);
static V S1063(void);
static V S1065(void);
static V W_Gen_dsig(V *a);
static V F_Sig_dwargs(V a0);
static V W_Sig_dwargs(V *a);
static V F_Gen_dwrapper(V a0, V a1);
static V S1068(void);
static V S1069(void);
static V L1070(V *a);
static V S1071(void);
static V S1072(void);
static V S1073(void);
static V S1074(void);
static V S1075(void);
static V W_Gen_dwrapper(V *a);
static V F_String_djoin(V a0, V a1);
static V W_String_djoin(V *a);
static V F_String_djoin_dgo(V a0, V a1, V a2);
static V W_String_djoin_dgo(V *a);
static V F_Gen_df(V a0);
static V S1078(void);
static V W_Gen_df(V *a);
static V F_Gen_dmangle(V a0);
static V S1080(void);
static V W_Gen_dmangle(V *a);
static V F_Gen_dmangle_dchr(V a0);
static V S1081(void);
static V S1082(void);
static V S1083(void);
static V W_Gen_dmangle_dchr(V *a);
static V F_Str_dchr(V a0);
static V W_Str_dchr(V *a);
static V F_Gen_dw(V a0);
static V S1084(void);
static V W_Gen_dw(V *a);
static V F_Gen_ddef_deff(V a0, V a1, V a2);
static V S1088(void);
static V S1090(void);
static V S1091(void);
static V S1092(void);
static V L1093(V *a);
static V S1094(void);
static V S1095(void);
static V L1096(V *a);
static V S1097(void);
static V S1098(void);
static V S1099(void);
static V S1100(void);
static V S1101(void);
static V S1102(void);
static V S1103(void);
static V S1104(void);
static V L1105(V *a);
static V S1106(void);
static V S1107(void);
static V S1108(void);
static V S1109(void);
static V S1110(void);
static V S1111(void);
static V S1112(void);
static V S1113(void);
static V S1114(void);
static V L1115(V *a);
static V W_Gen_ddef_deff(V *a);
static V F_Gen_deff_dargs(V a0, V a1);
static V S1117(void);
static V S1118(void);
static V W_Gen_deff_dargs(V *a);
static V F_Gen_dcid(V a0);
static V S1119(void);
static V W_Gen_dcid(V *a);
static V F_String_dto__upper(V a0);
static V W_String_dto__upper(V *a);
static V F_Char_dto__upper(V a0);
static V W_Char_dto__upper(V *a);
static V F_Bool_dto__u32(V a0);
static V W_Bool_dto__u32(V *a);
static V F_Gen_dhost(V a0);
static V S1123(void);
static V W_Gen_dhost(V *a);
static V F_Gen_dhost_dchr(V a0);
static V S1124(void);
static V W_Gen_dhost_dchr(V *a);
static V F_Gen_deffs(V a0);
static V L1125(V *a);
static V W_Gen_deffs(V *a);
static V F_Gen_deffs_dgo(V a0, V a1);
static V W_Gen_deffs_dgo(V *a);
static V F_Gen_deffs_dc(V a0);
static V S1128(void);
static V W_Gen_deffs_dc(V *a);
static V F_String_dends__with(V a0, V a1);
static V W_String_dends__with(V *a);
static V F_Gen_deffs_dc_dif(V a0, V a1, V a2);
static V W_Gen_deffs_dc_dif(V *a);
static V F_Gen_dcparams(V a0);
static V S1131(void);
static V S1132(void);
static V W_Gen_dcparams(V *a);
static V F_Gen_dcparams_dgo(V a0);
static V S1134(void);
static V W_Gen_dcparams_dgo(V *a);
static V F_Gen_ddef_dnative(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Gen_ddef_dnative(V *a);
static V F_Gen_ddef_dbody(V a0, V a1, V a2, V a3, V a4);
static V S1138(void);
static V S1139(void);
static V S1140(void);
static V S1141(void);
static V L1142(V *a);
static V S1143(void);
static V L1144(V *a);
static V S1145(void);
static V S1146(void);
static V L1147(V *a);
static V W_Gen_ddef_dbody(V *a);
static V F_R_dops(V a0, V a1);
static V S1149(void);
static V W_R_dops(V *a);
static V F_R_dopss(V a0, V a1);
static V W_R_dopss(V *a);
static V F_R_dopname(V a0);
static V S1151(void);
static V S1152(void);
static V S1153(void);
static V S1154(void);
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
static V W_R_dopname(V *a);
static V F_R_dopname_dgo(V a0);
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
static V W_R_dopname_dgo(V *a);
static V F_Gen_dstmt(V a0, V a1, V a2, V a3, V a4);
static V L1182(V *a);
static V W_Gen_dstmt(V *a);
static V F_Gen_dret(V a0, V a1);
static V S1184(void);
static V S1185(void);
static V S1186(void);
static V S1187(void);
static V W_Gen_dret(V *a);
static V F_Gen_dexpr(V a0, V a1, V a2);
static V S1189(void);
static V S1190(void);
static V S1191(void);
static V S1192(void);
static V L1193(V *a);
static V S1194(void);
static V S1195(void);
static V S1196(void);
static V S1197(void);
static V S1198(void);
static V L1199(V *a);
static V S1200(void);
static V S1201(void);
static V L1202(V *a);
static V S1203(void);
static V W_Gen_dexpr(V *a);
static V F_Gen_dblock(V a0, V a1, V a2);
static V L1204(V *a);
static V S1205(void);
static V L1206(V *a);
static V L1207(V *a);
static V S1208(void);
static V S1209(void);
static V S1210(void);
static V W_Gen_dblock(V *a);
static V F_Self_dnone(void);
static V S1211(void);
static V W_Self_dnone(V *a);
static V F_Gen_dlam(V a0, V a1, V a2, V a3);
static V L1214(V *a);
static V S1215(void);
static V L1216(V *a);
static V S1217(void);
static V S1218(void);
static V L1219(V *a);
static V S1220(void);
static V S1221(void);
static V L1222(V *a);
static V L1223(V *a);
static V S1224(void);
static V S1225(void);
static V S1226(void);
static V L1227(V *a);
static V S1228(void);
static V S1229(void);
static V S1230(void);
static V S1231(void);
static V S1232(void);
static V W_Gen_dlam(V *a);
static V F_Gen_dcaps_douter(V a0);
static V W_Gen_dcaps_douter(V *a);
static V F_Gen_darr(V a0);
static V S1235(void);
static V S1236(void);
static V S1237(void);
static V W_Gen_darr(V *a);
static V F_Gen_dcommas(V a0);
static V S1238(void);
static V W_Gen_dcommas(V *a);
static V F_Doc_dsep(V a0, V a1);
static V W_Doc_dsep(V *a);
static V F_Doc_dsep_dgo(V a0, V a1);
static V W_Doc_dsep_dgo(V *a);
static V F_Gen_dcaps_dinner(V a0, V a1);
static V S1242(void);
static V S1243(void);
static V W_Gen_dcaps_dinner(V *a);
static V F_Gen_dpat(V a0, V a1, V a2, V a3);
static V S1245(void);
static V S1246(void);
static V S1247(void);
static V S1248(void);
static V S1249(void);
static V S1250(void);
static V S1251(void);
static V S1252(void);
static V S1253(void);
static V S1254(void);
static V W_Gen_dpat(V *a);
static V F_Gen_dpat_dcond(V a0, V a1);
static V W_Gen_dpat_dcond(V *a);
static V F_Gen_dpat_dctor(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1257(void);
static V S1258(void);
static V W_Gen_dpat_dctor(V *a);
static V F_Gen_dpat_dkind(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S1260(void);
static V S1261(void);
static V S1262(void);
static V S1263(void);
static V S1264(void);
static V S1265(void);
static V S1266(void);
static V S1267(void);
static V S1268(void);
static V S1269(void);
static V S1270(void);
static V W_Gen_dpat_dkind(V *a);
static V F_Gen_dpat_dfields(V a0, V a1, V a2, V a3, V a4);
static V S1272(void);
static V S1273(void);
static V S1274(void);
static V W_Gen_dpat_dfields(V *a);
static V F_Gen_dpat_dtag(V a0, V a1, V a2);
static V W_Gen_dpat_dtag(V *a);
static V F_Gen_dpat_dvar(V a0, V a1, V a2);
static V S1277(void);
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
static V S1286(void);
static V L1287(V *a);
static V S1288(void);
static V L1289(V *a);
static V W_Gen_dctor_dinfo(V *a);
static V F_Gen_dctor_dkind(V a0, V a1, V a2);
static V S1291(void);
static V S1292(void);
static V S1293(void);
static V S1294(void);
static V S1295(void);
static V W_Gen_dctor_dkind(V *a);
static V F_Gen_dctor_dnode(V a0, V a1);
static V S1297(void);
static V S1298(void);
static V S1299(void);
static V S1300(void);
static V S1301(void);
static V S1302(void);
static V S1303(void);
static V S1304(void);
static V W_Gen_dctor_dnode(V *a);
static V F_Gen_dlen(V a0);
static V W_Gen_dlen(V *a);
static V F_Gen_dexprs(V a0, V a1, V a2);
static V L1306(V *a);
static V L1307(V *a);
static V W_Gen_dexprs(V *a);
static V F_Gen_dcall(V a0, V a1, V a2, V a3);
static V W_Gen_dcall(V *a);
static V F_Gen_dcall_dlocal(V a0, V a1, V a2, V a3);
static V L1309(V *a);
static V L1310(V *a);
static V W_Gen_dcall_dlocal(V *a);
static V F_Gen_dapply(V a0, V a1);
static V S1312(void);
static V S1313(void);
static V S1314(void);
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
static V S1324(void);
static V W_Gen_dsplit(V *a);
static V F_Gen_dcall_dkind(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1326(void);
static V S1327(void);
static V L1328(V *a);
static V S1329(void);
static V L1330(V *a);
static V W_Gen_dcall_dkind(V *a);
static V F_Gen_dcall_dsplit(V a0, V a1, V a2, V a3, V a4);
static V W_Gen_dcall_dsplit(V *a);
static V F_Gen_dcall_dfull(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L1333(V *a);
static V L1334(V *a);
static V S1335(void);
static V S1336(void);
static V L1337(V *a);
static V S1338(void);
static V S1339(void);
static V S1340(void);
static V S1341(void);
static V S1342(void);
static V W_Gen_dcall_dfull(V *a);
static V F_Gen_dref(V a0);
static V L1343(V *a);
static V W_Gen_dref(V *a);
static V F_Gen_dref_dgo(V a0, V a1);
static V W_Gen_dref_dgo(V *a);
static V F_Gen_dstr(V a0);
static V L1345(V *a);
static V S1346(void);
static V L1347(V *a);
static V S1348(void);
static V S1349(void);
static V L1350(V *a);
static V S1351(void);
static V S1352(void);
static V S1353(void);
static V L1354(V *a);
static V S1355(void);
static V W_Gen_dstr(V *a);
static V F_Gen_dlit(V a0);
static V S1357(void);
static V W_Gen_dlit(V *a);
static V F_Gen_dlit__chr(V a0);
static V S1358(void);
static V S1359(void);
static V S1360(void);
static V W_Gen_dlit__chr(V *a);
static V F_Gen_dutf8(V a0);
static V W_Gen_dutf8(V *a);
static V W_U32_dor(V *a);
static V F_Gen_doct(V a0);
static V S1361(void);
static V W_Gen_doct(V *a);
static V W_U32_dis__lt(V *a);
static V F_Gen_dvar(V a0, V a1, V a2);
static V W_Gen_dvar(V *a);
static V F_Gen_dvar_dfound(V a0, V a1, V a2);
static V S1363(void);
static V W_Gen_dvar_dfound(V *a);
static V F_Gen_dvar_dglobal(V a0, V a1, V a2);
static V S1365(void);
static V W_Gen_dvar_dglobal(V *a);
static V F_Gen_dvar_ddef(V a0, V a1);
static V W_Gen_dvar_ddef(V *a);
static V F_Gen_dvar_dkind(V a0, V a1, V a2);
static V S1368(void);
static V S1369(void);
static V L1370(V *a);
static V S1371(void);
static V L1372(V *a);
static V S1373(void);
static V S1374(void);
static V S1375(void);
static V S1376(void);
static V W_Gen_dvar_dkind(V *a);
static V F_Gen_dis__tail(V a0, V a1, V a2, V a3, V a4);
static V W_Gen_dis__tail(V *a);
static V W_Nat_dis__eq(V *a);
static V F_Gen_dis__ret(V a0);
static V W_Gen_dis__ret(V *a);
static V F_Gen_dstmt_dcall(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L1380(V *a);
static V W_Gen_dstmt_dcall(V *a);
static V F_Gen_dtail_dself(V a0, V a1, V a2, V a3);
static V W_Gen_dtail_dself(V *a);
static V F_Gen_dtail(V a0, V a1, V a2, V a3);
static V L1383(V *a);
static V S1384(void);
static V S1385(void);
static V W_Gen_dtail(V *a);
static V F_Gen_dtail_dassign(V a0, V a1);
static V S1387(void);
static V S1388(void);
static V W_Gen_dtail_dassign(V *a);
static V F_Gen_dtail_dtemps(V a0, V a1);
static V S1390(void);
static V S1391(void);
static V S1392(void);
static V W_Gen_dtail_dtemps(V *a);
static V F_Gen_dmatch(V a0, V a1, V a2, V a3, V a4, V a5);
static V L1393(V *a);
static V W_Gen_dmatch(V *a);
static V F_Gen_dmatch_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V L1395(V *a);
static V W_Gen_dmatch_dgo(V *a);
static V F_Gen_dcases(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1397(void);
static V L1401(V *a);
static V W_Gen_dcases(V *a);
static V F_Gen_dcases_dnext(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V S1403(void);
static V S1404(void);
static V L1405(V *a);
static V S1406(void);
static V S1407(void);
static V S1408(void);
static V W_Gen_dcases_dnext(V *a);
static V F_Gen_dand(V a0);
static V S1410(void);
static V S1411(void);
static V W_Gen_dand(V *a);
static V F_PatR_dconds(V a0);
static V W_PatR_dconds(V *a);
static V F_Gen_dpats(V a0, V a1, V a2, V a3);
static V W_Gen_dpats(V *a);
static V F_Gen_dscrs(V a0, V a1, V a2);
static V L1416(V *a);
static V S1417(void);
static V L1418(V *a);
static V L1419(V *a);
static V L1420(V *a);
static V W_Gen_dscrs(V *a);
static V F_Gen_dscrs_dput(V a0, V a1, V a2);
static V S1422(void);
static V S1423(void);
static V S1424(void);
static V W_Gen_dscrs_dput(V *a);
static V F_Gen_dlet(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S1426(void);
static V S1427(void);
static V W_Gen_dlet(V *a);
static V F_Gen_dlet_dpat(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L1428(V *a);
static V S1429(void);
static V L1430(V *a);
static V L1431(V *a);
static V L1432(V *a);
static V L1433(V *a);
static V S1434(void);
static V S1435(void);
static V S1436(void);
static V W_Gen_dlet_dpat(V *a);
static V F_Gen_dlet_dctor(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V W_Gen_dlet_dctor(V *a);
static V F_Gen_dlet_dpar(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Gen_dlet_dpar(V *a);
static V F_Gen_dpar(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L1439(V *a);
static V L1440(V *a);
static V L1441(V *a);
static V W_Gen_dpar(V *a);
static V F_Gen_dpar_denv(V a0, V a1, V a2, V a3);
static V S1443(void);
static V W_Gen_dpar_denv(V *a);
static V F_Gen_dpar_dname(V a0, V a1);
static V S1444(void);
static V S1445(void);
static V W_Gen_dpar_dname(V *a);
static V F_Gen_dpar_dvals(V a0, V a1, V a2, V a3, V a4);
static V L1447(V *a);
static V S1448(void);
static V S1449(void);
static V S1450(void);
static V S1451(void);
static V L1452(V *a);
static V L1453(V *a);
static V S1454(void);
static V S1455(void);
static V S1456(void);
static V S1457(void);
static V S1458(void);
static V S1459(void);
static V W_Gen_dpar_dvals(V *a);
static V F_Gen_dlet_dvar(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L1461(V *a);
static V L1462(V *a);
static V S1463(void);
static V S1464(void);
static V L1465(V *a);
static V S1466(void);
static V L1467(V *a);
static V L1468(V *a);
static V L1469(V *a);
static V S1470(void);
static V S1471(void);
static V S1472(void);
static V W_Gen_dlet_dvar(V *a);
static V F_Gen_dcids(V a0, V a1, V a2);
static V S1474(void);
static V S1475(void);
static V S1476(void);
static V S1477(void);
static V W_Gen_dcids(V *a);
static V F_Gen_dcids_dctors(V a0, V a1);
static V S1479(void);
static V W_Gen_dcids_dctors(V *a);
static V F_Gen_dcids_dkind(V a0, V a1);
static V S1481(void);
static V W_Gen_dcids_dkind(V *a);
static V F_Gen_dcids_dline(V a0, V a1, V a2);
static V S1483(void);
static V S1484(void);
static V S1485(void);
static V S1486(void);
static V S1487(void);
static V S1488(void);
static V S1489(void);
static V S1490(void);
static V S1491(void);
static V S1492(void);
static V W_Gen_dcids_dline(V *a);
static V F_Gen_dprogram_dfin(V a0, V a1);
static V S1495(void);
static V S1496(void);
static V S1497(void);
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
static V S1506(void);
static V S1507(void);
static V S1508(void);
static V S1509(void);
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
static V S1512(void);
static V S1513(void);
static V S1514(void);
static V S1515(void);
static V S1516(void);
static V S1517(void);
static V S1518(void);
static V S1519(void);
static V S1520(void);
static V S1521(void);
static V S1522(void);
static V S1523(void);
static V S1524(void);
static V S1525(void);
static V S1526(void);
static V S1527(void);
static V S1528(void);
static V S1529(void);
static V S1530(void);
static V S1531(void);
static V S1532(void);
static V S1533(void);
static V S1534(void);
static V S1535(void);
static V S1536(void);
static V S1537(void);
static V S1538(void);
static V S1539(void);
static V S1540(void);
static V S1541(void);
static V S1542(void);
static V S1543(void);
static V S1544(void);
static V S1545(void);
static V S1546(void);
static V S1547(void);
static V S1548(void);
static V S1549(void);
static V S1550(void);
static V S1551(void);
static V S1552(void);
static V S1553(void);
static V S1554(void);
static V S1555(void);
static V S1556(void);
static V S1557(void);
static V S1558(void);
static V S1559(void);
static V S1560(void);
static V S1561(void);
static V S1562(void);
static V S1563(void);
static V S1564(void);
static V S1565(void);
static V S1566(void);
static V S1567(void);
static V S1568(void);
static V S1569(void);
static V S1570(void);
static V S1571(void);
static V S1572(void);
static V S1573(void);
static V S1574(void);
static V S1575(void);
static V S1576(void);
static V S1577(void);
static V S1578(void);
static V S1579(void);
static V S1580(void);
static V S1581(void);
static V S1582(void);
static V S1583(void);
static V S1584(void);
static V S1585(void);
static V S1586(void);
static V S1587(void);
static V S1588(void);
static V S1589(void);
static V S1590(void);
static V S1591(void);
static V S1592(void);
static V S1593(void);
static V S1594(void);
static V S1595(void);
static V W_Natives(V *a);
static V F_G_dadd_dlaw(V a0, V a1, V a2);
static V W_G_dadd_dlaw(V *a);
static V F_G_dadd_dtype(V a0, V a1, V a2, V a3);
static V S1599(void);
static V W_G_dadd_dtype(V *a);
static V F_G_dctors(V a0, V a1, V a2, V a3, V a4);
static V W_G_dctors(V *a);
static V F_G_dctor__kind(V a0, V a1, V a2, V a3);
static V S1602(void);
static V S1603(void);
static V W_G_dctor__kind(V *a);
static V F_Main_demit(V a0);
static V S1606(void);
static V L1607(V *a);
static V S1608(void);
static V W_Main_demit(V *a);
static V F_IO_dprint__err(V a0);
static V E_IO_dprint__err(V *a);
static V W_IO_dprint__err(V *a);
static V F_IO_dbind(V a2, V a3);
static V L1609(V *a);
static V L1610(V *a);
static V L1611(V *a);
static V W_IO_dbind(V *a);
static V F_Main_demit_dok(V a0, V a1, V a2);
static V S1612(void);
static V L1613(V *a);
static V W_Main_demit_dok(V *a);
static V F_IO_dwrite(V a0);
static V E_IO_dwrite(V *a);
static V W_IO_dwrite(V *a);
static V F_Main_deffs(V a0, V a1);
static V L1615(V *a);
static V S1616(void);
static V W_Main_deffs(V *a);
static V F_IO_dread__file(V a0);
static V S1617(void);
static V L1618(V *a);
static V L1619(V *a);
static V W_IO_dread__file(V *a);
static V F_IO_dread__fin(V a0);
static V L1621(V *a);
static V W_IO_dread__fin(V *a);
static V F_IO_dpass(V a1);
static V W_IO_dpass(V *a);
static V F_IO_dpure(V a1);
static V L1623(V *a);
static V L1624(V *a);
static V W_IO_dpure(V *a);
static V F_File_dclose(V a0);
static V E_File_dclose(V *a);
static V W_File_dclose(V *a);
static V F_File_dread(V a0, V a1);
static V E_File_dread(V *a);
static V W_File_dread(V *a);
static V F_File_dopen(V a0, V a1);
static V E_File_dopen(V *a);
static V W_File_dopen(V *a);
static V F_IO_dtry(V a1);
static V W_IO_dtry(V *a);
static V F_Main_dload(V a0, V a1);
static V S1626(void);
static V L1627(V *a);
static V W_Main_dload(V *a);
static V F_Main_dload_dparsed(V a0, V a1, V a2, V a3);
static V S1629(void);
static V S1630(void);
static V L1631(V *a);
static V W_Main_dload_dparsed(V *a);
static V F_Main_dimports(V a0, V a1, V a2);
static V S1633(void);
static V W_Main_dimports(V *a);
static V F_Main_dimports_done(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1635(void);
static V L1636(V *a);
static V L1637(V *a);
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
static V S1647(void);
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
static V L1652(V *a);
static V S1653(void);
static V L1654(V *a);
static V L1655(V *a);
static V S1656(void);
static V W_Main_dload_dhub(V *a);
static V F_Main_dhub_durl(V a0);
static V S1658(void);
static V W_Main_dhub_durl(V *a);
static V F_Hub_densure(V a0, V a1, V a2);
static V E_Hub_densure(V *a);
static V W_Hub_densure(V *a);
static V F_IO_dget__env(V a0);
static V E_IO_dget__env(V *a);
static V W_IO_dget__env(V *a);
static V F_Main_dlib(void);
static V S1659(void);
static V L1660(V *a);
static V W_Main_dlib(V *a);
static V F_Main_dlib_dor(V a0);
static V S1662(void);
static V L1663(V *a);
static V S1664(void);
static V W_Main_dlib_dor(V *a);
static V F_Main_dast(V a0);
static V S1666(void);
static V W_Main_dast(V *a);
static V F_Decls_dshow(V a0);
static V W_Decls_dshow(V *a);
static V F_Decls_dshow_dgo(V a0);
static V S1668(void);
static V S1669(void);
static V W_Decls_dshow_dgo(V *a);
static V F_Decl_dshow(V a0);
static V S1671(void);
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
static V S1682(void);
static V S1683(void);
static V W_Decl_dshow(V *a);
static V F_Ctors_dshow(V a0);
static V S1685(void);
static V S1686(void);
static V W_Ctors_dshow(V *a);
static V F_Ctor_dshow(V a0);
static V S1688(void);
static V S1689(void);
static V W_Ctor_dshow(V *a);
static V F_Fields_dshow(V a0);
static V S1691(void);
static V S1692(void);
static V S1693(void);
static V W_Fields_dshow(V *a);
static V F_Params_dshow(V a0);
static V S1695(void);
static V S1696(void);
static V W_Params_dshow(V *a);
static V F_Param_dshow(V a0);
static V S1698(void);
static V W_Param_dshow(V *a);
static V F_Toks_dshow(V a0);
static V S1700(void);
static V W_Toks_dshow(V *a);
static V F_Tok_dshow(V a0);
static V S1702(void);
static V S1703(void);
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
static V L6(V *a) {
return F_Main_dcompile(F_Main_dresolve(F_Mod_ddir(a[1]), F_Main_dparse(a[0])), C1(1, a[2]));
}
static V L5(V *a) {
return F_IO_dbind(F_Main_dload(64u, a[1]), mk_clo(L6, 3, 2, (V[]){a[2], a[0]}));
}
static V S7(void) { static V c; return STRC(c, "usage: bendc <base.bend> <input.bend> | --tokens <file> | --ast <file>"); }
static V F_Main_drun(V a0) {
top:;
V s2 = a0;
if (TAG(s2) == 1 && TAG(FLD(s2, 0)) == 1 && (FLD(FLD(s2, 0), 0)) == 45 && TAG(FLD(FLD(s2, 0), 1)) == 1 && (FLD(FLD(FLD(s2, 0), 1), 0)) == 45 && TAG(FLD(FLD(FLD(s2, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s2, 0), 1), 1), 0)) == 116 && TAG(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 0)) == 111 && TAG(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 0)) == 107 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 0)) == 101 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 0)) == 110 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 0)) == 115 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s2, 1)) == 1 && (FLD(FLD(s2, 1), 1)) == IMM(0)) {
return F_IO_dbind(F_IO_dread__file(FLD(FLD(s2, 1), 0)), mk_clo(L3, 1, 0, 0));
} else if (TAG(s2) == 1 && TAG(FLD(s2, 0)) == 1 && (FLD(FLD(s2, 0), 0)) == 45 && TAG(FLD(FLD(s2, 0), 1)) == 1 && (FLD(FLD(FLD(s2, 0), 1), 0)) == 45 && TAG(FLD(FLD(FLD(s2, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s2, 0), 1), 1), 0)) == 97 && TAG(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 0)) == 115 && TAG(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 0)) == 116 && (FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s2, 1)) == 1 && (FLD(FLD(s2, 1), 1)) == IMM(0)) {
return F_IO_dbind(F_IO_dread__file(FLD(FLD(s2, 1), 0)), mk_clo(L4, 1, 0, 0));
} else if (TAG(s2) == 1 && TAG(FLD(s2, 1)) == 1 && (FLD(FLD(s2, 1), 1)) == IMM(0)) {
return F_IO_dbind(F_IO_dread__file(FLD(s2, 0)), mk_clo(L5, 3, 2, (V[]){FLD(s2, 0), FLD(FLD(s2, 1), 0)}));
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
V s10 = a0;
if ((s10) == IMM(0)) {
return C2(1, IMM(0), IMM(0));
} else if (TAG(s10) == 1) {
return F_String_dsplit_dfin(FLD(s10, 0), F_String_dsplit(FLD(s10, 1), a1), F_Char_dis__eq(FLD(s10, 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_String_dsplit(V *a) { (void)a; return F_String_dsplit(a[0], a[1]); }
static V F_Char_dis__eq(V a0, V a1) {
top:;
V s11 = a0;
V s12 = a1;
{
return F_U32_dis__eq(s11, s12);
}
}
static V W_Char_dis__eq(V *a) { (void)a; return F_Char_dis__eq(a[0], a[1]); }
static V W_U32_dis__eq(V *a) { (void)a; return F_U32_dis__eq(a[0], a[1]); }
static V F_String_dsplit_dfin(V a0, V a1, V a2) {
top:;
V s13 = a2;
if ((s13) == IMM(0)) {
return F_String_dsplit_dpush(a0, a1);
} else if ((s13) == IMM(1)) {
return C2(1, IMM(0), a1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dsplit_dfin(V *a) { (void)a; return F_String_dsplit_dfin(a[0], a[1], a[2]); }
static V F_String_dsplit_dpush(V a0, V a1) {
top:;
V s14 = a1;
if ((s14) == IMM(0)) {
return C2(1, C2(1, a0, IMM(0)), IMM(0));
} else if (TAG(s14) == 1) {
return C2(1, C2(1, a0, FLD(s14, 0)), FLD(s14, 1));
} else { bend_fail("incomplete match"); }
}
static V W_String_dsplit_dpush(V *a) { (void)a; return F_String_dsplit_dpush(a[0], a[1]); }
static V F_Lex_dlines_dgo(V a0, V a1) {
top:;
V s15 = a0;
if ((s15) == IMM(0)) {
return IMM(0);
} else if (TAG(s15) == 1) {
return F_Lex_dlines_dput(C3(0, F_Lex_dindent(FLD(s15, 0)), a1, F_List_dreverse(F_Lex_dline(FLD(s15, 0), IMM(1), a1, IMM(0)))), F_Lex_dlines_dgo(FLD(s15, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlines_dgo(V *a) { (void)a; return F_Lex_dlines_dgo(a[0], a[1]); }
static V W_U32_dinc(V *a) { (void)a; return F_U32_dinc(a[0]); }
static V F_Lex_dline(V a0, V a1, V a2, V a3) {
top:;
V s16 = a0;
if ((s16) == IMM(0)) {
return a3;
} else if (TAG(s16) == 1) {
return F_Lex_dline_dgo(FLD(s16, 0), FLD(s16, 1), a1, a2, a3, F_Lex_dclass(FLD(s16, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline(V *a) { (void)a; return F_Lex_dline(a[0], a[1], a[2], a[3]); }
static V F_Lex_dclass(V a0) {
top:;
return F_Bool_dpick(F_Bool_dor(F_U32_dis__eq(a0, 32u), F_U32_dis__eq(a0, 9u)), 0u, F_Bool_dpick(F_U32_dis__eq(a0, 35u), 1u, F_Bool_dpick(F_Lex_dis__ids(a0), 2u, F_Bool_dpick(F_Char_dis__digit(a0), 3u, F_Bool_dpick(F_U32_dis__eq(a0, 39u), 4u, F_Bool_dpick(F_U32_dis__eq(a0, 34u), 5u, F_Bool_dpick(F_U32_dis__eq(a0, 13u), 0u, 6u)))))));
}
static V W_Lex_dclass(V *a) { (void)a; return F_Lex_dclass(a[0]); }
static V F_Bool_dpick(V a1, V a2, V a3) {
top:;
V s17 = a1;
if ((s17) == IMM(0)) {
return a3;
} else if ((s17) == IMM(1)) {
return a2;
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dpick(V *a) { (void)a; return F_Bool_dpick(a[1], a[2], a[3]); }
static V F_Char_dis__digit(V a0) {
top:;
V s18 = a0;
{
return F_Bool_dand(F_U32_dis__ge(s18, 48u), F_U32_dis__le(s18, 57u));
}
}
static V W_Char_dis__digit(V *a) { (void)a; return F_Char_dis__digit(a[0]); }
static V W_U32_dis__le(V *a) { (void)a; return F_U32_dis__le(a[0], a[1]); }
static V W_U32_dis__ge(V *a) { (void)a; return F_U32_dis__ge(a[0], a[1]); }
static V F_Bool_dand(V a0, V a1) {
top:;
V s19 = a0;
if ((s19) == IMM(0)) {
return IMM(0);
} else if ((s19) == IMM(1)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dand(V *a) { (void)a; return F_Bool_dand(a[0], a[1]); }
static V F_Lex_dis__ids(V a0) {
top:;
return F_Bool_dor(F_Char_dis__alpha(a0), F_U32_dis__eq(F_Char_dto__u32(a0), 95u));
}
static V W_Lex_dis__ids(V *a) { (void)a; return F_Lex_dis__ids(a[0]); }
static V F_Char_dto__u32(V a0) {
top:;
V s20 = a0;
{
return s20;
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
V s21 = a0;
{
return F_Bool_dand(F_U32_dis__ge(s21, 97u), F_U32_dis__le(s21, 122u));
}
}
static V W_Char_dis__lower(V *a) { (void)a; return F_Char_dis__lower(a[0]); }
static V F_Char_dis__upper(V a0) {
top:;
V s22 = a0;
{
return F_Bool_dand(F_U32_dis__ge(s22, 65u), F_U32_dis__le(s22, 90u));
}
}
static V W_Char_dis__upper(V *a) { (void)a; return F_Char_dis__upper(a[0]); }
static V F_Bool_dor(V a0, V a1) {
top:;
V s23 = a0;
if ((s23) == IMM(0)) {
return a1;
} else if ((s23) == IMM(1)) {
return IMM(1);
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dor(V *a) { (void)a; return F_Bool_dor(a[0], a[1]); }
static V F_Lex_dline_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s24 = a5;
if ((s24) == 0) {
return F_Lex_dline(a1, IMM(1), a3, a4);
} else if ((s24) == 1) {
return a4;
} else if ((s24) == 2) {
return F_Lex_dline_did(a2, a3, a4, F_Lex_did(C2(1, a0, a1), IMM(0)));
} else if ((s24) == 3) {
return F_Lex_dline_dnum(a2, a3, a4, F_Lex_ddigits(C2(1, a0, a1), 0u));
} else if ((s24) == 4) {
return F_Lex_dline_dchr(a2, a3, a4, F_Lex_dlit__char(a1));
} else if ((s24) == 5) {
return F_Lex_dline_dstr(a2, a3, a4, F_Lex_dstr(a1, IMM(0)));
} else if (nat_ge(s24, 6)) {
V v25 = C2(1, a0, a1);
return F_Lex_dline_dop(v25, a2, a3, a4, F_Lex_dop__of(v25));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dgo(V *a) { (void)a; return F_Lex_dline_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Lex_dop__of(V a0) {
top:;
return F_Lex_dop__of_dgo(F_Lex_dfind__op(F_Lex_dops3(), a0), a0);
}
static V W_Lex_dop__of(V *a) { (void)a; return F_Lex_dop__of(a[0]); }
static V S26(void) { static V c; return STRC(c, ".&."); }
static V S27(void) { static V c; return STRC(c, ".|."); }
static V S28(void) { static V c; return STRC(c, ".^."); }
static V S29(void) { static V c; return STRC(c, "<&>"); }
static V F_Lex_dops3(void) {
top:;
return C2(1, S26(), C2(1, S27(), C2(1, S28(), C2(1, S29(), IMM(0)))));
}
static V W_Lex_dops3(V *a) { (void)a; return F_Lex_dops3(); }
static V F_Lex_dfind__op(V a0, V a1) {
top:;
V s30 = a0;
if ((s30) == IMM(0)) {
return IMM(0);
} else if (TAG(s30) == 1) {
return F_Lex_dfind__op_dif(FLD(s30, 0), FLD(s30, 1), a1, F_String_dstarts__with(a1, FLD(s30, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dfind__op(V *a) { (void)a; return F_Lex_dfind__op(a[0], a[1]); }
static V F_String_dstarts__with(V a0, V a1) {
top:;
V s31 = a0;
V s32 = a1;
if ((s31) == IMM(0) && (s32) == IMM(0)) {
return IMM(1);
} else if ((s31) == IMM(0) && TAG(s32) == 1) {
return IMM(0);
} else if (TAG(s31) == 1 && (s32) == IMM(0)) {
return IMM(1);
} else if (TAG(s31) == 1 && TAG(s32) == 1) {
return F_String_dstarts__with_dif(FLD(s31, 1), FLD(s32, 1), F_Char_dis__eq(FLD(s31, 0), FLD(s32, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_String_dstarts__with(V *a) { (void)a; return F_String_dstarts__with(a[0], a[1]); }
static V F_String_dstarts__with_dif(V a0, V a1, V a2) {
top:;
V s33 = a2;
if ((s33) == IMM(0)) {
return IMM(0);
} else if ((s33) == IMM(1)) {
return F_String_dstarts__with(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dstarts__with_dif(V *a) { (void)a; return F_String_dstarts__with_dif(a[0], a[1], a[2]); }
static V F_Lex_dfind__op_dif(V a0, V a1, V a2, V a3) {
top:;
V s34 = a3;
if ((s34) == IMM(1)) {
return C1(1, a0);
} else if ((s34) == IMM(0)) {
return F_Lex_dfind__op(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dfind__op_dif(V *a) { (void)a; return F_Lex_dfind__op_dif(a[0], a[1], a[2], a[3]); }
static V F_Lex_dop__of_dgo(V a0, V a1) {
top:;
V s35 = a0;
if (TAG(s35) == 1) {
return FLD(s35, 0);
} else if ((s35) == IMM(0)) {
return F_Lex_dop__of_dtwo(F_Lex_dfind__op(F_Lex_dops2(), a1), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dop__of_dgo(V *a) { (void)a; return F_Lex_dop__of_dgo(a[0], a[1]); }
static V S36(void) { static V c; return STRC(c, "=>"); }
static V S37(void) { static V c; return STRC(c, "->"); }
static V S38(void) { static V c; return STRC(c, "<-"); }
static V S39(void) { static V c; return STRC(c, "<>"); }
static V S40(void) { static V c; return STRC(c, "<="); }
static V S41(void) { static V c; return STRC(c, ">="); }
static V S42(void) { static V c; return STRC(c, "=="); }
static V S43(void) { static V c; return STRC(c, "!="); }
static V S44(void) { static V c; return STRC(c, "++"); }
static V S45(void) { static V c; return STRC(c, "&&"); }
static V S46(void) { static V c; return STRC(c, "||"); }
static V S47(void) { static V c; return STRC(c, ">>"); }
static V S48(void) { static V c; return STRC(c, "<<"); }
static V F_Lex_dops2(void) {
top:;
return C2(1, S36(), C2(1, S37(), C2(1, S38(), C2(1, S39(), C2(1, S40(), C2(1, S41(), C2(1, S42(), C2(1, S43(), C2(1, S44(), C2(1, S45(), C2(1, S46(), C2(1, S47(), C2(1, S48(), IMM(0))))))))))))));
}
static V W_Lex_dops2(V *a) { (void)a; return F_Lex_dops2(); }
static V F_Lex_dop__of_dtwo(V a0, V a1) {
top:;
V s49 = a0;
if (TAG(s49) == 1) {
return FLD(s49, 0);
} else if ((s49) == IMM(0)) {
return F_String_dtake(a1, 1u);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dop__of_dtwo(V *a) { (void)a; return F_Lex_dop__of_dtwo(a[0], a[1]); }
static V F_String_dtake(V a0, V a1) {
top:;
V s50 = a0;
V s51 = a1;
if ((s50) == IMM(0)) {
return IMM(0);
} else if (TAG(s50) == 1 && (s51) == 0) {
return IMM(0);
} else if (TAG(s50) == 1 && nat_ge(s51, 1)) {
return C2(1, FLD(s50, 0), F_String_dtake(FLD(s50, 1), nat_subk(s51, 1)));
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
V s52 = a0;
if ((s52) == IMM(0)) {
return 0u;
} else if (TAG(s52) == 1) {
return nat_addk(F_String_dlength(FLD(s52, 1)), 1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dlength(V *a) { (void)a; return F_String_dlength(a[0]); }
static V F_String_ddrop(V a0, V a1) {
top:;
V s53 = a0;
V s54 = a1;
if ((s53) == IMM(0)) {
return IMM(0);
} else if (TAG(s53) == 1 && (s54) == 0) {
return C2(1, FLD(s53, 0), FLD(s53, 1));
} else if (TAG(s53) == 1 && nat_ge(s54, 1)) {
{ V t0 = FLD(s53, 1); V t1 = nat_subk(s54, 1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_String_ddrop(V *a) { (void)a; return F_String_ddrop(a[0], a[1]); }
static V F_Lex_dstr(V a0, V a1) {
top:;
V s55 = a0;
if ((s55) == IMM(0)) {
return C2(0, F_Str_drev(a1), IMM(0));
} else if (TAG(s55) == 1) {
return F_Lex_dstr_dif(FLD(s55, 0), FLD(s55, 1), a1, F_U32_dis__eq(FLD(s55, 0), 34u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dstr(V *a) { (void)a; return F_Lex_dstr(a[0], a[1]); }
static V F_Lex_dstr_dif(V a0, V a1, V a2, V a3) {
top:;
V s56 = a3;
if ((s56) == IMM(1)) {
return C2(0, F_Str_drev(a2), a1);
} else if ((s56) == IMM(0)) {
return F_Lex_dstr_dnext(a2, F_Lex_dlit__char(C2(1, a0, a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dstr_dif(V *a) { (void)a; return F_Lex_dstr_dif(a[0], a[1], a[2], a[3]); }
static V F_Lex_dlit__char(V a0) {
top:;
V s57 = a0;
if ((s57) == IMM(0)) {
return C2(0, 0u, IMM(0));
} else if (TAG(s57) == 1) {
return F_Lex_dlit__char_dif(FLD(s57, 0), FLD(s57, 1), F_U32_dis__eq(FLD(s57, 0), 92u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlit__char(V *a) { (void)a; return F_Lex_dlit__char(a[0]); }
static V F_Lex_dlit__char_dif(V a0, V a1, V a2) {
top:;
V s58 = a2;
if ((s58) == IMM(0)) {
return C2(0, a0, a1);
} else if ((s58) == IMM(1)) {
return F_Lex_dlit__char_desc(a1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlit__char_dif(V *a) { (void)a; return F_Lex_dlit__char_dif(a[0], a[1], a[2]); }
static V F_Lex_dlit__char_desc(V a0) {
top:;
V s59 = a0;
if ((s59) == IMM(0)) {
return C2(0, 92u, IMM(0));
} else if (TAG(s59) == 1) {
return C2(0, F_Lex_desc(FLD(s59, 0)), FLD(s59, 1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlit__char_desc(V *a) { (void)a; return F_Lex_dlit__char_desc(a[0]); }
static V F_Lex_desc(V a0) {
top:;
V v60 = a0;
return F_Bool_dpick(F_U32_dis__eq(v60, 110u), 10u, F_Bool_dpick(F_U32_dis__eq(v60, 116u), 9u, F_Bool_dpick(F_U32_dis__eq(v60, 114u), 13u, F_Bool_dpick(F_U32_dis__eq(v60, 48u), 0u, v60))));
}
static V W_Lex_desc(V *a) { (void)a; return F_Lex_desc(a[0]); }
static V F_Lex_dstr_dnext(V a0, V a1) {
top:;
V v61 = a1;
return F_Lex_dstr(FLD(v61, 1), C2(1, FLD(v61, 0), a0));
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
V s62 = a0;
if ((s62) == IMM(0)) {
return a1;
} else if (TAG(s62) == 1) {
{ V t0 = FLD(s62, 1); V t1 = C2(1, FLD(s62, 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_String_dreverse_dgo(V *a) { (void)a; return F_String_dreverse_dgo(a[0], a[1]); }
static V F_Lex_dline_dstr(V a0, V a1, V a2, V a3) {
top:;
V v63 = a3;
return F_Lex_dline(FLD(v63, 1), IMM(0), a1, C2(1, C3(0, C1(6, FLD(v63, 0)), a0, a1), a2));
}
static V W_Lex_dline_dstr(V *a) { (void)a; return F_Lex_dline_dstr(a[0], a[1], a[2], a[3]); }
static V F_Lex_dline_dchr(V a0, V a1, V a2, V a3) {
top:;
V v64 = a3;
return F_Lex_dline(F_Lex_ddrop1(FLD(v64, 1)), IMM(0), a1, C2(1, C3(0, C1(5, FLD(v64, 0)), a0, a1), a2));
}
static V W_Lex_dline_dchr(V *a) { (void)a; return F_Lex_dline_dchr(a[0], a[1], a[2], a[3]); }
static V F_Lex_ddrop1(V a0) {
top:;
V s65 = a0;
if ((s65) == IMM(0)) {
return IMM(0);
} else if (TAG(s65) == 1) {
return FLD(s65, 1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddrop1(V *a) { (void)a; return F_Lex_ddrop1(a[0]); }
static V F_Lex_ddigits(V a0, V a1) {
top:;
V s66 = a0;
if ((s66) == IMM(0)) {
return C2(0, a1, IMM(0));
} else if (TAG(s66) == 1) {
return F_Lex_ddigits_dif(FLD(s66, 0), FLD(s66, 1), a1, F_Char_dis__digit(FLD(s66, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddigits(V *a) { (void)a; return F_Lex_ddigits(a[0], a[1]); }
static V F_Lex_ddigits_dif(V a0, V a1, V a2, V a3) {
top:;
V s67 = a3;
if ((s67) == IMM(1)) {
return F_Lex_ddigits(a1, F_U32_dadd(F_U32_dmul(a2, 10u), F_U32_dsub(F_Char_dto__u32(a0), 48u)));
} else if ((s67) == IMM(0)) {
return C2(0, a2, C2(1, a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddigits_dif(V *a) { (void)a; return F_Lex_ddigits_dif(a[0], a[1], a[2], a[3]); }
static V W_U32_dsub(V *a) { (void)a; return F_U32_dsub(a[0], a[1]); }
static V W_U32_dmul(V *a) { (void)a; return F_U32_dmul(a[0], a[1]); }
static V W_U32_dadd(V *a) { (void)a; return F_U32_dadd(a[0], a[1]); }
static V F_Lex_dline_dnum(V a0, V a1, V a2, V a3) {
top:;
V v68 = a3;
return F_Lex_dline_dnum_dgo(a0, a1, a2, FLD(v68, 0), FLD(v68, 1));
}
static V W_Lex_dline_dnum(V *a) { (void)a; return F_Lex_dline_dnum(a[0], a[1], a[2], a[3]); }
static V F_Lex_dline_dnum_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s69 = a4;
if ((s69) == IMM(0)) {
return F_Lex_dline(IMM(0), IMM(0), a1, C2(1, C3(0, C1(3, a3), a0, a1), a2));
} else if (TAG(s69) == 1) {
return F_Lex_dline_dnum_dif(a0, a1, a2, a3, FLD(s69, 0), FLD(s69, 1), F_Bool_dpick(F_U32_dis__eq(FLD(s69, 0), 110u), 1u, F_Bool_dpick(F_U32_dis__eq(FLD(s69, 0), 46u), 2u, 0u)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnum_dgo(V *a) { (void)a; return F_Lex_dline_dnum_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V F_Lex_dline_dnum_dif(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s70 = a6;
if ((s70) == 0) {
return F_Lex_dline(C2(1, a4, a5), IMM(0), a1, C2(1, C3(0, C1(3, a3), a0, a1), a2));
} else if ((s70) == 1) {
return F_Lex_dline_dnat(a0, a1, a2, a3, a5);
} else if (nat_ge(s70, 2)) {
return F_Lex_dline_dflt(a0, a1, a2, a3, F_Lex_ddtext(a5, IMM(0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnum_dif(V *a) { (void)a; return F_Lex_dline_dnum_dif(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Lex_ddtext(V a0, V a1) {
top:;
V s71 = a0;
if ((s71) == IMM(0)) {
return C2(0, F_Str_drev(a1), IMM(0));
} else if (TAG(s71) == 1) {
return F_Lex_ddtext_dif(FLD(s71, 0), FLD(s71, 1), a1, F_Char_dis__digit(FLD(s71, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddtext(V *a) { (void)a; return F_Lex_ddtext(a[0], a[1]); }
static V F_Lex_ddtext_dif(V a0, V a1, V a2, V a3) {
top:;
V s72 = a3;
if ((s72) == IMM(1)) {
return F_Lex_ddtext(a1, C2(1, a0, a2));
} else if ((s72) == IMM(0)) {
return C2(0, F_Str_drev(a2), C2(1, a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddtext_dif(V *a) { (void)a; return F_Lex_ddtext_dif(a[0], a[1], a[2], a[3]); }
static V S74(void) { static V c; return STRC(c, "."); }
static V F_Lex_dline_dflt(V a0, V a1, V a2, V a3, V a4) {
top:;
V v73 = a4;
return F_Lex_dline(FLD(v73, 1), IMM(0), a1, C2(1, C3(0, C1(4, F_String_dappend(F_U32_dshow(a3), F_String_dappend(S74(), FLD(v73, 0)))), a0, a1), a2));
}
static V W_Lex_dline_dflt(V *a) { (void)a; return F_Lex_dline_dflt(a[0], a[1], a[2], a[3], a[4]); }
static V F_String_dappend(V a0, V a1) {
top:;
V s75 = a0;
if ((s75) == IMM(0)) {
return a1;
} else if (TAG(s75) == 1) {
return C2(1, FLD(s75, 0), F_String_dappend(FLD(s75, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_String_dappend(V *a) { (void)a; return F_String_dappend(a[0], a[1]); }
static V F_U32_dshow(V a0) {
top:;
V v76 = a0;
return F_U32_dshow_dif(v76, F_U32_dis__zero(v76));
}
static V W_U32_dshow(V *a) { (void)a; return F_U32_dshow(a[0]); }
static V W_U32_dis__zero(V *a) { (void)a; return F_U32_dis__zero(a[0]); }
static V F_U32_dshow_dif(V a0, V a1) {
top:;
V s77 = a1;
if ((s77) == IMM(1)) {
return C2(1, 48u, IMM(0));
} else if ((s77) == IMM(0)) {
return F_U32_dshow_dgo(10u, a0, IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_U32_dshow_dif(V *a) { (void)a; return F_U32_dshow_dif(a[0], a[1]); }
static V F_U32_dshow_dgo(V a0, V a1, V a2) {
top:;
V s78 = a0;
if ((s78) == 0) {
return a2;
} else if (nat_ge(s78, 1)) {
return F_U32_dshow_dfin(nat_subk(s78, 1), a2, a1, F_U32_dis__zero(a1));
} else { bend_fail("incomplete match"); }
}
static V W_U32_dshow_dgo(V *a) { (void)a; return F_U32_dshow_dgo(a[0], a[1], a[2]); }
static V F_U32_dshow_dfin(V a0, V a1, V a2, V a3) {
top:;
V s79 = a3;
if ((s79) == IMM(1)) {
return a1;
} else if ((s79) == IMM(0)) {
return F_U32_dshow_dgo(a0, F_U32_ddiv(a2, 10u), C2(1, F_U32_dadd(48u, F_U32_dmod(a2, 10u)), a1));
} else { bend_fail("incomplete match"); }
}
static V W_U32_dshow_dfin(V *a) { (void)a; return F_U32_dshow_dfin(a[0], a[1], a[2], a[3]); }
static V W_U32_dmod(V *a) { (void)a; return F_U32_dmod(a[0], a[1]); }
static V W_U32_ddiv(V *a) { (void)a; return F_U32_ddiv(a[0], a[1]); }
static V F_Lex_dline_dnat(V a0, V a1, V a2, V a3, V a4) {
top:;
V s80 = a4;
if ((s80) == IMM(0)) {
return F_Lex_dline(IMM(0), IMM(0), a1, C2(1, C3(0, C1(1, a3), a0, a1), a2));
} else if (TAG(s80) == 1) {
return F_Lex_dline_dnat_dif(a0, a1, a2, a3, FLD(s80, 0), FLD(s80, 1), F_U32_dis__eq(FLD(s80, 0), 43u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnat(V *a) { (void)a; return F_Lex_dline_dnat(a[0], a[1], a[2], a[3], a[4]); }
static V F_Lex_dline_dnat_dif(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s81 = a6;
if ((s81) == IMM(1)) {
return F_Lex_dline(a5, IMM(0), a1, C2(1, C3(0, C1(2, a3), a0, a1), a2));
} else if ((s81) == IMM(0)) {
return F_Lex_dline(C2(1, a4, a5), IMM(0), a1, C2(1, C3(0, C1(1, a3), a0, a1), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnat_dif(V *a) { (void)a; return F_Lex_dline_dnat_dif(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Lex_did(V a0, V a1) {
top:;
V s82 = a0;
if ((s82) == IMM(0)) {
return C2(0, F_Str_drev(a1), IMM(0));
} else if (TAG(s82) == 1) {
return F_Lex_did_dif(FLD(s82, 0), FLD(s82, 1), a1, F_Lex_dis__idc(FLD(s82, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_did(V *a) { (void)a; return F_Lex_did(a[0], a[1]); }
static V F_Lex_dis__idc(V a0) {
top:;
V v83 = F_Char_dto__u32(a0);
return F_Bool_dor(F_Char_dis__alpha(a0), F_Bool_dor(F_Char_dis__digit(a0), F_Bool_dor(F_U32_dis__eq(v83, 95u), F_U32_dis__eq(v83, 46u))));
}
static V W_Lex_dis__idc(V *a) { (void)a; return F_Lex_dis__idc(a[0]); }
static V F_Lex_did_dif(V a0, V a1, V a2, V a3) {
top:;
V s84 = a3;
if ((s84) == IMM(1)) {
return F_Lex_did(a1, C2(1, a0, a2));
} else if ((s84) == IMM(0)) {
return C2(0, F_Str_drev(a2), C2(1, a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_did_dif(V *a) { (void)a; return F_Lex_did_dif(a[0], a[1], a[2], a[3]); }
static V F_Lex_dline_did(V a0, V a1, V a2, V a3) {
top:;
V v85 = a3;
return F_Lex_dline(FLD(v85, 1), IMM(0), a1, C2(1, C3(0, C1(0, FLD(v85, 0)), a0, a1), a2));
}
static V W_Lex_dline_did(V *a) { (void)a; return F_Lex_dline_did(a[0], a[1], a[2], a[3]); }
static V F_List_dreverse(V a2) {
top:;
return F_List_dreverse_dgo(a2, IMM(0));
}
static V W_List_dreverse(V *a) { (void)a; return F_List_dreverse(a[2]); }
static V F_List_dreverse_dgo(V a2, V a3) {
top:;
V s86 = a2;
if ((s86) == IMM(0)) {
return a3;
} else if (TAG(s86) == 1) {
{ V t0 = FLD(s86, 1); V t1 = C2(1, FLD(s86, 0), a3); a2 = t0; a3 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_List_dreverse_dgo(V *a) { (void)a; return F_List_dreverse_dgo(a[2], a[3]); }
static V F_Lex_dindent(V a0) {
top:;
V s87 = a0;
if ((s87) == IMM(0)) {
return 0u;
} else if (TAG(s87) == 1) {
return F_Lex_dindent_dif(FLD(s87, 1), F_U32_dis__eq(FLD(s87, 0), 32u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dindent(V *a) { (void)a; return F_Lex_dindent(a[0]); }
static V F_Lex_dindent_dif(V a0, V a1) {
top:;
V s88 = a1;
if ((s88) == IMM(1)) {
return F_U32_dinc(F_Lex_dindent(a0));
} else if ((s88) == IMM(0)) {
return 0u;
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dindent_dif(V *a) { (void)a; return F_Lex_dindent_dif(a[0], a[1]); }
static V F_Lex_dlines_dput(V a0, V a1) {
top:;
V s89 = a0;
if ((FLD(s89, 2)) == IMM(0)) {
return a1;
} else if (TAG(FLD(s89, 2)) == 1) {
return C2(1, C3(0, FLD(s89, 0), FLD(s89, 1), C2(1, FLD(FLD(s89, 2), 0), FLD(FLD(s89, 2), 1))), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlines_dput(V *a) { (void)a; return F_Lex_dlines_dput(a[0], a[1]); }
static V F_Lay_dlines(V a0, V a1) {
top:;
V s90 = a0;
if ((s90) == IMM(0)) {
return a1;
} else if (TAG(s90) == 1) {
{ V t0 = FLD(s90, 1); V t1 = F_Lay_dline(FLD(s90, 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dlines(V *a) { (void)a; return F_Lay_dlines(a[0], a[1]); }
static V F_Lay_dline(V a0, V a1) {
top:;
V v91 = a0;
V v92 = a1;
return F_Lay_dline_dgo(FLD(v91, 0), FLD(v91, 1), FLD(v91, 2), CN(0, 5, (V[]){FLD(v92, 0), FLD(v92, 1), FLD(v92, 2), FLD(v92, 3), FLD(v92, 4)}), F_U32_dis__zero(FLD(v92, 1)));
}
static V W_Lay_dline(V *a) { (void)a; return F_Lay_dline(a[0], a[1]); }
static V F_Lay_dline_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s93 = a4;
if ((s93) == IMM(1)) {
return F_Lay_dtoks(a2, F_Lay_dstart(a3, a0, a1));
} else if ((s93) == IMM(0)) {
return F_Lay_dtoks(a2, a3);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dline_dgo(V *a) { (void)a; return F_Lay_dline_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V S97(void) { static V c; return STRC(c, ":"); }
static V F_Lay_dtoks(V a0, V a1) {
top:;
V s94 = a0;
if ((s94) == IMM(0)) {
return a1;
} else if (TAG(s94) == 1) {
V v95 = a1;
V v96 = F_U32_dadd(FLD(v95, 1), F_Lay_ddelta(FLD(FLD(s94, 0), 0)));
{ V t0 = FLD(s94, 1); V t1 = CN(0, 5, (V[]){C2(1, C3(0, FLD(FLD(s94, 0), 0), FLD(FLD(s94, 0), 1), FLD(FLD(s94, 0), 2)), FLD(v95, 0)), v96, F_Bool_dand(F_Lay_dis__sym(FLD(FLD(s94, 0), 0), S97()), F_U32_dis__zero(v96)), FLD(v95, 3), F_Lay_dis__op(FLD(FLD(s94, 0), 0))}); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dtoks(V *a) { (void)a; return F_Lay_dtoks(a[0], a[1]); }
static V S99(void) { static V c; return STRC(c, "->"); }
static V S100(void) { static V c; return STRC(c, "=>"); }
static V S101(void) { static V c; return STRC(c, "&"); }
static V S102(void) { static V c; return STRC(c, "|"); }
static V S103(void) { static V c; return STRC(c, "++"); }
static V S104(void) { static V c; return STRC(c, "<>"); }
static V S105(void) { static V c; return STRC(c, "&&"); }
static V S106(void) { static V c; return STRC(c, "||"); }
static V S107(void) { static V c; return STRC(c, "+"); }
static V S108(void) { static V c; return STRC(c, "*"); }
static V S109(void) { static V c; return STRC(c, ","); }
static V S110(void) { static V c; return STRC(c, "="); }
static V S111(void) { static V c; return STRC(c, "<-"); }
static V F_Lay_dis__op(V a0) {
top:;
V s98 = a0;
if (TAG(s98) == 7) {
return F_List_dcontains(mk_clo(W_String_deq, 2, 0, 0), C2(1, S99(), C2(1, S100(), C2(1, S101(), C2(1, S102(), C2(1, S103(), C2(1, S104(), C2(1, S105(), C2(1, S106(), C2(1, S107(), C2(1, S108(), C2(1, S109(), C2(1, S110(), C2(1, S111(), IMM(0)))))))))))))), FLD(s98, 0));
} else {
return IMM(0);
}
}
static V W_Lay_dis__op(V *a) { (void)a; return F_Lay_dis__op(a[0]); }
static V F_String_deq(V a0, V a1) {
top:;
return F_String_deq_dfin(F_String_dcmp(a0, a1));
}
static V W_String_deq(V *a) { (void)a; return F_String_deq(a[0], a[1]); }
static V F_String_dcmp(V a0, V a1) {
top:;
V s112 = a0;
V s113 = a1;
if ((s112) == IMM(0) && (s113) == IMM(0)) {
return C2(0, C2(0, IMM(0), IMM(0)), IMM(1));
} else if ((s112) == IMM(0) && TAG(s113) == 1) {
return C2(0, C2(0, IMM(0), C2(1, FLD(s113, 0), FLD(s113, 1))), IMM(0));
} else if (TAG(s112) == 1 && (s113) == IMM(0)) {
return C2(0, C2(0, C2(1, FLD(s112, 0), FLD(s112, 1)), IMM(0)), IMM(2));
} else if (TAG(s112) == 1 && TAG(s113) == 1) {
return F_String_dcmp_dfin(FLD(s112, 1), FLD(s113, 1), F_Char_dcmp(FLD(s112, 0), FLD(s113, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_String_dcmp(V *a) { (void)a; return F_String_dcmp(a[0], a[1]); }
static V F_Char_dcmp(V a0, V a1) {
top:;
V s114 = a0;
V s115 = a1;
{
return C2(0, C2(0, s114, s115), F_U32_dcmp(s114, s115));
}
}
static V W_Char_dcmp(V *a) { (void)a; return F_Char_dcmp(a[0], a[1]); }
static V W_U32_dcmp(V *a) { (void)a; return F_U32_dcmp(a[0], a[1]); }
static V F_String_dcmp_dfin(V a0, V a1, V a2) {
top:;
V v116 = a2;
V s117 = FLD(v116, 1);
if ((s117) == IMM(0)) {
return C2(0, C2(0, C2(1, FLD(FLD(v116, 0), 0), a0), C2(1, FLD(FLD(v116, 0), 1), a1)), IMM(0));
} else if ((s117) == IMM(1)) {
return F_String_dcmp_drec(FLD(FLD(v116, 0), 0), FLD(FLD(v116, 0), 1), F_String_dcmp(a0, a1));
} else if ((s117) == IMM(2)) {
return C2(0, C2(0, C2(1, FLD(FLD(v116, 0), 0), a0), C2(1, FLD(FLD(v116, 0), 1), a1)), IMM(2));
} else { bend_fail("incomplete match"); }
}
static V W_String_dcmp_dfin(V *a) { (void)a; return F_String_dcmp_dfin(a[0], a[1], a[2]); }
static V F_String_dcmp_drec(V a0, V a1, V a2) {
top:;
V v118 = a2;
return C2(0, C2(0, C2(1, a0, FLD(FLD(v118, 0), 0)), C2(1, a1, FLD(FLD(v118, 0), 1))), FLD(v118, 1));
}
static V W_String_dcmp_drec(V *a) { (void)a; return F_String_dcmp_drec(a[0], a[1], a[2]); }
static V F_String_deq_dfin(V a0) {
top:;
V v119 = a0;
return F_Cmp_dis__eq(FLD(v119, 1));
}
static V W_String_deq_dfin(V *a) { (void)a; return F_String_deq_dfin(a[0]); }
static V F_Cmp_dis__eq(V a0) {
top:;
V s120 = a0;
if ((s120) == IMM(0)) {
return IMM(0);
} else if ((s120) == IMM(1)) {
return IMM(1);
} else if ((s120) == IMM(2)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Cmp_dis__eq(V *a) { (void)a; return F_Cmp_dis__eq(a[0]); }
static V F_List_dcontains(V a1, V a2, V a3) {
top:;
V s121 = a2;
if ((s121) == IMM(0)) {
return IMM(0);
} else if (TAG(s121) == 1) {
return F_Bool_dor(apply(apply(a1, FLD(s121, 0)), a3), F_List_dcontains(a1, FLD(s121, 1), a3));
} else { bend_fail("incomplete match"); }
}
static V W_List_dcontains(V *a) { (void)a; return F_List_dcontains(a[1], a[2], a[3]); }
static V F_Lay_dis__sym(V a0, V a1) {
top:;
V s122 = a0;
if (TAG(s122) == 7) {
return F_Str_deq(FLD(s122, 0), a1);
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
static V S123(void) { static V c; return STRC(c, "("); }
static V S124(void) { static V c; return STRC(c, "["); }
static V S125(void) { static V c; return STRC(c, "{"); }
static V S126(void) { static V c; return STRC(c, ")"); }
static V S127(void) { static V c; return STRC(c, "]"); }
static V S128(void) { static V c; return STRC(c, "}"); }
static V F_Lay_ddelta(V a0) {
top:;
return F_Bool_dpick(F_Bool_dor(F_Lay_dis__sym(a0, S123()), F_Bool_dor(F_Lay_dis__sym(a0, S124()), F_Lay_dis__sym(a0, S125()))), 1u, F_Bool_dpick(F_Bool_dor(F_Lay_dis__sym(a0, S126()), F_Bool_dor(F_Lay_dis__sym(a0, S127()), F_Lay_dis__sym(a0, S128()))), 4294967295u, 0u));
}
static V W_Lay_ddelta(V *a) { (void)a; return F_Lay_ddelta(a[0]); }
static V F_Lay_dstart(V a0, V a1, V a2) {
top:;
V v129 = a0;
V v130 = F_Lay_dtop(FLD(v129, 3));
return F_Lay_dstart_dop(FLD(v129, 0), FLD(v129, 1), FLD(v129, 2), FLD(v129, 3), a1, a2, F_U32_dcmp(a1, v130), FLD(v129, 4));
}
static V W_Lay_dstart(V *a) { (void)a; return F_Lay_dstart(a[0], a[1], a[2]); }
static V F_Lay_dstart_dop(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s131 = a7;
if ((s131) == IMM(1)) {
return CN(0, 5, (V[]){a0, a1, a2, a3, IMM(0)});
} else if ((s131) == IMM(0)) {
return F_Lay_dstart_dgo(a0, a1, a2, a3, a4, a5, a6);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dstart_dop(V *a) { (void)a; return F_Lay_dstart_dop(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V F_Lay_dstart_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s132 = a6;
if ((s132) == IMM(2)) {
return F_Lay_dstart_dgt(a0, a1, a2, a3, a4, a5, a2);
} else if ((s132) == IMM(1)) {
return CN(0, 5, (V[]){C2(1, F_Lay_dtok(IMM(8), a5), a0), a1, a2, a3, IMM(0)});
} else if ((s132) == IMM(0)) {
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
V s133 = a0;
if ((s133) == IMM(0)) {
return C2(0, IMM(0), a2);
} else if (TAG(s133) == 1) {
return F_Lay_dpop_dif(FLD(s133, 0), FLD(s133, 1), a1, a2, a3, F_U32_dis__gt(FLD(s133, 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dpop(V *a) { (void)a; return F_Lay_dpop(a[0], a[1], a[2], a[3]); }
static V W_U32_dis__gt(V *a) { (void)a; return F_U32_dis__gt(a[0], a[1]); }
static V F_Lay_dpop_dif(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s134 = a5;
if ((s134) == IMM(1)) {
return F_Lay_dpop(a1, a2, C2(1, F_Lay_dtok(IMM(10), a4), a3), a4);
} else if ((s134) == IMM(0)) {
return C2(0, C2(1, a0, a1), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dpop_dif(V *a) { (void)a; return F_Lay_dpop_dif(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Lay_ddedent(V a0, V a1, V a2, V a3) {
top:;
V v135 = a3;
return CN(0, 5, (V[]){FLD(v135, 1), a0, a1, FLD(v135, 0), IMM(0)});
}
static V W_Lay_ddedent(V *a) { (void)a; return F_Lay_ddedent(a[0], a[1], a[2], a[3]); }
static V F_Lay_dstart_dgt(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s136 = a6;
if ((s136) == IMM(1)) {
return CN(0, 5, (V[]){C2(1, F_Lay_dtok(IMM(9), a5), a0), a1, a2, C2(1, a4, a3), IMM(0)});
} else if ((s136) == IMM(0)) {
return CN(0, 5, (V[]){a0, a1, a2, a3, IMM(0)});
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dstart_dgt(V *a) { (void)a; return F_Lay_dstart_dgt(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Lay_dtop(V a0) {
top:;
V s137 = a0;
if ((s137) == IMM(0)) {
return 0u;
} else if (TAG(s137) == 1) {
return FLD(s137, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dtop(V *a) { (void)a; return F_Lay_dtop(a[0]); }
static V F_Lay_dfinish(V a0) {
top:;
V v138 = a0;
return F_Lay_dfinish_dgo(F_Lay_dpop(FLD(v138, 3), 0u, C2(1, F_Lay_dtok(IMM(8), 0u), FLD(v138, 0)), 0u));
}
static V W_Lay_dfinish(V *a) { (void)a; return F_Lay_dfinish(a[0]); }
static V F_Lay_dfinish_dgo(V a0) {
top:;
V v139 = a0;
return F_List_dreverse(C2(1, F_Lay_dtok(IMM(11), 0u), FLD(v139, 1)));
}
static V W_Lay_dfinish_dgo(V *a) { (void)a; return F_Lay_dfinish_dgo(a[0]); }
static V L141(V *a) {
return F_P_ddecls_dgo(F_P_dstuck(F_P_dtok__kind(a[0])));
}
static V L140(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L141, 1, 0, 0));
}
static V F_P_ddecls(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L140, 1, 0, 0));
}
static V W_P_ddecls(V *a) { (void)a; return F_P_ddecls(); }
static V F_P_dtok__kind(V a0) {
top:;
V v142 = a0;
return FLD(v142, 0);
}
static V W_P_dtok__kind(V *a) { (void)a; return F_P_dtok__kind(a[0]); }
static V F_P_dstuck(V a0) {
top:;
V s143 = a0;
if (TAG(s143) == 12) {
return IMM(1);
} else if ((s143) == IMM(11)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dstuck(V *a) { (void)a; return F_P_dstuck(a[0]); }
static V L146(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L145(V *a) {
return F_Parser_dbind(F_P_ddecls(), mk_clo(L146, 2, 1, (V[]){a[0]}));
}
static V F_P_ddecls_dgo(V a0) {
top:;
V s144 = a0;
if ((s144) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s144) == IMM(0)) {
return F_Parser_dbind(F_P_ddecl(), mk_clo(L145, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddecls_dgo(V *a) { (void)a; return F_P_ddecls_dgo(a[0]); }
static V L147(V *a) {
return C2(0, a[0], a[1]);
}
static V F_Parser_dpure(V a1) {
top:;
return mk_clo(L147, 2, 1, (V[]){a1});
}
static V W_Parser_dpure(V *a) { (void)a; return F_Parser_dpure(a[1]); }
static V L148(V *a) {
return F_Parser_dgo(apply(a[1], a[4]), a[0]);
}
static V F_Parser_dbind(V a2, V a3) {
top:;
return mk_clo(L148, 5, 4, (V[]){a3, a2, 0, 0});
}
static V W_Parser_dbind(V *a) { (void)a; return F_Parser_dbind(a[2], a[3]); }
static V F_Parser_dgo(V a2, V a3) {
top:;
V v149 = a2;
return apply(apply(a3, FLD(v149, 0)), FLD(v149, 1));
}
static V W_Parser_dgo(V *a) { (void)a; return F_Parser_dgo(a[2], a[3]); }
static V S151(void) { static V c; return STRC(c, "@"); }
static V L150(V *a) {
return F_P_ddecl_dat(F_P_dtok__is(a[0], S151()), a[0]);
}
static V F_P_ddecl(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L150, 1, 0, 0));
}
static V W_P_ddecl(V *a) { (void)a; return F_P_ddecl(); }
static V F_P_dtok__is(V a0, V a1) {
top:;
V s152 = a0;
if (TAG(FLD(s152, 0)) == 7) {
return F_Str_deq(FLD(FLD(s152, 0), 0), a1);
} else {
return IMM(0);
}
}
static V W_P_dtok__is(V *a) { (void)a; return F_P_dtok__is(a[0], a[1]); }
static V L156(V *a) {
return F_P_ddecl();
}
static V L155(V *a) {
return F_Parser_dbind(F_P_dnls(), mk_clo(L156, 1, 0, 0));
}
static V L154(V *a) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L155, 1, 0, 0));
}
static V S157(void) { static V c; return STRC(c, "def"); }
static V S158(void) { static V c; return STRC(c, "type"); }
static V S159(void) { static V c; return STRC(c, "law"); }
static V S160(void) { static V c; return STRC(c, "import"); }
static V F_P_ddecl_dat(V a0, V a1) {
top:;
V s153 = a0;
if ((s153) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L154, 1, 0, 0));
} else if ((s153) == IMM(0)) {
return F_P_ddecl_dgo(F_P_dtok__which__id(a1, C2(1, S157(), C2(1, S158(), C2(1, S159(), C2(1, S160(), IMM(0)))))));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddecl_dat(V *a) { (void)a; return F_P_ddecl_dat(a[0], a[1]); }
static V F_P_dtok__which__id(V a0, V a1) {
top:;
V s161 = a0;
if (TAG(FLD(s161, 0)) == 0) {
return F_P_dwhich(FLD(FLD(s161, 0), 0), a1);
} else {
return 99u;
}
}
static V W_P_dtok__which__id(V *a) { (void)a; return F_P_dtok__which__id(a[0], a[1]); }
static V F_P_dwhich(V a0, V a1) {
top:;
V s162 = a1;
if ((s162) == IMM(0)) {
return 0u;
} else if (TAG(s162) == 1) {
return F_P_dwhich_dif(a0, FLD(s162, 1), F_String_deq(a0, FLD(s162, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dwhich(V *a) { (void)a; return F_P_dwhich(a[0], a[1]); }
static V F_P_dwhich_dif(V a0, V a1, V a2) {
top:;
V s163 = a2;
if ((s163) == IMM(1)) {
return 0u;
} else if ((s163) == IMM(0)) {
return nat_addk(F_P_dwhich(a0, a1), 1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dwhich_dif(V *a) { (void)a; return F_P_dwhich_dif(a[0], a[1], a[2]); }
static V S165(void) { static V c; return STRC(c, "expected a declaration"); }
static V S167(void) { static V c; return STRC(c, ""); }
static V S168(void) { static V c; return STRC(c, ""); }
static V L166(V *a) {
return F_Parser_dpure(C2(4, S167(), S168()));
}
static V F_P_ddecl_dgo(V a0) {
top:;
V s164 = a0;
if ((s164) == 0) {
return F_P_ddef();
} else if ((s164) == 1) {
return F_P_dtype();
} else if ((s164) == 2) {
return F_P_dlaw();
} else if ((s164) == 3) {
return F_P_dimport();
} else if (nat_ge(s164, 4)) {
return F_Parser_dbind(F_P_derr(S165()), mk_clo(L166, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddecl_dgo(V *a) { (void)a; return F_P_ddecl_dgo(a[0]); }
static V L169(V *a) {
return F_P_derr_dgo(a[0], a[1]);
}
static V F_P_derr(V a0) {
top:;
return mk_clo(L169, 2, 1, (V[]){a0});
}
static V W_P_derr(V *a) { (void)a; return F_P_derr(a[0]); }
static V S171(void) { static V c; return STRC(c, "line "); }
static V S172(void) { static V c; return STRC(c, ": "); }
static V S173(void) { static V c; return STRC(c, " (got '"); }
static V S174(void) { static V c; return STRC(c, "')"); }
static V S175(void) { static V c; return STRC(c, " (at end)"); }
static V F_P_derr_dgo(V a0, V a1) {
top:;
V s170 = a1;
if (TAG(s170) == 1 && TAG(FLD(FLD(s170, 0), 0)) == 12) {
return C2(0, IMM(0), C2(1, C3(0, C1(12, FLD(FLD(FLD(s170, 0), 0), 0)), FLD(FLD(s170, 0), 1), FLD(FLD(s170, 0), 2)), IMM(0)));
} else if (TAG(s170) == 1) {
return C2(0, IMM(0), C2(1, C3(0, C1(12, F_String_dappend(S171(), F_String_dappend(F_U32_dshow(FLD(FLD(s170, 0), 2)), F_String_dappend(S172(), F_String_dappend(a0, F_String_dappend(S173(), F_String_dappend(F_TK_dshow(FLD(FLD(s170, 0), 0)), S174()))))))), FLD(FLD(s170, 0), 1), FLD(FLD(s170, 0), 2)), IMM(0)));
} else if ((s170) == IMM(0)) {
return C2(0, IMM(0), C2(1, C3(0, C1(12, F_String_dappend(a0, S175())), IMM(1), 0u), IMM(0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_derr_dgo(V *a) { (void)a; return F_P_derr_dgo(a[0], a[1]); }
static V S177(void) { static V c; return STRC(c, "n"); }
static V S178(void) { static V c; return STRC(c, "n+"); }
static V S179(void) { static V c; return STRC(c, "'"); }
static V S180(void) { static V c; return STRC(c, "'"); }
static V S181(void) { static V c; return STRC(c, "\042"); }
static V S182(void) { static V c; return STRC(c, "\042"); }
static V S183(void) { static V c; return STRC(c, "<NL>\012"); }
static V S184(void) { static V c; return STRC(c, "<IN>"); }
static V S185(void) { static V c; return STRC(c, "<DE>"); }
static V S186(void) { static V c; return STRC(c, "<EOF>"); }
static V S187(void) { static V c; return STRC(c, "<ERR "); }
static V S188(void) { static V c; return STRC(c, ">"); }
static V F_TK_dshow(V a0) {
top:;
V s176 = a0;
if (TAG(s176) == 0) {
return FLD(s176, 0);
} else if (TAG(s176) == 1) {
return F_String_dappend(F_U32_dshow(FLD(s176, 0)), S177());
} else if (TAG(s176) == 2) {
return F_String_dappend(F_U32_dshow(FLD(s176, 0)), S178());
} else if (TAG(s176) == 3) {
return F_U32_dshow(FLD(s176, 0));
} else if (TAG(s176) == 4) {
return FLD(s176, 0);
} else if (TAG(s176) == 5) {
return F_String_dappend(S179(), F_String_dappend(F_U32_dshow(FLD(s176, 0)), S180()));
} else if (TAG(s176) == 6) {
return F_String_dappend(S181(), F_String_dappend(FLD(s176, 0), S182()));
} else if (TAG(s176) == 7) {
return FLD(s176, 0);
} else if ((s176) == IMM(8)) {
return S183();
} else if ((s176) == IMM(9)) {
return S184();
} else if ((s176) == IMM(10)) {
return S185();
} else if ((s176) == IMM(11)) {
return S186();
} else if (TAG(s176) == 12) {
return F_String_dappend(S187(), F_String_dappend(FLD(s176, 0), S188()));
} else { bend_fail("incomplete match"); }
}
static V W_TK_dshow(V *a) { (void)a; return F_TK_dshow(a[0]); }
static V S192(void) { static V c; return STRC(c, "as"); }
static V L194(V *a) {
return F_Parser_dpure(C2(4, a[1], a[0]));
}
static V L193(V *a) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L194, 3, 2, (V[]){a[1], a[0]}));
}
static V L191(V *a) {
return F_Parser_dbind(F_P_dimport_dalias(F_P_dtok__is__id(a[1], S192())), mk_clo(L193, 2, 1, (V[]){a[0]}));
}
static V L190(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L191, 2, 1, (V[]){a[0]}));
}
static V L189(V *a) {
return F_Parser_dbind(F_P_dimport_dpath(), mk_clo(L190, 1, 0, 0));
}
static V F_P_dimport(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L189, 1, 0, 0));
}
static V W_P_dimport(V *a) { (void)a; return F_P_dimport(); }
static V L195(V *a) {
return C2(0, IMM(0), F_P_dskip__line_dgo(a[0]));
}
static V F_P_dskip__line(void) {
top:;
return mk_clo(L195, 1, 0, 0);
}
static V W_P_dskip__line(V *a) { (void)a; return F_P_dskip__line(); }
static V F_P_dskip__line_dgo(V a0) {
top:;
V s196 = a0;
if ((s196) == IMM(0)) {
return IMM(0);
} else if (TAG(s196) == 1 && (FLD(FLD(s196, 0), 0)) == IMM(8)) {
return C2(1, C3(0, IMM(8), FLD(FLD(s196, 0), 1), FLD(FLD(s196, 0), 2)), FLD(s196, 1));
} else if (TAG(s196) == 1 && (FLD(FLD(s196, 0), 0)) == IMM(10)) {
return C2(1, C3(0, IMM(10), FLD(FLD(s196, 0), 1), FLD(FLD(s196, 0), 2)), FLD(s196, 1));
} else if (TAG(s196) == 1 && (FLD(FLD(s196, 0), 0)) == IMM(11)) {
return C2(1, C3(0, IMM(11), FLD(FLD(s196, 0), 1), FLD(FLD(s196, 0), 2)), FLD(s196, 1));
} else if (TAG(s196) == 1 && TAG(FLD(FLD(s196, 0), 0)) == 12) {
return C2(1, C3(0, C1(12, FLD(FLD(FLD(s196, 0), 0), 0)), FLD(FLD(s196, 0), 1), FLD(FLD(s196, 0), 2)), FLD(s196, 1));
} else if (TAG(s196) == 1 && (FLD(FLD(s196, 0), 0)) == IMM(9)) {
return F_P_dskip__block_dgo(FLD(s196, 1), 1u);
} else if (TAG(s196) == 1) {
{ V t0 = FLD(s196, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__line_dgo(V *a) { (void)a; return F_P_dskip__line_dgo(a[0]); }
static V F_P_dskip__block_dgo(V a0, V a1) {
top:;
V s197 = a0;
if ((s197) == IMM(0)) {
return IMM(0);
} else if (TAG(s197) == 1 && (FLD(FLD(s197, 0), 0)) == IMM(9)) {
{ V t0 = FLD(s197, 1); V t1 = F_U32_dinc(a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s197) == 1 && (FLD(FLD(s197, 0), 0)) == IMM(10)) {
return F_P_dskip__block_dde(FLD(s197, 1), a1, F_U32_dis__eq(a1, 1u));
} else if (TAG(s197) == 1 && (FLD(FLD(s197, 0), 0)) == IMM(11)) {
return C2(1, C3(0, IMM(11), FLD(FLD(s197, 0), 1), FLD(FLD(s197, 0), 2)), FLD(s197, 1));
} else if (TAG(s197) == 1) {
{ V t0 = FLD(s197, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__block_dgo(V *a) { (void)a; return F_P_dskip__block_dgo(a[0], a[1]); }
static V F_P_dskip__block_dde(V a0, V a1, V a2) {
top:;
V s198 = a2;
if ((s198) == IMM(1)) {
return a0;
} else if ((s198) == IMM(0)) {
return F_P_dskip__block_dgo(a0, F_U32_dsub(a1, 1u));
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__block_dde(V *a) { (void)a; return F_P_dskip__block_dde(a[0], a[1], a[2]); }
static V F_P_dtok__is__id(V a0, V a1) {
top:;
V s199 = a0;
if (TAG(FLD(s199, 0)) == 0) {
return F_Str_deq(FLD(FLD(s199, 0), 0), a1);
} else {
return IMM(0);
}
}
static V W_P_dtok__is__id(V *a) { (void)a; return F_P_dtok__is__id(a[0], a[1]); }
static V L201(V *a) {
return F_P_dident();
}
static V S202(void) { static V c; return STRC(c, ""); }
static V F_P_dimport_dalias(V a0) {
top:;
V s200 = a0;
if ((s200) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L201, 1, 0, 0));
} else if ((s200) == IMM(0)) {
return F_Parser_dpure(S202());
} else { bend_fail("incomplete match"); }
}
static V W_P_dimport_dalias(V *a) { (void)a; return F_P_dimport_dalias(a[0]); }
static V L203(V *a) {
return F_P_dident_dk(F_P_dtok__kind(a[0]));
}
static V F_P_dident(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L203, 1, 0, 0));
}
static V W_P_dident(V *a) { (void)a; return F_P_dident(); }
static V L205(V *a) {
return F_Parser_dpure(a[0]);
}
static V S206(void) { static V c; return STRC(c, "expected an identifier"); }
static V S208(void) { static V c; return STRC(c, ""); }
static V L207(V *a) {
return F_Parser_dpure(S208());
}
static V F_P_dident_dk(V a0) {
top:;
V s204 = a0;
if (TAG(s204) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L205, 2, 1, (V[]){FLD(s204, 0)}));
} else {
return F_Parser_dbind(F_P_derr(S206()), mk_clo(L207, 1, 0, 0));
}
}
static V W_P_dident_dk(V *a) { (void)a; return F_P_dident_dk(a[0]); }
static V L209(V *a) {
return F_P_dskip_dgo(a[0]);
}
static V F_P_dskip(void) {
top:;
return mk_clo(L209, 1, 0, 0);
}
static V W_P_dskip(V *a) { (void)a; return F_P_dskip(); }
static V F_P_dskip_dgo(V a0) {
top:;
V s210 = a0;
if ((s210) == IMM(0)) {
return C2(0, IMM(0), IMM(0));
} else if (TAG(s210) == 1) {
return F_P_dskip_dif(C3(0, FLD(FLD(s210, 0), 0), FLD(FLD(s210, 0), 1), FLD(FLD(s210, 0), 2)), FLD(s210, 1), F_P_dstuck(FLD(FLD(s210, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip_dgo(V *a) { (void)a; return F_P_dskip_dgo(a[0]); }
static V F_P_dskip_dif(V a0, V a1, V a2) {
top:;
V s211 = a2;
if ((s211) == IMM(1)) {
return C2(0, IMM(0), C2(1, a0, a1));
} else if ((s211) == IMM(0)) {
return C2(0, IMM(0), a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip_dif(V *a) { (void)a; return F_P_dskip_dif(a[0], a[1], a[2]); }
static V L212(V *a) {
return F_P_dpeek_dgo(a[0]);
}
static V F_P_dpeek(void) {
top:;
return mk_clo(L212, 1, 0, 0);
}
static V W_P_dpeek(V *a) { (void)a; return F_P_dpeek(); }
static V F_P_dpeek_dgo(V a0) {
top:;
V s213 = a0;
if ((s213) == IMM(0)) {
return C2(0, F_P_deof__tok(), IMM(0));
} else if (TAG(s213) == 1) {
return C2(0, FLD(s213, 0), C2(1, FLD(s213, 0), FLD(s213, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpeek_dgo(V *a) { (void)a; return F_P_dpeek_dgo(a[0]); }
static V F_P_deof__tok(void) {
top:;
return C3(0, IMM(11), IMM(1), 0u);
}
static V W_P_deof__tok(V *a) { (void)a; return F_P_deof__tok(); }
static V L214(V *a) {
return F_P_dimport_dpath_dgo(a[0]);
}
static V F_P_dimport_dpath(void) {
top:;
return mk_clo(L214, 1, 0, 0);
}
static V W_P_dimport_dpath(V *a) { (void)a; return F_P_dimport_dpath(); }
static V S216(void) { static V c; return STRC(c, "as"); }
static V S217(void) { static V c; return STRC(c, ""); }
static V F_P_dimport_dpath_dgo(V a0) {
top:;
V s215 = a0;
if (TAG(s215) == 1 && TAG(FLD(FLD(s215, 0), 0)) == 0) {
return F_P_dimport_dpath_did(FLD(FLD(FLD(s215, 0), 0), 0), FLD(FLD(s215, 0), 1), FLD(FLD(s215, 0), 2), FLD(s215, 1), F_Str_deq(FLD(FLD(FLD(s215, 0), 0), 0), S216()));
} else if (TAG(s215) == 1 && TAG(FLD(FLD(s215, 0), 0)) == 7) {
return F_P_dimport_dpath_dcat(FLD(FLD(FLD(s215, 0), 0), 0), F_P_dimport_dpath_dgo(FLD(s215, 1)));
} else if (TAG(s215) == 1 && TAG(FLD(FLD(s215, 0), 0)) == 3) {
return F_P_dimport_dpath_dcat(F_U32_dshow(FLD(FLD(FLD(s215, 0), 0), 0)), F_P_dimport_dpath_dgo(FLD(s215, 1)));
} else {
return C2(0, S217(), s215);
}
}
static V W_P_dimport_dpath_dgo(V *a) { (void)a; return F_P_dimport_dpath_dgo(a[0]); }
static V F_P_dimport_dpath_dcat(V a0, V a1) {
top:;
V v218 = a1;
return C2(0, F_String_dappend(a0, FLD(v218, 0)), FLD(v218, 1));
}
static V W_P_dimport_dpath_dcat(V *a) { (void)a; return F_P_dimport_dpath_dcat(a[0], a[1]); }
static V S220(void) { static V c; return STRC(c, ""); }
static V F_P_dimport_dpath_did(V a0, V a1, V a2, V a3, V a4) {
top:;
V s219 = a4;
if ((s219) == IMM(1)) {
return C2(0, S220(), C2(1, C3(0, C1(0, a0), a1, a2), a3));
} else if ((s219) == IMM(0)) {
return F_P_dimport_dpath_dcat(a0, F_P_dimport_dpath_dgo(a3));
} else { bend_fail("incomplete match"); }
}
static V W_P_dimport_dpath_did(V *a) { (void)a; return F_P_dimport_dpath_did(a[0], a[1], a[2], a[3], a[4]); }
static V S223(void) { static V c; return STRC(c, ":"); }
static V L226(V *a) {
return F_Parser_dpure(C2(2, a[0], a[1]));
}
static V L225(V *a) {
return F_Parser_dbind(F_P_dlaw_dlines(), mk_clo(L226, 2, 1, (V[]){a[0]}));
}
static V L224(V *a) {
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L225, 2, 1, (V[]){a[0]}));
}
static V L222(V *a) {
return F_Parser_dbind(F_P_dexpect(S223()), mk_clo(L224, 2, 1, (V[]){a[0]}));
}
static V L221(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L222, 1, 0, 0));
}
static V F_P_dlaw(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L221, 1, 0, 0));
}
static V W_P_dlaw(V *a) { (void)a; return F_P_dlaw(); }
static V L228(V *a) {
return F_P_dlaw_dgo(a[0], F_Bool_dpick(F_P_dis__de(a[0]), 0u, F_Bool_dpick(F_P_dstuck(F_P_dtok__kind(a[0])), 1u, 2u)));
}
static V L227(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L228, 1, 0, 0));
}
static V F_P_dlaw_dlines(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L227, 1, 0, 0));
}
static V W_P_dlaw_dlines(V *a) { (void)a; return F_P_dlaw_dlines(); }
static V F_P_dis__de(V a0) {
top:;
V s229 = a0;
if ((FLD(s229, 0)) == IMM(10)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dis__de(V *a) { (void)a; return F_P_dis__de(a[0]); }
static V L231(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S232(void) { static V c; return STRC(c, "for"); }
static V F_P_dlaw_dgo(V a0, V a1) {
top:;
V s230 = a1;
if ((s230) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L231, 1, 0, 0));
} else if ((s230) == 1) {
return F_Parser_dpure(IMM(0));
} else if (nat_ge(s230, 2)) {
return F_P_dlaw_dline(F_P_dtok__which__id(a0, C2(1, S232(), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlaw_dgo(V *a) { (void)a; return F_P_dlaw_dgo(a[0], a[1]); }
static V L237(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L236(V *a) {
return F_Parser_dbind(F_P_dlaw_dlines(), mk_clo(L237, 2, 1, (V[]){a[0]}));
}
static V L235(V *a) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L236, 2, 1, (V[]){a[0]}));
}
static V L234(V *a) {
return F_Parser_dbind(F_P_dparam(), mk_clo(L235, 1, 0, 0));
}
static V L238(V *a) {
return F_P_dlaw_dlines();
}
static V F_P_dlaw_dline(V a0) {
top:;
V s233 = a0;
if ((s233) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L234, 1, 0, 0));
} else if (nat_ge(s233, 1)) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L238, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlaw_dline(V *a) { (void)a; return F_P_dlaw_dline(a[0]); }
static V S244(void) { static V c; return STRC(c, ":"); }
static V L243(V *a) {
return F_P_dparam_dty(a[1], a[0], F_P_dtok__is(a[2], S244()));
}
static V L242(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L243, 3, 2, (V[]){a[0], a[1]}));
}
static V L241(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L242, 2, 1, (V[]){a[0]}));
}
static V L240(V *a) {
return F_Parser_dbind(F_P_dparam_dskip__mode(a[0]), mk_clo(L241, 2, 1, (V[]){a[0]}));
}
static V L239(V *a) {
return F_Parser_dbind(F_Parser_dpure(F_P_dparam_dmode(a[0])), mk_clo(L240, 1, 0, 0));
}
static V F_P_dparam(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L239, 1, 0, 0));
}
static V W_P_dparam(V *a) { (void)a; return F_P_dparam(); }
static V L247(V *a) {
return F_Parser_dpure(C3(0, a[1], a[0], F_P_dhead(a[2])));
}
static V L246(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L247, 3, 2, (V[]){a[0], a[1]}));
}
static V S248(void) { static V c; return STRC(c, ""); }
static V F_P_dparam_dty(V a0, V a1, V a2) {
top:;
V s245 = a2;
if ((s245) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L246, 3, 2, (V[]){a1, a0}));
} else if ((s245) == IMM(0)) {
return F_Parser_dpure(C3(0, a0, F_Bool_dpick(F_U32_dis__zero(a1), 4u, a1), S248()));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparam_dty(V *a) { (void)a; return F_P_dparam_dty(a[0], a[1], a[2]); }
static V S250(void) { static V c; return STRC(c, ""); }
static V F_P_dhead(V a0) {
top:;
V s249 = a0;
if (TAG(s249) == 0) {
return FLD(s249, 0);
} else if (TAG(s249) == 5 && TAG(FLD(s249, 0)) == 0) {
return FLD(FLD(s249, 0), 0);
} else if (TAG(s249) == 14) {
return FLD(s249, 0);
} else {
return S250();
}
}
static V W_P_dhead(V *a) { (void)a; return F_P_dhead(a[0]); }
static V F_P_dexpr(void) {
top:;
return F_P_dbin(1u);
}
static V W_P_dexpr(V *a) { (void)a; return F_P_dexpr(); }
static V L251(V *a) {
return F_P_dbin_dloop(a[0], a[1]);
}
static V F_P_dbin(V a0) {
top:;
return F_Parser_dbind(F_P_dterm(), mk_clo(L251, 2, 1, (V[]){a0}));
}
static V W_P_dbin(V *a) { (void)a; return F_P_dbin(a[0]); }
static V L252(V *a) {
return F_P_dbin_dloop_dop(a[1], a[0], F_P_dtok__op(a[2]));
}
static V F_P_dbin_dloop(V a0, V a1) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L252, 3, 2, (V[]){a1, a0}));
}
static V W_P_dbin_dloop(V *a) { (void)a; return F_P_dbin_dloop(a[0], a[1]); }
static V S254(void) { static V c; return STRC(c, ""); }
static V F_P_dtok__op(V a0) {
top:;
V s253 = a0;
if (TAG(FLD(s253, 0)) == 7 && (FLD(s253, 1)) == IMM(1)) {
return F_P_dop__find(FLD(FLD(s253, 0), 0), F_P_dops());
} else {
return C3(0, S254(), 0u, IMM(0));
}
}
static V W_P_dtok__op(V *a) { (void)a; return F_P_dtok__op(a[0]); }
static V S255(void) { static V c; return STRC(c, "->"); }
static V S256(void) { static V c; return STRC(c, "|"); }
static V S257(void) { static V c; return STRC(c, "&"); }
static V S258(void) { static V c; return STRC(c, "<&>"); }
static V S259(void) { static V c; return STRC(c, "||"); }
static V S260(void) { static V c; return STRC(c, "&&"); }
static V S261(void) { static V c; return STRC(c, "<>"); }
static V S262(void) { static V c; return STRC(c, "++"); }
static V S263(void) { static V c; return STRC(c, "<"); }
static V S264(void) { static V c; return STRC(c, "<="); }
static V S265(void) { static V c; return STRC(c, ">"); }
static V S266(void) { static V c; return STRC(c, ">="); }
static V S267(void) { static V c; return STRC(c, ".|."); }
static V S268(void) { static V c; return STRC(c, ".^."); }
static V S269(void) { static V c; return STRC(c, ".&."); }
static V S270(void) { static V c; return STRC(c, "<<"); }
static V S271(void) { static V c; return STRC(c, ">>"); }
static V S272(void) { static V c; return STRC(c, "+"); }
static V S273(void) { static V c; return STRC(c, "-"); }
static V S274(void) { static V c; return STRC(c, "*"); }
static V S275(void) { static V c; return STRC(c, "/"); }
static V S276(void) { static V c; return STRC(c, "%"); }
static V F_P_dops(void) {
top:;
return C2(1, C3(0, S255(), 1u, IMM(1)), C2(1, C3(0, S256(), 2u, IMM(1)), C2(1, C3(0, S257(), 3u, IMM(1)), C2(1, C3(0, S258(), 3u, IMM(1)), C2(1, C3(0, S259(), 4u, IMM(0)), C2(1, C3(0, S260(), 5u, IMM(0)), C2(1, C3(0, S261(), 6u, IMM(1)), C2(1, C3(0, S262(), 6u, IMM(1)), C2(1, C3(0, S263(), 7u, IMM(0)), C2(1, C3(0, S264(), 7u, IMM(0)), C2(1, C3(0, S265(), 7u, IMM(0)), C2(1, C3(0, S266(), 7u, IMM(0)), C2(1, C3(0, S267(), 8u, IMM(0)), C2(1, C3(0, S268(), 9u, IMM(0)), C2(1, C3(0, S269(), 10u, IMM(0)), C2(1, C3(0, S270(), 11u, IMM(0)), C2(1, C3(0, S271(), 11u, IMM(0)), C2(1, C3(0, S272(), 12u, IMM(0)), C2(1, C3(0, S273(), 12u, IMM(0)), C2(1, C3(0, S274(), 13u, IMM(0)), C2(1, C3(0, S275(), 13u, IMM(0)), C2(1, C3(0, S276(), 13u, IMM(0)), IMM(0)))))))))))))))))))))));
}
static V W_P_dops(V *a) { (void)a; return F_P_dops(); }
static V S278(void) { static V c; return STRC(c, ""); }
static V F_P_dop__find(V a0, V a1) {
top:;
V s277 = a1;
if ((s277) == IMM(0)) {
return C3(0, S278(), 0u, IMM(0));
} else if (TAG(s277) == 1) {
return F_P_dop__find_dif(a0, FLD(s277, 1), C3(0, FLD(FLD(s277, 0), 0), FLD(FLD(s277, 0), 1), FLD(FLD(s277, 0), 2)), F_String_deq(a0, FLD(FLD(s277, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dop__find(V *a) { (void)a; return F_P_dop__find(a[0], a[1]); }
static V F_P_dop__find_dif(V a0, V a1, V a2, V a3) {
top:;
V s279 = a3;
if ((s279) == IMM(1)) {
return a2;
} else if ((s279) == IMM(0)) {
return F_P_dop__find(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dop__find_dif(V *a) { (void)a; return F_P_dop__find_dif(a[0], a[1], a[2], a[3]); }
static V F_P_dbin_dloop_dop(V a0, V a1, V a2) {
top:;
V v280 = a2;
return F_P_dbin_dloop_dgo(a0, a1, FLD(v280, 0), FLD(v280, 1), FLD(v280, 2), F_Bool_dand(F_U32_dis__ne(FLD(v280, 1), 0u), F_U32_dis__ge(FLD(v280, 1), a0)));
}
static V W_P_dbin_dloop_dop(V *a) { (void)a; return F_P_dbin_dloop_dop(a[0], a[1], a[2]); }
static V W_U32_dis__ne(V *a) { (void)a; return F_U32_dis__ne(a[0], a[1]); }
static V L283(V *a) {
return F_P_dbin_dloop(a[2], F_P_dmk__bin(a[1], a[0], a[3]));
}
static V L282(V *a) {
return F_Parser_dbind(F_P_dbin(F_Bool_dpick(a[4], a[3], F_U32_dinc(a[3]))), mk_clo(L283, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_P_dbin_dloop_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s281 = a5;
if ((s281) == IMM(0)) {
return F_Parser_dpure(a1);
} else if ((s281) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L282, 6, 5, (V[]){a1, a2, a0, a3, a4}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbin_dloop_dgo(V *a) { (void)a; return F_P_dbin_dloop_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S284(void) { static V c; return STRC(c, "->"); }
static V S285(void) { static V c; return STRC(c, "|"); }
static V S286(void) { static V c; return STRC(c, "&"); }
static V S287(void) { static V c; return STRC(c, "<&>"); }
static V S288(void) { static V c; return STRC(c, "||"); }
static V S289(void) { static V c; return STRC(c, "&&"); }
static V S290(void) { static V c; return STRC(c, "<>"); }
static V S291(void) { static V c; return STRC(c, "++"); }
static V F_P_dmk__bin(V a0, V a1, V a2) {
top:;
return F_P_dmk__bin_dgo(a0, a1, a2, F_P_dwhich(a0, C2(1, S284(), C2(1, S285(), C2(1, S286(), C2(1, S287(), C2(1, S288(), C2(1, S289(), C2(1, S290(), C2(1, S291(), IMM(0)))))))))));
}
static V W_P_dmk__bin(V *a) { (void)a; return F_P_dmk__bin(a[0], a[1], a[2]); }
static V S293(void) { static V c; return STRC(c, "->"); }
static V S294(void) { static V c; return STRC(c, "|"); }
static V S295(void) { static V c; return STRC(c, "&"); }
static V S296(void) { static V c; return STRC(c, "#q"); }
static V S297(void) { static V c; return STRC(c, "Bool.or"); }
static V S298(void) { static V c; return STRC(c, "Bool.and"); }
static V S299(void) { static V c; return STRC(c, "Con"); }
static V S300(void) { static V c; return STRC(c, "String.append"); }
static V F_P_dmk__bin_dgo(V a0, V a1, V a2, V a3) {
top:;
V s292 = a3;
if ((s292) == 0) {
return C2(14, S293(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s292) == 1) {
return C2(14, S294(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s292) == 2) {
return C2(14, S295(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s292) == 3) {
return C2(14, S296(), IMM(0));
} else if ((s292) == 4) {
return C2(5, C1(0, S297()), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s292) == 5) {
return C2(5, C1(0, S298()), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s292) == 6) {
return C2(6, S299(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s292) == 7) {
return C2(5, C1(0, S300()), C2(1, a1, C2(1, a2, IMM(0))));
} else if (nat_ge(s292, 8)) {
return C3(12, a0, a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_P_dmk__bin_dgo(V *a) { (void)a; return F_P_dmk__bin_dgo(a[0], a[1], a[2], a[3]); }
static V L301(V *a) {
return F_P_dpostfix(a[0]);
}
static V F_P_dterm(void) {
top:;
return F_Parser_dbind(F_P_dprimary(), mk_clo(L301, 1, 0, 0));
}
static V W_P_dterm(V *a) { (void)a; return F_P_dterm(); }
static V L302(V *a) {
return F_P_dpostfix_dt(a[0], a[1]);
}
static V F_P_dpostfix(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L302, 2, 1, (V[]){a0}));
}
static V W_P_dpostfix(V *a) { (void)a; return F_P_dpostfix(a[0]); }
static V S303(void) { static V c; return STRC(c, "("); }
static V S304(void) { static V c; return STRC(c, "!"); }
static V S305(void) { static V c; return STRC(c, "["); }
static V F_P_dpostfix_dt(V a0, V a1) {
top:;
return F_P_dpostfix_dk(a0, F_Bool_dpick(F_P_dtok__sp(a1), 9u, F_P_dtok__which(a1, C2(1, S303(), C2(1, S304(), C2(1, S305(), IMM(0)))))));
}
static V W_P_dpostfix_dt(V *a) { (void)a; return F_P_dpostfix_dt(a[0], a[1]); }
static V F_P_dtok__which(V a0, V a1) {
top:;
V s306 = a0;
if (TAG(FLD(s306, 0)) == 7) {
return F_P_dwhich(FLD(FLD(s306, 0), 0), a1);
} else {
return 99u;
}
}
static V W_P_dtok__which(V *a) { (void)a; return F_P_dtok__which(a[0], a[1]); }
static V F_P_dtok__sp(V a0) {
top:;
V v307 = a0;
return FLD(v307, 1);
}
static V W_P_dtok__sp(V *a) { (void)a; return F_P_dtok__sp(a[0]); }
static V S310(void) { static V c; return STRC(c, ")"); }
static V L311(V *a) {
return F_P_dpostfix(C2(5, a[0], a[1]));
}
static V L309(V *a) {
return F_Parser_dbind(F_P_dlist(S310()), mk_clo(L311, 2, 1, (V[]){a[0]}));
}
static V L312(V *a) {
return F_P_dpostfix(a[0]);
}
static V S315(void) { static V c; return STRC(c, "]"); }
static V S317(void) { static V c; return STRC(c, "Array.get"); }
static V S318(void) { static V c; return STRC(c, "U32"); }
static V L316(V *a) {
return F_P_dpostfix(C2(5, C1(0, S317()), C2(1, C2(14, S318(), IMM(0)), C2(1, a[1], C2(1, a[0], IMM(0))))));
}
static V L314(V *a) {
return F_Parser_dbind(F_P_dexpect(S315()), mk_clo(L316, 3, 2, (V[]){a[1], a[0]}));
}
static V L313(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L314, 2, 1, (V[]){a[0]}));
}
static V F_P_dpostfix_dk(V a0, V a1) {
top:;
V s308 = a1;
if ((s308) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L309, 2, 1, (V[]){a0}));
} else if ((s308) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L312, 2, 1, (V[]){a0}));
} else if ((s308) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L313, 2, 1, (V[]){a0}));
} else if (nat_ge(s308, 3)) {
return F_Parser_dpure(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dpostfix_dk(V *a) { (void)a; return F_P_dpostfix_dk(a[0], a[1]); }
static V L319(V *a) {
return F_P_dexpect_dif(a[0], F_P_dtok__is(a[1], a[0]));
}
static V F_P_dexpect(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L319, 2, 1, (V[]){a0}));
}
static V W_P_dexpect(V *a) { (void)a; return F_P_dexpect(a[0]); }
static V S321(void) { static V c; return STRC(c, "expected '"); }
static V S322(void) { static V c; return STRC(c, "'"); }
static V F_P_dexpect_dif(V a0, V a1) {
top:;
V s320 = a1;
if ((s320) == IMM(1)) {
return F_P_dskip();
} else if ((s320) == IMM(0)) {
return F_P_derr(F_String_dappend(S321(), F_String_dappend(a0, S322())));
} else { bend_fail("incomplete match"); }
}
static V W_P_dexpect_dif(V *a) { (void)a; return F_P_dexpect_dif(a[0], a[1]); }
static V L323(V *a) {
return F_P_dlist_dstuck(a[0], a[1], F_P_dstuck(F_P_dtok__kind(a[1])));
}
static V F_P_dlist(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L323, 2, 1, (V[]){a0}));
}
static V W_P_dlist(V *a) { (void)a; return F_P_dlist(a[0]); }
static V S325(void) { static V c; return STRC(c, "unterminated list"); }
static V L326(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dlist_dstuck(V a0, V a1, V a2) {
top:;
V s324 = a2;
if ((s324) == IMM(1)) {
return F_Parser_dbind(F_P_derr(S325()), mk_clo(L326, 1, 0, 0));
} else if ((s324) == IMM(0)) {
return F_P_dlist_dgo(a0, F_P_dtok__is(a1, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlist_dstuck(V *a) { (void)a; return F_P_dlist_dstuck(a[0], a[1], a[2]); }
static V L328(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dlist_dgo(V a0, V a1) {
top:;
V s327 = a1;
if ((s327) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L328, 1, 0, 0));
} else if ((s327) == IMM(0)) {
return F_P_dlist_ditem(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dlist_dgo(V *a) { (void)a; return F_P_dlist_dgo(a[0], a[1]); }
static V S330(void) { static V c; return STRC(c, ","); }
static V L332(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L331(V *a) {
return F_Parser_dbind(F_P_dlist_dmore(a[1], a[2]), mk_clo(L332, 2, 1, (V[]){a[0]}));
}
static V L329(V *a) {
return F_Parser_dbind(F_P_deat(S330()), mk_clo(L331, 3, 2, (V[]){a[1], a[0]}));
}
static V F_P_dlist_ditem(V a0) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L329, 2, 1, (V[]){a0}));
}
static V W_P_dlist_ditem(V *a) { (void)a; return F_P_dlist_ditem(a[0]); }
static V L334(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dlist_dmore(V a0, V a1) {
top:;
V s333 = a1;
if ((s333) == IMM(1)) {
return F_P_dlist(a0);
} else if ((s333) == IMM(0)) {
return F_Parser_dbind(F_P_dexpect(a0), mk_clo(L334, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlist_dmore(V *a) { (void)a; return F_P_dlist_dmore(a[0], a[1]); }
static V L335(V *a) {
return F_P_deat_dif(F_P_dtok__is(a[1], a[0]));
}
static V F_P_deat(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L335, 2, 1, (V[]){a0}));
}
static V W_P_deat(V *a) { (void)a; return F_P_deat(a[0]); }
static V L337(V *a) {
return F_Parser_dpure(IMM(1));
}
static V F_P_deat_dif(V a0) {
top:;
V s336 = a0;
if ((s336) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L337, 1, 0, 0));
} else if ((s336) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_deat_dif(V *a) { (void)a; return F_P_deat_dif(a[0]); }
static V L338(V *a) {
return F_P_dprimary_dk(F_P_dtok__kind(a[0]));
}
static V F_P_dprimary(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L338, 1, 0, 0));
}
static V W_P_dprimary(V *a) { (void)a; return F_P_dprimary(); }
static V L341(V *a) {
return F_P_dafter__id(a[0], a[1]);
}
static V L340(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L341, 2, 1, (V[]){a[0]}));
}
static V L342(V *a) {
return F_Parser_dpure(C1(1, a[0]));
}
static V L343(V *a) {
return F_Parser_dpure(C1(2, a[0]));
}
static V L345(V *a) {
return F_Parser_dpure(C2(11, a[0], a[1]));
}
static V L344(V *a) {
return F_Parser_dbind(F_P_dterm(), mk_clo(L345, 2, 1, (V[]){a[0]}));
}
static V L346(V *a) {
return F_Parser_dpure(C1(3, a[0]));
}
static V L347(V *a) {
return F_Parser_dpure(C1(1, a[0]));
}
static V L348(V *a) {
return F_Parser_dpure(C1(4, a[0]));
}
static V S349(void) { static V c; return STRC(c, "("); }
static V S350(void) { static V c; return STRC(c, "["); }
static V S351(void) { static V c; return STRC(c, "{"); }
static V S352(void) { static V c; return STRC(c, "~"); }
static V S353(void) { static V c; return STRC(c, "+"); }
static V S354(void) { static V c; return STRC(c, "-"); }
static V S355(void) { static V c; return STRC(c, "@"); }
static V S356(void) { static V c; return STRC(c, "&"); }
static V S357(void) { static V c; return STRC(c, "\077"); }
static V S358(void) { static V c; return STRC(c, "expected an expression"); }
static V S360(void) { static V c; return STRC(c, ""); }
static V L359(V *a) {
return F_Parser_dpure(C1(15, S360()));
}
static V F_P_dprimary_dk(V a0) {
top:;
V s339 = a0;
if (TAG(s339) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L340, 2, 1, (V[]){FLD(s339, 0)}));
} else if (TAG(s339) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L342, 2, 1, (V[]){FLD(s339, 0)}));
} else if (TAG(s339) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L343, 2, 1, (V[]){FLD(s339, 0)}));
} else if (TAG(s339) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L344, 2, 1, (V[]){FLD(s339, 0)}));
} else if (TAG(s339) == 4) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L346, 2, 1, (V[]){FLD(s339, 0)}));
} else if (TAG(s339) == 5) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L347, 2, 1, (V[]){FLD(s339, 0)}));
} else if (TAG(s339) == 6) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L348, 2, 1, (V[]){FLD(s339, 0)}));
} else if (TAG(s339) == 7) {
return F_P_dprimary_dsym(F_P_dwhich(FLD(s339, 0), C2(1, S349(), C2(1, S350(), C2(1, S351(), C2(1, S352(), C2(1, S353(), C2(1, S354(), C2(1, S355(), C2(1, S356(), C2(1, S357(), IMM(0))))))))))));
} else {
return F_Parser_dbind(F_P_derr(S358()), mk_clo(L359, 1, 0, 0));
}
}
static V W_P_dprimary_dk(V *a) { (void)a; return F_P_dprimary_dk(a[0]); }
static V L362(V *a) {
return F_P_dterm();
}
static V L363(V *a) {
return F_P_dterm();
}
static V L365(V *a) {
return F_Parser_dpure(F_P_dneg(a[0]));
}
static V L364(V *a) {
return F_Parser_dbind(F_P_dterm(), mk_clo(L365, 1, 0, 0));
}
static V L366(V *a) {
return F_P_ddep();
}
static V L368(V *a) {
return F_P_damp_dgo(a[0]);
}
static V L367(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L368, 1, 0, 0));
}
static V S371(void) { static V c; return STRC(c, ""); }
static V L370(V *a) {
return F_Parser_dpure(C2(14, S371(), IMM(0)));
}
static V L369(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L370, 1, 0, 0));
}
static V S372(void) { static V c; return STRC(c, "unexpected symbol"); }
static V S374(void) { static V c; return STRC(c, ""); }
static V L373(V *a) {
return F_Parser_dpure(C1(15, S374()));
}
static V F_P_dprimary_dsym(V a0) {
top:;
V s361 = a0;
if ((s361) == 0) {
return F_P_dparen();
} else if ((s361) == 1) {
return F_P_dbrack();
} else if ((s361) == 2) {
return F_P_dbrace();
} else if ((s361) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L362, 1, 0, 0));
} else if ((s361) == 4) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L363, 1, 0, 0));
} else if ((s361) == 5) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L364, 1, 0, 0));
} else if ((s361) == 6) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L366, 1, 0, 0));
} else if ((s361) == 7) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L367, 1, 0, 0));
} else if ((s361) == 8) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L369, 1, 0, 0));
} else if (nat_ge(s361, 9)) {
return F_Parser_dbind(F_P_derr(S372()), mk_clo(L373, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dprimary_dsym(V *a) { (void)a; return F_P_dprimary_dsym(a[0]); }
static V S377(void) { static V c; return STRC(c, "#q"); }
static V L376(V *a) {
return F_Parser_dpure(C2(14, S377(), IMM(0)));
}
static V F_P_damp_dgo(V a0) {
top:;
V s375 = a0;
if (TAG(FLD(s375, 0)) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L376, 1, 0, 0));
} else {
return F_P_ddep();
}
}
static V W_P_damp_dgo(V *a) { (void)a; return F_P_damp_dgo(a[0]); }
static V S378(void) { static V c; return STRC(c, "-"); }
static V S380(void) { static V c; return STRC(c, "+"); }
static V S383(void) { static V c; return STRC(c, ":"); }
static V S386(void) { static V c; return STRC(c, ""); }
static V L385(V *a) {
return F_Parser_dpure(C2(14, S386(), IMM(0)));
}
static V L384(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L385, 1, 0, 0));
}
static V L382(V *a) {
return F_Parser_dbind(F_P_dexpect(S383()), mk_clo(L384, 1, 0, 0));
}
static V L381(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L382, 1, 0, 0));
}
static V L379(V *a) {
return F_Parser_dbind(F_P_deat(S380()), mk_clo(L381, 1, 0, 0));
}
static V F_P_ddep(void) {
top:;
return F_Parser_dbind(F_P_deat(S378()), mk_clo(L379, 1, 0, 0));
}
static V W_P_ddep(V *a) { (void)a; return F_P_ddep(); }
static V S388(void) { static V c; return STRC(c, "-"); }
static V F_P_dneg(V a0) {
top:;
V s387 = a0;
if (TAG(s387) == 1) {
return C1(1, F_U32_dsub(0u, FLD(s387, 0)));
} else if (TAG(s387) == 3) {
return C1(3, F_String_dappend(S388(), FLD(s387, 0)));
} else {
return s387;
}
}
static V W_P_dneg(V *a) { (void)a; return F_P_dneg(a[0]); }
static V S391(void) { static V c; return STRC(c, "=="); }
static V L390(V *a) {
return F_P_dbrace_dgo(F_P_dtok__is(a[0], S391()));
}
static V L389(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L390, 1, 0, 0));
}
static V F_P_dbrace(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L389, 1, 0, 0));
}
static V W_P_dbrace(V *a) { (void)a; return F_P_dbrace(); }
static V S394(void) { static V c; return STRC(c, "}"); }
static V S396(void) { static V c; return STRC(c, ""); }
static V L395(V *a) {
return F_Parser_dpure(C2(14, S396(), IMM(0)));
}
static V L393(V *a) {
return F_Parser_dbind(F_P_dexpect(S394()), mk_clo(L395, 1, 0, 0));
}
static V F_P_dbrace_dgo(V a0) {
top:;
V s392 = a0;
if ((s392) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L393, 1, 0, 0));
} else if ((s392) == IMM(0)) {
return F_P_dbrace_dbody();
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrace_dgo(V *a) { (void)a; return F_P_dbrace_dgo(a[0]); }
static V S399(void) { static V c; return STRC(c, "=="); }
static V S400(void) { static V c; return STRC(c, "!="); }
static V S401(void) { static V c; return STRC(c, ":"); }
static V L398(V *a) {
return F_P_dbrace_dtail(a[0], F_P_dtok__which(a[1], C2(1, S399(), C2(1, S400(), C2(1, S401(), IMM(0))))));
}
static V L397(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L398, 2, 1, (V[]){a[0]}));
}
static V F_P_dbrace_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L397, 1, 0, 0));
}
static V W_P_dbrace_dbody(V *a) { (void)a; return F_P_dbrace_dbody(); }
static V S405(void) { static V c; return STRC(c, ":"); }
static V S408(void) { static V c; return STRC(c, "}"); }
static V S410(void) { static V c; return STRC(c, ""); }
static V L409(V *a) {
return F_Parser_dpure(C2(14, S410(), IMM(0)));
}
static V L407(V *a) {
return F_Parser_dbind(F_P_dexpect(S408()), mk_clo(L409, 1, 0, 0));
}
static V L406(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L407, 1, 0, 0));
}
static V L404(V *a) {
return F_Parser_dbind(F_P_dexpect(S405()), mk_clo(L406, 1, 0, 0));
}
static V L403(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L404, 1, 0, 0));
}
static V S413(void) { static V c; return STRC(c, ":"); }
static V S416(void) { static V c; return STRC(c, "}"); }
static V S418(void) { static V c; return STRC(c, ""); }
static V L417(V *a) {
return F_Parser_dpure(C2(14, S418(), IMM(0)));
}
static V L415(V *a) {
return F_Parser_dbind(F_P_dexpect(S416()), mk_clo(L417, 1, 0, 0));
}
static V L414(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L415, 1, 0, 0));
}
static V L412(V *a) {
return F_Parser_dbind(F_P_dexpect(S413()), mk_clo(L414, 1, 0, 0));
}
static V L411(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L412, 1, 0, 0));
}
static V S421(void) { static V c; return STRC(c, "}"); }
static V L422(V *a) {
return F_Parser_dpure(C2(13, a[1], F_P_dhead(a[0])));
}
static V L420(V *a) {
return F_Parser_dbind(F_P_dexpect(S421()), mk_clo(L422, 3, 2, (V[]){a[1], a[0]}));
}
static V L419(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L420, 2, 1, (V[]){a[0]}));
}
static V S423(void) { static V c; return STRC(c, "}"); }
static V L424(V *a) {
return F_Parser_dpure(a[0]);
}
static V F_P_dbrace_dtail(V a0, V a1) {
top:;
V s402 = a1;
if ((s402) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L403, 1, 0, 0));
} else if ((s402) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L411, 1, 0, 0));
} else if ((s402) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L419, 2, 1, (V[]){a0}));
} else if (nat_ge(s402, 3)) {
return F_Parser_dbind(F_P_dexpect(S423()), mk_clo(L424, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrace_dtail(V *a) { (void)a; return F_P_dbrace_dtail(a[0], a[1]); }
static V S427(void) { static V c; return STRC(c, "]"); }
static V L426(V *a) {
return F_P_dbrack_dgo(F_P_dtok__is(a[0], S427()));
}
static V L425(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L426, 1, 0, 0));
}
static V F_P_dbrack(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L425, 1, 0, 0));
}
static V W_P_dbrack(V *a) { (void)a; return F_P_dbrack(); }
static V S430(void) { static V c; return STRC(c, "Nil"); }
static V L429(V *a) {
return F_Parser_dpure(C2(6, S430(), IMM(0)));
}
static V F_P_dbrack_dgo(V a0) {
top:;
V s428 = a0;
if ((s428) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L429, 1, 0, 0));
} else if ((s428) == IMM(0)) {
return F_P_dbrack_dbody();
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrack_dgo(V *a) { (void)a; return F_P_dbrack_dgo(a[0]); }
static V S433(void) { static V c; return STRC(c, ":"); }
static V L432(V *a) {
return F_P_dbrack_dtail(a[0], F_P_dtok__is(a[1], S433()));
}
static V L431(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L432, 2, 1, (V[]){a[0]}));
}
static V F_P_dbrack_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L431, 1, 0, 0));
}
static V W_P_dbrack_dbody(V *a) { (void)a; return F_P_dbrack_dbody(); }
static V S435(void) { static V c; return STRC(c, ","); }
static V S437(void) { static V c; return STRC(c, "]"); }
static V L438(V *a) {
return F_Parser_dpure(F_P_delist(C2(1, a[0], a[1])));
}
static V L436(V *a) {
return F_Parser_dbind(F_P_dlist(S437()), mk_clo(L438, 2, 1, (V[]){a[0]}));
}
static V F_P_dbrack_dtail(V a0, V a1) {
top:;
V s434 = a1;
if ((s434) == IMM(1)) {
return F_P_darr(a0);
} else if ((s434) == IMM(0)) {
return F_Parser_dbind(F_P_deat(S435()), mk_clo(L436, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrack_dtail(V *a) { (void)a; return F_P_dbrack_dtail(a[0], a[1]); }
static V S440(void) { static V c; return STRC(c, "Nil"); }
static V S441(void) { static V c; return STRC(c, "Con"); }
static V F_P_delist(V a0) {
top:;
V s439 = a0;
if ((s439) == IMM(0)) {
return C2(6, S440(), IMM(0));
} else if (TAG(s439) == 1) {
return C2(6, S441(), C2(1, FLD(s439, 0), C2(1, F_P_delist(FLD(s439, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_delist(V *a) { (void)a; return F_P_delist(a[0]); }
static V S447(void) { static V c; return STRC(c, "^"); }
static V S449(void) { static V c; return STRC(c, "]"); }
static V S451(void) { static V c; return STRC(c, "Array.new"); }
static V S452(void) { static V c; return STRC(c, ""); }
static V L450(V *a) {
return F_Parser_dpure(C2(5, C1(0, S451()), C2(1, C2(14, S452(), IMM(0)), C2(1, a[1], C2(1, a[0], IMM(0))))));
}
static V L448(V *a) {
return F_Parser_dbind(F_P_dexpect(S449()), mk_clo(L450, 3, 2, (V[]){a[0], a[1]}));
}
static V L446(V *a) {
return F_Parser_dbind(F_P_darr_dsize(F_P_dtok__is(a[1], S447()), a[2]), mk_clo(L448, 2, 1, (V[]){a[0]}));
}
static V L445(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L446, 3, 2, (V[]){a[0], a[1]}));
}
static V L444(V *a) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L445, 3, 2, (V[]){a[0], a[1]}));
}
static V L443(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L444, 2, 1, (V[]){a[0]}));
}
static V L442(V *a) {
return F_Parser_dbind(F_P_dterm(), mk_clo(L443, 2, 1, (V[]){a[0]}));
}
static V F_P_darr(V a0) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L442, 2, 1, (V[]){a0}));
}
static V W_P_darr(V *a) { (void)a; return F_P_darr(a[0]); }
static V F_P_darr_dsize(V a0, V a1) {
top:;
V s453 = a0;
if ((s453) == IMM(1)) {
return F_P_dterm();
} else if ((s453) == IMM(0)) {
return F_P_darr_dsize_dlit(a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_darr_dsize(V *a) { (void)a; return F_P_darr_dsize(a[0], a[1]); }
static V L455(V *a) {
return F_Parser_dpure(C1(2, F_P_dlog2(a[0])));
}
static V S456(void) { static V c; return STRC(c, "expected an array size"); }
static V L457(V *a) {
return F_Parser_dpure(C1(2, 0u));
}
static V F_P_darr_dsize_dlit(V a0) {
top:;
V s454 = a0;
if (TAG(FLD(s454, 0)) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L455, 2, 1, (V[]){FLD(FLD(s454, 0), 0)}));
} else {
return F_Parser_dbind(F_P_derr(S456()), mk_clo(L457, 1, 0, 0));
}
}
static V W_P_darr_dsize_dlit(V *a) { (void)a; return F_P_darr_dsize_dlit(a[0]); }
static V F_P_dlog2(V a0) {
top:;
return F_U32_dfrom__nat(F_U32_dlog2(a0));
}
static V W_P_dlog2(V *a) { (void)a; return F_P_dlog2(a[0]); }
static V W_U32_dlog2(V *a) { (void)a; return F_U32_dlog2(a[0]); }
static V W_U32_dfrom__nat(V *a) { (void)a; return F_U32_dfrom__nat(a[0]); }
static V S460(void) { static V c; return STRC(c, ")"); }
static V L459(V *a) {
return F_P_dparen_dgo(F_P_dtok__is(a[0], S460()));
}
static V L458(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L459, 1, 0, 0));
}
static V F_P_dparen(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L458, 1, 0, 0));
}
static V W_P_dparen(V *a) { (void)a; return F_P_dparen(); }
static V S463(void) { static V c; return STRC(c, "Unit"); }
static V L462(V *a) {
return F_Parser_dpure(C2(6, S463(), IMM(0)));
}
static V F_P_dparen_dgo(V a0) {
top:;
V s461 = a0;
if ((s461) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L462, 1, 0, 0));
} else if ((s461) == IMM(0)) {
return F_P_dparen_dbody();
} else { bend_fail("incomplete match"); }
}
static V W_P_dparen_dgo(V *a) { (void)a; return F_P_dparen_dgo(a[0]); }
static V S466(void) { static V c; return STRC(c, ","); }
static V S467(void) { static V c; return STRC(c, ":"); }
static V L465(V *a) {
return F_P_dparen_dtail(a[0], F_P_dtok__which(a[1], C2(1, S466(), C2(1, S467(), IMM(0)))));
}
static V L464(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L465, 2, 1, (V[]){a[0]}));
}
static V F_P_dparen_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L464, 1, 0, 0));
}
static V W_P_dparen_dbody(V *a) { (void)a; return F_P_dparen_dbody(); }
static V S470(void) { static V c; return STRC(c, ")"); }
static V L471(V *a) {
return F_Parser_dpure(F_P_dtuple(C2(1, a[0], a[1])));
}
static V L469(V *a) {
return F_Parser_dbind(F_P_dlist(S470()), mk_clo(L471, 2, 1, (V[]){a[0]}));
}
static V S474(void) { static V c; return STRC(c, ")"); }
static V L475(V *a) {
return F_Parser_dpure(C2(13, a[1], F_P_dhead(a[0])));
}
static V L473(V *a) {
return F_Parser_dbind(F_P_dexpect(S474()), mk_clo(L475, 3, 2, (V[]){a[1], a[0]}));
}
static V L472(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L473, 2, 1, (V[]){a[0]}));
}
static V S476(void) { static V c; return STRC(c, ")"); }
static V L477(V *a) {
return F_Parser_dpure(a[0]);
}
static V F_P_dparen_dtail(V a0, V a1) {
top:;
V s468 = a1;
if ((s468) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L469, 2, 1, (V[]){a0}));
} else if ((s468) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L472, 2, 1, (V[]){a0}));
} else if (nat_ge(s468, 2)) {
return F_Parser_dbind(F_P_dexpect(S476()), mk_clo(L477, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparen_dtail(V *a) { (void)a; return F_P_dparen_dtail(a[0], a[1]); }
static V S479(void) { static V c; return STRC(c, "Unit"); }
static V S480(void) { static V c; return STRC(c, "Tuple"); }
static V F_P_dtuple(V a0) {
top:;
V s478 = a0;
if ((s478) == IMM(0)) {
return C2(6, S479(), IMM(0));
} else if (TAG(s478) == 1 && (FLD(s478, 1)) == IMM(0)) {
return FLD(s478, 0);
} else if (TAG(s478) == 1) {
return C2(6, S480(), C2(1, FLD(s478, 0), C2(1, F_P_dtuple(FLD(s478, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtuple(V *a) { (void)a; return F_P_dtuple(a[0]); }
static V S481(void) { static V c; return STRC(c, "{"); }
static V S482(void) { static V c; return STRC(c, "<"); }
static V S483(void) { static V c; return STRC(c, "=>"); }
static V F_P_dafter__id(V a0, V a1) {
top:;
return F_P_dafter__id_dgo(a0, F_Bool_dpick(F_P_dtok__sp(a1), 3u, F_P_dtok__which(a1, C2(1, S481(), C2(1, S482(), IMM(0))))), F_P_dtok__is(a1, S483()));
}
static V W_P_dafter__id(V *a) { (void)a; return F_P_dafter__id(a[0], a[1]); }
static V L486(V *a) {
return F_Parser_dpure(C2(7, C1(0, a[0]), a[1]));
}
static V L485(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L486, 2, 1, (V[]){a[0]}));
}
static V F_P_dafter__id_dgo(V a0, V a1, V a2) {
top:;
V s484 = a2;
if ((s484) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L485, 2, 1, (V[]){a0}));
} else if ((s484) == IMM(0)) {
return F_P_dafter__id_dk(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dafter__id_dgo(V *a) { (void)a; return F_P_dafter__id_dgo(a[0], a[1], a[2]); }
static V S489(void) { static V c; return STRC(c, "}"); }
static V L490(V *a) {
return F_Parser_dpure(C2(6, a[0], a[1]));
}
static V L488(V *a) {
return F_Parser_dbind(F_P_dlist(S489()), mk_clo(L490, 2, 1, (V[]){a[0]}));
}
static V L492(V *a) {
return F_Parser_dpure(C2(14, a[0], a[1]));
}
static V L491(V *a) {
return F_Parser_dbind(F_P_dtyargs(), mk_clo(L492, 2, 1, (V[]){a[0]}));
}
static V F_P_dafter__id_dk(V a0, V a1) {
top:;
V s487 = a1;
if ((s487) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L488, 2, 1, (V[]){a0}));
} else if ((s487) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L491, 2, 1, (V[]){a0}));
} else if (nat_ge(s487, 2)) {
return F_Parser_dpure(C1(0, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dafter__id_dk(V *a) { (void)a; return F_P_dafter__id_dk(a[0], a[1]); }
static V L493(V *a) {
return F_P_dtyargs_dgo(a[0], F_P_dstuck(F_P_dtok__kind(a[0])));
}
static V F_P_dtyargs(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L493, 1, 0, 0));
}
static V W_P_dtyargs(V *a) { (void)a; return F_P_dtyargs(); }
static V F_P_dtyargs_dgo(V a0, V a1) {
top:;
V s494 = a1;
if ((s494) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s494) == IMM(0)) {
return F_P_dtyargs_dclose(F_P_dis__gt(a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtyargs_dgo(V *a) { (void)a; return F_P_dtyargs_dgo(a[0], a[1]); }
static V S495(void) { static V c; return STRC(c, ">"); }
static V S496(void) { static V c; return STRC(c, ">>"); }
static V S497(void) { static V c; return STRC(c, ">="); }
static V F_P_dis__gt(V a0) {
top:;
return F_Bool_dor(F_P_dtok__is(a0, S495()), F_Bool_dor(F_P_dtok__is(a0, S496()), F_P_dtok__is(a0, S497())));
}
static V W_P_dis__gt(V *a) { (void)a; return F_P_dis__gt(a[0]); }
static V L499(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dtyargs_dclose(V a0) {
top:;
V s498 = a0;
if ((s498) == IMM(1)) {
return F_Parser_dbind(F_P_dgt(), mk_clo(L499, 1, 0, 0));
} else if ((s498) == IMM(0)) {
return F_P_dtyargs_ditem();
} else { bend_fail("incomplete match"); }
}
static V W_P_dtyargs_dclose(V *a) { (void)a; return F_P_dtyargs_dclose(a[0]); }
static V S501(void) { static V c; return STRC(c, ","); }
static V L503(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L502(V *a) {
return F_Parser_dbind(F_P_dtyargs_dmore(a[1]), mk_clo(L503, 2, 1, (V[]){a[0]}));
}
static V L500(V *a) {
return F_Parser_dbind(F_P_deat(S501()), mk_clo(L502, 2, 1, (V[]){a[0]}));
}
static V F_P_dtyargs_ditem(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L500, 1, 0, 0));
}
static V W_P_dtyargs_ditem(V *a) { (void)a; return F_P_dtyargs_ditem(); }
static V L505(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dtyargs_dmore(V a0) {
top:;
V s504 = a0;
if ((s504) == IMM(1)) {
return F_P_dtyargs();
} else if ((s504) == IMM(0)) {
return F_Parser_dbind(F_P_dgt(), mk_clo(L505, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtyargs_dmore(V *a) { (void)a; return F_P_dtyargs_dmore(a[0]); }
static V L506(V *a) {
return F_P_dgt_dgo(a[0]);
}
static V F_P_dgt(void) {
top:;
return mk_clo(L506, 1, 0, 0);
}
static V W_P_dgt(V *a) { (void)a; return F_P_dgt(); }
static V S508(void) { static V c; return STRC(c, ">"); }
static V S509(void) { static V c; return STRC(c, ">>"); }
static V S510(void) { static V c; return STRC(c, ">="); }
static V S511(void) { static V c; return STRC(c, "expected '>'"); }
static V F_P_dgt_dgo(V a0) {
top:;
V s507 = a0;
if (TAG(s507) == 1 && TAG(FLD(FLD(s507, 0), 0)) == 7) {
return F_P_dgt_dif(FLD(FLD(FLD(s507, 0), 0), 0), FLD(FLD(s507, 0), 1), FLD(FLD(s507, 0), 2), FLD(s507, 1), F_P_dwhich(FLD(FLD(FLD(s507, 0), 0), 0), C2(1, S508(), C2(1, S509(), C2(1, S510(), IMM(0))))));
} else {
return F_P_derr_dgo(S511(), s507);
}
}
static V W_P_dgt_dgo(V *a) { (void)a; return F_P_dgt_dgo(a[0]); }
static V S513(void) { static V c; return STRC(c, ">"); }
static V S514(void) { static V c; return STRC(c, "="); }
static V S515(void) { static V c; return STRC(c, "expected '>'"); }
static V F_P_dgt_dif(V a0, V a1, V a2, V a3, V a4) {
top:;
V s512 = a4;
if ((s512) == 0) {
return C2(0, IMM(0), a3);
} else if ((s512) == 1) {
return C2(0, IMM(0), C2(1, C3(0, C1(7, S513()), IMM(0), a2), a3));
} else if ((s512) == 2) {
return C2(0, IMM(0), C2(1, C3(0, C1(7, S514()), IMM(0), a2), a3));
} else if (nat_ge(s512, 3)) {
return F_P_derr_dgo(S515(), C2(1, C3(0, C1(7, a0), a1, a2), a3));
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
V s516 = a0;
if ((s516) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s516) == IMM(0)) {
return F_P_dskip();
} else { bend_fail("incomplete match"); }
}
static V W_P_dparam_dskip__mode_dgo(V *a) { (void)a; return F_P_dparam_dskip__mode_dgo(a[0]); }
static V S517(void) { static V c; return STRC(c, "-"); }
static V S518(void) { static V c; return STRC(c, "+"); }
static V S519(void) { static V c; return STRC(c, "~"); }
static V F_P_dparam_dmode(V a0) {
top:;
return F_Bool_dpick(F_P_dtok__is(a0, S517()), 1u, F_Bool_dpick(F_P_dtok__is(a0, S518()), 2u, F_Bool_dpick(F_P_dtok__is(a0, S519()), 3u, 0u)));
}
static V W_P_dparam_dmode(V *a) { (void)a; return F_P_dparam_dmode(a[0]); }
static V L520(V *a) {
return F_P_dnls_dif(F_P_dis__nl(a[0]));
}
static V F_P_dnls(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L520, 1, 0, 0));
}
static V W_P_dnls(V *a) { (void)a; return F_P_dnls(); }
static V F_P_dis__nl(V a0) {
top:;
V s521 = a0;
if ((FLD(s521, 0)) == IMM(8)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dis__nl(V *a) { (void)a; return F_P_dis__nl(a[0]); }
static V L523(V *a) {
return F_P_dnls();
}
static V F_P_dnls_dif(V a0) {
top:;
V s522 = a0;
if ((s522) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L523, 1, 0, 0));
} else if ((s522) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dnls_dif(V *a) { (void)a; return F_P_dnls_dif(a[0]); }
static V L524(V *a) {
return F_P_dexpect__in_dgo(F_P_dis__in(a[0]));
}
static V F_P_dexpect__in(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L524, 1, 0, 0));
}
static V W_P_dexpect__in(V *a) { (void)a; return F_P_dexpect__in(); }
static V F_P_dis__in(V a0) {
top:;
V s525 = a0;
if ((FLD(s525, 0)) == IMM(9)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dis__in(V *a) { (void)a; return F_P_dis__in(a[0]); }
static V S527(void) { static V c; return STRC(c, "expected an indented block"); }
static V F_P_dexpect__in_dgo(V a0) {
top:;
V s526 = a0;
if ((s526) == IMM(1)) {
return F_P_dskip();
} else if ((s526) == IMM(0)) {
return F_P_derr(S527());
} else { bend_fail("incomplete match"); }
}
static V W_P_dexpect__in_dgo(V *a) { (void)a; return F_P_dexpect__in_dgo(a[0]); }
static V S531(void) { static V c; return STRC(c, "<"); }
static V S532(void) { static V c; return STRC(c, "<-"); }
static V S536(void) { static V c; return STRC(c, ":"); }
static V L539(V *a) {
return F_Parser_dpure(C3(3, a[1], a[0], a[2]));
}
static V L538(V *a) {
return F_Parser_dbind(F_P_dtype_dbody(F_P_dis__in(a[2])), mk_clo(L539, 3, 2, (V[]){a[0], a[1]}));
}
static V L537(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L538, 3, 2, (V[]){a[0], a[1]}));
}
static V L535(V *a) {
return F_Parser_dbind(F_P_dexpect(S536()), mk_clo(L537, 3, 2, (V[]){a[0], a[1]}));
}
static V L534(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L535, 3, 2, (V[]){a[0], a[1]}));
}
static V L533(V *a) {
return F_Parser_dbind(F_P_duntil__is(), mk_clo(L534, 3, 2, (V[]){a[1], a[0]}));
}
static V L530(V *a) {
return F_Parser_dbind(F_P_dtparams_dopt(F_P_dtok__which(a[1], C2(1, S531(), C2(1, S532(), IMM(0))))), mk_clo(L533, 2, 1, (V[]){a[0]}));
}
static V L529(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L530, 2, 1, (V[]){a[0]}));
}
static V L528(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L529, 1, 0, 0));
}
static V F_P_dtype(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L528, 1, 0, 0));
}
static V W_P_dtype(V *a) { (void)a; return F_P_dtype(); }
static V L541(V *a) {
return F_P_dctors();
}
static V F_P_dtype_dbody(V a0) {
top:;
V s540 = a0;
if ((s540) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L541, 1, 0, 0));
} else if ((s540) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtype_dbody(V *a) { (void)a; return F_P_dtype_dbody(a[0]); }
static V L543(V *a) {
return F_P_dctors_dgo(a[0], F_Bool_dpick(F_P_dis__de(a[0]), 0u, F_Bool_dpick(F_P_dstuck(F_P_dtok__kind(a[0])), 1u, 2u)));
}
static V L542(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L543, 1, 0, 0));
}
static V F_P_dctors(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L542, 1, 0, 0));
}
static V W_P_dctors(V *a) { (void)a; return F_P_dctors(); }
static V L545(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S547(void) { static V c; return STRC(c, "{"); }
static V L550(V *a) {
return F_Parser_dpure(C2(1, C2(0, a[1], a[0]), a[2]));
}
static V L549(V *a) {
return F_Parser_dbind(F_P_dctors(), mk_clo(L550, 3, 2, (V[]){a[1], a[0]}));
}
static V L548(V *a) {
return F_Parser_dbind(F_P_dfields(), mk_clo(L549, 2, 1, (V[]){a[0]}));
}
static V L546(V *a) {
return F_Parser_dbind(F_P_dexpect(S547()), mk_clo(L548, 2, 1, (V[]){a[0]}));
}
static V F_P_dctors_dgo(V a0, V a1) {
top:;
V s544 = a1;
if ((s544) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L545, 1, 0, 0));
} else if ((s544) == 1) {
return F_Parser_dpure(IMM(0));
} else if (nat_ge(s544, 2)) {
return F_Parser_dbind(F_P_dident(), mk_clo(L546, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dctors_dgo(V *a) { (void)a; return F_P_dctors_dgo(a[0], a[1]); }
static V S552(void) { static V c; return STRC(c, "}"); }
static V L551(V *a) {
return F_P_dfields_dgo(F_Bool_dor(F_P_dtok__is(a[0], S552()), F_P_dstuck(F_P_dtok__kind(a[0]))));
}
static V F_P_dfields(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L551, 1, 0, 0));
}
static V W_P_dfields(V *a) { (void)a; return F_P_dfields(); }
static V L554(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S555(void) { static V c; return STRC(c, "+"); }
static V S557(void) { static V c; return STRC(c, "-"); }
static V S560(void) { static V c; return STRC(c, ":"); }
static V S563(void) { static V c; return STRC(c, ","); }
static V L565(V *a) {
return F_Parser_dpure(C2(1, C2(0, a[1], a[0]), a[2]));
}
static V L564(V *a) {
return F_Parser_dbind(F_P_dfields(), mk_clo(L565, 3, 2, (V[]){a[0], a[1]}));
}
static V L562(V *a) {
return F_Parser_dbind(F_P_deat(S563()), mk_clo(L564, 3, 2, (V[]){a[1], a[0]}));
}
static V L561(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L562, 2, 1, (V[]){a[0]}));
}
static V L559(V *a) {
return F_Parser_dbind(F_P_dexpect(S560()), mk_clo(L561, 2, 1, (V[]){a[0]}));
}
static V L558(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L559, 1, 0, 0));
}
static V L556(V *a) {
return F_Parser_dbind(F_P_deat(S557()), mk_clo(L558, 1, 0, 0));
}
static V F_P_dfields_dgo(V a0) {
top:;
V s553 = a0;
if ((s553) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L554, 1, 0, 0));
} else if ((s553) == IMM(0)) {
return F_Parser_dbind(F_P_deat(S555()), mk_clo(L556, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dfields_dgo(V *a) { (void)a; return F_P_dfields_dgo(a[0]); }
static V L566(V *a) {
return C2(0, IMM(0), F_P_duntil__is_dgo(a[0]));
}
static V F_P_duntil__is(void) {
top:;
return mk_clo(L566, 1, 0, 0);
}
static V W_P_duntil__is(V *a) { (void)a; return F_P_duntil__is(); }
static V S568(void) { static V c; return STRC(c, "is"); }
static V F_P_duntil__is_dgo(V a0) {
top:;
V s567 = a0;
if ((s567) == IMM(0)) {
return IMM(0);
} else if (TAG(s567) == 1 && TAG(FLD(FLD(s567, 0), 0)) == 0) {
return F_P_duntil__is_dif(C3(0, C1(0, FLD(FLD(FLD(s567, 0), 0), 0)), FLD(FLD(s567, 0), 1), FLD(FLD(s567, 0), 2)), FLD(s567, 1), F_Str_deq(FLD(FLD(FLD(s567, 0), 0), 0), S568()));
} else if (TAG(s567) == 1 && (FLD(FLD(s567, 0), 0)) == IMM(11)) {
return C2(1, C3(0, IMM(11), FLD(FLD(s567, 0), 1), FLD(FLD(s567, 0), 2)), FLD(s567, 1));
} else if (TAG(s567) == 1 && TAG(FLD(FLD(s567, 0), 0)) == 12) {
return C2(1, C3(0, C1(12, FLD(FLD(FLD(s567, 0), 0), 0)), FLD(FLD(s567, 0), 1), FLD(FLD(s567, 0), 2)), FLD(s567, 1));
} else if (TAG(s567) == 1) {
{ V t0 = FLD(s567, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_duntil__is_dgo(V *a) { (void)a; return F_P_duntil__is_dgo(a[0]); }
static V F_P_duntil__is_dif(V a0, V a1, V a2) {
top:;
V s569 = a2;
if ((s569) == IMM(1)) {
return a1;
} else if ((s569) == IMM(0)) {
return F_P_duntil__is_dgo(a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_duntil__is_dif(V *a) { (void)a; return F_P_duntil__is_dif(a[0], a[1], a[2]); }
static V L571(V *a) {
return F_P_dtparams();
}
static V L572(V *a) {
return F_P_dtparams();
}
static V F_P_dtparams_dopt(V a0) {
top:;
V s570 = a0;
if ((s570) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L571, 1, 0, 0));
} else if ((s570) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L572, 1, 0, 0));
} else if (nat_ge(s570, 2)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtparams_dopt(V *a) { (void)a; return F_P_dtparams_dopt(a[0]); }
static V S573(void) { static V c; return STRC(c, "-"); }
static V S577(void) { static V c; return STRC(c, ","); }
static V L579(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L578(V *a) {
return F_Parser_dbind(F_P_dtparams_dmore(a[1]), mk_clo(L579, 2, 1, (V[]){a[0]}));
}
static V L576(V *a) {
return F_Parser_dbind(F_P_deat(S577()), mk_clo(L578, 2, 1, (V[]){a[0]}));
}
static V L575(V *a) {
return F_Parser_dbind(F_P_dskip__ann(), mk_clo(L576, 2, 1, (V[]){a[0]}));
}
static V L574(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L575, 1, 0, 0));
}
static V F_P_dtparams(void) {
top:;
return F_Parser_dbind(F_P_deat(S573()), mk_clo(L574, 1, 0, 0));
}
static V W_P_dtparams(V *a) { (void)a; return F_P_dtparams(); }
static V L581(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dtparams_dmore(V a0) {
top:;
V s580 = a0;
if ((s580) == IMM(1)) {
return F_P_dtparams();
} else if ((s580) == IMM(0)) {
return F_Parser_dbind(F_P_dgt(), mk_clo(L581, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtparams_dmore(V *a) { (void)a; return F_P_dtparams_dmore(a[0]); }
static V S583(void) { static V c; return STRC(c, ":"); }
static V L582(V *a) {
return F_P_dskip__ann_dgo(F_P_dtok__is(a[0], S583()));
}
static V F_P_dskip__ann(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L582, 1, 0, 0));
}
static V W_P_dskip__ann(V *a) { (void)a; return F_P_dskip__ann(); }
static V L586(V *a) {
return F_Parser_dpure(IMM(0));
}
static V L585(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L586, 1, 0, 0));
}
static V F_P_dskip__ann_dgo(V a0) {
top:;
V s584 = a0;
if ((s584) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L585, 1, 0, 0));
} else if ((s584) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__ann_dgo(V *a) { (void)a; return F_P_dskip__ann_dgo(a[0]); }
static V S589(void) { static V c; return STRC(c, "("); }
static V S593(void) { static V c; return STRC(c, "->"); }
static V S595(void) { static V c; return STRC(c, ":"); }
static V S599(void) { static V c; return STRC(c, "import"); }
static V L598(V *a) {
return F_P_ddef_dbody(a[2], a[1], a[0], F_P_dtok__is__id(a[3], S599()));
}
static V L597(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L598, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L596(V *a) {
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L597, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L594(V *a) {
return F_Parser_dbind(F_P_dexpect(S595()), mk_clo(L596, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L592(V *a) {
return F_Parser_dbind(F_P_dret_dgo(F_P_dtok__is(a[2], S593())), mk_clo(L594, 3, 2, (V[]){a[0], a[1]}));
}
static V L591(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L592, 3, 2, (V[]){a[1], a[0]}));
}
static V L590(V *a) {
return F_Parser_dbind(F_P_dparams(), mk_clo(L591, 2, 1, (V[]){a[0]}));
}
static V L588(V *a) {
return F_Parser_dbind(F_P_dexpect(S589()), mk_clo(L590, 2, 1, (V[]){a[0]}));
}
static V L587(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L588, 1, 0, 0));
}
static V F_P_ddef(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L587, 1, 0, 0));
}
static V W_P_ddef(V *a) { (void)a; return F_P_ddef(); }
static V L601(V *a) {
return F_Parser_dpure(C3(1, a[1], a[0], a[2]));
}
static V L602(V *a) {
return F_Parser_dpure(C4(0, a[2], a[1], F_Fold_dplain(a[3]), a[0]));
}
static V F_P_ddef_dbody(V a0, V a1, V a2, V a3) {
top:;
V s600 = a3;
if ((s600) == IMM(1)) {
return F_Parser_dbind(F_P_deff_dimports(), mk_clo(L601, 3, 2, (V[]){a1, a0}));
} else if ((s600) == IMM(0)) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L602, 4, 3, (V[]){a2, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddef_dbody(V *a) { (void)a; return F_P_ddef_dbody(a[0], a[1], a[2], a[3]); }
static V S604(void) { static V c; return STRC(c, "empty block"); }
static V S605(void) { static V c; return STRC(c, ""); }
static V S606(void) { static V c; return STRC(c, "_"); }
static V F_Fold_dplain(V a0) {
top:;
V s603 = a0;
if ((s603) == IMM(0)) {
return C1(15, S604());
} else if (TAG(s603) == 1 && TAG(FLD(s603, 0)) == 0 && (FLD(s603, 1)) == IMM(0)) {
return FLD(FLD(s603, 0), 1);
} else if (TAG(s603) == 1 && TAG(FLD(s603, 0)) == 1 && (FLD(s603, 1)) == IMM(0)) {
return FLD(FLD(s603, 0), 1);
} else if (TAG(s603) == 1 && TAG(FLD(s603, 0)) == 2 && (FLD(s603, 1)) == IMM(0)) {
return FLD(FLD(s603, 0), 0);
} else if (TAG(s603) == 1 && TAG(FLD(s603, 0)) == 3 && (FLD(s603, 1)) == IMM(0)) {
return FLD(FLD(s603, 0), 0);
} else if (TAG(s603) == 1 && (FLD(s603, 0)) == IMM(4) && (FLD(s603, 1)) == IMM(0)) {
return C2(14, S605(), IMM(0));
} else if (TAG(s603) == 1 && TAG(FLD(s603, 0)) == 0) {
return C3(8, FLD(FLD(s603, 0), 0), FLD(FLD(s603, 0), 1), F_Fold_dplain(FLD(s603, 1)));
} else if (TAG(s603) == 1 && TAG(FLD(s603, 0)) == 1) {
return C3(8, C1(0, FLD(FLD(s603, 0), 0)), FLD(FLD(s603, 0), 1), F_Fold_dplain(FLD(s603, 1)));
} else if (TAG(s603) == 1 && TAG(FLD(s603, 0)) == 2) {
return FLD(FLD(s603, 0), 0);
} else if (TAG(s603) == 1 && TAG(FLD(s603, 0)) == 3) {
return C3(8, C1(0, S606()), FLD(FLD(s603, 0), 0), F_Fold_dplain(FLD(s603, 1)));
} else if (TAG(s603) == 1 && (FLD(s603, 0)) == IMM(4)) {
{ V t0 = FLD(s603, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Fold_dplain(V *a) { (void)a; return F_Fold_dplain(a[0]); }
static V L608(V *a) {
return F_P_dstmts_dgo(a[0], F_Bool_dpick(F_P_dis__de(a[0]), 0u, F_Bool_dpick(F_P_dstuck(F_P_dtok__kind(a[0])), 1u, 2u)));
}
static V L607(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L608, 1, 0, 0));
}
static V F_P_dstmts(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L607, 1, 0, 0));
}
static V W_P_dstmts(V *a) { (void)a; return F_P_dstmts(); }
static V L610(V *a) {
return F_Parser_dpure(IMM(0));
}
static V L612(V *a) {
return F_Parser_dpure(F_List_dappend(a[0], a[1]));
}
static V L611(V *a) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L612, 2, 1, (V[]){a[0]}));
}
static V F_P_dstmts_dgo(V a0, V a1) {
top:;
V s609 = a1;
if ((s609) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L610, 1, 0, 0));
} else if ((s609) == 1) {
return F_Parser_dpure(IMM(0));
} else if (nat_ge(s609, 2)) {
return F_Parser_dbind(F_P_dstmt(), mk_clo(L611, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmts_dgo(V *a) { (void)a; return F_P_dstmts_dgo(a[0], a[1]); }
static V F_List_dappend(V a2, V a3) {
top:;
V s613 = a2;
if ((s613) == IMM(0)) {
return a3;
} else if (TAG(s613) == 1) {
return C2(1, FLD(s613, 0), F_List_dappend(FLD(s613, 1), a3));
} else { bend_fail("incomplete match"); }
}
static V W_List_dappend(V *a) { (void)a; return F_List_dappend(a[2], a[3]); }
static V S615(void) { static V c; return STRC(c, "%"); }
static V L614(V *a) {
return F_P_dstmt_dgo(a[0], F_P_dtok__is(a[0], S615()));
}
static V F_P_dstmt(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L614, 1, 0, 0));
}
static V W_P_dstmt(V *a) { (void)a; return F_P_dstmt(); }
static V L617(V *a) {
return F_Parser_dpure(C2(1, IMM(4), IMM(0)));
}
static V S618(void) { static V c; return STRC(c, "match"); }
static V S619(void) { static V c; return STRC(c, "return"); }
static V S620(void) { static V c; return STRC(c, "do"); }
static V F_P_dstmt_dgo(V a0, V a1) {
top:;
V s616 = a1;
if ((s616) == IMM(1)) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L617, 1, 0, 0));
} else if ((s616) == IMM(0)) {
return F_P_dstmt_did(F_P_dtok__which__id(a0, C2(1, S618(), C2(1, S619(), C2(1, S620(), IMM(0))))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmt_dgo(V *a) { (void)a; return F_P_dstmt_dgo(a[0], a[1]); }
static V L622(V *a) {
return F_Parser_dpure(C2(1, C1(3, a[0]), IMM(0)));
}
static V L624(V *a) {
return F_Parser_dpure(C2(1, C1(2, a[0]), IMM(0)));
}
static V L623(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L624, 1, 0, 0));
}
static V L625(V *a) {
return F_Parser_dpure(C2(1, C1(3, a[0]), IMM(0)));
}
static V L626(V *a) {
return F_P_dstmt_dscan(a[0]);
}
static V F_P_dstmt_did(V a0) {
top:;
V s621 = a0;
if ((s621) == 0) {
return F_Parser_dbind(F_P_dmatch(), mk_clo(L622, 1, 0, 0));
} else if ((s621) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L623, 1, 0, 0));
} else if ((s621) == 2) {
return F_Parser_dbind(F_P_ddo(), mk_clo(L625, 1, 0, 0));
} else if (nat_ge(s621, 3)) {
return F_Parser_dbind(F_P_dscan(), mk_clo(L626, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmt_did(V *a) { (void)a; return F_P_dstmt_did(a[0]); }
static V F_P_dstmt_dscan(V a0) {
top:;
return F_P_dstmt_dscan_dgo(F_U32_dto__nat(a0));
}
static V W_P_dstmt_dscan(V *a) { (void)a; return F_P_dstmt_dscan(a[0]); }
static V W_U32_dto__nat(V *a) { (void)a; return F_U32_dto__nat(a[0]); }
static V L628(V *a) {
return F_Parser_dpure(C2(1, C1(3, a[0]), IMM(0)));
}
static V F_P_dstmt_dscan_dgo(V a0) {
top:;
V s627 = a0;
if ((s627) == 0) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L628, 1, 0, 0));
} else if ((s627) == 1) {
return F_P_dlet__stmt();
} else if (nat_ge(s627, 2)) {
return F_P_dbind__stmt();
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmt_dscan_dgo(V *a) { (void)a; return F_P_dstmt_dscan_dgo(a[0]); }
static V S629(void) { static V c; return STRC(c, "+"); }
static V S633(void) { static V c; return STRC(c, "["); }
static V L632(V *a) {
return F_P_dbind_darr(a[0], F_Bool_dand(F_P_dtok__is(a[1], S633()), F_Bool_dnot(F_P_dtok__sp(a[1]))));
}
static V L631(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L632, 2, 1, (V[]){a[0]}));
}
static V L630(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L631, 1, 0, 0));
}
static V F_P_dbind__stmt(void) {
top:;
return F_Parser_dbind(F_P_deat(S629()), mk_clo(L630, 1, 0, 0));
}
static V W_P_dbind__stmt(V *a) { (void)a; return F_P_dbind__stmt(); }
static V F_Bool_dnot(V a0) {
top:;
V s634 = a0;
if ((s634) == IMM(0)) {
return IMM(1);
} else if ((s634) == IMM(1)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dnot(V *a) { (void)a; return F_Bool_dnot(a[0]); }
static V S638(void) { static V c; return STRC(c, "]"); }
static V S640(void) { static V c; return STRC(c, "<-"); }
static V S643(void) { static V c; return STRC(c, "Array.set"); }
static V S644(void) { static V c; return STRC(c, "U32"); }
static V L642(V *a) {
return F_Parser_dpure(C2(1, C2(0, C1(0, a[1]), C2(5, C1(0, S643()), C2(1, C2(14, S644(), IMM(0)), C2(1, C1(0, a[1]), C2(1, a[0], C2(1, a[2], IMM(0))))))), IMM(0)));
}
static V L641(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L642, 3, 2, (V[]){a[0], a[1]}));
}
static V L639(V *a) {
return F_Parser_dbind(F_P_dexpect(S640()), mk_clo(L641, 3, 2, (V[]){a[0], a[1]}));
}
static V L637(V *a) {
return F_Parser_dbind(F_P_dexpect(S638()), mk_clo(L639, 3, 2, (V[]){a[1], a[0]}));
}
static V L636(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L637, 2, 1, (V[]){a[0]}));
}
static V S646(void) { static V c; return STRC(c, "<-"); }
static V L648(V *a) {
return F_Parser_dpure(C2(1, C2(1, a[0], a[1]), IMM(0)));
}
static V L647(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L648, 2, 1, (V[]){a[0]}));
}
static V L645(V *a) {
return F_Parser_dbind(F_P_dexpect(S646()), mk_clo(L647, 2, 1, (V[]){a[0]}));
}
static V F_P_dbind_darr(V a0, V a1) {
top:;
V s635 = a1;
if ((s635) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L636, 2, 1, (V[]){a0}));
} else if ((s635) == IMM(0)) {
return F_Parser_dbind(F_P_dskip__ann(), mk_clo(L645, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbind_darr(V *a) { (void)a; return F_P_dbind_darr(a[0], a[1]); }
static V S649(void) { static V c; return STRC(c, "="); }
static V S650(void) { static V c; return STRC(c, ":"); }
static V S653(void) { static V c; return STRC(c, "="); }
static V L655(V *a) {
return F_Parser_dpure(F_P_dlets_dpar(a[0], a[1]));
}
static V L654(V *a) {
return F_Parser_dbind(F_P_dexprs__n(F_List_dlength(a[0])), mk_clo(L655, 2, 1, (V[]){a[0]}));
}
static V L652(V *a) {
return F_Parser_dbind(F_P_dexpect(S653()), mk_clo(L654, 2, 1, (V[]){a[0]}));
}
static V L651(V *a) {
return F_Parser_dbind(F_P_dskip__ann(), mk_clo(L652, 2, 1, (V[]){a[0]}));
}
static V F_P_dlet__stmt(void) {
top:;
return F_Parser_dbind(F_P_dpat__seq(C2(1, S649(), C2(1, S650(), IMM(0)))), mk_clo(L651, 1, 0, 0));
}
static V W_P_dlet__stmt(V *a) { (void)a; return F_P_dlet__stmt(); }
static V S656(void) { static V c; return STRC(c, "%par"); }
static V S657(void) { static V c; return STRC(c, "%par"); }
static V F_P_dlets_dpar(V a0, V a1) {
top:;
return F_Bool_dpick(F_Nat_dis__gt(F_List_dlength(a0), 1u), C2(1, C2(0, C2(1, S656(), a0), C2(6, S657(), a1)), IMM(0)), F_P_dlets(a0, a1));
}
static V W_P_dlets_dpar(V *a) { (void)a; return F_P_dlets_dpar(a[0], a[1]); }
static V F_P_dlets(V a0, V a1) {
top:;
V s658 = a0;
V s659 = a1;
if (TAG(s658) == 1 && TAG(s659) == 1) {
return C2(1, C2(0, FLD(s658, 0), FLD(s659, 0)), F_P_dlets(FLD(s658, 1), FLD(s659, 1)));
} else {
return IMM(0);
}
}
static V W_P_dlets(V *a) { (void)a; return F_P_dlets(a[0], a[1]); }
static V F_List_dlength(V a2) {
top:;
V s660 = a2;
if ((s660) == IMM(0)) {
return 0u;
} else if (TAG(s660) == 1) {
return nat_addk(F_List_dlength(FLD(s660, 1)), 1);
} else { bend_fail("incomplete match"); }
}
static V W_List_dlength(V *a) { (void)a; return F_List_dlength(a[2]); }
static V W_Nat_dis__gt(V *a) { (void)a; return F_Nat_dis__gt(a[0], a[1]); }
static V L663(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L662(V *a) {
return F_Parser_dbind(F_P_dexprs__n(a[0]), mk_clo(L663, 2, 1, (V[]){a[1]}));
}
static V F_P_dexprs__n(V a0) {
top:;
V s661 = a0;
if ((s661) == 0) {
return F_Parser_dpure(IMM(0));
} else if (nat_ge(s661, 1)) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L662, 2, 1, (V[]){nat_subk(s661, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dexprs__n(V *a) { (void)a; return F_P_dexprs__n(a[0]); }
static V L664(V *a) {
return F_P_dpat__seq_dgo(a[0], a[1], F_P_dpat__seq_dstop(a[0], a[1]));
}
static V F_P_dpat__seq(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L664, 2, 1, (V[]){a0}));
}
static V W_P_dpat__seq(V *a) { (void)a; return F_P_dpat__seq(a[0]); }
static V F_P_dpat__seq_dstop(V a0, V a1) {
top:;
return F_Bool_dor(F_P_dstuck(F_P_dtok__kind(a1)), F_Bool_dor(F_P_dis__nl(a1), F_Nat_dis__lt(F_P_dtok__which(a1, a0), F_List_dlength(a0))));
}
static V W_P_dpat__seq_dstop(V *a) { (void)a; return F_P_dpat__seq_dstop(a[0], a[1]); }
static V W_Nat_dis__lt(V *a) { (void)a; return F_Nat_dis__lt(a[0], a[1]); }
static V L667(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L666(V *a) {
return F_Parser_dbind(F_P_dpat__seq(a[0]), mk_clo(L667, 2, 1, (V[]){a[1]}));
}
static V F_P_dpat__seq_dgo(V a0, V a1, V a2) {
top:;
V s665 = a2;
if ((s665) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s665) == IMM(0)) {
return F_Parser_dbind(F_P_dpat(), mk_clo(L666, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat__seq_dgo(V *a) { (void)a; return F_P_dpat__seq_dgo(a[0], a[1], a[2]); }
static V S670(void) { static V c; return STRC(c, "<>"); }
static V L669(V *a) {
return F_P_dpat_dcons(a[0], F_P_dtok__is(a[1], S670()));
}
static V L668(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L669, 2, 1, (V[]){a[0]}));
}
static V F_P_dpat(void) {
top:;
return F_Parser_dbind(F_P_dpat1(), mk_clo(L668, 1, 0, 0));
}
static V W_P_dpat(V *a) { (void)a; return F_P_dpat(); }
static V S674(void) { static V c; return STRC(c, "Con"); }
static V L673(V *a) {
return F_Parser_dpure(C2(1, S674(), C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V L672(V *a) {
return F_Parser_dbind(F_P_dpat(), mk_clo(L673, 2, 1, (V[]){a[0]}));
}
static V F_P_dpat_dcons(V a0, V a1) {
top:;
V s671 = a1;
if ((s671) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L672, 2, 1, (V[]){a0}));
} else if ((s671) == IMM(0)) {
return F_Parser_dpure(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat_dcons(V *a) { (void)a; return F_P_dpat_dcons(a[0], a[1]); }
static V L675(V *a) {
return F_P_dpat1_dk(F_P_dtok__kind(a[0]));
}
static V F_P_dpat1(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L675, 1, 0, 0));
}
static V W_P_dpat1(V *a) { (void)a; return F_P_dpat1(); }
static V S679(void) { static V c; return STRC(c, "{"); }
static V L678(V *a) {
return F_P_dpat_did(a[0], F_Bool_dand(F_P_dtok__is(a[1], S679()), F_Bool_dnot(F_P_dtok__sp(a[1]))));
}
static V L677(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L678, 2, 1, (V[]){a[0]}));
}
static V L680(V *a) {
return F_Parser_dpure(C1(2, a[0]));
}
static V L682(V *a) {
return F_Parser_dpure(C2(3, a[0], a[1]));
}
static V L681(V *a) {
return F_Parser_dbind(F_P_dpat1(), mk_clo(L682, 2, 1, (V[]){a[0]}));
}
static V L683(V *a) {
return F_Parser_dpure(C1(4, a[0]));
}
static V L684(V *a) {
return F_Parser_dpure(C1(4, a[0]));
}
static V L685(V *a) {
return F_Parser_dpure(F_P_dpstr(a[0]));
}
static V S686(void) { static V c; return STRC(c, "+"); }
static V S687(void) { static V c; return STRC(c, "-"); }
static V S688(void) { static V c; return STRC(c, "("); }
static V S689(void) { static V c; return STRC(c, "["); }
static V S690(void) { static V c; return STRC(c, "expected a pattern"); }
static V S692(void) { static V c; return STRC(c, "_"); }
static V L691(V *a) {
return F_Parser_dpure(C1(0, S692()));
}
static V F_P_dpat1_dk(V a0) {
top:;
V s676 = a0;
if (TAG(s676) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L677, 2, 1, (V[]){FLD(s676, 0)}));
} else if (TAG(s676) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L680, 2, 1, (V[]){FLD(s676, 0)}));
} else if (TAG(s676) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L681, 2, 1, (V[]){FLD(s676, 0)}));
} else if (TAG(s676) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L683, 2, 1, (V[]){FLD(s676, 0)}));
} else if (TAG(s676) == 5) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L684, 2, 1, (V[]){FLD(s676, 0)}));
} else if (TAG(s676) == 6) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L685, 2, 1, (V[]){FLD(s676, 0)}));
} else if (TAG(s676) == 7) {
return F_P_dpat_dsym(F_P_dwhich(FLD(s676, 0), C2(1, S686(), C2(1, S687(), C2(1, S688(), C2(1, S689(), IMM(0)))))));
} else {
return F_Parser_dbind(F_P_derr(S690()), mk_clo(L691, 1, 0, 0));
}
}
static V W_P_dpat1_dk(V *a) { (void)a; return F_P_dpat1_dk(a[0]); }
static V L694(V *a) {
return F_P_dpat1();
}
static V L695(V *a) {
return F_P_dpat1();
}
static V S697(void) { static V c; return STRC(c, ")"); }
static V L698(V *a) {
return F_Parser_dpure(F_P_dptuple(a[0]));
}
static V L696(V *a) {
return F_Parser_dbind(F_P_dpats(S697()), mk_clo(L698, 1, 0, 0));
}
static V S700(void) { static V c; return STRC(c, "]"); }
static V L701(V *a) {
return F_Parser_dpure(F_P_dplist(a[0]));
}
static V L699(V *a) {
return F_Parser_dbind(F_P_dpats(S700()), mk_clo(L701, 1, 0, 0));
}
static V S702(void) { static V c; return STRC(c, "expected a pattern"); }
static V S704(void) { static V c; return STRC(c, "_"); }
static V L703(V *a) {
return F_Parser_dpure(C1(0, S704()));
}
static V F_P_dpat_dsym(V a0) {
top:;
V s693 = a0;
if ((s693) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L694, 1, 0, 0));
} else if ((s693) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L695, 1, 0, 0));
} else if ((s693) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L696, 1, 0, 0));
} else if ((s693) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L699, 1, 0, 0));
} else if (nat_ge(s693, 4)) {
return F_Parser_dbind(F_P_derr(S702()), mk_clo(L703, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat_dsym(V *a) { (void)a; return F_P_dpat_dsym(a[0]); }
static V S706(void) { static V c; return STRC(c, "Nil"); }
static V S707(void) { static V c; return STRC(c, "Con"); }
static V F_P_dplist(V a0) {
top:;
V s705 = a0;
if ((s705) == IMM(0)) {
return C2(1, S706(), IMM(0));
} else if (TAG(s705) == 1) {
return C2(1, S707(), C2(1, FLD(s705, 0), C2(1, F_P_dplist(FLD(s705, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dplist(V *a) { (void)a; return F_P_dplist(a[0]); }
static V L708(V *a) {
return F_P_dpats_dgo(a[0], a[1], F_P_dstuck(F_P_dtok__kind(a[1])));
}
static V F_P_dpats(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L708, 2, 1, (V[]){a0}));
}
static V W_P_dpats(V *a) { (void)a; return F_P_dpats(a[0]); }
static V F_P_dpats_dgo(V a0, V a1, V a2) {
top:;
V s709 = a2;
if ((s709) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s709) == IMM(0)) {
return F_P_dpats_dclose(a0, F_P_dtok__is(a1, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpats_dgo(V *a) { (void)a; return F_P_dpats_dgo(a[0], a[1], a[2]); }
static V L711(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dpats_dclose(V a0, V a1) {
top:;
V s710 = a1;
if ((s710) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L711, 1, 0, 0));
} else if ((s710) == IMM(0)) {
return F_P_dpats_ditem(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dpats_dclose(V *a) { (void)a; return F_P_dpats_dclose(a[0], a[1]); }
static V S713(void) { static V c; return STRC(c, ","); }
static V L715(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L714(V *a) {
return F_Parser_dbind(F_P_dpats_dmore(a[1], a[2]), mk_clo(L715, 2, 1, (V[]){a[0]}));
}
static V L712(V *a) {
return F_Parser_dbind(F_P_deat(S713()), mk_clo(L714, 3, 2, (V[]){a[1], a[0]}));
}
static V F_P_dpats_ditem(V a0) {
top:;
return F_Parser_dbind(F_P_dpat(), mk_clo(L712, 2, 1, (V[]){a0}));
}
static V W_P_dpats_ditem(V *a) { (void)a; return F_P_dpats_ditem(a[0]); }
static V L717(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dpats_dmore(V a0, V a1) {
top:;
V s716 = a1;
if ((s716) == IMM(1)) {
return F_P_dpats(a0);
} else if ((s716) == IMM(0)) {
return F_Parser_dbind(F_P_dexpect(a0), mk_clo(L717, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpats_dmore(V *a) { (void)a; return F_P_dpats_dmore(a[0], a[1]); }
static V S719(void) { static V c; return STRC(c, "Unit"); }
static V S720(void) { static V c; return STRC(c, "Tuple"); }
static V F_P_dptuple(V a0) {
top:;
V s718 = a0;
if ((s718) == IMM(0)) {
return C2(1, S719(), IMM(0));
} else if (TAG(s718) == 1 && (FLD(s718, 1)) == IMM(0)) {
return FLD(s718, 0);
} else if (TAG(s718) == 1) {
return C2(1, S720(), C2(1, FLD(s718, 0), C2(1, F_P_dptuple(FLD(s718, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dptuple(V *a) { (void)a; return F_P_dptuple(a[0]); }
static V S722(void) { static V c; return STRC(c, "SNil"); }
static V S723(void) { static V c; return STRC(c, "SCon"); }
static V F_P_dpstr(V a0) {
top:;
V s721 = a0;
if ((s721) == IMM(0)) {
return C2(1, S722(), IMM(0));
} else if (TAG(s721) == 1) {
return C2(1, S723(), C2(1, C1(4, FLD(s721, 0)), C2(1, F_P_dpstr(FLD(s721, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpstr(V *a) { (void)a; return F_P_dpstr(a[0]); }
static V S726(void) { static V c; return STRC(c, "}"); }
static V L727(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L725(V *a) {
return F_Parser_dbind(F_P_dpats(S726()), mk_clo(L727, 2, 1, (V[]){a[0]}));
}
static V F_P_dpat_did(V a0, V a1) {
top:;
V s724 = a1;
if ((s724) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L725, 2, 1, (V[]){a0}));
} else if ((s724) == IMM(0)) {
return F_Parser_dpure(C1(0, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat_did(V *a) { (void)a; return F_P_dpat_did(a[0], a[1]); }
static V L728(V *a) {
return F_P_dscan_dret(a[0]);
}
static V F_P_dscan(void) {
top:;
return mk_clo(L728, 1, 0, 0);
}
static V W_P_dscan(V *a) { (void)a; return F_P_dscan(); }
static V F_P_dscan_dret(V a0) {
top:;
return C2(0, F_P_dscan_dgo(a0, 0u), a0);
}
static V W_P_dscan_dret(V *a) { (void)a; return F_P_dscan_dret(a[0]); }
static V S730(void) { static V c; return STRC(c, "="); }
static V S731(void) { static V c; return STRC(c, "<-"); }
static V S732(void) { static V c; return STRC(c, "("); }
static V S733(void) { static V c; return STRC(c, "["); }
static V S734(void) { static V c; return STRC(c, "{"); }
static V S735(void) { static V c; return STRC(c, ")"); }
static V S736(void) { static V c; return STRC(c, "]"); }
static V S737(void) { static V c; return STRC(c, "}"); }
static V F_P_dscan_dgo(V a0, V a1) {
top:;
V s729 = a0;
if ((s729) == IMM(0)) {
return 0u;
} else if (TAG(s729) == 1 && TAG(FLD(FLD(s729, 0), 0)) == 7) {
return F_P_dscan_dsym(FLD(s729, 1), a1, F_P_dwhich(FLD(FLD(FLD(s729, 0), 0), 0), C2(1, S730(), C2(1, S731(), C2(1, S732(), C2(1, S733(), C2(1, S734(), C2(1, S735(), C2(1, S736(), C2(1, S737(), IMM(0)))))))))));
} else if (TAG(s729) == 1 && TAG(FLD(FLD(s729, 0), 0)) == 0) {
{ V t0 = FLD(s729, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else if (TAG(s729) == 1 && (FLD(FLD(s729, 0), 0)) == IMM(8)) {
return F_P_dscan_dend(FLD(s729, 1), a1, F_U32_dis__zero(a1));
} else if (TAG(s729) == 1 && (FLD(FLD(s729, 0), 0)) == IMM(9)) {
return 0u;
} else if (TAG(s729) == 1 && (FLD(FLD(s729, 0), 0)) == IMM(10)) {
return 0u;
} else if (TAG(s729) == 1 && (FLD(FLD(s729, 0), 0)) == IMM(11)) {
return 0u;
} else if (TAG(s729) == 1 && TAG(FLD(FLD(s729, 0), 0)) == 12) {
return 0u;
} else if (TAG(s729) == 1) {
{ V t0 = FLD(s729, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dgo(V *a) { (void)a; return F_P_dscan_dgo(a[0], a[1]); }
static V F_P_dscan_dend(V a0, V a1, V a2) {
top:;
V s738 = a2;
if ((s738) == IMM(1)) {
return 0u;
} else if ((s738) == IMM(0)) {
return F_P_dscan_dgo(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dend(V *a) { (void)a; return F_P_dscan_dend(a[0], a[1], a[2]); }
static V F_P_dscan_dsym(V a0, V a1, V a2) {
top:;
V s739 = a2;
if ((s739) == 0) {
return F_P_dscan_dtop(a0, a1, 1u, F_U32_dis__zero(a1));
} else if ((s739) == 1) {
return F_P_dscan_dtop(a0, a1, 2u, F_U32_dis__zero(a1));
} else if ((s739) == 2) {
return F_P_dscan_dgo(a0, F_U32_dinc(a1));
} else if ((s739) == 3) {
return F_P_dscan_dgo(a0, F_U32_dinc(a1));
} else if ((s739) == 4) {
return F_P_dscan_dgo(a0, F_U32_dinc(a1));
} else if ((s739) == 5) {
return F_P_dscan_dgo(a0, F_U32_dsub(a1, 1u));
} else if ((s739) == 6) {
return F_P_dscan_dgo(a0, F_U32_dsub(a1, 1u));
} else if ((s739) == 7) {
return F_P_dscan_dgo(a0, F_U32_dsub(a1, 1u));
} else if (nat_ge(s739, 8)) {
return F_P_dscan_dgo(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dsym(V *a) { (void)a; return F_P_dscan_dsym(a[0], a[1], a[2]); }
static V F_P_dscan_dtop(V a0, V a1, V a2, V a3) {
top:;
V s740 = a3;
if ((s740) == IMM(1)) {
return a2;
} else if ((s740) == IMM(0)) {
return F_P_dscan_dgo(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dtop(V *a) { (void)a; return F_P_dscan_dtop(a[0], a[1], a[2], a[3]); }
static V S743(void) { static V c; return STRC(c, "<"); }
static V S746(void) { static V c; return STRC(c, ":"); }
static V L749(V *a) {
return F_Parser_dpure(F_Fold_ddo(a[1], F_P_dinit(a[0]), F_P_dlast(a[0]), a[2]));
}
static V L748(V *a) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L749, 3, 2, (V[]){a[0], a[1]}));
}
static V L747(V *a) {
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L748, 3, 2, (V[]){a[0], a[1]}));
}
static V L745(V *a) {
return F_Parser_dbind(F_P_dexpect(S746()), mk_clo(L747, 3, 2, (V[]){a[1], a[0]}));
}
static V L744(V *a) {
return F_Parser_dbind(F_P_dtyargs(), mk_clo(L745, 2, 1, (V[]){a[0]}));
}
static V L742(V *a) {
return F_Parser_dbind(F_P_dexpect(S743()), mk_clo(L744, 2, 1, (V[]){a[0]}));
}
static V L741(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L742, 1, 0, 0));
}
static V F_P_ddo(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L741, 1, 0, 0));
}
static V W_P_ddo(V *a) { (void)a; return F_P_ddo(); }
static V S751(void) { static V c; return STRC(c, ""); }
static V F_P_dlast(V a0) {
top:;
V s750 = a0;
if ((s750) == IMM(0)) {
return C2(14, S751(), IMM(0));
} else if (TAG(s750) == 1 && (FLD(s750, 1)) == IMM(0)) {
return FLD(s750, 0);
} else if (TAG(s750) == 1) {
{ V t0 = FLD(s750, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dlast(V *a) { (void)a; return F_P_dlast(a[0]); }
static V F_P_dinit(V a0) {
top:;
V s752 = a0;
if ((s752) == IMM(0)) {
return IMM(0);
} else if (TAG(s752) == 1 && (FLD(s752, 1)) == IMM(0)) {
return IMM(0);
} else if (TAG(s752) == 1) {
return C2(1, FLD(s752, 0), F_P_dinit(FLD(s752, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dinit(V *a) { (void)a; return F_P_dinit(a[0]); }
static V S754(void) { static V c; return STRC(c, "empty do block"); }
static V S755(void) { static V c; return STRC(c, "pure"); }
static V S756(void) { static V c; return STRC(c, ""); }
static V S757(void) { static V c; return STRC(c, "bind"); }
static V S758(void) { static V c; return STRC(c, ""); }
static V S759(void) { static V c; return STRC(c, "pure"); }
static V S760(void) { static V c; return STRC(c, "bind"); }
static V S761(void) { static V c; return STRC(c, ""); }
static V S762(void) { static V c; return STRC(c, "_"); }
static V F_Fold_ddo(V a0, V a1, V a2, V a3) {
top:;
V s753 = a3;
if ((s753) == IMM(0)) {
return C1(15, S754());
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 0 && (FLD(s753, 1)) == IMM(0)) {
return FLD(FLD(s753, 0), 1);
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 1 && (FLD(s753, 1)) == IMM(0)) {
return FLD(FLD(s753, 0), 1);
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 2 && (FLD(s753, 1)) == IMM(0)) {
return F_Fold_dapp(a0, S755(), a1, C2(1, a2, C2(1, FLD(FLD(s753, 0), 0), IMM(0))));
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 3 && (FLD(s753, 1)) == IMM(0)) {
return FLD(FLD(s753, 0), 0);
} else if (TAG(s753) == 1 && (FLD(s753, 0)) == IMM(4) && (FLD(s753, 1)) == IMM(0)) {
return C2(14, S756(), IMM(0));
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 0) {
return C3(8, FLD(FLD(s753, 0), 0), FLD(FLD(s753, 0), 1), F_Fold_ddo(a0, a1, a2, FLD(s753, 1)));
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 1) {
return F_Fold_dapp(a0, S757(), a1, C2(1, C2(14, S758(), IMM(0)), C2(1, a2, C2(1, FLD(FLD(s753, 0), 1), C2(1, C2(7, C1(0, FLD(FLD(s753, 0), 0)), F_Fold_ddo(a0, a1, a2, FLD(s753, 1))), IMM(0))))));
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 2) {
return F_Fold_dapp(a0, S759(), a1, C2(1, a2, C2(1, FLD(FLD(s753, 0), 0), IMM(0))));
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 3) {
return F_Fold_dapp(a0, S760(), a1, C2(1, C2(14, S761(), IMM(0)), C2(1, a2, C2(1, FLD(FLD(s753, 0), 0), C2(1, C2(7, C1(0, S762()), F_Fold_ddo(a0, a1, a2, FLD(s753, 1))), IMM(0))))));
} else if (TAG(s753) == 1 && (FLD(s753, 0)) == IMM(4)) {
{ V t0 = a0; V t1 = a1; V t2 = a2; V t3 = FLD(s753, 1); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Fold_ddo(V *a) { (void)a; return F_Fold_ddo(a[0], a[1], a[2], a[3]); }
static V S763(void) { static V c; return STRC(c, "."); }
static V F_Fold_dapp(V a0, V a1, V a2, V a3) {
top:;
return C2(5, C1(0, F_String_dappend(a0, F_String_dappend(S763(), a1))), F_List_dappend(a2, a3));
}
static V W_Fold_dapp(V *a) { (void)a; return F_Fold_dapp(a[0], a[1], a[2], a[3]); }
static V S766(void) { static V c; return STRC(c, ":"); }
static V L769(V *a) {
return F_Parser_dpure(C2(9, a[0], a[1]));
}
static V L768(V *a) {
return F_Parser_dbind(F_P_dmatch_dbody(F_P_dis__in(a[1])), mk_clo(L769, 2, 1, (V[]){a[0]}));
}
static V L767(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L768, 2, 1, (V[]){a[0]}));
}
static V L765(V *a) {
return F_Parser_dbind(F_P_dexpect(S766()), mk_clo(L767, 2, 1, (V[]){a[0]}));
}
static V L764(V *a) {
return F_Parser_dbind(F_P_dscrs(), mk_clo(L765, 1, 0, 0));
}
static V F_P_dmatch(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L764, 1, 0, 0));
}
static V W_P_dmatch(V *a) { (void)a; return F_P_dmatch(); }
static V L771(V *a) {
return F_P_dcases();
}
static V F_P_dmatch_dbody(V a0) {
top:;
V s770 = a0;
if ((s770) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L771, 1, 0, 0));
} else if ((s770) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dmatch_dbody(V *a) { (void)a; return F_P_dmatch_dbody(a[0]); }
static V L773(V *a) {
return F_P_dcases_dde(F_P_dis__de(a[0]));
}
static V L772(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L773, 1, 0, 0));
}
static V F_P_dcases(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L772, 1, 0, 0));
}
static V W_P_dcases(V *a) { (void)a; return F_P_dcases(); }
static V L775(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S777(void) { static V c; return STRC(c, "case"); }
static V L776(V *a) {
return F_P_dcases_dgo(F_P_dtok__which__id(a[0], C2(1, S777(), IMM(0))));
}
static V F_P_dcases_dde(V a0) {
top:;
V s774 = a0;
if ((s774) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L775, 1, 0, 0));
} else if ((s774) == IMM(0)) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L776, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dcases_dde(V *a) { (void)a; return F_P_dcases_dde(a[0]); }
static V S780(void) { static V c; return STRC(c, ":"); }
static V S782(void) { static V c; return STRC(c, ":"); }
static V L785(V *a) {
return F_Parser_dpure(C2(1, C2(10, a[1], a[0]), a[2]));
}
static V L784(V *a) {
return F_Parser_dbind(F_P_dcases(), mk_clo(L785, 3, 2, (V[]){a[1], a[0]}));
}
static V L783(V *a) {
return F_Parser_dbind(F_P_dbody(), mk_clo(L784, 2, 1, (V[]){a[0]}));
}
static V L781(V *a) {
return F_Parser_dbind(F_P_dexpect(S782()), mk_clo(L783, 2, 1, (V[]){a[0]}));
}
static V L779(V *a) {
return F_Parser_dbind(F_P_dpat__seq(C2(1, S780(), IMM(0))), mk_clo(L781, 1, 0, 0));
}
static V F_P_dcases_dgo(V a0) {
top:;
V s778 = a0;
if ((s778) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L779, 1, 0, 0));
} else if (nat_ge(s778, 1)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dcases_dgo(V *a) { (void)a; return F_P_dcases_dgo(a[0]); }
static V L787(V *a) {
return F_Parser_dpure(F_Fold_dplain(a[0]));
}
static V L786(V *a) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L787, 1, 0, 0));
}
static V F_P_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L786, 1, 0, 0));
}
static V W_P_dbody(V *a) { (void)a; return F_P_dbody(); }
static V S789(void) { static V c; return STRC(c, ":"); }
static V L788(V *a) {
return F_P_dscrs_dgo(a[0], F_Bool_dor(F_P_dtok__is(a[0], S789()), F_P_dstuck(F_P_dtok__kind(a[0]))));
}
static V F_P_dscrs(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L788, 1, 0, 0));
}
static V W_P_dscrs(V *a) { (void)a; return F_P_dscrs(); }
static V L792(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L791(V *a) {
return F_Parser_dbind(F_P_dscrs(), mk_clo(L792, 2, 1, (V[]){a[0]}));
}
static V F_P_dscrs_dgo(V a0, V a1) {
top:;
V s790 = a1;
if ((s790) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s790) == IMM(0)) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L791, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dscrs_dgo(V *a) { (void)a; return F_P_dscrs_dgo(a[0], a[1]); }
static V L793(V *a) {
return F_P_deff_dgo(a[0], IMM(0));
}
static V F_P_deff_dimports(void) {
top:;
return mk_clo(L793, 1, 0, 0);
}
static V W_P_deff_dimports(V *a) { (void)a; return F_P_deff_dimports(); }
static V F_P_deff_dgo(V a0, V a1) {
top:;
V s794 = a0;
if ((s794) == IMM(0)) {
return C2(0, a1, IMM(0));
} else if (TAG(s794) == 1 && TAG(FLD(FLD(s794, 0), 0)) == 6) {
{ V t0 = FLD(s794, 1); V t1 = F_List_dappend(a1, C2(1, FLD(FLD(FLD(s794, 0), 0), 0), IMM(0))); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s794) == 1 && (FLD(FLD(s794, 0), 0)) == IMM(10)) {
return C2(0, a1, FLD(s794, 1));
} else if (TAG(s794) == 1 && (FLD(FLD(s794, 0), 0)) == IMM(11)) {
return C2(0, a1, C2(1, C3(0, IMM(11), FLD(FLD(s794, 0), 1), FLD(FLD(s794, 0), 2)), FLD(s794, 1)));
} else if (TAG(s794) == 1 && TAG(FLD(FLD(s794, 0), 0)) == 12) {
return C2(0, a1, C2(1, C3(0, C1(12, FLD(FLD(FLD(s794, 0), 0), 0)), FLD(FLD(s794, 0), 1), FLD(FLD(s794, 0), 2)), FLD(s794, 1)));
} else if (TAG(s794) == 1) {
{ V t0 = FLD(s794, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_deff_dgo(V *a) { (void)a; return F_P_deff_dgo(a[0], a[1]); }
static V L796(V *a) {
return F_P_dexpr();
}
static V S797(void) { static V c; return STRC(c, ""); }
static V F_P_dret_dgo(V a0) {
top:;
V s795 = a0;
if ((s795) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L796, 1, 0, 0));
} else if ((s795) == IMM(0)) {
return F_Parser_dpure(C2(14, S797(), IMM(0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dret_dgo(V *a) { (void)a; return F_P_dret_dgo(a[0]); }
static V S799(void) { static V c; return STRC(c, ")"); }
static V L798(V *a) {
return F_P_dparams_dgo(F_Bool_dor(F_P_dtok__is(a[0], S799()), F_P_dstuck(F_P_dtok__kind(a[0]))));
}
static V F_P_dparams(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L798, 1, 0, 0));
}
static V W_P_dparams(V *a) { (void)a; return F_P_dparams(); }
static V L801(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S803(void) { static V c; return STRC(c, ","); }
static V L805(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L804(V *a) {
return F_Parser_dbind(F_P_dparams_dmore(a[1]), mk_clo(L805, 2, 1, (V[]){a[0]}));
}
static V L802(V *a) {
return F_Parser_dbind(F_P_deat(S803()), mk_clo(L804, 2, 1, (V[]){a[0]}));
}
static V F_P_dparams_dgo(V a0) {
top:;
V s800 = a0;
if ((s800) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L801, 1, 0, 0));
} else if ((s800) == IMM(0)) {
return F_Parser_dbind(F_P_dparam(), mk_clo(L802, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparams_dgo(V *a) { (void)a; return F_P_dparams_dgo(a[0]); }
static V S807(void) { static V c; return STRC(c, ")"); }
static V L808(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dparams_dmore(V a0) {
top:;
V s806 = a0;
if ((s806) == IMM(1)) {
return F_P_dparams();
} else if ((s806) == IMM(0)) {
return F_Parser_dbind(F_P_dexpect(S807()), mk_clo(L808, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparams_dmore(V *a) { (void)a; return F_P_dparams_dmore(a[0]); }
static V F_P_dfile_dfin(V a0) {
top:;
V v809 = a0;
return C2(0, FLD(v809, 0), F_P_dfile_derr(FLD(v809, 1)));
}
static V W_P_dfile_dfin(V *a) { (void)a; return F_P_dfile_dfin(a[0]); }
static V S811(void) { static V c; return STRC(c, ""); }
static V F_P_dfile_derr(V a0) {
top:;
V s810 = a0;
if (TAG(s810) == 1 && TAG(FLD(FLD(s810, 0), 0)) == 12) {
return FLD(FLD(FLD(s810, 0), 0), 0);
} else {
return S811();
}
}
static V W_P_dfile_derr(V *a) { (void)a; return F_P_dfile_derr(a[0]); }
static V F_Main_dparse_dfin(V a0) {
top:;
V v812 = a0;
return F_Bool_dpick(F_String_dis__empty(FLD(v812, 1)), C1(1, FLD(v812, 0)), C1(0, FLD(v812, 1)));
}
static V W_Main_dparse_dfin(V *a) { (void)a; return F_Main_dparse_dfin(a[0]); }
static V F_String_dis__empty(V a0) {
top:;
V s813 = a0;
if ((s813) == IMM(0)) {
return IMM(1);
} else if (TAG(s813) == 1) {
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
V s814 = a0;
if ((s814) == IMM(0)) {
return IMM(0);
} else if (TAG(s814) == 1) {
return F_Mod_ddir_dif(FLD(s814, 0), FLD(s814, 1), F_U32_dis__eq(FLD(s814, 0), 47u));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddir_dgo(V *a) { (void)a; return F_Mod_ddir_dgo(a[0]); }
static V F_Mod_ddir_dif(V a0, V a1, V a2) {
top:;
V s815 = a2;
if ((s815) == IMM(1)) {
return C2(1, a0, a1);
} else if ((s815) == IMM(0)) {
return F_Mod_ddir_dgo(a1);
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddir_dif(V *a) { (void)a; return F_Mod_ddir_dif(a[0], a[1], a[2]); }
static V F_Main_dresolve(V a0, V a1) {
top:;
V s816 = a1;
if (TAG(s816) == 0) {
return C1(0, FLD(s816, 0));
} else if (TAG(s816) == 1) {
return C1(1, F_Eff_ddecls(a0, FLD(s816, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dresolve(V *a) { (void)a; return F_Main_dresolve(a[0], a[1]); }
static V F_Eff_ddecls(V a0, V a1) {
top:;
V s817 = a1;
if ((s817) == IMM(0)) {
return IMM(0);
} else if (TAG(s817) == 1) {
return C2(1, F_Eff_ddecl(a0, FLD(s817, 0)), F_Eff_ddecls(a0, FLD(s817, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Eff_ddecls(V *a) { (void)a; return F_Eff_ddecls(a[0], a[1]); }
static V F_Eff_ddecl(V a0, V a1) {
top:;
V s818 = a1;
if (TAG(s818) == 1) {
return C3(1, FLD(s818, 0), FLD(s818, 1), F_Eff_dpaths(a0, FLD(s818, 2)));
} else {
return s818;
}
}
static V W_Eff_ddecl(V *a) { (void)a; return F_Eff_ddecl(a[0], a[1]); }
static V F_Eff_dpaths(V a0, V a1) {
top:;
V s819 = a1;
if ((s819) == IMM(0)) {
return IMM(0);
} else if (TAG(s819) == 1) {
return C2(1, F_Eff_dpath(a0, FLD(s819, 0)), F_Eff_dpaths(a0, FLD(s819, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Eff_dpaths(V *a) { (void)a; return F_Eff_dpaths(a[0], a[1]); }
static V S820(void) { static V c; return STRC(c, "/"); }
static V F_Eff_dpath(V a0, V a1) {
top:;
return F_Bool_dpick(F_String_dstarts__with(a1, S820()), a1, F_String_dappend(a0, a1));
}
static V W_Eff_dpath(V *a) { (void)a; return F_Eff_dpath(a[0], a[1]); }
static V S823(void) { static V c; return STRC(c, "bendc: parse error in base: "); }
static V S824(void) { static V c; return STRC(c, "bendc: parse error: "); }
static V F_Main_dcompile(V a0, V a1) {
top:;
V s821 = a0;
V s822 = a1;
if (TAG(s821) == 0) {
return F_IO_ddie(1u, F_String_dappend(S823(), FLD(s821, 0)));
} else if (TAG(s821) == 1 && TAG(s822) == 0) {
return F_IO_ddie(1u, F_String_dappend(S824(), FLD(s822, 0)));
} else if (TAG(s821) == 1 && TAG(s822) == 1) {
return F_Main_demit(F_Gen_dprogram(F_List_dappend(FLD(s821, 0), FLD(s822, 0))));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dcompile(V *a) { (void)a; return F_Main_dcompile(a[0], a[1]); }
static V F_Gen_dprogram(V a0) {
top:;
V v825 = F_G_dnew(a0);
return F_Gen_dprogram_dfin(F_Gen_dcids(v825, a0, 0u), apply(F_Gen_dprogram_dm(v825), CN(0, 7, (V[]){0u, IMM(0), IMM(0), IMM(0), IMM(0), IMM(0), IMM(0)})));
}
static V W_Gen_dprogram(V *a) { (void)a; return F_Gen_dprogram(a[0]); }
static V S826(void) { static V c; return STRC(c, "main"); }
static V S828(void) { static V c; return STRC(c, "main"); }
static V L827(V *a) {
return F_Gen_dentry(a[0], F_G_dbody(a[0], S828()));
}
static V F_Gen_dprogram_dm(V a0) {
top:;
return F_Gen_dbind(F_Gen_dall(a0, C2(1, S826(), IMM(0)), F_Set_dnew()), mk_clo(L827, 2, 1, (V[]){a0}));
}
static V W_Gen_dprogram_dm(V *a) { (void)a; return F_Gen_dprogram_dm(a[0]); }
static V S830(void) { static V c; return STRC(c, ""); }
static V S831(void) { static V c; return STRC(c, ""); }
static V F_G_dbody(V a0, V a1) {
top:;
V v829 = a0;
return F_G_dget(C2(4, S830(), S831()), FLD(v829, 2), a1);
}
static V W_G_dbody(V *a) { (void)a; return F_G_dbody(a[0], a[1]); }
static V F_G_dget(V a1, V a2, V a3) {
top:;
return F_Pair_dsnd(F_Map_dget(a1, a2, a3));
}
static V W_G_dget(V *a) { (void)a; return F_G_dget(a[1], a[2], a[3]); }
static V F_Map_dget(V a1, V a2, V a3) {
top:;
V s832 = a2;
if ((s832) == IMM(0)) {
return C2(0, IMM(0), a1);
} else if (TAG(s832) == 1) {
return F_Map_dget_dleaf(a1, FLD(s832, 1), F_String_dcmp(a3, FLD(s832, 0)));
} else if (TAG(s832) == 2) {
return F_Map_dget_dbit(a1, FLD(s832, 1), FLD(s832, 2), FLD(s832, 0), F_Map_dbit(a3, FLD(s832, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dget(V *a) { (void)a; return F_Map_dget(a[1], a[2], a[3]); }
static V F_Map_dbit(V a0, V a1) {
top:;
return F_Map_dbit_dat(a0, F_Nat_ddivmod(a1, 33u));
}
static V W_Map_dbit(V *a) { (void)a; return F_Map_dbit(a[0], a[1]); }
static V W_Nat_ddivmod(V *a) { (void)a; return F_Nat_ddivmod(a[0], a[1]); }
static V F_Map_dbit_dat(V a0, V a1) {
top:;
V v833 = a1;
return F_Map_dbit_dgo(a0, FLD(v833, 0), FLD(v833, 1));
}
static V W_Map_dbit_dat(V *a) { (void)a; return F_Map_dbit_dat(a[0], a[1]); }
static V F_Map_dbit_dgo(V a0, V a1, V a2) {
top:;
V s834 = a0;
if ((s834) == IMM(0)) {
return C2(0, IMM(0), IMM(0));
} else if (TAG(s834) == 1) {
V s835 = a1;
if ((s835) == 0) {
return F_Map_dbit_dgo_dchr(FLD(s834, 1), F_Map_dbit_dchr(FLD(s834, 0), a2));
} else if (nat_ge(s835, 1)) {
return F_Map_dbit_dgo_drec(FLD(s834, 0), F_Map_dbit_dgo(FLD(s834, 1), nat_subk(s835, 1), a2));
} else { bend_fail("incomplete match"); }
} else { bend_fail("incomplete match"); }
}
static V W_Map_dbit_dgo(V *a) { (void)a; return F_Map_dbit_dgo(a[0], a[1], a[2]); }
static V F_Map_dbit_dgo_drec(V a0, V a1) {
top:;
V v836 = a1;
return C2(0, C2(1, a0, FLD(v836, 0)), FLD(v836, 1));
}
static V W_Map_dbit_dgo_drec(V *a) { (void)a; return F_Map_dbit_dgo_drec(a[0], a[1]); }
static V F_Map_dbit_dchr(V a0, V a1) {
top:;
V s837 = a0;
V s838 = a1;
if ((s838) == 0) {
return C2(0, s837, IMM(1));
} else if (nat_ge(s838, 1)) {
return C2(0, s837, F_Map_dbit_du(s837, F_Nat_dsub(31u, nat_subk(s838, 1))));
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
static V F_Map_dbit_dgo_dchr(V a0, V a1) {
top:;
V v839 = a1;
return C2(0, C2(1, FLD(v839, 0), a0), FLD(v839, 1));
}
static V W_Map_dbit_dgo_dchr(V *a) { (void)a; return F_Map_dbit_dgo_dchr(a[0], a[1]); }
static V F_Map_dget_dbit(V a1, V a2, V a3, V a4, V a5) {
top:;
V v840 = a5;
V s841 = FLD(v840, 1);
if ((s841) == IMM(0)) {
return F_Map_dlo(a4, a3, F_Map_dget(a1, a2, FLD(v840, 0)));
} else if ((s841) == IMM(1)) {
return F_Map_dhi(a4, a2, F_Map_dget(a1, a3, FLD(v840, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dget_dbit(V *a) { (void)a; return F_Map_dget_dbit(a[1], a[2], a[3], a[4], a[5]); }
static V F_Map_dhi(V a3, V a4, V a5) {
top:;
V v842 = a5;
return C2(0, C3(2, a3, a4, FLD(v842, 0)), FLD(v842, 1));
}
static V W_Map_dhi(V *a) { (void)a; return F_Map_dhi(a[3], a[4], a[5]); }
static V F_Map_dlo(V a3, V a4, V a5) {
top:;
V v843 = a5;
return C2(0, C3(2, a3, FLD(v843, 0), a4), FLD(v843, 1));
}
static V W_Map_dlo(V *a) { (void)a; return F_Map_dlo(a[3], a[4], a[5]); }
static V F_Map_dget_dleaf(V a1, V a2, V a3) {
top:;
V v844 = a3;
V s845 = FLD(v844, 1);
if ((s845) == IMM(0)) {
return C2(0, C2(1, FLD(FLD(v844, 0), 1), a2), a1);
} else if ((s845) == IMM(1)) {
return C2(0, C2(1, FLD(FLD(v844, 0), 1), a2), a2);
} else if ((s845) == IMM(2)) {
return C2(0, C2(1, FLD(FLD(v844, 0), 1), a2), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Map_dget_dleaf(V *a) { (void)a; return F_Map_dget_dleaf(a[1], a[2], a[3]); }
static V F_Pair_dsnd(V a2) {
top:;
V v846 = a2;
return FLD(v846, 1);
}
static V W_Pair_dsnd(V *a) { (void)a; return F_Pair_dsnd(a[2]); }
static V S848(void) { static V c; return STRC(c, "IO"); }
static V S849(void) { static V c; return STRC(c, "no main definition"); }
static V S851(void) { static V c; return STRC(c, ""); }
static V L850(V *a) {
return F_Gen_dpure(S851());
}
static V F_Gen_dentry(V a0, V a1) {
top:;
V s847 = a1;
if (TAG(s847) == 0) {
return F_Gen_dentry_dty(a0, FLD(s847, 3), F_Str_deq(F_Ty_dhead(FLD(s847, 3)), S848()));
} else {
return F_Gen_dbind(F_Gen_derror(S849()), mk_clo(L850, 1, 0, 0));
}
}
static V W_Gen_dentry(V *a) { (void)a; return F_Gen_dentry(a[0], a[1]); }
static V L852(V *a) {
return C2(0, a[0], a[1]);
}
static V F_Gen_dpure(V a1) {
top:;
return mk_clo(L852, 2, 1, (V[]){a1});
}
static V W_Gen_dpure(V *a) { (void)a; return F_Gen_dpure(a[1]); }
static V L853(V *a) {
return F_Gen_derror_dgo(a[0], a[1]);
}
static V F_Gen_derror(V a0) {
top:;
return mk_clo(L853, 2, 1, (V[]){a0});
}
static V W_Gen_derror(V *a) { (void)a; return F_Gen_derror(a[0]); }
static V F_Gen_derror_dgo(V a0, V a1) {
top:;
V v854 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v854, 0), FLD(v854, 1), FLD(v854, 2), FLD(v854, 3), C2(1, a0, FLD(v854, 4)), FLD(v854, 5), FLD(v854, 6)}));
}
static V W_Gen_derror_dgo(V *a) { (void)a; return F_Gen_derror_dgo(a[0], a[1]); }
static V L855(V *a) {
return F_Gen_dgo(apply(a[1], a[4]), a[0]);
}
static V F_Gen_dbind(V a2, V a3) {
top:;
return mk_clo(L855, 5, 4, (V[]){a3, a2, 0, 0});
}
static V W_Gen_dbind(V *a) { (void)a; return F_Gen_dbind(a[2], a[3]); }
static V F_Gen_dgo(V a2, V a3) {
top:;
V v856 = a2;
return apply(apply(a3, FLD(v856, 0)), FLD(v856, 1));
}
static V W_Gen_dgo(V *a) { (void)a; return F_Gen_dgo(a[2], a[3]); }
static V S858(void) { static V c; return STRC(c, "\077"); }
static V F_Ty_dhead(V a0) {
top:;
V s857 = a0;
if (TAG(s857) == 0) {
return FLD(s857, 0);
} else if (TAG(s857) == 14) {
return FLD(s857, 0);
} else if (TAG(s857) == 5 && TAG(FLD(s857, 0)) == 0) {
return FLD(FLD(s857, 0), 0);
} else {
return S858();
}
}
static V W_Ty_dhead(V *a) { (void)a; return F_Ty_dhead(a[0]); }
static V S860(void) { static V c; return STRC(c, "int main(int argc, char **argv) { return bend_run(argc, argv, F_main); }\012"); }
static V S862(void) { static V c; return STRC(c, "int main(int argc, char **argv) { return bend_run_value(argc, argv, F_main, "); }
static V S863(void) { static V c; return STRC(c, "); }\012"); }
static V L861(V *a) {
return F_Gen_dpure(F_String_dappend(S862(), F_String_dappend(a[0], S863())));
}
static V F_Gen_dentry_dty(V a0, V a1, V a2) {
top:;
V s859 = a2;
if ((s859) == IMM(1)) {
return F_Gen_dpure(S860());
} else if ((s859) == IMM(0)) {
return F_Gen_dbind(F_Gen_dprinter(a0, a1), mk_clo(L861, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dentry_dty(V *a) { (void)a; return F_Gen_dentry_dty(a[0], a[1], a[2]); }
static V L865(V *a) {
return F_Gen_dprinter_dmemo(a[2], a[1], a[0], a[3]);
}
static V F_Gen_dprinter(V a0, V a1) {
top:;
V v864 = F_Expr_dshow(a1);
return F_Gen_dbind(F_Gen_dmemo_dfind(v864), mk_clo(L865, 4, 3, (V[]){v864, a1, a0}));
}
static V W_Gen_dprinter(V *a) { (void)a; return F_Gen_dprinter(a[0], a[1]); }
static V S868(void) { static V c; return STRC(c, "P"); }
static V S871(void) { static V c; return STRC(c, "static void "); }
static V S872(void) { static V c; return STRC(c, "(V v);\012"); }
static V S875(void) { static V c; return STRC(c, "static void "); }
static V S876(void) { static V c; return STRC(c, "(V v) {\012"); }
static V S877(void) { static V c; return STRC(c, "}\012"); }
static V L878(V *a) {
return F_Gen_dpure(a[0]);
}
static V L874(V *a) {
return F_Gen_dbind(F_Gen_dcode(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S875(), F_String_dappend(a[0], S876()))), C2(1, a[1], C2(1, C1(1, S877()), IMM(0)))))), mk_clo(L878, 2, 1, (V[]){a[0]}));
}
static V L873(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dbody(a[2], a[1], F_Ty_dhead(a[1])), mk_clo(L874, 2, 1, (V[]){a[0]}));
}
static V L870(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S871(), F_String_dappend(a[2], S872())))), mk_clo(L873, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L869(V *a) {
return F_Gen_dbind(F_Gen_dmemo_dadd(C2(0, a[2], a[3])), mk_clo(L870, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V L867(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S868(), F_U32_dshow(a[3]))), mk_clo(L869, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Gen_dprinter_dmemo(V a0, V a1, V a2, V a3) {
top:;
V s866 = a3;
if (TAG(s866) == 1) {
return F_Gen_dpure(FLD(s866, 0));
} else if ((s866) == IMM(0)) {
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L867, 4, 3, (V[]){a1, a0, a2}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dmemo(V *a) { (void)a; return F_Gen_dprinter_dmemo(a[0], a[1], a[2], a[3]); }
static V F_Doc_dlist(V a0) {
top:;
V s879 = a0;
if ((s879) == IMM(0)) {
return IMM(0);
} else if (TAG(s879) == 1) {
return C2(2, FLD(s879, 0), F_Doc_dlist(FLD(s879, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dlist(V *a) { (void)a; return F_Doc_dlist(a[0]); }
static V L880(V *a) {
return F_Gen_dcode_dgo(a[0], a[1]);
}
static V F_Gen_dcode(V a0) {
top:;
return mk_clo(L880, 2, 1, (V[]){a0});
}
static V W_Gen_dcode(V *a) { (void)a; return F_Gen_dcode(a[0]); }
static V F_Gen_dcode_dgo(V a0, V a1) {
top:;
V v881 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v881, 0), FLD(v881, 1), C2(2, FLD(v881, 2), a0), FLD(v881, 3), FLD(v881, 4), FLD(v881, 5), FLD(v881, 6)}));
}
static V W_Gen_dcode_dgo(V *a) { (void)a; return F_Gen_dcode_dgo(a[0], a[1]); }
static V S882(void) { static V c; return STRC(c, "U32"); }
static V S883(void) { static V c; return STRC(c, "Nat"); }
static V S884(void) { static V c; return STRC(c, "F32"); }
static V S885(void) { static V c; return STRC(c, "Char"); }
static V S886(void) { static V c; return STRC(c, "String"); }
static V S887(void) { static V c; return STRC(c, "List"); }
static V S888(void) { static V c; return STRC(c, "&"); }
static V S889(void) { static V c; return STRC(c, "->"); }
static V F_Gen_dprinter_dbody(V a0, V a1, V a2) {
top:;
return F_Gen_dprinter_dhead(a0, a1, F_P_dwhich(a2, C2(1, S882(), C2(1, S883(), C2(1, S884(), C2(1, S885(), C2(1, S886(), C2(1, S887(), C2(1, S888(), C2(1, S889(), IMM(0)))))))))));
}
static V W_Gen_dprinter_dbody(V *a) { (void)a; return F_Gen_dprinter_dbody(a[0], a[1], a[2]); }
static V S891(void) { static V c; return STRC(c, "pr_u32(v);\012"); }
static V S892(void) { static V c; return STRC(c, "pr_nat(v);\012"); }
static V S893(void) { static V c; return STRC(c, "pr_f32(v);\012"); }
static V S894(void) { static V c; return STRC(c, "pr_char(v);\012"); }
static V S895(void) { static V c; return STRC(c, "pr_str(v);\012"); }
static V S897(void) { static V c; return STRC(c, "pr_s(\042[\042);\012for (int i = 0; TAG(v) == 1; i++) { if (i) pr_s(\042, \042); "); }
static V S898(void) { static V c; return STRC(c, "(FLD(v, 0)); v = FLD(v, 1); }\012pr_s(\042]\042);\012"); }
static V L896(V *a) {
return F_Gen_dpure(C1(1, F_String_dappend(S897(), F_String_dappend(a[0], S898()))));
}
static V S899(void) { static V c; return STRC(c, "v"); }
static V S901(void) { static V c; return STRC(c, "pr_s(\042(\042);\012"); }
static V S902(void) { static V c; return STRC(c, "pr_s(\042)\042);\012"); }
static V L900(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S901()), C2(1, a[0], C2(1, C1(1, S902()), IMM(0))))));
}
static V S903(void) { static V c; return STRC(c, "(void)v; pr_s(\042<function>\042);\012"); }
static V S904(void) { static V c; return STRC(c, "%"); }
static V F_Gen_dprinter_dhead(V a0, V a1, V a2) {
top:;
V s890 = a2;
if ((s890) == 0) {
return F_Gen_dpure(C1(1, S891()));
} else if ((s890) == 1) {
return F_Gen_dpure(C1(1, S892()));
} else if ((s890) == 2) {
return F_Gen_dpure(C1(1, S893()));
} else if ((s890) == 3) {
return F_Gen_dpure(C1(1, S894()));
} else if ((s890) == 4) {
return F_Gen_dpure(C1(1, S895()));
} else if ((s890) == 5) {
return F_Gen_dbind(F_Gen_dprinter(a0, F_P_dlast(F_Ty_dargs(a1))), mk_clo(L896, 1, 0, 0));
} else if ((s890) == 6) {
return F_Gen_dbind(F_Gen_dprinter_dtuple(a0, F_Ty_dtuple(a1), S899()), mk_clo(L900, 1, 0, 0));
} else if ((s890) == 7) {
return F_Gen_dpure(C1(1, S903()));
} else if (nat_ge(s890, 8)) {
return F_Gen_dprinter_dadt(a0, a1, F_G_dbody(a0, F_String_dappend(S904(), F_Ty_dhead(a1))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dhead(V *a) { (void)a; return F_Gen_dprinter_dhead(a[0], a[1], a[2]); }
static V S907(void) { static V c; return STRC(c, "pr_s(\042\077\042);\012"); }
static V L906(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, C1(1, S907()), IMM(0)))));
}
static V S908(void) { static V c; return STRC(c, "(void)v; pr_s(\042\077\042);\012"); }
static V F_Gen_dprinter_dadt(V a0, V a1, V a2) {
top:;
V s905 = a2;
if (TAG(s905) == 3) {
return F_Gen_dbind(F_Gen_dprinter_dctors(a0, F_Ty_dbind(FLD(s905, 1), F_Ty_dargs(a1)), FLD(s905, 2)), mk_clo(L906, 1, 0, 0));
} else {
return F_Gen_dpure(C1(1, S908()));
}
}
static V W_Gen_dprinter_dadt(V *a) { (void)a; return F_Gen_dprinter_dadt(a[0], a[1], a[2]); }
static V F_Ty_dargs(V a0) {
top:;
V s909 = a0;
if (TAG(s909) == 14) {
return FLD(s909, 1);
} else if (TAG(s909) == 5) {
return FLD(s909, 1);
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
V s910 = a0;
V s911 = a1;
if (TAG(s910) == 1 && TAG(s911) == 1) {
return C2(1, C2(0, FLD(s910, 0), FLD(s911, 0)), F_Ty_dbind_dgo(FLD(s910, 1), FLD(s911, 1)));
} else {
return IMM(0);
}
}
static V W_Ty_dbind_dgo(V *a) { (void)a; return F_Ty_dbind_dgo(a[0], a[1]); }
static V L914(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V L913(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dctors(a[2], a[1], a[0]), mk_clo(L914, 2, 1, (V[]){a[3]}));
}
static V F_Gen_dprinter_dctors(V a0, V a1, V a2) {
top:;
V s912 = a2;
if ((s912) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s912) == 1) {
return F_Gen_dbind(F_Gen_dprinter_dctor(a0, a1, FLD(FLD(s912, 0), 0), FLD(FLD(s912, 0), 1), F_G_dctor(a0, FLD(FLD(s912, 0), 0))), mk_clo(L913, 4, 3, (V[]){FLD(s912, 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dctors(V *a) { (void)a; return F_Gen_dprinter_dctors(a[0], a[1], a[2]); }
static V F_G_dctor(V a0, V a1) {
top:;
V v915 = a0;
return F_Pair_dsnd(F_Map_dget(IMM(0), F_G_dopt__ctors(FLD(v915, 0)), a1));
}
static V W_G_dctor(V *a) { (void)a; return F_G_dctor(a[0], a[1]); }
static V F_G_dopt__ctors(V a0) {
top:;
V s916 = a0;
if ((s916) == IMM(0)) {
return IMM(0);
} else if (TAG(s916) == 1) {
return C2(1, FLD(s916, 0), C1(1, FLD(s916, 1)));
} else if (TAG(s916) == 2) {
return C3(2, FLD(s916, 0), F_G_dopt__ctors(FLD(s916, 1)), F_G_dopt__ctors(FLD(s916, 2)));
} else { bend_fail("incomplete match"); }
}
static V W_G_dopt__ctors(V *a) { (void)a; return F_G_dopt__ctors(a[0]); }
static V S918(void) { static V c; return STRC(c, "v"); }
static V S919(void) { static V c; return STRC(c, "FLD(v, "); }
static V S921(void) { static V c; return STRC(c, " { pr_s(\042"); }
static V S922(void) { static V c; return STRC(c, "{\042);\012"); }
static V S923(void) { static V c; return STRC(c, "pr_s(\042}\042); return; }\012"); }
static V L920(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(F_Gen_dprinter_dtest(a[3], a[2], a[1]), F_String_dappend(S921(), F_String_dappend(a[0], S922())))), C2(1, a[4], C2(1, C1(1, S923()), IMM(0))))));
}
static V F_Gen_dprinter_dctor(V a0, V a1, V a2, V a3, V a4) {
top:;
V s917 = a4;
if ((s917) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s917) == 1) {
return F_Gen_dbind(F_Gen_dprinter_dfields(a0, a1, a3, F_Bool_dpick(F_U32_dis__eq(FLD(FLD(s917, 0), 2), 2u), S918(), S919()), 0u), mk_clo(L920, 5, 4, (V[]){a2, FLD(FLD(s917, 0), 3), FLD(FLD(s917, 0), 0), FLD(FLD(s917, 0), 2)}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dctor(V *a) { (void)a; return F_Gen_dprinter_dctor(a[0], a[1], a[2], a[3], a[4]); }
static V S924(void) { static V c; return STRC(c, "if (1)"); }
static V S925(void) { static V c; return STRC(c, "if (v == IMM("); }
static V S926(void) { static V c; return STRC(c, "))"); }
static V S927(void) { static V c; return STRC(c, "if (!(v & 1) && TAG(v) == "); }
static V S928(void) { static V c; return STRC(c, ")"); }
static V F_Gen_dprinter_dtest(V a0, V a1, V a2) {
top:;
return F_Bool_dpick(a2, S924(), F_Bool_dpick(F_U32_dis__eq(a0, 1u), F_String_dappend(S925(), F_String_dappend(F_U32_dshow(a1), S926())), F_String_dappend(S927(), F_String_dappend(F_U32_dshow(a1), S928()))));
}
static V W_Gen_dprinter_dtest(V *a) { (void)a; return F_Gen_dprinter_dtest(a[0], a[1], a[2]); }
static V S932(void) { static V c; return STRC(c, ""); }
static V S933(void) { static V c; return STRC(c, "pr_s(\042, \042);\012"); }
static V S934(void) { static V c; return STRC(c, "("); }
static V S935(void) { static V c; return STRC(c, "v"); }
static V S936(void) { static V c; return STRC(c, "v"); }
static V S937(void) { static V c; return STRC(c, ")"); }
static V S938(void) { static V c; return STRC(c, ");\012"); }
static V L931(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(F_Bool_dpick(F_U32_dis__zero(a[2]), S932(), S933()), F_String_dappend(a[1], F_String_dappend(S934(), F_String_dappend(F_Bool_dpick(F_Str_deq(a[0], S935()), S936(), F_String_dappend(a[0], F_String_dappend(F_U32_dshow(a[2]), S937()))), S938()))))), C2(1, a[3], IMM(0)))));
}
static V L930(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dfields(a[4], a[3], a[2], a[1], F_U32_dinc(a[0])), mk_clo(L931, 4, 3, (V[]){a[1], a[5], a[0]}));
}
static V F_Gen_dprinter_dfields(V a0, V a1, V a2, V a3, V a4) {
top:;
V s929 = a2;
if ((s929) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s929) == 1) {
return F_Gen_dbind(F_Gen_dprinter(a0, F_Ty_dsubst(FLD(FLD(s929, 0), 1), a1)), mk_clo(L930, 6, 5, (V[]){a4, a3, FLD(s929, 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dfields(V *a) { (void)a; return F_Gen_dprinter_dfields(a[0], a[1], a[2], a[3], a[4]); }
static V F_Ty_dsubst(V a0, V a1) {
top:;
V s939 = a0;
if (TAG(s939) == 0) {
return F_Maybe_ddefault(F_Ty_dfind(a1, FLD(s939, 0)), C1(0, FLD(s939, 0)));
} else if (TAG(s939) == 14) {
return C2(14, FLD(s939, 0), F_Ty_dsubsts(FLD(s939, 1), a1));
} else if (TAG(s939) == 5) {
return C2(5, FLD(s939, 0), F_Ty_dsubsts(FLD(s939, 1), a1));
} else {
return s939;
}
}
static V W_Ty_dsubst(V *a) { (void)a; return F_Ty_dsubst(a[0], a[1]); }
static V F_Ty_dsubsts(V a0, V a1) {
top:;
V s940 = a0;
if ((s940) == IMM(0)) {
return IMM(0);
} else if (TAG(s940) == 1) {
return C2(1, F_Ty_dsubst(FLD(s940, 0), a1), F_Ty_dsubsts(FLD(s940, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dsubsts(V *a) { (void)a; return F_Ty_dsubsts(a[0], a[1]); }
static V F_Ty_dfind(V a0, V a1) {
top:;
V s941 = a0;
if ((s941) == IMM(0)) {
return IMM(0);
} else if (TAG(s941) == 1) {
return F_Ty_dfind_dif(FLD(FLD(s941, 0), 1), FLD(s941, 1), a1, F_String_deq(FLD(FLD(s941, 0), 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dfind(V *a) { (void)a; return F_Ty_dfind(a[0], a[1]); }
static V F_Ty_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s942 = a3;
if ((s942) == IMM(1)) {
return C1(1, a0);
} else if ((s942) == IMM(0)) {
return F_Ty_dfind(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dfind_dif(V *a) { (void)a; return F_Ty_dfind_dif(a[0], a[1], a[2], a[3]); }
static V F_Maybe_ddefault(V a2, V a3) {
top:;
V s943 = a2;
if ((s943) == IMM(0)) {
return a3;
} else if (TAG(s943) == 1) {
return FLD(s943, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Maybe_ddefault(V *a) { (void)a; return F_Maybe_ddefault(a[2], a[3]); }
static V S945(void) { static V c; return STRC(c, "&"); }
static V F_Ty_dtuple(V a0) {
top:;
V s944 = a0;
if (TAG(s944) == 14) {
return F_Ty_dtuple_dgo(C2(14, FLD(s944, 0), FLD(s944, 1)), FLD(s944, 1), F_Str_deq(FLD(s944, 0), S945()));
} else {
return C2(1, s944, IMM(0));
}
}
static V W_Ty_dtuple(V *a) { (void)a; return F_Ty_dtuple(a[0]); }
static V F_Ty_dtuple_dgo(V a0, V a1, V a2) {
top:;
V s946 = a2;
if ((s946) == IMM(1)) {
return F_Ty_dtuple_dargs(a0, a1);
} else if ((s946) == IMM(0)) {
return C2(1, a0, IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dtuple_dgo(V *a) { (void)a; return F_Ty_dtuple_dgo(a[0], a[1], a[2]); }
static V F_Ty_dtuple_dargs(V a0, V a1) {
top:;
V s947 = a1;
if (TAG(s947) == 1 && TAG(FLD(s947, 1)) == 1 && (FLD(FLD(s947, 1), 1)) == IMM(0)) {
return C2(1, FLD(s947, 0), F_Ty_dtuple(FLD(FLD(s947, 1), 0)));
} else {
return C2(1, a0, IMM(0));
}
}
static V W_Ty_dtuple_dargs(V *a) { (void)a; return F_Ty_dtuple_dargs(a[0], a[1]); }
static V S950(void) { static V c; return STRC(c, "("); }
static V S951(void) { static V c; return STRC(c, ");\012"); }
static V L949(V *a) {
return F_Gen_dpure(C1(1, F_String_dappend(a[1], F_String_dappend(S950(), F_String_dappend(a[0], S951())))));
}
static V S953(void) { static V c; return STRC(c, "FLD("); }
static V S954(void) { static V c; return STRC(c, ", 1)"); }
static V S956(void) { static V c; return STRC(c, "(FLD("); }
static V S957(void) { static V c; return STRC(c, ", 0));\012pr_s(\042, \042);\012"); }
static V L955(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(a[1], F_String_dappend(S956(), F_String_dappend(a[0], S957())))), C2(1, a[2], IMM(0)))));
}
static V L952(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dtuple(a[2], a[1], F_String_dappend(S953(), F_String_dappend(a[0], S954()))), mk_clo(L955, 3, 2, (V[]){a[0], a[3]}));
}
static V F_Gen_dprinter_dtuple(V a0, V a1, V a2) {
top:;
V s948 = a1;
if ((s948) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s948) == 1 && (FLD(s948, 1)) == IMM(0)) {
return F_Gen_dbind(F_Gen_dprinter(a0, FLD(s948, 0)), mk_clo(L949, 2, 1, (V[]){a2}));
} else if (TAG(s948) == 1) {
return F_Gen_dbind(F_Gen_dprinter(a0, FLD(s948, 0)), mk_clo(L952, 4, 3, (V[]){a2, FLD(s948, 1), a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dtuple(V *a) { (void)a; return F_Gen_dprinter_dtuple(a[0], a[1], a[2]); }
static V L958(V *a) {
return F_Gen_dproto_dgo(a[0], a[1]);
}
static V F_Gen_dproto(V a0) {
top:;
return mk_clo(L958, 2, 1, (V[]){a0});
}
static V W_Gen_dproto(V *a) { (void)a; return F_Gen_dproto(a[0]); }
static V F_Gen_dproto_dgo(V a0, V a1) {
top:;
V v959 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v959, 0), C2(2, FLD(v959, 1), a0), FLD(v959, 2), FLD(v959, 3), FLD(v959, 4), FLD(v959, 5), FLD(v959, 6)}));
}
static V W_Gen_dproto_dgo(V *a) { (void)a; return F_Gen_dproto_dgo(a[0], a[1]); }
static V L960(V *a) {
return F_Gen_dmemo_dadd_dgo(a[1], a[0]);
}
static V F_Gen_dmemo_dadd(V a0) {
top:;
return mk_clo(L960, 2, 1, (V[]){a0});
}
static V W_Gen_dmemo_dadd(V *a) { (void)a; return F_Gen_dmemo_dadd(a[0]); }
static V F_Gen_dmemo_dadd_dgo(V a0, V a1) {
top:;
V v961 = a0;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v961, 0), FLD(v961, 1), FLD(v961, 2), FLD(v961, 3), FLD(v961, 4), C2(1, a1, FLD(v961, 5)), FLD(v961, 6)}));
}
static V W_Gen_dmemo_dadd_dgo(V *a) { (void)a; return F_Gen_dmemo_dadd_dgo(a[0], a[1]); }
static V L962(V *a) {
return F_Gen_dfresh_dgo(a[0]);
}
static V F_Gen_dfresh(void) {
top:;
return mk_clo(L962, 1, 0, 0);
}
static V W_Gen_dfresh(V *a) { (void)a; return F_Gen_dfresh(); }
static V F_Gen_dfresh_dgo(V a0) {
top:;
V v963 = a0;
return C2(0, FLD(v963, 0), CN(0, 7, (V[]){F_U32_dinc(FLD(v963, 0)), FLD(v963, 1), FLD(v963, 2), FLD(v963, 3), FLD(v963, 4), FLD(v963, 5), FLD(v963, 6)}));
}
static V W_Gen_dfresh_dgo(V *a) { (void)a; return F_Gen_dfresh_dgo(a[0]); }
static V L964(V *a) {
return F_Gen_dmemo_dfind_dgo(a[1], a[0]);
}
static V F_Gen_dmemo_dfind(V a0) {
top:;
return mk_clo(L964, 2, 1, (V[]){a0});
}
static V W_Gen_dmemo_dfind(V *a) { (void)a; return F_Gen_dmemo_dfind(a[0]); }
static V F_Gen_dmemo_dfind_dgo(V a0, V a1) {
top:;
V v965 = a0;
return C2(0, F_Env_dfind(FLD(v965, 5), a1), CN(0, 7, (V[]){FLD(v965, 0), FLD(v965, 1), FLD(v965, 2), FLD(v965, 3), FLD(v965, 4), FLD(v965, 5), FLD(v965, 6)}));
}
static V W_Gen_dmemo_dfind_dgo(V *a) { (void)a; return F_Gen_dmemo_dfind_dgo(a[0], a[1]); }
static V F_Env_dfind(V a0, V a1) {
top:;
V s966 = a0;
if ((s966) == IMM(0)) {
return IMM(0);
} else if (TAG(s966) == 1) {
return F_Env_dfind_dif(FLD(FLD(s966, 0), 1), FLD(s966, 1), a1, F_String_deq(FLD(FLD(s966, 0), 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Env_dfind(V *a) { (void)a; return F_Env_dfind(a[0], a[1]); }
static V F_Env_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s967 = a3;
if ((s967) == IMM(1)) {
return C1(1, a0);
} else if ((s967) == IMM(0)) {
return F_Env_dfind(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Env_dfind_dif(V *a) { (void)a; return F_Env_dfind_dif(a[0], a[1], a[2], a[3]); }
static V S969(void) { static V c; return STRC(c, "n"); }
static V S970(void) { static V c; return STRC(c, "\042"); }
static V S971(void) { static V c; return STRC(c, "\042"); }
static V S972(void) { static V c; return STRC(c, "("); }
static V S973(void) { static V c; return STRC(c, " "); }
static V S974(void) { static V c; return STRC(c, ")"); }
static V S975(void) { static V c; return STRC(c, "{"); }
static V S976(void) { static V c; return STRC(c, "}"); }
static V S977(void) { static V c; return STRC(c, "(\134"); }
static V S978(void) { static V c; return STRC(c, " "); }
static V S979(void) { static V c; return STRC(c, ")"); }
static V S980(void) { static V c; return STRC(c, "(let "); }
static V S981(void) { static V c; return STRC(c, " "); }
static V S982(void) { static V c; return STRC(c, " "); }
static V S983(void) { static V c; return STRC(c, ")"); }
static V S984(void) { static V c; return STRC(c, "(match ["); }
static V S985(void) { static V c; return STRC(c, "] "); }
static V S986(void) { static V c; return STRC(c, ")"); }
static V S987(void) { static V c; return STRC(c, "(case "); }
static V S988(void) { static V c; return STRC(c, " => "); }
static V S989(void) { static V c; return STRC(c, ")"); }
static V S990(void) { static V c; return STRC(c, "("); }
static V S991(void) { static V c; return STRC(c, "n+ "); }
static V S992(void) { static V c; return STRC(c, ")"); }
static V S993(void) { static V c; return STRC(c, "("); }
static V S994(void) { static V c; return STRC(c, " "); }
static V S995(void) { static V c; return STRC(c, " "); }
static V S996(void) { static V c; return STRC(c, ")"); }
static V S997(void) { static V c; return STRC(c, "(: "); }
static V S998(void) { static V c; return STRC(c, " "); }
static V S999(void) { static V c; return STRC(c, ")"); }
static V S1000(void) { static V c; return STRC(c, "#"); }
static V S1001(void) { static V c; return STRC(c, "(ERR "); }
static V S1002(void) { static V c; return STRC(c, ")"); }
static V F_Expr_dshow(V a0) {
top:;
V s968 = a0;
if (TAG(s968) == 0) {
return FLD(s968, 0);
} else if (TAG(s968) == 1) {
return F_U32_dshow(FLD(s968, 0));
} else if (TAG(s968) == 2) {
return F_String_dappend(F_U32_dshow(FLD(s968, 0)), S969());
} else if (TAG(s968) == 3) {
return FLD(s968, 0);
} else if (TAG(s968) == 4) {
return F_String_dappend(S970(), F_String_dappend(FLD(s968, 0), S971()));
} else if (TAG(s968) == 5) {
return F_String_dappend(S972(), F_String_dappend(F_Expr_dshow(FLD(s968, 0)), F_String_dappend(S973(), F_String_dappend(F_Exprs_dshow(FLD(s968, 1)), S974()))));
} else if (TAG(s968) == 6) {
return F_String_dappend(FLD(s968, 0), F_String_dappend(S975(), F_String_dappend(F_Exprs_dshow(FLD(s968, 1)), S976())));
} else if (TAG(s968) == 7) {
return F_String_dappend(S977(), F_String_dappend(F_Pat_dshow(FLD(s968, 0)), F_String_dappend(S978(), F_String_dappend(F_Expr_dshow(FLD(s968, 1)), S979()))));
} else if (TAG(s968) == 8) {
return F_String_dappend(S980(), F_String_dappend(F_Pat_dshow(FLD(s968, 0)), F_String_dappend(S981(), F_String_dappend(F_Expr_dshow(FLD(s968, 1)), F_String_dappend(S982(), F_String_dappend(F_Expr_dshow(FLD(s968, 2)), S983()))))));
} else if (TAG(s968) == 9) {
return F_String_dappend(S984(), F_String_dappend(F_Exprs_dshow(FLD(s968, 0)), F_String_dappend(S985(), F_String_dappend(F_Exprs_dshow(FLD(s968, 1)), S986()))));
} else if (TAG(s968) == 10) {
return F_String_dappend(S987(), F_String_dappend(F_Pats_dshow(FLD(s968, 0)), F_String_dappend(S988(), F_String_dappend(F_Expr_dshow(FLD(s968, 1)), S989()))));
} else if (TAG(s968) == 11) {
return F_String_dappend(S990(), F_String_dappend(F_U32_dshow(FLD(s968, 0)), F_String_dappend(S991(), F_String_dappend(F_Expr_dshow(FLD(s968, 1)), S992()))));
} else if (TAG(s968) == 12) {
return F_String_dappend(S993(), F_String_dappend(FLD(s968, 0), F_String_dappend(S994(), F_String_dappend(F_Expr_dshow(FLD(s968, 1)), F_String_dappend(S995(), F_String_dappend(F_Expr_dshow(FLD(s968, 2)), S996()))))));
} else if (TAG(s968) == 13) {
return F_String_dappend(S997(), F_String_dappend(F_Expr_dshow(FLD(s968, 0)), F_String_dappend(S998(), F_String_dappend(FLD(s968, 1), S999()))));
} else if (TAG(s968) == 14) {
return F_String_dappend(S1000(), FLD(s968, 0));
} else if (TAG(s968) == 15) {
return F_String_dappend(S1001(), F_String_dappend(FLD(s968, 0), S1002()));
} else { bend_fail("incomplete match"); }
}
static V W_Expr_dshow(V *a) { (void)a; return F_Expr_dshow(a[0]); }
static V S1004(void) { static V c; return STRC(c, ""); }
static V S1005(void) { static V c; return STRC(c, " "); }
static V F_Pats_dshow(V a0) {
top:;
V s1003 = a0;
if ((s1003) == IMM(0)) {
return S1004();
} else if (TAG(s1003) == 1 && (FLD(s1003, 1)) == IMM(0)) {
return F_Pat_dshow(FLD(s1003, 0));
} else if (TAG(s1003) == 1) {
return F_String_dappend(F_Pat_dshow(FLD(s1003, 0)), F_String_dappend(S1005(), F_Pats_dshow(FLD(s1003, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Pats_dshow(V *a) { (void)a; return F_Pats_dshow(a[0]); }
static V S1007(void) { static V c; return STRC(c, "{"); }
static V S1008(void) { static V c; return STRC(c, "}"); }
static V S1009(void) { static V c; return STRC(c, "n"); }
static V S1010(void) { static V c; return STRC(c, "n+"); }
static V F_Pat_dshow(V a0) {
top:;
V s1006 = a0;
if (TAG(s1006) == 0) {
return FLD(s1006, 0);
} else if (TAG(s1006) == 1) {
return F_String_dappend(FLD(s1006, 0), F_String_dappend(S1007(), F_String_dappend(F_Pats_dshow(FLD(s1006, 1)), S1008())));
} else if (TAG(s1006) == 2) {
return F_String_dappend(F_U32_dshow(FLD(s1006, 0)), S1009());
} else if (TAG(s1006) == 3) {
return F_String_dappend(F_U32_dshow(FLD(s1006, 0)), F_String_dappend(S1010(), F_Pat_dshow(FLD(s1006, 1))));
} else if (TAG(s1006) == 4) {
return F_U32_dshow(FLD(s1006, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Pat_dshow(V *a) { (void)a; return F_Pat_dshow(a[0]); }
static V S1012(void) { static V c; return STRC(c, ""); }
static V S1013(void) { static V c; return STRC(c, " "); }
static V F_Exprs_dshow(V a0) {
top:;
V s1011 = a0;
if ((s1011) == IMM(0)) {
return S1012();
} else if (TAG(s1011) == 1 && (FLD(s1011, 1)) == IMM(0)) {
return F_Expr_dshow(FLD(s1011, 0));
} else if (TAG(s1011) == 1) {
return F_String_dappend(F_Expr_dshow(FLD(s1011, 0)), F_String_dappend(S1013(), F_Exprs_dshow(FLD(s1011, 1))));
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
V s1014 = a1;
if ((s1014) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1014) == 1) {
return F_Gen_dall_dseen(a0, FLD(s1014, 0), FLD(s1014, 1), F_Set_dhas(a2, FLD(s1014, 0)));
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
V s1015 = a2;
if ((s1015) == IMM(0)) {
return C2(0, IMM(0), IMM(0));
} else if (TAG(s1015) == 1) {
return F_Map_dhas_dleaf(FLD(s1015, 1), F_String_dcmp(a3, FLD(s1015, 0)));
} else if (TAG(s1015) == 2) {
return F_Map_dhas_dbit(FLD(s1015, 1), FLD(s1015, 2), FLD(s1015, 0), F_Map_dbit(a3, FLD(s1015, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dhas(V *a) { (void)a; return F_Map_dhas(a[2], a[3]); }
static V F_Map_dhas_dbit(V a2, V a3, V a4, V a5) {
top:;
V v1016 = a5;
V s1017 = FLD(v1016, 1);
if ((s1017) == IMM(0)) {
return F_Map_dlo(a4, a3, F_Map_dhas(a2, FLD(v1016, 0)));
} else if ((s1017) == IMM(1)) {
return F_Map_dhi(a4, a2, F_Map_dhas(a3, FLD(v1016, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dhas_dbit(V *a) { (void)a; return F_Map_dhas_dbit(a[2], a[3], a[4], a[5]); }
static V F_Map_dhas_dleaf(V a2, V a3) {
top:;
V v1018 = a3;
return C2(0, C2(1, FLD(FLD(v1018, 0), 1), a2), F_Cmp_dis__eq(FLD(v1018, 1)));
}
static V W_Map_dhas_dleaf(V *a) { (void)a; return F_Map_dhas_dleaf(a[2], a[3]); }
static V F_Gen_dall_dseen(V a0, V a1, V a2, V a3) {
top:;
V v1019 = a3;
return F_Gen_dall_dgo(a0, a1, a2, FLD(v1019, 0), FLD(v1019, 1));
}
static V W_Gen_dall_dseen(V *a) { (void)a; return F_Gen_dall_dseen(a[0], a[1], a[2], a[3]); }
static V L1022(V *a) {
return F_Gen_dall(a[3], F_List_dappend(a[4], a[2]), F_Set_dadd(a[1], a[0]));
}
static V L1021(V *a) {
return F_Gen_dbind(F_Gen_dtake__refs(), mk_clo(L1022, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Gen_dall_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1020 = a4;
if ((s1020) == IMM(1)) {
return F_Gen_dall(a0, a2, a3);
} else if ((s1020) == IMM(0)) {
return F_Gen_dbind(F_Gen_ddef(a0, a1), mk_clo(L1021, 5, 4, (V[]){a1, a3, a2, a0}));
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
V s1023 = a2;
if ((s1023) == IMM(0)) {
return C2(0, IMM(0), C2(0, a3, IMM(0)));
} else if (TAG(s1023) == 1) {
return C2(0, C2(1, FLD(s1023, 0), FLD(s1023, 1)), C2(0, a3, C1(1, FLD(s1023, 0))));
} else if (TAG(s1023) == 2) {
return F_Map_dseek_dbit(FLD(s1023, 1), FLD(s1023, 2), FLD(s1023, 0), F_Map_dbit(a3, FLD(s1023, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dseek(V *a) { (void)a; return F_Map_dseek(a[2], a[3]); }
static V F_Map_dseek_dbit(V a2, V a3, V a4, V a5) {
top:;
V v1024 = a5;
V s1025 = FLD(v1024, 1);
if ((s1025) == IMM(0)) {
return F_Map_dlo(a4, a3, F_Map_dseek(a2, FLD(v1024, 0)));
} else if ((s1025) == IMM(1)) {
return F_Map_dhi(a4, a2, F_Map_dseek(a3, FLD(v1024, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dseek_dbit(V *a) { (void)a; return F_Map_dseek_dbit(a[2], a[3], a[4], a[5]); }
static V F_Map_dset_dgo(V a2, V a3) {
top:;
V v1026 = a3;
V s1027 = FLD(FLD(v1026, 1), 1);
if ((s1027) == IMM(0)) {
return C2(1, FLD(FLD(v1026, 1), 0), a2);
} else if (TAG(s1027) == 1) {
V v1028 = FLD(FLD(v1026, 1), 0);
return F_Map_dset_dfin(FLD(v1026, 0), v1028, a2, v1028, FLD(s1027, 0));
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
V v1029 = a5;
V s1030 = FLD(v1029, 1);
if ((s1030) == IMM(0)) {
return F_Map_dins(a2, a3, a4, F_Map_ddiff(FLD(FLD(v1029, 0), 0), FLD(FLD(v1029, 0), 1)));
} else if ((s1030) == IMM(1)) {
return F_Map_dput(a2, a3, a4);
} else if ((s1030) == IMM(2)) {
return F_Map_dins(a2, a3, a4, F_Map_ddiff(FLD(FLD(v1029, 0), 0), FLD(FLD(v1029, 0), 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dset_dfin_dgo(V *a) { (void)a; return F_Map_dset_dfin_dgo(a[2], a[3], a[4], a[5]); }
static V F_Map_ddiff(V a0, V a1) {
top:;
V s1031 = a0;
V s1032 = a1;
if ((s1031) == IMM(0) && (s1032) == IMM(0)) {
return 0u;
} else if ((s1031) == IMM(0) && TAG(s1032) == 1) {
return 0u;
} else if (TAG(s1031) == 1 && (s1032) == IMM(0)) {
return 0u;
} else if (TAG(s1031) == 1 && TAG(s1032) == 1) {
return F_Map_ddiff_dfin(FLD(s1031, 1), FLD(s1032, 1), F_Map_ddiff_dstep(FLD(s1031, 0), FLD(s1032, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_ddiff(V *a) { (void)a; return F_Map_ddiff(a[0], a[1]); }
static V F_Map_ddiff_dstep(V a0, V a1) {
top:;
V s1033 = a0;
V s1034 = a1;
{
return C2(0, F_Map_ddiff_dchr(F_U32_dxor(s1033, s1034)), F_U32_dis__eq(s1033, s1034));
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
V s1035 = a0;
if ((s1035) == 0) {
return 0u;
} else if (nat_ge(s1035, 1)) {
return F_Map_dmsb_du_dif(nat_subk(s1035, 1), a1, F_U32_dis__zero(a1));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dmsb_du(V *a) { (void)a; return F_Map_dmsb_du(a[0], a[1]); }
static V F_Map_dmsb_du_dif(V a0, V a1, V a2) {
top:;
V s1036 = a2;
if ((s1036) == IMM(1)) {
return 0u;
} else if ((s1036) == IMM(0)) {
return F_Nat_dadd(1u, F_Map_dmsb_du(a0, F_U32_dshr(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dmsb_du_dif(V *a) { (void)a; return F_Map_dmsb_du_dif(a[0], a[1], a[2]); }
static V W_U32_dshr(V *a) { (void)a; return F_U32_dshr(a[0]); }
static V W_Nat_dadd(V *a) { (void)a; return F_Nat_dadd(a[0], a[1]); }
static V F_Map_ddiff_dfin(V a0, V a1, V a2) {
top:;
V v1037 = a2;
V s1038 = FLD(v1037, 1);
if ((s1038) == IMM(1)) {
return F_Nat_dadd(33u, F_Map_ddiff(a0, a1));
} else if ((s1038) == IMM(0)) {
return FLD(v1037, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Map_ddiff_dfin(V *a) { (void)a; return F_Map_ddiff_dfin(a[0], a[1], a[2]); }
static V F_Map_dins(V a2, V a3, V a4, V a5) {
top:;
V s1039 = a2;
if ((s1039) == IMM(0)) {
return C2(1, a3, a4);
} else if (TAG(s1039) == 1) {
return F_Map_dins_dsplice(a5, a3, a4, C2(1, FLD(s1039, 0), FLD(s1039, 1)));
} else if (TAG(s1039) == 2) {
return F_Map_dins_dif(a3, a4, FLD(s1039, 1), FLD(s1039, 2), FLD(s1039, 0), a5, F_Nat_dis__lt(FLD(s1039, 0), a5));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dins(V *a) { (void)a; return F_Map_dins(a[2], a[3], a[4], a[5]); }
static V F_Map_dins_dif(V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s1040 = a8;
if ((s1040) == IMM(0)) {
return F_Map_dins_dsplice(a7, a2, a3, C3(2, a6, a4, a5));
} else if ((s1040) == IMM(1)) {
return F_Map_dins_ddeep(a3, a4, a5, a7, a6, F_Map_dbit(a2, a6));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dins_dif(V *a) { (void)a; return F_Map_dins_dif(a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Map_dins_ddeep(V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V v1041 = a7;
V s1042 = FLD(v1041, 1);
if ((s1042) == IMM(0)) {
return C3(2, a6, F_Map_dins(a3, FLD(v1041, 0), a2, a5), a4);
} else if ((s1042) == IMM(1)) {
return C3(2, a6, a3, F_Map_dins(a4, FLD(v1041, 0), a2, a5));
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
V v1043 = a5;
V s1044 = FLD(v1043, 1);
if ((s1044) == IMM(0)) {
return C3(2, a4, C2(1, FLD(v1043, 0), a2), a3);
} else if ((s1044) == IMM(1)) {
return C3(2, a4, a3, C2(1, FLD(v1043, 0), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dins_dsplice_dbit(V *a) { (void)a; return F_Map_dins_dsplice_dbit(a[2], a[3], a[4], a[5]); }
static V F_Map_dput(V a2, V a3, V a4) {
top:;
V s1045 = a2;
if ((s1045) == IMM(0)) {
return C2(1, a3, a4);
} else if (TAG(s1045) == 1) {
return C2(1, FLD(s1045, 0), a4);
} else if (TAG(s1045) == 2) {
return F_Map_dput_dbit(a4, FLD(s1045, 0), FLD(s1045, 1), FLD(s1045, 2), F_Map_dbit(a3, FLD(s1045, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dput(V *a) { (void)a; return F_Map_dput(a[2], a[3], a[4]); }
static V F_Map_dput_dbit(V a2, V a3, V a4, V a5, V a6) {
top:;
V v1046 = a6;
V s1047 = FLD(v1046, 1);
if ((s1047) == IMM(0)) {
return C3(2, a3, F_Map_dput(a4, FLD(v1046, 0), a2), a5);
} else if ((s1047) == IMM(1)) {
return C3(2, a3, a4, F_Map_dput(a5, FLD(v1046, 0), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dput_dbit(V *a) { (void)a; return F_Map_dput_dbit(a[2], a[3], a[4], a[5], a[6]); }
static V L1048(V *a) {
return F_Gen_dtake__refs_dgo(a[0]);
}
static V F_Gen_dtake__refs(void) {
top:;
return mk_clo(L1048, 1, 0, 0);
}
static V W_Gen_dtake__refs(V *a) { (void)a; return F_Gen_dtake__refs(); }
static V F_Gen_dtake__refs_dgo(V a0) {
top:;
V v1049 = a0;
return C2(0, FLD(v1049, 3), CN(0, 7, (V[]){FLD(v1049, 0), FLD(v1049, 1), FLD(v1049, 2), IMM(0), FLD(v1049, 4), FLD(v1049, 5), FLD(v1049, 6)}));
}
static V W_Gen_dtake__refs_dgo(V *a) { (void)a; return F_Gen_dtake__refs_dgo(a[0]); }
static V F_Gen_ddef(V a0, V a1) {
top:;
return F_Gen_ddef_ddecl(a0, a1, F_G_ddef(a0, a1), F_G_dbody(a0, a1));
}
static V W_Gen_ddef(V *a) { (void)a; return F_Gen_ddef(a[0], a[1]); }
static V F_G_ddef(V a0, V a1) {
top:;
V v1050 = a0;
return F_G_dget(C2(0, 99u, IMM(0)), FLD(v1050, 1), a1);
}
static V W_G_ddef(V *a) { (void)a; return F_G_ddef(a[0], a[1]); }
static V F_Gen_ddef_ddecl(V a0, V a1, V a2, V a3) {
top:;
V v1051 = a2;
V s1052 = a3;
if (TAG(s1052) == 0) {
return F_Gen_ddef_dnative(a0, a1, FLD(v1051, 1), FLD(s1052, 2), F_Gen_dsig(FLD(s1052, 1), FLD(v1051, 1), 0u, C3(0, IMM(0), IMM(0), IMM(0))), F_U32_dis__eq(FLD(v1051, 0), 2u));
} else if (TAG(s1052) == 1) {
return F_Gen_ddef_deff(a1, F_Gen_dsig(FLD(s1052, 1), FLD(v1051, 1), 0u, C3(0, IMM(0), IMM(0), IMM(0))), FLD(s1052, 2));
} else {
return F_Gen_ddef_dlaw(a1, FLD(v1051, 1), F_U32_dis__eq(FLD(v1051, 0), 2u));
}
}
static V W_Gen_ddef_ddecl(V *a) { (void)a; return F_Gen_ddef_ddecl(a[0], a[1], a[2], a[3]); }
static V F_Gen_ddef_dlaw(V a0, V a1, V a2) {
top:;
V s1053 = a2;
if ((s1053) == IMM(1)) {
return F_Gen_dwrapper(a0, F_Sig_dwargs(F_Gen_dsig(F_Gen_ddummy__params(a1), a1, 0u, C3(0, IMM(0), IMM(0), IMM(0)))));
} else if ((s1053) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_ddef_dlaw(V *a) { (void)a; return F_Gen_ddef_dlaw(a[0], a[1], a[2]); }
static V S1055(void) { static V c; return STRC(c, "_"); }
static V S1056(void) { static V c; return STRC(c, ""); }
static V F_Gen_ddummy__params(V a0) {
top:;
V s1054 = a0;
if ((s1054) == IMM(0)) {
return IMM(0);
} else if (TAG(s1054) == 1) {
return C2(1, C3(0, S1055(), 0u, S1056()), F_Gen_ddummy__params(FLD(s1054, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_ddummy__params(V *a) { (void)a; return F_Gen_ddummy__params(a[0]); }
static V S1061(void) { static V c; return STRC(c, "a"); }
static V S1062(void) { static V c; return STRC(c, "a["); }
static V S1063(void) { static V c; return STRC(c, "]"); }
static V S1065(void) { static V c; return STRC(c, "0"); }
static V F_Gen_dsig(V a0, V a1, V a2, V a3) {
top:;
V s1057 = a0;
V s1058 = a1;
if (TAG(s1057) == 1 && TAG(s1058) == 1 && (FLD(s1058, 0)) == IMM(1)) {
V v1059 = a3;
V v1060 = F_String_dappend(S1061(), F_U32_dshow(a2));
{ V t0 = FLD(s1057, 1); V t1 = FLD(s1058, 1); V t2 = F_U32_dinc(a2); V t3 = C3(0, F_List_dappend(FLD(v1059, 0), C2(1, v1060, IMM(0))), C2(1, C2(0, FLD(FLD(s1057, 0), 0), v1060), FLD(v1059, 1)), F_List_dappend(FLD(v1059, 2), C2(1, F_String_dappend(S1062(), F_String_dappend(F_U32_dshow(a2), S1063())), IMM(0)))); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1057) == 1 && TAG(s1058) == 1 && (FLD(s1058, 0)) == IMM(0)) {
V v1064 = a3;
{ V t0 = FLD(s1057, 1); V t1 = FLD(s1058, 1); V t2 = F_U32_dinc(a2); V t3 = C3(0, FLD(v1064, 0), C2(1, C2(0, FLD(FLD(s1057, 0), 0), S1065()), FLD(v1064, 1)), FLD(v1064, 2)); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else {
return a3;
}
}
static V W_Gen_dsig(V *a) { (void)a; return F_Gen_dsig(a[0], a[1], a[2], a[3]); }
static V F_Sig_dwargs(V a0) {
top:;
V v1066 = a0;
return FLD(v1066, 2);
}
static V W_Sig_dwargs(V *a) { (void)a; return F_Sig_dwargs(a[0]); }
static V S1068(void) { static V c; return STRC(c, "static V "); }
static V S1069(void) { static V c; return STRC(c, "(V *a);\012"); }
static V S1071(void) { static V c; return STRC(c, "static V "); }
static V S1072(void) { static V c; return STRC(c, "(V *a) { (void)a; return "); }
static V S1073(void) { static V c; return STRC(c, "("); }
static V S1074(void) { static V c; return STRC(c, ", "); }
static V S1075(void) { static V c; return STRC(c, "); }\012"); }
static V L1070(V *a) {
return F_Gen_dcode(C1(1, F_String_dappend(S1071(), F_String_dappend(a[2], F_String_dappend(S1072(), F_String_dappend(F_Gen_df(a[1]), F_String_dappend(S1073(), F_String_dappend(F_String_djoin(a[0], S1074()), S1075()))))))));
}
static V F_Gen_dwrapper(V a0, V a1) {
top:;
V v1067 = F_Gen_dw(a0);
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S1068(), F_String_dappend(v1067, S1069())))), mk_clo(L1070, 4, 3, (V[]){a1, a0, v1067}));
}
static V W_Gen_dwrapper(V *a) { (void)a; return F_Gen_dwrapper(a[0], a[1]); }
static V F_String_djoin(V a0, V a1) {
top:;
V s1076 = a0;
if ((s1076) == IMM(0)) {
return IMM(0);
} else if (TAG(s1076) == 1) {
return F_String_djoin_dgo(FLD(s1076, 1), FLD(s1076, 0), a1);
} else { bend_fail("incomplete match"); }
}
static V W_String_djoin(V *a) { (void)a; return F_String_djoin(a[0], a[1]); }
static V F_String_djoin_dgo(V a0, V a1, V a2) {
top:;
V s1077 = a0;
if ((s1077) == IMM(0)) {
return a1;
} else if (TAG(s1077) == 1) {
return F_String_dappend(a1, F_String_dappend(a2, F_String_djoin_dgo(FLD(s1077, 1), FLD(s1077, 0), a2)));
} else { bend_fail("incomplete match"); }
}
static V W_String_djoin_dgo(V *a) { (void)a; return F_String_djoin_dgo(a[0], a[1], a[2]); }
static V S1078(void) { static V c; return STRC(c, "F_"); }
static V F_Gen_df(V a0) {
top:;
return F_String_dappend(S1078(), F_Gen_dmangle(a0));
}
static V W_Gen_df(V *a) { (void)a; return F_Gen_df(a[0]); }
static V S1080(void) { static V c; return STRC(c, ""); }
static V F_Gen_dmangle(V a0) {
top:;
V s1079 = a0;
if ((s1079) == IMM(0)) {
return S1080();
} else if (TAG(s1079) == 1) {
return F_String_dappend(F_Gen_dmangle_dchr(FLD(s1079, 0)), F_Gen_dmangle(FLD(s1079, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dmangle(V *a) { (void)a; return F_Gen_dmangle(a[0]); }
static V S1081(void) { static V c; return STRC(c, "_d"); }
static V S1082(void) { static V c; return STRC(c, "__"); }
static V S1083(void) { static V c; return STRC(c, "_x"); }
static V F_Gen_dmangle_dchr(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__eq(a0, 46u), S1081(), F_Bool_dpick(F_U32_dis__eq(a0, 95u), S1082(), F_Bool_dpick(F_Bool_dor(F_Char_dis__alpha(a0), F_Char_dis__digit(a0)), F_Str_dchr(a0), F_String_dappend(S1083(), F_U32_dshow(a0)))));
}
static V W_Gen_dmangle_dchr(V *a) { (void)a; return F_Gen_dmangle_dchr(a[0]); }
static V F_Str_dchr(V a0) {
top:;
return C2(1, a0, IMM(0));
}
static V W_Str_dchr(V *a) { (void)a; return F_Str_dchr(a[0]); }
static V S1084(void) { static V c; return STRC(c, "W_"); }
static V F_Gen_dw(V a0) {
top:;
return F_String_dappend(S1084(), F_Gen_dmangle(a0));
}
static V W_Gen_dw(V *a) { (void)a; return F_Gen_dw(a[0]); }
static V S1088(void) { static V c; return STRC(c, "E_"); }
static V S1090(void) { static V c; return STRC(c, "static V "); }
static V S1091(void) { static V c; return STRC(c, "("); }
static V S1092(void) { static V c; return STRC(c, ")"); }
static V S1094(void) { static V c; return STRC(c, ";\012static V "); }
static V S1095(void) { static V c; return STRC(c, "(V *a);\012"); }
static V S1097(void) { static V c; return STRC(c, "static V "); }
static V S1098(void) { static V c; return STRC(c, "(V *a) { return io_req("); }
static V S1099(void) { static V c; return STRC(c, ", "); }
static V S1100(void) { static V c; return STRC(c, ", (V[]){"); }
static V S1101(void) { static V c; return STRC(c, "a["); }
static V S1102(void) { static V c; return STRC(c, "]"); }
static V S1103(void) { static V c; return STRC(c, ", "); }
static V S1104(void) { static V c; return STRC(c, "}); }\012"); }
static V S1106(void) { static V c; return STRC(c, " { return mk_clo("); }
static V S1107(void) { static V c; return STRC(c, ", "); }
static V S1108(void) { static V c; return STRC(c, ", "); }
static V S1109(void) { static V c; return STRC(c, ", "); }
static V S1110(void) { static V c; return STRC(c, "0"); }
static V S1111(void) { static V c; return STRC(c, "(V[]){"); }
static V S1112(void) { static V c; return STRC(c, ", "); }
static V S1113(void) { static V c; return STRC(c, "}"); }
static V S1114(void) { static V c; return STRC(c, "); }\012"); }
static V L1115(V *a) {
return F_Gen_dwrapper(a[1], a[0]);
}
static V L1105(V *a) {
return F_Gen_dbind(F_Gen_dcode(C1(1, F_String_dappend(a[5], F_String_dappend(S1106(), F_String_dappend(a[4], F_String_dappend(S1107(), F_String_dappend(F_U32_dshow(F_U32_dadd(a[3], 2u)), F_String_dappend(S1108(), F_String_dappend(F_U32_dshow(a[3]), F_String_dappend(S1109(), F_String_dappend(F_Bool_dpick(F_U32_dis__zero(a[3]), S1110(), F_String_dappend(S1111(), F_String_dappend(F_String_djoin(a[2], S1112()), S1113()))), S1114()))))))))))), mk_clo(L1115, 3, 2, (V[]){a[0], a[1]}));
}
static V L1096(V *a) {
return F_Gen_dbind(F_Gen_dcode(C1(1, F_String_dappend(S1097(), F_String_dappend(a[5], F_String_dappend(S1098(), F_String_dappend(F_Gen_dcid(a[4]), F_String_dappend(S1099(), F_String_dappend(F_U32_dshow(F_U32_dinc(a[3])), F_String_dappend(S1100(), F_String_dappend(F_String_djoin(F_List_dappend(F_Gen_deff_dargs(F_U32_dto__nat(a[3]), 0u), C2(1, F_String_dappend(S1101(), F_String_dappend(F_U32_dshow(F_U32_dinc(a[3])), S1102())), IMM(0))), S1103()), S1104())))))))))), mk_clo(L1105, 7, 6, (V[]){a[0], a[4], a[1], a[3], a[5], a[2]}));
}
static V L1093(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(a[5], F_String_dappend(S1094(), F_String_dappend(a[4], S1095()))))), mk_clo(L1096, 7, 6, (V[]){a[0], a[1], a[5], a[2], a[3], a[4]}));
}
static V F_Gen_ddef_deff(V a0, V a1, V a2) {
top:;
V v1085 = a1;
V v1086 = F_U32_dfrom__nat(F_List_dlength(FLD(v1085, 0)));
V v1087 = F_String_dappend(S1088(), F_Gen_dmangle(a0));
V v1089 = F_String_dappend(S1090(), F_String_dappend(F_Gen_df(a0), F_String_dappend(S1091(), F_String_dappend(F_Gen_dcparams(FLD(v1085, 0)), S1092()))));
return F_Gen_dbind(F_Gen_deffs(a2), mk_clo(L1093, 7, 6, (V[]){FLD(v1085, 2), FLD(v1085, 0), v1086, a0, v1087, v1089}));
}
static V W_Gen_ddef_deff(V *a) { (void)a; return F_Gen_ddef_deff(a[0], a[1], a[2]); }
static V S1117(void) { static V c; return STRC(c, "a["); }
static V S1118(void) { static V c; return STRC(c, "]"); }
static V F_Gen_deff_dargs(V a0, V a1) {
top:;
V s1116 = a0;
if ((s1116) == 0) {
return IMM(0);
} else if (nat_ge(s1116, 1)) {
return C2(1, F_String_dappend(S1117(), F_String_dappend(F_U32_dshow(a1), S1118())), F_Gen_deff_dargs(nat_subk(s1116, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_deff_dargs(V *a) { (void)a; return F_Gen_deff_dargs(a[0], a[1]); }
static V S1119(void) { static V c; return STRC(c, "CID_"); }
static V F_Gen_dcid(V a0) {
top:;
return F_String_dappend(S1119(), F_Gen_dhost(F_String_dto__upper(a0)));
}
static V W_Gen_dcid(V *a) { (void)a; return F_Gen_dcid(a[0]); }
static V F_String_dto__upper(V a0) {
top:;
V s1120 = a0;
if ((s1120) == IMM(0)) {
return IMM(0);
} else if (TAG(s1120) == 1) {
return C2(1, F_Char_dto__upper(FLD(s1120, 0)), F_String_dto__upper(FLD(s1120, 1)));
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
V s1121 = a0;
if ((s1121) == IMM(0)) {
return 0u;
} else if ((s1121) == IMM(1)) {
return 1u;
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dto__u32(V *a) { (void)a; return F_Bool_dto__u32(a[0]); }
static V S1123(void) { static V c; return STRC(c, ""); }
static V F_Gen_dhost(V a0) {
top:;
V s1122 = a0;
if ((s1122) == IMM(0)) {
return S1123();
} else if (TAG(s1122) == 1) {
return F_String_dappend(F_Gen_dhost_dchr(FLD(s1122, 0)), F_Gen_dhost(FLD(s1122, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dhost(V *a) { (void)a; return F_Gen_dhost(a[0]); }
static V S1124(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dhost_dchr(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__eq(a0, 46u), S1124(), F_Str_dchr(a0));
}
static V W_Gen_dhost_dchr(V *a) { (void)a; return F_Gen_dhost_dchr(a[0]); }
static V L1125(V *a) {
return F_Gen_deffs_dgo(a[0], a[1]);
}
static V F_Gen_deffs(V a0) {
top:;
return mk_clo(L1125, 2, 1, (V[]){a0});
}
static V W_Gen_deffs(V *a) { (void)a; return F_Gen_deffs(a[0]); }
static V F_Gen_deffs_dgo(V a0, V a1) {
top:;
V v1126 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v1126, 0), FLD(v1126, 1), FLD(v1126, 2), FLD(v1126, 3), FLD(v1126, 4), FLD(v1126, 5), F_List_dappend(F_Gen_deffs_dc(a0), FLD(v1126, 6))}));
}
static V W_Gen_deffs_dgo(V *a) { (void)a; return F_Gen_deffs_dgo(a[0], a[1]); }
static V S1128(void) { static V c; return STRC(c, ".c"); }
static V F_Gen_deffs_dc(V a0) {
top:;
V s1127 = a0;
if ((s1127) == IMM(0)) {
return IMM(0);
} else if (TAG(s1127) == 1) {
return F_Gen_deffs_dc_dif(FLD(s1127, 0), F_Gen_deffs_dc(FLD(s1127, 1)), F_String_dends__with(FLD(s1127, 0), S1128()));
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
V s1129 = a2;
if ((s1129) == IMM(1)) {
return C2(1, a0, a1);
} else if ((s1129) == IMM(0)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Gen_deffs_dc_dif(V *a) { (void)a; return F_Gen_deffs_dc_dif(a[0], a[1], a[2]); }
static V S1131(void) { static V c; return STRC(c, "void"); }
static V S1132(void) { static V c; return STRC(c, ", "); }
static V F_Gen_dcparams(V a0) {
top:;
V s1130 = a0;
if ((s1130) == IMM(0)) {
return S1131();
} else if (TAG(s1130) == 1) {
return F_String_djoin(F_Gen_dcparams_dgo(C2(1, FLD(s1130, 0), FLD(s1130, 1))), S1132());
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcparams(V *a) { (void)a; return F_Gen_dcparams(a[0]); }
static V S1134(void) { static V c; return STRC(c, "V "); }
static V F_Gen_dcparams_dgo(V a0) {
top:;
V s1133 = a0;
if ((s1133) == IMM(0)) {
return IMM(0);
} else if (TAG(s1133) == 1) {
return C2(1, F_String_dappend(S1134(), FLD(s1133, 0)), F_Gen_dcparams_dgo(FLD(s1133, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcparams_dgo(V *a) { (void)a; return F_Gen_dcparams_dgo(a[0]); }
static V F_Gen_ddef_dnative(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1135 = a5;
if ((s1135) == IMM(1)) {
return F_Gen_dwrapper(a1, F_Sig_dwargs(a4));
} else if ((s1135) == IMM(0)) {
return F_Gen_ddef_dbody(a0, a1, a2, a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_ddef_dnative(V *a) { (void)a; return F_Gen_ddef_dnative(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1138(void) { static V c; return STRC(c, "static V "); }
static V S1139(void) { static V c; return STRC(c, "("); }
static V S1140(void) { static V c; return STRC(c, ")"); }
static V S1141(void) { static V c; return STRC(c, ";\012"); }
static V S1143(void) { static V c; return STRC(c, "Nat"); }
static V S1145(void) { static V c; return STRC(c, " {\012top:;\012"); }
static V S1146(void) { static V c; return STRC(c, "}\012"); }
static V L1147(V *a) {
return F_Gen_dwrapper(a[1], a[0]);
}
static V L1144(V *a) {
return F_Gen_dbind(F_Gen_dcode(F_Doc_dlist(C2(1, C1(1, F_String_dappend(a[2], S1145())), C2(1, a[3], C2(1, C1(1, S1146()), IMM(0)))))), mk_clo(L1147, 3, 2, (V[]){a[0], a[1]}));
}
static V L1142(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[7], a[6], C3(0, a[5], a[4], a[3]), IMM(0), F_R_dops(a[2], S1143())), mk_clo(L1144, 4, 3, (V[]){a[0], a[5], a[1]}));
}
static V F_Gen_ddef_dbody(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1136 = a4;
V v1137 = F_String_dappend(S1138(), F_String_dappend(F_Gen_df(a1), F_String_dappend(S1139(), F_String_dappend(F_Gen_dcparams(FLD(v1136, 0)), S1140()))));
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(v1137, S1141()))), mk_clo(L1142, 9, 8, (V[]){FLD(v1136, 2), v1137, a3, FLD(v1136, 0), a2, a1, FLD(v1136, 1), a0}));
}
static V W_Gen_ddef_dbody(V *a) { (void)a; return F_Gen_ddef_dbody(a[0], a[1], a[2], a[3], a[4]); }
static V S1149(void) { static V c; return STRC(c, "."); }
static V F_R_dops(V a0, V a1) {
top:;
V s1148 = a0;
if (TAG(s1148) == 12) {
return C2(5, C1(0, F_String_dappend(a1, F_String_dappend(S1149(), F_R_dopname(FLD(s1148, 0))))), C2(1, F_R_dops(FLD(s1148, 1), a1), C2(1, F_R_dops(FLD(s1148, 2), a1), IMM(0))));
} else if (TAG(s1148) == 13) {
{ V t0 = FLD(s1148, 0); V t1 = F_Bool_dpick(F_String_dis__empty(FLD(s1148, 1)), a1, FLD(s1148, 1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1148) == 5) {
return C2(5, F_R_dops(FLD(s1148, 0), a1), F_R_dopss(FLD(s1148, 1), a1));
} else if (TAG(s1148) == 6) {
return C2(6, FLD(s1148, 0), F_R_dopss(FLD(s1148, 1), a1));
} else if (TAG(s1148) == 7) {
return C2(7, FLD(s1148, 0), F_R_dops(FLD(s1148, 1), a1));
} else if (TAG(s1148) == 8) {
return C3(8, FLD(s1148, 0), F_R_dops(FLD(s1148, 1), a1), F_R_dops(FLD(s1148, 2), a1));
} else if (TAG(s1148) == 9) {
return C2(9, F_R_dopss(FLD(s1148, 0), a1), F_R_dopss(FLD(s1148, 1), a1));
} else if (TAG(s1148) == 10) {
return C2(10, FLD(s1148, 0), F_R_dops(FLD(s1148, 1), a1));
} else if (TAG(s1148) == 11) {
return C2(11, FLD(s1148, 0), F_R_dops(FLD(s1148, 1), a1));
} else {
return s1148;
}
}
static V W_R_dops(V *a) { (void)a; return F_R_dops(a[0], a[1]); }
static V F_R_dopss(V a0, V a1) {
top:;
V s1150 = a0;
if ((s1150) == IMM(0)) {
return IMM(0);
} else if (TAG(s1150) == 1) {
return C2(1, F_R_dops(FLD(s1150, 0), a1), F_R_dopss(FLD(s1150, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_R_dopss(V *a) { (void)a; return F_R_dopss(a[0], a[1]); }
static V S1151(void) { static V c; return STRC(c, "+"); }
static V S1152(void) { static V c; return STRC(c, "-"); }
static V S1153(void) { static V c; return STRC(c, "*"); }
static V S1154(void) { static V c; return STRC(c, "/"); }
static V S1155(void) { static V c; return STRC(c, "%"); }
static V S1156(void) { static V c; return STRC(c, "<"); }
static V S1157(void) { static V c; return STRC(c, "<="); }
static V S1158(void) { static V c; return STRC(c, ">"); }
static V S1159(void) { static V c; return STRC(c, ">="); }
static V S1160(void) { static V c; return STRC(c, ".&."); }
static V S1161(void) { static V c; return STRC(c, ".|."); }
static V S1162(void) { static V c; return STRC(c, ".^."); }
static V S1163(void) { static V c; return STRC(c, "<<"); }
static V S1164(void) { static V c; return STRC(c, ">>"); }
static V F_R_dopname(V a0) {
top:;
return F_R_dopname_dgo(F_P_dwhich(a0, C2(1, S1151(), C2(1, S1152(), C2(1, S1153(), C2(1, S1154(), C2(1, S1155(), C2(1, S1156(), C2(1, S1157(), C2(1, S1158(), C2(1, S1159(), C2(1, S1160(), C2(1, S1161(), C2(1, S1162(), C2(1, S1163(), C2(1, S1164(), IMM(0)))))))))))))))));
}
static V W_R_dopname(V *a) { (void)a; return F_R_dopname(a[0]); }
static V S1166(void) { static V c; return STRC(c, "add"); }
static V S1167(void) { static V c; return STRC(c, "sub"); }
static V S1168(void) { static V c; return STRC(c, "mul"); }
static V S1169(void) { static V c; return STRC(c, "div"); }
static V S1170(void) { static V c; return STRC(c, "mod"); }
static V S1171(void) { static V c; return STRC(c, "is_lt"); }
static V S1172(void) { static V c; return STRC(c, "is_le"); }
static V S1173(void) { static V c; return STRC(c, "is_gt"); }
static V S1174(void) { static V c; return STRC(c, "is_ge"); }
static V S1175(void) { static V c; return STRC(c, "and"); }
static V S1176(void) { static V c; return STRC(c, "or"); }
static V S1177(void) { static V c; return STRC(c, "xor"); }
static V S1178(void) { static V c; return STRC(c, "shln"); }
static V S1179(void) { static V c; return STRC(c, "shrn"); }
static V S1180(void) { static V c; return STRC(c, "\077"); }
static V F_R_dopname_dgo(V a0) {
top:;
V s1165 = a0;
if ((s1165) == 0) {
return S1166();
} else if ((s1165) == 1) {
return S1167();
} else if ((s1165) == 2) {
return S1168();
} else if ((s1165) == 3) {
return S1169();
} else if ((s1165) == 4) {
return S1170();
} else if ((s1165) == 5) {
return S1171();
} else if ((s1165) == 6) {
return S1172();
} else if ((s1165) == 7) {
return S1173();
} else if ((s1165) == 8) {
return S1174();
} else if ((s1165) == 9) {
return S1175();
} else if ((s1165) == 10) {
return S1176();
} else if ((s1165) == 11) {
return S1177();
} else if ((s1165) == 12) {
return S1178();
} else if ((s1165) == 13) {
return S1179();
} else if (nat_ge(s1165, 14)) {
return S1180();
} else { bend_fail("incomplete match"); }
}
static V W_R_dopname_dgo(V *a) { (void)a; return F_R_dopname_dgo(a[0]); }
static V L1182(V *a) {
return F_Gen_dpure(F_Gen_dret(a[0], a[1]));
}
static V F_Gen_dstmt(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1181 = a4;
if (TAG(s1181) == 8) {
return F_Gen_dlet(a0, a1, a2, a3, FLD(s1181, 0), FLD(s1181, 1), FLD(s1181, 2));
} else if (TAG(s1181) == 9) {
return F_Gen_dmatch(a0, a1, a2, a3, FLD(s1181, 0), FLD(s1181, 1));
} else if (TAG(s1181) == 5 && TAG(FLD(s1181, 0)) == 0) {
return F_Gen_dstmt_dcall(a0, a1, a2, a3, FLD(FLD(s1181, 0), 0), FLD(s1181, 1), F_Gen_dis__tail(a1, a2, a3, FLD(FLD(s1181, 0), 0), FLD(s1181, 1)));
} else {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, s1181), mk_clo(L1182, 2, 1, (V[]){a3}));
}
}
static V W_Gen_dstmt(V *a) { (void)a; return F_Gen_dstmt(a[0], a[1], a[2], a[3], a[4]); }
static V S1184(void) { static V c; return STRC(c, "return "); }
static V S1185(void) { static V c; return STRC(c, ";\012"); }
static V S1186(void) { static V c; return STRC(c, " = "); }
static V S1187(void) { static V c; return STRC(c, ";\012"); }
static V F_Gen_dret(V a0, V a1) {
top:;
V s1183 = a0;
if ((s1183) == IMM(0)) {
return F_Doc_dlist(C2(1, C1(1, S1184()), C2(1, a1, C2(1, C1(1, S1185()), IMM(0)))));
} else if (TAG(s1183) == 1) {
return F_Doc_dlist(C2(1, C1(1, FLD(s1183, 0)), C2(1, C1(1, S1186()), C2(1, a1, C2(1, C1(1, S1187()), IMM(0))))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dret(V *a) { (void)a; return F_Gen_dret(a[0], a[1]); }
static V S1189(void) { static V c; return STRC(c, "u"); }
static V S1190(void) { static V c; return STRC(c, "u"); }
static V S1191(void) { static V c; return STRC(c, "VF("); }
static V S1192(void) { static V c; return STRC(c, "f)"); }
static V S1194(void) { static V c; return STRC(c, "nat_addk("); }
static V S1195(void) { static V c; return STRC(c, ", "); }
static V S1196(void) { static V c; return STRC(c, ")"); }
static V L1193(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1194()), C2(1, a[1], C2(1, C1(1, F_String_dappend(S1195(), F_String_dappend(F_U32_dshow(a[0]), S1196()))), IMM(0))))));
}
static V S1197(void) { static V c; return STRC(c, "0"); }
static V S1198(void) { static V c; return STRC(c, "parse error: "); }
static V S1200(void) { static V c; return STRC(c, "0"); }
static V L1199(V *a) {
return F_Gen_dpure(C1(1, S1200()));
}
static V S1201(void) { static V c; return STRC(c, "unexpected expression: "); }
static V S1203(void) { static V c; return STRC(c, "0"); }
static V L1202(V *a) {
return F_Gen_dpure(C1(1, S1203()));
}
static V F_Gen_dexpr(V a0, V a1, V a2) {
top:;
V s1188 = a2;
if (TAG(s1188) == 0) {
return F_Gen_dvar(a0, a1, FLD(s1188, 0));
} else if (TAG(s1188) == 1) {
return F_Gen_dpure(C1(1, F_String_dappend(F_U32_dshow(FLD(s1188, 0)), S1189())));
} else if (TAG(s1188) == 2) {
return F_Gen_dpure(C1(1, F_String_dappend(F_U32_dshow(FLD(s1188, 0)), S1190())));
} else if (TAG(s1188) == 3) {
return F_Gen_dpure(C1(1, F_String_dappend(S1191(), F_String_dappend(FLD(s1188, 0), S1192()))));
} else if (TAG(s1188) == 4) {
return F_Gen_dstr(FLD(s1188, 0));
} else if (TAG(s1188) == 5) {
return F_Gen_dcall(a0, a1, FLD(s1188, 0), FLD(s1188, 1));
} else if (TAG(s1188) == 6) {
return F_Gen_dctor(a0, a1, FLD(s1188, 0), FLD(s1188, 1));
} else if (TAG(s1188) == 7) {
return F_Gen_dlam(a0, a1, FLD(s1188, 0), FLD(s1188, 1));
} else if (TAG(s1188) == 8) {
return F_Gen_dblock(a0, a1, C3(8, FLD(s1188, 0), FLD(s1188, 1), FLD(s1188, 2)));
} else if (TAG(s1188) == 9) {
return F_Gen_dblock(a0, a1, C2(9, FLD(s1188, 0), FLD(s1188, 1)));
} else if (TAG(s1188) == 11) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, FLD(s1188, 1)), mk_clo(L1193, 2, 1, (V[]){FLD(s1188, 0)}));
} else if (TAG(s1188) == 14) {
return F_Gen_dpure(C1(1, S1197()));
} else if (TAG(s1188) == 15) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1198(), FLD(s1188, 0))), mk_clo(L1199, 1, 0, 0));
} else {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1201(), F_Expr_dshow(s1188))), mk_clo(L1202, 1, 0, 0));
}
}
static V W_Gen_dexpr(V *a) { (void)a; return F_Gen_dexpr(a[0], a[1], a[2]); }
static V S1205(void) { static V c; return STRC(c, "r"); }
static V S1208(void) { static V c; return STRC(c, "({ V "); }
static V S1209(void) { static V c; return STRC(c, ";\012"); }
static V S1210(void) { static V c; return STRC(c, "; })"); }
static V L1207(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1208(), F_String_dappend(a[0], S1209()))), C2(1, a[1], C2(1, C1(1, F_String_dappend(a[0], S1210())), IMM(0))))));
}
static V L1206(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[2], a[1], F_Self_dnone(), C1(1, a[3]), a[0]), mk_clo(L1207, 2, 1, (V[]){a[3]}));
}
static V L1204(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1205(), F_U32_dshow(a[3]))), mk_clo(L1206, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Gen_dblock(V a0, V a1, V a2) {
top:;
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1204, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Gen_dblock(V *a) { (void)a; return F_Gen_dblock(a[0], a[1], a[2]); }
static V S1211(void) { static V c; return STRC(c, ""); }
static V F_Self_dnone(void) {
top:;
return C3(0, S1211(), IMM(0), IMM(0));
}
static V W_Self_dnone(V *a) { (void)a; return F_Self_dnone(); }
static V S1215(void) { static V c; return STRC(c, "L"); }
static V S1217(void) { static V c; return STRC(c, "static V "); }
static V S1218(void) { static V c; return STRC(c, "(V *a);\012"); }
static V S1220(void) { static V c; return STRC(c, "a["); }
static V S1221(void) { static V c; return STRC(c, "]"); }
static V S1224(void) { static V c; return STRC(c, "static V "); }
static V S1225(void) { static V c; return STRC(c, "(V *a) {\012"); }
static V S1226(void) { static V c; return STRC(c, "}\012"); }
static V S1228(void) { static V c; return STRC(c, "mk_clo("); }
static V S1229(void) { static V c; return STRC(c, ", "); }
static V S1230(void) { static V c; return STRC(c, ", "); }
static V S1231(void) { static V c; return STRC(c, ", "); }
static V S1232(void) { static V c; return STRC(c, ")"); }
static V L1227(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1228(), F_String_dappend(a[2], F_String_dappend(S1229(), F_String_dappend(F_U32_dshow(F_U32_dinc(a[1])), F_String_dappend(S1230(), F_String_dappend(F_U32_dshow(a[1]), S1231()))))))), C2(1, F_Gen_darr(F_Gen_dcaps_douter(a[0])), C2(1, C1(1, S1232()), IMM(0))))));
}
static V L1223(V *a) {
return F_Gen_dbind(F_Gen_dcode(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1224(), F_String_dappend(a[2], S1225()))), C2(1, a[3], C2(1, C1(1, S1226()), IMM(0)))))), mk_clo(L1227, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L1222(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[4], F_List_dappend(a[5], F_Gen_dcaps_dinner(a[3], 0u)), F_Self_dnone(), IMM(0), a[2]), mk_clo(L1223, 4, 3, (V[]){a[3], a[0], a[1]}));
}
static V L1219(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_PatR_dbinds(F_Gen_dpat(a[5], a[4], F_String_dappend(S1220(), F_String_dappend(F_U32_dshow(a[3]), S1221())), C2(0, IMM(0), IMM(0))))), mk_clo(L1222, 6, 5, (V[]){a[3], a[0], a[1], a[2], a[5]}));
}
static V L1216(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S1217(), F_String_dappend(a[5], S1218())))), mk_clo(L1219, 7, 6, (V[]){a[5], a[0], a[1], a[2], a[3], a[4]}));
}
static V L1214(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1215(), F_U32_dshow(a[5]))), mk_clo(L1216, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V F_Gen_dlam(V a0, V a1, V a2, V a3) {
top:;
V v1212 = F_Gen_dcaps(F_FV_dexpr(a3, F_Pat_dvars(a2, IMM(0)), IMM(0)), a1);
V v1213 = F_U32_dfrom__nat(F_List_dlength(v1212));
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1214, 6, 5, (V[]){a3, v1212, v1213, a2, a0}));
}
static V W_Gen_dlam(V *a) { (void)a; return F_Gen_dlam(a[0], a[1], a[2], a[3]); }
static V F_Gen_dcaps_douter(V a0) {
top:;
V s1233 = a0;
if ((s1233) == IMM(0)) {
return IMM(0);
} else if (TAG(s1233) == 1) {
return C2(1, C1(1, FLD(FLD(s1233, 0), 1)), F_Gen_dcaps_douter(FLD(s1233, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps_douter(V *a) { (void)a; return F_Gen_dcaps_douter(a[0]); }
static V S1235(void) { static V c; return STRC(c, "0"); }
static V S1236(void) { static V c; return STRC(c, "(V[]){"); }
static V S1237(void) { static V c; return STRC(c, "}"); }
static V F_Gen_darr(V a0) {
top:;
V s1234 = a0;
if ((s1234) == IMM(0)) {
return C1(1, S1235());
} else if (TAG(s1234) == 1) {
return F_Doc_dlist(C2(1, C1(1, S1236()), C2(1, F_Gen_dcommas(C2(1, FLD(s1234, 0), FLD(s1234, 1))), C2(1, C1(1, S1237()), IMM(0)))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_darr(V *a) { (void)a; return F_Gen_darr(a[0]); }
static V S1238(void) { static V c; return STRC(c, ", "); }
static V F_Gen_dcommas(V a0) {
top:;
return F_Doc_dsep(a0, S1238());
}
static V W_Gen_dcommas(V *a) { (void)a; return F_Gen_dcommas(a[0]); }
static V F_Doc_dsep(V a0, V a1) {
top:;
V s1239 = a0;
if ((s1239) == IMM(0)) {
return IMM(0);
} else if (TAG(s1239) == 1) {
return C2(2, FLD(s1239, 0), F_Doc_dsep_dgo(FLD(s1239, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dsep(V *a) { (void)a; return F_Doc_dsep(a[0], a[1]); }
static V F_Doc_dsep_dgo(V a0, V a1) {
top:;
V s1240 = a0;
if ((s1240) == IMM(0)) {
return IMM(0);
} else if (TAG(s1240) == 1) {
return C2(2, C1(1, a1), C2(2, FLD(s1240, 0), F_Doc_dsep_dgo(FLD(s1240, 1), a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dsep_dgo(V *a) { (void)a; return F_Doc_dsep_dgo(a[0], a[1]); }
static V S1242(void) { static V c; return STRC(c, "a["); }
static V S1243(void) { static V c; return STRC(c, "]"); }
static V F_Gen_dcaps_dinner(V a0, V a1) {
top:;
V s1241 = a0;
if ((s1241) == IMM(0)) {
return IMM(0);
} else if (TAG(s1241) == 1) {
return C2(1, C2(0, FLD(FLD(s1241, 0), 0), F_String_dappend(S1242(), F_String_dappend(F_U32_dshow(a1), S1243()))), F_Gen_dcaps_dinner(FLD(s1241, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps_dinner(V *a) { (void)a; return F_Gen_dcaps_dinner(a[0], a[1]); }
static V S1245(void) { static V c; return STRC(c, "("); }
static V S1246(void) { static V c; return STRC(c, ") == "); }
static V S1247(void) { static V c; return STRC(c, "nat_subk("); }
static V S1248(void) { static V c; return STRC(c, ", "); }
static V S1249(void) { static V c; return STRC(c, ")"); }
static V S1250(void) { static V c; return STRC(c, "nat_ge("); }
static V S1251(void) { static V c; return STRC(c, ", "); }
static V S1252(void) { static V c; return STRC(c, ")"); }
static V S1253(void) { static V c; return STRC(c, "("); }
static V S1254(void) { static V c; return STRC(c, ") == "); }
static V F_Gen_dpat(V a0, V a1, V a2, V a3) {
top:;
V s1244 = a1;
if (TAG(s1244) == 0) {
return F_Gen_dpat_dvar(FLD(s1244, 0), a2, a3);
} else if (TAG(s1244) == 1) {
return F_Gen_dpat_dctor(a0, F_G_dctor(a0, FLD(s1244, 0)), FLD(s1244, 0), FLD(s1244, 1), a2, a3);
} else if (TAG(s1244) == 2) {
return F_Gen_dpat_dcond(F_String_dappend(S1245(), F_String_dappend(a2, F_String_dappend(S1246(), F_U32_dshow(FLD(s1244, 0))))), a3);
} else if (TAG(s1244) == 3) {
{ V t0 = a0; V t1 = FLD(s1244, 1); V t2 = F_String_dappend(S1247(), F_String_dappend(a2, F_String_dappend(S1248(), F_String_dappend(F_U32_dshow(FLD(s1244, 0)), S1249())))); V t3 = F_Gen_dpat_dcond(F_String_dappend(S1250(), F_String_dappend(a2, F_String_dappend(S1251(), F_String_dappend(F_U32_dshow(FLD(s1244, 0)), S1252())))), a3); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1244) == 4) {
return F_Gen_dpat_dcond(F_String_dappend(S1253(), F_String_dappend(a2, F_String_dappend(S1254(), F_U32_dshow(FLD(s1244, 0))))), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat(V *a) { (void)a; return F_Gen_dpat(a[0], a[1], a[2], a[3]); }
static V F_Gen_dpat_dcond(V a0, V a1) {
top:;
V v1255 = a1;
return C2(0, C2(1, a0, FLD(v1255, 0)), FLD(v1255, 1));
}
static V W_Gen_dpat_dcond(V *a) { (void)a; return F_Gen_dpat_dcond(a[0], a[1]); }
static V S1257(void) { static V c; return STRC(c, "0 /* unknown constructor "); }
static V S1258(void) { static V c; return STRC(c, " */"); }
static V F_Gen_dpat_dctor(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1256 = a1;
if ((s1256) == IMM(0)) {
return F_Gen_dpat_dcond(F_String_dappend(S1257(), F_String_dappend(a2, S1258())), a5);
} else if (TAG(s1256) == 1) {
return F_Gen_dpat_dkind(a0, F_U32_dto__nat(FLD(FLD(s1256, 0), 2)), FLD(FLD(s1256, 0), 0), FLD(FLD(s1256, 0), 3), a3, a4, a5);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dctor(V *a) { (void)a; return F_Gen_dpat_dctor(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1260(void) { static V c; return STRC(c, "TAG("); }
static V S1261(void) { static V c; return STRC(c, ") == "); }
static V S1262(void) { static V c; return STRC(c, "("); }
static V S1263(void) { static V c; return STRC(c, ") == IMM("); }
static V S1264(void) { static V c; return STRC(c, ")"); }
static V S1265(void) { static V c; return STRC(c, "("); }
static V S1266(void) { static V c; return STRC(c, ") == 0"); }
static V S1267(void) { static V c; return STRC(c, "nat_subk("); }
static V S1268(void) { static V c; return STRC(c, ", 1)"); }
static V S1269(void) { static V c; return STRC(c, "("); }
static V S1270(void) { static V c; return STRC(c, ") != 0"); }
static V F_Gen_dpat_dkind(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1259 = a1;
if ((s1259) == 0) {
return F_Gen_dpat_dfields(a0, a4, a5, 0u, F_Gen_dpat_dtag(a3, F_String_dappend(S1260(), F_String_dappend(a5, F_String_dappend(S1261(), F_U32_dshow(a2)))), a6));
} else if ((s1259) == 1) {
return F_Gen_dpat_dtag(a3, F_String_dappend(S1262(), F_String_dappend(a5, F_String_dappend(S1263(), F_String_dappend(F_U32_dshow(a2), S1264())))), a6);
} else if ((s1259) == 2) {
return F_Gen_dpat_dfields(a0, a4, a5, 99u, a6);
} else if ((s1259) == 3) {
return F_Gen_dpat_dcond(F_String_dappend(S1265(), F_String_dappend(a5, S1266())), a6);
} else if (nat_ge(s1259, 4)) {
return F_Gen_dpat_dfields(a0, a4, F_String_dappend(S1267(), F_String_dappend(a5, S1268())), 99u, F_Gen_dpat_dcond(F_String_dappend(S1269(), F_String_dappend(a5, S1270())), a6));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dkind(V *a) { (void)a; return F_Gen_dpat_dkind(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S1272(void) { static V c; return STRC(c, "FLD("); }
static V S1273(void) { static V c; return STRC(c, ", "); }
static V S1274(void) { static V c; return STRC(c, ")"); }
static V F_Gen_dpat_dfields(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1271 = a1;
if ((s1271) == IMM(0)) {
return a4;
} else if (TAG(s1271) == 1) {
{ V t0 = a0; V t1 = FLD(s1271, 1); V t2 = a2; V t3 = F_U32_dinc(a3); V t4 = F_Gen_dpat(a0, FLD(s1271, 0), F_Bool_dpick(F_U32_dis__eq(a3, 99u), a2, F_String_dappend(S1272(), F_String_dappend(a2, F_String_dappend(S1273(), F_String_dappend(F_U32_dshow(a3), S1274()))))), a4); a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dfields(V *a) { (void)a; return F_Gen_dpat_dfields(a[0], a[1], a[2], a[3], a[4]); }
static V F_Gen_dpat_dtag(V a0, V a1, V a2) {
top:;
V s1275 = a0;
if ((s1275) == IMM(1)) {
return a2;
} else if ((s1275) == IMM(0)) {
return F_Gen_dpat_dcond(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dtag(V *a) { (void)a; return F_Gen_dpat_dtag(a[0], a[1], a[2]); }
static V S1277(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dpat_dvar(V a0, V a1, V a2) {
top:;
V v1276 = a2;
return C2(0, FLD(v1276, 0), F_Bool_dpick(F_Str_deq(a0, S1277()), FLD(v1276, 1), C2(1, C2(0, a0, a1), FLD(v1276, 1))));
}
static V W_Gen_dpat_dvar(V *a) { (void)a; return F_Gen_dpat_dvar(a[0], a[1], a[2]); }
static V F_PatR_dbinds(V a0) {
top:;
V v1278 = a0;
return FLD(v1278, 1);
}
static V W_PatR_dbinds(V *a) { (void)a; return F_PatR_dbinds(a[0]); }
static V F_Pat_dvars(V a0, V a1) {
top:;
V s1279 = a0;
if (TAG(s1279) == 0) {
return C2(1, FLD(s1279, 0), a1);
} else if (TAG(s1279) == 1) {
return F_Pats_dvars(FLD(s1279, 1), a1);
} else if (TAG(s1279) == 3) {
{ V t0 = FLD(s1279, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else {
return a1;
}
}
static V W_Pat_dvars(V *a) { (void)a; return F_Pat_dvars(a[0], a[1]); }
static V F_Pats_dvars(V a0, V a1) {
top:;
V s1280 = a0;
if ((s1280) == IMM(0)) {
return a1;
} else if (TAG(s1280) == 1) {
{ V t0 = FLD(s1280, 1); V t1 = F_Pat_dvars(FLD(s1280, 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Pats_dvars(V *a) { (void)a; return F_Pats_dvars(a[0], a[1]); }
static V F_FV_dexpr(V a0, V a1, V a2) {
top:;
V s1281 = a0;
if (TAG(s1281) == 0) {
return F_FV_dvar(FLD(s1281, 0), a1, a2);
} else if (TAG(s1281) == 5) {
return F_FV_dexprs(FLD(s1281, 1), a1, F_FV_dexpr(FLD(s1281, 0), a1, a2));
} else if (TAG(s1281) == 6) {
return F_FV_dexprs(FLD(s1281, 1), a1, a2);
} else if (TAG(s1281) == 7) {
{ V t0 = FLD(s1281, 1); V t1 = F_Pat_dvars(FLD(s1281, 0), a1); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1281) == 8) {
{ V t0 = FLD(s1281, 2); V t1 = F_Pat_dvars(FLD(s1281, 0), a1); V t2 = F_FV_dexpr(FLD(s1281, 1), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1281) == 9) {
return F_FV_dexprs(FLD(s1281, 1), a1, F_FV_dexprs(FLD(s1281, 0), a1, a2));
} else if (TAG(s1281) == 10) {
{ V t0 = FLD(s1281, 1); V t1 = F_Pats_dvars(FLD(s1281, 0), a1); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1281) == 11) {
{ V t0 = FLD(s1281, 1); V t1 = a1; V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1281) == 12) {
{ V t0 = FLD(s1281, 2); V t1 = a1; V t2 = F_FV_dexpr(FLD(s1281, 1), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1281) == 13) {
{ V t0 = FLD(s1281, 0); V t1 = a1; V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else {
return a2;
}
}
static V W_FV_dexpr(V *a) { (void)a; return F_FV_dexpr(a[0], a[1], a[2]); }
static V F_FV_dexprs(V a0, V a1, V a2) {
top:;
V s1282 = a0;
if ((s1282) == IMM(0)) {
return a2;
} else if (TAG(s1282) == 1) {
{ V t0 = FLD(s1282, 1); V t1 = a1; V t2 = F_FV_dexpr(FLD(s1282, 0), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
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
V s1283 = a0;
if ((s1283) == IMM(0)) {
return IMM(0);
} else if (TAG(s1283) == 1) {
return F_Gen_dcaps_dput(FLD(s1283, 0), F_Env_dfind(a1, FLD(s1283, 0)), F_Gen_dcaps(FLD(s1283, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps(V *a) { (void)a; return F_Gen_dcaps(a[0], a[1]); }
static V F_Gen_dcaps_dput(V a0, V a1, V a2) {
top:;
V s1284 = a1;
if ((s1284) == IMM(0)) {
return a2;
} else if (TAG(s1284) == 1) {
return C2(1, C2(0, a0, FLD(s1284, 0)), a2);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps_dput(V *a) { (void)a; return F_Gen_dcaps_dput(a[0], a[1], a[2]); }
static V F_Gen_dctor(V a0, V a1, V a2, V a3) {
top:;
return F_Gen_dctor_dinfo(a0, a1, a2, F_G_dctor(a0, a2), a3);
}
static V W_Gen_dctor(V *a) { (void)a; return F_Gen_dctor(a[0], a[1], a[2], a[3]); }
static V S1286(void) { static V c; return STRC(c, "unknown constructor: "); }
static V S1288(void) { static V c; return STRC(c, "0"); }
static V L1287(V *a) {
return F_Gen_dpure(C1(1, S1288()));
}
static V L1289(V *a) {
return F_Gen_dpure(F_Gen_dctor_dkind(a[1], F_U32_dto__nat(a[0]), a[2]));
}
static V F_Gen_dctor_dinfo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1285 = a3;
if ((s1285) == IMM(0)) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1286(), a2)), mk_clo(L1287, 1, 0, 0));
} else if (TAG(s1285) == 1) {
return F_Gen_dbind(F_Gen_dexprs(a0, a1, a4), mk_clo(L1289, 3, 2, (V[]){FLD(FLD(s1285, 0), 2), FLD(FLD(s1285, 0), 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dctor_dinfo(V *a) { (void)a; return F_Gen_dctor_dinfo(a[0], a[1], a[2], a[3], a[4]); }
static V S1291(void) { static V c; return STRC(c, "IMM("); }
static V S1292(void) { static V c; return STRC(c, ")"); }
static V S1293(void) { static V c; return STRC(c, "0"); }
static V S1294(void) { static V c; return STRC(c, "nat_addk("); }
static V S1295(void) { static V c; return STRC(c, ", 1)"); }
static V F_Gen_dctor_dkind(V a0, V a1, V a2) {
top:;
V s1290 = a1;
if ((s1290) == 0) {
return F_Gen_dctor_dnode(a0, a2);
} else if ((s1290) == 1) {
return C1(1, F_String_dappend(S1291(), F_String_dappend(F_U32_dshow(a0), S1292())));
} else if ((s1290) == 2) {
return F_Doc_dlist(a2);
} else if ((s1290) == 3) {
return C1(1, S1293());
} else if (nat_ge(s1290, 4)) {
return F_Doc_dlist(C2(1, C1(1, S1294()), C2(1, F_Doc_dlist(a2), C2(1, C1(1, S1295()), IMM(0)))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dctor_dkind(V *a) { (void)a; return F_Gen_dctor_dkind(a[0], a[1], a[2]); }
static V S1297(void) { static V c; return STRC(c, "C"); }
static V S1298(void) { static V c; return STRC(c, "("); }
static V S1299(void) { static V c; return STRC(c, ", "); }
static V S1300(void) { static V c; return STRC(c, ")"); }
static V S1301(void) { static V c; return STRC(c, "CN("); }
static V S1302(void) { static V c; return STRC(c, ", "); }
static V S1303(void) { static V c; return STRC(c, ", "); }
static V S1304(void) { static V c; return STRC(c, ")"); }
static V F_Gen_dctor_dnode(V a0, V a1) {
top:;
V v1296 = F_Gen_dlen(a1);
return F_Bool_dpick(F_U32_dis__le(v1296, 4u), F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1297(), F_String_dappend(F_U32_dshow(v1296), F_String_dappend(S1298(), F_String_dappend(F_U32_dshow(a0), S1299()))))), C2(1, F_Gen_dcommas(a1), C2(1, C1(1, S1300()), IMM(0))))), F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1301(), F_String_dappend(F_U32_dshow(a0), F_String_dappend(S1302(), F_String_dappend(F_U32_dshow(v1296), S1303()))))), C2(1, F_Gen_darr(a1), C2(1, C1(1, S1304()), IMM(0))))));
}
static V W_Gen_dctor_dnode(V *a) { (void)a; return F_Gen_dctor_dnode(a[0], a[1]); }
static V F_Gen_dlen(V a0) {
top:;
return F_U32_dfrom__nat(F_List_dlength(a0));
}
static V W_Gen_dlen(V *a) { (void)a; return F_Gen_dlen(a[0]); }
static V L1307(V *a) {
return F_Gen_dpure(C2(1, a[0], a[1]));
}
static V L1306(V *a) {
return F_Gen_dbind(F_Gen_dexprs(a[2], a[1], a[0]), mk_clo(L1307, 2, 1, (V[]){a[3]}));
}
static V F_Gen_dexprs(V a0, V a1, V a2) {
top:;
V s1305 = a2;
if ((s1305) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1305) == 1) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, FLD(s1305, 0)), mk_clo(L1306, 4, 3, (V[]){FLD(s1305, 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dexprs(V *a) { (void)a; return F_Gen_dexprs(a[0], a[1], a[2]); }
static V F_Gen_dcall(V a0, V a1, V a2, V a3) {
top:;
V s1308 = a2;
if (TAG(s1308) == 0) {
return F_Gen_dcall_dvar(a0, a1, FLD(s1308, 0), a3, F_Env_dhas(a1, FLD(s1308, 0)));
} else {
return F_Gen_dcall_dlocal(a0, a1, s1308, a3);
}
}
static V W_Gen_dcall(V *a) { (void)a; return F_Gen_dcall(a[0], a[1], a[2], a[3]); }
static V L1310(V *a) {
return F_Gen_dpure(F_Gen_dapply(a[1], a[0]));
}
static V L1309(V *a) {
return F_Gen_dbind(F_Gen_dexprs(a[2], a[1], a[0]), mk_clo(L1310, 2, 1, (V[]){a[3]}));
}
static V F_Gen_dcall_dlocal(V a0, V a1, V a2, V a3) {
top:;
return F_Gen_dbind(F_Gen_dexpr(a0, a1, a2), mk_clo(L1309, 4, 3, (V[]){a3, a1, a0}));
}
static V W_Gen_dcall_dlocal(V *a) { (void)a; return F_Gen_dcall_dlocal(a[0], a[1], a[2], a[3]); }
static V S1312(void) { static V c; return STRC(c, "apply("); }
static V S1313(void) { static V c; return STRC(c, ", "); }
static V S1314(void) { static V c; return STRC(c, ")"); }
static V F_Gen_dapply(V a0, V a1) {
top:;
V s1311 = a0;
if ((s1311) == IMM(0)) {
return a1;
} else if (TAG(s1311) == 1) {
{ V t0 = FLD(s1311, 1); V t1 = F_Doc_dlist(C2(1, C1(1, S1312()), C2(1, a1, C2(1, C1(1, S1313()), C2(1, FLD(s1311, 0), C2(1, C1(1, S1314()), IMM(0))))))); a0 = t0; a1 = t1; goto top; }
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
V s1315 = a2;
if ((s1315) == IMM(0)) {
return IMM(0);
} else if (TAG(s1315) == 1) {
return IMM(1);
} else { bend_fail("incomplete match"); }
}
static V W_Maybe_dis__some(V *a) { (void)a; return F_Maybe_dis__some(a[2]); }
static V F_Gen_dcall_dvar(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1316 = a4;
if ((s1316) == IMM(1)) {
return F_Gen_dcall_dlocal(a0, a1, C1(0, a2), a3);
} else if ((s1316) == IMM(0)) {
return F_Gen_dcall_ddef(a0, a1, a2, F_G_ddef(a0, a2), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcall_dvar(V *a) { (void)a; return F_Gen_dcall_dvar(a[0], a[1], a[2], a[3], a[4]); }
static V F_Gen_dcall_ddef(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1317 = a3;
return F_Gen_dcall_dkind(a0, a1, a2, F_U32_dto__nat(FLD(v1317, 0)), FLD(v1317, 1), F_Gen_dsplit(FLD(v1317, 1), a4, C4(0, IMM(0), IMM(0), IMM(0), IMM(0))));
}
static V W_Gen_dcall_ddef(V *a) { (void)a; return F_Gen_dcall_ddef(a[0], a[1], a[2], a[3], a[4]); }
static V S1324(void) { static V c; return STRC(c, ""); }
static V F_Gen_dsplit(V a0, V a1, V a2) {
top:;
V s1318 = a0;
V s1319 = a1;
if ((s1318) == IMM(0)) {
V v1320 = a2;
return C4(0, FLD(v1320, 0), FLD(v1320, 1), s1319, IMM(1));
} else if (TAG(s1318) == 1 && (s1319) == IMM(0)) {
V v1321 = a2;
return C4(0, FLD(v1321, 0), FLD(v1321, 1), IMM(0), IMM(0));
} else if (TAG(s1318) == 1 && (FLD(s1318, 0)) == IMM(1) && TAG(s1319) == 1) {
V v1322 = a2;
{ V t0 = FLD(s1318, 1); V t1 = FLD(s1319, 1); V t2 = C4(0, F_List_dappend(FLD(v1322, 0), C2(1, FLD(s1319, 0), IMM(0))), F_List_dappend(FLD(v1322, 1), C2(1, FLD(s1319, 0), IMM(0))), FLD(v1322, 2), FLD(v1322, 3)); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1318) == 1 && (FLD(s1318, 0)) == IMM(0) && TAG(s1319) == 1) {
V v1323 = a2;
{ V t0 = FLD(s1318, 1); V t1 = FLD(s1319, 1); V t2 = C4(0, FLD(v1323, 0), F_List_dappend(FLD(v1323, 1), C2(1, C2(14, S1324(), IMM(0)), IMM(0))), FLD(v1323, 2), FLD(v1323, 3)); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dsplit(V *a) { (void)a; return F_Gen_dsplit(a[0], a[1], a[2]); }
static V S1326(void) { static V c; return STRC(c, "0"); }
static V S1327(void) { static V c; return STRC(c, "unknown function: "); }
static V S1329(void) { static V c; return STRC(c, "0"); }
static V L1328(V *a) {
return F_Gen_dpure(C1(1, S1329()));
}
static V L1330(V *a) {
return F_Gen_dcall_dsplit(a[4], a[3], a[2], a[1], a[0]);
}
static V F_Gen_dcall_dkind(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1325 = a3;
if ((s1325) == 3) {
return F_Gen_dpure(C1(1, S1326()));
} else if ((s1325) == 99) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1327(), a2)), mk_clo(L1328, 1, 0, 0));
} else {
return F_Gen_dbind(F_Gen_dref(a2), mk_clo(L1330, 6, 5, (V[]){a5, a4, a2, a1, a0}));
}
}
static V W_Gen_dcall_dkind(V *a) { (void)a; return F_Gen_dcall_dkind(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Gen_dcall_dsplit(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1331 = a4;
return F_Gen_dcall_dfull(a0, a1, a2, a3, FLD(v1331, 0), FLD(v1331, 1), FLD(v1331, 2), FLD(v1331, 3));
}
static V W_Gen_dcall_dsplit(V *a) { (void)a; return F_Gen_dcall_dsplit(a[0], a[1], a[2], a[3], a[4]); }
static V S1335(void) { static V c; return STRC(c, "("); }
static V S1336(void) { static V c; return STRC(c, ")"); }
static V L1334(V *a) {
return F_Gen_dpure(F_Gen_dapply(a[2], F_Doc_dlist(C2(1, C1(1, F_String_dappend(F_Gen_df(a[1]), S1335())), C2(1, F_Gen_dcommas(a[0]), C2(1, C1(1, S1336()), IMM(0)))))));
}
static V L1333(V *a) {
return F_Gen_dbind(F_Gen_dexprs(a[3], a[2], a[1]), mk_clo(L1334, 3, 2, (V[]){a[4], a[0]}));
}
static V S1338(void) { static V c; return STRC(c, "mk_clo("); }
static V S1339(void) { static V c; return STRC(c, ", "); }
static V S1340(void) { static V c; return STRC(c, ", "); }
static V S1341(void) { static V c; return STRC(c, ", "); }
static V S1342(void) { static V c; return STRC(c, ")"); }
static V L1337(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1338(), F_String_dappend(F_Gen_dw(a[1]), F_String_dappend(S1339(), F_String_dappend(F_U32_dshow(F_U32_dfrom__nat(F_List_dlength(a[0]))), F_String_dappend(S1340(), F_String_dappend(F_U32_dshow(F_Gen_dlen(a[2])), S1341()))))))), C2(1, F_Gen_darr(a[2]), C2(1, C1(1, S1342()), IMM(0))))));
}
static V F_Gen_dcall_dfull(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s1332 = a7;
if ((s1332) == IMM(1)) {
return F_Gen_dbind(F_Gen_dexprs(a0, a1, a4), mk_clo(L1333, 5, 4, (V[]){a2, a6, a1, a0}));
} else if ((s1332) == IMM(0)) {
return F_Gen_dbind(F_Gen_dexprs(a0, a1, a5), mk_clo(L1337, 3, 2, (V[]){a3, a2}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcall_dfull(V *a) { (void)a; return F_Gen_dcall_dfull(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V L1343(V *a) {
return F_Gen_dref_dgo(a[0], a[1]);
}
static V F_Gen_dref(V a0) {
top:;
return mk_clo(L1343, 2, 1, (V[]){a0});
}
static V W_Gen_dref(V *a) { (void)a; return F_Gen_dref(a[0]); }
static V F_Gen_dref_dgo(V a0, V a1) {
top:;
V v1344 = a1;
return C2(0, IMM(0), CN(0, 7, (V[]){FLD(v1344, 0), FLD(v1344, 1), FLD(v1344, 2), C2(1, a0, FLD(v1344, 3)), FLD(v1344, 4), FLD(v1344, 5), FLD(v1344, 6)}));
}
static V W_Gen_dref_dgo(V *a) { (void)a; return F_Gen_dref_dgo(a[0], a[1]); }
static V S1346(void) { static V c; return STRC(c, "S"); }
static V S1348(void) { static V c; return STRC(c, "static V "); }
static V S1349(void) { static V c; return STRC(c, "(void);\012"); }
static V S1351(void) { static V c; return STRC(c, "static V "); }
static V S1352(void) { static V c; return STRC(c, "(void) { static V c; return STRC(c, \042"); }
static V S1353(void) { static V c; return STRC(c, "\042); }\012"); }
static V S1355(void) { static V c; return STRC(c, "()"); }
static V L1354(V *a) {
return F_Gen_dpure(C1(1, F_String_dappend(a[0], S1355())));
}
static V L1350(V *a) {
return F_Gen_dbind(F_Gen_dcode(C1(1, F_String_dappend(S1351(), F_String_dappend(a[1], F_String_dappend(S1352(), F_String_dappend(F_Gen_dlit(a[0]), S1353())))))), mk_clo(L1354, 2, 1, (V[]){a[1]}));
}
static V L1347(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S1348(), F_String_dappend(a[1], S1349())))), mk_clo(L1350, 3, 2, (V[]){a[0], a[1]}));
}
static V L1345(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1346(), F_U32_dshow(a[1]))), mk_clo(L1347, 2, 1, (V[]){a[0]}));
}
static V F_Gen_dstr(V a0) {
top:;
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1345, 2, 1, (V[]){a0}));
}
static V W_Gen_dstr(V *a) { (void)a; return F_Gen_dstr(a[0]); }
static V S1357(void) { static V c; return STRC(c, ""); }
static V F_Gen_dlit(V a0) {
top:;
V s1356 = a0;
if ((s1356) == IMM(0)) {
return S1357();
} else if (TAG(s1356) == 1) {
return F_String_dappend(F_Gen_dlit__chr(FLD(s1356, 0)), F_Gen_dlit(FLD(s1356, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dlit(V *a) { (void)a; return F_Gen_dlit(a[0]); }
static V S1358(void) { static V c; return STRC(c, "\042"); }
static V S1359(void) { static V c; return STRC(c, "\134"); }
static V S1360(void) { static V c; return STRC(c, "\077"); }
static V F_Gen_dlit__chr(V a0) {
top:;
return F_Bool_dpick(F_Bool_dand(F_Bool_dand(F_U32_dis__ge(a0, 32u), F_U32_dis__lt(a0, 127u)), F_Bool_dnot(F_Str_dhas(C2(1, S1358(), C2(1, S1359(), C2(1, S1360(), IMM(0)))), F_Str_dchr(a0)))), F_Str_dchr(a0), F_Gen_dutf8(a0));
}
static V W_Gen_dlit__chr(V *a) { (void)a; return F_Gen_dlit__chr(a[0]); }
static V F_Gen_dutf8(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__lt(a0, 128u), F_Gen_doct(a0), F_Bool_dpick(F_U32_dis__lt(a0, 2048u), F_String_dappend(F_Gen_doct(F_U32_dor(192u, F_U32_dshrn(a0, 6u))), F_Gen_doct(F_U32_dor(128u, F_U32_dand(a0, 63u)))), F_Bool_dpick(F_U32_dis__lt(a0, 65536u), F_String_dappend(F_Gen_doct(F_U32_dor(224u, F_U32_dshrn(a0, 12u))), F_String_dappend(F_Gen_doct(F_U32_dor(128u, F_U32_dand(F_U32_dshrn(a0, 6u), 63u))), F_Gen_doct(F_U32_dor(128u, F_U32_dand(a0, 63u))))), F_String_dappend(F_Gen_doct(F_U32_dor(240u, F_U32_dshrn(a0, 18u))), F_String_dappend(F_Gen_doct(F_U32_dor(128u, F_U32_dand(F_U32_dshrn(a0, 12u), 63u))), F_String_dappend(F_Gen_doct(F_U32_dor(128u, F_U32_dand(F_U32_dshrn(a0, 6u), 63u))), F_Gen_doct(F_U32_dor(128u, F_U32_dand(a0, 63u)))))))));
}
static V W_Gen_dutf8(V *a) { (void)a; return F_Gen_dutf8(a[0]); }
static V W_U32_dor(V *a) { (void)a; return F_U32_dor(a[0], a[1]); }
static V S1361(void) { static V c; return STRC(c, "\134"); }
static V F_Gen_doct(V a0) {
top:;
return F_String_dappend(S1361(), F_String_dappend(F_Str_dchr(F_U32_dadd(48u, F_U32_dand(F_U32_dshrn(a0, 6u), 7u))), F_String_dappend(F_Str_dchr(F_U32_dadd(48u, F_U32_dand(F_U32_dshrn(a0, 3u), 7u))), F_Str_dchr(F_U32_dadd(48u, F_U32_dand(a0, 7u))))));
}
static V W_Gen_doct(V *a) { (void)a; return F_Gen_doct(a[0]); }
static V W_U32_dis__lt(V *a) { (void)a; return F_U32_dis__lt(a[0], a[1]); }
static V F_Gen_dvar(V a0, V a1, V a2) {
top:;
return F_Gen_dvar_dfound(a0, a2, F_Env_dfind(a1, a2));
}
static V W_Gen_dvar(V *a) { (void)a; return F_Gen_dvar(a[0], a[1], a[2]); }
static V S1363(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dvar_dfound(V a0, V a1, V a2) {
top:;
V s1362 = a2;
if (TAG(s1362) == 1) {
return F_Gen_dpure(C1(1, FLD(s1362, 0)));
} else if ((s1362) == IMM(0)) {
return F_Gen_dvar_dglobal(a0, a1, F_Str_deq(a1, S1363()));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dvar_dfound(V *a) { (void)a; return F_Gen_dvar_dfound(a[0], a[1], a[2]); }
static V S1365(void) { static V c; return STRC(c, "0"); }
static V F_Gen_dvar_dglobal(V a0, V a1, V a2) {
top:;
V s1364 = a2;
if ((s1364) == IMM(1)) {
return F_Gen_dpure(C1(1, S1365()));
} else if ((s1364) == IMM(0)) {
return F_Gen_dvar_ddef(a1, F_G_ddef(a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dvar_dglobal(V *a) { (void)a; return F_Gen_dvar_dglobal(a[0], a[1], a[2]); }
static V F_Gen_dvar_ddef(V a0, V a1) {
top:;
V v1366 = a1;
return F_Gen_dvar_dkind(a0, F_U32_dto__nat(FLD(v1366, 0)), F_U32_dfrom__nat(F_List_dlength(FLD(v1366, 1))));
}
static V W_Gen_dvar_ddef(V *a) { (void)a; return F_Gen_dvar_ddef(a[0], a[1]); }
static V S1368(void) { static V c; return STRC(c, "0"); }
static V S1369(void) { static V c; return STRC(c, "unknown name: "); }
static V S1371(void) { static V c; return STRC(c, "0"); }
static V L1370(V *a) {
return F_Gen_dpure(C1(1, S1371()));
}
static V S1373(void) { static V c; return STRC(c, "()"); }
static V S1374(void) { static V c; return STRC(c, "mk_clo("); }
static V S1375(void) { static V c; return STRC(c, ", "); }
static V S1376(void) { static V c; return STRC(c, ", 0, 0)"); }
static V L1372(V *a) {
return F_Gen_dpure(F_Bool_dpick(F_U32_dis__zero(a[1]), C1(1, F_String_dappend(F_Gen_df(a[0]), S1373())), C1(1, F_String_dappend(S1374(), F_String_dappend(F_Gen_dw(a[0]), F_String_dappend(S1375(), F_String_dappend(F_U32_dshow(a[1]), S1376())))))));
}
static V F_Gen_dvar_dkind(V a0, V a1, V a2) {
top:;
V s1367 = a1;
if ((s1367) == 3) {
return F_Gen_dpure(C1(1, S1368()));
} else if ((s1367) == 99) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1369(), a0)), mk_clo(L1370, 1, 0, 0));
} else {
return F_Gen_dbind(F_Gen_dref(a0), mk_clo(L1372, 3, 2, (V[]){a0, a2}));
}
}
static V W_Gen_dvar_dkind(V *a) { (void)a; return F_Gen_dvar_dkind(a[0], a[1], a[2]); }
static V F_Gen_dis__tail(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1377 = a1;
return F_Bool_dand(F_Bool_dand(F_Gen_dis__ret(a2), F_Str_deq(FLD(v1377, 0), a3)), F_Bool_dand(F_Bool_dnot(F_Env_dhas(a0, a3)), F_Nat_dis__eq(F_List_dlength(FLD(v1377, 1)), F_List_dlength(a4))));
}
static V W_Gen_dis__tail(V *a) { (void)a; return F_Gen_dis__tail(a[0], a[1], a[2], a[3], a[4]); }
static V W_Nat_dis__eq(V *a) { (void)a; return F_Nat_dis__eq(a[0], a[1]); }
static V F_Gen_dis__ret(V a0) {
top:;
V s1378 = a0;
if ((s1378) == IMM(0)) {
return IMM(1);
} else if (TAG(s1378) == 1) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dis__ret(V *a) { (void)a; return F_Gen_dis__ret(a[0]); }
static V L1380(V *a) {
return F_Gen_dpure(F_Gen_dret(a[0], a[1]));
}
static V F_Gen_dstmt_dcall(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1379 = a6;
if ((s1379) == IMM(1)) {
return F_Gen_dtail_dself(a0, a1, a2, a5);
} else if ((s1379) == IMM(0)) {
return F_Gen_dbind(F_Gen_dcall(a0, a1, C1(0, a4), a5), mk_clo(L1380, 2, 1, (V[]){a3}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dstmt_dcall(V *a) { (void)a; return F_Gen_dstmt_dcall(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Gen_dtail_dself(V a0, V a1, V a2, V a3) {
top:;
V v1381 = a2;
return F_Gen_dtail(a0, a1, FLD(v1381, 2), F_Gen_dsplit(FLD(v1381, 1), a3, C4(0, IMM(0), IMM(0), IMM(0), IMM(0))));
}
static V W_Gen_dtail_dself(V *a) { (void)a; return F_Gen_dtail_dself(a[0], a[1], a[2], a[3]); }
static V S1384(void) { static V c; return STRC(c, "{ "); }
static V S1385(void) { static V c; return STRC(c, "goto top; }\012"); }
static V L1383(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1384()), C2(1, F_Gen_dtail_dtemps(a[1], 0u), C2(1, F_Gen_dtail_dassign(a[0], 0u), C2(1, C1(1, S1385()), IMM(0)))))));
}
static V F_Gen_dtail(V a0, V a1, V a2, V a3) {
top:;
V v1382 = a3;
return F_Gen_dbind(F_Gen_dexprs(a0, a1, FLD(v1382, 0)), mk_clo(L1383, 2, 1, (V[]){a2}));
}
static V W_Gen_dtail(V *a) { (void)a; return F_Gen_dtail(a[0], a[1], a[2], a[3]); }
static V S1387(void) { static V c; return STRC(c, " = t"); }
static V S1388(void) { static V c; return STRC(c, "; "); }
static V F_Gen_dtail_dassign(V a0, V a1) {
top:;
V s1386 = a0;
if ((s1386) == IMM(0)) {
return IMM(0);
} else if (TAG(s1386) == 1) {
return F_Doc_dlist(C2(1, C1(1, F_String_dappend(FLD(s1386, 0), F_String_dappend(S1387(), F_String_dappend(F_U32_dshow(a1), S1388())))), C2(1, F_Gen_dtail_dassign(FLD(s1386, 1), F_U32_dinc(a1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dtail_dassign(V *a) { (void)a; return F_Gen_dtail_dassign(a[0], a[1]); }
static V S1390(void) { static V c; return STRC(c, "V t"); }
static V S1391(void) { static V c; return STRC(c, " = "); }
static V S1392(void) { static V c; return STRC(c, "; "); }
static V F_Gen_dtail_dtemps(V a0, V a1) {
top:;
V s1389 = a0;
if ((s1389) == IMM(0)) {
return IMM(0);
} else if (TAG(s1389) == 1) {
return F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1390(), F_String_dappend(F_U32_dshow(a1), S1391()))), C2(1, FLD(s1389, 0), C2(1, C1(1, S1392()), C2(1, F_Gen_dtail_dtemps(FLD(s1389, 1), F_U32_dinc(a1)), IMM(0))))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dtail_dtemps(V *a) { (void)a; return F_Gen_dtail_dtemps(a[0], a[1]); }
static V L1393(V *a) {
return F_Gen_dmatch_dgo(a[4], a[3], a[2], a[1], a[0], a[5]);
}
static V F_Gen_dmatch(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Gen_dbind(F_Gen_dscrs(a0, a1, a4), mk_clo(L1393, 6, 5, (V[]){a5, a3, a2, a1, a0}));
}
static V W_Gen_dmatch(V *a) { (void)a; return F_Gen_dmatch(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L1395(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V F_Gen_dmatch_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v1394 = a5;
return F_Gen_dbind(F_Gen_dcases(a0, a1, a2, a3, FLD(v1394, 0), a4), mk_clo(L1395, 2, 1, (V[]){FLD(v1394, 1)}));
}
static V W_Gen_dmatch_dgo(V *a) { (void)a; return F_Gen_dmatch_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1397(void) { static V c; return STRC(c, "{ bend_fail(\042incomplete match\042); }\012"); }
static V L1401(V *a) {
return F_Gen_dcases_dnext(a[6], a[5], a[4], a[3], a[2], a[1], F_List_dreverse(a[0]), a[7]);
}
static V F_Gen_dcases(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1396 = a5;
if ((s1396) == IMM(0)) {
return F_Gen_dpure(C1(1, S1397()));
} else if (TAG(s1396) == 1 && TAG(FLD(s1396, 0)) == 10) {
V v1398 = F_Gen_dpats(a0, FLD(FLD(s1396, 0), 0), a4, C2(0, IMM(0), IMM(0)));
V v1399 = F_PatR_dconds(v1398);
V v1400 = F_PatR_dbinds(v1398);
return F_Gen_dbind(F_Gen_dstmt(a0, F_List_dappend(v1400, a1), a2, a3, FLD(FLD(s1396, 0), 1)), mk_clo(L1401, 8, 7, (V[]){v1399, FLD(s1396, 1), a4, a3, a2, a1, a0}));
} else if (TAG(s1396) == 1) {
{ V t0 = a0; V t1 = a1; V t2 = a2; V t3 = a3; V t4 = a4; V t5 = FLD(s1396, 1); a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; a5 = t5; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcases(V *a) { (void)a; return F_Gen_dcases(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1403(void) { static V c; return STRC(c, "{\012"); }
static V S1404(void) { static V c; return STRC(c, "}\012"); }
static V S1406(void) { static V c; return STRC(c, "if ("); }
static V S1407(void) { static V c; return STRC(c, ") {\012"); }
static V S1408(void) { static V c; return STRC(c, "} else "); }
static V L1405(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1406(), F_String_dappend(F_Gen_dand(C2(1, a[2], a[1])), S1407()))), C2(1, a[0], C2(1, C1(1, S1408()), C2(1, a[3], IMM(0)))))));
}
static V F_Gen_dcases_dnext(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s1402 = a6;
if ((s1402) == IMM(0)) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1403()), C2(1, a7, C2(1, C1(1, S1404()), IMM(0))))));
} else if (TAG(s1402) == 1) {
return F_Gen_dbind(F_Gen_dcases(a0, a1, a2, a3, a4, a5), mk_clo(L1405, 4, 3, (V[]){a7, FLD(s1402, 1), FLD(s1402, 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcases_dnext(V *a) { (void)a; return F_Gen_dcases_dnext(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S1410(void) { static V c; return STRC(c, "1"); }
static V S1411(void) { static V c; return STRC(c, " && "); }
static V F_Gen_dand(V a0) {
top:;
V s1409 = a0;
if ((s1409) == IMM(0)) {
return S1410();
} else if (TAG(s1409) == 1 && (FLD(s1409, 1)) == IMM(0)) {
return FLD(s1409, 0);
} else if (TAG(s1409) == 1) {
return F_String_dappend(FLD(s1409, 0), F_String_dappend(S1411(), F_Gen_dand(FLD(s1409, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dand(V *a) { (void)a; return F_Gen_dand(a[0]); }
static V F_PatR_dconds(V a0) {
top:;
V v1412 = a0;
return FLD(v1412, 0);
}
static V W_PatR_dconds(V *a) { (void)a; return F_PatR_dconds(a[0]); }
static V F_Gen_dpats(V a0, V a1, V a2, V a3) {
top:;
V s1413 = a1;
V s1414 = a2;
if (TAG(s1413) == 1 && TAG(s1414) == 1) {
{ V t0 = a0; V t1 = FLD(s1413, 1); V t2 = FLD(s1414, 1); V t3 = F_Gen_dpat(a0, FLD(s1413, 0), FLD(s1414, 0), a3); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else {
return a3;
}
}
static V W_Gen_dpats(V *a) { (void)a; return F_Gen_dpats(a[0], a[1], a[2], a[3]); }
static V S1417(void) { static V c; return STRC(c, "s"); }
static V L1420(V *a) {
return F_Gen_dpure(F_Gen_dscrs_dput(a[1], a[0], a[2]));
}
static V L1419(V *a) {
return F_Gen_dbind(F_Gen_dscrs(a[3], a[2], a[1]), mk_clo(L1420, 3, 2, (V[]){a[4], a[0]}));
}
static V L1418(V *a) {
return F_Gen_dbind(F_Gen_dexpr(a[3], a[2], a[1]), mk_clo(L1419, 5, 4, (V[]){a[4], a[0], a[2], a[3]}));
}
static V L1416(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1417(), F_U32_dshow(a[4]))), mk_clo(L1418, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Gen_dscrs(V a0, V a1, V a2) {
top:;
V s1415 = a2;
if ((s1415) == IMM(0)) {
return F_Gen_dpure(C2(0, IMM(0), IMM(0)));
} else if (TAG(s1415) == 1) {
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1416, 5, 4, (V[]){FLD(s1415, 1), FLD(s1415, 0), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dscrs(V *a) { (void)a; return F_Gen_dscrs(a[0], a[1], a[2]); }
static V S1422(void) { static V c; return STRC(c, "V "); }
static V S1423(void) { static V c; return STRC(c, " = "); }
static V S1424(void) { static V c; return STRC(c, ";\012"); }
static V F_Gen_dscrs_dput(V a0, V a1, V a2) {
top:;
V v1421 = a2;
return C2(0, C2(1, a0, FLD(v1421, 0)), F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1422(), F_String_dappend(a0, S1423()))), C2(1, a1, C2(1, C1(1, S1424()), C2(1, FLD(v1421, 1), IMM(0)))))));
}
static V W_Gen_dscrs_dput(V *a) { (void)a; return F_Gen_dscrs_dput(a[0], a[1], a[2]); }
static V S1426(void) { static V c; return STRC(c, "_"); }
static V S1427(void) { static V c; return STRC(c, "%par"); }
static V F_Gen_dlet(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1425 = a4;
if (TAG(s1425) == 0) {
return F_Gen_dlet_dvar(a0, a1, a2, a3, FLD(s1425, 0), a5, a6, F_Str_deq(FLD(s1425, 0), S1426()));
} else if (TAG(s1425) == 1) {
return F_Gen_dlet_dctor(a0, a1, a2, a3, FLD(s1425, 0), FLD(s1425, 1), a5, a6, F_Str_deq(FLD(s1425, 0), S1427()));
} else {
return F_Gen_dlet_dpat(a0, a1, a2, a3, s1425, a5, a6);
}
}
static V W_Gen_dlet(V *a) { (void)a; return F_Gen_dlet(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S1429(void) { static V c; return STRC(c, "v"); }
static V S1434(void) { static V c; return STRC(c, "V "); }
static V S1435(void) { static V c; return STRC(c, " = "); }
static V S1436(void) { static V c; return STRC(c, ";\012"); }
static V L1433(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1434(), F_String_dappend(a[1], S1435()))), C2(1, a[0], C2(1, C1(1, S1436()), C2(1, a[2], IMM(0)))))));
}
static V L1432(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[6], F_List_dappend(a[7], a[5]), a[4], a[3], a[2]), mk_clo(L1433, 3, 2, (V[]){a[0], a[1]}));
}
static V L1431(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_PatR_dbinds(F_Gen_dpat(a[6], a[5], a[4], C2(0, IMM(0), IMM(0))))), mk_clo(L1432, 8, 7, (V[]){a[7], a[4], a[0], a[1], a[2], a[3], a[6]}));
}
static V L1430(V *a) {
return F_Gen_dbind(F_Gen_dexpr(a[6], a[5], a[4]), mk_clo(L1431, 8, 7, (V[]){a[0], a[1], a[2], a[5], a[7], a[3], a[6]}));
}
static V L1428(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1429(), F_U32_dshow(a[7]))), mk_clo(L1430, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V F_Gen_dlet_dpat(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1428, 8, 7, (V[]){a6, a3, a2, a4, a5, a1, a0}));
}
static V W_Gen_dlet_dpat(V *a) { (void)a; return F_Gen_dlet_dpat(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Gen_dlet_dctor(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s1437 = a8;
if ((s1437) == IMM(1)) {
return F_Gen_dlet_dpar(a0, a1, a2, a3, a5, a6, a7);
} else if ((s1437) == IMM(0)) {
return F_Gen_dlet_dpat(a0, a1, a2, a3, C2(1, a4, a5), a6, a7);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dlet_dctor(V *a) { (void)a; return F_Gen_dlet_dctor(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Gen_dlet_dpar(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1438 = a5;
if (TAG(s1438) == 6) {
return F_Gen_dpar(a0, a1, a2, a3, a4, FLD(s1438, 1), a6);
} else {
return F_Gen_dpar(a0, a1, a2, a3, a4, C2(1, s1438, IMM(0)), a6);
}
}
static V W_Gen_dlet_dpar(V *a) { (void)a; return F_Gen_dlet_dpar(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V L1441(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V L1440(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[6], F_Gen_dpar_denv(a[5], a[4], 0u, a[3]), a[2], a[1], a[0]), mk_clo(L1441, 2, 1, (V[]){a[7]}));
}
static V L1439(V *a) {
return F_Gen_dbind(F_Gen_dpar_dvals(a[6], a[5], a[7], 0u, a[4]), mk_clo(L1440, 8, 7, (V[]){a[0], a[1], a[2], a[5], a[7], a[3], a[6]}));
}
static V F_Gen_dpar(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1439, 8, 7, (V[]){a6, a3, a2, a4, a5, a1, a0}));
}
static V W_Gen_dpar(V *a) { (void)a; return F_Gen_dpar(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S1443(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dpar_denv(V a0, V a1, V a2, V a3) {
top:;
V s1442 = a0;
if ((s1442) == IMM(0)) {
return a3;
} else if (TAG(s1442) == 1 && TAG(FLD(s1442, 0)) == 0) {
{ V t0 = FLD(s1442, 1); V t1 = a1; V t2 = F_U32_dinc(a2); V t3 = F_Bool_dpick(F_Str_deq(FLD(FLD(s1442, 0), 0), S1443()), a3, C2(1, C2(0, FLD(FLD(s1442, 0), 0), F_Gen_dpar_dname(a1, a2)), a3)); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1442) == 1) {
{ V t0 = FLD(s1442, 1); V t1 = a1; V t2 = F_U32_dinc(a2); V t3 = a3; a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpar_denv(V *a) { (void)a; return F_Gen_dpar_denv(a[0], a[1], a[2], a[3]); }
static V S1444(void) { static V c; return STRC(c, "p"); }
static V S1445(void) { static V c; return STRC(c, "_"); }
static V F_Gen_dpar_dname(V a0, V a1) {
top:;
return F_String_dappend(S1444(), F_String_dappend(F_U32_dshow(a0), F_String_dappend(S1445(), F_U32_dshow(a1))));
}
static V W_Gen_dpar_dname(V *a) { (void)a; return F_Gen_dpar_dname(a[0], a[1]); }
static V S1448(void) { static V c; return STRC(c, "V "); }
static V S1449(void) { static V c; return STRC(c, " = "); }
static V S1450(void) { static V c; return STRC(c, ";\012"); }
static V L1447(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1448(), F_String_dappend(F_Gen_dpar_dname(a[1], a[0]), S1449()))), C2(1, a[2], C2(1, C1(1, S1450()), IMM(0))))));
}
static V S1451(void) { static V c; return STRC(c, "_"); }
static V S1454(void) { static V c; return STRC(c, "V "); }
static V S1455(void) { static V c; return STRC(c, "t = par_fork("); }
static V S1456(void) { static V c; return STRC(c, ");\012"); }
static V S1457(void) { static V c; return STRC(c, "V "); }
static V S1458(void) { static V c; return STRC(c, " = par_join("); }
static V S1459(void) { static V c; return STRC(c, "t);\012"); }
static V L1453(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1454(), F_String_dappend(F_Gen_dpar_dname(a[2], a[1]), S1455()))), C2(1, a[0], C2(1, C1(1, S1456()), C2(1, a[3], C2(1, C1(1, F_String_dappend(S1457(), F_String_dappend(F_Gen_dpar_dname(a[2], a[1]), F_String_dappend(S1458(), F_String_dappend(F_Gen_dpar_dname(a[2], a[1]), S1459()))))), IMM(0))))))));
}
static V L1452(V *a) {
return F_Gen_dbind(F_Gen_dpar_dvals(a[4], a[3], a[2], F_U32_dinc(a[1]), a[0]), mk_clo(L1453, 4, 3, (V[]){a[5], a[1], a[2]}));
}
static V F_Gen_dpar_dvals(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1446 = a4;
if ((s1446) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1446) == 1 && (FLD(s1446, 1)) == IMM(0)) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, FLD(s1446, 0)), mk_clo(L1447, 3, 2, (V[]){a3, a2}));
} else if (TAG(s1446) == 1) {
return F_Gen_dbind(F_Gen_dlam(a0, a1, C1(0, S1451()), FLD(s1446, 0)), mk_clo(L1452, 6, 5, (V[]){FLD(s1446, 1), a3, a2, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpar_dvals(V *a) { (void)a; return F_Gen_dpar_dvals(a[0], a[1], a[2], a[3], a[4]); }
static V S1463(void) { static V c; return STRC(c, "(void)("); }
static V S1464(void) { static V c; return STRC(c, ");\012"); }
static V L1462(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1463()), C2(1, a[0], C2(1, C1(1, S1464()), C2(1, a[1], IMM(0)))))));
}
static V L1461(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[4], a[3], a[2], a[1], a[0]), mk_clo(L1462, 2, 1, (V[]){a[5]}));
}
static V S1466(void) { static V c; return STRC(c, "v"); }
static V S1470(void) { static V c; return STRC(c, "V "); }
static V S1471(void) { static V c; return STRC(c, " = "); }
static V S1472(void) { static V c; return STRC(c, ";\012"); }
static V L1469(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1470(), F_String_dappend(a[1], S1471()))), C2(1, a[0], C2(1, C1(1, S1472()), C2(1, a[2], IMM(0)))))));
}
static V L1468(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[6], C2(1, C2(0, a[5], a[4]), a[3]), a[2], a[1], a[0]), mk_clo(L1469, 3, 2, (V[]){a[7], a[4]}));
}
static V L1467(V *a) {
return F_Gen_dbind(F_Gen_dexpr(a[6], a[5], a[4]), mk_clo(L1468, 8, 7, (V[]){a[0], a[1], a[2], a[5], a[7], a[3], a[6]}));
}
static V L1465(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1466(), F_U32_dshow(a[7]))), mk_clo(L1467, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V F_Gen_dlet_dvar(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s1460 = a7;
if ((s1460) == IMM(1)) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, a5), mk_clo(L1461, 6, 5, (V[]){a6, a3, a2, a1, a0}));
} else if ((s1460) == IMM(0)) {
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1465, 8, 7, (V[]){a6, a3, a2, a4, a5, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dlet_dvar(V *a) { (void)a; return F_Gen_dlet_dvar(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S1474(void) { static V c; return STRC(c, ""); }
static V S1475(void) { static V c; return STRC(c, "#define "); }
static V S1476(void) { static V c; return STRC(c, " ((3u << 16) | "); }
static V S1477(void) { static V c; return STRC(c, "u)\012"); }
static V F_Gen_dcids(V a0, V a1, V a2) {
top:;
V s1473 = a1;
if ((s1473) == IMM(0)) {
return S1474();
} else if (TAG(s1473) == 1 && TAG(FLD(s1473, 0)) == 3) {
return F_String_dappend(F_Gen_dcids_dctors(a0, FLD(FLD(s1473, 0), 2)), F_Gen_dcids(a0, FLD(s1473, 1), a2));
} else if (TAG(s1473) == 1 && TAG(FLD(s1473, 0)) == 1) {
return F_String_dappend(S1475(), F_String_dappend(F_Gen_dcid(FLD(FLD(s1473, 0), 0)), F_String_dappend(S1476(), F_String_dappend(F_U32_dshow(a2), F_String_dappend(S1477(), F_Gen_dcids(a0, FLD(s1473, 1), F_U32_dinc(a2)))))));
} else if (TAG(s1473) == 1) {
{ V t0 = a0; V t1 = FLD(s1473, 1); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcids(V *a) { (void)a; return F_Gen_dcids(a[0], a[1], a[2]); }
static V S1479(void) { static V c; return STRC(c, ""); }
static V F_Gen_dcids_dctors(V a0, V a1) {
top:;
V s1478 = a1;
if ((s1478) == IMM(0)) {
return S1479();
} else if (TAG(s1478) == 1) {
return F_String_dappend(F_Gen_dcids_dkind(FLD(FLD(s1478, 0), 0), F_G_dctor(a0, FLD(FLD(s1478, 0), 0))), F_Gen_dcids_dctors(a0, FLD(s1478, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcids_dctors(V *a) { (void)a; return F_Gen_dcids_dctors(a[0], a[1]); }
static V S1481(void) { static V c; return STRC(c, ""); }
static V F_Gen_dcids_dkind(V a0, V a1) {
top:;
V s1480 = a1;
if ((s1480) == IMM(0)) {
return S1481();
} else if (TAG(s1480) == 1) {
return F_Gen_dcids_dline(a0, F_U32_dto__nat(FLD(FLD(s1480, 0), 2)), FLD(FLD(s1480, 0), 0));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcids_dkind(V *a) { (void)a; return F_Gen_dcids_dkind(a[0], a[1]); }
static V S1483(void) { static V c; return STRC(c, "#define "); }
static V S1484(void) { static V c; return STRC(c, " "); }
static V S1485(void) { static V c; return STRC(c, "u\012"); }
static V S1486(void) { static V c; return STRC(c, "#define "); }
static V S1487(void) { static V c; return STRC(c, " ((1u << 16) | "); }
static V S1488(void) { static V c; return STRC(c, "u)\012"); }
static V S1489(void) { static V c; return STRC(c, "#define "); }
static V S1490(void) { static V c; return STRC(c, " ((2u << 16) | "); }
static V S1491(void) { static V c; return STRC(c, "u)\012"); }
static V S1492(void) { static V c; return STRC(c, ""); }
static V F_Gen_dcids_dline(V a0, V a1, V a2) {
top:;
V s1482 = a1;
if ((s1482) == 0) {
return F_String_dappend(S1483(), F_String_dappend(F_Gen_dcid(a0), F_String_dappend(S1484(), F_String_dappend(F_U32_dshow(a2), S1485()))));
} else if ((s1482) == 1) {
return F_String_dappend(S1486(), F_String_dappend(F_Gen_dcid(a0), F_String_dappend(S1487(), F_String_dappend(F_U32_dshow(a2), S1488()))));
} else if ((s1482) == 2) {
return F_String_dappend(S1489(), F_String_dappend(F_Gen_dcid(a0), F_String_dappend(S1490(), F_String_dappend(F_U32_dshow(a2), S1491()))));
} else {
return S1492();
}
}
static V W_Gen_dcids_dline(V *a) { (void)a; return F_Gen_dcids_dline(a[0], a[1], a[2]); }
static V S1495(void) { static V c; return STRC(c, "#include \042bendrt.h\042\012\012"); }
static V S1496(void) { static V c; return STRC(c, "\012"); }
static V S1497(void) { static V c; return STRC(c, "\012"); }
static V F_Gen_dprogram_dfin(V a0, V a1) {
top:;
V v1493 = a1;
V v1494 = FLD(v1493, 1);
return C4(0, F_String_dappend(a0, S1495()), F_Gen_ddedup(F_List_dreverse(FLD(v1494, 6)), IMM(0)), F_Doc_dflat(F_Doc_dlist(C2(1, FLD(v1494, 1), C2(1, C1(1, S1496()), C2(1, FLD(v1494, 2), C2(1, C1(1, F_String_dappend(S1497(), FLD(v1493, 0))), IMM(0))))))), FLD(v1494, 4));
}
static V W_Gen_dprogram_dfin(V *a) { (void)a; return F_Gen_dprogram_dfin(a[0], a[1]); }
static V F_Doc_dflat(V a0) {
top:;
return F_Doc_dgo(a0, IMM(0));
}
static V W_Doc_dflat(V *a) { (void)a; return F_Doc_dflat(a[0]); }
static V F_Doc_dgo(V a0, V a1) {
top:;
V s1498 = a0;
if ((s1498) == IMM(0)) {
return a1;
} else if (TAG(s1498) == 1) {
return F_String_dappend(FLD(s1498, 0), a1);
} else if (TAG(s1498) == 2) {
{ V t0 = FLD(s1498, 0); V t1 = F_Doc_dgo(FLD(s1498, 1), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dgo(V *a) { (void)a; return F_Doc_dgo(a[0], a[1]); }
static V F_Gen_ddedup(V a0, V a1) {
top:;
V s1499 = a0;
if ((s1499) == IMM(0)) {
return F_List_dreverse(a1);
} else if (TAG(s1499) == 1) {
{ V t0 = FLD(s1499, 1); V t1 = F_Bool_dpick(F_Str_dhas(a1, FLD(s1499, 0)), a1, C2(1, FLD(s1499, 0), a1)); a0 = t0; a1 = t1; goto top; }
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
V s1500 = a0;
if ((s1500) == IMM(0)) {
return a1;
} else if (TAG(s1500) == 1 && TAG(FLD(s1500, 0)) == 2) {
{ V t0 = FLD(s1500, 1); V t1 = F_Map_dset(a1, FLD(FLD(s1500, 0), 0), FLD(FLD(s1500, 0), 1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1500) == 1) {
{ V t0 = FLD(s1500, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_G_dlaws(V *a) { (void)a; return F_G_dlaws(a[0], a[1]); }
static V F_G_dbuild(V a0, V a1, V a2) {
top:;
V s1501 = a0;
if ((s1501) == IMM(0)) {
return a2;
} else if (TAG(s1501) == 1) {
{ V t0 = FLD(s1501, 1); V t1 = a1; V t2 = F_G_dadd(FLD(s1501, 0), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_G_dbuild(V *a) { (void)a; return F_G_dbuild(a[0], a[1], a[2]); }
static V F_G_dadd(V a0, V a1, V a2) {
top:;
V s1502 = a0;
if (TAG(s1502) == 3) {
return F_G_dadd_dtype(FLD(s1502, 0), FLD(s1502, 1), FLD(s1502, 2), a2);
} else if (TAG(s1502) == 2) {
return F_G_dadd_dlaw(FLD(s1502, 0), FLD(s1502, 1), a2);
} else if (TAG(s1502) == 0) {
return F_G_dadd_ddef(FLD(s1502, 0), FLD(s1502, 1), FLD(s1502, 2), FLD(s1502, 3), a1, a2);
} else if (TAG(s1502) == 1) {
return F_G_dadd_deff(FLD(s1502, 0), FLD(s1502, 1), FLD(s1502, 2), a2);
} else if (TAG(s1502) == 4) {
return a2;
} else { bend_fail("incomplete match"); }
}
static V W_G_dadd(V *a) { (void)a; return F_G_dadd(a[0], a[1], a[2]); }
static V F_G_dadd_deff(V a0, V a1, V a2, V a3) {
top:;
V v1503 = a3;
return C3(0, FLD(v1503, 0), F_Map_dset(FLD(v1503, 1), a0, C2(0, 1u, F_G_dmask(a1))), F_Map_dset(FLD(v1503, 2), a0, C3(1, a0, a1, a2)));
}
static V W_G_dadd_deff(V *a) { (void)a; return F_G_dadd_deff(a[0], a[1], a[2], a[3]); }
static V F_G_dmask(V a0) {
top:;
V s1504 = a0;
if ((s1504) == IMM(0)) {
return IMM(0);
} else if (TAG(s1504) == 1) {
return C2(1, F_G_dkeep(FLD(s1504, 0)), F_G_dmask(FLD(s1504, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_G_dmask(V *a) { (void)a; return F_G_dmask(a[0]); }
static V F_G_dkeep(V a0) {
top:;
V v1505 = a0;
return F_Bool_dnot(F_Bool_dor(F_Bool_dor(F_U32_dis__eq(FLD(v1505, 1), 1u), F_U32_dis__eq(FLD(v1505, 1), 4u)), F_G_derased__ty(FLD(v1505, 2))));
}
static V W_G_dkeep(V *a) { (void)a; return F_G_dkeep(a[0]); }
static V S1506(void) { static V c; return STRC(c, "Type"); }
static V S1507(void) { static V c; return STRC(c, "Data"); }
static V S1508(void) { static V c; return STRC(c, "Quant"); }
static V S1509(void) { static V c; return STRC(c, "Kind"); }
static V F_G_derased__ty(V a0) {
top:;
return F_Str_dhas(C2(1, S1506(), C2(1, S1507(), C2(1, S1508(), C2(1, S1509(), IMM(0))))), a0);
}
static V W_G_derased__ty(V *a) { (void)a; return F_G_derased__ty(a[0]); }
static V F_G_dadd_ddef(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v1510 = a5;
return C3(0, FLD(v1510, 0), F_Map_dset(FLD(v1510, 1), a0, C2(0, F_Bool_dpick(F_G_dis__native(a0), 2u, 0u), F_G_dmask(F_G_dparams(a4, a0, a1)))), F_Map_dset(FLD(v1510, 2), a0, C4(0, a0, a1, a2, a3)));
}
static V W_G_dadd_ddef(V *a) { (void)a; return F_G_dadd_ddef(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_G_dparams(V a0, V a1, V a2) {
top:;
return F_G_dparams_dgo(F_G_dget(IMM(0), a0, a1), a2);
}
static V W_G_dparams(V *a) { (void)a; return F_G_dparams(a[0], a[1], a[2]); }
static V F_G_dparams_dgo(V a0, V a1) {
top:;
V s1511 = a0;
if ((s1511) == IMM(0)) {
return a1;
} else if (TAG(s1511) == 1) {
return C2(1, FLD(s1511, 0), FLD(s1511, 1));
} else { bend_fail("incomplete match"); }
}
static V W_G_dparams_dgo(V *a) { (void)a; return F_G_dparams_dgo(a[0], a[1]); }
static V F_G_dis__native(V a0) {
top:;
return F_Str_dhas(F_Natives(), a0);
}
static V W_G_dis__native(V *a) { (void)a; return F_G_dis__native(a[0]); }
static V S1512(void) { static V c; return STRC(c, "U32.inc"); }
static V S1513(void) { static V c; return STRC(c, "U32.add"); }
static V S1514(void) { static V c; return STRC(c, "U32.sub"); }
static V S1515(void) { static V c; return STRC(c, "U32.mul"); }
static V S1516(void) { static V c; return STRC(c, "U32.div"); }
static V S1517(void) { static V c; return STRC(c, "U32.mod"); }
static V S1518(void) { static V c; return STRC(c, "U32.not"); }
static V S1519(void) { static V c; return STRC(c, "U32.and"); }
static V S1520(void) { static V c; return STRC(c, "U32.or"); }
static V S1521(void) { static V c; return STRC(c, "U32.xor"); }
static V S1522(void) { static V c; return STRC(c, "U32.shl"); }
static V S1523(void) { static V c; return STRC(c, "U32.shr"); }
static V S1524(void) { static V c; return STRC(c, "U32.shln"); }
static V S1525(void) { static V c; return STRC(c, "U32.shrn"); }
static V S1526(void) { static V c; return STRC(c, "U32.cmp"); }
static V S1527(void) { static V c; return STRC(c, "U32.is_eq"); }
static V S1528(void) { static V c; return STRC(c, "U32.is_ne"); }
static V S1529(void) { static V c; return STRC(c, "U32.is_lt"); }
static V S1530(void) { static V c; return STRC(c, "U32.is_le"); }
static V S1531(void) { static V c; return STRC(c, "U32.is_gt"); }
static V S1532(void) { static V c; return STRC(c, "U32.is_ge"); }
static V S1533(void) { static V c; return STRC(c, "U32.is_zero"); }
static V S1534(void) { static V c; return STRC(c, "U32.is_even"); }
static V S1535(void) { static V c; return STRC(c, "U32.to_nat"); }
static V S1536(void) { static V c; return STRC(c, "U32.from_nat"); }
static V S1537(void) { static V c; return STRC(c, "U32.min"); }
static V S1538(void) { static V c; return STRC(c, "U32.max"); }
static V S1539(void) { static V c; return STRC(c, "U32.pow"); }
static V S1540(void) { static V c; return STRC(c, "U32.log2"); }
static V S1541(void) { static V c; return STRC(c, "U32.to_f32"); }
static V S1542(void) { static V c; return STRC(c, "Nat.double"); }
static V S1543(void) { static V c; return STRC(c, "Nat.add"); }
static V S1544(void) { static V c; return STRC(c, "Nat.sub"); }
static V S1545(void) { static V c; return STRC(c, "Nat.mul"); }
static V S1546(void) { static V c; return STRC(c, "Nat.divmod"); }
static V S1547(void) { static V c; return STRC(c, "Nat.div"); }
static V S1548(void) { static V c; return STRC(c, "Nat.mod"); }
static V S1549(void) { static V c; return STRC(c, "Nat.cmp"); }
static V S1550(void) { static V c; return STRC(c, "Nat.is_eq"); }
static V S1551(void) { static V c; return STRC(c, "Nat.is_ne"); }
static V S1552(void) { static V c; return STRC(c, "Nat.is_lt"); }
static V S1553(void) { static V c; return STRC(c, "Nat.is_le"); }
static V S1554(void) { static V c; return STRC(c, "Nat.is_gt"); }
static V S1555(void) { static V c; return STRC(c, "Nat.is_ge"); }
static V S1556(void) { static V c; return STRC(c, "Nat.min"); }
static V S1557(void) { static V c; return STRC(c, "Nat.max"); }
static V S1558(void) { static V c; return STRC(c, "Nat.pow"); }
static V S1559(void) { static V c; return STRC(c, "Nat.show"); }
static V S1560(void) { static V c; return STRC(c, "F32.add"); }
static V S1561(void) { static V c; return STRC(c, "F32.sub"); }
static V S1562(void) { static V c; return STRC(c, "F32.mul"); }
static V S1563(void) { static V c; return STRC(c, "F32.div"); }
static V S1564(void) { static V c; return STRC(c, "F32.mod"); }
static V S1565(void) { static V c; return STRC(c, "F32.pow"); }
static V S1566(void) { static V c; return STRC(c, "F32.atan2"); }
static V S1567(void) { static V c; return STRC(c, "F32.is_eq"); }
static V S1568(void) { static V c; return STRC(c, "F32.is_ne"); }
static V S1569(void) { static V c; return STRC(c, "F32.is_lt"); }
static V S1570(void) { static V c; return STRC(c, "F32.is_le"); }
static V S1571(void) { static V c; return STRC(c, "F32.is_gt"); }
static V S1572(void) { static V c; return STRC(c, "F32.is_ge"); }
static V S1573(void) { static V c; return STRC(c, "F32.neg"); }
static V S1574(void) { static V c; return STRC(c, "F32.abs"); }
static V S1575(void) { static V c; return STRC(c, "F32.sqrt"); }
static V S1576(void) { static V c; return STRC(c, "F32.exp"); }
static V S1577(void) { static V c; return STRC(c, "F32.log"); }
static V S1578(void) { static V c; return STRC(c, "F32.log2"); }
static V S1579(void) { static V c; return STRC(c, "F32.log10"); }
static V S1580(void) { static V c; return STRC(c, "F32.sin"); }
static V S1581(void) { static V c; return STRC(c, "F32.cos"); }
static V S1582(void) { static V c; return STRC(c, "F32.tan"); }
static V S1583(void) { static V c; return STRC(c, "F32.asin"); }
static V S1584(void) { static V c; return STRC(c, "F32.acos"); }
static V S1585(void) { static V c; return STRC(c, "F32.atan"); }
static V S1586(void) { static V c; return STRC(c, "F32.sinh"); }
static V S1587(void) { static V c; return STRC(c, "F32.cosh"); }
static V S1588(void) { static V c; return STRC(c, "F32.tanh"); }
static V S1589(void) { static V c; return STRC(c, "F32.floor"); }
static V S1590(void) { static V c; return STRC(c, "F32.ceil"); }
static V S1591(void) { static V c; return STRC(c, "F32.trunc"); }
static V S1592(void) { static V c; return STRC(c, "F32.bits"); }
static V S1593(void) { static V c; return STRC(c, "F32.to_u32"); }
static V S1594(void) { static V c; return STRC(c, "F32.show"); }
static V S1595(void) { static V c; return STRC(c, "F32.read"); }
static V F_Natives(void) {
top:;
return C2(1, S1512(), C2(1, S1513(), C2(1, S1514(), C2(1, S1515(), C2(1, S1516(), C2(1, S1517(), C2(1, S1518(), C2(1, S1519(), C2(1, S1520(), C2(1, S1521(), C2(1, S1522(), C2(1, S1523(), C2(1, S1524(), C2(1, S1525(), C2(1, S1526(), C2(1, S1527(), C2(1, S1528(), C2(1, S1529(), C2(1, S1530(), C2(1, S1531(), C2(1, S1532(), C2(1, S1533(), C2(1, S1534(), C2(1, S1535(), C2(1, S1536(), C2(1, S1537(), C2(1, S1538(), C2(1, S1539(), C2(1, S1540(), C2(1, S1541(), C2(1, S1542(), C2(1, S1543(), C2(1, S1544(), C2(1, S1545(), C2(1, S1546(), C2(1, S1547(), C2(1, S1548(), C2(1, S1549(), C2(1, S1550(), C2(1, S1551(), C2(1, S1552(), C2(1, S1553(), C2(1, S1554(), C2(1, S1555(), C2(1, S1556(), C2(1, S1557(), C2(1, S1558(), C2(1, S1559(), C2(1, S1560(), C2(1, S1561(), C2(1, S1562(), C2(1, S1563(), C2(1, S1564(), C2(1, S1565(), C2(1, S1566(), C2(1, S1567(), C2(1, S1568(), C2(1, S1569(), C2(1, S1570(), C2(1, S1571(), C2(1, S1572(), C2(1, S1573(), C2(1, S1574(), C2(1, S1575(), C2(1, S1576(), C2(1, S1577(), C2(1, S1578(), C2(1, S1579(), C2(1, S1580(), C2(1, S1581(), C2(1, S1582(), C2(1, S1583(), C2(1, S1584(), C2(1, S1585(), C2(1, S1586(), C2(1, S1587(), C2(1, S1588(), C2(1, S1589(), C2(1, S1590(), C2(1, S1591(), C2(1, S1592(), C2(1, S1593(), C2(1, S1594(), C2(1, S1595(), IMM(0)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
}
static V W_Natives(V *a) { (void)a; return F_Natives(); }
static V F_G_dadd_dlaw(V a0, V a1, V a2) {
top:;
V v1596 = a2;
return C3(0, FLD(v1596, 0), F_Map_dset(FLD(v1596, 1), a0, C2(0, F_Bool_dpick(F_G_dis__native(a0), 2u, 3u), F_G_dmask(a1))), FLD(v1596, 2));
}
static V W_G_dadd_dlaw(V *a) { (void)a; return F_G_dadd_dlaw(a[0], a[1], a[2]); }
static V S1599(void) { static V c; return STRC(c, "%"); }
static V F_G_dadd_dtype(V a0, V a1, V a2, V a3) {
top:;
V v1597 = a3;
V v1598 = F_U32_dfrom__nat(F_List_dlength(a2));
return C3(0, F_G_dctors(a0, a2, 0u, v1598, FLD(v1597, 0)), F_Map_dset(FLD(v1597, 1), a0, C2(0, 3u, IMM(0))), F_Map_dset(FLD(v1597, 2), F_String_dappend(S1599(), a0), C3(3, a0, a1, a2)));
}
static V W_G_dadd_dtype(V *a) { (void)a; return F_G_dadd_dtype(a[0], a[1], a[2], a[3]); }
static V F_G_dctors(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1600 = a1;
if ((s1600) == IMM(0)) {
return a4;
} else if (TAG(s1600) == 1) {
V v1601 = F_U32_dfrom__nat(F_List_dlength(FLD(FLD(s1600, 0), 1)));
{ V t0 = a0; V t1 = FLD(s1600, 1); V t2 = F_U32_dinc(a2); V t3 = a3; V t4 = F_Map_dset(a4, FLD(FLD(s1600, 0), 0), C4(0, a2, v1601, F_G_dctor__kind(a0, FLD(FLD(s1600, 0), 0), a3, v1601), F_U32_dis__eq(a3, 1u))); a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_G_dctors(V *a) { (void)a; return F_G_dctors(a[0], a[1], a[2], a[3], a[4]); }
static V S1602(void) { static V c; return STRC(c, "Nat"); }
static V S1603(void) { static V c; return STRC(c, "Zero"); }
static V F_G_dctor__kind(V a0, V a1, V a2, V a3) {
top:;
return F_Bool_dpick(F_Str_deq(a0, S1602()), F_Bool_dpick(F_Str_deq(a1, S1603()), 3u, 4u), F_Bool_dpick(F_Bool_dand(F_U32_dis__eq(a2, 1u), F_U32_dis__eq(a3, 1u)), 2u, F_Bool_dpick(F_U32_dis__zero(a3), 1u, 0u)));
}
static V W_G_dctor__kind(V *a) { (void)a; return F_G_dctor__kind(a[0], a[1], a[2], a[3]); }
static V S1606(void) { static V c; return STRC(c, "\012"); }
static V S1608(void) { static V c; return STRC(c, "bendc: compilation failed"); }
static V L1607(V *a) {
return F_IO_ddie(1u, S1608());
}
static V F_Main_demit(V a0) {
top:;
V v1604 = a0;
V s1605 = FLD(v1604, 3);
if ((s1605) == IMM(0)) {
return F_Main_demit_dok(FLD(v1604, 0), FLD(v1604, 1), FLD(v1604, 2));
} else if (TAG(s1605) == 1) {
return F_IO_dbind(F_IO_dprint__err(F_String_djoin(F_List_dreverse(C2(1, FLD(s1605, 0), FLD(s1605, 1))), S1606())), mk_clo(L1607, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Main_demit(V *a) { (void)a; return F_Main_demit(a[0]); }
static V E_IO_dprint__err(V *a) { return io_req(CID_IO_PRINT_ERR, 2, (V[]){a[0], a[2]}); }
static V F_IO_dprint__err(V a0) { return mk_clo(E_IO_dprint__err, 3, 1, (V[]){a0}); }
static V W_IO_dprint__err(V *a) { (void)a; return F_IO_dprint__err(a[0]); }
static V L1611(V *a) {
return apply(apply(apply(a[2], a[3]), a[1]), a[0]);
}
static V L1610(V *a) {
return apply(apply(a[2], a[1]), mk_clo(L1611, 4, 3, (V[]){a[3], a[1], a[0]}));
}
static V L1609(V *a) {
return mk_clo(L1610, 4, 3, (V[]){a[0], a[2], a[1]});
}
static V F_IO_dbind(V a2, V a3) {
top:;
return mk_clo(L1609, 3, 2, (V[]){a3, a2});
}
static V W_IO_dbind(V *a) { (void)a; return F_IO_dbind(a[2], a[3]); }
static V S1612(void) { static V c; return STRC(c, ""); }
static V L1613(V *a) {
return F_IO_dwrite(F_String_dappend(a[1], F_String_dappend(a[2], a[0])));
}
static V F_Main_demit_dok(V a0, V a1, V a2) {
top:;
return F_IO_dbind(F_Main_deffs(a1, S1612()), mk_clo(L1613, 3, 2, (V[]){a2, a0}));
}
static V W_Main_demit_dok(V *a) { (void)a; return F_Main_demit_dok(a[0], a[1], a[2]); }
static V E_IO_dwrite(V *a) { return io_req(CID_IO_WRITE, 2, (V[]){a[0], a[2]}); }
static V F_IO_dwrite(V a0) { return mk_clo(E_IO_dwrite, 3, 1, (V[]){a0}); }
static V W_IO_dwrite(V *a) { (void)a; return F_IO_dwrite(a[0]); }
static V S1616(void) { static V c; return STRC(c, "\012"); }
static V L1615(V *a) {
return F_Main_deffs(a[1], F_String_dappend(a[0], F_String_dappend(a[2], S1616())));
}
static V F_Main_deffs(V a0, V a1) {
top:;
V s1614 = a0;
if ((s1614) == IMM(0)) {
return F_IO_dpure(a1);
} else if (TAG(s1614) == 1) {
return F_IO_dbind(F_IO_dread__file(FLD(s1614, 0)), mk_clo(L1615, 3, 2, (V[]){a1, FLD(s1614, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_deffs(V *a) { (void)a; return F_Main_deffs(a[0], a[1]); }
static V S1617(void) { static V c; return STRC(c, "r"); }
static V L1619(V *a) {
return F_IO_dread__fin(a[0]);
}
static V L1618(V *a) {
return F_IO_dbind(F_File_dread(a[0], 2000000000u), mk_clo(L1619, 1, 0, 0));
}
static V F_IO_dread__file(V a0) {
top:;
return F_IO_dbind(F_IO_dtry(F_File_dopen(a0, S1617())), mk_clo(L1618, 1, 0, 0));
}
static V W_IO_dread__file(V *a) { (void)a; return F_IO_dread__file(a[0]); }
static V L1621(V *a) {
return F_IO_dpass(a[0]);
}
static V F_IO_dread__fin(V a0) {
top:;
V v1620 = a0;
return F_IO_dbind(F_File_dclose(FLD(v1620, 0)), mk_clo(L1621, 2, 1, (V[]){FLD(v1620, 1)}));
}
static V W_IO_dread__fin(V *a) { (void)a; return F_IO_dread__fin(a[0]); }
static V F_IO_dpass(V a1) {
top:;
V s1622 = a1;
if (TAG(s1622) == 1) {
return F_IO_dpure(FLD(s1622, 0));
} else if (TAG(s1622) == 0) {
return F_IO_ddie(FLD(FLD(s1622, 0), 0), FLD(FLD(s1622, 0), 1));
} else { bend_fail("incomplete match"); }
}
static V W_IO_dpass(V *a) { (void)a; return F_IO_dpass(a[1]); }
static V L1624(V *a) {
return apply(a[1], a[0]);
}
static V L1623(V *a) {
return mk_clo(L1624, 2, 1, (V[]){a[0]});
}
static V F_IO_dpure(V a1) {
top:;
return mk_clo(L1623, 2, 1, (V[]){a1});
}
static V W_IO_dpure(V *a) { (void)a; return F_IO_dpure(a[1]); }
static V E_File_dclose(V *a) { return io_req(CID_FILE_CLOSE, 2, (V[]){a[0], a[2]}); }
static V F_File_dclose(V a0) { return mk_clo(E_File_dclose, 3, 1, (V[]){a0}); }
static V W_File_dclose(V *a) { (void)a; return F_File_dclose(a[0]); }
static V E_File_dread(V *a) { return io_req(CID_FILE_READ, 3, (V[]){a[0], a[1], a[3]}); }
static V F_File_dread(V a0, V a1) { return mk_clo(E_File_dread, 4, 2, (V[]){a0, a1}); }
static V W_File_dread(V *a) { (void)a; return F_File_dread(a[0], a[1]); }
static V E_File_dopen(V *a) { return io_req(CID_FILE_OPEN, 3, (V[]){a[0], a[1], a[3]}); }
static V F_File_dopen(V a0, V a1) { return mk_clo(E_File_dopen, 4, 2, (V[]){a0, a1}); }
static V W_File_dopen(V *a) { (void)a; return F_File_dopen(a[0], a[1]); }
static V F_IO_dtry(V a1) {
top:;
return F_IO_dbind(a1, mk_clo(W_IO_dpass, 2, 1, (V[]){0}));
}
static V W_IO_dtry(V *a) { (void)a; return F_IO_dtry(a[1]); }
static V S1626(void) { static V c; return STRC(c, "bendc: imports nested too deeply at "); }
static V L1627(V *a) {
return F_Main_dload_dparsed(a[1], F_Mod_ddir(a[0]), a[0], F_Main_dparse(a[2]));
}
static V F_Main_dload(V a0, V a1) {
top:;
V s1625 = a0;
if ((s1625) == 0) {
return F_IO_ddie(1u, F_String_dappend(S1626(), a1));
} else if (nat_ge(s1625, 1)) {
return F_IO_dbind(F_IO_dread__file(a1), mk_clo(L1627, 3, 2, (V[]){a1, nat_subk(s1625, 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dload(V *a) { (void)a; return F_Main_dload(a[0], a[1]); }
static V S1629(void) { static V c; return STRC(c, "bendc: parse error in "); }
static V S1630(void) { static V c; return STRC(c, ": "); }
static V L1631(V *a) {
return F_IO_dpure(F_List_dappend(a[2], F_Eff_ddecls(a[1], a[0])));
}
static V F_Main_dload_dparsed(V a0, V a1, V a2, V a3) {
top:;
V s1628 = a3;
if (TAG(s1628) == 0) {
return F_IO_ddie(1u, F_String_dappend(S1629(), F_String_dappend(a2, F_String_dappend(S1630(), FLD(s1628, 0)))));
} else if (TAG(s1628) == 1) {
return F_IO_dbind(F_Main_dimports(a0, a1, FLD(s1628, 0)), mk_clo(L1631, 3, 2, (V[]){FLD(s1628, 0), a1}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dload_dparsed(V *a) { (void)a; return F_Main_dload_dparsed(a[0], a[1], a[2], a[3]); }
static V S1633(void) { static V c; return STRC(c, "Base"); }
static V F_Main_dimports(V a0, V a1, V a2) {
top:;
V s1632 = a2;
if ((s1632) == IMM(0)) {
return F_IO_dpure(IMM(0));
} else if (TAG(s1632) == 1 && TAG(FLD(s1632, 0)) == 4) {
return F_Main_dimports_done(a0, a1, FLD(FLD(s1632, 0), 0), FLD(FLD(s1632, 0), 1), FLD(s1632, 1), F_Str_deq(FLD(FLD(s1632, 0), 0), S1633()));
} else if (TAG(s1632) == 1) {
{ V t0 = a0; V t1 = a1; V t2 = FLD(s1632, 1); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Main_dimports(V *a) { (void)a; return F_Main_dimports(a[0], a[1], a[2]); }
static V S1635(void) { static V c; return STRC(c, "0x"); }
static V L1637(V *a) {
return F_IO_dpure(F_List_dappend(F_Mod_dqualify(a[1], a[0]), a[2]));
}
static V L1636(V *a) {
return F_IO_dbind(F_Main_dimports(a[3], a[2], a[1]), mk_clo(L1637, 3, 2, (V[]){a[4], a[0]}));
}
static V F_Main_dimports_done(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1634 = a5;
if ((s1634) == IMM(1)) {
return F_Main_dimports(a0, a1, a4);
} else if ((s1634) == IMM(0)) {
return F_IO_dbind(F_Main_dload_dimport(a0, a1, a2, F_String_dstarts__with(a2, S1635())), mk_clo(L1636, 5, 4, (V[]){a3, a4, a1, a0}));
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
V s1638 = a0;
if ((s1638) == IMM(0)) {
return a1;
} else if (TAG(s1638) == 1 && TAG(FLD(s1638, 0)) == 0) {
{ V t0 = FLD(s1638, 1); V t1 = C2(1, FLD(FLD(s1638, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1638) == 1 && TAG(FLD(s1638, 0)) == 1) {
{ V t0 = FLD(s1638, 1); V t1 = C2(1, FLD(FLD(s1638, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1638) == 1 && TAG(FLD(s1638, 0)) == 2) {
{ V t0 = FLD(s1638, 1); V t1 = C2(1, FLD(FLD(s1638, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1638) == 1 && TAG(FLD(s1638, 0)) == 3) {
{ V t0 = FLD(s1638, 1); V t1 = C2(1, FLD(FLD(s1638, 0), 0), F_Mod_dctor__names(FLD(FLD(s1638, 0), 2), a1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1638) == 1 && TAG(FLD(s1638, 0)) == 4) {
{ V t0 = FLD(s1638, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dnames(V *a) { (void)a; return F_Mod_dnames(a[0], a[1]); }
static V F_Mod_dctor__names(V a0, V a1) {
top:;
V s1639 = a0;
if ((s1639) == IMM(0)) {
return a1;
} else if (TAG(s1639) == 1) {
{ V t0 = FLD(s1639, 1); V t1 = C2(1, FLD(FLD(s1639, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dctor__names(V *a) { (void)a; return F_Mod_dctor__names(a[0], a[1]); }
static V F_Mod_ddecls(V a0, V a1) {
top:;
V s1640 = a1;
if ((s1640) == IMM(0)) {
return IMM(0);
} else if (TAG(s1640) == 1) {
return C2(1, F_Mod_ddecl(a0, FLD(s1640, 0)), F_Mod_ddecls(a0, FLD(s1640, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddecls(V *a) { (void)a; return F_Mod_ddecls(a[0], a[1]); }
static V F_Mod_ddecl(V a0, V a1) {
top:;
V s1641 = a1;
if (TAG(s1641) == 0) {
return C4(0, F_Mod_dq(a0, FLD(s1641, 0)), FLD(s1641, 1), F_Mod_dexpr(a0, F_Mod_dparam__names(FLD(s1641, 1)), FLD(s1641, 2)), F_Mod_dexpr(a0, IMM(0), FLD(s1641, 3)));
} else if (TAG(s1641) == 1) {
return C3(1, F_Mod_dq(a0, FLD(s1641, 0)), FLD(s1641, 1), FLD(s1641, 2));
} else if (TAG(s1641) == 2) {
return C2(2, F_Mod_dq(a0, FLD(s1641, 0)), FLD(s1641, 1));
} else if (TAG(s1641) == 3) {
return C3(3, F_Mod_dq(a0, FLD(s1641, 0)), FLD(s1641, 1), F_Mod_dctors(a0, FLD(s1641, 2)));
} else if (TAG(s1641) == 4) {
return C2(4, FLD(s1641, 0), FLD(s1641, 1));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddecl(V *a) { (void)a; return F_Mod_ddecl(a[0], a[1]); }
static V F_Mod_dctors(V a0, V a1) {
top:;
V s1642 = a1;
if ((s1642) == IMM(0)) {
return IMM(0);
} else if (TAG(s1642) == 1) {
return C2(1, C2(0, F_Mod_dq(a0, FLD(FLD(s1642, 0), 0)), F_Mod_dfields(a0, FLD(FLD(s1642, 0), 1))), F_Mod_dctors(a0, FLD(s1642, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dctors(V *a) { (void)a; return F_Mod_dctors(a[0], a[1]); }
static V F_Mod_dfields(V a0, V a1) {
top:;
V s1643 = a1;
if ((s1643) == IMM(0)) {
return IMM(0);
} else if (TAG(s1643) == 1) {
return C2(1, C2(0, FLD(FLD(s1643, 0), 0), F_Mod_dexpr(a0, IMM(0), FLD(FLD(s1643, 0), 1))), F_Mod_dfields(a0, FLD(s1643, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dfields(V *a) { (void)a; return F_Mod_dfields(a[0], a[1]); }
static V F_Mod_dexpr(V a0, V a1, V a2) {
top:;
V s1644 = a2;
if (TAG(s1644) == 0) {
return C1(0, F_Mod_dvar(a0, a1, FLD(s1644, 0)));
} else if (TAG(s1644) == 5) {
return C2(5, F_Mod_dexpr(a0, a1, FLD(s1644, 0)), F_Mod_dexprs(a0, a1, FLD(s1644, 1)));
} else if (TAG(s1644) == 6) {
return C2(6, F_Mod_dq(a0, FLD(s1644, 0)), F_Mod_dexprs(a0, a1, FLD(s1644, 1)));
} else if (TAG(s1644) == 7) {
return C2(7, F_Mod_dpat(a0, FLD(s1644, 0)), F_Mod_dexpr(a0, F_Pat_dvars(FLD(s1644, 0), a1), FLD(s1644, 1)));
} else if (TAG(s1644) == 8) {
return C3(8, F_Mod_dpat(a0, FLD(s1644, 0)), F_Mod_dexpr(a0, a1, FLD(s1644, 1)), F_Mod_dexpr(a0, F_Pat_dvars(FLD(s1644, 0), a1), FLD(s1644, 2)));
} else if (TAG(s1644) == 9) {
return C2(9, F_Mod_dexprs(a0, a1, FLD(s1644, 0)), F_Mod_dexprs(a0, a1, FLD(s1644, 1)));
} else if (TAG(s1644) == 10) {
return C2(10, F_Mod_dpats(a0, FLD(s1644, 0)), F_Mod_dexpr(a0, F_Pats_dvars(FLD(s1644, 0), a1), FLD(s1644, 1)));
} else if (TAG(s1644) == 11) {
return C2(11, FLD(s1644, 0), F_Mod_dexpr(a0, a1, FLD(s1644, 1)));
} else if (TAG(s1644) == 12) {
return C3(12, FLD(s1644, 0), F_Mod_dexpr(a0, a1, FLD(s1644, 1)), F_Mod_dexpr(a0, a1, FLD(s1644, 2)));
} else if (TAG(s1644) == 13) {
return C2(13, F_Mod_dexpr(a0, a1, FLD(s1644, 0)), F_Mod_dvar(a0, a1, FLD(s1644, 1)));
} else if (TAG(s1644) == 14) {
return C2(14, F_Mod_dvar(a0, a1, FLD(s1644, 0)), F_Mod_dexprs(a0, a1, FLD(s1644, 1)));
} else {
return s1644;
}
}
static V W_Mod_dexpr(V *a) { (void)a; return F_Mod_dexpr(a[0], a[1], a[2]); }
static V F_Mod_dexprs(V a0, V a1, V a2) {
top:;
V s1645 = a2;
if ((s1645) == IMM(0)) {
return IMM(0);
} else if (TAG(s1645) == 1) {
return C2(1, F_Mod_dexpr(a0, a1, FLD(s1645, 0)), F_Mod_dexprs(a0, a1, FLD(s1645, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dexprs(V *a) { (void)a; return F_Mod_dexprs(a[0], a[1], a[2]); }
static V F_Mod_dvar(V a0, V a1, V a2) {
top:;
return F_Bool_dpick(F_Str_dhas(a1, a2), a2, F_Mod_dq(a0, a2));
}
static V W_Mod_dvar(V *a) { (void)a; return F_Mod_dvar(a[0], a[1], a[2]); }
static V S1647(void) { static V c; return STRC(c, "."); }
static V F_Mod_dq(V a0, V a1) {
top:;
V v1646 = a0;
return F_Bool_dpick(F_Str_dhas(FLD(v1646, 1), a1), F_String_dappend(FLD(v1646, 0), F_String_dappend(S1647(), a1)), a1);
}
static V W_Mod_dq(V *a) { (void)a; return F_Mod_dq(a[0], a[1]); }
static V F_Mod_dpats(V a0, V a1) {
top:;
V s1648 = a1;
if ((s1648) == IMM(0)) {
return IMM(0);
} else if (TAG(s1648) == 1) {
return C2(1, F_Mod_dpat(a0, FLD(s1648, 0)), F_Mod_dpats(a0, FLD(s1648, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dpats(V *a) { (void)a; return F_Mod_dpats(a[0], a[1]); }
static V F_Mod_dpat(V a0, V a1) {
top:;
V s1649 = a1;
if (TAG(s1649) == 1) {
return C2(1, F_Mod_dq(a0, FLD(s1649, 0)), F_Mod_dpats(a0, FLD(s1649, 1)));
} else if (TAG(s1649) == 3) {
return C2(3, FLD(s1649, 0), F_Mod_dpat(a0, FLD(s1649, 1)));
} else {
return s1649;
}
}
static V W_Mod_dpat(V *a) { (void)a; return F_Mod_dpat(a[0], a[1]); }
static V F_Mod_dparam__names(V a0) {
top:;
V s1650 = a0;
if ((s1650) == IMM(0)) {
return IMM(0);
} else if (TAG(s1650) == 1) {
return C2(1, FLD(FLD(s1650, 0), 0), F_Mod_dparam__names(FLD(s1650, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dparam__names(V *a) { (void)a; return F_Mod_dparam__names(a[0]); }
static V F_Main_dload_dimport(V a0, V a1, V a2, V a3) {
top:;
V s1651 = a3;
if ((s1651) == IMM(1)) {
return F_Main_dload_dhub(a0, a2);
} else if ((s1651) == IMM(0)) {
return F_Main_dload(a0, F_Eff_dpath(a1, a2));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dload_dimport(V *a) { (void)a; return F_Main_dload_dimport(a[0], a[1], a[2], a[3]); }
static V S1653(void) { static V c; return STRC(c, "BEND_HUB"); }
static V S1656(void) { static V c; return STRC(c, "/"); }
static V L1655(V *a) {
return F_Main_dload(a[2], F_String_dappend(a[1], F_String_dappend(S1656(), a[0])));
}
static V L1654(V *a) {
return F_IO_dbind(F_IO_dtry(F_Hub_densure(a[2], F_Main_dhub_durl(a[3]), a[1])), mk_clo(L1655, 4, 3, (V[]){a[1], a[2], a[0]}));
}
static V L1652(V *a) {
return F_IO_dbind(F_IO_dget__env(S1653()), mk_clo(L1654, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Main_dload_dhub(V a0, V a1) {
top:;
return F_IO_dbind(F_Main_dlib(), mk_clo(L1652, 3, 2, (V[]){a0, a1}));
}
static V W_Main_dload_dhub(V *a) { (void)a; return F_Main_dload_dhub(a[0], a[1]); }
static V S1658(void) { static V c; return STRC(c, "https://hub.bend-lang.com"); }
static V F_Main_dhub_durl(V a0) {
top:;
V s1657 = a0;
if (TAG(s1657) == 1) {
return FLD(s1657, 0);
} else if (TAG(s1657) == 0) {
return S1658();
} else { bend_fail("incomplete match"); }
}
static V W_Main_dhub_durl(V *a) { (void)a; return F_Main_dhub_durl(a[0]); }
static V E_Hub_densure(V *a) { return io_req(CID_HUB_ENSURE, 4, (V[]){a[0], a[1], a[2], a[4]}); }
static V F_Hub_densure(V a0, V a1, V a2) { return mk_clo(E_Hub_densure, 5, 3, (V[]){a0, a1, a2}); }
static V W_Hub_densure(V *a) { (void)a; return F_Hub_densure(a[0], a[1], a[2]); }
static V E_IO_dget__env(V *a) { return io_req(CID_IO_GET_ENV, 2, (V[]){a[0], a[2]}); }
static V F_IO_dget__env(V a0) { return mk_clo(E_IO_dget__env, 3, 1, (V[]){a0}); }
static V W_IO_dget__env(V *a) { (void)a; return F_IO_dget__env(a[0]); }
static V S1659(void) { static V c; return STRC(c, "BEND_LIB"); }
static V L1660(V *a) {
return F_Main_dlib_dor(a[0]);
}
static V F_Main_dlib(void) {
top:;
return F_IO_dbind(F_IO_dget__env(S1659()), mk_clo(L1660, 1, 0, 0));
}
static V W_Main_dlib(V *a) { (void)a; return F_Main_dlib(); }
static V S1662(void) { static V c; return STRC(c, "HOME"); }
static V S1664(void) { static V c; return STRC(c, "/.bend/lib"); }
static V L1663(V *a) {
return F_IO_dpure(F_String_dappend(a[0], S1664()));
}
static V F_Main_dlib_dor(V a0) {
top:;
V s1661 = a0;
if (TAG(s1661) == 1) {
return F_IO_dpure(FLD(s1661, 0));
} else if (TAG(s1661) == 0) {
return F_IO_dbind(F_IO_dtry(F_IO_dget__env(S1662())), mk_clo(L1663, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dlib_dor(V *a) { (void)a; return F_Main_dlib_dor(a[0]); }
static V S1666(void) { static V c; return STRC(c, "bendc: parse error: "); }
static V F_Main_dast(V a0) {
top:;
V s1665 = a0;
if (TAG(s1665) == 0) {
return F_IO_ddie(1u, F_String_dappend(S1666(), FLD(s1665, 0)));
} else if (TAG(s1665) == 1) {
return F_IO_dwrite(F_Decls_dshow(FLD(s1665, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dast(V *a) { (void)a; return F_Main_dast(a[0]); }
static V F_Decls_dshow(V a0) {
top:;
return F_Decls_dshow_dgo(a0);
}
static V W_Decls_dshow(V *a) { (void)a; return F_Decls_dshow(a[0]); }
static V S1668(void) { static V c; return STRC(c, ""); }
static V S1669(void) { static V c; return STRC(c, "\012"); }
static V F_Decls_dshow_dgo(V a0) {
top:;
V s1667 = a0;
if ((s1667) == IMM(0)) {
return S1668();
} else if (TAG(s1667) == 1) {
return F_String_dappend(F_Decl_dshow(FLD(s1667, 0)), F_String_dappend(S1669(), F_Decls_dshow_dgo(FLD(s1667, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Decls_dshow_dgo(V *a) { (void)a; return F_Decls_dshow_dgo(a[0]); }
static V S1671(void) { static V c; return STRC(c, "def "); }
static V S1672(void) { static V c; return STRC(c, "("); }
static V S1673(void) { static V c; return STRC(c, ") = "); }
static V S1674(void) { static V c; return STRC(c, "eff "); }
static V S1675(void) { static V c; return STRC(c, "("); }
static V S1676(void) { static V c; return STRC(c, ")"); }
static V S1677(void) { static V c; return STRC(c, "law "); }
static V S1678(void) { static V c; return STRC(c, "("); }
static V S1679(void) { static V c; return STRC(c, ")"); }
static V S1680(void) { static V c; return STRC(c, "type "); }
static V S1681(void) { static V c; return STRC(c, " "); }
static V S1682(void) { static V c; return STRC(c, "import "); }
static V S1683(void) { static V c; return STRC(c, " as "); }
static V F_Decl_dshow(V a0) {
top:;
V s1670 = a0;
if (TAG(s1670) == 0) {
return F_String_dappend(S1671(), F_String_dappend(FLD(s1670, 0), F_String_dappend(S1672(), F_String_dappend(F_Params_dshow(FLD(s1670, 1)), F_String_dappend(S1673(), F_Expr_dshow(FLD(s1670, 2)))))));
} else if (TAG(s1670) == 1) {
return F_String_dappend(S1674(), F_String_dappend(FLD(s1670, 0), F_String_dappend(S1675(), F_String_dappend(F_Params_dshow(FLD(s1670, 1)), S1676()))));
} else if (TAG(s1670) == 2) {
return F_String_dappend(S1677(), F_String_dappend(FLD(s1670, 0), F_String_dappend(S1678(), F_String_dappend(F_Params_dshow(FLD(s1670, 1)), S1679()))));
} else if (TAG(s1670) == 3) {
return F_String_dappend(S1680(), F_String_dappend(FLD(s1670, 0), F_String_dappend(S1681(), F_Ctors_dshow(FLD(s1670, 2)))));
} else if (TAG(s1670) == 4) {
return F_String_dappend(S1682(), F_String_dappend(FLD(s1670, 0), F_String_dappend(S1683(), FLD(s1670, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Decl_dshow(V *a) { (void)a; return F_Decl_dshow(a[0]); }
static V S1685(void) { static V c; return STRC(c, ""); }
static V S1686(void) { static V c; return STRC(c, " "); }
static V F_Ctors_dshow(V a0) {
top:;
V s1684 = a0;
if ((s1684) == IMM(0)) {
return S1685();
} else if (TAG(s1684) == 1) {
return F_String_dappend(F_Ctor_dshow(FLD(s1684, 0)), F_String_dappend(S1686(), F_Ctors_dshow(FLD(s1684, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Ctors_dshow(V *a) { (void)a; return F_Ctors_dshow(a[0]); }
static V S1688(void) { static V c; return STRC(c, "{"); }
static V S1689(void) { static V c; return STRC(c, "}"); }
static V F_Ctor_dshow(V a0) {
top:;
V v1687 = a0;
return F_String_dappend(FLD(v1687, 0), F_String_dappend(S1688(), F_String_dappend(F_Fields_dshow(FLD(v1687, 1)), S1689())));
}
static V W_Ctor_dshow(V *a) { (void)a; return F_Ctor_dshow(a[0]); }
static V S1691(void) { static V c; return STRC(c, ""); }
static V S1692(void) { static V c; return STRC(c, ":"); }
static V S1693(void) { static V c; return STRC(c, " "); }
static V F_Fields_dshow(V a0) {
top:;
V s1690 = a0;
if ((s1690) == IMM(0)) {
return S1691();
} else if (TAG(s1690) == 1) {
return F_String_dappend(FLD(FLD(s1690, 0), 0), F_String_dappend(S1692(), F_String_dappend(F_Expr_dshow(FLD(FLD(s1690, 0), 1)), F_String_dappend(S1693(), F_Fields_dshow(FLD(s1690, 1))))));
} else { bend_fail("incomplete match"); }
}
static V W_Fields_dshow(V *a) { (void)a; return F_Fields_dshow(a[0]); }
static V S1695(void) { static V c; return STRC(c, ""); }
static V S1696(void) { static V c; return STRC(c, " "); }
static V F_Params_dshow(V a0) {
top:;
V s1694 = a0;
if ((s1694) == IMM(0)) {
return S1695();
} else if (TAG(s1694) == 1) {
return F_String_dappend(F_Param_dshow(FLD(s1694, 0)), F_String_dappend(S1696(), F_Params_dshow(FLD(s1694, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Params_dshow(V *a) { (void)a; return F_Params_dshow(a[0]); }
static V S1698(void) { static V c; return STRC(c, ":"); }
static V F_Param_dshow(V a0) {
top:;
V v1697 = a0;
return F_String_dappend(F_U32_dshow(FLD(v1697, 1)), F_String_dappend(FLD(v1697, 0), F_String_dappend(S1698(), FLD(v1697, 2))));
}
static V W_Param_dshow(V *a) { (void)a; return F_Param_dshow(a[0]); }
static V S1700(void) { static V c; return STRC(c, ""); }
static V F_Toks_dshow(V a0) {
top:;
V s1699 = a0;
if ((s1699) == IMM(0)) {
return S1700();
} else if (TAG(s1699) == 1) {
return F_String_dappend(F_Tok_dshow(FLD(s1699, 0)), F_Toks_dshow(FLD(s1699, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Toks_dshow(V *a) { (void)a; return F_Toks_dshow(a[0]); }
static V S1702(void) { static V c; return STRC(c, " "); }
static V S1703(void) { static V c; return STRC(c, ""); }
static V F_Tok_dshow(V a0) {
top:;
V v1701 = a0;
return F_String_dappend(F_Bool_dpick(FLD(v1701, 1), S1702(), S1703()), F_TK_dshow(FLD(v1701, 0)));
}
static V W_Tok_dshow(V *a) { (void)a; return F_Tok_dshow(a[0]); }
static V E_IO_dprint(V *a) { return io_req(CID_IO_PRINT, 2, (V[]){a[0], a[2]}); }
static V F_IO_dprint(V a0) { return mk_clo(E_IO_dprint, 3, 1, (V[]){a0}); }
static V W_IO_dprint(V *a) { (void)a; return F_IO_dprint(a[0]); }
static V E_IO_dargs(V *a) { return io_req(CID_IO_ARGS, 1, (V[]){a[1]}); }
static V F_IO_dargs(void) { return mk_clo(E_IO_dargs, 2, 0, 0); }
static V W_IO_dargs(V *a) { (void)a; return F_IO_dargs(); }

int main(int argc, char **argv) { return bend_run(argc, argv, F_main); }

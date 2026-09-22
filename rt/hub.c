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

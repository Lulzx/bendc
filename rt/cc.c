// bendc -o
// ========
//
// `bendc -o prog base.bend prog.bend` builds a binary. Cc.begin sends what
// bendc writes (the program's C) to a temporary file; Cc.end compiles it with
// $CC (default cc) against the runtime compiled once: bendrt.o beside the
// bendc executable, built from rt/bendrt_impl.c when it is missing or older.
// The runtime's directory is ../rt from the executable, or $BENDC_RT. A
// program then compiles only its own code.

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

static int cc_saved = -1;
static char cc_tmp[PATH_MAX];

// The directory of the running executable.
static int cc_exe_dir(char *out, size_t n) {
  char path[PATH_MAX];
#ifdef __APPLE__
  uint32_t sz = sizeof path;
  if (_NSGetExecutablePath(path, &sz) != 0) return -1;
#else
  ssize_t k = readlink("/proc/self/exe", path, sizeof path - 1);
  if (k < 0) return -1;
  path[k] = 0;
#endif
  char real[PATH_MAX];
  if (!realpath(path, real)) return -1;
  char *slash = strrchr(real, '/');
  if (!slash) return -1;
  *slash = 0;
  snprintf(out, n, "%s", real);
  return 0;
}

static long cc_mtime(const char *p) {
  struct stat st;
  return stat(p, &st) == 0 ? (long)st.st_mtime : -1;
}

Term cc_begin_run(Env e, Term *f, IoWork *w) {
  (void)f;
  (void)w;
  fflush(stdout);
  snprintf(cc_tmp, sizeof cc_tmp, "%s/bendc-XXXXXX.c", getenv("TMPDIR") ? getenv("TMPDIR") : "/tmp");
  int fd = mkstemps(cc_tmp, 2);
  if (fd < 0) return io_fail(e, (u32)errno, "cannot make a temporary file");
  cc_saved = dup(1);
  dup2(fd, 1);
  close(fd);
  return io_done(e, term_pak(CID_UNIT, 0));
}

static Term cc_fail(Env e, const char *msg) {
  unlink(cc_tmp);
  return io_fail(e, 1, msg);
}

Term cc_end_run(Env e, Term *f, IoWork *w) {
  (void)w;
  u64 n;
  char *out = io_cstr(e, f[0], &n);
  fflush(stdout);
  if (cc_saved >= 0) {
    dup2(cc_saved, 1);
    close(cc_saved);
    cc_saved = -1;
  }
  char dir[PATH_MAX], rt[PATH_MAX], obj[PATH_MAX], impl[PATH_MAX], hdr[PATH_MAX];
  if (cc_exe_dir(dir, sizeof dir) != 0) { free(out); return cc_fail(e, "cannot find the bendc executable"); }
  const char *env_rt = getenv("BENDC_RT");
  if (env_rt && *env_rt) snprintf(rt, sizeof rt, "%s", env_rt);
  else snprintf(rt, sizeof rt, "%s/../rt", dir);
  snprintf(obj, sizeof obj, "%s/bendrt.o", dir);
  snprintf(impl, sizeof impl, "%s/bendrt_impl.c", rt);
  snprintf(hdr, sizeof hdr, "%s/bendrt_split.h", rt);
  const char *cc = getenv("CC") && *getenv("CC") ? getenv("CC") : "cc";
  size_t cl = strlen(cc) + 3 * PATH_MAX + strlen(out) + 256;
  char *cmd = malloc(cl);
  if (cc_mtime(obj) < 0 || cc_mtime(obj) < cc_mtime(impl) || cc_mtime(obj) < cc_mtime(hdr)) {
    snprintf(cmd, cl, "%s -O2 -w -I '%s' -c '%s' -o '%s.tmp' && mv '%s.tmp' '%s'", cc, rt, impl, obj, obj, obj);
    if (system(cmd) != 0) { free(cmd); free(out); return cc_fail(e, "the runtime (bendrt.o) does not compile"); }
  }
#ifdef __APPLE__
  const char *libs = "-lm -lpthread";
#else
  const char *libs = "-lm -lpthread -ldl";
#endif
  snprintf(cmd, cl, "%s -O2 -w -DBEND_RT_SPLIT -I '%s' '%s' '%s' -o '%s' %s", cc, rt, cc_tmp, obj, out, libs);
  int rc = system(cmd);
  free(cmd);
  free(out);
  if (rc != 0) return cc_fail(e, "the C compiler failed");
  unlink(cc_tmp);
  return io_done(e, term_pak(CID_UNIT, 0));
}

static void __attribute__((constructor)) cc_use(void) {
  io_eff(CID_CC_BEGIN, cc_begin_run, 0);
  io_eff(CID_CC_END, cc_end_run, 0);
}

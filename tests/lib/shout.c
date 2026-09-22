// Upper-cases a string on a helper thread (io_work), then answers it.
static void shout_call(IoWork* w) {
  for (u64 i = 0; i < w->size; i++) {
    if (w->data[i] >= 'a' && w->data[i] <= 'z') w->data[i] -= 32;
  }
}

static Term shout_pack(Env e, IoWork* w) {
  Term s = io_str(e, w->data, w->size);
  free(w->data);
  return io_done(e, s);
}

Term shout_run(Env e, Term* f, IoWork* w) {
  w->data = io_cstr(e, f[0], &w->size);
  return io_work(w, shout_call, shout_pack);
}

static void __attribute__((constructor)) shout_use(void) {
  io_eff(CID_SHOUT, shout_run, 0);
}

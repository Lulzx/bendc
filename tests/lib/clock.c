Term clock_now_run(Env e, Term* f, IoWork* w) {
  return (Term)(uint32_t)(io_tick() / 1000000ull);
}

static void __attribute__((constructor)) clock_now_use(void) {
  io_eff(CID_CLOCK_NOW, clock_now_run, 0);
}

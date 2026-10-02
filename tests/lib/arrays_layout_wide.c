Term foreign_make_run(Env e, Term *f, IoWork *w) { return arr_new(2, 23); }
static void __attribute__((constructor)) foreign_make_use(void) { io_eff(CID_FOREIGN_MAKE, foreign_make_run, 0); }

Term foreign_grove_run(Env e, Term *f, IoWork *w) { return C2(CID_TAG(CID_FORK), term_pak(CID_SEED, 5), term_pak(CID_SEED, 11)); }
static void __attribute__((constructor)) foreign_grove_use(void) { io_eff(CID_FOREIGN_GROVE, foreign_grove_run, 0); }

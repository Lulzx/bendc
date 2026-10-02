Term foreign_box_run(Env e, Term *f, IoWork *w) { return C2(CID_TAG(CID_BOX), arr_new(2, 29), 0); }
static void __attribute__((constructor)) foreign_box_use(void) { io_eff(CID_FOREIGN_BOX, foreign_box_run, 0); }

Term probe_run(Env e, Term *f, IoWork *w) {
  V a = arr_new(2, 0);
  F_Array_dset_x37w(a, 0, 19);
  V x = arr_rdw(a, 0);
  if (gc_hot.rc) rc_drop(a); else arr_dead(a);
  return x;
}
static void __attribute__((constructor)) probe_use(void) { io_eff(CID_PROBE, probe_run, 0); }

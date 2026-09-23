// bendc -o builds with a C compiler (see rt/cc.c); not from JavaScript.
function cc_begin() {
  return io_fail(1, "bendc -o needs the C build of bendc");
}
function cc_end(out) {
  return io_fail(1, "bendc -o needs the C build of bendc");
}

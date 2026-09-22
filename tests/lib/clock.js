function clock_now() {
  return Math.floor(performance.now()) >>> 0;
}

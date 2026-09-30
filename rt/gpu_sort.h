// Host-side lane permutation. src holds sorted source lane indices; dst
// holds the same waiting lanes in ascending order. Other lanes stay intact.
// KW and K_LANE come from gpu.h.
static void gpu_sort_permute(KW *L, KW n, KW *src, const KW *dst, KW k) {
  // Convert source lane indices to positions among the waiting lanes.
  for (KW i = 0; i < k; i++) {
    KW lo = 0, hi = k;
    while (lo < hi) {
      KW mid = lo + (hi - lo) / 2;
      if (dst[mid] < src[i]) lo = mid + 1;
      else hi = mid;
    }
    src[i] = lo;
  }
  for (KW i = 0; i < k; i++) {
    if (src[i] == i) continue;
    KW held[K_LANE];
    for (int word = 0; word < K_LANE; word++) held[word] = L[word * n + dst[i]];
    KW at = i;
    while (src[at] != i) {
      KW from = src[at];
      for (int word = 0; word < K_LANE; word++)
        L[word * n + dst[at]] = L[word * n + dst[from]];
      src[at] = at;
      at = from;
    }
    for (int word = 0; word < K_LANE; word++) L[word * n + dst[at]] = held[word];
    src[at] = at;
  }
}

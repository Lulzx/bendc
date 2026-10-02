#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
typedef uint64_t KW;
#define K_LANE 24
#include "gpu_sort.h"
static uint32_t state = 123456789;
static uint32_t next(void) { state = state * 1664525 + 1013904223; return state; }
int main(void) {
  for (KW n = 1; n <= 512; n *= 2) {
    KW *L = malloc(n * K_LANE * sizeof(KW));
    KW *expected = malloc(n * K_LANE * sizeof(KW));
    KW *dst = malloc(n * sizeof(KW)), *src = malloc(n * sizeof(KW));
    assert(L && expected && dst && src);
    for (int trial = 0; trial < 100; trial++) {
      KW k = 0;
      for (KW lane = 0; lane < n; lane++) {
        for (int word = 0; word < K_LANE; word++) L[word * n + lane] = ((KW)next() << 32) | next();
        if (trial == 1 || (trial != 0 && next() % 3)) src[k] = dst[k] = lane, k++;
      }
      memcpy(expected, L, n * K_LANE * sizeof(KW));
      for (KW i = k; i > 1; i--) {
        KW j = next() % i, t = src[i - 1]; src[i - 1] = src[j]; src[j] = t;
      }
      for (KW i = 0; i < k; i++)
        for (int word = 0; word < K_LANE; word++) expected[word * n + dst[i]] = L[word * n + src[i]];
      gpu_sort_permute(L, n, src, dst, k);
      assert(memcmp(L, expected, n * K_LANE * sizeof(KW)) == 0);
      for (KW i = 0; i < k; i++) assert(src[i] == i);
    }
    free(src); free(dst); free(expected); free(L);
  }
  puts("ok");
}

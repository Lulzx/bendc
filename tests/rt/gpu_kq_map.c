#include <stdint.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "gpu.h"
static unsigned calls[16], order[16], count, fail_lane;
KINLINE KW k_frame_size(KW l) { return 8; }
KINLINE void k_cases(KCtx *c) { k_fail(c, KE_PC); }
KINLINE KW k_kq(KCtx *c, bool *ok) {
  (void)ok;
  calls[c->lane]++;
  order[count++] = c->lane;
  if (c->lane == fail_lane) k_fail(c, KE_HEAP);
  return c->kqa[0] + 1;
}
int main(void) {
  KW H[4096] = {0}, before[4096]; KAU A[64] = {0};
  KParams p = {0}; p.nlanes = 16; p.lane0 = 256; p.kqmap = 1280;
  p.ab = (KW)(uintptr_t)H; p.an = sizeof H;
  for (KW lane = 0; lane < p.nlanes; lane++) {
    for (int word = 0; word < K_LANE; word++) H[p.lane0 + word * p.nlanes + lane] = 1000 + word * 100 + lane;
    H[p.lane0 + lane] = PC_IDLE;
    H[p.lane0 + 8 * p.nlanes + lane] = PC_JOIN;
    H[p.lane0 + 10 * p.nlanes + lane] = 100 + lane;
  }
  KW lanes[] = {10, 3, 7};
  H[p.kqmap] = 3;
  for (int i = 0; i < 3; i++) {
    H[p.kqmap + 1 + i] = lanes[i]; H[p.lane0 + lanes[i]] = PC_KQ;
  }
  memcpy(before, H, sizeof H);
  fail_lane = 7;
  for (KU thread = 0; thread < p.nlanes; thread++) bend_kq(H, A, &p, NULL, thread);
  assert(count == 3 && order[0] == 10 && order[1] == 3 && order[2] == 7);
  assert(A[KA_GROW] == 1 && H[p.lane0 + 7] == PC_KQ);
  fail_lane = 99; A[KA_GROW] = 0;
  for (KU thread = 0; thread < p.nlanes; thread++) bend_kq(H, A, &p, NULL, thread);
  assert(count == 4 && order[3] == 7 && calls[7] == 2 && A[KA_GROW] == 0);
  for (KW lane = 0; lane < p.nlanes; lane++) {
    bool ran = lane == 10 || lane == 3 || lane == 7;
    assert(calls[lane] == (ran ? (lane == 7 ? 2 : 1) : 0));
    assert(H[p.lane0 + lane] == (ran ? PC_JOIN : PC_IDLE));
    if (ran) assert(H[p.lane0 + 2 * p.nlanes + lane] == 101 + lane);
    for (int word = 1; word < K_LANE; word++) {
      if (ran && word == 2) continue;
      assert(H[p.lane0 + word * p.nlanes + lane] == before[p.lane0 + word * p.nlanes + lane]);
    }
  }
  // Disabling the map retains the original lane-order dispatch.
  memset(calls, 0, sizeof calls); count = 0; p.kqmap = 0;
  for (int i = 0; i < 3; i++) H[p.lane0 + lanes[i]] = PC_KQ;
  for (KU thread = 0; thread < p.nlanes; thread++) bend_kq(H, A, &p, NULL, thread);
  assert(count == 3 && order[0] == 3 && order[1] == 7 && order[2] == 10);
  puts("ok");
}

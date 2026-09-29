// The atomics the runtime relies on, as the C compiler at hand builds them
// (run_tests.sh compiles every tests/rt/*.c with $CC against rt/bendrt.h and
// expects "ok"). tcc's own stdatomic.h made both of these fail on arm64 (see
// the note after #include <stdatomic.h> in rt/bendrt.h), and tests/maps
// then crashed now and then: a worker stole from a thread whose slot in
// gc_thrs it saw counted but not yet written.
#include "bendrt.h"

#define PUB_N 4096
static void *pub_slots[PUB_N];
static int pub_n;
static volatile int pub_stop;
static long pub_nulls;

// The publish of thr_register: the slot, then the count with a release
// store. A reader that acquires the count must see the slot.
static void *pub_reader(void *a) {
  (void)a;
  long nulls = 0;
  while (!pub_stop) {
    int k = __atomic_load_n(&pub_n, __ATOMIC_ACQUIRE);
    if (k > 0 && pub_slots[k - 1] == NULL) nulls++;
  }
  __atomic_fetch_add(&pub_nulls, nulls, __ATOMIC_RELAXED);
  return NULL;
}

// A lock made of a strong compare-and-swap (as a block's owned flag and the
// deques' top are claimed) and a release store: no increment is lost.
#define LK_T 4
#define LK_K 200000
static uint8_t lk8;
static long lk64;
static long lk_c8, lk_c64;
static void *lk_run(void *a) {
  (void)a;
  for (int i = 0; i < LK_K; i++) {
    uint8_t z = 0;
    while (!__atomic_compare_exchange_n(&lk8, &z, 1, 0, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)) z = 0;
    lk_c8++;
    __atomic_store_n(&lk8, 0, __ATOMIC_RELEASE);
    long x = 0;
    while (!atomic_compare_exchange_strong_explicit((_Atomic long *)&lk64, &x, 1, memory_order_seq_cst, memory_order_relaxed)) x = 0;
    lk_c64++;
    __atomic_store_n(&lk64, 0, __ATOMIC_RELEASE);
  }
  return NULL;
}

int main(void) {
  static int dummy[PUB_N];
  int bad = 0;
  // __atomic_store_n evaluates its value once
  int calls = 0, cell = 0;
  __atomic_store_n(&cell, ++calls, __ATOMIC_RELEASE);
  if (calls != 1 || cell != 1) { printf("__atomic_store_n evaluated its value %d times\n", calls); bad = 1; }
  for (int round = 0; round < 50; round++) {
    for (int i = 0; i < PUB_N; i++) pub_slots[i] = NULL;
    __atomic_store_n(&pub_n, 0, __ATOMIC_SEQ_CST);
    pub_stop = 0;
    pthread_t t[3];
    for (int i = 0; i < 3; i++) pthread_create(&t[i], NULL, pub_reader, NULL);
    for (int i = 0; i < PUB_N; i++) {
      pub_slots[i] = &dummy[i];
      __atomic_store_n(&pub_n, i + 1, __ATOMIC_RELEASE);
    }
    pub_stop = 1;
    for (int i = 0; i < 3; i++) pthread_join(t[i], NULL);
  }
  if (pub_nulls) { printf("a released count was seen before its slot %ld times\n", pub_nulls); bad = 1; }
  pthread_t t[LK_T];
  for (int i = 0; i < LK_T; i++) pthread_create(&t[i], NULL, lk_run, NULL);
  for (int i = 0; i < LK_T; i++) pthread_join(t[i], NULL);
  if (lk_c8 != (long)LK_T * LK_K || lk_c64 != (long)LK_T * LK_K) {
    printf("a compare-and-swap lock lost increments: %ld and %ld of %ld\n", lk_c8, lk_c64, (long)LK_T * LK_K);
    bad = 1;
  }
  if (!bad) printf("ok\n");
  return bad;
}

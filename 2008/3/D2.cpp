#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MOD 10007

int dx, dy;
int r;
int rx[10];
int ry[10];


int inv[MOD];


int testx[20];
int testy[20];

int binom(int n, int k) {
  assert(n >= 0);
  assert(k >= 0);
  if (n >= MOD)
    return (binom(n / MOD, k / MOD) * binom(n % MOD, k % MOD)) % MOD;
  else {
    int t = 1;
    int b = 1;
    FORE(i, n-k+1, n+1) t = (t * i) % MOD;
    FORE(i, 1, k + 1) b = (b * inv[i]) % MOD;
    return (t * b) % MOD;
  }
}


int ways(int x1, int y1, int x2, int y2) {
  if (x2 < x1 || y2 < y1) return 0;
  int dxl = x2 - x1;
  int dyl = y2 - y1;
  if ((dxl + dyl) % 3 != 0) return 0;
  if (dxl > 2 * dyl || dyl > 2 * dxl) return 0;
  int n = (dxl + dyl) / 3;
  int k = dyl - n;
  //printf("Computing %d, %d -> %d %d - (%d / %d) result %d\n", x1, y1, x2, y2, n, k, binom(n, k));
  return binom(n, k);
}


void computeInv(void) {
  FORE(i, 1, MOD) {
    int c = i;
    int t = 1;
    int m = MOD - 2;
    while (m > 0) {
      if ((m & 1) != 0) t = (t * c) % MOD;
      c = (c * c) % MOD;
      m >>= 1;
    }
    inv[i] = t;
  }
}

void swap(int * x, int * y) {
  int t = *x;
  *x = *y;
  *y = t;
}

void sort() {
  FOR(i, r)
    FORE(j, i+1, r)
      if (rx[i] > rx[j]) {
        swap(&rx[i], &rx[j]);
        swap(&ry[i], &ry[j]);
      }
}

int main(void) {
  int cases;
  computeInv();
  testx[0] = 1;
  testy[0] = 1;


  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %d %d", &dy, &dx, &r);
    FOR(i, r) scanf("%d %d", &ry[i], &rx[i]);
    sort();

    int total = 0;

    FOR(i, 1<<r) {
      int bits = 1;
      FOR(j, r) if ((i & (1<<j)) != 0) {
        testx[bits] = rx[j];
        testy[bits] = ry[j];
        bits++;
      }
      testx[bits] = dx;
      testy[bits] = dy;
      int cur = 1;
      for(int j=0;j<bits && cur > 0;j++) cur = (cur * ways(testx[j], testy[j], testx[j+1], testy[j+1])) % MOD;
      if (bits & 1) total += cur; else total -= cur;
    }
    total %= MOD;
    printf("Case #%d: %d\n", c, (total + MOD) % MOD);
  }
}

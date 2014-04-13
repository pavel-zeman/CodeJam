#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define PARTS 10000
#define N 5000

int a[N], b[N], c[N];
int n, currentMax;


int main(void) {
  int cases;

  scanf("%d", &cases);
  for(int cas=1;cas<=cases;cas++) {
    scanf("%d", &n);
    FOR(i, n) scanf("%d%d%d", a + i, b + i, c + i);
    currentMax = 0;

    for(int z=0;z<=PARTS;z++) {
      int y = PARTS - z;
      int ok = 0;
      FOR(i, n) if (a[i] <= 0 && b[i] <= y && c[i] <= z) ok++;
      if (ok > currentMax) currentMax = ok;

      // fill in auxiliary arrays
      int add[PARTS+1], remove[PARTS+2];
      FOR(i, PARTS+1) add[i] = remove[i] = 0;
      FOR(i, n) {
        if (c[i] <= z && b[i] <= PARTS - z - a[i]) {
          add[a[i]]++;
          remove[PARTS - z - b[i] + 1]++;
        }
      }

      for(int x = 1; x<=PARTS-z;x++) {
        ok += add[x] - remove[x];
        if (ok > currentMax) currentMax = ok;
      }

    }

    printf("Case #%d: %d\n", cas, currentMax);

  }
}

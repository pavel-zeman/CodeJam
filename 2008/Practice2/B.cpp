#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int k, n;
int pointsx[15], pointsy[15];
int min;
int set[15];

int max(int a, int b) {
  return a > b ? a : b;
}

void generate(int u) {
  if (u < n) {
    FOR(i, k) {
      set[u] = i;
      generate(u + 1);
    }
  } else {
    int curr = 0;
    FOR(i, k) {
      int minx = 65000;
      int miny = 65000;
      int maxx = 0;
      int maxy = 0;
      FOR(j, n) {
        if (set[j] == i) {
          if (pointsx[j] < minx) minx = pointsx[j];
          if (pointsx[j] > maxx) maxx = pointsx[j];
          if (pointsy[j] < miny) miny = pointsy[j];
          if (pointsy[j] > maxy) maxy = pointsy[j];
        }
      }

      if (minx != 65000) {
        int mm = max(maxx - minx, maxy - miny);
        if (mm > curr) curr = mm;
      }
    }
    if (curr < min) min = curr;
  }
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %d", &n, &k);
    FOR(i, n) scanf("%d %d", &pointsx[i], &pointsy[i]);
    min = 70000;
    generate(0);

    printf("Case #%d: %d\n", c, min);
  }
}

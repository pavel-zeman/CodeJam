#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define N 1000

int n;

struct ship {
  int x, y, z;
  int p;
} ships[N];




bool check(double p) {
  double a[4], b[4];
  FOR(i, 4) {a[i] = -1e12; b[i] = 1e12;}
  FOR(i, n) {
    double z = 0;
    a[0] = fmax(a[0], z + ships[i].x + ships[i].y + ships[i].z - ships[i].p * p);
    b[0] = fmin(b[0], z + ships[i].x + ships[i].y + ships[i].z + ships[i].p * p);
    a[1] = fmax(a[1], z + ships[i].x - ships[i].y + ships[i].z - ships[i].p * p);
    b[1] = fmin(b[1], z + ships[i].x - ships[i].y + ships[i].z + ships[i].p * p);
    a[2] = fmax(a[2], z + ships[i].x + ships[i].y - ships[i].z - ships[i].p * p);
    b[2] = fmin(b[2], z + ships[i].x + ships[i].y - ships[i].z + ships[i].p * p);
    a[3] = fmax(a[3], z + ships[i].x - ships[i].y - ships[i].z - ships[i].p * p);
    b[3] = fmin(b[3], z + ships[i].x - ships[i].y - ships[i].z + ships[i].p * p);
  }
  return (a[0] <= b[0] && a[1] <= b[1] && a[2] <= b[2] && a[3] <= b[3]);
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d", &n);
    FOR(i, n) scanf("%d %d %d %d", &ships[i].x, &ships[i].y, &ships[i].z, &ships[i].p);

    double a = 0;
    double b = 1e12;
    FOR(i, 100) {
      double m = (a + b) / 2;
      if (check(m)) b = m; else a = m;
    }

    printf("Case #%d: %.6lf\n", c, a);
  }
}

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int n;
int x[100], y[100], r[100];

int d[3][3] = {{0, 1, 2}, {0, 2, 1}, {1, 2, 0}};

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    double res;
    scanf("%d", &n);
    FOR(i, n) scanf("%d %d %d", &x[i], &y[i], &r[i]);

    if (n == 1) {
      res = r[0];
    } else if (n == 2) {
      res = r[0] > r[1] ? r[0] : r[1];
    } else {
      res = INT_MAX;
      FOR(i, 3) {
        int f1 = d[i][0];
        int f2 = d[i][1];
        int f3 = d[i][2];
        double xdif = x[f1] - x[f2];
        double ydif = y[f1] - y[f2];
        double cur = (sqrt(xdif * xdif + ydif * ydif) + r[f1] + r[f2]) / 2;
        if (r[f3] > cur) cur = r[f3];
        if (cur < res) res = cur;
      }

    }
    printf("Case #%d: %.7lf\n", c, res);
  }
}

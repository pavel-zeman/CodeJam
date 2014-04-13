#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int n, m;
int x2, y2, x3, y3;
long long a;

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %d %lld", &n, &m, &a);
    n++;
    m++;

    x2 = -1;
    FORE(i, 1, n) FOR(j, m) FOR(k, n) {
      long long t = a + j * k;
      if (t % i == 0) {
        long long l = t / i;
        if (l >=0 && l < m) {
          x2 = i;
          y2 = j;
          x3 = k;
          y3 = l;
          goto end;
        }
      }
      t = -a + j * k;
      if (t % i ==0) {
        long long l = t / i;
        if (l >=0 && l < m) {
          x2 = i;
          y2 = j;
          x3 = k;
          y3 = l;
          goto end;
        }
      }
    }

    FOR(j, m) FOR(k, n) {
      long long t = j * k;
      if (t == a) {
        x2 = 0;
        y2 = j;
        x3 = k;
        y3 = 0;
        goto end;
      }
    }


    end:

    printf("Case #%d: ", c);
    if (x2 == -1)
      printf("IMPOSSIBLE\n");
    else {
      double a1 = sqrt(x2 * x2 + y2 * y2);
      double a2 = sqrt(x3 * x3 + y3 * y3);
      double a3 = sqrt((x2 - x3)*(x2 - x3) + (y2 - y3) * (y2 - y3));
      double s = (a1 + a2 + a3) / 2;
      double S = sqrt(s * (s - a1) * (s - a2) * (s - a3)) * 2;
      //printf("%f %lld\n", S, a);
      assert(a >= S - 0.1 && a <= S + 0.1);

      assert(abs(x2 * y3 - x3 * y2) == a);
      assert(x2 >= 0 && x2 < n);
      assert(x3 >= 0 && x3 < n);
      assert(y2 >= 0 && y2 < m);
      assert(y3 >= 0 && y3 < m);
      printf("0 0 %d %d %d %d\n", x2, y2, x3, y3);
    }
  }
}

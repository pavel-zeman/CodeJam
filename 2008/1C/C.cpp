#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define M 1000000007

int n, m, x, y, z;
int a[500000];

int values[500000];

int total[500000];

struct {
  int left, right;
  int total;
} treeItem[500000];

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %d %d %d %d", &n, &m, &x, &y, &z);
    FOR(i, m) scanf("%d", &a[i]);

    FOR(i, n) {
      values[i] = a[i % m];
      //printf("%d ", values[i]);
      a[i % m] = (((long long)x) * a[i % m] + ((long long)y) * (i + 1)) % z;
    }

    total[0] = 1;
    treeItem[0].total = 1;

    //printf("\n");

    FORE(i, 1, n) {
      long long t = 1;
      for(int j=i-1;j>=0;j--) {
        if (values[j] < values[i])
          t += total[j];
        else if (values[j] == values[i]) {
          t += total[j] - 1;
          break;
        }
      }
      total[i] = t % M;
      //printf("%d ", total[i]);
    }

    //printf("\n");
    long long t = 0;
    FOR(i, n) t += total[i];

    printf("Case #%d: %lld\n", c, t % M);
  }
}

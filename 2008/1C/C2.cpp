#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define M 1000000007
#define T 500002

int n, m, x, y, z;

int a[T];
int values[T];
int order[T], pos[T];
int tree[T];


int read(int where) {
  int sum = 0;
  while (where > 0) {
    sum = (sum + tree[where - 1]) % M;
    where -= where & -where;
  }
  return sum;
}

void update(int where, int value) {
  while (where <= n) {
    tree[where - 1] = (tree[where - 1] + value) % M;
    where += where & -where;
  }
}

int compare(const void *a, const void *b) {
  if (values[*(int *)a] != values[*(int *)b])
    return values[*(int *)a] - values[*(int *)b];
  else
    return *(int *)b - *(int *)a;
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %d %d %d %d", &n, &m, &x, &y, &z);
    FOR(i, m) scanf("%d", &a[i]);

    FOR(i, n) {
      values[i] = a[i % m];
      a[i % m] = (((long long)x) * a[i % m] + ((long long)y) * (i + 1)) % z;
    }

    FOR(i, n) { order[i] = i; tree[i] = 0; }
    qsort(order, n, sizeof(order[0]), compare);
    FOR(i, n) pos[order[i]] = i + 1;

    FOR(i, n) update(pos[i], (read(pos[i]) + 1) % M);

    printf("Case #%d: %d\n", c, read(n));
  }
}

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int coins[200][200];

int p, q;
int cells[200];


int compare(const int *a, const int * b) {
  return *a - *b;
}


int solve(int a, int b) {
  if (coins[a][b] >= 0) return coins[a][b];
  if (a + 1 == b) {
    return (coins[a][b] = 0);
  } else {
    int min = INT_MAX;
    FORE(i, a + 1, b) {
      int x = solve(a, i) + solve(i, b) + cells[b] - cells[a] - 2;
      if (x < min) min = x;
    }
    return (coins[a][b] = min);
  }
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %d", &p, &q);
    FOR(i, q) scanf("%d", &cells[i + 1]);
    cells[0] = 0;
    cells[q + 1] = p + 1;
    qsort(cells, q + 2, sizeof(int), (int (*)(const void *, const void *))compare);

    FOR(i, q + 2) FORE(j, i + 1, q + 2) coins[i][j] = -1;
    solve(0, q + 1);

    printf("Case #%d: %d\n", c, coins[0][q + 1]);
  }
}

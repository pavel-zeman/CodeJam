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

int w, h;
int r;
int rx[10];
int ry[10];

int ways[100][100];


bool isRock(int x, int y) {
  FOR(i, r) if (rx[i] - 1 == x && ry[i] - 1 == y) return true;
  return false;
}

int solve(int x, int y) {
  if (x >= h || y >= w || isRock(x, y)) return 0;
  if (ways[x][y] != -1) return ways[x][y];
  if (x == h - 1 && y == w - 1) return 1;
  return (ways[x][y] = (solve(x + 2, y + 1) + solve(x + 1, y + 2)) % MOD);
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %d %d", &h, &w, &r);
    FOR(i, r) scanf("%d %d", &rx[i], &ry[i]);
    FOR(i, h) FOR(j, w) ways[i][j] = -1;

    int total = solve(0, 0);

    printf("Case #%d: %d\n", c, total);
  }
}

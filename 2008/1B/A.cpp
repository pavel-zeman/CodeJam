#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


long long n, A, B, C, D, x0, y0, M;

int trees[3][3];

int pos[3];

long long total;

void solve(long long res, int last, int level, int remx, int remy) {
  if (level == 3) {
    if ((remx % 3) == 0 && (remy % 3) == 0) {
      int div = (pos[0] == pos[1] && pos[1] == pos[2] ? 6 : (pos[0] == pos[1] || pos[1] == pos[2] || pos[0] == pos[2] ? 2 : 1));
      total += res / div;
      //FOR(i, 3) printf("%d %d\n", pos1[i], pos2[i]);
    }
  } else {
    FOR(i, 3) FOR(j, 3) {
      if (i + j * 3 >= last && trees[i][j] > 0) {
        long long resLocal = res * trees[i][j];
        trees[i][j]--;
        pos[level] = i + j * 3;
        solve(resLocal, i + j * 3, level + 1, remx + i, remy + j);
        trees[i][j]++;
      }
    }
  }

}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%lld %lld %lld %lld %lld %lld %lld %lld", &n, &A, &B, &C, &D, &x0, &y0, &M);
    FOR(i, 3) FOR(j, 3) trees[i][j] = 0;

    FOR(i, n) {
      int x = x0 % 3;
      int y = y0 % 3;
      trees[x][y]++;
      x0 = (A*x0 + B) % M;
      y0 = (C*y0 + D) % M;
    }

    //FOR(i, 3) FOR(j, 3) printf("%d ", trees[i][j]);

    total = 0;
    solve(1, 0, 0, 0, 0);


    printf("Case #%d: %lld\n", c, total);
  }
}

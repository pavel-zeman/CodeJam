#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define WHITE 1
#define BLACK 2
#define UNKNOWN 3

char results[1001][1001];


int max(int a, int b) {
  return a > b ? a : b;
}

int compute(int w, int b) {

  if (results[w][b] != 0) return results[w][b];
  int res1 = 0, res2 = 0, res3 = 0;

  if (w >= 2) res1 = compute(w - 1, b);
  if (b >= 2) res2 = compute(w + 1, b - 2);
  if (w >= 1 && b >= 1) res3 = compute(w - 1, b);

  int m = max(max(res1, res2), res3);
  if ((res1 == 0 || res1 == m) && (res2 == 0 || res2 == m) && (res3 == 0 || res3 == m)) {
    results[w][b] = m;
    return m;
  }
  results[w][b] = UNKNOWN;
  return UNKNOWN;
}

int main(void) {
  int cases;
  int w, b;

  scanf("%d", &cases);

  results[0][1] = BLACK;
  results[1][0] = WHITE;

  /*for(int i=1;i<10;i++) {
    for(int j=1;j<10;j++) {
      compute(i, j);
      printf("%d ", results[i][j]);
    }
    printf("\n");
  }*/


  for(int c=1;c<=cases;c++) {
    scanf("%d %d", &w, &b);
    //compute(w, b);

    //printf("Case #%d: %s\n", c, results[w][b] == WHITE ? "WHITE" : (results[w][b] == BLACK ? "BLACK" : "UNKNOWN"));
    printf("Case #%d: %s\n", c, (b & 1) == 1 ? "BLACK" : "WHITE");
  }
}

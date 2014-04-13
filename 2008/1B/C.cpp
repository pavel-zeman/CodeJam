#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int k;
int n;
int indices[200];
int deck[10000];

int next(int pos) {
  do {
    if (++pos == k) pos = 0;
  } while (deck[pos] != 0);
  return pos;
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %d", &k, &n);
    FOR(i, n) scanf("%d", &indices[i]);

    FOR(i, k) deck[i] = 0;

    int pos = k - 1;
    FOR(i, k) {
      int c = i + 1;
      while (c--) {
        pos = next(pos);
      }
      deck[pos] = i + 1;
    }

    printf("Case #%d:", c);
    FOR(i, n) printf(" %d", deck[indices[i] - 1]);
    printf("\n");
  }
}

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int c;
int i;
int p[3000];

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int cas=1;cas<=cases;cas++) {
    scanf("%d %d", &c, &i);
    for(int x=0;x<i;x++)
      scanf("%d", p + x);

    for(int x=0;x<i;x++)
      for(int y=x + 1;y<i;y++)
        if (p[x] + p[y] == c) {
          printf("Case #%d: %d %d\n", cas, x + 1, y + 1);
        }
  }
}

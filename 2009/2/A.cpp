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

char line[100];
char pos[100];

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d", &n);
    FOR(i, n) {
      scanf("%s", line);
      int j = n - 1;
      while (j >= 0 && line[j] == '0') j--;
      j++;
      pos[i] = j;
    }

    int total = 0;

    FOR(i, n) {
      if (pos[i] > i + 1) {
        int j = i + 1;
        while (pos[j] > i + 1) j++;
        assert(j < n);
        total += j - i;

        int x = pos[j];
        for(int k = j;k>i;k--) pos[k] = pos[k - 1];
        pos[i] = x;
      }
    }

    printf("Case #%d: %d\n", c, total);
  }
}

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define LINE 500
#define WL 19
#define MOD 10000

char line[LINE + 1];

char *welcome = "welcome to code jam";
int count[WL][LINE];

int main(void) {
  int cases;
  gets(line);
  cases = atol(line);
  for(int cas=1;cas<=cases;cas++) {
    gets(line);
    int length = strlen(line);

    for(int i=0;i<WL - 1;i++)
      count[i][length - 1] = 0;

    int c = 0;
    for(int i=length - 1;i>=0;i--) {
      if (line[i] == 'm') c++;
      count[WL - 1][i] = c;
    }

    for(int i=length - 2;i>=0;i--) {
      for(int j=WL - 2;j>=0;j--) {
        c = count[j][i + 1];
        if (line[i] == welcome[j]) c += count[j + 1][i + 1];
        count[j][i] = c % MOD;
      }
    }
    printf("Case #%d: %04d\n", cas, count[0][0]);
  }
}

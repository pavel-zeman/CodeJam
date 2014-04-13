#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define M 1001
#define MOD 210
#define PLUS 0
#define MINUS 1


// position of last sign, sign, modulo
long long last[M][2][MOD];
long long curr[M][2][MOD];

char input[M + 1];
int length;

int digits[M];

char isUgly(int i) {
  return i % 2 == 0 || i % 3 == 0 || i % 5 == 0 || i % 7 == 0;
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%s", input);
    length = strlen(input);

    FOR(i, length) digits[i] = input[i] - '0';
    FOR(j, 2) FOR(k, MOD) last[0][j][k] = 0;
    last[0][PLUS][digits[0]] = 1;

    FORE(d, 1, length) {
      FOR(i, d + 1) FOR(j, 2) FOR(k, MOD) curr[i][j][k] = 0;
      FOR(i, d) {
        int total = 0;
        FORE(j, i, d) total = (total * 10 + digits[j]) % MOD;
        FOR(j, 2) FOR(k, MOD) {
          if (last[i][j][k] > 0) {
            curr[d][PLUS][(k + digits[d])%MOD] += last[i][j][k];
            curr[d][MINUS][(k - digits[d] + MOD)%MOD] += last[i][j][k];
            if (j == PLUS) {
              curr[i][j][(k - total + total * 10 + digits[d])%MOD] += last[i][j][k];
            } else {
              curr[i][j][((k + total - total * 10 - digits[d])%MOD + MOD)%MOD] += last[i][j][k];
            }
          }
        }
      }
      FOR(i, d + 1) FOR(j, 2) FOR(k, MOD) last[i][j][k] = curr[i][j][k];
    }

    long long total = 0;
    FOR(i, MOD) {
      if (isUgly(i)) {
        FOR(j, 2) FOR(k, length) total += last[k][j][i];
      }
    }

    printf("Case #%d: %lld\n", c, total);
  }
}

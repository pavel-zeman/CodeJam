#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define S 50000
#define K 16

int k;
int minLength;

char data[S+1];
int length;

int lastFirst[K][K];
int neigh[K][K];

// first, last, used
int cache[K][K][(1<<K)];

int min(int a, int b) {
  return a < b ? a : b;
}

int max(int a, int b) {
  return a < b ? b : a;
}

int best(int first, int last, int used) {
  if (used == (1<<k) - 1) return neigh[first][last];
  if (cache[first][last][used] != -1) return cache[first][last][used];
  int res = 0;
  FOR(i, k)
    if ((used & (1<<i)) == 0) {
      res = max(res, best(i, last, used | (1<<i)) + neigh[first][i]);
    }
  return (cache[first][last][used] = res);
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %s", &k, data);
    minLength = length = strlen(data);
    FOR(i, k) FOR(j, k) lastFirst[i][j] = neigh[i][j] = 0;
    assert(length % k == 0);
    for(int i=0;i<length;i+=k) {
      FOR(j, k) FORE(l, j + 1, k) {
        if (data[i + j] == data[i + l]) {
          neigh[j][l]++; neigh[l][j]++;
        }
        if (i < length - k && data[i + j] == data[i + k + l]) lastFirst[j][l]++;
        if (i < length - k && data[i + k + j] == data[i + l]) lastFirst[l][j]++;
      }
    }


    FOR(i, k) FOR(j, k) FOR(l, (1<<k)) cache[i][j][l] = -1;
    FOR(i, k) FOR(j, k) if (i != j) {
      minLength = min(minLength, length - best(i, j, (1<<i) | (1<<j)) - lastFirst[j][i]);
    }

    printf("Case #%d: %d\n", c, minLength);
  }
}

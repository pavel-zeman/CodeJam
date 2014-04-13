#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int fa[15], fb[15];
int k, n;
int invalid;

int path[300];
bool used[300];


bool isOk(int a, int b) {
  FOR(i, k)
    if (fa[i] == a && fb[i] == b || fa[i] == b && fb[i] == a) return false;

  return true;
}

void generate(int u) {
  if (u < n) {
    FOR(i, n) {
      if (!used[i]) {
        path[u] = i;
        used[i] = true;
        generate(u + 1);
        used[i] = false;
      }
    }
  } else {
    FOR(i, n - 1)
      if (!isOk(path[i], path[i + 1])) {
        invalid++;
        return;
      }
    if (!isOk(path[0], path[n - 1])) invalid++;
  }
}

int fact(int a) {
  int r = 1;
  while (a) r *= a--;
  return r;
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  used[0] = true;
  path[0] = 0;
  for(int c=1;c<=cases;c++) {
    scanf("%d %d", &n, &k);
    FOR(i, k) scanf("%d %d", &fa[i], &fb[i]);
    FOR(i, k) { fa[i]--; fb[i]--;}
    invalid = 0;
    generate(1);

    printf("Case #%d: %d\n", c, (fact(n - 1)/2 - invalid/2)%9901);
  }
}

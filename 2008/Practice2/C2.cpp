#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MOD 9901

int fa[15], fb[15];
int k, n;
int invalid;

int fact[301];

int path[300];
int set[300];


void generateFact() {
  int f = 1;
  fact[0] = 1;
  FORE(i, 1, 301) {
    f *= i;
    f %= MOD;
    fact[i] = f;
  }
}


int sign(int count) {
  return (count & 1) == 1 ? 1 : -1;
}

int root(int pos) {
  while (set[pos] != pos) pos = set[pos];
  return pos;
}

void connect(int a, int b) {
  int ra = root(a);
  int rb = root(b);
  set[rb] = ra;
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  generateFact();

  for(int c=1;c<=cases;c++) {
    scanf("%d %d", &n, &k);
    FOR(i, k) {
      scanf("%d %d", &fa[i], &fb[i]);
      fa[i]--;
      fb[i]--;
    }

    invalid = 0;
    FORE(i, 1, 1<<k) {
      int edges = 0;
      int edgeNumbers[15];
      int curr = i;
      int pos = 0;
      int countUsed[300];
      while (curr > 0) {
        if ((curr & 1) == 1) {
          edgeNumbers[edges++] = pos;
        }
        curr >>= 1;
        pos++;
      }
      bool ok = true;
      bool cycle = false;
      FOR(j, n) { countUsed[j] = 0; set[j] = j; }
      FOR(j, edges) {
        if (root(fa[edgeNumbers[j]]) == root(fb[edgeNumbers[j]])) cycle = true;

        if (countUsed[fa[edgeNumbers[j]]] >= 2) {
          ok = false;
          break;
        } else
          countUsed[fa[edgeNumbers[j]]]++;

        if (countUsed[fb[edgeNumbers[j]]] >= 2) {
          ok = false;
          break;
        } else
          countUsed[fb[edgeNumbers[j]]]++;
        connect(fa[edgeNumbers[j]], fb[edgeNumbers[j]]);
      }
      if (cycle && edges < n) ok = false;
      if (cycle && edges == n) {
        int firstRoot = root(0);
        FORE(j, 1, n) if (root(j) != firstRoot) { ok = false; break; }
      }

      if (ok) {
        int num1s = 0;
        FOR(j, n) if (countUsed[j] == 1) num1s++;
        if (edges == n) invalid += sign(edges) * 2;
        else {
          assert(num1s > 0);
          invalid += sign(edges) * fact[n - edges - 1] * (1 << (num1s/2));
        }
        invalid = ((invalid % MOD) + MOD) % MOD;

      }
    }

    printf("Case #%d: %d\n", c, (((fact[n - 1] - invalid) * 4951) % MOD + MOD) % MOD);
  }
}

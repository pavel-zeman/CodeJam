#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include <queue>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define N 500

#define EMPTY -1
#define USED -2
#define MOD 1000000009

using namespace std;

int n, k;
int edge[N][N];
long long total;

int totalColors;
queue<int> searchQueue;

bool usedColors[N];
int usedColorCount;

void countColors(int vertex, int from, int level) {
  FOR(i, n)
    if (edge[vertex][i] >= 0 && i != from) {
      if (!usedColors[edge[vertex][i]]) {
        usedColors[edge[vertex][i]] = true;
        usedColorCount++;
      }
      if (level == 2) countColors(i, vertex, level - 1);
    }
}

void search(int vertex) {
  FOR(i, n) {
    if (edge[vertex][i] == USED) {
      FOR(j, totalColors) usedColors[j] = false;
      usedColorCount = 0;
      countColors(vertex, vertex, 2);

      assert(usedColorCount <= totalColors);
      assert(totalColors <= k);
      int foundColor = -1;
      if (usedColorCount == totalColors) {
        foundColor = totalColors++;
      } else {
        FOR(j, totalColors)
          if (usedColors[j] == false) {
            foundColor = j;
            break;
          }
      }
      assert(foundColor >= 0);
      edge[vertex][i] = edge[i][vertex] = foundColor;
      if (k <= usedColorCount) {
        total = 0;
        return;
      }
      //printf("Edge %d %d %d\n", vertex + 1, i + 1, k - usedColorCount);

      total *= k - usedColorCount;
      total %= MOD;
      if (total == 0) return;

      searchQueue.push(i);
    }
  }
}

int main(void) {
  int cases;
  scanf("%d", &cases);

  for(int c=1;c<=cases;c++) {
    FOR(i, N) FOR(j, N) edge[i][j] = EMPTY;
    scanf("%d %d", &n, &k);
    FOR(i, (n-1)) {
      int x, y;
      scanf("%d %d", &x, &y);
      edge[x - 1][y - 1] = edge[y - 1][x - 1] = USED;
    }

    total = 1;
    totalColors = 0;

    searchQueue.push(0);

    while (!searchQueue.empty() && total != 0) {
      search(searchQueue.front());
      searchQueue.pop();
    }

    while (!searchQueue.empty()) searchQueue.pop();

    printf("Case #%d: %lld\n", c, total);
  }
}

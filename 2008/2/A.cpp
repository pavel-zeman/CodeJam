#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define AND 1
#define OR 0

#define M 30000

#define MAX 1000000

int m;
int v;
int interior;
int values[M];

int changeable[M];
int function[M];

int compute(int pos) {
  if (pos >= interior) return values[pos]; else {
    int a = compute(2*(pos + 1) - 1);
    int b = compute(2*(pos + 1));
    values[pos] = function[pos] == AND ? a & b : a | b;
    return values[pos];
  }
}

int min(int a, int b) {
  return a < b ? a : b;
}

int min(int a, int b, int c) {
  return a < b ? a : b;
}


int findMin(int pos, int value) {
  if (value == values[pos]) return 0;
  if (pos >= interior) return MAX;
  int aPos = 2*(pos + 1) - 1;
  int bPos = 2*(pos + 1);

  if (!changeable[pos]) {
    if (function[pos] == AND) {
      if (value == 1) return findMin(aPos, 1) + findMin(bPos, 1);
      else return min(findMin(aPos, 0), findMin(bPos, 0));
    } else {
      if (value == 1) return min(findMin(aPos, 1), findMin(bPos, 1));
      else return findMin(aPos, 0) + findMin(bPos, 0);
    }
  }

  if (function[pos] == AND) {
    if (value == 1) {
      return min(findMin(aPos, 1) + findMin(bPos, 1), min(findMin(aPos, 1), findMin(bPos, 1)) + 1);
    } else {
      return min(findMin(aPos, 0), findMin(bPos, 0));
    }
  } else {
    if (value == 1) {
      return min(findMin(aPos, 1), findMin(bPos, 1));
    } else {
      return min(findMin(aPos, 0) + findMin(bPos, 0), min(findMin(aPos, 0), findMin(bPos, 0)) + 1);
    }
  }
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %d", &m, &v);
    interior = (m-1)/2;
    FOR(i, interior) scanf("%d %d", &function[i], &changeable[i]);
    FORE(i, interior, m) scanf("%d", &values[i]);

    compute(0);
    int r = findMin(0, v);
    printf("Case #%d: ", c);

    if (r >= MAX) printf("IMPOSSIBLE\n"); else printf("%d\n", r);
  }
}

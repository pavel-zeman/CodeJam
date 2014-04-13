#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

struct {
  char name[100];
  int price;
} products[64];

int numProducts;

int pos[64];
int toRemove[64];

// lowest number of the longest sequence using number 0..I and length J + 1
int A[65][65];

int min(int a, int b) {
  return a < b ? a : b;
}

int longest(int * items, int count) {
  A[0][0] = items[0];
  A[0][1] = -1;
  FORE(i, 1, count) {
    A[i][0] = min(A[i-1][0], items[i]);
    FORE(j, 1, i+1) {
      if (A[i-1][j-1] == -1) A[i][j] = -1; else
      if (items[i] > A[i-1][j-1]) {
         if (A[i-1][j] == -1) A[i][j] = items[i];
         else A[i][j] = min(A[i-1][j], items[i]);
      } else A[i][j] = A[i-1][j];
    }
    A[i][i+1] = -1;
  }
  int i = count - 1;
  while (A[count-1][i] == -1) i--;
  return i + 1;
}


int main(void) {
  int cases;
  int prices[64];
  scanf("%d", &cases);
  FOR(c,cases) {
    numProducts = 0;

    // read products
    scanf("%s", products[numProducts].name);
    while (!isdigit(products[numProducts].name[0])) {
      numProducts++;
      scanf("%s", products[numProducts].name);
    }

    // read prices
    products[0].price = atoi(products[numProducts].name);
    FORE(i, 1, numProducts) scanf("%d", &products[i].price);

    FOR(i, numProducts) prices[i] = products[i].price;
    FOR(i, numProducts) pos[i] = i;
    FOR(i, numProducts - 1) FORE(j, i + 1, numProducts)
      if (strcmp(products[pos[i]].name, products[pos[j]].name) > 0) {
        int x = pos[i];
        pos[i] = pos[j];
        pos[j] = x;
      }

    int l = longest(prices, numProducts);
    int lastPos = 0;
    FOR(i, numProducts - l) {
      int copy[64];
      s: assert(lastPos < numProducts);
      int p = 0;
      FOR(j, numProducts) {
        if (pos[lastPos] == j) continue;
        char found = 0;
        FOR(k, i) if (j == toRemove[k]) { found = 1; break; }
        if (!found) copy[p++] = prices[j];
      }

      int l2 = longest(copy, numProducts - i - 1);
      if (l2 == l) {
        toRemove[i] = pos[lastPos++];
      } else {
        lastPos++;
        goto s;
      }
    }

    printf("Case #%d:", c + 1);
    FOR(i, numProducts - l) printf(" %s", products[toRemove[i]].name);
    printf("\n");
  }
}

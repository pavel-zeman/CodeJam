#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define M 1000000007

int n, m, x, y, z;
int a[500000];

int values[500000];

int total[500000];

struct {
  int left, right;
  int total;
  int self;
  int rmax;
} treeItem[500000];


int lmax;

long long getTotal(int value, int pos) {
  long long t = 0;
  if (values[pos] < value) {
    if (treeItem[pos].left != -1) t += treeItem[treeItem[pos].left].total;
    t += treeItem[pos].self;
    if (treeItem[pos].right != -1) t += getTotal(value, treeItem[pos].right);
  } else {
    if (treeItem[pos].left != -1) t += getTotal(value, treeItem[pos].left);
  }
  return t;
}

void addItem(int value, int pos, int total, int current, int level = 0) {
  if (value > values[pos]) {
    if (treeItem[pos].right == -1) {
      treeItem[pos].right = current;
      if (value > treeItem[pos].rmax) treeItem[pos].rmax = value;
    } else {
      addItem(value, treeItem[pos].right, total, current, level + 1);
      if (treeItem[treeItem[pos].right].rmax > treeItem[pos].rmax)
        treeItem[pos].rmax = treeItem[treeItem[pos].right].rmax;
    }
  } else {
    if (treeItem[pos].left == -1) {
      treeItem[pos].left = current;
    } else
      addItem(value, treeItem[pos].left, total, current, level + 1);
  }
  if (level > lmax) lmax = level;
  treeItem[pos].total += total;
  if (treeItem[pos].total >= M) treeItem[pos].total -= M;
}

void printTree(int level, int pos) {
  FOR(i, 3*level) printf(" ");
  if (pos == -1) {
    printf("-\n");
  } else {
    printf("%d %d %d\n", values[pos], treeItem[pos].self, treeItem[pos].total);
    printTree(level + 1, treeItem[pos].right);
    printTree(level + 1, treeItem[pos].left);
  }
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %d %d %d %d", &n, &m, &x, &y, &z);
    FOR(i, m) scanf("%d", &a[i]);

    FOR(i, n) {
      values[i] = a[i % m];
      //printf("%d ", values[i]);
      a[i % m] = (((long long)x) * a[i % m] + ((long long)y) * (i + 1)) % z;
    }

    total[0] = 1;
    treeItem[0].total = treeItem[0].self = 1;
    treeItem[0].left = treeItem[0].right = -1;
    treeItem[0].rmax = values[0];
    lmax = 0;

    //printf("\n");

    //FOR(i, n) printf("%d ", values[i]);
    //printf("\n");

    FORE(i, 1, n) {
      long long t = getTotal(values[i], 0) + 1;
      treeItem[i].left = treeItem[i].right = -1;
      treeItem[i].total = treeItem[i].self = t % M;
      treeItem[i].rmax = values[i];
      addItem(values[i], 0, t % M, i);
    }

    //printTree(0, 0);

    //long long t = 0;
    //FOR(i, n) t += total[i];

    printf("Case #%d: %d %d\n", c, treeItem[0].total, lmax);
  }
}

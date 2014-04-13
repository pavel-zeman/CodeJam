#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define OK 1
#define BROKEN 2
#define USED 1
#define CHAIR 3

int dy, dx;

char chairs[100][100];

int pos[1<<20][20];

bool isSet(int data, int bit) {
  return (data & (1 << bit)) != 0;
}

bool checkRow(int row, int data, int dataPrev, int count) {
  FOR(i, count) if (isSet(data, i) && chairs[i][row] != OK) return false;
  FOR(i, count)
    if (isSet(data, i)) {
       if (i > 0 && isSet(data, i - 1) || i < count - 1 && isSet(data, i + 1)) return false;
       if (i > 0 && isSet(dataPrev, i - 1) || i < count - 1 && isSet(dataPrev, i + 1)) return false;
    }
  return true;
}

int numBits(int data) {
  int bits = 0;
  while (data > 0) {
    if ((data & 1) != 0) bits++;
    data >>= 1;
  }
  return bits;
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %d", &dy, &dx);
    FOR(i, dy) {
      char s[200];
      scanf("%s", s);
      FOR(j, dx)
        chairs[j][i] = s[j] == '.' ? OK : BROKEN;
    }

    FOR(i, 1<<dx) {
      pos[i][0] = checkRow(0, i, 0, dx) ? numBits(i) : 0;
    }
    FORE(i, 1, dy) {
      FOR(j, 1<<dx) {
        pos[j][i] = 0;
        if (checkRow(i, j, 0, dx)) {
          int max = 0;
          FOR(k, 1<<dx) if (checkRow(i, j, k, dx) && pos[k][i - 1] > max) {
            max = pos[k][i - 1];
          }
          if (max > 0) pos[j][i] = max + numBits(j);
        }
      }
    }

    int maxTotal = 0;
    FOR(i, 1<<dx) if (pos[i][dy - 1] > maxTotal) maxTotal = pos[i][dy - 1];

    printf("Case #%d: %d\n", c, maxTotal);
  }
  return 0;
}

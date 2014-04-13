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

int m, n;

char chairs[100][100];
char used[100][100];

char getUsed(int i, int j) {
  return i >= 0 && j >=0 && i < m && j < n ? used[i][j] : 0;
}

char isUsed(int i, int j) {
  return i >= 0 && j >=0 && i < m && j < n && used[i][j] || i < 0 || j < 0 || i >= m || j >= n;
}

int countUsed(int i, int j) {
  return isUsed(i, j - 1) + isUsed(i, j + 1) + isUsed(i - 1, j - 1) + isUsed(i - 1, j + 1);
}

void setUsedChair(int i, int j, int type = USED) {
  if (i >= 0 && j >=0 && i < m && j < n && !used[i][j]) used[i][j] = type;
}

void setUsed(int i, int j) {
  setUsedChair(i, j, CHAIR);
  setUsedChair(i, j - 1);
  setUsedChair(i, j + 1);
  setUsedChair(i - 1, j - 1);
  setUsedChair(i - 1, j + 1);
}


bool isPossible(int i, int j) {
  return getUsed(i, j - 1) != CHAIR && getUsed(i, j + 1) != CHAIR && getUsed(i - 1, j - 1) != CHAIR && getUsed(i - 1, j + 1) != CHAIR;
}


bool getNext() {
  int y = - 1, x = -1;
  int maxCount = -1;
  FOR(i, m) FOR(j, n) {
    if (!used[i][j] && isPossible(i, j)) {
       int a = countUsed(i, j);
       if (a > maxCount) {
         //printf("Setting max: %d %d %d\n", j, i, a);
         maxCount = a;
         y = i;
         x = j;
       }
    }
  }

  if (y != -1) {
    //printf("%d %d %d\n", x, y, maxCount);
    setUsed(y, x);
    return true;
  } else
    return false;
}


int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %d", &m, &n);
    FOR(i, m) FOR(j, n) used[i][j] = 0;
    FOR(i, m) {
      char s[200];
      scanf("%s", s);
      FOR(j, n) {
        chairs[i][j] = s[j] == '.' ? OK : BROKEN;
        if (s[j] != '.') used[i][j] = 2;
      }
    }

    //printf("%d\n", used[0][4]);

    int maxTotal = 0;

    FOR(i, m) FOR(j, n) {
      if (used[i][j] != 2) {
        FOR(a, m) FOR(b, n) if (used[a][b] == 1) used[a][b] = 0;
        int total = 1;
        setUsed(i, j);
        while (getNext()) total++;
        if (total > maxTotal) maxTotal = total;
        //printf("%d\n", total);
      }
    }


    printf("Case #%d: %d\n", c, maxTotal);
  }
}

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define STAR 1
#define PRIME 2

int C[100][100];
int C1[100][100];

int M[100][100];
char rowCoverage[100], colCoverage[100];

int items;

int positions[100];
int values[100];

int rowMin[100], rowMax[100];

struct point {
  int row;
  int column;
} finalPosition[100];

void print(void) {
  return;
  FOR(i, items) {
    FOR(j, items)
      printf("%d%c ", C[i][j], M[i][j] == STAR ? '*' : (M[i][j] == PRIME ? '\'' : ' '));
    printf("\n");
  }
  printf("\n");
}


void munkres(void) {
  // step 1 - subtract minimum from each item
  print();
  FOR(i, items) {
    int min = C[i][0];
    FORE(j, 1, items) if (C[i][j] < min) min = C[i][j];
    FOR(j, items) C[i][j] -= min;
  }

  // step 2
  print();
  FOR(i, items) FOR(j, items) M[i][j] = 0;
  FOR(i, items) rowCoverage[i] = colCoverage[i] = 0;

  FOR(i, items) FOR(j, items)
    if (C[i][j] == 0 && !rowCoverage[i] && !colCoverage[j]) {
      M[i][j] = STAR;
      rowCoverage[i] = colCoverage[j] = 1;
    }

  FOR(i, items) rowCoverage[i] = colCoverage[i] = 0;

  // step 3
  step3:
  print();
  int covered = 0;
  FOR(j, items) FOR(i, items)
    if (M[i][j] == STAR) {
      colCoverage[j] = 1;
      covered++;
      break;
    }

  if (covered == items) return;

  // step 4
  step4:
  print();

  struct {
    int x;
    int y;
  } path[200];
  int pathLength = 1;

  FOR(i, items) FOR(j, items)
    if (C[i][j] == 0 && !rowCoverage[i] && !colCoverage[j]) {
      M[i][j] = PRIME;
      int starX = -1;
      FOR(k, items) if (M[i][k] == STAR) {
        starX = k;
        break;
      }
      if (starX >= 0) {
        rowCoverage[i] = 1;
        colCoverage[starX] = 0;
        goto step4;
      } else {
        // no star found
        path[0].x = j;
        path[0].y = i;
        goto step5;
      }
    }
  // no zeros left - goto 6
  goto step6;

  step5:
  print();
  while (1) {
    // find star in column
    int starRow = -1;
    FOR(i, items)
      if (M[i][path[pathLength - 1].x] == STAR) {
         starRow = i;
         break;
      }
    if (starRow >= 0) {
      path[pathLength].x = path[pathLength - 1].x;
      path[pathLength].y = starRow;
      pathLength++;
    } else
      break;

    // find prime in row
    int primeColumn = -1;
    FOR(i, items)
      if (M[path[pathLength-1].y][i] == PRIME) {
        primeColumn = i;
        break;
      }
    path[pathLength].x = primeColumn;
    path[pathLength].y = path[pathLength - 1].y;
    pathLength++;
  }

  FOR(i, pathLength)
    M[path[i].y][path[i].x] = M[path[i].y][path[i].x] == STAR ? 0 : STAR;
  FOR(i, items) rowCoverage[i] = colCoverage[i] = 0;
  FOR(i, items) FOR(j, items) if (M[i][j] == PRIME) M[i][j] = 0;
  goto step3;

  step6:
  print();
  int min = INT_MAX;
  FOR(i, items) FOR(j, items)
    if (!rowCoverage[i] && !colCoverage[j] && C[i][j] < min)
      min = C[i][j];

  FOR(i, items) FOR(j, items) {
    if (rowCoverage[i]) C[i][j] += min;
    if (!colCoverage[j]) C[i][j] -= min;
  }

  goto step4;
}


void readLine(int * data) {
  char buffer[1000];
  items = 0;
  // read
  gets(buffer);
  int start = 0, temp = 0;
  while (1) {
    while (buffer[temp] != ' ' && buffer[temp] != 0) temp++;
    if (buffer[temp] == 0) break;
    buffer[temp] = 0;
    data[items++] = atoi(buffer + start);
    start = ++temp;
  }
  data[items++] = atoi(buffer + start);
}

int min(int a, int b) {
  return a > b ? b : a;
}

int getDistance(int x1, int y1, int x2, int y2) {
  int steps = 0;
  if (x1 > x2 && y1 < y2) {
    int m = min(abs(x1 - x2), abs(y1 - y2));
    x1 -= m;
    y1 += m;
    steps += m;
  } else if (x1 < x2 && y1 > y2) {
    int m = min(abs(x1 - x2), abs(y1 - y2));
    x1 += m;
    y1 -= m;
    steps += m;
  }
  return steps + abs(x1 - x2) + abs(y1 - y2);
}

int checkFinalPosition() {
  FOR(i, items) {
    int x = -1, y = -1;
    int pos = positions[i] - 1;
    FOR(j, items) {
      if (pos > rowMax[j] - rowMin[j]) pos -= rowMax[j] - rowMin[j] + 1;
      else {
        y = j;
        x = rowMin[j] + pos;
        break;
      }
    }
    assert(x >= 0);
    assert(y >= 0);

    FOR(j, items) C[i][j] = getDistance(x, y, finalPosition[j].column, finalPosition[j].row) * values[i];
  }

  FOR(i, items) FOR(j, items) C1[i][j] = C[i][j];

  //FOR(i, items) { FOR(j, items) printf("%d ", C[i][j]); printf("\n");}
  //printf("\n");
  munkres();

  int total = 0;

  FOR(i, items) FOR(j, items) if (M[i][j] == STAR) total += C1[i][j];
  return total;
}

int main(void) {
  int cases;
  char temp[100];

  gets(temp);
  cases = atoi(temp);
  for(int c=1;c<=cases;c++) {
    readLine(positions);
    readLine(values);

    // min and max for each row
    FOR(i, items/2 + 1) {
      rowMax[i] = items - 1;
      rowMin[i] = items/2 - i;
    }
    FORE(i, items/2 + 1, items) {
      rowMin[i] = 0;
      rowMax[i] = items - i + items/2 - 1;
    }

    // generate and check positions
    FOR(i, items) { finalPosition[i].row = items/2; finalPosition[i].column = i; }
    int a = checkFinalPosition();
    FOR(i, items) { finalPosition[i].row = i; finalPosition[i].column = items/2; }
    a = min(a, checkFinalPosition());
    FOR(i, items) { finalPosition[i].row = i; finalPosition[i].column = items - 1 - i; }
    a = min(a, checkFinalPosition());

    printf("Case #%d: %d\n", c, a);
  }
}

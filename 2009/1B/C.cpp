#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


#define W 20
#define Q 20
#define S (10)
#define INF 100000
#define V 400

char square[W][W];

char sequence[W][W][V][800];
bool fixed[W][W][V];
int value[W][W][V];
int w, q;

int dirs[16][2][2] = {
  {{-1, 0}, {-1, 1}},
  {{-1, 0}, {-2, 0}},
  {{-1, 0}, {-1, -1}},
  {{0, -1}, {-1, -1}},
  {{0, -1}, {0, -2}},
  {{0, -1}, {1, -1}},
  {{1, 0}, {1, -1}},
  {{1, 0}, {2, 0}},
  {{1, 0}, {1, 1}},
  {{0, 1}, {-1, 1}},
  {{0, 1}, {0, 2}},
  {{0, 1}, {1, 1}},
  {{-1, 0}, {0, 0}},
  {{0, -1}, {0, 0}},
  {{1, 0}, {0, 0}},
  {{0, 1}, {0, 0}}
};

void extend(int i, int j, int k) {
  char seq[800];
  strcpy(seq, sequence[i][j][k]);
  int l = strlen(seq);
  seq[l + 2] = 0;

  FOR(c, 16) {
    int sx = i + dirs[c][0][0];
    int sy = j + dirs[c][0][1];
    int vx = i + dirs[c][1][0];
    int vy = j + dirs[c][1][1];

    if (sx >=0 && sx < w && vx >= 0 && vx < w && sy >= 0 && sy < w && vy >= 0 && vy < w) {
      char s = square[sx][sy];
      char v = square[vx][vy];
      int k2 = s == '+' ? k + v - '0' : k - (v - '0');
      if (k2 >= 0 && k2 < V && !fixed[vx][vy][k2]) {
        if (value[i][j][k] + 1 <= value[vx][vy][k2]) {
          seq[l] = s;
          seq[l + 1] = v;
          if (value[i][j][k] + 1 < value[vx][vy][k2] || value[i][j][k] + 1 == value[vx][vy][k2] && strcmp(seq, sequence[vx][vy][k2]) < 0) {
            value[vx][vy][k2] = value[i][j][k] + 1;
            strcpy(sequence[vx][vy][k2], seq);
          }
        }
      }
    }
  }
}


bool isLess(int i, int j, int k, int v, char *s) {
  return (value[i][j][k] < v || value[i][j][k] == v && strcmp(sequence[i][j][k], s) < 0);
}


int main(void) {
  int cases;
  scanf("%d", &cases);

  for(int c=1;c<=cases;c++) {
    scanf("%d %d", &w, &q);
    FOR(i, w) scanf("%s", square[i]);
    FOR(i, w) FOR(j, w) FOR(k, V) { value[i][j][k] = INF; sequence[i][j][k][0] = 0; fixed[i][j][k] = false; }
    FOR(i, w) {
      FOR(j, w) {
        if (isdigit(square[i][j])) {
          value[i][j][square[i][j] + S - '0'] = 0;
          sequence[i][j][square[i][j] + S - '0'][0] = square[i][j];
          sequence[i][j][square[i][j] + S - '0'][1] = 0;
        }
      }
    }

    printf("Case #%d:\n", c);


    FOR(i, q) {
      int result;
      scanf("%d", &result);

      char emptyS[100] = {0};
      char *minS = emptyS;
      int minV = INF;
      int ci = -1, cj = -1;


      FOR(i, w) FOR(j, w) {
        if (fixed[i][j][result + S] && isLess(i, j, result + S, minV, minS)) {
          ci = i, cj = j;
          minS = sequence[i][j][result + S];
          minV = value[i][j][result + S];
        }
      }

      if (ci == -1) {
        while (true) {
          minV = INF;
          minS = emptyS;
          ci = -1;
          int ck = -1;
          FOR(i, w) FOR(j, w) FOR(k, V) {
            if (!fixed[i][j][k] && isLess(i, j, k, minV, minS)) {
              ci = i;
              cj = j;
              ck = k;
              minS = sequence[i][j][k];
              minV = value[i][j][k];
            }
          }
          fixed[ci][cj][ck] = true;
          extend(ci, cj, ck);

          if (ck == result + S) break;

          assert (ci != -1);

        }
      }
      printf("%s\n", minS);
    }
  }
}

// vyuziti binarni haldy pro vyhledani minima pro dalsi krok Dijkstrova algoritmu

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
#define V 1000

char square[W][W];

char sequence[W][W][V][800];
bool fixed[W][W][V];
int value[W][W][V];
int w, q;

int tree[W * W * V][3];
int treeItems;

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


bool isLess(int v1, char * s1, int v2, char * s2) {
  return v1 < v2 || v1 == v2 && strcmp(s1, s2) < 0;
}


bool isLess(int i, int j, int k, int v, char *s) {
  return isLess(value[i][j][k], sequence[i][j][k], v, s);
}


bool isLess(int i1, int j1, int k1, int i2, int j2, int k2) {
  return isLess(value[i1][j1][k1], sequence[i1][j1][k1], value[i2][j2][k2], sequence[i2][j2][k2]);
}

int parent(int pos) {
  return (pos - 1) >> 1;
}

int child(int pos) {
  return (pos << 1) + 1;
}

void swap(int *a, int *b) {
  int c = *a;
  *a = *b;
  *b = c;
}

void insertTree(int i, int j, int k) {
  int pos = treeItems++;
  tree[pos][0] = i;
  tree[pos][1] = j;
  tree[pos][2] = k;

  while (pos > 0 && isLess(i, j, k, tree[parent(pos)][0], tree[parent(pos)][1], tree[parent(pos)][2])) {
    int p = parent(pos);
    FOR(i, 3) swap(&tree[p][i], &tree[pos][i]);
    pos = p;
  }
  assert(treeItems < (int)(sizeof(value) / sizeof(value[0][0][0])));
}

void removeMin(void) {
  treeItems--;
  FOR(i, 3) tree[0][i] = tree[treeItems][i];

  int pos = 0;
  while (child(pos) < treeItems) {
    int ch = child(pos);
    if (isLess(tree[ch][0], tree[ch][1], tree[ch][2], tree[pos][0], tree[pos][1], tree[pos][2]) ||
      ch + 1 < treeItems && isLess(tree[ch + 1][0], tree[ch + 1][1], tree[ch + 1][2], tree[pos][0], tree[pos][1], tree[pos][2])) {
      int xch = ch;
      if (ch + 1 < treeItems && isLess(tree[ch + 1][0], tree[ch + 1][1], tree[ch + 1][2], tree[ch][0], tree[ch][1], tree[ch][2])) xch++;
      FOR(i, 3) swap(&tree[xch][i], &tree[pos][i]);
      pos = xch;
    } else
      break;
  }
}

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
            insertTree(vx, vy, k2);
          }
        }
      }
    }
  }
}



int main(void) {
  int cases;
  scanf("%d", &cases);

  for(int c=1;c<=cases;c++) {
    scanf("%d %d", &w, &q);
    FOR(i, w) scanf("%s", square[i]);
    FOR(i, w) FOR(j, w) FOR(k, V) { value[i][j][k] = INF; sequence[i][j][k][0] = 0; fixed[i][j][k] = false; }

    treeItems = 0;
    FOR(i, w) {
      FOR(j, w) {
        if (isdigit(square[i][j])) {
          value[i][j][square[i][j] + S - '0'] = 0;
          sequence[i][j][square[i][j] + S - '0'][0] = square[i][j];
          sequence[i][j][square[i][j] + S - '0'][1] = 0;
          insertTree(i, j, square[i][j] + S - '0');
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
          assert (treeItems > 0);
          ci = tree[0][0];
          cj = tree[0][1];
          int ck = tree[0][2];

          if (!fixed[ci][cj][ck]) {

            fixed[ci][cj][ck] = true;
            extend(ci, cj, ck);
          }
          if (ck == result + S) {
            minS = sequence[ci][cj][ck];
            break;
          }
          removeMin();
        }
      }
      printf("%s\n", minS);
    }
  }
}

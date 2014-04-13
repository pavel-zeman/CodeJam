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

int nodes1, nodes2;
int nodes[100][100];


#define MAX_P1 3200
#define MAX_P2 3200
bool g[MAX_P1][MAX_P2];


int maxMatching(int p1, int p2) {
  int match[MAX_P2];
  int prev1[MAX_P1];
  int prev2[MAX_P2];
  int label1[MAX_P1];
  int label2[MAX_P2];
  bool matched1[MAX_P1];

  FOR(i, p2) match[i] = -1;
  FOR(i, p1) matched1[i] = false;

  // start with some matching
  FOR(i, p2)
    FOR(j, p1)
      if (g[j][i] && !matched1[j]) {
        match[i] = j;
        matched1[j] = true;
        break;
      }

  // find augmenting path
  nextround:
  int label = 0;
  bool found = true;
  FOR(i, p2) label2[i] = -1;
  FOR(i, p1) label1[i] = matched1[i] ? -1 : 0;

  while (found) {
    found = false;
    FOR(i, p1) {
      if (label1[i] == label) {
        FOR(j, p2)
          if (g[i][j] && label2[j] == -1) {
            if (match[j] == -1) {
              // got it
              match[j] = i;
              while (label1[i] != 0) {
                i = prev1[i];
                match[i] = prev2[i];
                i = prev2[i];
              }
              matched1[i] = true;
              goto nextround;
            } else {
              prev2[j] = i;
              label2[j] = label + 1;
              found = true;
            }
        }
      }
    }
    label++;

    FOR(i, p2) if (match[i] != -1 && label2[i] == label) {
      prev1[match[i]] = i;
      label1[match[i]] = label + 1;
    }
    label++;
  }

  int t = 0;
  FOR(i, p1) if (matched1[i]) t++;
  return t;
}


bool isValid(int x, int y) {
  return x >=0 && y >= 0 && x < dx && y < dy && chairs[x][y] == OK;
}

void setEdge(int x1, int y1, int x2, int y2, bool from1) {
  if (from1)
    g[nodes[x1][y1]][nodes[x2][y2]] = true;
  else
    g[nodes[x2][y2]][nodes[x1][y1]] = true;
}

void addEdges(int x, int y, bool from1) {
  if (isValid(x, y)) {
    if (isValid(x - 1, y)) setEdge(x, y, x - 1, y, from1);
    if (isValid(x + 1, y)) setEdge(x, y, x + 1, y, from1);
    if (isValid(x - 1, y - 1)) setEdge(x, y, x - 1, y - 1, from1);
    if (isValid(x + 1, y - 1)) setEdge(x, y, x + 1, y - 1, from1);
  }
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

    nodes1 = nodes2 = 0;
    FOR(i, dx) {
      FOR(j, dy) if (chairs[i][j] == OK) nodes[i][j] = nodes1++;
      i++;
      if (i < dx) {
        FOR(j, dy) if (chairs[i][j] == OK) nodes[i][j] = nodes2++;
      }
    }
    FOR(i, nodes1) FOR(j, nodes2) g[i][j] = false;

    FOR(i, dx) {
      FOR(j, dy) addEdges(i, j, true);
      i++;
      if (i < dx) FOR(j, dy) addEdges(i, j, false);
    }

    int m = maxMatching(nodes1, nodes2);

    printf("Case #%d: %d\n", c, nodes1 + nodes2 - m);
  }
  return 0;
}

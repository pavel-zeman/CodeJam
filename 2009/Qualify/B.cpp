#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define H 100
#define W 100

int h, w;
int map[H][W];
char basin[H][W];

struct {
  int h;
  int w;
} queue[H * W * 2];

int dirs[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};


void getFlow(int h1, int w1, int *h2, int *w2) {
  *h2 = -1;
  *w2 = -1;
  if (h1 < 0 || h1 >= h || w1 < 0 || w1 >= w) return;

  int minAlt = map[h1][w1];
  for(int i=0;i<4;i++) {
    int h3 = h1 + dirs[i][0];
    int w3 = w1 + dirs[i][1];
    if (h3 >=0 && h3 < h && w3 >= 0 && w3 < w && map[h3][w3] < minAlt) {
      minAlt = map[h3][w3];
      *h2 = h3;
      *w2 = w3;
    }
  }
}

int main(void) {
  int t;
  scanf("%d", &t);

  for(int c=1;c<=t;c++) {

    scanf("%d %d", &h, &w);

    for(int i=0;i<h;i++)
      for(int j=0;j<w;j++) {
        scanf("%d", &map[i][j]);
        basin[i][j] = 0;
      }

    char currentBasin = 'a';

    while (1) {
      int queueStart = 0;
      int queueEnd = 0;

      for(int i=0;i<h;i++)
        for(int j=0;j<w;j++)
          if (!basin[i][j]) {
            queue[0].h = i;
            queue[0].w = j;
            queueEnd++;
            basin[i][j] = currentBasin;
            goto found;
          }
      // nothing found
      break;

      found:
      while (queueStart != queueEnd) {
        int h2, w2;
        getFlow(queue[queueStart].h, queue[queueStart].w, &h2, &w2);
        if (h2 >= 0 && !basin[h2][w2]) {
          queue[queueEnd].h = h2;
          queue[queueEnd++].w = w2;
          basin[h2][w2] = currentBasin;
        }

        for(int i=0;i<4;i++) {
          int h3 = queue[queueStart].h + dirs[i][0];
          int w3 = queue[queueStart].w + dirs[i][1];
          getFlow(h3, w3, &h2, &w2);
          if (h2 == queue[queueStart].h && w2 == queue[queueStart].w && !basin[h3][w3]) {
            queue[queueEnd].h = h3;
            queue[queueEnd++].w = w3;
            basin[h3][w3] = currentBasin;
          }
        }
        queueStart++;
      }
      currentBasin++;
    }

    printf("Case #%d:\n", c);

    for(int i=0;i<h;i++) {
      for(int j=0;j<w;j++)
        printf("%c ", basin[i][j]);
      printf("\n");
    }
  }
}

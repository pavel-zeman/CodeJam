#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


#define M 20000

int l;
int x, y;
int d;

int values[M];


struct wall {
  int v;
  struct wall * next;
};

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

struct firstWall {
  int count;
  struct wall * first;
  int minv, maxv;
} horizontal[M], vertical[M];

int min(int a, int b) {
  return a < b ? a : b;
}

int max(int a, int b) {
  return a > b ? a : b;
}


void addHorizontal(int y, int x) {
  struct wall * w = new wall();
  w->v = x;
  w->next = NULL;
  if (horizontal[y].first == NULL) {
    horizontal[y].count = 1;
    horizontal[y].first = w;
    horizontal[y].minv = horizontal[y].maxv = w->v;
  } else {
    struct wall * last = horizontal[y].first;
    while (last->next != NULL) last = last->next;
    last->next = w;
    horizontal[y].count++;
    horizontal[y].minv = min(w->v, horizontal[y].minv);
    horizontal[y].maxv = max(w->v, horizontal[y].maxv);
  }
}

void addVertical(int x, int y) {
  struct wall * w = new wall();
  w->v = y;
  w->next = NULL;
  if (vertical[x].first == NULL) {
    vertical[x].count = 1;
    vertical[x].first = w;
    vertical[x].minv = vertical[x].maxv = w->v;
  } else {
    struct wall * last = vertical[x].first;
    while (last->next != NULL) last = last->next;
    last->next = w;
    vertical[x].count++;
    vertical[x].minv = min(w->v, vertical[x].minv);
    vertical[x].maxv = max(w->v, vertical[x].maxv);
  }
}

int compute(void) {
  int total = 0;

  // vertical
  FOR(i, M) {
    if (vertical[i].first != NULL) {
      struct wall * next = vertical[i].first;
      int t = vertical[i].count;
      FOR(j, t) {
        values[j] = next->v;
        next = next->next;
      }

      FOR(a, t) FORE(b, a+1, t) if (values[a] > values[b]) { int aa = values[a]; values[a] = values[b]; values[b] = aa;}
      FORE(j, 1, t - 1) {
        //printf("Vertical %d %d %d\n", i, values[j], values[j + 1]);
        total += values[j + 1] - values[j];
        j++;
      }
    }
  }

  // horizontal
  FOR(i, M) {
    if (horizontal[i].first != NULL) {
      struct wall * next = horizontal[i].first;
      //printf("%d %d\n", i, horizontal[i].count);
      int t = horizontal[i].count;
      FOR(j, t) {
        values[j] = next->v;
        next = next->next;
      }

      FOR(a, t) FORE(b, a+1, t) if (values[a] > values[b]) { int aa = values[a]; values[a] = values[b]; values[b] = aa;}
      FORE(j, 1, t - 1) {
        FORE(k, values[j], values[j+1]) {
          if (i >= vertical[k].maxv || i < vertical[k].minv) {
            //printf("%d %d\n", i, k);
            total++;
          }
        }
        j++;
      }
    }
  }

  return total;

}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d", &l);
    x = y = M/2;
    d = 0;

    FOR(i, M) horizontal[i].first = vertical[i].first = NULL;

    FOR(i, l) {
      char s[1000];
      int t;
      scanf("%s %d", s, &t);
      int l = strlen(s);
      FOR(j, t) {
        FOR(k, l) {
          switch (s[k]) {
            case 'L': d = (d - 1) & 3; break;
            case 'R': d = (d + 1) & 3; break;
            case 'F':
              if (d == 0 || d == 2) addVertical(min(y, y + dy[d]), x);
              else addHorizontal(min(x, x + dx[d]), y);
              //printf("%d %d\n", x, y);
              x += dx[d];
              y += dy[d];
              break;
          }
        }
      }
    }

    ;

    printf("Case #%d: %d\n", c, compute());
  }
}

#include <stdio.h>
#include <string.h>
#include <limits.h>
//#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX 1000001

int r;
int maxx, maxy, minc;
int rounds;

struct {
    int x1, y1, x2, y2;
    bool used;
} rects[1000];


void solve(int p) {
    rects[p].used = true;
    if (rects[p].y2 > maxy) maxy = rects[p].y2;
    if (rects[p].x2 > maxx) maxx = rects[p].x2;
    if (rects[p].x1 + rects[p].y1 < minc) minc = rects[p].x1 + rects[p].y1;

    FOR(i, r) {
        if (!rects[i].used && rects[p].x2 + 1 >= rects[i].x1 && rects[p].x1 <= rects[i].x2 + 1 &&
        rects[p].y2 + 1 >= rects[i].y1 && rects[p].y1 <= rects[i].y2 + 1 &&
        !(rects[p].x2 + 1 == rects[i].x1 && rects[p].y2 + 1 == rects[i].y1) &&
        !(rects[i].x2 + 1 == rects[p].x1 && rects[i].y2 + 1 == rects[p].y1)) {
            solve(i);
        }
    }
}



int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d", &r);
        FOR(i, r) {
            scanf("%d %d %d %d", &rects[i].x1, &rects[i].y1, &rects[i].x2, &rects[i].y2);
            rects[i].used = false;
        }
        rounds = 0;
        FOR(i, r) {
            maxx = maxy = 0;
            minc = INT_MAX;
            if (!rects[i].used)
                solve(i);
            int nr = maxx + maxy - minc + 1;
            if (nr > rounds) rounds = nr;
        }


        printf("Case #%d: %d\n", c, rounds);
    }
    return 0;
}

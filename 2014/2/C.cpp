// Walk through a maze - start from the bottom and try to get to the top using a "left-hand rule" (each cell can be visited at most once)
// https://code.google.com/codejam/contest/3014486/dashboard#s=p2
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_W 200
#define MAX_H 600

bool used[MAX_W][MAX_H];
int w, h;

int incx[4] = {0, 1, 0, -1};
int incy[4] = {1, 0, -1, 0};

char c = 0;
int getInt() {
    int r = 0;
    while (!(c == '-' || (c >= '0' && c <= '9'))) c = getc_unlocked(stdin);
    bool minus = c == '-';
    if (minus) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

bool check(int x, int y, int direction) {
    if (x < 0 || x >= w || y < 0 || y >= h) return false;
    if (used[x][y]) return false;
    used[x][y] = true;
    if (y == h - 1) return true;
    int s = (direction - 1 + 4) & 3;
    FOR(i, 3) {
        if (check(x + incx[s], y + incy[s], s)) return true;
        s = (s + 1) & 3;
    }
    return false;
}

int main(void) {
    int cases = getInt();
    for(int c=1;c<=cases;c++) {
        w = getInt();
        h = getInt();
        FOR(i, w) FOR(j, h) used[i][j] = false;
        int b = getInt();
        FOR(i, b) {
            int x0 = getInt(), y0 = getInt(), x1 = getInt(), y1 = getInt();
            FORE(k, x0, x1 + 1) FORE(l, y0, y1 + 1) used[k][l] = true;
        }
        int total = 0;
        FOR(i, w) if (check(i, 0, 0)) total++;
        printf("Case #%d: %d\n", c, total);
    }
}

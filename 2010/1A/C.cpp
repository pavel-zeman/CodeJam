#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int a1, a2, b1, b2;

bool win(int x, int y) {
    //printf("Checking %d %d\n", x, y);
    if (x == y) {
        return false;
    } if (x == 0 || y == 0) {
        return true;
    } else {
        int v = x > y ? x : y;
        int m = x > y ? y : x;
        int res = v % m;
        bool sub = win(res, m);
        if (!sub) {
            return true;
        } else {
            if (v >= 2 * m) return true; else return false;
        }
    }
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d %d %d %d", &a1, &a2, &b1, &b2);
        int total = 0;
        FORE(i, a1, a2+1) FORE(j, b1, b2+1)
          if (win(i, j)) total++;
        printf("Case #%d: %d\n", c, total);
    }
}

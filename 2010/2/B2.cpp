#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

//#define INT_MAX 1000000000

int p;
int total;
int miss[1024];
int prices[10][1024];

int solve(int x, int y, int level) {
    //printf("Solving %d %d %d\n", x, y, level);
    bool found = false;
    bool impossible = false;
    for(int i = x;i<y;i++) {
        if (miss[i] > 0) { found = true; }
        if (miss[i] > level + 1) { impossible = true; break; }
    }
    if (impossible) return INT_MAX / 3;

    if (found) {
        if (level > 0) {
            int p1 = solve(x, (x + y) / 2, level - 1) + solve((x + y) / 2, y, level - 1);

            for(int i=x;i<y;i++) miss[i]--;

            int p2 = solve(x, (x + y) / 2, level - 1) + solve((x + y) / 2, y, level - 1) + prices[level][x];
            for(int i=x;i<y;i++) miss[i]++;

            //printf("Returning: %d %d %d %d %d\n", x, y, level, prices[level][x], p1 < p2 ? p1 : p2);
            return p1 < p2 ? p1 : p2;
        } else {
            //printf("Price: %d\n", prices[level][x]);
            return prices[level][x];
        }
    } else {
        return 0;
    }
}


int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d", &p);
        total = 1<<p;
        FOR(i, total) scanf("%d", &miss[i]);
        for(int j=p-1;j>=0;j--) {
            int step = 1 << (p - j);
            FOR(i, 1<<j) {
                scanf("%d", &prices[p - 1 - j][i * step]);
                //printf("Reading %d %d %d\n", p - 1 - j, i*step, prices[p - 1 - j][i * step]);
            }
        }

        FOR(i, total) miss[i] = p - miss[i];

        int res = solve(0, total, p - 1);

        printf("Case #%d: %d\n", c, res);
    }
}

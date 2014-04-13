#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int p;
int total;
int miss[1024];
int price;

void solve(int x, int y) {
    //printf("Solving %d %d\n", x, y);
    bool found = false;
    for(int i = x;i<y;i++) {
        if (miss[i] > 0) { found = true; break; }
    }

    if (found) {
        for(int i=x;i<y;i++) miss[i]--;
        price++;
        if (y > x+1) {
            solve(x, (x + y) / 2);
            solve((x + y) / 2, y);
        }
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
            int nothing;
            FOR(i, 1<<j) scanf("%d", &nothing);
        }

        FOR(i, total) miss[i] = p - miss[i];

        price = 0;
        solve(0, total);

        printf("Case #%d: %d\n", c, price);
    }
}

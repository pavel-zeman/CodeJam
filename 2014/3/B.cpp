// Dynamic programming based on the starting tower and the number of hits, that Diana has before tower
// https://code.google.com/codejam/contest/3024486/dashboard#s=p1
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1000
#define MAX_HITS 1500

int p, q, n;

int h[MAX_N], g[MAX_N];
int max[MAX_N][MAX_HITS];



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

int calc(int start, int hitsRemain) {
    if (start == n) return 0;

    if (max[start][hitsRemain] == -1) {
        int res = calc(start + 1, hitsRemain + (h[start] - 1) / q + 1);
        int towerHit = (h[start] - 1) / q;
        int remain = h[start] - towerHit * q;
        int dianaHit = (remain - 1) / p + 1;
        if (dianaHit <= hitsRemain + towerHit) {
            int t = g[start] + calc(start + 1, hitsRemain - dianaHit + towerHit);
            if (t > res) res = t;
        }
        max[start][hitsRemain] = res;
    }
    return max[start][hitsRemain];
}

int main(void) {
    int cases = getInt();
    for(int c=1;c<=cases;c++) {
        p = getInt();
        q = getInt();
        n = getInt();
        FOR(i, n) {
            h[i] = getInt();
            g[i] = getInt();
        }
        FOR(i, MAX_N) FOR(j, MAX_HITS) max[i][j] = -1;

        printf("Case #%d: %d\n", c, calc(0, 1));
    }
}

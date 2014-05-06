// Optimized solution using DP
// https://code.google.com/codejam/contest/2994486/dashboard#s=p1
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_BITS 30

int a, b, k;
long long int res[MAX_BITS + 1][2][2][2];

long long int solve(int bits, int ba, int bb, int bk) {
    //printf("Solving %d %d %d %d\n", bits, ba, bb, bk);
    if (bits == MAX_BITS + 1) return ba & bb & bk;
    if (res[bits][ba][bb][bk] >= 0) return res[bits][ba][bb][bk];
    long long int result = 0;
    int ma = ba ? 1 : (a >> (MAX_BITS - bits)) & 1;
    int mb = bb ? 1 : (b >> (MAX_BITS - bits)) & 1;
    int mk = bk ? 1 : (k >> (MAX_BITS - bits)) & 1;
    FOR(i, ma + 1) FOR(j, mb + 1) {
        int temp = i & j;
        if (temp <= mk) {
            result += solve(bits + 1,
                ba | (i < ((a >> (MAX_BITS - bits)) & 1)),
                bb | (j < ((b >> (MAX_BITS - bits)) & 1)),
                bk | (temp < ((k >> (MAX_BITS - bits)) & 1))
            );
        }
    }
    return res[bits][ba][bb][bk] = result;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d %d %d", &a, &b, &k);

        FOR(i, MAX_BITS + 1) FOR(j, 2) FOR(k, 2) FOR(l, 2) res[i][j][k][l] = -1;

        printf("Case #%d: %lld\n", c, solve(0, 0, 0, 0));
    }
}

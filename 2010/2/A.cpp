#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)



int k;
int diamond[1000][1000];
int min;


bool verify(int cx, int cy, int i, int j) {
    if (diamond[i][j] == -1) return true;

    int k = i > cx ? cx - (i - cx) : cx + (cx - i);
    int l = j > cy ? cy - (j - cy) : cy + (cy - j);

    if (k >= 0 && diamond[k][j] != -1 && diamond[k][j] != diamond[i][j]) return false;
    if (l >= 0 && diamond[i][l] != -1 && diamond[i][l] != diamond[i][j]) return false;
    return true;
}

void check(int a, int b) {
    FOR(i, k * 2 + 1) FOR(j, k * 2 + 1)
        if (!verify(a, b, i, j)) return;
    int r1, r2;
    r1 = a > k ? a - k : k - a;
    r2 = b > k ? b - k : k - b;

    int m = r1 + r2 + k;
    if (m < min) min = m;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d", &k);
        FOR(i, 6*k + 2) FOR(j, 6*k + 2) diamond[i][j] = -1;

        FOR(i, k) {
            FOR(j, i + 1) {
                scanf("%d", &diamond[i + 1][k - i + j * 2]);
            }
        }
        for(int i=k - 2;i>=0;i--) {
            FOR(j, i + 1) {
                scanf("%d", &diamond[k - 1 - i + k][k - i + j * 2]);
            }
        }


        min = INT_MAX;
        FOR(i, k * 2 + 1) FOR(j, k * 2 + 1) check(i, j);

        printf("Case #%d: %d\n", c, min * min - k * k);
    }
}

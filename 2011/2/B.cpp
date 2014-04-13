#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int r, c, d;
int mass[1000][1000];


bool check(int rr, int cc, int k) {
    int totalx = 0, totaly = 0;
    FOR(i, k)
        FOR(j, k) {
            if (! (i == 0 && j == 0 || i == k - 1 && j == 0 || i == 0 && j == k - 1 || i == k - 1 && j == k - 1)) {
                totalx += mass[rr + i][cc + j] * (j * 2 + 1 - k);
                totaly += mass[rr + i][cc + j] * (i * 2 + 1 - k);
            }
        }
    //printf("Checking: %d %d %d: %d %d\n", rr, cc, k, totalx, totaly);
    return totalx == 0 && totaly == 0;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++) {
        scanf("%d%d%d", &r, &c, &d);
        FOR(i, r) {
            char row[1000];
            scanf("%s", row);
            FOR(j, c) mass[i][j] = row[j] - '0';
        }

        int k = r > c ? c : r;

        while (k >= 3) {
            FOR(i, r - k + 1) FOR(j, c - k + 1) {
                if (check(i, j, k)) {
                    goto end;
                }
            }
            k--;
        }

        end:

        printf("Case #%d: ", cc);
        if (k >= 3) printf("%d\n", k); else printf("IMPOSSIBLE\n");
    }
}

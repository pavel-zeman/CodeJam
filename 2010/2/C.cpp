#include <stdio.h>
#include <string.h>
#include <limits.h>
//#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX 1000

char bact[MAX][MAX];
int r;
int x1, x2, y1, y2;
int maxx, maxy;



int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        FOR(i, MAX) FOR(j, MAX) bact[i][j] = 0;
        int total = 0;
        maxx = 0;
        maxy = 0;

        scanf("%d", &r);
        FOR(k, r) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            if (x2 > maxx) maxx = x2;
            if (y2 > maxy) maxy = y2;
            for(int i=x1;i<=x2;i++)
                for(int j=y1;j<=y2;j++)
                    bact[i][j] = 1, total++;
        }

        int rounds = 0;
        while (total > 0) {
            rounds++;
            int total2 = 0;

            for(int i=maxx; i>=0;i--) {
                for(int j=maxy;j>=0;j--) {
                    if (bact[i][j] == 0 && i > 0 && j > 0 && bact[i-1][j] == 1 && bact[i][j-1] == 1) {
                        bact[i][j] = 1;
                        total2++;
                    } else if (bact[i][j] == 1 && (i == 0 || bact[i-1][j] == 0) && (j==0 || bact[i][j-1] == 0)) {
                        bact[i][j] = 0;
                    } else if (bact[i][j] == 1) {
                        total2++;
                    }
                }
            }
            total = total2;
        }
        printf("Case #%d: %d\n", c, rounds);
    }
    return 0;
}

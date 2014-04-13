#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int p, w;

bool hole[400][400];
int dist1[400], dist2[400];
int maxThreaten;
int path[400];


void calc(int *dist, int start, int end) {
    dist[start] = 0;
    int d = 0;
    while (dist[end] == -1) {
        FOR(i, p) {
            if (dist[i] == d) {
                FOR(j, p) if (dist[j] == -1 && hole[i][j]) {
                    dist[j] = d + 1;
                }
            }
        }
        d++;
    }
}


void check(int pos, int *dist1, int *dist2, int total, bool *threaten) {
    //printf("Check: %d %d %d\n", pos, dist1[pos], total);
    if (dist1[pos] == total) {
        int l = 0;
        FOR(i, p) if (threaten[i] && !path[i]) l++;
        if (l > maxThreaten) {
            maxThreaten = l;
            /*FOR(i, p) if (path[i]) printf("%d(%d) ", i, path[i]);
            printf("\n");
            FOR(i, p) if (threaten[i] && !path[i]) printf("%d ", i);
            printf("\n");*/
        }
    } else {
        bool threaten2[400];
        FOR(j, p) threaten2[j] = threaten[j];
        FOR(j, p) if (hole[pos][j]) threaten2[j] = true;
        path[pos] = dist1[pos] + 1;
        FOR(i, p) {
            if (!path[i] && hole[pos][i] && dist1[i] == dist1[pos] + 1 && dist1[i] + dist2[i] == total && dist1[i] >= 0 && dist2[i] >= 0) {
                check(i, dist1, dist2, total, threaten2);
            }
        }
        path[pos] = false;

    }
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d%d", &p, &w);
        FOR(i, p) FOR(j, p) hole[i][j] = false;
        FOR(i, w) {
            int h1, h2;
            scanf("%d, %d", &h1, &h2);
            hole[h1][h2] = true;
            hole[h2][h1] = true;
        }
        /*FOR(i, p) {
            FOR(j, p) printf("%c", hole[i][j] ? '1' : '0');
            printf("\n");
        }*/
        FOR(i, p) dist1[i] = dist2[i] = -1;
        calc(dist1, 0, 1);
        calc(dist2, 1, 0);

        int m = 0;
        FOR(i, p) if (dist1[i] + dist2[i] == dist1[1]) m++;
        //printf("%d %d\n", m, dist1[1]);

        maxThreaten = 0;
        bool threaten[400];
        FOR(i, p) threaten[i] = false;
        FOR(i, p) path[i] = 0;
        check(0, dist1, dist2, dist1[1], threaten);

        printf("Case #%d: %d %d\n", c, dist1[1] - 1, maxThreaten);
    }
}

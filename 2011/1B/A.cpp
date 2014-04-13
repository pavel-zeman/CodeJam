#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int n;

double wp[1000], owp[1000], oowp[1000];

char schedule[1000][1000];


double calcWp(int team, int omit) {
    int games = 0;
    int wins = 0;
    FOR(j, n) {
        if (j != omit) {
            switch (schedule[team][j]) {
                case '1':
                    wins++;
                case '0':
                    games++;
                    break;
            }
        }
    }
    return ((double)wins)/games;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d", &n);

        FOR(i, n) scanf("%s", schedule[i]);

        FOR(i, n) wp[i] = calcWp(i, -1);

        FOR(i, n) {
            double total = 0;
            int games = 0;
            FOR(j, n) {
                if (schedule[i][j] != '.') {
                    total += calcWp(j, i);
                    games++;
                }
            }
            owp[i] = total / games;
        }

        FOR(i, n) {
            double total = 0;
            int games = 0;
            FOR(j, n)
                if (schedule[i][j] != '.') {
                    total += owp[j];
                    games++;
                }
            oowp[i] = total / games;
        }




        printf("Case #%d:\n", c);
        FOR(i, n) {
            //printf("%lf %lf %lf\n", wp[i], owp[i], oowp[i]);
            printf("%.12lf\n", 0.25 * wp[i] + 0.5 * owp[i] + 0.25 * oowp[i]);
        }
    }
}

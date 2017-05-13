// Brute force solution for the small input
// https://code.google.com/codejam/contest/5314486/dashboard#s=p1&a=2

#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(int)(t);c++)
#define LLI long long int
#define MOD 1000000007

int power(int a, int b) {
    int sq = a;
    int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * (LLI)sq % MOD;
        sq = sq * (LLI)sq % MOD;
        b >>= 1;
    }
    return result;
}

int inv(int a) {
    return power(a, MOD - 2);
}

void fail() {
    *((char *)0) = 0;
}


int counts[1024][1024];
int total[1024];


int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++) {
        int n, c, m;
        scanf("%d %d %d", &n, &c, &m);
        FOR(i, c) FOR(j, n) counts[i][j] = 0;
        FOR(i, m) {
            int b, p;
            scanf("%d %d", &p, &b);
            counts[b - 1][p - 1]++;
            total[b - 1]++;
        }
        int rides = 0, promotions = 0;
        if (n == 1) {
            rides = total[0] + total[1];
        } else {
            rides += counts[0][0];
            int remain = counts[0][0];
            counts[0][0] = 0;
            FORE(i, 1, n) while (remain > 0 && counts[0][i] > 0 && counts[1][i] > 0) {
                remain--;
                counts[1][i]--;
            }
            FORE(i, 1, n) while (remain > 0 && counts[1][i] > 0) {
                remain--;
                counts[1][i]--;
            }

            remain = counts[1][0];
            rides += remain;
            counts[1][0] = 0;

            //printf("P1: %d %d\n", counts[0][1], counts[1][1]);

            FORE(i, 1, n) while (remain > 0 && counts[0][i] > 0 && counts[1][i] > 0) {
                remain--;
                counts[0][i]--;
            }
            FORE(i, 1, n) while (remain > 0 && counts[0][i] > 0) {
                remain--;
                counts[0][i]--;
            }

            FORE(i, 1, n) {
                int remain = counts[0][i];
                FORE(j, 1, n) while (j != i && remain > 0 && counts[0][j] > 0 && counts[1][j] > 0) {
                    remain--;
                    rides++;
                    counts[1][j]--;
                    counts[0][i]--;
                }
            }
            //printf("P2: %d %d\n", counts[0][1], counts[1][1]);
            FORE(i, 1, n) {
                int remain = counts[0][i];
                FORE(j, 1, n) while (j != i && remain > 0 && counts[1][j] > 0) {
                    remain--;
                    rides++;
                    counts[1][j]--;
                    counts[0][i]--;
                }
            }

            FORE(i, 1, n) {
                int remain = counts[0][i];
                rides += remain;
                int j = i;
                while (remain > 0 && counts[1][j] > 0) {
                    remain--;
                    promotions++;
                    counts[1][j]--;
                    counts[0][i]--;
                }
            }
            FORE(i, 1, n) rides += counts[1][i];
        }

        printf("Case #%d: %d %d\n", cc, rides, promotions);
    }
}

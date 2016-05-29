// Maximum number of ways is 2^(B - 2). The graph contains all edges (i, j) where j > i and j != B and then edges from each i to B to reach the required sum.
// https://code.google.com/codejam/contest/4314486/dashboard#s=p1

#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
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

#define MAX_B 60
int matrix[MAX_B][MAX_B];

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++) {
        int b;
        LLI m;
        scanf("%d %lld", &b, &m);
        LLI mx = 1;
        mx <<= (b - 2);
        printf("Case #%d: ", cc);
        if (m > mx) printf("IMPOSSIBLE\n");
        else {
            FOR(i, b) FOR(j, b) matrix[i][j] = 0;
            FOR(i, b - 1) FORE(j, i + 1, b - 1) matrix[i][j] = 1;
            if (m == mx) { matrix[0][b - 1] = 1; m--;}
            FORE(i, 1, b - 1) {
                if ((m & 1) == 1) matrix[i][b - 1] = 1;
                m >>= 1;
            }
            printf("POSSIBLE\n");
            FOR(i, b) {
                FOR(j, b) printf("%d", matrix[i][j]);;
                printf("\n");
            }
        }
    }
}

// Description
// https://code.google.com/codejam/contest/3264486/dashboard#s=p2

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



int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++) {
        LLI n, k;
        scanf("%lld %lld", &n, &k);
        LLI g1, g2;
        LLI c1, c2;
        g1 = n;
        c1 = 1;
        g2 = n + 1;
        c2 = 0;
        while (c1 + c2 < k) {
            LLI ng1, ng2;
            LLI nc1, nc2;
            if (g1 % 2 == 0) {
                ng1 = g1 / 2 - 1;
                ng2 = ng1 + 1;
                nc1 = c1;
                nc2 = c1 + c2 + c2;
            } else {
                ng1 = g1 / 2;
                ng2 = ng1 + 1;
                nc1 = c1 + c1 + c2;
                nc2 = c2;
            }
            k -= c1 + c2;
            g1 = ng1;
            g2 = ng2;
            c1 = nc1;
            c2 = nc2;
        }
        LLI mn, mx;
        if (k <= c2) {
            mx = g2 / 2;
            mn = g2 - mx - 1;
        } else {
            mx = g1 / 2;
            mn = g1 - mx - 1;
        }

        printf("Case #%d: %lld %lld\n", cc, mx, mn);
    }
}

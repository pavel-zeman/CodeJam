// Description
// https://code.google.com/codejam/contest/8294486/dashboard#s=p0

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

#define MAX_N 1024
int d, n;
pair<int, int> h[MAX_N];



int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++) {
        scanf("%d %d", &d, &n);
        FOR(i, n) {
            int k, s;
            scanf("%d %d", &k, &s);
            h[i] = make_pair(k, s);
        }
        sort(h, h + n);
        double t = 0;
        for(int i = n - 1; i >= 0; i--) {
            double t2 = (d - h[i].first) / (double)h[i].second;
            if (t2 > t) t = t2;
        }

        printf("Case #%d: %.10lf\n", cc, d / t);
    }
}

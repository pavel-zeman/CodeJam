// Brute force solution handling all possible cases
// https://code.google.com/codejam/contest/5314486/dashboard#s=p0&a=2

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
        int n, p;
        int counts[10];
        FOR(i, p) counts[i] = 0;
        scanf("%d %d", &n, &p);
        FOR(i, n) {
            int g;
            scanf("%d", &g);
            counts[g % p]++;
        }
        int res = counts[0];
        if (p == 2) {
            res += (counts[1] + 1) / 2;
        } else if (p == 3) {
            int m = min(counts[1], counts[2]);
            res += m;
            counts[1] -= m;
            counts[2] -= m;
            if (counts[1] > 0) res += (counts[1] + 2) / 3;
            else res += (counts[2] + 2) / 3;
        } else if (p == 4) {
            int m = min(counts[1], counts[3]);
            res += m;
            counts[1] -= m;
            counts[3] -= m;
            m = counts[2] / 2;
            res += m;
            counts[2] -= m * 2;
            if (counts[1] == 0) {
                if (counts[2] > 0) {
                    if (counts[3] >= 2) {
                        res++;
                        counts[2]--;
                        counts[3] -= 2;
                    } else {
                        res++;
                        counts[2] = counts[3] = 0;
                    }
                    res += (counts[3] + 3)/ 4;
                } else res += (counts[3] + 3)/ 4;
            } else {
                if (counts[2] > 0) {
                    if (counts[1] >= 2) {
                        res++;
                        counts[2]--;
                        counts[1] -= 2;
                    } else {
                        res++;
                        counts[2] = counts[1] = 0;
                    }
                    res += (counts[1] + 3)/ 4;
                } else res += (counts[1] + 3)/ 4;
            }
        }
        printf("Case #%d: %d\n", cc, res);
    }
}

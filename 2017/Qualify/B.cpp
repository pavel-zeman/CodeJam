// Find the first digit from the left, which is higher then the next digit. Then decrement the digit and change all subsequent digits to 9. Repeat, until the digits are in non-decreasing order.
// https://code.google.com/codejam/contest/3264486/dashboard#s=p1

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
        LLI n;
        int digits[20];
        scanf("%lld", &n);
        while (true) {
            int dc = 0;
            LLI p = n;
            while (p > 0) {
                digits[dc++] = p % 10;
                p /= 10;
            }
            int pos = -1;
            for(int i=dc-1; i > 0;i--) if (digits[i] > digits[i - 1]) {
                pos = i;
                break;
            }
            if (pos < 0) break;
            n = 0;
            for(int i = dc - 1; i >= pos; i--) n = n * 10 + digits[i];
            n--;
            for(int i = pos - 1; i >= 0; i--) n = n * 10 + 9;
        }

        printf("Case #%d: %lld\n", cc, n);
    }
}

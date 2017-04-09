// Start flipping the pancakes from the left and then check, if all the pancakes are happy side up.
// https://code.google.com/codejam/contest/3264486/dashboard

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


#define MAX_S 1010
#define H1 '+'
#define H2 '-'
char input[MAX_S];

char flip(char a) {
    return a == H1 ? H2 : H1;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++) {
        int k;
        scanf("%s %d", input, &k);
        int l = strlen(input);
        int steps = 0;
        FOR(i, l - k + 1) {
            if (input[i] != H1) {
                FOR(j, k) input[i + j] = flip(input[i + j]);
                steps++;
            }
        }
        printf("Case #%d: ", cc);
        bool ok = true;
        FORE(i, l - k, l) if (input[i] != H1) {
            ok = false;
            break;
        }
        if (ok) printf("%d\n", steps); else printf("IMPOSSIBLE\n");
    }
}

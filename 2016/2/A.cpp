// First calculate the winning choice (if there is any). Then go back and reconstruct the original choice (for each result, there is a unique combination of choices) and swap their positions, if necessary.
// https://code.google.com/codejam/contest/10224486/dashboard#s=p0

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

#define R 0
#define P 1
#define S 2
#define INVALID -1


int n, r, p, s;
int result[3][3] = {{INVALID, P, R}, {P, INVALID, S}, {R, S, INVALID}};
char ch[3] = {'R', 'P', 'S'};

char resultString[10000];
int first[3] = {R, P, P};
int second[3] = {S, R, S};

int getResult(int l, int r, int p, int s) {
    if (l == 0) {
        if (r > 0) return R;
        if (p > 0) return P;
        if (s > 0) return S;
    }
    int remainRp = r + p - s;
    if (remainRp < 0) return INVALID;
    if ((remainRp & 1) == 1) return INVALID;

    int pr = remainRp >> 1;
    int rs = r - pr;
    int ps = p - pr;
    if (rs < 0 || ps < 0) return INVALID;
    return getResult(l - 1, rs, pr, ps);
}

void swp(int pos, int length) {
    int l2 = length >> 1;
    char tmp[5000];
    FOR(i, l2) tmp[i] = resultString[pos + i];
    FOR(i, l2) resultString[pos + i] = resultString[pos + i + l2];
    FOR(i, l2) resultString[pos + i + l2] = tmp[i];
}

void gen(int what, int pos, int length) {
    int l2 = length >> 1;
    if (length == 2) {
        resultString[pos] = ch[first[what]];
        resultString[pos + 1] = ch[second[what]];
    } else {
        gen(first[what], pos, l2);
        gen(second[what], pos + l2, l2);
    }
    if (strncmp(resultString + pos, resultString + pos + l2, l2) > 0) {
        swp(pos, length);
    }

}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++) {
        scanf("%d %d %d %d", &n, &r, &p, &s);
        int res = getResult(n, r, p, s);

        printf("Case #%d: ", cc);
        if (res == -1) printf("IMPOSSIBLE"); else {
            gen(res, 0, 1 << n);
            resultString[1 << n] = 0;
            printf("%s", resultString);
        }
        puts("");
    }
}


// Sort the probabilities and then choose first x and last k - x (for each x from 0 to k). For each choice, calculate the probability of a tie using dynamic programming.
// https://code.google.com/codejam/contest/10224486/dashboard#s=p1

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

#define MAX_N 220
int n, k;
double p[MAX_N];
double testP[MAX_N];

double prob[MAX_N][MAX_N][MAX_N];

double calcProb(int pos, int yes, int no) {
    if (pos == k) return 1;
    double result = prob[pos][yes][no];
    if (result < 0) {
        result = 0;
        if (yes > 0) result += testP[pos] * calcProb(pos + 1, yes - 1, no);
        if (no > 0) result += (1 - testP[pos]) * calcProb(pos + 1, yes, no - 1);
        prob[pos][yes][no] = result;
    }
    return result;
}

double calcTie() {
    int k2 = k >> 1;
    double pTie = 0;
    FOR(j, 1 << k) {
        if (__builtin_popcount(j) == k2) {
            double py = 1;
            double pn = 1;
            int x = j;
            FOR(l, k) {
                if ((x & 1) == 1) py *= testP[l]; else pn *= (1 - testP[l]);
                x >>= 1;
            }
            pTie += py * pn;
        }
    }
    return pTie;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++) {
        scanf("%d %d", &n, &k);
        FOR(i, n) scanf("%lf", &p[i]);
        sort(p, p + n);
        double maxTie = 0;
        int k2 = (k >> 1);
        FOR(i, k + 1) {
            int pos = 0;
            FOR(j, i) testP[pos++] = p[j];
            FORE(j, n - (k - i), n) testP[pos++] = p[j];
            FOR(x, k + 1) FOR(y, k2 + 1) FOR(z, k2 + 1) prob[x][y][z] = -1;
            double res = calcProb(0, k2, k2);
            if (res > maxTie) maxTie = res;
        }

        printf("Case #%d: %.10lf\n", cc, maxTie);
    }
}

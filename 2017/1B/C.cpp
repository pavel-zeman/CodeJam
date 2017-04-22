// Description
// https://code.google.com/codejam/contest/8294486/dashboard#s=p2

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

#define MAX_N 128
int e[MAX_N], s[MAX_N];
int d[MAX_N][MAX_N];
double r[MAX_N];
double best[MAX_N];
double bestLocal[MAX_N];
set<int> toCalc;
int n, q;
bool visited[MAX_N];

void spread(int node, int e, int s, double t) {
    if (bestLocal[node] == -1 || t < bestLocal[node]) {
        bestLocal[node] = t;
        if (best[node] == -1 || t < best[node]) {
            best[node] = t;
            toCalc.insert(node);
        }

        FOR(i, n)
            if (d[node][i] > 0 && d[node][i] <= e) {
                spread(i, e - d[node][i], s, t + d[node][i] / (double)s);
            }
    }
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++) {

        scanf("%d %d", &n, &q);
        FOR(i, n) scanf("%d %d", &e[i], &s[i]);;
        FOR(i, n) FOR(j, n) scanf("%d", &d[i][j]);
        FOR(i, n) d[i][i] = -1;
        FOR(i, q) {
            int u, v;
            scanf("%d %d", &u, &v);
            u--;
            v--;
            FOR(j, n) best[j] = -1;
            best[u] = 0;
            toCalc.insert(u);
            while (!toCalc.empty()) {
                int first = *toCalc.begin();
                toCalc.erase(first);
                FOR(i, n) visited[i] = false;
                FOR(i, n) bestLocal[i] = -1;
                spread(first, e[first], s[first], best[first]);
            }
            r[i] = best[v];
        }
        printf("Case #%d:", cc);
        FOR(i, q) printf(" %.10lf", r[i]);
        printf("\n");
    }
}

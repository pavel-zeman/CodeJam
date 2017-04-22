// Description
// https://code.google.com/codejam/contest/8294486/dashboard#s=p1

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
#define R 0
#define O 1
#define Y 2
#define G 3
#define B 4
#define V 5
int possible[6][3] = {
    {Y, B, G},
    {B, -1},
    {R, B, V},
    {R, -1},
    {R, Y, O},
    {Y, -1}
};
char colors[] = "ROYGBV";
int c[6];
int n;
int first;
int stall[MAX_N];
int nextPrev[6] = {R, possible[1][0], Y, possible[3][0], B, possible[5][0]};
int remAdd[6] = {1, 2, 1, 2, 1, 2};

set<LLI> visited[6];

LLI getValue() {
    LLI result = 0;
    FOR(i, 6) {
        result <<= 10;
        result |= c[i];
    }
    return result;
}

int getc(LLI v, int i) {
    return (v >> (10 * (5 - i))) & 1023;
}

LLI dec(LLI v, int i) {
    return v - (((LLI)1) << (10 * (5 - i)));
}


bool solve(LLI v, int prev, int remain) {
    if (visited[prev].find(v) == visited[prev].end()) {
        if (remain == 0) {
            FOR(i, 3) if (possible[prev][i] == first) {
                return true;
            }
            visited[prev].insert(v);
            return false;
        } else {
            FOR(i, 3) if (possible[prev][i] >= 0) {
                int p = possible[prev][i];
                int c = getc(v, p);
                stall[remain - 1] = p;
                if (c > 0) {
                    if (solve(dec(v, p), nextPrev[p], remain - remAdd[p])) return true;
                }
            } else break;
            visited[prev].insert(v);
            return false;
        }
    } else return false;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++) {
        scanf("%d", &n);
        FOR(i, 6) scanf("%d", &c[i]);
        bool res = true;
        FOR(i, n) stall[i] = -1;
        c[possible[O][0]] -= c[O];
        c[possible[G][0]] -= c[G];
        c[possible[V][0]] -= c[V];
        FOR(i, 6) if (c[i] < 0) res = false;
        if (res) {
            first = -1;
            FOR(i, 3) if (c[i * 2 + 1] > 0) { first = i * 2 + 1; stall[n - 1] = first; c[i * 2 + 1]--; break;}
            if (first < 0) {
                FOR(i, 6) if (c[i] > 0) {
                    first = i;
                    stall[n - 1] = first;
                    c[i]--;
                    break;
                }
            }
            LLI v = getValue();
            FOR(i, 6) visited[i].clear();
            res = solve(v, nextPrev[first], n - remAdd[first]);
        }

        printf("Case #%d: ", cc);
        if (res) {
            for(int i = n - 1; i >= 0; i--) if (stall[i] == O || stall[i] == G || stall[i] == V) {
                stall[i - 1] = possible[stall[i]][0];
            }
            FOR(i, n) printf("%c", colors[stall[i]]);
            printf("\n");
        } else printf("IMPOSSIBLE\n");
    }
}

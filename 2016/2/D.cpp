// Just brute force solution for the small input.
// https://code.google.com/codejam/contest/10224486/dashboard#s=p3

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

#define MAX_N 10
int n;
bool operate[MAX_N][MAX_N];

bool workerUsed[MAX_N];
bool machineUsed[MAX_N];


bool check(int order) {
    if (order < n) {
        FOR(i, n) {
            if (!workerUsed[i]) {
                workerUsed[i] = true;
                bool found = false;
                FOR(j, n) {
                    if (!machineUsed[j] && operate[i][j]) {
                        machineUsed[j] = true;
                        found = true;
                        bool res = check(order + 1);
                        machineUsed[j] = false;
                        if (!res) {
                            workerUsed[i] = false;
                            return false;
                        }
                    }
                }
                workerUsed[i] = false;
                if (!found) return false;
            }
        }
    }
    return true;
}


bool works(int level, int total, int nextPos) {
    if (level == total) return check(0);
    else {
        FORE(i, nextPos, n * n) {
            int w = i / n;
            int m = i % n;
            if (!operate[w][m]) {
                operate[w][m] = true;
                bool res = works(level + 1, total, i + 1);
                operate[w][m] = false;
                if (res) return true;
            }
        }
        return false;
    }
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++) {
        scanf("%d", &n);
        FOR(i, n) {
            char line[MAX_N];
            scanf("%s", line);
            FOR(j, n) operate[i][j] = line[j] == '1';
        }
        int result = 0;
        FOR(i, n * n + 1) {
            if (works(0, i, 0)) {
                result = i;
                break;
            }
        }
        printf("Case #%d: %d\n", cc, result);
    }
}

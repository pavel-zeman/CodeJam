// Description
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000051679/0000000000146185
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(int)(t);c++)
#define LLI long long int
#define MOD 1000000007


char ccc = 0;
int getInt() {
    int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}

int getString(char *start) {
    char *data = start;
    while (!(ccc > ' ' && ccc <= '~')) ccc = getc_unlocked(stdin);
    while (ccc > ' ' && ccc <= '~') {
        *data++ = ccc;
        ccc = getc_unlocked(stdin);
    }
    *data = 0;
    return data - start;
}


int getSignedInt() {
    int r = 0;
    while (!(ccc == '-' || (ccc >= '0' && ccc <= '9'))) ccc = getc_unlocked(stdin);
    bool minus = ccc == '-';
    if (minus) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

long long int getLongLongInt() {
    long long int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}


template <class type> void print(type a) {
    if (a < 0) {
        putc_unlocked('-', stdout);
        a = -a;
    }
    if (a == 0) {
        putc_unlocked('0', stdout);
    } else {
        char result[20];
        int resSize = 0;
        while (a > 0) {
            result[resSize++] = '0' + a % 10;
            a /= 10;
        }
        while (--resSize >= 0) putc_unlocked(result[resSize], stdout);
    }
    putc_unlocked('\n', stdout);
}

void printString(const char *str) {
    while (*str) putc_unlocked(*str++, stdout);
    putc_unlocked('\n', stdout);
}

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

template <class type> type gcd(type a, type b) {
    return b == 0 ? a : gcd(b, a % b);
}

void fail() {
    *((char *)0) = 0;
}

double cpu() {
    return clock() / (double)CLOCKS_PER_SEC;
}

#define MAX_M 16
int m;
int neigh[MAX_M][2];
LLI g[MAX_M];
bool makesLead[MAX_M];
int steps[MAX_M];
bool visited[MAX_M];


bool isCycleWithLead(int node, bool withLead) {
    FOR(i, 2) {
        int n = neigh[node][i];
        if (!visited[n]) {
            visited[n] = true;
            bool result = isCycleWithLead(n, withLead || n == 0);
            visited[n] = false;
            if (result) return true;
        } else if (visited[n] && (withLead || n == 0)) return true;
    }
    return false;
}

void makeLead(int node, int level) {
    if (level > 0 && node != 0) {
        int n1 = neigh[node][0];
        int n2 = neigh[node][1];
        g[n1] = (g[n1] + g[node]) % MOD;
        g[n2] = (g[n2] + g[node]) % MOD;
        g[node] = 0;
        makeLead(n1, level - 1);
        makeLead(n2, level - 1);
    }
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        m = getInt();
        FOR(i, m) {
            neigh[i][0] = getInt() - 1;
            neigh[i][1] = getInt() - 1;
        }
        FOR(i, m) makesLead[i] = false;
        FOR(i, m) g[i] = getInt();
        FOR(i, m) if (neigh[i][0] == 0 || neigh[i][1] == 0) {
            makesLead[i] = true;
            steps[i] = 1;
        }
        bool changed = true;
        int s = 1;
        while (changed) {
            s++;
            changed = false;
            FOR(i, m) if (!makesLead[i]) {
                FOR(j, 2) if (makesLead[neigh[i][j]]) {
                    makesLead[i] = true;
                    changed = true;
                    steps[i] = s;
                }
            }
        }

        bool cycle = false;
        FOR(i, m) {
            if (g[i] > 0 && makesLead[i]) {
                bool changed = true;
                bool used[MAX_M];
                used[i] = true;
                while (changed) {
                    changed = false;
                    FOR(j, m) if (used[j]) {
                        int n1 = neigh[j][0];
                        int n2 = neigh[j][1];
                        if (!used[n1]) {
                            used[n1] = true;
                            changed = true;
                        }
                        if (!used[n2]) {
                            used[n2] = true;
                            changed = true;
                        }
                        if (n1 == i || n2 == i) {
                            cycle = true;
                        }
                    }
                }
            }
        }
        if (!cycle) {
            bool changed = true;
            while (changed) {
                changed = false;
                FOR(i, m) if (makesLead[i] && g[i] > 0) {
                    makeLead(i, m);
                    changed = true;
                }
            }
        }

        printf("Case #%d: ", tt + 1);
        if (cycle) printf("UNBOUNDED\n"); else printf("%lld\n", g[0]);
    }
}


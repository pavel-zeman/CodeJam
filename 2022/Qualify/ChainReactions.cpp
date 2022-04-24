// Description
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000876ff1/0000000000a45ef7
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

#define MAX_N 100010
#define MM 1000000010
int f[MAX_N];
int p[MAX_N];
int n;
vector<int> children[MAX_N];
int minFactor[MAX_N];
int minChild[MAX_N];
LLI total;
bool used[MAX_N];

int calculateMinimum(int node) {
    if (children[node].empty()) {
        minFactor[node] = f[node];
    } else {
        int mm = MM;
        int minNode = 0;
        for(int i = 0; i < children[node].size(); i++) {
            int value = calculateMinimum(children[node][i]);
            if (value < mm) {
                mm = value;
                minNode = i;
            }
        }
        minChild[node] = minNode;
        minFactor[node] = max(f[node], mm);
    }
    return minFactor[node];
}

void solve(int node) {
  if (!used[node]) {
    total += minFactor[node];
    int i = node;
    while (!children[i].empty()) {
        used[i] = true;
        i = children[i][minChild[i]];
    }
    used[i] = true;
  }
  for(int i = 0; i < children[node].size(); i++) solve(children[node][i]);
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        total = 0;
        n = getInt();
        FOR(i, n) children[i].clear();
        FOR(i, n) f[i] = getInt();
        FOR(i, n) {
            used[i] = false;
            p[i] = getInt() - 1;
            if (p[i] >= 0) children[p[i]].push_back(i);
        }
        FOR(i, n) if (p[i] < 0) calculateMinimum(i);
        FOR(i, n) if (p[i] < 0) solve(i);

        printf("Case #%d: %lld\n", tt + 1, total);
    }
}


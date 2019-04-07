// There are 4 possible cases to solve.
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000051705/00000000000881da
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
#define E 'E'
#define S 'S'
char p[MAX_N];
char out[MAX_N];

pair<int, int> find2(char what, int l) {
    int r = 0;
    int c = 0;
    FOR(i, l) {
        if (i > 0 && p[i] == what && p[i - 1] == what) return make_pair(r, c);
        if (p[i] == E) c++; else r++;
    }
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int l = getString(p);
        int oc = 0;

        if (p[0] == E) {
            if (p[l - 1] == E) {
                // E -> E
                auto two = find2(S, l);
                int l = two.first;
                FOR(i, l) out[oc++] = S;
                FOR(i, n - 1) out[oc++] = E;
                FOR(i, n - 1 - l) out[oc++] = S;
            } else {
                // E -> S
                FOR(i, n - 1) out[oc++] = S;
                FOR(i, n - 1) out[oc++] = E;
            }
        } else {
            if (p[l - 1] == E) {
                // S -> E
                FOR(i, n - 1) out[oc++] = E;
                FOR(i, n - 1) out[oc++] = S;
            } else {
                // S -> S
                auto two = find2(E, l);
                int l = two.second;
                FOR(i, l) out[oc++] = E;
                FOR(i, n - 1) out[oc++] = S;
                FOR(i, n - 1 - l) out[oc++] = E;
            }
        }
        out[oc] = 0;
        printf("Case #%d: %s\n", tt + 1, out);
    }
}


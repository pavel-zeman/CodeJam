// Description
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000051679/0000000000146183
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

#define MAX_N 512
int c[MAX_N];
int j[MAX_N];
int order[MAX_N];
bool used[MAX_N];
int n;
int total;


bool isGreater(int p1, int q1, int p2, int q2) {
    return ((LLI)p1) * q2 > ((LLI)p2) * q1;
}

int isOrdered() {
    int minp = 0, minq = 1;
    int maxp, maxq;
    bool maxSet = false;
    FOR(i, n - 1) {
        int c1 = c[order[i]];
        int c2 = c[order[i + 1]];
        int j1 = j[order[i]];
        int j2 = j[order[i + 1]];
        if (c1 > c2) {
            if (j2 <= j1) return 0;
            int p = j2 - j1;
            int q = c1 - c2;
            if (maxSet) {
                if (isGreater(maxp, maxq, p, q)) maxp = p, maxq = q;
            } else {
                maxSet = true;
                maxp = p, maxq = q;
            }
        } else if (c1 < c2) {
            if (j2 < j1) {
                int p = j1 - j2;
                int q = c2 - c1;
                if (isGreater(p, q, minp, minq)) minp = p, minq = q;
            }
        } else if (j1 >= j2) return 0;
    }
    return !maxSet || isGreater(maxp, maxq, minp, minq);
}

void check(int level) {
    if (level < n) {
        FOR(i, n) if (!used[i]) {
            used[i] = true;
            order[level] = i;
            check(level + 1);
            used[i] = false;
        }
    } else {
        total += isOrdered();
    }
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) {
            c[i] = getInt();
            j[i] = getInt();
            used[i] = false;
        }
        total = 0;
        check(0);
        printf("Case #%d: %d\n", tt + 1, total);
    }
}


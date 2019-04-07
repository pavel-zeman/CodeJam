// Description
// https://codejam.withgoogle.com/2018/challenges/0000000000007764/dashboard/000000000003675b
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

#define MAX_S 100010
int a[MAX_S];
int b[MAX_S];
int d[MAX_S];

bool check(int start, int l) {
    bool nset = false, mset = false;
    int e = start + l;
    int n, m;
    bool ok = true;

    nset = true;
    n = d[start] - b[start];
    FORE(i, start + 1, e) {
        if (d[i] - b[i] != n) {
            if (!mset) {
                mset = true;
                m = d[i] + a[i];
            } else if (d[i] + a[i] != m) {
                ok = false;
                break;
            }
        }
    }
    if (ok) return true;

    mset = nset = false;
    mset = true;
    ok = true;

    m = d[start] + a[start];
    FORE(i, start + 1, e) {
        if (d[i] + a[i] != m) {
            if (!nset) {
                nset = true;
                n = d[i] - b[i];
            } else if (d[i] - b[i] != n) {
                ok = false;
                break;
            }
        }
    }
    return ok;
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int s = getInt();
        FOR(i, s) {
            d[i] = getInt();
            a[i] = getInt();
            b[i] = getInt();
        }
        int maxLength = min(2, s);
        for(int i = s; i >= 3; i--) {
            FOR(j, s - i + 1) if (check(j, i)) {
                maxLength = i;
                goto ee;
            }
        }
        ee:
        int total = 0;
        if (maxLength <= 2) total = s - maxLength + 1;
        else {
            FOR(i, s - maxLength + 1) if (check(i, maxLength)) total++;
        }
        printf("Case #%d: %d %d\n", tt + 1, maxLength, total);
    }
}


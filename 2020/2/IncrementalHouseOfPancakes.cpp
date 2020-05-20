// Description
// https://codingcompetitions.withgoogle.com/codejam/round/000000000019ffb9/00000000003384ea
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

LLI total(LLI n) {
    return n * (n + 1) / 2;
}

LLI total(LLI first, LLI last) {
    return (first + last) * ((last - first + 2) / 2) / 2;
}

LLI solve(LLI k) {
    return k == 0 ? 0 : (sqrt(8 * (double)k + 1) - 1) / 2;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        LLI l = getLongLongInt();
        LLI r = getLongLongInt();
        LLI s = l + r;
        LLI n = 0;
        if (l > r) {
            n = solve(l - r) + 2;
            while (l - total(n) < r) n--;
            l -= total(n);
        } else if (l < r) {
            n = solve(r - l) + 2;
            while (r - total(n) < l) n--;
            if (r - total(n) > l && r - total(n) >= n + 1) n++;
            r -= total(n);
        }
        LLI n2;
        if (l >= n + 1) {
            n2 = solve(s) + 2;
            while (true) {
                LLI total1 = total(n + 1, (n2 & 1) == (n & 1) ? n2 - 1 : n2);
                LLI total2 = total(n + 2, (n2 & 1) != (n & 1) ? n2 - 1 : n2);
                if (l >= total1 && r >= total2) {
                    l -= total1;
                    r -= total2;
                    break;
                }
                n2--;
            }
        } else n2 = n;



        printf("Case #%d: %lld %lld %lld\n", tt + 1, n2, l, r);
    }
}


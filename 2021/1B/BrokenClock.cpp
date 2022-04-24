// Description
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000435baf/00000000007ae694
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

LLI s = 120 * (LLI)1000000000;
LLI full = 360 * s;

LLI getSecond(int tim) {
    tim = tim % 60;
    return tim * s * 6;
}

LLI getMinute(int tim) {
    tim = tim % 3600;
    return tim * s / 10;
}

LLI getHour(int tim) {
    return tim * 36 * s / 4320;
}

LLI diff(LLI a, LLI b) {
    LLI r = a - b;
    return r < 0 ? r + full : r;
}

int test(LLI a, LLI b, LLI c) {
    FOR(i, 86400) {
        LLI aa = getSecond(i);
        LLI bb = getMinute(i);
        LLI cc = getHour(i);
        if (diff(a, b) == diff(aa, bb) && diff(a, c) == diff(aa, cc) && diff(b, c) == diff(bb, cc)) return i;
    }
    return -1;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        LLI a = getLongLongInt();
        LLI b = getLongLongInt();
        LLI c = getLongLongInt();
        int tim = test(a, b, c);
        if (tim < 0) tim = test(a, c, b);
        if (tim < 0) tim = test(b, a, c);
        if (tim < 0) tim = test(b, c, a);
        if (tim < 0) tim = test(c, a, b);
        if (tim < 0) tim = test(c, b, a);
        printf("Case #%d: %d %d %d 0\n", tt + 1, tim / 3600, tim % 3600 / 60, tim % 60);
    }
}


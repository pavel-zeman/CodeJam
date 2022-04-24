// Description
// https://codingcompetitions.withgoogle.com/codejam/round/000000000087711b/0000000000acd29b
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

int rot(int value, int c) {
    FOR(i, c) {
      int last = value & 1;
      value = (value >> 1) | (last << 7);
    }
    return value;
}

int numOnes(int value) {
    int res = 0;
    while (value > 0) {
        res += value & 1;
        value >>= 1;
    }
    return res;
}

LLI getTotal(int value, int bits) {
    LLI result = 0;
    FOR(i, 256) {
        if (numOnes(i) == bits) {
            FOR(j, 8) {
                int x = i ^ rot(value, j);
                result += numOnes(x);
            }
        }
    }
    return result;
}

int choose(int bits) {
    LLI minValue = 256 * 256;
    int result;
    FORE(i, 1, 255) {
        LLI x = getTotal(i, bits);
        if (x < minValue) {
            result = i;
            minValue = x;
        }
    }
    return result;
}

char str[10];

void toString(int value) {
    FOR(i, 8) {
        str[i] = (value & 1) + '0';
        value >>= 1;
    }
    str[8] = 0;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = 1;
        while (true) {
            int v = 0;
            if (n == 8) v = 255;
            else {
                FOR(i, n) v = v | (1 << i);
            }
            toString(v);
            printf("%s\n", str);
            fflush(stdout);
            n = getSignedInt();
            if (n == -1) exit(0);
            if (n == 0) break;
        }
    }
}


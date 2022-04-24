// Description
// https://codingcompetitions.withgoogle.com/codejam/round/000000000087711b/0000000000accfdb
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

#define MAX_N 1024
#define MAX_P 128
int x[MAX_N][MAX_P];
LLI result[MAX_N][2];
int n, p;

LLI calcDiff(int pos) {
    LLI result = 0;
    FORE(i, 1, p) result += abs(x[pos][i] - x[pos][i - 1]);
    return result;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        p = getInt();
        FOR(i, n) {
            FOR(j, p) x[i][j] = getInt();
            sort(x[i], x[i] + p);
        }
        LLI t = calcDiff(0);
        result[0][0] = t + x[0][0];
        result[0][1] = t + x[0][p - 1];
        FORE(i, 1, n) {
            t = calcDiff(i);
            result[i][0] = t + min(
                result[i - 1][0] + abs(x[i][0] - x[i - 1][p - 1]),
                result[i - 1][1] + abs(x[i][0] - x[i - 1][0])
            );
            result[i][1] = t + min(
                result[i - 1][0] + abs(x[i][p - 1] - x[i - 1][p - 1]),
                result[i - 1][1] + abs(x[i][p - 1] - x[i - 1][0])
            );
        }

        printf("Case #%d: %lld\n", tt + 1, min(result[n - 1][0], result[n - 1][1]));
    }
}


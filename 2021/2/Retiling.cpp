// Description
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000435915/00000000007dc2de
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

#define MAX_N 16
bool curr[MAX_N][MAX_N];
bool target[MAX_N][MAX_N];
char line[MAX_N];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int r = getInt();
        int c = getInt();
        int f = getInt();
        int s = getInt();
        FOR(i, r) {
            getString(line);
            FOR(j, c) curr[i][j] = line[j] == 'M';
        }
        FOR(i, r) {
            getString(line);
            FOR(j, c) target[i][j] = line[j] == 'M';
        }
        int total = 0;

        FOR(i, r) FOR(j, c - 1) {
            if (curr[i][j] != target[i][j] && curr[i][j + 1] != target[i][j + 1] && curr[i][j + 1] != curr[i][j]) {
                total++;
                curr[i][j] = !curr[i][j];
                curr[i][j + 1] = !curr[i][j + 1];
            }
        }

        FOR(i, r - 1) FOR(j, c) {
            if (curr[i][j] != target[i][j] && curr[i + 1][j] != target[i + 1][j] && curr[i + 1][j] != curr[i][j]) {
                total++;
                curr[i][j] = !curr[i][j];
                curr[i + 1][j] = !curr[i + 1][j];
            }
        }

        FOR(i, r) FOR(j, c) if (curr[i][j] != target[i][j]) total++;

        printf("Case #%d: %d\n", tt + 1, total);
    }
}


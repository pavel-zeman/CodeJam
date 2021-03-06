// Description
// https://codejam.withgoogle.com/2018/challenges/0000000000007706/dashboard
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

#define MAX_C 128
int c;
int b[MAX_C];
char res[MAX_C][MAX_C];
int firstRow;

void addRow() {
    firstRow--;
    FOR(i, c) res[firstRow][i] = '.';
    res[firstRow][c] = 0;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        c = getInt();
        FOR(i, c) b[i] = getInt();
        bool ok = true;
        firstRow = MAX_C;
        if (b[0] == 0 || b[c - 1] == 0) ok = false; else {
            addRow();
            int target = 0;
            FOR(i, c) {
                while (b[target] == 0) target++;
                b[target]--;
                if (target > i) {
                    int r = MAX_C - 2;
                    for(int j = target - 1; j >= i; j--) {
                        if (r < firstRow) addRow();
                        res[r][j] = '\\';
                        r--;
                    }
                } else if (target < i) {
                    int r = MAX_C - 2;
                    for(int j = target + 1; j <= i; j++) {
                        if (r < firstRow) addRow();
                        res[r][j] = '/';
                        r--;
                    }
                }
            }
        }
        printf("Case #%d: ", tt + 1);
        if (ok) {
            printf("%d\n", MAX_C - firstRow);
            FORE(i, firstRow, MAX_C) printf("%s\n", res[i]);
        } else printf("IMPOSSIBLE\n");
    }
}


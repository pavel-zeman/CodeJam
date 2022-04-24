// Description
// https://codingcompetitions.withgoogle.com/codejam/round/000000000043580a/00000000006d1284
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

#define MAX_N 100
int result[MAX_N];
int used;

int ask(int a, int b, int c) {
    printf("%d %d %d\n", a + 1, b + 1, c + 1);
    fflush(stdout);
    int res = getSignedInt();
    if (res < 0) exit(1);
    return res - 1;
}

void insertElement(int pos, int v) {
    for(int i = used; i > pos; i --) result[i] = result[i - 1];
    result[pos] = v;
    used++;
}

void ins(int a, int b, int d) {
    if (a == b) { if (a > 0) a--; else b++; };
    if (a + 1 == b) {
        int r = ask(result[a], result[b], d);
        if (r == result[a]) insertElement(a, d);
        else if (r == result[b]) insertElement(b + 1, d);
        else insertElement(b, d);
    } else {
        int m = (a + b) / 2;
        int r = ask(result[a], result[m], d);
        if (r == result[a]) insertElement(a, d);
        else if (r == result[m]) ins(m + 1, b, d);
        else if (a + 1 == m) insertElement(m, d);
        else ins(a + 1, m - 1, d);
    }
}


int main(void) {
    int t = getInt();
    int n = getInt();
    int q = getInt();
    FOR(tt, t) {
        int r = ask(0, 1, 2);
        switch(r) {
            case 0: result[0] = 1; result[1] = 0; result[2] = 2; break;
            case 1: result[0] = 0; result[1] = 1; result[2] = 2; break;
            case 2: result[0] = 0; result[1] = 2; result[2] = 1; break;
        }
        used = 3;
        FORE(i, 3, n) ins(0, i - 1, i);
        FOR(i, n) printf("%d ", result[i] + 1);
        printf("\n");
        fflush(stdout);
        int res = getSignedInt();
        if (res != 1) exit(1);
    }
}


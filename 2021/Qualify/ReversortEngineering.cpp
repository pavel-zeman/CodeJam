// Description
// https://codingcompetitions.withgoogle.com/codejam/round/000000000043580a/00000000006d12d7
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

#define MAX_N 1000
int l[MAX_N];
int cost[MAX_N];

void rev(int a, int b) {
    while (b > a) {
        int x = l[b];
        l[b] = l[a];
        l[a] = x;
        a++;
        b--;
    }
}

void moveLeft(int a, int b) {
    FORE(i, a, b + 1) l[i - 1] = l[i];
}

int findMin(int a, int b) {
    int m = MAX_N;
    int r = 0;
    FORE(i, a, b + 1) if (l[i] < m) { m = l[i]; r = i;}
    return r;
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int c = getInt();
        bool possible = false;
        if (c >= n - 1 && c <= (n + 2) * (n - 1) / 2) {
            possible = true;
            int remaining = c;
            FOR(i, n - 1) {
                cost[i] = min(n - i, remaining - (n - i - 2));
                remaining -= cost[i];
            }
            l[n - 1] = n - 1;
            for(int i = n - 2; i >= 0; i--) {
                int cc = cost[i];
                moveLeft(i + 1, i + cc - 1);
                rev(i + 1, i + cc - 1);
                l[i + cc - 1] = i;
            }
        }

        printf("Case #%d:", tt + 1);
        if (possible) FOR(i, n) printf(" %d", l[i] + 1);
        else printf(" IMPOSSIBLE");
        printf("\n");
    }
}


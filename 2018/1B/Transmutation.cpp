// Description
// https://codejam.withgoogle.com/2018/challenges/0000000000007764/dashboard/000000000003675c
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

#define MAX_M 110
pair<int, int> r[MAX_M];
LLI g[MAX_M];
int m;
LLI total;
bool visited[MAX_M];

void make(int index) {
    visited[index] = true;
    if (r[index].first == index || r[index].second == index || r[index].first == 0 || r[index].second == 0) return;
    LLI lastTotal;
    do {
        int mm = min(g[r[index].first], g[r[index].second]);
        if (r[index].first == r[index].second) mm >>= 1;
        if (mm >= 1) {
            mm = 1;
            g[r[index].first] -= mm;
            g[r[index].second] -= mm;
            g[index] += mm;
            total -= mm;
            break;
        }

        lastTotal = total;
        if (r[index].first == r[index].second) {
            if (!visited[r[index].first]) make(r[index].first);
        } else {
            if (g[r[index].first] == 0 && !visited[r[index].first]) make(r[index].first);
            if (g[r[index].second] == 0 && !visited[r[index].second]) make(r[index].second);
        }
    } while (lastTotal != total);
    visited[index] = false;
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        m = getInt();
        FOR(i, m) {
            r[i].first = getInt() - 1;
            r[i].second = getInt() - 1;
            visited[i] = false;
        }
        total = 0;
        FOR(i, m) total += g[i] = getInt();
        LLI lastTotal = total;
        do {
            lastTotal = total;
            make(0);
        } while (lastTotal != total);
        printf("Case #%d: %lld\n", tt + 1, g[0]);
    }
}


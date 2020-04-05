// Description
// https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/0000000000209a9e?show=progress
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

int b, l, r;
int data[128];
int moves;


int firstDifferent() {
    FOR(i, l) if (data[i] != data[b - 1 - i]) return i;
    return -1;
}

int firstSame() {
    FOR(i, l) if (data[i] == data[b - 1 - i]) return i;
    return -1;
}

int getValue(int pos) {
    moves++;
    printf("%d\n", pos + 1);
    fflush(stdout);
    return getInt();
}

void neg() {
    FOR(i, b) data[i] ^= 1;
}

void swp() {
    FOR(i, l) swap(data[i], data[b - 1 - i]);
}


int main(void) {
    int t = getInt();
    b = getInt();
    FOR(tt, t) {
        l = 0;
        r = b - 1;
        moves = 0;
        while (l < r) {
            int v = getValue(l);
            if (moves % 10 == 1 && moves > 10) {
                int d = firstDifferent();
                int s = firstSame();
                if (d >= 0 && s >= 0) {
                    int vd = getValue(d);
                    int vs = getValue(s);
                    if (vs != data[s]) neg();
                    if (vs != data[s] && vd == data[d] || vs == data[s] && vd != data[d]) swp();
                } else if (d >= 0) {
                    int vd = getValue(d);
                    vd = getValue(d);
                    if (vd != data[d]) neg();
                } else {
                    int vs = getValue(s);
                    vs = getValue(s);
                    if (vs != data[s]) neg();
                }
            }
            data[l++] = v;

            v = getValue(r);
            data[r--] = v;
        }
        FOR(i, b) printf("%d", data[i]);
        printf("\n");
        fflush(stdout);

        char answer[10];
        getString(answer);
        if (answer[0] != 'Y') return 0;
    }
}


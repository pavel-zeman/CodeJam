// Description
// https://codingcompetitions.withgoogle.com/codejam/round/000000000043580a/00000000006d1155
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

int abs(int a) {
    return a < 0 ? -a : a;
}

#define P 100
#define Q 10000
bool correct[P][Q];
char qr[Q + 2];
int better[P][P];
int diff[P];

int main(void) {
    int t = getInt();
    getInt();
    FOR(tt, t) {
        FOR(i, P) FOR(j, P) better[i][j] = 0;
        FOR(i, P) {
            getString(qr);
            FOR(j, Q) correct[i][j] = qr[j] == '1';
        }
        FOR(i, P) FOR(j, P) FOR(k, Q) {
            if (correct[i][k] && !correct[j][k]) better[i][j]++;
            else if (!correct[i][k] && correct[j][k]) better[j][i]++;
        }

        FOR(i, P) diff[i] = 0;
        FOR(i, P) FOR(j, P) diff[i] += abs(better[i][j] - better[j][i]);
        //FOR(i, P) printf("%d %d\n", i + 1, diff[i]);

        int cheater = min_element(diff, diff + P) - diff;
        printf("Case #%d: %d\n", tt + 1, cheater + 1);

        FOR(i, P) {
            int total = 0;
            FOR(j, Q) total += correct[i][j];
            printf("%d\n", total);
        }
    }
}


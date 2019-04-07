// Interval halving with initial interval of length 16 (because there can be at most 15 bad bits)
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000051705/00000000000881de
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

#define MAX_N 1030

struct {
    int pos;
    int valid;
} s1[MAX_N], s2[MAX_N];
int s1c, s2c;


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int b = getInt();
        int f = getInt();

        if (n <= 16) {
            s1[0].pos = 0;
            s1[0].valid = n - b;
            s1[1].pos = n;
            s1c = 2;
        } else {
            char input[MAX_N];
            int value = 0;
            FOR(i, n) {
                FORE(j, i, min(n, i + 16)) input[j] = value + '0';
                i += 15;
                value ^= 1;
            }
            input[n] = 0;
            puts(input);
            fflush(stdout);
            char output[MAX_N];
            int l = getString(output);
            int outp = 0;
            value = 0;
            s1[0].pos = 0;
            s1c = 1;
            while (outp < l) {
                int s = outp;
                while (outp < l && output[outp] == value + '0') outp++;
                s1[s1c - 1].valid = outp - s;
                s1[s1c].pos = min(s1[s1c - 1].pos + 16, n);
                s1c++;
                value ^= 1;
            }
            if (s1[s1c - 1].pos != n) {
                s1[s1c].pos = n;
                s1[s1c - 1].valid = 0;
                s1c++;
            }
        }


        while (true) {
            char input[MAX_N];
            int inp = 0;
            FOR(i, s1c - 1) {
                int l = s1[i + 1].pos - s1[i].pos;
                if (l == 1) input[inp++] = '0'; else {
                    int l1 = l >> 1;
                    FOR(j, l1) input[inp++] = '0';
                    FOR(j, l - l1) input[inp++] = '1';
                }
            }
            input[inp] = 0;
            puts(input);
            fflush(stdout);

            char output[MAX_N];
            getString(output);
            int outp = 0;
            s2c = 0;

            bool allOnes = true;
            FOR(i, s1c - 1) {
                int l = s1[i + 1].pos - s1[i].pos;
                if (l == 1) {
                    s2[s2c++] = s1[i];
                    outp += s1[i].valid;
                } else {
                    int l1 = l >> 1;
                    int s = outp;
                    int e = outp + s1[i].valid;
                    while (outp < e && output[outp] == '0') outp++;
                    s2[s2c].pos = s1[i].pos;
                    s2[s2c].valid = outp - s;
                    s2c++;
                    s2[s2c].pos = s1[i].pos + l1;
                    s2[s2c].valid = e - outp;
                    s2c++;
                    outp = e;
                    if (l1 > 1 || l - l1 > 1) allOnes = false;
                }
            }
            s2[s2c++] = s1[s1c - 1];
            FOR(i, s2c) s1[i] = s2[i];
            s1c = s2c;
            if (allOnes) break;
        }
        FOR(i, s1c - 1) if (s1[i].valid == 0) printf("%d ", i);
        printf("\n");
        fflush(stdout);
        if (getSignedInt() != 1) return 0;
    }
}


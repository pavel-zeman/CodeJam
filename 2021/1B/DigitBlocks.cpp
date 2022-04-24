// Description
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000435baf/00000000007ae37b
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

int n;
int b;

LLI total;
#define MAX_N 32
int piles[MAX_N];
int v[MAX_N][MAX_N];

int first() {
    FOR(i, n) if (piles[i] < b) return i;
}

int place(int d) {
    int f = first();
    if (d == 9) {
        // just f
    } else if (piles[f] < b - 1 || f == n - 1) {
        // just f
    } else {
        int i = f;
        while (piles[i] == b - 1 && i < n) i++;
        f = i == n ? f : i;
    }
    v[f][piles[f]] = d;
    piles[f]++;
    return f;
}

int place3(int d) {
    int f = 0;
    if (d == 9) {
        while (piles[f] == b) f++;
    } else if (d == 8) {
        while (f < n && piles[f] != b - 2) f++;
        if (f == n) {
            f = 0;
            while (f < n && piles[f] > b - 2) f++;
            if (f == n) {
                f = 0;
                while (piles[f] == b) f++;
            }
        }
    } else {
        while (f < n && piles[f] >= b - 2) f++;
        if (f == n) {
            f = 0;
            while (f < n && piles[f] >= b - 1) f++;
            if (f == n) {
                f = 0;
                while (piles[f] >= b) f++;
            }
        }
    }
    v[f][piles[f]] = d;
    piles[f]++;
    return f;
}


int place2(int d) {
    int mm = d * b / 10;
    int f = -1;
    int minDiff = 10000;
    if (d == 9) {
        FOR(i, n) if (piles[i] == b - 1) { f = i; break;}
    }
    if (f < 0) {
        FOR(i, n) if (piles[i] < b && piles[i] != b - 1 && abs(piles[i] - mm) < minDiff) {
            minDiff = abs(piles[i] - mm);
            f = i;
        }
    }
    if (f < 0) {
        FOR(i, n) if (piles[i] < b && abs(piles[i] - mm) < minDiff) {
            minDiff = abs(piles[i] - mm);
            f = i;
        }
    }
    //while (i < n && (piles[i] < mm - 1 || piles[i] > mm + 1 || piles[i] == b)) i++;

    /*if (d == 9) {
        // just f
    } else if (piles[f] < b - 1 || f == n - 1) {
        // just f
    } else {
        int i = f;
        while (piles[i] == b - 1 && i < n) i++;
        f = i == n ? f : i;
    }*/
    v[f][piles[f]] = d;
    piles[f]++;
    return f;
}

LLI ex(int x) {
    LLI res = 1;
    FOR(i, x) res *= 10;
    return res;
}

int main(void) {
    int t = getInt();
    n = getInt();
    b = getInt();
    LLI p = getLongLongInt();
    total = 0;
    FOR(tt, t) {
        FOR(i, n) piles[i] = 0;
        FOR(i, n * b) {
            int d = getInt();
            //int p = i > n * b * 1 / 2 ? place(d) : place2(d);
            int p = place3(d);
            total += ex(piles[p] - 1) * d;
            printf("%d\n", p + 1);
            fflush(stdout);
        }
        /*FOR(i, n) {
            FOR(j, b) printf("%d ", v[i][j]);
            printf("\n");
        }*/
    }
    //printf("%lld\n", total);
    getSignedInt();
}


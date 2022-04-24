// Description
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000435915/00000000007dbf06
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

#define MAX_N 1000010
bool prime[MAX_N];
int primes[MAX_N];
int totalPrimes;

int res[MAX_N];

#define M 1000
int cache[M][M];

int solve(int remainingSides, int currentSides) {
    if (remainingSides < M && currentSides < M && cache[remainingSides][currentSides] >= -1) return cache[remainingSides][currentSides];
    if (remainingSides == 0) {
        if (remainingSides < M && currentSides < M) cache[remainingSides][currentSides] = 0;
        return 0;
    }
    int m = -1;
    FORE(i, 3, currentSides) {
        if (i > remainingSides) break;
        if (currentSides % i == 0) {
            int mm = solve(remainingSides - i, i);
            if (mm > m) m = mm;
        }
    }
    int res = m == -1 ? m : m + 1;
    if (remainingSides < M && currentSides < M) cache[remainingSides][currentSides] = res;
    return res;
}

void gen(int currentSide, int totalSides, int totalPolygons) {
    //if (currentSide == 6)
        //printf("%d %d %d %d\n", currentSide, totalSides, totalPolygons, firstPrime);
    if (res[totalSides] < totalPolygons) res[totalSides] = totalPolygons;
    /*FORE(i, firstPrime, totalPrimes) {
        LLI x = totalSides + (LLI)currentSide * primes[i];
        if (x >= MAX_N) break;
        gen(currentSide * primes[i], totalSides + currentSide * primes[i], totalPolygons + 1, i);
    }*/
    int x = currentSide + currentSide;
    while (totalSides + x < MAX_N) {
        gen(x, totalSides + x, totalPolygons + 1);
        x += currentSide;
    }
    /*FORE(i, 2, MAX_N) {
        LLI x = totalSides + (LLI)currentSide * i;
        if (x >= MAX_N) break;
        gen(currentSide * i, totalSides + currentSide * i, totalPolygons + 1, i);
    }*/
}


int main(void) {
    FOR(i, MAX_N) prime[i] = true;
    FORE(i, 2, MAX_N) {
        if (prime[i]) {
            primes[totalPrimes++] = i;
            int j = i + i;
            while (j < MAX_N) {
                prime[j] = false;
                j += i;
            }
        }
    }
    FORE(i, 3, MAX_N) if (res[i] == 0) gen(i, i, 1);
    //FOR(i, MAX_N) printf("%d,\n", res[i]);
    //return 0;
    //FORE(i, 3, 10) printf("%d %d\n", i, res[i]);
    //FOR(i, M) FOR(j, M) cache[i][j] = -2;

    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        /*int m = -1;
        FORE(i, 3, n + 1) {
            int mm = solve(n - i, i);
            if (mm > m) m = mm;
        }*/
        printf("Case #%d: %d\n", tt + 1, res[n]);
    }
}


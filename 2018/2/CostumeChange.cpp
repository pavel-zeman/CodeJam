// Description
// https://codejam.withgoogle.com/2018/challenges/0000000000007706/dashboard/0000000000045875
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

#define MAX_N 10
int n;
int totalUsed;
int a[MAX_N][MAX_N];
int rowTotal[MAX_N][MAX_N * MAX_N];
int columnTotal[MAX_N][MAX_N * MAX_N];

int solve(int r, int c) {
    if (r == n) {
        FOR(i, n) FOR(j, totalUsed) if (rowTotal[i][j] > 1) return n * n;
        FOR(i, n) FOR(j, totalUsed) if (columnTotal[i][j] > 1) return n * n;
        return 0;
    } else {
        int nr = r;
        int nc = c + 1;
        if (nc == n) { nr++; nc = 0;}
        int r1 = solve(nr, nc);
        int r2 = n * n;
        if (rowTotal[r][a[r][c]] > 1 || columnTotal[c][a[r][c]] > 1) {
            rowTotal[r][a[r][c]]--;
            columnTotal[c][a[r][c]]--;
            r2 = solve(nr, nc) + 1;
            rowTotal[r][a[r][c]]++;
            columnTotal[c][a[r][c]]++;
        }
        return min(r1, r2);
    }
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        totalUsed = 0;
        map<int, int> used;
        FOR(i, n) FOR(j, n) {
            int aa = getSignedInt();
            auto it = used.find(aa);
            int v;
            if (it == used.end()) {
                used[aa] = totalUsed;
                v = totalUsed++;
            } else v = it->second;
            a[i][j] = v;
        }
        /*FOR(i, n) {
            FOR(j, n) printf("%d ", a[i][j]);
            printf("\n");
        }*/
        FOR(i, n) {
            FOR(j, totalUsed) rowTotal[i][j] = 0;
            FOR(j, n) rowTotal[i][a[i][j]]++;
        }

        FOR(i, n) {
            FOR(j, totalUsed) columnTotal[i][j] = 0;
            FOR(j, n) columnTotal[i][a[j][i]]++;
        }
        //FOR(i, n) { printf("%d %d\n", rowTotal[i][0], columnTotal[i][0]);}
        printf("Case #%d: %d\n", tt + 1, solve(0, 0));
    }
}


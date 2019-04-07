// Description
// https://codejam.withgoogle.com/2018/challenges/0000000000007706/dashboard/00000000000459f4
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

int r, c;
int g[10][10];
bool used[10][10];
int dirs[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int findLargest(int a, int b, int v) {
    if (a < 0 || a >= r || b < 0 || b >= c) return 0;
    if (!used[a][b] && g[a][b] == v) {
        used[a][b] = true;
        int res = 1;
        FOR(i, 4) {
            int na = a + dirs[i][0];
            int nb = b + dirs[i][1];
            int temp = findLargest(na, nb, v);
        }
        used[a][b] = false;
        return res;

    } else return 0;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        r = getInt();
        c = getInt();
        FOR(i, r) {
            char row[100];
            getString(row);
            FOR(j, c) g[i][j] = row[j] == 'B';
        }
        FOR(i, r) FOR(j, c) used[i][j] = 0;
        int res = 0;
        FOR(i, r) FOR(j, c) {
            if (!used[i][j]) {
                queue<pair<int, int>> q;
                used[i][j] = true;
                q.push(make_pair(i, j));
                int total = 0;
                while (!q.empty()) {
                    pair<int, int> x = q.front();
                    q.pop();
                    total++;
                    FOR(k, 4) {
                        int ni = x.first + dirs[k][0];
                        int nj = x.second + dirs[k][1];
                        if (ni >= 0 && ni < r && nj >= 0 && nj < c && !used[ni][nj] && g[ni][nj] == g[i][j]) {
                            q.push(make_pair(ni, nj));
                            used[ni][nj] = true;
                        }
                    }
                }
                if (total > res) res = total;
            }
        }


        printf("Case #%d: %d\n", tt + 1, res);
    }
}


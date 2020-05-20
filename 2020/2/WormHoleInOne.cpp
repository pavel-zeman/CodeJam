// Description
// https://codingcompetitions.withgoogle.com/codejam/round/000000000019ffb9/00000000003386d0
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

#define MAX_N 128
LLI x[MAX_N];
LLI y[MAX_N];
int n;
LLI dx;
LLI dy;
bool used[MAX_N];
bool usedIn[MAX_N];
int wormhole[MAX_N];
int start;
int path[MAX_N];

int sign(LLI x) {
    return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

int solve(int hole, int pp);


int solve2(int hole, int pp) {
    int best = 0;
    FOR(i, n) if (i != hole && wormhole[i] == 0) {
        wormhole[i] = hole + 1;
        wormhole[hole] = i + 1;
        used[i] = true;
        usedIn[hole] = true;
        path[pp] = i;
        int res = solve(i, pp + 1) + 1;
        used[i] = false;
        usedIn[hole] = false;
        wormhole[i] = wormhole[hole] = 0;
        if (res > best) best = res;
    }
    return best;
}

int solve(int hole, int pp) {
    LLI dist = 2000000000L * 1000;
    bool found = false;
    int foundNode;
    FOR(i, n) if (i != hole) {
        LLI cx = x[i] - x[hole];
        LLI cy = y[i] - y[hole];
        if (cx * dy == dx * cy && sign(cx) == sign(dx) && sign(cy) == sign(dy)) {
            LLI dist2 = abs(cx) + abs(cy);
            found = true;
            if (dist2 < dist) {
                dist = dist2;
                foundNode = i;
            }
        }
    }

    if (!found) return 0; else {
        if (used[foundNode]) {
            if (usedIn[foundNode]) return 0; else {
                usedIn[foundNode] = true;
                path[pp] = foundNode;
                int res = solve(wormhole[foundNode] - 1, pp + 1);
                usedIn[foundNode] = false;
                return res;
            }
        } else {
            used[foundNode] = true;
            path[pp] = foundNode;
            int res = solve2(foundNode, pp + 1) + 1;
            int totalUsed = 0;
            FOR(i, n) totalUsed += used[i];

            used[foundNode] = false;
            return res;
        }
    }
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        if (n > 10) return 0;
        FOR(i, n) {
            x[i] = getSignedInt();
            y[i] = getSignedInt();
            used[i] = false;
            usedIn[i] = false;
            wormhole[i] = 0;
        }

        int best = 0;
        FOR(i, n) FOR(j, n) FOR(k, n) {
            if (i != j && i != k && j != k) {
                path[0] = i;
                path[1] = j;
                used[i] = used[j] = true;
                usedIn[i] = true;
                wormhole[i] = j + 1;
                wormhole[j] = i + 1;

                dx = x[k] - x[j];
                dy = y[k] - y[j];
                int v = solve(j, 2) + 2;
                if (v > best) best = v;

                wormhole[i] = wormhole[j] = 0;
                used[i] = used[j] = false;
                usedIn[i] = false;
            }
        }
        if (n <= 2) best = n;

        printf("Case #%d: %d\n", tt + 1, best);
    }
}


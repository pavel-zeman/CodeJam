// Description
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000051706/000000000012295c
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

#define MAX_Q 16

char dirLetters[] = "NSEW";
int directions[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int grid[MAX_Q][MAX_Q];

pair<int, int> horiz[600];
int hc;
pair<int, int> vert[600];
int vc;


int getDir(char d) {
    FOR(i, 4) if (dirLetters[i] == d) return i;
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int p = getInt();
        int q = getInt();
        hc = vc = 0;
        FOR(i, p) {
            int x = getInt();
            int y = getInt();
            char d[10];
            getString(d);
            switch (d[0]) {
                case 'E':
                    horiz[hc].first = x + 1;
                    horiz[hc].second = 1;
                    hc++;
                    break;
                case 'W':
                    horiz[hc].first = x;
                    horiz[hc].second = -1;
                    hc++;
                    break;
                case 'N':
                    vert[vc].first = y + 1;
                    vert[vc].second = 1;
                    vc++;
                    break;
                case 'S':
                    vert[vc].first = y;
                    vert[vc].second = -1;
                    vc++;
                    break;
            }
        }
        sort(horiz, horiz + hc);
        int hs = 0;
        FOR(i, hc) if (horiz[i].second == -1) hs++;
        int rx = 0;
        int mx = hs;
        FOR(i, hc) {
            hs += horiz[i].second;
            while (i < hc - 1 && horiz[i + 1].first == horiz[i].first) {
                i++;
                hs += horiz[i].second;
            }
            if (hs > mx) {
                mx = hs;
                rx = horiz[i].first;
            }
        }

        sort(vert, vert + vc);
        int vs = 0;
        FOR(i, vc) if (vert[i].second == -1) vs++;
        int ry = 0;
        int my = vs;
        FOR(i, vc) {
            vs += vert[i].second;
            while (i < vc - 1 && vert[i + 1].first == vert[i].first) {
                i++;
                vs += vert[i].second;
            }
            if (vs > my) {
                my = vs;
                ry = vert[i].first;
            }
        }

        printf("Case #%d: %d %d\n", tt + 1, rx, ry);
    }
}


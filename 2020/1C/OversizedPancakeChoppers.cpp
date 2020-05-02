// Description
// https://codingcompetitions.withgoogle.com/codejam/round/000000000019fef4/00000000003172d1
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

LLI a[12000];
int used[12000];

bool findDouble(int from, int n, LLI value) {
    FORE(i, from, n) if (a[i] == value) return true;
    return false;
}

int main(void) {
    int t = getInt();
    int it = 0;
    FOR(tt, t) {
        int n = getInt();
        int d = getInt();
        FOR(i, n) a[i] = getLongLongInt();
        sort(a, a + n);
        int result = d - 1;
        FORE(i, 1, d + 1) {
            if (i <= result) {
                FOR(j, n) {
                    it++;
                    if (j > 0 && a[j] == a[j - 1]) continue;
                    LLI sliceA = a[j];
                    int sliceB = i;
                    int cuts = 0;
                    int slices = 0;
                    bool found = false;

                    FORE(k, j, n) {
                        if (a[k] * sliceB > (d - slices) * sliceA) { cuts += (d - slices); slices = d; found = true; break;}
                        if (a[k] * sliceB % sliceA == 0) {
                            int res = a[k] * sliceB / sliceA;
                            cuts += res - 1;
                            slices += res;
                            used[k] = it;
                            if (slices == d) { found = true; break;}
                        } else {
                            int res = a[k] * sliceB / sliceA + 1;
                            LLI next = (res * sliceA + sliceB - 1) / sliceB;
                            k = lower_bound(a + k + 1, a + n, next) - a - 1;
                        }
                    }
                    if (!found) {
                        LLI totalUnused = 0;
                        FORE(k, j, n) {
                            if (used[k] != it) {
                                totalUnused += a[k] * sliceB / sliceA;
                                if (totalUnused >= d - slices) {
                                    found = true;
                                    cuts += d - slices;
                                    slices = d;
                                    break;
                                }
                            }
                        }
                    }
                    if (found && cuts < result) result = cuts;
                }
            }
        }

        printf("Case #%d: %d\n", tt + 1, result);
    }
}


// Hungry algorithm - start from the biggest files and try to pack them on a single CD with another as big file as possible
// https://code.google.com/codejam/contest/3014486/dashboard#s=p0
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100000

int n;
int x;
int s[MAX_N];
bool used[MAX_N];

char c = 0;
int getInt() {
    int r = 0;
    while (!(c == '-' || (c >= '0' && c <= '9'))) c = getc_unlocked(stdin);
    bool minus = c == '-';
    if (minus) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

int cmp(const void *p1, const void *p2) {
    int *x1 = (int *)p1;
    int *x2 = (int *)p2;
    return *x2 - *x1;
}

int main(void) {
    int cases = getInt();
    for(int c=1;c<=cases;c++) {
        n = getInt();
        x = getInt();
        FOR(i, n) s[i] = getInt();
        FOR(i, n) used[i] = false;
        qsort(s, n, sizeof(s[0]), cmp);
        int total = 0;
        FOR(i, n) {
            if (!used[i]) {
                used[i] = true;
                total++;
                int c = s[i];
                FORE(j, i + 1, n) {
                    if (!used[j] && s[j] + c <= x) {
                        used[j] = true;
                        break;
                    }
                }
            }
        }

        printf("Case #%d: %d\n", c, total);
    }
}

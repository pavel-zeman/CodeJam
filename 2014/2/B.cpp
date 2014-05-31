// Hungry algorithm - take the numbers in increasing order and move each one to one of the ends (choose the end, which is "cheaper")
// https://code.google.com/codejam/contest/3014486/dashboard#s=p1
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 10000

int n;
int a[MAX_N];

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

int main(void) {
    int cases = getInt();
    for(int c=1;c<=cases;c++) {
        n = getInt();
        FOR(i, n) a[i] = getInt();
        int start = 0;
        int end = n - 1;
        int total = 0;
        FOR(i, n - 1) {
            int min = 1000000010;
            int pos = -1;
            FORE(j, start, end + 1) {
                if (a[j] < min) {
                    min = a[j];
                    pos = j;
                }
            }
            if (pos - start <= end - pos) {
                total += pos - start;
                for(int j=pos;j>start;j--) a[j] = a[j - 1];
                a[start] = min;
                start++;
            } else {
                total += end - pos;
                FORE(j, pos, end) a[j] = a[j + 1];
                a[end] = min;
                end--;
            }
        }

        printf("Case #%d: %d\n", c, total);
    }
}

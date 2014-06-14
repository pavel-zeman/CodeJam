// Try to count up so that the running sum is about one third of the total and then try numbers around the cut point
// https://code.google.com/codejam/contest/3024486/dashboard#s=p0
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1000020

int n;
int device[MAX_N];
long long int partial[MAX_N];



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

long long int total(int a, int b) {
    long long int s = a == 0 ? 0 : partial[a - 1];
    return partial[b] - s;
}

long long int max(long long int a, long long int b) {
    return a > b ? a : b;
}

int main(void) {
    int cases = getInt();
    for(int c=1;c<=cases;c++) {
        n = getInt();
        int p = getInt();
        int q = getInt();
        int r = getInt();
        int s = getInt();
        int mm = q - p;
        FOR(i, n) {
            mm = (mm + p) % r;
            device[i] = mm + s;
        }
        partial[0] = device[0];
        FORE(i, 1, n) partial[i] = partial[i - 1] + device[i];

        long long int sum = total(0, n - 1);
        long long int third = sum / 3;
        long long int s1 = 0;
        int m1 = 0;
        FOR(i, n - 1) {
            if (s1 + device[i] <= third) s1 += device[i];
            else {
                m1 = i - 1;
                break;
            }
        }
        int i = n - 1;
        long long int s3 = 0;
        int m3 = 0;
        while (i > 0) {
            if (s3 + device[i] <= third) s3 += device[i];
            else {
                m3 = i + 1;
                break;
            }
            i--;
        }
        long long int s2 = sum - s1 - s2;
        long long int res = sum;
        FORE(i, -6000, 6000) {
            if (m1 + i >= 0) {
                int s = m3 - 6000;
                if (s < m1 + i) s = m1 + i;
                int e = m3 + 6000;
                if (e > n) e = n;
                FORE(j, s, e) {
                    long long int s1 = total(0, m1 + i - 1);
                    long long int s2 = total(m1 + i, j);
                    long long int s3 = total(j + 1, n - 1);
                    long long int m = max(max(s1, s2), s3);
                    if (m < res) {
                        res = m;
                        //printf("%d %d ", m1 + i, m3 + j);
                    }
                }
            }
        }
        double d = sum - res;
        printf("Case #%d: %.10lf\n", c, d / sum);
    }
}

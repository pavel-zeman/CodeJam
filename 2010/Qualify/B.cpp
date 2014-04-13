#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


long long int t[10000];
int n;

long long int abs(long long int a) {
    return a < 0 ? -a : a;
}

long long int gcd(long long int a, long long int b) {
    while (b != 0) {
        long long int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d", &n);
        FOR(i, n) {
            scanf("%lld", t + i);
        }
        long long int tmax = abs(t[1] - t[0]);
        for(int i=2;i<n;i++) tmax = gcd(tmax, abs(t[i] - t[i - 1]));
        printf("Case #%d: %lld\n", c, (tmax - (t[0] % tmax)) % tmax);
    }
}

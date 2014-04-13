#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

long long int l, h;
int n;

long long int other[100000];

bool test(long long int f) {
    FOR(i, n)
        if (f % other[i] != 0 && other[i] % f != 0) return false;
    return true;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d%lld%lld", &n, &l, &h);
        FOR(i, n) scanf("%lld", &other[i]);

        long long int freq = -1;
        for(long long int i = l;i<=h;i++) {
            if (test(i)) {
                freq = i;
                break;
            }
        }

        printf("Case #%d: ", c);
        if (freq == -1) printf("NO\n"); else printf("%lld\n", freq);

    }
}

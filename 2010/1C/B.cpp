#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX 1001

long long int l, p, c;

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cas=1;cas<=cases;cas++) {
        scanf("%lld %lld %lld", &l, &p, &c);

        int steps = 0;
        while (l * c < p) { c *= c; steps++; }

        printf("Case #%d: %d\n", cas, steps);
    }
}

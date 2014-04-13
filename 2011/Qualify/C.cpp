#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        int n;
        int min = 1<<24;
        int total =0 ;
        int tx = 0;
        scanf("%d", &n);

        FOR(i, n) {
            int x;
            scanf("%d", &x);
            if (x < min) min = x;
            total += x;
            tx ^= x;
        }

        printf("Case #%d: ", c);

        if (tx == 0)
            printf("%d\n", total - min);
        else
            printf("NO\n");
    }
}

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
    int n, k;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d %d", &n, &k);
        printf("Case #%d: %s\n", c, (k % (1 << n)) == (1 << n) - 1 ? "ON" : "OFF");
    }
}

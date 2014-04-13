#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int n, k, b, t;
int pos[100];
int speed[100];
bool ok[100];

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d %d %d %d", &n, &k, &b, &t);
        FOR(i, n) scanf("%d", pos + i);
        FOR(i, n) scanf("%d", speed + i);
        FOR(i, n) ok[i] = false;

        int remain = k;
        int last;
        for(int i=n-1;i>=0;i--) {
            if (b - pos[i] <= t * speed[i]) {
                ok[i] = true;
                if (--remain == 0) {
                    last = i;
                    break;
                }
            }
        }

        //printf("Remain: %d %d %d %d\n", remain, last, k, n);
        if (remain > 0) {
            printf("Case #%d: IMPOSSIBLE\n", c);
        } else {
            int swapped = 0;
            int swaps = 0;
            for(int i = last;i<n;i++) {
                if (!ok[i]) {
                    swaps += i - last - swapped;
                    swapped++;
                }
            }
            printf("Case #%d: %d\n", c, swaps);
        }
    }
}

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int n;
int input[10000];

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d", &n);
        FOR(i, n) scanf("%d", &input[i]);
        FOR(i, n) input[i]--;

        double total = 0;
        FOR(i, n) {
            if (input[i] != i && input[i] != -1) {
                int z = i;
                int cycle = 0;
                while (input[z] != -1) {
                    int z2 = input[z];
                    input[z] = -1;
                    z = z2;
                    cycle++;
                }
                total += cycle;
            }
        }
        printf("Case #%d: %.6lf\n", c, total);
    }
}

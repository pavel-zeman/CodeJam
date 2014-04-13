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
int a[10000], b[10000];

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d", &n);
        FOR(i, n) scanf("%d %d", a + i, b + i);

        int total = 0;
        for(int i=0;i<n;i++) for(int j=i + 1;j<n;j++)
            if (a[i] < a[j] && b [i] > b[j] || a[i] > a[j] && b [i] < b[j]) total++;
        printf("Case #%d: %d\n", c, total);
    }
}

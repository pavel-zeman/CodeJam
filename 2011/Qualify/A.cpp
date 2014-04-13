#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int pos[2];
int tim[2];

int abs(int x) {
    return x >= 0 ? x : -x;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int ccc=1;ccc<=cases;ccc++) {
        int n;
        scanf("%d", &n);
        pos[0] = pos[1] = 1;
        tim[0] = tim[1] = 0;
        for (int i=0;i<n;i++) {
            char r[10];
            int p;
            scanf("%s%d", r, &p);

            int c = r[0] == 'O' ? 0 : 1;

            tim[c] += abs(p - pos[c]);
            pos[c] = p;
            tim[c] = max(tim[c], tim[c^1]);
            tim[c]++;

        }
        printf("Case #%d: %d\n", ccc, max(tim[0], tim[1]));
    }
}

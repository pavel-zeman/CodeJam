#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int x, s, r, t, n;

struct w {
    int b, e, w;
} walk[10000];


int compare(struct w *a, struct w *b) {
    return a->w - b->w;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d%d%d%d%d", &x, &s, &r, &t, &n);
        FOR(i, n) scanf("%d%d%d", &walk[i].b, &walk[i].e, &walk[i].w);
        qsort(walk, n, sizeof(walk[0]), (int(*)(const void *, const void *))compare);

        double totalTime = 0;
        double remainingRun = t;

        int totalWalkLine = 0;
        FOR (i, n) totalWalkLine += walk[i].e - walk[i].b;

        double runDist = r * remainingRun;
        if (runDist > x - totalWalkLine) runDist = x - totalWalkLine;
        totalTime += runDist / r;
        totalTime += (x - totalWalkLine - runDist) / s;

        remainingRun -= runDist / r;



        int pos = 0;
        while (remainingRun > 0 && pos < n) {
            double runTime = (((double)walk[pos].e) - walk[pos].b) / (walk[pos].w + r);
            if (runTime <= remainingRun) {
                totalTime += runTime;
                remainingRun -= runTime;
            } else {
                double runDist = (walk[pos].w + r) * remainingRun;
                totalTime += remainingRun;
                remainingRun = 0;
                totalTime += (((double)walk[pos].e) - walk[pos].b - runDist) / (walk[pos].w + s);
            }
            pos++;
        }

        while (pos < n) {
            totalTime += (((double)walk[pos].e) - walk[pos].b) / (walk[pos].w + s);
            pos++;
        }



        printf("Case #%d: %.10lf\n", c, totalTime);
    }
}

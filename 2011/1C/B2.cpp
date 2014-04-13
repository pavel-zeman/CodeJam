#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int l, n, c;
long long int t;

int a[10000];
int dist[10000000];
//long long int saves[10000000];

bool placed[10000000];

double result = 1e30;

int indCount;
int indices[10000000];


double calcTime() {
    double total = 0;
    FOR(i, n) {
        if (!placed[i]) {
            total += dist[i] * 2;
        } else {
            if (total >= t) {
                total += dist[i];
            } else if (t >= total + dist[i] * 2) {
                total += dist[i] * 2;
            } else {
                double part = (t - total) / 2;
                total = t + (dist[i] - part);
            }
        }
    }
    return total;
}

int compare(const int *a, const int *b) {
    return dist[*b] - dist[*a];
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cas=1;cas<=cases;cas++) {
        scanf("%d %lld %d %d", &l, &t, &n, &c);
        FOR(i, c) scanf("%d", &a[i]);
        FOR(i, n) dist[i] = a[i % c];

        // first to build
        long long int total = 0;
        int start = n;
        FOR(i, n) {
            if (t < total + dist[i] * 2) {
                start = i;
                break;
            }
            total += dist[i] * 2;
        }

        FOR(i, n) placed[i] = false;

        if (start < n && l > 0) {
            indCount = n - start - 1;
            FOR(i, indCount) indices[i] = start + 1 + i;
            qsort(indices, indCount, sizeof(int), (int(*)(const void *, const void *))compare);

            FOR(i, l) placed[indices[i]] = true;

            result = calcTime();

            FOR(i, n) placed[i] = false;
            placed[start] = true;
            FOR(i, l - 1) placed[indices[i]] = true;
            double res2 = calcTime();
            if (res2 < result) result = res2;
        } else {
            result = calcTime();
        }


        printf("Case #%d: %.0lf\n", cas, result);
    }
}

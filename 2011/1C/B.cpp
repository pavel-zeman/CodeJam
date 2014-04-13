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

void check(int todo, int start) {
    if (todo == 0) {
        double res = calcTime();
        if (res < result) result = res;
    } else {
        for(int i=start;i<n;i++) {
            placed[i] = true;
            check(todo - 1, i + 1);
            placed[i] = false;
        }
    }
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cas=1;cas<=cases;cas++) {
        scanf("%d %lld %d %d", &l, &t, &n, &c);
        FOR(i, c) scanf("%d", &a[i]);
        FOR(i, n) dist[i] = a[i % c];

        FOR(i, n) placed[i] = false;

        result = 1e30;
        check(l, 0);

        printf("Case #%d: %.0lf\n", cas, result);
    }
}

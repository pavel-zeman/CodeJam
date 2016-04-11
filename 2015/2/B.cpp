//
// https://code.google.com/codejam/contest/8234486/dashboard#s=p1
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <set>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 110

int n;
double v;
double x;
double r[MAX_N];
double c[MAX_N];
double e = 1e-12;

int getInt() {
    int d;
    scanf("%d", &d);
    return d;
}

double max(double x, double y) {
    return x > y ? x : y;
}

double min(double x, double y) {
    return x < y ? x : y;
}

int main(void) {
    int cases = getInt();
    for(int cc=1;cc<=cases;cc++) {
        n = getInt();
        scanf("%lf %lf", &v, &x);
        FOR(i, n) scanf("%lf %lf", &r[i], &c[i]);
        //printf("%lf %lf\n", v, x);
        //FOR(i, n) printf("%lf %lf\n", r[i], c[i]);

        bool possible = true;
        double result;
        if (n == 1) {
            if (c[0] == x) result = v / r[0]; else possible = false;
        } else {
            if (c[0] == x || c[1] == x) {
                if (c[0] == x) {
                    result = v / r[0];
                    if (c[1] == x) result = v / (r[0] + r[1]);
                } else result = v / r[1];
            } else if (c[0] < x && c[1] < x || c[0] > x && c[1] > x) possible = false;
            else {
                double t2 = r[1] + r[1] * (c[1] - x) / (x - c[0]);
                t2 = v / t2;
                double t1 = t2 * r[1] * (c[1] - x) / r[0] / (x - c[0]);
                //printf("%lf %lf\n", t1, t2);
                //if (t1 >= -e && t2 >= -e) result = max(t1, t2); else possible = false;
                result = max(t1, t2);
                double resultC = (t1 * r[0] * c[0] + t2 * r[1] * c[1]) / v;

                double v0 = v * (x - c[1]) / (c[0] - c[1]);
                double v1 = v - v0;
                result = max(v0 / r[0], v1 / r[1]);
                //printf("%.10lf %.10lf %.10lf %.10lf %.10lf\n", t1, t2, x, resultC, resultC - x);
            }
        }

        if (possible) printf("Case #%d: %.10lf\n", cc, result);
        else printf("Case #%d: IMPOSSIBLE\n", cc);
    }
}

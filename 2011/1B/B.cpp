#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define M ((double)1e-9)

struct item {
    double center;
    double min;
    double max;
    double time;
    int count;
} items[1000];

int d;
int c;

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d%d", &c, &d);
        FOR(i, c) {
            int p, v;
            scanf("%d%d", &p, &v);
            item[i].center = p;
            item[i].pos = p;
            item[i].count = v;
            item[i].time = (((double)v - 1) * d) / 2;
            item[i].min = item[i].center - item[i].time;
            item[i].min = item[i].center + item[i].time;
        }

        bool problem = true;
        while (problem) {
            problem = false;
            FOR(i, c - 1)
                if (item[i].max > item[i+1].min + M) {

                }


        printf("Case #%d:", c);
    }
}

// If we reduce each group of the same characters to just a single character, then all the resulting strings must be the same. Minimum can then be calculated easily.
// https://code.google.com/codejam/contest/2994486/dashboard#s=p0
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 120
#define MAX_LENGTH 120

char line[MAX_N][MAX_LENGTH];
int globalItemCount[MAX_N];

struct Item {
    char c;
    int count;
} items[MAX_N][MAX_LENGTH];

int absa(int a) {
    return a < 0 ? -a : a;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        int n;
        scanf("%d", &n);
        FOR(i, n) {
            char temp[MAX_LENGTH];
            scanf("%s", temp);

            char *a = temp;
            char last = temp[0];
            int count = 0;
            int itemCount = 0;
            while (*a) {
                if (*a == last) count++; else {
                    items[i][itemCount].c = last;
                    items[i][itemCount].count = count;
                    count = 1;
                    itemCount++;
                    last = *a;
                }
                a++;
            }
            items[i][itemCount].c = last;
            items[i][itemCount].count = count;
            globalItemCount[i] = itemCount + 1;
        }

        bool ok = true;
        FORE(i, 1, n) {
            if (globalItemCount[i] != globalItemCount[0]) {
                ok = false;
                break;
            }
            FOR(j, globalItemCount[0]) {
                if (items[i][j].c != items[0][j].c) {
                    ok = false;
                    break;
                }
            }
            if (!ok) break;
        }

        printf("Case #%d: ", c);
        if (!ok) {
            printf("Fegla Won\n");
        } else {
            int total = 0;
            FOR(j, globalItemCount[0]) {
                int min = MAX_LENGTH * MAX_N;
                FORE(k, 1, MAX_LENGTH) {
                    int local = 0;
                    FOR(i, n) local += absa(items[i][j].count - k);
                    if (local < min) min = local;
                }
                total += min;
            }
            printf("%d\n", total);
        }
    }
}

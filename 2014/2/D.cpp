// Naïve brute force algorithm
// https://code.google.com/codejam/contest/3014486/dashboard#s=p3
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_M 10
#define MAX_LENGTH 20
#define MAX_ITEMS 10000
#define MAX_N 10
#define MAX_C 26

int n, m;
char s[MAX_M][MAX_LENGTH];
int sPos[MAX_M];
int max;
int count;

struct item {
    int next[MAX_C];
} items[MAX_ITEMS];
int usedItems;
int firstItem[MAX_N];

int getItem() {
    FOR(i, MAX_C) items[usedItems].next[i] = -1;
    return usedItems++;
}

void build() {
    FOR(i, n) firstItem[i] = -1;
    usedItems = 0;
    FOR(i, m) {
        int pos = sPos[i];
        if (firstItem[pos] == -1) firstItem[pos] = getItem();
        int item = firstItem[pos];
        char *c = s[i];
        while (*c) {
            if (items[item].next[*c - 'A'] == -1) {
                items[item].next[*c - 'A'] = getItem();
            }
            item = items[item].next[*c - 'A'];
            c++;
        }
    }
    if (usedItems > max) {
        max = usedItems;
        count = 0;
    }
    if (usedItems == max) count++;
}

void check(int pos) {
    if (pos < m) {
        FOR(i, n) {
            sPos[pos] = i;
            check(pos + 1);
        }
    } else build();
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d%d", &m, &n);
        FOR(i, m) scanf("%s", s[i]);
        max = 0;
        count = 0;
        check(0);

        printf("Case #%d: %d %d\n", c, max, count);
    }
}

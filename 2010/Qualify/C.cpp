#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int r, k, n;
int g[10000];
char used[10000];


void singleRound(int pointer, int *euros, int *next) {
    int startPointer = pointer;
    int remain = k;
    do {
        remain -= g[pointer];
        pointer++;
        pointer %= n;
    } while (remain >= g[pointer] && pointer != startPointer);
    *euros = k - remain;
    *next = pointer;
}




int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d %d %d", &r, &k, &n);
        FOR(i, n) scanf("%d", g + i);
        FOR(i, n) used[i] = 0;

        long long euros1 = 0;
        long long euros2 = 0;
        int rounds1 = 0;
        int rounds2 = 0;
        int pointer = 0;

        // find start of cycle
        do {
            int euros;
            int nextPointer;
            used[pointer] = 1;
            singleRound(pointer, &euros, &nextPointer);
            pointer = nextPointer;
        } while (!used[pointer]);

        int startRound = pointer;

        // up to the start of the round
        pointer = 0;
        do {
            int euros;
            int nextPointer;
            singleRound(pointer, &euros, &nextPointer);
            pointer = nextPointer;
            euros1 += euros;
            rounds1++;
        } while (pointer != startRound);

        // single round
        do {
            int euros;
            int nextPointer;
            singleRound(pointer, &euros, &nextPointer);
            pointer = nextPointer;
            euros2 += euros;
            rounds2++;
        } while (pointer != startRound);


        long long int eurosTotal;
        if (r >= rounds1) {
            r -= rounds1;
            eurosTotal = euros1 + r / rounds2 * euros2;
            r %= rounds2;
        } else {
            pointer = 0;
            eurosTotal = 0;
        }


        // last part
        while (r--) {
            int euros;
            int nextPointer;
            singleRound(pointer, &euros, &nextPointer);
            pointer = nextPointer;
            eurosTotal += euros;
        }

        printf("Case #%d: %lld\n", c, eurosTotal);
    }
}

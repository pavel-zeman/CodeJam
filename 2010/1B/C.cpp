#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define MOD 100003

int n;

int fib[10000];

int numbers[1000];

bool test(int x, int must) {
    int total = 0;
    int pos = 0;
    while (x > 0) {
        if ((x & 1) == 1) {
            numbers[total++] = pos + 2;
        }
        pos++;
        x >>= 1;
    }
    numbers[total++] = must;
    numbers[total] = must + 1;

    int curr = must;
    while (curr > 1) {
        //printf("Testing %d\n", curr);
        pos = 0;
        while (pos < total && curr > numbers[pos]) pos++;
        if (numbers[pos] != curr) return false;
        curr = pos + 1;
    }
    return true;
}

int main(void) {
    fib[0] = 1;
    fib[1] = 1;
    for(int i = 2;i<10000;i++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
    }


    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d", &n);
        int total = 0;
        int last = (1 << (n - 2));
        for(int i=0;i<last;i++) {
            if (test(i, n)) total++;

        }
        printf("Case #%d: %d\n", c, total % MOD);
    }
}

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX 10000

int primes[10000];
int primeCount;
int d, k;
int numbers[10];
int maxInput;

int main(void) {

    primes[0] = 2;
    primeCount = 1;

    FORE(i, 3, MAX) {
        bool prime = true;
        FOR(j, primeCount) {
            if (i % primes[j] == 0) {
                prime = false;
                break;
            }
            if (primes[j] * primes[j] > i) break;
        }
        if (prime) {
            primes[primeCount++] = i;
        }
    }

    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d %d", &d, &k);
        maxInput = 0;
        FOR(i, k) {
            scanf("%d", &numbers[i]);
            if (numbers[i] > maxInput) maxInput = numbers[i];
        }

        if (k == 1) {
            printf("Case #%d: I don't know.\n", c);
        } else {
            int next = -1;
            int max = 1;
            bool know = true;
            FOR(i, d) max *= 10;

            FOR(i, primeCount) {
                int p = primes[i];
                if (p > max) break;
                if (p > maxInput) {
                    FOR(a, p) {
                        int res = (a * numbers[0]) % p;
                        int b = (numbers[1] - res + p) % p;
                        bool ok = true;
                        FOR(j, k - 1) {
                            if ((a * numbers[j] + b) % p != numbers[j + 1]) {
                                ok = false;
                                break;
                            }
                        }
                        if (ok) {
                            int next1 = (a * numbers[k - 1] + b) % p;
                            if (next == -1) next = next1; else
                            if (next != next1) {
                                know = false;
                                goto end;
                            }
                        }

                    }
                }
            }
            end:

            if (know)
                printf("Case #%d: %d\n", c, next);
            else
                printf("Case #%d: I don't know.\n", c);
        }
    }
}

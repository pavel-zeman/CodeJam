#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


long long a, b, p;

int set[2000];


char used[2000];

int primes[1000];

int primeCount;

char isPrime(int i) {
  int end = (int)sqrt(i);
  FORE(j, 2, end + 1)
    if (i % j == 0) return 0;
  return 1;
}

void mergeSet(int dst, int src) {
  if (dst != src) {
    FOR(i, b - a + 1)
      if (set[i] == dst) set[i] = src;
  }
}

int main(void) {
  primeCount = 0;
  FORE(i, 2, 1000000)
    if (isPrime(i))
      primes[primeCount++] = i;

  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%lld %lld %lld", &a, &b, &p);

    FOR(i, b-a+1) { set[i] = i; used[i] = 0;}

    FORE(i, a, b + 1) {
      FOR(j, primeCount) {
        if (primes[j] >= p && (i % primes[j] == 0)) {
          int s = set[i - a];
          int k = i + primes[j];
          while (k <= b) {
            mergeSet(set[k - a], s);
            k += primes[j];
          }
        }
      }
    }

    int total = 0;
    FOR(i, b - a + 1)
      if (!used[set[i]]) {
        used[set[i]] = 1;
        total++;
      }

    //FOR(i, b - a + 1) printf("%d ", set[i]);

    printf("Case #%d: %d\n", c, total);
  }
}

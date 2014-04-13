#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

long long a, b, p;

// set values - number of set, to which this value belongs
int set[2000000];

// pointer to the first item of the set
struct {
  int first;
  int count;
} setFirst[2000000];

struct {
  int value;
  int next;
} setItem[2000000];

int primes[100000];
int primeCount;

char isPrime(int i) {
  int end = (int)sqrt(i);
  FOR(j, primeCount) {
    if (primes[j] > end) return 1;
    if (i % primes[j] == 0) return 0;
  }
  return 1;
}

int mergeSet(int dst, int src) {
  if (dst != src) {
    if (setFirst[src].count < setFirst[dst].count) { int x = src; src = dst; dst = x; }

    int next = setFirst[dst].first;
    while (true) {
      set[setItem[next].value] = src;
      if (setItem[next].next == -1) break; else next = setItem[next].next;
    }
    setItem[next].next = setFirst[src].first;
    setFirst[src].first = setFirst[dst].first;
    setFirst[dst].first = -1;
    setFirst[src].count += setFirst[dst].count;
  }
  return src;
}

int main(void) {
  primeCount = 0;
  FORE(i, 2, 1000002)
    if (isPrime(i))
      primes[primeCount++] = i;

  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%lld %lld %lld", &a, &b, &p);

    FOR(i, b-a+1) {
      set[i] = setFirst[i].first = setItem[i].value = i;
      setFirst[i].count = 1;
      setItem[i].next = -1;
    }


    int length = b - a;
    FOR(i, primeCount)
      if (primes[i] >= p && primes[i] <= length) {
        long long rem = a % primes[i];
        long long k = rem == 0 ? a : a + primes[i] - rem;
        int s = set[k - a];

        k += primes[i];
        while (k <= b) {
          if (set[k - a] != s)
           s = mergeSet(set[k - a], s);
          k += primes[i];
        }
      }

    int total = 0;
    FOR(i, b - a + 1)
      if (setFirst[i].first != -1) total++;

    printf("Case #%d: %d\n", c, total);
  }
}

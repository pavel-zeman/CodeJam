#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int p, k, l;
int freq[1000];

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %d %d", &p, &k, &l);
    FOR(i, l) scanf("%d", &freq[i]);

    FOR(i, l - 1) FORE(j, i + 1, l)
      if (freq[i] < freq[j]) { int t = freq[i]; freq[i] = freq[j]; freq[j] = t; }

    long long total = 0;
    FOR(i, l)
      total += freq[i] * ((i / k) + 1);

    printf("Case #%d: %lld\n", c, total);
  }
}

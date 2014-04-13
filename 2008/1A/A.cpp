#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int n;
int a1[1000], a2[1000];

void sort1(int * x, int c) {
  FOR(i, c - 1) FORE(j, i+1, c) 
    if (x[i] > x[j]) {
      int t = x[i];
      x[i] = x[j];
      x[j] = t;
    }
}

void sort2(int * x, int c) {
  FOR(i, c - 1) FORE(j, i+1, c) 
    if (x[i] < x[j]) {
      int t = x[i];
      x[i] = x[j];
      x[j] = t;
    }
}

      

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d", &n);
    FOR(i, n) scanf("%d", &a1[i]);
    FOR(i, n) scanf("%d", &a2[i]);
    
    sort1(a1, n);
    sort2(a2, n);
    
    long long total = 0;
    FOR(i, n) {
      long long t1 = a1[i];
      long long t2 = a2[i];
      total += t1 * t2;
    }
    
    printf("Case #%d: %lld\n", c, total);
  }
}

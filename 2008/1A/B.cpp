#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define N 20
#define M 100


int n, m;


struct {
  char shakes[2*N];
} cust[101];
  

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    // read input
    scanf("%d %d", &n, &m);
    FOR(i, m) {
      int t;
      scanf("%d", &t);
      FOR(j, 2*N) cust[i].shakes[j] = 0;
      FOR(j, t) {
        int x, y;
        scanf("%d %d", &x, &y);
        cust[i].shakes[x - 1 + y * N] = 1;
      }
    }
    
    // test all possibilities
    int minValue = -1, minMalted = n + 1;

    FOR(i, 1 << n) {
      char satisfied[M];
      FOR(j, m) satisfied[j] = 0;
      int t = i;
      int totalMalted = 0;
      
      FOR(j, n) {
        int malted = t & 1;
        totalMalted += malted;
        FOR(k, m) if (cust[k].shakes[j + malted * N]) satisfied[k] = 1;
        t >>= 1;
      }
      
      int totalSatisfied = 0;
      FOR(j, m) totalSatisfied += satisfied[j];
      if (totalSatisfied == m && totalMalted < minMalted) {
        minValue = i;
        minMalted = totalMalted;
      }
    }
        
    printf("Case #%d:", c);
    
    if (minValue == -1) printf(" IMPOSSIBLE"); else {
      int t = minValue; 
      FOR(i, n) { printf(" %d", t & 1); t >>= 1; }
    }
    printf("\n");
  }
}

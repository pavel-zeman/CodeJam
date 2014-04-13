#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int s;
int q;

int currentPosition;

struct {
  char name[200];
} engines[101];

int queries[1001];


int getEngine(char * query) {
  FOR(i, s) if (!strcmp(query, engines[i].name)) return i;
  printf("Can't find engine %s\n", query);
  exit(0);
}

void findLongest(void) {
  int maxPos = currentPosition;
  FOR(i, s) {
    int j = currentPosition;
    while (j < q && queries[j] != i) j++;
    if (j > maxPos) maxPos = j;
  }  
  currentPosition = maxPos;
}

int main(void) {
  int cases;
  char temp[200];
  gets(temp);
  cases = atoi(temp);
  for(int c=1;c<=cases;c++) {
    gets(temp); s = atoi(temp);
    FOR(i, s) gets(engines[i].name);
    gets(temp); q = atoi(temp);
    FOR(i, q) {
      gets(temp);
      queries[i] = getEngine(temp);
    }
    
    int switches = 0;
    currentPosition = 0;
    findLongest();
    while (currentPosition < q) {
      switches++;
      findLongest();
    }
    printf("Case #%d: %d\n", c, switches);
  }
}

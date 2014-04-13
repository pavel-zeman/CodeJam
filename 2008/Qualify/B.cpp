#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int turnaround;

int numTtA, numTtB;
int numTrainsA, numTrainsB;
int posTtA, posTtB;

struct tt {
  int start;
  int end;
} ttA[1000], ttB[1000];


struct station {
  int departures[1000];
  int trains;
  
  void getTrain(int time, int * numTrains) {
    if (trains > 0 && departures[0] <= time) {
      // OK, we have it
      trains--;
      FOR(i, trains) departures[i] = departures[i + 1];
    } else // no train, need to add one
      (*numTrains)++;
  }
  
  void addTrain(int time) {
    int pos = 0;
    while (pos < trains && departures[pos] < time) pos++;
    for(int i=trains;i>pos;i--) departures[i] = departures[i-1];
    trains++;
    departures[pos] = time;
  }  

} stationA, stationB;


int getTime(char * data) {
  data[2] = 0;
  return atoi(data) * 60 + atoi(data+3);
}

void readTimes(struct tt * where, int count) {
  // read it
  FOR(i, count) {
    char temp1[10], temp2[10];
    scanf("%s %s", temp1, temp2);
    where[i].start = getTime(temp1);
    where[i].end = getTime(temp2);
  }
  
  // and sort it
  struct tt temp;
  FOR(i, count - 1)
    FORE(j, i+1, count)
      if (where[i].start > where[j].start) {
        temp = where[i];
        where[i] = where[j];
        where[j] = temp;
      }
}

void solve(void) {
  while (posTtA < numTtA || posTtB < numTtB) {
    if (posTtA < numTtA && (posTtB == numTtB || ttA[posTtA].start <= ttB[posTtB].start)) {
      // choose A
      stationA.getTrain(ttA[posTtA].start, &numTrainsA);
      stationB.addTrain(ttA[posTtA].end + turnaround);
      posTtA++;
    } else {
      // choose B
      stationB.getTrain(ttB[posTtB].start, &numTrainsB);
      stationA.addTrain(ttB[posTtB].end + turnaround);
      posTtB++;
    }
  }
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d", &turnaround);
    scanf("%d %d", &numTtA, &numTtB);
    readTimes(ttA, numTtA);
    readTimes(ttB, numTtB);
    
    numTrainsA = numTrainsB = 0;
    stationA.trains = stationB.trains = 0;
    posTtA = posTtB = 0;
    
    solve();
    
    printf("Case #%d: %d %d\n", c, numTrainsA, numTrainsB);
  }
}

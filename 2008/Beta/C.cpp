#include <stdio.h>
#include <string.h>
#include <limits.h>



int numRoads;
int numCities;

int directDistance[100][100];
int numDirectRoutes[100][100];

int minDistance[100][100];
int numRoutes[100][100];

struct {
  char city1[100];
  char city2[100];
  int id1;
  int id2;
  int time;
  double prob;
} roads[50];


struct {
  char name[100];
} cities[100];


int getCity(char city[100]) {
  int j =0;
  while (j < numCities && strcmp(city, cities[j].name)) j++;
  if (j == numCities) {
    strcpy(cities[j].name, city);
    numCities++;
  }
  return j;
}


void calculateMinDistances() {
  for(int i=0;i<100;i++) for(int j=0;j<100;j++) directDistance[i][j] = numDirectRoutes[i][j] = minDistance[i][j] = numRoutes[i][j] = 0;
  for(int i=0;i<100;i++) numDirectRoutes[i][i] = 1;
  
  // initialize routes
  for(int i=0;i<numRoads;i++) {
    if (directDistance[roads[i].id1][roads[i].id2] == 0 || directDistance[roads[i].id1][roads[i].id2] == roads[i].time) {
      directDistance[roads[i].id1][roads[i].id2] = roads[i].time;
      numDirectRoutes[roads[i].id1][roads[i].id2]++;
    } else if (roads[i].time < directDistance[roads[i].id1][roads[i].id2]) {
      directDistance[roads[i].id1][roads[i].id2] = roads[i].time;
      numDirectRoutes[roads[i].id1][roads[i].id2] = 1;
    }
  }
  
  int localMinRoute[100];
  char fixed[100];
  
  // Dijkstra's algorithm
  for(int i=0;i<numCities;i++) {
    for(int j=0;j<numCities;localMinRoute[j++] = INT_MAX);
    for(int j=0;j<numCities;fixed[j++] = 0);
    
    localMinRoute[i] = 0;
    
    for(int c=0;c<numCities;c++) {
      // find minimum distance
      int minDist = INT_MAX;
      int minPos = 0;
      for(int j=0;j<numCities;j++) 
        if (!fixed[j] && localMinRoute[j] < minDist) { minDist = localMinRoute[j]; minPos = j;}
      
      if (minDist == INT_MAX) break;
      
      fixed[minPos] = 1;
      
      
      for(int j=0;j<numCities;j++) {
        if (directDistance[minPos][j] != 0 && localMinRoute[minPos] + directDistance[minPos][j] < localMinRoute[j]) 
          localMinRoute[j] = localMinRoute[minPos] + directDistance[minPos][j];
      }
    }
    
    for(int j=0;j<numCities;j++)
      if (localMinRoute[j] != INT_MAX)
        minDistance[i][j] = localMinRoute[j];
  }
}


int getRoutes(int x, int y) {
  if (numRoutes[x][y] != -1) return numRoutes[x][y];
  
  int total = 0;
  for(int i=0;i<numCities;i++) {
    if (directDistance[x][i] != 0 && directDistance[x][i] + minDistance[i][y] == minDistance[x][y])
       total += numDirectRoutes[x][i] * getRoutes(i, y);
  }
  return (numRoutes[x][y] = total);
}

void calculateRoutes(void) {
  for(int i=0;i<numCities;i++) for(int j=0;j<numCities;j++) numRoutes[i][j] = -1;
  for(int i=0;i<numCities;i++) numRoutes[i][i] = 1;
  
  for(int i=0;i<numCities;i++) for(int j=0;j<numCities;j++) getRoutes(i, j);    
}

void calculateProbability(int start) {
  int drivC = 0;
  for(int i=0;i<numCities;i++)
    if (i != start) {
       int totalRoutes = numRoutes[start][i];
       int mind = minDistance[start][i];
       if (totalRoutes > 0) {
          drivC++;
          for(int j=0;j<numRoads;j++) {
            if (minDistance[start][roads[j].id1] + roads[j].time + minDistance[roads[j].id2][i] == mind) {
              roads[j].prob += numRoutes[start][roads[j].id1] * numRoutes[roads[j].id2][i]/(double)totalRoutes;
            }
          }
       }
    }
  for(int i=0;i<numRoads;i++) roads[i].prob /= drivC;
}

int main(void) {
  int cases;
  char temp[100];
  scanf("%d", &cases);
  
  for(int c=1;c<=cases;c++) {
    scanf("%d %s", &numRoads, temp);
    numCities = 0;
    for(int i=0;i<numRoads;i++) {
      scanf("%s %s %d", roads[i].city1, roads[i].city2, &roads[i].time);
      roads[i].id1 = getCity(roads[i].city1);
      roads[i].id2 = getCity(roads[i].city2);
      roads[i].prob = 0;
    }

    calculateMinDistances();
    calculateRoutes();
    calculateProbability(getCity(temp));
    
    printf("Case #%d:", c);
    for(int i=0;i<numRoads;i++) printf(" %.7f", roads[i].prob);
    printf("\n");
  }
}

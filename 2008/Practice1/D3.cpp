#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int numItems;
int numStores;
int priceOfGas;

struct {
  char name[100];
  char perishable;
  int numStores;
  struct {
    int id;
    int price;
  } stores[50];
} items[15];


struct {
  int x;
  int y;
} stores[52];

#define MAXD 999999999.0

double minArray[1<<15][51][2];
double distances[51][51];

double sqr(double x) {
  return x * x;
}

double distance(int from, int to) {
  return distances[from][to];
}

double solve(int remainingItems, char lastPerishable, int lastShop) {
  if (minArray[remainingItems][lastShop][lastPerishable] != MAXD) 
    return minArray[remainingItems][lastShop][lastPerishable];

  if (remainingItems == 0) {
     double d = distance(lastShop, 0);
     minArray[0][lastShop][0] = minArray[0][lastShop][1] = d;
     return d;
  } else {
    double localMin = MAXD;
    for(int i=0;i<numItems;i++) {
      if ((remainingItems & (1<<i)) != 0) {
         if (!lastPerishable) {
           for(int j=0;j<items[i].numStores;j++) {
             double res = solve(remainingItems ^ (1<<i), items[i].perishable, items[i].stores[j].id) + 
                    items[i].stores[j].price + distance(lastShop, items[i].stores[j].id);
             if (res < localMin) localMin = res;
           }
         } else {
           // try local store
           for(int j=0;j<items[i].numStores;j++)
             if (items[i].stores[j].id == lastShop) {
               double res = solve(remainingItems ^ (1<<i), 1, lastShop) + items[i].stores[j].price;
               if (res < localMin) localMin = res;
               break;
             }
           // and go back home
           double res = solve(remainingItems, 0, 0) + distance(lastShop, 0);
           if (res < localMin) localMin = res;
         }
      }
    }
    minArray[remainingItems][lastShop][lastPerishable] = localMin;
    return localMin;
  }
}


int main(void) {
  int cases;
  char temp[1000];
  
  // home is just a special store
  stores[0].x = 0;
  stores[0].y = 0;
  
  scanf("%d", &cases);
  scanf("%s", temp);
  for(int c=1;c<=cases;c++) {
    numItems = atoi(temp);
    scanf("%d %d", &numStores, &priceOfGas);
    // read items
    for(int i=0;i<numItems;i++) {
      scanf("%s", items[i].name);
      int l = strlen(items[i].name) - 1;
      if (items[i].name[l] == '!') {
        items[i].perishable = 1;
        items[i].name[l] = 0;
      } else items[i].perishable = 0;
      items[i].numStores = 0;
    }              
    
    // read stores
    scanf("%s", temp);
    for(int i=1;i<=numStores;i++) {
      stores[i].x = atoi(temp);
      scanf("%d %s", &stores[i].y, temp);
      char *colonPos;
      while ((colonPos = strchr(temp, ':')) != NULL) {
        *colonPos = 0;
        int j = 0;
        while (strcmp(temp, items[j].name)) j++;
        items[j].stores[items[j].numStores].id = i;
        items[j].stores[items[j].numStores].price = atoi(colonPos + 1);
        items[j].numStores++;
        if (scanf("%s", temp) == EOF) break;
      }
    }
    
    // now we have all the data, so try to solve the problem :)
    for(int i=0;i<(1<<numItems);i++)
      for(int j=0;j<=numStores;j++)
        minArray[i][j][0] = minArray[i][j][1] = MAXD;
    for(int i=0;i<=numStores;i++)
      for(int j=0;j<=numStores;j++)
        distances[i][j] = sqrt(sqr(stores[i].x - stores[j].x) + sqr(stores[i].y - stores[j].y)) * priceOfGas;

    solve((1<<numItems) - 1, 0, 0);
    printf("Case #%d: %.7lf\n", c, minArray[(1<<numItems) - 1][0][0]);
  }
}

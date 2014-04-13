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
    int x;
    int y;
  } stores[50];
} items[15];


struct {
  int x;
  int y;
  int numItems;
  struct {
    int id;
    int price;
  } items[15];
} stores[52];

#define MAXD 9999999

double min;


double minArray[1<<15];

double sqr(double x) {
  return x * x;
}

double distance(int from, int to) {
  return sqrt(sqr(stores[from].x - stores[to].x) + sqr(stores[from].y + stores[to].y)) * priceOfGas;
}

double solve(int remainingItems, char lastPerishable, int lastShop, double currentSum) {
  if (currentSum >= min) return MAXD;
  
  if (remainingItems == 0) {
     double d = distance(lastShop, 0);
     currentSum += d;
     if (currentSum < min) {
       //printf("Min: %.20lf %.20lf\n", min, currentSum);
       min = currentSum;
     }
     return d;
  } else {
    if (lastShop == 0 && minArray[remainingItems] != MAXD) return minArray[remainingItems];
    double localMin = MAXD;
    for(int i=0;i<numItems;i++) {
      if ((remainingItems & (1<<i)) != 0) {
         int localStorePrice = INT_MAX;
         if (lastShop != 0)
           for(int j=0;j<items[i].numStores;j++)
             if (items[i].stores[j].id == lastShop) {
                localStorePrice = items[i].stores[j].price;
                localMin = solve(remainingItems ^ (1<<i), lastPerishable || items[i].perishable, lastShop, currentSum + localStorePrice) + localStorePrice;
             }
         
         if (!lastPerishable) {
           for(int j=0;j<items[i].numStores;j++) {
             if (items[i].stores[j].id != lastShop && items[i].stores[j].price < localStorePrice) {
               double d = distance(lastShop, items[i].stores[j].id); 
               double res = solve(remainingItems ^ (1<<i), 
                 items[i].perishable, 
                 items[i].stores[j].id, currentSum + items[i].stores[j].price + d) + items[i].stores[j].price + d;
               if (res < localMin) localMin = res;
             }
           }
         } else {
           // must go back home
           double d = distance(lastShop, 0);
           double res = solve(remainingItems, 0, 0, currentSum + d) + d;
           if (res < localMin) localMin = res;
         }
      }
    }
    if (lastShop == 0) minArray[remainingItems] = localMin;
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
      int itemsInStore = 0;
      while ((colonPos = strchr(temp, ':')) != NULL) {
        *colonPos = 0;
        int j = 0;
        while (strcmp(temp, items[j].name)) j++;
        stores[i].items[itemsInStore].id = j;
        stores[i].items[itemsInStore].price = atoi(colonPos + 1);
        scanf("%s", temp);
        items[j].stores[items[j].numStores].id = i;
        items[j].stores[items[j].numStores].price = stores[i].items[itemsInStore].price;
        items[j].stores[items[j].numStores].x = stores[i].x;
        items[j].stores[items[j].numStores].y = stores[i].y;
        items[j].numStores++;
        itemsInStore++;
      }
      stores[i].numItems = itemsInStore;
    }
    
    // now we have all the data, so try to solve the problem :)
    min = MAXD;
    for(int i=0;i<sizeof(minArray)/sizeof(double);minArray[i++] = MAXD);
    solve((1<<numItems) - 1, 0, 0, 0);
    printf("Case #%d: %.7lf\n", c, min);
  }
}

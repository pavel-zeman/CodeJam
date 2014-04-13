#include <stdio.h>
#include <limits.h>
#include <string.h>


#define W 95000
#define H 34

long long data[H][W];
long long max = 1;
long long maxAccepted = 1;

void fillData() {
  memset(data, 0, sizeof(data));
  for(int i=1;i<40;i++) max <<= 1;
  for(int i=0;i<32;i++) maxAccepted <<= 1;
  for(int i=1;i<W;i++) data[1][i] = i;
  for(int i=2;i<H;i++) data[i][1] = 1;
  
  for(int i=2;i<H;i++) {
    for(int j=2;j<W;j++) {
      data[i][j] = data[i][j-1] + data[i-1][j-1] + 1;
      if (data[i][j] > max) {
         data[i][j] = 0;
         break;
      }
    }
  }
}


unsigned int findMaximumF(int d, int b) {
  unsigned long long result;
  if (b >= d) {
    // the result is driven by d
    if (d >= 33) return 0;
    result = 1;
    return (result<<d) - 1;
  } else {
    // b < d
    if (b == 1) return d;
    if (b >= 33) return 0;
    // now 33 > b > 1
    if (d >= W) return 0;
    return data[b][d] >= maxAccepted ? 0 : data[b][d];
  }
}

int findMinimumD(int f, int b) {
  if (b == 1) return f;
  if (b > 1 && b < 33) {
     int i = 1;
     long long f1 = f;
     while (data[b][i] < f1 && data[b][i] != 0) i++;
     return i;
  }
  
  if (b >= 33) {
     long long f1 = f;
     long long d = 1;
     int i = 1;
     while ( (d<<i) - 1 < f1) i++;
     return i;
  }
}

int findMinimumB(int f, int d) {
  if (d >= W) return f > d ? 2 : 1;
  
  int i = 1;
  while (data[i][d] < f && data[i][d] != 0) i++;  
  return i;
}

void solve(int f, int d, int b, int c) {
  unsigned int resF = findMaximumF(d, b);
  int resD = findMinimumD(f, b);
  int resB = findMinimumB(f, d);
  
  printf("Case #%d: ", c);
  if (resF == 0) printf("-1"); else printf("%u", resF);
  printf(" %d %d\n", resD, resB);
  
  if (resD > d) printf("ErrorD");
  if (resB > b) printf("ErrorB");
  if (resF != 0 && resF < f) printf("ErrorF");
  
}

int main(void) {    
  int cases;
  
  fillData();
  
  scanf("%d", &cases);
  
  for(int c=0;c<cases;c++) {
    int f, d, b;
    scanf("%d %d %d", &f, &d, &b);
    solve(f, d , b, c + 1);
  }    
}

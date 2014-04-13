#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)



int main(void) {
  long double c1 = 5;  
  long double C = 3 + sqrt(c1);
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    int n;
    scanf("%d", &n);
    long double x = 1;
    FOR(i, n) {
      x *= C;
      while (x > 100000.0) x -= 100000.0;
      printf("%LF\n", x);
    }
           
    char res[100];
    sprintf(res, "%Lf", x);
    int dotPos = 0;
    while (res[dotPos] != '.') dotPos++;
    
    
    char fres[4];
    fres[0] = fres[1] = fres[2] = '0';
    fres[3] = 0;
    res[dotPos] = 0;
    if (dotPos < 3) strcpy(fres + 3 - dotPos, res); else strcpy(fres, res + dotPos - 3);
    
    printf("Case #%d: %s\n", c, fres);
  }
}

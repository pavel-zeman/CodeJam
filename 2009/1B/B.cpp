#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


void getDigits(int number, int * digits) {
  while (number > 0) {
    digits[number % 10]++;
    number /= 10;
  }
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    int number;
    int srcDigits[10];
    int dstDigits[10];
    scanf("%d", &number);

    FOR(i, 10) srcDigits[i] = 0;
    getDigits(number, srcDigits);
    while (true) {
      number++;
      FOR(i, 10) dstDigits[i] = 0;
      getDigits(number, dstDigits);
      bool found = true;
      FORE(i, 1, 10)
        if (dstDigits[i] != srcDigits[i]) {
          found = false;
          break;
        }
      if (found) break;
    }

    printf("Case #%d: %d\n", c, number);
  }
}

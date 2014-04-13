#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


char buf[1000000];


char *clicks[] = {"2", "22", "222", "3", "33", "333", "4", "44", "444", "5", "55", "555", "6", "66", "666", "7", "77", "777", "7777", "8", "88", "888", "9", "99", "999", "9999", "0"};

int main(void) {
  gets(buf);
  int cases = atoi(buf);
  for(int c=1;c<=cases;c++) {
    gets(buf);
    char lastDigit = 0;
    printf("Case #%d: ", c);
    for (char *start = buf; *start; start++) {
      if (*start == ' ') *start = 'z' + 1;
      if (lastDigit == clicks[*start - 'a'][0]) printf(" "); else lastDigit = clicks[*start - 'a'][0];
      printf("%s", clicks[*start - 'a']);
    }
    printf("\n");
  }
}

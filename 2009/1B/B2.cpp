#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)



int digits[10];

int main(void) {
  int cases;
  char line[100];
  char out[100];

  gets(line);
  cases = atoi(line);
  for(int c=1;c<=cases;c++) {
    gets(line);
    int l = strlen(line);
    if (line[l - 1] == 10 || line[l - 1] == 13) {
      line[l - 1] = 0;
      l--;
    }

    int pos = 0;


    if (l == 1) {
      out[0] = line[0];
      out[1] = '0';
      out[2] = 0;
    } else {
      pos = l - 1;
      int last = line[pos];
      pos--;
      while (pos >= 0 && line[pos] >= last) {
        last = line[pos];
        pos--;
      }

      int m = pos >= 0 ? line[pos] : '0';

      // new value to pos
      int pos2 = l - 1;
      while (line[pos2] <= m) pos2--;

      FOR(i, 10) digits[i] = 0;

      int dpos = pos;
      if (dpos < 0) {
        dpos = 0;
        digits[0]++;
      }

      while (isdigit(line[dpos]) && dpos < l) {
        digits[line[dpos] - '0']++;
        dpos++;
      }


      digits[line[pos2] - '0']--;

      int outp = 0;
      FOR(i, pos) out[outp++] = line[i];
      out[outp++] = line[pos2];

      FOR(i, 10) {
        FOR(j, digits[i])
          out[outp++] = '0' + i;
      }
      out[outp] = 0;

    }

    printf("Case #%d: %s\n", c, out);
  }
}

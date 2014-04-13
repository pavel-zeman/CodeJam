#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int k;
int minLength;
char data[10000];
char used[16];
int value[16];
int length;


void test() {
  char local[10000];
  int pos = 0;
  int bunch = 0;
  int changes;
  char v;
  FOR(i, length) {
    local[i] = data[bunch + value[pos]];
    pos++;
    if (pos == k) {
      pos = 0;a
      bunch += k;
    }
  }

  v = 0;
  changes = 0;
  FOR(i, length) {
    if (local[i] != v) {
      v = local[i];
      changes ++;
    }
  }

  if (changes < minLength) minLength = changes;
}

void generate(int level) {
  if (level < k) {
    FOR(i, k)
      if (!used[i]) {
        used[i] = 1;
        value[level] = i;
        generate(level + 1);
        used[i] = 0;
      }
  } else {
    test();
  }
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %s", &k, data);
    minLength = length = strlen(data);
    FOR(i, k) used[i] = 0;
    generate(0);

    printf("Case #%d: %d\n", c, minLength);
  }
}

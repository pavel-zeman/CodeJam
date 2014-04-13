#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define L 15
#define D 5000
#define CHARS ('z' - 'a' + 1)

int l, d, n;
char words[D][L + 1];


int main(void) {
  char pattern[(CHARS + 2) * L + 1];
  scanf("%d %d %d", &l, &d, &n);

  for(int i=0;i<d;i++)
    scanf("%s", words[i]);

  for(int c=1;c<=n;c++) {
    scanf("%s", pattern);

    int pos = 0;
    int totalWords = d;
    int wordIndices[D];
    char characters[CHARS];
    for(int i=0;i<d;i++) wordIndices[i] = i;

    for(int i=0;i<l && totalWords > 0;i++) {
      for(int j=0;j<CHARS;characters[j++] = 0);
      if (pattern[pos] == '(') {
        while (pattern[++pos] != ')')
          characters[pattern[pos] - 'a'] = 1;
      } else {
        characters[pattern[pos] - 'a'] = 1;
      }
      pos++;

      int newTotalWords = 0;
      for(int j=0;j<totalWords;j++) {
        if (characters[words[wordIndices[j]][i] - 'a']) {
          wordIndices[newTotalWords++] = wordIndices[j];
        }
      }
      totalWords = newTotalWords;
    }

    printf("Case #%d: %d\n", c, totalWords);
  }
}

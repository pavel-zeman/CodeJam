#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include <list>
#include <string>
#include <iterator>
#include <iostream>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

using namespace std;

char buf[1000000];

int main(void) {
  gets(buf);
  int cases = atoi(buf);
  list<string> words;
  for(int c=1;c<=cases;c++) {
    gets(buf);
    buf[strlen(buf) + 1] = 0;
    words.clear();

    char *s = buf;
    do {
      char *wordStart = s;
      while (*s != ' ' && *s) s++;
      char origEnd = *s;
      *s = 0;
      words.push_back(string(wordStart));
    } while (*++s);

    cout << "Case #" << c << ": ";
    copy(words.rbegin(), words.rend(), ostream_iterator<string>(cout, " "));
    cout << endl;
  }
}

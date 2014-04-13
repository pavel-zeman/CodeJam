#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

using namespace std;

int n;

set<string> colors;

struct offer {
  int a, b;

  bool operator<(const offer& o2) const {
    return b > o2.b;
  }
};

string colorNames[300];
vector<offer> offers[300];
int totalColors;
int totalMin;


int usedColors[3];

int addColor(const string & s) {
  if (colors.find(s) == colors.end()) {
    colorNames[totalColors] = s;
    colors.insert(s);
    return totalColors++;
  } else {
    FOR(i, totalColors)
      if (colorNames[i] == s) return i;
  }
  assert(false);
  return 0;
}


void generate(int u, int first) {
  if (u == 3 || u == totalColors) {
    // test
    int items = 0;
    FOR(i, u) items += offers[usedColors[i]].size();
    vector<offer> validOffers(items);

    vector<offer>::iterator lastUsed = validOffers.begin();
    FOR(i, u) lastUsed = copy(offers[usedColors[i]].begin(), offers[usedColors[i]].end(), lastUsed);

    sort(validOffers.begin(), validOffers.end());

    int search = 10000;
    int count = 0;
    vector<offer>::iterator it = validOffers.begin();

    while (search > 0) {
      int minLeft = INT_MAX;
      while (it != validOffers.end() && it->b >= search) {
        if (it->a < minLeft) minLeft = it->a;
        it++;
      }
      if (minLeft == INT_MAX) return;
      count++;
      search = minLeft - 1;
    }

    if (count < totalMin) totalMin = count;
  } else {
    FORE(i, first, totalColors) {
      usedColors[u] = i;
      generate(u + 1, i + 1);
    }
  }
}

int main(void) {
  int cases;
  scanf("%d", &cases);

  for(int c=1;c<=cases;c++) {
    scanf("%d", &n);

    colors.clear();
    totalColors = 0;
    totalMin = INT_MAX;

    FOR(i, (int)(sizeof(offers)/sizeof(offers[0]))) offers[i].clear();

    FOR(i, n) {
      char color[100];
      offer o;
      scanf("%s %d %d", color, &o.a, &o.b);
      offers[addColor(color)].push_back(o);
    }

    generate(0, 0);

    printf("Case #%d: ", c);

    if (totalMin == INT_MAX) printf("IMPOSSIBLE\n"); else printf("%d\n", totalMin);
  }
}

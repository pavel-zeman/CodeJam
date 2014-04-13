#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define M 1000001

int k;
int n;
int indices[200];
int deck[M];

int tree[M];

int read(int where) {
  int sum = 0;
  while (where > 0) {
    sum += tree[where - 1];
    where -= where & -where;
  }
  return sum;
}

void update(int where, int value) {
  while (where <= k) {
    tree[where - 1] += value;
    where += where & -where;
  }
}


int find(int value, int bitMask){
  //printf("Looking up value %d\n", value);
	int idx = 0;
	while ((bitMask != 0) && (idx < k)){
		int tIdx = idx + bitMask;
		if (tIdx <= k && value >= tree[tIdx - 1]){
			idx = tIdx;
			value -= tree[tIdx - 1];
		}
		bitMask >>= 1;
	}
	if (value != 0)
		return -1;
	else
		return idx;
}


int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    scanf("%d %d", &k, &n);
    FOR(i, n) scanf("%d", &indices[i]);
    FOR(i, M) tree[i] = 0;
    FOR(i, k) {
      deck[i] = 0;
      update(i + 1, 1);
    }

    int x = k;
    int bitMask = 1;
    while (x != 0) { bitMask <<= 1; x >>= 1; }
    bitMask >>= 1;

    int pos = k - 1;
    FOR(i, k) {
      int c = i % (k - i) + 1;
      int after = read(k) - read(pos + 1);
      if (c <= after) {
        pos = find(read(pos + 1) + c - 1, bitMask);
      } else {
        pos = find(c - after - 1, bitMask);
        if (pos == -1) pos = 0;
      }
      assert(pos >= 0);
      deck[pos] = i + 1;
      update(pos + 1, -1);
    }

    printf("Case #%d:", c);
    FOR(i, n) printf(" %d", deck[indices[i] - 1]);
    printf("\n");
  }
}

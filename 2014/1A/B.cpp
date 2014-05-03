// Calculate maximum possible full binary tree for each root
// http://code.google.com/codejam/contest/2984486/dashboard#s=p1
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1002

using namespace std;

vector<int> neighbors[MAX_N];
bool used[MAX_N];
int n;


char c = 0;
int getInt() {
    int r = 0;
    while (!(c == '-' || (c >= '0' && c <= '9'))) c = getc_unlocked(stdin);
    bool minus = c == '-';
    if (minus) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

int check(int node) {
    int children = 0;
    int t = neighbors[node].size();
    int max = 0;
    int secondMax = 0;

    used[node] = true;

    FOR(i, t) {
        int child = neighbors[node][i];
        if (!used[child]) {
            children++;
            int x = check(child);
            if (x >= max) {
                secondMax = max;
                max = x;
            } else if (x > secondMax) secondMax = x;
        }
    }
    return children <= 1 ? 1 : max + secondMax + 1;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        n = getInt();
        FOR(i, n) neighbors[i].clear();
        FOR(i, n - 1) {
            int x = getInt() - 1;
            int y = getInt() - 1;
            neighbors[x].push_back(y);
            neighbors[y].push_back(x);
        }
        int max = 0;
        FOR(i, n) {
            FOR(j, n) used[j] = false;
            int t = check(i);
            if (t > max) max = t;
        }
        printf("Case #%d: %d\n", c, n - max);
    }
}

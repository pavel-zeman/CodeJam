//
// https://code.google.com/codejam/contest/8234486/dashboard#s=p0
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <set>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define EMPTY 5
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define MAX_N 110

using namespace std;

char grid[MAX_N][MAX_N];
char row[MAX_N];
int rows, columns;
bool safe[MAX_N][MAX_N];

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};


int getInt() {
    int d;
    scanf("%d", &d);
    return d;
}

bool go(int r, int c, int *nr, int *nc) {
    int direction = grid[r][c];
    r += dr[direction];
    c += dc[direction];
    while (r >= 0 && r < rows && c >= 0 && c < columns && grid[r][c] == EMPTY) {
        r += dr[direction];
        c += dc[direction];
    }
    if (r >= 0 && r < rows && c >= 0 && c < columns) {
        *nr = r;
        *nc = c;
        return true;
    } else return false;
}

int main(void) {
    int cases = getInt();
    for(int c=1;c<=cases;c++) {
        rows = getInt();
        columns = getInt();
        FOR(i, rows) {
            scanf("%s", row);
            FOR(j, columns) {
                switch (row[j]) {
                    case '.': grid[i][j] = EMPTY; break;
                    case '^': grid[i][j] = UP; break;
                    case '>': grid[i][j] = RIGHT; break;
                    case 'v': grid[i][j] = DOWN; break;
                    case '<': grid[i][j] = LEFT; break;
                }
                safe[i][j] = false;
            }
        }
        bool possible = true;
        int total = 0;
        FOR(i, rows) FOR(j, columns) {
            if (grid[i][j] != EMPTY && !safe[i][j]) {
                int lastr = i;
                int lastc = j;
                int nextr = i;
                int nextc = j;
                bool res = go(lastr, lastc, &nextr, &nextc);
                if (!res) {
                    bool ok = false;
                    FOR(k, 3) {
                        grid[i][j] = (grid[i][j] + 1) & 3;
                        if (go(lastr, lastc, &nextr, &nextc)) {
                            ok = true;
                            break;
                        }
                    }
                    //printf("%d %d\n", i, j);
                    total++;
                    if (!ok) {
                        possible = false;
                        goto finish;
                    }
                }
                while (true) {
                    safe[lastr][lastc] = true;
                    res = go(lastr, lastc, &nextr, &nextc);
                    if (res) {
                        if (safe[nextr][nextc]) break;
                    } else {
                        safe[nextr][nextc] = true;
                        total++;
                        //printf("%d %d\n", nextr, nextc);
                        break;
                    }
                    lastr = nextr;
                    lastc = nextc;
                }
            }
        }

        finish:
        if (possible) printf("Case #%d: %d\n", c, total);
        else printf("Case #%d: IMPOSSIBLE\n", c);
    }
}

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int r, c;

char tiles[100][100];

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cas=1;cas<=cases;cas++) {
        scanf("%d%d", &r, &c);
        FOR(i, r) {
            scanf("%s", tiles[i]);
        }

        bool possible = true;
        FOR(i, r - 1)
            FOR(j, c - 1) {
                if (tiles[i][j] == '#') {
                    if (tiles[i][j+1] == '#' && tiles[i+1][j] == '#' && tiles[i+1][j+1] == '#') {
                        tiles[i+1][j+1] = tiles[i][j] = '/';
                        tiles[i+1][j] = tiles[i][j+1] = '\\';
                    } else {
                        possible = false;
                        goto end;
                    }
                }
            }

        end:
        if (possible) {
            FOR(i, c) if (tiles[r - 1][i] == '#') {
                possible = false;
                break;
            }

            FOR(i, r) if (tiles[i][c - 1] == '#') {
                possible = false;
                break;
            }
        }


        printf("Case #%d:\n", cas);
        if (possible) {
            FOR(i, r) printf("%s\n", tiles[i]);
        } else
            printf("Impossible\n");
    }
}

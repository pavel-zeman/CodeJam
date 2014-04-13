#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int n, k;
char board1[100][100];
char board2[100][100];

void rotate(void) {
    FOR(i, n) FOR(j, n) board2[i][j] = board1[n - 1- j][i];
    FOR(i, n) {
        for(int j=n-1;j>0;j--) {
            int s = j;
            while (board2[s][i] == '.' && s >= 0) s--;
            if (s < 0) break;
            if (s != j) {
                board2[j][i] = board2[s][i];
                board2[s][i] = '.';
            }
        }
    }
}

void print(void) {
    FOR(i, n) {
        FOR(j, n) printf("%c", board2[i][j]);
        printf("\n");
    }
}

bool check(char b) {
    // horizontal
    FOR(i, n) FOR(j, n - k + 1) {
        bool found = true;
        FOR(x, k) {
            if (board2[i][j + x] != b) {
                found = false;
                break;
            }
        }
        if (found) return true;
    }

    // vertical
    FOR(i, n - k + 1) FOR(j, n) {
        bool found = true;
        FOR(x, k) {
            if (board2[i + x][j] != b) {
                found = false;
                break;
            }
        }
        if (found) return true;
    }

    // right down
    FOR(i, n - k + 1) FOR(j, n - k + 1) {
        bool found = true;
        FOR(x, k) {
            if (board2[i+x][j+x] != b) {
                found = false;
                break;
            }
        }
        if (found) return true;
    }

    // left down
    FOR(i, n - k + 1) FOR(j, n - k + 1) {
        bool found = true;
        FOR(x, k) {
            if (board2[i+x][n - 1 - j - x] != b) {
                found = false;
                break;
            }
        }
        if (found) return true;
    }

    return false;
}


int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d %d", &n, &k);
        FOR(i, n) scanf("%s", board1[i]);

        rotate();
        //print();
        bool red = check('R');
        bool blue = check('B');



        printf("Case #%d: %s\n", c, red && blue ? "Both" : (red && !blue ? "Red" : (!red && blue ? "Blue" : "Neither")));
    }
}

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define B 'B'
#define W 'W'
#define E ' '

int n, m;
char board[512][512];
int size[512][512];
int count[513];

int min(int x, int y) {
    return x < y ? x : y;
}

void calculateSize(int sx, int sy, int ex, int ey) {
    if (sx < 1) sx = 1;
    if (sy < 1) sy = 1;
    if (ex > m) ex = m;
    if (ey > n) ey = n;
    FORE(i, sx, ex) FORE(j, sy, ey) {
        if (board[i][j] == E) size[i][j] = 0;
        else {
            if (board[i][j] != board[i-1][j] && board[i][j] != board[i][j-1] && board[i][j] == board[i-1][j-1]) {
                int m = min(size[i-1][j], size[i-1][j-1]);
                size[i][j] = min(m, size[i][j-1]) + 1;
            } else
                size[i][j] = 1;
        }
    }
}

int main(void) {


    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d %d", &m, &n);

        FOR(i, m) {
            char row[1000];
            scanf("%s", row);
            FOR(j, n/4) {
                int v = row[j] >= 'A' ? row[j] - 'A' + 10 : row[j] - '0';
                FOR(k, 4) {
                    board[i][j * 4 + 3 - k] = ((v & 1) == 1) ? 'W' : 'B';
                    v >>= 1;
                }
            }
        }


        FOR(i, m + 1) count[i] = 0;

        int remain = m * n;
        FOR(i, 512) size[i][0] = size[0][i] = 1;
        calculateSize(1, 1, m, n);

        while (remain) {
            //printf("Remain: %d %d %d\n", remain, m, n);
            int x = -1;
            int max = 0;
            FOR(i, m) FOR(j, n) if (size[i][j] > max) {
                max = size[i][j];
                x = i;
            }

            //printf("Max: %d\n", max);

            FORE(i, x, m) FOR(j, n) {
                if (size[i][j] == max) {
                    //printf("%d %d %d %d\n", i, j, max, remain);
                    count[max]++;
                    remain -= max*max;
                    FOR(k, max) FOR(l, max) {
                        size[i - k][j - l] = 0;
                        board[i - k][j - l] = E;
                    }

                    if (max > 1) calculateSize(i - max + 1, j - max + 1, i + max, j + max);
                }
            }
        }

        int diff = 0;
        FOR(i, m + 1) {
            if (count[i] > 0) diff++;
        }

        printf("Case #%d: %d\n", c, diff);
        for(int i=m;i>0;i--) if (count[i] > 0) printf("%d %d\n", i, count[i]);
    }
}

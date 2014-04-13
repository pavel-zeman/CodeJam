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

void calculateSize(int sx, int sy, int ex, int ey) {
    if (sx < 0) sx = 0;
    if (sy < 0) sy = 0;
    FORE(i, sx, ex) FORE(j, sy, ey) {
        if (board[i][j] == E) size[i][j] = 0; else {
            size[i][j] = 1;
            FORE(k, 2, m + 2) {
                bool ok = true;
                if (j + k -1 >= n || i +k - 1 >= m) { ok = false;}
                if (ok) {
                    FOR(l, k - 1) {
                        if (board[i + l][j + k - 1] == board[i + l][j + k - 2] || board[i + l][j + k - 1] == E) { ok = false; break; }
                        if (board[i + k - 1][j + l] == board[i + k - 2][j + l] || board[i + k - 1][j + l] == E) { ok = false; break; }

                    }
                    if (ok && (board[i + k -1][j + k - 1] == board[i + k - 2][j + k - 1] || board[i + k - 1][j + k - 1] == board[i + k - 1][j + k - 2])) ok = false;
                    if (ok && board[i + k -1][j + k - 1] == E) ok = false;
                }
                if (!ok) {
                    size[i][j] = k - 1;
                    break;
                }
            }
        }
    }

    /*FOR(i, m) {
        FOR(j, n) printf("%c ", board[i][j]);
        printf("\n");
    }

    FOR(i, m) {
        FOR(j, n) printf("%d ", size[i][j]);
        printf("\n");
    }*/
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
        calculateSize(0, 0, m, n);

        while (remain) {
            //printf("Remain: %d %d %d\n", remain, m, n);
            int x = -1, y = -1;
            int max = 0;
            FOR(i, m) FOR(j, n) if (size[i][j] > max) {
                max = size[i][j];
                x = i;
                y = j;
            }

            //printf("Max: %d\n", max);

            FORE(i, x, m) FOR(j, n) {
                if (size[i][j] == max) {
                    //printf("%d %d %d\n", i, j, max);
                    count[max]++;
                    remain -= max*max;
                    FOR(k, max) FOR(l, max) {
                        size[i + k][j + l] = 0;
                        board[i + k][j + l] = E;
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
        for(int i=m;i>0;i--) {
            if (count[i] > 0) printf("%d %d\n", i, count[i]);
        }
    }
}

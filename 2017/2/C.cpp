// Brute force solution for the small input
// https://code.google.com/codejam/contest/5314486/dashboard#s=p2&a=2

#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI long long int
#define MOD 1000000007

int power(int a, int b) {
    int sq = a;
    int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * (LLI)sq % MOD;
        sq = sq * (LLI)sq % MOD;
        b >>= 1;
    }
    return result;
}

int inv(int a) {
    return power(a, MOD - 2);
}

void fail() {
    *((char *)0) = 0;
}

#define W 0
#define E 1
#define V 2
#define H 3

int r, c;
char line[100];
int grid[100][100];
bool ff[100][100];
bool covered[100][100];

int findBeamVert(int a, int b) {
    FORE(i, a + 1, r) {
        if (grid[i][b] == W) return -1;
        if (grid[i][b] == H || grid[i][b] == V) return i;
    }
    return -1;
}

int findBeamVert2(int a, int b) {
    FORE(i, a + 1, r) {
        if (grid[i][b] == W) break;
        if (grid[i][b] == H || grid[i][b] == V) return i;
    }
    for(int i = a - 1; i >= 0; i--) {
        if (grid[i][b] == W) break;
        if (grid[i][b] == H || grid[i][b] == V) return i;
    }
    return -1;
}

int findBeamHor(int a, int b) {
    FORE(i, b + 1, c) {
        if (grid[a][i] == W) return -1;
        if (grid[a][i] == H || grid[a][i] == V) return i;
    }
    return -1;
}

int findBeamHor2(int a, int b) {
    FORE(i, b + 1, c) {
        if (grid[a][i] == W) break;
        if (grid[a][i] == H || grid[a][i] == V) return i;
    }
    for(int i = b - 1; i >= 0; i--) {
        if (grid[a][i] == W) break;
        if (grid[a][i] == H || grid[a][i] == V) return i;
    }
    return -1;
}


bool isCovered(int pos) {
    int row = pos / c;
    int column = pos % c;
    if (grid[row][column] != E) return true;
    else {
        int bRow = findBeamVert2(row, column);
        int bColumn = findBeamHor2(row, column);
        if (bRow >= 0 && ff[bRow][column] && grid[bRow][column] == V) return true;
        if (bColumn >= 0 && ff[row][bColumn] && grid[row][bColumn] == H) return true;
        return false;
    }
}

bool checkCovered(int pos) {
    while (pos < r * c && isCovered(pos)) pos++;
    if (pos == r * c) return true;
    else {
        int row = pos / c;
        int column = pos % c;
        int bRow = findBeamVert2(row, column);
        int bColumn = findBeamHor2(row, column);
        if (bRow >= 0 && !ff[bRow][column]) {
            grid[bRow][column] = V;
            ff[bRow][column] = true;
            if (checkCovered(pos + 1)) return true;
            ff[bRow][column] = false;
        }
        if (bColumn >= 0 && !ff[row][bColumn]) {
            grid[row][bColumn] = H;
            ff[row][bColumn] = true;
            if (checkCovered(pos + 1)) return true;
            ff[row][bColumn] = false;
        }
        return false;
    }
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++) {
        scanf("%d %d", &r, &c);
        FOR(i, r) {
            scanf("%s", line);
            FOR(j, c) {
                int x = 0;
                switch (line[j]) {
                    case '#': x = W; break;
                    case '.': x = E; break;
                    case '|': x = V; break;
                    case '-': x = H; break;
                }
                grid[i][j] = x;
                ff[i][j] = false;
                covered[i][j] = false;
            }
        }
        bool ok = true;
        FOR(i, r) {
            FOR(j, c) {
                if (grid[i][j] == V || grid[i][j] == H) {
                    int beamPos = findBeamVert(i, j);
                    if (beamPos >= 0) {
                        if ((grid[i][j] == V && ff[i][j]) || (grid[beamPos][j] == V && ff[beamPos][j])) {
                            ok = false;
                            break;
                        }
                        grid[i][j] = H;
                        grid[beamPos][j] = H;
                        ff[i][j] = ff[beamPos][j] = true;
                    }
                }
            }
        }
        FOR(i, r) {
            FOR(j, c) {
                if (grid[i][j] == V || grid[i][j] == H) {
                    //printf("Looking for beam at %d %d\n", i, j);
                    int beamPos = findBeamHor(i, j);
                    if (beamPos >= 0) {
                        if ((grid[i][j] == H && ff[i][j]) || (grid[i][beamPos] == H && ff[i][beamPos])) {
                            ok = false;
                            break;
                        }
                        grid[i][j] = V;
                        grid[i][beamPos] = V;
                        ff[i][j] = ff[i][beamPos] = true;
                    }
                }
            }
        }
        /*
        FOR(i, r) {
            FOR(j, c) printf("%d", grid[i][j]);
            printf("\n");
        }

        FOR(i, r) {
            FOR(j, c) printf("%d", ff[i][j]);
            printf("\n");
        }
        */
        if (ok) ok = checkCovered(0);

        printf("Case #%d: %s\n", cc, ok ? "POSSIBLE" : "IMPOSSIBLE");
        if (ok) {
            FOR(i, r) {
                FOR(j, c) {
                    char ch = 'X';
                    switch (grid[i][j]) {
                        case E: ch = '.'; break;
                        case W: ch = '#'; break;
                        case H: ch = '-'; break;
                        case V: ch = '|'; break;
                    }
                    printf("%c", ch);
                }
                printf("\n");
            }
        }
    }
}

// Unfortunately this does not work
// https://code.google.com/codejam/contest/3024486/dashboard#s=p2
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define IN 1
#define OUT 2
#define DONT_KNOW 0

#define MAX_ID 2010
#define MAX_N 2000
#define ENTER 'E'
#define LEAVE 'L'

int status[MAX_ID];
int n;

bool used[MAX_N];
char a[MAX_N];
int ids[MAX_N];

int last(char action, int id, int i) {
    while (true) {
        i--;
        if (!used[i] && a[i] == action && ids[i] == id) return i;
    }
}
int next(char action, int start, int end) {
    FORE(i, start, end) {
        if (!used[i] && a[i] == action && ids[i] == 0) {
            used[i] = true;
            return i;
        }
    }
    return -1;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d", &n);
        bool crimeTime = false;
        FOR(i, MAX_ID) status[i] = DONT_KNOW;

        FOR(i, n) {
            char action[10];
            int id;
            scanf("%s %d", action, &id);
            a[i] = action[0];
            ids[i] = id;
            used[i] = false;

            if (action[0] == ENTER) {
                if (id != 0) {
                    if (status[id] == IN) {
                        int l = last(ENTER, id, i);
                        int nn = next(LEAVE, l, i);
                        if (nn == -1) crimeTime = true;
                        used[i] = true;
                    } else if (status[id] == OUT) {
                        //int l = last(LEAVE, id, i);
                        //used[l] = true;
                    }
                    status[id] = IN;
                }
            } else {
                // leave
                if (id != 0) {
                    if (status[id] == OUT) {
                        int l = last(LEAVE, id, i);
                        int nn = next(ENTER, l, i);
                        if (nn == -1) crimeTime = true;
                        used[i] = true;
                    } else if (status[id] == IN) {
                        int l = last(ENTER, id, i);
                        used[l] = true;
                        used[i] = true;
                    }
                    status[id] = OUT;
                }
            }
        }

        int minIn = 0;
        if (!crimeTime) {
            FORE(i, 1, MAX_ID) {
                if (status[i] == IN) {
                    int l = last(ENTER, i, n);
                    int nn = next(LEAVE, l, n);
                    if (nn == -1) {
                        minIn++;
                        //printf("%d ", i);
                    }
                }
            }
            FOR(i, n) {
                if (a[i] == ENTER && ids[i] == 0 && !used[i]) {
                    //printf("Checking %d ", i);
                    bool found = false;
                    FORE(j, i + 1, n) {
                        if (!used[j] && a[j] == LEAVE) {
                            used[j] = true;
                            //printf("Found: %d ", j);
                            found = true;
                            break;
                        }
                    }
                    if (!found) minIn++;
                }
            }
        }

        printf("Case #%d: ", c);
        if (crimeTime) {
            printf("CRIME TIME\n");
        } else {
            printf("%d\n", minIn);
        }
    }
}

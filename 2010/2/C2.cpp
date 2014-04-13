#include <stdio.h>
#include <string.h>
#include <limits.h>
//#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX 1000001

int r;
int x1, x2, y1, y2;
int maxx, maxy, miny;
int linesToCompact[MAX];
int numLines;

struct interval {
    int a, b;
    int next, prev;
} intervals[MAX * 3];

int usedIntervals;

int findInterval(int row, int a) {
    int last = row;
    while (intervals[last].next != -1 && intervals[intervals[last].next].a <= a) {
        last = intervals[last].next;
    }
    return last;
}


void remove(int i) {
    int p = intervals[i].prev;
    int n = intervals[i].next;
    if (n != -1) {
        intervals[n].prev = p;
    }
    intervals[p].next = n;
}

void compactAll(void) {
    for(int i=miny;i<=maxy;i++) {
        int r = i;
        while (intervals[r].next != -1) {
            int n = intervals[r].next;
            if (intervals[r].b >= intervals[n].a - 1) {
                intervals[r].b = intervals[r].b > intervals[n].b ? intervals[r].b : intervals[n].b;
                remove(n);
            } else
                r = intervals[r].next;
        }
    }
}


void compact(void) {
    for(int i=0;i<numLines;i++) {
        int r = linesToCompact[i];
        while (intervals[r].next != -1) {
            int n = intervals[r].next;
            if (intervals[r].b >= intervals[n].a - 1) {
                intervals[r].b = intervals[r].b > intervals[n].b ? intervals[r].b : intervals[n].b;
                remove(n);
            } else
                r = intervals[r].next;
        }
    }
}


int findLast(int i) {
    while (intervals[i].next != -1) {
        i = intervals[i].next;
    }
    return i;
}

void updateMins(void) {
    while (intervals[miny].next == -1 && miny < MAX) miny++;
    while (intervals[maxy].next == -1 && maxy >= 0) maxy--;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        FOR(i, MAX) {
            intervals[i].a = -1;
            intervals[i].b = -1;
            intervals[i].prev = -1;
            intervals[i].next = -1;
        }
        usedIntervals = MAX;
        maxx = 0;
        maxy = 0;
        miny = MAX;

        scanf("%d", &r);
        FOR(k, r) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            y1--;
            y2--;
            if (x2 > maxx) maxx = x2;
            if (y2 > maxy) maxy = y2;
            if (y1 < miny) miny = y1;
            for(int i=y1;i<=y2;i++) {
                int ins = findInterval(i, x1);
                intervals[usedIntervals].a = x1;
                intervals[usedIntervals].b = x2;
                intervals[usedIntervals].next = intervals[ins].next;
                intervals[usedIntervals].prev = ins;
                if (intervals[ins].next != -1) {
                    intervals[intervals[ins].next].prev = usedIntervals;
                }
                intervals[ins].next = usedIntervals;
                usedIntervals++;
            }
        }

        compactAll();
        updateMins();


        int rounds = 0;
        while (maxy >= 0) {
            //printf("%d %d %d %d\n", miny, maxy, intervals[0].next > 0 ? intervals[intervals[0].next].a : 0, numLines);
            /*for(int i=miny;i<=maxy;i++) {
                int x = i;
                printf("%d. ", x);
                while (x != -1) {
                    printf("%d %d  ", intervals[x].a, intervals[x].b);
                    x = intervals[x].next;
                }
                printf("\n");
            }
            printf("\n");*/

            numLines = 0;

            for(int i=maxy;i>=miny;i--) {
                if (intervals[i].next != -1) {
                    int l = findLast(i);
                    int lp = i == 0 ? 0 : findLast(i - 1);
                    while (l >= MAX) {

                        while (intervals[lp].a > intervals[l].b + 1) lp = intervals[lp].prev;
                        //printf("Row: %d, checking %d versus %d %d\n", i, intervals[l].b, intervals[lp].a, intervals[lp].b);
                        if (intervals[l].b  + 1 >= intervals[lp].a && intervals[l].b  + 1 <= intervals[lp].b) {
                            intervals[l].b++;
                            if (numLines == 0 || linesToCompact[numLines - 1] != i) {
                                linesToCompact[numLines++] = i;
                            }
                        }

                        while (intervals[lp].a > intervals[l].a) lp = intervals[lp].prev;
                        if (intervals[l].a >= intervals[lp].a && intervals[l].a <= intervals[lp].b) {
                            //intervals[l].b++;
                            //printf("New one\n");
                        } else
                            intervals[l].a++;


                        if (intervals[l].a > intervals[l].b) remove(l);
                        l = intervals[l].prev;
                    }
                }
            }
            compact();
            updateMins();
            rounds++;
        }
        printf("Case #%d: %d\n", c, rounds);
    }
    return 0;
}

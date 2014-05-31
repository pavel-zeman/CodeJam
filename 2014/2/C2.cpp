// An attempt for an efficient maze walk - instead of each cell, track just vertical segments (unfortunately the implementation is not complete)
// https://code.google.com/codejam/contest/3014486/dashboard#s=p2
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_W 200

struct segment {
    int start, end;
    segment(int a, int b) {
        start = a;
        end = b;
    }
};

struct result {
    int segment;
    int position;

    result(int s, int p) {
        segment = s;
        position = p;
    }
};

int w, h;

vector<segment> segments[MAX_W];

int incx[4] = {0, 1, 0, -1};
int incy[4] = {1, 0, -1, 0};

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

void addSegment(int x, int start, int end) {
    if (segments[x].empty()) {
        segments[x].push_back(segment(start, end));
    } else {
        int i = 0;
        int size = segments[x].size();
        while (i < size && start > segments[x][i].end) i++;
        if (i == size) segments[x].push_back(segment(start, end));
        else segments[x].insert(segments[x].begin() + i, segment(start, end));
    }
}

bool isUsed(int x, int y) {
    int size = segments[x].size();
    FOR(i, size) {
        if (y < segments[x][i].start) return false;
        if (y >= segments[x][i].start && y <= segments[x][i].end) return true;
    }
    return false;
}

result findFirstObstacleUp(int x, int y) {
    int size = segments[x].size();
    FOR(i, size) {
        if (segments[x][i].start > y) {
            return result(i, segments[x][i].start);
        }
    }
    return result(-1, -1);
}

result findFirstFreeUp(int x, int y) {
    if (x < 0 || x >= w) {
        return result(-1, -1);
    }
    int size = segments[x].size();
    FOR(i, size) {
        if (y < segments[x][i].start) return result(i, y);
        if (y >= segments[x][i].start && y <= segments[x][i].end) y = segments[x][i].end + 1;
    }
    return result(-1, -1);
}

bool check(int x, int y, int direction) {
    int s = direction;
    FOR(i, 3) {
        struct result result1(-1, -1), result2(-1, -1);
        switch (s) {
            case 0: // up
                result1 = findFirstObstacleUp(x, y);
                result2 = findFirstFreeUp(x - 1, y);
                if (result2.segment != -1 && (result1.segment == -1 || result1.position > result2.position)) {
                    addSegment(x, y + 1, result2.position);
                    if (check(x, result2.position, 3)) return true;
                } else {
                    if (result1.segment == -1) {
                        addSegment(x, y + 1, h - 1);
                        return true;
                    }
                    if (result1.position > y + 1) {
                        addSegment(x, y + 1, result1.position - 1);
                        if (check(x, result.position - 1, 1)) return true;
                    }
                }
                break;
            case 1: // right

        }
        s = (s + 1) & 3;
    }
    return false;
}

int main(void) {
    int cases = getInt();
    for(int c=1;c<=cases;c++) {
        w = getInt();
        h = getInt();
        FOR(i, w) segments[i].clear();

        int b = getInt();
        FOR(i, b) {
            int x0 = getInt(), y0 = getInt(), x1 = getInt(), y1 = getInt();
            FORE(j, x0, x1 + 1) addSegment(j, y0, y1);
        }
        int total = 0;
        FOR(i, w) if (!isUsed(i, 0) && check(i, 0, 0)) total++;
        printf("Case #%d: %d\n", c, total);
    }
}

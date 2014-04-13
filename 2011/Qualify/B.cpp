#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


char combine[100][4];
char oppose[100][4];
int combs;
int opps;
int bufSize;
char buffer[1000];

char isCombine(char c) {
    if (bufSize == 0) return 0;

    char last = buffer[bufSize - 1];
    FOR(i, combs)
        if (combine[i][0] == c && combine[i][1] == last || combine[i][0] == last && combine[i][1] == c)
            return combine[i][2];
    return 0;
}


bool isOppose(char c) {
    if (bufSize == 0) return false;

    FOR(i, opps)
        FOR(j, bufSize)
            if (buffer[j] == oppose[i][0] && c == oppose[i][1] || buffer[j] == oppose[i][1] && c == oppose[i][0])
                return true;
    return false;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int ccc=1;ccc<=cases;ccc++) {
        scanf("%d", &combs);
        FOR(i, combs) scanf("%s", combine[i]);
        scanf("%d", &opps);
        FOR(i, opps) scanf("%s", oppose[i]);

        int n;
        char input[1000];
        scanf("%d%s", &n, input);

        bufSize = 0;

        FOR(i, n) {
            char c = isCombine(input[i]);
            if (c) {
                buffer[bufSize - 1] = c;
            } else {
                if (isOppose(input[i])) {
                    bufSize = 0;
                } else {
                    buffer[bufSize++] = input[i];
                }
            }
        }

        printf("Case #%d: [", ccc);
        FOR(i, bufSize) {
            if (i > 0) printf(", ");
            printf("%c", buffer[i]);
        }
        printf("]\n");
    }
}

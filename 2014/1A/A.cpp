// Check first device against all the outlets, get the state of the flips and verify, if it is possible to plug all other devices into all other outlets
// http://code.google.com/codejam/contest/2984486/dashboard#s=p0
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 200
#define MAX_L 50

using namespace std;

long long int device[MAX_N];
long long int outlet[MAX_N], outlet2[MAX_N];
int n;
int l;

long long int convert(char *data) {
    long long int result = 0;
    while (*data) {
        result += *data - '0';
        result <<= 1;
        data++;
    }
    return result;
}

int cmp(const void *p1, const void *p2) {
    long long int i1 = (*(long long int *)p1);
    long long int i2 = (*(long long int *)p2);
    if (i1 < i2) return -1;
    if (i1 > i2) return 1;
    return 0;
}

bool equal(long long int *a, long long int *b, int c) {
    FOR(i, c) if (a[i] != b[i]) return false;
    return true;
}

int bits(long long int a) {
    int res = 0;
    while (a > 0) {
        if ((a & 1) == 1) res++;
        a >>= 1;
    }
    return res;
}


int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        char buffer[MAX_L];
        scanf("%d%d", &n, &l);
        FOR(i, n) {
            scanf("%s", buffer);
            outlet[i] = convert(buffer);
        }
        FOR(i, n) {
            scanf("%s", buffer);
            device[i] = convert(buffer);
        }
        qsort(device, n, sizeof(device[0]), cmp);
        qsort(outlet, n, sizeof(outlet[0]), cmp);
        int res = l + 1;
        FOR(i, n) {
            long long int mask = device[0] ^ outlet[i];
            FOR(j, n) outlet2[j] = outlet[j] ^ mask;
            qsort(outlet2, n, sizeof(outlet2[0]), cmp);
            if (equal(device, outlet2, n) && bits(mask) < res) {
                res = bits(mask);
            }
        }

        printf("Case #%d: ", c);
        if (res > l) printf("NOT POSSIBLE\n"); else printf("%d\n", res);
    }
}

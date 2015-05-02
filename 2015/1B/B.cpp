// Fill in half the apartments without any walls. Then start filling corners (with 2 walls), sides (with 3 walls) and all other positions (with 4 walls).
// https://code.google.com/codejam/contest/8224486/dashboard#s=p1
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_TOTAL_POS 40

int r, c, n;
int result;
int totalPos;

bool used[MAX_TOTAL_POS];

char cc = 0;
int getInt() {
    int r = 0;
    while (!(cc >= '0' && cc <= '9')) cc = getc_unlocked(stdin);
    while (cc >= '0' && cc <= '9') {
        r = r * 10 + (cc - '0');
        cc = getc_unlocked(stdin);
    }
    return r;
}


int main(void) {
    int cases = getInt();
    for(int cc=1;cc<=cases;cc++) {
        r = getInt();
        c = getInt();
        n = getInt();
        result = 0;
        if (n * 2 - 1 <= r * c) {
            result = 0;
        } else  if (r == 1 || c == 1) {
            if (c == 1) {
                int t = c;
                c = r;
                r = t;
            }
            n -= (r * c + 1) / 2;
            if (n > 0) {
                if (c % 2 == 0) {
                    result++;
                    n--;
                }
                result += n * 2;
            }
        } else {
            n -= (r * c + 1) / 2;
            int corners = r % 2 == 1 && c % 2 == 1 ? 0 : 2;
            if (n >= corners) {
                result += 2 * corners;
                n -= corners;
            } else {
                result += 2 * n;
                n = 0;
            }
            int sides = 0;
            if (r % 2 == 0 && c % 2 == 0) sides = r + c - 4;
            else if (r % 2 == 0 && c % 2 == 1) sides = (c - 1) / 2 + (c + 1) / 2 - 2 + r - 2;
            else if (c % 2 == 0 && r % 2 == 1) sides = (r - 1) / 2 + (r + 1) / 2 - 2 + c - 2;
            else sides = c - 1 + r - 1;

            if (n >= sides) {
                result += 3 * sides;
                n -= sides;
            } else {
                if (r % 2 == 1 && c % 2 == 1 && n > 2) result--;
                result += 3 * n;
                n = 0;
            }
            result += 4 * n;
        }
        printf("Case #%d: %d\n", cc, result);
    }
}

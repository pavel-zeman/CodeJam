#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <gmpxx.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

using namespace std;

mpz_class t[10000];
int n;


mpz_class gcd(mpz_class a, mpz_class b) {
    while (b != 0) {
        mpz_class r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d", &n);
        FOR(i, n) {
            char num[1000];
            scanf("%s", num);
            t[i].set_str(num, 10);
        }
        mpz_class tmax = abs(t[1] - t[0]);
        for(int i=2;i<n;i++) tmax = gcd(tmax, abs(t[i] - t[i - 1]));
        mpz_class res = (tmax - (t[0] % tmax)) % tmax;
        printf("Case #%d: %s\n", c, res.get_str().c_str());
    }
}

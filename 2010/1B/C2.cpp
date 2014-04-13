#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <gmpxx.h>
#include <string>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define MOD 100003
#define MAX 1000

int n;

int res[MAX][MAX];
int cmb[MAX][MAX];

using namespace std;

mpz_class f[1000];

int fact(int n) {
    int total = 1;
    for(int i=1;i<=n;i++) total *= i;
    return total;
}

int comb(int n, int k) {
    if (n < k) return 1;
    //printf("Comb: %d %d\n", n, k);
    if (n < 0 || k < 0 || n >= MAX || k >= MAX) {
        printf("ERRRR\n");
    }

    if (cmb[n][k] == -1 ) {
        mpz_class res =  (f[n] / f[k] / f[n-k]) % MOD;
        //printf("Comb: %s\n", res.get_str().c_str());
        cmb[n][k] = atoi(res.get_str().c_str());
    }
    return cmb[n][k];
}

int main(void) {

    FOR(i, MAX) FOR(j, MAX) { res[i][j] = -1; cmb[i][j] = -1; }

    for(int i=2;i<=500;i++) res[i][1] = 1;
    f[0] = 1;
    f[1] = 1;
    for(int i=2;i<=500;i++) {
        f[i] = f[i - 1] * i;
        //printf("Fact %d %s\n", i, f[i].get_str().c_str());
    }


    for(int i = 2; i<=500; i++) {
        for(int j = 2; j<i;j++) {
            int total2 = 0;
            for(int k = 1;k<j;k++) {
                if (i - j >= j - k) {
                    //if (i == 4) printf("%d %d %d %d\n", i, j, k, comb(i - j - 1, j - k - 1));
                    long long int v1 = res[j][k];
                    long long int v2 = comb(i - j - 1, j - k - 1);
                    total2 += (v1 * v2) % MOD;
                    total2 %= MOD;
                }
            }
            res[i][j] = total2;
        }
    }


    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d", &n);
        int total = 0;

        for(int i=1;i<n;i++)
            total += res[n][i];

        printf("Case #%d: %d\n", c, total % MOD);
    }
}

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define P 100000000

long long int l, h;
int n;

long long int other[10000];


char prime[P];
int primeCount = 0;
int primes[10000000];

struct primeItem {
    int num;
    int count;
};

struct primeData {
    struct primeItem items[100];
    int count;
} otherPrimes[10000];


bool test(long long int f) {
    FOR(i, n)
        if (f % other[i] != 0 && other[i] % f != 0) return false;
    return true;
}



struct primeData generatePrimes(long long int data) {
    struct primeData result;
    result.count = 0;
    FOR(i, primeCount) {
        if (data % primes[i] == 0) {
            int c = 1;
            long long int div = primes[i];
            while (data % div == 0) {
                div *= primes[i];
                c++;
            }
            result.items[result.count].num = i;
            result.items[result.count].count = c - 1;
            result.count++;
        }
    }
    return result;
}

void addNsn(struct primeData *toAdd, struct primeItem data) {
    int i = 0;
    while (i < toAdd->count) {
        if (data.num <= toAdd->items[i].num) {
             break;
        }
    }
    if (i < toAdd->count) {
        if (data.num == toAdd->items[i].num) {
            if (data.count > toAdd->items[i].count) toAdd->items[i].count = data.count;
        } else {
            for(int j=toAdd->count;j>i;j--) toAdd->items[j] = toAdd->items[j - 1];
            toAdd->count++;
            toAdd->items[i] = data;
        }
    } else {
        toAdd->items[i] = data;
        toAdd->count++;
    }
}

void generateNsn(int start, int end) {
    struct primeData result = otherPrimes[start];
    for(int i=start+1;i<=end;i++) {
        FOR(j, otherPrimes[i].count) {
            addNsn(&result, otherPrimes[i].items[j]);
        }
    }
}

long long int gcd(long long int a, long long int b) {
    return a == 0 ? b : gcd(b % a, a);
}

long long int getGcd(int start, int end) {
    if (end == start) return other[end];
    long long int res = other[start];
    for(int i=start + 1;i<=end;i++) {
        res = gcd(res, other[i]);
    }
    return res;
}

int compare(const long long int *a, const long long int *b) {
    return *a > *b ? 1 : (*a < *b ? -1 : 0);
}

long long int find(long long int nsn, long long int gcd) {
    if (nsn > gcd) return -1;
    if (nsn == gcd) return (nsn >= l && nsn <= h) ? nsn : -1;
    if (nsn > h || gcd < l) return -1;
    struct primeData divData = generatePrimes(
}

int main(void) {
    FOR(i, P) prime[i] = 1;

    for(int i=2;i<=10000;i++) {
        if (prime[i]) {
            int j = i;
            while ((j += i) < P) prime[j] = 0;
        }
    }
    FORE(i, 2, P) if (prime[i]) {
        primes[primeCount++] = i;
    }
    printf("%d\n", primeCount);


    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d%lld%lld", &n, &l, &h);
        FOR(i, n) scanf("%lld", &other[i]);
        qsort(other, n, sizeof(long long int), (int(*)(const void *, const void *))compare);

        long long min = find(1, gcd(0, n - 1);
        if (min == -1) {
        }

        FOR(i, n - 1) {

        }

        long long int freq = -1;
        for(long long int i = l;i<=h;i++) {
            if (test(i)) {
                freq = i;
                break;
            }
        }

        printf("Case #%d: ", c);
        if (freq == -1) printf("NO\n"); else printf("%lld\n", freq);

    }
}

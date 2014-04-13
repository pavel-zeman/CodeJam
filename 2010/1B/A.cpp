#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <string>
#include <map>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


using namespace std;

int n, m;
char path[1000];
int total;

class dir {
public:
    map<string, dir> items;
} root;


void insert(char *path) {
    char *s = path;
    dir *r = &root;
    while (*s) {
        char *s2 = ++s;
        while (*s2 && *s2 != '/') s2++;
        char orig = *s2;
        *s2 = 0;
        if (r->items.find(s) == r->items.end()) {
            dir * nd = new dir();
            //nd.items.clear();
            r->items[s] = *nd;
            //r.items["AAA"] = nd;
            total++;
            //printf("Inserting item %s %d %d\n", s, r->items.size(), root.items.size());
        }
        r = &(r->items[s]);
        *s2 = orig;
        s = s2;
    }
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d %d", &n, &m);
        root.items.clear();
        char x[1000];
        strcpy(x, "/aaa");
        //printf("Root: %d\n", root.items.size());
        insert(x);
        //printf("Root: %d\n", root.items.size());
        strcpy(x, "/bbb");
        insert(x);
        //printf("Root: %d\n", root.items.size());

        total = 0;
        FOR(i, n) {
            scanf("%s", path);
            insert(path);
        }

        total = 0;
        FOR(i, m) {
            scanf("%s", path);
            insert(path);
        }

        printf("Case #%d: %d\n", c, total);
    }
}

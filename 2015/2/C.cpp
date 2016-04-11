//
// https://code.google.com/codejam/contest/8234486/dashboard#s=p2
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <set>
#include <vector>
#include <string>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 30

int n;
char buf[100000];
vector<string> first;
vector<string> second;
vector<string> other[MAX_N];
set<string> english;
set<string> french;
int mmm;

void readLine(vector<string> *res) {
    gets(buf);
    char *start = buf;
    while (true) {
        char *t = start;
        while (*t >= 'a' && *t <= 'z') t++;
        char temp = *t;
        *t = 0;
        string *ss = new string((const char *)start);
        res->push_back(*ss);
        if (temp != ' ') break;
        start = t + 1;
    }
}

void test(int level) {
    if (level == n - 2) {
       int words = 0;
       for (set<string>::iterator it=english.begin(); it!=english.end(); ++it) {
          if (french.find(*it) != french.end()) words++;
       }
       if (words < mmm) mmm = words;
    } else {
        bool inserted[100];
        FOR(j, (int)other[level].size()) inserted[j] = english.insert(other[level][j]).second;
        test(level + 1);
        FOR(j, (int)other[level].size()) if (inserted[j]) english.erase(other[level][j]);

        FOR(j, (int)other[level].size()) inserted[j] = french.insert(other[level][j]).second;
        test(level + 1);
        FOR(j, (int)other[level].size()) if (inserted[j]) french.erase(other[level][j]);
    }
}


int main(void) {
    gets(buf);
    int cases = atoi(buf);
    for(int cc=1;cc<=cases;cc++) {
       gets(buf);
       n = atoi(buf);
       first.clear();
       second.clear();
       english.clear();
       french.clear();
       readLine(&first);
       readLine(&second);
       FOR(i, n - 2) {
           other[i].clear();
           readLine(&other[i]);
       }
       mmm = 1000000000;
       FOR(i, (int)first.size()) english.insert(first[i]);
       FOR(i, (int)second.size()) french.insert(second[i]);
       test(0);

       printf("Case #%d: %d\n", cc, mmm);
    }
}

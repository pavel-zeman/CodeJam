// Description
// https://codingcompetitions.withgoogle.com/codejam/round/000000000019ffb9/000000000033871f
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(int)(t);c++)
#define LLI long long int
#define MOD 1000000007


char ccc = 0;
int getInt() {
    int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}

int getString(char *start) {
    char *data = start;
    while (!(ccc > ' ' && ccc <= '~')) ccc = getc_unlocked(stdin);
    while (ccc > ' ' && ccc <= '~') {
        *data++ = ccc;
        ccc = getc_unlocked(stdin);
    }
    *data = 0;
    return data - start;
}


int getSignedInt() {
    int r = 0;
    while (!(ccc == '-' || (ccc >= '0' && ccc <= '9'))) ccc = getc_unlocked(stdin);
    bool minus = ccc == '-';
    if (minus) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

long long int getLongLongInt() {
    long long int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}


template <class type> void print(type a) {
    if (a < 0) {
        putc_unlocked('-', stdout);
        a = -a;
    }
    if (a == 0) {
        putc_unlocked('0', stdout);
    } else {
        char result[20];
        int resSize = 0;
        while (a > 0) {
            result[resSize++] = '0' + a % 10;
            a /= 10;
        }
        while (--resSize >= 0) putc_unlocked(result[resSize], stdout);
    }
    putc_unlocked('\n', stdout);
}

void printString(const char *str) {
    while (*str) putc_unlocked(*str++, stdout);
    putc_unlocked('\n', stdout);
}

int power(int a, int b) {
    int sq = a;
    int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * (LLI)sq % MOD;
        sq = sq * (LLI)sq % MOD;
        b >>= 1;
    }
    return result;
}

int inv(int a) {
    return power(a, MOD - 2);
}

template <class type> type gcd(type a, type b) {
    return b == 0 ? a : gcd(b, a % b);
}

void fail() {
    *((char *)0) = 0;
}

double cpu() {
    return clock() / (double)CLOCKS_PER_SEC;
}

#define MAX_C 128
#define MAX_D 1024
int connection[MAX_C][MAX_C];
int latency[MAX_C][MAX_C];

int c, d;
vector<pair<int, int>> times;
vector<pair<int, int>> preds;
vector<int> neigh[MAX_C];

bool done[MAX_C];
int doneTimes[MAX_C];

int result[MAX_D];


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        c = getInt();
        d = getInt();

        times.clear();
        preds.clear();

        FOR(i, c - 1) {
            int v = getSignedInt();
            if (v > 0) times.push_back(make_pair(v, i + 1));
            else preds.push_back(make_pair(-v , i + 1));
        }
        sort(times.begin(), times.end());
        sort(preds.begin(), preds.end());

        FOR(i, c) FOR(j, c) connection[i][j] = 0;
        FOR(i, c) neigh[i].clear();
        FOR(i, c) done[i] = false;
        done[0] = true;
        doneTimes[0] = 0;


        FOR(i, d) {
            int u = getInt() - 1;
            int v = getInt() - 1;
            connection[u][v] = i + 1;
            connection[v][u] = i + 1;
            neigh[u].push_back(v);
            neigh[v].push_back(u);
        }

        int predPos = 0;
        int timePos = 0;
        int fixed = 1;
        int time = 0;
        while (predPos < preds.size()) {
            if (preds[predPos].first > fixed) {
                int currentTime = times[timePos].first;
                while (timePos < times.size() && currentTime == times[timePos].first) {
                    int node = times[timePos].second;
                    doneTimes[node] = currentTime;
                    done[node] = true;
                    FOR(i, neigh[node].size()) {
                        int n = neigh[node][i];
                        if (done[n]) {
                            if (doneTimes[n] < currentTime) latency[node][n] = latency[n][node] = currentTime - doneTimes[n];
                            else latency[node][n] = latency[n][node] = 1;
                        }
                    }
                    timePos++;
                    fixed++;
                }
                time = currentTime;
            } else {
                int currentTime = time + 1;
                int currentPreds = preds[predPos].first;
                while (predPos < preds.size() && currentPreds == preds[predPos].first) {
                    int node = preds[predPos].second;
                    doneTimes[node] = currentTime;
                    done[node] = true;
                    FOR(i, neigh[node].size()) {
                        int n = neigh[node][i];
                        if (done[n]) {
                            if (doneTimes[n] < currentTime) latency[node][n] = latency[n][node] = currentTime - doneTimes[n];
                            else latency[node][n] = latency[n][node] = 1;
                        }
                    }
                    predPos++;
                    fixed++;
                }
                time = currentTime;
            }
        }

        while (timePos < times.size()) {
            int currentTime = times[timePos].first;
            while (timePos < times.size() && currentTime == times[timePos].first) {
                int node = times[timePos].second;
                doneTimes[node] = currentTime;
                done[node] = true;
                FOR(i, neigh[node].size()) {
                    int n = neigh[node][i];
                    if (done[n]) {
                        if (doneTimes[n] < currentTime) latency[node][n] = latency[n][node] = currentTime - doneTimes[n];
                        else latency[node][n] = latency[n][node] = 1;
                    }
                }
                timePos++;
                fixed++;
            }
            time = currentTime;
        }

        FOR(i, c) FOR(j, c) if (connection[i][j] > 0) {
            result[connection[i][j] - 1] = latency[i][j];
        }

        printf("Case #%d: ", tt + 1);
        FOR(i, d) printf("%d ", result[i]);
        printf("\n");
    }
}


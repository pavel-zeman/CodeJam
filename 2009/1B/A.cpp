#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

char line[1000];


int inputPos;
char inputData[100000];

struct {
  char feature[20];
  double w;
  int first;
  int second;
} tree[10000];

int treeItems;


void white(void) {
  while (inputData[inputPos] == ' ') inputPos++;
}

int parseTree(void) {
  int numberStart;
  char numberString[100];

  //printf("Parsing tree: %d\n", inputPos);
  int currentItem = treeItems++;
  white();

  switch (inputData[inputPos]) {
    case '(':
      inputPos++;
      white();
      numberStart = inputPos;
      while (isdigit(inputData[inputPos]) || inputData[inputPos] == '.') inputPos++;
      strncpy(numberString, inputData + numberStart, inputPos - numberStart);
      numberString[inputPos - numberStart] = 0;

      tree[currentItem].w = atof(numberString);
      //printf("Reading w: %lf\n", tree[currentItem].w);

      white();

      if (inputData[inputPos] == ')') {
        tree[currentItem].feature[0] = 0;
        inputPos++;
      } else {
        numberStart = inputPos;
        while (isalpha(inputData[inputPos])) inputPos++;
        strncpy(tree[currentItem].feature, inputData + numberStart, inputPos - numberStart);
        tree[currentItem].feature[inputPos - numberStart] = 0;
        tree[currentItem].first = parseTree();
        tree[currentItem].second = parseTree();

        white();
        assert (inputData[inputPos] == ')');
        inputPos++;
      }
      return currentItem;
    default:
      assert(false);
  }
  return -1;
}


int main(void) {
  int cases;


  gets(line);
  cases = atoi(line);
  for(int c=1;c<=cases;c++) {
    int l;
    gets(line);
    l = atoi(line);

    // read input
    inputData[0] = 0;
    FOR(i, l) {
      gets(inputData + strlen(inputData));
      int x = strlen(inputData);
      if (inputData[x - 1] == 10 || inputData[x - 1] == 13) inputData[x - 1] = 0;
    }
    treeItems = 0;
    inputPos =0;
    parseTree();


    int a;
    gets(line);
    a = atoi(line);


    printf("Case #%d:\n", c);

    FOR(i, a) {
      char fc[100];
      char features[200][20];
      int featureCount;
      int fcStart;
      inputPos = 0;
      gets(line);

      //printf("Reading animal\n");
      while (line[inputPos] != ' ') inputPos++;
      inputPos++;
      fcStart = inputPos;
      while (isdigit(line[inputPos])) inputPos++;
      strncpy(fc, line + fcStart, inputPos - fcStart);
      fc[inputPos - fcStart] = 0;
      featureCount = atoi(fc);
      FOR(j, featureCount) {
        inputPos++;
        fcStart = inputPos;
        //printf("Reading feature\n");
        while (isalpha(line[inputPos])) inputPos++;
        strncpy(features[j], line + fcStart, inputPos - fcStart);
        features[j][inputPos - fcStart] = 0;
      }

      double result = 1;
      int tp = 0;
      result *= tree[tp].w;
      while (tree[tp].feature[0]) {
        bool found = false;
        FOR(j, featureCount)
          if (!strcmp(tree[tp].feature, features[j])) {
            found = true;
            break;
          }

        tp = found ? tree[tp].first : tree[tp].second;
        result *= tree[tp].w;
      }
      printf("%.7lf\n", result);
    }
  }
}

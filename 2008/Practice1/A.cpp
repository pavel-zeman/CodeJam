#include <stdio.h>
#include <string.h>

char alienNumber[100], srcLang[100], dstLang[100];
int srcDigits, dstDigits;


int getSrcDigit(char value) {
  for(int i=0;i<srcDigits;i++)
    if (srcLang[i] == value) 
      return i;
}

int main(int argc, char *argv[]) {
  int numCases;
  
  scanf("%d", &numCases);
  
  for(int c=0;c<numCases;c++) {
    scanf("%s %s %s", alienNumber, srcLang, dstLang);
    srcDigits = strlen(srcLang);
    dstDigits = strlen(dstLang);
  
    int number = 0;
    int currentValue = 1;
    for(int i=strlen(alienNumber)-1;i>=0;i--) {
      number += getSrcDigit(alienNumber[i]) * currentValue;
      currentValue *= srcDigits;
    }
    
    char dstNumber[100];
    char dstNumberReversed[100];
    int i=0;
    for(;number > 0;number /= dstDigits)
      dstNumber[i++] = dstLang[number % dstDigits];
    
    for(int j=0;j<i;j++)
      dstNumberReversed[j] = dstNumber[i - 1 - j];
      
    dstNumberReversed[i] = 0;
    
    printf("Case #%d: %s\n", c + 1, dstNumberReversed);
  }    

}

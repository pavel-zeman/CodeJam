#include <stdio.h>
#include <string.h>

#define ACUTE 1
#define OBTUSE 2
#define RIGHT 3

struct {
  int x;
  int y;
} points[3];

int lengths[3];

char equal(int a, int b) {
  return points[a].x == points[b].x && points[a].y == points[b].y;
}

char colinear(void) {
  return (points[1].y - points[0].y) * (points[2].x - points[0].x) == (points[2].y - points[0].y) * (points[1].x - points[0].x);
}


int sqr(int x) { return x * x; }

int getIndex(int index) {
  return index < 0 ? index + 3 : (index > 2 ? index - 3 : index);
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  
  for(int c=1;c<=cases;c++) {
    scanf("%d %d %d %d %d %d", &points[0].x, &points[0].y, &points[1].x, &points[1].y, &points[2].x, &points[2].y);
    
    if (equal(0, 1) || equal(0, 2) || equal(1, 2) || colinear()) {
      printf("Case #%d: not a triangle\n", c);
    } else {
      for(int i=0;i<3;i++) lengths[i] = sqr(points[getIndex(i+1)].x - points[i].x) + sqr(points[getIndex(i+1)].y - points[i].y);
      char isosceles = lengths[0] == lengths[1] || lengths[0] == lengths[2] || lengths[1] == lengths[2];
      char angle = ACUTE;
      for(int i=0;i<3;i++) {
        int scalar = (points[getIndex(i+1)].x - points[i].x) * (points[getIndex(i -1)].x - points[i].x) +
                     (points[getIndex(i+1)].y - points[i].y) * (points[getIndex(i -1)].y - points[i].y);
        if (scalar == 0) {
          angle = RIGHT;
          break;
        } else if (scalar < 0) {
          angle = OBTUSE;
          break;
        }
      }
      printf("Case #%d: %s %s triangle\n", c, isosceles ? "isosceles" : "scalene", 
        angle == ACUTE ? "acute" : (angle == RIGHT ? "right" : "obtuse"));
    }
  }
}

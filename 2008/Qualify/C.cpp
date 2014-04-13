#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


double f, R, t, r, g;

struct point {
  double x;
  double y;
};

double sqr(double x) {
  return x * x;
}

struct point lineIntersect(struct point i, struct point j, double radius) {
  struct point res;
  if (i.x == j.x) {
    if (sqr(i.x) >= sqr(radius)) res.x = 0; else {
      res.x = i.x;
      res.y = sqrt(sqr(radius) - sqr(res.x));
      if (res.y >= fmax(i.y, j.y) || res.y <= fmin(i.y, j.y)) res.x = 0;
    }
  } else {
    if (sqr(i.y) >= sqr(radius)) res.x = 0; else {
      res.y = i.y;
      res.x = sqrt(sqr(radius) - sqr(res.y));
      if (res.x >= fmax(i.x, j.x) || res.x <= fmin(i.x, j.x)) res.x = 0;
    }
  }
  return res;
}


double triangleArea(double a, double b, double c) {
  double s = (a + b + c) / 2;
  //printf("Triangle area: %.6lf\n", sqrt(s * (s - a) * (s - b) * (s - c)));
  return sqrt(s * (s - a) * (s - b) * (s - c));
}

double circleArea(struct point a, struct point b, double radius) {
  double a1 = atan(a.y / a.x);
  double a2 = atan(b.y / b.x);
  //printf("Circle area: %.6lf\n", fabs(a1 - a2) * sqr(radius) / 2);
  return fabs(a1 - a2) * sqr(radius) / 2;
}

double interpolateX(struct point p, double y) {
  return y * p.x / p.y;
}

double interpolateY(struct point p, double x) {
  return x * p.y / p.x;
}

double distance(struct point p) {
  return sqrt(sqr(p.x) + sqr(p.y));
}

double intersect(double x, double y) {
  struct point A, B, C, D;
  struct point pa, pb, pc, pd;
  double R2 = R - t - f;
  
  // points
  A.x = x + f;
  A.y = y + f;
  B.x = x + g - f;
  B.y = y + f;
  C.x = x + g - f;
  C.y = y + g - f;
  D.x = x + f;
  D.y = y + g - f;
  
  // completely outside
  if (sqr(A.x) + sqr(A.y) >= sqr(R2)) return 0;
  
  // completely inside
  if (sqr(C.x) + sqr(C.y) <= sqr(R2)) return sqr(g - 2 * f);
  
  // intersection points
  pa = lineIntersect(A, B, R2);
  pb = lineIntersect(B, C, R2);
  pc = lineIntersect(C, D, R2);
  pd = lineIntersect(D, A, R2);
  
  if (pd.x != 0 && pa.x != 0) {
    // case 1
    return circleArea(pd, pa, R2) - 
      triangleArea(pd.y - A.y, distance(A), distance(pd)) -
      triangleArea(pa.x - A.x, distance(A), distance(pa));
  } else if (pd.x != 0 && pb.x != 0) {
    // case 2
    struct point t;
    t.y = A.y;
    t.x = interpolateX(pb, t.y);
    return circleArea(pd, pb, R2) - 
      triangleArea(pd.y - A.y, distance(A), distance(pd)) -
      triangleArea(t.x - A.x, distance(A), distance(t)) +
      (pb.y - B.y) * (B.x - t.x) / 2;
  } else if (pc.x != 0 && pa.x != 0) {
    // case 3
    struct point t;
    t.x = interpolateX(pc, A.y);
    if (t.x >= A.x) {
      t.y = A.y; 
      return circleArea(pc, pa, R2) -
        triangleArea(distance(t), pa.x - t.x, distance(pa)) +
        (g - 2 * f) * (pc.x - t.x) / 2 + (g - 2 * f) * (t.x - A.x);
    } else {
      t.y = interpolateY(pc, A.x);
      t.x = A.x;
      return circleArea(pc, pa, R2) -
        triangleArea(distance(t), t.y - A.y, distance(A)) -
        triangleArea(pa.x - A.x, distance(pa), distance(A)) +
        (pc.x - A.x) * (D.y - t.y) / 2;
    }
  } else if (pb.x != 0 && pc.x != 0) {
    // case 4
    struct point tc, tb;
    tc.x = interpolateX(pc, A.y);
    if (tc.x  >= A.x) {
      tc.y = A.y;
      tb.y = A.y;
      tb.x = interpolateX(pb, A.y);
      return circleArea(pc, pb, R2) -
        triangleArea(distance(tc), tb.x - tc.x, distance(tb)) +
        (pb.y - B.y) * (B.x - tb.x) / 2 + (g - 2 * f) * (pc.x - tc.x) / 2 + (g - 2 * f) * (tc.x - A.x);
    } else {
      tc.x = A.x;
      tc.y = interpolateY(pc, tc.x);
      tb.x = interpolateX(pb, A.y);
      if (tb.x >= A.x) {
        tb.y = A.y;
        return circleArea(pc, pb, R2) -
          triangleArea(distance(tc), distance(A), tc.y - A.y) -
          triangleArea(distance(A), distance(tb), tb.x - A.x) +
          (pb.y - B.y) * (B.x - tb.x) / 2 + (pc.x - D.x) * (D.y - tc.y) / 2;
      } else {
        tb.y = interpolateY(pb, A.x);
        tb.x = A.x;
        return circleArea(pc, pb, R2) -
          triangleArea(distance(tc), distance(tb), tc.y - tb.y) +
          (pc.x - D.x) * (D.y - tc.y) / 2 + (g - 2 * f) * (pb.y - tb.y) / 2 + (g - 2 * f) * (tb.y - A.y);
      }    
    
    }
  } else {
    printf("Incorrect data!!!!!\n");
    return -111111111;
  }
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int c=1;c<=cases;c++) {
    double res;
    scanf("%lf %lf %lf %lf %lf", &f, &R, &t, &r, &g);
    
    if (2 * f >= g) {
      // the ball cannot go through the holes
      res = 1;
    } else {
      double holes = 0;
      double y = r;
      int j = 0;
      while (y < R - t) {
        double x = r;
        int i = 0;
        while (x * x + y * y < (R - t) * (R - t)) {
          holes += intersect(x, y);
          //printf("%.6lf %.6lf %.6lf\n", x, y, holes);
          x = r + ++i * (g + 2 * r);
        }
        y = r + ++j * (g + 2 * r);
      }
      //printf("Total holes and area: %.6lf %.6lf\n", 4 * holes, (M_PI * R * R));
      res = 1 - 4 * holes / (M_PI * R * R);
    }
     
    printf("Case #%d: %.6lf\n", c, res);
  }
}

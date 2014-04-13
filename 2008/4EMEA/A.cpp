#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int xx1[3], yy1[3], x2[3], y2[3];

double matrix[3][4];

double solution[3];

void move(int a, int b) {
  FOR(i, 4) {
    double x = matrix[a][i];
    matrix[a][i] = matrix[b][i];
    matrix[b][i] = x;
  }
}

void printMatrix() {
  FOR(i, 3) {
    FOR(j, 4) printf("%lf ", matrix[i][j]);
    printf("\n");
  }
  printf("\n");
}

void solve(void) {
  //printMatrix();

  FOR(i, 2) {
    if (matrix[i][i] == 0) {
      FORE(j, i + 1, 3) {
        if (matrix[j][i] != 0) {
          move(i, j);
          break;
        }
      }
    }
    assert(matrix[i][i] != 0);

    FORE(j, i + 1, 3) {
      double coef = matrix[j][i] / matrix[i][i];
      FOR(k, 4) matrix[j][k] -= coef * matrix[i][k];
    }
  }

  for(int i=2;i>0;i--) {
    assert(matrix[i][i] != 0);

    for(int j=i-1;j>=0;j--) {
      double coef = matrix[j][i] / matrix[i][i];
      FOR(k, 4) matrix[j][k] -= coef * matrix[i][k];
    }
  }

  //printMatrix();

  FOR(i, 3) {
    matrix[i][3] /= matrix[i][i];
    matrix[i][i] = 1;
    solution[i] = matrix[i][3];
  }

  //printMatrix();

}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for(int cas=1;cas<=cases;cas++) {
    FOR(i, 3) scanf("%d %d", &xx1[i], &yy1[i]);
    FOR(i, 3) scanf("%d %d", &x2[i], &y2[i]);

    FOR(i, 3) { matrix[i][0] = xx1[i]; matrix[i][1] = yy1[i]; matrix[i][2] = 1; matrix[i][3] = x2[i]; }
    solve();
    double a = solution[0], b = solution[1], c = solution[2];
    FOR(i, 3) { matrix[i][0] = xx1[i]; matrix[i][1] = yy1[i]; matrix[i][2] = 1; matrix[i][3] = y2[i]; }
    solve();
    double d = solution[0], e = solution[1], f = solution[2];

    /*FOR(i, 3) {
      if (fabs(xx1[i] * a + yy1[i] * b + c - x2[i]) > 1e-12) {
        printf("Error: %lf %lf\n", xx1[0] * a + yy1[0] * b + c, (double)x2[0]);
      }

      if (fabs(xx1[i] * d + yy1[i] * e + f - y2[i]) > 1e-12) {
        printf("Error: %lf %lf\n", xx1[0] * d + yy1[0] * e + f, (double)y2[0]);
      }
    }*/

    assert(fabs(xx1[0] * d + yy1[0] * e + f - y2[0]) < 0.001);

    double x = x2[0], xo = x;
    double y = y2[0], yo = y;


#define DIF 1e-9
    FORE(i, 1, 10000000) {
      double xa = x * a + y * b + c;
      double ya = x * d + y * e + f;
      x = xa;
      y = ya;
      if (i % 1000 == 0) {
        if (fabs(x - xo) < DIF && fabs(y - yo) < DIF) {
          break;
        }
        xo = x;
        yo = y;
      }
    }

    //printf("%lf %lf\n%lf %lf\n", x, x * a + y * b + c, y, x * d + y * e + f);

    //printf("%lf %lf\n", x, y);



    printf("Case #%d: %lf %lf\n", cas, x, y);
  }
}

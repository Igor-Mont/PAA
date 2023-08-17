#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
  int x, y;
}Point;

void print(Point *P, int n) {
  for (int i = 0; i < n; i++) {
    printf("(%d %d)\n", P[i].x, P[i].y);
  }
}

int compareByX(const void *a, const void *b) {
  Point *p1 = (Point *)a;
  Point *p2 = (Point *)b;

  if (p1->x < p2->x)
    return -1;
  else if (p1->x > p2->x) {
    return 1;
  }

  if (p1->y < p2->y)
    return -1;
  else if (p1->y > p2->y) {
    return 1;
  }

  return 0;
}

int compareByY(const void *a, const void *b) {
  Point *p1 = (Point *)a;
  Point *p2 = (Point *)b;

  if (p1->y > p2->y)
    return -1;
  else if (p1->y < p2->y) {
    return 1;
  }

  if (p1->x > p2->x)
    return -1;
  else if (p1->x < p2->x) {
    return 1;
  }

  return 0;
}

double calculateSum(Point *orderByX, Point *orderByY, int n) {
  double result = 0;

  Point *peaks = malloc(sizeof(Point)*n);

  peaks[0] = orderByY[0];
  int lenPeaky = 1;
  int currentGreaterPeaky = orderByY[0].x;

  for(int i = 1; i < n-1; i++) {
    if(orderByY[i].x > currentGreaterPeaky) {
      currentGreaterPeaky = orderByY[i].x;
      peaks[lenPeaky++] = orderByY[i];
    }
  }

  //print(peaks, lenPeaky);

  Point A, B, C;
  int j = 0;
  for(int i = 0; i < lenPeaky; i++) {
    A = peaks[i];

    //get B
    for(;j < n; j++) {
      if(A.x == orderByX[j].x) {
        B = orderByX[j+1];
        break;
      }
    }

    C = peaks[i+1];
    int dy = B.y - A.y;

    int dyPow = pow(dy, 2);
    int dxPow = pow(B.x - A.x, 2);
    double hPow = dyPow + dxPow;

    double tetha = dy / sqrt(hPow);

    int dyAC = A.y - C.y;
    double h = dyAC / tetha;

    //printf("distancia induvidual: %lf\n", h);
    result += fabs(h);
  }

  return result;
}



int main() {
  int cases, n;
  scanf("%d", &cases);
  while(cases) {
    scanf("%d", &n);
    Point *orderByX = malloc(sizeof(Point)*n);
    Point *orderByY = malloc(sizeof(Point)*n);

    for (int i = 0; i < n; i++) {
      scanf("%d %d", &orderByX[i].x, &orderByX[i].y);
      orderByY[i].x = orderByX[i].x;
      orderByY[i].y = orderByX[i].y;
    }

    qsort(orderByX, n, sizeof(Point), compareByX);
    qsort(orderByY, n, sizeof(Point), compareByY);

    double sum = calculateSum(orderByX, orderByY, n);
    printf("%.2lf\n", sum);

    cases--;
  }

}

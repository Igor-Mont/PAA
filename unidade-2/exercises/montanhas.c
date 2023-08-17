#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct {
  int x;
  int y;
} Point;

void print_vector(Point * points, int length) {
  for (int i = 0; i < length; i++) printf("(%d, %d)\n", points[i].x, points[i].y);
  printf("\n");
}

int compareByX(const void * a, const void * b) {
  Point * p1 = (Point *)a;
  Point * p2 = (Point *)b;
  
  if(p1->x < p2->x) return -1;
  else if (p1->x > p2->x) return 1;

  if(p1->y < p2->y) return -1;
  else if (p1->y > p2->y) return 1;

  return 0;
}

int compareByY(const void * a, const void * b) {
  Point * p1 = (Point *)a;
  Point * p2 = (Point *)b;
  
  if(p1->y > p2->y) return -1;
  else if (p1->y < p2->y) return 1;

  if(p1->x > p2->x) return -1;
  else if (p1->x < p2->x) return 1;

  return 0;
}

// 1200
// 1100
// 800
// 500
// 

double distance(Point * sorted_by_x, Point * sorted_by_y, int n) {
  int i, k, max_x;
  double result = 0;
  Point *max_y_points = malloc(sizeof(Point)*n);

  max_y_points[k] = sorted_by_y[k];
  max_x = sorted_by_y[k++].x;

  for(int i = 1; i < n-2; i++) {
    if(sorted_by_y[i].x > max_x) {
      max_x = sorted_by_y[i].x;
      max_y_points[k++] = sorted_by_y[i];
    }
  }

 Point A, B, C;
  int j = 0;
  for(i = 0; i < k; i++) {
    A = max_y_points[i];

    for(;j < n; j++) {
      if(A.x == sorted_by_x[j].x) {
        B = sorted_by_x[j+1];
        break;
      }
    }

    C = max_y_points[i+1];
    int dy = B.y - A.y;

    int dyPow = pow(dy, 2);
    int dxPow = pow(B.x - A.x, 2);
    double hPow = dyPow + dxPow;

    double tetha = dy / sqrt(hPow);

    int dyAC = A.y - C.y;
    double h = dyAC / tetha;

    result += fabs(h);
  }

  return result;
}

int main() {
  int times, i, j, n_points;
  scanf("%d", &times);

  for (i = 0; i < times; i++) {
    scanf("%d", &n_points);

    Point * sorted_by_x = malloc(n_points * sizeof(Point));
    Point * sorted_by_y = malloc(n_points * sizeof(Point));
    for (j = 0; j < n_points; j++) {
      scanf("%d %d", &sorted_by_x[j].x, &sorted_by_x[j].y);
      sorted_by_y[j].x = sorted_by_x[j].x;
      sorted_by_y[j].y = sorted_by_x[j].y;
    }

    qsort(sorted_by_x, n_points, sizeof(Point), compareByX);
    qsort(sorted_by_y, n_points, sizeof(Point), compareByY);

    double d = distance(sorted_by_x, sorted_by_y, n_points);
    printf("%.2lf\n", d);

    free(sorted_by_x);
    free(sorted_by_y);
  }


  return 0;
}
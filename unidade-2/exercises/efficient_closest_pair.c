#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct {
  double x;
  double y;
} Point;

void print_vector(Point * points, int length) {
  for (int i = 0; i < length; i++) printf("(%lf, %lf)\n", points[i].x, points[i].y);
  printf("\n");
}

void copy(Point * X, Point * Y, int start_x, int end_x, int start_y) {
  int i;
  for (i = start_x; i <= end_x; i++) Y[start_y++] = X[i];
}

double brute_force_closest_pair(Point * P, int n) {
  int i, j;
  double d = INFINITY;

  for(i = 0; i < n - 1; i++)
    for(j = i + 1; j < n; j++) {
      double current_distance = pow(P[i].x - P[j].x, 2) + pow(P[i].y - P[j].y, 2);
      d = fmin(current_distance, d);
    }

  return d;
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
  
  if(p1->y < p2->y) return -1;
  else if (p1->y > p2->y) return 1;

  if(p1->x < p2->x) return -1;
  else if (p1->x > p2->x) return 1;

  return 0;
}

double efficient_closest_pair(Point * P, Point * Q, int n) {
  if (n <= 3) return brute_force_closest_pair(P, n);
  int i, k, half_l, half_r;
  int num = 0, current_index_ql = 0, current_index_qr = 0;;

  half_l = n / 2;
  half_r = n - half_l;
  Point Pl[half_l];
  Point Pr[half_r];
  Point Ql[half_l];
  Point Qr[half_r];
  
  memcpy(Pl, P, sizeof(Point) * half_l);  
  memcpy(Pr, &P[half_l], sizeof(Point) * half_r); 

  Point middle_point = P[half_l - 1];
  for(i = 0; i < n; i++) {
    if(Q[i].x <= middle_point.x && current_index_ql < half_l) {
      Ql[current_index_ql++] = Q[i];
    } else {
      Qr[current_index_qr++] = Q[i];
    }
  }

  double dl = efficient_closest_pair(Pl, Ql, half_l);
  double dr = efficient_closest_pair(Pr, Qr, half_r);
  double d = fmin(dl, dr);

  Point * S = NULL;
  for (i = 0; i < n; i++) {
    if (pow(Q[i].x - middle_point.x, 2) < d) {
      S = (Point *)realloc(S, (num + 1) * sizeof(Point));
      S[num++] = Q[i];
    }
  }

  k = 0;
  double dminsq = d;
  for (i = 0; i < num - 1; i++) {
    k = i + 1;
    double dx = pow(S[k].x - S[i].x, 2);
    double dy = pow(S[k].y - S[i].y, 2);

    while (k < num && (dy < dminsq)) {
      dminsq = fmin(dx + dy, dminsq);
      k++;
    }
  } 

  free(S);
  return dminsq;
}

int main() {
  int n;
  scanf("%d", &n);
  while (n != 0) {
    int i;
    Point * points = (Point *)malloc(n * sizeof(Point));

    Point point;
    for (i = 0; i < n; i++) {
      scanf("%lf %lf", &point.x, &point.y);
      points[i] = point;
    }

    int length = i;

    Point * points_sorted_by_y = (Point *)malloc(i * sizeof(Point));
    qsort(points, i, sizeof(Point), compareByX);
    copy(points, points_sorted_by_y, 0, i - 1, 0);
    qsort(points_sorted_by_y, i, sizeof(Point), compareByY);

    double result = sqrt(efficient_closest_pair(points, points_sorted_by_y, length));
    double limite = 10000;
    if (result >= limite) {
      printf("INFINITY\n");
    } else {
      printf("%.4f\n", result);
    }

    free(points);
    free(points_sorted_by_y);
    scanf("%d", &n);
  }

  return 0;
}
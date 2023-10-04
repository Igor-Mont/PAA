#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct {
  double x, y;
  int type;
} Point;

Point points_final[100];
int current_index = 0;

void print_vector(Point * points, int length) {
  for (int i = 0; i < length; i++) printf("(%lf, %lf) - Type (%d)\n", points[i].x, points[i].y, points[i].type);
  printf("\n");
}

double brute_force_closest_pair(Point * P, int n) {
  int i, j;
  double d = INFINITY;

  // printf("Brute force POINTS\n");
  // print_vector(P, n);

  for(i = 0; i < n - 1; i++)
    for(j = i + 1; j < n; j++) {
      if (P[i].type != P[j].type) {
      double dx = pow(P[j].x - P[i].x, 2);
      double dy = pow(P[j].y - P[i].y, 2);
      // printf("S[k]: (%lf %lf) Type (%d)\n", S[k].x, S[k].y, S[k].type);
      // printf("S[i]: (%lf %lf) Type (%d)\n", S[i].x, S[i].y, S[i].type);

      if(dx + dy <= d) {
        points_final[0] = P[j];
        points_final[1] = P[i]; 
        d = dx + dy;
      }
      double current_distance = pow(P[i].x - P[j].x, 2) + pow(P[i].y - P[j].y, 2);
      d = fmin(current_distance, d);
    };
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
  int num = 0, current_index_ql = 0, current_index_qr = 0;

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

    if (S[i].type != S[k].type) {
      double dx = pow(S[k].x - S[i].x, 2);
      double dy = pow(S[k].y - S[i].y, 2);
      // printf("S[k]: (%lf %lf) Type (%d)\n", S[k].x, S[k].y, S[k].type);
      // printf("S[i]: (%lf %lf) Type (%d)\n", S[i].x, S[i].y, S[i].type);

      while (k < num && (dy < dminsq)) {
        // printf("dminsq: %lf | dx + dy: %lf\n", dminsq, dx + dy);
        if(dx + dy <= dminsq) {
          points_final[current_index++] = S[k];
          points_final[current_index++] = S[i]; 
          dminsq = dx + dy;
        }
        k++;
      }
    };
    
  } 

  free(S);
  return dminsq;
}

void copy(Point * X, Point * Y, int start_x, int end_x, int start_y) {
  int i;
  for (i = start_x; i <= end_x; i++) Y[start_y++] = X[i];
}

bool point_first(Point * points, Point p1, Point p2, int n) {
  int i, j;
  for (i = 0; i < n; i++) if (points[i].x == p1.x && points[i].y == p1.y) break;
  for (j = 0; j < n; j++) if (points[j].x == p2.x && points[j].y == p2.y) break;

  return i < j;
}

int main() {
  long n;
  int i, type;

  scanf("%ld", &n);

  Point points[n];
  Point points_sorted_by_y[n];
  Point points_sorted_by_x[n];

  for (i = 0; i < n; i++)
    scanf("%lf %lf %d", &points[i].x, &points[i].y, &points[i].type);

  copy(points, points_sorted_by_x, 0, n - 1, 0);
  qsort(points_sorted_by_x, n, sizeof(Point), compareByX);
  copy(points, points_sorted_by_y, 0, n - 1, 0);
  qsort(points_sorted_by_y, n, sizeof(Point), compareByY);

  // print_vector(points, n);
  // print_vector(points_sorted_by_y, n);
  double result = sqrt(efficient_closest_pair(points_sorted_by_x, points_sorted_by_y, n));
  Point equal_point;
  if (result == 0) {
    for(int i = 0; i < n-1; i++) {
      if(points_sorted_by_x[i].x == points_sorted_by_x[i+1].x && points_sorted_by_x[i].y == points_sorted_by_x[i+1].y && points_sorted_by_x[i].type != points_sorted_by_x[i+1].type) {
        equal_point = points_sorted_by_x[i + 1];
        break;
      }
    }

    printf("%d %d %d %d\n", (int)equal_point.x, (int)equal_point.y, (int)equal_point.x, (int)equal_point.y);
    return 0;
  }
  // printf("Vetor final: \n");
  // print_vector(points_final, n);

  bool p1_frist = point_first(points, points_final[0], points_final[1], n);

  if(p1_frist) {
    printf("%d %d %d %d\n", (int)points_final[0].x, (int)points_final[0].y, (int)points_final[1].x, (int)points_final[1].y);
  } else {
    printf("%d %d %d %d\n", (int)points_final[1].x, (int)points_final[1].y, (int)points_final[0].x, (int)points_final[0].y);
  }

  // printf("%s\n", p1_frist ? "P1 FIRST" : "P1 SECOND");
  return 0;
}
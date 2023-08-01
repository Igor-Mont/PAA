#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
  int x;
  int y;
} Point;

void print_vector(Point * vector, int length) {
  for (int i = 0; i < length; i++) printf("%d %d | ", vector[i].x, vector[i].y);
  printf("\n");
}

void copy(Point * X, Point * Y, int start_x, int end_x, int start_y) {
  int i;
  for (i = start_x; i <= end_x; i++) Y[start_y++] = X[i];
}

void merge(Point * B, int p, Point * C, int q, Point * A, bool sort_by_x) {
  int i = 0, j = 0, k = 0;

  while (i < p && j < q) {
    if(sort_by_x) {
      if (B[i].x <= C[j].x) A[k] = B[i++];
      else A[k] = C[j++];
      k++;
    } else {
      if (B[i].y <= C[j].y) A[k] = B[i++];
      else A[k] = C[j++];
      k++;
    }
  }

  if (i == p) copy(C, A, j, q - 1, k);
  else copy(B, A, i, p - 1, k);
}

void merge_sort(Point * A, int n, bool sort_by_x) {
  if (n > 1) {
    int half = n / 2;
    Point * B = (Point *)malloc(half * sizeof(Point));
    Point * C = (Point *)malloc((n - half) * sizeof(Point));

    copy(A, B, 0, half - 1, 0);
    copy(A, C, half, n - 1, 0);
    merge_sort(B, half, sort_by_x);
    merge_sort(C, n - half, sort_by_x);
    merge(B, half, C, n - half, A, sort_by_x);

    free(B);
    free(C);
  }
}

double min(double x, double y) {
  return (x < y) ? x : y;
}

double brute_force_closest_pair(Point * P, int n) {
  int i, j;
  double d = INFINITY;

  for(i = 0; i < n - 1; i++)
    for(j = i + 1; j < n; j++) {
      double current_distance = (P[i].x - P[j].x) * (P[i].x - P[j].x) + (P[i].y - P[j].y) * (P[i].y - P[j].y);
      d = min(current_distance, d);
    }

  // Essa chamada pode gerar um erro em cascata.
  // Melhor tirar a raíz quadrada apenas no reusltado da função.
  return sqrt(d); // pode remover a raíz quadrada.
}

double efficient_closest_pair(Point * P, Point * Q, int n) {
  int i, k, num = 0;
  if (n <= 3) return brute_force_closest_pair(P, n);

  int half = n / 2;
  Point * Pl = (Point *)malloc(half * sizeof(Point));
  Point * Pr = (Point *)malloc((n - half) * sizeof(Point));
  Point * Ql = (Point *)malloc(half * sizeof(Point));
  Point * Qr = (Point *)malloc((n - half) * sizeof(Point));

  copy(P, Pl, 0, half, 0);
  copy(Q, Ql, 0, half, 0);

  // copiar os mesmos pontos para Ql ordenados por y

  copy(P, Pr, half, n - 1, 0);
  copy(Q, Qr, half, n - 1, 0);
  // copiar os mesmos pontos para Qr ordenados por y

  double dl = efficient_closest_pair(Pl, Ql, half);
  double dr = efficient_closest_pair(Pr, Qr, n - half);
  double d = min(dl, dr);
  int m = P[half - 1].x;

  Point * S = NULL;
  for (i = 0; i < n; i++) {
    if (abs(Q[i].x - m) < d) {
      S = (Point *)realloc(S, (num + 1) * sizeof(Point));
      S[num++] = Q[i];
    }
  }

  double dminsq = d * d;

  for (i = 0; i <= num - 2; i++) {
    k = i + 1;
    double dy = (S[k].y - S[i].y) * (S[k].y - S[i].y);
    while (k <= num - 1 && (dy < dminsq)) {
      double dx = (S[k].x - S[i].x) * (S[k].x - S[i].x);
      dminsq = min(dx + dy, dminsq);
      k++;
    }
  } 

  return sqrt(dminsq);
}

int main() {
  int i = 0;
  Point * points = NULL;

  Point point;
  while (scanf("%d %d", &point.x, &point.y) != EOF) {
    points = (Point *)realloc(points, (i + 1) * sizeof(Point));
    points[i++] = point;
  }

  int length = i;

  Point * points_sorted_by_y = (Point *)malloc(i * sizeof(Point));
  merge_sort(points, length, true);
  copy(points, points_sorted_by_y, 0, i - 1, 0);
  merge_sort(points_sorted_by_y, length, false);

  print_vector(points, length);
  print_vector(points_sorted_by_y, length);

  double result = efficient_closest_pair(points, points_sorted_by_y, length);
  printf("RESULTADO: %f\n", result);
  return 0;
}
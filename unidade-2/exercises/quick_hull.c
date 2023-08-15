#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

typedef struct {
  int x;
  int y;
} Point;


void print_vector(Point * points, int length) {
  for (int i = 0; i < length; i++) printf("(%d, %d) |", points[i].x, points[i].y);
  printf("\n");
}

int determinant(Point * p_min, Point * p_max, Point * p_n) {
  int dp = p_min->x * p_max->y + p_min->y * p_n->x + p_max->x * p_n->y; 
  int ds = p_max->y * p_n->x + p_min->x * p_n->y + p_min->y * p_max->x;
  printf("dp: %d | ds: %d\n", dp, ds);
  return dp - ds; 
}

void quick_hull(Point * points, int n) {
  int i;
  Point min_point;
  min_point.x = INT_MAX;
  min_point.y = INT_MAX;
  Point max_point;
  max_point.x = INT_MIN;
  max_point.y = INT_MIN;

  for (i = 0; i < n; i++) {
    if (points[i].x < min_point.x) min_point = points[i];
    else if (points[i].x  == min_point.x || points[i].y < min_point.y) min_point = points[i];
    
    if (points[i].x  > max_point.x) max_point = points[i];
    else if (points[i].x  == max_point.x || points[i].y > max_point.y) max_point = points[i];
  }

  printf("Min. point = (%d %d)\n", min_point.x, min_point.y);
  printf("Max. point = (%d %d)\n", max_point.x, max_point.y);
  printf("N. point = (%d %d)\n", points[0].x, points[0].y);

  int d = abs(determinant(&min_point, &max_point, &points[0]));
  printf("Determiannte: %d\n", d);
}

int main() {
  int i = 0;
  Point * points = NULL;

  Point min_point;
  min_point.x = INT_MAX;
  min_point.y = INT_MAX;
  Point max_point;
  max_point.x = INT_MIN;
  max_point.y = INT_MIN;

  Point point;
  while (scanf("%d %d", &point.x, &point.y) != EOF) {
    points = (Point *)realloc(points, (i + 1) * sizeof(Point));
    points[i++] = point;
  }

  int length = i;
  print_vector(points, i);
  quick_hull(points, length);
}
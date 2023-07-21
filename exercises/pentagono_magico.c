#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
  LEFT,
  RIGHT
} Direction;

typedef struct {
  int id;
  int x;
  int y;
} Point;


void line_equation(int * a, int * b, int * c, Point point1, Point point2) {
  *a = point2.y - point1.y;
  *b = point1.x - point2.x;
  *c = point1.x * point2.y - point1.y * point2.x;
}

bool is_a_convex_hull(Point * points, int n_points, Point point1, Point point2) {
  int a, b, c, i;
  Direction main_direction;

  line_equation(&a, &b, &c, point1, point2);

  for (i = 0; i < n_points; i++) {
    Point point = points[i];
    if(point.id != point1.id && point.id != point2.id) continue;
  
    int result = a * point.x + b * point.y;
    Direction current_direction = result < c ? LEFT : RIGHT;

    if (i == 0) {
      printf("i = %d\n", i);
      main_direction = current_direction;
      continue;
    }

    if (current_direction != main_direction) return false;
  }

  return true;
}

int main() {
  int n_points, i, j;

  scanf("%d", &n_points);

  Point * points = (Point *)malloc(n_points * sizeof(Point));
  Point convex_hull_list[100];
  int counter_convex_hull_list = 0;

  for (i = 0; i < n_points; i++) {
    int x, y;
    scanf("%d %d", &x, &y);

    Point point;
    point.id = i;
    point.x = x;
    point.y = y;
    points[i] = point;
  }


  for (i = 0; i < n_points; i++) {
    for (j = 0; j < n_points; j++) {
      if(i == j) continue;
      bool is_convex_hull = is_a_convex_hull(points, n_points, points[i], points[j]);

      if (is_convex_hull) {
        convex_hull_list[counter_convex_hull_list++] = points[i];
        convex_hull_list[counter_convex_hull_list++] = points[j];
        printf("EH %d\n", i);
      }
    }
  }

  for (i = 0; i < counter_convex_hull_list; i++) {
    printf("PONTO SELECIONADO (%d, %d)\n", convex_hull_list[i].x, convex_hull_list[i].y);
  }

  return 0;
}
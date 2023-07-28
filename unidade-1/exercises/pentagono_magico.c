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

typedef struct {
  int x1;
  int y1;
  int x2;
  int y2;
} Segment;


void line_equation(int * a, int * b, int * c, Point point1, Point point2) {
  *a = point2.y - point1.y;
  *b = point1.x - point2.x;
  *c = point1.x * point2.y - point1.y * point2.x;
}

Segment * sort_list_segments(Segment * segments, int n_segments) {
  Segment * sorted_segments = (Segment *)malloc(n_segments * sizeof(Segment));

  int current_index = 0;
  sorted_segments[current_index] = segments[current_index];
  int i = 1;
  while (current_index < n_segments - 1) { 
    Segment current_segment = sorted_segments[current_index];
    Segment segment = segments[i];
    bool equal_segments = current_segment.x2 == segment.x1 && current_segment.y2 == segment.y1;
    if(equal_segments) {
      sorted_segments[++current_index] = segment;
    }
    
    bool is_last_index = i == n_segments - 1; 
    if (is_last_index) {
      i = 1;
    } else {
      i++;
    }
  }

  return sorted_segments;
}

bool is_a_convex_hull(Point * points, int n_points, Point point1, Point point2) {
  int a, b, c, i;
  int main_direction;

  line_equation(&a, &b, &c, point1, point2);

  for (i = 0; i < n_points; i++) {
    printf("i = %d\n", i);
    Point point = points[i];
  
    int result = a * point.x + b * point.y;
    int current_direction = result < c ? 1 : 0;

    if (i == 0) {
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
  Segment convex_hull_list[50];
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
      printf("Iteracao %d - %s \n", i, is_a_convex_hull ? "sim" : "nao");
      if (is_convex_hull) {
        Segment segment;
        segment.x1 = points[i].x;
        segment.y1 = points[i].y;
        segment.x2 = points[j].x;
        segment.y2 = points[j].y;
        convex_hull_list[counter_convex_hull_list++] = segment;
      }
    }
  }
  Segment * sorted_segments = sort_list_segments(convex_hull_list, counter_convex_hull_list);

  printf("SEGMENTOS\n");
  for (i = 0; i < counter_convex_hull_list; i++) {
    printf("[(%d, %d), (%d, %d)]\n", convex_hull_list[i].x1, convex_hull_list[i].y1, convex_hull_list[i].x2, convex_hull_list[i].y2);
  }

  printf("SEGMENTOS ORDENADOS\n");
  for (int i = 0; i < counter_convex_hull_list; i++) {
    printf("[(%d, %d), (%d, %d)]\n", sorted_segments[i].x1, sorted_segments[i].y1, sorted_segments[i].x2, sorted_segments[i].y2);
  }

  return 0;
}
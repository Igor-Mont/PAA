#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10000000

typedef struct {
  long long int x, y;
} Point;

struct Stack {
  Point items[MAX_SIZE];
  long long top;
};

void print(Point *P, int n);

Point pop(struct Stack *stack);

void swap(Point *p1, Point *p2);

int calculateNumConvexPoints(Point points[], int n);

void initialize(struct Stack *stack) { stack->top = 0; }

void push(struct Stack *stack, Point item);

Point top(struct Stack *stack) { return stack->items[stack->top-1]; }

Point nextToTop(struct Stack *stack);

int compare(const void *vp1, const void *vp2);

void convexHull(Point points[], long n, long distanciaMax);

long long int distSq(Point p1, Point p2);

int orientation(Point p, Point q, Point r);

struct Stack stack;

Point p0;

int main() {

  long long n, distanciaMax;
  scanf("%lld %lld", &n, &distanciaMax);
  Point points[n];
  for (long long i = 0; i < n; i++) {
    scanf("%lld %lld", &points[i].x, &points[i].y);
  }

  convexHull(points, n, distanciaMax);

  /* while (!empty(&stack)) {
    Point p = top(&stack);
    pop(&stack);
  } */

  long double dist;
  long long naves = 0;
  for (long long i = 0; i < stack.top-1; i++) {
    dist = sqrt(distSq(stack.items[i], stack.items[(i + 1)]));
    while (dist > distanciaMax) {
      dist -= distanciaMax;
      naves++;
    }
  }

  dist = sqrt(distSq(stack.items[0], stack.items[(stack.top-1)]));
  printf("%lld %lld, %lld %lld\n", stack.items[0].x, stack.items[0].y, stack.items[stack.top-1].x, stack.items[stack.top-1].y);
  printf("%lld\n", naves);
  while (dist > distanciaMax) {
    dist -= distanciaMax;
    naves++;
  }
  printf("%lld\n", naves);
  printf("%lld\n", stack.top);


  printf("%lld", stack.top + naves);
  return 0;
}

void convexHull(Point points[], long n, long distanciaMax) {

  long long int ymin = points[0].y;
  long long int min = 0;

  for (long i = 1; i < n; i++) {
    long long int y = points[i].y;

    if ((y < ymin) || (ymin == y && points[i].x < points[min].x)){
      ymin = points[i].y;
      min = i;
    }
  }

  swap(&points[0], &points[min]);

  p0 = points[0];
  qsort(&points[1], n - 1, sizeof(Point), compare);

  long long numConvexPoints = calculateNumConvexPoints(points, n);

  if (numConvexPoints < 3)
    return;

  initialize(&stack);
  push(&stack, points[0]);
  push(&stack, points[1]);
  push(&stack, points[2]);

  for (long long i = 3; i < numConvexPoints; i++) {

    while ((stack.top > 0 && orientation(nextToTop(&stack), top(&stack), points[i]) != 2)) {
      pop(&stack);
    }

    push(&stack, points[i]);
  }
}

void print(Point *P, int n) {
  for (int i = 0; i < n; i++) {
    printf("(%lld %lld)\n", P[i].x, P[i].y);
  }
}

void push(struct Stack *stack, Point item) {
  stack->items[stack->top++] = item;
}

Point pop(struct Stack *stack) {
  Point item = stack->items[--stack->top];
  return item;
}

Point nextToTop(struct Stack *stack) {
  Point p = top(stack);
  pop(stack);
  Point res = top(stack);
  push(stack, p);
  return res;
}

long long int distSq(Point p1, Point p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void swap(Point *p1, Point *p2) {
  Point temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}

int orientation(Point p, Point q, Point r) {
  long long int result = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

  if (result == 0)
    return 0;
  return (result > 0) ? 1 : 2;
}

int compare(const void *vp1, const void *vp2) {
  Point *p1 = (Point *)vp1;
  Point *p2 = (Point *)vp2;

  int o = orientation(p0, *p1, *p2);
  if (o == 0)
    return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

  return (o == 2) ? -1 : 1;
}

int calculateNumConvexPoints(Point points[], int n) {
  int numConvexPoints = 1;

  for (int i = 1; i < n; i++) {
    while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
      i++;

    points[numConvexPoints] = points[i];
    numConvexPoints++;
  }

  return numConvexPoints;
}
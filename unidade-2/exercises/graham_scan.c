#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 1000

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
    Point data[MAX_SIZE];
    int top;
} Stack;

Point p0;

void initialize(Stack *stack) {
    stack->top = -1; // Pilha vazia
}

// Função para verificar se a pilha está vazia
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Função para verificar se a pilha está cheia
int isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

// Função para empilhar um elemento na pilha
void push(Stack *stack, Point value) {
    if (isFull(stack)) {
        printf("Erro: A pilha está cheia.\n");
        return;
    }
    stack->top++;
    stack->data[stack->top] = value;
}

// Função para desempilhar um elemento da pilha
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Erro: A pilha está vazia.\n");
        return -1; // Valor inválido para indicar erro
    }
    stack->top--;
    return 1;
}

// Função para obter o elemento no topo da pilha
Point top(Stack *stack) {
    return stack->data[stack->top];
}

void print_vector(Point * points, int length) {
  for (int i = 0; i < length; i++) printf("(%d, %d) |", points[i].x, points[i].y);
  printf("\n");
}

int distSq(Point p1, Point p2){
  return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}
 
int orientation(Point p, Point q, Point r) {
  int value = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

  if (value == 0) return 0;   // collinear
  return (value > 0) ? 1 : 2; // clock or counterclock wise
}
 
int compare(const void *p1, const void *p2) {
  Point * p1_aux = (Point *)p1;
  Point * p2_aux = (Point *)p2;

  int o = orientation(p0, *p1_aux, *p2_aux);
  if (o == 0) 
    return (distSq(p0, *p2_aux) >= distSq(p0, *p1_aux)) ? -1 : 1;

  return (o == 2) ? -1 : 1;
}

void swap(Point * p1, Point  * p2){
  Point * temp = p1;
  p1 = p2;
  p2 = temp;
}

Point nextToTop (Stack * stack) {
    Point p = top(stack);
    pop(stack);
    Point res = top(stack);
    push(stack, p);
    return res;
}

void graham_scan(Point * points, int n) {
  int i, min;
  Point p_min = points[0];
  for(i = 1; i < n; i++) {
    bool is_min_y = points[i].y < p_min.y; 
    bool is_equal_y = points[i].y == p_min.y; 
    bool is_leftmost_x = points[i].x < p_min.x;
    if (is_min_y || (is_equal_y && is_leftmost_x)) {
      p_min = points[i];
      min = i;
    }
  }

  swap(&points[0], &points[min]);
  p0 = points[0];

  qsort(&points[1], n - 1, sizeof(Point), compare);

  int m = 1;
  for (int i = 1; i < n; i++) {
    bool is_coolinear = orientation(p0, points[i], points[i+1]) == 0;
      while (i < n - 1 && is_coolinear) i++;
      points[m] = points[i];
      m++;  
  }

  if (m < 3) {
    printf("Convex hull is not possible.");
    return;
  };

  Stack stack;
  initialize(&stack);
  push(&stack, points[0]);
  push(&stack, points[1]);
  push(&stack, points[2]);

  for (int i = 3; i < m; i++) {
    while (stack.top + 1 > 1 && orientation(nextToTop(&stack), (Point)top(&stack), points[i]) != 2)
      pop(&stack);
    push(&stack, points[i]);
  }

  while (!isEmpty(&stack)) {
    Point p = top(&stack);
    printf("(%d, %d) ", p.x, p.y);
    pop(&stack);
  }

}

int main() {
  // int i = 0;
  // Point * points = NULL;

  // Point point;
  // while (scanf("%d %d", &point.x, &point.y) != EOF) {
  //   points = (Point *)realloc(points, (i + 1) * sizeof(Point));
  //   points[i++] = point;
  // }

  // int length = i;
  // print_vector(points, i);
  Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                      {0, 0}, {1, 2}, {3, 1}, {3, 3}};
  int n = sizeof(points)/sizeof(points[0]);
  graham_scan(points, n);
  return 0;
}
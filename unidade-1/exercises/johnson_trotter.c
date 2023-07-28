#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
  LEFT,
  RIGHT
} Direction;

typedef struct {
  int num;
  int index;
  Direction direction;
} JohnsonTrotterElement;

bool has_largest_mobile_element(JohnsonTrotterElement * permutation, JohnsonTrotterElement * larguest_mobile_element, int * n) {
  larguest_mobile_element->num = -1;
  bool has_largest = false; 

  for (int i = 0; i < *n; i++) {
    if(permutation[i].direction == LEFT) {
      if(i == 0) continue;
      if(permutation[i].num > permutation[i - 1].num) {
        if(permutation[i].num > larguest_mobile_element->num) {
          has_largest = true;
          * larguest_mobile_element = permutation[i]; 
        }
      }
    }

    if(permutation[i].direction == RIGHT) {
      if(i == (*n - 1)) continue;

      if(permutation[i].num > permutation[i + 1].num) {
        if(permutation[i].num > larguest_mobile_element->num) {
          has_largest = true;
          * larguest_mobile_element = permutation[i]; 
        }
      }
    }
  }

  return has_largest;
}

int fatorial(int n) {
  if (n == 0 || n == 1)
    return 1;

  return n * fatorial(n - 1);
}

JohnsonTrotterElement * swap(JohnsonTrotterElement * permutation, JohnsonTrotterElement * k, int * n) {
  JohnsonTrotterElement * permutation_copy = malloc((*n) * sizeof(JohnsonTrotterElement));

  for (int i = 0; i < *n; i++) {
    permutation_copy[i] = permutation[i];
  }

  Direction direction = permutation_copy[k->index].direction; 

  if(direction == LEFT) {
    // [1, 2, 3, 4, 5] ------> INDEX DO 5 = 3 | INDEX DO 4 = 4
    printf("BEFORE: K->index: %d | K->index - 1: %d\n", k->index, k->index -1);
    permutation_copy[k->index].index--;
    permutation_copy[k->index - 1].index++;

    // index aux = 3 | index 3 -> index 2 |
    printf("AFTER: K->index: %d | K->index - 1: %d\n", k->index, k->index -1);
    JohnsonTrotterElement aux = permutation_copy[k->index];
    permutation_copy[k->index] = permutation_copy[k->index - 1];
    permutation_copy[k->index - 1] = aux;
  } else {
    permutation_copy[k->index].index++;
    permutation_copy[k->index + 1].index--;

    JohnsonTrotterElement aux = permutation_copy[k->index];
    permutation_copy[k->index] = permutation_copy[k->index + 1];
    permutation_copy[k->index + 1] = aux;
  }

  return permutation_copy;
}

void reverse_direction_if_above_k(JohnsonTrotterElement * permutation, JohnsonTrotterElement * k, int * n) {
  for (int i = 0; i < *n; i++) {
    if(permutation[i].num == k->num) continue;

    if(permutation[i].num > k->num) {
      permutation[i].direction = permutation[i].direction == LEFT ? RIGHT : LEFT;
    }
  }
}

JohnsonTrotterElement ** johnsonTrotter(int * n) {
  int nPermutations = fatorial(*n);
  printf("Número de permutações: %d\n", nPermutations);
  
  JohnsonTrotterElement ** permutations = malloc(nPermutations * sizeof(JohnsonTrotterElement *));

  for (int i = 0; i < nPermutations; i++) {
    permutations[i] = malloc((*n) * sizeof(JohnsonTrotterElement));
  }

  int counter = 0;
  for (int i = 1; i <= *n; i++) {
    JohnsonTrotterElement element;
    element.direction = LEFT;
    element.num = i;
    element.index = i - 1;
    permutations[counter][i-1] = element;
  }

  JohnsonTrotterElement * k = malloc(sizeof(JohnsonTrotterElement));
  while(has_largest_mobile_element(permutations[counter], k, n)) {
    JohnsonTrotterElement * permutation = swap(permutations[counter], k, n);
    reverse_direction_if_above_k(permutation, k, n);

    permutations[++counter] = permutation;
  }

  return permutations;
}

int main() {
  int n;
  scanf("%d", &n);

  JohnsonTrotterElement ** permutations = johnsonTrotter(&n);

  for (int i = 0; i < fatorial(n); i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", permutations[i][j].num);
    }
    printf("\n");
  }

  return 0;
}
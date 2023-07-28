#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  int i;
  int j;
} Indexes;


int fatorial(int n) {
  if (n == 0 || n == 1) return 1;
  return n * fatorial(n-1);
}

Indexes find_i_j(int * permutation, int length) {
  int i = length - 1;
  while (i > 0 && permutation[i - 1] >= permutation[i])
    i--;

  int j = length - 1;
  while (permutation[j] <= permutation[i - 1])
    j--;

  Indexes indexes;
  indexes.i = i - 1;
  indexes.j = j;
  return indexes;
}

bool has_two_consecutive_elements_in_increasing_order(int * permutation, int length) {
  for (int i = 0; i < length - 1; i++) 
    if(permutation[i] < permutation[i + 1]) return true;
  
  return false;
} 

int * swap(int * permutation, int n, int i, int j) {
  int * permutation_copy = (int *)malloc(n * sizeof(int));
  for (int k = 0; k < n; k++)
    permutation_copy[k] = permutation[k];

  int aux = permutation_copy[i];
  permutation_copy[i] = permutation_copy[j];
  permutation_copy[j] = aux;

  return permutation_copy;
}

void reverse(int * permutation, int i, int n) {
  while (i < n) {
    int aux = permutation[i];
    permutation[i] = permutation[n];
    permutation[n] = aux;
    i++;
    n--;
  }
}

int ** lexicographic_permute(int n) {
  int nPermutations = fatorial(n);
  printf("Número de permutações: %d\n", nPermutations);
  int ** permutations = (int **)malloc(nPermutations * sizeof(int *));

  for (int i = 0; i < nPermutations; i++)
    permutations[i] = (int *)malloc(n * sizeof(int));

  int counter = 0;
  for (int i = 1; i <= n; i++)
    permutations[counter][i-1] = i;

  while (has_two_consecutive_elements_in_increasing_order(permutations[counter], n)) {
    int * permutation = permutations[counter];
    Indexes indexes = find_i_j(permutation, n);
    int * newPermutation = swap(permutation, n, indexes.i, indexes.j);
    reverse(newPermutation, indexes.i + 1, n - 1);
    permutations[counter + 1] = newPermutation;
    counter++;
  }

  return permutations;
}

int main() {
  int n;
  scanf("%d", &n);
  
  int nPermutations = fatorial(n);
  int ** permutations = lexicographic_permute(n);

  printf("\n");
  for (int i = 0; i < nPermutations; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", permutations[i][j]);
    }
    printf("\n");
  }
    
    
  return 0;
}
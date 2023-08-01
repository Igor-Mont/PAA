#include <stdio.h>
#include <stdlib.h>

void print_vector(int vector[], int length) {
  for (int i = 0; i < length; i++) printf("%d ", vector[i]);
  printf("\n");
}

void copy(int * X, int * Y, int start_x, int end_x, int start_y) {
  int i;
  for (i = start_x; i <= end_x; i++) Y[start_y++] = X[i];
}

void merge(int * B, int p, int * C, int q, int * A) {
  int i = 0, j = 0, k = 0;

  while (i < p && j < q) {
    if (B[i] <= C[j]) A[k] = B[i++];
    else A[k] = C[j++];
    k++;
  }

  if (i == p) copy(C, A, j, q - 1, k);
  else copy(B, A, i, p - 1, k);
}

void merge_sort(int * A, int n) {
  if (n > 1) {
    int half = n / 2;
    int * B = (int *)malloc(half * sizeof(int));
    int * C = (int *)malloc((n - half) * sizeof(int));

    copy(A, B, 0, half - 1, 0);
    copy(A, C, half, n - 1, 0);
    merge_sort(B, half);
    merge_sort(C, n - half);
    merge(B, half, C, n - half, A);

    free(B);
    free(C);
  }
}

int main() {
  int A[] = {4, 7, 2, 6, 4, 1, 8, 3, 2};
  int length = sizeof(A) / sizeof(A[0]);

  merge_sort(A, length);
  print_vector(A, length);

  // free(A);
  return 0;
}
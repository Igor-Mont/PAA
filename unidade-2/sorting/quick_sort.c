#include <stdio.h>
#include <stdlib.h>

void print_vector(int vector[], int length) {
  for (int i = 0; i < length; i++) printf("%d ", vector[i]);
  printf("\n");
}

void swap(int * a, int * b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int hoare_partition(int * A, int l, int r) {
  int i = l - 1, j = r + 1, p = A[l];
  printf("i: %d | j: %d\n", i, j);

  while(1) {
    do {
      i++;
    } while (A[i] < p);

    do {
      j--;
    } while (A[j] > p);

    if(i >= j) return j;
    swap(&A[i], &A[j]);
  }
}

void quick_sort(int * A, int l, int r) {
  int s;
  if (l < r) {
    s = hoare_partition(A, l, r);
    quick_sort(A, l, s);
    quick_sort(A, s + 1, r);
  }
}

int main() {
  int A[] = {4, 7, 2, 6, 4, 1, 8, 3, 2, 3, 2, 1, 2, 3, 6, 7, 8, 9,9,2};
  int length = sizeof(A) / sizeof(A[0]);

  quick_sort(A, 0, length - 1);

  print_vector(A, length);

  return 0;
}
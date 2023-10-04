#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
 
#define SIZE 256

long int max(long int a, long int b) {
  return a > b ? a : b;
}
 
void table(char * P, long int size, long int badchar[SIZE]) {
  long int i;
  for (i = 0; i < SIZE; i++)
    badchar[i] = -1;

  for (i = 0; i < size; i++)
    badchar[(long int) P[i]] = i;
}

int is_lower_one(int x) {
  return x < 1;
}
 
int boyer_moore(char * T, char * P, long int n, long int m) {
  long int badchar[SIZE];

  table(P, m, badchar);

  long int index = 0;
  while (index <= (n - m)) {
    long int j = m - 1;
    while(j >= 0 && (P[j] == T[index+j] || P[j] == '_')) {
      j--;
    }

    if (j < 0) {
      return index;
    } else {
      long int a = j - badchar[(long int)T[index + j]];
      long int b = 1;
      if (is_lower_one(a)) b = 1 - a;
      index += max(b, 1);
    }
  }

  return -1;
}
 
int main() {
  long int sizeT, sizeP;
  scanf("%ld %ld", &sizeT, &sizeP);

  char T[sizeT];
  char P[sizeP];
  scanf("%s", T);
  scanf("%s", P);

  long int index = boyer_moore(T, P, sizeT, sizeP);
  if (index == -1) {
    printf("Nao descendente");
  } else {
    printf("%ld\n", index);
  }
  return 0;
}
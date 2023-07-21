#include <stdio.h>
#include <stdlib.h>

int * gerar_intervalo(int n, int m, int * tamanho_intervalo, int * intervalos, int tamanho_intervalos) {
  *tamanho_intervalo += (m - n + 1);
  int * intervalo = (int *)malloc(*tamanho_intervalo * sizeof(int));

  int index_atual = 0;
  for(int i = n; i <= m; i++)
    intervalo[index_atual++] = i;

  return intervalo;
}

void concat(int * intervalos, int tamanho_intervalos, int * intervalo, int tamanho_interavalo) {
  int counter = 0;
  for (int i = tamanho_intervalos; i < tamanho_intervalos + tamanho_interavalo; i++)
    intervalos[i] = intervalo[counter++];
}

void selectionSort(int * A, int n) {
  int min;
  for (int i = 0; i <= n - 2; i++) {
    min = i;
    for (int j = i + 1; j <= n - 1; j++) {
      if (A[j] < A[min]) min = j;
    }
    int aux = A[min];
    A[min] = A[i];
    A[i] = aux;
  }
}

int main() {
  int n_intervalos, counter = 0;

  while (scanf("%d", &n_intervalos) != EOF) {
    int tamanho_intervalos = 0;
    int intervalos[10000];

    for(int i = 0; i < n_intervalos; i++) {
      int tamanho_intervalo = 0, n, m;
      scanf("%d %d", &n, &m);
      int * intervalo = gerar_intervalo(n, m, &tamanho_intervalo, intervalos, tamanho_intervalos);
      concat(intervalos, tamanho_intervalos, intervalo, tamanho_intervalo);
      free(intervalo);
      tamanho_intervalos += tamanho_intervalo;
    }

    int num;
    scanf("%d", &num);
    selectionSort(intervalos, tamanho_intervalos);

    int start = -1;
    int end = -1;
    for(int i = 0; i < tamanho_intervalos; i++) {
      if(intervalos[i] == num) {
        if(start == -1) {
          start = i; 
        }
        end = i;
      }
    }
    
    printf("\nSTART: %d | END: %d", start, end);
  }
  
  return 0;
}
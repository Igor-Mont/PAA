#include <stdio.h>
#include <stdlib.h>

// gcc spaceuber.c -o ./out/spaceuber
// ./out/spaceuber.exe < ./in/spaceuber.txt

typedef struct {
    int origem;
    int destino;
} Viagem;

int compare(const void *a, const void *b) {
  return ((Viagem *)a)->destino - ((Viagem *)b)->destino;
}

int main() {
    int n_viagens, i, j, max_viagens = 0;
    scanf("%d", &n_viagens);

    

    Viagem * viagens = malloc(n_viagens * sizeof(Viagem));
    for (int i = 0; i < n_viagens; i++) scanf("%d %d", &viagens[i].origem, &viagens[i].destino);

    qsort(viagens, n_viagens, sizeof(Viagem), compare);

    int * pd = malloc((n_viagens + 1) * sizeof(int));
    pd[0] = 0;

    for (i = 1; i <= n_viagens; i++) {
      pd[i] = 1;
      for (j = 1; j < i; j++)
        if (viagens[i - 1].origem >= viagens[j - 1].destino && pd[j] + 1 > pd[i]) {
          pd[i] = pd[j] + 1;
        }
    }

    for (i = 1; i <= n_viagens; i++)
      if (pd[i] > max_viagens) max_viagens = pd[i];

    printf("%d\n", max_viagens);

    free(viagens);
    free(pd);

    return 0;
}
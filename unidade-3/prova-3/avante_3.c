#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_M 10000

// gcc avante_3.c -o ./out/avante_3
// ./out/avante_3.exe < ./in/avante_3.txt

int custo_da_mudanca_de_rota(char via_original, char via_nova) {
  if (via_original == via_nova) {
    return 1;
  } else if (via_original == 'P' && via_nova == '#') {
    return 2;
  } else if (via_original == '#' && via_nova == 'P') {
    return 2;
  } else if (via_original == via_nova == '#') {
    return -1;
  } else if (via_original == 'P' && via_nova == 'P') {
    return 1;
  } else if (via_original == '#' && via_nova == '#') {
    return -1;
  } else {
    return 3;
  }
}

int main() {
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);

  char rota_original[MAX_N], rota_nova[MAX_M];
  scanf("%s %s", rota_original, rota_nova);

  int custo_acumulado[MAX_M];
  custo_acumulado[0] = custo_da_mudanca_de_rota(rota_original[0], rota_nova[0]);

  for (int i = 1; i < m; i++) {
    int custo = custo_da_mudanca_de_rota(rota_original[i], rota_nova[i]);
    if (custo == -1) {
      custo_acumulado[i] = custo_acumulado[i - 1];
    } else {
      custo_acumulado[i] = custo_acumulado[i - 1] + custo;
    }
  }

  if (custo_acumulado[m - 1] <= k) {
    printf("Lucro: %d. A caminho!\n", k - custo_acumulado[m - 1]);
  } else {
    printf("Carona inviavel, favor solicitar a outra nave.\n");
  }

  return 0;
}

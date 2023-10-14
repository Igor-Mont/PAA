#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// gcc espaço_loja.c -o ./out/espaço_loja
// ./out/espaço_loja.exe < ./in/espaço_loja.txt

bool compativel_com_itens_escolhidos(int incompatibilidades[][2], int * escolhidos, int indice_item, int M){
  bool eh_compativel = true;

  for (int i = 0; i < M; i++) {
    if (incompatibilidades[i][0] == indice_item + 1 && escolhidos[incompatibilidades[i][1] - 1] == 1) {
      eh_compativel = false;
      break;
    }
    if (incompatibilidades[i][1] == indice_item + 1 && escolhidos[incompatibilidades[i][0] - 1] == 1) {
      eh_compativel = false;
      break;
    }
  }

  return eh_compativel;
}

bool possivel_adicionar(bool eh_compativel, int peso_atual, int itens[][2], int indice_item, int D) {
  return eh_compativel && peso_atual + itens[indice_item][1] <= D;
}

int maximizar(int N, int D, int itens[][2], int M, int incompatibilidades[][2], int indice_item, int valor_atual, int peso_atual, int escolhidos[]) {
  if (indice_item == N) return valor_atual;

  bool eh_compativel = compativel_com_itens_escolhidos(incompatibilidades, escolhidos, indice_item, M);

  int valor_maximo = maximizar(N, D, itens, M, incompatibilidades, indice_item + 1, valor_atual, peso_atual, escolhidos);

  if (possivel_adicionar(eh_compativel, peso_atual, itens, indice_item, D)) {
    escolhidos[indice_item] = 1;
    int valor_com_item = maximizar(N, D, itens, M, incompatibilidades, indice_item + 1, valor_atual + itens[indice_item][0], peso_atual + itens[indice_item][1], escolhidos);
    escolhidos[indice_item] = 0;
    valor_maximo = (valor_com_item > valor_maximo) ? valor_com_item : valor_maximo;
  }

  return valor_maximo;
}

int main() {
  if(feof(stdin)) return 0;

  int N, D;
  scanf("%d %d", &N, &D);

  int itens[N][2];
  for (int i = 0; i < N; i++)
    scanf("%d %d", &itens[i][0], &itens[i][1]);

  int M;
  scanf("%d", &M);
  int incompatibilidades[M][2];
  for (int i = 0; i < M; i++)
    scanf("%d %d", &incompatibilidades[i][0], &incompatibilidades[i][1]);

  int * escolhidos = (int *)calloc(N, sizeof(int));

  int resultado = maximizar(N, D, itens, M, incompatibilidades, 0, 0, 0, escolhidos);
  printf("%d\n", resultado);

  return 0;
}

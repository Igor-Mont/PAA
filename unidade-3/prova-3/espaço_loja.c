#include <stdio.h>
#include <stdbool.h>

// gcc espaço_loja.c -o ./out/espaço_loja
// ./out/espaço_loja.exe < ./in/espaço_loja.txt

// Função recursiva para maximizar o valor dos itens na loja
int maximizar_valor(int N, int D, int itens[][2], int M, int incompatibilidades[][2], int indice_item, int valor_atual, int peso_atual, int escolhidos[]) {
  if (indice_item == N) return valor_atual;

  // Verifica se o item é compatível com os itens já escolhidos
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

  // Maximiza o valor considerando o item atual
  int valor_maximo = maximizar_valor(N, D, itens, M, incompatibilidades, indice_item + 1, valor_atual, peso_atual, escolhidos);

  // Verifica se é possível adicionar o item sem exceder o limite de peso
  if (eh_compativel && peso_atual + itens[indice_item][1] <= D) {
    escolhidos[indice_item] = 1;
    int valor_com_item = maximizar_valor(N, D, itens, M, incompatibilidades, indice_item + 1, valor_atual + itens[indice_item][0], peso_atual + itens[indice_item][1], escolhidos);
    escolhidos[indice_item] = 0;
    valor_maximo = (valor_com_item > valor_maximo) ? valor_com_item : valor_maximo;
  }

  return valor_maximo;
}

int main() {
  int N, D, M;
  scanf("%d %d", &N, &D);

  // Entrada dos valores e pesos dos itens
  int itens[N][2];
  for (int i = 0; i < N; i++)
    scanf("%d %d", &itens[i][0], &itens[i][1]);

  // Entrada das incompatibilidades entre os itens
  scanf("%d", &M);
  int incompatibilidades[M][2];
  for (int i = 0; i < M; i++)
    scanf("%d %d", &incompatibilidades[i][0], &incompatibilidades[i][1]);

  // Array para armazenar os itens escolhidos
  int escolhidos[N];
  for (int i = 0; i < N; i++)
    escolhidos[i] = 0;

  // Chama a função para maximizar o valor e imprime o resultado
  int resultado = maximizar_valor(N, D, itens, M, incompatibilidades, 0, 0, 0, escolhidos);
  printf("%d\n", resultado);

  return 0;
}

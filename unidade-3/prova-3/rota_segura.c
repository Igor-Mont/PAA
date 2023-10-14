#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// gcc rota_segura.c -o ./out/rota_segura
// ./out/rota_segura.exe < ./in/rota_segura.txt

char resultado[100];
int comprimento = 0;

int minimo(int a, int b) {
  return a < b ? a : b;
}

int maximo(int a, int b) {
  return a > b ? a : b;
}

bool existe_solucao = false;

int resolverCaminho(int linha, int coluna, int nLinha, int nColuna, char tabuleiro[][nColuna]) {
  if (linha == nLinha - 1 && coluna == nColuna - 1) {
    for (int i = 0; i < comprimento; i++) printf("%c", resultado[i]);
	
    puts("");
    existe_solucao = true;
  }

  if (coluna - 1 >= 0 && tabuleiro[linha][coluna - 1] != 'T') {
		resultado[comprimento] = 'D';
		comprimento++;

		tabuleiro[linha][coluna] = 'T';

		resolverCaminho(linha, coluna - 1, nLinha, nColuna, tabuleiro);

		comprimento--;

		tabuleiro[linha][coluna] = 'L';
  }

  if (coluna + 1 < nColuna  && tabuleiro[linha][coluna + 1] != 'T') {
		resultado[comprimento] = 'E';
		comprimento++;

		tabuleiro[linha][coluna] = 'T';

		resolverCaminho(linha, coluna + 1, nLinha, nColuna, tabuleiro);
		comprimento--;

		tabuleiro[linha][coluna] = 'L';
  }

  if (linha + 1 < nLinha && tabuleiro[linha + 1][coluna] != 'T') {
		resultado[comprimento] = 'F';
		comprimento++;

		tabuleiro[linha][coluna] = 'T';

		resolverCaminho(linha + 1, coluna, nLinha, nColuna, tabuleiro);
		comprimento--;

		tabuleiro[linha][coluna] = 'L';
  }

  if (linha - 1 >= 0 && tabuleiro[linha - 1][coluna] != 'T') {
		resultado[comprimento] = 'T';
		comprimento++;

		tabuleiro[linha][coluna] = 'T';

		resolverCaminho(linha - 1, coluna, nLinha, nColuna, tabuleiro);
		comprimento--;

		tabuleiro[linha][coluna] = 'L';
  }
}

int main() {
  int linhas, colunas;

  scanf("%d%d", &linhas, &colunas);

  char tabuleiro[linhas][colunas];

  for (int i = 0; i < linhas; i++) scanf("%s", tabuleiro[i]);

  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      if(tabuleiro[i][j] == 'A') {
        tabuleiro[i][j] = 'A';

        if(i + 1 < linhas && tabuleiro[i + 1][j] != 'A') tabuleiro[i + 1][j] = 'T';
        if(i - 1 >= 0 && tabuleiro[i - 1][j] != 'A') tabuleiro[i - 1][j] = 'T';
        if(j + 1 < colunas && tabuleiro[i][j + 1] != 'A') tabuleiro[i][j + 1] = 'T';
        if(j - 1 >= 0 && tabuleiro[i][j - 1] != 'A') tabuleiro[i][j - 1] = 'T';
      }
    }
  }

  resolverCaminho(0, 0, linhas, colunas, tabuleiro);
  if (!existe_solucao) printf("Sem saida!\n");

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// gcc rota_segura.c -o ./out/rota_segura
// ./out/rota_segura.exe < ./in/rota_segura.txt

typedef struct {
	char valores[100];
	bool existe_solucao;
	int comprimento;
} Resultado;

typedef struct {
	int linha;
	int coluna;
	int total_linhas;
	int total_colunas;
} InformacoesTabuleiro;

Resultado resultado;

bool diferente_t(int colunas, char tabuleiro[][colunas], int linha, int coluna) {
	return tabuleiro[linha][coluna] != 'T';
}

int resolver_caminho(InformacoesTabuleiro info, char tabuleiro[][info.total_colunas]) {
  if (info.linha == info.total_linhas - 1 && info.coluna == info.total_colunas - 1) {
    for (int i = 0; i < resultado.comprimento; i++) printf("%c", resultado.valores[i]);
	
    printf("\n");
    resultado.existe_solucao = true;
  }

	InformacoesTabuleiro new_info;
	new_info.total_linhas = info.total_linhas;
	new_info.total_colunas = info.total_colunas;

  if (info.coluna - 1 >= 0 && diferente_t(info.total_colunas, tabuleiro, info.linha, info.coluna - 1)) {
		resultado.valores[resultado.comprimento++] = 'D';
		tabuleiro[info.linha][info.coluna] = 'T';

		new_info.linha = info.linha;
		new_info.coluna = info.coluna - 1;

		resolver_caminho(new_info, tabuleiro);

		resultado.comprimento--;
		tabuleiro[info.linha][info.coluna] = 'L';
  }

  if (info.coluna + 1 < info.total_colunas  && diferente_t(info.total_colunas, tabuleiro, info.linha, info.coluna + 1)) {
		resultado.valores[resultado.comprimento++] = 'E';
		tabuleiro[info.linha][info.coluna] = 'T';

		new_info.linha = info.linha;
		new_info.coluna = info.coluna + 1;

		resolver_caminho(new_info, tabuleiro);

		resultado.comprimento--;
		tabuleiro[info.linha][info.coluna] = 'L';
  }

  if (info.linha + 1 < info.total_linhas && diferente_t(info.total_colunas, tabuleiro, info.linha + 1, info.coluna)) {
		resultado.valores[resultado.comprimento++] = 'F';
		tabuleiro[info.linha][info.coluna] = 'T';

		new_info.linha = info.linha + 1;
		new_info.coluna = info.coluna;

		resolver_caminho(new_info, tabuleiro);

		resultado.comprimento--;
		tabuleiro[info.linha][info.coluna] = 'L';
  }
	
  if (info.linha - 1 >= 0 && diferente_t(info.total_colunas, tabuleiro, info.linha -1, info.coluna)) {
		resultado.valores[resultado.comprimento++] = 'T';
		tabuleiro[info.linha][info.coluna] = 'T';
				
		new_info.linha = info.linha - 1;
		new_info.coluna = info.coluna;

		resolver_caminho(new_info, tabuleiro);

		resultado.comprimento--;
		tabuleiro[info.linha][info.coluna] = 'L';
  }
}

void ler_tabuleiro(int linhas, int colunas, char tabuleiro[linhas][colunas]) {
	for (int i = 0; i < linhas; i++) scanf("%s", tabuleiro[i]);
}

void marcar_tabuleiro(int linhas, int colunas, char tabuleiro[linhas][colunas]) {
	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			if (tabuleiro[i][j] == 'A') {
				if (i + 1 < linhas && tabuleiro[i + 1][j] != 'A') tabuleiro[i + 1][j] = 'T';
				if (i - 1 >= 0 && tabuleiro[i - 1][j] != 'A') tabuleiro[i - 1][j] = 'T';
				if (j + 1 < colunas && tabuleiro[i][j + 1] != 'A') tabuleiro[i][j + 1] = 'T';
				if (j - 1 >= 0 && tabuleiro[i][j - 1] != 'A') tabuleiro[i][j - 1] = 'T';
			}
		}
	}
}

int main() {
  int linhas, colunas, i, j;
  scanf("%d%d", &linhas, &colunas);

  char tabuleiro[linhas][colunas];

	ler_tabuleiro(linhas, colunas, tabuleiro);
	marcar_tabuleiro(linhas, colunas, tabuleiro);

	resultado.existe_solucao = false;
	resultado.comprimento = 0;

	InformacoesTabuleiro infos;
	infos.linha = 0;
	infos.coluna = 0;
	infos.total_colunas = colunas;
	infos.total_linhas = linhas;

  resolver_caminho(infos, tabuleiro);
  if (!resultado.existe_solucao) printf("Sem saida!\n");

  return 0;
}

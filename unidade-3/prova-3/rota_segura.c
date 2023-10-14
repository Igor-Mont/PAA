#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int linha;
    int coluna;
    int totalLinhas;
    int totalColunas;
} InformacoesTabuleiro;

typedef struct {
    char resultado[100];
    int temSolucao;
    int comprimento;
} Resultado;

// gcc rota_segura.c -o ./out/rota_segura
// ./out/rota_segura.exe < ./in/rota_segura.txt

void resolverCaminho(InformacoesTabuleiro info, char tabuleiro[][info.totalColunas], Resultado* resultado) {
    if (info.linha == info.totalLinhas - 1 && info.coluna == info.totalColunas - 1) {
        for (int i = 0; i < resultado->comprimento; i++) 
            printf("%c", resultado->resultado[i]);

        puts("");
        resultado->temSolucao = 1;
    }

    if (info.coluna - 1 >= 0 && tabuleiro[info.linha][info.coluna - 1] != 'T') {
        resultado->resultado[resultado->comprimento] = 'D';
        resultado->comprimento++;

        tabuleiro[info.linha][info.coluna] = 'T';

        resolverCaminho(info, tabuleiro, resultado);

        resultado->comprimento--;

        tabuleiro[info.linha][info.coluna] = 'L';
    }

    if (info.coluna + 1 < info.totalColunas && tabuleiro[info.linha][info.coluna + 1] != 'T') {
        resultado->resultado[resultado->comprimento] = 'E';
        resultado->comprimento++;

        tabuleiro[info.linha][info.coluna] = 'T';

        resolverCaminho(info, tabuleiro, resultado);
        resultado->comprimento--;

        tabuleiro[info.linha][info.coluna] = 'L';
    }

    if (info.linha + 1 < info.totalLinhas && tabuleiro[info.linha + 1][info.coluna] != 'T') {
        resultado->resultado[resultado->comprimento] = 'F';
        resultado->comprimento++;

        tabuleiro[info.linha][info.coluna] = 'T';

        resolverCaminho(info, tabuleiro, resultado);
        resultado->comprimento--;

        tabuleiro[info.linha][info.coluna] = 'L';
    }

    if (info.linha - 1 >= 0 && tabuleiro[info.linha - 1][info.coluna] != 'T') {
        resultado->resultado[resultado->comprimento] = 'T';
        resultado->comprimento++;

        tabuleiro[info.linha][info.coluna] = 'T';

        resolverCaminho(info, tabuleiro, resultado);
        resultado->comprimento--;

        tabuleiro[info.linha][info.coluna] = 'L';
    }
}

int main() {
    InformacoesTabuleiro informacoes;

    scanf("%d%d", &informacoes.totalLinhas, &informacoes.totalColunas);

    char tabuleiro[informacoes.totalLinhas][informacoes.totalColunas];

    for (int i = 0; i < informacoes.totalLinhas; i++) 
        scanf("%s", tabuleiro[i]);

    for (int i = 0; i < informacoes.totalLinhas; i++) {
        for (int j = 0; j < informacoes.totalColunas; j++) {
            if (tabuleiro[i][j] == 'A') {
                tabuleiro[i][j] = 'A';

                if (i + 1 < informacoes.totalLinhas && tabuleiro[i + 1][j] != 'A') 
                    tabuleiro[i + 1][j] = 'T';
                
                if (i - 1 >= 0 && tabuleiro[i - 1][j] != 'A') 
                    tabuleiro[i - 1][j] = 'T';
                
                if (j + 1 < informacoes.totalColunas && tabuleiro[i][j + 1] != 'A') 
                    tabuleiro[i][j + 1] = 'T';
                
                if (j - 1 >= 0 && tabuleiro[i][j - 1] != 'A') 
                    tabuleiro[i][j - 1] = 'T';
            }
        }
    }

    Resultado resultado;
    resultado.comprimento = 0;
    resultado.temSolucao = 0;

    resolverCaminho((InformacoesTabuleiro){0, 0, informacoes.totalLinhas, informacoes.totalColunas}, tabuleiro, &resultado);

    if (!resultado.temSolucao) 
        printf("Sem saída!\n");

    return 0;
}

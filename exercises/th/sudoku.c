#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define linhas 9
#define colunas 9

int ** leMatriz() {
  int ** matriz = NULL;
  int linha_atual = 0;
  int coluna_atual = 0;

  matriz = (int **)malloc(sizeof(int *) * linhas);

  for (int i = 0; i < linhas * colunas; i++) {
    int n;
    scanf("%d", &n);

    if (!coluna_atual) {
      matriz[linha_atual] = (int *)malloc(colunas * sizeof(int));
    }

    matriz[linha_atual][coluna_atual] = n;
    coluna_atual++;

    if (coluna_atual == colunas) {
      linha_atual++;
      coluna_atual = 0;
    }
  }

  return matriz;
}

bool verificar_linhas(int ** sudoku) {
  for (int i = 0; i < linhas; i++) {
    bool ocorrencias[9] = {false}; 

    for (int j = 0; j < colunas; j++) {
      int num = sudoku[i][j];
      if (ocorrencias[num - 1]) return false;
      ocorrencias[num - 1] = true; 
    }
  }

  return true;
}

bool verificar_colunas(int ** sudoku) {
    for (int j = 0; j < colunas; j++) {
      bool ocorrencias[9] = {false}; 

      for (int i = 0; i < linhas; i++) {
        int num = sudoku[i][j];
        if (ocorrencias[num - 1]) return false;
        ocorrencias[num - 1] = true; 
      }
    }

    return true;
}

bool verificaMatrizGlobal(int ** sudoku) {
  return verificar_linhas(sudoku) || verificar_colunas(sudoku);
}

void extrairSubgrade(int ** sudoku, int linhaInicial, int colunaInicial, int subgrade[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      subgrade[i][j] = sudoku[linhaInicial + i][colunaInicial + j];
    }
  }
}

bool verificarSubgrade(int subgrade[3][3]) {
  int numeros[9] = {0};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int numero = subgrade[i][j];
      if (numeros[numero - 1] != 0) {
        return false; 
      }
      numeros[numero - 1] = numero;
    }
  }

  return true;
}

bool verificaMatrizInterna(int ** sudoku) {
  for (int i = 0; i < 9; i += 3) {
    for (int j = 0; j < 9; j += 3) {
      int subgrade[3][3];
      extrairSubgrade(sudoku, i, j, subgrade);
      if(!verificarSubgrade(subgrade)) return false;
    }
  }

  return true;
}

int main() {
  int ** sudoku = leMatriz();
  bool global = verificaMatrizGlobal(sudoku);
  bool interna = verificaMatrizInterna(sudoku);
  if(global && interna) {
    printf("YES");
    return 0;
  }

  if(!global) {
    printf("NO\nGLOBAL");
    return 0;
  }

  if(!interna) {
    printf("NO\nINTERNA");
    return 0;
  }

  return 0;
}
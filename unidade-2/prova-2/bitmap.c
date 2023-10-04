#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef int Matrix[200][200];

typedef struct {
  int first_column, second_column;
} Columns;

typedef struct {
  int first_row, second_row;
} Lines;

int active_column;

int verify_matrix(Matrix matrix, Lines lines, Columns columns) {
  int i, j, result = -1;

  for (i = lines.first_row; i < lines.second_row; ++i)
    for (j = columns.first_column; j < columns.second_column; ++j) {
      if ((result == 1 ||  result == -1) && matrix[i][j] == 1) result = 1;
      else if ((result == 0 ||  result == -1) && matrix[i][j] == 0) result = 0;
      else return -1;
    }

  return result;
}

bool verify_subtraction_one(int n, int m) {
  return m - n == 1;
}

void verify_active_column() {
  if(active_column == 50) {
    active_column = 0;
    printf("\n");
  }
}

void matrix_handler(Matrix matrix, Lines lines, Columns columns) {
  int middle_column, middle_line;

  bool detect_row_column_match = (lines.first_row == lines.second_row) || (columns.first_column == columns.second_column); 
  if (detect_row_column_match) return;

  int result = verify_matrix(matrix, lines, columns);
  if (result != -1) {
    verify_active_column();
    printf("%d", result);

    active_column++;
    return;
  } 

  verify_active_column();
  printf("D");

  active_column++;

  bool is_substractions_one = verify_subtraction_one(lines.first_row, lines.second_row) && verify_subtraction_one(columns.first_column, columns.second_column); 
  if (is_substractions_one) return;
  
  middle_column = ceil((columns.first_column + columns.second_column) / 2.0);
  middle_line = ceil((lines.first_row + lines.second_row) / 2.0);

  Lines l1, l2;
  Columns c1, c2;

  l1.first_row = lines.first_row;
  l1.second_row = middle_line;

  c1.first_column = columns.first_column;
  c1.second_column = middle_column;

  l2.first_row = middle_line;
  l2.second_row = lines.second_row;

  c2.first_column = middle_column;
  c2.second_column = columns.second_column;

  matrix_handler(matrix, l1, c1); 
  matrix_handler(matrix, l1, c2); 
  matrix_handler(matrix, l2, c1); 
  matrix_handler(matrix, l2, c2); 
}

int main() {
  int times, line, column, i, j;
  Matrix matrix;
  
  scanf("%d", &times);
  
  while (times != 0) {
    scanf("%d %d", &line, &column); 

    for (i = 0; i < line; ++i)
      for (j = 0; j < column; ++j) scanf(" %1d", &matrix[i][j]);

    active_column = 0;

    Lines lines;
    lines.first_row = 0;
    lines.second_row = line;

    Columns columns;
    columns.first_column = 0;
    columns.second_column = column;

    matrix_handler(matrix, lines, columns);

    printf("\n");

    times--;
  }
  return 0;
}
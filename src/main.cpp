#include <iostream>
#include <iomanip>
#include <vector>

static const int N = 5;

typedef double Matrix[N][N + 1];

void gauss_jordan(Matrix &matrix);

bool is_row_zero(const Matrix &matrix, size_t pivot_row, size_t pivot_column);

void print_matrix(const Matrix &matrix, size_t row = 0, size_t column = 0);

int main() {
  Matrix matrix = {
    {2, -1, 2, 6, -10, -9},
    {-7, 5, -9, 9, 2, -6},
    {1, -6, -4, -3, 10, -6},
    {-3, -4, 4, 0, 9, 4},
    {10, 9, 7, -6, 1, 6},
  };
  gauss_jordan(matrix);
  return 0;
}

void gauss_jordan(Matrix &matrix) {
  std::cout << "Gestartet mit:" << std::endl;
  print_matrix(matrix);
  std::cout << std::endl;

  size_t pivot_row = 0, pivot_column = 0;
  while (pivot_row < N && pivot_column < N) {
    // 1. Man sucht die erste Spalte bei der an mindestens einer Stelle keine Null steht.
    if(is_row_zero(matrix, pivot_row, pivot_column)) {
      pivot_column++;
      continue;
    }

    // 2. Ist die oberste Zahl eine 0, so vertausche die Zeile mit einer anderen die keine
    //    Null enthält.
    if (matrix[pivot_row][pivot_column] == 0) {
      for (size_t row = pivot_row + 1; row < N; row++) {
        if (matrix[row][pivot_column] != 0) {
          std::swap(matrix[pivot_row], matrix[row]);
          break;
        }
      }
    }

    // 3. Nun wird die erste Zeile anhand der ersten Zahl normiert, so dass das erste Element
    //    eine 1 ist.
    double factor = matrix[pivot_row][pivot_column];
    for (size_t column = pivot_column; column < N + 1; column++) {
      matrix[pivot_row][column] /= factor;
    }

    // 4. Nun wird die erste Zahl der übrigen Zeilen zu null gemacht, indem ein Vielfaches der
    //    erstens Zeile abgezogen wird.
    for (size_t row = pivot_row + 1; row < N; row++) {
      double factor = matrix[row][pivot_column];

      for (size_t column = pivot_column; column < N + 1; column++) {
        matrix[row][column] -= factor * matrix[pivot_row][column];
      }
    }

    // 5. Nun streicht man die erste Zeile und Spalte und fährt mit der Restmatrix fort.
    pivot_column++;
    pivot_row++;
  }

  // 6. Nun zieht man danach von den darüberliegenden Zeilen entsprechende Vielfache ab,
  //    sodass über einer führenden 1 nur Nullen stehen.
  for (size_t row = N - 1; row > 0; row--) {
    for (int upper_row = row - 1; upper_row >= 0; upper_row--) {
      double factor = matrix[upper_row][row];

      for (size_t column = 0; column < N + 1; column++) {
        matrix[upper_row][column] -= factor * matrix[row][column];
      }
    }
  }

  std::cout << "Fertig mit:" << std::endl;
  print_matrix(matrix);
  std::cout << std::endl;

  std::cout << "Ergebnisse:" << std::endl;
  for (size_t row = 0; row < N; row++) {
    std::cout << "x" << row + 1 << " = " << matrix[row][N] << std::endl;
  }
}

// Im schlechtesten Fall O(n)
bool is_row_zero(const Matrix &matrix, size_t pivot_row, size_t pivot_column) {
  for (size_t row = pivot_row; row < N; row++) {
    if (matrix[row][pivot_column] != 0) {
      return false;
    }
  }

  return true;
}

// Im schlechtesten Fall O(n^2)
void print_matrix(const Matrix &matrix, size_t row, size_t column) {
  for (size_t i = row; i < N; i++) {
    for (size_t j = column; j < N; j++) {
      std::cout << std::fixed << std::setprecision(2);
      std::cout << matrix[i][j] << " ";
    }

    std::cout << "| " << matrix[i][N] << std::endl;
  }
}

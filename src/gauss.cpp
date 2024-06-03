#include "gauss.h"

#include <iostream>
#include <iomanip>
#include <vector>

// Im schlechtesten Fall: O(n^3)
void gauss_jordan(Matrix &matrix) {
  size_t pivot_row = 0, pivot_column = 0;

  // Laufzeit der Schleife: O(n)
  // Somit schlechteste Laufzeit: O(n^3)
  while (pivot_row < N && pivot_column < N) {
    // 1. Man sucht die erste Spalte bei der an mindestens einer Stelle keine Null steht.
    // Laufzeit im schlechtesten Fall: O(n)
    if(is_row_zero(matrix, pivot_row, pivot_column)) {
      pivot_column++;
      continue;
    }

    // 2. Ist die oberste Zahl eine 0, so vertausche die Zeile mit einer anderen die keine
    //    Null enthält.
    //    Laufzeit im schlechtesten Fall: O(n)
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
    //    Laufzeit im schlechtesten Fall: O(n)
    double factor = matrix[pivot_row][pivot_column];
    for (size_t column = pivot_column; column < N + 1; column++) {
      matrix[pivot_row][column] /= factor;
    }

    // 4. Nun wird die erste Zahl der übrigen Zeilen zu null gemacht, indem ein Vielfaches der
    //    erstens Zeile abgezogen wird.
    //    Laufzeit im schlechtesten Fall: O(n^2)
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
  //    Laufzeit im schlechtesten Fall: O(n^3)
  for (size_t row = N - 1; row > 0; row--) {
    for (int upper_row = row - 1; upper_row >= 0; upper_row--) {
      double factor = matrix[upper_row][row];

      for (size_t column = 0; column < N + 1; column++) {
        matrix[upper_row][column] -= factor * matrix[row][column];
      }
    }
  }
}

// Laufzeit im schlechtesten Fall: O(n)
bool is_row_zero(const Matrix &matrix, size_t pivot_row, size_t pivot_column) {
  for (size_t row = pivot_row; row < N; row++) {
    if (matrix[row][pivot_column] != 0) {
      return false;
    }
  }

  return true;
}

// Laufzeit im schlechtesten Fall: O(n^2)
void print_matrix(const Matrix &matrix, size_t row, size_t column) {
  for (size_t i = row; i < N; i++) {
    for (size_t j = column; j < N; j++) {
      std::cout << std::fixed << std::setprecision(2);
      std::cout << matrix[i][j] << " ";
    }

    std::cout << "| " << matrix[i][N] << std::endl;
  }
}

#include <random>

double stability(size_t amount, double lower_bound, double upper_bound) {
  std::random_device random_device;
  std::mt19937 gen(random_device());
  std::uniform_real_distribution<double> dist1(-10000000, 10000000);
  std::uniform_real_distribution<double> dist2(upper_bound, lower_bound);

  double average_diff = 0;

  for (size_t i = 0; i < amount; i++) {
    Matrix input = {
      {dist1(gen), dist1(gen), dist1(gen), dist1(gen)},
      {dist1(gen), dist1(gen), dist1(gen), dist1(gen)},
      {dist1(gen), dist1(gen), dist1(gen), dist1(gen)}
    };
    
    Matrix disturbed;
    copy(input, disturbed);

    for (size_t i = 0; i < N; i++) {
      disturbed[i][i] += dist2(gen);
    }

    gauss_jordan(input);
    gauss_jordan(disturbed);

    double diff = 0;
    for (size_t i = 0; i < N; i++) {
      diff += std::abs(input[i][N] - disturbed[i][N]);
    }

    average_diff += diff;
  }

  average_diff /= amount;

  return average_diff;
}

void copy(const Matrix &source, Matrix &destination) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N + 1; ++j) {
            destination[i][j] = source[i][j];
        }
    }
}

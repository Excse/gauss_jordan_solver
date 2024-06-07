#include "solver.h"

#include <random>

void solve_matrix(Matrix &matrix) {
  size_t p_row = 0, p_col = 0;

  while (p_row < matrix.rows() && p_col < matrix.cols()) {
    // 1. Man sucht die erste Spalte bei der an mindestens einer Stelle keine
    // Null steht.
    if (matrix.is_row_zero(p_row, p_col)) {
      p_col++;
      continue;
    }

    // 2. Ist die oberste Zahl eine 0, so vertausche die Zeile mit einer anderen
    // die keine
    //    Null enthält.
    if (matrix(p_row, p_col) == 0) {
      for (size_t row = p_row + 1; row < matrix.rows(); row++) {
        if (matrix(row, p_col) != 0) {
          matrix.swap_rows(p_row, row);
          break;
        }
      }
    }

    // 3. Nun wird die erste Zeile anhand der ersten Zahl normiert, so dass das
    // erste Element
    //    eine 1 ist.
    double factor = matrix(p_row, p_col);
    for (size_t col = p_col; col < matrix.cols(); col++) {
      matrix(p_row, col) /= factor;
    }

    // 4. Nun wird die erste Zahl der übrigen Zeilen zu null gemacht, indem ein
    // Vielfaches der
    //    erstens Zeile abgezogen wird.
    for (size_t row = p_row + 1; row < matrix.rows(); row++) {
      double factor = matrix(row, p_col);

      for (size_t col = p_col; col < matrix.cols(); col++) {
        matrix(row, col) -= factor * matrix(p_row, col);
      }
    }

    // 5. Nun streicht man die erste Zeile und Spalte und fährt mit der
    // Restmatrix fort.
    p_col++;
    p_row++;
  }

  // 6. Nun zieht man danach von den darüberliegenden Zeilen entsprechende
  // Vielfache ab,
  //    sodass über einer führenden 1 nur Nullen stehen.
  for (size_t row = matrix.rows() - 1; row > 0; row--) {
    for (int u_row = row - 1; u_row >= 0; u_row--) {
      double factor = matrix(u_row, row);

      for (size_t col = 0; col < matrix.cols(); col++) {
        matrix(u_row, col) -= factor * matrix(row, col);
      }
    }
  }
}

double stability(size_t amount, size_t rows, size_t cols, double lower_bound,
                 double upper_bound) {
  std::random_device random_device;
  std::mt19937 gen(random_device());
  std::uniform_real_distribution<double> number(-10000000, 10000000);
  std::uniform_real_distribution<double> noise(upper_bound, lower_bound);

  double avg_difference = 0;
  for (size_t iteration = 0; iteration < amount; iteration++) {
    Matrix input(rows, cols);
    for (size_t row = 0; row < rows; row++) {
      for (size_t col = 0; col < cols; col++) {
        input(row, col) = number(gen);
      }
    }

    Matrix disturbed(input);
    for (size_t row = 0; row < disturbed.rows(); row++) {
      for (size_t col = 0; col < disturbed.cols(); col++) {
        disturbed(row, col) += noise(gen);
      }
    }

    solve_matrix(input);
    solve_matrix(disturbed);

    double difference = 0;
    for (size_t row = 0; row < input.rows(); row++) {
      for (size_t col = 0; col < input.cols() - 1; col++) {
        difference += std::abs(input(row, col) - disturbed(row, col));
      }
    }

    avg_difference += difference;
  }

  avg_difference /= amount;

  return avg_difference;
}

#include "solver.h"

#include <random>

/**
 * Löst das Gleichungssystem mithilfe des Gauss-Jordan-Verfahrens. Die übergebene
 * Matrix wird dabei verändert.
 */
void solve_matrix(Matrix &matrix, bool debug) {
  // Hilfsvariablen, welche genutzt werden um eine Restmatrix zu verwirklichen.
  size_t p_row = 0, p_col = 0;

  if (debug) std::cout << "Matrix before solving:\n" << matrix << std::endl;

  // Ein Teil des 5. Schrittes, indem der Algorithmus immer wieder auf die Restmatrix
  // angewandt wird. Dieser Schritt wird so lange wiederholt, bis es keine Restmatrix
  // mehr gibt.
  while (p_row < matrix.rows() && p_col < matrix.cols()) {
    // 1. Man sucht die erste Spalte bei der an mindestens einer Stelle keine
    // Null steht.
    if (matrix.is_row_zero(p_row, p_col)) {
      p_col++;

      if (debug) {
        std::cout << "1.) Step:" << std::endl;
        std::cout << "Skipped row " << p_row << std::endl;
        matrix.print(std::cout, p_row, p_col);
        std::cout << std::endl;
      }
      continue;
    } else if (debug) {
      std::cout << "1.) Not needed:" << std::endl;
      matrix.print(std::cout, p_row, p_col);
      std::cout << std::endl;
    }

    // 2. Ist die oberste Zahl eine 0, so vertausche die Zeile mit einer anderen
    // die keine Null enthält.
    if (matrix(p_row, p_col) == 0) {
      for (size_t row = p_row + 1; row < matrix.rows(); row++) {
        if (matrix(row, p_col) != 0) {
          matrix.swap_rows(p_row, row);

          if (debug) {
            std::cout << "2.) Step:" << std::endl;
            std::cout << "Swapped row " << p_row << " with row " << row << std::endl;
            matrix.print(std::cout, p_row, p_col);
            std::cout << std::endl;
          }
          break;
        }
      }
    } else if (debug) {
      std::cout << "2.) Not needed:" << std::endl;
      matrix.print(std::cout, p_row, p_col);
      std::cout << std::endl;
    }

    if (debug) std::cout << "3.) Step:" << std::endl;

    // 3. Nun wird die erste Zeile anhand der ersten Zahl normiert, so dass das
    // erste Element eine 1 ist.
    double factor = matrix(p_row, p_col);
    for (size_t col = p_col; col < matrix.cols(); col++) {
      matrix(p_row, col) /= factor;
    }

    if (debug) {
      std::cout << "Normalized row " << p_row << " using the factor " << factor << std::endl;
      matrix.print(std::cout, p_row, p_col);
      std::cout << std::endl;

      std::cout << "4.) Step:" << std::endl;
    }

    // 4. Nun wird die erste Zahl der übrigen Zeilen zu null gemacht, indem ein
    // Vielfaches der erstens Zeile abgezogen wird.
    for (size_t row = p_row + 1; row < matrix.rows(); row++) {
      double factor = matrix(row, p_col);

      for (size_t col = p_col; col < matrix.cols(); col++) {
        matrix(row, col) -= factor * matrix(p_row, col);
      }

      if (debug) std::cout << "Subtracted row " << p_row << " from row " << row << " using the factor " << factor << std::endl;
    }

    if (debug) {
      matrix.print(std::cout, p_row, p_col);
      std::cout << std::endl;
    }

    // 5. Nun streicht man die erste Zeile und Spalte und fährt mit der
    // Restmatrix fort.
    p_col++;
    p_row++;

    if (debug) {
      std::cout << "5.) Step:" << std::endl;
      matrix.print(std::cout, p_row, p_col);
      std::cout << std::endl;
    }
  }

  if (debug) {
    std::cout << "Matrix before 6.) Step:" << std::endl;
    std::cout << matrix << std::endl;
    std::cout << std::endl;

    std::cout << "6.) Step:" << std::endl;
  }

  // 6. Nun zieht man danach von den darüberliegenden Zeilen entsprechende
  // Vielfache ab, sodass über einer führenden 1 nur Nullen stehen.
  for (size_t index = matrix.rows() - 1; index > 0; index--) {
    for (int u_row = index - 1; u_row >= 0; u_row--) {
      double factor = matrix(u_row, index);

      for (size_t col = 0; col < matrix.cols(); col++) {
        matrix(u_row, col) -= factor * matrix(index, col);
      }

      if (debug) std::cout << "Subtracted row " << index << " from row " << u_row << " using the factor " << factor << std::endl;
    }
  }

  if (debug) {
    std::cout << matrix << std::endl;
    std::cout << std::endl;
  }
}

/**
 * Prüft den Algorithmus auf die Stabilität, indem n Matrizen mit den gegebenen 
 * Dimensionen  erstellt werden, die leicht verändert werden. Die Differenz der Matrix
 * gibt hierbei die durchschnittliche Fehlerrate an, welche auch zurückgegeben wird.
 */
double stability(size_t amount, size_t rows, size_t cols, double lower_bound,
                 double upper_bound) {
  // Initialisierung von den Zufallsgeneratoren die genutzt werden um zufällige Zahlen
  // sowie Störungen zu generieren.
  std::random_device random_device;
  std::mt19937 gen(random_device());
  std::uniform_real_distribution<double> number(-10000000, 10000000);
  std::uniform_real_distribution<double> noise(upper_bound, lower_bound);

  // Die durchschnittliche Fehlerrate der Matrizen.
  double avg_difference = 0;

  // Erstellt n Matrizen mit den gegebenen Dimensionen und verändert diese leicht um
  // die Stabilität des Algorithmus zu prüfen.
  for (size_t iteration = 0; iteration < amount; iteration++) {
    // Erstellt eine Matrix mit zufälligen Zahlen.
    Matrix input(rows, cols);
    for (size_t row = 0; row < rows; row++) {
      for (size_t col = 0; col < cols; col++) {
        input(row, col) = number(gen);
      }
    }

    // Kopiert die originale Matrix und verändert diese leicht.
    Matrix disturbed(input);
    for (size_t row = 0; row < disturbed.rows(); row++) {
      for (size_t col = 0; col < disturbed.cols(); col++) {
        disturbed(row, col) += noise(gen);
      }
    }

    // Löst beide Matrizen mithilfe des Gauss-Jordan-Verfahrens.
    solve_matrix(input);
    solve_matrix(disturbed);

    // Berechnung der Differenz der beiden Matrizen.
    double difference = 0;
    for (size_t row = 0; row < input.rows(); row++) {
      for (size_t col = 0; col < input.cols(); col++) {
        difference += std::abs(input(row, col) - disturbed(row, col));
      }
    }

    avg_difference += difference;
  }

  avg_difference /= amount;

  return avg_difference;
}

#include "matrix.h"

#include <iomanip>
#include <stdexcept>

/**
 * Erstellt eine Matrix mit den übergebenen Werten.
 */
Matrix::Matrix(std::initializer_list<std::initializer_list<double>> init) {
  if (init.size() <= 0) {
    throw std::invalid_argument("There must be at least one row.");
  }

  this->_rows = init.size();

  size_t cols = init.begin()->size();
  this->_cols = cols;

  this->_data = std::vector<double>(this->rows() * this->cols());

  size_t index = 0;
  for (const auto &row : init) {
    if (row.size() != this->cols()) {
      throw std::invalid_argument(
          "All rows must have the same number of columns");
    }

    for (const auto &elem : row) {
      this->_data[index++] = elem;
    }
  }
}

/**
 * Erstellt eine Matrix mit der angegebenen Anzahl an Zeilen und Spalten.
 * Die Matrix wird mit Nullen initialisiert.
 */
Matrix::Matrix(size_t rows, size_t cols)
    : _data(rows * cols), _cols(cols), _rows(rows) {}

/**
 * Wird genutzt um auf ein einziges Element der Matrix zugreifen zu können. Hierbei
 * wird ein nicht-const-double zurückgegeben, damit das Element verändert werden kann.
 */
double &Matrix::operator()(size_t row, size_t col) {
  if (row >= this->_rows || col >= this->_cols) {
    throw std::out_of_range("Matrix indices out of range");
  }

  return this->_data[row * this->_cols + col];
}

/**
 * Wird genutzt um auf ein einziges Element der Matrix zugreifen zu können. Hierbei
 * wird ein const-double zurückgegeben, damit das Element nicht verändert werden kann.
 */
double Matrix::operator()(size_t row, size_t col) const {
  if (row >= this->_rows || col >= this->_cols) {
    throw std::out_of_range("Matrix indices out of range");
  }

  return this->_data[row * this->_cols + col];
}

/**
 * Wird genutzt um die Matrix Zeile für Zeile einzulesen.
 */
std::istream &operator>>(std::istream &input, Matrix &matrix) {
  for (size_t row = 0; row < matrix.rows(); ++row) {
    for (size_t column = 0; column < matrix.cols(); ++column) {
      input >> matrix(row, column);
    }
  }

  return input;
}

/**
 * Wird genuzt um die Matrix auf der Konsole auszugeben. Hierbei werden immer 2 Nachkommastellen
 * ausgegeben.
 */
std::ostream &operator<<(std::ostream &input, Matrix &matrix) {
  for (size_t row = 0; row < matrix.rows(); row++) {
    for (size_t column = 0; column < matrix.cols(); column++) {
      std::cout << std::fixed << std::setprecision(2);
      std::cout << matrix(row, column) << " ";
    }

    std::cout << std::endl;
  }

  return input;
}

/**
 * Tauscht zwei angegebene Zeilen miteinander.
 */
void Matrix::swap_rows(size_t first, size_t second) {
  for (size_t column = 0; column < this->cols(); column++) {
    std::swap((*this)(first, column), (*this)(second, column));
  }
}

/**
 * Prüft ob die übergebene Zeile nur Nullen enthält. Zudem kann mit einem Offset
 * angegeben werden, ab welcher Spalte geprüft werden soll.
 */
bool Matrix::is_row_zero(size_t row, size_t column_offset) {
  for (size_t i_row = row; i_row < this->rows(); i_row++) {
    if ((*this)(i_row, column_offset) != 0) {
      return false;
    }
  }

  return true;
}

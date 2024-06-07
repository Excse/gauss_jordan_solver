#include "matrix.h"

#include <iomanip>
#include <stdexcept>

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

Matrix::Matrix(size_t rows, size_t cols)
    : _data(rows * cols), _cols(cols), _rows(rows) {}

double &Matrix::operator()(size_t row, size_t col) {
  if (row >= this->_rows || col >= this->_cols) {
    throw std::out_of_range("Matrix indices out of range");
  }

  return this->_data[row * this->_cols + col];
}

double Matrix::operator()(size_t row, size_t col) const {
  if (row >= this->_rows || col >= this->_cols) {
    throw std::out_of_range("Matrix indices out of range");
  }

  return this->_data[row * this->_cols + col];
}

std::istream &operator>>(std::istream &input, Matrix &matrix) {
  for (size_t row = 0; row < matrix.rows(); ++row) {
    for (size_t column = 0; column < matrix.cols(); ++column) {
      input >> matrix(row, column);
    }
  }

  return input;
}

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

void Matrix::swap_rows(size_t first, size_t second) {
  for (size_t column = 0; column < this->cols(); column++) {
    std::swap((*this)(first, column), (*this)(second, column));
  }
}

bool Matrix::is_row_zero(size_t row, size_t column_offset) {
  for (size_t i_row = row; i_row < this->rows(); i_row++) {
    if ((*this)(i_row, column_offset) != 0) {
      return false;
    }
  }

  return true;
}

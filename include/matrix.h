#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <cstddef>
#include <vector>

class Matrix {
private:
  std::vector<double> _data;
  size_t _cols, _rows;

public:
  Matrix(std::initializer_list<std::initializer_list<double>> init);

  Matrix(size_t rows, size_t cols);

  double &operator()(size_t row, size_t col);

  double operator()(size_t row, size_t col) const;

  friend std::istream &operator>>(std::istream &input, Matrix &matrix);

  friend std::ostream &operator<<(std::ostream &output, Matrix &matrix);

  bool is_row_zero(size_t row, size_t col_offset = 0);

  void swap_rows(size_t first, size_t second);

  size_t cols() const {
    return this->_cols;
  }

  size_t rows() const {
    return this->_rows;
  }
};

#endif /* MATRIX_H_ */

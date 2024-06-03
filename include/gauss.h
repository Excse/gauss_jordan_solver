#pragma once

#include <cstddef>
#include <vector>

static const int N = 3;

typedef std::vector<double> Output;
typedef double Matrix[N][N + 1];

void gauss_jordan(Matrix &matrix);

bool is_row_zero(const Matrix &matrix, size_t pivot_row, size_t pivot_column);

void print_matrix(const Matrix &matrix, size_t row = 0, size_t column = 0);

double stability(size_t amount, double lower_bound, double upper_bound);

void copy(const Matrix &source, Matrix &destination);

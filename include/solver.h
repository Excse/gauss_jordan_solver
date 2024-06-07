#ifndef SOLVER_H_
#define SOLVER_H_

#include "matrix.h"

void solve_matrix(Matrix &matrix);

double stability(size_t amount, size_t rows, size_t cols, double lower_bound,
                 double upper_bound);

#endif /* SOLVER_H_ */

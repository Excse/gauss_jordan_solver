#include <gtest/gtest.h>

#include "gauss.h"

TEST(gauss, test1) {
  Matrix matrix = {
    {0, 2, 1, 3},
    {4, 2, 0, 8},
    {2, 3, 0, 0}
  };

  gauss_jordan(matrix);

  EXPECT_NEAR(matrix[0][3], 3.0, 1e-6);
  EXPECT_NEAR(matrix[1][3], -2.0, 1e-6);
  EXPECT_NEAR(matrix[2][3], 7.0, 1e-6);
}

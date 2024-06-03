#include <gtest/gtest.h>

#include "gauss.h"

TEST(gauss, stability) {
  EXPECT_LT(stability(1000000, 1e-12, 1e-6), 1e-5);
  EXPECT_LT(stability(1000000, 1e-10, 1e-6), 1e-5);
  EXPECT_LT(stability(1000000, 1e-8, 1e-6), 1e-5);
  EXPECT_LT(stability(10000000, 1e-6, 1e-6), 1e-5);
}

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

TEST(gauss, failed_huge_1) {
  Matrix matrix = {
    {-2470757741212121, 20950064612121212, -515840988121213, -4909749912121214},
    {864389502121215, 786016363121216, 2522071351212121, -712001599121218},
    {441663974121219, -781179334121211, -11736194812121212, -416561849121213}
  };

  gauss_jordan(matrix);

  EXPECT_NEAR(matrix[0][3], 0.742331234075, 1e-12);
  EXPECT_NEAR(matrix[1][3], -0.145008181443, 1e-12);
  EXPECT_NEAR(matrix[2][3], 0.073081626577, 1e-12);
}

TEST(gauss, failed_small_1) {
  Matrix matrix = {
    {0.0000247075774, 0.0209500646, 0.00515840988, 0.049097499},
    {0.00864389502, 0.0000786016363, 0.0252207135, 0.00712001599},
    {0.0441663974, 0.00781179334, 0.0117361948, 0.000416561849},
  };

  gauss_jordan(matrix);

  EXPECT_NEAR(matrix[0][3], 10211972632.519414044384, 1e-12);
  EXPECT_NEAR(matrix[1][3], 850380731.563873854552, 1e-12);
  EXPECT_NEAR(matrix[2][3], -3502599587.139743237815, 1e-12);
}

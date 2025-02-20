/**
 * Nullity test of Divergence operator
 */

#include <mole/divergence.h>
#include <mole/operators.h>
#include <gtest/gtest.h>

void run_nullity_test(int k, Real tol)
{
  int m = 2 * k + 1;
  Real dx = 1;

  Divergence D(k, m, dx);
  arma::vec field(m + 1, fill::ones);

  arma::vec sol = D * field;

  EXPECT_NEAR(arma::norm(sol), 0, tol);
}

TEST(DivergenceTests, Nullity)
{
  Real tol = 1e-10;
  for (int k : {2, 4, 6})
  {
    run_nullity_test(k, tol);
  }
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

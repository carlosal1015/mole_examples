/**
 * Nullity test of Gradient operator
 */

#include <mole/gradient.h>
#include <mole/operators.h>
#include <gtest/gtest.h>

void run_nullity_test(int k, Real tol)
{
  int m = 2 * k + 1;
  Real dx = 1;

  Gradient G(k, m, dx);
  arma::vec field(m + 2, fill::ones);

  arma::vec sol = G * field;

  ASSERT_LT(arma::norm(sol), tol) << "Gradient Nullity Test failed for k = " << k;
}

TEST(GradientTests, Nullity)
{
  Real tol = 1e-10;
  for (int k : {2, 4, 6, 8})
  {
    run_nullity_test(k, tol);
  }
}

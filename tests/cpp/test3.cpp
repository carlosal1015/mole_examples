/**
 * Nullity test of Laplacian operator
 */
#include <gtest/gtest.h>
#include <mole/laplacian.h>
#include <mole/operators.h>

void run_nullity_test(int k, Real tol)
{
  int m = 2 * k + 1;
  Real dx = 1;

  Laplacian L(k, m, dx);
  arma::vec field(m + 2, arma::fill::ones);
  arma::vec sol = L * field;

  ASSERT_LT(arma::norm(sol), tol)
      << "Laplacian Nullity Test failed for k = " << k;
}

TEST(LaplacianTests, Nullity)
{
  Real tol = 1e-10;
  for (int k : {2, 4, 6}) {
    run_nullity_test(k, tol);
  }
}

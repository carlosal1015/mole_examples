/**
 * Poisson accuracy test
 */

#include <gtest/gtest.h>
#include <mole/laplacian.h>
#include <mole/operators.h>

void run_test(int k, arma::vec grid_sizes)
{
  Real west = 0; // Domain's limits
  Real east = 1;

  arma::vec errors(grid_sizes.size());

  for (int i = 0; i < grid_sizes.size(); ++i) {
    int m = grid_sizes(i);       // Number of cells
    Real dx = (east - west) / m; // Step length

    Laplacian L(k, m, dx);
    RobinBC BC(k, m, dx, 1, 1);
    L = L + BC;

    arma::vec grid(m + 2);
    grid(0) = west;
    grid(1) = west + dx / 2.0;
    for (int j = 2; j <= m; j++) {
      grid(j) = grid(j - 1) + dx;
    }
    grid(m + 1) = east;

    arma::vec U = arma::exp(grid);
    U(0) = 0;                   // West BC
    U(m + 1) = 2 * std::exp(1); // East BC

#ifdef EIGEN
    arma::vec computed_solution = Utils::spsolve_eigen(L, U);
#elif LAPACK
    arma::vec computed_solution = spsolve(L, U, "lapack"); // Will use LAPACK
#else
    arma::vec computed_solution = spsolve(L, U); // Will use SuperLU
#endif

    arma::vec analytical_solution = arma::exp(grid);
    errors(i) = arma::max(arma::abs(computed_solution - analytical_solution));
  }

  arma::vec order(errors.size() - 1);
  for (int i = 0; i < errors.size() - 1; ++i) {
    order(i) = std::log2(errors(i) / errors(i + 1));
    ASSERT_GE(order(i), k - 0.5) << "Poisson Test failed for k = " << k;
  }
}

TEST(PoissonTests, Accuracy)
{
  arma::vec grid_sizes = {20, 40};
  for (int k : {2, 4, 6}) {
    run_test(k, grid_sizes);
  }
}

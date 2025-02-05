/**
 * Poisson accuracy test
 */

#include <mole/operators.h>
#include <mole/laplacian.h>

void run_test(int k, arma::vec grid_sizes)
{
  Real west = 0; // Domain's limits
  Real east = 1;

  vec errors(grid_sizes.size());

  for (int i = 0; i < grid_sizes.size(); ++i)
  {
    int m = grid_sizes(i);       // Number of cells
    Real dx = (east - west) / m; // Step length

    Laplacian L(k, m, dx);

    // Impose Robin BC on laplacian operator
    RobinBC BC(k, m, dx, 1, 1);
    L = L + BC;

    // 1D Staggered grid
    arma::vec grid(m + 2);
    grid(0) = west;
    grid(1) = west + dx / 2.0;
    for (int j = 2; j <= m; j++)
    {
      grid(j) = grid(j - 1) + dx;
    }
    grid(m + 1) = east;

    // RHS
    vec U = arma::exp(grid);
    U(0) = 0;                   // West BC
    U(m + 1) = 2 * std::exp(1); // East BC

// Solve the system of linear equations
#ifdef EIGEN
    // Use Eigen only if SuperLU (faster) is not available
    vec computed_solution = Utils::spsolve_eigen(L, U);
#else
    vec computed_solution = arma::spsolve(L, U); // Will use SuperLU
#endif

    // Compute error
    arma::vec analytical_solution = arma::exp(grid);
    errors(i) = arma::max(arma::abs(computed_solution - analytical_solution));
  }

  // Compute order of accuracy
  arma::vec order(errors.size() - 1);
  for (int i = 0; i < errors.size() - 1; ++i)
  {
    order(i) = std::log2(errors(i) / errors(i + 1));

    if (order(i) - k < -0.5)
    {
      std::cout << "\033[1;31mTest FAILED for k = " << k << "!\033[0m\n";
      std::exit(1);
    }
  }
}

int main()
{
  arma::vec grid_sizes = {20, 40}; // Different grid sizes to test
  for (int k : {2, 4, 6})
    run_test(k, grid_sizes);

  std::cout << "\033[1;32mTest PASSED!\033[0m\n";

  return 0;
}

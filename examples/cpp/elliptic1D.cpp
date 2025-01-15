/**
 * This example uses MOLE to solve a 1D BVP
 */

#define ARMA_USE_HDF5
#include <cmath>
#include <iostream>
#include <mole/laplacian.h>
#include <mole/operators.h>
#include <mole/robinbc.h>

// using Real = double;

int main()
{
  int k = 6;             // Operators' order of accuracy
  Real a = 0;            // Left boundary
  Real b = 1;            // Right boundary
  int m = 2 * k + 1;     // Number of cells
  Real dx = (b - a) / m; // Step size

  // Get mimetic operators
  Laplacian L(k, m, dx);
  Real d = 1; // Dirichlet coefficient
  Real n = 1; // Neumann coefficient
  RobinBC BC(k, m, dx, d, n);
  L = L + BC;

  // 1D Staggered grid
  arma::vec grid(m + 2);
  grid(0) = a;
  grid(1) = a + dx / 2.0;
  int i;
  for (i = 2; i <= m; i++) {
    grid(i) = grid(i - 1) + dx;
  }
  grid(i) = b;

  // Build RHS for system of equations
  arma::vec rhs(m + 2);
  rhs = arma::exp(grid); // rhs(0) = 1
  rhs(0) = 0;
  rhs(m + 1) = 2 * std::exp(1); // rhs(1) = 2e

  // Solve the system of linear equations
#ifdef EIGEN
  // Use Eigen only if SuperLU (faster) is not available
  std::cout << "With Eigen" << std::endl;
  vec sol = Utils::spsolve_eigen(L, rhs);
#else
  std::cout << "With SuperLU" << std::endl;
  arma::vec sol = spsolve(L, rhs); // Will use SuperLU
#endif

  // Save grid
  grid.save(arma::hdf5_name("elliptic1d_grid.h5", "elliptic1d_grid"));
  // Save the solution
  sol.save(arma::hdf5_name("elliptic1d_solution.h5", "elliptic1d_solution"));
  // Print out the solution
  std::cout << sol;

  return 0;
}

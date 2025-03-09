/**
 * This example uses MOLE to solve the 1D Schrodinger equation
 */

#include <iostream>
#include <mole/laplacian.h>

int main()
{

  int k = 4;   // Operators' order of accuracy
  Real a = -5; // Left boundary
  Real b = 5;  // Right boundary
  int m = 500; // Number of cells
  vec grid = arma::linspace(a, b, m);
  Real dx = grid(1) - grid(0); // Step size

  // Get mimetic Laplacian operator
  Laplacian L(k, m - 2, dx);

  std::transform(grid.begin(), grid.end(), grid.begin(),
                 [](Real x) { return x * x; });

  arma::sp_mat V(m, m); // Potential energy operator
  V.diag(0) = grid;

  // Hamiltonian
  arma::sp_mat H = -0.5 * (arma::sp_mat)L + V;

  arma::cx_vec eigval;
  arma::eig_gen(eigval, (arma::mat)H); // Compute eigenvalues

  eigval = arma::sort(eigval);

  std::cout << "Energy levels = [ ";
  for (int i = 0; i < 4; ++i)
    std::cout << std::real(eigval(i) / eigval(0)) << ' ';
  std::cout << "]\n";

  return 0;
}

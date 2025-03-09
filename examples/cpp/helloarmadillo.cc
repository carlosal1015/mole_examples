#include <armadillo>
// #define ARMA_USE_SUPERLU 1
#include <iostream>

int main()
{
  // Create two matrices A and B
  arma::mat A(4, 5, arma::fill::randu);
  arma::mat B(4, 5, arma::fill::randu);

  // Multiply A * B
  std::cout << A * B.t() << std::endl;

  arma::sp_mat C = arma::sprandu<arma::sp_mat>(1000, 1000, 0.1);
  arma::vec b = arma::randu<arma::vec>(1000);
  arma::vec x;
  arma::spsolve(x, C, b, "lapack"); // solve one system

  unsigned short k = 2;
  unsigned short m = 2 * k + 1;
  double west = 0;
  double east = 1;
  arma::vec nodes = arma::linspace(west, east, 2 * m);

  std::cout << nodes << "\n";
  // arma::mat grid = arma::join_rows(0, nodes);

  arma::vec grid = arma::regspace(west, 0.01, east);
  std::cout << grid << "\n";

  return 0;
}

#include <armadillo>
#include <iostream>

int main()
{
  arma::mat A(4, 5, arma::fill::randu);
  arma::mat B(4, 5, arma::fill::randu);

  std::cout << A * B.t() << std::endl;

  unsigned short k = 2;
  unsigned short m = 2 * k + 1;
  double west = 0;
  double east = 1;
  arma::vec nodes = arma::linspace(west, east, 2 * m);

  std::cout << nodes << "\n";
  // arma::mat grid = arma::join_rows(0, nodes);

  return 0;
}

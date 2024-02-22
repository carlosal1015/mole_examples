#include <iostream>
#include <armadillo>

int main()
{
  arma::mat A(4, 5, arma::fill::randu);
  arma::mat B(4, 5, arma::fill::randu);

  std::cout << A * B.t() << std::endl;

  return 0;
}

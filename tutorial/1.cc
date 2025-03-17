#define ARMA_DONT_USE_WRAPPER
#include <armadillo>
#include <iostream>

int main()
{
  // Show Armadillo version
  std::cout << "Armadillo version: " << ARMA_VERSION_MAJOR << "."
            << ARMA_VERSION_MINOR << "." << ARMA_VERSION_PATCH << " "
            << ARMA_VERSION_NAME " ";

  int n = 5;
  int m = 4;

  std::cout
      // Vector of n entries
      << arma::vec(n)
      << "\n"
      // Vector of m entries of 2s
      << arma::vec(m).fill(2)
      << "\n"
      // Declare and fill a vector with random values from a uniform
      // distribution.
      << arma::vec(n).randu()
      << "\n"
      // Declare and fill a vector with the values 0.1, 0.2 and 0.3.
      << arma::vec("0.0 0.1 0.2");

  std::cout
      // Matrix of n times m entries
      << arma::mat(n, m)
      << "\n"
      // Matrix of n times m entries of 2s
      << arma::mat(n, m).fill(2.)
      << "\n"
      // Declare and fill a matrix with random values from a uniform
      // distribution
      << arma::mat(n, m).randn()
      << "\n"
      // Declare and fill a vector with the values 0.0, 0.1 and 0.2.
      << arma::mat("0.0 0.1 0.2 ; 1.0 1.1 1.2 ; 2.0 2.1 2.2");

  arma::mat A = arma::mat("0.0 0.1 0.2 ; 1.0 1.1 1.2 ; 2.0 2.1 2.2");
  arma::vec x = arma::vec("20. 10. 30.");
  arma::uvec x_sort_indices =
      arma::sort_index(x); // Get index ordering that sorts x.
  x = x(x_sort_indices);
  A = A.cols(x_sort_indices);

  // A.save(filename);
  // B = arma::mat();  // Initialize an arma::mat variable
  // B.load(filename); // Load content of arma::mat A stored earlier into
  // arma::mat B.

  return 0;
}

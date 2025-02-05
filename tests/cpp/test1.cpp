/**
 * Nullity test of Divergence operator
 */

#include <mole/divergence.h>
#include <mole/operators.h>

void run_nullity_test(int k, Real tol)
{
  int m = 2 * k + 1;
  Real dx = 1;

  Divergence D(k, m, dx);
  vec field(m + 1, fill::ones);

  arma::vec sol = D * field;
  std::cout << sol << "\n";

  if (norm(sol) > tol)
  {
    std::cout << "\033[1;31mTest FAILED!\033[0m\n";
    std::exit(1);
  }
}

int main()
{
  Real tol = 1e-10;

  for (int k : {2, 4, 6})
    run_nullity_test(k, tol);

  std::cout << "\033[1;32mTest PASSED!\033[0m\n";

  return 0;
}

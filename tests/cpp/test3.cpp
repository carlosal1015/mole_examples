/**
 * Nullity test of Laplacian operator
 */
#include <mole/operators.h>
#include <mole/laplacian.h>

void run_nullity_test(int k, Real tol)
{
  int m = 2 * k + 1;
  Real dx = 1;

  Laplacian L(k, m, dx);
  vec field(m + 2, fill::ones);

  vec sol = L * field;

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

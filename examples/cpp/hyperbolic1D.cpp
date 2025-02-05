/**
 * This example uses MOLE to solves the 1D Advection equation with periodic
 * boundary conditions
 */

#define ARMA_USE_HDF5
#include <mole/divergence.h>
#include <mole/operators.h>

int main()
{
  Real velocity = 1; // Velocity

  unsigned short k = 2;  // Operators' order of accuracy
  Real a = 0;            // Left boundary
  Real b = 1;            // Right boundary
  unsigned short m = 50; // Number of cells

  Real dx = (b - a) / m; // Step size

  double t0 = 0; // initial time
  double tf = 1; // final time

  double dt =
      tf /
      (std::ceil((3 * tf) /
                 (dx * dx))); // Von Neumann stability criterion for explicit
                              // scheme, if k > 2 then dt/dx^2<0.5.

  return 0;
}
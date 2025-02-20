/**
 * @file Schrodinger2D.cpp
 * @brief Solves a 2D Time Dependant Schrodinger's Equation using mimetic
 * methods (MOLE).
 *
 * Can be visualized as a surface using gnuplot by running the command:
 *
 *     ./Schrodinger2D | sed 1d | gnuplot -p -e "splot '<cat'"
 */

#include <iomanip>
#include <mole/mole.h>

int main()
{
  int p = 105; // Number of time steps for the simulation
  double Lxy = 1.0;
  int k = 2;           // Order of accuracy
  int m = 50;          // Grid points in x
  int n = 50;          // Grid points in y
  int nx = 2;          // Energy level in x
  int ny = 2;          // Energy level in y
  double dx = Lxy / m; // Step in x
  double dy = Lxy / n; // Step in y
  double dt = dx;      // Time step size

  // Define staggered grids
  arma::vec xgrid =
      arma::join_vert(arma::vec({0}), arma::linspace(dx / 2, Lxy - dx / 2, m),
                      arma::vec({Lxy}));
  arma::vec ygrid =
      arma::join_vert(arma::vec({0}), arma::linspace(dy / 2, Lxy - dy / 2, n),
                      arma::vec({Lxy}));

  // Initialize 2D staggered grid
  arma::mat X, Y;
  Utils utils;
  utils.meshgrid(xgrid, ygrid, X, Y);

  // Initialize Laplacian operator with Robin BC
  Laplacian L(k, m, n, dx, dy);
  RobinBC BC(k, m, 1, n, 1, 1, 0);
  L = L + BC;

  // Ensure the Laplacian is square
  int total_size =
      (m + 2) * (n + 2); // Total size for the grid including boundaries

  // Hamiltonian definition
  auto H = [&](const vec &x) {
    vec result = 0.5 * (L * x);
    return result;
  };

  // Define wave numbers
  auto kx = [&](int nx) { return nx * M_PI / Lxy; };
  auto ky = [&](int ny) { return ny * M_PI / Lxy; };

  double A = 2 / Lxy;

  // Initialize the wavefunction psi_old
  mat Psi_grid(m + 2, n + 2, fill::zeros);

  // Manually pad Psi_grid
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      Psi_grid(i, j) = A * sin(kx(nx) * X(i, j)) * sin(ky(ny) * Y(i, j));
    }
  }

  // Convert to column vector for compatibility
  vec psi_old = arma::vectorise(Psi_grid); // Convert to column vector
  // Create interpolators
  Interpol I(m, n, 0.5, 0.5);
  Interpol I2(true, m, n, 0.5, 0.5);

  I *= dt; // Scale by dt
  I2 *= 0.5 * dt;

  arma::vec v_old(2 * m * n + m + n, arma::fill::zeros); // Initialize v_old

  // Initialize Psi_re with zeros
  arma::mat Psi_re = arma::zeros<arma::mat>(m + 2, n + 2);

  try {
    // Time-stepping loop (Position Verlet)
    for (int t = 0; t <= p; ++t) {
      // Position Verlet algorithm: Update psi_old based on v_old
      psi_old = psi_old + I2 * v_old;

      // Calculate v_new using the Hamiltonian and psi_old
      vec v_new = v_old + I * H(psi_old);

      // Update psi_old based on v_new
      psi_old = psi_old + I2 * v_new;

      // Update Psi_re for output
      Psi_re = arma::reshape(psi_old, m + 2, n + 2);

      if (t == p) {
        std::cout << "Final Time Step " << t << ": X, Y, Psi" << std::endl;
        for (std::size_t i = 0; i < Psi_re.n_rows; ++i) {
          for (std::size_t j = 0; j < Psi_re.n_cols; ++j) {
            std::cout << std::fixed << std::setprecision(5) << X(i, j) << ", "
                      << Y(i, j) << ", " << Psi_re(i, j) << std::endl;
          }
        }
      }

      // Update variables for the next time step
      v_old = v_new;
    }
  }
  catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return -1;
  }

  std::cout << "Simulation complete." << std::endl;
  return 0;
}

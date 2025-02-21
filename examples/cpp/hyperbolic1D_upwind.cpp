#include <cmath>
// #include <chrono>
#include <iostream>
#include <mole/mole.h>

// using namespace std::chrono_literals;
constexpr double pi = 3.14159;

arma::sp_mat sidedNodalTemp(int m, double dx, const std::string &type)
{

  // Create a sparse matrix of size (m+1) x (m+1)
  arma::sp_mat S(m + 1, m + 1);
  if (type == "backward") {
    // Backward difference
    S.diag(-1) = -arma::ones<vec>(m);   // Sub-diagonal
    S.diag(0) = arma::ones<vec>(m + 1); // Main diagonal
    S(0, m - 1) = -1;                   // Wrap-around for periodic boundary
    S /= dx;
  }
  else if (type == "forward") {
    // Forward difference
    S.diag(0) = -arma::ones<vec>(m + 1); // Main diagonal
    S.diag(1) = arma::ones<vec>(m);      // Super-diagonal
    S(m, 1) = 1;                   // Wrap-around for periodic boundary
    S /= dx;
  }
  else { // "centered"
    // Centered difference
    S.diag(-1) = -arma::ones<vec>(m); // Sub-diagonal
    S.diag(1) = arma::ones<vec>(m);   // Super-diagonal
    S(0, m - 1) = -1;           // Wrap-around for periodic boundary
    S(m, 1) = 1;                // Wrap-around for periodic boundary
    S /= (2 * dx);
  }

  return S;
}

int main()
{
  double a = 1.0;    // Velocity
  double west = 0.0; // Domain's left limit
  double east = 1.0; // Domain's right limit

  int m = 20;                    // Number of cells
  double dx = (east - west) / m; // Grid spacing

  double t = 1.0;               // Simulation time
  double dt = dx / std::abs(a); // Time step based on CFL condition

  arma::sp_mat S = sidedNodalTemp(
      m, dx, (a > 0) ? "backward" : "forward"); // Use "forward" if a < 0

  arma::vec grid = arma::regspace(west, dx, east);
  arma::vec U = arma::sin(2 * pi * grid);

  S = arma::speye<arma::sp_mat>(S.n_rows, S.n_cols) - a * dt * S;

  int steps = t / dt;

  std::ofstream dataFile("results.dat");
  if (!dataFile) {
    std::cerr << "Error opening data file.\n";
    return 1;
  }

  // Write all time steps to a single data file
  for (int i = 1; i <= steps; ++i) {
    // Compute U^(n+1)
    U = S * U;

    // Store the data with an empty line between time steps for indexing in
    // GNUplot
    for (size_t j = 0; j < grid.size(); ++j) {
      dataFile << grid[j] << " " << U[j] << " "
               << std::sin(2 * pi * (grid[j] - a * i * dt)) << "\n";
    }
    dataFile << "\n\n"; // Separate time steps
  }
  dataFile.close();

  // Create the GNUplot script
  std::ofstream scriptFile("gp_script");
  if (!scriptFile) {
    std::cerr << "Error creating GNUplot script.\n";
    return 1;
  }

  scriptFile << "set terminal qt\n";
  scriptFile << "set xlabel 'x'\n";
  scriptFile << "set ylabel 'u(x,t)'\n";
  scriptFile << "set xrange [" << west << ":" << east << "]\n";
  scriptFile << "set yrange [-1.5:1.5]\n";
  scriptFile << "set grid\n";
  scriptFile << "do for [i=0:" << steps - 1 << "] {\n";
  scriptFile
      << "    plot 'results.dat' index i using 1:2 with linespoints title "
         "sprintf('t = %.2f', i*"
      << dt << " + " << dt
      << "), "
         "'results.dat' index i using 1:3 with lines title 'Exact Solution'\n";
  scriptFile << "    pause 0.1\n";
  scriptFile << "}\n";

  scriptFile.close();

  // Run GNUplot with the script
  std::system("gnuplot -persistent gp_script");
}
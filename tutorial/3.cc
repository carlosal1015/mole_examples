// #define EIGEN_USE_MKL_ALL
#include <eigen3/Eigen/Sparse>
#include <eigen3/Eigen/SparseLU>
#include <iostream>
#include <vector>

void insertCoefficient(int id, int i, int j, double w, std::vector<Eigen::Triplet<double>> &coeffs,
                       Eigen::VectorXd &b, const Eigen::VectorXd &boundary)
{
    int n = int(boundary.size());
    int id1 = i + j * n;

    if (i == -1 || i == n)
        b(id) -= w * boundary(j); // constrained coefficient
    else if (j == -1 || j == n)
        b(id) -= w * boundary(i); // constrained coefficient
    else
        coeffs.push_back(Eigen::Triplet<double>(id, id1, w)); // unknown coefficient
}

void buildProblem(std::vector<Eigen::Triplet<double>> &coefficients, Eigen::VectorXd &b, int n)
{
    b.setZero();
    Eigen::ArrayXd boundary = Eigen::ArrayXd::LinSpaced(n, 0, M_PI).sin().pow(2);
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < n; ++i)
        {
            int id = i + j * n;
            insertCoefficient(id, i - 1, j, -1, coefficients, b, boundary);
            insertCoefficient(id, i + 1, j, -1, coefficients, b, boundary);
            insertCoefficient(id, i, j - 1, -1, coefficients, b, boundary);
            insertCoefficient(id, i, j + 1, -1, coefficients, b, boundary);
            insertCoefficient(id, i, j, 4, coefficients, b, boundary);
        }
    }
}

int main()
{
    std::cout << "Eigen version: "
              << EIGEN_WORLD_VERSION
              << "."
              << EIGEN_MAJOR_VERSION
              << "."
              << EIGEN_MINOR_VERSION
              << "\n";

    Eigen::MatrixXd M(2, 2);
    std::cout << M << "\n";

    int n = 300; // size of the image
    int m = n * n;
    std::vector<Eigen::Triplet<double>> coefficients;
    Eigen::VectorXd b(m);
    buildProblem(coefficients, b, n);

    Eigen::SparseMatrix<double> A(m, m);
    A.setFromTriplets(coefficients.begin(), coefficients.end());
    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> chol(A); // performs a Cholesky factorization of A
    Eigen::VectorXd x = chol.solve(b);                              // use the factorization to solve for the given right hand side
    // Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
    // solver.compute(A);

    return 0;
}
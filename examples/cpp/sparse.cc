// https://stackoverflow.com/a/63587324
#include <Eigen/SparseLU>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>
#include <vector>

using namespace Eigen;

int main()
{
    SparseLU<SparseMatrix<double>> solver;
    SparseMatrix<double> A(9, 9);
    typedef Triplet<double> T;
    std::vector<T> triplet;
    VectorXd B(9);

    for (int i = 0; i < 4; i++)
    {
        triplet.push_back(T(i, i, 1));
        triplet.push_back(T(i + 5, i + 5, 1));
    }

    triplet.push_back(T(4, 1, -1));
    triplet.push_back(T(4, 3, -1));
    triplet.push_back(T(4, 5, -1));
    triplet.push_back(T(4, 7, -1));
    triplet.push_back(T(4, 4, 4));

    A.setFromTriplets(triplet.begin(), triplet.end());
    B << 0, 0, 0, 0, 0.387049, 0, 0, 0, 0;

    solver.compute(A);
    VectorXd x = solver.solve(B);

    std::cout << "A\n"
              << A << "\n";
    std::cout << "B\n"
              << B << "\n";
    std::cout << "x\n"
              << x << "\n";

    return 0;
}
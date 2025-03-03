
#include <carma>
#include <armadillo>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/pytypes.h>

namespace py = pybind11;

py::tuple ols(arma::mat &X, arma::colvec &y)
{
    // We borrow the data underlying the numpy arrays
    int n = X.n_rows, k = X.n_cols;

    arma::colvec coeffs = arma::solve(X, y);
    arma::colvec resid = y - X * coeffs;

    double sig2 = arma::as_scalar(arma::trans(resid) * resid / (n - k));
    arma::colvec std_errs = arma::sqrt(sig2 * arma::diagvec(arma::inv(arma::trans(X) * X)));

    // We take ownership of the memory from the armadillo objects and
    // return to python as a tuple containing two Numpy arrays.
    return py::make_tuple(
        carma::col_to_arr(coeffs),
        carma::col_to_arr(std_errs));
}

// adapted from https://gallery.rcpp.org/articles/fast-linear-model-with-armadillo/
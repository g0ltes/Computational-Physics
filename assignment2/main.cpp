#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include "armadillo"

const double PI = 3.14159;

int main() {

    int       i, j;
    int       N, duration;
    double    dx, dt, alpha; 
    double    sigma, den, a;        // For the initial Gaussian function
    arma::vec U, x;
    arma::mat I, A, B, D, M;
    
    duration = 50;                  // Milliseconds

    N     = 201;                    // Number of points
    dx    = 0.01;                   // ERROR ERROR HARDCODING
    dt    = 0.001;                  // Time step
    alpha = dt / (std::pow(dx, 2));

    U.zeros(N);
    I.eye(N, N);
    A.zeros(N, N);
    B.zeros(N, N);
    D.zeros(N, N);
    M.zeros(N, N);

    /* Populate the initial value vector U_0. U_0 is a Dirac delta function
     * centered around x = 0, here approximated by a "sharp" Gauss function,
     * U_0 = U(x, 0) = 1 / sqrt(2*PI)*sigma * exp(-(x^2/2*sigma^2)).
     * The sigma is chosen to make the FWHM = 0.1. */
    sigma = 0.042466;     
    den   = 1 / (2 * std::pow(sigma, 2));
    a     = 1 / (sigma * std::sqrt(2 * PI));

    x = arma::linspace<arma::vec>(-1, 1, N);

    U = a * arma::exp(-den * arma::pow(x, 2));

    U.save("U0.txt", arma::raw_ascii);

    /* Populate the matrices */

    D(0, 0) = 2;

    for (i = 1; i < N; i++) {
        D(i, i)   =  2;
        D(i-1, i) = -1;
        D(i, i-1) = -1;
    }

    /* Compute the matrix A, which is the inverse of the matrix in front
     * of the U_n vector. This is only valid for diffusion constant D = 1. */
    A = arma::inv(2*I + alpha*D);
    B = 2*I - alpha*D;
    M = A * B;

    std::stringstream ss;     // For the filename when saving results

    for (i = 0; i < duration; i++) {
        U = A * U;
        if ((i == 1) || (i == 5) || (i == 10)) {
            ss << "U" << i << ".txt";
            U.save(ss.str(), arma::raw_ascii);
            ss.str(std::string());                  // Clear stringstream
        }
    } // End for

    return 0;
}

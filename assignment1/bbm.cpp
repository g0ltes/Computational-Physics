#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <fstream>
#include <ctime>
using namespace std;

/* Program constants */
const double epsilon = numeric_limits<double>::min();
const double twoPi = 2.0 * 3.14159265358979323846;

/* Physical constants */
const double eta = 1e-3;
const double kbT = 26e-3;
const double dU = 1 * kbT;
const double alpha = 0.2;
const double L = 20e-6;
//const double dx = 1e-9;
const double dt = 1e-3;
const double D = kbT / dU;
const int T = 500;
//double gamma;

/* Physical variables */
double x;
double t;

/* Tunable parameters */
double tau;
double r;

/* Switch the flashing signal on/off */
bool flashing;

int flashingSignal(const double t);
double potential(const double x, const double t);
double force(const double x, const double t);
double gaussianRNG(double mu, double sigma);
void euler(double &x, const double dt);
void initRand();

int main(int argc, char* argv[]) {

    if (argc == 1) {
        r = 12e-9;
        tau = 0.01;
        flashing = false;
        cout << "Using default parameters: r = " << r << ", tau = "
             << tau << ", flashing = " << flashing << ".\n";
    } else if (argc == 4) {
        r = atof(argv[1]);
        tau = atof(argv[2]);
        flashing = atoi(argv[3]);
    } else {
        cout << "Need exactly 0 or 3 arguments!\n";
        exit(1);
    }

    int i;
    ofstream out;
    out.open("trajectory.txt");

    t = 0;
    x = 0;
    initRand();

    out << t << "\t" << x << endl;
    for (i = 0; i < T; i++) {
        t += dt;
        euler(x, t);
        out << t << "\t" << x << endl;
    }

    out.close();
    cout << "Done.\n";
    return 0;
}

// Uses cmath
int flashingSignal(const double t) {
    if ((t-floor(t) < 0.75*tau) && (flashing))
        return 0;
    else
        return 1;
}

// Uses cmath, flashingSignal
double potential(const double x, const double t) {
    double z = x - floor(x);
    if (z < alpha)
        return (z/alpha) * flashingSignal(t);
    else
        return ((1-z)/(1-alpha)) * flashingSignal(t);
}

// Uses cmath, flashingSignal
double force(const double x, const double t) {
    double z = x - floor(x);
    if (z < alpha)
        return (1/alpha) * flashingSignal(t);
    else
        return (-1/(1-alpha)) * flashingSignal(t);
}

// Uses cstdlib, cmath, limits
double gaussianRNG(double mu, double sigma) {
    double z0, z1, u1, u2;

    do {
        u1 = rand() * (1.0/RAND_MAX);
        u2 = rand() * (1.0/RAND_MAX);
    } while (u1 <= epsilon);

    z0 = sqrt(-2.0 * log(u1)) * cos(twoPi * u2);
    z1 = sqrt(-2.0 * log(u1)) * sin(twoPi * u2);

    return z0*sigma + mu;
}

// Uses cmath, force, gaussianRNG
void euler(double &x, const double t) {
    x = x - force(x, t)*dt + sqrt(2*D*dt)*gaussianRNG(0, 1);
}

// Uses cstdlib, ctime, fstream
void initRand() {
    int seed;
    ofstream seedStream;

    seed = time(NULL);
    srand(seed);

    seedStream.open("seed_lastrun.txt");
    seedStream << "Seed last run: " << seed << endl;
    seedStream.close();
}

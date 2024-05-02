#ifndef MAIN_BUTCHERTABLE_HH
#define MAIN_BUTCHERTABLE_HH

#include "vector"

/**
 * @brief Represents a Butcher table used in the Universal Runge-Kutta stepper.
 * 
 * The Butcher table consists of coefficients used in the Runge-Kutta method for numerical integration.
 * It contains vectors `c`, `a`, and `b` which represent the coefficients for the method.
 * 
 * - `c` is a vector of length `s`, where `s` is the number of stages in the Runge-Kutta method.
 *   It represents the coefficients for the time steps.
 * 
 * - `a` is a 2D vector of size `s x s`, where `s` is the number of stages.
 *   It represents the coefficients for the intermediate steps.
 * 
 * - `b` is a vector of length `s`.
 *   It represents the coefficients for the final step.
 */
struct ButcherTable {
    std::vector<double> c;
    std::vector<std::vector<double>> a;
    std::vector<double> b;

};
#endif //MAIN_BUTCHERTABLE_HH

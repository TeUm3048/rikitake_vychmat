#ifndef MAIN_ADAMSBASHFORTH_HH
#define MAIN_ADAMSBASHFORTH_HH

#include "../IMultistepper.hh"
#include "../IOneStepper.hh"
#include "../System.hh"
#include <boost/circular_buffer.hpp>

/**
 * @brief Implements the Adams-Bashforth method for numerical integration of ordinary differential equations.
 *
 * This class provides a multi-step integration scheme for solving systems of ordinary differential equations.
 * It uses the Adams-Bashforth method, which is an explicit method that uses previous steps to estimate the next step.
 *
 * @tparam T The type of the state variables.
 * @tparam P The type of the parameters.
 */
template<typename T, typename P>
class AdamsBashforth : public IMultiStepper<T> {
public:
    /**
     * @brief Constructs an AdamsBashforth object.
     *
     * @param system1 The system of ordinary differential equations to be integrated.
     * @param oneStepper_ The one-step integration scheme to be used for the first N steps.
     * @param numOneStepSteps The number of steps to use the one-step integration scheme before switching to the multi-step scheme.
     */
    AdamsBashforth(System<T, P> &system1, IOneStepper<T> &oneStepper_, int N_)
            : oneStepper(oneStepper_), system(system1),
              dx_dt_circular_buffer(N_),
              N(N_) {};

    /**
     * @brief Performs a single integration step.
     *
     * This method calculates the next state of the system by using the Adams-Bashforth method.
     * If the number of steps performed is less than N, it uses the one-step integration scheme.
     * Otherwise, it uses the multi-step scheme.
     */
    inline void doStep() override {
        if (run < N) {
            oneStepper.doStep();
            dx_dt_circular_buffer.push_back(system.dx_dt());
            run++;
            return;
        }
        auto [c, corrector] = correctors[N - 1];
        // x_{n+1} =
        // x_n + h\sum^{k}_{i=0} {u_{-i}f(x_{n-i},x_{n-i})}$
        T fix;
        dx_dt_circular_buffer.push_back(system.dx_dt());
        for (int i = 0; i < N; ++i) {
            fix += corrector[i] * dx_dt_circular_buffer[i];
        }
        system.state += system.step / c * fix;
        system.time += system.step;
    };

    /**
     * @brief Gets the current state of the system.
     *
     * @return The current state of the system.
     */
    inline T getState() const override {
        return system.state;
    };

private:
    // The number of steps performed so far.F
    std::size_t run = 0;
    // The system of ordinary differential equations to be integrated.
    System<T, P> &system;
    // The one-step integration scheme to be used for the first N steps.
    IOneStepper<T> &oneStepper;
    // Circular buffer to store the derivatives of the state variables.
    boost::circular_buffer<T> dx_dt_circular_buffer;
    // The number of steps to use the one-step integration scheme before switching to the multi-step scheme.
    int N;
    // Coefficients for the multi-step scheme.
    std::vector<std::tuple<double, std::vector<double>>> correctors = {
            {1,      {1}},
            {2,      {-1,     3}},
            {12,     {5,      -16,     23}},
            {24,     {-9,     37,      -59,     55}},
            {720,    {251,    -1274,   2616,    -2774,   1901}},
            {1440,   {-475,   2877,    -7298,   9982,    -7923,    4277}},
            {60480,  {19825,  -115732, 336918,  -561717, 587482,   -392835, 173927}},
            {120960, {-36799, 220043,  -662724, 1062079, -1154077, 806207,  -358163, 98957}},
    };
};

#endif // MAIN_ADAMSBASHFORTH_HH

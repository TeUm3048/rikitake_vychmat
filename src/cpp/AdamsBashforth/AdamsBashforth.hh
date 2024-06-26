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
    AdamsBashforth(System<T, P> &system1, IOneStepper<T> &oneStepper_,
                   size_t N_) : system(system1),
                                oneStepper(oneStepper_),
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
        // One step integration scheme
        if (run < N) {
            dx_dt_circular_buffer.push_back(system.dx_dt());
            if (run != N - 1) {
                auto s = system.step;
                system.step = system.step / m;

                for (int i = 0; i < m; ++i) {
                    oneStepper.doStep();
                }

                system.step = s;
            }
            run++;
            return;
        }

        // Multi-step integration scheme
        
        auto [c, corrector] = correctors[N - 1];
        T fix;
        for (size_t i = 0; i < N; ++i) {
            auto d = dx_dt_circular_buffer[i];
            fix += corrector[i] * d;
        }
        system.state += system.step / c * fix;
        system.time += system.step;
        dx_dt_circular_buffer.push_back(system.dx_dt());
    };

    inline void doSimplifiedStep() override {
        oneStepper.doSimplifiedStep();
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
    // The system of ordinary differential equations to be integrated.
    System<T, P> &system;
    // The one-step integration scheme to be used for the first N steps.
    IOneStepper<T> &oneStepper;
    // Circular buffer to store the derivatives of the state variables.
    boost::circular_buffer<T> dx_dt_circular_buffer;
    // The number of steps to use the one-step integration scheme before switching to the multi-step scheme.
    std::size_t N;
    // The number of steps performed so far.
    std::size_t run = 0;
    // Coefficients for the multi-step scheme.
    std::vector<std::tuple<double, std::vector<double>>> correctors = {
            {1.,      {1.}},
            {2.,      {-1.,     3.}},
            {12.,     {5.,      -16.,     23.}},
            {24.,     {-9.,     37.,      -59.,     55.}},
            {720.,    {251.,    -1274.,   2616.,    -2774.,   1901.}},
            {1440.,   {-475.,   2877.,    -7298.,   9982.,    -7923.,    4277.}},
            {60480.,  {19825.,  -115732., 336918.,  -561717., 587482.,   -392835., 173927.}},
            {120960., {-36799., 295767.,  -1041723., 2102243., -2664477., 2183877.,  -1152169., 434241.}},
    };
    // The number to divide the number of one-step integration scheme into smaller steps.
    int m = 2;

};

#endif // MAIN_ADAMSBASHFORTH_HH

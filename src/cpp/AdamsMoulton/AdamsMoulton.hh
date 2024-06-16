#ifndef MAIN_ADAMSMOULTON_HH
#define MAIN_ADAMSMOULTON_HH


#include "../IMultistepper.hh"
#include "../IOneStepper.hh"
#include "../System.hh"
#include "./last_backward_difference.hh"
#include <boost/circular_buffer.hpp>


/**
 * @class AdamsMoulton
 * @brief Represents a multi-step integration scheme using the Adams-Moulton method.
 * @tparam T The type of the state variables.
 * @tparam P The type of the parameters.
 */
template<typename T, typename P>
class AdamsMoulton : public IMultiStepper<T> {
public:
    /**
     * @brief Constructs an AdamsMoulton object.
     *
     * @param system1 The system of ordinary differential equations to be integrated.
     * @param oneStepper_ The one-step integration scheme to be used for the first N steps.
     * @param numOneStepSteps The number of steps to use the one-step integration scheme before switching to the multi-step scheme.
     * @param numCorrSteps_ The number of correction steps to be performed after the prediction step.
     */
    AdamsMoulton(System<T, P> &system1, IOneStepper<T> &oneStepper_,
                 size_t numOneStepSteps, size_t numCorrSteps_)
            : system(system1),
              oneStepper(oneStepper_),
              dx_dt_circular_buffer(numOneStepSteps),
              N(numOneStepSteps),
              numCorrSteps(numCorrSteps_) {};

    /**
     * @brief Performs a single integration step.
     *
     * This method calculates the next state of the system by using the Adams-Bashforth method.
     * If the number of steps performed is less than N, it uses the one-step integration scheme.
     * Otherwise, it uses the multi-step scheme.
     */
    inline void doStep() override {
        if (run < N ) {
            dx_dt_circular_buffer.push_back(system.dx_dt());
            double s = system.step;
            int n = 2;
            system.step = system.step / static_cast<double>(n);
            for (int i = 0; i < n; ++i) {
                oneStepper.doStep();
            }
            system.step = s;
            run++;
            return;
        }
        auto [c, corrector, gamma] = correctors[N - 1];

        // Prediction
        // x_{n+1} =
        // x_n + h\sum^{k}_{i=0} {u_{-i}f(x_{n-i},x_{n-i})}$
        T x_next;
        for (size_t i = 0; i < N; ++i) {
            x_next += corrector[i] * dx_dt_circular_buffer[i];
        }
        x_next = system.state + system.step / c * x_next;
//       for (size_t i = 0; i < N; ++i) {
//           auto d = dx_dt_circular_buffer[i];
//           std::cout << d.x << std::endl;
//       }
//       std::cout << std::endl;

        T dx_dt_next = system.dx_dt_(x_next, system.params);
        dx_dt_circular_buffer.push_back(dx_dt_next);
//        for (size_t i = 0; i < N; ++i) {
//            auto d = dx_dt_circular_buffer[i];
//            std::cout << d.x << std::endl;
//        }
//        std::cout << std::endl;
        // EC * N
        for (size_t i = 0; i < numCorrSteps; ++i) {
            // Evaluation
            T dx_dt_next = system.dx_dt_(x_next, system.params);
            dx_dt_circular_buffer.pop_back();
            dx_dt_circular_buffer.push_back(dx_dt_next);

//            for (size_t i = 0; i < N; ++i) {
//                auto d = dx_dt_circular_buffer[i];
//                std::cout << d.x << std::endl;
//            }
//            std::cout << std::endl;

            // Correction
            x_next += system.step * gamma / corrector[N-1] *
                      last_backward_difference(
                              dx_dt_circular_buffer.begin(),
                              dx_dt_circular_buffer.end());
        }

        system.state = x_next;
        system.time += system.step;
        // std::cout << system.time << ',' << system.state.x << std::endl;
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
    size_t N;
    // The number of steps performed so far.
    size_t run = 0;
    // The number of correction steps to be performed after the prediction step.
    size_t numCorrSteps;
    // Coefficients for the multi-step scheme.
    std::vector<std::tuple<double, std::vector<double>, double>> correctors = {
            {1,      {1},                                                                             1},
            {2,      {-1,     3},                                                                     -1},
            {12,     {5,      -16,     23}, -1},
            {24, {-9, 37, -59,                    55}, 1},
            {720, {251, -1274, 2616, -2774,                 1901}, -19},
            {1440, {-475, 2877, -7298, 9982, -7923,                    4277},                         27},
            {60480,  {19825,  -115732, 336918,    -561717,  587482,    -392835,  173927},             -863},
            {120960, {-36799, 295767,  -1041723., 2102243., -2664477., 2183877., -1152169., 434241.}, 1375},
    };
};


#endif //MAIN_ADAMSMOULTON_HH

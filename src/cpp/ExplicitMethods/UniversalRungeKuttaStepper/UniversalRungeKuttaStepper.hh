#ifndef MAIN_UNIVERSALRUNGEKUTTASTEPPER_HH
#define MAIN_UNIVERSALRUNGEKUTTASTEPPER_HH

#include "../../IOneStepper.hh"
#include "ButcherTable.hh"
#include "../../System.hh"

/**
 * @brief A class representing a universal Runge-Kutta stepper.
 * 
 * This class implements the IOneStepper interface and provides a generic implementation of a Runge-Kutta stepper.
 * It performs numerical integration of a system of ordinary differential equations using the Runge-Kutta method.
 * 
 * @tparam T The type of the state variables.
 * @tparam P The type of the parameters.
 */
template<typename T, typename P>
class UniversalRungeKuttaStepper : public IOneStepper<T> {
public:
    /**
     * @brief Constructs a UniversalRungeKuttaStepper object.
     * 
     * @param butcherTable1 The Butcher table containing the coefficients for the Runge-Kutta method.
     * @param system1 The system of ordinary differential equations to be integrated.
     */
    UniversalRungeKuttaStepper(ButcherTable butcherTable1,
                               System<T, P> &system1)
            : butcherTable(
            butcherTable1), stages(butcherTable1.b.size()), system(system1) {};

    /**
     * @brief Performs a single integration step using the Runge-Kutta method.
     * 
     * This function updates the state of the system by performing a single integration step using the Runge-Kutta method.
     * It calculates the intermediate stages and the final state using the coefficients from the Butcher table.
     */
    inline
    void doStep() override {
        std::vector<T> k(stages);

        for (std::size_t i = 0; i < stages; ++i) {
            T sum = T();
            for (std::size_t j = 0; j < i; ++j) {
                sum += butcherTable.a[i][j] * k[j];
            }
            k[i] = system.dx_dt_(system.state + system.step * sum,
                                 system.params);
        }

        // $x(t+h) = x(t) + \sum_i{b_i k_i}$
        for (std::size_t i = 0; i < stages; ++i) {
            system.state += system.step * butcherTable.b[i] * k[i];
        }

        system.time += system.step;
    };

    /**
     * @brief Returns the current state of the system.
     * 
     * @return The current state of the system.
     */
    inline
    T getState() const override {
        return system.state;
    };

private:
    ButcherTable butcherTable;  // The Butcher table containing the coefficients for the Runge-Kutta method.
    std::size_t stages;  // The number of stages in the Runge-Kutta method.
    System<T, P> &system;  // The system of ordinary differential equations to be integrated.
};

#endif // MAIN_UNIVERSALRUNGEKUTTASTEPPER_HH

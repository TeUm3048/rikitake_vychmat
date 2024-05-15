#ifndef MAIN_RK4_HH
#define MAIN_RK4_HH

#include "UniversalRungeKuttaStepper/UniversalRungeKuttaStepper.hh"

/**
 * @brief The RK4 class represents the fourth-order Runge-Kutta method.
 *
 * This class provides the Butcher table for the RK4 method, which is used for numerical integration of ordinary differential equations.
 * The Butcher table consists of the coefficients used in the RK4 method.
 *
 * @tparam T The type of the state vector.
 * @tparam P The type of the function that defines the derivative of the state vector.
 */
template<typename T, typename P>
class RK4 : public UniversalRungeKuttaStepper<T, P> {
public:
    /**
     * @brief Constructs an RK4 object with the given system.
     *
     * @param system1 The system object that defines the derivative of the state vector.
     */
    explicit RK4(System<T, P> &system1) : UniversalRungeKuttaStepper<T, P>(
            butcherTable,
            system1) {
    }

private:
    /**
     * @brief The Butcher table for the RK4 method.
     *
     * The Butcher table consists of the coefficients used in the RK4 method.
     */
    static ButcherTable butcherTable;
};

template<typename T, typename P>
ButcherTable RK4<T, P>::butcherTable = ButcherTable{
        {0,       0,       0,       0},
        {
         {0.},
                  {0.5, 0},
                           {0., 0.5, 0.},
                                    {0., 0., 1., 0.},
        },
        {1. / 6., 1. / 3., 1. / 3., 1. / 6.},
};

#endif // MAIN_RK4_HH



#ifndef MAIN_DOPRI8_HH
#define MAIN_DOPRI8_HH

#include "UniversalRungeKuttaStepper/UniversalRungeKuttaStepper.hh"

/**
 * @class DOPRI8
 * @brief A class that represents the DOPRI8 method for solving ordinary differential equations.
 *
 * The DOPRI8 class is a subclass of UniversalRungeKuttaStepper and implements the DOPRI8 method
 * for solving ordinary differential equations. It uses a Butcher table to store the coefficients
 * used in the method.
 *
 * @tparam T The type of the state vector.
 * @tparam P The type of the parameters.
 */
template<typename T, typename P>
class DOPRI8 : public UniversalRungeKuttaStepper<T, P> {
public:
    /**
     * @brief Constructs a DOPRI8 object with the given system.
     *
     * @param system1 The system object that defines the derivative of the state vector.
     */
    explicit DOPRI8(System<T, P> &system1) : UniversalRungeKuttaStepper<T, P>(
            butcherTable, system1) {
    }

private:
    /**
     * @brief The Butcher table for the DOPRI8 method.
     *
     * The Butcher table consists of the coefficients used in the DOPRI8 method.
     */
    static ButcherTable butcherTable;
};

template<typename T, typename P>
ButcherTable DOPRI8<T, P>::butcherTable = ButcherTable{
        {0.},
        {
         {0.},
                {1. / 18.},
                {1. / 48., 1. / 16.},
                {1. / 32., 0., 3. / 32.},
                {5. / 16., 0., -75. / 64., 75. / 64.},
                {3. / 80., 0., 0., 3. / 16., 3. / 20.},
                {29443841. / 614563906., 0., 0., 77736538. / 692538347.,
                        -28693883. / 1125000000., 23124283. / 1800000000.},
                {16016141. / 946692911., 0., 0., 61564180. / 158732637.,
                        22789713. / 633445777., 545815736. / 2771057229.,
                        -180193667. / 1043307555.},
                {39632708. / 573591083., 0., 0., -433636366. / 683701615.,
                        -421739975. / 2616292301., 100302831. / 723423059.,
                        790204164. / 839813087., 800635310. / 3783071287.},
                {246121993. / 1340847787., 0., 0., -37695042795. / 15268766246.,
                        -309121744. / 1061227803., -12992083. / 490766935.,
                        6005943493. / 2108947869., 393006217. / 1396673457.,
                        123872331. / 1001029789.},
                {-1028468189. / 846180014., 0., 0., 8478235783. / 508512852.,
                        1311729495. / 1432422823., -10304129995. / 1701304382.,
                        -48777925059. / 3047939560., 15336726248. / 1032824649.,
                        -45442868181. / 3398467696., 3065993473. / 597172653.},
                {185892177. / 718116043., 0., 0., -3185094517. / 667107341.,
                        -477755414. / 1098053517., -703635378. / 230739211.,
                        5731566787. / 1027545527., 5232866602. / 850066563.,
                        -4093664535. / 808688257., 3962137247. / 1805957418.,
                        65686358. / 487910083.},
                {403863854. / 491063109., 0., 0., -5068492393. / 434740067.,
                        -411421997. / 543043805., 652783627. / 914296604.,
                        11173962825. / 925320556., -13158990841. / 6184727034.,
                        3936647629. / 1978049680., -160528059. / 685178525.,
                        248638103. / 1413531060., 0.},

        },
        {{14005451. / 335480064., 0., 0., 0., 0., -59238493. / 1068277825.,
                 181606767. / 758867731., 561292985. / 797845732.,
                 -1041891430. / 1371343529., 760417239. / 1151165299.,
                 118820643. / 751138087., -528747749. / 2220607170., 1. / 4.}}};

#endif // MAIN_DOPRI8_HH

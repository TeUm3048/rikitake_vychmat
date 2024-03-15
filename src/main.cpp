#include "calc_model.h"
#include "integrate_methods.h"
#include "UniversalRungeKutta.h"
#include "explicit_methods/ForwardEuler.h"
#include "explicit_methods/Midpoint.h"
#include "explicit_methods/RugleKutta4.h"
#include "explicit_methods/DOPRI8.h"
#include <fstream>

int
main() {
    double k = 2;
    double k1 = 2. / k;
    double nu = 10;
    State state(k, k1, nu * k * k);

    Parametrs params{nu, nu * (k * k - k1 * k1)};

//    calc_model(state, 1000, 0.1, f,
//               midpoint<State, Parametrs>, params);

//    std::vector<std::vector<double>> butcher_table = {{0.},
//                                                      {0.5, 0.},
//                                                      {0.,  1.}};
//    UniversalRungeKutta<State, Parametrs> rk(butcher_table);
//    calc_model(state, 1000, 0.1, f, rk, params);
    RungeKutta4<State, Parametrs> rungeKutta4;
    Midpoint<State, Parametrs> midpoint1;
    DOPRI8<State, Parametrs> dopri8;
    {
        std::ofstream rk4_data("rk4.data", std::ios::binary);
        calc_model(state, 1000, 0.01, f, midpoint1, params, rk4_data);
    }
    {
        std::ofstream dopri8_data("dopri8.data", std::ios::binary);
        calc_model(state, 1000, 0.01, f, rungeKutta4, params, dopri8_data);
    }

    return 0;
}
#include <iostream>
#include <iomanip>
#include "RikitakeModel/dx_dt.hh"
#include "ExplicitMethods/RK4.hh"
#include "ExplicitMethods/DOPRI8.hh"
#include "AdamsBashforth/AdamsBashforth.hh"

int
main() {
    double k = 2.;
    double k1 = 2. / k;
    double nu = 1.;
//    State state(1.66124939e+00, 2.37450056e+00, 2.46131135e+01);
//    State state(3.49181352e-01,   -1.65340490e-01,    3.62014887e+00);
    State state(k, k1, nu * k * k);
    Parametrs params{nu, nu * (k * k - k1 * k1)};

    System<State, Parametrs> system = {state, params, 0.05, 0, dx_dt};

    RK4<State, Parametrs> rk4(system);
    DOPRI8<State, Parametrs> dopri8(system);
    AdamsBashforth<State, Parametrs> adamsBashforth(system, rk4, 5);
    int width = 18;
    std::cout << std::setprecision(8) << std::scientific;
    std::cout << std::setw(4) << "id" << "\t"
              << std::setw(width) << "time" << "\t"
              << std::setw(width) << "x" << "\t"
              << std::setw(width) << "y" << "\t"
              << std::setw(width) << "z" << std::endl;

    for (int i = 0; i < 200; ++i) {
        std::cout << std::setw(4) << i << "\t"
                  << std::setw(width) << system.time << "\t"
                  << std::setw(width) << system.state.x << "\t"
                  << std::setw(width) << system.state.y << "\t"
                  << std::setw(width) << system.state.z << std::endl;
        adamsBashforth.doStep();
    }

    std::cout << std::setw(4) << "N" << "\t"
              << std::setw(width) << system.time << "\t"
              << std::setw(width) << system.state.x << "\t"
              << std::setw(width) << system.state.y << "\t"
              << std::setw(width) << system.state.z << std::endl;


}

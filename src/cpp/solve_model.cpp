#include <iostream>
#include <iomanip>
#include <memory>

#include "solve_model.hh"


void solve_model(ConfigModel &config) {


    double k = 2.;
    double k1 = 2. / k;
    double nu = 1.;

    std::string sep = ",";
//    State state(1.66124939e+00, 2.37450056e+00, 2.46131135e+01);
//    State state(3.49181352e-01,   -1.65340490e-01,    3.62014887e+00);
    State state(k, k1, nu * k * k);
    Parametrs params{nu, nu * (k * k - k1 * k1)};

    System<State, Parametrs> system = {state, params, config.step_size, 0,
                                       dx_dt};

    RK4<State, Parametrs> rk4(system);
//    DOPRI8<State, Parametrs> dopri8(system);
//    AdamsBashforth<State, Parametrs> adamsBashforth(system, rk4, 5);
//    AdamsMoulton<State, Parametrs> adamsMoulton(system, rk4, 5, 5);
    std::unique_ptr<IStepper<State>> stepper;
    switch (config.solver) {
        case SolverType::RK4:
            stepper = std::make_unique<RK4<State, Parametrs>>(system);
            break;
        case SolverType::DOPRI54:
            stepper = std::make_unique<DOPRI54<State, Parametrs>>(system, 1e-8,
                                                                  1e-5);
            break;
        case SolverType::DOPRI8:
            stepper = std::make_unique<DOPRI8<State, Parametrs>>(system);
            break;
        case SolverType::ADAMS_BASHFORTH:
            stepper = std::make_unique<AdamsBashforth<State, Parametrs>>(system,
                                                                         rk4,
                                                                         5);
            break;
        case SolverType::ADAMS_MOULTON:
            stepper = std::make_unique<AdamsMoulton<State, Parametrs>>(system,
                                                                       rk4,
                                                                       5,
                                                                       5);
            break;
        default:
            std::cerr << "Unknown solver type" << std::endl;
            return;
    }

    int width = 18;
    std::cout << std::setprecision(8) << std::scientific;
    std::cout
//             << "id" << sep
            << "time" << sep
            << "x" << sep
            << "y" << sep
            << "z" << std::endl;
    size_t j = config.every_n_steps;
    for (size_t i = 0; i < config.steps; ++i) {
        if (j == config.every_n_steps) {
            std::cout
//                 << i << sep
                    << system.time << sep
                    << system.state.x << sep
                    << system.state.y << sep
                    << system.state.z << sep
                    << system.step << std::endl;
            j = 0;
        }
        stepper->doStep();
        j++;
    }

    std::cout
//             << steps << sep
            << system.time << sep
            << system.state.x << sep
            << system.state.y << sep
            << system.state.z << std::endl;


}
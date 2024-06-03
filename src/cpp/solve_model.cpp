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

    std::unique_ptr<IStepper<State>> stepper;
    switch (config.solver) {
        case SolverType::RK4:
            stepper = std::make_unique<RK4<State, Parametrs>>(system);
            break;
        case SolverType::DOPRI54:
            stepper = std::make_unique<DOPRI54<State, Parametrs>>(system,
                                                                  config.atol,
                                                                  config.rtol);
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

    int precision = 8;

    std::cout << std::setprecision(precision)
              << std::scientific;
    std::cout
            << "time" << sep
            << "x" << sep
            << "y" << sep
            << "z" << std::endl;
    double pt = 0;
    State old_state = system.state;
    double old_time = system.time;
    while (system.time < config.end_time) {
        if (system.time >= pt) {
            double curr_step = system.step;

            // Set previous values
            double step = pt - old_time;
            system.state = old_state;
            system.step = step;
            system.time = old_time;

            stepper->doSimplifiedStep();
            std::cout
//                    << std::setprecision(time_precision)
                    << system.time << sep
                    << std::setprecision(precision)
                    << system.state.x << sep
                    << system.state.y << sep
                    << system.state.z
                    << std::endl;

            // Restore step
            system.step = curr_step;

            old_time = system.time;
            old_state = system.state;

            pt += config.every_step;
            continue;
        }
        old_time = system.time;
        old_state = system.state;
        stepper->doStep();
    }

    std::cout
//            << std::setprecision(time_precision)
            << system.time << sep
            << std::setprecision(precision)
            << system.state.x << sep
            << system.state.y << sep
            << system.state.z
            << std::endl;


}
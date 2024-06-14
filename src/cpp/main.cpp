#include <iostream>
#include <boost/program_options.hpp>

#include "solve_model.hh"
#include "SolverType.hh"

namespace po = boost::program_options;


int main(int ac, char *av[]) {
    ConfigModel config_model;

    po::options_description desc("Allowed options");

    desc.add_options()("help,h", "Show help");
    po::options_description solver_desc("Solver options");

    solver_desc.add_options()
            ("solver",
             po::value<SolverType>(&config_model.solver)->default_value(
                     SolverType::RK4),
             "Choose the solver type\n"
             "RK4 | DOPRI54 | DOPRI8 | ADAMS_BASHFORTH | ADAMS_MOULTON")
            ("end",
             po::value<double>(&config_model.end_time)->default_value(100),
             "Time to stop the simulation\n"
             "<double>")
            ("step,H",
             po::value<double>(&config_model.step_size)->default_value(1e-3),
             "Size of the step to integrate the system\n"
             "<double>")
            ("every",
             po::value<double>(&config_model.every_step)->default_value(2e-3),
             "Size of the step to print the results\n"
             "<double>")
            ("atol", po::value<double>(&config_model.atol)->default_value(1e-8),
             "Absolute tolerance\n"
             "Used only in DOPRI54\n"
             "<double>")
            ("rtol", po::value<double>(&config_model.rtol)->default_value(1e-5),
             "Relative tolerance\n"
             "Used only in DOPRI54\n"
             "<double>");

    desc.add(solver_desc);

    try {
        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);
        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 0;
        }
        if (config_model.every_step < config_model.step_size) {
            config_model.every_step = config_model.step_size;
        }
    } catch (std::exception &ex) {
        std::cout << ex.what() << "\n\n";
        std::cout << desc << std::endl;
        return 1;
    }

    solve_model(config_model);
}

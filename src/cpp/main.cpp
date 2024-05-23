#include <iostream>
#include <boost/program_options.hpp>

#include "solve_model.hh"
#include "SolverType.hh"

namespace po = boost::program_options;


int main(int ac, char *av[]) {
    po::options_description desc("Allowed options");
    ConfigModel config_model;
    SolverType solver;
    unsigned steps;
    unsigned every_n_steps = 200;
    double step_size = 5e-6;
    desc.add_options()("help,h", "Show help");
    po::options_description solver_desc("Solver options");

    solver_desc.add_options()
            ("solver",
             po::value<SolverType>(&config_model.solver)->default_value(SolverType::RK4),
             "Choose the solver type\n"
             "RK4 | DOPRI54 | DOPRI8 | ADAMS_BASHFORTH | ADAMS_MOULTON")
            ("steps,n", po::value<unsigned>(&config_model.steps)->default_value(1000),
             "Set number of steps to count\n"
             "<unsigned>")
            ("every", po::value<unsigned>(&config_model.every_n_steps)->default_value(1),
             "Print every n-th step\n"
             "<unsigned>")
            ("step,H", po::value<double>(&config_model.step_size)->default_value(1e-3),
             "Set step size\n"
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
//1.00000000e+00,2.48805274e+00,3.38984105e-01,2.52330438e+00
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << "\n\n";
        std::cout << desc << std::endl;
        return 1;
    }
    solve_model(config_model);
}

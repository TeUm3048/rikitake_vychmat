#ifndef MAIN_SOLVE_MODEL_HH
#define MAIN_SOLVE_MODEL_HH

#include "RikitakeModel/dx_dt.hh"
#include "ExplicitMethods/RK4.hh"
#include "DOPRI54/DOPRI54.hh"
#include "ExplicitMethods/DOPRI8.hh"
#include "AdamsBashforth/AdamsBashforth.hh"
#include "AdamsMoulton/AdamsMoulton.hh"
#include "SolverType.hh"

struct ConfigModel {
    SolverType solver;
    double step_size;
    unsigned steps;
    unsigned every_n_steps;
};

void solve_model(ConfigModel &config);

#endif //MAIN_SOLVE_MODEL_HH

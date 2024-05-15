#ifndef MAIN_SOLVE_MODEL_HH
#define MAIN_SOLVE_MODEL_HH

#include "RikitakeModel/dx_dt.hh"
#include "ExplicitMethods/RK4.hh"
#include "ExplicitMethods/DOPRI8.hh"
#include "AdamsBashforth/AdamsBashforth.hh"
#include "AdamsMoulton/AdamsMoulton.hh"
#include "SolverType.hh"

void solve_model(SolverType solver, double h, unsigned steps,
                 unsigned every_n_steps);

#endif //MAIN_SOLVE_MODEL_HH

#include "./dx_dt.hh"

State dx_dt(const State &state, const Parametrs &params) {
    return State(-params.nu * state.x + state.z * state.y,
                 -params.nu * state.y +
                 (state.z - params.A) * state.x,
                 1 - state.x * state.y);
}
#ifndef MAIN_SYSTEM_HH
#define MAIN_SYSTEM_HH

#include <functional>

template<typename T, typename P>
struct System {
    T &state;
    P &params;
    double step;
    double time;

    T (*dx_dt_)(const T &, const P &);

    inline
    T dx_dt() {
        return dx_dt_(state, params);
    };
};

#endif //MAIN_SYSTEM_HH

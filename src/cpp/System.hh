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

template<typename T>
bool allclose(const T &a, const T &b, double rtol, double atol);

template<typename T>
double estimate_err(const T &a, const T &b, double rtol, double atol);

#endif //MAIN_SYSTEM_HH

#ifndef MAIN_SYSTEM_HH
#define MAIN_SYSTEM_HH

#include <functional>

template<typename T, typename P>
struct System {
    T &state;
    P &params;
    double step;
    double time;
    std::function<T(T, P)> dx_dt_;

    inline
    T dx_dt() {
        return dx_dt_(state, params);
    };
};

#endif //MAIN_SYSTEM_HH

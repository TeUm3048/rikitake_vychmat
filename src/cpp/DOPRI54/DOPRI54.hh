#ifndef MAIN_DOPRI54_HH
#define MAIN_DOPRI54_HH

#include <cmath>
#include "../IOneStepper.hh"
#include "../System.hh"
// #include "../ExplicitMethods/UniversalRungeKuttaStepper/ButcherTable.hh"

struct DOPRIButcherTable {
    std::vector<std::vector<double>> a;
    std::vector<double> c;
    std::vector<double> b;
    std::vector<double> e;
};

template<typename T, typename P>
class DOPRI54 : public IOneStepper<T> {
public:
    DOPRI54(System<T, P> &system_, double atol_, double rtol_)
            : system(system_), atol(atol_), rtol(rtol_) {};

    inline void doStep() override {
        double t = system.time;
        T state = system.state;
        T err_state = system.state;

        double min_step = 10 * std::abs(
                std::nextafter(t, std::numeric_limits<double>::infinity()) - t);

        // if (system.step > max_step)
        //     system.step = max_step;
        if (system.step < min_step)
            system.step = min_step;

        bool step_accepted = false;
        bool step_rejected = true;

        while (!step_accepted) {
            if (system.step < min_step) {
                return;
            }
            double time_new = system.time + system.step;

            std::vector<T> k(stages);

            for (std::size_t i = 0; i < stages; ++i) {
                T sum = T();
                for (std::size_t j = 0; j < i; ++j) {
                    sum += table.a[i][j] * k[j];
                }
                T k1;
                k1 = system.dx_dt_(state + system.step * sum,
                                   system.params);
                k[i] = k1;
            }
            T k7;
            // $x(t+h) = x(t) + \sum_i{b_i k_i}$
            for (std::size_t i = 0; i < stages; ++i) {
                state += system.step * table.b[i] * k[i];
            }
            k7 = system.dx_dt_(state, system.params);

            for (std::size_t i = 0; i < stages; ++i) {
                err_state += system.step * table.e[i] * k[i];
            }
            err_state += system.step * table.e[6] * k7;

//            if (allclose(state, err_state, rtol, atol)) {
//                step_accepted = true;
//                step_rejected = false;
//            } else {
//                system.step /= 2;
//                state = system.state;
//                err_state = system.state;
//            }
//
            double err = estimate_err(state, err_state, rtol, atol);
            if (0.9  < err && err <= 1. ) {
                step_accepted = true;
            } else {
                double a = std::pow(err, -1. / 5);
                std::cout << system.step << ',' << err << std::endl;
                if (0.87 <= a && a < 1.) {
                    a = 0.87;
                }
                system.step *= a;
                state = system.state;
                err_state = system.state;
            }
        } // end while

        system.state = state;
        system.time += system.step;
    };

    /**
     * @brief Returns the current state of the system.
     *
     * @return The current state of the system.
     */
    inline T getState() const override {
        return system.state;
    };

private:
    System<T, P> &system; // The system of ordinary differential equations to be integrated.
    static DOPRIButcherTable table;
    double atol;
    double rtol;
//    double max_step;
    int stages = 6;
};

template<typename T, typename P>
DOPRIButcherTable DOPRI54<T, P>::table = {
        {{0.0, 0.0, 0.0, 0.0, 0.0},
                        {1. / 5., 0.0, 0.0, 0.0,
                                0.0},
                {3. / 40., 9. / 40, 0.0, 0.0, 0.0},
                              {44. / 45., -56. / 15, 32. / 9, 0.0, 0.0},
                {19372. / 6561., -25360. / 2187., 64448. / 6561.,
                        -212. / 729., 0.0},
                                  {9017. / 3168., -355. / 33., 46732. / 5247.,
                                          49. / 176., -5103. / 18656.}},
        {0.,            1. / 5.,
                3. / 10.,     4. / 5.,
                8. / 9.,          1.},
        {35. / 384.,    0.,
                500. / 1113., 125. / 192.,
                -2187. / 6784.,   11. / 84.},
        {-71. / 57600., 0,
                71. / 16695., -71. / 1920.,
                17253. / 339200., -22. / 525.,
                1. / 40.}};
#endif // MAIN_DOPRI54_HH

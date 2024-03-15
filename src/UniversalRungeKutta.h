//
// Created by TeUm3 on 13.03.2024.
//

#ifndef TEST_UNIVERSALRUNGEKUTTA_H
#define TEST_UNIVERSALRUNGEKUTTA_H

#include <vector>
#include <functional>

// Exaple to use
//    std::vector<std::vector<double>> butcher_table = {
//        {0.},
//        {0.5, 0.},
//        {0.,  1.}
//    };
//    UniversalRungeKutta<State, Parametrs> rk(butcher_table);
//    calc_model(state, 1000, 0.1, f, rk, params);


template<typename T, typename P,
        typename F = std::function<T(T, P)>>
class UniversalRungeKutta {
private:
    size_t stages;
    std::vector<double> c;
    std::vector<std::vector<double>> a;
    std::vector<double> b;


public:
    explicit UniversalRungeKutta(
            const std::vector<std::vector<double>> &butcher_table)
            : stages(butcher_table.size() - 1),
              c(stages),
              a(stages, std::vector<double>(stages)),
              b(stages) {

        // Extracting coefficients from Butcher table
        b = butcher_table.back();
        for (int i = 0; i < stages; ++i) {
            a[i] = butcher_table[i];
        }
    }

    inline
    T operator()(T x0, double h, F f, P params) {
        std::vector<T> k(stages);

        T result = x0;
        for (size_t i = 0; i < stages; ++i) {
            T sum = T();
            for (size_t j = 0; j < i; ++j) {
                sum += a[i][j] * k[j];
            }
            k[i] = f(x0 + h * sum, params);
        }

        // $x(t+h) = x(t) + \sum_i{b_i k_i}$
        for (size_t i = 0; i < stages; ++i) {
            result += h * b[i] * k[i];
        }

        return result;
    }
};


#endif //TEST_UNIVERSALRUNGEKUTTA_H

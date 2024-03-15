//
// Created by TeUm3 on 13.03.2024.
//

#ifndef TEST_RUGLEKUTTA4_H
#define TEST_RUGLEKUTTA4_H

template<typename T, typename P>
class RungeKutta4 : public UniversalRungeKutta<T, P> {
private:
    static std::vector<std::vector<double>> butcher_table;
public:
    RungeKutta4() : UniversalRungeKutta<T, P>(butcher_table) {

    }
};

template<typename T, typename P>
std::vector<std::vector<double>> RungeKutta4<T, P>::butcher_table = {
        {0.},
        {0.5,     0},
        {0.,      0.5,     0.},
        {0.,      0.,      1.,      0.},
        {1. / 6., 1. / 3., 1. / 3., 1. / 6.}
};

#endif //TEST_RUGLEKUTTA4_H

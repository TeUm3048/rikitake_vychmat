//
// Created by TeUm3 on 13.03.2024.
//

#ifndef TEST_FORWARDEULER_H
#define TEST_FORWARDEULER_H

#include "../UniversalRungeKutta.h"

template<typename T, typename P>
class ForwardEuler : public UniversalRungeKutta<T, P> {
private:
    static std::vector<std::vector<double>> butcher_table;
public:
    ForwardEuler() : UniversalRungeKutta<T, P>(butcher_table) {

    }
};

template<typename T, typename P>
std::vector<std::vector<double>> ForwardEuler<T, P>::butcher_table = {{0.},
                                                                      {1.}};


#endif //TEST_FORWARDEULER_H

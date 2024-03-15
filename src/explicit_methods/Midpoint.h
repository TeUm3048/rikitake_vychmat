//
// Created by TeUm3 on 13.03.2024.
//

#ifndef TEST_MIDPOINT_H
#define TEST_MIDPOINT_H

#include "../UniversalRungeKutta.h"


template<typename T, typename P>
class Midpoint : public UniversalRungeKutta<T, P> {
private:
    static std::vector<std::vector<double>> butcher_table;

public:
    Midpoint() : UniversalRungeKutta<T, P>(butcher_table) {

    }
};

template<typename T, typename P>
std::vector<std::vector<double>> Midpoint<T, P>::butcher_table = {{0.},
                                                                  {0.5, 0.},
                                                                  {0.,  1.}};

#endif //TEST_MIDPOINT_H

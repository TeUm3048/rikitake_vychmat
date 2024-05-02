//
// Created by TeUm3 on 10.04.2024.
//

#ifndef MAIN_ADAMS_SOLVER_H
#define MAIN_ADAMS_SOLVER_H


#include "../Interfaces/IStepper.h"

template<typename T, typename P>
class Adams_multistepper {
public:
    Adams_multistepper(IStepper<T, P> stepper);
};

#endif //MAIN_ADAMS_SOLVER_H

//
// Created by TeUm3 on 14.03.2024.
//

#ifndef TEST_STEPPER_H
#define TEST_STEPPER_H

template<typename T, typename P>
class IStepper {
    virtual T
    operator()() = 0;
};

#endif //TEST_STEPPER_H

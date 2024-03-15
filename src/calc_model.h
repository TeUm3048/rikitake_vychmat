//
// Created by TeUm3 on 05.03.2024.
//

#ifndef TEST_CALC_MODEL_H
#define TEST_CALC_MODEL_H

#include <functional>
#include <iostream>
#include <iomanip>

#include "State.h"
#include "Parameters.h"

/**
 * @brief Функция, описывающая дифференциальное уравнение.
 *
 * @param state Текущее состояние системы.
 * @param params Параметры системы.
 * @return Новое состояние системы, полученное в результате дифференциального уравнения.
 */
State
f(const State &state, const Parametrs &params);

/**
 * @brief Функция для численного моделирования системы.
 *
 * @tparam F Тип функции, описывающей дифференциальное уравнение.
 * @tparam M Тип функции, определяющей метод численного интегрирования.
 *
 * @param initial_state Начальное состояние системы.
 * @param time Общее время моделирования.
 * @param h Шаг интегрирования.
 * @param f Функция, описывающая дифференциальное уравнение.
 * @param method Функция, определяющая метод численного интегрирования.
 * @param params Параметры системы.
 * @param out Поток вывода, в который будет производиться запись результатов.
 */
template<typename F = std::function<
        State(State, Parametrs)>,
        typename M = std::function<
                State(State, double, F,
                      Parametrs)>>
void
calc_model(State initial_state, double time, double h, F f,
           M method,
           Parametrs params,
           std::ostream &out) {
    double t;
    State state = initial_state;
    for (t = 0.; t < time; t += h) {
        out << std::scientific << std::setprecision(8)
            << t << " " << state.x << " " << state.y << " " << state.z << "\n";
        state = method(state, h, f, params);
    }
//    out << std::scientific << std::setprecision(8)
//        << t << " " << state.x << " " << state.y << " " << state.z << "\n";
}


#endif //TEST_CALC_MODEL_H

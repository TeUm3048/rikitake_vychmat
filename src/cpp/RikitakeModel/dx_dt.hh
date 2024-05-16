//
// Created by TeUm3 on 01.05.2024.
//

#ifndef MAIN_DX_DT_HH
#define MAIN_DX_DT_HH

#include "./State.hh"
#include "Parameters.hh"

/**
 * @brief Функция, описывающая дифференциальное уравнение.
 *
 * @param state Текущее состояние системы.
 * @param params Параметры системы.
 * @return Новое состояние системы, полученное в результате дифференциального уравнения.
 */
inline
State dx_dt(const State &state, const Parametrs &params) {
    return {-params.nu * state.x + state.z * state.y,
            -params.nu * state.y +
            (state.z - params.A) * state.x,
            1 - state.x * state.y};
}

#endif // MAIN_DX_DT_HH

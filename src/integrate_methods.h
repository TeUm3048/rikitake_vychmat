/**
 * @file numerical_methods.hpp
 * @brief Функции для численных методов решения дифференциальных уравнений.
 */

#ifndef TEST_INTEGRATE_METHODS_H
#define TEST_INTEGRATE_METHODS_H

#include <utility>
#include <functional>
#include <cstdio>

/**
 * @brief Производит один шаг метода Эйлера для численного решения дифференциального уравнения.
 *
 * @tparam T Тип данных аргумента и возвращаемого значения функции.
 * @tparam P Тип данных параметров функции.
 * @tparam F Тип данных функции.
 *
 * @param x0 Текущее значение аргумента.
 * @param h Шаг интегрирования.
 * @param f Функция, описывающая дифференциальное уравнение.
 *      Принимает аргумент x и параметры params, возвращает значение функции.
 * @param params Параметры функции f.
 * @return Новое значение аргумента после одного шага метода Эйлера.
 */
template<typename T, typename P,
         typename F = std::function<T(T, P)>>
T
euler_step(T x0, double h, F f, P params) {
    return x0 + h * f(x0, params);
}

/**
 * @brief Производит один шаг метода средней точки (midpoint) для численного решения дифференциального уравнения.
 *
 * @tparam T Тип данных аргумента и возвращаемого значения функции.
 * @tparam P Тип данных параметров функции.
 * @tparam F Тип данных функции, по умолчанию std::function.
 *
 * @param x0 Текущее значение аргумента.
 * @param h Шаг интегрирования.
 * @param f Функция, описывающая дифференциальное уравнение.
 *      Принимает аргумент x и параметры params, возвращает значение функции.
 * @param params Параметры функции f.
 * @return Новое значение аргумента после одного шага метода средней точки.
 */
template<typename T, typename P,
         typename F = std::function<T(T, P)>>
T
midpoint(T x0, double h, F f, P params) {

    T x_mid = x0 + 0.5 * h * f(x0, params);
    return x0 + h * 1 * f(x_mid, params);
}

/**
 * @brief Производит численное интегрирование дифференциального уравнения.
 *
 * @tparam T Тип данных аргумента и возвращаемого значения функции.
 * @tparam P Тип данных параметров функции.
 * @tparam F Тип данных функции, описывающей дифференциальное уравнение.
 * @tparam M Тип данных функции, описывающей шаг интегрирования.
 *
 * @param x0 Начальное значение аргумента.
 * @param time Общее время интегрирования.
 * @param h Шаг интегрирования.
 * @param f Функция, описывающая дифференциальное уравнение.
 *      Принимает аргумент x, параметры params и возвращает значение функции.
 * @param method Функция, определяющая метод интегрирования.
 *      Принимает текущее значение x, шаг dt и функцию f, возвращает новое значение x.
 * @param params Параметры функции f.
 */
template<typename P,
         typename F = std::function<double(double, P)>,
         typename M = std::function<
                 double(double, double, F, P)>>
void
integrate(double x0, double time, double h, F f, M method,
          P params) {
    double t;
    double x = x0;

    for (t = 0; t < time; t += h) {
        printf("%.3le %.8le\n", t, x);
        x = method(x, h, f, params);
    }
    printf("%.3le %.8le\n", t, x);
}


#endif //TEST_INTEGRATE_METHODS_H

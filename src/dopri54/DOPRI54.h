//
// Created by TeUm3 on 13.03.2024.
//

#ifndef TEST_DOPRI54_H
#define TEST_DOPRI54_H

#include <iostream>
#include <vector>
#include <cmath>

// Определение функции f(y,t)
double f(double y, double t) {
    return y - t*t + 1;
}

// Определение метода Dormand-Prince
std::vector<double> dopri5(double y0, double t0, double tf, double h) {
    // Коэффициенты метода Dormand-Prince
    std::vector<double> c = {1/5., 3/10., 4/5., 8/9., 1., 1.};
    std::vector<std::vector<double>> a = {
            {1/5.},
            {3/40., 9/40.},
            {44/45., -56/15., 32/9.},
            {19372/6561., -25360/2187., 64448/6561., -212/729.},
            {9017/3168., -355/33., 46732/5247., 49/176., -5103/18656.},
            {35/384., 0., 500/1113., 125/192., -2187/6784., 11/84.}
    };
    std::vector<double> b = {35/384., 0., 500/1113., 125/192., -2187/6784., 11/84., 0.};
    std::vector<double> bstar = {5179/57600., 0., 7571/16695., 393/640., -92097/339200., 187/2100., 1/40.};

    std::vector<double> y = {y0};  // Инициализация вектора решений
    double t = t0;  // Начальное время

    // Цикл по времени
    while (t < tf) {
        std::vector<double> k(7);
        for (int i = 0; i < 7; ++i) {
            double ti = t + c[i]*h;
            double yi = y.back();
            for (int j = 0; j < i; ++j) {
                yi += h * a[i][j] * k[j];
            }
            k[i] = f(yi, ti);
        }

        // Вычисление y(t+h) с использованием коэффициентов b и bstar
        double y_next = y.back();
        double y_next_star = y.back();
        for (int i = 0; i < 7; ++i) {
            y_next += h * b[i] * k[i];
            y_next_star += h * bstar[i] * k[i];
        }

        // Обновление времени и решения
        t += h;
        y.push_back(y_next);

        // Обновление шага h на основе оценки ошибки
        double error = std::abs(y_next - y_next_star);
        h *= std::pow(1/error, 1/5.);
    }

    return y;
}




#endif //TEST_DOPRI54_H

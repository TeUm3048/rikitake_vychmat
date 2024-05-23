#ifndef MAIN_STATE_HH
#define MAIN_STATE_HH

#include <algorithm>

/**
 * @brief Класс, представляющий состояние системы.
 *
 * Этот класс содержит значения переменных состояния системы.
 */
struct State {
public:
    double x; /**< Безразмерный ток первого диска. */
    double y; /**< Безразмерный ток второго диска. */
    double z; /**< Безразмерная угловая скорость диска. */
public:
    State();

    State(double _x, double _y, double _z);

    void operator+=(const State &a);

    State operator+(const State &a) const;

    State operator+(const double &a) const;

    State operator-(const State &a) const;

    State operator-(const double &a) const;

    friend State operator+(const double &a, const State &state);

    friend State operator-(const double &a, const State &state);

    State operator*(const State &a) const;

    State operator*(const double &a) const;

    friend State operator*(const double &a, const State &state);

    friend
    bool allclose(const State &a, const State &b, double rtol, double atol);

    friend
    double estimate_err(const State &a, const State &b, double rtol, double atol);
};

#endif // MAIN_STATE_HH

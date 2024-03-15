//
// Created by TeUm3 on 05.03.2024.
//

#ifndef TEST_STATE_H
#define TEST_STATE_H

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

    /**
     * @brief Конструктор класса State.
     *
     * Создает объект класса State с заданными значениями переменных состояния.
     *
     * @param _x Безразмерный ток первого диска.
     * @param _y Безразмерный ток второго диска.
     * @param _z Безразмерная угловая скорость диска.
     */
    State(double _x, double _y, double _z);

    inline void
    operator+=(const State &a) {
        this->x += a.x;
        this->y += a.y;
        this->z += a.z;
    }

    inline State
    operator+(const State &a) const {
        return {this->x + a.x,
                this->y + a.y,
                this->z + a.z};
    }

    inline State
    operator+(const double &a) const {
        return {this->x + a,
                this->y + a,
                this->z + a};
    }

    friend inline State
    operator+(const double &a, const State &state) {
        return state + a;
    }

    inline State
    operator*(const State &a) const {
        return {this->x * a.x,
                this->y * a.y,
                this->z * a.z};
    }

    inline State
    operator*(const double &a) const {
        return {this->x * a,
                this->y * a,
                this->z * a};
    }


    friend inline State
    operator*(const double &a, const State &state) {
        return state * a;
    }
};

#endif //TEST_STATE_H

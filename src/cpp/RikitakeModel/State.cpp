#include <cmath>
#include "./State.hh"

State::State(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};

State::State() : x(.0), y(.0), z(.0) {};

void State::operator+=(const State &a) {
    this->x += a.x;
    this->y += a.y;
    this->z += a.z;
}

State State::operator+(const State &a) const {
    return {this->x + a.x,
            this->y + a.y,
            this->z + a.z};
}

State State::operator+(const double &a) const {
    return {this->x + a,
            this->y + a,
            this->z + a};
}

State operator+(const double &a, const State &state) {
    return state + a;
}

State State::operator*(const State &a) const {
    return {this->x * a.x,
            this->y * a.y,
            this->z * a.z};
}

State State::operator*(const double &a) const {
    return {this->x * a,
            this->y * a,
            this->z * a};
}

State operator*(const double &a, const State &state) {
    return state * a;
}

State State::operator-(const State &a) const {
    return {this->x - a.x,
            this->y - a.y,
            this->z - a.z};
}

State State::operator-(const double &a) const {
    return {this->x - a,
            this->y - a,
            this->z - a};
}

State operator-(const double &a, const State &state) {
    return {-state.x + a,
            -state.y + a,
            -state.z + a};
}

bool allclose(const State &a, const State &b, double rtol, double atol) {
    return std::abs(a.x - b.x) <=
           (atol + rtol * std::max(std::abs(a.x), std::abs(b.x))) &&
           std::abs(a.y - b.y) <=
           (atol + rtol * std::max(std::abs(a.y), std::abs(b.y))) &&
           std::abs(a.z - b.z) <=
           (atol + rtol * std::max(std::abs(a.z), std::abs(b.z)));
}

double estimate_err(const State &a, const State &b, double rtol, double atol) {
    double tol_x = atol + rtol * std::max(std::abs(a.x), std::abs(b.x));
    double tol_y = atol + rtol * std::max(std::abs(a.y), std::abs(b.y));
    double tol_z = atol + rtol * std::max(std::abs(a.z), std::abs(b.z));
    double s = .0;
    s += std::pow((a.x - b.x) / tol_x, 2);
    s += std::pow((a.y - b.y) / tol_y, 2);
    s += std::pow((a.z - b.z) / tol_z, 2);

    return std::sqrt(1. / 3 * s);
}

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
#ifndef MAIN_SOLVERTYPE_HH
#define MAIN_SOLVERTYPE_HH

#include <algorithm>
#include <boost/program_options.hpp>

enum class SolverType {
    RK4,
    DOPRI54,
    DOPRI8,
    ADAMS_BASHFORTH,
    ADAMS_MOULTON
};

inline std::istream &operator>>(std::istream &in, SolverType &solverType) {
    std::string token;
    in >> token;
    std::transform(token.begin(), token.end(), token.begin(), toupper);

    if (token == "RK4")
        solverType = SolverType::RK4;
    else if (token == "DOPRI54" || token == "DOPRI45")
        solverType = SolverType::DOPRI54;
    else if (token == "DOPRI8")
        solverType = SolverType::DOPRI8;
    else if (token == "ADAMS_BASHFORTH")
        solverType = SolverType::ADAMS_BASHFORTH;
    else if (token == "ADAMS_MOULTON")
        solverType = SolverType::ADAMS_MOULTON;
    else
        in.setstate(std::ios_base::failbit);
    return in;
}

inline std::ostream &operator<<(std::ostream &out, const SolverType &solverType) {
    switch (solverType) {
        case SolverType::RK4:
            out << "RK4";
            break;
        case SolverType::DOPRI54:
            out << "DOPRI54";
            break;
        case SolverType::DOPRI8:
            out << "DOPRI8";
            break;
        case SolverType::ADAMS_BASHFORTH:
            out << "ADAMS_BASHFORTH";
            break;
        case SolverType::ADAMS_MOULTON:
            out << "ADAMS_MOULTON";
            break;
    }
    return out;
}

#endif // MAIN_SOLVERTYPE_HH

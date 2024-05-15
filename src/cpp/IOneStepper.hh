#ifndef MAIN_IONESTEPPER_HH
#define MAIN_IONESTEPPER_HH

#include "IStepper.hh"

/**
 * @brief An interface for stepping algorithms that perform step by step.
 *
 * This interface extends the base IStepper class and is used for algorithms that perform a single step.
 *
 * @tparam T The type of the step value.
 */
template <typename T>
class IOneStepper : public IStepper<T>
{
};

#endif // MAIN_IONESTEPPER_HH

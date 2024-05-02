#ifndef RK_IStepper
#define RK_IStepper

/**
 * @brief Interface for a stepper class.
 * 
 * This interface defines the common methods that a stepper class should implement.
 * A stepper class is responsible for performing a single step of a simulation or computation.
 * 
 * @tparam T The type of the state.
 */
template<typename T>
class IStepper {
public:
    /**
     * @brief Perform a single step.
     * 
     * This method should be implemented by the derived class to perform a single step of the simulation or computation.
     */
    virtual void doStep() = 0;

    /**
     * @brief Get the current state.
     * 
     * This method should be implemented by the derived class to return the current state of the simulation or computation.
     * 
     * @return The current state.
     */
    virtual T getState() const = 0;
};

#endif // RK_IStepper

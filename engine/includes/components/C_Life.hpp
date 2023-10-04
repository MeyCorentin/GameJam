#pragma once

#include "Component.hpp"

/**
 * @brief A template class representing C_life value as a component.
 *
 * This template class represents a C_life value as a component. It is used
 * to associate a C_life value with an entity in a game or simulation.
 */
template <class T>
class C_Life : public Component<T> {
public:
    /**
     * @brief Constructor to initialize the C_life component with a value.
     *
     * This constructor initializes the C_life component with the specified
     * C_life value.
     *
     * @param n The initial C_life value.
     */
    C_Life(T n) : Component<T>(n) {}
    C_Life() : Component<T>() {}

    /**
     * @brief Get the type information of the C_Life component.
     *
     * This method returns the type information of the C_Life component.
     *
     * @return The type information of the C_Life component.
     */
    const std::type_info& getType() const override {
        return typeid(C_Life);
    }

    std::shared_ptr<ComponentBase> clone() const override {
        return std::make_shared<C_Life>(*this);
    }
};
#pragma once

#include "TComponent.hpp"

/**
 * @brief A template class representing life value as a component.
 *
 * This template class represents a life value as a component. It is used
 * to associate a life value with an entity in a game or simulation.
 */
template <class T>
class Life : public TComponent<T> {
public:
    /**
     * @brief Constructor to initialize the life component with a value.
     *
     * This constructor initializes the life component with the specified
     * life value.
     *
     * @param n The initial life value.
     */
    Life(T n) : TComponent<T>(n) {}
    Life() : TComponent<T>() {}

    /**
     * @brief Get the type information of the Life component.
     *
     * This method returns the type information of the Life component.
     *
     * @return The type information of the Life component.
     */
    const std::type_info& getType() const override {
        return typeid(Life);
    }

    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Life>(*this);
    }
};
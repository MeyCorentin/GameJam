#pragma once

#include "Component.hpp"

/**
 * @brief A template class representing life value as a component.
 *
 * This template class represents a life value as a component. It is used
 * to associate a life value with an entity in a game or simulation.
 */
template <class T>
class C_Mana : public Component<T> {
public:
    /**
     * @brief Constructor to initialize the life component with a value.
     *
     * This constructor initializes the life component with the specified
     * life value.
     *
     * @param n The initial life value.
     */
    C_Mana(T n) : Component<T>(n) {}
    C_Mana() : Component<T>() {}

    /**
     * @brief Get the type information of the Life component.
     *
     * This method returns the type information of the Life component.
     *
     * @return The type information of the Life component.
     */
    const std::type_info& getType() const override {
        return typeid(C_Mana);
    }

    std::shared_ptr<ComponentBase> clone() const override {
        return std::make_shared<C_Mana>(*this);
    }
};
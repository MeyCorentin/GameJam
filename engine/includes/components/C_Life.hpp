#pragma once

#include "AComponent.hpp"

/**
 * @brief A template class representing C_life value as a component.
 *
 * This template class represents a C_life value as a component. It is used
 * to associate a C_life value with an entity in a game or simulation.
 */
template <class T>
class C_Life : public AComponent<T> {
    public:
        C_Life(T arg_n) :
            AComponent<T>(arg_n) {}

        C_Life() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Life);
        }

        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_Life>(*this);
        }
};
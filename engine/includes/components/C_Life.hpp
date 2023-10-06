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
        C_Life(T arg_n) :
            Component<T>(arg_n) {}

        C_Life() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Life);
        }

        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_Life>(*this);
        }
};
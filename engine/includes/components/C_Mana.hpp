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
        C_Mana(T arg_n) :
            Component<T>(arg_n) {}

        C_Mana() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Mana);
        }

        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_Mana>(*this);
        }
};
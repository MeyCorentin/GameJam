#pragma once

#include "AComponent.hpp"

/**
 * @brief A template class representing life value as a component.
 *
 * This template class represents a life value as a component. It is used
 * to associate a life value with an entity in a game or simulation.
 */
template <class T>
class C_Mana : public AComponent<T> {
    public:
        C_Mana(T arg_n) :
            AComponent<T>(arg_n) {}

        C_Mana() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Mana);
        }

        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_Mana>(*this);
        }
};
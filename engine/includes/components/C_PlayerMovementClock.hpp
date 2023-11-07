#pragma once

#include "AComponent.hpp"

template <class T>
class C_PlayerMovementClock : public AComponent<T> {
    public:
        C_PlayerMovementClock(T arg_n) :
            AComponent<T>(arg_n) {}

        C_PlayerMovementClock() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_PlayerMovementClock);
        }

        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_PlayerMovementClock>(*this);
        }
};
#pragma once

#include "AComponent.hpp"

template <class T>
class C_EntityMovementClock : public AComponent<T> {
    public:
        C_EntityMovementClock(T arg_n) :
            AComponent<T>(arg_n) {}

        C_EntityMovementClock() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_EntityMovementClock);
        }

        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_EntityMovementClock>(*this);
        }
};
#pragma once

#include "Component.hpp"

template <class T>
class C_PlayerMovementClock : public Component<T> {
    public:
        C_PlayerMovementClock(T arg_n) :
            Component<T>(arg_n) {}

        C_PlayerMovementClock() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_PlayerMovementClock);
        }

        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_PlayerMovementClock>(*this);
        }
};
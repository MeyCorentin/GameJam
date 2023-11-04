#pragma once

#include "Component.hpp"

template <class T>
class C_EntityMovementClock : public Component<T> {
    public:
        C_EntityMovementClock(T arg_n) :
            Component<T>(arg_n) {}

        C_EntityMovementClock() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_EntityMovementClock);
        }

        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_EntityMovementClock>(*this);
        }
};
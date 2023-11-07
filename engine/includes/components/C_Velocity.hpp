#pragma once

#include "AComponent.hpp"

template <class T>
class C_Velocity : public AComponent<T> {
public:
    C_Velocity(T arg_n) :
        AComponent<T>(arg_n) {}

    C_Velocity() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Velocity);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Velocity>(*this);
    }
};
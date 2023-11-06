#pragma once

#include "Component.hpp"

template <class T>
class C_Velocity : public Component<T> {
public:
    C_Velocity(T arg_n) :
        Component<T>(arg_n) {}

    C_Velocity() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Velocity);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Velocity>(*this);
    }
};
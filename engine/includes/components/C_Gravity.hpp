#pragma once

#include "Component.hpp"

template <class T>
class C_Gravity : public Component<T> {
public:
    C_Gravity(T arg_n) :
        Component<T>(arg_n) {}

    C_Gravity() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Gravity);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Gravity>(*this);
    }
};
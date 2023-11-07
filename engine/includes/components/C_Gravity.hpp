#pragma once

#include "AComponent.hpp"

template <class T>
class C_Gravity : public AComponent<T> {
public:
    C_Gravity(T arg_n) :
        AComponent<T>(arg_n) {}

    C_Gravity() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Gravity);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Gravity>(*this);
    }
};
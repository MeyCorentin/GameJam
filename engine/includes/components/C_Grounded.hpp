#pragma once

#include "AComponent.hpp"

template <class T>
class C_Grounded : public AComponent<T> {
public:
    C_Grounded(T arg_n) :
        AComponent<T>(arg_n) {}

    C_Grounded() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Grounded);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Grounded>(*this);
    }
};
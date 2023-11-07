#pragma once

#include "AComponent.hpp"

template <class T>
class C_IsClickable : public AComponent<T> {
public:
    C_IsClickable(T arg_n) :
        AComponent<T>(arg_n) {}

    C_IsClickable() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_IsClickable);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_IsClickable>(*this);
    }
};
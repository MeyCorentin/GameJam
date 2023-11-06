#pragma once

#include "Component.hpp"

template <class T>
class C_IsClickable : public Component<T> {
public:
    C_IsClickable(T arg_n) :
        Component<T>(arg_n) {}

    C_IsClickable() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_IsClickable);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_IsClickable>(*this);
    }
};
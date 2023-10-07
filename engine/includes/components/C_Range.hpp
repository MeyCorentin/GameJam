#pragma once

#include "Component.hpp"

template <class T>
class C_Range : public Component<T> {
public:
    C_Range(T n) : Component<T>(n) {}
    C_Range() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Range);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Range>(*this);
    }
};
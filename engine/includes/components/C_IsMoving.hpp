#pragma once

#include "Component.hpp"

template <class T>
class C_IsMoving : public Component<T> {
public:
    C_IsMoving(T n) : Component<T>(n) {}
    C_IsMoving() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_IsMoving);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_IsMoving>(*this);
    }
};
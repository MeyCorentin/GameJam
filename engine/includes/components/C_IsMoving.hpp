#pragma once

#include "AComponent.hpp"

template <class T>
class C_IsMoving : public AComponent<T> {
public:
    C_IsMoving(T n) : AComponent<T>(n) {}
    C_IsMoving() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_IsMoving);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_IsMoving>(*this);
    }
};
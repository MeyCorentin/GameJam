#pragma once

#include "AComponent.hpp"

template <class T>
class C_PlayerAmmo : public AComponent<T> {
public:
    C_PlayerAmmo(T n) : AComponent<T>(n) {}
    C_PlayerAmmo() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_PlayerAmmo);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_PlayerAmmo>(*this);
    }
};
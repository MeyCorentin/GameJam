#pragma once

#include "Component.hpp"

template <class T>
class C_PlayerAmmo : public Component<T> {
public:
    C_PlayerAmmo(T n) : Component<T>(n) {}
    C_PlayerAmmo() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_PlayerAmmo);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_PlayerAmmo>(*this);
    }
};
#pragma once

#include "Component.hpp"

template <class T>
class C_ShootCharging : public Component<T> {
public:
    C_ShootCharging(T n) : Component<T>(n) {}
    C_ShootCharging() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_ShootCharging);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_ShootCharging>(*this);
    }
};
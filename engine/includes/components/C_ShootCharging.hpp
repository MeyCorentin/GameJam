#pragma once

#include "AComponent.hpp"

template <class T>
class C_ShootCharging : public AComponent<T> {
public:
    C_ShootCharging(T n) : AComponent<T>(n) {}
    C_ShootCharging() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_ShootCharging);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_ShootCharging>(*this);
    }
};
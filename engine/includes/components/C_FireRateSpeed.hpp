#pragma once

#include "AComponent.hpp"

template <class T>
class C_FireRateSpeed : public AComponent<T> {
public:
    C_FireRateSpeed(T n) : AComponent<T>(n) {}
    C_FireRateSpeed() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_FireRateSpeed);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_FireRateSpeed>(*this);
    }
};
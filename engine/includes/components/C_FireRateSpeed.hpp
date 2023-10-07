#pragma once

#include "Component.hpp"

template <class T>
class C_FireRateSpeed : public Component<T> {
public:
    C_FireRateSpeed(T n) : Component<T>(n) {}
    C_FireRateSpeed() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_FireRateSpeed);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_FireRateSpeed>(*this);
    }
};
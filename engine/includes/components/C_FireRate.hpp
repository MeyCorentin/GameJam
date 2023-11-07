#pragma once

#include "AComponent.hpp"

template <class T>
class C_FireRate : public AComponent<T> {
public:
    C_FireRate(T n) : AComponent<T>(n) {}
    C_FireRate() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_FireRate);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_FireRate>(*this);
    }
};
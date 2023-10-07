#pragma once

#include "Component.hpp"

template <class T>
class C_FireRate : public Component<T> {
public:
    C_FireRate(T n) : Component<T>(n) {}
    C_FireRate() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_FireRate);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_FireRate>(*this);
    }
};
#pragma once

#include "Component.hpp"

template <class T>
class C_Shoot : public Component<T> {
public:
    C_Shoot(T n) : Component<T>(n) {}
    C_Shoot() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Shoot);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Shoot>(*this);
    }
};
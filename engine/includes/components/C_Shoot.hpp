#pragma once

#include "AComponent.hpp"

template <class T>
class C_Shoot : public AComponent<T> {
public:
    C_Shoot(T n) : AComponent<T>(n) {}
    C_Shoot() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Shoot);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Shoot>(*this);
    }
};
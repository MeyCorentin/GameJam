#pragma once

#include "AComponent.hpp"

template <class T>
class C_Weapon : public AComponent<T> {
public:
    C_Weapon(T n) : AComponent<T>(n) {}
    C_Weapon() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Weapon);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Weapon>(*this);
    }
};
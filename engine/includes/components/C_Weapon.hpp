#pragma once

#include "Component.hpp"

template <class T>
class C_Weapon : public Component<T> {
public:
    C_Weapon(T n) : Component<T>(n) {}
    C_Weapon() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Weapon);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Weapon>(*this);
    }
};
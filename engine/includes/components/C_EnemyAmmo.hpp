#pragma once

#include "Component.hpp"

template <class T>
class C_EnemyAmmo : public Component<T> {
public:
    C_EnemyAmmo(T arg_n) :
        Component<T>(arg_n) {}

    C_EnemyAmmo() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_EnemyAmmo);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_EnemyAmmo>(*this);
    }
};
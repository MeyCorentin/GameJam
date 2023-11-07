#pragma once

#include "AComponent.hpp"

template <class T>
class C_EnemyAmmo : public AComponent<T> {
public:
    C_EnemyAmmo(T arg_n) :
        AComponent<T>(arg_n) {}

    C_EnemyAmmo() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_EnemyAmmo);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_EnemyAmmo>(*this);
    }
};
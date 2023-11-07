#pragma once

#include "AComponent.hpp"

template <class T>
class C_Ammo : public AComponent<T> {
public:
    C_Ammo(T arg_n) :
        AComponent<T>(arg_n) {}

    C_Ammo() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Ammo);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Ammo>(*this);
    }
};
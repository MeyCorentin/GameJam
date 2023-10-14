#pragma once

#include "Component.hpp"

template <class T>
class C_Ammo : public Component<T> {
public:
    C_Ammo(T arg_n) :
        Component<T>(arg_n) {}

    C_Ammo() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Ammo);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Ammo>(*this);
    }
};
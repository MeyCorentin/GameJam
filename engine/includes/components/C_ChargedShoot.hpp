#pragma once

#include "Component.hpp"

template <class T>
class C_ChargedShoot : public Component<T> {
public:
    C_ChargedShoot(T n) : Component<T>(n) {}
    C_ChargedShoot() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_ChargedShoot);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_ChargedShoot>(*this);
    }
};
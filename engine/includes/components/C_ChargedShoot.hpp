#pragma once

#include "AComponent.hpp"

template <class T>
class C_ChargedShoot : public AComponent<T> {
public:
    C_ChargedShoot(T n) : AComponent<T>(n) {}
    C_ChargedShoot() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_ChargedShoot);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_ChargedShoot>(*this);
    }
};
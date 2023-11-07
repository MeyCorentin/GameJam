#pragma once

#include "AComponent.hpp"

template <class T>
class C_BonusPower : public AComponent<T> {
public:
    C_BonusPower(T n) : AComponent<T>(n) {}
    C_BonusPower() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_BonusPower);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_BonusPower>(*this);
    }
};
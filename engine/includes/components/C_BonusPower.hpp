#pragma once

#include "Component.hpp"

template <class T>
class C_BonusPower : public Component<T> {
public:
    C_BonusPower(T n) : Component<T>(n) {}
    C_BonusPower() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_BonusPower);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_BonusPower>(*this);
    }
};
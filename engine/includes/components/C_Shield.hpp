#pragma once

#include "Component.hpp"

template <class T>
class C_Shield : public Component<T> {
public:
    C_Shield(T n) : Component<T>(n) {}
    C_Shield() : Component<T>() {}
    const std::type_info& getType() const override {
        return typeid(C_Shield);
    }
    std::shared_ptr<ComponentBase> clone() const override {
        return std::make_shared<C_Shield>(*this);
    }
};
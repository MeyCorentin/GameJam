#pragma once

#include "Component.hpp"

template <class T>
class C_Direction : public Component<T> {
public:
    C_Direction(T n) : Component<T>(n) {}
    C_Direction() : Component<T>() {}
    const std::type_info& getType() const override {
        return typeid(C_Direction);
    }
    std::shared_ptr<ComponentBase> clone() const override {
        return std::make_shared<C_Direction>(*this);
    }
};
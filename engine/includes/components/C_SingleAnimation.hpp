#pragma once

#include "Component.hpp"

template <class T>
class C_SingleAnimation : public Component<T> {
public:
    C_SingleAnimation(T n) : Component<T>(n) {}
    C_SingleAnimation() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_SingleAnimation);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_SingleAnimation>(*this);
    }
};
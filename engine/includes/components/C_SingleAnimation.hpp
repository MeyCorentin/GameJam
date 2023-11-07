#pragma once

#include "AComponent.hpp"

template <class T>
class C_SingleAnimation : public AComponent<T> {
public:
    C_SingleAnimation(T n) : AComponent<T>(n) {}
    C_SingleAnimation() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_SingleAnimation);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_SingleAnimation>(*this);
    }
};
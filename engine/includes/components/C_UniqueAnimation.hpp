#pragma once

#include "AComponent.hpp"

template <class T>
class C_UniqueAnimation : public AComponent<T> {
public:
    C_UniqueAnimation(T n) : AComponent<T>(n) {}
    C_UniqueAnimation() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_UniqueAnimation);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_UniqueAnimation>(*this);
    }
};
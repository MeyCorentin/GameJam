#pragma once

#include "Component.hpp"

template <class T>
class C_UniqueAnimation : public Component<T> {
public:
    C_UniqueAnimation(T n) : Component<T>(n) {}
    C_UniqueAnimation() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_UniqueAnimation);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_UniqueAnimation>(*this);
    }
};
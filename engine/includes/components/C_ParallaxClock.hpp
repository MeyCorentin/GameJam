#pragma once

#include "Component.hpp"

template <class T>
class C_ParallaxClock : public Component<T> {
public:
    C_ParallaxClock(T n) : Component<T>(n) {}
    C_ParallaxClock() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_ParallaxClock);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_ParallaxClock>(*this);
    }
};
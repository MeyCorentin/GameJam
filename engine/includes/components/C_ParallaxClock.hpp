#pragma once

#include "AComponent.hpp"

template <class T>
class C_ParallaxClock : public AComponent<T> {
public:
    C_ParallaxClock(T n) : AComponent<T>(n) {}
    C_ParallaxClock() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_ParallaxClock);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_ParallaxClock>(*this);
    }
};
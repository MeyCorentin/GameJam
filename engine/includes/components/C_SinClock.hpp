#pragma once

#include "AComponent.hpp"

template <class T>
class C_SinClock : public AComponent<T> {
public:
    C_SinClock(T n) : AComponent<T>(n) {}
    C_SinClock() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_SinClock);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_SinClock>(*this);
    }
};
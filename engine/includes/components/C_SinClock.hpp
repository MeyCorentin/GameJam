#pragma once

#include "Component.hpp"

template <class T>
class C_SinClock : public Component<T> {
public:
    C_SinClock(T n) : Component<T>(n) {}
    C_SinClock() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_SinClock);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_SinClock>(*this);
    }
};
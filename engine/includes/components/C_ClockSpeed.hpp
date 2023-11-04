#pragma once

#include "Component.hpp"

template <class T>
class C_ClockSpeed : public Component<T> {
public:
    C_ClockSpeed(T n) : Component<T>(n) {}
    C_ClockSpeed() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_ClockSpeed);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_ClockSpeed>(*this);
    }
};
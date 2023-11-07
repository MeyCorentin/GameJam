#pragma once

#include "AComponent.hpp"

template <class T>
class C_ClockSpeed : public AComponent<T> {
public:
    C_ClockSpeed(T n) : AComponent<T>(n) {}
    C_ClockSpeed() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_ClockSpeed);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_ClockSpeed>(*this);
    }
};
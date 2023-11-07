#pragma once

#include "AComponent.hpp"

template <class T>
class C_Clock : public AComponent<T> {
public:
    C_Clock(T n) : AComponent<T>(n) {}
    C_Clock() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Clock);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Clock>(*this);
    }
};
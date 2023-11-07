#pragma once

#include "AComponent.hpp"

template <class T>
class C_Follow : public AComponent<T> {
public:
    C_Follow(T n) : AComponent<T>(n) {}
    C_Follow() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Follow);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Follow>(*this);
    }
};
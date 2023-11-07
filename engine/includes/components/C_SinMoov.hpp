#pragma once

#include "AComponent.hpp"

template <class T>
class C_SinMoov : public AComponent<T> {
public:
    C_SinMoov(T n) : AComponent<T>(n) {}
    C_SinMoov() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_SinMoov);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_SinMoov>(*this);
    }
};
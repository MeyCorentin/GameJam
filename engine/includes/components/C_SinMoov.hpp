#pragma once

#include "Component.hpp"

template <class T>
class C_SinMoov : public Component<T> {
public:
    C_SinMoov(T n) : Component<T>(n) {}
    C_SinMoov() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_SinMoov);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_SinMoov>(*this);
    }
};
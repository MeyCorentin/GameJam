#pragma once

#include "Component.hpp"

template <class T>
class C_Clock : public Component<T> {
public:
    C_Clock(T n) : Component<T>(n) {}
    C_Clock() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Clock);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Clock>(*this);
    }
};
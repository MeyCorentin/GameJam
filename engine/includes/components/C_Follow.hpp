#pragma once

#include "Component.hpp"

template <class T>
class C_Follow : public Component<T> {
public:
    C_Follow(T n) : Component<T>(n) {}
    C_Follow() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Follow);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Follow>(*this);
    }
};
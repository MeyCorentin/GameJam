#pragma once

#include "Component.hpp"

template <class T>
class C_Animation : public Component<T> {
public:
    C_Animation(T n) : Component<T>(n) {}
    C_Animation() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Animation);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Animation>(*this);
    }
};
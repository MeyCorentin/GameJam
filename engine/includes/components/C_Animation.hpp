#pragma once

#include "AComponent.hpp"

template <class T>
class C_Animation : public AComponent<T> {
public:
    C_Animation(T n) : AComponent<T>(n) {}
    C_Animation() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Animation);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Animation>(*this);
    }
};
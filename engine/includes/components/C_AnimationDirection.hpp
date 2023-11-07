#pragma once

#include "AComponent.hpp"

template <class T>
class C_AnimationDirection : public AComponent<T> {
public:
    C_AnimationDirection(T arg_n) :
        AComponent<T>(arg_n) {}

    C_AnimationDirection() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_AnimationDirection);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_AnimationDirection>(*this);
    }
};
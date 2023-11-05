#pragma once

#include "Component.hpp"

template <class T>
class C_AnimationDirection : public Component<T> {
public:
    C_AnimationDirection(T arg_n) :
        Component<T>(arg_n) {}

    C_AnimationDirection() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_AnimationDirection);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_AnimationDirection>(*this);
    }
};
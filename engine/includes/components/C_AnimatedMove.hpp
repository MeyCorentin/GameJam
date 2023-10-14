#pragma once

#include "Component.hpp"

template <class T>
class C_AnimatedMove : public Component<T> {
public:
    C_AnimatedMove(T n) : Component<T>(n) {}
    C_AnimatedMove() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_AnimatedMove);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_AnimatedMove>(*this);
    }
};
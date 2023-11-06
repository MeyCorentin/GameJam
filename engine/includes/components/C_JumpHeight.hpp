#pragma once

#include "Component.hpp"

template <class T>
class C_JumpHeight : public Component<T> {
public:
    C_JumpHeight(T arg_n) :
        Component<T>(arg_n) {}

    C_JumpHeight() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_JumpHeight);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_JumpHeight>(*this);
    }
};
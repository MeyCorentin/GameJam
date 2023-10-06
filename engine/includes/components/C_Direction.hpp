#pragma once

#include "Component.hpp"

template <class T>
class C_Direction : public Component<T> {
public:
    C_Direction(T arg_n) :
        Component<T>(arg_n) {}

    C_Direction() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Direction);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Direction>(*this);
    }
};
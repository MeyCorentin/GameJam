#pragma once

#include "Component.hpp"

template <class T>
class C_PositionStart : public Component<T> {
public:
    C_PositionStart(T arg_n) :
        Component<T>(arg_n) {}

    C_PositionStart() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_PositionStart);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_PositionStart>(*this);
    }
};
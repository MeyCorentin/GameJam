#pragma once

#include "Component.hpp"

template <class T>
class C_PositionEnd : public Component<T> {
public:
    C_PositionEnd(T arg_n) :
        Component<T>(arg_n) {}

    C_PositionEnd() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_PositionEnd);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_PositionEnd>(*this);
    }
};
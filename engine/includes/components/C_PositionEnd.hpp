#pragma once

#include "AComponent.hpp"

template <class T>
class C_PositionEnd : public AComponent<T> {
public:
    C_PositionEnd(T arg_n) :
        AComponent<T>(arg_n) {}

    C_PositionEnd() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_PositionEnd);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_PositionEnd>(*this);
    }
};
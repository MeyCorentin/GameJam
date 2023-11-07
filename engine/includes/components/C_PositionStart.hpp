#pragma once

#include "AComponent.hpp"

template <class T>
class C_PositionStart : public AComponent<T> {
public:
    C_PositionStart(T arg_n) :
        AComponent<T>(arg_n) {}

    C_PositionStart() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_PositionStart);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_PositionStart>(*this);
    }
};
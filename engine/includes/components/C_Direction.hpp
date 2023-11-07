#pragma once

#include "AComponent.hpp"

template <class T>
class C_Direction : public AComponent<T> {
public:
    C_Direction(T arg_n) :
        AComponent<T>(arg_n) {}

    C_Direction() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Direction);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Direction>(*this);
    }
};
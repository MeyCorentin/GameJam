#pragma once

#include "AComponent.hpp"

template <class T>
class C_Jump : public AComponent<T> {
public:
    C_Jump(T arg_n) :
        AComponent<T>(arg_n) {}

    C_Jump() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Jump);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Jump>(*this);
    }
};
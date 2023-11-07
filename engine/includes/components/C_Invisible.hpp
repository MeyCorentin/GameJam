#pragma once

#include "AComponent.hpp"

template <class T>
class C_Invisible : public AComponent<T> {
public:
    C_Invisible(T arg_n) :
        AComponent<T>(arg_n) {}

    C_Invisible() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Invisible);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Invisible>(*this);
    }
};
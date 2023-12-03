#pragma once

#include "AComponent.hpp"

template <class T>
class C_IsFighting : public AComponent<T> {
public:
    C_IsFighting(T arg_n) :
        AComponent<T>(arg_n) {}

    C_IsFighting() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_IsFighting);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_IsFighting>(*this);
    }
};
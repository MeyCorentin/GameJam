#pragma once

#include "AComponent.hpp"

template <class T>
class C_Range : public AComponent<T> {
public:
    C_Range(T n) : AComponent<T>(n) {}
    C_Range() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Range);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Range>(*this);
    }
};
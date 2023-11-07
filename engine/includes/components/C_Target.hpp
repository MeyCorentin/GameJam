#pragma once

#include "AComponent.hpp"

template <class T>
class C_Target : public AComponent<T> {
public:
    C_Target(T n) : AComponent<T>(n) {}
    C_Target() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Target);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Target>(*this);
    }
};
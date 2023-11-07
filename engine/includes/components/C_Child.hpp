#pragma once

#include "AComponent.hpp"

template <class T>
class C_Child : public AComponent<T> {
public:
    C_Child(T n) : AComponent<T>(n) {}
    C_Child() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Child);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Child>(*this);
    }
};
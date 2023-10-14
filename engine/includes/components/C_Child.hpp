#pragma once

#include "Component.hpp"

template <class T>
class C_Child : public Component<T> {
public:
    C_Child(T n) : Component<T>(n) {}
    C_Child() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Child);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Child>(*this);
    }
};
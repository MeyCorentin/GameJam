#pragma once

#include "Component.hpp"

template <class T>
class C_Target : public Component<T> {
public:
    C_Target(T n) : Component<T>(n) {}
    C_Target() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Target);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Target>(*this);
    }
};
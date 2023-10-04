#pragma once

#include "Component.hpp"

template <class T>
class C_Server : public Component<T> {
public:
    C_Server(T n) : Component<T>(n) {}
    C_Server() : Component<T>() {}
    const std::type_info& getType() const override {
        return typeid(C_Server);
    }
    std::shared_ptr<ComponentBase> clone() const override {
        return std::make_shared<C_Server>(*this);
    }
};
#pragma once

#include "Component.hpp"

template <class T>
class C_Client : public Component<T> {
public:
    C_Client(T n) : Component<T>(n) {}
    C_Client() : Component<T>() {}
    const std::type_info& getType() const override {
        return typeid(C_Client);
    }
    std::shared_ptr<ComponentBase> clone() const override {
        return std::make_shared<C_Client>(*this);
    }
};
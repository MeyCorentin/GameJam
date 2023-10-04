#pragma once

#include "Component.hpp"

template <class T>
class C_Client : public Component<T> {
public:
    C_Client(T arg_n) :
        Component<T>(arg_n) {}

    C_Client() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Client);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Client>(*this);
    }
};
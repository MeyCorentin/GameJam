#pragma once

#include "AComponent.hpp"

template <class T>
class C_Client : public AComponent<T> {
public:
    C_Client(T arg_n) :
        AComponent<T>(arg_n) {}

    C_Client() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Client);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Client>(*this);
    }
};
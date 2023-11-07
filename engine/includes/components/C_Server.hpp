#pragma once

#include "AComponent.hpp"

template <class T>
class C_Server : public AComponent<T> {
    public:
        C_Server(T arg_n) :
            AComponent<T>(arg_n) {}

        C_Server() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Server);
        }

        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_Server>(*this);
        }
};
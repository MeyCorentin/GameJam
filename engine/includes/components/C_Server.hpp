#pragma once

#include "Component.hpp"

template <class T>
class C_Server : public Component<T> {
    public:
        C_Server(T arg_n) :
            Component<T>(arg_n) {}

        C_Server() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Server);
        }

        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_Server>(*this);
        }
};
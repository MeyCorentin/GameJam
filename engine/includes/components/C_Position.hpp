#pragma once

#include "Component.hpp"

template <class T>
class C_Position : public Component<T> {
    public:
        C_Position(T arg_n) :
            Component<T>(arg_n) {}

        C_Position() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Position);
        }

        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_Position>(*this);
        }
};
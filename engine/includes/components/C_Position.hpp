#pragma once

#include "AComponent.hpp"

template <class T>
class C_Position : public AComponent<T> {
    public:
        C_Position(T arg_n) :
            AComponent<T>(arg_n) {}

        C_Position() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Position);
        }

        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_Position>(*this);
        }
};
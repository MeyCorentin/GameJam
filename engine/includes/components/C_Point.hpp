#pragma once

#include "AComponent.hpp"

template <class T>
class C_Point : public AComponent<T> {
    public:
        C_Point(T arg_n) :
            AComponent<T>(arg_n) {}

        C_Point() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Point);
        }

        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_Point>(*this);
        }
};
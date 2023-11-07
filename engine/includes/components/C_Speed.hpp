#pragma once

#include "AComponent.hpp"

template <class T>
class C_Speed : public AComponent<T> {
    public:
        C_Speed(T arg_n) :
            AComponent<T>(arg_n) {}

        C_Speed() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Speed);
        }
        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_Speed>(*this);
        }
};
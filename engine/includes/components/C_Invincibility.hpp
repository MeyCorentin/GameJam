#pragma once

#include "AComponent.hpp"

template <class T>
class C_Invincibility : public AComponent<T> {
    public:
        C_Invincibility(T arg_n) :
            AComponent<T>(arg_n) {}

        C_Invincibility() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Invincibility);
        }
        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_Invincibility>(*this);
        }
};
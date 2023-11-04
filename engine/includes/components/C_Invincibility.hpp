#pragma once

#include "Component.hpp"

template <class T>
class C_Invincibility : public Component<T> {
    public:
        C_Invincibility(T arg_n) :
            Component<T>(arg_n) {}

        C_Invincibility() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Invincibility);
        }
        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_Invincibility>(*this);
        }
};
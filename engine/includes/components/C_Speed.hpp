#pragma once

#include "Component.hpp"

template <class T>
class C_Speed : public Component<T> {
    public:
        C_Speed(T arg_n) :
            Component<T>(arg_n) {}

        C_Speed() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Speed);
        }
        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_Speed>(*this);
        }
};
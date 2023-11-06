#pragma once

#include "Component.hpp"

template <class T>
class C_Text : public Component<T> {
    public:
        C_Text(T arg_n) :
            Component<T>(arg_n) {}

        C_Text() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Text);
        }
        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_Text>(*this);
        }
};
#pragma once

#include "AComponent.hpp"

template <class T>
class C_Text : public AComponent<T> {
    public:
        C_Text(T arg_n) :
            AComponent<T>(arg_n) {}

        C_Text() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Text);
        }
        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_Text>(*this);
        }
};
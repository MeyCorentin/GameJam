#pragma once

#include "AComponent.hpp"

template <class T>
class C_TextMessage : public AComponent<T> {
    public:
        C_TextMessage(T arg_n) :
            AComponent<T>(arg_n) {}

        C_TextMessage() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_TextMessage);
        }
        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_TextMessage>(*this);
        }
};
#pragma once

#include "Component.hpp"

template <class T>
class C_TextMessage : public Component<T> {
    public:
        C_TextMessage(T arg_n) :
            Component<T>(arg_n) {}

        C_TextMessage() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_TextMessage);
        }
        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_TextMessage>(*this);
        }
};
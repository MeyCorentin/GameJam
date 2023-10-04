#pragma once

#include "Component.hpp"

template <class T>
class C_Player : public Component<T> {
    public:
        C_Player(T arg_n) :
            Component<T>(arg_n) {}

        C_Player() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Player);
        }
        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_Player>(*this);
        }
};
#pragma once

#include "AComponent.hpp"

template <class T>
class C_Player : public AComponent<T> {
    public:
        C_Player(T arg_n) :
            AComponent<T>(arg_n) {}

        C_Player() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Player);
        }
        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_Player>(*this);
        }
};
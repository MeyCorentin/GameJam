#pragma once

#include "AComponent.hpp"

template <class T>
class C_Hitbox : public AComponent<T> {
public:
    C_Hitbox(T arg_n) :
        AComponent<T>(arg_n) {}

    C_Hitbox() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Hitbox);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Hitbox>(*this);
    }
};
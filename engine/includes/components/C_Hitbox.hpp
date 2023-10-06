#pragma once

#include "Component.hpp"

template <class T>
class C_Hitbox : public Component<T> {
public:
    C_Hitbox(T arg_n) :
        Component<T>(arg_n) {}

    C_Hitbox() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Hitbox);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Hitbox>(*this);
    }
};
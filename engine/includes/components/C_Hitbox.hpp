#pragma once

#include "Component.hpp"

template <class T>
class C_Hitbox : public Component<T> {
public:
    C_Hitbox(T n) : Component<T>(n) {}
    C_Hitbox() : Component<T>() {}
    const std::type_info& getType() const override {
        return typeid(C_Hitbox);
    }
    std::shared_ptr<ComponentBase> clone() const override {
        return std::make_shared<C_Hitbox>(*this);
    }
};
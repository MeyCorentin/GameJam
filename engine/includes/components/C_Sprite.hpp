#pragma once

#include "Component.hpp"

template <class T>
class C_Sprite : public Component<T> {
public:
    C_Sprite(T n) : Component<T>(n) {}
    C_Sprite() : Component<T>() {}
    const std::type_info& getType() const override {
        return typeid(C_Sprite);
    }
    std::shared_ptr<ComponentBase> clone() const override {
        return std::make_shared<C_Sprite>(*this);
    }
};
#pragma once

#include "Component.hpp"

template <class T>
class C_SpriteRect : public Component<T> {
public:
    C_SpriteRect(T n) : Component<T>(n) {}
    C_SpriteRect() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_SpriteRect);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_SpriteRect>(*this);
    }
};
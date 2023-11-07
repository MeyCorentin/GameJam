#pragma once

#include "AComponent.hpp"

template <class T>
class C_SpriteRect : public AComponent<T> {
public:
    C_SpriteRect(T n) : AComponent<T>(n) {}
    C_SpriteRect() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_SpriteRect);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_SpriteRect>(*this);
    }
};
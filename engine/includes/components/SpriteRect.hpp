#pragma once

#include "TComponent.hpp"

template <class T>
class SpriteRect : public TComponent<T> {
public:
    SpriteRect(T n) : TComponent<T>(n) {}
    SpriteRect() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(SpriteRect);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<SpriteRect>(*this);
    }
};
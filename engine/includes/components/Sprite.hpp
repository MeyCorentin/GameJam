#pragma once

#include "TComponent.hpp"

template <class T>
class Sprite : public TComponent<T> {
public:
    Sprite(T n) : TComponent<T>(n) {}
    Sprite() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(Sprite);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Sprite>(*this);
    }
};
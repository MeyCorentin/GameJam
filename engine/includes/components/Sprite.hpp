#pragma once

#include "TComponent.hpp"

template <class T>
class Sprite : public TComponent<T> {
public:
    Sprite(T n) : TComponent<T>(n) {}
    const std::type_info& getType() const override {
        return typeid(Sprite);
    }
};
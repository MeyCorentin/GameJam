#pragma once

#include "TComponent.hpp"

template <class T>
class Hitbox : public TComponent<T> {
public:
    Hitbox(T n) : TComponent<T>(n) {}
    Hitbox() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(Hitbox);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Hitbox>(*this);
    }
};
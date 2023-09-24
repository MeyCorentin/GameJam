#pragma once

#include "TComponent.hpp"

template <class T>
class Player : public TComponent<T> {
public:
    Player(T n) : TComponent<T>(n) {}
    const std::type_info& getType() const override {
        return typeid(Player);
    }
};
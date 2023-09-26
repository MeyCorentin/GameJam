#pragma once

#include "TComponent.hpp"

template <class T>
class Player : public TComponent<T> {
public:
    Player(T n) : TComponent<T>(n) {}
    Player() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(Player);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Player>(*this);
    }
};
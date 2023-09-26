#pragma once

#include "TComponent.hpp"

template <class T>
class Player : public TComponent<T> {
public:
    Player(T n) : TComponent<T>(n) {}
<<<<<<< HEAD
    Player() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(Player);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Player>(*this);
    }
=======
    const std::type_info& getType() const override {
        return typeid(Player);
    }
>>>>>>> a5a4786374f43f10e1597baecd486ba09e0e679c
};
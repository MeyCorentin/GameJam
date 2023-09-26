#pragma once

#include "TComponent.hpp"

template <class T>
class Position : public TComponent<T> {
public:
    Position(T n) : TComponent<T>(n) {}
<<<<<<< HEAD
    Position() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(Position);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Position>(*this);
    }
=======
    const std::type_info& getType() const override {
        return typeid(Position);
    }
>>>>>>> a5a4786374f43f10e1597baecd486ba09e0e679c
};
#pragma once

#include "TComponent.hpp"

template <class T>
class Position : public TComponent<T> {
public:
    Position(T n) : TComponent<T>(n) {}
    Position() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(Position);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Position>(*this);
    }
};
#pragma once

#include "TComponent.hpp"

template <class T>
class Direction : public TComponent<T> {
public:
    Direction(T n) : TComponent<T>(n) {}
    Direction() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(Direction);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Direction>(*this);
    }
};
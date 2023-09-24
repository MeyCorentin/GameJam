#pragma once

#include "TComponent.hpp"

template <class T>
class Position : public TComponent<T> {
public:
    Position(T n) : TComponent<T>(n) {}
    const std::type_info& getType() const override {
        return typeid(Position);
    }
};
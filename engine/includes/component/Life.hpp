#pragma once

#include "TComponent.hpp"

template <class T>
class Life : public TComponent<T> {
public:
    Life(T n) : TComponent<T>(n) {}
    const std::type_info& getType() const override {
        return typeid(Life);
    }
};
#pragma once

#include "TComponent.hpp"

template <class T>
class Damage : public TComponent<T> {
public:
    Damage(T n) : TComponent<T>(n) {}
};
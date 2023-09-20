#pragma once

#include "../main.hpp"
#include "TComponentBase.hpp"

template <class T>
class TComponent: public TComponentBase {
    private:
    T value;

    public:
        TComponent(T n) : value(n) {}

        T getValue() {
            return value;
        }

        void setValue(T newValue) {
            value = newValue;
        }
};

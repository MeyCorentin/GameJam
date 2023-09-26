#pragma once

#include "../main.hpp"
#include "TComponentBase.hpp"

template <class T>
class TComponent: public TComponentBase {
    private:
    T value;
<<<<<<< HEAD
    const std::type_info& originalType;

    public:
        TComponent(T n) : value(n), originalType(typeid(*this)) {}
        TComponent() : value(), originalType(typeid(*this)) {}
        const std::type_info& getType() const override {
            return originalType;
        }
=======

    public:
        TComponent(T n) : value(n) {}
>>>>>>> a5a4786374f43f10e1597baecd486ba09e0e679c

        T &getValue() {
            return value;
        }
<<<<<<< HEAD
        void setValue(T newValue) {
            value = newValue;
        };
        std::shared_ptr<TComponentBase> clone() const override {
            return std::make_shared<TComponent>(*this);
=======

        void setValue(T newValue) {
            value = newValue;
>>>>>>> a5a4786374f43f10e1597baecd486ba09e0e679c
        }
};

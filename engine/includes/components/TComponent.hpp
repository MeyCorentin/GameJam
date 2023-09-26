#pragma once

#include "../main.hpp"
#include "TComponentBase.hpp"

template <class T>
class TComponent: public TComponentBase {
    private:
    T value;
    const std::type_info& originalType;

    public:
        TComponent(T n) : value(n), originalType(typeid(*this)) {}
        TComponent() : value(), originalType(typeid(*this)) {}
        const std::type_info& getType() const override {
            return originalType;
        }

        T &getValue() {
            return value;
        }
        void setValue(T newValue) {
            value = newValue;
        };
        std::shared_ptr<TComponentBase> clone() const override {
            return std::make_shared<TComponent>(*this);
        }
};

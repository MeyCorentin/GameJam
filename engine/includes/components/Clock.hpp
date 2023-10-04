#pragma once

#include "TComponent.hpp"

template <class T>
class Clock : public TComponent<T> {
public:
    Clock(T n) : TComponent<T>(n) {}
    Clock() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(Clock);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Clock>(*this);
    }
};
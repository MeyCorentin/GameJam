#pragma once

#include "TComponent.hpp"

template <class T>
class Speed : public TComponent<T> {
public:
    Speed(T n) : TComponent<T>(n) {}
    Speed() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(Speed);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Speed>(*this);
    }
};
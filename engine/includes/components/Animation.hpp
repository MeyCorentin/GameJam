#pragma once

#include "TComponent.hpp"

template <class T>
class Animation : public TComponent<T> {
public:
    Animation(T n) : TComponent<T>(n) {}
    Animation() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(Animation);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Animation>(*this);
    }
};
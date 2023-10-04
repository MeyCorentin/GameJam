#pragma once

#include "TComponent.hpp"

template <class T>
class Size : public TComponent<T> {
public:
    Size(T n) : TComponent<T>(n) {}
    Size() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(Size);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Size>(*this);
    }
};
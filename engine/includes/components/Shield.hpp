#pragma once

#include "TComponent.hpp"

template <class T>
class Shield : public TComponent<T> {
public:
    Shield(T n) : TComponent<T>(n) {}
    Shield() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(Shield);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Shield>(*this);
    }
};
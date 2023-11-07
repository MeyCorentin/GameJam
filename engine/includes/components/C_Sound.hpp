#pragma once

#include "AComponent.hpp"

template <class T>
class C_Sound : public AComponent<T> {
public:
    C_Sound(T n) : AComponent<T>(n) {}
    C_Sound() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Sound);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Sound>(*this);
    }
};
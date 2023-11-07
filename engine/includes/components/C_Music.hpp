#pragma once

#include "AComponent.hpp"

template <class T>
class C_Music : public AComponent<T> {
public:
    C_Music(T n) : AComponent<T>(n) {}
    C_Music() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Music);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Music>(*this);
    }
};
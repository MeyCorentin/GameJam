#pragma once

#include "AComponent.hpp"

template <class T>
class C_SoundIsActive : public AComponent<T> {
public:
    C_SoundIsActive(T n) : AComponent<T>(n) {}
    C_SoundIsActive() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_SoundIsActive);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_SoundIsActive>(*this);
    }
};
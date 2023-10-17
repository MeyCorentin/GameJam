#pragma once

#include "Component.hpp"

template <class T>
class C_SoundIsActive : public Component<T> {
public:
    C_SoundIsActive(T n) : Component<T>(n) {}
    C_SoundIsActive() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_SoundIsActive);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_SoundIsActive>(*this);
    }
};
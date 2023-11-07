#pragma once

#include "AComponent.hpp"

template <class T>
class C_SoundBuffer : public AComponent<T> {
public:
    C_SoundBuffer(T n) : AComponent<T>(n) {}
    C_SoundBuffer() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_SoundBuffer);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_SoundBuffer>(*this);
    }
};
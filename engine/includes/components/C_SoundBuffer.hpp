#pragma once

#include "Component.hpp"

template <class T>
class C_SoundBuffer : public Component<T> {
public:
    C_SoundBuffer(T n) : Component<T>(n) {}
    C_SoundBuffer() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_SoundBuffer);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_SoundBuffer>(*this);
    }
};
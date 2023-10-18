#pragma once

#include "Component.hpp"

template <class T>
class C_Music : public Component<T> {
public:
    C_Music(T n) : Component<T>(n) {}
    C_Music() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Music);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Music>(*this);
    }
};
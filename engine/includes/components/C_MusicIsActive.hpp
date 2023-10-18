#pragma once

#include "Component.hpp"

template <class T>
class C_MusicIsActive : public Component<T> {
public:
    C_MusicIsActive(T n) : Component<T>(n) {}
    C_MusicIsActive() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_MusicIsActive);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_MusicIsActive>(*this);
    }
};
#pragma once

#include "Component.hpp"

template <class T>
class C_RespawnPosition : public Component<T> {
public:
    C_RespawnPosition(T n) : Component<T>(n) {}
    C_RespawnPosition() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_RespawnPosition);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_RespawnPosition>(*this);
    }
};
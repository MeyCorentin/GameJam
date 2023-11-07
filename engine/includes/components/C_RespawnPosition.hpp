#pragma once

#include "AComponent.hpp"

template <class T>
class C_RespawnPosition : public AComponent<T> {
public:
    C_RespawnPosition(T n) : AComponent<T>(n) {}
    C_RespawnPosition() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_RespawnPosition);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_RespawnPosition>(*this);
    }
};
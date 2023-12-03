#pragma once

#include "AComponent.hpp"

template <class T>
class C_SpawnClock : public AComponent<T> {
public:
    C_SpawnClock(T n) : AComponent<T>(n) {}
    C_SpawnClock() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_SpawnClock);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_SpawnClock>(*this);
    }
};
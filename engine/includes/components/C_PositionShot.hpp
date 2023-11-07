#pragma once

#include "AComponent.hpp"

template <class T>
class C_PositionShot : public AComponent<T> {
public:
    C_PositionShot(T n) : AComponent<T>(n) {}
    C_PositionShot() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_PositionShot);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_PositionShot>(*this);
    }
};
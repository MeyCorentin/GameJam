#pragma once

#include "Component.hpp"

template <class T>
class C_PositionShot : public Component<T> {
public:
    C_PositionShot(T n) : Component<T>(n) {}
    C_PositionShot() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_PositionShot);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_PositionShot>(*this);
    }
};
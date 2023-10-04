#pragma once

#include "Component.hpp"

template <class T>
class C_Player : public Component<T> {
public:
    C_Player(T n) : Component<T>(n) {}
    C_Player() : Component<T>() {}
    const std::type_info& getType() const override {
        return typeid(C_Player);
    }
    std::shared_ptr<ComponentBase> clone() const override {
        return std::make_shared<C_Player>(*this);
    }
};
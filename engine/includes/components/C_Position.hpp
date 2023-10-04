#pragma once

#include "Component.hpp"

template <class T>
class C_Position : public Component<T> {
public:
    C_Position(T n) : Component<T>(n) {}
    C_Position() : Component<T>() {}
    const std::type_info& getType() const override {
        return typeid(C_Position);
    }
    std::shared_ptr<ComponentBase> clone() const override {
        return std::make_shared<C_Position>(*this);
    }
};
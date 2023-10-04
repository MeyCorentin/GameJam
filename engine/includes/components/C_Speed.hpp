#pragma once

#include "Component.hpp"

template <class T>
class C_Speed : public Component<T> {
public:
    C_Speed(T n) : Component<T>(n) {}
    C_Speed() : Component<T>() {}
    const std::type_info& getType() const override {
        return typeid(C_Speed);
    }
    std::shared_ptr<ComponentBase> clone() const override {
        return std::make_shared<C_Speed>(*this);
    }
};
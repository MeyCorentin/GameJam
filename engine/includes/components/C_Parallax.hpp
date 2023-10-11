#pragma once

#include "Component.hpp"

template <class T>
class C_Parallax : public Component<T> {
public:
    C_Parallax(T n) : Component<T>(n) {}
    C_Parallax() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Parallax);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Parallax>(*this);
    }
};
#pragma once

#include "Component.hpp"

template <class T>
class C_Texture : public Component<T> {
public:
    C_Texture(T n) : Component<T>(n) {}
    C_Texture() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Texture);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Texture>(*this);
    }
};
#pragma once

#include "AComponent.hpp"

template <class T>
class C_Texture : public AComponent<T> {
public:
    C_Texture(T n) : AComponent<T>(n) {}
    C_Texture() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Texture);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Texture>(*this);
    }
};
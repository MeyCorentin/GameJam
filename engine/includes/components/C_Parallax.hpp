#pragma once

#include "AComponent.hpp"

template <class T>
class C_Parallax : public AComponent<T> {
public:
    C_Parallax(T n) : AComponent<T>(n) {}
    C_Parallax() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Parallax);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Parallax>(*this);
    }
};
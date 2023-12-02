#pragma once

#include "AComponent.hpp"

template <class T>
class C_Button : public AComponent<T> {
public:
    C_Button(T n) : AComponent<T>(n) {}
    C_Button() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Button);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Button>(*this);
    }
};
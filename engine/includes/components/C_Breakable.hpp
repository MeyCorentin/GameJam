#pragma once

#include "AComponent.hpp"

template <class T>
class C_Breakable : public AComponent<T> {
public:
    C_Breakable(T n) : AComponent<T>(n) {}
    C_Breakable() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Breakable);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Breakable>(*this);
    }
};
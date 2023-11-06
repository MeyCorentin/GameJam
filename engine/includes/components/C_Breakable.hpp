#pragma once

#include "Component.hpp"

template <class T>
class C_Breakable : public Component<T> {
public:
    C_Breakable(T n) : Component<T>(n) {}
    C_Breakable() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Breakable);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Breakable>(*this);
    }
};
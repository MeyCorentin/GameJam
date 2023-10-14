#pragma once

#include "Component.hpp"

template <class T>
class C_Admin : public Component<T> {
public:
    C_Admin(T n) : Component<T>(n) {}
    C_Admin() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Admin);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Admin>(*this);
    }
};
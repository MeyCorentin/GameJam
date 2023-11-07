#pragma once

#include "AComponent.hpp"

template <class T>
class C_Admin : public AComponent<T> {
public:
    C_Admin(T n) : AComponent<T>(n) {}
    C_Admin() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Admin);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Admin>(*this);
    }
};
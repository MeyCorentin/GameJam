#pragma once

#include "AComponent.hpp"

template <class T>
class C_Attack : public AComponent<T> {
public:
    C_Attack(T n) : AComponent<T>(n) {}
    C_Attack() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Attack);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Attack>(*this);
    }
};
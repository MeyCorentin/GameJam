#pragma once

#include "AComponent.hpp"

template <class T>
class C_Inventory : public AComponent<T> {
public:
    C_Inventory(T n) : AComponent<T>(n) {}
    C_Inventory() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Inventory);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Inventory>(*this);
    }
};
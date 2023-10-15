#pragma once

#include "Component.hpp"

template <class T>
class C_Inventory : public Component<T> {
public:
    C_Inventory(T n) : Component<T>(n) {}
    C_Inventory() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Inventory);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Inventory>(*this);
    }
};
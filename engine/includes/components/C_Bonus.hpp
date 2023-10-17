#pragma once

#include "Component.hpp"

template <class T>
class C_Bonus : public Component<T> {
public:
    C_Bonus(T n) : Component<T>(n) {}
    C_Bonus() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Bonus);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Bonus>(*this);
    }
};
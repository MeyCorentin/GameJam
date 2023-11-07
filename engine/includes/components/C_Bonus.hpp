#pragma once

#include "AComponent.hpp"

template <class T>
class C_Bonus : public AComponent<T> {
public:
    C_Bonus(T n) : AComponent<T>(n) {}
    C_Bonus() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Bonus);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Bonus>(*this);
    }
};
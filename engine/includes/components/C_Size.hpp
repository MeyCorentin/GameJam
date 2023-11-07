#pragma once

#include "AComponent.hpp"

template <class T>
class C_Size : public AComponent<T> {
public:
    C_Size(T n) : AComponent<T>(n) {}
    C_Size() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Size);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Size>(*this);
    }
};
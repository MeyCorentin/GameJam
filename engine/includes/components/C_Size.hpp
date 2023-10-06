#pragma once

#include "Component.hpp"

template <class T>
class C_Size : public Component<T> {
public:
    C_Size(T n) : Component<T>(n) {}
    C_Size() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Size);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Size>(*this);
    }
};
#pragma once

#include "Component.hpp"

template <class T>
class C_Grounded : public Component<T> {
public:
    C_Grounded(T arg_n) :
        Component<T>(arg_n) {}

    C_Grounded() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Grounded);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Grounded>(*this);
    }
};
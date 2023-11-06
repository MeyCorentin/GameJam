#pragma once

#include "Component.hpp"

template <class T>
class C_Jump : public Component<T> {
public:
    C_Jump(T arg_n) :
        Component<T>(arg_n) {}

    C_Jump() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Jump);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Jump>(*this);
    }
};
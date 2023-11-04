#pragma once

#include "Component.hpp"

template <class T>
class C_Invisible : public Component<T> {
public:
    C_Invisible(T arg_n) :
        Component<T>(arg_n) {}

    C_Invisible() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Invisible);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Invisible>(*this);
    }
};
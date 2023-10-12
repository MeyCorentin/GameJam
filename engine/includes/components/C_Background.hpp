#pragma once

#include "Component.hpp"

template <class T>
class C_Background : public Component<T> {
public:
    C_Background(T arg_n) :
        Component<T>(arg_n) {}

    C_Background() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Background);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Background>(*this);
    }
};
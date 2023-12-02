#pragma once

#include "AComponent.hpp"

template <class T>
class C_Grass : public AComponent<T> {
public:
    C_Grass(T arg_n) :
        AComponent<T>(arg_n) {}

    C_Grass() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_Grass);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Grass>(*this);
    }
};
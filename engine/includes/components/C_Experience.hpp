#pragma once

#include "AComponent.hpp"

template <class T>
class C_Experience : public AComponent<T> {
public:
    C_Experience(T n) : AComponent<T>(n) {}
    C_Experience() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Experience);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Experience>(*this);
    }
};
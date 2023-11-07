#pragma once

#include "AComponent.hpp"

template <class T>
class C_Shield : public AComponent<T> {
    public:
        C_Shield(T arg_n) :
            AComponent<T>(arg_n) {}

        C_Shield() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Shield);
        }
        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_Shield>(*this);
        }
};
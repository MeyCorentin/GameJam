#pragma once

#include "Component.hpp"

template <class T>
class C_Shield : public Component<T> {
    public:
        C_Shield(T arg_n) :
            Component<T>(arg_n) {}

        C_Shield() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Shield);
        }
        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_Shield>(*this);
        }
};
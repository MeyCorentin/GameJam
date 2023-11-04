#pragma once

#include "Component.hpp"

template <class T>
class C_IsAutoMove : public Component<T> {
    public:
        C_IsAutoMove(T arg_n) :
            Component<T>(arg_n) {}

        C_IsAutoMove() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_IsAutoMove);
        }
        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_IsAutoMove>(*this);
        }
};
#pragma once

#include "AComponent.hpp"

template <class T>
class C_IsAutoMove : public AComponent<T> {
    public:
        C_IsAutoMove(T arg_n) :
            AComponent<T>(arg_n) {}

        C_IsAutoMove() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_IsAutoMove);
        }
        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_IsAutoMove>(*this);
        }
};
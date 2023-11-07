#pragma once

#include "AComponent.hpp"

template <class T>
class C_TimeAutoMove : public AComponent<T> {
    public:
        C_TimeAutoMove(T arg_n) :
            AComponent<T>(arg_n) {}

        C_TimeAutoMove() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_TimeAutoMove);
        }
        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_TimeAutoMove>(*this);
        }
};
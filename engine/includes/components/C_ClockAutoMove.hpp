#pragma once

#include "AComponent.hpp"

template <class T>
class C_ClockAutoMove : public AComponent<T> {
    public:
        C_ClockAutoMove(T arg_n) :
            AComponent<T>(arg_n) {}

        C_ClockAutoMove() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_ClockAutoMove);
        }
        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_ClockAutoMove>(*this);
        }
};
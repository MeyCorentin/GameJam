#pragma once

#include "Component.hpp"

template <class T>
class C_ClockAutoMove : public Component<T> {
    public:
        C_ClockAutoMove(T arg_n) :
            Component<T>(arg_n) {}

        C_ClockAutoMove() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_ClockAutoMove);
        }
        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_ClockAutoMove>(*this);
        }
};
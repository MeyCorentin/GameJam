#pragma once

#include "Component.hpp"

template <class T>
class C_TimeAutoMove : public Component<T> {
    public:
        C_TimeAutoMove(T arg_n) :
            Component<T>(arg_n) {}

        C_TimeAutoMove() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_TimeAutoMove);
        }
        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_TimeAutoMove>(*this);
        }
};
#pragma once

#include "AComponent.hpp"

template <class T>
class C_Score : public AComponent<T> {
    public:
        C_Score(T arg_n) :
            AComponent<T>(arg_n) {}

        C_Score() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Score);
        }

        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_Score>(*this);
        }
};
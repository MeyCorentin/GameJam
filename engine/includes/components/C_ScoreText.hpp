#pragma once

#include "AComponent.hpp"

template <class T>
class C_ScoreText : public AComponent<T> {
    public:
        C_ScoreText(T arg_n) :
            AComponent<T>(arg_n) {}

        C_ScoreText() :
            AComponent<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_ScoreText);
        }

        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<C_ScoreText>(*this);
        }
};
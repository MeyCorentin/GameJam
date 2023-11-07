#pragma once

#include "../main.hpp"
#include "IComponent.hpp"

template <class T>
class AComponent: public IComponent {
    private:
        T value_;
        const std::type_info& original_type_;

    public:
        AComponent(T arg_n) :
            value_(arg_n), original_type_(typeid(*this)) {}

        AComponent() :
            value_(), original_type_(typeid(*this)) {}

        const std::type_info& GetType() const override {
            return original_type_;
        }

        T &getValue() {
            return value_;
        }
        void setValue(T arg_new_value) {
            value_ = arg_new_value;
        };
        std::shared_ptr<IComponent> Clone() const override {
            return std::make_shared<AComponent>(*this);
        }
};

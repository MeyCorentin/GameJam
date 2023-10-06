#pragma once

#include "Component.hpp"

template <class T>
class C_Sprite : public Component<T> {
    public:
        C_Sprite(T arg_n) :
            Component<T>(arg_n) {}

        C_Sprite() :
            Component<T>() {}

        const std::type_info& GetType() const override {
            return typeid(C_Sprite);
        }

        std::shared_ptr<ComponentBase> Clone() const override {
            return std::make_shared<C_Sprite>(*this);
        }
};
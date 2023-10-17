#pragma once

#include "Component.hpp"
#include <SFML/Audio.hpp>


template <class T>
class C_Sound : public Component<T> {
public:
    C_Sound(T n) : Component<T>(n) {}
    C_Sound() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Sound);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Sound>(*this);
    }
};
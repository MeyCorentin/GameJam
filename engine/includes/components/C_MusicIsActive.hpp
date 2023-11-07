#pragma once

#include "AComponent.hpp"

template <class T>
class C_MusicIsActive : public AComponent<T> {
public:
    C_MusicIsActive(T n) : AComponent<T>(n) {}
    C_MusicIsActive() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_MusicIsActive);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_MusicIsActive>(*this);
    }
};
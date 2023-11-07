#pragma once

#include "AComponent.hpp"

template <class T>
class C_PositionFollow : public AComponent<T> {
public:
    C_PositionFollow(T n) : AComponent<T>(n) {}
    C_PositionFollow() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_PositionFollow);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_PositionFollow>(*this);
    }
};
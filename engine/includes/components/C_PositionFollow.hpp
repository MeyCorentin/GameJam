#pragma once

#include "Component.hpp"

template <class T>
class C_PositionFollow : public Component<T> {
public:
    C_PositionFollow(T n) : Component<T>(n) {}
    C_PositionFollow() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_PositionFollow);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_PositionFollow>(*this);
    }
};
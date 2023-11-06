#pragma once

#include "Component.hpp"

template <class T>
class C_PositionStorage : public Component<T> {
public:
    C_PositionStorage(T arg_n) :
        Component<T>(arg_n) {}

    C_PositionStorage() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_PositionStorage);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_PositionStorage>(*this);
    }
};
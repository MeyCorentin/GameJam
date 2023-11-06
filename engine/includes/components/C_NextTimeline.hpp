#pragma once

#include "Component.hpp"

template <class T>
class C_NextTimeline : public Component<T> {
public:
    C_NextTimeline(T arg_n) :
        Component<T>(arg_n) {}

    C_NextTimeline() :
        Component<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_NextTimeline);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_NextTimeline>(*this);
    }
};
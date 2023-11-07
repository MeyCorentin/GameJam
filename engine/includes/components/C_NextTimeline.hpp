#pragma once

#include "AComponent.hpp"

template <class T>
class C_NextTimeline : public AComponent<T> {
public:
    C_NextTimeline(T arg_n) :
        AComponent<T>(arg_n) {}

    C_NextTimeline() :
        AComponent<T>() {}

    const std::type_info& GetType() const override {
        return typeid(C_NextTimeline);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_NextTimeline>(*this);
    }
};
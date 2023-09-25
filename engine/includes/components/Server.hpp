#pragma once

#include "TComponent.hpp"

template <class T>
class Server : public TComponent<T> {
public:
    Server(T n) : TComponent<T>(n) {}
    const std::type_info& getType() const override {
        return typeid(Server);
    }
};
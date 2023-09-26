#pragma once

#include "TComponent.hpp"

template <class T>
class Server : public TComponent<T> {
public:
    Server(T n) : TComponent<T>(n) {}
    Server() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(Server);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Server>(*this);
    }
};
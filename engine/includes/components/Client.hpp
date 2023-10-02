#pragma once

#include "TComponent.hpp"

template <class T>
class Client : public TComponent<T> {
public:
    Client(T n) : TComponent<T>(n) {}
    Client() : TComponent<T>() {}
    const std::type_info& getType() const override {
        return typeid(Client);
    }
    std::shared_ptr<TComponentBase> clone() const override {
        return std::make_shared<Client>(*this);
    }
};
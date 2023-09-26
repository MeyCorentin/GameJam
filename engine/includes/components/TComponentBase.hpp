#pragma once
#include "../main.hpp"
class TComponentBase {
public:
    virtual ~TComponentBase() {}
    virtual const std::type_info& getType() const {
        return typeid(TComponentBase);
    };
    virtual std::shared_ptr<TComponentBase> clone() const = 0;
    template <typename T>
    void setValue(T newValue) {};
};

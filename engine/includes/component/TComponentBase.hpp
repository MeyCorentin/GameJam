#pragma once
#include "../main.hpp"
class TComponentBase {
public:
    virtual ~TComponentBase() {}
    virtual const std::type_info& getType() const {
        return typeid(TComponentBase);
    };
};

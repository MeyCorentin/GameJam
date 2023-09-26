#pragma once
#include "../main.hpp"
class TComponentBase {
public:
    virtual ~TComponentBase() {}
    virtual const std::type_info& getType() const {
        return typeid(TComponentBase);
    };
<<<<<<< HEAD
    virtual std::shared_ptr<TComponentBase> clone() const = 0;
    template <typename T>
    void setValue(T newValue) {};
=======
>>>>>>> a5a4786374f43f10e1597baecd486ba09e0e679c
};

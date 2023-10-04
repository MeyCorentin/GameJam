#pragma once
#include "../main.hpp"
class ComponentBase {
public:
    virtual ~ComponentBase() {}
    virtual const std::type_info& getType() const {
        return typeid(ComponentBase);
    };
    virtual std::shared_ptr<ComponentBase> clone() const = 0;
    template <typename T>
    void setValue(T arg_new_value) {};
};

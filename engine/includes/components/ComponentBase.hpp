#pragma once
#include "../main.hpp"
class ComponentBase {
public:
    virtual ~ComponentBase() {}
    virtual const std::type_info& GetType() const {
        return typeid(ComponentBase);
    };
    virtual std::shared_ptr<ComponentBase> Clone() const = 0;
    template <typename T>
    void SetValue(T arg_new_value) {};
};

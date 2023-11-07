#pragma once
#include "../main.hpp"
class IComponent {
public:
    virtual ~IComponent() {}
    virtual const std::type_info& GetType() const {
        return typeid(IComponent);
    };
    virtual std::shared_ptr<IComponent> Clone() const = 0;
    template <typename T>
    void SetValue(T arg_new_value) {};
};

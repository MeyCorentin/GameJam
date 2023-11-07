# Component

## Class ComponentBase
### Files:
- ComponentBase.hpp: Header file for the ComponentBase class.
- Brief: The ComponentBase class serves as the base class for all components in the application. It provides a common interface for components and a method to identify their types.

### Class Declaration:
```
class ComponentBase {
public:
    virtual ~ComponentBase() {}
​
    virtual const std::type_info& GetType() const {
        return typeid(ComponentBase);
    };
​
    virtual std::shared_ptr<ComponentBase> Clone() const = 0;
​
    template <typename T>
    void SetValue(T arg_new_value) {};
};
```
## Component Class
### Files:
- Component.hpp: Header file for the Component class.
- Brief: The Component class is a generic component template that stores data of a specific type. It derives from the ComponentBase class and provides methods to set and retrieve the stored value.

### Class Declaration:
```
template <class T>
class Component : public ComponentBase {
private:
    T value_;
    const std::type_info& original_type_;
​
public:
    Component(T arg_n) :
        value_(arg_n), original_type_(typeid(*this)) {}
​
    Component() :
        value_(), original_type_(typeid(*this)) {}
​
    const std::type_info& GetType() const override {
        return original_type_;
    }
​
    T &getValue() {
        return value_;
    }
​
    void setValue(T arg_new_value) {
        value_ = arg_new_value;
    }
​
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<Component>(*this);
    }
};
```

## C_Weapon Class (Exemple)
### Files:
- C_Weapon.hpp: Header file for the C_Weapon class.
- Brief: The C_Weapon class is an example of a specific component representing a weapon. It inherits properties from the generic Component class and provides methods to access and modify weapon-related data.

### Class Declaration:
```
template <class T>
class C_Weapon : public Component<T> {
public:
    C_Weapon(T n) : Component<T>(n) {}
    C_Weapon() : Component<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Weapon);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Weapon>(*this);
    }
};
```
### Purpose: The C_Weapon class is an example component that represents a weapon. It demonstrates how to create specialized components based on the generic Component class. Such components are used to define and customize the properties of weapons that entities can possess within the game.
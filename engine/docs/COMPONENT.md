# Component

## Documentation Menu
- [Documentation Menu](DOCUMENTATION.md)

## Class IComponent
### Files:
- IComponent.hpp: Header file for the IComponent class.
- Brief: The IComponent class serves as the base class for all components in the application. It provides a common interface for components and a method to identify their types.

### Class Declaration:
```
class IComponent {
public:
    virtual ~IComponent() {}
​
    virtual const std::type_info& GetType() const {
        return typeid(IComponent);
    };
​
    virtual std::shared_ptr<IComponent> Clone() const = 0;
​
    template <typename T>
    void SetValue(T arg_new_value) {};
};
```
## Component Class
### Files:
- Component.hpp: Header file for the Component class.
- Brief: The Component class is a generic component template that stores data of a specific type. It derives from the IComponent class and provides methods to set and retrieve the stored value.

### Class Declaration:
```
template <class T>
class AComponent : public IComponent {
private:
    T value_;
    const std::type_info& original_type_;
​
public:
    AComponent(T arg_n) :
        value_(arg_n), original_type_(typeid(*this)) {}
​
    AComponent() :
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
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<AComponent>(*this);
    }
};
```

## C_Weapon Class (Exemple)
### Files:
- C_Weapon.hpp: Header file for the C_Weapon class.
- Brief: The C_Weapon class is an example of a specific component representing a weapon. It inherits properties from the generic AComponent class and provides methods to access and modify weapon-related data.

### Class Declaration:
```
template <class T>
class C_Weapon : public AComponent<T> {
public:
    C_Weapon(T n) : AComponent<T>(n) {}
    C_Weapon() : AComponent<T>() {}
    const std::type_info& GetType() const override {
        return typeid(C_Weapon);
    }
    std::shared_ptr<IComponent> Clone() const override {
        return std::make_shared<C_Weapon>(*this);
    }
};
```
### Purpose: The C_Weapon class is an example component that represents a weapon. It demonstrates how to create specialized components based on the generic AComponent class. Such components are used to define and customize the properties of weapons that entities can possess within the game.
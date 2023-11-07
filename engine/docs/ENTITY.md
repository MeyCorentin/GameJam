# Entity

The Entity class is a fundamental building block within the application, representing in-game entities such as characters, objects, or creatures. Each Entity is identified by a unique ID and can be equipped with various components that define its behavior, properties, and functionalities. This documentation provides a comprehensive overview of the Entity class, its properties, and methods.

## Files

- Entity.hpp: Header file for the Entity class.
- Entity.cpp: Implementation file for the Entity class.
- EntityBuilder.hpp: Header file for the EntityBuilder class used for constructing Entity objects.

## Class Declaration

````
class Entity {
public:
    int id_;
    bool is_dead_ = false;
    std::vector<std::shared_ptr<ComponentBase>> components_;
​
    Entity(int arg_id, std::vector<std::shared_ptr<ComponentBase>> arg_components);
    Entity(const Entity& other);
    int GetId();
    void SetId(int arg_id);
    std::shared_ptr<Entity> Clone() const;
    bool HasComponent(const std::type_info& arg_type) const;
​
    template <class ComponentType>
    std::shared_ptr<ComponentType> GetComponent() const;
};
````
## Class Members

- int id_: The unique identifier for the entity.
- bool is_dead_: A flag indicating if the entity is marked as "dead."
- std::vector<std::shared_ptr<ComponentBase>> components_: A list of components associated with the entity.


## Constructors
- Entity(int arg_id, std::vector<std::shared_ptr<ComponentBase>> arg_components): Constructor for the - Entity class.
- Entity(const Entity& other): Copy constructor for the Entity class.


## Public Methods

- int GetId(): Returns the unique identifier of the entity.
- void SetId(int arg_id): Sets the unique identifier of the entity.
- std::shared_ptr<Entity> Clone() const: Creates a deep copy of the entity.
- bool HasComponent(const std::type_info& arg_type) const: Checks if the entity has a specific type of component.
- template <class ComponentType> std::shared_ptr<ComponentType> GetComponent() const: Retrieves a component of a specific type.

## EntityBuilder

- EntityBuilder is a companion class used for constructing Entity objects. It is described in the files EntityBuilder.hpp and is used for assembling and configuring new entities.

## Purpose

The Entity class serves as a container for game entities, allowing for easy creation and management of in-game elements. By associating various components with entities, their behavior and attributes can be customized to suit specific gameplay requirements. This documentation covers the essential aspects of the Entity class, including its properties, constructors, and methods. It is a key component in building the application's game world and facilitating interactive gameplay.
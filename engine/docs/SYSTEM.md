# System

## Documentation Menu
- [Documentation Menu](DOCUMENTATION.md)

The System class is a fundamental component within the application's architecture that controls and manages various aspects of the game world. Systems are responsible for executing logic and rendering entities. This documentation provides an overview of the System class, including its purpose, methods, and a sample implementation of the S_Display system.

## Files
- System.hpp: Header file for the System class.
- S_Display.hpp: Header file for the S_Display system implementation.

## Class Declaration

```
class ISystem {
public:
    virtual ~ISystem() {}

    void Compute(
        int arg_is_server,
        Scene * arg_scene
    );

    virtual std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) = 0;
    virtual void Execute(
        int arg_is_server,
        Scene * arg_scene
    ) = 0;
};
```

## Class Members
- virtual ~ISystem() {}: A virtual destructor for the ISystem interface, making it a polymorphic base class.
- void Compute(int arg_is_server, Scene * arg_scene): A method for executing system logic.
- virtual std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities): A pure virtual method for filtering entities based on components. Must be implemented by any class that inherits from ISystem.
- virtual void Execute(int arg_is_server, Scene * arg_scene): A pure virtual method for executing system-specific logic. Must be implemented by any class that inherits from ISystem.

## Purpose
The ISystem interface is a fundamental component of the game engine, responsible for implementing various game mechanics, logic, and rendering tasks. As an interface, ISystem sets out a framework for what a system should be within the game engine. Classes that implement this interface are tasked with defining the behavior of entities by processing their components.

At its core, each system iterates over the entities present in the scene, referred to as entities_, applying logic and rendering as defined by the specific system. This continuous loop plays a crucial role in managing and updating the game state, making systems a critical part of the game's architecture.

Systems play a crucial role in managing and updating the game state, making them a critical part of the game's architecture. By providing pure virtual methods for entity filtering and system-specific logic execution, the ISystem interface allows for great flexibility and extensibility in the design and implementation of game systems.

## Exemple

```
#include "system/S_Mana.hpp"


std::vector<std::shared_ptr<IEntity>> S_Mana::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Mana<int>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_Mana::Execute(
        int arg_is_server,
        Scene * arg_scene) {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    int current_mana;
    std::shared_ptr<C_Mana<int>> mana_comp;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        mana_comp = entity->template GetComponent<C_Mana<int>>();
        current_mana = mana_comp->getValue();
        mana_comp->setValue(current_mana + 1);
    }
}
```

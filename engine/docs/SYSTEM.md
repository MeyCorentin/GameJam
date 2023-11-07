# System

## Documentation Menu
- [Documentation Menu](DOCUMENTATION.md)

The System class is a fundamental component within the application's architecture that controls and manages various aspects of the game world. Systems are responsible for executing logic and rendering entities. This documentation provides an overview of the System class, including its purpose, methods, and a sample implementation of the S_Display system.

## Files
- System.hpp: Header file for the System class.
- S_Display.hpp: Header file for the S_Display system implementation.

## Class Declaration

```
class System {
public:
    virtual ~System() {}
​
    void Compute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& arg_entities,
        std::shared_ptr<sf::RenderWindow> arg_window,
        std::vector<int> arg_inputs,
        std::vector<sf::Sprite>& arg_sprites,
        std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
        std::shared_ptr<sf::Event> event_
    );
​
    virtual std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) = 0;
    virtual void Execute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& arg_entities,
        std::shared_ptr<sf::RenderWindow> arg_window,
        std::vector<int> arg_inputs,
        std::vector<std::shared_ptr<Entity>>& arg_all_entities,
        std::vector<sf::Sprite>& arg_sprites,
        std::vector<std::shared_ptr<sf::Texture>>& textures,
        std::shared_ptr<sf::Event> event_
    ) = 0;
};
```

## Class Members
- virtual ~System() {}: A virtual destructor for the System class, making it a polymorphic base class.
- void Compute(...): A method for executing system logic and rendering entities.
- virtual std::vector<std::shared_ptr<Entity>> Filter(...): A virtual method for filtering entities based on components.
- virtual void Execute(...): A virtual method for executing system-specific logic and rendering entities.

## Purpose
The System class is a core component of the game engine responsible for implementing various game mechanics, logic, and rendering tasks. Systems define the behavior of entities by processing their components. They play a crucial role in managing and updating the game state, making them a critical part of the game's architecture.

## Sample System: S_Display
- Class Name: S_Display
- Brief: The S_Display system is responsible for rendering and displaying entities within the game system. It filters entities with specific components (C_Sprite and C_Position) and manages their rendering on the game window. This system is crucial for providing the visual representation of entities in the game world.
- Header File: S_Display.hpp

## Sample Implementation
The S_Display system is a concrete implementation of the System class. It defines two key methods: Filter and Execute, which are overridden to handle rendering tasks. The following is a sample implementation of the S_Display system:

```
#include "system/S_Display.hpp"
​
std::vector<std::shared_ptr<Entity>> S_Display::Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) {
    std::vector<std::shared_ptr<Entity>> filtered_entities;
​
    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Sprite<sf::Sprite>)) &&
            entity->HasComponent(typeid(C_Position<std::pair<double, double>>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}
​
void S_Display::Execute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& arg_entities,
        std::shared_ptr<sf::RenderWindow> arg_window,
        std::vector<int> arg_inputs,
        std::vector<std::shared_ptr<Entity>>& arg_all_entities,
        std::vector<sf::Sprite>& arg_sprites,
        std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
        std::shared_ptr<sf::Event> event_) {
    sf::Sprite sprite_comp;
    std::shared_ptr<C_Position<std::pair<double, double>> position_comp;
    std::shared_ptr<C_Background<bool>> is_background;
}
```

The S_Display system is designed to render entities with sprite and position components and distinguish between background and foreground entities to ensure the correct rendering order.

## Inheritance

The System class is designed to be a base class for various concrete system implementations, each responsible for a specific aspect of the game. The S_Display system, as an example, inherits from System and specializes in rendering entities.

## Usage
The System class and its derivatives are used to implement game logic, rendering, and other core functionalities within the application. Each system class has a specific role in managing the game state and processing entities, contributing to the overall gameplay experience.
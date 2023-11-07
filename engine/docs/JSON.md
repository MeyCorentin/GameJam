# Json

## Documentation Menu
- [Documentation Menu](DOCUMENTATION.md)

The JSON structure can be divided into several major components:


# GAME.JSON

The game.json file is an essential configuration file in game development. It defines the various components, systems, and entities that make up the game.

### Structure
The game.json file is structured into several main sections:

**Systems:** 

This section contains a list of system objects, each representing a specific system within the game. Each system object is characterized by a unique __"id__" and a __"type"__ that describes the system's function.

**Components:** This part contains a list of component objects, each representing a particular type of component and its corresponding value __type__. These components define the attributes and properties of entities. Each Component has a unique __id__.

**Entities:** This section is a collection of individual entities within the game. Each entity has a unique "id" and is associated with various components. These components are specified by their __"component_id"__ along with their respective __"value,"__ reflecting the values or attributes of each component within the entity.

**Timeline:** The timeline section outlines the different timelines in the game, each associated with a JSON file that details events or triggers.
Usage
In game development, the game.json file is used to define the game's structure, mechanics, and attributes.

The **Systems** section is used to implement various game mechanics, logic, and rendering tasks. Each system iterates over the entities in the scene and applies its specific logic and rendering.
The Components section is used to define the attributes and properties of entities. These could be anything from a character's health points, position, sprite image, to its speed or direction of movement.

The **Entities** section is used to bring together the components into individual entities within the game. An entity could be anything from a player character, enemy, item, or environmental object.
The Timeline section is used to define different events or triggers in the game. Each timeline is associated with a JSON file that outlines the specific events or triggers.

### Here is an example of a game.json file:
```
{
    "systems": [
        {
            "id": 4,
            "type": "BasicInputSystem"
        },
        ...
    ],
    "components": [
        {
            "id": 1,
            "type": "Sprite",
            "value_type": "Sprite"
        },
        ...
    ],
    "entities": [
        {
            "id": 1,
            "components": [
                {
                    "component_id": 74,
                    "value": { "x": 0, "y": 0 }
                },
                ...
            ]
        },
        ...
    ],
    "timeline": [
        {
            "1": "timeline_1.json"
        },
        ...
    ]
}
```

This game.json structure provides a comprehensive framework for defining the game's logic and attributes. Systems govern the game's functionality, components hold the entity attributes, entities aggregate these components, and timeline configurations dictate when certain events or triggers occur.

# SETTINGS.JSON
The settings.json file is another important configuration file in game development. It defines the settings of the game window.

### Structure

The settings.json file is structured into a main section:

**Settings** This sections contain 2 other groups, the first one is the **"name"** that represent the name of the game's window, the second one is **"window"** who has two value **"x"** and **"y"**. X and Y are the size of the window.

### Usage
In game development, the settings.json file is used to defined the game window.

### Here is an example of a settings.json file:
```
{
    "settings": {
        "name" : "meetboy",
        "window": {
            "x" : 1920,
            "y" : 1080
        }
    }
}
```

# TIMELINE.JSON
The timeline.json file is another important configuration file in game development. It defines when and where specific entities spawn in the game.


### Structure

The timeline.json file is structured into a main section:

**Spawn:** This section contains a list of spawn objects, each representing a specific tick (or time point) in the game when certain entities are spawned. Each spawn object is characterized by a **"tick"** and a **"mob_id"** that contains a list of entities to be spawned at that tick. Each entity in the **"mob_id"** list is defined by an **"entity_id"** and a **"position"** that specifies the location where the entity will be spawned. If there is no **"position"** the enemy spawn is random.

### Usage
In game development, the timeline.json file is used to control the spawning of entities over time in the game.

### Here is an example of a timeline.json file:
```
{
    "spawn": [
        {
            "tick": 0,
            "mob_id": [
                {
                    "entity_id": 1,
                    "position": {
                        "x": 20,
                        "y": 125
                    }
                },
                ...
            ]
        },
        ...
    ]
}
```

This timeline.json structure provides a comprehensive framework for controlling the flow and progression of the game. The spawn configurations dictate when and where specific entities appear in the game, adding dynamic elements to the gameplay.

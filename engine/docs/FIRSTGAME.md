# Your first game !
In this section, you will be guided through the process of creating your first game using the provided game engine. We'll begin by creating a game configuration in JSON format and progressively define systems, components, entities, and the spawning of those entities based on ticks. Let's get started!
### Step 1: Game Configuration
First, you need to set up the basic configuration for your game. We'll use a JSON file to define your game's structure. Below is an example of a minimal game configuration JSON:
```
"systems": [],
"components": [],
"entities": [],
"spawn": []
```
In this initial configuration, we have empty arrays for "systems," "components," "entities," and "spawn." We will fill these in as we progress.
### Step 2: Create a System
Systems are responsible for handling different aspects of your game, such as input, rendering, physics, and more. Let's create an example "InputSystem" in your JSON configuration:
```
"systems": [
  {
    "id": 1,
    "type": "InputSystem"
  }
]
```
In this step, we've created an "InputSystem" with a unique "id."
### Step 3: Define a Component
Components represent the attributes of your game entities. Let's create a "Position" component with a "PairDouble" value type:
```
  "components": [
    {
      "id": 1,
      "type": "Position",
      "value_type": "PairDouble"
    }
  ]
 ```
Here, we've defined a "Position" component with a "PairDouble" value type.
### Step 4: Create an Entity
Entities are the in-game objects with attributes defined by components. Let's create an entity, for example, a "Player" entity:
```
"entities": [
  {
    "id": 1,
    "components": [
      {
        "component_id": 1,
        "value": { "x": 100, "y": 150 }
      }
    ]
  }
]
```

In this step, we've created a "Player" entity with a "Position" component, specifying its initial position.

### Step 5: Define Entity Spawning
Now, let's set up the spawning of entities based on ticks. You can specify the entities to spawn at specific ticks in the "spawn" array. For example, spawning a "Player" entity at tick 0:

```
"spawn": [
  {
    "tick": 0,
    "mob_id": [
      {
        "entity_id": 1
      }
    ]
  }
]
```
Here, we're spawning the "Player" entity with the unique ID "1" at tick 0.
With these steps, you have created a game configuration, defined a system, component, entity, and set up the spawning of that entity at a specific tick. This forms the foundation for your game development. As you continue building your game, you can add more systems, components, entities, and define their behaviors within your systems.
component, an entity, and entity spawning:

**Exemple:**
```
"systems": [
  {
    "id": 1,
    "type": "InputSystem"
  }
],
"components": [
  {
    "id": 1,
    "type": "Position",
    "value_type": "PairDouble"
  }
],
"entities": [
  {
    "id": 1,
    "components": [
      {
        "component_id": 1,
        "value": { "x": 100, "y": 150 }
      }
    ]
  }
],
"spawn": [
  {
    "tick": 0,
    "mob_id": [
      {
        "entity_id": 1
      }
    ]
  }
]
```
# Json
The JSON structure can be divided into several major components:
1. Systems:
This section contains a list of system objects, each representing a specific system within the game.
Each system object is characterized by a unique "ID" and a "Type" that describes the system's function.

2. Components:
Within this part, you'll find a list of component objects, with each object representing a particular type of component and its corresponding value type.
These components define the attributes and properties of entities.

3. Entities:
The entities section is a collection of individual entities within the game.
Each entity possesses a unique "ID" and is associated with various components.
These components are specified by their "component_id" along with their respective "value," reflecting the values or attributes of each component within the entity.

4. Spawn:
The spawn section outlines configurations for spawning entities at specific points in time.
Each spawn configuration includes a "tick" value, denoting the moment at which certain entities are introduced into the game.
A "mob_id" references a specific entity, and its positioning is described by a "position" object containing "x" and "y" coordinates.
This JSON structure provides a comprehensive framework for defining the game's logic and attributes. Systems govern the game's functionality, components hold the entity attributes, entities aggregate these components, and spawn configurations dictate when and where entities enter the game world.

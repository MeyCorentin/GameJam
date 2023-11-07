#include "ISystem.hpp"
#include "../scene/Scene.hpp"
#include "../components/C_Position.hpp"
/**
 * @class S_Position
 * @brief A class responsible for handling entity positioning in the system.
 *
 * The S_Position system is designed to filter entities with position components and process
 * their positions as needed. It serves as part of the core functionality for managing entity
 * positions within the system.
 */
class S_Position : public ISystem {
    public:
    /**
     * @brief Filters a list of entities based on their components.
     *
     * Filters the input list of entities and returns a new list containing
     * entities with component(s):
     *      - C_Position
     *
     * @param arg_entities The list of entities to filter.
     * @return A filtered list of entities.
     */
    std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

    /**
     * @brief Updates the positions of entities with position components.
     *
     * This function iterates through a list of entities and retrieves the position components,
     * updating the positions as required. It plays a key role in maintaining the positions of
     * entities within the system.
     *
     * This function applies to entities that have the component(s):
     *      - C_Position
     *
     * @param arg_is_server An integer indicating whether the system is running on the server.
     * @param arg_entities A list of entities to apply the sinusoidal movement to.
     * @param arg_window A shared pointer to the rendering window.
     * @param arg_inputs A list of input values.
     * @param arg_all_entities A list of all entities in the system.
     * @param event_ A shared pointer to the event object.
     */
        void Execute(
                int arg_is_server,
                Scene * arg_scene) override;
};

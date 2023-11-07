#include "ISystem.hpp"
#include "../scene/Scene.hpp"
#include "../components/C_Position.hpp"

/**
 * @class S_KillEntity
 * @brief A class responsible for managing entities and removing them when they are outside a specified area.
 *
 * The S_KillEntity system is designed to filter entities and remove them from the system when they move outside a
 * specified area. It is responsible for managing the removal of entities based on their positions.
 */
class S_KillEntity : public ISystem {
    public:
    /**
     * @brief Filters a list of entities based on their components.
     *
     * Filters the input list of entities and returns a new list containing
     * entities with component(s):
     *
     * @param arg_entities The list of entities to filter.
     * @return A filtered list of entities.
     */
    std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

    /**
     * @brief Manages the removal of entities that move outside a specified area.
     *
     * This function processes entities and checks if they have moved outside a specified area. If an entity's position
     * exceeds the defined boundaries, it is marked as "dead" and removed from the system to maintain system performance.
     *
     *
     * @param arg_is_server An integer indicating whether the system is running on the server.
     * @param arg_entities A list of entities to apply the sinusoidal movement to.
     * @param arg_window A shared pointer to the rendering window.
     * @param arg_inputs A list of input values.
     * @param arg_all_entities A list of all entities in the system.
     * @param arg_textures A list of texture objects.
     * @param event_ A shared pointer to the event object.
     */
        void Execute(
                int arg_is_server,
                Scene * arg_scene) override;
};

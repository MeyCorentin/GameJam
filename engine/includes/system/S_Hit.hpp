#include "ISystem.hpp"
#include "../scene/Scene.hpp"
#include "../components/C_Life.hpp"
#include "../components/C_Shield.hpp"

/**
 * @class S_Hit
 * @brief A class responsible for managing entity damage and handling hit-related actions in the system.
 *
 * The S_Hit system is designed to filter entities with life components and manage actions related to taking damage.
 * It handles reducing shield and life points of entities, reflecting hits and damage management within the system.
 */
class S_Hit : public ISystem {
    public:
    /**
     * @brief Filters a list of entities based on their components.
     *
     * Filters the input list of entities and returns a new list containing
     * entities with component(s):
     *      - C_Life
     *
     * @param arg_entities The list of entities to filter.
     * @return A filtered list of entities.
     */
    std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

    /**
     * @brief Manages the reduction of shield and life points for entities taking damage.
     *
     * This function processes entities with shield and life components, reducing shield points first, and then life points
     * in case the shield is depleted. It reflects the impact of hits and the reduction of defensive and offensive abilities
     * for entities within the system.
     *
     * This function applies to entities that have the component(s):
     *      - C_Life
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

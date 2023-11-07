#include "ISystem.hpp"
#include "../scene/Scene.hpp"
#include "../components/C_Mana.hpp"

/**
 * @class S_Mana
 * @brief A class responsible for managing mana-related actions in the system.
 *
 * The S_Mana system is designed to filter entities with mana components and execute actions related
 * to mana management. It tracks and updates mana values for entities, allowing for mana-related functionality
 * within the system.
 */
class S_Mana : public ISystem {
    public:
    /**
     * @brief Filters a list of entities based on their components.
     *
     * Filters the input list of entities and returns a new list containing
     * entities with component(s):
     *      - C_Mana
     *
     * @param arg_entities The list of entities to filter.
     * @return A filtered list of entities.
     */
    std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

    /**
     * @brief Manages mana-related actions for entities with mana components.
     *
     * This function processes entities with mana components and performs actions related to mana management.
     * It increases the current mana values of these entities, facilitating mana-related behavior within the system.
     *
     * This function applies to entities that have the component(s):
     *      - C_Mana
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

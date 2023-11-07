#pragma once

#include "ISystem.hpp"
#include "../scene/Scene.hpp"
#include "../components/C_Target.hpp"
#include "../components/C_Follow.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_Shoot.hpp"
#include "../components/C_FireRate.hpp"
#include "../components/C_FireRateSpeed.hpp"
#include "../components/C_Direction.hpp"
#include "../components/C_Range.hpp"
#include "../components/C_Ammo.hpp"
#include "../components/C_PositionFollow.hpp"
#include "../components/C_Life.hpp"
#include "../components/C_Inventory.hpp"
#include "S_Input.hpp"
/**
 * @class S_Target
 * @brief A class that represents a system for handling target-related actions.
 *
 * The S_Target system is responsible for filtering and executing various target-related actions
 * for entities, such as following and shooting at specified targets. It processes entities
 * with components related to targeting and takes appropriate actions based on their configurations.
 */
class S_Target : public ISystem {
    public:
    /**
     * @brief Filters a list of entities based on their components.
     *
     * Filters the input list of entities and returns a new list containing
     * entities with component(s):
     *      - C_Target
     *
     * @param arg_entities The list of entities to filter.
     * @return A filtered list of entities.
     */
    std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

    /**
    * @brief Executes target-related actions for entities.
    *
    * This function processes entities with target-related components and performs actions based on
    * their configurations. It handles actions like following a target and shooting at it, with considerations
    * for ammo, firing rate, range, and more.
    *
    * This function applies sinusoidal movement to entities that have the following components:
    *      - C_Target
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
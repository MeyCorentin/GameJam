#pragma once

#include "ISystem.hpp"
#include "../scene/Scene.hpp"
#include "S_Input.hpp"
#include "../components/C_Child.hpp"
#include "../components/C_Sprite.hpp"
#include "../components/C_Life.hpp"
#include "../components/C_SpriteRect.hpp"

/**
 * @class S_MakeBaby
 * @brief A class responsible for creating new entities based on specific conditions.
 *
 * The S_MakeBaby system is designed to filter entities that meet certain conditions and create new entities
 * based on those conditions. It is responsible for managing the creation of "baby" entities within the system.
 */
class S_MakeBaby : public ISystem {
    public:
    /**
     * @brief Filters a list of entities based on their components.
     *
     * Filters the input list of entities and returns a new list containing
     * entities with component(s):
     *      - C_Child
     *      - C_Sprite
     *      - C_SpriteRect
     *
     * @param arg_entities The list of entities to filter.
     * @return A filtered list of entities.
     */
    std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

    /**
     * @brief Creates new entities based on specified conditions.
     *
     * This function processes entities that meet specific conditions and generates new entities based on those conditions.
     * It retrieves entity configurations from an external source and creates new entities to be added to the system.
     *
     * This function applies to entities that have the component(s):
     *      - C_Child
     *      - C_Sprite
     *      - C_SpriteRect
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

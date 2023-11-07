#pragma once

#include "ISystem.hpp"
#include "../scene/Scene.hpp"
#include "../components/C_Direction.hpp"
#include "../components/C_Speed.hpp"
#include "../components/C_Parallax.hpp"
#include "../components/C_ParallaxClock.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_PositionStart.hpp"
#include "../components/C_PositionEnd.hpp"

/**
 * @class S_Parallax
 * @brief A class responsible for handling parallax effects in the system.
 *
 * The S_Parallax system is designed to filter entities with the necessary components for implementing
 * parallax effects and to execute actions related to parallax scrolling. It is responsible for simulating
 * the visual depth and movement of objects within the system, creating a parallax effect.
 */
class S_Parallax : public ISystem {
    public:
    /**
     * @brief Filters a list of entities based on their components.
     *
     * Filters the input list of entities and returns a new list containing
     * entities with component(s):
     *      - C_Position
     *      - C_Parallax
     *
     * @param arg_entities The list of entities to filter.
     * @return A filtered list of entities.
     */
    std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

    /**
     * @brief Manages parallax scrolling effects for entities with parallax components.
     *
     * This function processes entities with parallax components and updates their positions to create
     * parallax scrolling effects. It takes into account the parallax factor and the specified range of
     * movement to achieve the desired visual depth and movement within the system.
     *
     * This function applies to entities that have the component(s):
     *      - C_Position
     *      - C_Parallax
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
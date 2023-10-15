#pragma once

#include "System.hpp"
#include "../components/C_Direction.hpp"
#include "../components/C_Speed.hpp"
#include "../components/C_Parallax.hpp"
#include "../components/C_SinMoov.hpp"
#include "../components/C_SinClock.hpp"
#include "../components/C_Position.hpp"

/**
 * @class S_SinMoov
 * @brief A class that represents a system for sinusoidal movement of entities.
 */
class S_SinMoov : public System {
public:
    /**
     * @brief Filters a list of entities based on their components.
     *
     * Filters the input list of entities and returns a new list containing
     * entities with component(s):
     *      - C_SinMoov
     *      - C_SinClock
     *
     * @param arg_entities The list of entities to filter.
     * @return A filtered list of entities.
     */
    std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override;

    /**
     * @brief Executes the sinusoidal movement for selected entities.
     *
     * This function applies sinusoidal movement to entities that have the component(s):
     *      - C_SinMoov
     *      - C_SinClock
     *
     * @param arg_is_server An integer indicating whether the system is running on the server.
     * @param arg_entities A list of entities to apply the sinusoidal movement to.
     * @param arg_window A shared pointer to the rendering window.
     * @param arg_inputs A list of input values.
     * @param arg_all_entities A list of all entities in the system.
     * @param arg_sprites A list of sprite objects.
     * @param arg_textures A list of texture objects.
     * @param event_ A shared pointer to the event object.
     */
    void Execute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& arg_entities,
        std::shared_ptr<sf::RenderWindow> arg_window,
        std::vector<int> arg_inputs,
        std::vector<std::shared_ptr<Entity>>& arg_all_entities,
        std::vector<sf::Sprite>& arg_sprites,
        std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
        std::shared_ptr<sf::Event> event_) override;
};
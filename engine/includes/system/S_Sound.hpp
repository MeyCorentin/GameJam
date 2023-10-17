#pragma once

#include "System.hpp"
#include "../components/C_Sound.hpp"

class S_Sound : public System {

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
    std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override;

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
     * @param arg_sprites A list of sprite objects.
     * @param arg_textures A list of texture objects.
     * @param event_ A shared pointer to the event object.
     */
        void Execute(
                int arg_is_server,
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_input,
                std::vector<std::shared_ptr<Entity>>& arg_all_Entities,
                std::vector<sf::Sprite>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
                std::shared_ptr<sf::Event> event_) override;
// public:
//     std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override {
//         std::vector<std::shared_ptr<Entity>> entities;

//         for (auto& entity : arg_entities) {
//             if (entity->HasComponent(typeid(C_Sound<sf::Sound>)) {
//                 entities.push_back(entity);
//             }
//         }

//         return entities;
//     }

//     void Execute(
//             int arg_is_server,
//             std::vector<std::shared_ptr<Entity>>& arg_entities,
//             std::shared_ptr<sf::RenderWindow> arg_window,
//             std::vector<int> arg_input,
//             std::vector<std::shared_ptr<Entity>>& arg_all_Entities,
//             std::vector<sf::Sprite>& arg_sprites,
//             std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
//             std::shared_ptr<sf::Event> event_) override {

//         for (auto& entity : arg_entities) {
//             auto soundComp = entity->GetComponent<C_Sound>();
//             if (soundComp) {
//                 // Dans ce cas on joue le son. On peut ajouter plus de logique pour déterminer quand et comment le jouer.
//                 soundComp->Play();
//             }
//         }
//     }
};

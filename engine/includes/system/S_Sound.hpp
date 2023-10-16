#pragma once

#include "System.hpp"
#include "../components/C_Sound.hpp"

class S_Sound : public System {
public:
    std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override {
        std::vector<std::shared_ptr<Entity>> entities;

        for (auto& entity : arg_entities) {
            if (entity->HasComponent<C_Sound>()) {
                entities.push_back(entity);
            }
        }

        return entities;
    }

    void Execute(
            int arg_is_server,
            std::vector<std::shared_ptr<Entity>>& arg_entities,
            std::shared_ptr<sf::RenderWindow> arg_window,
            std::vector<int> arg_input,
            std::vector<std::shared_ptr<Entity>>& arg_all_Entities,
            std::vector<sf::Sprite>& arg_sprites,
            std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
            std::shared_ptr<sf::Event> event_) override {

        for (auto& entity : arg_entities) {
            auto soundComp = entity->GetComponent<C_Sound>();
            if (soundComp) {
                // Dans ce cas on joue le son. On peut ajouter plus de logique pour déterminer quand et comment le jouer.
                soundComp->Play();
            }
        }
    }
};

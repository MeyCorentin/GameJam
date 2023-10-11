#pragma once

#include "../main.hpp"
#include "../entity/Entity.hpp"

class System {
    public:
        virtual ~System() {}
        void Compute(
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_inputs,
                std::vector<sf::Sprite>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
                std::shared_ptr<sf::Event> event_) {
            std::vector<std::shared_ptr<Entity>> entities = Filter(arg_entities);
            Execute(entities, arg_window, arg_inputs, arg_entities, arg_sprites, arg_textures, event_);
        }
        virtual std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) = 0;
        virtual void Execute(
            std::vector<std::shared_ptr<Entity>>& arg_entities,
            std::shared_ptr<sf::RenderWindow> arg_window,
            std::vector<int> arg_inputs,
            std::vector<std::shared_ptr<Entity>>& arg_all_entities,
            std::vector<sf::Sprite>& arg_sprites,
            std::vector<std::shared_ptr<sf::Texture>>& textures,
            std::shared_ptr<sf::Event> event_) = 0;
};
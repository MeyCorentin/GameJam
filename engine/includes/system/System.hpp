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
                std::vector<std::shared_ptr<sf::Sprite>>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures) {
            std::vector<std::shared_ptr<Entity>> entities = Filter(arg_entities);
            Execute(entities, arg_window, arg_inputs, arg_entities, arg_sprites, arg_textures);
        }
        virtual std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) = 0;
        virtual void Execute(
            std::vector<std::shared_ptr<Entity>>& arg_entities,
            std::shared_ptr<sf::RenderWindow> arg_window,
            std::vector<int>  arg_inputs,
            std::vector<std::shared_ptr<Entity>>& arg_all_entities,
            std::vector<std::shared_ptr<sf::Sprite>>& arg_sprites,
            std::vector<std::shared_ptr<sf::Texture>>& textures) = 0;
};
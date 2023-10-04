#pragma once

#include "../main.hpp"
#include "../entity/EntityBuilder.hpp"
#include "../system/System.hpp"
#include "Scene.hpp"


class SceneBuilder {
    private:
        std::vector<std::shared_ptr<System>> systems_;
        std::vector<std::shared_ptr<Entity>> entities_;
        std::vector<std::shared_ptr<sf::Sprite>> sprites_;
        std::vector<std::shared_ptr<sf::Texture>> textures_;

    public:
        SceneBuilder& addSystem(std::shared_ptr<System> arg_system) {
            systems_.push_back(arg_system);
            return *this;
        }

        SceneBuilder& addEntity(std::shared_ptr<Entity> arg_entity) {
            entities_.push_back(arg_entity);
            return *this;
        }

        SceneBuilder& addSprite(std::shared_ptr<sf::Sprite> arg_sprite) {
            sprites_.push_back(arg_sprite);
            return *this;
        }

        SceneBuilder& addTexture(std::shared_ptr<sf::Texture> arg_texture) {
            textures_.push_back(arg_texture);
            return *this;
        }

        std::vector<std::shared_ptr<Entity>> geteEntities()
        {
            return  entities_;
        }

        std::vector<std::shared_ptr<System>> getSystems()
        {
            return systems_;
        }

        Scene build() {
            std::cout << "[BUILDER] Scene build" << std::endl;
            Scene scene(systems_, entities_, sprites_, textures_);
            return scene;
        }
};
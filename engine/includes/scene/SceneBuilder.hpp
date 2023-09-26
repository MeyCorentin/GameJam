#pragma once

#include "../main.hpp"
#include "../entity/EntityBuilder.hpp"
#include "../system/TSystem.hpp"
#include "TScene.hpp"


class SceneBuilder {
    private:
        std::vector<std::shared_ptr<TSystem>> systems;
        std::vector<std::shared_ptr<TEntity>> entities;
        std::vector<std::shared_ptr<sf::Sprite>> sprites;
        std::vector<std::shared_ptr<sf::Texture>> textures;

    public:
        SceneBuilder& addSystem(std::shared_ptr<TSystem> _system) {
            systems.push_back(_system);
            return *this;
        }

        SceneBuilder& addEntity(std::shared_ptr<TEntity> _entity) {
            entities.push_back(_entity);
            return *this;
        }

        SceneBuilder& addSprite(std::shared_ptr<sf::Sprite> _sprite) {
            sprites.push_back(_sprite);
            return *this;
        }

        SceneBuilder& addTexture(std::shared_ptr<sf::Texture> _texture) {
            textures.push_back(_texture);
            return *this;
        }

        std::vector<std::shared_ptr<TEntity>> getEntities()
        {
            return  entities;
        }

        std::vector<std::shared_ptr<TSystem>> getSystems()
        {
            return systems;
        }

        TScene build() {
            std::cout << "[BUILDER] Scene build" << std::endl;
            TScene scene(systems, entities, sprites, textures);
            return scene;
        }
};
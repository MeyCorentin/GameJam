#pragma once

#include "../main.hpp"
#include "../entity/EntityBuilder.hpp"
#include "../system/TSystem.hpp"
#include "TScene.hpp"


class SceneBuilder {
    private:
        std::vector<std::shared_ptr<TSystem>> systems;
        std::vector<std::shared_ptr<TEntity>> entities;

    public:
        SceneBuilder& addSystem(std::shared_ptr<TSystem> system) {
            systems.push_back(system);
            return *this;
        }

        SceneBuilder& addEntity(std::shared_ptr<TEntity> entity) {
            entities.push_back(entity);
            return *this;
        }

        TScene build() {
            TScene scene(systems, entities);
            return scene;
    }
};
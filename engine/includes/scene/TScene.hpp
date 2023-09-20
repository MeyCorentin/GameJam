#pragma once

#include "../main.hpp"
#include "../entity/TEntity.hpp"
#include "../system/TSystem.hpp"

class TScene {
    private:
        std::vector<TEntity> entities;
        std::vector<std::shared_ptr<TSystem>> systems;

    public:
        TScene(std::initializer_list<std::shared_ptr<TSystem>> systemList, std::initializer_list<TEntity> entityList)
            : systems(systemList), entities(entityList) {}

        void run() {
            for (const auto& system : systems) {
                system->compute(entities);
            }
        }
};


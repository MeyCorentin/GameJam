#include "TSystem.hpp"
#include "../component/Position.hpp"

class PositionSystem : public TSystem {
public:
    std::vector<TEntity> filter(const std::vector<TEntity>& entities) override {
        std::vector<TEntity> filteredEntities;
        for (const TEntity& entity : entities)
            if (entity.hasComponent(typeid(Position<std::pair<int, int>>)))
                filteredEntities.push_back(entity);
        return filteredEntities;
    }

    void execute(std::vector<TEntity>& entities) override {
        for (TEntity& entity : entities) {
            auto entityPosition = entity.template getComponent<Position<std::pair<int, int>>>();
            std::pair<int, int> currentLife = entityPosition->getValue();
            std::cout << entity.getId() << ": Positon :    " << entityPosition->getValue().second << ", " << entityPosition->getValue().first << std::endl;
        }
    }
};
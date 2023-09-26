#include "TSystem.hpp"
#include "../components/Life.hpp"

/**
 * @class HitSystem
 * @brief Manages entities with a life component and decreases their life.
 */
class HitSystem : public TSystem {
public:
    /**
     * @brief Filters entities to keep only those with a life component.
     * @param _entities The complete list of entities.
     * @return A list of entities with a life component.
     */
    std::vector<std::shared_ptr<TEntity>> filter(const std::vector<std::shared_ptr<TEntity>>& _entities) override {
        std::vector<std::shared_ptr<TEntity>> filteredEntities;
        for (const std::shared_ptr<TEntity>& entity : _entities) {
            if (entity->hasComponent(typeid(Life<int>))) {
                filteredEntities.push_back(entity);
            }
        }
        return filteredEntities;
    }

    /**
     * @brief Reduces the value of the life component for each entity.
     * @param _entities The list of entities with a life component.
     * @param _window The SFML window used for display (not used in this function).
     * @param _input User inputs (not used in this function).
     */
    void execute(std::vector<std::shared_ptr<TEntity>>& _entities, sf::RenderWindow &_window, std::vector<int> _input) override {
        for (const std::shared_ptr<TEntity>& entity : _entities) {
            std::shared_ptr<Life<int>> lifeComp = entity->template getComponent<Life<int>>();
            int currentLife = lifeComp->getValue();
            lifeComp->setValue(currentLife - 1);
        }
    }
};
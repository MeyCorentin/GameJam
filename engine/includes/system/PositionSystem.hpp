#include "TSystem.hpp"
#include "../components/Position.hpp"


/**
 * @brief A system for handling entities with Position components.
 *
 * This system filters entities that have a Position component and can perform
 * operations on them.
 */
class PositionSystem : public TSystem {
public:
    /**
     * @brief Filters entities with Position components.
     *
     * This function filters entities from the input vector that have a Position
     * component and returns a vector containing those filtered entities.
     *
     * @param _entities The vector of entities to filter.
     * @return A vector of shared pointers to filtered entities.
     */
    std::vector<std::shared_ptr<TEntity>> filter(const std::vector<std::shared_ptr<TEntity>>& _entities) override {
        std::vector<std::shared_ptr<TEntity>> filteredEntities;
        for (const std::shared_ptr<TEntity>& entity : _entities) {
            if (entity->hasComponent(typeid(Position<std::pair<int, int>>))) {
                filteredEntities.push_back(entity);
            }
        }
        return filteredEntities;
    }

    /**
     * @brief Execute operations on filtered entities.
     *
     * This function performs operations on the filtered entities, such as
     * accessing and manipulating their Position components.
     *
     * @param _entities A vector of shared pointers to filtered entities.
     * @param _window A reference to an SFML RenderWindow.
     * @param _inputs A vector of integers representing user inputs.
     */
    void execute(std::vector<std::shared_ptr<TEntity>>& _entities, sf::RenderWindow &_window, std::vector<int> _inputs) override {
        for (std::shared_ptr<TEntity>& entity : _entities) {
            std::pair<int, int> positionComp = entity->template getComponent<Position<std::pair<int, int>>>()->getValue();
        }
    }
};
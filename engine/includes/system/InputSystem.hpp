#include "TSystem.hpp"
#include "../components/Position.hpp"
#include "../components/Player.hpp"
/**
 * @brief A system for processing player input and updating entity positions.
 *
 * This system filters entities that have both Player and Position components, and it updates
 * the position of those entities based on the provided input.
 */
class InputSystem : public TSystem {
public:
    /**
     * @brief Filters entities with Player and Position components.
     *
     * @param _entities The list of entities to filter.
     * @return Filtered entities with Player and Position components.
     */
    std::vector<std::shared_ptr<TEntity>> filter(const std::vector<std::shared_ptr<TEntity>>& _entities) override {
        std::vector<std::shared_ptr<TEntity>> filteredEntities;
        for (const std::shared_ptr<TEntity>& entity : _entities) {
            if (entity->hasComponent(typeid(Player<bool>)) && entity->hasComponent(typeid(Position<std::pair<int, int>>))) {
                filteredEntities.push_back(entity);
            }
        }
        return filteredEntities;
    }

    /**
     * @brief Updates the positions of entities based on player input.
     *
     * This method iterates through the filtered entities and adjusts their positions
     * based on the input provided in the _inputs vector.
     *
     * @param _entities Vector of entities to update.
     * @param _window SFML window (not used in this function).
     * @param _inputs Vector of integers representing player input.
     */
    void execute(std::vector<std::shared_ptr<TEntity>>& _entities, sf::RenderWindow &_window, std::vector<int>  _inputs) override {
        for (const std::shared_ptr<TEntity>& entity : _entities) {
            std::shared_ptr<Position<std::pair<int, int>>> positionComp = entity->template getComponent<Position<std::pair<int, int>>>();
            if (_inputs[0] == 1)
                positionComp->setValue(std::make_pair(positionComp->getValue().first, positionComp->getValue().second - 5));
            if (_inputs[1] == 1)
                positionComp->setValue(std::make_pair(positionComp->getValue().first - 5, positionComp->getValue().second));
            if (_inputs[2] == 1)
                positionComp->setValue(std::make_pair(positionComp->getValue().first, positionComp->getValue().second  + 5));
            if (_inputs[3] == 1)
                positionComp->setValue(std::make_pair(positionComp->getValue().first + 5, positionComp->getValue().second));
        }
    }
};
#include "TSystem.hpp"
#include "../components/Sprite.hpp"
#include "../components/Position.hpp"

/**
 * @brief A rendering system for displaying entities with Sprite and Position components.
 *
 * This system filters entities that have both Sprite and Position components and renders them
 * on an SFML window.
 */
class DisplaySystem : public TSystem {
public:
    /**
     * @brief Filters entities with Sprite and Position components.
     *
     * @param _entities The list of entities to filter.
     * @return Filtered entities with Sprite and Position components.
     */
    std::vector<std::shared_ptr<TEntity>> filter(const std::vector<std::shared_ptr<TEntity>>& _entities) override {
        std::vector<std::shared_ptr<TEntity>> filteredEntities;
        for (const std::shared_ptr<TEntity>& entity : _entities) {
            if (entity->hasComponent(typeid(Sprite<std::shared_ptr<sf::Sprite>>)) &&
                entity->hasComponent(typeid(Position<std::pair<double, double>>))) {
                filteredEntities.push_back(entity);
            }
        }
        return filteredEntities;
    }

    /**
     * @brief Draws entities on the SFML window.
     *
     * This method iterates through the vector of entities and draws each entity
     * on the SFML window at its current position.
     *
     * @param _entities Vector of entities to draw.
     * @param _window SFML window on which to draw the entities.
     * @param _inputs Vector of integers representing user input (not used in this function).
     */
    void execute(std::vector<std::shared_ptr<TEntity>>& _entities, sf::RenderWindow &_window, std::vector<int> _inputs) override {
        for (const std::shared_ptr<TEntity>& entity : _entities) {
            std::shared_ptr<sf::Sprite> spriteComp = entity->template getComponent<Sprite<std::shared_ptr<sf::Sprite>>>()->getValue();
            std::shared_ptr<Position<std::pair<double, double>>> positionComp = entity->template getComponent<Position<std::pair<double, double>>>();
            float xPosition = static_cast<float>(positionComp->getValue().first);
            float yPosition = static_cast<float>(positionComp->getValue().second);

            spriteComp->setPosition(xPosition, yPosition);
            _window.draw(*spriteComp);
        }
    }
};

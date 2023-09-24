#pragma once

#include "../main.hpp"
#include "../entity/TEntity.hpp"

#pragma once

#include "../main.hpp"
#include "../entity/TEntity.hpp"
/**
 * @brief Base class for the systems in the game engine.
 *
 * This abstract class defines the common interface for all systems
 * in the game engine.
 */
class TSystem {
public:
    /**
     * @brief Virtual destructor to allow proper destruction of derived classes.
     */
    virtual ~TSystem() {}

    /**
     * @brief Perform the system's calculation on the filtered entities.
     *
     * This function first calls the filtering function to obtain the list
     * of filtered entities, and then calls the execution function on these entities.
     *
     * @param _entities List of game entities.
     * @param _window Game rendering window.
     * @param _inputs User inputs (e.g., keyboard keys).
     */
    void compute(std::vector<std::shared_ptr<TEntity>>& _entities, sf::RenderWindow &_window, std::vector<int> _inputs) {
        std::vector<std::shared_ptr<TEntity>> entities = filter(_entities);
        execute(entities, _window, _inputs);
    }

    /**
     * @brief Pure virtual function to filter relevant entities.
     *
     * This function must be implemented by derived classes to filter
     * relevant entities for this system.
     *
     * @param _entities List of all game entities.
     * @return List of filtered entities.
     */
    virtual std::vector<std::shared_ptr<TEntity>> filter(const std::vector<std::shared_ptr<TEntity>>& _entities) = 0;

    /**
     * @brief Pure virtual function to perform system-specific operations on filtered entities.
     *
     * This function must be implemented by derived classes to perform specific
     * system operations on the filtered entities.
     *
     * @param _entities List of filtered entities.
     * @param _window Game rendering window.
     * @param _inputs User inputs (e.g., keyboard keys).
     */
    virtual void execute(std::vector<std::shared_ptr<TEntity>>& _entities, sf::RenderWindow &_window, std::vector<int>  _inputs) = 0;
};
#include "ISystem.hpp"
#include "../scene/Scene.hpp"
#include "../components/C_Sprite.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_Background.hpp"
#include "../components/C_Texture.hpp"

/**
 * @class S_Display
 * @brief A class responsible for rendering and displaying entities within the system.
 *
 * The S_Display system filters entities with sprite and position components and manages their rendering
 * on the game window. It is responsible for rendering both background and foreground entities, providing
 * the visual representation of the entities within the system.
 */
class S_Display : public ISystem {
    public:
    /**
     * @brief Filters a list of entities based on their components.
     *
     * Filters the input list of entities and returns a new list containing
     * entities with component(s):
     *      - C_Sprite
     *      - C_Position
     *
     * @param arg_entities The list of entities to filter.
     * @return A filtered list of entities.
     */
    std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

    /**
     * @brief Renders and displays entities on the game window.
     *
     * This function processes entities with sprite and position components, rendering them on the game window.
     * It distinguishes between background and foreground entities to ensure the correct rendering order. Background
     * entities are rendered first, followed by foreground entities, providing the visual representation of the system.
     *
     * This function applies to entities that have the component(s):
     *      - C_Sprite
     *      - C_Position
     *
     * @param arg_is_server An integer indicating whether the system is running on the server.
     * @param arg_entities A list of entities to apply the sinusoidal movement to.
     * @param arg_window A shared pointer to the rendering window.
     * @param arg_inputs A list of input values.
     * @param arg_all_entities A list of all entities in the system.
     * @param event_ A shared pointer to the event object.
     */
        void Execute(
                int arg_is_server,
                Scene * arg_scene) override;
};

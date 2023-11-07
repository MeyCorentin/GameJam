#include "ISystem.hpp"
#include "../scene/Scene.hpp"
#include "../components/C_Sprite.hpp"
#include "../components/C_Clock.hpp"
#include "../components/C_SpriteRect.hpp"
#include "../components/C_Size.hpp"
#include "../components/C_Animation.hpp"
#include "../components/C_IsMoving.hpp"
#include "../components/C_Life.hpp"
#include "../components/C_UniqueAnimation.hpp"
#include "../components/C_ClockSpeed.hpp"
#include "../components/C_SingleAnimation.hpp"
#include "../components/C_AnimationDirection.hpp"
#include "../components/C_NextTimeline.hpp"

/**
 * @class S_Animation
 * @brief A class responsible for managing sprite animations for entities in the system.
 *
 * The S_Animation system filters entities that require sprite animations, based on the presence of
 * specific components. It controls the animation frames and timing for entities, allowing them to display
 * dynamic animations during gameplay.
 */
class S_Animation : public ISystem {
    public:
    /**
     * @brief Manages sprite animations for filtered entities.
     *
     * This function processes entities that require sprite animations. It updates the animation frames and timing
     * for each entity, allowing them to display dynamic animations. The animation consists of transitioning between
     * different sprite frames, and the animation cycle is based on the provided timing.
     *
     * Filters the input list of entities and returns a new list containing
     * entities with component(s):
     *      - C_Sprite
     *      - C_Clock
     *      - C_SpriteRect
     *      - C_UniqueAnimation
     *      - C_Size
     *      - C_Animation
     *
     * and not containing the component(s):
     *      - C_IsMoving
     *
     * @param arg_entities The list of entities to filter.
     * @return A filtered list of entities.
     */
    std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

    /**
     * @brief Executes the sinusoidal movement for selected entities.
     *
     * This function applies to entities that have the component(s):_____
     *      - C_Sprite
     *      - C_Clock
     *      - C_SpriteRect
     *      - C_UniqueAnimation
     *      - C_Size
     *      - C_Animation
     *
     * and not containing the component(s):
     *      - C_IsMoving
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


#include "System.hpp"
#include "../components/C_Sprite.hpp"
#include "../components/C_Clock.hpp"
#include "../components/C_SpriteRect.hpp"
#include "../components/C_Size.hpp"
#include "../components/C_Animation.hpp"
#include "../components/C_IsMoving.hpp"
#include "../components/C_Life.hpp"
#include "../components/C_UniqueAnimation.hpp"

class S_Animation : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& _entities) override;

        void Execute(
                int arg_is_server,
                std::vector<std::shared_ptr<Entity>>& _entities,
                std::shared_ptr<sf::RenderWindow> _window,
                std::vector<int> _inputs,
                std::vector<std::shared_ptr<Entity>>& allEntities,
                std::vector<sf::Sprite>& sprites, std::vector<std::shared_ptr<sf::Texture>>& textures,
                std::shared_ptr<sf::Event> event_) override;
};


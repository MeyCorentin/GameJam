
#include "../includes/main.hpp"
#include "../includes/system/TSystem.hpp"
#include "../includes/system/PositionSystem.hpp"
#include "../includes/system/HitSystem.hpp"
#include "../includes/system/DisplaySystem.hpp"
#include "../includes/system/InputSystem.hpp"
#include "../includes/system/ManaSystem.hpp"
#include "../includes/system/CollisionSystem.hpp"
#include "../includes/system/MouvementSystem.hpp"

#include "../includes/components/Life.hpp"
#include "../includes/components/Player.hpp"
#include "../includes/components/Sprite.hpp"
#include "../includes/components/Position.hpp"
#include "../includes/components/Direction.hpp"
#include "../includes/components/Speed.hpp"
#include "../includes/components/Mana.hpp"
#include "../includes/components/Client.hpp"
#include "../includes/components/Server.hpp"
#include "../includes/components/TComponentBase.hpp"

#include "../includes/scene/SystemRegister.hpp"
#include "../includes/scene/ComponentRegister.hpp"
#include "../includes/scene/SceneBuilder.hpp"
#include "../includes/scene/SceneDirector.hpp"

class Ecs
{
    TScene scene;
    public:
        Ecs(){}
        Ecs(int ac, char **av)
        {
            SystemRegistry::instance().registerSystem("CollisionSystem", []() { return std::make_shared<CollisionSystem>(); });
            SystemRegistry::instance().registerSystem("HitSystem", []() { return std::make_shared<HitSystem>(); });
            SystemRegistry::instance().registerSystem("PositionSystem", []() { return std::make_shared<PositionSystem>(); });
            SystemRegistry::instance().registerSystem("DisplaySystem", []() { return std::make_shared<DisplaySystem>(); });
            SystemRegistry::instance().registerSystem("InputSystem", []() { return std::make_shared<InputSystem>(); });
            SystemRegistry::instance().registerSystem("ManaSystem", []() { return std::make_shared<ManaSystem>(); });
            SystemRegistry::instance().registerSystem("MouvementSystem", []() { return std::make_shared<MouvementSystem>(); });

            ComponentRegistry::instance().registerComponent("Sprite", []() { return std::make_shared<Sprite<std::shared_ptr<sf::Sprite>>>(); });
            ComponentRegistry::instance().registerComponent("Life", []() { return std::make_shared<Life<int>>(); });
            ComponentRegistry::instance().registerComponent("Mana", []() { return std::make_shared<Mana<int>>(); });
            ComponentRegistry::instance().registerComponent("Position", []() { return std::make_shared<Position<std::pair<double, double>>>(); });
            ComponentRegistry::instance().registerComponent("Direction", []() { return std::make_shared<Direction<std::pair<double, double>>>(); });
            ComponentRegistry::instance().registerComponent("Speed", []() { return std::make_shared<Speed<double>>(); });
            ComponentRegistry::instance().registerComponent("Hitbox", []() { return std::make_shared<Hitbox<std::pair<int, int>>>(); });
            ComponentRegistry::instance().registerComponent("Player", []() { return std::make_shared<Player<bool>>(); });
            ComponentRegistry::instance().registerComponent("Server", []() { return std::make_shared<Server<bool>>(); });
            ComponentRegistry::instance().registerComponent("Client", []() { return std::make_shared<Client<bool>>(); });
        };
        void update()
        {
            scene.update();
        }
        void create()
        {
            std::cout << "[ECS] start create scene" << std::endl;
            SceneDirector SceneDirector("../scene_test.json");

            scene = SceneDirector.constructScene();
        }
};
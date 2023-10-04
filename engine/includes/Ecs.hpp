
#include "../includes/main.hpp"
#include "../includes/system/System.hpp"
#include "../includes/system/S_Position.hpp"
#include "../includes/system/S_Hit.hpp"
#include "../includes/system/S_Display.hpp"
#include "../includes/system/S_Input.hpp"
#include "../includes/system/S_Mana.hpp"
#include "../includes/system/S_Collision.hpp"
#include "../includes/system/S_Mouvement.hpp"

#include "../includes/components/C_Life.hpp"
#include "../includes/components/C_Player.hpp"
#include "../includes/components/C_Sprite.hpp"
#include "../includes/components/C_Position.hpp"
#include "../includes/components/C_Direction.hpp"
#include "../includes/components/C_Speed.hpp"
#include "../includes/components/C_Mana.hpp"
#include "../includes/components/C_Client.hpp"
#include "../includes/components/C_Server.hpp"
#include "../includes/components/ComponentBase.hpp"

#include "../includes/scene/SystemRegister.hpp"
#include "../includes/scene/ComponentRegister.hpp"
#include "../includes/scene/SceneBuilder.hpp"
#include "../includes/scene/SceneDirector.hpp"

class Ecs
{
    Scene scene;
    public:
    
        Ecs(){}
        Ecs(int ac, char **av)
        {
        };
        void update()
        {
            scene.update();
        }
        void create()
        {

            SystemRegistry::instance().registerSystem("CollisionSystem", []() { return std::make_shared<S_Collision>(); });
            SystemRegistry::instance().registerSystem("HitSystem", []() { return std::make_shared<S_Hit>(); });
            SystemRegistry::instance().registerSystem("PositionSystem", []() { return std::make_shared<S_Position>(); });
            SystemRegistry::instance().registerSystem("DisplaySystem", []() { return std::make_shared<S_Display>(); });
            SystemRegistry::instance().registerSystem("InputSystem", []() { return std::make_shared<S_Input>(); });
            SystemRegistry::instance().registerSystem("ManaSystem", []() { return std::make_shared<S_Mana>(); });
            SystemRegistry::instance().registerSystem("MouvementSystem", []() { return std::make_shared<S_Mouvement>(); });

            ComponentRegistry::instance().registerComponent("Sprite", []() { return std::make_shared<C_Sprite<std::shared_ptr<sf::Sprite>>>(); });
            ComponentRegistry::instance().registerComponent("Life", []() { return std::make_shared<C_Life<int>>(); });
            ComponentRegistry::instance().registerComponent("Mana", []() { return std::make_shared<C_Mana<int>>(); });
            ComponentRegistry::instance().registerComponent("Position", []() { return std::make_shared<C_Position<std::pair<double, double>>>(); });
            ComponentRegistry::instance().registerComponent("Direction", []() { return std::make_shared<C_Direction<std::pair<double, double>>>(); });
            ComponentRegistry::instance().registerComponent("Speed", []() { return std::make_shared<C_Speed<double>>(); });
            ComponentRegistry::instance().registerComponent("Hitbox", []() { return std::make_shared<C_Hitbox<std::pair<int, int>>>(); });
            ComponentRegistry::instance().registerComponent("Player", []() { return std::make_shared<C_Player<bool>>(); });
            ComponentRegistry::instance().registerComponent("Server", []() { return std::make_shared<C_Server<bool>>(); });
            ComponentRegistry::instance().registerComponent("Client", []() { return std::make_shared<C_Client<bool>>(); });

            std::cout << "[ECS] start create scene" << std::endl;
            SceneDirector SceneDirector("../../rtype/scene_test.json");

            scene = SceneDirector.constructScene();
        }
};
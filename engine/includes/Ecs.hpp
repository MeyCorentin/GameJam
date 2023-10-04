
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
        void Update()
        {
            scene.Update();
        }
        void Create()
        {
            SystemRegistry::Instance().RegisterSystem("CollisionSystem", []() { return std::make_shared<S_Collision>(); });
            SystemRegistry::Instance().RegisterSystem("HitSystem", []() { return std::make_shared<S_Hit>(); });
            SystemRegistry::Instance().RegisterSystem("PositionSystem", []() { return std::make_shared<S_Position>(); });
            SystemRegistry::Instance().RegisterSystem("DisplaySystem", []() { return std::make_shared<S_Display>(); });
            SystemRegistry::Instance().RegisterSystem("InputSystem", []() { return std::make_shared<S_Input>(); });
            SystemRegistry::Instance().RegisterSystem("ManaSystem", []() { return std::make_shared<S_Mana>(); });
            SystemRegistry::Instance().RegisterSystem("MouvementSystem", []() { return std::make_shared<S_Mouvement>(); });

            ComponentRegistry::Instance().RegisterComponent("Sprite", []() { return std::make_shared<C_Sprite<std::shared_ptr<sf::Sprite>>>(); });
            ComponentRegistry::Instance().RegisterComponent("Life", []() { return std::make_shared<C_Life<int>>(); });
            ComponentRegistry::Instance().RegisterComponent("Mana", []() { return std::make_shared<C_Mana<int>>(); });
            ComponentRegistry::Instance().RegisterComponent("Position", []() { return std::make_shared<C_Position<std::pair<double, double>>>(); });
            ComponentRegistry::Instance().RegisterComponent("Direction", []() { return std::make_shared<C_Direction<std::pair<double, double>>>(); });
            ComponentRegistry::Instance().RegisterComponent("Speed", []() { return std::make_shared<C_Speed<double>>(); });
            ComponentRegistry::Instance().RegisterComponent("Hitbox", []() { return std::make_shared<C_Hitbox<std::pair<int, int>>>(); });
            ComponentRegistry::Instance().RegisterComponent("Player", []() { return std::make_shared<C_Player<bool>>(); });
            ComponentRegistry::Instance().RegisterComponent("Server", []() { return std::make_shared<C_Server<bool>>(); });
            ComponentRegistry::Instance().RegisterComponent("Client", []() { return std::make_shared<C_Client<bool>>(); });

            std::cout << "[ECS] start create scene" << std::endl;
            SceneDirector SceneDirector("../../rtype/scene_test.json");

            scene = SceneDirector.ConstructScene();
        }
};
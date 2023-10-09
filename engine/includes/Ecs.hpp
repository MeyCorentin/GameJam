
#include "../includes/main.hpp"
#include "../includes/system/System.hpp"
#include "../includes/system/S_Position.hpp"
#include "../includes/system/S_Hit.hpp"
#include "../includes/system/S_Display.hpp"
#include "../includes/system/S_Input.hpp"
#include "../includes/system/S_Mana.hpp"
#include "../includes/system/S_Collision.hpp"
#include "../includes/system/S_Mouvement.hpp"
#include "../includes/system/S_Animation.hpp"
#include "../includes/system/S_Target.hpp"
#include "../includes/system/S_KillEntity.hpp"
#include "../includes/system/S_Parallax.hpp"

#include "../includes/components/C_Life.hpp"
#include "../includes/components/C_Player.hpp"
#include "../includes/components/C_Sprite.hpp"
#include "../includes/components/C_Position.hpp"
#include "../includes/components/C_Direction.hpp"
#include "../includes/components/C_Speed.hpp"
#include "../includes/components/C_Mana.hpp"
#include "../includes/components/C_Shoot.hpp"
#include "../includes/components/C_Target.hpp"
#include "../includes/components/C_Follow.hpp"
#include "../includes/components/C_Animation.hpp"
#include "../includes/components/C_Server.hpp"
#include "../includes/components/C_Client.hpp"
#include "../includes/components/C_Size.hpp"
#include "../includes/components/C_SpriteRect.hpp"
#include "../includes/components/C_Clock.hpp"
#include "../includes/components/C_FireRate.hpp"
#include "../includes/components/C_Parallax.hpp"
#include "../includes/components/C_Range.hpp"
#include "../includes/components/C_FireRateSpeed.hpp"
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
            SystemRegistry::Instance().RegisterSystem("S_Animation", []() { return std::make_shared<S_Animation>(); });
            SystemRegistry::Instance().RegisterSystem("S_Target", []() { return std::make_shared<S_Target>(); });
            SystemRegistry::Instance().RegisterSystem("KillEntity", []() { return std::make_shared<S_KillEntity>(); });
            SystemRegistry::Instance().RegisterSystem("ParallaxSystem", []() { return std::make_shared<S_Parallax>(); });

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
            ComponentRegistry::Instance().RegisterComponent("Shield", []() { return std::make_shared<C_Shield<int>>(); });
            ComponentRegistry::Instance().RegisterComponent("Clock", []() { return std::make_shared<C_Clock<sf::Clock>>(); });
            ComponentRegistry::Instance().RegisterComponent("SpriteRect", []() { return std::make_shared<C_SpriteRect<std::shared_ptr<sf::IntRect>>>(); });
            ComponentRegistry::Instance().RegisterComponent("Size", []() { return std::make_shared<C_Size<std::pair<int, int>>>(); });
            ComponentRegistry::Instance().RegisterComponent("Animation", []() { return std::make_shared<C_Animation<bool>>(); });
            ComponentRegistry::Instance().RegisterComponent("Shoot", []() { return std::make_shared<C_Shoot<bool>>(); });
            ComponentRegistry::Instance().RegisterComponent("Target", []() { return std::make_shared<C_Target<int>>(); });
            ComponentRegistry::Instance().RegisterComponent("Follow", []() { return std::make_shared<C_Follow<bool>>(); });
            ComponentRegistry::Instance().RegisterComponent("FireRate", []() { return std::make_shared<C_FireRate<sf::Clock>>(); });
            ComponentRegistry::Instance().RegisterComponent("FireRateSpeed", []() { return std::make_shared<C_FireRateSpeed<double>>(); });
            ComponentRegistry::Instance().RegisterComponent("Range", []() { return std::make_shared<C_Range<int>>(); });
            ComponentRegistry::Instance().RegisterComponent("Parallax", []() { return std::make_shared<C_Parallax<int>>(); });

            std::cout << "[ECS] start create scene" << std::endl;
            SceneDirector SceneDirector("../../rtype/scene_test.json");

            scene = SceneDirector.ConstructScene();
        }
};
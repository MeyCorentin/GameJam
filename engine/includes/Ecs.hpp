
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
#include "../includes/system/S_SinMoov.hpp"
#include "../includes/system/S_EraseEntity.hpp"

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
#include "../includes/components/C_Background.hpp"
#include "../includes/components/C_Animation.hpp"
#include "../includes/components/C_Server.hpp"
#include "../includes/components/C_Client.hpp"
#include "../includes/components/C_Size.hpp"
#include "../includes/components/C_SinMoov.hpp"
#include "../includes/components/C_SpriteRect.hpp"
#include "../includes/components/C_Clock.hpp"
#include "../includes/components/C_FireRate.hpp"
#include "../includes/components/C_Parallax.hpp"
#include "../includes/components/C_Range.hpp"
#include "../includes/components/C_FireRateSpeed.hpp"
#include "../includes/components/C_ChargedShoot.hpp"
#include "../includes/components/C_ShootCharging.hpp"
#include "../includes/components/C_PlayerAmmo.hpp"
#include "../includes/components/C_SinClock.hpp"
#include "../includes/components/C_AnimatedMove.hpp"
#include "../includes/components/C_IsMoving.hpp"
#include "../includes/components/C_Child.hpp"
#include "../includes/components/C_UniqueAnimation.hpp"
#include "../includes/components/ComponentBase.hpp"

#include "../includes/scene/SystemRegister.hpp"
#include "../includes/scene/ComponentRegister.hpp"
#include "../includes/scene/SceneBuilder.hpp"
#include "../includes/scene/SceneDirector.hpp"

class Ecs
{
    public:
        Scene scene_;
        Ecs(){}
        Ecs(int ac, char **av)
        {
        };
        void Update(int arg_is_server)
        {
            scene_.Update(arg_is_server);
        }
        void Create(int arg_is_server)
        {
            SystemRegistry::Instance().RegisterSystem("CollisionSystem", []() { return std::make_shared<S_Collision>(); });
            SystemRegistry::Instance().RegisterSystem("HitSystem", []() { return std::make_shared<S_Hit>(); });
            SystemRegistry::Instance().RegisterSystem("PositionSystem", []() { return std::make_shared<S_Position>(); });
            SystemRegistry::Instance().RegisterSystem("S_Animation", []() { return std::make_shared<S_Animation>(); });
            SystemRegistry::Instance().RegisterSystem("DisplaySystem", []() { return std::make_shared<S_Display>(); });
            SystemRegistry::Instance().RegisterSystem("InputSystem", []() { return std::make_shared<S_Input>(); });
            SystemRegistry::Instance().RegisterSystem("ManaSystem", []() { return std::make_shared<S_Mana>(); });
            SystemRegistry::Instance().RegisterSystem("MouvementSystem", []() { return std::make_shared<S_Mouvement>(); });
            SystemRegistry::Instance().RegisterSystem("S_Target", []() { return std::make_shared<S_Target>(); });
            SystemRegistry::Instance().RegisterSystem("KillEntity", []() { return std::make_shared<S_KillEntity>(); });
            SystemRegistry::Instance().RegisterSystem("ParallaxSystem", []() { return std::make_shared<S_Parallax>(); });
            SystemRegistry::Instance().RegisterSystem("SinMoovSystem", []() { return std::make_shared<S_SinMoov>(); });
            SystemRegistry::Instance().RegisterSystem("EraseEntity", []() { return std::make_shared<S_EraseEntity>(); });

            ComponentRegistry::Instance().RegisterComponent("Sprite", []() { return std::make_shared<C_Sprite<sf::Sprite>>(); });
            ComponentRegistry::Instance().RegisterComponent("Life", []() { return std::make_shared<C_Life<int>>(); });
            ComponentRegistry::Instance().RegisterComponent("Mana", []() { return std::make_shared<C_Mana<int>>(); });
            ComponentRegistry::Instance().RegisterComponent("Position", []() { return std::make_shared<C_Position<std::pair<double, double>>>(); });
            ComponentRegistry::Instance().RegisterComponent("Direction", []() { return std::make_shared<C_Direction<std::pair<double, double>>>(); });
            ComponentRegistry::Instance().RegisterComponent("Speed", []() { return std::make_shared<C_Speed<double>>(); });
            ComponentRegistry::Instance().RegisterComponent("Hitbox", []() { return std::make_shared<C_Hitbox<std::pair<int, int>>>(); });
            ComponentRegistry::Instance().RegisterComponent("Player", []() { return std::make_shared<C_Player<int>>(); });
            ComponentRegistry::Instance().RegisterComponent("Server", []() { return std::make_shared<C_Server<bool>>(); });
            ComponentRegistry::Instance().RegisterComponent("Client", []() { return std::make_shared<C_Client<bool>>(); });
            ComponentRegistry::Instance().RegisterComponent("Shield", []() { return std::make_shared<C_Shield<int>>(); });
            ComponentRegistry::Instance().RegisterComponent("Clock", []() { return std::make_shared<C_Clock<sf::Clock>>(); });
            ComponentRegistry::Instance().RegisterComponent("SpriteRect", []() { return std::make_shared<C_SpriteRect<sf::IntRect>>(); });
            ComponentRegistry::Instance().RegisterComponent("Size", []() { return std::make_shared<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>>(); });
            ComponentRegistry::Instance().RegisterComponent("Animation", []() { return std::make_shared<C_Animation<bool>>(); });
            ComponentRegistry::Instance().RegisterComponent("Shoot", []() { return std::make_shared<C_Shoot<bool>>(); });
            ComponentRegistry::Instance().RegisterComponent("Target", []() { return std::make_shared<C_Target<int>>(); });
            ComponentRegistry::Instance().RegisterComponent("Follow", []() { return std::make_shared<C_Follow<bool>>(); });
            ComponentRegistry::Instance().RegisterComponent("FireRate", []() { return std::make_shared<C_FireRate<sf::Clock>>(); });
            ComponentRegistry::Instance().RegisterComponent("FireRateSpeed", []() { return std::make_shared<C_FireRateSpeed<double>>(); });
            ComponentRegistry::Instance().RegisterComponent("Range", []() { return std::make_shared<C_Range<int>>(); });
            ComponentRegistry::Instance().RegisterComponent("Parallax", []() { return std::make_shared<C_Parallax<int>>(); });
            ComponentRegistry::Instance().RegisterComponent("ChargedShoot", []() { return std::make_shared<C_ChargedShoot<sf::Clock>>(); });
            ComponentRegistry::Instance().RegisterComponent("ShootCharging", []() { return std::make_shared<C_ShootCharging<bool>>(); });
            ComponentRegistry::Instance().RegisterComponent("PlayerAmmo", []() { return std::make_shared<C_PlayerAmmo<bool>>(); });
            ComponentRegistry::Instance().RegisterComponent("SinMoov", []() { return std::make_shared<C_SinMoov<SinusoidalFunction>>(); });
            ComponentRegistry::Instance().RegisterComponent("SinClock", []() { return std::make_shared<C_SinClock<sf::Clock>>(); });
            ComponentRegistry::Instance().RegisterComponent("Background", []() { return std::make_shared<C_Background<bool>>(); });
            ComponentRegistry::Instance().RegisterComponent("AnimatedMove", []() { return std::make_shared<C_AnimatedMove<sf::Clock>>(); });
            ComponentRegistry::Instance().RegisterComponent("IsMoving", []() { return std::make_shared<C_IsMoving<bool>>(); });
            ComponentRegistry::Instance().RegisterComponent("Child", []() { return std::make_shared<C_Child<int>>(); });
            ComponentRegistry::Instance().RegisterComponent("UniqueAnimation", []() { return std::make_shared<C_UniqueAnimation<bool>>(); });

            std::cout << "[ECS] start create scene" << std::endl;
            SceneDirector SceneDirector("../../rtype/scene_test.json", arg_is_server);

            scene_ = SceneDirector.ConstructScene();
        }
};
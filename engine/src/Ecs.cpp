#include "Ecs.hpp"


Ecs::Ecs(){}

Ecs::Ecs(int ac, char **av)
{
};
void Ecs::Update(int arg_is_server)
{
    scene_.Update(arg_is_server);
}
void Ecs::Create(int arg_is_server)
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
    SystemRegistry::Instance().RegisterSystem("MakeBaby", []() { return std::make_shared<S_MakeBaby>(); });

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
    ComponentRegistry::Instance().RegisterComponent("Ammo", []() { return std::make_shared<C_Ammo<int>>(); });
    ComponentRegistry::Instance().RegisterComponent("Admin", []() { return std::make_shared<C_Admin<bool>>(); });
    ComponentRegistry::Instance().RegisterComponent("UniqueAnimation", []() { return std::make_shared<C_UniqueAnimation<bool>>(); });
    ComponentRegistry::Instance().RegisterComponent("PositionEnd", []() { return std::make_shared<C_PositionEnd<std::pair<double, double>>>(); });
    ComponentRegistry::Instance().RegisterComponent("PositionStart", []() { return std::make_shared<C_PositionStart<std::pair<double, double>>>(); });
    ComponentRegistry::Instance().RegisterComponent("PositionFollow", []() { return std::make_shared<C_PositionFollow<std::pair<double, double>>>(); });
    ComponentRegistry::Instance().RegisterComponent("Inventory", []() { return std::make_shared<C_Inventory<std::vector<std::shared_ptr<Entity>>>>(); });

    std::cout << "[ECS] start create scene" << std::endl;
    SceneDirector SceneDirector("../../rtype/scene_test.json", arg_is_server);

    scene_ = SceneDirector.ConstructScene();
}
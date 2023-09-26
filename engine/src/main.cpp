#include "../includes/system/TSystem.hpp"
#include "../includes/system/PositionSystem.hpp"
#include "../includes/system/HitSystem.hpp"
#include "../includes/system/DisplaySystem.hpp"
#include "../includes/system/InputSystem.hpp"

#include "../includes/components/Life.hpp"
#include "../includes/components/Player.hpp"
#include "../includes/components/Sprite.hpp"
#include "../includes/components/Position.hpp"
#include "../includes/components/TComponentBase.hpp"

#include "../includes/scene/SystemRegister.hpp"
#include "../includes/scene/ComponentRegister.hpp"
#include "../includes/scene/SceneBuilder.hpp"
#include "../includes/scene/SceneDirector.hpp"
#include "../includes/main.hpp"

int main(int argc, char **argv)
{
    SystemRegistry::instance().registerSystem("HitSystem", []() { return std::make_shared<HitSystem>(); });
    SystemRegistry::instance().registerSystem("PositionSystem", []() { return std::make_shared<PositionSystem>(); });
    SystemRegistry::instance().registerSystem("DisplaySystem", []() { return std::make_shared<DisplaySystem>(); });
    SystemRegistry::instance().registerSystem("InputSystem", []() { return std::make_shared<InputSystem>(); });

    ComponentRegistry::instance().registerComponent("Sprite", []() { return std::make_shared<Sprite<std::shared_ptr<sf::Sprite>>>(); });
    ComponentRegistry::instance().registerComponent("Life", []() { return std::make_shared<Life<int>>(); });
    ComponentRegistry::instance().registerComponent("Position", []() { return std::make_shared<Position<std::pair<int, int>>>(); });
    ComponentRegistry::instance().registerComponent("Player", []() { return std::make_shared<Player<bool>>(); });

    SceneDirector SceneDirector("../scene_test.json");

    TScene scene = SceneDirector.constructScene();

    scene.run();
    return 0;
}
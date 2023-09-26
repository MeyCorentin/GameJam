#include "../includes/system/TSystem.hpp"
#include "../includes/system/PositionSystem.hpp"
#include "../includes/system/HitSystem.hpp"
#include "../includes/system/DisplaySystem.hpp"
#include "../includes/system/InputSystem.hpp"

#include "../includes/components/Life.hpp"
#include "../includes/components/Player.hpp"
#include "../includes/components/Sprite.hpp"
#include "../includes/components/Position.hpp"
#include "../includes/scene/SceneBuilder.hpp"
#include "../includes/components/TComponentBase.hpp"
#include "../includes/main.hpp"

int main(int argc, char **argv)
{
    sf::Texture texture;
    texture.loadFromFile("../../sprites/test.gif");
    sf::Sprite sprite;
    sprite.setTexture(texture);

    std::shared_ptr<TSystem> SHit = std::make_shared<HitSystem>();
    std::shared_ptr<TSystem> SPosition = std::make_shared<PositionSystem>();
    std::shared_ptr<TSystem> SDisplay = std::make_shared<DisplaySystem>();
    std::shared_ptr<TSystem> SInput = std::make_shared<InputSystem>();

    std::map<std::string, std::shared_ptr<TComponentBase>> componentMap;
    componentMap["Sprite"] = std::make_shared<Sprite<sf::Sprite>>();
    componentMap["Life"] = std::make_shared<Life<int>>();
    componentMap["Position"] = std::make_shared<Position<std::pair<int, int>>>();
    componentMap["Player"] = std::make_shared<Player<bool>>();

    EntityBuilder entityBuilder(1);
    entityBuilder.addComponent(componentMap["Sprite"]->clone() , sprite)
                .addComponent(componentMap["Life"]->clone(), 1000)
                .addComponent(componentMap["Position"]->clone(), std::pair<int, int>(50, 50))
                .addComponent(componentMap["Player"]->clone(), true);

    EntityBuilder entityBuilder2(2);
    entityBuilder2.addComponent(componentMap["Sprite"]->clone(), sprite)
                .addComponent(componentMap["Life"]->clone(), 1000)
                .addComponent(componentMap["Position"]->clone(), std::pair<int, int>(100, 100))
                .addComponent(componentMap["Player"]->clone(), true);

    std::shared_ptr<TEntity> EPlayer = entityBuilder.build();
    std::shared_ptr<TEntity> EPlayer2 = entityBuilder2.build();

    SceneBuilder sceneBuilder;
    sceneBuilder.addSystem(SHit)
                .addSystem(SPosition)
                .addSystem(SDisplay)
                .addSystem(SInput)
                .addEntity(EPlayer)
                .addEntity(EPlayer2);

    TScene scene = sceneBuilder.build();
    scene.run();
    return 0;
}
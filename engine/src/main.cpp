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

    std::shared_ptr<Player<bool>> CPlayer = std::make_shared<Player<bool>>(true);
    std::shared_ptr<Sprite<sf::Sprite>> CSprite = std::make_shared<Sprite<sf::Sprite>>(sprite);
    std::shared_ptr<Life<int>> CLife = std::make_shared<Life<int>>(100);
    std::shared_ptr<Position<std::pair<int, int>>> CPosition = std::make_shared<Position<std::pair<int, int>>>(std::pair(50, 50));


    EntityBuilder entityBuilder(1);
    entityBuilder.addComponent(CSprite)
        .addComponent(CLife)
        .addComponent(CPosition)
        .addComponent(CPlayer);

    std::shared_ptr<TEntity> EPlayer = entityBuilder.build();

    SceneBuilder sceneBuilder;
    sceneBuilder.addSystem(SHit)
                .addSystem(SPosition)
                .addSystem(SDisplay)
                .addSystem(SInput)
                .addEntity(EPlayer);

    TScene scene = sceneBuilder.build();
    scene.run();
    return 0;
}
#include "../includes/system/TSystem.hpp"
#include "../includes/system/PositionSystem.hpp"
#include "../includes/system/HitSystem.hpp"
#include "../includes/component/Life.hpp"
#include "../includes/component/Position.hpp"
#include "../includes/scene/TScene.hpp"
#include "../includes/component/TComponentBase.hpp"
#include "../includes/main.hpp"

int main(int argc, char **argv)
{
    std::shared_ptr<TSystem> hitSystem = std::make_shared<HitSystem>();
    std::shared_ptr<TSystem> positionSystem = std::make_shared<PositionSystem>();

    TEntity entity1(1, {std::make_shared<Life<int>>(100), std::make_shared<Position<std::pair<int, int>>>(std::pair(0,0))});
    TEntity entity2(2, {});
    TEntity entity3(3, {std::make_shared<Life<int>>(100)});

    TScene scene({hitSystem, positionSystem}, {entity1, entity2, entity3});

    scene.run();

    return 0;
}
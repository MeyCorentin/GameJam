#pragma once

#include "../main.hpp"
#include "../entity/Entity.hpp"

class Scene;
class System {
public:
    virtual ~System() {}

    void Compute(
        int arg_is_server,
        Scene * arg_scene
    );

    virtual std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) = 0;
    virtual void Execute(
        int arg_is_server,
        Scene * arg_scene
    ) = 0;
};
#pragma once

#include "../main.hpp"
#include "../entity/IEntity.hpp"

class Scene;
class ISystem {
public:
    virtual ~ISystem() {}

    void Compute(
        int arg_is_server,
        Scene * arg_scene
    );

    virtual std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) = 0;
    virtual void Execute(
        int arg_is_server,
        Scene * arg_scene
    ) = 0;
};
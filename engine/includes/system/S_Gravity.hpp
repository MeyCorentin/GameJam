#pragma once

#include "System.hpp"
#include "../scene/Scene.hpp"

#include "../components/C_Position.hpp"
#include "../components/C_Velocity.hpp"
#include "../components/C_Gravity.hpp"
#include "../components/C_Jump.hpp"
#include "../components/C_Grounded.hpp"
#include "../components/C_Hitbox.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_PositionStorage.hpp"

class S_Gravity : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override;

        void Execute(
                int arg_is_server,
                Scene * arg_scene) override;
};
#pragma once

#include "ISystem.hpp"
#include "../scene/Scene.hpp"

#include "../components/C_Position.hpp"
#include "../components/C_Velocity.hpp"
#include "../components/C_Gravity.hpp"
#include "../components/C_Jump.hpp"
#include "../components/C_Grounded.hpp"
#include "../components/C_Hitbox.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_PositionStorage.hpp"
#include "../components/C_PlayerAmmo.hpp"

class S_Gravity : public ISystem {
    public:
        std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

        void Execute(
                int arg_is_server,
                Scene * arg_scene) override;
};
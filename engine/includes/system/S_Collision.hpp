#pragma once

#include "ISystem.hpp"
#include "../scene/Scene.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_PlayerAmmo.hpp"
#include "../components/C_Player.hpp"
#include "../components/C_Hitbox.hpp"
#include "../components/C_Life.hpp"
#include "../components/C_Follow.hpp"
#include "../components/C_Inventory.hpp"
#include "../components/C_Bonus.hpp"
#include "../components/C_Weapon.hpp"
#include "../components/C_BonusPower.hpp"
#include "../components/C_PositionFollow.hpp"
#include "../components/C_Invincibility.hpp"
#include "../components/C_TimeAutoMove.hpp"
#include "../components/C_ClockAutoMove.hpp"
#include "../components/C_IsAutoMove.hpp"
#include "../components/C_Invisible.hpp"
#include "../components/C_EnemyAmmo.hpp"
#include "../components/C_Breakable.hpp"

#include "S_Input.hpp"

class S_Collision : public ISystem {
    public:
        std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

        std::shared_ptr<IEntity> reCreateEntity(
                std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
                int id,
                std::shared_ptr<C_Position<std::pair<double, double>>> arg_position_comp,
                Scene * arg_scene);

        void Execute(
                int arg_is_server,
                Scene * arg_scene) override;
};

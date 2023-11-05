#pragma once

#include "System.hpp"
#include "../scene/Scene.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_Hitbox.hpp"
#include "../components/C_Player.hpp"
#include "../components/C_ShootCharging.hpp"
#include "../components/C_Inventory.hpp"
#include "../components/C_ChargedShoot.hpp"


class S_InputFromPlayer : public System {
    private:
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities);
        void Execute(
                int arg_is_server,
                Scene * arg_scene);
};

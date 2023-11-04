#pragma once

#include "System.hpp"
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
#include "../includes/components/C_TimeAutoMove.hpp"
#include "../includes/components/C_ClockAutoMove.hpp"
#include "../includes/components/C_IsAutoMove.hpp"
#include "../includes/components/C_Invisible.hpp"
#include "../includes/components/C_EnemyAmmo.hpp"

#include "S_Input.hpp"

class S_Collision : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override;

        std::shared_ptr<Entity> reCreateEntity(
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                int id,
                std::shared_ptr<C_Position<std::pair<double, double>>> arg_position_comp);

        void Execute(
                int arg_is_server,
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_inputs,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::vector<std::shared_ptr<sf::Music>>& arg_music_list,
                std::shared_ptr<sf::Event> event_) override;
};

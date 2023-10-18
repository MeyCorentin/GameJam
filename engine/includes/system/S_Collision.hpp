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

class S_Collision : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override;

        void Execute(
                int arg_is_server,
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_inputs,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::vector<sf::Sprite>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
                std::vector<std::shared_ptr<sf::Music>>& arg_music_list,
                std::shared_ptr<sf::Event> event_) override;
};

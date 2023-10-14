#pragma once

#include "System.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_PlayerAmmo.hpp"
#include "../components/C_Player.hpp"
#include "../components/C_Hitbox.hpp"
#include "../components/C_Life.hpp"

class S_Collision : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override;

        void DrawHitbox(
                std::shared_ptr<sf::RenderWindow> arg_window,
                const std::shared_ptr<C_Position<std::pair<double, double>>>& arg_position_comp,
                const std::shared_ptr<C_Hitbox<std::pair<int, int>>>& arg_hitbox_comp,
                bool arg_is_player,
                bool arg_is_player_ammo);

        void Execute(
                int arg_is_server,
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_inputs,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::vector<sf::Sprite>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
                std::shared_ptr<sf::Event> event_) override;
};

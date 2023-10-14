#pragma once

#include "System.hpp"
#include "../components/C_Target.hpp"
#include "../components/C_Follow.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_Shoot.hpp"
#include "../components/C_FireRate.hpp"
#include "../components/C_FireRateSpeed.hpp"
#include "../components/C_Direction.hpp"
#include "../components/C_Range.hpp"
#include "../components/C_Ammo.hpp"
#include "../components/C_Life.hpp"
#include "S_Input.hpp"

class S_Target : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override;
        void Execute(
                int arg_is_server,
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_input,
                std::vector<std::shared_ptr<Entity>>& arg_all_Entities,
                std::vector<sf::Sprite>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
                std::shared_ptr<sf::Event> event_) override;
};
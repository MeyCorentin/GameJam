#pragma once

#include "System.hpp"
#include "S_Input.hpp"
#include "../components/C_Child.hpp"
#include "../components/C_Sprite.hpp"
#include "../components/C_Life.hpp"
#include "../components/C_SpriteRect.hpp"

class S_MakeBaby : public System {
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

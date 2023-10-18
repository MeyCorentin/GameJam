#include "System.hpp"

#include "../components/C_Music.hpp"
#include "../components/C_MusicIsActive.hpp"
#include <SFML/Audio.hpp>

class S_PlayMusic : public System {
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
#include "system/S_PlayMusic.hpp"

std::vector<std::shared_ptr<Entity>> S_PlayMusic::Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) {
    std::vector<std::shared_ptr<Entity>> filtered_entities;

    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Music<std::string>)) &&
            entity->HasComponent(typeid(C_MusicIsActive<bool>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_PlayMusic::Execute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& arg_entities,
        std::shared_ptr<sf::RenderWindow> arg_window,
        std::vector<int> arg_inputs,
        std::vector<std::shared_ptr<Entity>>& arg_all_entities,
        std::vector<sf::Sprite>& arg_sprites,
        std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
        std::vector<std::shared_ptr<sf::Music>>& arg_music_list,
        std::shared_ptr<sf::Event> event_)  {

    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        std::shared_ptr<C_Music<std::string>> music_path = entity->template GetComponent<C_Music<std::string>>();
        std::shared_ptr<C_MusicIsActive<bool>> is_active = entity->template GetComponent<C_MusicIsActive<bool>>();

        auto music = arg_music_list.begin();

        if (!is_active->getValue()) {
            if (!(*music)->openFromFile(music_path->getValue()))
                std::cerr << "Failed to open file : " << music_path->getValue() << std::endl;
            (*music)->play();
            is_active->getValue() = true;
        }
    }
}
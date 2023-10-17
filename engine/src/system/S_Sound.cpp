#include "system/S_Sound.hpp"

std::vector<std::shared_ptr<Entity>> S_Sound::Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) {
    std::vector<std::shared_ptr<Entity>> filtered_entities;

    std::cout << " ---- SOUND___ ----" << std::endl;
    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Sound<sf::Sound>))) {
            std::cout << " ---- SOUND__1 ----" << std::endl;
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_Sound::Execute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& arg_entities,
        std::shared_ptr<sf::RenderWindow> arg_window,
        std::vector<int> arg_input,
        std::vector<std::shared_ptr<Entity>>& arg_all_Entities,
        std::vector<sf::Sprite>& arg_sprites,
        std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
        std::shared_ptr<sf::Event> event_)  {
    std::shared_ptr<C_Sound<sf::Sound>> sound_comp;

    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        std::cout << " ---- SOUND__2 ----" << std::endl;
        sound_comp = entity->template GetComponent<C_Sound<sf::Sound>>();
        if (sound_comp) {
            sound_comp->getValue().play();
        }
    }
}
